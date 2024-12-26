/***************************************************************************//**
 * @file
 * @brief Core application logic.
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
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "app.h"
#include "app_timer.h"
#include "gatt_db.h"
#include "app_log.h"
#include "global.h"
#include "sl_udelay.h"
#include "em_usart.h"
#include "dht/DHT.h"
#include "lcd/app_lcd.h"
#include "ble/custom_adv.h"

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;
uint32_t Student_ID     = 0x21200247;

static app_timer_t update_timer;
static global_data_t globalData = {0,0,0,0,1000,1000,0};
CustomAdv_t sData;

static void update_timer_cb(app_timer_t *timer, void *data)
{
  (void)data;
  (void)timer;

  DHT_GetData(&globalData);
  handleData();
  memlcd_update(&globalData);

  uint32_t bleData = (uint32_t)(globalData.tempInt / 10) << 28
                | (uint32_t)(globalData.tempInt % 10) << 24
                | (uint32_t)(globalData.tempFrac / 10) << 20
                | (uint32_t)(globalData.tempFrac % 10) << 16
                | (uint32_t)(globalData.humidInt / 10) << 12
                | (uint32_t)(globalData.humidInt % 10) << 8
                | (uint32_t)(globalData.humidFrac / 10) << 4
                | (uint32_t)(globalData.humidFrac % 10);


  update_adv_data(&sData, advertising_set_handle,bleData);
}

void handleData(void)
{
  if(globalData.tempFrac < 10)
    {
      globalData.tempFrac *=10;
    }

  if(globalData.humidFrac < 10)
    {
      globalData.humidFrac *= 10;
    }
}
/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////

  sl_status_t sc;

  sc = app_timer_start(&update_timer,
                             1000,              //ms
                             update_timer_cb,
                             NULL,
                             true);
   app_assert_status(sc);
}



/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;
  uint8_t system_id[8];

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:

      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      app_assert_status(sc);

      // Pad and reverse unique ID to get System ID.
      system_id[0] = address.addr[5];
      system_id[1] = address.addr[4];
      system_id[2] = address.addr[3];
      system_id[3] = 0xFF;
      system_id[4] = 0xFE;
      system_id[5] = address.addr[2];
      system_id[6] = address.addr[1];
      system_id[7] = address.addr[0];

      sc = sl_bt_gatt_server_write_attribute_value(gattdb_system_id,
                                                   0,
                                                   sizeof(system_id),
                                                   system_id);
      app_assert_status(sc);

      // Create an advertising set.
      sc = sl_bt_advertiser_create_set(&advertising_set_handle);
      app_assert_status(sc);

      // Set advertising interval to 1s.
      sc = sl_bt_advertiser_set_timing(
        advertising_set_handle,
        1600, // min. adv. interval (milliseconds * 1.6)
        1600, // max. adv. interval (milliseconds * 1.6)
        0,   // adv. duration
        0);  // max. num. adv. events
      app_assert_status(sc);

      // Setting channel
      sl_bt_advertiser_set_channel_map(advertising_set_handle, 7);
      app_assert_status(sc);

      //Add data to Adv packet
      fill_adv_packet(&sData, FLAG, COMPANY_ID, Student_ID, "TEAM 7");
      app_log("fill_adv_packet completed\r\n");

      //Strart advertise
      start_adv(&sData, advertising_set_handle);
      app_log("Started advertising\r\n");

      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      // Generate data for advertising
      sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                                 sl_bt_advertiser_general_discoverable);
      app_assert_status(sc);

      // Restart advertising after client has disconnected.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_advertiser_connectable_scannable);
      app_assert_status(sc);
      break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}

void getDataUART()
{
    app_log("Trung\r\n\n");
    app_log("Nhiet do: %d.%d *C\r\n",globalData.tempInt,globalData.tempFrac);
    app_log("Do am: %d.%d %\r\n", globalData.humidInt,globalData.humidFrac);
    app_log("ADV BLE Time: %d\r\n", globalData.advPeriod);
    app_log("Sample Period: %d\r\n", globalData.rPeriod);
}

void updateADVPeriod(int newPeriod)
{
  sl_status_t sc;

  sc = sl_bt_advertiser_stop(advertising_set_handle);
  app_assert_status(sc);

  globalData.advPeriod = newPeriod;

  sc = sl_bt_advertiser_set_timing(
    advertising_set_handle,
    globalData.advPeriod*1.6, // min. adv. interval (milliseconds * 1.6)
    globalData.advPeriod*1.6, // max. adv. interval (milliseconds * 1.6)
    0,   // adv. duration
    0);  // max. num. adv. events

  app_assert_status(sc);
  start_adv(&sData, advertising_set_handle);

}

void updateReadPeriod(int newPeriod)
{
  sl_status_t sc;
  sc = app_timer_stop(&update_timer);
  app_assert_status(sc);

  globalData.rPeriod = newPeriod;

  sc = app_timer_start(&update_timer,
                             globalData.rPeriod,              //ms
                             update_timer_cb,
                             NULL,
                             true);
  app_assert_status(sc);

}


