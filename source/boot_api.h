/*
 * boot_api.h
 *
 *  Created on: 22-Jun-2024
 *      Author: gp
 */

#ifndef BOOT_API_H_
#define BOOT_API_H_

#include "boot_defs.h"
#define RESP_ACK         0
#define RESP_NAK         1

extern uint32_t exit_boot_mode;

uint8_t page_write(uint16_t page_num,uint8_t * data,uint16_t len);
uint8_t erase_app(uint32_t start_addr,uint32_t end_addr);

#endif /* BOOT_API_H_ */
