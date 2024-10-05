/*
 * LDR.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Youssef Khaled
 */

#include "LDR.h"
#include "ADC.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the Light intensity from the ADC digital value.
 */
uint16 LDR_getLightIntensity(void)
{
	/*Variable to store the calculated light intensity*/
	uint16 Light_value = 0;
	/*Variable to store the raw ADC value*/
	uint16 adc_value = 0;

	/* Read ADC channel where the LDR sensor is connected */
	adc_value = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	Light_value = (uint16)(((uint32)adc_value*LDR_SENSOR_MAX_LIGHT_INTENSITY*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*LDR_SENSOR_MAX_VOLT_VALUE));

	return Light_value;
}

