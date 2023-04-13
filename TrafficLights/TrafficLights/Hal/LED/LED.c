/*
 * LED.c
 *
 *  Author: Ahmed
 */ 
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "LED.h"
#include "../../Utilities/BitOperations.h"
#include "../../Mcal/DIO/DIO.h"

/************************************************************************/
/* Global Functions Definitions                                         */
/************************************************************************/
void LED_InitLEDs(void)
{
	DIO_InitPin(PORTA, 0, OUTPUT);
	DIO_InitPin(PORTA, 1, OUTPUT);
	DIO_InitPin(PORTA, 2, OUTPUT);
	DIO_InitPin(PORTB, 0, OUTPUT);
	DIO_InitPin(PORTB, 1, OUTPUT);
	DIO_InitPin(PORTB, 2, OUTPUT);
}
void LED_TurnOnLED(uint8 LEDName)
{
	switch(LEDName)
	{
		case PORTA0:
			DIO_WritePin(PORTA, 0, HIGH);
			break;
		case PORTA1:
			DIO_WritePin(PORTA, 1, HIGH);
			break;
		case PORTA2:
			DIO_WritePin(PORTA, 2, HIGH);
			break;
		case PORTB0:
			DIO_WritePin(PORTB, 0, HIGH);
			break;
		case PORTB1:
			DIO_WritePin(PORTB, 1, HIGH);
			break;
		case PORTB2:
			DIO_WritePin(PORTB, 2, HIGH);
			break;
	}	
}
void LED_TurnOffLED(uint8 LEDName)
{
	switch (LEDName)
	{
		case PORTA0:
			DIO_WritePin(PORTA, 0, LOW);
			break;
		case PORTA1:
			DIO_WritePin(PORTA, 1, LOW);
			break;
		case PORTA2:
			DIO_WritePin(PORTA, 2, LOW);
			break;
		case PORTB0:
			DIO_WritePin(PORTB, 0, LOW);
			break;
		case PORTB1:
			DIO_WritePin(PORTB, 1, LOW);
			break;
		case PORTB2:
			DIO_WritePin(PORTB, 2, LOW);
			break;
	}
}
void LED_ToggleLED(uint8 LEDName)
{
	switch (LEDName)
	{
		case PORTA0:
			DIO_TogglePin(PORTA, 0);
			break;
		case PORTA1:
			DIO_TogglePin(PORTA, 1);
			break;
		case PORTA2:
			DIO_TogglePin(PORTA, 2);
			break;
		case PORTB0:
			DIO_TogglePin(PORTB, 0);
			break;
		case PORTB1:
			DIO_TogglePin(PORTB, 1);
			break;
		case PORTB2:
			DIO_TogglePin(PORTB, 2);
			break;
	}
}