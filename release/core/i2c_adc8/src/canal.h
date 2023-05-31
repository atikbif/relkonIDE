#ifndef CANAL_H_
#define CANAL_H_

#define CANAL_DELAY						    ( ( portTickType ) 1 / portTICK_RATE_MS )
#define Canal_TASK_PRIORITY				    ( tskIDLE_PRIORITY + 6 )

#define _RELKON               	0
#define _MODBUS               	1

#define BUF_SIZE    		  	512

void BinCanTask( void *pvParameters );
void AsciiCanTask( void *pvParameters );
void BinCan2Task( void *pvParameters );
void AsciiCan2Task( void *pvParameters );
void PultCanTask( void *pvParameters );
unsigned char* get_can_rx_ptr(unsigned char num);
unsigned char* get_can_tx_ptr(unsigned char num);
void can_disable(unsigned char can);
void can_enable(unsigned char can);
void clear_rx_cnt(unsigned char num);
unsigned short get_rx_cnt(unsigned char num);
void send(unsigned char can_num,unsigned char* ptr, unsigned short cnt);
void send_str(unsigned char can_num,char* ptr);
char search(unsigned char can_num,unsigned char* ptr);

#endif



