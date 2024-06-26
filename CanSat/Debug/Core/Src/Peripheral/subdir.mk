################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Peripheral/BMP280.c \
../Core/Src/Peripheral/NRF24.c \
../Core/Src/Peripheral/mpu6050.c 

OBJS += \
./Core/Src/Peripheral/BMP280.o \
./Core/Src/Peripheral/NRF24.o \
./Core/Src/Peripheral/mpu6050.o 

C_DEPS += \
./Core/Src/Peripheral/BMP280.d \
./Core/Src/Peripheral/NRF24.d \
./Core/Src/Peripheral/mpu6050.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Peripheral/%.o Core/Src/Peripheral/%.su Core/Src/Peripheral/%.cyclo: ../Core/Src/Peripheral/%.c Core/Src/Peripheral/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Peripheral

clean-Core-2f-Src-2f-Peripheral:
	-$(RM) ./Core/Src/Peripheral/BMP280.cyclo ./Core/Src/Peripheral/BMP280.d ./Core/Src/Peripheral/BMP280.o ./Core/Src/Peripheral/BMP280.su ./Core/Src/Peripheral/NRF24.cyclo ./Core/Src/Peripheral/NRF24.d ./Core/Src/Peripheral/NRF24.o ./Core/Src/Peripheral/NRF24.su ./Core/Src/Peripheral/mpu6050.cyclo ./Core/Src/Peripheral/mpu6050.d ./Core/Src/Peripheral/mpu6050.o ./Core/Src/Peripheral/mpu6050.su

.PHONY: clean-Core-2f-Src-2f-Peripheral

