
cmake_minimum_required(VERSION 4.0.2)

project(Flash)
enable_language(C CXX ASM)

set(DEVICE "STM32F103xB")

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-toolchain.cmake)
set(LD_SCRIPT ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/gcc/STM32F103.ld)

set(
    SOURCES 
    src/main.c
    Drivers/CMSIS/Device/system_stm32f1xx.c
    Drivers/CMSIS/Device/gcc/startup_stm32f103xb.s
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Core
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/Includes
)

target_link_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Core
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/Includes
)

target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
    ${DEVICE}
)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    -mthumb
    -mcpu=cortex-m3 
    -std=c23 
    -Wall 
    -Wextra 
    -Wpedantic
    -ffunction-sections 
    -fdata-sections
    -O0
)

target_link_options(
    ${PROJECT_NAME} PRIVATE
    -Wl,--gc-sections
    -Wl,-T${LD_SCRIPT}
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>
)

add_custom_command(
    OUTPUT ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    DEPENDS ${PROJECT_NAME}.elf
)

add_custom_target(generate_bin ALL
    DEPENDS ${PROJECT_NAME}.bin
)