/*
 * applicationConfig.h
 *
 *  Created on: 30/giu/2015
 *      Author: Marcello
 */

#ifndef APPLICATIONCONFIG_H_
#define APPLICATIONCONFIG_H_

#include "security.h"

//lunghezza chiave in byte
#define KEYLEN 16 		//16 byte = 128 bit
static const SEC_CRYP_AlgorithmTypeDef CRYPTO_ALGORITHM = SEC_AES128;

#ifdef OPERATIVE_NODE

#define IDCONTROLLO "\x2a\x00\x31\x00\x0e\x47\x32\x34\x38\x36\x36\x31"

static const SEC_AES128_Key key = "1234567891234567";

#endif /* OPERATIVE_NODE */

/* lunghezza segreto in byte
 * N.B. il segreto viene generato in HW. Questo usa un registro a 4 byte
 * per cui SECRETLEN deve essere un multiplo di 4*/
#define SECRETLEN 16	//16 byte = 128 bit

#define FRAMEIDLEN 1	//16 byte = 128 bit

//lunghezza in byte dell'identificativo della scheda
#define IDLEN 12
#define TIMESTAMPLEN 4

static const SEC_HASH_AlgorithmTypeDef HASH_ALGORITHM = SEC_MD5;
#define DIGESTLEN 20

#define MAX_LENGTH 16

#define HMAC_LENGTH (1+IDLEN+TIMESTAMPLEN+MAX_LENGTH)

//Per il protocollo di JOIN
#define SEC_JOIN_REQ 0xA3
#define SEC_JOIN_RES 0xA4
#define SEC_JOIN_ACK 0xA5
#define DATA_FRAME 0xFF

//Per il protocollo di aggiornamento della chiave
#define SEC_SECRETCHANGE_START	 	0xAA
#define SEC_SECRETCHANGE_ACK 		0xAB
#define SEC_SECRETCHANGE_OK		 	0xAC

typedef unsigned char byte;

typedef struct{
	unsigned char ID; //1 byte
	unsigned char sourceID[IDLEN]; //12 byte
	unsigned char timestamp[TIMESTAMPLEN]; //4 byte
	unsigned char msg[MAX_LENGTH]; //1024 byte
	unsigned char digest[DIGESTLEN]; //20 byte
}SEC_ApplicationFrameTypedef;


#endif /* APPLICATIONCONFIG_H_ */
