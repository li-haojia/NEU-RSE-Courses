#include <reg52.h>

int timer_count = 0;
sbit LED = P1 ^ 0;
void main()
{
    TMOD = 0x10;
    TH1 = (65536 - 50000) / 256;
    TL1 = (65536 - 50000) % 256;
    TF1 = 0;
    //开总中断
    EA = 1;
    //开定时器1中断
    ET1 = 1;
    //启动定时器1
    TR1 = 1;
    while (1)
    {
        ;
    }
}

void timer_1() interrupt 3
{           
    TH1 = (65536 - 50000) / 256;
    TL1 = (65536 - 50000) % 256;
    timer_count++;
    if (timer_count >= 1000 / 50)
    {
        timer_count=0;
        LED = ~LED;
    }
}
