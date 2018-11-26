/*******************************************************************************
*******************************************************************************/
#include "log_debug/log_debug.h"
#include "led/led.h"
#include "button_detection/button_detection.h"
#include "timer/timer.h"
#include "low_power/low_power.h"
#include "log_debug/data_process_center.h"

#include "stm8l15x.h"

/*******************************************************************************
**	Main function
*******************************************************************************/
int main( void )
{
	LOG_Module_Init();
	LED_Module_Init(HIGH_LEVEL);
	SYSTEM_Ports_Init();
	TIMER_Function_Init();
	BUTTON_Detection_Module();

	SYSTEM_Reset_SetLevel(HIGH_LEVEL);	/* invalid reset */
	SYSTEM_Power_SetLevel(HIGH_LEVEL);	/* valid power */

	DATA_ProcessCenter_Init();
	LOG_Text_Output("Debug Log", "wait mode init!");
	LPOWER_DeInit();

	//LPOWER_WakeUpEvent_Setting(); ##
	while(1) {
		DATA_Analyze_Control();
		BUTTON_Handle_Button_Event();
		LOG_Text_Output("Debug Log", "Hello World!1 \r\n");
		Delay(0xFFFF);
		halt();
        Delay(0xFFFF);
		LOG_Text_Output("Debug Log", "Hello World!2 \r\n");
		//LED_ToggleBits();
		//Delay(0xFFFF);
	}
    
}

/*******************************************************************************
*******************************************************************************/
