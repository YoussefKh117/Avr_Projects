/*
 * DC_Motor.h
 *
 *  Created on: Oct 3, 2024
 *      Author: Youssef Khaled
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DC_MOTOR_PORT PORTB_ID /*Change to your port*/
#define IN1 PIN0_ID            /*Change to your pin*/
#define IN2 PIN1_ID            /*Change to your pin*/

typedef enum {
	Stop, /*Stop*/
	ClockWise, /*Clockwise*/
	Anti_ClockWise /*Anti-Clockwise*/
} DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Function responsible initializes the DC motor pins */
void DC_Motor_Init();

/* Function responsible initializes the DC motor state (CW,A-CW,S) and Speed */
void DC_Motor_Rotate(uint8 state, uint8 speed);

#endif /* DC_MOTOR_H_ */
