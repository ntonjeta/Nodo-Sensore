/*
// * net_apis_core.h
// *
// *  Created on: 05/lug/2015
// *      Author: gennaro
// */
//
//#ifndef NET_APIS_CORE_H_
//#define NET_APIS_CORE_H_
//
//#include "NLS_globals.h"
//#include "datagram_builders.h"
//#include "net_apis.h"
//
////defines
//#define	OK_SND		0
//#define FAIL_SND	1
//
//typedef enum
//{
//	CHECK_OK,
//	CHECK_FAILED
//}check_status;
//
//
//
//extern struct NLS_HandleTypedef hNLS;
//
//void enable_if (struct NLS_HandleTypedef* hNLS , uint8_t _if);
//
//#ifndef ROOT
//uint8_t send_upstream (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
//#endif
//uint8_t send_downstream (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
//
//void forward(struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
//void broadcast(datagram_info* d_info);
//void throw_back(datagram_info* d_info);
//
//uint8_t* trailer_gen(uint8_t* packet , uint8_t length);
//
////wrapper eventi
//check_status on_datagram_check(datagram_info* d_info);
//void on_datagram_received(datagram_info* d_info);
//
///**
// * @brief chiamata quando si verifica l'evento di inizio di una path discovery
// *
// * se la path discovery è eseguita a seguito della ricezione di una PREQ, passare l'ID
// * di interfaccia di ricezione, altrimenti passare 0xFF
// */
//challenge_t on_path_discovery(struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
//
//void on_PREQ (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
//void on_PFWD (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
//void on_PREP (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
//void on_PACK (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
//void on_send_fail (struct NLS_HandleTypedef* hNLS);
//
//
//
//
//#endif /* NET_APIS_CORE_H_ */


/*
 * net_apis_core.h
 *
 *  Created on: 05/lug/2015
 *      Author: gennaro
 */

#ifndef NET_APIS_CORE_H_
#define NET_APIS_CORE_H_

#include "NLS_globals.h"
#include "datagram_builders.h"
#include "net_apis.h"

//defines
#define	OK_SND		0
#define FAIL_SND	1

typedef enum
{
	CHECK_OK,
	CHECK_FAILED
}check_status;

typedef enum
{
	SENT,
	NOT_SENT
}NLS_sendStatus;

extern struct NLS_HandleTypedef hNLS;

void enable_if (struct NLS_HandleTypedef* hNLS , uint8_t _if);

#ifndef ROOT
uint8_t send_upstream (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
#endif
uint8_t send_downstream (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);

NLS_sendStatus forward(struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
void broadcast(datagram_info* d_info);
void throw_back(datagram_info* d_info);

uint8_t* trailer_gen(uint8_t* packet , uint8_t length);

//wrapper eventi
check_status on_datagram_check(datagram_info* d_info);
void on_datagram_received(datagram_info* d_info);

/**
 * @brief chiamata quando si verifica l'evento di inizio di una path discovery
 *
 * se la path discovery è eseguita a seguito della ricezione di una PREQ, passare l'ID
 * di interfaccia di ricezione, altrimenti passare 0xFF
 */
challenge_t on_path_discovery(struct NLS_HandleTypedef* hNLS , datagram_info* d_info);

void on_PREQ (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
void on_PFWD (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
void on_PREP (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
void on_PACK (struct NLS_HandleTypedef* hNLS , datagram_info* d_info);
void on_send_fail (struct NLS_HandleTypedef* hNLS);




#endif /* NET_APIS_CORE_H_ */
