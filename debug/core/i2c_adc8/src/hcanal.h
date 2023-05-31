#define USART2_DR_Base			0x40004404
#define UART4_DR_Base			0x40004C04

void write_canal(unsigned short count);
void write_canal2(unsigned short count);
void init_pc_canal(void);
void pc_message_bin(void);
void pc_message_ascii(void);
void init_prog_canal(void);
void prog_message_bin(void);
void prog_message_ascii(void);
unsigned long get_pc_tmr(void);
unsigned long get_pr_tmr(void);
void clear_pc_toggle_pin();
char get_pc_toggle_pin_state();
void clear_pr_toggle_pin();
char get_pr_toggle_pin_state();
