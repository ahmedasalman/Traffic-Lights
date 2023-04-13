/*
 * Timers.h
 *
 *  Author: Ahmed
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "../../Utilities/Types.h"
#include "../Common/Registers.h"

/************************************************************************/
/* Macros Definitions		                                            */
/************************************************************************/
#define NORMAL			0U
#define PHASECORRECTPWM 1U
#define CTC				2U
#define FASTPWM			3U

#define NO_PRESCALE		0U
#define CLOCK_8			1U
#define CLOCK_32		2U
#define CLOCK_64		3U
#define CLOCK_128		4U
#define CLOCK_256		5U
#define CLOCK_1024		6U

#define NO_OVERFLOW      0U
#define TIMER_OVERFLOW   1U

/************************************************************************/
/* Functions Decelerations		                                        */
/************************************************************************/
extern void  Timer_ConfigTimer0(uint8 OperatingMode);
extern void  Timer_SetValueTimer0(uint8 InitialValue);
extern void  Timer_StartTimer0(uint8 PreScale);
extern void  Timer_StopTimer0(void);
extern void  Timer_ResetOverFlowFlagTimer0(void);
extern uint8 Timer_GetStateTimer0(void);
extern uint8 Timer_GetValueTimer0(void);
extern void  Timer_BusyDelaymsTimer0(float32 DelayTime);
extern void Timer_EnableTimer0OV(void);
extern void Timer_DisableTimer0OV(void);
extern void Timer_RegisterCallbackTimer0OV(void (*Callback)(void));
extern void Timer_StartCountingTimer0(void);
extern void Timer_StopCountingTimer0(void);
extern float32 Timer_GetCounterTimeTimer0(void);


extern void  Timer_ConfigTimer2(uint8 OperatingMode);
extern void  Timer_SetValueTimer2(uint8 InitialValue);
extern void  Timer_StartTimer2(uint8 PreScale);
extern void  Timer_StopTimer2(void);
extern void  Timer_ResetOverFlowFlagTimer2(void);
extern uint8 Timer_GetStateTimer2(void);
extern uint8 Timer_GetValueTimer2(void);
extern void  Timer_BusyDelaymsTimer2(float32 DelayTime);
extern void Timer_EnableTimer2OV(void);
extern void Timer_DisableTimer2OV(void);
extern void Timer_RegisterCallbackTimer2OV(void (*Callback)(void));
extern void Timer_StartCountingTimer2(void);
extern void Timer_StopCountingTimer2(void);
extern float32 Timer_GetCounterTimeTimer2(void);

#endif /* TIMERS_H_ */