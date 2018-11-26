/*
	@file:button_detection.h
	@author: wave top
	@date:2018/11/07
	@brief:the file of detect button
	**************************************************
	@attention
	The module(led) control to detect the operation(press/release) of button.
*/
#ifndef _BUTTON_DETECTION_H
#define _BUTTON_DETECTION_H

#define BUTTON_GPIO_PORT  GPIOA
#define KEY1_GPIO_PINS  GPIO_Pin_2	/* test button */
#define BUTTON1_GPIO_PINS  GPIO_Pin_4	/* order button */
#define BUTTON2_GPIO_PINS  GPIO_Pin_5	/* cancel button */
#define BUTTON3_GPIO_PINS  GPIO_Pin_6	/* wake button */

typedef enum {
	BUTTON_ORDER = 0,
	BUTTON_CANCEL,
	BUTTON_WAKED,
	BUTTON_DEFAULT
} BUTTON_TYPE;

/* Functional functions */
void BUTTON_Detection_Module();

void BUTTON_Handle_Button_Event();

void BUTTON_SetPowerButton_Type(BUTTON_TYPE type);
void BUTTON_SetResetButton_Type(BUTTON_TYPE type);
BUTTON_TYPE BUTTON_PowerButton_Type();
BUTTON_TYPE BUTTON_ResetButton_Type();

#endif