/**
 * @brief:软件pwm控制速度并通过key改变转速，
 * 读取电机脉冲计数，获得电机速度显示在LED上
 * @author:李昊佳
 * @data:2019-11-30
*/
#include <reg52.h>

int pwm_count = 0; //pwm计数
int pwm_set = 0;   //pwm设定
sbit motor = P3 ^ 0;
sbit key = P3 ^ 1;

void main()
{
    //定时器0初始化，用作计数器
    TMOD |= 0x06;
    TH0 = 0;
    TL0 = 0;
    TF0 = 0;
    TR0 = 1;
    //定时器1初始化 1ms中断一次 产生软件pwm
    //定时器1同时复用，用于脉冲计数定时，计算速度
    //400ms读取一次计数器数字 表示速度
    TMOD |= 0x10;
    TH1 = (65536 - 1000) / 256;
    TL1 = (65536 - 1000) % 256;
    TF1 = 0;
    IT1 = 1;
    EA = 1;
    TR1 = 1;

    while (1)
    {
        //key控制pwm数值
        if (key == 0)
        {
            pwm_set += 10;
            if (pwm_set > 100)
                pwm_set = 0;
            while (key == 0)
                ;
        }
    }
}

void timer_1() interrupt 3
{
    static unsigned int timer_count = 0;
    TH1 = (65536 - 1000) / 256;
    TL1 = (65536 - 1000) % 256;
    TF0 = 0;
    //软件产生pwm
    pwm_count++;
    if (pwm_count >= 100)
    {
        pwm_count = 0;
    }
    if (pwm_count >= pwm_set)
    {
        motor = 0;
    }
    else
    {
        motor = 1;
    }

    //计算速度定时400ms
    timer_count++;
    if (timer_count > 400)
    {
        timer_count = 0;
        P1 = TL0;  //LED显示速度
        TL0 = 0;   //计数器清零
    }
}
