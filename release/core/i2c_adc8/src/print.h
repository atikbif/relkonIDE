#ifndef PRINT_H_
#define PRINT_H_

void print_long(long val, unsigned char str_num,unsigned char pos,unsigned char s,unsigned char point);
void print_float(float val, unsigned char str_num,unsigned char pos,unsigned char s,unsigned char fpoint);
void print_str(char* ptr, unsigned char str_num,unsigned char pos,unsigned char width);
void print_time(unsigned char str_num,unsigned char pos,unsigned char type);
void print_diagn(void);
unsigned char print_long_buf(unsigned long val,unsigned char* ptr);
unsigned char print_short_buf(short val,unsigned char* ptr);
void print_sms_var(short value, unsigned char *sms_buf, unsigned char width, unsigned char point_pos);
unsigned char print_ip_buf(unsigned char ip1, unsigned char ip2, unsigned char ip3, unsigned char ip4, unsigned char* ptr);
void print_edit(void* val,unsigned char str_num,unsigned char pos,unsigned char width,unsigned char point,unsigned char type);
void print_edit_ee(unsigned short ind,unsigned char str_num,unsigned char pos,unsigned char width,unsigned char point,unsigned char type);
unsigned char* conv_to_ascii(unsigned long value);

#endif /* PRINT_H_ */
