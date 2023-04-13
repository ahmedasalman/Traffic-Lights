/*
 * DIO.h
 *
 *  Author: Ahmed
 */ 


#ifndef DIO_H_
#define DIO_H_
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "../../Utilities/Types.h"
#include "../Common/Registers.h"

/************************************************************************/
/* Macros Definitions		                                            */
/************************************************************************/
#define INPUT  0U
#define OUTPUT 1U

#define PORTA 0U
#define PORTB 1U
#define PORTC 2U
#define PORTD 3U

/************************************************************************/
/* Functions Decelerations		                                        */
/************************************************************************/
extern void  DIO_InitPin(uint8 PortName, uint8 PinNumber, uint8 Direction);
extern void  DIO_WritePin(uint8 PortName, uint8 PinNumber, uint8 Value);
extern void  DIO_TogglePin(uint8 PortName, uint8 PinNumber);
extern uint8 DIO_ReadPin(uint8 PortName, uint8 PinNumber);


#endif /* DIO_H_ */