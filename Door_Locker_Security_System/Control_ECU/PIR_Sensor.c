/*
 * PIR_Sensor.c
 *
 *  Created on: Oct 27, 2024
 *      Author: Youssef Khaled
 */

#include "PIR_Sensor.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function: PIR_init
 * Description: Initializes the PIR sensor pin direction.
 */
void PIR_init(void) {
    /* Set the flame sensor pin direction to input */
    GPIO_setupPinDirection(PIR_SENSOR_PORT, PIR_SENSOR_PIN, PIN_INPUT);
}

/*
 * Function: PIR_getValue
 * Description: Reads the value from the PIR sensor and returns it.
 * Returns: 1 if someone is detected, 0 otherwise.
 */
uint8 PIR_getValue(void) {
    /* Read the value from the PIR sensor pin */
    /* Return 1 if the sensor detects someone, otherwise return 0 */
    return GPIO_readPin(PIR_SENSOR_PORT, PIR_SENSOR_PIN);
}
