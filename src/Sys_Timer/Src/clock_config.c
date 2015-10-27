/*
 * clock_config.h
 *
 *  Created on: Jul 12, 2015
 *      Author: andrea
 */
#include "clock.h"
#include "applayer.h"

SyncResultTypedef Lower_level_send(uint8_t client_id, sys_time* time){


        uint32_t Sec_millisec = time->milliseconds | (time->seconds << 16);
        uint32_t Month_minutes = time->minutes | (time->month<<16);
	NetMessage* payload = (NetMessage*)malloc(sizeof(NetMessage));
	payload->opCode = SYNC;
	if(time){
		payload->sensorID = client_id;
		payload->alarm = time->day;
		payload->highThreshold = Month_minutes;
		payload->lowThreshold = Sec_millisec;
		payload->period = time->year;
		payload->priority = time->hour;
	}
	securityLevelSend(client_id, payload);
	free(payload);

	return SYNC_OK;

}

