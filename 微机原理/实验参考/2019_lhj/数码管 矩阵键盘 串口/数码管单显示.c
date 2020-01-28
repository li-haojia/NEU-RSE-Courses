/**
 * @brief: 数码显示
 * @author: 李昊佳
 * @date:2019-12-7
 * 
 * */
#include <reg52.h>

xdata unsigned char DIS_PORT _at_ 0x8004;
xdata unsigned char DIS_CS_PORT _at_ 0x8002;


unsigned char code dis[]={0x3f,0x06,0x5b,0x4f, 0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0}; //16代表不显示

unsigned char num[6]={4,2,3,4,5,6};  //改变这个数组的数 对应改变显示的数

void delayms(unsigned int tt)		//@12.000MHz
{
	unsigned char i, j;
    while(--tt)
    {
        i = 2;
        j = 239;
        do
        {
            while (--j);
        } while (--i);
    }
}

//显示函数，需要不断调用，调用一次进行一次刷新
void display()
{
    char i;
    for (i = 0; i < 6; i++)
    {
        DIS_PORT = 0;  //关显示，防止残影
        DIS_CS_PORT = 0x01 << i; //选择刷新的数码管（计算位码）
        DIS_PORT = dis[num[i]];  //送入显示字符

        delayms(2);
    }
}

void main()
{

    while (1)
    {
        display();
    }

}
