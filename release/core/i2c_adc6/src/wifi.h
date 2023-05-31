#ifndef WIFI_H_
#define WIFI_H_

#include "hwifi.h"

#define 	CC_BUFFER_SIZE					 2048
#define READ                    			 3
#define WRITE                   			 1
#define HI(value)               			 (((value) & 0xFF00) >> 8)
#define LO(value)               			 ((value) & 0x00FF)

void WIFITask( void *pvParameters );
void SCAN_WIFITask( void *pvParameters );
long SpiWrite(unsigned char *pUserBuffer, unsigned short usLength);
void scan_wifi(portTickType ptr);
void SpiOpen(gcSpiHandleRx pfRxHandler);
void SpiClose(void);
void SpiResumeSpi(void);

#endif /* WIFI_H_ */
