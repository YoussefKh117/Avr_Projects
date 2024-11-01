/*
 * PIR_Sensor.h
 *
 *  Created on: Oct 27, 2024
 *      Author: Youssef Khaled
 */

#ifndef PIR_SENSOR_H_
#define PIR_SENSOR_H_

#include "std_types.h"
#include "GPIO.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PIR_SENSOR_PORT PORTC_ID
#define PIR_SENSOR_PIN  PIN2_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Function responsible initializes the PIR sensor pin direction */
void PIR_init(void);

/* Function reads the value from the PIR sensor and returns it */
uint8 PIR_getValue(void);


#endif /* PIR_SENSOR_H_ */
