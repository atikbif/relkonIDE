#ifndef HTIME_H_
#define HTIME_H_

void init_timer(void);
void set_time(void);
void get_time(void);
void init_calendar(void);
void RTC_Config(void);

typedef struct
{
    volatile unsigned char sec;
    volatile unsigned char min;
    volatile unsigned char hour;
    volatile unsigned char date;
    volatile unsigned char month;
    volatile unsigned char year;
    volatile unsigned char day;
}tm;

#endif


