/**
 * brief:8255A实验2
 * author:李昊佳
 * data 2019-12-16
 * */
xdata unsigned char PORTA _at_ 0x8000;
xdata unsigned char PORTB _at_ 0x8001;
xdata unsigned char PORTC _at_ 0x8002;
xdata unsigned char PORTCMD _at_ 0x8003;

void delay(unsigned int tt)
{
    unsigned char j, k;
    while (--tt)
        for (j = 40; j > 0; j--)
            for (k = 214; k > 0; k--)
                ;
}
void main()
{
    unsigned char a = 0;
    unsigned char b = 0, i = 0;
    unsigned int c = 0;
    PORTCMD = 0x90;
    while (1)
    {
        b = PORTA;
        //计算速度
        c = b >> 2;
        c &= 0x07;
        c += 1;
        c *= 10;
        //判断左移右移
        if (b & 0x02)
        {
            a = 0x01;
            for (i = 0; i < 8; i++)
            {
                PORTB = a;
                a = a << 1;
                delay(c);
            }
        }

        else
        {
            a = 0x80;
            for (i = 0; i < 8; i++)
            {
                PORTB = a;
                a = a >> 1;
                delay(c);
            }
        }
    }
}
