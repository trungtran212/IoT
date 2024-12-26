/***************************************************************************//**
 * @file
 * @brief main() function.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "sl_component_catalog.h"
#include "sl_system_init.h"
#include "app.h"
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif // SL_CATALOG_POWER_MANAGER_PRESENT
#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "sl_system_kernel.h"
#else // SL_CATALOG_KERNEL_PRESENT
#include "sl_system_process_action.h"
#endif // SL_CATALOG_KERNEL_PRESENT

#include <string.h>
#include "lcd/app_lcd.h"
#include "app.h"
#include "global.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_cmu.h"

#define BSP_TXPORT gpioPortA
#define BSP_RXPORT gpioPortA
#define BSP_TXPIN 5
#define BSP_RXPIN 6
#define BSP_ENABLE_PORT gpioPortD
#define BSP_ENABLE_PIN 4

#define BSP_GPIO_LED0_PORT gpioPortD
#define BSP_GPIO_LED0_PIN 2
#define BSP_GPIO_LED1_PORT gpioPortD
#define BSP_GPIO_LED1_PIN 3
#define BSP_GPIO_PB0_PORT gpioPortB
#define BSP_GPIO_PB0_PIN 0
#define BSP_GPIO_PB1_PORT gpioPortB
#define BSP_GPIO_PB1_PIN 1

// Size of the buffer for received data
#define BUFLEN  10

// Receive data buffer
uint8_t buffer[BUFLEN];

// Current position in buffer
uint32_t inpos = 0;

// Flag for interrupt
uint8_t flag_usart_rx = 0;

int cmd = -1, data = 0, len = 0;
/**************************************************************************//**
 * @brief
 *    GPIO initialization
 *****************************************************************************/
void initGPIO (void)
{
  CMU_ClockEnable (cmuClock_GPIO, true);
  GPIO_PinModeSet (BSP_TXPORT, BSP_TXPIN, gpioModePushPull, 1);
  GPIO_PinModeSet (BSP_RXPORT, BSP_RXPIN, gpioModeInput, 0);
  GPIO_PinModeSet (BSP_ENABLE_PORT, BSP_ENABLE_PIN, gpioModePushPull, 1);
}

/**************************************************************************//**
 * @brief
 *    USART0 initialization
 *****************************************************************************/
void initUSART0 (void)
{
  CMU_ClockEnable (cmuClock_USART0, true);
  USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
  init.baudrate = 115200;

  // Configure USART
  USART_InitAsync (USART0, &init);

  // Route USART0 TX and RX
  GPIO->USARTROUTE[0].TXROUTE = (BSP_TXPORT << _GPIO_USART_TXROUTE_PORT_SHIFT)
      | (BSP_TXPIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[0].RXROUTE = (BSP_RXPORT << _GPIO_USART_RXROUTE_PORT_SHIFT)
      | (BSP_RXPIN << _GPIO_USART_RXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN |
  GPIO_USART_ROUTEEN_TXPEN;

  // Enable RX interrupt
  USART_IntClear (USART0, USART_IF_RXDATAV);
  USART_IntEnable (USART0, USART_IEN_RXDATAV);
  NVIC_ClearPendingIRQ(USART0_RX_IRQn);
  NVIC_EnableIRQ(USART0_RX_IRQn);
}

/**************************************************************************//**
 * @brief
 *    The USART0 receive interrupt saves incoming characters.
 *****************************************************************************/
void USART0_RX_IRQHandler(void)
{
  // Get the character just received
  uint8_t received_char = USART0->RXDATA;

  // Save data to buffer if space is available
  if ((received_char != '\r') && (inpos < BUFLEN - 1))
    {
      buffer[inpos++] = received_char;
    }
  else
    {
      buffer[inpos] = '\0'; // Null-terminate string
      inpos = 0;            // Reset position
      flag_usart_rx = 1;    // Set flag to process data
    }

  // Clear interrupt flag
  USART_IntClear (USART0, USART_IF_RXDATAV);
}

void initLED_BUTTON(void)
{
  CMU_ClockEnable(cmuClock_GPIO, true);

  GPIO_PinModeSet(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, gpioModeInputPullFilter, 1);
  GPIO_PinModeSet(BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN, gpioModeInputPullFilter, 1);

  GPIO_PinModeSet(BSP_GPIO_LED0_PORT, BSP_GPIO_LED0_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(BSP_GPIO_LED1_PORT, BSP_GPIO_LED1_PIN, gpioModePushPull, 0);
}


int main (void)
{
  // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
  // Note that if the kernel is present, processing task(s) will be created by
  // this call.
  sl_system_init ();

  // Initialize the application. For example, create periodic timer(s) or
  // task(s) if the kernel is present.
  app_init ();

  memlcd_app_init ();

  initGPIO ();
  initUSART0 ();
  initLED_BUTTON();
  USART_IntEnable (USART0, USART_IEN_RXDATAV);

#if defined(SL_CATALOG_KERNEL_PRESENT)
  // Start the kernel. Task(s) created in app_init() will start running.
  sl_system_kernel_start();
#else // SL_CATALOG_KERNEL_PRESENT
  while (1)
    {
      // Do not remove this call: Silicon Labs components process action routine
      // must be called from the super loop.
      sl_system_process_action ();

      // Application process.
      app_process_action ();

      // Check USART flag
      if (flag_usart_rx)
        {
          flag_usart_rx = 0; // Clear flag

          len = strlen ((char*) buffer);

          // Extract command and data
          cmd = buffer[0] - '0';
          data = 0;

          for (int i = 1; i < len; i++)
            {
              data = data * 10 + (buffer[i] - '0');
            }

          // Process command
          switch (cmd)
            {
            case 1:
              updateReadPeriod(data);
              for (int i = 0; i < BUFLEN; i++)
                {

                  buffer[i] = 0;
                }
              break;

            case 2:
              updateADVPeriod(data);
              for (int i = 0; i < BUFLEN; i++)
                {

                  buffer[i] = 0;
                }

              break;

            case 3:
             getDataUART();

              break;

            default:
              break;
            }
        }
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
      // Let the CPU go to sleep if the system allows it.
      sl_power_manager_sleep ();
#endif
    }
#endif // SL_CATALOG_KERNEL_PRESENT
}
