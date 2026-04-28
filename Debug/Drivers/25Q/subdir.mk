################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/25Q/w25q_spi.c 

OBJS += \
./Drivers/25Q/w25q_spi.o 

C_DEPS += \
./Drivers/25Q/w25q_spi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/25Q/%.o Drivers/25Q/%.su Drivers/25Q/%.cyclo: ../Drivers/25Q/%.c Drivers/25Q/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/Documents/GitHub/ECG_sensor_med_proj/Libraries/Inc" -I"C:/Users/Admin/Documents/GitHub/ECG_sensor_med_proj/Drivers/ADS1293" -I../Core/Inc -I"C:/Users/Admin/Documents/GitHub/ECG_sensor_med_proj/Drivers/25Q" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-25Q

clean-Drivers-2f-25Q:
	-$(RM) ./Drivers/25Q/w25q_spi.cyclo ./Drivers/25Q/w25q_spi.d ./Drivers/25Q/w25q_spi.o ./Drivers/25Q/w25q_spi.su

.PHONY: clean-Drivers-2f-25Q

