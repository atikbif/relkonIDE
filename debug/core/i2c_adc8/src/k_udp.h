/*
 * k_udp.h
 *
 *  Created on: Mar 15, 2012
 *      Author: Роман
 */

#ifndef K_UDP_H_
#define K_UDP_H_

#include "heth.h"
#include "k_ip.h"

#define UDP_PORT_SIZE	5

typedef struct
{
	unsigned char p_s[2];
	unsigned char p_d[2];
	eth_buf buf;
}udp_pkt;

void udp_init(void);
udp_pkt* udp_rcv(ip_pkt* pkt);
unsigned char udp_listen(unsigned short port, void (*func)(udp_pkt* pkt1,ip_pkt* pkt2));
void portudp_scan(udp_pkt* pkt1, ip_pkt* pkt2);
void udp_answer_head(udp_pkt* pkt1,ip_pkt* pkt2);
void send_udp(udp_pkt* pkt1,ip_pkt* pkt2);
void send_udp_to_buf(udp_pkt* pkt1,ip_pkt* pkt2);

#endif /* K_UDP_H_ */
