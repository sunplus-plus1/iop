#ifndef __SUNPLUS_8051_HH
#define __SUNPLUS_8051_HH
#include "compiler.h"

//Setting for the 8051 bank Addressing mode
//IM: Instruction memory
//DM: Data memory
#if defined(SDCC)
IDATA AT (0x30) unsigned char IOP_IM_Base_7_0;            /*7:0*/
IDATA AT (0x31) unsigned char IOP_IM_Base_15_8;           /*15:8*/
IDATA AT (0x32) unsigned char IOP_IM_Base_23_16;          /*23:16*/
IDATA AT (0x33) unsigned char IOP_IM_Base_31_24;          /*31:24*/
IDATA AT (0x35) unsigned char IOP_DM_Base_23_16;          /*23:16*/
IDATA AT (0x36) unsigned char IOP_DM_Base_31_24;          /*31:24*/

//Setting for Interrupt
//bit0:Timer1 interrupt;bit1:Timer0 interrupt; bit2:External interrupt(IR/RTC/SPI/UART wakup)
//bit3:XDM cache miss in power down mode; bit4:Access XDM during cache flushing;
//bit5:IM cache miss in power down mode
IDATA AT (0x38) unsigned char IntMask;
IDATA AT (0x39) unsigned char IntFlag;
IDATA AT (0x3A) unsigned char Trigger2risc;

//Cache Control
//[6:0]  0:none;1:2 lines are checked; 0x7F 4KB are checkd
IDATA AT (0x3B) unsigned char XDM_Cache_Flush_LINE_NO;
IDATA AT (0x3C) unsigned char XDM_CacheCtrl;

//Infrared and RTC status
IDATA AT (0x3D) unsigned char IR_RTC_Status;

//IOP embed Timer , the clock source is 27MHz
IDATA AT (0x3E) unsigned char TimerA_L;
IDATA AT (0x3F) unsigned char TimerA_H;
IDATA AT (0x40) unsigned char TimerB_L;
IDATA AT (0x41) unsigned char TimerB_H;
IDATA AT (0x42) unsigned char Timer_Ctrl;

//For System Resume function;
IDATA AT (0x44) unsigned char IOP_WATCH_DOG_RST_EN;
IDATA AT (0x45) unsigned char IOP_RESUME_PCL_0;
IDATA AT (0x46) unsigned char IOP_RESUME_PCL_1;
IDATA AT (0x47) unsigned char IOP_RESUME_PCH_0;
IDATA AT (0x48) unsigned char IOP_RESUME_PCH_1;

//
IDATA AT (0x49) unsigned char IOP_INT_MASK1_B;
IDATA AT (0x4A) unsigned char IOP_INT_FLAG1;
IDATA AT (0x4B) unsigned char IOP_INT_MASK2_B;
IDATA AT (0x4C) unsigned char IOP_INT_FLAG2;
IDATA AT (0x4D) unsigned char IOP_INT_MASK3_B;
IDATA AT (0x4E) unsigned char IOP_INT_FLAG3;

/*=====================================================================
MailBox
should pay attentation to the using of mailbox
including addressig mode
=====================================================================*/
IDATA AT (0x50) unsigned char IOP_DATA0_L;
IDATA AT (0x51) unsigned char IOP_DATA0_H;
IDATA AT (0x52) unsigned char IOP_DATA1_L ;
IDATA AT (0x53) unsigned char IOP_DATA1_H ;
IDATA AT (0x54) unsigned char IOP_DATA2_L ;
IDATA AT (0x55) unsigned char IOP_DATA2_H ;
IDATA AT (0x56) unsigned char IOP_DATA3_L ;
IDATA AT (0x57) unsigned char IOP_DATA3_H ;
IDATA AT (0x58) unsigned char IOP_DATA4_L ;
IDATA AT (0x59) unsigned char IOP_DATA4_H ;
IDATA AT (0x5A) unsigned char IOP_DATA5_L ;
IDATA AT (0x5B) unsigned char IOP_DATA5_H ;
IDATA AT (0x5C) unsigned char IOP_DATA6_L ;
IDATA AT (0x5D) unsigned char IOP_DATA6_H ;
IDATA AT (0x5E) unsigned char IOP_DATA7_L ;
IDATA AT (0x5F) unsigned char IOP_DATA7_H ;
IDATA AT (0x60) unsigned char IOP_DATA8_L ;
IDATA AT (0x61) unsigned char IOP_DATA8_H ;
IDATA AT (0x62) unsigned char IOP_DATA9_L ;
IDATA AT (0x63) unsigned char IOP_DATA9_H ;
IDATA AT (0x64) unsigned char IOP_DATA10_L;
IDATA AT (0x65) unsigned char IOP_DATA10_H;
IDATA AT (0x66) unsigned char IOP_DATA11_L;
IDATA AT (0x67) unsigned char IOP_DATA11_H;

//For RTC Timer
IDATA AT (0x68) unsigned char SYS_RTC_TIMER_A;
IDATA AT (0x69) unsigned char SYS_RTC_TIMER_B;
IDATA AT (0x6A) unsigned char SYS_RTC_TIMER_C;
IDATA AT (0x6B) unsigned char SYS_RTC_TIMER_D;
IDATA AT (0x6C) unsigned char SYS_RTC_ONTIME_SET_A;
IDATA AT (0x6D) unsigned char SYS_RTC_ONTIME_SET_B;
IDATA AT (0x6E) unsigned char SYS_RTC_ONTIME_SET_C;
IDATA AT (0x6F) unsigned char SYS_RTC_ONTIME_SET_D;


//XDM(exteranl data memory the whole chip space access) R/W
IDATA AT (0x70) unsigned char XDMDATA_OUT_HH;
IDATA AT (0x71) unsigned char XDMDATA_OUT_HL;
IDATA AT (0x72) unsigned char XDMDATA_OUT_LH;
IDATA AT (0x73) unsigned char XDMDATA_OUT_LL;

IDATA AT (0x74) unsigned char XDMDATA_IN_LL;
IDATA AT (0x75) unsigned char XDMDATA_IN_LH;
IDATA AT (0x76) unsigned char XDMDATA_IN_HL;
IDATA AT (0x77) unsigned char XDMDATA_IN_HH;

//8051 access the chip whole space by bank address
IDATA AT (0x78) unsigned char XDM_Bank_ADR_HH;
IDATA AT (0x79) unsigned char XDM_Bank_ADR_HL;


//General Purpose Output Enable  (Read/Write)
//"1" for Output and "0" for Input
SFR AT (0xB0) GPIO_IO0_CFG;
SFR AT (0xB1) GPIO_IO1_CFG;
SFR AT (0xB2) GPIO_IO2_CFG;
SFR AT (0xB3) GPIO_IO3_CFG;
SFR AT (0xB4) GPIO_IO4_CFG;
SFR AT (0xB5) GPIO_IO5_CFG;
SFR AT (0xB6) GPIO_IO6_CFG;
SFR AT (0xB7) GPIO_IO7_CFG;
SFR AT (0x98) GPIO_IO8_CFG;
SFR AT (0x99) GPIO_IO9_CFG;
SFR AT (0x9A) GPIO_IO10_CFG;
SFR AT (0x9B) GPIO_IO11_CFG;
SFR AT (0x9C) GPIO_IO12_CFG;
SFR AT (0x9D) GPIO_IO13_CFG;
SFR AT (0x9E) GPIO_IO14_CFG;
SFR AT (0x9F) GPIO_IO15_CFG;


//General Purpose Output   (Read/Write)
SFR AT (0xC0) GPIO_PORT0_OUT ;
SFR AT (0xC1) GPIO_PORT1_OUT ;
SFR AT (0xC2) GPIO_PORT2_OUT ;
SFR AT (0xC3) GPIO_PORT3_OUT ;
SFR AT (0xC4) GPIO_PORT4_OUT ;
SFR AT (0xC5) GPIO_PORT5_OUT ;
SFR AT (0xC6) GPIO_PORT6_OUT ;
SFR AT (0xC7) GPIO_PORT7_OUT ;
SFR AT (0xC8) GPIO_PORT8_OUT ;
SFR AT (0xC9) GPIO_PORT9_OUT ;
SFR AT (0xCA) GPIO_PORT10_OUT;
SFR AT (0xCB) GPIO_PORT11_OUT;
SFR AT (0xCC) GPIO_PORT12_OUT;
SFR AT (0xCD) GPIO_PORT13_OUT;
SFR AT (0xCE) GPIO_PORT14_OUT;
SFR AT (0xCF) GPIO_PORT15_OUT;

//General Purpose Input (Read only)
SFR AT (0xD4) GPIO_PORT0_IN ;
SFR AT (0xD5) GPIO_PORT1_IN ;
SFR AT (0xD6) GPIO_PORT2_IN ;
SFR AT (0xD7) GPIO_PORT3_IN ;
SFR AT (0xDC) GPIO_PORT4_IN ;
SFR AT (0xDD) GPIO_PORT5_IN ;
SFR AT (0xDE) GPIO_PORT6_IN ;
SFR AT (0xDF) GPIO_PORT7_IN ;
SFR AT (0xE4) GPIO_PORT8_IN ;
SFR AT (0xE5) GPIO_PORT9_IN ;
SFR AT (0xE6) GPIO_PORT10_IN;
SFR AT (0xE7) GPIO_PORT11_IN;
SFR AT (0xEC) GPIO_PORT12_IN;
SFR AT (0xED) GPIO_PORT13_IN;
SFR AT (0xEE) GPIO_PORT14_IN;
SFR AT (0xEF) GPIO_PORT15_IN;

SFR AT (0xF4) POWER_CONTROL;
SFR AT (0xF5) POWER_GATE;
#else  //Keil compiler


extern unsigned char IDATA IOP_IM_Base_7_0   ;    /*7:0*/
extern unsigned char IDATA IOP_IM_Base_15_8  ;    /*15:8*/
extern unsigned char IDATA IOP_IM_Base_23_16 ;    /*23:16*/
extern unsigned char IDATA IOP_IM_Base_31_24 ;    /*31:24*/

extern unsigned char IDATA IOP_DM_Base_23_16 ;     /*23:16*/
extern unsigned char IDATA IOP_DM_Base_31_24 ;     /*31:24*/

//Setting for Interrupt
//bit0:Timer1 interrupt;bit1:Timer0 interrupt; bit2:External interrupt(IR/RTC/SPI/UART wakup)
//bit3:XDM cache miss in power down mode; bit4:Access XDM during cache flushing;
//bit5:IM cache miss in power down mode
extern  unsigned char IDATA IntMask          ;
extern  unsigned char IDATA IntFlag          ;
extern  unsigned char IDATA Trigger2risc     ;


//Cache Control
//[6:0]  0:none;1:2 lines are checked; 0x7F 4KB are checkd
extern unsigned char IDATA XDM_Cache_Flush_LINE_NO    ;
extern unsigned char IDATA XDM_CacheCtrl              ;


//Infrared and RTC status
extern unsigned char IDATA IR_RTC_Status              ;

//IOP embed Timer , the clock source is 27MHz
extern unsigned char IDATA TimerA_L                      ;
extern unsigned char IDATA TimerA_H                      ;
extern unsigned char IDATA TimerB_L                      ;
extern unsigned char IDATA TimerB_H                      ;
extern unsigned char IDATA Timer_Ctrl                    ;


//For System Resume function;
extern unsigned char IDATA IOP_WATCH_DOG_RST_EN          ;
extern unsigned char IDATA IOP_RESUME_PCL_0              ;
extern unsigned char IDATA IOP_RESUME_PCL_1              ;
extern unsigned char IDATA IOP_RESUME_PCH_0              ;
extern unsigned char IDATA IOP_RESUME_PCH_1              ;

extern unsigned char IDATA IOP_INT_MASK1_B               ;
extern unsigned char IDATA IOP_INT_FLAG1                 ;
extern unsigned char IDATA IOP_INT_MASK2_B               ;
extern unsigned char IDATA IOP_INT_FLAG2                 ;
extern unsigned char IDATA IOP_INT_MASK3_B               ;
extern unsigned char IDATA IOP_INT_FLAG3                 ;

/*=====================================================================
MailBox
should pay attentation to the using of mailbox
including addressig mode
=====================================================================*/
extern unsigned char IDATA IOP_DATA0_L     ;
extern unsigned char IDATA IOP_DATA0_H     ;
extern unsigned char IDATA IOP_DATA1_L     ;
extern unsigned char IDATA IOP_DATA1_H     ;
extern unsigned char IDATA IOP_DATA2_L     ;
extern unsigned char IDATA IOP_DATA2_H     ;
extern unsigned char IDATA IOP_DATA3_L     ;
extern unsigned char IDATA IOP_DATA3_H     ;
extern unsigned char IDATA IOP_DATA4_L     ;
extern unsigned char IDATA IOP_DATA4_H     ;
extern unsigned char IDATA IOP_DATA5_L     ;
extern unsigned char IDATA IOP_DATA5_H     ;
extern unsigned char IDATA IOP_DATA6_L     ;
extern unsigned char IDATA IOP_DATA6_H     ;
extern unsigned char IDATA IOP_DATA7_L     ;
extern unsigned char IDATA IOP_DATA7_H     ;
extern unsigned char IDATA IOP_DATA8_L     ;
extern unsigned char IDATA IOP_DATA8_H     ;
extern unsigned char IDATA IOP_DATA9_L     ;
extern unsigned char IDATA IOP_DATA9_H     ;
extern unsigned char IDATA IOP_DATA10_L    ;
extern unsigned char IDATA IOP_DATA10_H    ;
extern unsigned char IDATA IOP_DATA11_L    ;
extern unsigned char IDATA IOP_DATA11_H    ;

//For RTC Timer
extern unsigned char IDATA SYS_RTC_TIMER_A    ;
extern unsigned char IDATA SYS_RTC_TIMER_B    ;
extern unsigned char IDATA SYS_RTC_TIMER_C    ;
extern unsigned char IDATA SYS_RTC_TIMER_D    ;
extern unsigned char IDATA SYS_RTC_ONTIME_SET_A ;
extern unsigned char IDATA SYS_RTC_ONTIME_SET_B ;
extern unsigned char IDATA SYS_RTC_ONTIME_SET_C ;
extern unsigned char IDATA SYS_RTC_ONTIME_SET_D ;

//XDM(exteranl data memory the whole chip space access) R/W
extern unsigned char IDATA XDMDATA_OUT_HH ;
extern unsigned char IDATA XDMDATA_OUT_HL ;
extern unsigned char IDATA XDMDATA_OUT_LH ;
extern unsigned char IDATA XDMDATA_OUT_LL ;

extern unsigned char IDATA XDMDATA_IN_LL ;
extern unsigned char IDATA XDMDATA_IN_LH ;
extern unsigned char IDATA XDMDATA_IN_HL ;
extern unsigned char IDATA XDMDATA_IN_HH ;

//8051 access the chip whole space by bank address
extern unsigned char IDATA XDM_Bank_ADR_HH ;
extern unsigned char IDATA XDM_Bank_ADR_HL ;


//General Purpose Output Enable  (Read/Write)
//"1" for Output and "0" for Input
SFR GPIO_IO0_CFG = 0xB0 ;
SFR GPIO_IO1_CFG = 0xB1 ;
SFR GPIO_IO2_CFG = 0xB2 ;
SFR GPIO_IO3_CFG = 0xB3 ;
SFR GPIO_IO4_CFG = 0xB4 ;
SFR GPIO_IO5_CFG = 0xB5 ;
SFR GPIO_IO6_CFG = 0xB6 ;
SFR GPIO_IO7_CFG = 0xB7 ;
SFR GPIO_IO8_CFG = 0x98 ;
SFR GPIO_IO9_CFG = 0x99 ;
SFR GPIO_IO10_CFG = 0x9A ;
SFR GPIO_IO11_CFG = 0x9B ;
SFR GPIO_IO12_CFG = 0x9C ;
SFR GPIO_IO13_CFG = 0x9D ;
SFR GPIO_IO14_CFG = 0x9E ;
SFR GPIO_IO15_CFG = 0x9F ;


//General Purpose Output   (Read/Write)
SFR GPIO_PORT0_OUT = 0xC0    ;
SFR GPIO_PORT1_OUT = 0xC1    ;
SFR GPIO_PORT2_OUT = 0xC2    ;
SFR GPIO_PORT3_OUT = 0xC3    ;
SFR GPIO_PORT4_OUT = 0xC4    ;
SFR GPIO_PORT5_OUT = 0xC5    ;
SFR GPIO_PORT6_OUT = 0xC6    ;
SFR GPIO_PORT7_OUT = 0xC7    ;
SFR GPIO_PORT8_OUT = 0xC8    ;
SFR GPIO_PORT9_OUT = 0xC9    ;
SFR GPIO_PORT10_OUT = 0xCA    ;
SFR GPIO_PORT11_OUT = 0xCB    ;
SFR GPIO_PORT12_OUT = 0xCC    ;
SFR GPIO_PORT13_OUT = 0xCD    ;
SFR GPIO_PORT14_OUT = 0xCE    ;
SFR GPIO_PORT15_OUT = 0xCF    ;

//General Purpose Input (Read only)
SFR GPIO_PORT0_IN = 0xD4    ;
SFR GPIO_PORT1_IN = 0xD5    ;
SFR GPIO_PORT2_IN = 0xD6    ;
SFR GPIO_PORT3_IN = 0xD7    ;
SFR GPIO_PORT4_IN = 0xDC    ;
SFR GPIO_PORT5_IN = 0xDD    ;
SFR GPIO_PORT6_IN = 0xDE    ;
SFR GPIO_PORT7_IN = 0xDF    ;
SFR GPIO_PORT8_IN = 0xE4    ;
SFR GPIO_PORT9_IN = 0xE5    ;
SFR GPIO_PORT10_IN = 0xE6    ;
SFR GPIO_PORT11_IN = 0xE7    ;
SFR GPIO_PORT12_IN = 0xEC    ;
SFR GPIO_PORT13_IN = 0xED    ;
SFR GPIO_PORT14_IN = 0xEE    ;
SFR GPIO_PORT15_IN = 0xEF    ;

SFR POWER_CONTROL = 0xF4    ;
SFR POWER_GATE    = 0xF5    ;
#endif


#define IM_BASE_7_0                IOP_IM_Base_7_0
#define IM_BASE_15_8               IOP_IM_Base_15_8
#define IM_BASE_23_16              IOP_IM_Base_23_16
#define IM_BASE_31_24              IOP_IM_Base_31_24

#define DM_BASE_23_16              IOP_DM_Base_23_16
#define DM_BASE_31_24              IOP_DM_Base_31_24

#define RISC2IOP_INTERUPT_MASK     IntMask
#define RISC2IOP_INTERRUPT_FLAG    IntFlag
#define IOP2RISC_TRIGGER           Trigger2risc

#define XDM_CACHE_FLUSH            XDM_Cache_Flush_LINE_NO
#define XDM_CACHE_CTRL             XDM_CacheCtrl

#define IR_RTC_STATUS              IR_RTC_Status

#define TIMERA_COUNTER_7_0         TimerA_L
#define TIMERA_COUNTER_15_8        TimerA_H
#define TIMERB_COUNTER_7_0         TimerB_L
#define TIMERB_COUNTER_15_8        TimerB_H
#define TIMER_CTRL                 Timer_Ctrl

#define WATCHDOG_EN_RESET          IOP_WATCH_DOG_RST_EN
#define RESUME_PC_7_0              IOP_RESUME_PCL_0
#define RESUME_PC_15_8             IOP_RESUME_PCL_1
#define RESUME_PC_23_16            IOP_RESUME_PCH_0
#define RESUME_PC_31_24            IOP_RESUME_PCH_1

#define INTERRUPT1_MASK            IOP_INT_MASK1_B
#define INTERRUPT1_FLAG            IOP_INT_FLAG1
#define INTERRUPT2_MASK            IOP_INT_MASK2_B
#define INTERRUPT2_FLAG            IOP_INT_FLAG2
#define INTERRUPT3_MASK            IOP_INT_MASK3_B
#define INTERRUPT3_FLAG            IOP_INT_FLAG3

#define MAILBOX_DATA0_7_0          IOP_DATA0_L
#define MAILBOX_DATA0_15_8         IOP_DATA0_H
#define MAILBOX_DATA1_7_0          IOP_DATA1_L
#define MAILBOX_DATA1_15_8         IOP_DATA1_H
#define MAILBOX_DATA2_7_0          IOP_DATA2_L
#define MAILBOX_DATA2_15_8         IOP_DATA2_H
#define MAILBOX_DATA3_7_0          IOP_DATA3_L
#define MAILBOX_DATA3_15_8         IOP_DATA3_H
#define MAILBOX_DATA4_7_0          IOP_DATA4_L
#define MAILBOX_DATA4_15_8         IOP_DATA4_H
#define MAILBOX_DATA5_7_0          IOP_DATA5_L
#define MAILBOX_DATA5_15_8         IOP_DATA5_H
#define MAILBOX_DATA6_7_0          IOP_DATA6_L
#define MAILBOX_DATA6_15_8         IOP_DATA6_H
#define MAILBOX_DATA7_7_0          IOP_DATA7_L
#define MAILBOX_DATA7_15_8         IOP_DATA7_H
#define MAILBOX_DATA8_7_0          IOP_DATA8_L
#define MAILBOX_DATA8_15_8         IOP_DATA8_H
#define MAILBOX_DATA9_7_0          IOP_DATA9_L
#define MAILBOX_DATA9_15_8         IOP_DATA9_H
#define MAILBOX_DATA10_7_0         IOP_DATA10_L
#define MAILBOX_DATA10_15_8        IOP_DATA10_H
#define MAILBOX_DATA11_7_0         IOP_DATA11_L
#define MAILBOX_DATA11_15_8        IOP_DATA11_H

#define RTC_COUNTER_31_24          SYS_RTC_TIMER_A
#define RTC_COUNTER_23_16          SYS_RTC_TIMER_B
#define RTC_COUNTER_15_8           SYS_RTC_TIMER_C
#define RTC_COUNTER_7_0            SYS_RTC_TIMER_D
#define ALARM_COUNTER_31_24        SYS_RTC_ONTIME_SET_A
#define ALARM_COUNTER_23_16        SYS_RTC_ONTIME_SET_B
#define ALARM_COUNTER_15_8         SYS_RTC_ONTIME_SET_C
#define ALARM_COUNTER_7_0          SYS_RTC_ONTIME_SET_D

#define XDM_OUT_DATA_31_24         XDMDATA_OUT_HH
#define XDM_OUT_DATA_23_16         XDMDATA_OUT_HL
#define XDM_OUT_DATA_15_8          XDMDATA_OUT_LH
#define XDM_OUT_DATA_8_0           XDMDATA_OUT_LL

#define XDM_IN_DATA_31_24          XDMDATA_IN_LL
#define XDM_IN_DATA_23_16          XDMDATA_IN_LH
#define XDM_IN_DATA_15_8           XDMDATA_IN_HL
#define XDM_IN_DATA_7_0            XDMDATA_IN_HH

#define XDM_BANK_31_24             XDM_Bank_ADR_HH
#define XDM_BANK_23_16             XDM_Bank_ADR_HL



#endif
