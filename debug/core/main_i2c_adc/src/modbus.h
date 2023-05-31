#ifndef MODBUS_H_
#define MODBUS_H_

#include "request.h"

unsigned short read_coils(request* req);
unsigned short read_dinputs(request* req);
unsigned short read_holdregs(request* req);
unsigned short read_inregs(request* req);
unsigned short write_single_coil(request* req);
unsigned short write_single_reg(request* req);
unsigned short write_multi_regs(request* req);
unsigned short write_multi_coils(request* req);
unsigned short check_ascii_modbus(request* req);


#endif /* MODBUS_H_ */
