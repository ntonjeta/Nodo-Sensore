///*
// * routing.c
// *
// *  Created on: 03/lug/2015
// *      Author: gennaro
// */
//#include "data_plane.h"
//#include "NLS_globals.h"
//#include "net_apis_usr.h"
//#include "net_apis.h"
//#include "net_apis_core.h"
//
//#include "datagram_builders.h"
//#include "stm32f4_discovery.h"
//
//extern struct NLS_HandleTypedef hNLS;
//
//
//
////STUB!
///**
// *  Funzione eseguita ciclicamente. Disaccoda un pacchetto, ne verifica il tipo
// *  ed chiama la primitiva di invio appropriata.
// */
//void dispatch (struct NLS_HandleTypedef* hNLS)
//{
//	//scoda la prep queue se vuota
//	if (!simpleQueueEmpty(hNLS->PREP_queue))
//	{
//		on_PREP(hNLS , simpleQueueDequeue(hNLS->PREP_queue));
//	}
//
//	//scoda la coda di ingresso
//	datagram_info* d_info = (datagram_info*)priorityQueueDequeue(hNLS->routing_queue);
//	if (d_info == NULL)	return;
//
//
//	//i messaggi di upstream e downstream diretti al root vanno direttamente al livello superiore
//	#ifdef ROOT
//	if (d_info->type == DATA_UP) //XXX CONTROLLARE DATA_DOWN
//	{
//		on_datagram_received(d_info);
//		return;
//	}
//#else
//	if ((get_datagram_address(d_info->packet) == MY_ADDRESS) && (d_info->type == DATA_DOWN))
//	{
//		//� un datagramma dati, manda ai livelli superiori
//		on_datagram_received(d_info);
//		//BSP_LED_On(LED5);
//		return;
//	}
//
//	//se non ho un path
//	if(UTGetSize(hNLS->uTable) == 0)
//	{
//		//se non ho un path ma  ho pacchetti da inviare
//		if(d_info != NULL)
//		{
//
//			//fai path discovery
//			on_path_discovery(hNLS , d_info);
//
//			//bloccati sulla PREP queue
//			while(simpleQueueEmpty(hNLS->PREP_queue))
//			{
//				vTaskDelay(NLS_DISPATCHER_WAITING_PREP_TIME/portTICK_PERIOD_MS);
//			}
//
//			//ho scoperto un path, sono associato
//			on_PREP(hNLS , simpleQueueDequeue(hNLS->PREP_queue));
//
//		}
//
//	}
//#endif
//
//
//	//qui sono associato
//	switch(d_info->type)
//	{
//
//	case DATA_UP:
//	{
//#ifndef ROOT   //XXX PER PAOLO: Attenzione a questo #ifndef; potrebbe anche non essere necessario
//		if(d_info->source_if == UTGetMainLink(hNLS->uTable))
//		{
//			UTSwapMainLink(hNLS->uTable);
//		}
//		send_upstream(hNLS , d_info);
//#endif
//		break;
//
//	}
//	case DATA_DOWN:
//	{
//		send_downstream(hNLS , d_info);
//		break;
//
//	}
//	case BSRP_PREQ:
//	{
//		on_PREQ(hNLS  , d_info);
//		break;
//	}
//	case BSRP_PFWD:
//	{
//		on_PFWD(hNLS , d_info);
//		break;
//	}
//	case BSRP_PREP:
//	{
//#ifndef ROOT
//		send_downstream(hNLS  , d_info);
//#endif
//		break;
//
//	}
//	case BSRP_PACK:
//	{
//		break;
//	}
//}
//
//
//}
//
//void unjoined_hndl(struct NLS_HandleTypedef* hNLS, datagram_info* d_info)
//{
//
//}
//void joining_hndl(struct NLS_HandleTypedef* hNLS, datagram_info* d_info)
//{
//
//}
//void recur_hndl(struct NLS_HandleTypedef* hNLS, datagram_info* d_info)
//{
//
//}
//void light_hndl(struct NLS_HandleTypedef* hNLS, datagram_info* d_info)
//{
//
//}
//void joined_hndl(struct NLS_HandleTypedef* hNLS, datagram_info* d_info)
//{
//
//}

/*
 * routing.c
 *
 *  Created on: 03/lug/2015
 *      Author: gennaro
 */
#include "data_plane.h"
#include "NLS_globals.h"
#include "net_apis_usr.h"
#include "net_apis.h"
#include "net_apis_core.h"

#include "datagram_builders.h"
#include "stm32f4_discovery.h"

//STUB!
/**
 *  Funzione eseguita ciclicamente. Disaccoda un pacchetto, ne verifica il tipo
 *  ed chiama la primitiva di invio appropriata.
 */
void dispatchNet (struct NLS_HandleTypedef* hNLS)   //XXX PER PAOLO: MODIFICA FATTA!!
{
	//scoda la prep queue se vuota
	if (!simpleQueueEmpty(hNLS->PREP_queue))
	{
		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "dispatch()",
		//							LOG_STRING, "scoda la coda PREP", "OK",
		//							LOG_END);

		on_PREP(hNLS , simpleQueueDequeue(hNLS->PREP_queue));
	}

	//scoda la coda di ingresso
	datagram_info* d_info = (datagram_info*)priorityQueueDequeue(hNLS->routing_queue);

	if (d_info == NULL)
	{
		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "dispatch()",
		//							LOG_STRING, "scoda la coda d'ingresso", "OK",
		//							LOG_STRING, "coda d'ingresso", "nessun datagram",
		//							LOG_END);

		return;
	}

	//TODO Log
	//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "dispatch()",
	//							LOG_STRING, "scoda la coda d'ingresso", "OK",
	//							LOG_STRING, "coda d'ingresso", "datagram scodato",
	//							LOG_INT, "if source", d_info->source_if,
	//							LOG_INT, "datagram type", d_info->type,
	//							LOG_INT, "packet length", d_info->packet_length,
	//							LOG_INT, "address", d_info->address,
	//							LOG_END);


	//i messaggi di upstream e downstream diretti al root vanno direttamente al livello superiore
#ifdef ROOT
	if (d_info->type == DATA_UP) //XXX CONTROLLARE DATA_DOWN
	{

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "dispatch()",
		//							LOG_STRING, "nodo ROOT: datagram type", "DATA UP",
		//							LOG_STRING, "nodo ROOT: trasferisci al livello superiore", "OK",
		//							LOG_END);

		on_datagram_received(d_info);
		return;
	}
#else
	if ((get_datagram_address(d_info->packet) == MY_ADDRESS) && (d_info->type == DATA_DOWN))
	{
		//� un datagramma dati, manda ai livelli superiori

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "dispatch()",
		//							LOG_STRING, "datagram dati", "trasferisci aL livellO superiorE",
		//							LOG_END);

		on_datagram_received(d_info);
		//BSP_LED_On(LED5);
		return;
	}


	//se non ho un path
	if(UTGetSize(hNLS->uTable) == 0)
	{
		//se non ho un path ma  ho pacchetti da inviare
		if(d_info != NULL)
		{

			//fai path discovery

			//TODO Log
			//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "dispatch",
			//							LOG_STRING, "nessun path e datagram da inviare", "esegui path discovery",
			//							LOG_END);

			on_path_discovery(hNLS , d_info);

		}

	}
#endif


	//qui sono associato
	switch(d_info->type)
	{

	case DATA_UP:
	{
#ifndef ROOT   //XXX PER PAOLO: Attenzione a questo #ifndef; potrebbe anche non essere necessario
		if(d_info->source_if == UTGetMainLink(hNLS->uTable))
		{

			//TODO Log
			//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "dispatch()",
			//							LOG_STRING, "datagram type", "DATA UP",
			//							LOG_STRING, "swap main link in Upstream Table", "OK",
			//							LOG_END);

			UTSwapMainLink(hNLS->uTable);
		}

		send_upstream(hNLS , d_info);
#endif
		break;

	}
	case DATA_DOWN:
	{

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "dispatch()",
		//							LOG_STRING, "datagram type", "DATA DOWN",
		//							LOG_STRING, "trasmissione DOWNSTREAM", "OK",
		//							LOG_END);

		send_downstream(hNLS , d_info);
		break;

	}
	case BSRP_PREQ:
	{
#ifndef ROOT
		if(hNLS->enabled_ifs_num!=1)  //XXX ZUPPA PAOLO: TENTATIVO DI AGGIUSTARE IL PROTOCOLLO
#endif

			//TODO Log
			//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "dispatch()",
			//							LOG_STRING, "datagram type", "PREQ",
			//							LOG_STRING, "on PREQ", "OK",
			//							LOG_END);

			on_PREQ(hNLS  , d_info);

		break;
	}
	case BSRP_PFWD:
	{

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "dispatch()",
		//							LOG_STRING, "datagram type", "PFWD",
		//							LOG_STRING, "on PFWD", "OK",
		//							LOG_END);

		on_PFWD(hNLS , d_info);
		break;
	}
	case BSRP_PREP:
	{
#ifndef ROOT

		//TODO Log
		//EventLogger_LogEvent(&LOG_HANDLE, NETWORK, NOTICE, MY_ADDRESS, "dispatch()",
		//							LOG_STRING, "datagram type", "PREP",
		//							LOG_STRING, "trasmissione DOWNSTREAM", "OK",
		//							LOG_END);

		send_downstream(hNLS  , d_info);
#endif
		break;

	}
	case BSRP_PACK:
	{
		break;
	}
	}


}

void unjoined_hndl(struct NLS_HandleTypedef* hNLS, datagram_info* d_info)
{

}
void joining_hndl(struct NLS_HandleTypedef* hNLS, datagram_info* d_info)
{

}
void recur_hndl(struct NLS_HandleTypedef* hNLS, datagram_info* d_info)
{

}
void light_hndl(struct NLS_HandleTypedef* hNLS, datagram_info* d_info)
{

}
void joined_hndl(struct NLS_HandleTypedef* hNLS, datagram_info* d_info)
{

}

