/*
 * Flame_Sensor.h
 *
 *  Created on: Oct 5, 2024
 *      Author: Youssef Khaled
 */

#ifndef FLAME_SENSOR_H_
#define FLAME_SENSOR_H_

#include "GPIO.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define FLAME_SENSOR_PORT PORTD_ID
#define FLAME_SENSOR_PIN  PIN2_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/* Function responsible initializes the flame sensor pin direction */
void FlameSensor_init(void);

/* Function reads the value from the flame sensor and returns it */
uint8 FlameSensor_getValue(void);

#endif /* FLAME_SENSOR_H_ */
