/*
 * configuration.h
 *
 *  Created on: 20/giu/2015
 *      Author: dario
 */

#ifndef WOLFCRYPT_INCLUDE_CONFIG_H_
#define WOLFCRYPT_INCLUDE_CONFIG_H_

#define NO_CYASSL_CLIENT
#define NO_CYASSL_SERVER
//#define NO_DES3
#define NO_DH
#define NO_ERROR_STRINGS

#define NO_MD4
//#define NO_MD5
//#define NO_SHA
//#define NO_SHA256
#define WOLFSSL_SHA512
#define WOLFSSL_SHA384


#define NO_PSK
#define NO_PWDBASED
//#define NO_RC4
#define NO_RABBIT
#define NO_HC128
#define NO_SESSION_CACHE
#define NO_TLS
#define SMALL_SESSION_CACHE
#define SINGLE_THREADED


#endif /* WOLFCRYPT_INCLUDE_CONFIG_H_ */
