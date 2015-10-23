/*
 * EventLogger_conf.c
 *
 *  Created on: Jul 1, 2015
 *      Author: davide
 */

#include "EventLogger.h"
#include "stm32f4_discovery.h"
#include "clock.h"


/* Flash Management Variables */
#define FLASHTOUSB_PRIO		osPriorityLow
#define FLASHTOUSB_STACKSIZE (2 * configMINIMAL_STACK_SIZE)
#define FLASHTOUSB_PERIOD	15
#define LOGMEMSIZE		1000*LOG_MAX_DIM
__attribute__((__section__(".user_data"))) volatile const uint8_t Log_Memory[LOGMEMSIZE];
osThreadId	FlashUSBID;

/* USB Variables */
USBH_HandleTypeDef hUSB_Host;
FATFS USBDISKFatFs;
char USBDISKPath[4];
/* File Variables */
FIL log_file;
int OK = 0;
int STOP = 0;
/* Task Counters */
int LogsStored_Flash = 0;
int LogsToStore_USB = 0;


static void CreateLogFile();
static void FlashToUSB_Process_OS(void const * argument);
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
		HAL_FLASH_Unlock();
		FLASH_Erase_Sector(FLASH_SECTOR_6,VOLTAGE_RANGE_3);
		HAL_FLASH_Lock();
		osThreadDef(LogFlashToUSB, FlashToUSB_Process_OS, FLASHTOUSB_PRIO, 0, FLASHTOUSB_STACKSIZE);
		FlashUSBID = osThreadCreate (osThread(LogFlashToUSB), plog);


	return plog->LogStatus;
}

EventLogger_Status_TypeDef  USBH_LogDeInit(EventLogger_Handle_TypeDef *plog){

	int NextLogToFlush = 0;
	char NextFlushString[LOG_MAX_DIM];

	if(OK == 1){
		if(f_open(&log_file, plog->LogFile, FA_WRITE) != FR_OK){
			plog->LogStatus = LOG_FILE_OPEN_FAILED;
		}
		if(f_lseek(&log_file, f_size(&log_file)) != FR_OK){
			plog->LogStatus = LOG_FILE_ACCESS_FAILED;
		}

		while(LogsToStore_USB > 0){
			NextLogToFlush = (LogsStored_Flash - LogsToStore_USB)*LOG_MAX_DIM;
			HAL_FLASH_Unlock();
			for(int i = 0; i < LOG_MAX_DIM; i++){
				NextFlushString[i] = Log_Memory[NextLogToFlush++];
				if(NextFlushString[i] == '\0') break;
			}
			HAL_FLASH_Lock();
			f_printf(&log_file, "%s", NextFlushString);
			LogsToStore_USB -= 1;
		}

		f_printf(&log_file, "%d:%d:%d,%d:%d:%d,Maintence,info,%d,Disk_Remove();\n",
				_sys_time.year, _sys_time.month, _sys_time.day,
				_sys_time.hour, _sys_time.minutes, _sys_time.seconds,
				10);
		f_close (&log_file);
		BSP_LED_Off(LED4);
		BSP_LED_On(LED6);
		plog->LogStatus = LOG_OK;
	}

	OK = 0;
	plog->LogStatus = LOG_OK;

	return plog->LogStatus;
}

EventLogger_Status_TypeDef  Write_FatFS      (EventLogger_Handle_TypeDef *plog){

	int current_position = LogsStored_Flash*LOG_MAX_DIM;
	char* current_string = plog->pLogData->LogString;
	if(current_position >= LOGMEMSIZE){
		plog->LogStatus = LOG_FILE_WRITE_FAILED;
		return plog->LogStatus;
	}
	HAL_FLASH_Unlock();
	for(int i = 0; i < LOG_MAX_DIM; i++){
	HAL_FLASH_Program(TYPEPROGRAM_BYTE,
				(uint8_t*) &Log_Memory[current_position++], current_string[i]);
		if(current_string[i] == '\0') break;
	}
	HAL_FLASH_Lock();
	LogsStored_Flash++;
	LogsToStore_USB++;

	BSP_LED_On(LED4);
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
		OK = 0;
		STOP = 1;
		BSP_LED_Off(LED3);
		BSP_LED_Off(LED4);
		BSP_LED_Off(LED5);
		BSP_LED_Off(LED6);
		break;

	case HOST_USER_CLASS_ACTIVE:
		CreateLogFile();
		OK=1;
		STOP = 0;
		break;

	case HOST_USER_CONNECTION:

		break;

	default:

		break;

	}
}

static void FlashToUSB_Process_OS(void const * argument){
	int NextLogToStore = 0;
	char NextString[LOG_MAX_DIM];

	while(1){
		if((LogsToStore_USB > 0) && (OK == 1))
		{

			if(f_open(&log_file, ((EventLogger_Handle_TypeDef*)argument)->LogFile, FA_WRITE) != FR_OK){
				((EventLogger_Handle_TypeDef*)argument)->LogStatus = LOG_FILE_OPEN_FAILED;
			}
			if(f_lseek(&log_file, f_size(&log_file)) != FR_OK){
				((EventLogger_Handle_TypeDef*)argument)->LogStatus = LOG_FILE_ACCESS_FAILED;
			}

			if(LogsToStore_USB > 0){
				NextLogToStore = (LogsStored_Flash - LogsToStore_USB)*LOG_MAX_DIM;
				HAL_FLASH_Unlock();
				for(int i = 0; i < LOG_MAX_DIM; i++){
					NextString[i] = Log_Memory[NextLogToStore++];
					if(NextString[i] == '\0') break;
				}
				HAL_FLASH_Lock();
				f_printf(&log_file, "%s", NextString);
				LogsToStore_USB -= 1;
			}
			f_close (&log_file);
			BSP_LED_Toggle(LED4);
			((EventLogger_Handle_TypeDef*)argument)->LogStatus = LOG_OK;
		}
		osDelay(FLASHTOUSB_PERIOD);
	}
}


void CreateLogFile(){
	if(f_open(&log_file, LOG_HANDLE.LogFile, FA_OPEN_ALWAYS | FA_WRITE) != FR_OK)
	{
		LOG_HANDLE.LogStatus = LOG_FILE_OPEN_FAILED;
	}
	else{
		f_printf(&log_file, "%d:%d:%d,%d:%d:%d,Maintence,info,%d,Disk_Attached();\n",
				_sys_time.year, _sys_time.month, _sys_time.day,
				_sys_time.hour, _sys_time.minutes, _sys_time.seconds,
				10);
		if(f_close(&log_file) != FR_OK) LOG_HANDLE.LogStatus = LOG_FILE_CLOSE_FAILED;
		else {
			LOG_HANDLE.LogStatus = LOG_OK;
		}
	}
}
