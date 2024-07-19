/*
 * bootldr_defs.h
 *
 *  Created on: 12-Jan-2023
 *      Author: pawan
 */

#ifndef BOOT_DEFS_H_
#define BOOT_DEFS_H_
#include <stdint.h>

#define APP_START_ADDR               0x20000
#define APP_END_ADDR                 0x80000
#define APP_START_SECTOR                   4
#define APP_END_SECTOR                    15

#define GET_SECTOR_NUM(page_num)     (page_num/128) /*128 pages per sector*/
#define	GET_FLS_ADDR(page_num)       (page_num*256) /* 256 Bytes per page*/
#define GET_PAGENUM_FROM_ADDR(x)     (x /256) /* 256 Bytes per Page*/



#endif /* BOOT_DEFS_H_ */
