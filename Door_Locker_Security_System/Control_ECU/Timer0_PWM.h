/*
 * Timer0_PWM.h
 *
 *  Created on: Oct 3, 2024
 *      Author: Youssef Khaled
 */

#ifndef TIMER0_PWM_H_
#define TIMER0_PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PWM_OUTPUT_PIN PIN3

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to init timer0 in PWM mode.
 */
void Timer0_init_PWM();

/*
 * Description :
 * Function to set duty cycle in PWM mode.
 */
void PWM_Set_Duty_Cycle(uint8 duty_cycle);

#endif /* TIMER0_PWM_H_ */
