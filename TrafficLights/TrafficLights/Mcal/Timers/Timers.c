/*
 * Timers.c
 *
 *  Author: Ahmed
 */
 /************************************************************************/
 /* Includes		   		                                            */
 /************************************************************************/
#include "Timers.h"
#include "../../Utilities/BitOperations.h"
#include "../Interrupts/Interrupts.h"

/************************************************************************/
/* Macros Definitions		                                            */
/************************************************************************/
#define DELAY_PRESCALE    CLOCK_64
#define COUNTING_PRESCALE CLOCK_64
#define F_CPU (1000000U)

/************************************************************************/
/* Local Variable Definitions                                           */
/************************************************************************/
static uint32 Timer0AccumulatedCounter = 0U;
static uint32 Timer2AccumulatedCounter = 0U;

static void (*Timer0OVFCallBackPtr)()= NULL;
static void (*Timer2OVFCallBackPtr)()= NULL;

/************************************************************************/
/* Local Functions Definitions                                          */
/************************************************************************/
static void Timer_IncCounterTimer0(void)
{
	Timer0AccumulatedCounter += 256;
}
static void Timer_IncCounterTimer2(void)
{
	Timer2AccumulatedCounter += 256;
}
ISR(TIMER0_OVF)
{
	if(Timer0OVFCallBackPtr != NULL)
	{
		(*Timer0OVFCallBackPtr)();
	}
}
ISR(TIMER2_OVF)
{
	if(Timer2OVFCallBackPtr != NULL)
	{
		(*Timer2OVFCallBackPtr)();
	}
}

/************************************************************************/
/* Global Functions Definitions                                         */
/************************************************************************/
void  Timer_ConfigTimer0(uint8 OperatingMode)
{
	switch (OperatingMode)
	{
		case NORMAL:
		REG_TCCR0 = 0u;
		break;
		case FASTPWM:
		SET_BIT(REG_TCCR0,3);
		SET_BIT(REG_TCCR0,6);
		break;
		case PHASECORRECTPWM:
		SET_BIT(REG_TCCR0,6);
		break;
		case CTC:
		SET_BIT(REG_TCCR0,3);
		break;
	}	
}
void  Timer_SetValueTimer0(uint8 InitialValue)
{
	REG_TCNT0 = InitialValue;	
}
void  Timer_StartTimer0(uint8 PreScale)
{
	switch (PreScale)
	{
		case NO_PRESCALE:
		REG_TCCR0 = (REG_TCCR0 & ~(7 << 0)) | (0b001 << 0);
		break;
		case CLOCK_8:
		REG_TCCR0 = (REG_TCCR0 & ~(7 << 0)) | (0b010 << 0);
		break;
		case CLOCK_64:
		REG_TCCR0 = (REG_TCCR0 & ~(7 << 0)) | (0b011 << 0);
		break;
		case CLOCK_256:
		REG_TCCR0 = (REG_TCCR0 & ~(7 << 0)) | (0b100 << 0);
		break;
		case CLOCK_1024:
		REG_TCCR0 = (REG_TCCR0 & ~(7 << 0)) | (0b101 << 0);
		break;
	}
}
void  Timer_StopTimer0(void)
{
	REG_TCCR0 &= ~(7 << 0);
}
void  Timer_ResetOverFlowFlagTimer0(void)
{
	SET_BIT(REG_TIFR, 0);
}
uint8 Timer_GetStateTimer0(void)
{
	return CHECK_BIT(REG_TIFR,0);
}
uint8 Timer_GetValueTimer0(void)
{
	return REG_TCNT0;
}
void Timer_EnableTimer0OV(void)
{
	SET_BIT(REG_TIMSK,0);
}
void Timer_DisableTimer0OV(void)
{
	CLEAR_BIT(REG_TIMSK,0);
}
void Timer_RegisterCallbackTimer0OV(void (*Callback)(void))
{
	if(Callback != NULL)
	{
		Timer0OVFCallBackPtr = Callback;
	}
}
void  Timer_BusyDelaymsTimer0(float32 DelayTime)
{
	Timer_StopTimer0();
	Timer_ResetOverFlowFlagTimer0();
	volatile float32 TickTime = ((1.0F/(F_CPU)) * 64.0F) * 1000.0;
	uint32 NoOfTicks = (uint32)((float32)DelayTime / (float32)TickTime);
	uint8 InitialValue = 256 - NoOfTicks % 256;
	uint32 NoOfOverFlow = NoOfTicks / 256 +1;
	uint32 OverFlowCounter = 0U;
	Timer_SetValueTimer0(InitialValue);
	Timer_StartTimer0(DELAY_PRESCALE);
	while(OverFlowCounter < NoOfOverFlow)
	{
		if(Timer_GetStateTimer0() != NO_OVERFLOW)
		{
			OverFlowCounter++;
			Timer_ResetOverFlowFlagTimer0();
		}
	}
	Timer_StopTimer0();
}
void Timer_StartCountingTimer0(void)
{
	Timer0AccumulatedCounter = 0;
	Timer_StopTimer0();
	Timer_SetValueTimer0(0.0F);
	if(Timer_GetStateTimer0() != NO_OVERFLOW)
	{
		Timer_ResetOverFlowFlagTimer0();
	}
	Timer_RegisterCallbackTimer0OV(Timer_IncCounterTimer0);
	Timer_EnableTimer0OV();
	Timer_StartTimer0(COUNTING_PRESCALE);
}
void Timer_StopCountingTimer0(void)
{
	Timer_StopTimer0();
	Timer0AccumulatedCounter += Timer_GetValueTimer0();
	if(Timer_GetStateTimer0() != NO_OVERFLOW)
	{
		Timer_ResetOverFlowFlagTimer0();
	}
	Timer_DisableTimer0OV();
}
float32 Timer_GetCounterTimeTimer0(void)
{
	volatile float32 TickTime = ((1.0F/(F_CPU)) * 64.0F) * 1000.0;
	return ((float32)Timer0AccumulatedCounter * TickTime);
}

void  Timer_ConfigTimer2(uint8 OperatingMode)
{
	switch (OperatingMode)
	{
		case NORMAL:
		REG_TCCR2 = 0u;
		break;
		case FASTPWM:
		SET_BIT(REG_TCCR2,3);
		SET_BIT(REG_TCCR2,6);
		break;
		case PHASECORRECTPWM:
		SET_BIT(REG_TCCR2,6);
		break;
		case CTC:
		SET_BIT(REG_TCCR2,3);
		break;
	}
}
void  Timer_SetValueTimer2(uint8 InitialValue)
{
	REG_TCNT2 = InitialValue;
}
void  Timer_StartTimer2(uint8 PreScale)
{
	switch (PreScale)
	{
		case NO_PRESCALE:
		REG_TCCR2 = (REG_TCCR2 & ~(7 << 0)) | (0b001 << 0);
		break;
		case CLOCK_8:
		REG_TCCR2 = (REG_TCCR2 & ~(7 << 0)) | (0b010 << 0);
		break;
		case CLOCK_32:
		REG_TCCR2 = (REG_TCCR2 & ~(7 << 0)) | (0b011 << 0);
		break;
		case CLOCK_64:
		REG_TCCR2 = (REG_TCCR2 & ~(7 << 0)) | (0b100 << 0);
		break;
		case CLOCK_128:
		REG_TCCR2 = (REG_TCCR2 & ~(7 << 0)) | (0b101 << 0);
		break;
		case CLOCK_256:
		REG_TCCR2 = (REG_TCCR2 & ~(7 << 0)) | (0b110 << 0);
		break;
		case CLOCK_1024:
		REG_TCCR2 = (REG_TCCR2 & ~(7 << 0)) | (0b111 << 0);
		break;
	}
}
void  Timer_StopTimer2(void)
{
	REG_TCCR2 &= ~(7 << 0);
}
void  Timer_ResetOverFlowFlagTimer2(void)
{
	SET_BIT(REG_TIFR, 6);
}
uint8 Timer_GetStateTimer2(void)
{
	return CHECK_BIT(REG_TIFR,6);
}
uint8 Timer_GetValueTimer2(void)
{
	return REG_TCNT2;
}
void Timer_EnableTimer2OV(void)
{
	SET_BIT(REG_TIMSK,6);
}
void Timer_DisableTimer2OV(void)
{
	CLEAR_BIT(REG_TIMSK,6);
}
void Timer_RegisterCallbackTimer2OV(void (*Callback)(void))
{
	if(Callback != NULL)
	{
		Timer2OVFCallBackPtr = Callback;
	}
}
void  Timer_BusyDelaymsTimer2(float32 DelayTime)
{
	Timer_StopTimer2();
	Timer_ResetOverFlowFlagTimer2();
	volatile float32 TickTime = ((1.0F/(F_CPU)) * 64.0F) * 1000.0;
	uint32 NoOfTicks = (uint32)((float32)DelayTime / (float32)TickTime);
	uint8 InitialValue = 256 - NoOfTicks % 256;
	uint32 NoOfOverFlow = NoOfTicks / 256 +1;
	uint32 OverFlowCounter = 0U;
	Timer_SetValueTimer2(InitialValue);
	Timer_StartTimer2(DELAY_PRESCALE);
	while(OverFlowCounter < NoOfOverFlow)
	{
		if(Timer_GetStateTimer2() != NO_OVERFLOW)
		{
			OverFlowCounter++;
			Timer_ResetOverFlowFlagTimer2();
		}
	}
	Timer_StopTimer2();
}
void Timer_StartCountingTimer2(void)
{
	Timer2AccumulatedCounter = 0;
	Timer_StopTimer2();
	Timer_SetValueTimer2(0.0F);
	if(Timer_GetStateTimer2() != NO_OVERFLOW)
	{
		Timer_ResetOverFlowFlagTimer2();
	}
	Timer_RegisterCallbackTimer2OV(Timer_IncCounterTimer2);
	Timer_EnableTimer2OV();
	Timer_StartTimer2(COUNTING_PRESCALE);
}
void Timer_StopCountingTimer2(void)
{
	Timer_StopTimer2();
	Timer2AccumulatedCounter += Timer_GetValueTimer2();
	if(Timer_GetStateTimer2() != NO_OVERFLOW)
	{
		Timer_ResetOverFlowFlagTimer2();
	}
	Timer_DisableTimer2OV();
}
float32 Timer_GetCounterTimeTimer2(void)
{
	volatile float32 TickTime = ((1.0F/(F_CPU)) * 64.0F) * 1000.0;
	return ((float32)Timer2AccumulatedCounter * TickTime);
}
