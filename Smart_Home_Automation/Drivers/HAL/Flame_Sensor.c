/*
 * Flame_Sensor.c
 *
 *  Created on: Oct 5, 2024
 *      Author: Youssef Khaled
 */

#include "Flame_Sensor.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function: FlameSensor_init
 * Description: Initializes the flame sensor pin direction.
 */
void FlameSensor_init(void) {
    // Set the flame sensor pin direction to input
    GPIO_setupPinDirection(FLAME_SENSOR_PORT, FLAME_SENSOR_PIN, PIN_INPUT);
}

/*
 * Function: FlameSensor_getValue
 * Description: Reads the value from the flame sensor and returns it.
 * Returns: 1 if fire is detected, 0 otherwise.
 */
uint8 FlameSensor_getValue(void) {
    // Read the value from the flame sensor pin
    // Return 1 if the sensor detects fire, otherwise return 0
    return GPIO_readPin(FLAME_SENSOR_PORT, FLAME_SENSOR_PIN);
}

