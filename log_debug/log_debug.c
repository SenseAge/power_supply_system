/*
	@file:log_debug.c
	@author: wave top
	@date:2018/11/04
	@brief:the file of debug log message
	**************************************************
	@attention
	The module(log_debug) is to print the log message, such as the text message, variable and text message.
*/
#include "stm8l15x.h"
#include "log_debug.h"
/* Functions declaration */
static void LOG_SendData8(uint8_t cdata);

/**
  * @brief : The log module's initialization function
  * @par Parameters : None
  * None
  * @retval 
  * None
*/
void LOG_Module_Init()
{
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//¿ªÆôUSARTÊ±ÖÓ
    USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx|USART_Mode_Rx);//ÉèÖÃUSART²ÎÊý9600£¬8N1£¬½ÓÊÕ/·¢ËÍ
    USART_ITConfig (USART1,USART_IT_RXNE,ENABLE);//Ê¹ÄÜ½ÓÊÕÖÐ¶Ï,ÖÐ¶ÏÏòÁ¿ºÅÎª28 |USART_IT_TC
    USART_Cmd (USART1,ENABLE);//Ê¹ÄÜUSART
    enableInterrupts(); 
}

/**
  * @brief : Print the text message
  * @par Parameters : head_msg - The head message of log message
					  msg - The text message of log message
  * None
  * @retval 
  * None
*/
void LOG_Text_Output(const char *head_msg, const char *msg)
{
	if(head_msg != 0 || msg != 0) {
		while(*head_msg != '\0') {
			LOG_SendData8(*head_msg);
	    	head_msg ++;
		}
		LOG_SendData8(':');
		while(*msg != '\0') {
			LOG_SendData8(*msg);
	    	msg ++;
		}
	}
}

/**
  * @brief : Print the text and variable message
  * @par Parameters : head_msg - The head message of log message
					  msg - The text message of log message
					  variable - The key variable of log message
  * None
  * @retval 
  * None
*/
void LOG_TextVariable_Output(const char *head_msg, const char *msg, int variable)
{
	//None
}

/**
  * @brief : Print the text message
  * @par Parameters : head_msg - The head message of log message
					  msg - The text message of log message
  * None
  * @retval 
  * None
*/
void LOG_CommData_Transmition(const char *msg)
{
	if( msg != 0 ) {
		while(*msg != '\0') {
			LOG_SendData8(*msg);
	    	msg ++;
		}
	}
}

/**
  * @brief : Print the character data
  * @par Parameters : cdata - The character data
  * None
  * @retval
  * None
*/
static void LOG_SendData8(uint8_t cdata)
{
	/* Wait transmit data is completed */
	while((RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE)));
	USART_SendData8 (USART1, cdata);
}