/*
	@file:led.h
	@author: wave top
	@date:2018/11/06
	@brief:the file of control led
	**************************************************
	@attention
	The module(led) control the led to light on/off.
*/
#ifndef _LED_H
#define _LED_H

#define LED_GPIO_PORT  GPIOB
#define LED_GPIO_PINS  GPIO_Pin_3
#define POWER_GPIO_PINS  GPIO_Pin_4
#define RESET_GPIO_PINS  GPIO_Pin_5

#define LED_TEST

#define LOW_LEVEL	0
#define	HIGH_LEVEL	1

/* Functional functions */
void LED_Module_Init(unsigned char level);
void LED_ToggleBits();
void SYSTEM_Ports_Init();
void SYSTEM_Reset_SetLevel(unsigned char level);
void SYSTEM_Power_SetLevel(unsigned char level);
void Delay(unsigned int nCount);

#endif