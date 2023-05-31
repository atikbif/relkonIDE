#ifndef CRC_H_
#define CRC_H_

unsigned int GetCRC16 (unsigned char* ptr,unsigned int cnt);
void update_CRC4(unsigned char* ptr,unsigned char val);
unsigned char CheckLRC(unsigned char* ptr,unsigned short lng);
unsigned char getLRC(unsigned char* ptr,unsigned short lng);

#endif /* CRC_H_ */
