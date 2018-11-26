/*
	@file:low_power.h
	@author: wave top
	@date:2018/11/14
	@brief:low power consumption of mcu
	**************************************************
	@attention
	The module(data_process_center) is to achieve the low power consumption's features.
*/
#ifndef _LOW_POWER_H
#define _LOW_POWER_H

/* The status of the Soc moudle */
typedef enum {
	SOC_POWER_OFF = 0,
	SOC_POWER_ON,
	SOC_POWER_MAX	
} SOC_POWER_STATUS;

/* Functional functions */
void LPOWER_DeInit();
void LPOWER_WakeUpEvent_Setting();

void LPOWER_SetSocPower_Status(SOC_POWER_STATUS power_status);
SOC_POWER_STATUS LPOWER_GetSocPower_Status();

void LPOWER_MCU_lowPower_Mode();

#endif