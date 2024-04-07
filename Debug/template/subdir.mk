################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../template/algorithm.c \
../template/global_variable.c \
../template/gw1ns4c_it.c \
../template/linealg.c \
../template/main.c \
../template/mymath.c \
../template/strio.c 

OBJS += \
./template/algorithm.o \
./template/global_variable.o \
./template/gw1ns4c_it.o \
./template/linealg.o \
./template/main.o \
./template/mymath.o \
./template/strio.o 

C_DEPS += \
./template/algorithm.d \
./template/global_variable.d \
./template/gw1ns4c_it.d \
./template/linealg.d \
./template/main.d \
./template/mymath.d \
./template/strio.d 


# Each subdirectory must supply rules for building sources it contributes
template/%.o: ../template/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Users\christmas\Desktop\вуз\diplom\temp\finalsize\lib\CMSIS\CoreSupport\gmd" -I"C:\Users\christmas\Desktop\вуз\diplom\temp\finalsize\lib\CMSIS\DeviceSupport\system" -I"C:\Users\christmas\Desktop\вуз\diplom\temp\finalsize\lib\StdPeriph_Driver\Includes" -I"C:\Users\christmas\Desktop\вуз\diplom\temp\finalsize\template" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


