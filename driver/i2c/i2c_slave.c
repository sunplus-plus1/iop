#include "common.h"
#include "i2c_slave_common.h"
#include "i2c_slave.h"
#include "string.h"

#define TRANS_TIMEOUT                      (10)
static volatile char IDATA i2c_status=I2C_SLAVE_IDLE;
unsigned char IDATA rw_flag = 0;    //0:write  1:read
unsigned int  SCL_PORT,SDA_PORT,SCL_BIT,SDA_BIT,I2C_SLAVE_ADDR;

void i2c_scl_set_in_mode()                  {    I2C_SCL_CFG &=~ (1<<I2C_SCL_BIT);         }

void i2c_sda_set_in_mode()                  {    I2C_SDA_CFG &=~ (1<<I2C_SDA_BIT);         }
void i2c_sda_set_out_mode()                 {    I2C_SDA_CFG |=  (1<<I2C_SDA_BIT);         }

void I2C_SDA_OUT_H()                        {    I2C_SDA_PORT_OUT |=  (1<<I2C_SDA_BIT);    }
void I2C_SDA_OUT_L()                        {    I2C_SDA_PORT_OUT &=~ (1<<I2C_SDA_BIT);    }
int  I2C_SCL_GET()                          {    return ((I2C_SCL_PORT_IN >> I2C_SCL_BIT) & 0x01); }
int  I2C_SDA_GET()                          {    return ((I2C_SDA_PORT_IN >> I2C_SDA_BIT) & 0x01); }

void i2c_wait_scl_low()
{
    volatile int cnt = 0;
    while(1)
    {
        if(!I2C_SCL_GET())
            break;
        if(cnt++ > TRANS_TIMEOUT)
        {
            i2c_status = I2C_SLAVE_STOP;
            break;
        }
    }
}
void i2c_wait_scl_high()
{
    volatile int cnt = 0;
    while(1)
    {
        if(I2C_SCL_GET())
            break;
        if(cnt++ > TRANS_TIMEOUT)
        {
            i2c_status = I2C_SLAVE_STOP;
            break;
        }
    } 
}
int i2c_wait_scl_low_check_staus(void)
{
    char IDATA flag=0;
    volatile int IDATA sda = 0,cnt = 0;;
    while(I2C_SCL_GET())
    {
        if(flag == 0)
        {
            sda = I2C_SDA_GET();
            flag = 1;
        }
        if(sda != I2C_SDA_GET())
        {
            i2c_status = I2C_SLAVE_STOP;
            return -1;
        }
        if(cnt++ > TRANS_TIMEOUT)
        {
            i2c_status = I2C_SLAVE_STOP;
            return -1;
        }
    }
    return 0;
}

int i2c_send_ack()
{
    i2c_wait_scl_low();
    i2c_sda_set_out_mode();
    I2C_SDA_OUT_L();
    i2c_wait_scl_high();
    return 0;
}

int i2c_send_nack()
{
    i2c_wait_scl_low();
    i2c_sda_set_out_mode();
    I2C_SDA_OUT_H();
    i2c_wait_scl_high();
    return 0;
}

int i2c_read_address(void)
{
    int  bitcount = 0,value=0;

    i2c_sda_set_in_mode();

    for(bitcount=0;bitcount<8;bitcount++)
    {
        i2c_wait_scl_low();
        i2c_wait_scl_high();
        value = value << 1;
        value |= I2C_SDA_GET();
    }

    if(((value>>1)&0x7f) == I2C_SLAVE_ADDR)
    {
        i2c_send_ack();
        send_irq_to_risc();
        rw_flag = value&0x01;
        return 0;
    }
    else
    {
        i2c_send_nack();
    }
    return -1;
}

int i2c_read_data(void)
{
    int bitcount = 0,value=0;

    i2c_wait_scl_low();
    i2c_sda_set_in_mode();

    for(bitcount=0;bitcount<8;bitcount++)
    {
        if(i2c_wait_scl_low_check_staus()) // maybe the stop signal
        {
            return -1;
        }
        i2c_wait_scl_high();
        value = value << 1;
        value |= I2C_SDA_GET();
    }
    i2c_send_ack();
    store_data(value);
    return 0;
}

void i2c_send_data(void)
{
    int bitcount = 0;
    int send_mask = 0x80;
    int value = load_data();

    i2c_sda_set_out_mode();

    for(bitcount=0;bitcount < 8;bitcount++)
    {
        i2c_wait_scl_low();

        if(value & send_mask)
            I2C_SDA_OUT_H();
        else
            I2C_SDA_OUT_L();

        i2c_wait_scl_high();
        send_mask = send_mask >> 1;
    }

    i2c_wait_scl_low();
    i2c_sda_set_in_mode();;
    i2c_wait_scl_high();

    if(I2C_SDA_GET() == 0)
    {
       return ;  // master send ack, continue to send data;
    }

    i2c_status = I2C_SLAVE_WAIT_STOP; //master send nack,wait stop signal;
}

//wait status change to start/stop
void i2c_wait_SS()
{
    i2c_wait_scl_low_check_staus();  //wait for sda changed in scl high state
}

void i2c_slave_protocol(void)
{
    switch(i2c_status)
    {
        case I2C_SLAVE_IDLE:
            if((I2C_SCL_GET() == 1)&&(I2C_SDA_GET() == 0))
            {
                EA = 0;
                i2c_status = I2C_SLAVE_READ_ADDRESS;
            }
        break;
        case I2C_SLAVE_READ_ADDRESS:
            if(i2c_read_address() == 0)
            {
                i2c_status = I2C_SLAVE_RW_DATA;
            }
            else
            {
                EA = 1;
                i2c_status = I2C_SLAVE_IDLE;
                i2c_sda_set_in_mode();
            }
        break;
        case I2C_SLAVE_RW_DATA:
            if(!rw_flag)
            {
                i2c_read_data();//master write,slave read
            }
            else
            {
                i2c_send_data(); //master read,slave write
            }
        break;
        case I2C_SLAVE_WAIT_STOP:
            i2c_wait_SS();
            break;
        case I2C_SLAVE_STOP:
            EA = 1;
            i2c_status = I2C_SLAVE_IDLE;
            i2c_sda_set_in_mode();
        break;
        default:
        break;
    }
}

void i2c_slave_init()
{
    diag_printf("  [i2c slave] in \n");

    I2C_SLAVE_ADDR = I2C_SLAVE_CTL & I2C_SLAVE_ADDRESS;

    i2c_scl_set_in_mode();
    i2c_sda_set_in_mode();

    i2c_data_init();

    i2c_status = I2C_SLAVE_IDLE;
}

void i2c_slave_hanle(void)
{
    i2c_slave_init();
    while(1)
    {
        i2c_slave_protocol();
        if(i2c_status == I2C_SLAVE_IDLE)
        {
            if((I2C_SLAVE_CTL & I2C_ENABLE_BIT) == 0)
            {
                diag_printf("  [i2c slave] out \n");
                break;
            }
            i2c_slave_save_data(); //save data to RISC
            i2c_slave_get_data();  //get data from RISC
        }
    }
}
