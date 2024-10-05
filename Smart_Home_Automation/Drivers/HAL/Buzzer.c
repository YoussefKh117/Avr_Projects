/*
 * Buzzer.c
 *
 *  Created on: Oct 5, 2024
 *      Author: Youssef Khaled
 */

#include "Buzzer.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function: Buzzer_init
 * Description: Initializes the buzzer pin direction and turns off the buzzer.
 */
void Buzzer_init(void) {
    // Set the buzzer pin direction to output
    GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);

    // Turn off the buzzer initially
    GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}

/*
 * Function: Buzzer_on
 * Description: Activates the buzzer.
 */

void Buzzer_on(void) {
    // Set the buzzer pin to high to activate the buzzer
    GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
}

/*
 * Function: Buzzer_off
 * Description: Deactivates the buzzer.
 */

void Buzzer_off(void) {
    // Set the buzzer pin to low to deactivate the buzzer
    GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}
