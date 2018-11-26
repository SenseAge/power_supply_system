/*
	@file:timer.c
	@author: wave top
	@date:2018/11/08
	@brief:the file of timer relation
	**************************************************
	@attention
	The module(timer) control to set the timer time function and the pwm wave.
*/

#include "timer.h"
#include "stm8l15x.h"

/**
  * @brief : The timer module's initialization function(timer time function)
  * @par Parameters
  * None
  * @retval 
  * None
*/
void TIMER_Function_Init()
{
    CLK_PeripheralClockConfig (CLK_Peripheral_TIM4,ENABLE);

    // 16M/8/128=15.625K, 0xff=255, 255*（1/15625）= 0.01632s
    /* 0x9c=156,  156*（1/15625）=0.01s */
    TIM4_TimeBaseInit(TIM4_Prescaler_128, 0x9c);
    // Overflow interrupt, interrupt function vector number is 25
    TIM4_ITConfig(TIM4_IT_Update, ENABLE);
    
    //TIM4_Cmd(ENABLE);
    enableInterrupts();
}

/**
  * @brief : The timer module is starting(timer time function)
  * @par Parameters
  * None
  * @retval 
  * None
*/
void TIMER_Start()
{
    TIM4_Cmd(ENABLE);
}

/**
  * @brief : The timer module is ending(timer time function)
  * @par Parameters
  * None
  * @retval 
  * None
*/
void TIMER_End()
{
    TIM4_Cmd(DISABLE);
}