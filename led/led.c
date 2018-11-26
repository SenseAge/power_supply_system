/*
	@file:led.c
	@author: wave top
	@date:2018/11/06
	@brief:the file of control led
	**************************************************
	@attention
	The module(led) control the led to light on/off.
*/

#include "led.h"
#include "stm8l15x.h"

/* High level -- GPIO Port
**
** GPIO_Mode_Out_OD_HiZ_Fast: Output open-drain, high-impedance level, 10MHz
** GPIO_Mode_Out_PP_High_Fast: Output push-pull, high level, 10MHz
** GPIO_Mode_Out_OD_HiZ_Slow: Output open-drain, high-impedance level, 2MHz
** GPIO_Mode_Out_PP_High_Slow: Output push-pull, high level, 2MHz
**
*/

/* Low level -- GPIO Port
**
** GPIO_Mode_Out_OD_Low_Fast: Output open-drain, low level, 10MHz
** GPIO_Mode_Out_PP_Low_Fast: Output push-pull, low level, 10MHz
** GPIO_Mode_Out_OD_Low_Slow: Output open-drain, low level, 2MHz
** GPIO_Mode_Out_PP_Low_Slow: Output push-pull, low level, 2MHz
**
*/

/**
  * @brief : The led module's initialization function(On/Off Status)
  * @par Parameters : level -- Low level/High level
  * None
  * @retval 
  * None
*/
void LED_Module_Init(unsigned char level)
{
	if(level == LOW_LEVEL) {
    	GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);
	} else {
    	GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_High_Slow);
	}
}

/**
  * @brief : Toggle the led's level
  * @par Parameters
  * None
  * @retval 
  * None
*/
void LED_ToggleBits() 
{
  GPIO_ToggleBits(LED_GPIO_PORT, LED_GPIO_PINS);
}

/**
  * @brief : The port's initialization function(Power&&Reset)
  * @par Parameters
  * None
  * @retval 
  * None
*/
void SYSTEM_Ports_Init()
{
    GPIO_Init(LED_GPIO_PORT, POWER_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(LED_GPIO_PORT, RESET_GPIO_PINS, GPIO_Mode_Out_PP_High_Slow);
}

/**
  * @brief : The port's setting function(Reset)
  * @par Parameters
  * None
  * @retval 
  * None
*/
void SYSTEM_Reset_SetLevel(unsigned char level)
{
  if(level == LOW_LEVEL) {
    GPIO_ResetBits(LED_GPIO_PORT, RESET_GPIO_PINS);
#ifdef LED_TEST
    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PINS);
#endif
  } else {
    GPIO_SetBits(LED_GPIO_PORT, RESET_GPIO_PINS);
#ifdef LED_TEST
    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PINS);
#endif
  }
}

/**
  * @brief : The port's setting function(Power)
  * @par Parameters
  * None
  * @retval 
  * None
*/
void SYSTEM_Power_SetLevel(unsigned char level)
{
  if(level == LOW_LEVEL) {
    GPIO_ResetBits(LED_GPIO_PORT, POWER_GPIO_PINS);
    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PINS);
  } else {
    GPIO_SetBits(LED_GPIO_PORT, POWER_GPIO_PINS);
    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PINS);
  }
}

/**
  * @brief : Delay function
  * @par Parameters : nCount -- delay count
  * 
  * @retval 
  * None
*/
void Delay(unsigned int nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}
