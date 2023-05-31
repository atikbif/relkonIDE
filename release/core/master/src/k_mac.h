/*
 * k_mac.h
 *
 *  Created on: Mar 15, 2012
 *      Author: Роман
 */

#ifndef K_MAC_H_
#define K_MAC_H_

#define IP_TYPE			0
#define ARP_TYPE		1
#define UNDEF_TYPE		2

#include "heth.h"

typedef struct
{
	unsigned char mac_s[6];
	unsigned char mac_d[6];
	unsigned char type[2];
	eth_buf buf;
}mac_pkt;

void get_mac(unsigned char* m);
void set_mac(unsigned char* m);
mac_pkt* get_mac_pkt(eth_buf* buf);
unsigned char check_mac(mac_pkt* pkt);
unsigned char get_eth_type(mac_pkt* pkt);

#endif /* K_MAC_H_ */
