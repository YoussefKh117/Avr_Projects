/*
 * Timer.c
 *
 *  Created on: Oct 27, 2024
 *      Author: Youssef Khaled
 */

#include "Timer_Private.h"
#include "Timer.h"
#include "avr/interrupt.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
/* Array for callback functions for each timer*/
static volatile void (*g_callBackPtr[3])(void) = {NULL_PTR,NULL_PTR,NULL_PTR };

/*******************************************************************************
 *                          Private Functions                                  *
 *******************************************************************************/
static void Timer0_init(const Timer_ConfigType *Config_Ptr);
static void Timer1_init(const Timer_ConfigType *Config_Ptr);
static void Timer2_init(const Timer_ConfigType *Config_Ptr);
static void Timer0_deInit(void);
static void Timer1_deInit(void);
static void Timer2_deInit(void);

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect) {
	if (g_callBackPtr[0] != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[0])();
	}
}

ISR(TIMER0_COMP_vect) {
	if (g_callBackPtr[0] != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[0])();
	}
}

ISR(TIMER1_OVF_vect) {
	if (g_callBackPtr[1] != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[1])();
	}
}

ISR(TIMER1_COMPA_vect) {
	if (g_callBackPtr[1] != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[1])();
	}
}

ISR(TIMER2_OVF_vect) {
	if (g_callBackPtr[2] != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[2])();
	}
}

ISR(TIMER2_COMP_vect) {
	if (g_callBackPtr[2] != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[2])();
	}
}

/*******************************************************************************
 *                            Function Definitions                             *
 *******************************************************************************/

void Timer_init(const Timer_ConfigType *Config_Ptr) {
	switch (Config_Ptr->timer_ID) {
	case TIMER0:
		Timer0_init(Config_Ptr);
		break;
	case TIMER1:
		Timer1_init(Config_Ptr);
		break;
	case TIMER2:
		Timer2_init(Config_Ptr);
		break;
	}
}

void Timer_deInit(Timer_ID_Type timer_type) {
	switch (timer_type) {
	case TIMER0:
		Timer0_deInit();
		break;
	case TIMER1:
		Timer1_deInit();
		break;
	case TIMER2:
		Timer2_deInit();
		break;
	}
}

void Timer_setCallBack(void (*a_ptr)(void), Timer_ID_Type a_timer_ID) {
	g_callBackPtr[a_timer_ID] = a_ptr;
}

/*******************************************************************************
 *                          Timer0 Functions                                   *
 *******************************************************************************/

static void Timer0_init(const Timer_ConfigType *Config_Ptr) {
	/* Set the initial value */
	TCNT0_REG.Byte = Config_Ptr->timer_InitialValue;

	/* Set the prescaler based on the provided timer_clock */
	switch (Config_Ptr->timer_clock) {
	case NO_CLOCK:
		/* Stop the timer */
		TCCR0_REG.Bits.CS00_Bit = 0;
		TCCR0_REG.Bits.CS01_Bit = 0;
		TCCR0_REG.Bits.CS02_Bit = 0;
		break;
	case PRESCALER_1:
		TCCR0_REG.Bits.CS00_Bit = 1;
		break;
	case PRESCALER_8:
		TCCR0_REG.Bits.CS01_Bit = 1;
		break;
	case PRESCALER_64:
		TCCR0_REG.Bits.CS00_Bit = 1;
		TCCR0_REG.Bits.CS01_Bit = 1;
		break;
	case PRESCALER_256:
		TCCR0_REG.Bits.CS02_Bit = 1;
		break;
	case PRESCALER_1024:
		TCCR0_REG.Bits.CS02_Bit = 1;
		TCCR0_REG.Bits.CS00_Bit = 1;
		break;
	}

	if (Config_Ptr->timer_mode == NORMAL_MODE) {
		/* Enable Timer0 overflow interrupt */
		TIMSK_REG.Bits.TOIE0_Bit = 1;
	} else if (Config_Ptr->timer_mode == COMPARE_MODE) {
		/* Set compare match value */
		OCR0_REG.Byte = Config_Ptr->timer_compare_MatchValue;

		/* Enable Timer0 compare interrupt */
		TIMSK_REG.Bits.OCIE0_Bit = 1;
	}
}

// Timer0 de-initialization
static void Timer0_deInit(void) {
	TCCR0_REG.Byte = 0; /* Stop the timer */
	 /* Clear the prescaler bits in TCCR0 to stop the timer */
	TCCR0_REG.Bits.CS00_Bit = 0; /* Clear Clock Select Bit 0 */
	TCCR0_REG.Bits.CS01_Bit = 0; /* Clear Clock Select Bit 1 */
	TCCR0_REG.Bits.CS02_Bit = 0; /* Clear Clock Select Bit 2 */

	TIMSK_REG.Bits.TOIE0_Bit = 0; /* Disable Timer0 overflow interrupt */
	TIMSK_REG.Bits.OCIE0_Bit = 0; /* Disable Timer0 compare interrupt */

	g_callBackPtr[0] = NULL_PTR;
}

/*******************************************************************************
 *                          Timer1 Functions                                   *
 *******************************************************************************/

static void Timer1_init(const Timer_ConfigType *Config_Ptr) {

	/************************** TCCR1A Description **************************
	 * COM1A1:0 = 00  Normal port operation, OC1A disconnected
	 * COM1B1:0 = 00  Normal port operation, OC1B disconnected
	 * FOC1A    = 1   Force Output Compare for Compare unit A (non-PWM mode)
	 * FOC1B    = 1   Force Output Compare for Compare unit B (non-PWM mode)
	 * WGM11:0        Waveform Generation Mode, selected in configuration
	 ***********************************************************************/

	TCCR1A_REG.Bits.FOC1A_Bit = 1;
	TCCR1A_REG.Bits.FOC1B_Bit = 1;

	/*
	 * insert the required mode in WGM bits (WGM10 and WGM11) of TCCR1A Register
	 * and (WGM12 and WGM13) of TCCR1B Register
	 */

	if (Config_Ptr->timer_mode == NORMAL_MODE) {
		TCCR1A_REG.Bits.WGM10_Bit = 0;
		TCCR1A_REG.Bits.WGM11_Bit = 0;
		TCCR1B_REG.Bits.WGM12_Bit = 0;
		TCCR1B_REG.Bits.WGM13_Bit = 0;
	} else if (Config_Ptr->timer_mode == COMPARE_MODE) {
		TCCR1A_REG.Bits.WGM10_Bit = 0;
		TCCR1A_REG.Bits.WGM11_Bit = 0;
		TCCR1B_REG.Bits.WGM12_Bit = 1;
		TCCR1B_REG.Bits.WGM13_Bit = 0;
	}

	/************************** TCCR1B Description **************************
	 * ICNC1    = 0   Input Capture Noise Canceller
	 * ICES1    = 0   Input Capture Edge Select
	 * WGM13:2        Waveform Generation Mode, selected in configuration
	 * CS12:0   = 0   Clock Select, selected in configuration
	 ***********************************************************************/

	/* Set the prescaler based on the provided timer_clock */
	TCCR1B_REG.Byte = (0xF8 & TCCR1B_REG.Byte) | (Config_Ptr->timer_clock);

	/* Set Initial value */
	TCNT1_REG.Word = Config_Ptr->timer_InitialValue;

	/* Check For mode */
	if (Config_Ptr->timer_mode == NORMAL_MODE) {
		/* Enable Timer1 overflow interrupt */
		TIMSK1_REG.Bits.TOIE1_Bit = 1;

	} else if (Config_Ptr->timer_mode == COMPARE_MODE) {
		/* Set compare match value */
		OCR1A_REG.Word = Config_Ptr->timer_compare_MatchValue;

		/* Enable Timer1 compare interrupt */
		TIMSK1_REG.Bits.OCIE1A_Bit = 1;
	}
}

static void Timer1_deInit(void) {
	/* Reset TCCR1A and TCCR1B registers to their default values */
	TCCR1A_REG.Byte = 0;
	TCCR1B_REG.Byte = 0;

	/* Clear the Timer1 counter register */
	TCNT1_REG.Word = 0;

	/* Clear the Output Compare Register */
	OCR1A_REG.Word = 0;

	/* Disable Timer1 overflow interrupt */
	TIMSK1_REG.Bits.TOIE1_Bit = 0;

	/* Disable Timer1 compare match interrupt */
	TIMSK1_REG.Bits.OCIE1A_Bit = 0;

	g_callBackPtr[1] = NULL_PTR;
}

/*******************************************************************************
 *                          Timer2 Functions                                   *
 *******************************************************************************/

static void Timer2_init(const Timer_ConfigType *Config_Ptr) {
	/* Set the initial value */
	TCNT2_REG.Byte = Config_Ptr->timer_InitialValue;

	/* Force Output Compare */
	TCCR2_REG.Bits.FOC2_Bit = 1;

	switch (Config_Ptr->timer_clock) {
	case NO_CLOCK:
		/* Stop the timer */
		TCCR2_REG.Bits.CS20_Bit = 0;
		TCCR2_REG.Bits.CS21_Bit = 0;
		TCCR2_REG.Bits.CS22_Bit = 0;
		break;
	case PRESCALER_1:
		TCCR2_REG.Bits.CS20_Bit = 1;
		break;
	case PRESCALER_8:
		TCCR2_REG.Bits.CS21_Bit = 1;
		break;
	case PRESCALER_64:
		TCCR2_REG.Bits.CS22_Bit = 1;
		break;
	case PRESCALER_256:
		TCCR2_REG.Bits.CS21_Bit = 1;
		TCCR2_REG.Bits.CS22_Bit = 1;
		break;
	case PRESCALER_1024:
		TCCR2_REG.Bits.CS22_Bit = 1;
		TCCR2_REG.Bits.CS21_Bit = 1;
		TCCR2_REG.Bits.CS20_Bit = 1;
		break;
	}
	if (Config_Ptr->timer_mode == NORMAL_MODE) {
		/* Waveform Generation Mode For CTC */
		TCCR2_REG.Bits.WGM20_Bit = 0;
		TCCR2_REG.Bits.WGM21_Bit = 0;

		/* Enable Timer2 OverFlow interrupt */
		TIMSK2_REG.Bits.TOIE2_Bit = 1;

	} else if (Config_Ptr->timer_mode == COMPARE_MODE) {

		/* Waveform Generation Mode For CTC */

		TCCR2_REG.Bits.WGM20_Bit = 0;
		TCCR2_REG.Bits.WGM21_Bit = 1;

		/* Set compare match value */

		OCR2_REG.Byte = Config_Ptr->timer_compare_MatchValue;

		/* Enable Timer2 compare interrupt */

		TIMSK2_REG.Bits.OCIE2_Bit = 1;

	}
}

static void Timer2_deInit(void) {
	/* Reset TCCR2 register to its default value */
	TCCR2_REG.Byte = 0;

	/* Clear the Timer2 counter register */
	TCNT2_REG.Byte = 0;

	/* Clear the Output Compare Register */
	OCR2_REG.Byte = 0;

	/* Disable Timer2 overflow interrupt */
	TIMSK2_REG.Bits.TOIE2_Bit = 0;

	/* Disable Timer2 compare match interrupt */
	TIMSK2_REG.Bits.OCIE2_Bit = 0;

	g_callBackPtr[2] = NULL_PTR;
}
