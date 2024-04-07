################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/StdPeriph_Driver/Sources/gw1ns4c_gpio.c \
../lib/StdPeriph_Driver/Sources/gw1ns4c_i2c.c \
../lib/StdPeriph_Driver/Sources/gw1ns4c_misc.c \
../lib/StdPeriph_Driver/Sources/gw1ns4c_rtc.c \
../lib/StdPeriph_Driver/Sources/gw1ns4c_spi.c \
../lib/StdPeriph_Driver/Sources/gw1ns4c_syscon.c \
../lib/StdPeriph_Driver/Sources/gw1ns4c_timer.c \
../lib/StdPeriph_Driver/Sources/gw1ns4c_uart.c \
../lib/StdPeriph_Driver/Sources/gw1ns4c_wdog.c 

OBJS += \
./lib/StdPeriph_Driver/Sources/gw1ns4c_gpio.o \
./lib/StdPeriph_Driver/Sources/gw1ns4c_i2c.o \
./lib/StdPeriph_Driver/Sources/gw1ns4c_misc.o \
./lib/StdPeriph_Driver/Sources/gw1ns4c_rtc.o \
./lib/StdPeriph_Driver/Sources/gw1ns4c_spi.o \
./lib/StdPeriph_Driver/Sources/gw1ns4c_syscon.o \
./lib/StdPeriph_Driver/Sources/gw1ns4c_timer.o \
./lib/StdPeriph_Driver/Sources/gw1ns4c_uart.o \
./lib/StdPeriph_Driver/Sources/gw1ns4c_wdog.o 

C_DEPS += \
./lib/StdPeriph_Driver/Sources/gw1ns4c_gpio.d \
./lib/StdPeriph_Driver/Sources/gw1ns4c_i2c.d \
./lib/StdPeriph_Driver/Sources/gw1ns4c_misc.d \
./lib/StdPeriph_Driver/Sources/gw1ns4c_rtc.d \
./lib/StdPeriph_Driver/Sources/gw1ns4c_spi.d \
./lib/StdPeriph_Driver/Sources/gw1ns4c_syscon.d \
./lib/StdPeriph_Driver/Sources/gw1ns4c_timer.d \
./lib/StdPeriph_Driver/Sources/gw1ns4c_uart.d \
./lib/StdPeriph_Driver/Sources/gw1ns4c_wdog.d 


# Each subdirectory must supply rules for building sources it contributes
lib/StdPeriph_Driver/Sources/%.o: ../lib/StdPeriph_Driver/Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


