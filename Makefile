PROJECT_NAME = raven
TARGET       = $(BUILD_DIR)/$(PROJECT_NAME).elf

# Directories
BUILD_DIR      = build
SRC_DIRS       = src
INCLUDE_DIR    = $(SRC_DIRS)/include
CMSIS_GCC_DIR  = $(INCLUDE_DIR)/st_cmsis/Source/Templates/gcc

# Hardware specific
STARTUP := $(CMSIS_GCC_DIR)/startup_stm32wb55xx_cm4.s
LSCRIPT := $(CMSIS_GCC_DIR)/linker/stm32wb55xx_flash_cm4.ld
DFLAGS  := -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
DEFINES := -DUSE_HAL_DRIVER -DSTM32WB55xx -DSTM32WB

# Hardware toolchain
CC  := arm-none-eabi-gcc
LD  := arm-none-eabi-gcc
CPY := arm-none-eabi-objcopy
GDB := arm-none-eabi-gdb

# Source files, objects, & dependencies
SRCS := $(filter-out $(SRC_DIRS)/include/%, $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s'))
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
SRCS += $(STARTUP)  # Add after to prevent being compiled(if it is in OBJS)

# Includes/libs
INC_DIRS  := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LIBS      := -lc -lgcc

# Compiler flags
CFLAGS := -O0 -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion -Wformat-truncation -Wno-padded -Wconversion  -ffunction-sections -fdata-sections -fno-common  # -fno-short-enums !! newlib doesn't like this
CFLAGS += $(DFLAGS)
CFLAGS += $(EXTRA_CFLAGS)
CFLAGS += $(INC_SRCH_PATH) $(LIB_FLAGS)
CFLAGS += $(DEFINES)
CFLAGS += -g3 -ggdb3
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

# Linker flags
LDFLAGS ?= -T$(LSCRIPT) -nostartfiles -nostdlib --specs nano.specs -Wl,--gc-sections -Wl,-Map=$(TARGET).map
OFLAGS  ?= -O binary

# LVGL setup
include $(INCLUDE_DIR)/lvgl/lvgl.mk


.DEFAULT_GOAL = all

all: build flash

build: $(TARGET)

# Compilation
# Assembly
$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	#$(AS) $(ASFLAGS) -c $< -o $@
	@echo "Compile: $< to $@"

# C source
$(BUILD_DIR)/%.c.o: %.c
	@echo $(SRCS)
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	@echo "Compile: $< to $@"

# C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
	@echo "Compile: $< to $@"

# Generate target
$(TARGET): $(OBJS)
	@$(LD) $^ $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@
	@echo -e "Generate target: $(notdir $@) from $^\n\nSuccess!"

$(SRCS): $(LSCRIPT)

clean:
	@$(RM) -rf $(BUILD_DIR)
	@echo "Removed build dir: $(BUILD_DIR)"

rebuild: clean build

flash:
	@openocd -f interface/stlink.cfg -f board/st_nucleo_wb55.cfg -c "program $(TARGET) verify reset exit"

debug:
	@echo "Connecting OpenOCD and running $(GDB)"
	@openocd -f interface/stlink.cfg -f board/st_nucleo_wb55.cfg -c "init" &
	@$(GDB) $(TARGET) -x .gdbconf

test:
	@echo "Running Act GitHub workflow"
	@act --job act-linux

serial:
	@echo "picocom serial on baud 9600"
	@picocom -b 9600 -f n -y n -d 8 -p 1 -c /dev/ttyUSB0  # For comm. with Attify Badge

.PHONY: clean
