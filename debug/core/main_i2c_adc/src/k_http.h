/*
 * k_http.h
 *
 *  Created on: Mar 29, 2012
 *      Author: Роман
 */

#ifndef K_HTTP_H_
#define K_HTTP_H_

#include "k_tcp.h"
#include "k_ip.h"

#define MAX_WEB_FILE_CNT	20

#define HTML_TXT			0
#define IZO					1
#define JS					2
#define DYN_DATA			3
#define CSS					4

typedef struct
{
	unsigned char* name;
	unsigned char namelen;
	unsigned char type;
	unsigned long size;
	unsigned char* fdata;
}flist;

unsigned char add_web_file(flist* f);
flist* get_web_file(tcp_pkt* pkt);
void send_web_file(tcp_pkt* pkt1, ip_pkt* pkt2, flist* f);

unsigned char check_http_req(tcp_pkt* pkt);
void http_enable(void);
unsigned char get_http_stat(void);
void web_req(tcp_pkt* pkt1,ip_pkt* pkt2);

#endif /* K_HTTP_H_ */
