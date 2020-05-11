################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx.c \
/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_cortex.c \
/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_delay.c \
/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_gpio.c \
/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_i2c.c \
/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_rcc.c \
/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_utils.c 

OBJS += \
./Drivers/MY/Src/my_stm32f0xx.o \
./Drivers/MY/Src/my_stm32f0xx_cortex.o \
./Drivers/MY/Src/my_stm32f0xx_delay.o \
./Drivers/MY/Src/my_stm32f0xx_gpio.o \
./Drivers/MY/Src/my_stm32f0xx_i2c.o \
./Drivers/MY/Src/my_stm32f0xx_rcc.o \
./Drivers/MY/Src/my_stm32f0xx_utils.o 

C_DEPS += \
./Drivers/MY/Src/my_stm32f0xx.d \
./Drivers/MY/Src/my_stm32f0xx_cortex.d \
./Drivers/MY/Src/my_stm32f0xx_delay.d \
./Drivers/MY/Src/my_stm32f0xx_gpio.d \
./Drivers/MY/Src/my_stm32f0xx_i2c.d \
./Drivers/MY/Src/my_stm32f0xx_rcc.d \
./Drivers/MY/Src/my_stm32f0xx_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MY/Src/my_stm32f0xx.o: /home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F051R8Tx -c -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/MY/Src/my_stm32f0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/MY/Src/my_stm32f0xx_cortex.o: /home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_cortex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F051R8Tx -c -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/MY/Src/my_stm32f0xx_cortex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/MY/Src/my_stm32f0xx_delay.o: /home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F051R8Tx -c -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/MY/Src/my_stm32f0xx_delay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/MY/Src/my_stm32f0xx_gpio.o: /home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F051R8Tx -c -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/MY/Src/my_stm32f0xx_gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/MY/Src/my_stm32f0xx_i2c.o: /home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F051R8Tx -c -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/MY/Src/my_stm32f0xx_i2c.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/MY/Src/my_stm32f0xx_rcc.o: /home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F051R8Tx -c -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/MY/Src/my_stm32f0xx_rcc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/MY/Src/my_stm32f0xx_utils.o: /home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src/my_stm32f0xx_utils.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F051R8Tx -c -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/CMSIS/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers/MY/Src -I/home/megalloid/STM32CubeIDE/STM32F0xx/Drivers -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Inc -I/home/megalloid/STM32CubeIDE/STM32F0xx/Template/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/MY/Src/my_stm32f0xx_utils.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

