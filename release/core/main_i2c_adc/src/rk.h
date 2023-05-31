#ifndef RK_H_
#define RK_H_

#include "request.h"

unsigned short get_software_ver(request* req);
unsigned short get_hardware_ver(request* req);
unsigned short get_obj_name(request* req);
unsigned short get_can_name(request* req);
unsigned short read_mem(request* req);
unsigned short read_time(request* req);
unsigned short read_frmem(request* req);
unsigned short read_ram(request* req);
unsigned short read_flash(request* req);
unsigned short read_preset(request* req);
unsigned short write_mem(request* req);
unsigned short write_time(request* req);
unsigned short write_frmem(request* req);
unsigned short write_ram(request* req);
unsigned short write_preset(request* req);
unsigned short read_io(request* req);
unsigned short write_io(request* req);
unsigned short exchange_cmd(request* req);
void reset_cmd(void);
unsigned short check_ascii_rk(request* req);


#endif /* RK_H_ */
