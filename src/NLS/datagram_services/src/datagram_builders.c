/*
 * datagram_builders.c
 *
 *  Created on: 02/lug/2015
 *      Author: gennaro
 */

#include "datagram_data_upstream_t.h"
#include "datagram_data_downstream_t.h"
#include "datagram_pfwd_t.h"

#include "datagram_builders.h"
#include "network_config.h"


//-------------------------------------------------------------------------------------

uint8_t* build_usData (usData_typedef usData , int* datagram_length)
{
	*datagram_length = DATAGRAM_DATAUP_HEADER_LEN_BYTE +(int)usData.payload_length;

	if (usData.trailer != NULL)
	{
		*datagram_length += TRAILER_LEN_BYTE;
	}

	uint8_t* packet = (uint8_t*)malloc(sizeof(uint8_t)*(*datagram_length));

	set_datagram_type(packet , DATA_UP);
	set_datagram_QoS(packet , usData.qos);
	set_datagram_address(packet , MY_ADDRESS);
	set_datagram_dataup_len_payload(packet , usData.payload_length);
	set_datagram_dataup_payload(packet , (payload_t)usData.payload);

	if (usData.trailer != NULL)
	{
		set_datagram_T(packet , 1);
		set_datagram_dataup_trailer(packet , usData.trailer);
	}
	return packet;
}

void print_usData (uint8_t* packet)
{
	printf ("type : %i \n\r" , get_datagram_type(packet));
	printf ("qos : %i \n\r" , get_datagram_QoS(packet));
	printf ("address : %x \n\r" , get_datagram_address(packet));
	printf ("payload length : %x \n\r" , get_datagram_dataup_len_payload(packet));
	printf ("payload : ");
	print_payload(get_datagram_dataup_payload(packet) , get_datagram_dataup_len_payload(packet) , 0);
	printf("\n\r");
}


//-------------------------------------------------------------------------------------

uint8_t* build_dsData (dsData_typedef dsData , int* datagram_length)
{
	*datagram_length = DATAGRAM_DATADOWN_HEADER_LEN_BYTE +(int)dsData.payload_length;

	if (dsData.trailer != NULL)
	{
		*datagram_length += TRAILER_LEN_BYTE;
	}

	uint8_t* packet = (uint8_t*)malloc(sizeof(uint8_t)*(*datagram_length));

	set_datagram_type(packet , DATA_DOWN);
	set_datagram_QoS(packet , dsData.qos);
	set_datagram_address(packet, dsData.address);
	set_datagram_datadown_ds_path_length(packet , dsData.ds_path_length);
	set_datagram_datadown_hop_count(packet , dsData.ds_path_length);

	if (dsData.ds_path != NULL) set_datagram_datadown_ds_path(packet , dsData.ds_path);

	set_datagram_datadown_len_payload(packet , dsData.payload_length);
	set_datagram_datadown_payload(packet , dsData.payload);

	if (dsData.trailer != NULL)
	{
		set_datagram_T(packet , 1);
		set_datagram_datadown_trailer(packet , dsData.trailer);
	}

	return packet;
}

uint8_t* modify_dsData (uint8_t* dsData)
{
	datagram_datadown_hop_count_t tmp = get_datagram_datadown_hop_count(dsData);
	tmp--;
	set_datagram_datadown_hop_count(dsData , tmp);

	return dsData;
}

void print_dsData (uint8_t* packet)
{
	printf ("type : %i \n\r" , get_datagram_type(packet));
	printf ("qos : %i \n\r" , get_datagram_QoS(packet));
	printf ("address : %x \n\r" , get_datagram_address(packet));
	printf ("payload length : %i \n\r" , get_datagram_datadown_len_payload(packet));
	printf ("payload : ");
	print_payload(get_datagram_datadown_payload(packet), get_datagram_datadown_len_payload(packet), 0);
	printf("\n\r");
	printf ("path list length : %i \n\r" , get_datagram_datadown_ds_path_length(packet));
	printf ("hop count : %i \n\r" , get_datagram_datadown_hop_count(packet));


	if(get_datagram_datadown_ds_path_length(packet) != 0)
	{
		int i;

		printf("hop list\n\r");
		for (i = 0 ; i < get_datagram_datadown_ds_path_length(packet); i++)
		{
			printf(" hop[%i] %x\n\r " , i , get_datagram_datadown_hop_if(packet , i));
		}
	} else {
		printf("Nessuna hop list\n\r");
	}


}


//-------------------------------------------------------------------------------------

uint8_t* build_PREQ (PREQ_typedef preq , int* datagram_length)
{
	usData_typedef data;
	data.payload_length = CHALLENGE_LEN_BYTE;
	data.payload = preq.challenge;
	data.qos = CONTROL;
	data.trailer = NULL;

	uint8_t* packet = build_usData(data , datagram_length);
	set_datagram_type(packet , BSRP_PREQ);
	set_datagram_address(packet, MY_ADDRESS);

	return packet;
}

void print_PREQ (uint8_t* packet)
{
	print_usData(packet);
}


//-------------------------------------------------------------------------------------

uint8_t* build_PFWD (PFWD_typedef pfwd, datagram_address_t source_address, int* datagram_length)
{
	*datagram_length = DATAGRAM_PFWD_HEADER_LEN_BYTE + CHALLENGE_LEN_BYTE;

	uint8_t* packet = (uint8_t*)malloc(sizeof(uint8_t)*(*datagram_length));
//
	set_datagram_T(packet , 0);
	set_datagram_type(packet , BSRP_PFWD);
	set_datagram_QoS(packet , CONTROL);
	set_datagram_address(packet , source_address);
	set_datagram_pfwd_hop_list_length(packet, 0);
	set_datagram_pfwd_challenge(packet, pfwd.challenge);

	int i;
	for (i=0 ; i < MAX_HOP_COUNT ; i++)
	{
		set_datagram_pfwd_hop_if(packet , i , 0);
		set_datagram_pfwd_hop_address(packet , i , 0);
	}

	return packet;

}

void modify_PFWD (uint8_t* pfwd , datagram_hop_if_t hop)
{
	uint8_t i = get_datagram_pfwd_hop_list_length(pfwd);
	set_datagram_pfwd_hop_if(pfwd , i , hop);
	set_datagram_pfwd_hop_address(pfwd , i , MY_ADDRESS);

	i++;
	set_datagram_pfwd_hop_list_length(pfwd , i);


}

void print_PFWD (uint8_t* pfwd)
{
	printf ("type : %i \n\r" , get_datagram_type(pfwd));
	printf ("qos : %i \n\r" , get_datagram_QoS(pfwd));
	printf ("address : %x \n\r" , get_datagram_address(pfwd));
	printf ("payload : ");
	print_payload(get_datagram_pfwd_challenge(pfwd), CHALLENGE_LEN_BYTE, 0);
	printf("\n\r");
	printf ("hop_list length: %i \n\r" , get_datagram_pfwd_hop_list_length(pfwd));

	if(get_datagram_pfwd_hop_list_length(pfwd) != 0)
	{
		int i;

		printf("hop list\n\r");
		for (i = 0 ; i < get_datagram_pfwd_hop_list_length(pfwd); i++)
		{
			printf(" hop[%i] %x - address[%i] %x\n\r " , i , get_datagram_pfwd_hop_if(pfwd , i),
														 i , get_datagram_pfwd_hop_address(pfwd , i));
		}
	} else {
		printf("Nessuna hop list\n\r");
	}
}


//-------------------------------------------------------------------------------------

uint8_t* build_PREP (PREP_typedef prep, int* datagram_length)
{

	uint8_t* packet = build_dsData ((dsData_typedef)prep , datagram_length);
	set_datagram_QoS(packet , CONTROL);
	set_datagram_type(packet , BSRP_PREP);


	return packet;

}

/**
 *
 * TODO NON TESTATAAAAA
 */
uint8_t* build_PREP_from_PFWD(uint8_t* packet,  datagram_hop_if_t source_if , int* length , uint8_t* secret , uint8_t* trailer)
{
	/*modify_PFWD (packet, source_if);

	PREP_typedef prep;
	prep.address = get_datagram_address(packet);
	prep.ds_path_length = get_datagram_pfwd_hop_list_length(packet);
	prep.payload = secret;
	prep.payload_length = SECRET_LEN_BYTE;
	prep.qos = CONTROL;
	prep.trailer = trailer;

	uint8_t* out = build_PREP(prep , length);

	int i;
	for (i=0 ; i < prep.ds_path_length ; i++)
	{
		set_datagram_datadown_hop_if(out , i , get_datagram_pfwd_hop_if(packet , i));

	}

	return out;*/
	modify_PFWD (packet, source_if);

	PREP_typedef prep;
	prep.address = get_datagram_address(packet);
	prep.ds_path_length = get_datagram_pfwd_hop_list_length(packet);
	prep.payload = secret;
	prep.payload_length = SECRET_LEN_BYTE;
	prep.qos = CONTROL;
	prep.trailer = trailer;

	//for(int i=0;i)

	int i;
	uint8_t sfaccimm[prep.ds_path_length];

	for (i=0 ; i < prep.ds_path_length ; i++)
	{
		sfaccimm[i] =  get_datagram_pfwd_hop_if(packet , i);

	}
	prep.ds_path = sfaccimm;

	uint8_t* out = build_PREP(prep , length);



	return out;
}

void print_PREP (uint8_t* prep)
{
	print_dsData(prep);
}

void modify_PREP (uint8_t* prep) {
	modify_dsData(prep);
}
//-------------------------------------------------------------------------------------

uint8_t* build_PFWD_from_PREQ (uint8_t* preq , datagram_hop_if_t first_hop , int* datagram_length)
{


	PFWD_typedef pfwd;
	pfwd.challenge = get_datagram_dataup_payload(preq);

	uint8_t* packet = build_PFWD(pfwd , get_datagram_address(preq) , datagram_length);
	modify_PFWD(packet, first_hop);

	return packet;

}

void print_payload(uint8_t const* payload , int payload_length , int exadecimal)
{
	int i;

	if (exadecimal !=0)
	{
		printf("payload: %s\n\r" , (char*)payload);
		return;
	}

	for (i = 0 ; i < payload_length ; i++)
	{
		printf("%x " , payload[i]);
	}

	printf("\n\r");
}
