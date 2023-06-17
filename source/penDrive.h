/*
 * penDrive.h
 *
 *  Created on: 20-Mar-2023
 *      Author: pawan
 */

#ifndef PENDRIVE_H_
#define PENDRIVE_H_

#include "usb_host_config.h"
#include "usb_host.h"
#include "usb_host_msd.h"
#include "host_msd_fatfs.h"
#include "ff.h"
#include "diskio.h"
#include "stdio.h"
#include "fsl_device_registers.h"
#include "app.h"

#include "board.h"

#define EP22_APP_START_ADDR               0x20000
#define EP22_APP_END_ADDR                 0x80000
#define EP22_APP_START_SECTOR                   5//4
#define EP22_APP_END_SECTOR                    15

extern void penDrive_Task(void);

#endif /* PENDRIVE_H_ */
