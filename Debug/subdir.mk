################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../retarget.c 

OBJS += \
./retarget.o 

C_DEPS += \
./retarget.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Users\christmas\Desktop\вуз\diplom\temp\finalsize\lib\CMSIS\CoreSupport\gmd" -I"C:\Users\christmas\Desktop\вуз\diplom\temp\finalsize\lib\CMSIS\DeviceSupport\system" -I"C:\Users\christmas\Desktop\вуз\diplom\temp\finalsize\lib\StdPeriph_Driver\Includes" -I"C:\Users\christmas\Desktop\вуз\diplom\temp\finalsize\template" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


