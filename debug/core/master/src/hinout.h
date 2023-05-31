#define MOD_BUF_SIZE    					512
#define USART1_DR_Base						0x40013804
#define ANSWER_PAUSE    					45000

inline void baud_19200(void);
void write_module(unsigned short count);
void dio_conf(void);
void init_mb_canal(void);
void clear_mb_toggle_pin();
char get_mb_toggle_pin_state();
unsigned char read_din(unsigned char num);
void dout_settings(void);
void din_settings(void);
void write_dout(unsigned char num, unsigned char val);
unsigned long get_mmb_tmr(void);
