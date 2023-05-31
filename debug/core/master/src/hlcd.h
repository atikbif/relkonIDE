#define UART5_DR_Base  0x40005004

#define SEC_TYPE                0
#define MIN_TYPE              1
#define HOUR_TYPE           2
#define DATE_TYPE            3
#define MONTH_TYPE      4
#define YEAR_TYPE       5

void init_lcd_canal(void);
void write_lcd(unsigned short cnt);
void rst_pu_toggle(void);
