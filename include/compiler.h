#ifndef __COMPILER_H__
#define __COMPILER_H__

#if defined (SDCC)
#define SFR                    __sfr
#define SBIT                   __sbit
#define AT                     __at
#define INTERRUPT_VECTOR       __interrupt
#define IDATA                  __idata
//#define XDATA                  __xdata
#define CODE                   __code
#else
#define SFR                    sfr
#define SBIT                   sbit
#define AT                     _at_
#define INTERRUPT_VECTOR       interrupt
#define IDATA                  idata
#define XDATA                  xdata
#define CODE                   code
#endif



#endif
