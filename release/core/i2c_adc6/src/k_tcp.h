/*
 * k_tcp.h
 *
 *  Created on: Mar 27, 2012
 *      Author: Роман
 */

#ifndef K_TCP_H_
#define K_TCP_H_

#include "heth.h"
#include "k_ip.h"

#define FL_FIN		1
#define FL_SYN		2
#define FL_RST		4
#define FL_PSH		8
#define FL_ACK		16
#define FL_URG		32

#define TCP_PORT_SIZE	5

typedef struct
{
	unsigned short p_s;
	unsigned short p_d;
	unsigned long n_tr;
	unsigned long n_rcv;
	unsigned char fl;
	unsigned short window;
	eth_buf buf;
}tcp_pkt;

tcp_pkt* tcp_rcv(ip_pkt* pkt);
void tcp_init(void);
unsigned char tcp_listen(unsigned short port, void (*func)(tcp_pkt* pkt1,ip_pkt* pkt2));
void porttcp_scan(tcp_pkt* pkt1, ip_pkt* pkt2);
void answer_syn(tcp_pkt* pkt1,ip_pkt* pkt2);
void send_tcp(tcp_pkt* pkt1,ip_pkt* pkt2);
void answer_tcpack(tcp_pkt* pkt1,ip_pkt* pkt2);
void tcp_answer_head(tcp_pkt* pkt1,ip_pkt* pkt2);

#endif /* K_TCP_H_ */
