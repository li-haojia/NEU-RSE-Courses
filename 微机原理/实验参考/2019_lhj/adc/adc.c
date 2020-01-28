/**
 * brief:ADC
 * author:¿ÓÍªº—
 * data 2019-12-23
 * */

#include <reg52.h>
xdata unsigned char PORTA _at_ 0x9000;
xdata unsigned char PORTB _at_ 0x9001;
xdata unsigned char PORTC _at_ 0x9002;
xdata unsigned char PORTCMD _at_ 0x9003;

xdata unsigned char ADC0809_IN0 _at_ 0x8000;
xdata unsigned char ADC0809_IN1 _at_ 0x8001;

unsigned char busy_flag = 0;
sbit busy_line = P3 ^ 2;

void int0_init(void)
{

    IT0 = 0;
    EX0 = 1;
    EA = 1;
}

void main()
{
    PORTCMD = 0x80; //≥ı ºªØ
    //int0_init();
    while (1)
    {
        /* if(busy_flag==0)
        {

            ADC0809_IN0=0;
            busy_flag=1; 
        }  
           */
        ADC0809_IN0 = 0;
        while (busy_line == 0)
            ;
        PORTA = ADC0809_IN0;
    }
}

/*void int0_isr() interrupt 0
{
    PORTA = ADC0809_IN0;
    busy_flag = 0;
}*/
