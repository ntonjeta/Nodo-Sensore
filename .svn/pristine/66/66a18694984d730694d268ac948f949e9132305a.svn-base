/*
 * EventLogger_conf_template.h
 *
 *  Created on: Jul 1, 2015
 *      Author: davide
 */

#ifndef EVENTLOGGER_INC_EVENTLOGGER_CONF_H_
#define EVENTLOGGER_INC_EVENTLOGGER_CONF_H_

#include "usbh_core.h"
#include "usbh_conf.h"
#include "usbh_def.h"

#include "usbh_msc.h"

#include "ff.h"
#include "ffconf.h"
#include "ff_gen_drv.h"
#include "usbh_diskio.h"

extern USBH_HandleTypeDef hUSB_Host;
extern int OK;

#define LOG_USE_OS 			1
#define LOG_USE_BUFFERING	1
#if (LOG_USE_BUFFERING == 1)
#define LOG_MAX_BUFF		10
#endif

#endif /* EVENTLOGGER_INC_EVENTLOGGER_CONF_H_ */
