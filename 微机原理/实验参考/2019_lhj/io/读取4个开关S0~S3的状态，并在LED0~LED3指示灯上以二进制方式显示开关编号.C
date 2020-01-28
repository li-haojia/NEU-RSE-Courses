#include <reg52.h>

void main()
{

 P1=0xF0;
 while(1)
 {
    P1=0xF0;
    switch((P1&0xF0))
    {
    case 0x00:  P1|=0;      break;
    case 0x10:  P1|=1;      break;
    case 0x20:  P1|=2;      break;
    case 0x40:  P1|=3;      break;
    case 0x80:  P1|=4;      break;
    default:    P1|=0x0f;   break;
    }
 }

}
