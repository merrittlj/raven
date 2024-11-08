cmake_minimum_required(VERSION 3.29)
include(FetchContent)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmake")
set(CMAKE_GENERATOR Ninja)

project(raven
		VERSION 0.2
		DESCRIPTION "Smartwatch"
		LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_BINARY_DIR 				${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_BINARY_DIR})
set(PROJECT_SOURCE_DIR 				${CMAKE_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR 			${CMAKE_SOURCE_DIR}/include)
set(PROJECT_LIBRARY_DIR 			${CMAKE_SOURCE_DIR}/lib)

if(NOT CMAKE_BUILD_TYPE) # Set mode to debug by default
    set(CMAKE_BUILD_TYPE Debug)
endif()

###############################

include(${PROJECT_LIBRARY_DIR}/stm_cube.cmake) # STM32 CMSIS/HAL/Drivers, Arm CMSIS/RTOS
include(${PROJECT_LIBRARY_DIR}/debouncer.cmake)
include(${PROJECT_LIBRARY_DIR}/lvgl.cmake)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/stm32 # For stm*hal_conf
        ${PROJECT_SOURCE_DIR}/app # For utilities_common
        ${PROJECT_SOURCE_DIR}/ble # For ble_common
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/core/main.cpp
    ${PROJECT_SOURCE_DIR}/core/syscalls.c
    ${PROJECT_SOURCE_DIR}/core/sysmem.c

    ${PROJECT_SOURCE_DIR}/stm32/stm32wbxx_it.cpp

    ${PROJECT_SOURCE_DIR}/hw/hw_ipcc.cpp

    ${PROJECT_SOURCE_DIR}/app/app_debug.cpp

    ${PROJECT_SOURCE_DIR}/ble/gatt_service.cpp

    ${PROJECT_SOURCE_DIR}/gpio/gpio.cpp
)

target_link_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
		lib::stm_cube
        lib::debouncer
        lib::lvgl
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

# list size of executable after building
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
        COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}
)

# generate .hex and .bin files after building
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME} ${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
)

add_custom_target(flash
    COMMAND openocd -f interface/stlink.cfg -f board/st_nucleo_wb55.cfg -c "program ${PROJECT_NAME} verify reset exit"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(debug
    COMMAND openocd -f interface/stlink.cfg -f board/st_nucleo_wb55.cfg -c "init" &
    COMMAND arm-none-eabi-gdb ${PROJECT_NAME} -x ${CMAKE_SOURCE_DIR}/.gdbconf
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(serial
    COMMAND picocom -b 9600 -f n -y n -d 8 -p 1 -c /dev/ttyUSB0
    DEPENDS ${PROJECT_NAME}
)
