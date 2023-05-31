#ifndef ETH_TASK_H_
#define ETH_TASK_H_

#include "k_ip.h"
#include "k_udp.h"
#include "k_tcp.h"

#define ETH_DELAY						    ( ( portTickType ) 1 / portTICK_RATE_MS )
#define ETH_TASK_PRIORITY				    ( tskIDLE_PRIORITY + 1 )

void EthTask( void *pvParameters );
void udp_protocol(udp_pkt* pkt1,ip_pkt* pkt2);
void tcp_modbus(tcp_pkt* pkt1,ip_pkt* pkt2);

#endif


