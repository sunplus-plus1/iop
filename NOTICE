1.compile

Support SDCC and KEIL compilation
SDCC:
install sdcc toolchain in the following 2 ways:
1、apt install sdcc
2、https://sourceforge.net/projects/sdcc/files/

Compile command:
normal : make
standby: make STANDBY=1

KEIL:
Click the build button directly on the project

2.OUTPUT
Under normal compilation conditions , iopnormal.c file will be generated in the out directory
Under Standby compilation conditions, iopstandby.c file will be generated in the out directory
Replace this two files with the same files under linux/kernel/drivers/misc/iop/.

3.printf
iop not have its own UART , so store the printf data in IOP_DATA8, and output by arm926 .

#define DEBUG_ENABLE    // enable/disable printf function

#define PRINTF_REG_IOP_2_RISC               IOP_DATA8_L      // sync transmit status
#define PRINTF_DATA_IOP_2_RISC              IOP_DATA8_H     // printf data ,iop transmit to arm926
/*----------------------------------------------------------------------------------------------------
|PRINTF_DATA_IOP_2_RISC   | 7:0 |   data            write by IOP,read by RISC
|                                                   this register is used for transmit data from IOP to RISC
----------------------------------------------------------------------------------------------------
|PRINTF_REG_IOP_2_RISC    | 7:2 |   reserved
|                         |  1  |   tx flag         read/write by RISC or IOP
|                                                   1:IOP send 1byte data in IOP_DATA_8_H to RISC. set to 1;
|                                                   0:RISC have read temp buf from IOP. clear to 0;
|                         |  0  |   tx empty flag   read/write by IOP only
|                                                   1:tx buf is empty, not send data to RISC
|                                                   0:tx buf is not empty.
----------------------------------------------------------------------------------------------------*/

4.timer

#define TIME0_MODE0              /*  118.51us */
//#define TIME0_MODE1            /*  2133.33us */
//#define TIME0_MODE2            /*  7.4us */
//#define TIME0_MODE3            /*  8.33us */
//#define TIME1_MODE0            /*  7.4us */
//#define TIME1_MODE1            /*  118.51us */
//#define TIME1_MODE2            /*  2133.33us */
//#define EXT_TIMER1
//#define EXT_TIMER2

The 8051 implements the above timers by default,  You can also modify the TH/TL/TMOD parameters in timer.c/Int_Vec.c to configure
different timing times according to your own needs ,timer0/timer1 can only work in 1 mode at the same time

timer0 responds in timer0_isr interrupt function.
Timer1 responds in timer1_isr interrupt function.
EXT_TIMER1/2 responds in exo_isr interrupt function, the interrupt is distinguished by the bit of the IntFlag register(0x39).

5.i2c slave

#define REG_RISC_2_IOP         IOP_DATA10_L   //sync transmit status
#define DATA_RISC_2_IOP        IOP_DATA10_H   // i2c send data to i2c master, data risc transmit to IOP
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

#define REG_IOP_2_RISC            IOP_DATA11_L   //sync transmit status
#define DATA_IOP_2_RISC           IOP_DATA11_H   // i2c receive data from i2c master,and  iop transmit data to risc,
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
#define I2C_ENABLE_BIT             (0x01<<7)      // enable/disable  i2c slave
#define I2C_SLAVE_ADDRESS          (0x7f<<0)      // i2c slave address,
/**************************************************************************************************
----------------------------------------------------------------------------------------------------
|REG_I2C_ADDR         |  7  |   i2c enable        write by RISC,read by IOP
|                                                 1: enable i2c slave
|                                                 0: disable i2c slave
|                     | 6:0 |   i2c slave addr    write by RISC
|                                                 i2c slave address,set by RISC
----------------------------------------------------------------------------------------------------
**************************************************************************************************/
