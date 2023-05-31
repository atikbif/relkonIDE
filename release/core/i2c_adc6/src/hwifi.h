/*
 * hwifi.h
 *
 *  Created on: Jun 21, 2012
 *      Author: Роман
 */

#ifndef HWIFI_H_
#define HWIFI_H_

#include "stm32f10x_conf.h"
#include "FreeRTOS.h"

#define 	eSPI_STATE_POWERUP 				 (0)
#define 	eSPI_STATE_INITIALIZED  		 (1)
#define 	eSPI_STATE_IDLE					 (2)
#define 	eSPI_STATE_WRITE_IRQ	   		 (3)
#define 	eSPI_STATE_READ_IRQ				 (6)

#define WF_TASK_PRIORITY				    ( tskIDLE_PRIORITY + 1 )
#define WF_DELAY			                ( ( portTickType ) 1 / portTICK_RATE_MS )

#define ASSERT_CS()          GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define DEASSERT_CS()        GPIO_SetBits(GPIOB,GPIO_Pin_12)

typedef void (*gcSpiHandleRx)(void *p);

typedef struct
{
	gcSpiHandleRx  SPIRxHandler;
	unsigned short usTxPacketLength;
	unsigned short usRxPacketLength;
	volatile unsigned long  ulSpiState;
	unsigned char *pTxPacket;
	unsigned char *pRxPacket;
}tSpiInformation;

typedef struct __attribute__ ((__packed__)) _btspi_hdr
{
    unsigned char   cmd;
    unsigned short  length;
    unsigned char   pad[2];
}btspi_hdr;

void cc_gpio_init(void);
void WriteWlanPin( unsigned char val );
long ReadWlanInterruptPin(void);
void WlanInterruptEnable(void);
void WlanInterruptDisable(void);
void init_cctimer(void);
void pause_us(unsigned short val);
void SpiSend(unsigned char* tx_ptr,unsigned char* rx_ptr,unsigned short l,portTickType ptr);
void wait_spi(void);

#endif /* HWIFI_H_ */
