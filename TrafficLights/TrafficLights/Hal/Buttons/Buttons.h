/*
 * Buttons.h
 *
 *  Author: Ahmed
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "../../Utilities/Types.h"

/************************************************************************/
/* Macros Definitions		                                            */
/************************************************************************/
#define PORTD2 0

#define PEDESTRIAN_BUTTON PORTD2

/************************************************************************/
/* Functions Decelerations		                                        */
/************************************************************************/
void Buttons_Init(void);
void Buttons_Start(void (*CallBack)(void));
uint8 Buttons_GetButtonState(void);

#endif /* BUTTONS_H_ */