################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../Buzzer.c \
../DC_Motor.c \
../Flame_Sensor.c \
../GPIO.c \
../LCD.c \
../LDR.c \
../LED.c \
../LM35.c \
../Timer0_PWM.c \
../main.c 

OBJS += \
./ADC.o \
./Buzzer.o \
./DC_Motor.o \
./Flame_Sensor.o \
./GPIO.o \
./LCD.o \
./LDR.o \
./LED.o \
./LM35.o \
./Timer0_PWM.o \
./main.o 

C_DEPS += \
./ADC.d \
./Buzzer.d \
./DC_Motor.d \
./Flame_Sensor.d \
./GPIO.d \
./LCD.d \
./LDR.d \
./LED.d \
./LM35.d \
./Timer0_PWM.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


