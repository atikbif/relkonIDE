#ifndef MAIN_H_
#define MAIN_H_

#include "hmain.h"

#define mainFLASH_TASK_PRIORITY				( tskIDLE_PRIORITY + 1)
#define mainFLASH_DELAY						( ( portTickType ) 10 / portTICK_RATE_MS )

typedef struct
{
	union{unsigned char b1[1024];unsigned short b2[512];unsigned long b4[256];}FR;
	union{unsigned char b1[256];unsigned short b2[128];long b4[64];float fl[64];}Mem;
	unsigned char Adr;
	unsigned char Can1_Type;
	unsigned char Can2_Type;
	unsigned char Can1_Baudrate;
	unsigned char Can2_Baudrate;
	unsigned int S1,S2,S3,S4;
}plc_stat;

#endif /* MAIN_H_ */
