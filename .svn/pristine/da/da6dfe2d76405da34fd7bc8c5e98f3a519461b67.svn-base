/*
 * EventLogger_conf.c
 *
 *  Created on: Jul 1, 2015
 *      Author: davide
 */

#include "EventLogger.h"
#include "stm32f4_discovery.h"

USBH_HandleTypeDef hUSB_Host;
FATFS USBDISKFatFs;           /* File system object for USB disk logical drive */
char USBDISKPath[4];
FIL log_file;
int OK = 0;

static void CreateLogFile();
void USBH_LogProcess (USBH_HandleTypeDef *pHost, uint8_t vId);

EventLogger_Status_TypeDef  USBH_LogInit        (EventLogger_Handle_TypeDef *plog);
EventLogger_Status_TypeDef  USBH_LogDeInit      (EventLogger_Handle_TypeDef *plog);
EventLogger_Status_TypeDef  Write_FatFS      (EventLogger_Handle_TypeDef *plog);

EventLogger_Interface_TypeDef LOG_Interface =
{
  USBH_LogInit,
  USBH_LogDeInit,
  Write_FatFS
};

EventLogger_Status_TypeDef  USBH_LogInit(EventLogger_Handle_TypeDef *plog){
	if(FATFS_LinkDriver(&USBH_Driver, USBDISKPath) != 0){
		plog->LogStatus = LOG_STORAGE_INIT_FAILED;
		return plog->LogStatus;
	}
	else{
		plog->LogStatus = LOG_OK;
	}
	USBH_Init(&hUSB_Host, USBH_LogProcess, 0);
	USBH_RegisterClass(&hUSB_Host, USBH_MSC_CLASS);
	USBH_Start(&hUSB_Host);
	if(f_mount(&USBDISKFatFs, (TCHAR const*)USBDISKPath, 0) != FR_OK){
		LOG_HANDLE.LogStatus = LOG_FILESYSTEM_INIT_FAILED;
	}

	return plog->LogStatus;
}

EventLogger_Status_TypeDef  USBH_LogDeInit(EventLogger_Handle_TypeDef *plog){

	EventLogger_LogEvent(plog, MAINTENCE, INFORMATIONAL, 203834, "Disk_Remove()",
			LOG_END);
	OK = 0;
	plog->LogStatus = LOG_OK;

	return plog->LogStatus;
}

EventLogger_Status_TypeDef  Write_FatFS      (EventLogger_Handle_TypeDef *plog){

	if(f_open(&log_file, plog->LogFile, FA_WRITE) != FR_OK){
		plog->LogStatus = LOG_FILE_OPEN_FAILED;
		return plog->LogStatus;
	}
	if(f_lseek(&log_file, f_size(&log_file)) != FR_OK){
		plog->LogStatus = LOG_FILE_ACCESS_FAILED;
		return plog->LogStatus;
	}
	f_printf(&log_file, "%s", plog->pLogData->LogString );

	f_close (&log_file);
	plog->LogStatus = LOG_OK;
	return plog->LogStatus;
}

void USBH_LogProcess (USBH_HandleTypeDef *pHost, uint8_t vId)

{
	switch (vId)

	{

	case HOST_USER_SELECT_CONFIGURATION:

		break;



	case HOST_USER_DISCONNECTION:

		BSP_LED_On(LED3);
		BSP_LED_On(LED4);
		BSP_LED_On(LED5);
		BSP_LED_On(LED6);
#if	(LOG_USE_OS == 0)
		HAL_Delay(1000);
#else
		//osMessagePut(AppliEvent, APPLICATION_DISCONNECT, 0);
#endif
		BSP_LED_Off(LED3);
		BSP_LED_Off(LED4);
		BSP_LED_Off(LED5);
		BSP_LED_Off(LED6);
		break;



	case HOST_USER_CLASS_ACTIVE:
		CreateLogFile();
#if (LOG_USE_OS == 1)
		//osMessagePut(AppliEvent, APPLICATION_READY, 0);
#endif
		break;



	case HOST_USER_CONNECTION:
		BSP_LED_On(LED3);
		BSP_LED_On(LED4);
		BSP_LED_On(LED5);
		BSP_LED_On(LED6);
#if	(LOG_USE_OS == 0)
		HAL_Delay(1000);
#endif
		BSP_LED_Off(LED3);
		BSP_LED_Off(LED4);
		BSP_LED_Off(LED5);
		BSP_LED_Off(LED6);
		break;

	default:

		break;

	}
}

void CreateLogFile(){
	if(f_open(&log_file, LOG_HANDLE.LogFile, FA_OPEN_ALWAYS ) != FR_OK)
	{
		LOG_HANDLE.LogStatus = LOG_FILE_OPEN_FAILED;
	}
	else{
		if(f_close(&log_file) != FR_OK) LOG_HANDLE.LogStatus = LOG_FILE_CLOSE_FAILED;
		else {
			OK=1;
			LOG_HANDLE.LogStatus = LOG_OK;
		}
	}
}
