/*
 * k_arp.h
 *
 *  Created on: Mar 15, 2012
 *      Author: Роман
 */
#ifndef K_ARP_H_
#define K_ARP_H_

#define ARP_TAB_SIZE	10

typedef struct
{
	unsigned char mac_s[6];
	unsigned char mac_d[6];
	unsigned char ip_s[4];
	unsigned char ip_d[4];
	unsigned char oper[2];
}arp_pkt;

#include "k_mac.h"

void init_arp_tab(void);
unsigned char* get_mac_tab(unsigned char* ip_req);
void add_arp_tab(unsigned char* ip_tab,unsigned char* mac_tab);
arp_pkt* arp_rcv(mac_pkt* pkt);
unsigned char check_arp_req(arp_pkt* pkt);
unsigned char check_arp_answer_gate(arp_pkt* pkt);
unsigned char check_arp_answer(arp_pkt* pkt);
void send_arp(arp_pkt* pkt);
void arp_answer(arp_pkt* pkt);
void get_gate_mac(void);
void set_gate_mac(unsigned char* m);
unsigned char* get_gate_ptr(void);

#endif /* K_ARP_H_ */


