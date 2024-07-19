/*
 * boot_api.c
 *
 *  Created on: 22-Jun-2024
 *      Author: gp
 */

#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC54628.h"
#include "fsl_debug_console.h"

#include "fsl_flashiap.h"
#include "boot_api.h"

uint32_t exit_boot_mode;

uint8_t page_write(uint16_t page_num,uint8_t * data,uint16_t len)
{
	__disable_irq();
	uint32_t sector_num = GET_SECTOR_NUM(page_num);
	uint32_t start_addr = GET_FLS_ADDR(page_num);
	uint8_t wdata[256];

	memcpy(wdata,data,len);

	if(len < 256)
	{
		memset(&wdata[len],0xFF,(256-len));
	}

	PRINTF("Fls Write start_addr = %04x\n",start_addr);

	if((sector_num < APP_START_SECTOR) || (sector_num > APP_END_SECTOR))
	{
		return RESP_NAK;
	}
	FLASHIAP_PrepareSectorForWrite(sector_num,sector_num);
	if(FLASHIAP_CopyRamToFlash(start_addr,(uint32_t *) wdata, (uint32_t) 256,SystemCoreClock) != kStatus_FLASHIAP_Success)
	{
		__enable_irq();
		return RESP_NAK;
	}
	else
	{
		__enable_irq();
		return RESP_ACK;
	}
	__enable_irq();
	return RESP_ACK;
}

uint8_t erase_app(uint32_t start_addr,uint32_t end_addr)
{
	__disable_irq();
	if((APP_START_ADDR == start_addr) && (APP_END_ADDR == end_addr))
	{
		PRINTF("Erase Start Addr = %04x End Addr = %04x \n",start_addr,end_addr);
		for(int sector_num=APP_START_SECTOR;sector_num <= APP_END_SECTOR;sector_num++)
		{
			if(FLASHIAP_PrepareSectorForWrite(sector_num,sector_num) != kStatus_FLASHIAP_Success)
			{
				return RESP_NAK;
			}
			if(FLASHIAP_EraseSector(sector_num, sector_num, SystemCoreClock) != kStatus_FLASHIAP_Success)
			{
				return RESP_NAK;
			}
		}
		__enable_irq();
		return RESP_ACK;
	}
	else
	{
		PRINTF("Fail Erase Start Addr = %04x End Addr = %04x \n",start_addr,end_addr);
		__enable_irq();
		return RESP_NAK;
	}
}
