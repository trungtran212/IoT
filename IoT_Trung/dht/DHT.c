#include "sl_udelay.h"
#include "DHT.h"
#include "stdint.h"
#include "stdbool.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "app_log.h"
#include "global.h"

#define DHT_PORT gpioPortB
#define DHT_PIN 0
#define TIMEOUT_THRESHOLD 1000

uint8_t Humid_Int, Humid_Frac, Temp_Int, Temp_Frac;
uint16_t SUM;
uint8_t Presence = 0;

void DHT_Start(void) {
    CMU_ClockEnable(cmuClock_GPIO, true);
    GPIO_PinModeSet(DHT_PORT, DHT_PIN, gpioModePushPull, 0);
    GPIO_PinOutClear(DHT_PORT, DHT_PIN);
    sl_udelay_wait(18000); // chờ 18ms
    GPIO_PinOutSet(DHT_PORT, DHT_PIN);
    sl_udelay_wait(20); // chờ 20us
    GPIO_PinModeSet(DHT_PORT, DHT_PIN, gpioModeInputPullFilter, 1);
}

uint8_t DHT_Check_Response(void) {
    uint8_t Response = 0;
    uint32_t timeout = 0;

    sl_udelay_wait(40);
    if (!(GPIO_PinInGet(DHT_PORT, DHT_PIN))) {
        sl_udelay_wait(80);
        if ((GPIO_PinInGet(DHT_PORT, DHT_PIN))) {
            Response = 1;
        } else {
            Response = -1;
        }
    }

    timeout = 0;
    while ((GPIO_PinInGet(DHT_PORT, DHT_PIN))) {
        if (++timeout > TIMEOUT_THRESHOLD) {
            return -1; // Trả về lỗi nếu vượt timeout
        }
    }

    return Response;
}

uint8_t DHT_Read(void) {
    uint8_t data = 0;

    for (int i = 0; i < 8; i++) {
        uint32_t timeout = 0;

        while (!(GPIO_PinInGet(DHT_PORT, DHT_PIN))) {
            if (++timeout > TIMEOUT_THRESHOLD) {
                return 0xFF; // Trả về lỗi
            }
        }

        sl_udelay_wait(40);

        if (!(GPIO_PinInGet(DHT_PORT, DHT_PIN))) {
            data &= ~(1 << (7 - i)); // Ghi 0
        } else {
            data |= (1 << (7 - i)); // Ghi 1
        }

        timeout = 0;
        while ((GPIO_PinInGet(DHT_PORT, DHT_PIN))) {
            if (++timeout > TIMEOUT_THRESHOLD) {
                return 0xFF; // Trả về lỗi
            }
        }
    }

    return data;
}

void DHT_GetData(global_data_t *data ) {
    DHT_Start();
    Presence = DHT_Check_Response();

    if (Presence != 1) {
        //Error: No response from DHT11
        return;
    }

    Humid_Int = DHT_Read();
    if (Humid_Int == 0xFF) {
        //Error: Timeout reading Humid_Int
        return;
    }

    Humid_Frac = DHT_Read();
    if (Humid_Frac == 0xFF) {
        //Error: Timeout reading Humid_Frac
        return;
    }

    Temp_Int = DHT_Read();
    if (Temp_Int == 0xFF) {
        //Error: Timeout reading Temp_Int
        return;
    }

    Temp_Frac = DHT_Read();
    if (Temp_Frac == 0xFF) {
        //Error: Timeout reading Temp_Frac
        return;
    }

    SUM = DHT_Read();
    if (SUM == 0xFF) {
        //Error: Timeout reading SUM
        return;
    }

    if (SUM == (Humid_Int + Humid_Frac + Temp_Int + Temp_Frac)) {
        data->tempInt = Temp_Int;
        data->tempFrac = Temp_Frac;
        data->humidInt = Humid_Int;
        data->humidFrac = Humid_Frac;
        data->cnt++;
    }
    //Error: Checksum mismatch
}
