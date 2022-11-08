#include <stdio.h>
#include "string.h"

#include "i2c_slave_common.h"
#include "i2c_slave.h"

unsigned int  tx_head=0,tx_tail=0,rx_head=0,rx_tail=0;
unsigned char  rx_data_buf[I2C_RING_FIFO_LEN],tx_data_buf[I2C_RING_FIFO_LEN];

/*  i2c master send data to IOP */
int store_data(int value)
{
    tx_data_buf[tx_tail] = value;
    tx_tail = (tx_tail+1)%I2C_RING_FIFO_LEN;

    if((REG_IOP_2_RISC & I2C_TX_EMPTY_MASK) == I2C_TX_EMPTY_MASK)
    {
        IOP_WRITE_DATA(REG_IOP_2_RISC,I2C_TX_EMPTY_MASK,0<<I2C_TX_EMPTY_POS);
    }
    return 1;
}
/*  i2c master get data from IOP */
int load_data(void)
{
    unsigned int value;
    if(rx_tail == rx_head)
    {
        return 0xFF; // iop rx buf is empty
    }
    value = rx_data_buf[rx_head];
    rx_head = (rx_head+1)%I2C_RING_FIFO_LEN;

    if((REG_RISC_2_IOP & I2C_RX_BUF_FULL_MASK) == I2C_RX_BUF_FULL_MASK)
    {
        IOP_WRITE_DATA(REG_RISC_2_IOP,I2C_RX_BUF_FULL_MASK,0<<I2C_RX_BUF_FULL_POS);
    }
    return value;
}

#if 0
int tx_available(void)
{
    return (!(((tx_tail+1)%I2C_RING_FIFO_LEN) == tx_head));
}
#endif

int rx_available(void)
{
    return (!(((rx_tail+1)%I2C_RING_FIFO_LEN) == rx_head));
}
/*  i2c master send data to IOP by store_data(), store data in IOP_DATA for CA7 get */
void i2c_slave_save_data()
{
    if((REG_IOP_2_RISC & I2C_TX_FLAG_MASK) == 0x0) // no data in DATA_IOP_2_RISC
    {
        if(tx_tail == tx_head) // no data in tx_data_buf or get out all data of tx_data_buf
        {
            IOP_WRITE_DATA(REG_IOP_2_RISC,I2C_TX_EMPTY_MASK,1<<I2C_TX_EMPTY_POS);
            return;
        }

        DATA_IOP_2_RISC = tx_data_buf[tx_head];
        tx_head = (tx_head+1)%I2C_RING_FIFO_LEN;
        IOP_WRITE_DATA(REG_IOP_2_RISC,I2C_TX_FLAG_MASK,1<<I2C_TX_FLAG_POS);
    }
}
/*  IOP get data from CA7,and store in rx_buf for i2c master get by load_data() */
void i2c_slave_get_data()
{
    // no data to get
    if((REG_RISC_2_IOP & I2C_RX_FLAG_MASK) == 0x0)
        return;

    // rx buf full
    if((REG_RISC_2_IOP & I2C_RX_BUF_FULL_MASK) == I2C_RX_BUF_FULL_MASK)
    {
        return;
    }
    rx_data_buf[rx_tail] = DATA_RISC_2_IOP;
    rx_tail = (rx_tail+1)%I2C_RING_FIFO_LEN;

    IOP_WRITE_DATA(REG_RISC_2_IOP,I2C_RX_FLAG_MASK,0<<I2C_RX_FLAG_POS);

    if(rx_available() == 0)
    {
        IOP_WRITE_DATA(REG_RISC_2_IOP,I2C_RX_BUF_FULL_MASK,1<<I2C_RX_BUF_FULL_POS);
        return;
    }
}

void send_irq_to_risc()
{
    Trigger2risc |= 0x01;
}

void i2c_data_init()
{
    memset(rx_data_buf,0x0,I2C_RING_FIFO_LEN);
    memset(tx_data_buf,0x0,I2C_RING_FIFO_LEN);

    DATA_IOP_2_RISC = 0x0;
    REG_IOP_2_RISC = 0x0;
    IOP_WRITE_DATA(REG_IOP_2_RISC,I2C_TX_EMPTY_MASK,1<<I2C_TX_EMPTY_POS);
    IOP_WRITE_DATA(REG_IOP_2_RISC,I2C_TX_FLAG_MASK,0<<I2C_TX_FLAG_POS);

    DATA_RISC_2_IOP = 0x0;
    REG_RISC_2_IOP = 0x0;
    IOP_WRITE_DATA(REG_RISC_2_IOP,I2C_RX_FLAG_MASK,0<<I2C_RX_FLAG_POS);
    IOP_WRITE_DATA(REG_RISC_2_IOP,I2C_RX_BUF_FULL_MASK,0<<I2C_RX_BUF_FULL_POS);

}
