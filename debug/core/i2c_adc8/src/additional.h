#ifndef ADD_H_
#define ADD_H_

#include "inout_def.h"
#include "pult_def.h"
#include "mem_def.h"
#include "exchange_def.h"
#include "sd_def.h"

#include "htime.h"
#include "main.h"
#include "fram.h"
#include "lcd.h"
#include "print.h"
#include "mmb.h"
#include "inout.h"
#include "crc.h"
#include "iodefines.h"
#include "eedefines.h"
#include "error_module.h"
#include "modem.h"
#include "string_func.h"
#include "canal.h"
#include "master.h"

#include "FreeRTOS.h"
#include "stm32f10x_conf.h"

#include "fat_filelib.h"
#include <stdlib.h>
#include "k_udp_master.h"

#define key	_SysKey

extern unsigned char plc[8],err[8];

extern volatile unsigned char led;
extern unsigned short _SysRealTmr, max_load;
extern volatile unsigned char _SysKey;

extern volatile unsigned long* led_ptr;
extern volatile unsigned long* key_ptr;

extern volatile unsigned char _Sys_IN[6];
extern volatile unsigned char _Sys_OUT[6];
extern volatile unsigned short _Sys_ADC[8];
extern volatile short _EA[8];
extern volatile unsigned short _Sys_DAC[4];
extern unsigned char   IN[32];
extern unsigned char   OUT[32];
extern unsigned int Sum_err;

extern mmb_ain _ADC;
extern mmb_dac _DAC;
extern volatile unsigned char err_mod[256];

extern unsigned long cpu;
extern plc_stat _Sys;
extern tm times,wr_times;

extern unsigned char tx_mod_buf[MOD_BUF_SIZE];
extern unsigned char rx_mod_buf[MOD_BUF_SIZE];
extern volatile unsigned int rx_mod_cnt;
extern volatile unsigned char prot_enable;

unsigned short c1_n;
unsigned char tmp_sec=0;
unsigned int r1=0,r5=0,r10=0,r100=0,r1000=0;
//
extern volatile unsigned char sd_buf[512];
extern unsigned char sd_stat;
extern unsigned long sd_addr;
//

extern volatile unsigned char EXCHANGE;
extern volatile unsigned char START_P1,START_P2,START_P3,START_P4;
extern volatile unsigned char START_P5,START_P6,START_P7,START_P8;

extern unsigned char TX_1[64],TX_2[64],TX_3[64],TX_4[64],TX_5[64],TX_6[64],TX_7[64],TX_8[64];
extern unsigned char RX_1[64],RX_2[64],RX_3[64],RX_4[64],RX_5[64],RX_6[64],RX_7[64],RX_8[64];
extern unsigned char TX[64];
extern unsigned char RX[64];

extern unsigned short sd_err;

extern unsigned short rx_req_cnt_mmb;
extern unsigned short rx_req_cnt_pc;
extern unsigned short rx_req_cnt_pu;
extern unsigned short rx_req_cnt_pr;

#endif
