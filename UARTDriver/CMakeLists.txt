cmake_minimum_required(VERSION 3.10)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(UartDriver)

enable_language(C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_SYSTEM_NAME Windows)
set(STM32CUBEMX_GENERATED_FILES

        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c

        ../UARTDriver/Core/Inc/main.h
        ../UARTDriver/Core/Inc/stm32f4xx_hal_conf.h
        ../UARTDriver/Core/Inc/stm32f4xx_it.h

        ../UARTDriver/Core/Src/main.c
        ../UARTDriver/Core/Src/freertos.c
        ../UARTDriver/Core/Src/stm32f4xx_hal_msp.c
        ../UARTDriver/Core/Src/stm32f4xx_it.c
        ../UARTDriver/Core/Src/system_stm32f4xx.c
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/list.c
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/queue.c
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/timers.c
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
        ../UARTDriver/Application/src/Application.c
        ../UARTDriver/Application/src/RingBuffer.c

        ../UARTDriver/startup_stm32f407xx.s)

set(EXECUTABLE ${PROJECT_NAME}.out)

add_executable(${EXECUTABLE} ${STM32CUBEMX_GENERATED_FILES})

target_compile_definitions(${EXECUTABLE} PRIVATE
        -DUSE_HAL_DRIVER
        -DSTM32F407xx
        )

target_include_directories(${EXECUTABLE} PRIVATE
        ../UARTDriver/Core/Inc
        ../UARTDriver/Drivers/STM32F4xx_HAL_Driver/Inc
        ../UARTDriver/Drivers/CMSIS/Device/ST/STM32F4xx/Include
        ../UARTDriver/Drivers/CMSIS/Include
        ../UARTDriver/Application/Inc
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/Include
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
        ../UARTDriver/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
        ../UARTDriver/USB_Device/App
        ../UARTDriver/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
        ../UARTDriver/USB_Device/Target
        ../UARTDriver/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
        ../UARTDriver/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
        ../UARTDriver/USB_HOST/App
        ../UARTDriver/Middlewares/ST/STM32_USB_Host_Library/Core/Inc
        ../UARTDriver/USB_HOST/Target
        ../UARTDriver/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc
        ../UARTDriver/Application/inc
        )

target_compile_options(${EXECUTABLE} PRIVATE
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard

        -fdata-sections
        -ffunction-sections

        -Wall

        $<$<CONFIG:Debug>:-Og>
        )

target_link_options(${EXECUTABLE} PRIVATE
        -T${CMAKE_SOURCE_DIR}/STM32F407VGTx_FLASH.ld
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -lc
        -lm
        -lnosys
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
        )

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-size ${EXECUTABLE})

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)

# Flash target

add_custom_target(flashBoard COMMAND cmd /c D:/UARTDriver/UARTDriver/flashBoard.bat)
ADD_DEPENDENCIES(flashBoard flashBoard)