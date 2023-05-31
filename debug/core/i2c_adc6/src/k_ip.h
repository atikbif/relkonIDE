/*
 * k_ip.h
 *
 *  Created on: Mar 15, 2012
 *      Author: Роман
 */

#ifndef K_IP_H_
#define K_IP_H_

#include "heth.h"
#include "k_mac.h"

#define ICMP_TYPE		1
#define UDP_TYPE		2
#define TCP_TYPE		3
#define UNDEFIP_TYPE	4

typedef struct
{
	unsigned char ip_s[4];
	unsigned char ip_d[4];
	unsigned char pr;
	unsigned char id[2];
	eth_buf buf;
}ip_pkt;

void set_gate_cmd(void);
void clr_gate_cmd(void);
void get_ip(unsigned char* ip_data);
void set_ip(unsigned char* ip_data);
ip_pkt* ip_rcv(mac_pkt* pkt);
void send_ip(ip_pkt* pkt);
void send_ip_without_id_increment(ip_pkt* pkt);
unsigned char check_ip_req(ip_pkt* pkt);
unsigned char get_ip_type(ip_pkt* pkt);
void set_mask(unsigned char* new_m);
void set_gate(unsigned char* new_gate);
void get_mask(unsigned char* m);
void get_gate(unsigned char* g);
unsigned char check_mask(unsigned char* ips);
void set_id(unsigned short value);
unsigned short get_id(void);

#endif /* K_IP_H_ */
