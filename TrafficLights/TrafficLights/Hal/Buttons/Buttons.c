/*
 * Buttons.c
 *
 *  Author: Ahmed
 */ 
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "Buttons.h"
#include "../../Utilities/BitOperations.h"
#include "../../Mcal/DIO/DIO.h"
#include "../../Mcal/Interrupts/ExtInterrupts.h"

/************************************************************************/
/* Functions Definitions		                                        */
/************************************************************************/
void Buttons_Init()
{
	DIO_InitPin(PORTD, 2, INPUT);
	Interrupts_ConfigExtInterrupt(INT0, CHANGE);
}
void Buttons_Start(void (*CallBack)(void))
{
	Interrupts_RegisterCallbackExtInt0(CallBack);
	Interrupts_EnableExtInterrupt(INT0);
}
uint8 Buttons_GetButtonState(void)
{
	return DIO_ReadPin(PORTD, 2);
}