################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tower-of-hanoi/hanoi.c 

OBJS += \
./tower-of-hanoi/hanoi.o 

C_DEPS += \
./tower-of-hanoi/hanoi.d 


# Each subdirectory must supply rules for building sources it contributes
tower-of-hanoi/%.o: ../tower-of-hanoi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g -DSTM32F746xx -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -DOS_USE_SEMIHOSTING -DPERFORMANCE_RUN=1 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7-hal" -I../coremark -I../tower-of-hanoi -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


