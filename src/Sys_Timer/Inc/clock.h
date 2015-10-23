/*
 * clock.h
 *
 *  Created on: Jun 25, 2015
 *      Author: andrea
 */

#ifndef CLOCK_INC_CLOCK_H_
#define CLOCK_INC_CLOCK_H_

#include <stdlib.h>
#include <stdint.h>

#define TIME_SERVER 0		/*da settare a 1 se server, 0 se client*/

typedef struct {

	uint16_t  year;
	uint8_t   month;
	uint8_t   day;
	uint8_t   hour;
	uint8_t   minutes;
	uint8_t   seconds;
	uint16_t  milliseconds;

} sys_time;

void init_time(uint32_t timeout);
void set_timeout(uint32_t timeout);
void set_time(sys_time _time);
void get_time(sys_time _time);
#if TIME_SERVER == 1
void host_send_time(uint8_t client_id);
#else
void client_sync_time(sys_time temp);
#endif
uint8_t is_time_enabled();
void IncTime(void);

extern sys_time _sys_time;



#endif /* CLOCK_INC_CLOCK_H_ */
