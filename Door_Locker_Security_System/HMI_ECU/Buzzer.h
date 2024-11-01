/*
 * Buzzer.h
 *
 *  Created on: Oct 5, 2024
 *      Author: Youssef Khaled
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "GPIO.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT PORTD_ID
#define BUZZER_PIN  PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function: Buzzer_init
 * Description: Initializes the buzzer by setting its GPIO pin direction
 *              to output and turns off the buzzer initially.
 *              Call this function before using the buzzer.
 */
void Buzzer_init(void);

/*
 * Function: Buzzer_on
 * Description: Activates the buzzer by setting its GPIO pin to high.
 *              This will turn the buzzer on to signal an alert.
 */
void Buzzer_on(void);

/*
 * Function: Buzzer_off
 * Description: Deactivates the buzzer by setting its GPIO pin to low.
 *              This will turn the buzzer off, stopping any sound.
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
