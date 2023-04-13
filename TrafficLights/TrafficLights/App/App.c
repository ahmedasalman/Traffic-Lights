/*
 * App.c
 *
 *  Author: Ahmed
 */ 
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "App.h"
#include "../Utilities/BitOperations.h"
#include "../Mcal/DIO/DIO.h"
#include "../Mcal/Timers/Timers.h"
#include "../Mcal/Interrupts/ExtInterrupts.h"
#include "../Hal/LED/LED.h"
#include "../Hal/Buttons/Buttons.h"

/************************************************************************/
/* Macros Definitions		                                            */
/************************************************************************/
#define CHANGE_TIME	    6000.0F
#define LONG_PRESS_THRS 2000.0F
#define BLINK_ON_TIME   800.0F
#define BLINK_OFF_TIME  200.0F

/************************************************************************/
/* Local Variable Definitions                                           */
/************************************************************************/
static enum Enum_TrafficState TrafficState	  = NORMAL_MODE;
static enum Enum_TrafficState PrevTrafficState	  = NORMAL_MODE;
static enum Enum_TrafficLight CarsLight	      = GREEN_LIGHT;

static uint8 YellowState = LOW;
static float32 LightsTimer = 0.0F;
static float32 BlinkTimer = 0.0F;

/************************************************************************/
/* Local Functions Definitions                                           */
/************************************************************************/
void ButtonResponse(void)
{
	volatile float32 PressTime = 0.0F;
	if(Buttons_GetButtonState() != LOW)
	{
		Timer_StartCountingTimer2();
	}
	else
	{
		Timer_StopCountingTimer2();
		PressTime = Timer_GetCounterTimeTimer2();
		if(PressTime <= LONG_PRESS_THRS)
		{
			TrafficState = PEDESTRIAN_MODE;
		}
	}
}
void ChangeToGreen(void)
{
	LED_TurnOffLED(CAR_RED_LED);
	LED_TurnOffLED(CAR_YELLOW_LED);
	LED_TurnOnLED(CAR_GREEN_LED);
	LED_TurnOnLED(PEDESTRIAN_RED_LED);
	LED_TurnOffLED(PEDESTRIAN_YELLOW_LED);
	LED_TurnOffLED(PEDESTRIAN_GREEN_LED);
	YellowState = LOW;
}
void ChangeToYellow(void)
{
	LED_TurnOffLED(CAR_RED_LED);
	LED_TurnOnLED(CAR_YELLOW_LED);
	LED_TurnOffLED(CAR_GREEN_LED);
	LED_TurnOffLED(PEDESTRIAN_RED_LED);
	LED_TurnOnLED(PEDESTRIAN_YELLOW_LED);
	LED_TurnOffLED(PEDESTRIAN_GREEN_LED);
	YellowState = HIGH;
}
void ChangeToRed(void)
{
	LED_TurnOnLED(CAR_RED_LED);
	LED_TurnOffLED(CAR_YELLOW_LED);
	LED_TurnOffLED(CAR_GREEN_LED);
	LED_TurnOffLED(PEDESTRIAN_RED_LED);
	LED_TurnOffLED(PEDESTRIAN_YELLOW_LED);
	LED_TurnOnLED(PEDESTRIAN_GREEN_LED);
	YellowState = LOW;
}
void ToggleYellowLight(void)
{
	LED_ToggleLED(CAR_YELLOW_LED);
	LED_ToggleLED(PEDESTRIAN_YELLOW_LED);
	YellowState = !YellowState;
}

/************************************************************************/
/* Global Functions Definitions                                           */
/************************************************************************/
void AppInit()
{
	//Initialize IO
	LED_InitLEDs();
	Buttons_Init();
	//Initialize Timers
	Timer_ConfigTimer0(NORMAL);
	Timer_ConfigTimer2(NORMAL);
	//Enable Global interrupts
	Interrupts_EnableGlobalInterrupts();
	
	//Start The traffic lights
	Buttons_Start(&ButtonResponse);
	
	ChangeToGreen();
	
}
void AppRun()
{
	switch(TrafficState)
	{
		case NORMAL_MODE:
			switch (CarsLight)
			{
				case GREEN_LIGHT:
					if (LightsTimer >= CHANGE_TIME)
					{
						LightsTimer = 0.0F;
						CarsLight = YELLOWTORED_LIGHT;
						ChangeToYellow();
					}
					else
					{
						Timer_BusyDelaymsTimer0(100);
						LightsTimer += 100.0;
					}
					break;
				case YELLOWTORED_LIGHT:
					if (LightsTimer >= CHANGE_TIME)
					{
						LightsTimer = 0.0F;
						BlinkTimer = 0.0F;
						CarsLight = RED_LIGHT;
						ChangeToRed();
					}
					else if (((BlinkTimer >= BLINK_OFF_TIME) && (YellowState == LOW)) || ((BlinkTimer >= BLINK_ON_TIME) && (YellowState == HIGH)))
					{
						BlinkTimer = 0.0F;
						ToggleYellowLight();
					}
					else
					{
						Timer_BusyDelaymsTimer0(100);
						LightsTimer += 100.0;
						BlinkTimer += 100.0F;
					}
					break;
				case RED_LIGHT:
					if (LightsTimer >= CHANGE_TIME)
					{
						LightsTimer = 0.0F;
						CarsLight = YELLOWTOGREEN_LIGHT;
						ChangeToYellow();
					}
					else
					{
						Timer_BusyDelaymsTimer0(100);
						LightsTimer += 100.0;
					}
					break;
				case YELLOWTOGREEN_LIGHT:
					if (LightsTimer >= CHANGE_TIME)
					{
						LightsTimer = 0.0F;
						BlinkTimer = 0.0F;
						CarsLight = GREEN_LIGHT;
						ChangeToGreen();
					}
					else if (((BlinkTimer >= BLINK_OFF_TIME) && (YellowState == LOW)) || ((BlinkTimer >= BLINK_ON_TIME) && (YellowState == HIGH)))
					{
						BlinkTimer = 0.0F;
						ToggleYellowLight();
					}
					else
					{
						Timer_BusyDelaymsTimer0(100);
						LightsTimer += 100.0;
						BlinkTimer += 100.0F;
					}
					break;
			}
			PrevTrafficState = NORMAL_MODE;
			break;
		case PEDESTRIAN_MODE:
			if(PrevTrafficState != PEDESTRIAN_MODE)
			{
				switch (CarsLight)
				{
					case GREEN_LIGHT:
						LightsTimer = 0.0F;
						CarsLight = YELLOWTORED_LIGHT;
						ChangeToYellow();
						break;
					case YELLOWTORED_LIGHT:
						break;
					case YELLOWTOGREEN_LIGHT:
						CarsLight = YELLOWTORED_LIGHT;
						break;
					case RED_LIGHT:
						break;
				}
			}
			switch (CarsLight)
			{
				case YELLOWTORED_LIGHT:
					if (LightsTimer >= CHANGE_TIME)
					{
						LightsTimer = 0.0F;
						BlinkTimer = 0.0F;
						CarsLight = RED_LIGHT;
						ChangeToRed();
					}
					else if (((BlinkTimer >= BLINK_OFF_TIME) && (YellowState == LOW)) || ((BlinkTimer >= BLINK_ON_TIME) && (YellowState == HIGH)))
					{
						BlinkTimer = 0.0F;
						ToggleYellowLight();
					}
					else
					{
						Timer_BusyDelaymsTimer0(100);
						LightsTimer += 100.0;
						BlinkTimer += 100.0F;
					}
					break;
				case RED_LIGHT:
					if (LightsTimer >= CHANGE_TIME)
					{
						LightsTimer = 0.0F;
						CarsLight = YELLOWTOGREEN_LIGHT;
						ChangeToYellow();
						TrafficState = NORMAL_MODE;
					}
					else
					{
						Timer_BusyDelaymsTimer0(100);
						LightsTimer += 100.0;
					}
					break;
				default:
					break;
			}
			PrevTrafficState = PEDESTRIAN_MODE;
			break;
	}
}