#ifndef FRAM_H_
#define FRAM_H_

#include "hfram.h"

void write_fram(unsigned short adr,unsigned char size,unsigned char* ptr);
void read_fram(unsigned short adr,unsigned char size,unsigned char* ptr);
unsigned short get_ee_addr(unsigned short num);

#endif /* FRAM_H_ */
