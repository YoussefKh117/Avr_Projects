################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../Control_ECU_main.c \
../DC_Motor.c \
../GPIO.c \
../Keypad.c \
../LCD.c \
../PIR_Sensor.c \
../Timer.c \
../Timer0_PWM.c \
../external_eeprom.c \
../twi.c \
../uart.c 

OBJS += \
./Buzzer.o \
./Control_ECU_main.o \
./DC_Motor.o \
./GPIO.o \
./Keypad.o \
./LCD.o \
./PIR_Sensor.o \
./Timer.o \
./Timer0_PWM.o \
./external_eeprom.o \
./twi.o \
./uart.o 

C_DEPS += \
./Buzzer.d \
./Control_ECU_main.d \
./DC_Motor.d \
./GPIO.d \
./Keypad.d \
./LCD.d \
./PIR_Sensor.d \
./Timer.d \
./Timer0_PWM.d \
./external_eeprom.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


