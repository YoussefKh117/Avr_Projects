/*
 * UltraSonic_Sesnor.h
 *
 *  Created on: Oct 10, 2024
 *      Author: Youssef Khaled
 */

#ifndef ULTRASONIC_SESNOR_H_
#define ULTRASONIC_SESNOR_H_

#include "GPIO.h"
#include "ICU.h"
#include "avr/delay.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*
 * Define the ports and pins for the Ultrasonic sensor
 * ECHO pin is used to capture the echo signal for distance measurement
 * TRIGGER pin is used to send the trigger pulse to the ultrasonic sensor
 */

#define UltraSonic_ECHO_PORT    PORTD_ID
#define UltraSonic_ECHO_PIN     PIN6_ID

#define UltraSonic_TRIGGER_PORT PORTD_ID
#define UltraSonic_TRIGGER_PIN  PIN7_ID

#define TRIGGER_DELAY_VALUE     20
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Initialize the Ultrasonic sensor by configuring the GPIO pins for
 * the trigger and echo signals, and by initializing the ICU driver.
 *
 * Inputs: None
 * Return: None
 */
void UltraSonic_init(void);

/*
 * Description:
 * Send the trigger pulse to the Ultrasonic sensor to initiate
 * distance measurement. The pulse lasts for at least 10 microseconds.
 *
 * Inputs: None
 * Return: None
 */
void Ultrasonic_Trigger(void);

/*
 * Description:
 * This function triggers the ultrasonic sensor, waits for the echo pulse,
 * and then reads the distance to the object in centimeters.
 * It uses the ICU to measure the time the echo signal stays HIGH.
 *
 * Inputs: None
 * Return: The measured distance in centimeters.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description:
 * This is the callback function called by the ICU driver when an edge is detected.
 * It calculates the pulse width by measuring the time between the rising and falling
 * edges of the echo signal.
 *
 * Inputs: None
 * Return: None
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_SESNOR_H_ */
