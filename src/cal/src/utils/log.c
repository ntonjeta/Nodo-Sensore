/**
  ******************************************************************************
  * @file    log.c
  * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
  * @version V1.0
  * @date    11/lug/2015
  * @brief   TODO: brief for log.c
  ******************************************************************************
  */

/* Includes ********************************************************************/
#include "cal_def.h"
#include "utils/log.h"

#ifndef CAL_USE_LOG
#define CAL_USE_LOG 0
#endif

/**
 * @addtogroup CAL_Module CAL Module
 * @{
 */

/**
 * @addtogroup CAL_LOG CAL Log Module
 * @brief Modulo per il logging in CAL
 * @{
 */

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/
/* Private Types ***************************************************************/
/* Private Variables ***********************************************************/
/* Private Functions ***********************************************************/

/**
 * @brief CAL_LOG_Private_Functions Private Functions
 * @brief Funzioni private
 * @{
 */

#if (CAL_USE_EVENTLOGGER_LOG == 1)
/**
 * @brief Mapping between internal and external severity
 * @param severity
 * @param functionName
 * @param name
 * @param value
 * @retval External severity
 */
static uint8_t calSeverityToEventLoggerSeverity(CAL_LogSeverity severity)
{
	switch(severity)
	{
	case CAL_LOG_ALERT:
		return ALERT;
		break;
	case CAL_LOG_CRITICAL:
		return CRITICAL;
		break;
	case CAL_LOG_ERROR:
		return ERROR;
		break;
	case CAL_LOG_WARNING:
		return WARNING;
		break;
	case CAL_LOG_NOTICE:
		return NOTICE;
		break;
	case CAL_LOG_INFORMATIONAL:
		return INFORMATIONAL;
		break;
	case CAL_LOG_DEBUG:
		return DEBUGGING;
		break;
	default:
		return INFORMATIONAL;
		break;
	}
}
#endif

/**
 * @}
 */
/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @defgroup CAL_LOG_Exported_Functions
 * @{
 */

/**
 * @brief Log di un valore intero
 * @param severity Severity
 * @param functionName Nome della funzione che fa il log
 * @param name Nome della entry del log
 * @param value Valore da loggare
 * @retval none
 */
void calLogInt(CAL_LogSeverity severity, char* functionName, char* name, uint16_t value)
{
	// If the logging feature is not enabled, simply return
#if (CAL_USE_LOG == 0)
	return;
#endif

	// Do not log events with severity lower than the one specified into the CAL_LOG_LEVEL
	if (severity > CAL_LOG_LEVEL)
	{
		return;
	}

	// Log only if the EVENTLOGGER is enabled
#if (CAL_USE_EVENTLOGGER_LOG == 1)
	// Log using the LogEvent facility
	EventLogger_LogEvent(
		&LOG_HANDLE,
		CAL_LOG_NAMESPACE,
		calSeverityToEventLoggerSeverity(severity),
		CAL_LOG_NODEID,
		(char*)functionName,
		LOG_INT, name, value, LOG_END
	);
#else
	calUnused(functionName);
	calUnused(name);
	calUnused(value);
#endif

	/*
	switch(severity)
	{
	case CAL_LOG_ALERT:
		printf("ALERT - %s - %s - %d", functionName, name, value);
		break;
	case CAL_LOG_CRITICAL:
		printf("CRITICAL - %s - %s - %d", functionName, name, value);
		break;
	case CAL_LOG_ERROR:
		printf("ERROR - %s - %s - %d", functionName, name, value);
		break;
	case CAL_LOG_WARNING:
		printf("WARNING - %s - %s - %d", functionName, name, value);
		break;
	case CAL_LOG_NOTICE:
		printf("NOTICE - %s - %s - %d", functionName, name, value);
		break;
	case CAL_LOG_INFORMATIONAL:
		printf("INFORMATIONAL - %s - %s - %d", functionName, name, value);
		break;
	case CAL_LOG_DEBUG:
		printf("DEBUG - %s - %s - %d", functionName, name, value);
		break;
	default:
		printf("DEFAULT - %s - %s - %d", functionName, name, value);
		break;
	}
	printf("\r\n");
	*/
}

/**
 * @brief Log di una stringa
 * @param severity Severity
 * @param functionName Nome della funzione che fa il log
 * @param name Nome della entry del log
 * @param value Valore da loggare
 * @retval none
 */
void calLogString(CAL_LogSeverity severity, char* functionName, char* name, char* value)
{
	// If the logging feature is not enabled, simply return
#if (CAL_USE_LOG == 0)
	return;
#endif

	// Do not log events with severity lower than the one specified into the CAL_LOG_LEVEL
	if (severity > CAL_LOG_LEVEL)
	{
		return;
	}

	// Log only if the EVENTLOGGER is enabled
#if (CAL_USE_EVENTLOGGER_LOG == 1)
	// Log using the LogEvent facility
	EventLogger_LogEvent(
		&LOG_HANDLE,
		CAL_LOG_NAMESPACE,
		calSeverityToEventLoggerSeverity(severity),
		CAL_LOG_NODEID,
		(char*)functionName,
		LOG_STRING, name, value, LOG_END
	);
#else
	calUnused(functionName);
	calUnused(name);
	calUnused(value);
#endif

	/*
	switch(severity)
	{
	case CAL_LOG_ALERT:
		printf("ALERT - %s - %s - %s", functionName, name, value);
		break;
	case CAL_LOG_CRITICAL:
		printf("CRITICAL - %s - %s - %s", functionName, name, value);
		break;
	case CAL_LOG_ERROR:
		printf("ERROR - %s - %s - %s", functionName, name, value);
		break;
	case CAL_LOG_WARNING:
		printf("WARNING - %s - %s - %s", functionName, name, value);
		break;
	case CAL_LOG_NOTICE:
		printf("NOTICE - %s - %s - %s", functionName, name, value);
		break;
	case CAL_LOG_INFORMATIONAL:
		printf("INFORMATIONAL - %s - %s - %s", functionName, name, value);
		break;
	case CAL_LOG_DEBUG:
		printf("DEBUG - %s - %s - %s", functionName, name, value);
		break;
	default:
		printf("DEFAULT - %s - %s - %s", functionName, name, value);
		break;
	}
	printf("\r\n");
	*/

}


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
