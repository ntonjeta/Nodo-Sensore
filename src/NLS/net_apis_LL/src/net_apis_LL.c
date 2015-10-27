/*
 * net_apis_LL.c

 *
 *  Created on: 12/lug/2015
 *      Author: gennaro
 */

#include "net_apis_LL.h"
#include "NLS_globals.h"
#include "net_apis_RTOS.h"

struct NLS_HandleTypedef hNLS;

uint8_t isIfEnabled (uint8_t ifx)
{
	return (hNLS.enabled_ifs &  (1<< ifx)) != 0;
}

/**
 * @addtogroup	NET_APIS Low Level
 * @{
 */

/** @defgroup Implementazione callback NLS_LL
 * @{
 */

void NLS_LL_enable_if (struct NLS_HandleTypedef* hNLS , uint8_t _if)
{
	enableInterface(_if);
	hNLS->enabled_ifs |= (1 << _if);
	hNLS->enabled_ifs_num++;
}

void NLS_LL_received_datagram (struct NLS_HandleTypedef* hNLS_ , datagram_info* d_info)
{
	xQueueSendFromISR(hNLS_->event_queue, (void*)&d_info,  NULL);
}

void NLS_LL_init (struct NLS_HandleTypedef* hNLS)
{
	calInit();

	//TODO abilitare tutte le interfacce

}

void NLS_LL_deinit (struct NLS_HandleTypedef* hNLS)
{
}

NLS_sendStatus NLS_LL_sendPacketTo(CAL_InterfaceNumber ifx, uint8_t *packet, uint16_t packetLength, uint8_t numRetry)
{
	if( isIfEnabled(ifx))
	{
		sendPacketTo(ifx , packet , packetLength , numRetry);

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "NLS_LL_sendPacketTo()",
		//							LOG_STRING, "sent packet", "OK",
		//							LOG_END);

		return SENT;
	}
	else
	{

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, ERROR, MY_ADDRESS, "NLS_LL_sendPacketTo()",
		//							LOG_STRING, "sent packet", "FALLITO",
		//							LOG_STRING, "interfaccia" "NON ALIBLITATA",
		//							LOG_END);

		return NOT_SENT;
	}
}

NLS_sendStatus NLS_LL_sendPacketMulticast(CAL_InterfaceNumber *ifxVector, uint8_t ifxVettLength, uint8_t *packet, uint16_t packetLength, uint8_t numRetry)
{
	int i;
	for (i = 0 ; i < ifxVettLength ; i++)
	{
		if( !isIfEnabled(ifxVector[i]) )
		{

			//TODO Log
			//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, ERROR, MY_ADDRESS, "NLS_LL_sendPacketMulticast()",
			//							LOG_STRING, "sent packet MULTICAST", "FALLITO",
			//							LOG_END);

			return NOT_SENT;
		}

	}

	//TODO Log
	//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "NLS_LL_sendPacketMulticast()",
	//							LOG_STRING, "sent packet MULTICAST", "OK",
	//							LOG_END);

	sendPacketMulticast(ifxVector , ifxVettLength , packet , packetLength , numRetry);
	return SENT;



}

NLS_sendStatus NLS_LL_sendPacketBroadcast(uint8_t *packet, uint16_t packetLength, uint8_t numRetry)
{
	//	uint16_t tmp = hNLS.enabled_ifs;
	//	CAL_InterfaceNumber ifxs[hNLS.enabled_ifs_num];
	//	int i , j = 0;
	//	for (i = 0 ; i < 16 ; i++)
	//	{
	//		if(( (tmp >> i) & 1)  == 1)
	//		{
	//			ifxs[j] = i;
	//			j++;
	//		}
	//	}

	//	sendPacketMulticast(ifxs, (hNLS.enabled_ifs_num)-1 , packet, packetLength, numRetry);
	sendPacketBroadcast(packet , packetLength , numRetry);

	//TODO Log
	//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "NLS_LL_sendPacketBroadcast()",
	//							LOG_STRING, "sent packet BROADCAST", "OK",
	//							LOG_END);

	return SENT;
}



/** @defgroup Implementazione callback CARL
 * @{
 */
void interfaceAttachedCallback(CAL_InterfaceNumber ifx)
{

}

void interfaceDetachedCallback(CAL_InterfaceNumber ifx)
{

}

void sentPacketCallback(CAL_InterfaceNumber ifx, uint8_t *packet, uint16_t packetLength)
{
#ifdef NLS_TRACE
	printf("pacchetto inviato su interfaccia %i\n\r" , ifx);
#endif

	//TODO Log
	//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "sentPacketCallback()",
	//							LOG_INT, "sent packet callback interfaccia", ifx,
	//							LOG_END);


//	if(get_datagram_type(packet)==DATA_UP){
//		printf("MESSAGGIO INVIATO DATA UP\n\r");
//		print_usData(packet);
//		printf("==========================\n\r");
//	}
//
//	else{
//		printf("MESSAGGIO INVIATO\n\r");
//		printf("tipo: %d \n\r",get_datagram_type(packet));
//		printf("indirizzo: %x\n\r",get_datagram_address(packet));
//		printf("interfaccia: %d \n\r",ifx);
//		printf("======================\n\r");
//	}
}

	void receivedPacketCallback(CAL_InterfaceNumber ifx, uint8_t* packet, uint16_t packetLength)
	{
#ifdef NLS_TRACE

		printf("receivedPacketCallback\n\r");
#endif

		datagram_info* d_info = init_datagram_info(packet, ifx, packetLength, 0);
		NLS_LL_received_datagram( &hNLS , d_info);

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "receivedPacketCallback()",
		//							LOG_INT, "received packet callback interfaccia", ifx,
		//							LOG_INT, "if source", d_info->source_if,
		//							LOG_INT, "datagram type", d_info->type,
		//							LOG_INT, "packet length", d_info->packet_length,
		//							LOG_INT, "address", d_info->address,
		//							LOG_END);

//		datagram_info stampatore;
//		stampatore.packet=packet;
//		stampatore.source_if=ifx;
//		stampatore.packet_length=packetLength;
//		if(get_datagram_type(packet)==DATA_UP){
//			printf("MESSAGGIO RICEVUTO DATA UP\n\r");
//			print_usData(packet);
//			printf("==========================\n\r");
//		}
//
//		else{
//
//			printf("MESSAGGIO RICEVUTO\n\r");
//			printf("tipo: %d \n\r",get_datagram_type(stampatore.packet));
//			printf("indirizzo: %x\n\r",get_datagram_address(stampatore.packet));
//			printf("interfaccia: %d \n\r",ifx);
//			printf("======================\n\r");
//		}
	}

	void sendErrorCallback(CAL_InterfaceNumber ifx, uint8_t* packet,uint16_t packetLength)
	{
#ifdef NLS_TRACE

		printf("sendErrorCallback interfaccia = %d \n\r",ifx);
#endif

		printf("Errore invio interfaccia = %d \n\r",ifx);
		datagram_info* d_info = init_datagram_info(packet, NO_SRC_IF, packetLength, 1);
		NLS_LL_received_datagram(&hNLS , d_info);

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, WARNING, MY_ADDRESS, "sendErrorCallback()",
		//							LOG_INT, "send error callback interfaccia", ifx,
		//							LOG_INT, "if source", d_info->source_if,
		//							LOG_INT, "datagram type", d_info->type,
		//							LOG_INT, "packet length", d_info->packet_length,
		//							LOG_INT, "address", d_info->address,
		//							LOG_END);

	}


