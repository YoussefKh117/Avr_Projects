/*
 * Timer_Private.h
 *
 *  Created on: Oct 27, 2024
 *      Author: Youssef Khaled
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#include "std_types.h"

/*******************************************************************************
 *                 Timer0 Registers type structure declarations                *
 *******************************************************************************/

/* Bitmap structure for TCCR0 register */
typedef union {
    uint8 Byte; /* All register bits */
    struct {
        uint8 CS00_Bit :1; /* Clock Select Bit 0 */
        uint8 CS01_Bit :1; /* Clock Select Bit 1 */
        uint8 CS02_Bit :1; /* Clock Select Bit 2 */
        uint8 WGM00_Bit :1; /* Waveform Generation Mode Bit 0 */
        uint8 WGM01_Bit :1; /* Waveform Generation Mode Bit 1 */
        uint8 COM00_Bit :1; /* Compare Output Mode Bit 0 */
        uint8 COM01_Bit :1; /* Compare Output Mode Bit 1 */
        uint8 FOC0_Bit  :1; /* Force Output Compare */
    } Bits;
} Timer0_TCCR0;

/* Bitmap structure for TCNT0 register */
typedef union {
    uint8 Byte; /* All register bits */
    struct {
        uint8 TCNT0_0 :1; /* Timer Counter Bit 0 */
        uint8 TCNT0_1 :1; /* Timer Counter Bit 1 */
        uint8 TCNT0_2 :1; /* Timer Counter Bit 2 */
        uint8 TCNT0_3 :1; /* Timer Counter Bit 3 */
        uint8 TCNT0_4 :1; /* Timer Counter Bit 4 */
        uint8 TCNT0_5 :1; /* Timer Counter Bit 5 */
        uint8 TCNT0_6 :1; /* Timer Counter Bit 6 */
        uint8 TCNT0_7 :1; /* Timer Counter Bit 7 */
    } Bits;
} Timer0_TCNT0;

/* Bitmap structure for OCR0 register */
typedef union {
    uint8 Byte; /* All register bits */
    struct {
        uint8 OCR0_0 :1; /* Output Compare Register Bit 0 */
        uint8 OCR0_1 :1; /* Output Compare Register Bit 1 */
        uint8 OCR0_2 :1; /* Output Compare Register Bit 2 */
        uint8 OCR0_3 :1; /* Output Compare Register Bit 3 */
        uint8 OCR0_4 :1; /* Output Compare Register Bit 4 */
        uint8 OCR0_5 :1; /* Output Compare Register Bit 5 */
        uint8 OCR0_6 :1; /* Output Compare Register Bit 6 */
        uint8 OCR0_7 :1; /* Output Compare Register Bit 7 */
    } Bits;
} Timer0_OCR0;

/* Bitmap structure for TIMSK register */
typedef union {
    uint8 Byte; /* All register bits */
    struct {
        uint8 TOIE0_Bit :1; /* Timer Overflow Interrupt Enable */
        uint8 OCIE0_Bit :1; /* Output Compare Interrupt Enable */
        uint8 reserved :6; /* Reserved bits */
    } Bits;
} Timer0_TIMSK;

/* Bitmap structure for TIFR register */
typedef union {
    uint8 Byte; /* All register bits */
    struct {
        uint8 TOV0_Bit :1; /* Timer Overflow Flag */
        uint8 OCF0_Bit :1; /* Output Compare Flag */
        uint8 reserved :6; /* Reserved bits */
    } Bits;
} Timer0_TIFR;


/*******************************************************************************
 *                         Timer0 Registers Definitions                        *
 *******************************************************************************/
#define TCCR0_REG (*(volatile Timer0_TCCR0 *const)     0x53)
#define TCNT0_REG (*(volatile Timer0_TCNT0 *const)     0x52)
#define OCR0_REG  (*(volatile Timer0_OCR0 *const)      0x5C)
#define TIMSK_REG (*(volatile Timer0_TIMSK *const)     0x59)
#define TIFR_REG  (*(volatile Timer0_TIFR *const)      0x58)





/*******************************************************************************
 *                 Timer1 Registers type structure declarations                *
 *******************************************************************************/
/* Bitmap structure for TCCR1A register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 WGM10_Bit :1;  /* WGM10 bit 0 */
		uint8 WGM11_Bit :1;  /* WGM11 bit 1 */
		uint8 FOC1B_Bit :1;  /* FOC1B bit 2 */
		uint8 FOC1A_Bit :1;  /* FOC1A bit 3 */
		uint8 COM1B0_Bit :1; /* COM1B0 bit 4 */
		uint8 COM1B1_Bit :1; /* COM1B1 bit 5 */
		uint8 COM1A0_Bit :1; /* COM1A0 bit 6 */
		uint8 COM1A1_Bit :1; /* COM1A1 bit 7 */
	} Bits;
} Timer1_TCCR1A;

/* Bitmap structure for TCCR1B register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 CS10_Bit :1;  /* CS10 bit 0 */
		uint8 CS11_Bit :1;  /* CS11 bit 1 */
		uint8 CS12_Bit :1;  /* CS12 bit 2 */
		uint8 WGM12_Bit :1; /* WGM12 bit 3 */
		uint8 WGM13_Bit :1; /* WGM13 bit 4 */
		uint8 :1; 			/* Reserved bit 5 */
		uint8 ICES1_Bit :1; /* ICES1 bit 6 */
		uint8 ICNC1_Bit :1; /* ICNC1 bit 7 */
	} Bits;
} Timer1_TCCR1B;

/* Bitmap structure for TCNT1 register */
typedef union
{
    struct {
        uint8 TCNT1L; /* Low byte of Timer/Counter1 */
        uint8 TCNT1H; /* High byte of Timer/Counter1 */
    } Bytes;
    uint16 Word; /* Combined 16-bit Timer/Counter1 */
} Timer1_TCNT1;

/* Bitmap structure for OCR1A register */
typedef union
{
    struct {
        uint8 OCR1AL; /* Low byte of Output Compare Register 1 A */
        uint8 OCR1AH; /* High byte of Output Compare Register 1 A */
    } Bytes;
    uint16 Word; /* Combined 16-bit Output Compare Register 1 A */
} Timer1_OCR1A;

/* Bitmap structure for OCR1B register */
typedef union
{
    struct {
        uint8 OCR1BL; /* Low byte of Output Compare Register 1 B */
        uint8 OCR1BH; /* High byte of Output Compare Register 1 B */
    } Bytes;
    uint16 Word; /* Combined 16-bit Output Compare Register 1 B */
} Timer1_OCR1B;

/* Bitmap structure for ICR1 register */
typedef union {
    struct {
        uint8 ICR1L; /* Low byte of Input Capture Register 1 */
        uint8 ICR1H; /* High byte of Input Capture Register 1 */
    } Bytes;
    uint16 Word; /* Combined 16-bit Input Capture Register 1 */
} Timer1_ICR1;

/* Bitmap structure for TIMSK register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 TOIE0_Bit :1; /* TOIE0 bit 0 */
		uint8 OCIE0_Bit :1; /* OCIE0 bit 1 */
		uint8 TOIE1_Bit :1; /* TOIE1 bit 2 */
		uint8 OCIE1B_Bit :1; /* OCIE1B bit 3 */
		uint8 OCIE1A_Bit :1; /* OCIE1A bit 4 */
		uint8 TICIE1_Bit :1; /* TICIE1 bit 5 */
		uint8 TOIE2_Bit :1; /* TOIE2 bit 6 */
		uint8 OCIE2_Bit :1; /* OCIE2 bit 7 */
	} Bits;
} Timer1_TIMSK;

/* Bitmap structure for TIFR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 TOV0_Bit :1; /* TOV0 bit 0 */
		uint8 OCF0_Bit :1; /* OCF0 bit 1 */
		uint8 TOV1_Bit :1; /* TOV1 bit 2 */
		uint8 OCF1B_Bit :1; /* OCF1B bit 3 */
		uint8 OCF1A_Bit :1; /* OCF1A bit 4 */
		uint8 ICF1_Bit :1; /* ICF1 bit 5 */
		uint8 TOV2_Bit :1; /* TOV2 bit 6 */
		uint8 OCF2_Bit :1; /* OCF2 bit 7 */
	} Bits;
} Timer1_TIFR;

/*******************************************************************************
 *                         Timer1 Registers Definitions
 *******************************************************************************/
#define TCCR1A_REG (*(volatile Timer1_TCCR1A *const)     0x4F) /* Timer1 Control Register A */
#define TCCR1B_REG (*(volatile Timer1_TCCR1B *const)     0x4E) /* Timer1 Control Register B */
#define TCNT1_REG (*(volatile Timer1_TCNT1 *const)       0x4C) /* Timer1 Counter Register */
#define OCR1A_REG (*(volatile Timer1_OCR1A *const)       0x4A) /* Timer1 Output Compare Register A */
#define OCR1B_REG (*(volatile Timer1_OCR1B *const)       0x48) /* Timer1 Output Compare Register B */
#define ICR1_REG (*(volatile Timer1_ICR1 *const) 		 0x46) /* Input Capture Register 1 */
#define TIMSK1_REG (*(volatile Timer1_TIMSK *const)     0x59) /* Timer1 Interrupt Mask Register */
#define TIFR1_REG (*(volatile Timer1_TIFR *const)       0x58) /* Timer1 Interrupt Flag Register */



/*******************************************************************************
 *                 Timer2 Registers type structure declarations                *
 *******************************************************************************/

/* Bitmap structure for TCCR2 register */
typedef union {
    uint8 Byte; /* All register bits */
    struct {
        uint8 CS20_Bit :1;  /* Clock Select bit 0 */
        uint8 CS21_Bit :1;  /* Clock Select bit 1 */
        uint8 CS22_Bit :1;  /* Clock Select bit 2 */
        uint8 WGM21_Bit :1; /* WGM21 bit 1 */
        uint8 COM20_Bit :1; /* Compare Match Output Mode for OC2 */
        uint8 COM21_Bit :1; /* Compare Match Output Mode for OC2 */
        uint8 WGM20_Bit :1; /* WGM20 bit 0 */
        uint8 FOC2_Bit :1;  /* Force Output Compare */
    } Bits;
} Timer2_TCCR2;

/* Bitmap structure for TCNT2 register */
typedef union {
    uint8 Byte; /* Timer/Counter2 value */
} Timer2_TCNT2;

/* Bitmap structure for OCR2 register */
typedef union {
    uint8 Byte; /* Output Compare Register 2 value */
} Timer2_OCR2;

/* Bitmap structure for TIMSK2 register */
typedef union {
    uint8 Byte; /* All register bits */
    struct {
        uint8 reserved :6;   /* Reserved bits */
        uint8 OCIE2_Bit :1; /* Output Compare Interrupt Enable */
        uint8 TOIE2_Bit :1; /* Timer Overflow Interrupt Enable */
    } Bits;
} Timer2_TIMSK;

/* Bitmap structure for TIFR2 register */
typedef union {
    uint8 Byte; /* All register bits */
    struct {
        uint8 reserved :6;  /* Reserved bits */
        uint8 OCF2_Bit :1; /* Output Compare Flag */
        uint8 TOV2_Bit :1; /* Timer Overflow Flag */
    } Bits;
} Timer2_TIFR;

/*******************************************************************************
 *                         Timer2 Registers Definitions
 *******************************************************************************/
#define TCCR2_REG (*(volatile Timer2_TCCR2 *const)     0x45) /* Timer2 Control Register */
#define TCNT2_REG (*(volatile Timer2_TCNT2 *const)       0x44) /* Timer2 Counter Register */
#define OCR2_REG (*(volatile Timer2_OCR2 *const)         0x43) /* Timer2 Output Compare Register */
#define TIMSK2_REG (*(volatile Timer2_TIMSK *const)     0x59) /* Timer2 Interrupt Mask Register */
#define TIFR2_REG (*(volatile Timer2_TIFR *const)       0x58) /* Timer2 Interrupt Flag Register */


#endif /* TIMER_PRIVATE_H_ */
