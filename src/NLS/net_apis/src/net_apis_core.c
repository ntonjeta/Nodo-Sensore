///*
// * net_apis_core.c
// *
// *  Created on: 05/lug/2015
// *      Author: gennaro
// */
//
//#include "net_apis_core.h"
//#include "net_apis.h"
//#include "net_apis_usr.h"
//#include "NLS_globals.h"
//
//#ifndef ROOT
///**
// * @brief primitiva di invio dati in upstrem
// * @param [in] hNLS , handler dell'istanza NLS
// * @param [in] d_info struttura informazioni del datagramma
// */
//uint8_t send_upstream (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
//{
//
//	uint8_t main_link = UTGetMainLink(hNLS->uTable);
//
//#	ifdef NLS_TRACE
//	printf("===============================\n\r");
//	printf("SEND_UPSTREAM\n\r");
//	//print_datagram_info(d_info);
//	printf("\n\r");	//TODO: Controllare
//#	endif
//
//	if (main_link ==  MAIN_LINK_DOES_NOT_EXIST) //XXX CAMBIARE
//	{
//#		ifdef NLS_TRACE
//		printf("Main Link inesistente -> Invio fallito!\n\r");
//#		endif
//
//		free_datagram_info(d_info);
//		return FAIL_SND;
//	}
//
//	sendPacketTo((CAL_InterfaceNumber)main_link , d_info->packet , d_info->packet_length , UPSTREAM_SND_RETRY);
//
//#	ifdef NLS_TRACE
//	printf("Invio effettuato con successo!\n\r");
//	printf("===============================\n\r");
//#	endif
//
//	free_datagram_info(d_info);
//
//	return OK_SND;
//}
//#endif
///**
// * @brief primitiva invocata per inviare un pacchetto in direzione downstream
// * @param [in] hNLS , handler dell'istanza NLS
// * @param [in] d_info struttura informazioni del datagramma
// */
//
//uint8_t send_downstream (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
//{
//
//#	ifdef NLS_TRACE
//	printf("===============================\n\r");
//	printf("SEND_DOWNSTREAM\n\r");
//	print_datagram_info(d_info);
//
//	printf("invia su interfaccia %i" , (CAL_InterfaceNumber)get_datagram_datadown_next_hop_if(d_info->packet));
//	printf("\n\r");	//TODO: Controllare
//#	endif
//
//	modify_dsData(d_info->packet);
//	uint8_t dest_if = get_datagram_datadown_hop_count(d_info->packet);
//
//	sendPacketTo((CAL_InterfaceNumber)get_datagram_datadown_hop_if(d_info->packet , dest_if) , d_info->packet , d_info->packet_length  , DOWNSTREAM_SND_RETRY);
//
//	free_datagram_info(d_info);
//
//#	ifdef NLS_TRACE
//	printf("Invio effettuato con successo!\n\r");
//	printf("===============================\n\r");
//#	endif
//
//	return 0;
//}
//
//void forward(struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
//{
//
//	//XXX PAOLO FORWARD
//	uint16_t tmp = hNLS->enabled_ifs;
//	tmp &= ~(1 << d_info->source_if);
//	CAL_InterfaceNumber ifxs[hNLS->enabled_ifs_num-1];
//	int i , j = 0;
//	for (i = 0 ; i < 16 ; i++)
//	{
//		if(( (tmp >> i) & 1)  == 1)
//		{
//			ifxs[j] = i;
//			j++;
//		}
//	}
//	//uint8_t point;
//	//point=0;
//#	ifdef NLS_TRACE
//	printf("===============================\n\r");
//	printf("FORWARD\n\r");
//	print_datagram_info(d_info);
//#	endif
//
//	sendPacketMulticast(ifxs, (hNLS->enabled_ifs_num)-1 , d_info->packet, d_info->packet_length, 0);
//	//sendPacketMulticast(&point, 1 , d_info->packet, d_info->packet_length, 0);
//	free_datagram_info(d_info);
//
//#	ifdef NLS_TRACE
//	printf("Invio effettuato con successo!\n\r");
//	printf("===============================\n\r");
//#	endif
//
//
//}
//
//void broadcast(datagram_info* d_info)
//{
//#	ifdef NLS_TRACE
//	printf("===============================\n\r");
//	printf("BROADCAST\n\r");
//	print_datagram_info(d_info);
//#	endif
//	sendPacketBroadcast(d_info->packet , d_info->packet_length , 1);
//	free_datagram_info(d_info);
//
//#	ifdef NLS_TRACE
//	printf("Invio effettuato con successo!\n\r");
//	printf("===============================\n\r");
//#	endif
//
//}
//
//void throw_back(datagram_info* d_info)
//{
//#	ifdef NLS_TRACE
//	printf("===============================\n\r");
//	printf("THROW BACK\n\r");
//	print_datagram_info(d_info);
//
//	printf("invia su interfaccia %i" , d_info->source_if);
//	printf("\n\r");	//TODO: Controllare
//#	endif
//
//	sendPacketTo(d_info->source_if , d_info->packet , d_info->packet_length , DOWNSTREAM_SND_RETRY);
//
//#	ifdef NLS_TRACE
//	printf("Invio effettuato con successo!\n\r");
//	printf("===============================\n\r");
//#	endif
//}
//
//void enable_if (struct NLS_HandleTypedef* hNLS , uint8_t _if)
//{
//	enableInterface(_if);
//	hNLS->enabled_ifs |= 1 << _if;
//	hNLS->enabled_ifs_num++;
//}
//
//uint8_t* trailer_gen(uint8_t* packet , uint8_t length)
//{
//	uint8_t hc = 0;
//	if(get_datagram_type(packet) == DATA_DOWN)
//	{
//		hc = get_datagram_datadown_hop_count(packet);
//		set_datagram_datadown_hop_count(packet , 0);
//	}
//
//	uint8_t* out = on_USR_trailer_gen(packet , length);
//	if(get_datagram_type(packet) == DATA_DOWN)set_datagram_datadown_hop_count(packet , hc);
//
//	return out;
//
//
//
//
//}
//
//
//
////=================================================================================================
///**
// * @brief funzione chiamata alla ricezione di ogni datagramma. invoca la USR_datagram_check
// * utilizzata per implementare controlli di integrita. Poich� il protocollo prevede che l'unico messaggio
// * firmato con campi mutevoli hop per hop e il datagramma DOWNSTREAM, il campo mutevole (ossia hop count)
// * viene azzerato prima di passare alla callback utente e poi ripristinato. in questo modo non � necessario
// * ricalcolare la firma ad ogni ricezione, sebbene non verr� garantita l'integrit� su tale campo
// *
// * TODO inserire flag per decidere se la firma deve essere ricalcolata dopo il check
// *
// * @param [in] d_info struttura informmazioni del datagramma
// *
// * @retval stato del controllo
// */
//check_status on_datagram_check(datagram_info* d_info)
//{
//	uint8_t hc;
//
//	if(d_info->type == DATA_DOWN)
//	{
//		hc = get_datagram_datadown_hop_count(d_info->packet);
//		set_datagram_datadown_hop_count(d_info->packet , 0);
//	}
//	check_status s = on_USR_datagram_check(getTrailer(d_info->packet));
//
//	if (s == CHECK_FAILED)
//	{
//		free_datagram_info(d_info);
//	}
//	else
//	{
//		if(d_info->type == DATA_DOWN)set_datagram_datadown_hop_count(d_info->packet , hc);
//
//	}
//
//	return s;
//}
//
//
//
//void on_datagram_received(datagram_info* d_info)
//{
//	uint8_t payload_len = 0;
//
//	if(d_info->type == DATA_UP)
//	{
//		payload_len = (uint8_t)get_datagram_dataup_len_payload(d_info->packet);
//	}
//	else if(d_info->type == DATA_DOWN)
//	{
//		payload_len = (uint8_t)get_datagram_datadown_len_payload(d_info->packet);
//	}
//
//	uint8_t* payload = malloc(sizeof(uint8_t)*payload_len);
////	memcpy(payload , d_info->packet , payload_len);
//
//	if(d_info->type == DATA_UP)
//	{
//		memcpy(payload , get_datagram_dataup_payload(d_info->packet) , payload_len);
//	}
//	else if(d_info->type == DATA_DOWN)
//	{
//		memcpy(payload , get_datagram_datadown_payload(d_info->packet) , payload_len);
//	}
//
//	on_USR_datagram_received(payload , payload_len , d_info->address);
//
//	free_datagram_info(d_info);
//}
//
///**
// * prende come parametro le info del pacchetto che ha scatenato la path discovery
// */
//challenge_t on_path_discovery(struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
//{
//	int preq_length;
//	PREQ_typedef preq;
//	preq.challenge = on_USR_path_discovery();
//
//	uint8_t* packet = build_PREQ(preq , &preq_length);
//
//	free(preq.challenge);
//
//
//	//se la path disocery avviene a seguito di una preq, non rimando indietro la mia preq
//	if(d_info->type == BSRP_PREQ)
//	{
//		forward(hNLS , init_datagram_info(packet , d_info->source_if , preq_length, 0));
//	}
//	else
//	{
//		broadcast(init_datagram_info(packet , NO_SRC_IF , preq_length, 0));
//
//	}
//
//
//	return 0;
//}
//
//void on_PREQ (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
//{
//#ifdef ROOT
//	int prep_len;
//
//	uint8_t* secret = on_USR_PREQ(get_datagram_dataup_payload(d_info->packet));
//	secret[0]=0x22;
//	secret[1]=0x24;
//
//	if (secret != NULL)
//	{
//		d_info->packet = build_PREP_from_PREQ(d_info->packet, &prep_len , secret , trailer_gen(d_info->packet , d_info->packet_length-TRAILER_LEN_BYTE));
//		d_info->packet_length = prep_len;
//
//		uint8_t path_len = 1;
//		uint8_t path[1] = {d_info->source_if};
//
//		uint8_t prova[1];
//		//li salvo nella ds table
//		downStreamTableInsert(hNLS->dTable , d_info->address , path , path_len , 0);
//
//
//		throw_back(d_info);
//		free(secret);
//	}
//
//	free_datagram_info(d_info);
//
//#else
//	int len;
//	uint8_t* pfwd;
//	pfwd = build_PFWD_from_PREQ(d_info->packet,d_info->source_if,&len);
//	send_upstream(hNLS,init_datagram_info(pfwd,d_info->source_if,len, 0));
//#endif
//}
//
//void on_PFWD (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
//{
//#ifdef ROOT
//	int prep_len;
//
//	uint8_t* secret = on_USR_PREQ(get_datagram_dataup_payload(d_info->packet));
//
//	if (secret != NULL)
//	{
//		uint8_t* prep = build_PREP_from_PFWD(d_info->packet, d_info->source_if , &prep_len , secret , trailer_gen(d_info->packet , d_info->packet_length-TRAILER_LEN_BYTE));
//		//estraggo ds path e ds path length
//		int i;
//		uint8_t path_len = get_datagram_datadown_ds_path_length(prep);
//		uint8_t path[path_len];
//
//		for (i = 0 ; i < path_len ; i++)
//		{
//			path[i] = get_datagram_datadown_hop_if(prep , i);
//		}
//
//
//		//li salvo nella ds table
//		downStreamTableInsert(hNLS->dTable , d_info->address , path , path_len , 0);
//		//downstreamTableGetBestPath(hNLS->dTable , d_info->address , patate , &path_len);
//		//printf("TEST INSERT DOWNTABLE path[0] : %d path[1] : %d\n\r", patate[0], patate[1]);
////		printf("INSERISCO IL PATH DI LUNGHEZZA %d per %x \n\r",path_len,d_info->address);
////		for(int i=0;i<path_len;i++)
////			printf("Interfaccia %d : %d\n\r",i,path[i]);
//		//costruisco una PREP
//
//		on_USR_path_discovered_root(d_info->address ,  path , path_len);
//
//		//la invio
////		sendPacketTo(d_info->source_if , prep , prep_len , 1);
//		send_downstream(hNLS,init_datagram_info(prep,d_info->source_if,prep_len, 0));
//		free(secret);
//		free(prep);
//	}
//
//	free_datagram_info(d_info);
//
//#else
//
//	//se nella pfwd c'� il mio indirizzo, sto ricevendo una pfwd generata da me, e qua � fatt e loop
//	if (get_datagram_address(d_info->packet) == MY_ADDRESS )
//	{
//		free_datagram_info(d_info);
//		return;
//	}
//
//	//elimino un padre presente nella hop list per evitare loop
//	//UTFilter(hNLS->uTable , get_datagram_pfwd_hop_list_length(d_info->packet) , get_datagram_pfwd_hop_list_length(d_info->packet));
//
//	modify_PFWD(d_info->packet , d_info->source_if);
//
//#ifdef NLS_TRACE
//	printf("inoltro una PFWD");
//	print_PFWD(d_info->packet);
//#endif
//
//	send_upstream(hNLS , d_info);
//#endif
//}
//
//void on_PREP (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
//{
//#ifdef ROOT
//	//non previsto. fai qualcosa che dica alla rete che stanno for ca cap
//#else
//
//	on_USR_path_discovered ();
//	UTInsertEntry(hNLS->uTable , d_info->source_if , get_datagram_datadown_ds_path_length(d_info->packet) , d_info->address);
//
//	PACK_typedef pack;
//	pack.secret = on_USR_PREP(d_info->packet , d_info->packet_length);
//	pack.trailer = on_USR_trailer_gen(d_info->packet , d_info->packet_length-TRAILER_LEN_BYTE);
//
//#endif
//
//}
//
///**
// * funzione da chiamare nella callback di invio fallito
// */
//void on_send_fail (struct NLS_HandleTypedef* hNLS)
//{
//	//qui penalizzo solo il main link, ma il pacchetto da reinviare viene comunque accodato
//#ifndef ROOT
//	UTSwapMainLink(hNLS->uTable);
//#endif
//}
//
//void on_PACK (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
//{
//#ifdef ROOT
//
//	on_USR_PACK_check(get_datagram_dataup_payload(d_info->packet) , get_datagram_dataup_len_payload(d_info->packet) );
//
//#else
//
//	send_upstream(hNLS , d_info);
//#endif
//}
//
//
////==============================================================================================

/*
 * net_apis_core.c
 *
 *  Created on: 05/lug/2015
 *      Author: gennaro
 */

#include "net_apis_core.h"
#include "net_apis.h"
#include "net_apis_usr.h"
#include "net_apis_LL.h"
#include "NLS_globals.h"
#include "net_apis_RTOS.h"

#ifndef ROOT
/**
 * @brief primitiva di invio dati in upstrem
 * @param [in] hNLS , handler dell'istanza NLS
 * @param [in] d_info struttura informazioni del datagramma
 */
uint8_t send_upstream (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
{

	uint8_t main_link = UTGetMainLink(hNLS->uTable);

#	ifdef NLS_TRACE
	printf("===============================\n\r");
	printf("SEND_UPSTREAM\n\r");
	//print_datagram_info(d_info);
	printf("\n\r");	//TODO: Controllare

#	endif

	if (main_link ==  UPSTREAM_TABLE_IS_EMPTY) //XXX CAMBIARE
	{
#		ifdef NLS_TRACE
		printf("Main Link inesistente -> Invio fallito!\n\r");

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, ERROR, MY_ADDRESS, "send_upstream()",
		//							LOG_STRING, "send UPSTREAM", "FALLITO",
		//							LOG_STRING, "main link" "INESISTENTE",
		//							LOG_END);

#		endif

		free_datagram_info(d_info);
		return FAIL_SND;
	}

	NLS_LL_sendPacketTo((CAL_InterfaceNumber)main_link , d_info->packet , d_info->packet_length , UPSTREAM_SND_RETRY);

#	ifdef NLS_TRACE
	printf("Invio effettuato con successo!\n\r");
	printf("===============================\n\r");
#	endif

	//TODO Log
	//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "send_upstream()",
	//							LOG_STRING, "send UPSTREAM", "OK",
	//							LOG_INT, "if source", d_info->source_if,
	//							LOG_INT, "datagram type", d_info->type,
	//							LOG_INT, "packet length", d_info->packet_length,
	//							LOG_INT, "address", d_info->address,
	//							LOG_END);

	free_datagram_info(d_info);

	return OK_SND;
}
#endif
/**
 * @brief primitiva invocata per inviare un pacchetto in direzione downstream
 * @param [in] hNLS , handler dell'istanza NLS
 * @param [in] d_info struttura informazioni del datagramma
 */

uint8_t send_downstream (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
{

#	ifdef NLS_TRACE
	printf("===============================\n\r");
	printf("SEND_DOWNSTREAM\n\r");
	print_datagram_info(d_info);

	printf("invia su interfaccia %i" , (CAL_InterfaceNumber)get_datagram_datadown_next_hop_if(d_info->packet));
	printf("\n\r");	//TODO: Controllare
#	endif

	modify_dsData(d_info->packet);
	uint8_t dest_if = get_datagram_datadown_hop_count(d_info->packet);

	//TODO Log
	//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "send_downstream()",
	//							LOG_STRING, "send DOWNSTREAM", "OK",
	//							LOG_INT, "if source", d_info->source_if,
	//							LOG_INT, "datagram type", d_info->type,
	//							LOG_INT, "packet length", d_info->packet_length,
	//							LOG_INT, "address", d_info->address,
	//							LOG_END);

	NLS_LL_sendPacketTo((CAL_InterfaceNumber)get_datagram_datadown_hop_if(d_info->packet , dest_if) , d_info->packet , d_info->packet_length  , DOWNSTREAM_SND_RETRY);

	free_datagram_info(d_info);

#	ifdef NLS_TRACE
	printf("Invio effettuato con successo!\n\r");
	printf("===============================\n\r");
#	endif

	return 0;
}

NLS_sendStatus forward(struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
{

	NLS_sendStatus result = NOT_SENT;


	if (hNLS->enabled_ifs_num != 1)
	{
		//XXX PAOLO FORWARD
		uint16_t tmp = hNLS->enabled_ifs;
		tmp &= ~(1 << d_info->source_if);
		CAL_InterfaceNumber ifxs[hNLS->enabled_ifs_num-1];
		int i , j = 0;
		for (i = 0 ; i < 16 ; i++)
		{
			if(( (tmp >> i) & 1)  == 1)
			{
				ifxs[j] = i;
				j++;
			}
		}

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "forward()",
		//							LOG_STRING, "send FORWARD", "OK",
		//							LOG_INT, "if source", d_info->source_if,
		//							LOG_INT, "datagram type", d_info->type,
		//							LOG_INT, "packet length", d_info->packet_length,
		//							LOG_INT, "address", d_info->address,
		//							LOG_END);

		NLS_LL_sendPacketMulticast(ifxs, (hNLS->enabled_ifs_num)-1 , d_info->packet, d_info->packet_length, 0);

		result = SENT;
	}
	//uint8_t point;
	//point=0;
#	ifdef NLS_TRACE
	printf("===============================\n\r");
	printf("FORWARD\n\r");
	print_datagram_info(d_info);
#	endif

	free_datagram_info(d_info);

#	ifdef NLS_TRACE
	printf("Invio effettuato con successo!\n\r");
	printf("===============================\n\r");
#	endif


	return result;
}

void broadcast(datagram_info* d_info)
{
#	ifdef NLS_TRACE
	printf("===============================\n\r");
	printf("BROADCAST\n\r");
	print_datagram_info(d_info);
#	endif

	//TODO Log
	//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "broadcast()",
	//							LOG_STRING, "send BROADCAST", "OK",
	//							LOG_INT, "if source", d_info->source_if,
	//							LOG_INT, "datagram type", d_info->type,
	//							LOG_INT, "packet length", d_info->packet_length,
	//							LOG_INT, "address", d_info->address,
	//							LOG_END);

	NLS_LL_sendPacketBroadcast(d_info->packet , d_info->packet_length , 1);
	free_datagram_info(d_info);

#	ifdef NLS_TRACE
	printf("Invio effettuato con successo!\n\r");
	printf("===============================\n\r");
#	endif

}

void throw_back(datagram_info* d_info)
{
#	ifdef NLS_TRACE
	printf("===============================\n\r");
	printf("THROW BACK\n\r");
	print_datagram_info(d_info);

	printf("invia su interfaccia %i" , d_info->source_if);
	printf("\n\r");	//TODO: Controllare
#	endif

	//TODO Log
	//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "throw_back()",
	//							LOG_STRING, "send THROW BACK", "OK",
	//							LOG_INT, "if source", d_info->source_if,
	//							LOG_INT, "datagram type", d_info->type,
	//							LOG_INT, "packet length", d_info->packet_length,
	//							LOG_INT, "address", d_info->address,
	//							LOG_END);

	NLS_LL_sendPacketTo(d_info->source_if , d_info->packet , d_info->packet_length , DOWNSTREAM_SND_RETRY);

#	ifdef NLS_TRACE
	printf("Invio effettuato con successo!\n\r");
	printf("===============================\n\r");
#	endif
}



uint8_t* trailer_gen(uint8_t* packet , uint8_t length)
{
	uint8_t hc;
	if(get_datagram_type(packet) == DATA_DOWN)
	{
		hc = get_datagram_datadown_hop_count(packet);
		set_datagram_datadown_hop_count(packet , 0);

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "trailer_gen()",
		//							LOG_INT, "hop count", 0,
		//							LOG_END);

	}

	uint8_t* out = on_USR_trailer_gen(packet , length);
	if(get_datagram_type(packet) == DATA_DOWN)set_datagram_datadown_hop_count(packet , hc);

	//TODO Log
	//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "trailer_gen()",
	//							LOG_STRING, "trailer generation", "OK",
	//							LOG_INT, "hop count", hc,
	//							LOG_END);

	return out;




}



//=================================================================================================
/**
 * @brief funzione chiamata alla ricezione di ogni datagramma. invoca la USR_datagram_check
 * utilizzata per implementare controlli di integrita. Poich� il protocollo prevede che l'unico messaggio
 * firmato con campi mutevoli hop per hop e il datagramma DOWNSTREAM, il campo mutevole (ossia hop count)
 * viene azzerato prima di passare alla callback utente e poi ripristinato. in questo modo non � necessario
 * ricalcolare la firma ad ogni ricezione, sebbene non verr� garantita l'integrit� su tale campo
 *
 * TODO inserire flag per decidere se la firma deve essere ricalcolata dopo il check
 *
 * @param [in] d_info struttura informmazioni del datagramma
 *
 * @retval stato del controllo
 */
check_status on_datagram_check(datagram_info* d_info)
{
	uint8_t hc;

	if(d_info->type == DATA_DOWN)
	{
		hc = get_datagram_datadown_hop_count(d_info->packet);
		set_datagram_datadown_hop_count(d_info->packet , 0);
	}
	check_status s = on_USR_datagram_check(getTrailer(d_info->packet));

	if (s == CHECK_FAILED)
	{

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, ERROR, MY_ADDRESS, "on_datagram_check()",
		//							LOG_STRING, "check del datagram", "FALLITO",
		//							LOG_END);

		free_datagram_info(d_info);
	}
	else
	{
		if(d_info->type == DATA_DOWN)set_datagram_datadown_hop_count(d_info->packet , hc);

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "on_datagram_check()",
		//							LOG_STRING, "check del datagram", "OK",
		//							LOG_INT, "if source", d_info->source_if,
		//							LOG_INT, "datagram type", d_info->type,
		//							LOG_INT, "packet length", d_info->packet_length,
		//							LOG_INT, "address", d_info->address,
		//							LOG_END);

	}

	return s;
}



void on_datagram_received(datagram_info* d_info)
{
	uint8_t payload_len = 0;

	if(d_info->type == DATA_UP)
	{
		payload_len = (uint8_t)get_datagram_dataup_len_payload(d_info->packet);
	}
	else if(d_info->type == DATA_DOWN)
	{
		payload_len = (uint8_t)get_datagram_datadown_len_payload(d_info->packet);
	}

	uint8_t* payload = malloc(sizeof(uint8_t)*payload_len);
//	memcpy(payload , d_info->packet , payload_len);

	if(d_info->type == DATA_UP)
	{
		memcpy(payload , get_datagram_dataup_payload(d_info->packet) , payload_len);
	}
	else if(d_info->type == DATA_DOWN)
	{
		memcpy(payload , get_datagram_datadown_payload(d_info->packet) , payload_len);
	}

	on_USR_datagram_received(payload , payload_len , d_info->address);

	free_datagram_info(d_info);
}

/**
 * prende come parametro le info del pacchetto che ha scatenato la path discovery
 */
challenge_t on_path_discovery(struct NLS_HandleTypedef* hNLS , datagram_info* d_info)  //XXX PER PAOLO!!! MODIFICA FATTA!!!
{
	int preq_length;
	PREQ_typedef preq;
	preq.challenge = on_USR_path_discovery();

	uint8_t* packet = build_PREQ(preq , &preq_length);

	NLS_sendStatus mustWait = SENT;

	free(preq.challenge);


	uint8_t counter = 0;

	//se la path disocery avviene a seguito di una preq, non rimando indietro la mia preq
	//SE HO RICEVUTO LA PREQ DA UNA INTERFACCIA, LA ESCLUDO DAL BROADCAST ALTRIMENTI
	//SCOPRIREI UN PATH VERSO UN MIO POSSIBILE FIGLIO MA


	if(d_info->type == BSRP_PREQ)
	{
		mustWait = forward(hNLS , init_datagram_info(packet , d_info->source_if , preq_length, 0));
	}
	else
	{
		broadcast(init_datagram_info(packet , NO_SRC_IF , preq_length, 0));

	}

	//bloccati sulla PREP queue
	if (mustWait == SENT)
	{


		while(simpleQueueEmpty(hNLS->PREP_queue) && mustWait == SENT)
		{
			vTaskDelay(NLS_DISPATCHER_WAITING_PREP_TIME/portTICK_PERIOD_MS);
		}



		//ho scoperto un path, sono associato
		on_PREP(hNLS , simpleQueueDequeue(hNLS->PREP_queue));
	}

	return 0;
}

void on_PREQ (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
{
#ifdef ROOT
	int prep_len;

	uint8_t* secret = on_USR_PREQ(get_datagram_dataup_payload(d_info->packet));
	secret[0]=0x22;
	secret[1]=0x24;

	if (secret != NULL)
	{
		d_info->packet = build_PREP_from_PREQ(d_info->packet, &prep_len , secret , trailer_gen(d_info->packet , d_info->packet_length-TRAILER_LEN_BYTE));
		d_info->packet_length = prep_len;

		uint8_t path_len = 1;
		uint8_t path[1] = {d_info->source_if};

		uint8_t prova[1];
		//li salvo nella ds table
		downStreamTableInsert(hNLS->dTable , d_info->address , path , path_len , 0);


		throw_back(d_info);
		free(secret);
	}

	free_datagram_info(d_info);

#else
	int len;
	uint8_t* pfwd;
	pfwd = build_PFWD_from_PREQ(d_info->packet,d_info->source_if,&len);
	send_upstream(hNLS,init_datagram_info(pfwd,d_info->source_if,len,0));
#endif
}

void on_PFWD (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
{
#ifdef ROOT
	int prep_len;

	uint8_t* secret = on_USR_PREQ(get_datagram_dataup_payload(d_info->packet));

	if (secret != NULL)
	{
		uint8_t* prep = build_PREP_from_PFWD(d_info->packet, d_info->source_if , &prep_len , secret , trailer_gen(d_info->packet , d_info->packet_length-TRAILER_LEN_BYTE));
		//estraggo ds path e ds path length
		int i;
		uint8_t path_len = get_datagram_datadown_ds_path_length(prep);
		uint8_t path[path_len];

		for (i = 0 ; i < path_len ; i++)
		{
			path[i] = get_datagram_datadown_hop_if(prep , i);
		}


		//li salvo nella ds table
		downStreamTableInsert(hNLS->dTable , d_info->address , path , path_len , 0);
		//downstreamTableGetBestPath(hNLS->dTable , d_info->address , patate , &path_len);
		//printf("TEST INSERT DOWNTABLE path[0] : %d path[1] : %d\n\r", patate[0], patate[1]);
//		printf("INSERISCO IL PATH DI LUNGHEZZA %d per %x \n\r",path_len,d_info->address);
//		for(int i=0;i<path_len;i++)
//			printf("Interfaccia %d : %d\n\r",i,path[i]);
		//costruisco una PREP

		on_USR_path_discovered_root(d_info->address ,  path , path_len);

		//la invio
//		sendPacketTo(d_info->source_if , prep , prep_len , 1);
		send_downstream(hNLS,init_datagram_info(prep,d_info->source_if,prep_len,0));
		free(secret);
		free(prep);
	}

	free_datagram_info(d_info);

#else

	//se nella pfwd c'� il mio indirizzo, sto ricevendo una pfwd generata da me, e qua � fatt e loop
	if (get_datagram_address(d_info->packet) == MY_ADDRESS )
	{
		free_datagram_info(d_info);
		return;
	}

	//elimino un padre presente nella hop list per evitare loop
	//UTFilter(hNLS->uTable , get_datagram_pfwd_hop_list_length(d_info->packet) , get_datagram_pfwd_hop_list_length(d_info->packet));

	modify_PFWD(d_info->packet , d_info->source_if);

#ifdef NLS_TRACE
	printf("inoltro una PFWD");
	print_PFWD(d_info->packet);
#endif

	send_upstream(hNLS , d_info);
#endif
}

void on_PREP (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
{
#ifdef ROOT
	//non previsto. fai qualcosa che dica alla rete che stanno for ca cap
#else

	on_USR_path_discovered ();
	UTInsertEntry(hNLS->uTable , d_info->source_if , get_datagram_datadown_ds_path_length(d_info->packet) , d_info->address);

	PACK_typedef pack;
	pack.secret = on_USR_PREP(d_info->packet , d_info->packet_length);
	pack.trailer = on_USR_trailer_gen(d_info->packet , d_info->packet_length-TRAILER_LEN_BYTE);

#endif

}

/**
 * funzione da chiamare nella callback di invio fallito
 */
void on_send_fail (struct NLS_HandleTypedef* hNLS)
{
	//qui penalizzo solo il main link, ma il pacchetto da reinviare viene comunque accodato
#ifndef ROOT
	UTSwapMainLink(hNLS->uTable);
#endif
}

void on_PACK (struct NLS_HandleTypedef* hNLS , datagram_info* d_info)
{
#ifdef ROOT

	on_USR_PACK_check(get_datagram_dataup_payload(d_info->packet) , get_datagram_dataup_len_payload(d_info->packet) );

#else

	send_upstream(hNLS , d_info);
#endif
}


//==============================================================================================
