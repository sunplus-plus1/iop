#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#if defined (SDCC)
#include "8051.h"
#else
#include "dp8051xp.h"
#endif
#include "sunplus8051.h"

/*  printf out enable, store data in IOP_DATA8, output by arm926 */
//#define DEBUG_ENABLE

/* timer select */
#define TIME0_MODE0              /*  118.51us */
//#define TIME0_MODE1            /*  2133.33us */
//#define TIME0_MODE2            /*  7.4us */
//#define TIME0_MODE3            /*  8.33us */
//#define TIME1_MODE0            /*  7.4us */
//#define TIME1_MODE1            /*  118.51us */
//#define TIME1_MODE2            /*  2133.33us */
//#define EXT_TIMER1
//#define EXT_TIMER2

#ifdef DEBUG_ENABLE

    #define diag_printf                         printf

    #define PRINTF_REG_IOP_2_RISC               IOP_DATA8_L
    #define PRINTF_DATA_IOP_2_RISC              IOP_DATA8_H

    #define PRINTF_TX_EMPTY_POS                 0
    #define PRINTF_TX_EMPTY_MASK                (1<<PRINTF_TX_EMPTY_POS)
    #define PRINTF_TX_FLAG_POS                  1
    #define PRINTF_TX_FLAG_MASK                 (1<<PRINTF_TX_FLAG_POS)

    void print_data();
#else
    #define diag_printf
#endif

#ifdef STANDBY
#undef DEBUG_ENABLE
#endif

void timer_init(void);
void delay_1ms(unsigned int n);
void delay_1us(unsigned int n);
void standby_wait_1ms (unsigned char n);

#endif
