# v1.20.0
FetchContent_Declare(STM32CubeWB
    GIT_REPOSITORY https://github.com/STMicroelectronics/STM32CubeWB.git
    GIT_TAG v1.20.0
)
FetchContent_MakeAvailable(STM32CubeWB)

set(STARTUP_SRC ${stm32cubewb_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32WBxx/Source/Templates/gcc/startup_stm32wb55xx_cm4.s)
set(LINKER_SCRIPT ${stm32cubewb_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32WBxx/Source/Templates/gcc/linker/stm32wb55xx_flash_cm4.ld)
add_library(STM32CubeWB
    ${stm32cubewb_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32WBxx/Source/Templates/system_stm32wbxx.c
    ${STARTUP_SRC}
)
add_library(lib::stm_cube ALIAS STM32CubeWB)

set_source_files_properties(${STARTUP_SRC} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")
set_property(SOURCE ${STARTUP_SRC} PROPERTY LANGUAGE C)

target_include_directories(STM32CubeWB
    PUBLIC
        ${stm32cubewb_SOURCE_DIR}/Drivers/STM32WBxx_HAL_Driver/Inc
        ${stm32cubewb_SOURCE_DIR}/Drivers/CMSIS/Inc
        ${stm32cubewb_SOURCE_DIR}/Drivers/CMSIS/Device/Inc
)
