/*
 * EventLogger.c
 *
 *  Created on: Jul 1, 2015
 *      Author: davide
 */

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "EventLogger.h"
#include "clock.h"

#if (LOG_USE_OS == 1)
osMutexId Log_Mutex;
#if (LOG_USE_BUFFERING == 1)
int LogIndex_List[LOG_MAX_BUFF];
EventLogger_Log_TypeDef Log_List[LOG_MAX_BUFF];
static void LogCollector_Process_OS(void const * argument);
#endif	//END BUFFERING
#endif	//END OS

#if (LOG_USE_BUFFERING == 0)
EventLogger_Log_TypeDef    LogMsg;
#endif

static char* IntegerToString(int number, char* string){
	    char* p = string;
	    if(number<0){
	        *p++ = '-';
	        number *= -1;
	    }
	    int shifter = number;
	    do{
	        ++p;
	        shifter = shifter/10;
	    }while(shifter);
	    *p = '\0';
	    do{
	        *--p = (number%10)+48;
	        number = number/10;
	    }while(number);
	    return string;
}

EventLogger_Status_TypeDef EventLogger_Init(EventLogger_Handle_TypeDef *plog, EventLogger_Interface_TypeDef *ploginterface){

		if(plog->LogFile == NULL) plog->LogFile = LOGFILE_DEFAULT;
		plog->Interface = ploginterface;

		plog->LogStatus = plog->Interface->Init(plog);
#if (LOG_USE_OS == 1)
		osMutexDef(Log_Mutex);
		Log_Mutex = osMutexCreate(osMutex(Log_Mutex));
#if (LOG_USE_BUFFERING == 1)
		for(int i = 0; i< LOG_MAX_BUFF; i++) LogIndex_List[i] = 0;
		osMessageQDef(Log_Queue, LOG_MAX_BUFF, uint16_t);
		plog->os_event = osMessageCreate (osMessageQ(Log_Queue), NULL);
		osThreadDef(LogCollector, LogCollector_Process_OS, LOG_COLLECTOR_PRIO, 0, LOG_COLLECTOR_STACKSIZE);
		plog->thread = osThreadCreate (osThread(LogCollector), plog);
		plog->pLogData = 0;
#endif	//END BUFFRING
#endif	//END OS
#if (LOG_USE_BUFFERING == 0)
		plog->pLogData = &LogMsg;
#endif

	return plog->LogStatus;
}

EventLogger_Status_TypeDef EventLogger_DeInit(EventLogger_Handle_TypeDef *plog){

	plog->LogStatus = plog->Interface->DeInit(plog);
	return plog->LogStatus;
}

EventLogger_Status_TypeDef EventLogger_LogEvent(EventLogger_Handle_TypeDef *plog, uint Facility,
												uint Severity, uint Node_id, char* Function_id,
												...){

	EventLogger_Log_TypeDef		TempLog;
	TempLog.LogString[0] = '\0';
	char String[20];
	String[0] = '\0';
	char Time[20];
	Time[0] = '\0';
	int Next = -1;

	switch(Facility){
		case APPLICATION:
			strcat(TempLog.LogString,"Application");
			break;
		case NETWORK:
			strcat(TempLog.LogString,"Network");
			break;
		case DATALINK:
			strcat(TempLog.LogString,"Datalink");
			break;
		case SECURITY:
			strcat(TempLog.LogString,"Security");
			break;
		case MAINTENCE:
			strcat(TempLog.LogString,"Maintence");
			break;
		default:
			strcat(TempLog.LogString,"Unknown");
			break;
	}

	strcat(TempLog.LogString, ",");

	switch(Severity){
		case ALERT:
			strcat(TempLog.LogString, "alert");
			break;
		case CRITICAL:
			strcat(TempLog.LogString, "crit");
			break;
		case ERROR:
			strcat(TempLog.LogString, "err");
			break;
		case WARNING:
			strcat(TempLog.LogString, "warning");
			break;
		case NOTICE:
			strcat(TempLog.LogString, "notice");
			break;
		case INFORMATIONAL:
			strcat(TempLog.LogString, "info");
			break;
		case DEBUGGING:
			strcat(TempLog.LogString, "debug");
			break;
		default:
			strcat(TempLog.LogString, "unknown");
			break;
	}

	strcat(TempLog.LogString, ",");
	strcat(TempLog.LogString, IntegerToString(Node_id, String));
	strcat(TempLog.LogString, ",");
	strcat(TempLog.LogString, Function_id);

	va_list Description_Params;
	va_start (Description_Params, Function_id);

	Next = va_arg(Description_Params, int);
	if(Next == LOG_END){
		strcat(TempLog.LogString, ";\n");
	}
	else{
		strcat(TempLog.LogString, ",");
	do{
		switch(Next){
			case LOG_INT:
				strcat(TempLog.LogString, " ");
				strcpy(String, va_arg(Description_Params, char*));
				strcat(TempLog.LogString, String);
				strcat(TempLog.LogString, "=");
				IntegerToString(va_arg(Description_Params, int), String);
				strcat(TempLog.LogString, String);
				break;
			case LOG_STRING:
				strcat(TempLog.LogString, " ");
				strcpy(String, va_arg(Description_Params, char*));
				strcat(TempLog.LogString, String);
				strcat(TempLog.LogString, "=");
				strcpy(String, va_arg(Description_Params, char*));
				strcat(TempLog.LogString, String);
				break;
			case LOG_END:
				break;
			default:
				Next = LOG_END;
				break;
		}
		Next = va_arg(Description_Params, int);
	} while ( Next != LOG_END);

	strcat(TempLog.LogString, ";\n");
	}


#if (LOG_USE_OS == 1)
	osMutexWait(Log_Mutex, osWaitForever);
	strcat(Time,IntegerToString(_sys_time.year,String));
	strcat(Time, ":");
	strcat(Time,IntegerToString(_sys_time.month,String));
	strcat(Time, ":");
	strcat(Time,IntegerToString(_sys_time.day,String));
	strcat(Time, ",");
	strcat(Time,IntegerToString(_sys_time.hour,String));
	strcat(Time, ":");
	strcat(Time,IntegerToString(_sys_time.minutes,String));
	strcat(Time, ":");
	strcat(Time,IntegerToString(_sys_time.seconds,String));
	strcat(Time, ",");
#if	(LOG_USE_BUFFERING == 1)
	int i = 0;
	while(LogIndex_List[i] != 0) {i++;}
	LogIndex_List[i] = 1;
	strcpy(Log_List[i].LogString, Time);
	strcat(Log_List[i].LogString, TempLog.LogString);
	osMessagePut ( plog->os_event, i, 0);
#else	//ELSE BUFFERING
	strcpy(plog->pLogData->LogString, Time);
	strcat(plog->pLogData->LogString, TempLog.LogString);
	plog->Interface->WriteLog(plog);
#endif	//END BUFFERING
	osMutexRelease(Log_Mutex);
#else	// ELSE OS
	strcat(Time,IntegerToString(_sys_time.year,String));
	strcat(Time, ":");
	strcat(Time,IntegerToString(_sys_time.month,String));
	strcat(Time, ":");
	strcat(Time,IntegerToString(_sys_time.day,String));
	strcat(Time, ",");
	strcat(Time,IntegerToString(_sys_time.hour,String));
	strcat(Time, ":");
	strcat(Time,IntegerToString(_sys_time.minutes,String));
	strcat(Time, ":");
	strcat(Time,IntegerToString(_sys_time.seconds,String));
	strcat(Time, ",");
	strcpy(plog->pLogData->LogString, Time);
	strcat(plog->pLogData->LogString, TempLog.LogString);
	plog->Interface->WriteLog(plog);
#endif	// END OS
	va_end(Description_Params);
	return LOG_OK;
}

#if ((LOG_USE_OS == 1) && (LOG_USE_BUFFERING == 1))
static void LogCollector_Process_OS(void const * argument)
{
  osEvent event;

  for(;;)
  {
    event = osMessageGet(((EventLogger_Handle_TypeDef *)argument)->os_event, osWaitForever );

    if( event.status == osEventMessage  )
    {
    	((EventLogger_Handle_TypeDef *)argument)->pLogData = &Log_List[event.value.v];
    	((EventLogger_Handle_TypeDef*) argument)->Interface->WriteLog((EventLogger_Handle_TypeDef*) argument);
    	((EventLogger_Handle_TypeDef *)argument)->pLogData = 0;
    	LogIndex_List[event.value.v] = 0;
    }

    osDelay(LOG_COLLECTOR_PERIOD);
   }
}

#endif
