#ifndef SDCARD_H_
#define SDCARD_H_

#include "hsd.h"

#define SD_TASK_PRIORITY				    ( tskIDLE_PRIORITY + 1 )

void ArchiveTask( void *pvParameters );
void SD_Cmd(unsigned char cmd, unsigned short paramx, unsigned short paramy);
unsigned char SD_Resp8b(void);
unsigned short SD_Resp16b(void);
char SD_writeSector(unsigned long address, unsigned char* buf);
char SD_readSector(unsigned long address, unsigned char* buf, unsigned short len);
char SD_getDriveSize(unsigned long* drive_size );
char SD_Init(void);
char initInterface(void);
int media_read(unsigned long sector, unsigned char *buffer, unsigned long sector_count);
int media_write(unsigned long sector, unsigned char *buffer, unsigned long sector_count);

#endif /* SDCARD_H_ */
