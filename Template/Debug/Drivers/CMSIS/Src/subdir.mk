################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Src/system_stm32f0xx.c 

OBJS += \
./Drivers/CMSIS/Src/system_stm32f0xx.o 

C_DEPS += \
./Drivers/CMSIS/Src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Src/system_stm32f0xx.o: /home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Src/system_stm32f0xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F051R8Tx -c -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/Src/system_stm32f0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

