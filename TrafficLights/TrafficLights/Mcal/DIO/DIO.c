/*
 * DIO.c
 *
 *  Author: Ahmed
 */ 
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "DIO.h"
#include "../../Utilities/BitOperations.h"

/************************************************************************/
/* Functions Definitions                                                */
/************************************************************************/
void  DIO_InitPin(uint8 PortName, uint8 PinNumber, uint8 Direction)
{
	switch (PortName)
	{
	case PORTA:
		 if (Direction == OUTPUT)
		 {
			SET_BIT(REG_DDRA, PinNumber);
		 }
		 else if (Direction == INPUT)
		 {
			CLEAR_BIT(REG_DDRA, PinNumber);
		 }
		break;
	case PORTB:
		if (Direction == OUTPUT)
		{
			SET_BIT(REG_DDRB, PinNumber);
		}
		else if (Direction == INPUT)
		{
			CLEAR_BIT(REG_DDRB, PinNumber);
		}
		break;
	case PORTC:
		if (Direction == OUTPUT)
		{
			SET_BIT(REG_DDRC, PinNumber);
		}
		else if (Direction == INPUT)
		{
			CLEAR_BIT(REG_DDRC, PinNumber);
		}
		break;
	case PORTD:
		if (Direction == OUTPUT)
		{
			SET_BIT(REG_DDRD, PinNumber);
		}
		else if (Direction == INPUT)
		{
			CLEAR_BIT(REG_DDRD, PinNumber);
		}
		break;
	}
}
void  DIO_WritePin(uint8 PortName, uint8 PinNumber, uint8 Value)
{
	switch (PortName)
	{
	case PORTA:
		if (Value == HIGH)
		{
			SET_BIT(REG_PORTA, PinNumber);
		}
		else if (Value == LOW)
		{
			CLEAR_BIT(REG_PORTA, PinNumber);
		}
		break;
	case PORTB:
		if (Value == HIGH)
		{
			SET_BIT(REG_PORTB, PinNumber);
		}
		else if (Value == LOW)
		{
			CLEAR_BIT(REG_PORTB, PinNumber);
		}
		break;
	case PORTC:
		if (Value == HIGH)
		{
			SET_BIT(REG_PORTC, PinNumber);
		}
		else if (Value == LOW)
		{
			CLEAR_BIT(REG_PORTC, PinNumber);
		}
		break;
	case PORTD:
		if (Value == HIGH)
		{
			SET_BIT(REG_PORTD, PinNumber);
		}
		else if (Value == LOW)
		{
			CLEAR_BIT(REG_PORTD, PinNumber);
		}
		break;
	}	
}
void  DIO_TogglePin(uint8 PortName, uint8 PinNumber)
{
	switch (PortName)
	{
		case PORTA:
			TOGGLE_BIT(REG_PORTA, PinNumber);
			break;
		case PORTB:
			TOGGLE_BIT(REG_PORTB, PinNumber);
			break;
		case PORTC:
			TOGGLE_BIT(REG_PORTC, PinNumber);
			break;
		case PORTD:
			TOGGLE_BIT(REG_PORTD, PinNumber);
			break;
	}
}
uint8 DIO_ReadPin(uint8 PortName, uint8 PinNumber)
{
	uint8 reading = -1;
	switch (PortName)
	{
	case PORTA:
		reading = CHECK_BIT(REG_PINA, PinNumber);
		break;
	case PORTB:
		reading = CHECK_BIT(REG_PINB, PinNumber);
		break;
	case PORTC:
		reading = CHECK_BIT(REG_PINC, PinNumber);
		break;
	case PORTD:
		reading = CHECK_BIT(REG_PIND, PinNumber);
		break;
	}	
	return reading;
}