#include "i2c_slave.h"

#if defined(SDCC)
extern void timer0_isr(void) INTERRUPT_VECTOR 1;
extern void timer1_isr (void) INTERRUPT_VECTOR 3;
extern void ex0_isr (void) INTERRUPT_VECTOR 0;
#endif

void main(void)
{
#ifdef DEBUG_ENABLE
      timer_init();
#endif
    diag_printf("======= I2OP main  %s  =======\n",__TIME__);
    while(1)
    {
        if((I2C_SLAVE_CTL & I2C_ENABLE_BIT) == I2C_ENABLE_BIT)
        {
            i2c_slave_hanle();
        }
    }
}
