/*
 * LDR.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Youssef Khaled
 */

#ifndef LDR_H_
#define LDR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define LDR_SENSOR_CHANNEL_ID        	  0
#define LDR_SENSOR_MAX_VOLT_VALUE     	  2.56
#define LDR_SENSOR_MAX_LIGHT_INTENSITY    100

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint16 LDR_getLightIntensity();

#endif /* LDR_H_ */
