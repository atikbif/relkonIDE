#ifndef LCD_H_
#define LCD_H_

#include "hlcd.h"

#ifndef EDIT_VAR
	#define EDIT_VAR
	typedef struct
	{
		unsigned char pos;
		long          var;
		unsigned char var_num;
		unsigned char search;
		unsigned char search_num;
		long*         point;
		unsigned char mode;
		unsigned char cnt;
		unsigned int  str1,str2,str3,str4;
		unsigned char left,right,p;
		unsigned char type;
		unsigned short index;
		unsigned char curs_x,curs_y;
		unsigned char curs_on;
		unsigned char curs_cnt;
	}ed_var;
#endif

#define KEY_F1		1
#define KEY_L		2
#define KEY_U		4
#define KEY_R		8
#define KEY_E		16
#define KEY_D		32
#define KEY_S		64
#define KEY_F2		128

#define LCD_TASK_PRIORITY				    ( tskIDLE_PRIORITY + 1 )
#define LCD_DELAY			                ( ( portTickType ) 50 / portTICK_RATE_MS )

#define TOGGLE_DIAGN    10



#define CURS_FR1     12
#define CURS_FR2     15

void LCDTask( void *pvParameters );

#endif /* LCD_H_ */
