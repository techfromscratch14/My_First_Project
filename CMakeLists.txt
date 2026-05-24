# ==========================================
# STM32 Bare Metal Project using CMake
# ==========================================

cmake_minimum_required(VERSION 3.15)


# ==========================================
# Embedded Target Configuration
# ==========================================

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR  arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# ==========================================
# Project
# ==========================================

project(My_First_Project C ASM)


# ==========================================
# Toolchain
# ==========================================

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)

# ==========================================
# MCU FLAGS
# ==========================================

set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb")

# ==========================================
# Compiler Flags
# ==========================================

set(CMAKE_C_FLAGS "${MCU_FLAGS} -std=c11 -O0 -Wall -nostdlib")

set(CMAKE_ASM_FLAGS "${MCU_FLAGS}")

# ==========================================
# Output Directory
# ==========================================

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build)

# ==========================================
# Linker Script
# ==========================================

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Platform/stm32f446re/linker/linker.ld)

# ==========================================
# Source Files
# ==========================================

file(GLOB_RECURSE C_SOURCES
    ${CMAKE_SOURCE_DIR}/Platform/stm32f446re/*.c
    ${CMAKE_SOURCE_DIR}/Application/*.c)

set(ASM_SOURCES
    ${CMAKE_SOURCE_DIR}/Platform/stm32f446re/startup/startup_stm32f446re.s)


# ==========================================
# Include Directories
# ==========================================

include_directories(
     ${CMAKE_SOURCE_DIR}/platform/stm32f446re/drivers
)

# ==========================================
# ELF Target
# ==========================================

add_executable(${PROJECT_NAME} ${C_SOURCES} ${ASM_SOURCES})

# Generate .elf extension

set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")

# ==========================================
# Linker Options
# ==========================================

target_link_options(${PROJECT_NAME} PRIVATE -T${LINKER_SCRIPT} -Wl,-Map=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.map)


# ==========================================
# HEX and BIN Generation
# ==========================================

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.bin)

 
# ==========================================
# Flash Target
# ==========================================

add_custom_target(flash 
    COMMAND st-flash write ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.bin 0x0800000)
