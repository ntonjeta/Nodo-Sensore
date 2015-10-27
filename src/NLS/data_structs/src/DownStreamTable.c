/*
 * DownStreamTable.c
 *
 *  Created on: 03/lug/2015
 *      Author: Ciro
 */

#include "DownStreamTable.h"
#include <stdlib.h>
#include <string.h>

void downStreamTableNodeInitialize(DownStreamTableNode* node, datagram_address_t address);
void downStreamTableNodeDestroy(DownStreamTableNode* node);
void downStreamTableNodeRecursiveDestroy(DownStreamTableNode* node);
DownStreamTableNode* downStreamTableSearch(DownStreamTable* table, datagram_address_t destinationAddress);

void downStreamTableNodeInitialize(DownStreamTableNode* node, datagram_address_t address){
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	downStreamPathListInitialize(&(node->pathList), address);
}

void downStreamTableNodeDestroy(DownStreamTableNode* node){
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	downStreamPathListDestroy(&(node->pathList));
}

DownStreamTableNode* downStreamTableSearch(DownStreamTable* table, datagram_address_t destinationAddress){
	DownStreamTableNode* x = table->root;
	while(x != NULL && destinationAddress != x->pathList.destinationAddress){
		if (destinationAddress < x->pathList.destinationAddress)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

void downStreamTableNodeRecursiveDestroy(DownStreamTableNode* node){
	if (node == NULL)
		return;
	downStreamTableNodeRecursiveDestroy((DownStreamTableNode*)node->left);
	downStreamTableNodeRecursiveDestroy((DownStreamTableNode*)node->right);
	downStreamTableNodeDestroy(node);
	free(node);
}

void downStreamTableInitialize(DownStreamTable* downStreamTable){
	downStreamTable->root = NULL;
}


void downStreamTableDestroy(DownStreamTable* downStreamTable){
	downStreamTableNodeRecursiveDestroy(downStreamTable->root);
}

void downStreamTableInsert(DownStreamTable* table, uint8_t address, datagram_if_id_t* path, uint8_t length, uint8_t penality){
	DownStreamTableNode* y = NULL;
	DownStreamTableNode* x = table->root;
	while (x != NULL && x->pathList.destinationAddress != address){
		y = x;
		if (address < x->pathList.destinationAddress)
			x = x->left;
		else
			x = x->right;
	}

	if (x != NULL){
		//A: La lista lista è già presente
		downStreamPathListInsert(&(x->pathList), path, length, penality);
		return;
	}else{
		DownStreamTableNode* z = (DownStreamTableNode*)malloc(sizeof(DownStreamTableNode));
		downStreamTableNodeInitialize(z, address);
		downStreamPathListInsert(&(z->pathList), path, length, penality);
		z->parent = y;
		if (y == NULL){
			table->root = z;		//L'albero era vuoto
		}else if (address < y->pathList.destinationAddress){
			y->left = z;
		}else{
			y->right = z;
		}

	}
}

int downstreamTableGetBestPath(DownStreamTable* table, datagram_address_t destinationAddress, datagram_if_id_t* path, uint8_t* length){
	DownStreamTableNode* x = downStreamTableSearch(table, destinationAddress);
	if (x != NULL){
		const DownStreamPath* downStreamPath = downStreamPathListGetBestPath(&(x->pathList));
		*length = downStreamPath->length;
		memcpy(path, downStreamPath->path, downStreamPath->length);
		return 0;
	} else {
		*length = 0;
		return 1;
	}
}

int downStreamTablePenaliziesBestPath(DownStreamTable* table, datagram_address_t destinationAddress){
	DownStreamTableNode* x = downStreamTableSearch(table, destinationAddress);
	if (x != NULL){
		DownStreamPath* downStreamPath = downStreamPathListGetBestPath(&(x->pathList));
		if (downStreamPath != NULL){
			downStreamPathPenalizes(downStreamPath);
			return 1;
		}
	}
	return 0;
}

