/*
 * HMI_ECU_main.c
 *
 *  Created on: Oct 27, 2024
 *      Author: Youssef Khaled
 */

#include "std_types.h"
#include "Timer.h"
#include "GPIO_private.h"
#include "uart.h"
#include "LCD.h"
#include "Keypad.h"
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

/*******************************************************************************
 *                            Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Function to active keypad to get input number from it.
 * Function input: array of uint8 to save numbers from keypad on it.
 * */
void GetPasswordFromKeyPad(uint8 password[]);

/*
 * Description :
 * Function to create password and save it to EEPROM :
 * 1. Take password and confirm password from user.
 * 2. Compare the two passwords.
 * 3. If the two passwords are matched, then send it through UART
 * 	  to control ECU and save it to EEPROM.
 * 4. If the two passwords are not matched, then repeat step1.
 * Function input:  void.
 * Function return: uint8 (as a flag).
 */
uint8 CreatePassword();

/*
 * Description :
 * Function to take confirm password then compare it with password and return if matched or not.
 * Function input: two arrays of uint8 to compare between them.
 * Function output: uint8 flag that indicate the matching of passwords.
 */
uint8 comparePasswords(uint8 password[], uint8 confirmPassword[]);

/*
 * Description :
 * Function to send password through UART to control ECU.
 * Function input:  array of uint8 to send it to control ECU.
 * Function output: void.
 */
void sendPasswordToControlECU(uint8 password[]);

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
	uint8 temp, number_of_tries, Password_Created, Password_Changed;
	uint8 password[5];
	/* select the configuration of UART */
	UART_ConfigType uart_config = { ASYNCHRONOUS, UART_DATA_8_BITS,
			UART_NO_PARITY, UART_ONE_STOP_BIT, UART_BAUD_RATE_9600 };
	/*Passing configuration to uart init*/
	UART_init(&uart_config);
	/*Initialize LCD*/
	LCD_init();
	LCD_clearScreen();
	LCD_displayString("  Final Project ");
	LCD_moveCursor(1, 0);
	LCD_displayString("Edges Diploma 90");
	_delay_ms(250);
	LCD_clearScreen();
	LCD_displayString("     Made By    ");
	LCD_moveCursor(1, 0);
	LCD_displayString(" Youssef Khaled ");
	_delay_ms(250);
	LCD_clearScreen();
	LCD_displayString("Heartfelt thanks");
	LCD_moveCursor(1, 0);
	LCD_displayString("to MohamedTarek");
	_delay_ms(250);
	LCD_clearScreen();
	while (youssef_is_here) {
		/*
		 * select the action of create password at the start of program.
		 * the byte which sent to control ECU tell him to be ready to receive password
		 * after check matching here.
		 */
		UART_sendByte(CREATE_PASSWORD_ACTION);
		/*At first no password created*/
		Password_Created = FALSE;
		/* loop until the password is created and saved successfully to EEPROM */
		while (Password_Created == FALSE) {
			Password_Created = CreatePassword();
		}
		/*Main menu of program*/
		while (youssef_is_here) {
			LCD_clearScreen();
			LCD_displayString("+ : Open Door");
			LCD_moveCursor(1, 0);
			LCD_displayString("- : Change Pass");
			/* get the option from user using keypad */
			temp = KEYPAD_getPressedKey();
			/* if choosing first option => open door */
			if (temp == '+') {
				/* variable to count number of tries */
				number_of_tries = 0;
				/*
				 * select the action of check password.
				 * the byte which sent to control ECU tell him to be ready to check
				 * the received password with the password in EEPROM.
				 */
				UART_sendByte(CHECK_PASSWORD_ACTION);
				/*
				 * select the mode of open door.
				 * the byte which sent to control ECU tell him to be ready for
				 * open door mode.
				 */
				UART_sendByte(OPEN_DOOR_MODE);
				while (youssef_is_here) {
					LCD_clearScreen();
					LCD_displayString("plz enter pass:");
					LCD_moveCursor(1, 0);
					GetPasswordFromKeyPad(password);
					/* send the password to control ECU to check if correct or not */
					sendPasswordToControlECU(password);
					_delay_ms(100);
					/* the control ECU will replay with a byte which indicate if password correct or not */
					uint8 respone = UART_recieveByte();
					if (respone == PASSWORD_CORRECT) {
						/* reset the tries variable */
						number_of_tries = 0;
						LCD_clearScreen();
						LCD_displayString("Correct Password");
						LCD_clearScreen();
						/* the password is correct, then start door open mode */
						LCD_clearScreen();
						LCD_displayString("    Door is     ");
						LCD_moveCursor(1, 0);
						LCD_displayString("   Unlocking    ");
						/* waiting for 15 seconds until the door is unlocking */
						Timer1_DelaySecond(DOOR_UNLOCKING_PERIOD);
						LCD_clearScreen();
						LCD_displayString("wait fr checking");
						LCD_moveCursor(1, 0);
						LCD_displayString(" people to enter");
						_delay_ms(250);
						uint8 people, msg = 0;
						while (youssef_is_here) {
							people = UART_recieveByte();
							if (people == NO_PEOPLE_ENTERING) {
								break; /*Exit loop and proceed to lock the door*/
							} else if (people == PEOPLE_ENTERING && msg != 1) {
								LCD_clearScreen();
								LCD_displayString(" People Entering");
								LCD_moveCursor(1, 0);
								LCD_displayString("   Please wait  ");
								msg = 1;
								_delay_ms(500);
							}
						}
						// Continuously check for people entering
						/*						uint8 peopleEntering = TRUE;
						 while (peopleEntering) {
						 if (UART_recieveByte() == NO_PEOPLE_ENTERING) {
						 peopleEntering = FALSE;
						 }
						 }*/
						LCD_clearScreen();
						LCD_displayString("    Door is     ");
						LCD_moveCursor(1, 0);
						LCD_displayString("    locking     ");
						/* waiting for 15 seconds until the door is locking */
						Timer1_DelaySecond(DOOR_LOCKING_PERIOD);
						break;
					} else if (respone == PASSWORD_INCORRECT) {
						LCD_clearScreen();
						LCD_displayString("Wrong Password");
						_delay_ms(500);
						/* each time the entered password is incorrect, the try variable increment by 1 */
						number_of_tries++;
						/* if the tries reach to 3, send to control ECU to enable the buzzer */
						if (number_of_tries == NUMBER_OF_PASSWORD_TRIES) {
							UART_sendByte(BUZZER_ON);
						} else {
							UART_sendByte(BUZZER_OFF);
						}
					}
					if (number_of_tries == NUMBER_OF_PASSWORD_TRIES) {
						LCD_clearScreen();
						LCD_displayString("  System Locked ");
						LCD_moveCursor(1, 0);
						LCD_displayString("Wait for 1 min");
						/* waiting for 1 minute for the */
						Timer1_DelaySecond(BUZZER_ACTIVE_PERIOD);
						/* reset the tries variable */
						number_of_tries = 0;
						break;
					}

				}
			}
			/* if choosing second option => change password */
			else if (temp == '-') {
				/*reset the number of tries*/
				number_of_tries = 0;
				/*
				 * select the action of check password.
				 * the byte which sent to control ECU tell him to be ready to check
				 * the received password with the password in EEPROM.
				 */
				UART_sendByte(CHECK_PASSWORD_ACTION);
				/*
				 * select the mode of open door.
				 * the byte which sent to control ECU tell him to be ready for
				 * change password mode.
				 */
				UART_sendByte(CHANGE_PASSWORD_MODE);
				while (youssef_is_here) {
					LCD_clearScreen();
					LCD_displayString("plz enter old");
					LCD_moveCursor(1, 0);
					LCD_displayString("pass :) ");
					/* take the password from user using keypad */
					GetPasswordFromKeyPad(password);
					/* send the password to control ECU to check if correct or not */
					sendPasswordToControlECU(password);
					/* the control ECU will replay with a byte which indicate if password correct or not */
					if (UART_recieveByte() == PASSWORD_CORRECT) {
						LCD_clearScreen();
						LCD_displayString("Correct Password");
						_delay_ms(250);
						Password_Changed = FALSE;
						/* loop until the password is changed and saved successfully to EEPROM */
						while (Password_Changed == FALSE) {
							Password_Changed = CreatePassword();
						}
						LCD_clearScreen();
						LCD_displayString("Password Changed");
						LCD_moveCursor(1, 0);
						LCD_displayString("  Successfully  ");
						_delay_ms(250);
						/* reset the tries variable */
						number_of_tries = 0;
						break;
					} else {
						LCD_clearScreen();
						LCD_displayString("Wrong Password");
						_delay_ms(500);
						/* each time the entered password is incorrect, the try variable increment by 1 */
						number_of_tries++;
						/* if the tries reach to 3, send to control ECU to enable the buzzer */
						if (number_of_tries == NUMBER_OF_PASSWORD_TRIES) {
							UART_sendByte(BUZZER_ON);
						} else {
							UART_sendByte(BUZZER_OFF);
						}
					}
					/* if the tries reach to 3, display error massage on LCD */
					if (number_of_tries == NUMBER_OF_PASSWORD_TRIES) {
						LCD_clearScreen();
						LCD_displayString("  System Locked ");
						LCD_moveCursor(1, 0);
						LCD_displayString("Wait for 1 min");
						/* waiting for 1 minute for the */
						Timer1_DelaySecond(BUZZER_ACTIVE_PERIOD);
						/* reset the tries variable */
						number_of_tries = 0;
						break;
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
 * Function to create password and save it to EEPROM :
 * 1. Take password and confirm password from user.
 * 2. Compare the two passwords.
 * 3. If the two passwords are matched, then send it through UART
 * 	  to control ECU and save it to EEPROM.
 * 4. If the two passwords are not matched, then repeat step1.
 * Function input:  void.
 * Function return: uint8 (as a flag).
 */
uint8 CreatePassword() {
	uint8 Password[PASSWORD_LENGTH]; /* array to save password on it */
	uint8 Confirm_Password[PASSWORD_LENGTH]; /* array to save the confirmed password on it */
	uint8 Flag = 0; /* flag to indicate the matching of the two passwords */
	while (youssef_is_here) {
		/*First clear screen*/
		LCD_clearScreen();
		LCD_displayString("Plz Enter Pass :");
		/*Move cursor to second row*/
		LCD_moveCursor(1, 0);
		/*Call a function to get the password*/
		GetPasswordFromKeyPad(Password);
		/*Clear the screen*/
		LCD_clearScreen();
		LCD_displayString("Plz re-enter the:");
		/*Move cursor to second row*/
		LCD_moveCursor(1, 0);
		LCD_displayString("same pass: ");
		LCD_moveCursor(1, 11);
		/*Call a function to get the Cofirmation_password*/
		GetPasswordFromKeyPad(Confirm_Password);
		Flag = comparePasswords(Password, Confirm_Password);
		if (Flag) {
			sendPasswordToControlECU(Password);
			LCD_clearScreen();
			LCD_displayString("The 2 Passwords");
			LCD_moveCursor(1, 0);
			LCD_displayString("Are Matched :)");
			_delay_ms(250);
			/* return true to not repeat this step as password created successfully */
			return TRUE;
			/*break;*/
		} else {
			LCD_clearScreen();
			LCD_displayString("The 2 Passwords");
			LCD_moveCursor(1, 0);
			LCD_displayString("Are not match-_-");
			_delay_ms(250);
			/* return false to repeat this step as password is not created successfully */
			return FALSE;
		}
	}
}
/*
 * Description :
 * Function to active keypad to get input number from it.
 * Function input: array of uint8 to save numbers from keypad on it.
 * */
void GetPasswordFromKeyPad(uint8 password[]) {
	uint8 i = 0; // Counter for password digits
	uint8 temp;
	while (i < PASSWORD_LENGTH) {
		// Get a keypress from the keypad
		temp = KEYPAD_getPressedKey();
		_delay_ms(250); // Debounce delay

		// Check if the pressed key is a number (0-9)
		if (temp >= 0 && temp <= 9) {
			password[i] = temp;
			LCD_displayCharacter('*'); // Display '*' for each character
			i++; // Move to the next digit
		}
	}

// Wait for the user to press the '#' key as an "Enter" key
	while (KEYPAD_getPressedKey() != '#')
		;
}
/*
 * Description :
 * Function to take confirm password then compare it with password and return if matched or not.
 * Function input: two arrays of uint8 to compare between them.
 * Function output: uint8 flag that indicate the matching of passwords.
 */
uint8 comparePasswords(uint8 password[], uint8 confirmPassword[]) {
	for (uint8 i = 0; i < PASSWORD_LENGTH; i++) {
		if (password[i] != confirmPassword[i]) {
			return 0; /* Passwords do not match */
		}
	}
	return 1; /* Passwords match */
}
/*
 * Description :
 * Function to send password through UART to control ECU.
 * Function input:  array of uint8 to send it to control ECU.
 * Function output: void.
 */
void sendPasswordToControlECU(uint8 password[]) {
	uint8 i;
	i = 0;
	while (i < PASSWORD_LENGTH) {
		/* waiting the replay from control that it is ready to receive again */
		while (UART_recieveByte() != START_COMMUNICATION)
			;
		/* send the password byte by byte to control ECU through UART  */
		UART_sendByte(password[i]);
		i++;
	}
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
