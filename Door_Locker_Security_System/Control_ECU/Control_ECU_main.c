/*
 * Control_ECU_main.c
 *
 *  Created on: Oct 27, 2024
 *      Author: Youssef Khaled
 */

#include "std_types.h"
#include "uart.h"
#include "twi.h"
#include "DC_Motor.h"
#include "external_eeprom.h"
#include "Buzzer.h"
#include "Timer.h"
#include "Timer0_PWM.h"
#include "GPIO_private.h"
#include "PIR_Sensor.h"
#include <util/delay.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile uint8 g_ticks = 0;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define youssef_is_here 				1
#define START_COMMUNICATION			    0x11
#define CTC_VALUE_FOR_ONE_SECOND 		31249
#define CTC_INITIAL_VALUE 				0
#define PASSWORD_CORRECT            	0xAA
#define PASSWORD_INCORRECT          	0xBB
#define CREATE_PASSWORD_ACTION      	0xCC
#define CHECK_PASSWORD_ACTION       	0xDD
#define CHANGE_PASSWORD_MODE        	0xEE
#define OPEN_DOOR_MODE              	0xFF
#define PEOPLE_ENTERING         		0x00
#define NO_PEOPLE_ENTERING         		0x02
#define BUZZER_ON                   	0x68
#define BUZZER_OFF               	   	0x69
#define BUZZER_ACTIVE_PERIOD			5
#define PASSWORD_LENGTH					5
#define DOOR_UNLOCKING_PERIOD        	5
#define DOOR_LOCKING_PERIOD          	5
#define NUMBER_OF_PASSWORD_TRIES	 	3
#define EEPROM_FIRST_ADDRESS_VALUE  	0x0311

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

/*
 * Description :
 * Function to save the received password through UART to EEPROM.
 * Function input:  void.
 * Function output: void.
 */
void SavePasswordToEEPROM();

/*
 * Description :
 * Function to receive password through UART and check
 * it with the one in EEPROM .
 * Function input:  void.
 * Function output: uint8 flag which indicate password correct.
 */
uint8 RecivePasswordAndCheck();

/*
 * Description :
 * Function to count a number of seconds which passed to it.
 * Function input:  number of seconds.
 * Function output: void.
 */
void Timer1_DelaySecond(uint8 time);

/*
 * Description :
 * This is the call back function which will be executed each interrupt in timer1.
 * Function input:  void.
 * Function output: void.
 */
void countOneSecond(void);

/* ################################ Main Program ################################ */

int main() {
	/* Configuration and initialization functions */
	/* Enable Global interrupt SREG */
	SREG_REG.Bits.I_Bit = 1;
	uint8 flag, action, mode;
	/* select the configuration of UART */
	UART_ConfigType uart_config = { ASYNCHRONOUS, UART_DATA_8_BITS,
			UART_NO_PARITY, UART_ONE_STOP_BIT, UART_BAUD_RATE_9600 };
	/*Passing configuration to uart init*/
	UART_init(&uart_config);
	/* select the configuration of TWI */
	TWI_ConfigType twi_config =
			{ MC_ADDRESS, TWI_PRESCALER_1, TWI_BAUDRATE_400K };
	/* passing the configuration to initialization function of TWI */
	TWI_init(&twi_config);
	/*Initialization buzzer*/
	Buzzer_init();
	/* call the initialization function of PWM TIMER0 */
	Timer0_init_PWM();
	/*Initialization DC motor*/
	DC_Motor_Init();
	/*Initialization PIR Sensor*/
	PIR_init();

	while (youssef_is_here) {
		/* receive the action from HMI ECU through UART */
		action = UART_recieveByte();
		/* if the action is create password, then receive and save it */
		if (action == CREATE_PASSWORD_ACTION) {
			SavePasswordToEEPROM();
		} else if (action == CHECK_PASSWORD_ACTION) {
			/* the action is check password */
			/* receive the mode from HMI ECU through UART */
			mode = UART_recieveByte();
			if (mode == OPEN_DOOR_MODE) {
				/* mode is open door mode */
				while (youssef_is_here) {
					/* receive the password and check if equal to the one in EEPROM */
					flag = RecivePasswordAndCheck();
					if (flag) {
						/* the password is correct and send to HMI that password is correct */
						UART_sendByte(PASSWORD_CORRECT);
						/* turn on motor at max speed with clock wise direction */
						DC_Motor_Rotate(ClockWise, 100);
						/* waiting for 15 seconds until the door is unlocking */
						Timer1_DelaySecond(DOOR_UNLOCKING_PERIOD);
						/*wait until no people are entering*/
						DC_Motor_Rotate(Stop, 0);
						while (1) {
							if (PIR_getValue()) {
								/*If motion detected*/
								UART_sendByte(PEOPLE_ENTERING);
							} else {
								/*If no motion is detected, lock the door*/
								UART_sendByte(NO_PEOPLE_ENTERING);
								/*Timer1_DelaySecond(3);*/
								break;
							}
						}
						/* turn on motor at max speed with anti clock wise direction */
						DC_Motor_Rotate(Anti_ClockWise, 100);
						/* waiting for 15 seconds until the door is locking  */
						Timer1_DelaySecond(DOOR_LOCKING_PERIOD);
						/*Stop the DC motor*/
						DC_Motor_Rotate(Stop, 0);
						break;
					} else {
						/* the password is incorrect and send to HMI that password is incorrect */
						UART_sendByte(PASSWORD_INCORRECT);
						/* wait for replay from HMI ECU to take an action of incorrect password */
						if (UART_recieveByte() == BUZZER_ON) {
							/* if receiving buzzer on byte, that mean the 3 tries is made */
							/* turn on the buzzer */
							Buzzer_on();
							/* waiting for 1 minute */
							Timer1_DelaySecond(BUZZER_ACTIVE_PERIOD);
							/* turn off the buzzer */
							Buzzer_off();
							break;
						} else {
							continue;
						}
					}
				}
			} else if (mode == CHANGE_PASSWORD_MODE) {
				/*mode is change password*/
				while (youssef_is_here) {
					/* receive the password and check if equal to the one in EEPROM */
					flag = RecivePasswordAndCheck();
					if (flag) {
						/* the password is correct and send to HMI that password is correct */
						UART_sendByte(PASSWORD_CORRECT);
						/* start the action of change password */
						SavePasswordToEEPROM();
						break;
					} else {
						/* the password is incorrect and send to HMI that password is incorrect */
						UART_sendByte(PASSWORD_INCORRECT);
						if (UART_recieveByte() == BUZZER_ON) {
							/* if receiving buzzer on byte, that mean the 3 tries is made */
							/* turn on the buzzer */
							Buzzer_on();
							/* waiting for 1 minute */
							Timer1_DelaySecond(BUZZER_ACTIVE_PERIOD);
							/* turn off the buzzer */
							Buzzer_off();
							break;
						} else {
							continue;
						}
					}
				}
			}
		}
	}

}

/*******************************************************************************
 *                           Functions Definitions                            *
 *******************************************************************************/

/*
 * Description :
 * Function to save the received password through UART to EEPROM.
 * Function input:  void.
 * Function output: void.
 */
void SavePasswordToEEPROM() {
	uint8 i = 0; // Counter for password digits
	uint8 temp;
	while (i < PASSWORD_LENGTH) {
		UART_sendByte(START_COMMUNICATION);
		/* recieving bytes */
		temp = UART_recieveByte();
		/*store every recieved byte in EEPROM*/
		EEPROM_writeByte(EEPROM_FIRST_ADDRESS_VALUE + i, temp);
		_delay_ms(10); /* delay for EEPROM*/
		i++;
	}
}

/*
 * Description :
 * Function to receive password through UART and check
 * it with the one in EEPROM .
 * Function input:  void.
 * Function output: uint8 flag which indicate password correct.
 */
uint8 RecivePasswordAndCheck() {
	/*temp1 to get the password from HMI , temp2 to get the password from EEPROM*/
	uint8 temp1, temp2, Password_Checker;
	uint8 i = 0;
	/* we suppose at first the password is correct */
	Password_Checker = TRUE;
	while (i < PASSWORD_LENGTH) {
		/* send to HMI ECU that the control ECU is ready to receive byte */
		UART_sendByte(START_COMMUNICATION);
		temp1 = UART_recieveByte();
		EEPROM_readByte(EEPROM_FIRST_ADDRESS_VALUE + i, &temp2);
		if (temp1 != temp2) {
			Password_Checker = FALSE;
		}
		i++;
	}
	if (Password_Checker) {
		UART_sendByte(PASSWORD_CORRECT);
	} else {
		UART_sendByte(PASSWORD_INCORRECT);
	}
	return Password_Checker;
}

/*
 * Description :
 * Function to count a number of seconds which passed to it.
 * Function input:  number of seconds.
 * Function output: void.
 */
void Timer1_DelaySecond(uint8 time) {
	Timer_ConfigType timer_config = { CTC_INITIAL_VALUE,
	CTC_VALUE_FOR_ONE_SECOND, TIMER1, PRESCALER_256, COMPARE_MODE };
	/* setup the call back function */
	Timer_setCallBack(countOneSecond, TIMER1);
	/* passing the configuration to initialization function of TIMER1 */
	Timer_init(&timer_config);
	/* waiting for 15 seconds until the door is unlocking */
	while (g_ticks < time)
		;
	/* reset the global variable of ticks */
	g_ticks = 0;
	/*Stop the Timer*/
	Timer_deInit(TIMER1);
}

/*
 * Description :
 * This is the call back function which will be executed each interrupt in timer1.
 * Function input:  void.
 * Function output: void.
 */
void countOneSecond(void) {
	/*Increase ticks every 1 second*/
	g_ticks++;
}
