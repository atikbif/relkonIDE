#define UDP_WR_USER			1
#define UDP_RD_USER			2
#define UDP_WAIT_ANSWER		0
#define UDP_CORRECT_ANSWER	1
#define ID_LIST_CNT			20

#include "k_udp.h"

typedef struct{
	unsigned char cmd;		// код команды - чтение/запись
	unsigned char ip[4];		// ip адрес получателя
	unsigned short addr;		// адрес ячейки памяти
	unsigned short cnt;		// количество регистров для чтения записи
	unsigned char *rx;		// буфер для сохранения прочитанных данных
	unsigned char *tx;		// буфер с данными для записи
	unsigned char result;	// код результата (получен ли ответ)
	unsigned short id;		// внутренний идентификатор ip команды
}udp_request;

void mac_request(unsigned char *ip);	// запрос в сеть для чтения MAC адреса по значению IP адреса
void udp_cmd(udp_request *req);			// послать в сеть команду 
void id_list_init(void);				// обнуление списка id и ip адресов к которым было обращение в режиме мастера
void add_id(udp_request *r);
udp_request* get_req_by_id(unsigned short id);
ip_pkt* get_buf_ip_pkt();
void clear_buf_ip_pkt();

