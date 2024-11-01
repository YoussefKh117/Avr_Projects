/*
 * DC_Motor.h
 *
 *  Created on: Oct 3, 2024
 *      Author: Youssef Khaled
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"

#define DC_MOTOR_PORT PORTB_ID /*Change to your port*/
#define IN1 PIN0_ID            /*Change to your pin*/
#define IN2 PIN1_ID            /*Change to your pin*/

typedef enum {
	Stop, /*Stop*/
	ClockWise, /*Clockwise*/
	Anti_ClockWise /*Anti-Clockwise*/
} DcMotor_State;
void DC_Motor_Init();
void DC_Motor_Rotate(uint8 state, uint8 speed);

#endif /* DC_MOTOR_H_ */
