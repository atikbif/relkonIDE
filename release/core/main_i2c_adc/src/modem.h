#ifndef MODEM_H_
#define MODEM_H_

void get_number(unsigned char* ptr);
void set_password(unsigned char* ptr);
unsigned char get_sms_text(unsigned char can,unsigned char* ptr,unsigned char max);
unsigned char read_sms(unsigned char can,unsigned char i);
unsigned char get_index(unsigned char can);
void del_sms(unsigned char can_num,unsigned char i);
void call_data7(unsigned char can_num,unsigned char* num);
void call7(unsigned char can_num,unsigned char* num);
void call_data(unsigned char can_num,unsigned char* num);
void call(unsigned char can_num,unsigned char* num);
void send_sms(unsigned char can_num,unsigned char* num,unsigned char* sms);
void write_head(unsigned char can_num);
void clear_buf(unsigned char can_num);
void mqtt_connect(unsigned char can_num, char* client_id, char* user_name, char* user_password);
void mqtt_publish(unsigned char can_num, char* topic, unsigned char* data_ptr, unsigned short data_length);

#endif /* MODEM_H_ */
