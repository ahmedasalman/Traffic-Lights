/*
 * Registers.h
 *
 *  Author: Ahmed
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "../../Utilities/Types.h"

/************************************************************************/
/* Macros Definitions		                                            */
/************************************************************************/
#define REG_PORTA (*(volatile uint8*)(0x3BU))
#define REG_DDRA  (*(volatile uint8*)(0x3AU))
#define REG_PINA  (*(volatile uint8*)(0x39U))

#define REG_PORTB (*(volatile uint8*)(0x38U))
#define REG_DDRB  (*(volatile uint8*)(0x37U))
#define REG_PINB  (*(volatile uint8*)(0x36U))

#define REG_PORTC (*(volatile uint8*)(0x35U))
#define REG_DDRC  (*(volatile uint8*)(0x34U))
#define REG_PINC  (*(volatile uint8*)(0x33U))

#define REG_PORTD (*(volatile uint8*)(0x32U))
#define REG_DDRD  (*(volatile uint8*)(0x31U))
#define REG_PIND  (*(volatile uint8*)(0x30U))


#define REG_TIFR   (*(volatile uint8*)(0x58U))
#define REG_TIMSK  (*(volatile uint8*)(0x59U))
#define REG_SFIOR  (*(volatile uint8*)(0x50U))

#define REG_TCCR0  (*(volatile uint8*)(0x53U))
#define REG_TCNT0  (*(volatile uint8*)(0x52U))
#define REG_OCR0   (*(volatile uint8*)(0x5CU))

#define REG_TCCR2  (*(volatile uint8*)(0x45U))
#define REG_TCNT2  (*(volatile uint8*)(0x44U))
#define REG_OCR2   (*(volatile uint8*)(0x43U))

#define REG_SREG   (*(volatile uint8*)(0x5FU))
#define REG_MCUCR  (*(volatile uint8*)(0x55U))
#define REG_MCUCSR (*(volatile uint8*)(0x54U))
#define REG_GICR   (*(volatile uint8*)(0x5BU))
#define REG_GIFR   (*(volatile uint8*)(0x5AU))


#endif /* REGISTERS_H_ */