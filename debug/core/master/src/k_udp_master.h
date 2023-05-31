#define UDP_WR_USER			1
#define UDP_RD_USER			2
#define UDP_WAIT_ANSWER		0
#define UDP_CORRECT_ANSWER	1
#define ID_LIST_CNT			20

#include "k_udp.h"

typedef struct{
	unsigned char cmd;		// ��� ������� - ������/������
	unsigned char ip[4];		// ip ����� ����������
	unsigned short addr;		// ����� ������ ������
	unsigned short cnt;		// ���������� ��������� ��� ������ ������
	unsigned char *rx;		// ����� ��� ���������� ����������� ������
	unsigned char *tx;		// ����� � ������� ��� ������
	unsigned char result;	// ��� ���������� (������� �� �����)
	unsigned short id;		// ���������� ������������� ip �������
}udp_request;

void mac_request(unsigned char *ip);	// ������ � ���� ��� ������ MAC ������ �� �������� IP ������
void udp_cmd(udp_request *req);			// ������� � ���� ������� 
void id_list_init(void);				// ��������� ������ id � ip ������� � ������� ���� ��������� � ������ �������
void add_id(udp_request *r);
udp_request* get_req_by_id(unsigned short id);
ip_pkt* get_buf_ip_pkt();
void clear_buf_ip_pkt();

