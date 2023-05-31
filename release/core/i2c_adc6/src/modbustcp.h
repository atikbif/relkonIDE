#ifndef MODBUSTCP_H_
#define MODBUSTCP_H_

#include "request.h"

unsigned short tcpread_coils(request* req);
unsigned short tcpread_dinputs(request* req);
unsigned short tcpread_holdregs(request* req);
unsigned short tcpread_inregs(request* req);
unsigned short tcpwrite_single_coil(request* req);
unsigned short tcpwrite_single_reg(request* req);
unsigned short tcpwrite_multi_regs(request* req);
unsigned short tcpwrite_multi_coils(request* req);

#endif /* MODBUSTCP_H_ */
