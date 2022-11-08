#include "compiler.h"
/*===================================================================
                    Register map for IOP
====================================================================*/

#ifndef SDCC

unsigned char IDATA IOP_IM_Base_7_0      AT        0x30;    /*7:0*/
unsigned char IDATA IOP_IM_Base_15_8     AT        0x31;    /*15:8*/
unsigned char IDATA IOP_IM_Base_23_16    AT        0x32;    /*23:16*/
unsigned char IDATA IOP_IM_Base_31_24    AT        0x33;    /*31:24*/

unsigned char IDATA IOP_DM_Base_23_16    AT        0x35;    /*23:16*/
unsigned char IDATA IOP_DM_Base_31_24    AT        0x36;    /*31:24*/

//Setting for Interrupt
//bit0:Timer1 interrupt;bit1:Timer0 interrupt; bit2:External interrupt(IR/RTC/SPI/UART wakup)
//bit3:XDM cache miss in power down mode; bit4:Access XDM during cache flushing;
//bit5:IM cache miss in power down mode
unsigned char IDATA IntMask             AT        0x38;
unsigned char IDATA IntFlag             AT        0x39;
unsigned char IDATA Trigger2risc        AT        0x3A;


//Cache Control
//[6:0]  0:none;1:2 lines are checked; 0x7F 4KB are checkd
unsigned char IDATA XDM_Cache_Flush_LINE_NO     AT        0x3B;
unsigned char IDATA XDM_CacheCtrl               AT        0x3C;


//Infrared and RTC status
unsigned char IDATA IR_RTC_Status               AT        0x3D;

//IOP embed Timer , the clock source is 27MHz
unsigned char IDATA TimerA_L                    AT        0x3E;
unsigned char IDATA TimerA_H                    AT        0x3F;
unsigned char IDATA TimerB_L                    AT        0x40;
unsigned char IDATA TimerB_H                    AT        0x41;
unsigned char IDATA Timer_Ctrl                  AT        0x42;


//For System Resume function;
unsigned char IDATA IOP_WATCH_DOG_RST_EN        AT        0x44;
unsigned char IDATA IOP_RESUME_PCL_0            AT        0x45;
unsigned char IDATA IOP_RESUME_PCL_1            AT        0x46;
unsigned char IDATA IOP_RESUME_PCH_0            AT        0x47;
unsigned char IDATA IOP_RESUME_PCH_1            AT        0x48;


//
unsigned char IDATA IOP_INT_MASK1_B             AT        0x49;
unsigned char IDATA IOP_INT_FLAG1               AT        0x4A;
unsigned char IDATA IOP_INT_MASK2_B             AT        0x4B;
unsigned char IDATA IOP_INT_FLAG2               AT        0x4C;
unsigned char IDATA IOP_INT_MASK3_B             AT        0x4D;
unsigned char IDATA IOP_INT_FLAG3               AT        0x4E;

/*=====================================================================
MailBox
should pay attentation to the using of mailbox
including addressig mode
=====================================================================*/
unsigned char IDATA IOP_DATA0_L                 AT        0x50;
unsigned char IDATA IOP_DATA0_H                 AT        0x51;
unsigned char IDATA IOP_DATA1_L                 AT        0x52;
unsigned char IDATA IOP_DATA1_H                 AT        0x53;
unsigned char IDATA IOP_DATA2_L                 AT        0x54;
unsigned char IDATA IOP_DATA2_H                 AT        0x55;
unsigned char IDATA IOP_DATA3_L                 AT        0x56;
unsigned char IDATA IOP_DATA3_H                 AT        0x57;
unsigned char IDATA IOP_DATA4_L                 AT        0x58;
unsigned char IDATA IOP_DATA4_H                 AT        0x59;
unsigned char IDATA IOP_DATA5_L                 AT        0x5A;
unsigned char IDATA IOP_DATA5_H                 AT        0x5B;
unsigned char IDATA IOP_DATA6_L                 AT        0x5C;
unsigned char IDATA IOP_DATA6_H                 AT        0x5D;
unsigned char IDATA IOP_DATA7_L                 AT        0x5E;
unsigned char IDATA IOP_DATA7_H                 AT        0x5F;
unsigned char IDATA IOP_DATA8_L                 AT        0x60;
unsigned char IDATA IOP_DATA8_H                 AT        0x61;
unsigned char IDATA IOP_DATA9_L                 AT        0x62;
unsigned char IDATA IOP_DATA9_H                 AT        0x63;
unsigned char IDATA IOP_DATA10_L                AT        0x64;
unsigned char IDATA IOP_DATA10_H                AT        0x65;
unsigned char IDATA IOP_DATA11_L                AT        0x66;
unsigned char IDATA IOP_DATA11_H                AT        0x67;

//For RTC Timer
unsigned char IDATA SYS_RTC_TIMER_A             AT        0x68;
unsigned char IDATA SYS_RTC_TIMER_B             AT        0x69;
unsigned char IDATA SYS_RTC_TIMER_C             AT        0x6A;
unsigned char IDATA SYS_RTC_TIMER_D             AT        0x6B;
unsigned char IDATA SYS_RTC_ONTIME_SET_A        AT        0x6C;
unsigned char IDATA SYS_RTC_ONTIME_SET_B        AT        0x6D;
unsigned char IDATA SYS_RTC_ONTIME_SET_C        AT        0x6E;
unsigned char IDATA SYS_RTC_ONTIME_SET_D        AT        0x6F;

//XDM(exteranl data memory the whole chip space access) R/W
unsigned char IDATA XDMDATA_OUT_HH              AT        0x70;
unsigned char IDATA XDMDATA_OUT_HL              AT        0x71;
unsigned char IDATA XDMDATA_OUT_LH              AT        0x72;
unsigned char IDATA XDMDATA_OUT_LL              AT        0x73;

unsigned char IDATA XDMDATA_IN_LL               AT        0x74;
unsigned char IDATA XDMDATA_IN_LH               AT        0x75;
unsigned char IDATA XDMDATA_IN_HL               AT        0x76;
unsigned char IDATA XDMDATA_IN_HH               AT        0x77;

//8051 access the chip whole space by bank address
unsigned char IDATA XDM_Bank_ADR_HH             AT        0x78;
unsigned char IDATA XDM_Bank_ADR_HL             AT        0x79;

#endif
