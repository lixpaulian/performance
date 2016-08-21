################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/stm32f7xx_hal_msp.c \
../src/timing.c \
../src/xxtea.c 

OBJS += \
./src/main.o \
./src/stm32f7xx_hal_msp.o \
./src/timing.o \
./src/xxtea.o 

C_DEPS += \
./src/main.d \
./src/stm32f7xx_hal_msp.d \
./src/timing.d \
./src/xxtea.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g -DSTM32F746xx -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -DOS_USE_SEMIHOSTING -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7-hal" -I../coremark -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/stm32f7xx_hal_msp.o: ../src/stm32f7xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g -DSTM32F746xx -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -DOS_USE_SEMIHOSTING -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7-hal" -I../coremark -std=gnu11 -Wno-missing-prototypes -Wno-missing-declarations -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/stm32f7xx_hal_msp.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


