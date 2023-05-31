#include "request.h"

#define PLC1    (plc[0])
#define PLC2    (plc[1])
#define PLC3    (plc[2])
#define PLC4    (plc[3])
#define PLC5    (plc[4])
#define PLC6    (plc[5])
#define PLC7    (plc[6])
#define PLC8    (plc[7])

#define ERR1    (err[0])
#define ERR2    (err[1])
#define ERR3    (err[2])
#define ERR4    (err[3])
#define ERR5    (err[4])
#define ERR6    (err[5])
#define ERR7    (err[6])
#define ERR8    (err[7])

void exchange_work(void);
void exch_answer(request* req);
void set_exchange_net_addr(unsigned char plcNum, unsigned char netAddr);
