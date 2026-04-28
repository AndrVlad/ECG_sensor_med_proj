################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Src/SPI_Connection.c \
../Libraries/Src/protocol_parser.c \
../Libraries/Src/sensor_utils.c 

OBJS += \
./Libraries/Src/SPI_Connection.o \
./Libraries/Src/protocol_parser.o \
./Libraries/Src/sensor_utils.o 

C_DEPS += \
./Libraries/Src/SPI_Connection.d \
./Libraries/Src/protocol_parser.d \
./Libraries/Src/sensor_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Src/%.o Libraries/Src/%.su Libraries/Src/%.cyclo: ../Libraries/Src/%.c Libraries/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/Documents/GitHub/ECG_sensor_med_proj/Libraries/Inc" -I"C:/Users/Admin/Documents/GitHub/ECG_sensor_med_proj/Drivers/ADS1293" -I../Core/Inc -I"C:/Users/Admin/Documents/GitHub/ECG_sensor_med_proj/Drivers/25Q" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-Src

clean-Libraries-2f-Src:
	-$(RM) ./Libraries/Src/SPI_Connection.cyclo ./Libraries/Src/SPI_Connection.d ./Libraries/Src/SPI_Connection.o ./Libraries/Src/SPI_Connection.su ./Libraries/Src/protocol_parser.cyclo ./Libraries/Src/protocol_parser.d ./Libraries/Src/protocol_parser.o ./Libraries/Src/protocol_parser.su ./Libraries/Src/sensor_utils.cyclo ./Libraries/Src/sensor_utils.d ./Libraries/Src/sensor_utils.o ./Libraries/Src/sensor_utils.su

.PHONY: clean-Libraries-2f-Src

