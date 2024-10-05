################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../DC_Motor.c \
../GPIO.c \
../LCD.c \
../LM35.c \
../Timer0_PWM.c \
../main.c 

OBJS += \
./ADC.o \
./DC_Motor.o \
./GPIO.o \
./LCD.o \
./LM35.o \
./Timer0_PWM.o \
./main.o 

C_DEPS += \
./ADC.d \
./DC_Motor.d \
./GPIO.d \
./LCD.d \
./LM35.d \
./Timer0_PWM.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


