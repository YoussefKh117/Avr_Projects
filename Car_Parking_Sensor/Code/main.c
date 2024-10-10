/*
 * main.c
 *
 *  Created on: Oct 10, 2024
 *      Author: Youssef Khaled
 */

#include "common_macros.h"
#include "std_types.h"
#include "LCD.h"
#include "LED.h"
#include "Buzzer.h"
#include "UltraSonic_Sesnor.h"
#include <avr/io.h>

#define youssef 1

int main() {
	/* Enable global interrupt by setting the I-bit in the status register */
	SET_BIT(SREG, 7);
	/* Initialize LCD */
	LCD_init();
	/* Initialize Buzzer */
	Buzzer_init();
	/* Initialize LEDs */
	LEDS_init();
	/* Initialize Ultrasonic sensor */
	UltraSonic_init();

	/* Variable to store distance read by UltraSonic sensor*/
	uint16 Distance = 0;

	/* Display the initial message on the LCD */
	LCD_displayString("Distance=     cm");

	while (youssef) {
		/*read distance from UltraSonic sensor*/
		Distance = Ultrasonic_readDistance() + 1;
		/* Move cursor to the position where the distance value will be displayed on the LCD */
		LCD_moveCursor(0, 10);
		/* Display the distance on the LCD screen */
		LCD_intgerToString(Distance);

		/* Clear extra characters for distances less than 100 cm */
		if (Distance < 100) {
			LCD_displayCharacter(' ');
		} else if (Distance < 10) {
			LCD_displayString("  ");
		}
		/* Distance to LED and Buzzer Mapping */
		if (Distance <= 5) {
			/* All LEDs are flashing, Buzzer sounds, LCD shows "Stop" */
			Buzzer_on();
			LCD_moveCursor(1, 0);
			LCD_displayString("      Stop!     ");
			LED_on(RED_LED);
			LED_on(GREEN_LED);
			LED_on(BLUE_LED);
			_delay_ms(200); /*Simple flashing effect*/
			LED_off(RED_LED);
			LED_off(GREEN_LED);
			LED_off(BLUE_LED);
			_delay_ms(200);
		} else if (Distance <= 10) {
			/* All LEDs ON (Red, Green, Blue), No buzzer */
			LCD_moveCursor(1, 0);
			LCD_displayString("               ");
			LED_on(RED_LED);
			LED_on(GREEN_LED);
			LED_on(BLUE_LED);
			Buzzer_off();
		} else if (Distance <= 15) {
			/* Red and Green LEDs ON, Blue LED OFF */
			LCD_moveCursor(1, 0);
			LCD_displayString("               ");
			LED_on(RED_LED);
			LED_on(GREEN_LED);
			LED_off(BLUE_LED);
			Buzzer_off();
		} else if (Distance <= 20) {
			/* Only Red LED ON, others OFF */
			LCD_moveCursor(1, 0);
			LCD_displayString("               ");
			LED_on(RED_LED);
			LED_off(GREEN_LED);
			LED_off(BLUE_LED);
			Buzzer_off();
		} else {
			/* All LEDs OFF, Buzzer OFF */
			LCD_moveCursor(1, 0);
			LCD_displayString("               ");
			LED_off(RED_LED);
			LED_off(GREEN_LED);
			LED_off(BLUE_LED);
			Buzzer_off();
		}

		/* Add a small delay for stability */
		_delay_ms(100);
	}

}
