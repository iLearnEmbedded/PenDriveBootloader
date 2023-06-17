/*
 * penDrive.c
 *
 *  Created on: 20-Mar-2023
 *      Author: pawan
 */

#include "penDrive.h"
#include "fsl_flashiap.h"S

const char *fname = "1:/APP.BIN";
static FATFS fatfs;
FILINFO fno;

extern FRESULT USB_HostMsdFatfsListDirectory(const TCHAR *path);

/*
 * penDrive_Task
 */

void penDrive_Task(void)
{
	FRESULT fatfsCode;
	FATFS *fs;
	FIL file;
	FILINFO fileInfo;
	uint32_t freeClusterNumber;
	uint32_t index;
	uint32_t resultSize;
	char *testString;
	uint8_t driverNumberBuffer[3];

	 /* time delay */
	for (freeClusterNumber = 0; freeClusterNumber < 10000; ++freeClusterNumber)
	{
		__ASM("nop");
	}

	usb_echo("1)....fatfs mount as logical driver %d......\r\n", USBDISK);

	sprintf((char *)&driverNumberBuffer[0], "%c:", USBDISK + '0');
	fatfsCode = f_mount(&fatfs, (char const *)&driverNumberBuffer[0], 0);
	if (fatfsCode)
	{
		usb_echo("error\r\n");
		return;
	}
	usb_echo("success\r\n");

	usb_echo("2)....fatfs check file presence......\r\n", USBDISK);

	fatfsCode = f_open(&file, fname,FA_READ | FA_OPEN_EXISTING);
	if(fatfsCode == FR_OK)
	{
		usb_echo("File Found\r\n");

		__disable_irq();
		for(int sector_num=EP22_APP_START_SECTOR;sector_num <= EP22_APP_END_SECTOR;sector_num++)
		{
			if(FLASHIAP_PrepareSectorForWrite(sector_num,sector_num) != kStatus_FLASHIAP_Success)
			{
				usb_echo("Flash Erase Error\r\n");
			}
			if(FLASHIAP_EraseSector(sector_num, sector_num, SystemCoreClock) != kStatus_FLASHIAP_Success)
			{
				usb_echo("Flash Erase Error\r\n");
			}
		}
		__enable_irq();
		usb_echo("Flash Erase Success\r\n");

		uint32_t file_size = 0;
		uint32_t idx = 0;
		uint32_t ridx;
		uint8_t page_data[128] = {0xFF};
		file_size = f_size(&file);
		usb_echo("File size is %d\n",file_size);

		//construct 128 Byte Packets
		while(idx < file_size)
		{
			f_read(&file,&page_data,128,&ridx);
			for(int i=0;i<128;i++)
			{
				usb_echo("%02x",page_data[i]);
			}
			idx = idx + 128;
		}
		usb_echo("File size is %d\n",file_size);

	}
	else
	{
		usb_echo("File not Found.. %d\r\n",fatfsCode);
	}

	usb_echo("driverNumberBuffer: %d",driverNumberBuffer[0]);
	fatfsCode = USB_HostMsdFatfsListDirectory((char const *)&driverNumberBuffer[0]);
}
