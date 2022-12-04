################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_Drivers/Utils/utils.c 

C_DEPS += \
./User_Drivers/Utils/utils.d 

OBJS += \
./User_Drivers/Utils/utils.o 


# Each subdirectory must supply rules for building sources it contributes
User_Drivers/Utils/%.o User_Drivers/Utils/%.su: ../User_Drivers/Utils/%.c User_Drivers/Utils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -D__TARGET_FPU_VFP -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_Drivers-2f-Utils

clean-User_Drivers-2f-Utils:
	-$(RM) ./User_Drivers/Utils/utils.d ./User_Drivers/Utils/utils.o ./User_Drivers/Utils/utils.su

.PHONY: clean-User_Drivers-2f-Utils

