/*
 * routing.h
 *
 *  Created on: 03/lug/2015
 *      Author: gennaro
 */

#ifndef ROUTING_H_
#define ROUTING_H_

#include "NLS_globals.h"
#include "net_apis.h"

void dispatchNet (struct NLS_HandleTypedef* hNLS);

void unjoined_hndl(struct NLS_HandleTypedef* , datagram_info*);
void joining_hndl(struct NLS_HandleTypedef* , datagram_info*);
void recur_hndl(struct NLS_HandleTypedef* , datagram_info*);
void light_hndl(struct NLS_HandleTypedef* , datagram_info*);
void joined_hndl(struct NLS_HandleTypedef*, datagram_info*);


#endif /* ROUTING_H_ */
