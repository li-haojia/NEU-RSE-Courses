#include <reg52.h>

void main()
{
  char i = 0;
  P1 = 0xF0;
  while (1)
  {
    i = P1;
    i = i >> 4;
    i = ~i;
    i |= 0xF0;
    P1 = i;
  }
}
