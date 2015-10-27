/*
 * NLS_globals.h
 *
 *  Created on: 03/lug/2015
 *      Author: gennaro
 */

#ifndef NLS_GLOBALS_H_
#define NLS_GLOBALS_H_

//#define NLS_TRACE

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "UpstreamTable.h"
#include "PriorityQueue.h"
#include "datagram_info.h"

#include "datagram_t.h"
#include "datagram_data_upstream_t.h"
#include "datagram_data_downstream_t.h"
#include "datagram_pfwd_t.h"
#include "datagram_defs.h"
#include "cal_def.h"
#include "cal.h"

#define NLS_DISPATCHER_DELAY				300
#define NLS_DISPATCHER_WAITING_PREP_TIME	300
#define NLS_RECEIVE_TASK_STACK_SIZE 		300
#define NLS_SEND_TASK_STACK_SIZE			300
#define NLS_EVENT_QUEUE_SIZE				100
#define NLS_RECEIVE_TASK_PRIORITY 			tskIDLE_PRIORITY+2
#define NLS_SEND_TASK_PRIORITY				tskIDLE_PRIORITY+2

#endif /* NLS_GLOBALS_H_ */
