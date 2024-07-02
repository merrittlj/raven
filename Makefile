PROJECT_NAME = raven
TARGET       = $(PROJECT_NAME).elf

# Directories
BUILD_DIR      = build
SRC_DIRS       = src
INCLUDE_DIR    = $(SRC_DIRS)/include
CMSIS_GCC_DIR  = $(INCLUDE_DIR)/cmsis_wb/Source/Templates/gcc

# Hardware specific
STARTUP := $(CMSIS_GCC_DIR)/startup_stm32wb55xx_cm4.s
LSCRIPT := $(CMSIS_GCC_DIR)/linker/stm32wb55xx_flash_cm4.ld
DFLAGS  := -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
DEFINES := -DUSE_HAL_DRIVER -DSTM32WB55xx

# Hardware toolchain
CC  := arm-none-eabi-gcc
LD  := arm-none-eabi-gcc
CPY := arm-none-eabi-objcopy
GDB := arm-none-eabi-gdb

# Source files, objects, & dependencies
SRCS := $(filter-out $(SRC_DIRS)/include/*, $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s))
SRCS += STARTUP
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Includes/libs
INC_DIRS  := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LIBS      := -lc -lgcc

# Compiler flags
CFLAGS := -O0 -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion -Wformat-truncation -Wpadded -Wconversion  -ffunction-sections -fdata-sections -fno-common  # -fno-short-enums !! newlib doesn't like this
CFLAGS += $(DFLAGS)
CFLAGS += $(EXTRA_CFLAGS)
CFLAGS += $(INC_SRCH_PATH) $(LIB_FLAGS)
CFLAGS += -g3 -ggdb3
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

# Linker flags
LDFLAGS ?= -T$(LSCRIPT) -nostartfiles -nostdlib --specs nano.specs -Wl,--gc-sections -Wl,-Map=$(TARGET).map
OFLAGS  ?= -O binary


.DEFAULT_GOAL = all

all: build flash

build: $(BUILD_DIR)/$(TARGET)

# Compilation
# Assembly
$(BUILD_DIR)/%.s.o: %.s
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Generate target
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@$(LD) $^ $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@
	@echo "Generate target: $(notdir $@) from $^"

$(SRCS): $(LSCRIPT)

clean:
	@$(RM) -rf $(BUILD_DIR)
	@echo "Removed build dir: $(BUILD_DIR)"

rebuild: clean build

flash:
	@openocd -f interface/stlink.cfg -f board/st_nucleo_wb55.cfg -c "program bin/firmware.elf verify reset exit"

debug:
	@echo "Connecting OpenOCD and running $(GDB)"
	@openocd -f interface/stlink.cfg -f board/st_nucleo_wb55.cfg -c "init" &
	@$(GDB) bin/firmware.elf -x .gdbconf

test:
	@echo "Running Act GitHub workflow"
	@act --job act-linux

serial:
	@echo "picocom serial on baud 9600"
	@picocom -b 9600 -f n -y n -d 8 -p 1 -c /dev/ttyUSB0  # For comm. with Attify Badge.

.PHONY: clean
