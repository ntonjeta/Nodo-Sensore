/*
 * net_apis_usr_template.c
 *
 *  Created on: 04/lug/2015
 *      Author: gennaro
 */
#include "net_apis_usr.h"
#include "stm32f4_discovery.h"
#include <stdlib.h>

check_status on_USR_datagram_check(uint8_t* trailer)
{
	return CHECK_OK;

}

//XXX COMMENTATA PER USARE LIVELLO TRASPORTO
//void on_USR_datagram_received(uint8_t* packet , int len , uint16_t addr)
//{
//#ifdef ROOT
//	//send_datagram(&hNLS,packet,len,0x11,CONTROL,1);
	//send_datagram(&hNLS,packet,len,addr,CONTROL,1);
//#endif
//
//}


challenge_t on_USR_path_discovery ()
{
	return (challenge_t)malloc( (sizeof(challenge_t)*CHALLENGE_LEN_BYTE));
}

uint8_t* on_USR_PREQ(uint8_t* challenge)
{
	return (uint8_t*)malloc(sizeof(uint8_t)*CHALLENGE_LEN_BYTE);
}

void on_USR_path_discovered ()
{

}

uint8_t* on_USR_trailer_gen(uint8_t* packet , uint8_t length)
{
	return (uint8_t*)malloc(length);
}

uint8_t* on_USR_PREP (uint8_t* secret , uint8_t length)
{
	return (uint8_t*)malloc(length);

}
void on_USR_path_discovered_root (uint16_t node , uint16_t* path , uint8_t length)
{

}
