/*
 * Timer.h
 *
 *  Created on: Oct 27, 2024
 *      Author: Youssef Khaled
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Data Types                                  *
 *******************************************************************************/
typedef enum {
    TIMER0,
    TIMER1,
    TIMER2
} Timer_ID_Type;

typedef enum {
    NO_CLOCK,
    PRESCALER_1,
    PRESCALER_8,
    PRESCALER_64,
    PRESCALER_256,
    PRESCALER_1024
} Timer_ClockType;

typedef enum {
    NORMAL_MODE,
    COMPARE_MODE
} Timer_ModeType;

typedef struct {
    uint16 timer_InitialValue;
    uint16 timer_compare_MatchValue; /* Used in compare mode only */
    Timer_ID_Type timer_ID;
    Timer_ClockType timer_clock;
    Timer_ModeType timer_mode;
} Timer_ConfigType;

/*******************************************************************************
 *                                Function Prototypes                         *
 *******************************************************************************/
void Timer_init(const Timer_ConfigType * Config_Ptr);
void Timer_deInit(Timer_ID_Type timer_type);
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID);

#endif /* TIMER_H_ */
