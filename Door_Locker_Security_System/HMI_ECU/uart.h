/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Youssef Khaled
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum {
	ASYNCHRONOUS, SYNCHRONOUS
} UART_ModeType;

typedef enum {
	UART_DATA_5_BITS, UART_DATA_6_BITS, UART_DATA_7_BITS, UART_DATA_8_BITS
} UART_BitDataType;

typedef enum {
	UART_NO_PARITY = 0, UART_EVEN_PARITY = 2, UART_ODD_PARITY = 3
} UART_ParityType;

typedef enum {
	UART_ONE_STOP_BIT, UART_TWO_STOP_BITS
} UART_StopBitType;

typedef enum {
	UART_BAUD_RATE_2400 = 2400,
	UART_BAUD_RATE_4800 = 4800,
	UART_BAUD_RATE_9600 = 9600,
	UART_BAUD_RATE_14400 = 14400,
	UART_BAUD_RATE_19200 = 19200,
	UART_BAUD_RATE_28800 = 28800,
	UART_BAUD_RATE_38400 = 38400,
	UART_BAUD_RATE_57600 = 57600,
	UART_BAUD_RATE_76800 = 76800,
	UART_BAUD_RATE_115200 = 115200,
	UART_BAUD_RATE_230400 = 230400,
	UART_BAUD_RATE_250000 = 250000
} UART_BaudRateType;

typedef struct {
	UART_ModeType Mode;
	UART_BitDataType Bit_Size;
	UART_ParityType Parity;
	UART_StopBitType Stop_Bit;
	UART_BaudRateType Baud_Rate;
} UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
