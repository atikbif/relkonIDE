#ifndef HTTP_DATA_H_
#define HTTP_DATA_H_

#include "k_http.h"

void web_file_init(void);
unsigned char get_webdyn(flist* fdyn,unsigned short offset);

#endif /* HTTP_DATA_H_ */
