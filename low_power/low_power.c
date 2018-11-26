/*
	@file:low_power.c
	@author: wave top
	@date:2018/11/14
	@brief:low power consumption of mcu
	**************************************************
	@attention
	The module(data_process_center) is to achieve the low power consumption's features.
*/

#include "stm8l15x.h"
#include "low_power.h"

SOC_POWER_STATUS Soc_Power_Status = SOC_POWER_OFF;

/**
  * @brief : set the WFE configuration to the default reset staten
  * @par Parameters : None
  * None
  * @retval 
  * None
*/
void LPOWER_DeInit()
{
	WFE_DeInit();
}

/**
  * @brief : Wake up the low power status according(I/O port interrupt from Pins 6)
  * @par Parameters : None
  * None
  * @retval 
  * None
*/
void LPOWER_WakeUpEvent_Setting()
{
	WFE_WakeUpSourceEventCmd(WFE_Source_EXTI_EV6, ENABLE);
}

/**
  * @brief : The power status of Soc moudle
  * @par Parameters : power_status -- power status
  * None
  * @retval 
  * None
*/
void LPOWER_SetSocPower_Status(SOC_POWER_STATUS power_status)
{
	Soc_Power_Status = power_status;
}

SOC_POWER_STATUS LPOWER_GetSocPower_Status()
{
	return Soc_Power_Status;
}

/**
  * @brief : MCU enter to the lower power status
  * @par Parameters : None
  * None
  * @retval 
  * None
*/
void LPOWER_MCU_lowPower_Mode()
{
	/* Mcu enter to low power status */
	
}