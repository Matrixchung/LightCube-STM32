################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_Drivers/USART/retarget.c \
../User_Drivers/USART/uart_callback.c 

C_DEPS += \
./User_Drivers/USART/retarget.d \
./User_Drivers/USART/uart_callback.d 

OBJS += \
./User_Drivers/USART/retarget.o \
./User_Drivers/USART/uart_callback.o 


# Each subdirectory must supply rules for building sources it contributes
User_Drivers/USART/%.o User_Drivers/USART/%.su: ../User_Drivers/USART/%.c User_Drivers/USART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -D__TARGET_FPU_VFP -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_Drivers-2f-USART

clean-User_Drivers-2f-USART:
	-$(RM) ./User_Drivers/USART/retarget.d ./User_Drivers/USART/retarget.o ./User_Drivers/USART/retarget.su ./User_Drivers/USART/uart_callback.d ./User_Drivers/USART/uart_callback.o ./User_Drivers/USART/uart_callback.su

.PHONY: clean-User_Drivers-2f-USART

