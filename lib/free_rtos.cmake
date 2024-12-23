# No version
FetchContent_Declare(freertos_kernel
    GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
    GIT_TAG V11.1.0
)

set(RTOS_PORTABLE ARM_CM4F)

add_library(freertos_config INTERFACE)
add_library(lib::free_rtos_config ALIAS freertos_config)

target_include_directories(freertos_config SYSTEM
INTERFACE
${PROJECT_SOURCE_DIR}
)

target_compile_definitions(freertos_config
  INTERFACE
    projCOVERAGE_TEST=0
)

target_compile_definitions(freertos_config INTERFACE ${definitions})
target_compile_options(freertos_config INTERFACE ${options})

if (CMAKE_CROSSCOMPILING)
  set(FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "" FORCE)
endif()

FetchContent_MakeAvailable(freertos_kernel)

include_directories(
    ${freertos_kernel_SOURCE_DIR}/include
    ${freertos_kernel_SOURCE_DIR}/portable/GCC/${RTOS_PORTABLE}
)

add_library(rtos
    ${freertos_kernel_SOURCE_DIR}/tasks.c
    ${freertos_kernel_SOURCE_DIR}/list.c
    ${freertos_kernel_SOURCE_DIR}/timers.c
    ${freertos_kernel_SOURCE_DIR}/queue.c

    ${freertos_kernel_SOURCE_DIR}/portable/GCC/${RTOS_PORTABLE}/port.c
    ${freertos_kernel_SOURCE_DIR}/portable/MemMang/heap_4.c
)
add_library(lib::rtos ALIAS rtos)

target_include_directories(rtos
    PRIVATE
    ${freertos_kernel_SOURCE_DIR}/include
    ${freertos_kernel_SOURCE_DIR}/portable/GCC/${RTOS_PORTABLE}
)

target_link_libraries(rtos
    PUBLIC
    lib::free_rtos_config
)
