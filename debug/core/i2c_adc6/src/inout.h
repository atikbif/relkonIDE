#ifndef INOUT_H_
#define INOUT_H_

#include "hinout.h"
#include "mem_def.h"

#define InOut_DELAY						    ( ( portTickType ) 1 / portTICK_RATE_MS )
#define InOut_TASK_PRIORITY                 ( tskIDLE_PRIORITY + 7 )

void InOutTask( void *pvParameters );
unsigned char get_input(void);
void set_output(unsigned char dt);
void write_module(unsigned short count);
void mb_modbus(void);

#endif
