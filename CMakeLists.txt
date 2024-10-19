cmake_minimum_required(VERSION 3.29)
include(FetchContent)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmake")

project(raven
		VERSION 0.2
		DESCRIPTION "Smartwatch"
		LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/core/main.cpp
    ${PROJECT_SOURCE_DIR}/core/syscalls.c
    ${PROJECT_SOURCE_DIR}/core/sysmem.c
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
        cxx_std_23
)
