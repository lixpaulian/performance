################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../coremark/core_list_join.c \
../coremark/core_main.c \
../coremark/core_matrix.c \
../coremark/core_portme.c \
../coremark/core_state.c \
../coremark/core_util.c 

OBJS += \
./coremark/core_list_join.o \
./coremark/core_main.o \
./coremark/core_matrix.o \
./coremark/core_portme.o \
./coremark/core_state.o \
./coremark/core_util.o 

C_DEPS += \
./coremark/core_list_join.d \
./coremark/core_main.d \
./coremark/core_matrix.d \
./coremark/core_portme.d \
./coremark/core_state.d \
./coremark/core_util.d 


# Each subdirectory must supply rules for building sources it contributes
coremark/%.o: ../coremark/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g -DSTM32F746xx -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -DOS_USE_SEMIHOSTING -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7-hal" -I../coremark -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


