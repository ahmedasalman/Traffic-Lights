/*
 * Interrupts.h
 *
 *  Author: Ahmed
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/************************************************************************/
/* Macros Definitions		                                            */
/************************************************************************/
#define EXT_INT_0  __vector_1
#define EXT_INT_1  __vector_2
#define EXT_INT_2  __vector_3
#define TIMER2_OVF __vector_5
#define TIMER1_OVF __vector_9
#define TIMER0_OVF __vector_11

#define ISR(INT_VECT) void INT_VECT(void) __attribute__ ((signal,used)); \
void INT_VECT(void)
#endif /* INTERRUPTS_H_ */