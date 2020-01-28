#include <reg52.h>

#define STEP 8              //相位数
#define DELAY_FACTOR 5     //延时系数（1*DELAY_FACTOR--8*DELAY_FACTOR）
 //相位表
unsigned char code motor_state[STEP] = {0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09}; 

sbit start_button = P3^3;  //定义启停接口
sbit rotation = P3^4;      //定义旋转方向

void delay1ms(unsigned int tt)      //@12.000MHz
{
    unsigned char i, j;

    while(--tt)
    {
        i = 2;
        j = 239;
        do
        {
            while (--j);
        }
        while (--i);
    }
}

unsigned int speed_get(unsigned char i)  //根据P3口状态设定速度
{
    unsigned char speed = i&0x07;       //只使用低三位确保其他位数没有干扰
    speed +=1;
    return speed *DELAY_FACTOR  ;
}

void main()
{
    char i;  //相位序号变量
    unsigned int speed;
    while(1)
    {
        if(start_button)
        {
            P1=motor_state[i];
            speed = speed_get(P3);   
            delay1ms(speed);

            //这样处理可以保证立马切换旋转方向
            if(rotation)
            {
                i++;
                if(i>=STEP)i=0;
            }
            else
            {
                i--;
                if(i<0)i=(STEP -1);
            }
        }

    }
}
