/*
 * Timer0_PWM.c
 *
 *  Created on: Oct 3, 2024
 *      Author: Youssef Khaled
 */

#include "Timer0_PWM.h"
#include "common_macros.h"
#include "std_types.h"
#include <avr/io.h>

void Timer0_init_PWM() {

	/* Initialize Timer0 counter to 0 */
	TCNT0 = 0;

	/* Set PB3/OC0 as output pin -> pin where the PWM signal is generated from MC */
	DDRB |= (1 << PWM_OUTPUT_PIN);

	/* Configure Timer0 for Fast PWM mode and set prescaler to 1024 */

	/* Set WGM00, WGM01 bits for Fast PWM mode */
	TCCR0 |= (1 << WGM00) | (1 << WGM01);

	/* Clear OC0 on Compare Match (non-inverted mode) */
	TCCR0 |= (1 << COM01);

	/* Set CS00, CS02 bits for prescaler = 1024 */
	TCCR0 |= (1 << CS00) | (1 << CS02);
}
void PWM_Set_Duty_Cycle(uint8 duty_cycle) {

	/*Set the Output Compare Register with duty cycle*/

	/** Set the duty cycle */

	if (duty_cycle > 100) {
		duty_cycle = 100; /*Cap the duty cycle to 100%*/
	}

	OCR0 = (uint8)(((uint16) duty_cycle * 255) / 100); /*Convert percentage to OCR value (0-255)*/
}
