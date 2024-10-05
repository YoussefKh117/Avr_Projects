/*
 * main.c
 *
 *  Created on: Oct 3, 2024
 *      Author: Youssef Khaled
 */

#include "Timer0_PWM.h"
#include "DC_Motor.h"
#include "ADC.h"
#include "LM35.h"
#include "LCD.h"
#include "LED.h"
#include "LDR.h"
#include "Flame_Sensor.h"
#include "Buzzer.h"

int main() {
	/* Variable to store the temperature value read from the sensor */
	uint8 Temp_Value = 0;
	volatile uint8 Flame_detect = 0;
	uint16 Light_value = 0;

	/* Initialize the ADC to read analog values from the sensor */
	ADC_init();

	/* Initialize Timer0 for PWM to control the motor speed */
	Timer0_init_PWM();

	/* Initialize the DC Motor for fan control */
	DC_Motor_Init();

	/* Initialize the LCD display */
	LCD_init();

	/* Clear the LCD screen before starting */
	LCD_clearScreen();

	/* Initialize the LED driver */
	LEDS_init();

	/* Initialize the FLAME_SESNOR driver */
	FlameSensor_init();

	/* Initialize the Buzzer driver */
	Buzzer_init();

	/* Infinite loop to continuously monitor the temperature and control the fan */
	while (1) {
		/* Get the temperature value from the LM35 sensor */
		Temp_Value = LM35_getTemperature();

		/*Get the light value from LDR sensor*/
		Light_value = LDR_getLightIntensity();

		/* Read the value from the flame sensor */
		Flame_detect = FlameSensor_getValue();

		if (Flame_detect) {
			/* Raise alarm and display alert on the LCD */
			LCD_moveCursor(0, 0);
			LCD_clearScreen();
			LCD_displayString("Critical alert!"); /* Display alert message */
			/* Trigger alarm (this can be a buzzer or any other alert mechanism) */
			Buzzer_on(); /* Function to turn on the alarm */

			/* Continue to check for flame until it is no longer detected */
			while (Flame_detect) {
				Flame_detect=FlameSensor_getValue();
			}

			/* Once flame is no longer detected, turn off the alarm */
			Buzzer_off(); /* Function to turn off the alarm */
			/* Clear the alert message */
			LCD_clearScreen(); /* Clear the LCD screen */
		}
		/* Control the fan based on temperature value */
		/* If the temperature is below 25 degrees, turn off the fan */
		if (Temp_Value < 25) {
			/* Stop the motor (fan) */
			DC_Motor_Rotate(Stop, 0);

			/* Move the LCD cursor to the right position and display "Fan is Off" */
			LCD_moveCursor(0, 3);
			LCD_displayString("Fan is Off   "); /* Enough spaces to clear "Fan is On" */

			/* If the temperature is between 25 and 30 degrees, run the fan at 25% speed */
		} else if (Temp_Value < 30) {
			/* Rotate the motor (fan) clockwise at 25% speed */
			DC_Motor_Rotate(ClockWise, 25);

			/* Move the LCD cursor to the right position and display "Fan is On" */
			LCD_moveCursor(0, 3);
			LCD_displayString("Fan is On    "); /* Enough spaces to clear "Fan is Off" */

			/* If the temperature is between 30 and 35 degrees, run the fan at 50% speed */
		} else if (Temp_Value < 35) {
			/* Rotate the motor (fan) clockwise at 50% speed */
			DC_Motor_Rotate(ClockWise, 50);

			/* Move the LCD cursor to the right position and display "Fan is On" */
			LCD_moveCursor(0, 3);
			LCD_displayString("Fan is On    ");

			/* If the temperature is between 35 and 40 degrees, run the fan at 75% speed */
		} else if (Temp_Value < 40) {
			/* Rotate the motor (fan) clockwise at 75% speed */
			DC_Motor_Rotate(ClockWise, 75);

			/* Move the LCD cursor to the right position and display "Fan is On" */
			LCD_moveCursor(0, 3);
			LCD_displayString("Fan is On    ");

			/* If the temperature is 40 degrees or above, run the fan at 100% speed */
		} else {
			/* Rotate the motor (fan) clockwise at 100% speed */
			DC_Motor_Rotate(ClockWise, 100);

			/* Move the LCD cursor to the right position and display "Fan is On" */
			LCD_moveCursor(0, 3);
			LCD_displayString("Fan is On    ");
		}

		/* Control LEDs based on light intensity */
		if (Light_value < 15) {
			/* Turn on the red LED */
			LED_on(RED_LED);
			/* Turn on the green LED */
			LED_on(GREEN_LED);
			/* Turn on the blue LED */
			LED_on(BLUE_LED);
		} else if (Light_value <= 50) {
			/* Turn on the red LED */
			LED_on(RED_LED);
			/* Turn on the green LED */
			LED_on(GREEN_LED);
			/* Turn off the blue LED */
			LED_off(BLUE_LED);
		} else if (Light_value <= 70) {
			/* Turn on the red LED */
			LED_on(RED_LED);
			/* Turn off the green LED */
			LED_off(GREEN_LED);
			/* Turn off the blue LED */
			LED_off(BLUE_LED);
		} else {
			/* Turn off the red LED */
			LED_off(RED_LED);
			/* Turn off the green LED */
			LED_off(GREEN_LED);
			/* Turn off the blue LED */
			LED_off(BLUE_LED);
		}
		/* Display the temperature value on the LCD */
		LCD_moveCursor(1, 0);
		LCD_displayString("Temp=");
		LCD_intgerToString(Temp_Value);

		/* Clear any extra characters on the LCD if the temperature value has fewer digits */
		if (Temp_Value < 100) {
			LCD_displayCharacter(' '); /* Clears leftover digits when Temp_Value is less than 100 */
		}
		/* Display the label for light intensity */
		LCD_displayString(" LDR=");
		/* Display light intensity value */
		LCD_intgerToString(Light_value);
		/* Display percentage sign */
		LCD_displayString("% ");
	}
}
