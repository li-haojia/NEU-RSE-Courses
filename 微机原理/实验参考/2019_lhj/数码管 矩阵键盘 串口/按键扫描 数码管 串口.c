/**
 * @brief: 串口收发、矩阵键盘扫描、数码显示
 * 接收端与发送端一体
 * @author: 李昊佳
 * @date:2019-12-7
 * 
 * Using GBK encoding
 * */

#include <reg51.h>

//定义接口
xdata unsigned char DIS_PORT _at_ 0x8004;    //显示段位
xdata unsigned char DIS_CS_PORT _at_ 0x8002; //显示位码
xdata unsigned char KEY_CS_PORT _at_ 0x8002; //按键列接口
xdata unsigned char KEY_PORT _at_ 0x8001;    //按键行

//unsigned char code dis_cs[]={1,2,4,8,16,32};
//数码管段码表0-9 A-F 最后一个代表啥也不显示
unsigned char code dis[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0};
//按键表，用以快速修改键值含义 16对应啥也不显示  其他对应按键数值
unsigned char code key_value[6][4] = {{16, 16, 16, 16}, {16, 16, 16, 16}, {0x0d, 0x0c, 0x0b, 0x0a}, {0x0e, 3, 6, 9}, {0x0f, 2, 5, 8}, {0, 1, 4, 7}};

//按键列选择表 用于循环扫面时候端口赋值，0代表选中该列
unsigned char code key_cs[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
//数码管显示数组缓存，只要更新这个数组即可显示对应的数字  16表示啥也不显
unsigned char num[6] = {0, 16, 16, 16, 16, 16};

void delayms(unsigned int tt) //@12.000MHz
{
    unsigned char i, j;
    while (--tt)
    {
        i = 2;
        j = 239;
        do
        {
            while (--j)
                ;
        } while (--i);
    }
}

//串口初始化 9600 全双工
void uart_init()
{

    TMOD = 0x20;
    SCON = 0x50;
    //TH1=256-(12000000/(384*9600));
    //TL1=256-(12000000/(384*9600));
    TH1 = 0xfd;
    TL1 = 0xfd;
    EA = 1;
    ES = 1;
    TR1 = 1;
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

//按键扫描函数
unsigned char keyscan()
{
    char i;
    DIS_PORT = 0;  //关显示 由于复用  防止冲突
    //扫描六列
    for (i = 0; i < 6; i++)
    {
        KEY_CS_PORT = key_cs[i];//扫描当前列的IO，将当前列IO设置为低电平

        if (KEY_PORT != 0x0F)  //有按键按下
        {
            delayms(5);  //消抖
            if (KEY_PORT != 0x0F)
            {
                switch (KEY_PORT)
                {
                case 0x0e://第一行按下
                    while (KEY_PORT != 0x0f)  //松手检测，防止多次返回
                    {
                        display();           //调用显示函数，避免按下按键时候数码管灭掉
                        KEY_CS_PORT = key_cs[i];  //将列选择重新设置为当前扫描列
                    };
                    return key_value[i][0];
                    break;
                case 0x0d://第二行按下
                    while (KEY_PORT != 0x0f)  //松手检测，防止多次返回
                    {
                        display();             //调用显示函数，避免按下按键时候数码管灭掉
                        KEY_CS_PORT = key_cs[i]; //将列选择重新设置为当前扫描列
                    };
                    return key_value[i][1];
                    break;
                case 0x0b: //第三行按下
                    while (KEY_PORT != 0x0f)  //松手检测，防止多次返回
                    {
                        display();              //调用显示函数，避免按下按键时候数码管灭掉
                        KEY_CS_PORT = key_cs[i];  //将列选择重新设置为当前扫描列
                    };
                    return key_value[i][2];
                    break;
                case 0x07: //第四行按下
                    while (KEY_PORT != 0x0f)  //松手检测，防止多次返回
                    {
                        display();                //调用显示函数，避免按下按键时候数码管灭掉
                        KEY_CS_PORT = key_cs[i];  //将列选择重新设置为当前扫描列，用于后面松手检测
                    };
                    return key_value[i][3];
                    break;
                default:  //乱码或者多个按键同时按下
                    while (KEY_PORT != 0x0f)  //松手检测，防止多次返回
                    {
                        display();
                        KEY_CS_PORT = key_cs[i];
                    };
                    return 255;
                }
            }
        }
    }
    return 255;  //返回255表示啥也没按下
}

void main()
{
    int i;
    unsigned char a = 255;
    uart_init();
    while (1)
    {
        display();

        a = keyscan();
        //有按键按下发送数据
        if (a != 255)
        {
            SBUF = a;  
        }
    }
}

//串口中断函数
void UART() interrupt 4
{
    char i;
    if (RI == 1) //如果接收到计算机发的数据
    {
        //将显示数据向前平移 新的数据放在0号数码管
        for (i = 6; i > 0; i--)
        {
            num[i] = num[i - 1];
        }

        num[0] = SBUF; //取出数据
        RI = 0;        //清除标志位
    }
    if (TI == 1) //如果发送完毕
    {
        TI = 0; //清除标志位
    }
}
