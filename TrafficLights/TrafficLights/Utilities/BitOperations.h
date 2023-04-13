/*
 * BitOperations.h
 *
 *  Author: Ahmed
 */ 


#ifndef BITOPERATIONS_H_
#define BITOPERATIONS_H_
/************************************************************************/
/* Macros Definitions		                                            */
/************************************************************************/
#define NULL 0
#define SET_BIT(var, bit)    (var |= (1U << bit))
#define CLEAR_BIT(var, bit)  (var &= ~(1U << bit))
#define TOGGLE_BIT(var, bit) (var ^= (1U << bit))
#define CHECK_BIT(var, bit)  ((var & (1UL << bit)) >> bit)

#define TRUE  1U
#define FALSE 0U
#define HIGH  1U
#define LOW   0U
#endif /* BITOPERATIONS_H_ */