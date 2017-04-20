#ifndef FCUCSETTINGS_H
#define FCUCSETTINGS_H


class FCUCSettings
{
    int eMemSize;
    static const int min_value = 10;
    static const int max_value = 1000;
public:
    FCUCSettings();
    void setEMemSize(int value) {if((value>=min_value)&&(value<=max_value)) eMemSize = value;}
    int getEMemsize(void) const {return eMemSize;}
};

#endif // FCUCSETTINGS_H
