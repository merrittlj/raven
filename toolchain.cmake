set(TC_PATH "arm-none-eabi-")

set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

set(CMAKE_AR                    ${TC_PATH}gcc-ar)
set(CMAKE_ASM_COMPILER          ${TC_PATH}gcc)
set(CMAKE_C_COMPILER            ${TC_PATH}gcc)
set(CMAKE_CXX_COMPILER          ${TC_PATH}g++)
set(CMAKE_LINKER                ${TC_PATH}gcc)
set(CMAKE_OBJCOPY               ${TC_PATH}objcopy)
set(CMAKE_RANLIB                ${TC_PATH}gcc-ranlib)
set(CMAKE_SIZE                  ${TC_PATH}size)
set(CMAKE_STRIP                 ${TC_PATH}strip)


# Device-specific
set(DFLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(DEFINES "-DUSE_HAL_DRIVER -DSTM32WB55xx -DSTM32WB -DHAL_SPI_MODULE_ENABLED")
set(LDFLAGS "-T../src/linker.ld -nostartfiles --specs=nano.specs --specs=nosys.specs -Wl,-Map=out.map -Wl,--gc-sections")

set(CMAKE_C_FLAGS                   "-Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion -Wformat-truncation -Wno-padded -Wconversion -Wno-missing-field-initializers -Wno-unused-variable -Wno-unused-but-set-variable -ffunction-sections -fdata-sections -fno-common")
set(CMAKE_C_FLAGS					"${CMAKE_C_FLAGS} ${DFLAGS} ${DEFINES} ${LDFLAGS}")

set(CMAKE_C_FLAGS_DEBUG             "-Os -g3 -ggdb3 -DDEBUG" CACHE INTERNAL "")
set(CMAKE_C_FLAGS_RELEASE           "-Os -DNDEBUG" CACHE INTERNAL "")

set(CMAKE_CXX_FLAGS                 "${CMAKE_C_FLAGS}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_C_FLAGS_DEBUG}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_C_FLAGS_RELEASE}" CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM     NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY     ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE     ONLY)

# Optionally reduce compiler sanity check when cross-compiling
set(CMAKE_TRY_COMPILE_TARGET_TYPE         STATIC_LIBRARY)
