cmake_minimum_required(VERSION 3.28.0)

set(CMAKE_TOOLCHAIN_FILE "toolchain.cmake")
project(ocelot
		VERSION 0.2
		DESCRIPTION "Smartwatch"
		LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR 				${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_BINARY_DIR})
set(PROJECT_SOURCE_DIR 				${CMAKE_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR 			${CMAKE_SOURCE_DIR}/include)
set(PROJECT_LIBRARIES_DIR 			${CMAKE_SOURCE_DIR}/libs)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message("WARNING: Ocelot is only supported(compilation-wise) on Linux!")
endif()

if(NOT CMAKE_BUILD_TYPE) # Set mode to debug by default
    set(CMAKE_BUILD_TYPE Debug)
endif()

###############################

set(ARM_CMSIS_DIR "${PROJECT_LIBRARIES_DIR}/CMSIS_6")
add_subdirectory(${ARM_CMSIS_DIR} EXCLUDE_FROM_ALL)

set(STM_CMSIS_DIR "${PROJECT_LIBRARIES_DIR}/cmsis_device_wb")
add_subdirectory(${STM_CMSIS_DIR} EXCLUDE_FROM_ALL)

set(STM_HAL_DIR "${PROJECT_LIBRARIES_DIR}/stm32wbxx_hal_driver")
add_subdirectory(${STM_HAL_DIR} EXCLUDE_FROM_ALL)

set(DEBOUNCER_DIR "${PROJECT_LIBRARIES_DIR}/Button_Debouncer")
add_subdirectory(${DEBOUNCER_DIR} EXCLUDE_FROM_ALL)

set(LVGL_DIR "${PROJECT_LIBRARIES_DIR}/lvgl")
add_subdirectory(${LVGL_DIR} EXCLUDE_FROM_ALL)

set(FREE_RTOS_DIR "${PROJECT_LIBRARIES_DIR}/FreeRTOS")
add_subdirectory(${FREE_RTOS_DIR} EXCLUDE_FROM_ALL)

target_include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/main.cpp
)

target_link_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        CMSIS_6
        cmsis_device_wb
		stm32wbxx_hal_driver
        Button_Debouncer
        lvgl
		FreeRTOS
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
#target_compile_definitions(${PROJECT_NAME} PRIVATE
