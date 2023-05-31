/*
 * k_icmp.h
 *
 *  Created on: Mar 15, 2012
 *      Author: Роман
 */

#ifndef K_ICMP_H_
#define K_ICMP_H_

#include "heth.h"
#include "k_ip.h"

typedef struct
{
	unsigned char type;
	unsigned char code;
	unsigned char id[2];
	unsigned char num[2];
	eth_buf buf;
}icmp_pkt;



icmp_pkt* icmp_rcv(ip_pkt* pkt);
unsigned char check_ping(icmp_pkt* pkt);
void ping_echo(icmp_pkt* pkt1,ip_pkt* pkt2);

#endif /* K_ICMP_H_ */
