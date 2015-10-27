/*
 * datagram.c
 *
 *  Created on: 01/lug/2015
 *      Author: gennaro
 */

#include "datagram_t.h"
#include "datagram_defs.h"

uint8_t get_datagram_T(uint8_t* packet)
{
	return (uint8_t)getField(packet , DATAGRAM_T_DISP , DATAGRAM_T_LEN );
}

void set_datagram_T(uint8_t* packet, uint8_t T)
{
	setField(packet , 0 , 1  , (int)T);
}

datagram_type_t get_datagram_type(uint8_t* packet)
{

	return (datagram_type_t)getField(packet,DATAGRAM_TYPE_DISP,DATAGRAM_TYPE_LEN);
}

datagram_qos_t get_datagram_QoS(uint8_t* packet)
{
	return (datagram_qos_t)getField(packet,DATAGRAM_QOS_DISP,DATAGRAM_QOS_LEN);

}

datagram_address_t get_datagram_address(uint8_t* packet)
{
	return (datagram_address_t)getField(packet,DATAGRAM_ADDRESS_DISP,DATAGRAM_ADDRESS_LEN);

}

void set_datagram_type(uint8_t* packet, datagram_type_t type)
{

	setField(packet , DATAGRAM_TYPE_DISP , DATAGRAM_TYPE_LEN , type);

}

void set_datagram_address(uint8_t* packet, datagram_address_t address)
{

	setField(packet , DATAGRAM_ADDRESS_DISP , DATAGRAM_ADDRESS_LEN , address);

}

void set_datagram_QoS(uint8_t* packet, datagram_qos_t qos)
{

	setField(packet , DATAGRAM_QOS_DISP , DATAGRAM_QOS_LEN , qos);

}


