#ifndef __I2C_SLAVE__
#define __I2C_SLAVE__

#include <stdio.h>
#include "common.h"

#define I2C_RW_POS            0
#define I2C_RW_MASK           (1<<I2C_RW_POS)

#define I2C_TX_EMPTY_POS      1
#define I2C_TX_EMPTY_MASK     (1<<I2C_TX_EMPTY_POS)

#define I2C_TX_FLAG_POS        2
#define I2C_TX_FLAG_MASK       (1<<I2C_TX_FLAG_POS)

#define I2C_RX_BUF_FULL_POS    3
#define I2C_RX_BUF_FULL_MASK   (1<<I2C_RX_BUF_FULL_POS)

#define I2C_RX_FLAG_POS        4
#define I2C_RX_FLAG_MASK       (1<<I2C_RX_FLAG_POS)

/*IOP ring buf length,for transfer data between IOP and RISC*/
#define I2C_RING_FIFO_LEN      32


#define REG_RISC_2_IOP         IOP_DATA10_L
#define DATA_RISC_2_IOP        IOP_DATA10_H
/**************************************************************************************************
----------------------------------------------------------------------------------------------------
|DATA_RISC_2_IOP   | 7:0 |   data          write by RISC,read by IOP
|                                          this register is used for transmit data from RISC to IOP
----------------------------------------------------------------------------------------------------
|REG_RISC_2_IOP    | 7:5 |   reserved
|                  |  4  |   rx flag       read/write by RISC or IOP
|                                          1:RISC send 1byte data in IOP_DATA_10_H to IOP. set to 1;
|                                          0:IOP have read temp buf from RISC. clear to 0;
|                  |  3  |   rx full flag  read/write by IOP only
|                                          1:rx buf is full, not receive data from RISC
|                                          0:rx buf is not full.
|                  | 2:0 |   reserved
----------------------------------------------------------------------------------------------------
**************************************************************************************************/

#define REG_IOP_2_RISC            IOP_DATA11_L
#define DATA_IOP_2_RISC           IOP_DATA11_H
/**************************************************************************************************
----------------------------------------------------------------------------------------------------
|DATA_IOP_2_RISC   | 7:0 |   data           write by IOP,read by RISC
|                                           this register is used for transmit data from IOP to RISC
----------------------------------------------------------------------------------------------------
|REG_IOP_2_RISC    | 7:3 |   reserved
|                  |  2  |   tx flag        read/write by RISC or IOP
|                                           1:IOP send 1byte data in IOP_DATA_11_H to RISC. set to 1;
|                                           0:RISC have read temp buf from IOP. clear to 0;
|                  |  1  |   tx empty flag  read/write by IOP only
|                                           1:tx buf is empty, not send data to RISC
|                                           0:tx buf is not empty.
|                  |  0  |   reserved
----------------------------------------------------------------------------------------------------
**************************************************************************************************/

#define I2C_SLAVE_CTL              IOP_DATA0_L
#define I2C_ENABLE_BIT             (0x01<<7)
#define I2C_SLAVE_ADDRESS          (0x7f<<0)
/**************************************************************************************************
----------------------------------------------------------------------------------------------------
|REG_I2C_ADDR         |  7  |   i2c enable        write by RISC,read by IOP
|                                                 1: enable i2c slave
|                                                 0: disable i2c slave
|                     | 6:0 |   i2c slave addr    write by RISC
|                                                 i2c slave address,set by RISC
----------------------------------------------------------------------------------------------------
**************************************************************************************************/


/**************************************************************************************************
default  pin number : SCL:G_MX13  SDA: G_MX12

SDA: G_MX12 = GPIO_P[1]_[4]
I2C_SDA_BIT:  4
GPIO_IO1_CFG/GPIO_PORT1_OUT/GPIO_PORT1_IN

SCL: G_MX22 = GPIO_P[2]_[6]
I2C_SCL_BIT:  6
GPIO_IO2_CFG/GPIO_PORT2_OUT/GPIO_PORT2_IN
**************************************************************************************************/


 #define I2C_SDA_BIT                    (1)
 #define I2C_SCL_BIT                    (2)

 #define I2C_SDA_CFG                    GPIO_IO4_CFG
 #define I2C_SDA_PORT_OUT               GPIO_PORT4_OUT
 #define I2C_SDA_PORT_IN                GPIO_PORT4_IN

 #define I2C_SCL_CFG                    GPIO_IO4_CFG
 #define I2C_SCL_PORT_OUT               GPIO_PORT4_OUT
 #define I2C_SCL_PORT_IN                GPIO_PORT4_IN


#define IOP_WRITE_DATA(ADDR,CLEARMASK,SETMASK)   (ADDR = (ADDR&(~(CLEARMASK))|(SETMASK)))

typedef enum{
    I2C_SLAVE_IDLE=0,
    I2C_SLAVE_START,
    I2C_SLAVE_READ_ADDRESS,
    I2C_SLAVE_RW_DATA,
    I2C_SLAVE_WAIT_STOP,
    I2C_SLAVE_STOP,
}st_i2c_status;

void i2c_slave_hanle(void);

#endif
