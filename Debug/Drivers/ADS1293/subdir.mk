################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ADS1293/ADS1293.c 

OBJS += \
./Drivers/ADS1293/ADS1293.o 

C_DEPS += \
./Drivers/ADS1293/ADS1293.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ADS1293/%.o Drivers/ADS1293/%.su Drivers/ADS1293/%.cyclo: ../Drivers/ADS1293/%.c Drivers/ADS1293/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/vlado/STM32CubeIDE/workspace_1.12.0/ECG_sensor/Libraries/Inc" -I"C:/Users/vlado/STM32CubeIDE/workspace_1.12.0/ECG_sensor/Drivers/ADS1293" -I../Core/Inc -I"C:/Users/vlado/STM32CubeIDE/workspace_1.12.0/ECG_sensor/Drivers/25Q" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-ADS1293

clean-Drivers-2f-ADS1293:
	-$(RM) ./Drivers/ADS1293/ADS1293.cyclo ./Drivers/ADS1293/ADS1293.d ./Drivers/ADS1293/ADS1293.o ./Drivers/ADS1293/ADS1293.su

.PHONY: clean-Drivers-2f-ADS1293

