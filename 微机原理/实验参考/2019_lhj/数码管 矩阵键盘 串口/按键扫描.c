#include <reg51.h>

//定义接口

xdata unsigned char KEY_CS_PORT _at_ 0x8002; //按键列接口
xdata unsigned char KEY_PORT _at_ 0x8001;    //按键行


//按键表，用以快速修改键值含义 16对应啥也不显示  其他对应按键数值
unsigned char code key_value[6][4] = {{16, 16, 16, 16}, {16, 16, 16, 16}, {0x0d, 0x0c, 0x0b, 0x0a}, {0x0e, 3, 6, 9}, {0x0f, 2, 5, 8}, {0, 1, 4, 7}};

//按键列选择表 用于循环扫面时候端口赋值，0代表选中该列
unsigned char code key_cs[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};

//按键扫描函数
unsigned char keyscan()
{
    char i;
    //DIS_PORT = 0;  //关显示 由于复用  防止冲突
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
                        // //调用显示函数，避免按下按键时候数码管灭掉
                        // display(); 
                        // //将列选择重新设置为当前扫描列
                        // KEY_CS_PORT = key_cs[i];  
                    };
                    return key_value[i][0];
                    break;
                case 0x0d://第二行按下
                    while (KEY_PORT != 0x0f)  //松手检测，防止多次返回
                    {
                        // //调用显示函数，避免按下按键时候数码管灭掉
                        // display();  
                        // //将列选择重新设置为当前扫描列           
                        // KEY_CS_PORT = key_cs[i]; 
                    };
                    return key_value[i][1];
                    break;
                case 0x0b: //第三行按下
                    while (KEY_PORT != 0x0f)  //松手检测，防止多次返回
                    {
                        // //调用显示函数，避免按下按键时候数码管灭掉
                        // display();  
                        //  //将列选择重新设置为当前扫描列
                        // KEY_CS_PORT = key_cs[i]; 
                    };
                    return key_value[i][2];
                    break;
                case 0x07: //第四行按下
                    while (KEY_PORT != 0x0f)  //松手检测，防止多次返回
                    {
                        // display();               
                        // KEY_CS_PORT = key_cs[i];  
                    };
                    return key_value[i][3];
                    break;
                default:  //乱码或者多个按键同时按下
                    while (KEY_PORT != 0x0f)  //松手检测，防止多次返回
                    {
                        // display();
                        // KEY_CS_PORT = key_cs[i];
                    };
                    return 255;
                }
            }
        }
    }
    return 255;  //返回255表示啥也没按下
}