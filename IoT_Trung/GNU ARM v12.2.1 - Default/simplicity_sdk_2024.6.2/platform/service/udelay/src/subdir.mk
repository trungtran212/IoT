################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk/platform/service/udelay/src/sl_udelay.c 

S_UPPER_SRCS += \
C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.S 

OBJS += \
./simplicity_sdk_2024.6.2/platform/service/udelay/src/sl_udelay.o \
./simplicity_sdk_2024.6.2/platform/service/udelay/src/sl_udelay_armv6m_gcc.o 

C_DEPS += \
./simplicity_sdk_2024.6.2/platform/service/udelay/src/sl_udelay.d 


# Each subdirectory must supply rules for building sources it contributes
simplicity_sdk_2024.6.2/platform/service/udelay/src/sl_udelay.o: C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk/platform/service/udelay/src/sl_udelay.c simplicity_sdk_2024.6.2/platform/service/udelay/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c18 '-DEFR32MG21A020F1024IM32=1' '-DSL_APP_PROPERTIES=1' '-DBOOTLOADER_APPLOADER=1' '-DSL_BOARD_NAME="BRD4180B"' '-DSL_BOARD_REV="A03"' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DHFXO_FREQ=38400000' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DCMSIS_NVIC_VIRTUAL=1' '-DCMSIS_NVIC_VIRTUAL_HEADER_FILE="cmsis_nvic_virtual.h"' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DSL_MEMORY_POOL_LIGHT=1' '-DSL_CODE_COMPONENT_POWER_MANAGER=power_manager' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DSL_CODE_COMPONENT_CORE=core' '-DSL_CODE_COMPONENT_SLEEPTIMER=sleeptimer' '-DSLI_RADIOAES_REQUIRES_MASKING=1' -I"C:\Users\ACER\SimplicityStudio\v5_workspace\IoT_Trung\autogen" -I"C:\Users\ACER\SimplicityStudio\v5_workspace\IoT_Trung\config" -I"C:\Users\ACER\SimplicityStudio\v5_workspace\IoT_Trung\config\btconf" -I"C:\Users\ACER\SimplicityStudio\v5_workspace\IoT_Trung" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/Device/SiliconLabs/EFR32MG21/Include" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/common/util/app_assert" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/common/util/app_log" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/common/util/app_timer" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/common/util/app_timer/bm" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//protocol/bluetooth/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/common/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//protocol/bluetooth/bgcommon/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//protocol/bluetooth/bgstack/ll/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//hardware/board/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/bootloader" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/bootloader/api" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/clock_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/clock_manager/src" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/CMSIS/Core/Include" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/driver/debug/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/device_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/emdrv/dmadrv/inc/s2_signals" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/emdrv/common/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/emlib/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/bluetooth/common/gatt_service_device_information" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/bluetooth/common/in_place_ota_dfu" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/interrupt_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/interrupt_manager/inc/arm" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/iostream/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/sl_mbedtls_support/config" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/sl_mbedtls_support/config/preset" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/sl_mbedtls_support/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//util/third_party/mbedtls/include" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//util/third_party/mbedtls/library" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/memory_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/memory_manager/src" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/memory_manager/profiler/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/mpu/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/emdrv/nvm3/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/power_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/sl_psa_driver/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/common" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/protocol/ble" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/protocol/ieee802154" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/protocol/wmbus" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/protocol/zwave" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/protocol/sidewalk" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/plugin/pa-conversions" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/plugin/pa-conversions/efr32xg21" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/plugin/rail_util_pti" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/plugin/rail_util_rf_path" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/se_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/se_manager/src" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/common/toolchain/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/system/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/sleeptimer/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/sl_protocol_crypto/src" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/udelay/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"simplicity_sdk_2024.6.2/platform/service/udelay/src/sl_udelay.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

simplicity_sdk_2024.6.2/platform/service/udelay/src/sl_udelay_armv6m_gcc.o: C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.S simplicity_sdk_2024.6.2/platform/service/udelay/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -I"C:\Users\ACER\SimplicityStudio\v5_workspace\IoT_Trung\autogen" -I"C:\Users\ACER\SimplicityStudio\v5_workspace\IoT_Trung\config" -I"C:\Users\ACER\SimplicityStudio\v5_workspace\IoT_Trung\config\btconf" -I"C:\Users\ACER\SimplicityStudio\v5_workspace\IoT_Trung" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/Device/SiliconLabs/EFR32MG21/Include" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/common/util/app_assert" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/common/util/app_log" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/common/util/app_timer" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/common/util/app_timer/bm" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//protocol/bluetooth/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/common/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//protocol/bluetooth/bgcommon/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//protocol/bluetooth/bgstack/ll/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//hardware/board/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/bootloader" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/bootloader/api" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/clock_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/clock_manager/src" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/CMSIS/Core/Include" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/driver/debug/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/device_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/emdrv/dmadrv/inc/s2_signals" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/emdrv/common/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/emlib/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/bluetooth/common/gatt_service_device_information" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//app/bluetooth/common/in_place_ota_dfu" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/interrupt_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/interrupt_manager/inc/arm" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/iostream/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/sl_mbedtls_support/config" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/sl_mbedtls_support/config/preset" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/sl_mbedtls_support/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//util/third_party/mbedtls/include" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//util/third_party/mbedtls/library" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/memory_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/memory_manager/src" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/memory_manager/profiler/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/mpu/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/emdrv/nvm3/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/power_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/sl_psa_driver/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/common" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/protocol/ble" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/protocol/ieee802154" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/protocol/wmbus" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/protocol/zwave" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/protocol/sidewalk" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/plugin/pa-conversions" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/plugin/pa-conversions/efr32xg21" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/plugin/rail_util_pti" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/radio/rail_lib/plugin/rail_util_rf_path" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/se_manager/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/se_manager/src" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/common/toolchain/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/system/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/sleeptimer/inc" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/security/sl_component/sl_protocol_crypto/src" -I"C:/Users/ACER/SimplicityStudio/SDKs/simplicity_sdk//platform/service/udelay/inc" '-DEFR32MG21A020F1024IM32=1' '-DSL_APP_PROPERTIES=1' '-DBOOTLOADER_APPLOADER=1' '-DSL_BOARD_NAME="BRD4180B"' '-DSL_BOARD_REV="A03"' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DHFXO_FREQ=38400000' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DCMSIS_NVIC_VIRTUAL=1' '-DCMSIS_NVIC_VIRTUAL_HEADER_FILE="cmsis_nvic_virtual.h"' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DSL_MEMORY_POOL_LIGHT=1' '-DSL_CODE_COMPONENT_POWER_MANAGER=power_manager' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DSL_CODE_COMPONENT_CORE=core' '-DSL_CODE_COMPONENT_SLEEPTIMER=sleeptimer' '-DSLI_RADIOAES_REQUIRES_MASKING=1' -mfpu=fpv5-sp-d16 -mfloat-abi=hard -imacrossl_gcc_preinclude.h -c -x assembler-with-cpp -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


