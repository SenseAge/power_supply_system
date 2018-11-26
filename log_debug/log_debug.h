/*
	@file:log_debug.h
	@author: wave top
	@date:2018/11/04
	@brief:the file of debug log message
	**************************************************
	@attention
	The module(log_debug) is to print the log message, such as the text message, variable and text message.
*/
#ifndef _LOG_DEBUG_H
#define _LOG_DEBUG_H

/* Functional functions */
void LOG_Module_Init();
void LOG_Text_Output(const char *head_msg,const char *msg);
void LOG_CommData_Transmition(const char *msg);
void LOG_TextVariable_Output(const char *head_msg, const char *msg, int variable);

#endif