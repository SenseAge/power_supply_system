/*
	@file:button_detection.c
	@author: wave top
	@date:2018/11/07
	@brief:the file of detect button
	**************************************************
	@attention
	The module(led) control to detect the operation(press/release) of button.
*/

#include "button_detection.h"
#include "low_power/low_power.h"
#include "led/led.h"
#include "timer/timer.h"
#include "stm8l15x.h"

BUTTON_TYPE button_powertype = BUTTON_DEFAULT;
BUTTON_TYPE button_resettype = BUTTON_DEFAULT;

/**
  * @brief : The Button module's initialization function(rising/falling check operation)
  * @par Parameters
  * None
  * @retval 
  * None
*/
void BUTTON_Detection_Module()
{
#if 0
	/* GPIOA_2 -- External interrupt function */
	GPIO_Init(BUTTON_GPIO_PORT, KEY1_GPIO_PINS, GPIO_Mode_In_FL_IT);
	/* GPIOA_2 -- falling edge and low level capture feature */
	EXTI_SetPinSensitivity(EXTI_Pin_2, EXTI_Trigger_Rising);
#endif

	/* GPIOA_4 -- External interrupt function */
	GPIO_Init(BUTTON_GPIO_PORT, BUTTON1_GPIO_PINS, GPIO_Mode_In_FL_IT);
	/* GPIOA_4 -- falling edge and low level capture feature */
	EXTI_SetPinSensitivity(EXTI_Pin_4, EXTI_Trigger_Rising);

#if 0
	/* GPIOA_5 -- External interrupt function */
	GPIO_Init(BUTTON_GPIO_PORT, BUTTON2_GPIO_PINS, GPIO_Mode_In_FL_IT);
	/* GPIOA_5 -- falling edge and rising sdge capture feature */
	EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Rising_Falling);

	/* GPIOA_6 -- External interrupt function */
	GPIO_Init(BUTTON_GPIO_PORT, BUTTON3_GPIO_PINS, GPIO_Mode_In_FL_IT);
	/* GPIOA_6 -- falling edge and rising sdge capture feature */
	EXTI_SetPinSensitivity(EXTI_Pin_6, EXTI_Trigger_Rising);

#endif

	enableInterrupts();
}

/**
  * @brief : Handle the button event
  * @par Parameters
  * None
  * @retval 
  * None
*/
void BUTTON_Handle_Button_Event()
{
	switch(BUTTON_PowerButton_Type()) {
		case BUTTON_ORDER:
			if(SOC_POWER_OFF == LPOWER_GetSocPower_Status()) {
				SYSTEM_Power_SetLevel(HIGH_LEVEL);	/* valid power */
			} else {
				LOG_CommData_Transmition("%order%");
				BUTTON_SetPowerButton_Type(BUTTON_DEFAULT);
				/* enter the low power status */
				LPOWER_MCU_lowPower_Mode();
			}
		break;
		case BUTTON_CANCEL:
			if(SOC_POWER_OFF == LPOWER_GetSocPower_Status()) {
				SYSTEM_Power_SetLevel(HIGH_LEVEL);	/* valid power */
			} else {
				LOG_CommData_Transmition("%cancel%");
				BUTTON_SetPowerButton_Type(BUTTON_DEFAULT);
				/* enter the low power status */
				LPOWER_MCU_lowPower_Mode();
			}
		break;
		default:
			/* do nothing */
		break;
	}

	switch(button_resettype) {
		case BUTTON_WAKED:
			SYSTEM_Reset_SetLevel(LOW_LEVEL);	/* valid reset */
			TIMER_Start();	/* 10ms counts */
		break;
		default:
			/* do nothing */
		break;
	}
}

/**
  * @brief : The type of functional button
  * @par Parameters: type -- button type
  * None
  * @retval 
  * None
*/
void BUTTON_SetPowerButton_Type(BUTTON_TYPE type)
{
	button_powertype = type;
}

BUTTON_TYPE BUTTON_PowerButton_Type()
{
	return button_powertype;
}

/**
  * @brief : The type of reset button
  * @par Parameters: type -- button type(reset/default)
  * None
  * @retval 
  * None
*/
void BUTTON_SetResetButton_Type(BUTTON_TYPE type)
{
	button_resettype = type;
}

BUTTON_TYPE BUTTON_ResetButton_Type()
{
	return button_resettype;
}
