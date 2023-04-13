/*
 * App.h
 *
 *  Author: Ahmed
 */ 


#ifndef APP_H_
#define APP_H_
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "../Utilities/Types.h"

/************************************************************************/
/* Type Definitions									                    */
/************************************************************************/
enum Enum_TrafficState 
{
	NORMAL_MODE,
	PEDESTRIAN_MODE,
};
enum Enum_TrafficLight
{
	RED_LIGHT,
	YELLOWTOGREEN_LIGHT,
	YELLOWTORED_LIGHT,
	GREEN_LIGHT,
};

/************************************************************************/
/* Functions Decelerations		                                        */
/************************************************************************/
extern void AppInit();
extern void AppRun();

#endif /* APP_H_ */