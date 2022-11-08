#ifndef __I2C_SLAVE_COMMON__
#define __I2C_SLAVE_COMMON__

#include "common.h"

int rx_available(void);
int store_data(int value);
int load_data();
void send_irq_to_risc();
void i2c_slave_save_data();
void i2c_slave_get_data();
void i2c_data_init();
#endif
