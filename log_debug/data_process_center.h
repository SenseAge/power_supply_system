/*
	@file:data_process_center.h
	@author: wave top
	@date:2018/11/10
	@brief:the file of data processing center
	**************************************************
	@attention
	The module(data_process_center) is to process the data from Soc, include Storing data, 
		analyse data and send data.
*/
#ifndef _DATA_PROCESS_CENTER_H
#define _DATA_PROCESS_CENTER_H

#define	DATA_MAX_SIZE	50
#define COMMOND_SIZE	10

#define	COMMOND_TRUE	1
#define COMMOND_FALSE	0

#define COMMOND_NUM		6
#define COMMOND_MAX_SIZE	10

#define INT_COMMOND_LENGTH_MAX  10

/* Status of analyse the data poll */
typedef enum
{
	OPERATION_START = 0,
	OPERATION_DATA,
	OPERATION_END
}OPERATION_STATUS;

/* Status of analyze the result of the datapool */
typedef enum
{
	COMMOND_OK = 0,
	COMMOND_OPERATION
}COMMOND_STATUS;

/* Status of receive the valid commond in USART receive interrupt */
typedef enum
{
	DATA_START = 0,
	DATA_RCV,
	DATA_END
}USART_DATA_STATUS;

/* Status of judge the valid data in USART receive interrupt */
typedef enum
{
	COMMOND_INVALID = 0,
	COMMOND_VALID
}USART_STATUS;

/* Status of judge the valid data in USART receive interrupt */
typedef struct
{
	USART_DATA_STATUS uart_data_sts;
	USART_STATUS commond_rcv_sts;
	unsigned char commond_analyse[INT_COMMOND_LENGTH_MAX];
	unsigned char commond_size;
}COMMOND_MESSAGE;

/* Status of compare the specefic commond */
typedef enum
{
	COMMOND_WAKED = 0,
	COMMOND_POWERED,
	COMMOND_ORDER,
	COMMOND_CANCEL,
	COMMOND_SETUP,
	COMMOND_OFF,
	COMMOND_MAX
}COMMOND_RESULT;

/* Functional functions */
void DATA_ProcessCenter_Init();
void DATA_Write_Operation(unsigned char com_data);
void DATA_Analyze_Control();
void DATA_Analyze_Commond();
void DATA_Analyze_Operation();
unsigned char DATA_Read_Operation();

void DATA_HandleMessage_UartInterrupt();

#endif