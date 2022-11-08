#include "common.h"

void delay_1us(unsigned int n)
{
  unsigned int  i=1,j=0;
  while(i--);

  for(i=1;i<n;i++)
    for(j=0;j<6;j++);
}

void delay_1ms(unsigned int n)
{
    unsigned int  i=0,j=0;
    for(i=0;i<n;i++)
        for(j=0;j<6870;j++);
}
