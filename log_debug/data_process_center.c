/*
	@file:data_process_center.c
	@author: wave top
	@date:2018/11/10
	@brief:the file of data processing center
	**************************************************
	@attention
	The module(data_process_center) is to process the data from Soc, include Storing data, 
		analyse data and send data.
*/

#include <string.h>
#include "data_process_center.h"
#include "low_power/low_power.h"
#include "button_detection/button_detection.h"
#include "led/led.h"
#include "STM8L15x_conf_it\stm8l15x_it.h"

/* all communication commond */
const char *commond_all[COMMOND_NUM] = {
	"waked",
	"powered",
	"order",
	"cancel",
	"1",
	"off"
};

const char commond_start = '%';
const char commond_end = '$';

/* some specefice commonds */
unsigned char new_commond;
char commond[COMMOND_MAX_SIZE];
char *commond_ptr = NULL;
char *commond_head = NULL;
char *commond_tail = NULL;

char commond_test[COMMOND_MAX_SIZE];
char *commond_ptr_test = &commond_test[0];
char i_test = 0;

/* communication data poll */
unsigned char data_poll[DATA_MAX_SIZE];
unsigned char *tail_ptr = NULL;
unsigned char *head_ptr = NULL;
unsigned char *wr_ptr = NULL;
unsigned char *rd_ptr = NULL;
unsigned int data_size;

unsigned int data_size_test = 0;

/* control status -- analyse status/compare commond status */
OPERATION_STATUS operation_sts;
COMMOND_STATUS commond_sts;

/**
  * @brief : Iniaialization of process data's center 
  * @par Parameters 
  *	None
  * None
  * @retval 
  * None
*/
void DATA_ProcessCenter_Init()
{
	INT_InitCommondMessage();

	memset(data_poll, 0x00, sizeof(data_poll));

	commond_ptr = commond_head = &commond[0];
	commond_tail = &commond[DATA_MAX_SIZE];

	tail_ptr = &data_poll[DATA_MAX_SIZE];
	head_ptr = &data_poll[0];
	rd_ptr = wr_ptr = head_ptr;
	data_size = 0;

	operation_sts = OPERATION_START;
	new_commond = COMMOND_FALSE;
	commond_sts = COMMOND_OPERATION;
}

/**
  * @brief : Control operation of process commond's center 
  * @par Parameters
  *	None
  * None
  * @retval 
  * None
*/
void DATA_Analyze_Control()
{
	if(new_commond == COMMOND_TRUE) {
		commond_sts = COMMOND_OK;
	} else if(new_commond == COMMOND_FALSE) {
		commond_sts = COMMOND_OPERATION;
	}

	switch(commond_sts) {
		case COMMOND_OK:
			DATA_Analyze_Commond();
			new_commond = COMMOND_FALSE;
		break;
		case COMMOND_OPERATION:
			DATA_Analyze_Operation();
		break;
		default:
		break;
	}
}

/**
  * @brief : Execute operation of compare the commond's center 
  * @par Parameters 
  *	None
  * None
  * @retval 
  * None
*/
void DATA_Analyze_Commond()
{
	unsigned char i;
	for(i = 0; i < COMMOND_MAX; i++) {
		if(0 == strncmp( commond, commond_all[i], sizeof(commond_all[i]))){
			break;
		}			
	}

	switch(i){
		case COMMOND_WAKED:
			LPOWER_SetSocPower_Status(SOC_POWER_ON);
			LOG_CommData_Transmition("%powered%");
			if(BUTTON_DEFAULT ==BUTTON_PowerButton_Type()) {
				LPOWER_MCU_lowPower_Mode();
			}
			LOG_Text_Output("msg0:",commond_all[i]);
		break;
		case COMMOND_POWERED:
			LOG_Text_Output("msg1:",commond_all[i]);
		break;
		case COMMOND_ORDER:
			LOG_Text_Output("msg2:",commond_all[i]);
		break;
		case COMMOND_CANCEL:
			LOG_Text_Output("msg3:",commond_all[i]);
		break;
		case COMMOND_SETUP:
			LOG_Text_Output("msg4:","HELLO!");
		break;
		case COMMOND_OFF:
			LOG_CommData_Transmition("%off%");
			SYSTEM_Power_SetLevel(LOW_LEVEL);	/* invalid power */
			LPOWER_SetSocPower_Status(SOC_POWER_OFF);
			LPOWER_MCU_lowPower_Mode();
		break;
		default:
		break;
	}
}

/**
  * @brief : Analyse data operation of handle the data poll 
  * @par Parameters
  *	None
  * None
  * @retval 
  * None
*/
void DATA_Analyze_Operation()
{
	unsigned char cur_data;

	DATA_HandleMessage_UartInterrupt();

	if(data_size > 0 || operation_sts == OPERATION_END) {
		switch(operation_sts) {
			case OPERATION_START:
				i_test ++;
				cur_data = DATA_Read_Operation();
				if(commond_start == cur_data) {
					operation_sts = OPERATION_DATA;
					memset(commond, 0x00, sizeof(commond));
					if(i_test == 8) {
						memset(commond_test, 0x00, sizeof(commond_test));
					}
				} else {
					operation_sts = OPERATION_START;
				}
			break;
			case OPERATION_DATA:
				cur_data = DATA_Read_Operation();
				if(commond_end == cur_data) {
					operation_sts = OPERATION_END;
				} else {
					*commond_ptr = cur_data;
					commond_ptr ++;

					*commond_ptr_test = cur_data;
					commond_ptr_test ++;

					if(commond_ptr == commond_tail) {
						commond_ptr = commond_head; 
					}
				}
			break;
			case OPERATION_END:
				commond_ptr = commond_head;
				new_commond = COMMOND_TRUE;
				operation_sts = OPERATION_START;
				data_size_test = 0;
				commond_ptr_test = &commond_test[0];
			break;
			default:
			break;
		}
	}
}

/**
  * @brief : Read operation of handle the data poll 
  * @par Parameters
  *	None
  * None
  * @retval 
  * None
*/
unsigned char DATA_Read_Operation()
{
	unsigned char cur_data;
	if(data_size > 0  && wr_ptr != rd_ptr) {
		cur_data = *rd_ptr;

		if(rd_ptr ==  tail_ptr) {
			rd_ptr = head_ptr;
		} else {
			rd_ptr ++;
		}
		data_size --;
	}

	return cur_data;
}

/**
  * @brief : Write operation of load into the data poll 
  * @par Parameters: com_data -- loaded data
  *	None
  * None
  * @retval 
  * None
*/
void DATA_Write_Operation(unsigned char com_data)
{
	if( wr_ptr == tail_ptr) {
		wr_ptr = head_ptr;
	}

	if( wr_ptr == rd_ptr && data_size == DATA_MAX_SIZE) {
		data_size = 0;
	}

	*wr_ptr = com_data;
	wr_ptr ++;

	data_size ++;
	data_size_test ++;
}

void DATA_HandleMessage_UartInterrupt()
{
	unsigned char i = 0;
	COMMOND_MESSAGE commond_msg;

	commond_msg = INT_GetCommondMessage();

	if(COMMOND_VALID == commond_msg.commond_rcv_sts && commond_msg.commond_size > 0) {
		for(i = 0; i < commond_msg.commond_size; i ++) {
			DATA_Write_Operation(commond_msg.commond_analyse[i]);
		}
		INT_SetCommondMessage( DATA_START, COMMOND_INVALID, 0);
	}
}