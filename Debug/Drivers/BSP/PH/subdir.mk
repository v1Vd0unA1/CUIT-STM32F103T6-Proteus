################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/PH/ph_meter.c 

OBJS += \
./Drivers/BSP/PH/ph_meter.o 

C_DEPS += \
./Drivers/BSP/PH/ph_meter.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/PH/%.o Drivers/BSP/PH/%.su Drivers/BSP/PH/%.cyclo: ../Drivers/BSP/PH/%.c Drivers/BSP/PH/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I"D:/STM32CubeIDE/workspace/Sensor_Final_Project_Proteus/Drivers/BSP/APP" -I"D:/STM32CubeIDE/workspace/Sensor_Final_Project_Proteus/Drivers/BSP/OLED" -I"D:/STM32CubeIDE/workspace/Sensor_Final_Project_Proteus/Drivers/BSP/PH" -I"D:/STM32CubeIDE/workspace/Sensor_Final_Project_Proteus/Drivers/BSP/RETARGET" -I"D:/STM32CubeIDE/workspace/Sensor_Final_Project_Proteus/Drivers/BSP/TIME" -I"D:/STM32CubeIDE/workspace/Sensor_Final_Project_Proteus/Drivers/BSP/DELAY" -I"D:/STM32CubeIDE/workspace/Sensor_Final_Project_Proteus/Drivers/BSP/DS18B20" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-PH

clean-Drivers-2f-BSP-2f-PH:
	-$(RM) ./Drivers/BSP/PH/ph_meter.cyclo ./Drivers/BSP/PH/ph_meter.d ./Drivers/BSP/PH/ph_meter.o ./Drivers/BSP/PH/ph_meter.su

.PHONY: clean-Drivers-2f-BSP-2f-PH

