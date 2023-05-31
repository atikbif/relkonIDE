#ifndef PULT_DEF_H_
#define PULT_DEF_H_

#define st1	_Sys.S1
#define st2	_Sys.S2
#define st3	_Sys.S3
#define st4	_Sys.S4

#define Z30	_Sys.S1
#define Z31	_Sys.S2
#define Z32	_Sys.S3
#define Z33	_Sys.S4

#define     Z50     key
#define     Z40     led

#define led_1   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&led-0x20000000)*32)+0)))
#define led_2   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&led-0x20000000)*32)+4)))
#define led_3   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&led-0x20000000)*32)+8)))
#define led_4   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&led-0x20000000)*32)+12)))
#define led_5   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&led-0x20000000)*32)+16)))
#define led_6   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&led-0x20000000)*32)+20)))
#define led_7   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&led-0x20000000)*32)+24)))
#define led_8   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&led-0x20000000)*32)+28)))

#define key_1   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&key-0x20000000)*32)+0)))
#define key_2   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&key-0x20000000)*32)+4)))
#define key_3   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&key-0x20000000)*32)+8)))
#define key_4   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&key-0x20000000)*32)+12)))
#define key_5   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&key-0x20000000)*32)+16)))
#define key_6   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&key-0x20000000)*32)+20)))
#define key_7   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&key-0x20000000)*32)+24)))
#define key_8   (*((volatile unsigned long *)((unsigned long) 0x22000000 + (((unsigned long)&key-0x20000000)*32)+28)))

#endif /* PULT_DEF_H_ */
