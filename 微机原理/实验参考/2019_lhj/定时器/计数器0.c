/**
 * 计数器
 * */

#include <reg52.h>

void main()
{
    TMOD = 0x05;
    /*
    TMOD 
    GATE C/T- M1 M0     GATE C/T- M1 M0  
    C/T- 表示计数或者定时
    */
    TH0 = 0xff;
    TL0 = 0;
    TF0 = 0;

    EA = 1;
    ET0 = 1;
    TR0 = 1;
    
    while (1)
    {
        P1=TL0;
    }
}

void timer_0() interrupt 1
{
    TH0 = 0xff;
    TL0 = 0;
}
