/*
 * LED.h
 *
 *  Author: Ahmed
 */ 


#ifndef LED_H_
#define LED_H_
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "../../Utilities/Types.h"

/************************************************************************/
/* Macros Definitions		                                            */
/************************************************************************/
#define PORTB0 0
#define PORTB1 1
#define PORTB2 2

#define PORTA0 3
#define PORTA1 4
#define PORTA2 5

#define PEDESTRIAN_GREEN_LED  PORTB0
#define PEDESTRIAN_YELLOW_LED PORTB1
#define PEDESTRIAN_RED_LED    PORTB2

#define CAR_GREEN_LED  PORTA0
#define CAR_YELLOW_LED PORTA1
#define CAR_RED_LED    PORTA2

/************************************************************************/
/* Functions Decelerations		                                        */
/************************************************************************/
extern void LED_InitLEDs(void);
extern void LED_TurnOnLED(uint8 LEDName);
extern void LED_TurnOffLED(uint8 LEDName);
extern void LED_ToggleLED(uint8 LEDName);

#endif /* LED_H_ */