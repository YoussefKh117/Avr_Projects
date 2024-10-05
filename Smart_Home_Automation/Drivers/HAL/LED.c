/*
 * LED.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Youssef Khaled
 */

#include "LED.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initializing the LED driver by setting up the
 * direction of the LED pins and turning off all LEDs initially.
 */
void LEDS_init() {
	// Set the direction of the LED pins to output
	GPIO_setupPinDirection(RED_LED_PORT, RED_LED_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(GREEN_LED_PORT, GREEN_LED_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(BLUE_LED_PORT, BLUE_LED_PIN, PIN_OUTPUT);

	// Turn off all LEDs initially
	GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOGIC_LOW); // Turn off the red LED
	GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOGIC_LOW); // Turn off the green LED
	GPIO_writePin(BLUE_LED_PORT, BLUE_LED_PIN, LOGIC_LOW); // Turn off the blue LED
}

void LED_on(LED_ID id) {
	if (LED_LOGIC == POSITIVE_LOGIC) { // Check if positive logic is used
		// Turn on the LED by setting the corresponding pin high
		switch (id) {
		case RED_LED:
			GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOGIC_HIGH); // Turn on the red LED
			break;
		case GREEN_LED:
			GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOGIC_HIGH); // Turn on the green LED
			break;
		case BLUE_LED:
			GPIO_writePin(BLUE_LED_PORT, BLUE_LED_PIN, LOGIC_HIGH); // Turn on the blue LED
			break;
		}
	} else {
		// Turn on the LED by setting the corresponding pin low
		switch (id) {
		case RED_LED:
			GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOGIC_LOW); // Turn on the red LED
			break;
		case GREEN_LED:
			GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOGIC_LOW); // Turn on the green LED
			break;
		case BLUE_LED:
			GPIO_writePin(BLUE_LED_PORT, BLUE_LED_PIN, LOGIC_LOW); // Turn on the blue LED
			break;
		}
	}
}

/*
 * Description :
 * Function responsible for turning off the specified LED based on its ID.
 */
void LED_off(LED_ID id) {
	if (LED_LOGIC == POSITIVE_LOGIC) { // Check if positive logic is used
		// Turn off the LED by setting the corresponding pin low
		switch (id) {
		case RED_LED:
			GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOGIC_LOW); // Turn off the red LED
			break;
		case GREEN_LED:
			GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOGIC_LOW); // Turn off the green LED
			break;
		case BLUE_LED:
			GPIO_writePin(BLUE_LED_PORT, BLUE_LED_PIN, LOGIC_LOW); // Turn off the blue LED
			break;
		}
	} else {
		// Turn off the LED by setting the corresponding pin high
		switch (id) {
		case RED_LED:
			GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOGIC_HIGH); // Turn off the red LED
			break;
		case GREEN_LED:
			GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOGIC_HIGH); // Turn off the green LED
			break;
		case BLUE_LED:
			GPIO_writePin(BLUE_LED_PORT, BLUE_LED_PIN, LOGIC_HIGH); // Turn off the blue LED
			break;
		}
	}
}
