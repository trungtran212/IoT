/*
 * lcd.c
 *
 *  Created on: Nov 4, 2024
 *      Author: Phat_Dang
 */
#include <stdio.h>

#include "sl_board_control.h"
#include "em_assert.h"
#include "glib.h"
#include "dmd.h"
#include "global.h"

#ifndef LCD_MAX_LINES
#define LCD_MAX_LINES      11
#endif

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static GLIB_Context_t glibContext;
static int currentLine = 0;

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize example.
 ******************************************************************************/
void memlcd_app_init(void)
{
  uint32_t status;

  /* Enable the memory lcd */
  status = sl_board_enable_display();
  EFM_ASSERT(status == SL_STATUS_OK);

  /* Initialize the DMD support for memory lcd display */
  status = DMD_init(0);
  EFM_ASSERT(status == DMD_OK);

  /* Initialize the glib context */
  status = GLIB_contextInit(&glibContext);
  EFM_ASSERT(status == GLIB_OK);

  glibContext.backgroundColor = White;
  glibContext.foregroundColor = Black;

  /* Fill lcd with background color */
  GLIB_clear(&glibContext);

  /* Use Narrow font */
  GLIB_setFont(&glibContext, (GLIB_Font_t *) &GLIB_FontNarrow6x8);

  /* Draw text on the memory lcd display*/
  GLIB_drawStringOnLine(&glibContext,
                        "",
                        currentLine,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);

  DMD_updateDisplay();
}

void memlcd_update(global_data_t *data)
{

  int line = 0;
  char tempStr[50];
  char humidStr[50];
  char rPeriodStr[50];
  char advPeriodStr[50];
  char cntStr[50];

  snprintf(tempStr, 50, "Nhiet do: %d.%d *C", data->tempInt, data->tempFrac);
  snprintf(humidStr, 50, "Do am: %d.%d %%", data->humidInt, data->humidFrac);
  snprintf(rPeriodStr, 50, "Sample Period: %d", data->rPeriod);
  snprintf(advPeriodStr, 50, "ADV BLE Time: %d", data->advPeriod);

  GLIB_clear(&glibContext);

   GLIB_drawStringOnLine(&glibContext,
                         "Trung",
                         line++,
                         GLIB_ALIGN_CENTER,
                         0,
                         5,
                         true);
line++;
   GLIB_drawStringOnLine(&glibContext,
                         tempStr,
                         line++,
                         GLIB_ALIGN_LEFT,
                         5,
                         5,
                         true);

   GLIB_drawStringOnLine(&glibContext,
                         humidStr,
                         line++,
                         GLIB_ALIGN_LEFT,
                         5,
                         5,
                         true);

   GLIB_drawStringOnLine(&glibContext,
                         rPeriodStr,
                         line++,
                         GLIB_ALIGN_LEFT,
                         5,
                         5,
                         true);

   GLIB_drawStringOnLine(&glibContext,
                         advPeriodStr,
                         line++,
                         GLIB_ALIGN_LEFT,
                         5,
                         5,
                         true);
 }


/***************************************************************************//**
 * Ticking function.
 ******************************************************************************/
void memlcd_app_process_action(float)
{
  return;
}

