#include <reg52.h>

void delay(unsigned int tt)
{
      unsigned char j, k;
      while (--tt)
            for (j = 116; j > 0; j--)
                  for (k = 214; k > 0; k--);                        
}

void main()
{
      int i = 0;

      while (1)
      {
            P1 = 0x01;
            for (i = 0; i < 7; i++)
            {
                  P1 = P1 << 1;
                  delay(10);
            }
            P1 = 0x80;
            for (i = 0; i < 7; i++)
            {
                  P1 = P1 >> 1;
                  delay(10);
            }
      }
}
