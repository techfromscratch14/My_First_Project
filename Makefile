# ==============================
# Simple STM32 Makefile
# ==============================
#project name

TARGET = My_First_Project

#Build folders
BUILD_DIR = Build
OBJ_DIR = $(BUILD_DIR)/obj

#Compiler
CC = arm-none-eabi-gcc
OBJ_COPY = arm-none-eabi-objcopy

#MCU Flags
CFLAGS = -mcpu=cortex-m4 \
		-mthumb \
		-std=c11 \
		-O0 \
		-Wall \
		-nostdlib

#Linker script
LDSCRIPT = Platform/stm32f446re/linker/linker.ld

#source files

C_SRCS = $(wildcard Platform/stm32f446re/*.c)

#Assembly files

ASM_SRCS = Platform/stm32f446re/startup/startup_stm32f446re.s

#Object files

C_OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(C_SRCS:.c=.o)))


ASM_OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(ASM_SRCS:.s=.o)))

OBJS = $(C_OBJS) $(ASM_OBJS)

#Inlcude Paths

INCLUDES = -IInc

#output files

TARGET_ELF = $(BUILD_DIR)/$(TARGET).elf 
TARGET_HEX = $(BUILD_DIR)/$(TARGET).hex
TARGET_BIN = $(BUILD_DIR)/$(TARGET).bin
TARGET_MAP = $(BUILD_DIR)/$(TARGET).map

#Linker flags

LDFLAGS = -T$(LDSCRIPT) \
			-Wl,-Map=$(TARGET_MAP)

# ==============================
# Build Rules
# ==============================

all: BuildFolder $(TARGET_ELF) $(TARGET_HEX) $(TARGET_BIN)

#Create build folders

BuildFolder:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

#Compile C files
$(OBJ_DIR)/%.o : Platform/stm32f446re/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Assemble .s files
$(OBJ_DIR)/%.o: Platform/stm32f446re/startup/%.s
	$(CC) $(CFLAGS) -c $< -o $@

#Link
$(TARGET_ELF): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

#Generate HEX
$(TARGET_HEX): $(TARGET_ELF)
	$(OBJ_COPY) -O ihex $< $@


#Generate BIN
$(TARGET_BIN): $(TARGET_ELF)
	$(OBJ_COPY) -O binary $< $@

#clean
clean:
	rm -rf $(BUILD_DIR)

#Flash using ST-link
flash:
	st-flash write $(TARGET_BIN) 0x08000000
