
#ifndef H_ETH_H_
#define H_ETH_H_

#define ETH_PKT_SIZE	ETH_MAX_PACKET_SIZE

#define ETH_RXBUFNB 6
#define ETH_TXBUFNB 2

#include "stm32_eth.h"

typedef struct
{
	unsigned char* ptr;
	unsigned short len;
}eth_buf;

void GPIO_ENETConfiguration(void);
unsigned long ENET_Configuration(void);
unsigned char get_link_status(void);
unsigned char test_rx_overflow(void);
eth_buf* get_mac_data(unsigned char num);
void unlock_mac_rx(unsigned char num);
void send_mac_data(unsigned short len);
unsigned char* get_mac_tx(void);

#endif /* H_ETH_H_ */


