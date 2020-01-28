#include <reg52.h>

int timer_count = 0;
sbit LED=P1^0;
void main()
{
    TMOD=0x10;
    //定时器初值计算方法 12mhz
    //(65536-us)/256   (65536-us)%256
    TH1=(65536-50000)/256;
    TL1=(65536-50000)%256;
    TF1=0;
    TR1=1;
    while(1)
    {
        if(TF1==1)
        {
            TF1=0;
            TH1=(65536-50000)/256;
            TL1=(65536-50000)%256;
            timer_count++;
            if(timer_count>=(1000/50))
            {
            timer_count=0;
                LED=~LED;
            }
        }
    }

}
