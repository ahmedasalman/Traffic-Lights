/*
 * ExtInterrupts.h
 *
 *  Author: Ahmed
 */ 


#ifndef EXTINTERRUPTS_H_
#define EXTINTERRUPTS_H_
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "interrupts.h"
#include "../../Utilities/Types.h"
#include "../Common/Registers.h"

/************************************************************************/
/* Macros Definitions		                                            */
/************************************************************************/
#define INT0 0
#define INT1 1
#define INT2 2

#define FALLING_EDGE 0
#define RISING_EDGE  1
#define CHANGE		 2
#define LOW_LEVEL	 3

/************************************************************************/
/* Functions Decelerations		                                        */
/************************************************************************/
extern void Interrupts_EnableGlobalInterrupts(void);
extern void Interrupts_DisableGlobalInterrupts(void);
extern void Interrupts_EnableExtInterrupt(uint8 ExtInterruptNo);
extern void Interrupts_DisableExtInterrupt(uint8 ExtInterruptNo);
extern void Interrupts_ConfigExtInterrupt(uint8 ExtInterruptNo, uint8 InterruptType);
extern void Interrupts_RegisterCallbackExtInt0(void (*Callback)(void));
extern void Interrupts_RegisterCallbackExtInt1(void (*Callback)(void));
extern void Interrupts_RegisterCallbackExtInt2(void (*Callback)(void));


#endif /* EXTINTERRUPTS_H_ */