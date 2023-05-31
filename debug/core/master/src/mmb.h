#ifndef MMB_H_
#define MMB_H_

typedef struct{
    unsigned int D1[32];
    unsigned int D2[32];
    unsigned int D3[32];
    unsigned int D4[32];
}mmb_ain;//_ADC;

typedef struct{
    unsigned int D1[32];
    unsigned int D2[32];
}mmb_dac;//_DAC;

typedef struct {
	unsigned short start_byte_num;
	char bit_offset;
	unsigned short *ptr;
}mvar;

typedef struct {
	const char *request;
	unsigned short req_length;
	unsigned short answer_length;
	const mvar *vars_ptr;
	unsigned short var_cnt;
	unsigned char wr_flag;
}mvar_reqs;

void mmb_work(void);

#endif /* MMB_H_ */
