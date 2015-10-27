/*
 * syscall.c
 *
 *  Created on: 12/mag/2015
 *      Author: mariobarbareschi
 */

#include <sys/stat.h>
//#include "usbd_core.h"
//#include "usbd_cdc.h"
//#include "usbd_desc.h"
//#include "usbd_cdc_if_template.h"

int __errno;

int _close(int file) {
	return 0;
}

int _fstat(int file, struct stat *st) {
	return 0;
}

int _isatty(int file) {
	return 1;
}

int _lseek(int file, int ptr, int dir) {
	return 0;
}

int _open(const char *name, int flags, int mode) {
	return -1;
}

int _read(int file, char *ptr, int len) {
//	if (file != 0) {
		return 0;
//	}
//
//	// Use USB CDC Port for stdin
//	VCP_read((uint8_t*)ptr, len);

//	return 1;
}

/*The _sbrk_r is provided by the toolchain compiler*/

int _write(int file, char *ptr, int len) {
//	VCP_write((uint8_t*)ptr, len);
//	return len;
	return 0;
}
