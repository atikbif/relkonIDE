#define SPI_CS_HIGH()    GPIO_SetBits(GPIOB, GPIO_Pin_10)
#define SPI_CS_LOW()    GPIO_ResetBits(GPIOB, GPIO_Pin_10)

void _SPI_init(void);
unsigned char SPI_SendByte(unsigned char byte);
void read_data(unsigned char adr_H,unsigned char adr_L,unsigned char size,unsigned char* ptr);
void write_data(unsigned char adr_H,unsigned char adr_L,unsigned char size,unsigned char* ptr);
void write_enable(void);
