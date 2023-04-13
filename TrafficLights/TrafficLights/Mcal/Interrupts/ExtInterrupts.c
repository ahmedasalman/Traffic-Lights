/*
 * ExtInterrupts.c
 *
 *  Author: Ahmed
 */
/************************************************************************/
/* Includes					                                            */
/************************************************************************/
#include "ExtInterrupts.h"
#include "../../Utilities/BitOperations.h"

/************************************************************************/
/* Local Variable Definitions                                           */
/************************************************************************/
static void (*ExtInterrupt0CallBackPtr)()= NULL;
static void (*ExtInterrupt1CallBackPtr)()= NULL;
static void (*ExtInterrupt2CallBackPtr)()= NULL;

/************************************************************************/
/* Functions Definitions                                                */
/************************************************************************/
void Interrupts_EnableGlobalInterrupts(void)
{
	SET_BIT(REG_SREG, 7u);
}
void Interrupts_DisableGlobalInterrupts(void)
{
	CLEAR_BIT(REG_SREG, 7u);
}
void Interrupts_EnableExtInterrupt(uint8 ExtInterruptNo)
{
	switch (ExtInterruptNo)
	{
		case INT0:
		SET_BIT(REG_GICR,6);
		break;
		case INT1:
		SET_BIT(REG_GICR,7);
		break;
		case INT2:
		SET_BIT(REG_GICR,5);
		break;
	}
}
void Interrupts_DisableExtInterrupt(uint8 ExtInterruptNo)
{
	switch (ExtInterruptNo)
	{
		case INT0:
		CLEAR_BIT(REG_GICR,6);
		break;
		case INT1:
		CLEAR_BIT(REG_GICR,7);
		break;
		case INT2:
		CLEAR_BIT(REG_GICR,5);
		break;
	}
}
void Interrupts_ConfigExtInterrupt(uint8 ExtInterruptNo, uint8 InterruptType)
{
	switch (ExtInterruptNo)
	{
		case INT0:
		if(InterruptType == RISING_EDGE)
		{
			SET_BIT(REG_MCUCR, 0);
			SET_BIT(REG_MCUCR, 1);
		}
		else if (InterruptType == FALLING_EDGE)
		{
			CLEAR_BIT(REG_MCUCR, 0);
			SET_BIT(REG_MCUCR, 1);
		}
		else if (InterruptType == CHANGE)
		{
			SET_BIT(REG_MCUCR, 0);
			CLEAR_BIT(REG_MCUCR, 1);
		}
		else if (InterruptType == LOW_LEVEL)
		{
			CLEAR_BIT(REG_MCUCR, 0);
			CLEAR_BIT(REG_MCUCR, 1);
		}
		break;
		case INT1:
		if(InterruptType == RISING_EDGE)
		{
			SET_BIT(REG_MCUCR, 2);
			SET_BIT(REG_MCUCR, 3);
		}
		else if (InterruptType == FALLING_EDGE)
		{
			CLEAR_BIT(REG_MCUCR, 2);
			SET_BIT(REG_MCUCR, 3);
		}
		else if (InterruptType == CHANGE)
		{
			SET_BIT(REG_MCUCR, 2);
			CLEAR_BIT(REG_MCUCR, 3);
		}
		else if (InterruptType == LOW_LEVEL)
		{
			CLEAR_BIT(REG_MCUCR, 2);
			CLEAR_BIT(REG_MCUCR, 3);
		}
		break;
		case INT2:
		if(InterruptType == RISING_EDGE)
		{
			SET_BIT(REG_MCUCSR, 6);
		}
		else if (InterruptType == FALLING_EDGE)
		{
			CLEAR_BIT(REG_MCUCSR, 6);
		}
		break;
	}
}
void Interrupts_RegisterCallbackExtInt0(void (*Callback)(void))
{
	if(Callback != NULL)
	{
		ExtInterrupt0CallBackPtr = Callback;
	}
}
void Interrupts_RegisterCallbackExtInt1(void (*Callback)(void))
{
	if(Callback != NULL)
	{
		ExtInterrupt1CallBackPtr = Callback;
	}	
}
void Interrupts_RegisterCallbackExtInt2(void (*Callback)(void))
{
	if(Callback != NULL)
	{
		ExtInterrupt2CallBackPtr = Callback;
	}
}
ISR(EXT_INT_0)
{
	if(ExtInterrupt0CallBackPtr != NULL)
	{
		(*ExtInterrupt0CallBackPtr)();
	}
}
ISR(EXT_INT_1)
{
	if(ExtInterrupt0CallBackPtr != NULL)
	{
		(*ExtInterrupt1CallBackPtr)();
	}
}
ISR(EXT_INT_2)
{
	if(ExtInterrupt0CallBackPtr != NULL)
	{
		(*ExtInterrupt2CallBackPtr)();
	}
}