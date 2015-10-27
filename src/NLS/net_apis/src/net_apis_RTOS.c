/*
 * net_apis_RTOS.c
 *
 *  Created on: 12/lug/2015
 *      Author: gennaro
 */

#include "net_apis_RTOS.h"
#include "data_plane.h"


void NLS_RTOS_init (struct NLS_HandleTypedef* hNLS)
{
	hNLS->event_queue = xQueueCreate(NLS_EVENT_QUEUE_SIZE, sizeof(datagram_info*));

	 xTaskCreate( receive_task, 				/* Pointer to the function that implements the task. */
	   	            "NLS Receive Task",				/* Text name for the task. For debugging only. */
	   	            NLS_RECEIVE_TASK_STACK_SIZE,	/* Stack depth in words. */
	   	            (void*)hNLS,							/* We are using the task parameter. */
	   	            NLS_RECEIVE_TASK_PRIORITY,  	/* Task Priority */
	   	            hNLS->receive_task_handle 		/* Task handle. */
	   	            );

	 xTaskCreate( send_task, 					/* Pointer to the function that implements the task. */
	   	            "NLS Send Task",				/* Text name for the task. For debugging only. */
	   	            NLS_SEND_TASK_STACK_SIZE,		/* Stack depth in words. */
	   	            (void*)hNLS,							/* We are not using the task parameter. */
	   	            NLS_SEND_TASK_PRIORITY,  		/* Task Priority */
	   	            hNLS->send_task_handle 							/* Task handle. */
	   	            );

}

void NLS_RTOS_deinit (struct NLS_HandleTypedef* hNLS)
{
	vQueueDelete(hNLS->event_queue);
	vTaskDelete(hNLS->send_task_handle);
	vTaskDelete(hNLS->receive_task_handle);
}


void receive_task(void* pvParameters)
{
	struct NLS_HandleTypedef* hNLS = (struct NLS_HandleTypedef*)pvParameters;
	datagram_info* d_info;
	for( ; ; )
	{
		xQueueReceive(hNLS->event_queue, &d_info, portMAX_DELAY);
		#ifndef ROOT

		if (d_info->retry != 0)
		{
			UTSwapMainLink(hNLS->uTable);

			if(UTGetMainLink(hNLS->uTable) == UPSTREAM_TABLE_IS_EMPTY)
			{
				free_datagram_info(d_info);
			}
			else
			{
				receive_datagram(hNLS, d_info->source_if, d_info->packet, d_info->packet_length);

			}

		}
		else
		{
			receive_datagram(hNLS, d_info->source_if, d_info->packet, d_info->packet_length);
		}
		#else

		if (d_info->retry != 0)
		{
			downStreamTablePenaliziesBestPath(hNLS->dTable , d_info->address);
		}
		receive_datagram(hNLS,d_info->source_if,d_info->packet,d_info->packet_length);

		#endif
	}

}

void send_task(void* pvParameters)
{
	for ( ; ; ){
		dispatchNet((struct NLS_HandleTypedef*)pvParameters);
		vTaskDelay(NLS_DISPATCHER_DELAY/portTICK_PERIOD_MS);
	}
}

