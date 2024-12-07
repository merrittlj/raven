# v1.20.0
FetchContent_Declare(STM32CubeWB
    GIT_REPOSITORY https://github.com/STMicroelectronics/STM32CubeWB.git
    GIT_TAG v1.20.0
)
FetchContent_MakeAvailable(STM32CubeWB)

set(SYSTEM_SRC ${stm32cubewb_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32WBxx/Source/Templates/system_stm32wbxx.c)
set(STARTUP_SRC ${stm32cubewb_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32WBxx/Source/Templates/gcc/startup_stm32wb55xx_cm4.s)

set(LINKER_SCRIPT ${stm32cubewb_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32WBxx/Source/Templates/gcc/linker/stm32wb55xx_flash_cm4.ld)
add_library(STM32CubeWB
    ${SYSTEM_SRC}
    ${STARTUP_SRC}
    ${stm32cubewb_SOURCE_DIR}/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal.c
    ${stm32cubewb_SOURCE_DIR}/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_pwr.c
    ${stm32cubewb_SOURCE_DIR}/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_pwr_ex.c
    ${stm32cubewb_SOURCE_DIR}/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_rcc.c
    ${stm32cubewb_SOURCE_DIR}/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_rcc_ex.c
    ${stm32cubewb_SOURCE_DIR}/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_cortex.c
    ${stm32cubewb_SOURCE_DIR}/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_gpio.c
    ${stm32cubewb_SOURCE_DIR}/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_hal_spi.c

    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/ble/core/auto/ble_gatt_aci.c 
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/ble/core/template/osal.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/tl_mbox.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/utilities/stm_list.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/hci_tl.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/shci_tl.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci/shci.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/shci_tl_if.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/hci_tl_if.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/ble/svc/Src/svc_ctl.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/utilities/otp.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/ble/core/auto/ble_hal_aci.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/ble/core/auto/ble_hci_le.c
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/ble/core/auto/ble_gap_aci.c
    ${stm32cubewb_SOURCE_DIR}/
)
add_library(lib::stm_cube ALIAS STM32CubeWB)

set_source_files_properties(${STARTUP_SRC} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")
set_source_files_properties(${SYSTEM_SRC} PROPERTIES COMPILE_FLAGS "-Wno-sign-conversion")
set_property(SOURCE ${STARTUP_SRC} PROPERTY LANGUAGE C)

target_compile_options(STM32CubeWB
    PUBLIC
        -Wno-sign-conversion
        -Wno-conversion
        -Wno-undef
        -Wno-unused-parameter
)

target_include_directories(STM32CubeWB
    PRIVATE
        ${PROJECT_SOURCE_DIR}/stm32
)

include_directories(
    ${stm32cubewb_SOURCE_DIR}/Drivers/STM32WBxx_HAL_Driver/Inc
    ${stm32cubewb_SOURCE_DIR}/Drivers/CMSIS/Include
    ${stm32cubewb_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32WBxx/Include

    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread # hw.h
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/ble/core # ble_bufsize.h
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/ble/core/auto # ble_types.h
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/utilities # utilities_common.h
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci # shci.h
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl # mbox_def.h
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN # stm32_wpan_common.h
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/ble # ble_common.h
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/ble/core/template # ble_const.h
    ${stm32cubewb_SOURCE_DIR}/Middlewares/ST/STM32_WPAN/ble/svc/Inc # svc_ctl.h
)
