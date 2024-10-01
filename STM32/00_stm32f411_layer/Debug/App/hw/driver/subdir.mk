################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/hw/driver/led.c 

OBJS += \
./App/hw/driver/led.o 

C_DEPS += \
./App/hw/driver/led.d 


# Each subdirectory must supply rules for building sources it contributes
App/hw/driver/%.o App/hw/driver/%.su App/hw/driver/%.cyclo: ../App/hw/driver/%.c App/hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/kyh/cubeIDE/00_stm32f411_layer/App" -I"C:/kyh/cubeIDE/00_stm32f411_layer/App/common" -I"C:/kyh/cubeIDE/00_stm32f411_layer/App/hw" -I"C:/kyh/cubeIDE/00_stm32f411_layer/App/hw/driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-hw-2f-driver

clean-App-2f-hw-2f-driver:
	-$(RM) ./App/hw/driver/led.cyclo ./App/hw/driver/led.d ./App/hw/driver/led.o ./App/hw/driver/led.su

.PHONY: clean-App-2f-hw-2f-driver

