/*
 * DownStreamTable.h
 *
 *  Created on: 03/lug/2015
 *      Author: Ciro
 */

#ifndef DOWNSTREAMTABLE_H_
#define DOWNSTREAMTABLE_H_

#include "DownstreamPathList.h"

typedef struct DSTableNode{
	struct DSTableNode* parent;
	struct DSTableNode* left;
	struct DSTableNode* right;
	DownStreamPathList pathList;
} DownStreamTableNode;

typedef struct {
	DownStreamTableNode* root;
}DownStreamTable;


void downStreamTableInitialize(DownStreamTable* table);
void downStreamTableDestroy(DownStreamTable*);

void downStreamTableInsert(DownStreamTable* table, uint8_t address, datagram_if_id_t* path, uint8_t length, uint8_t penality);
int downstreamTableGetBestPath(DownStreamTable* table, datagram_address_t destinationAddress, datagram_if_id_t* path, uint8_t* length);
int downStreamTablePenaliziesBestPath(DownStreamTable* table, datagram_address_t destinationAddress);


#endif /* DOWNSTREAMTABLE_H_ */
