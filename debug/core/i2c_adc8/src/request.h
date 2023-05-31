#ifndef REQUEST_H_
#define REQUEST_H_

#define CAN_PR	0
#define CAN_PC	1
#define CAN_MB	2
#define CAN_PU	3
#define CAN_RF	4
#define CAN_UDP 5
#define CAN_TCP 6
#define CAN_WF	7

#define BIN_MODE	0
#define ASCII_MODE	1

typedef struct
{
	unsigned short addr;
	unsigned long laddr;
	unsigned short cnt;
	unsigned char* tx_buf;
	unsigned char* rx_buf;
	unsigned char can_name;
	unsigned char mode;
}request;

#endif /* REQUEST_H_ */
