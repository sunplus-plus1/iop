#include "common.h"
#include <stdio.h>
#include "Int_Vec.h"
void timer_init(void)
{
#ifdef TIME0_MODE0 //Timer0 mode0
        #define T 3200 //Timer delay time = (1/27MHz)*3200= 118.51us
        TMOD = 0x04;    //C/T=bit2=1 : External timer, bit1=0, bit0=0 : mode 0
        TL0 = (8192 - T) % 32;
        TH0 = (8192 - T) / 32;
        EA = 1;                 //Enable global interrupts
        ET0 = 1;                //Enable Timer 0 interrupts
        TR0 = 1;                //Enable Timer 0 run control
#endif
#ifdef TIME0_MODE1 //Timer0 mode1
        #define T 57600  //Timer delay time = (1/27MHz)*57600= 2133.33us
        TMOD = 0x05;    //C/T=bit2=1 : External timer, bit1=0, bit0=1 : mode 1
        TL0 = 65536 - T;
        TH0 = (65536-T) >> 8;
        EA = 1;                 //Enable global interrupts
        ET0 = 1;                //Enable Timer 0 interrupts
        TR0 = 1;                //Enable Timer 0 run control
#endif

#ifdef TIME0_MODE2 //Timer0 mode2
        #define T 200  //Timer delay time = (1/27MHz)*200= 7.4us
        TMOD = 0x06;    //C/T=bit2=1 : External timer, bit1=1, bit0=0 : mode 2
        TL0 = TH0 = 256 - T;
        EA = 1;                 //Enable global interrupts
        ET0 = 1;                //Enable Timer 0 interrupts
        TR0 = 1;                //Enable Timer 0 run control
#endif

#ifdef TIME0_MODE3 //Timer0 mode3
        #define TL 225          //Timer delay time = (1/27MHz)*225= 8.33us
        #define TH 235          //Timer delay time = (1/16.6MHz)*235= 14.15us
        TMOD = 0x07;            //C/T=bit2=1 : External timer, bit1=1, bit0=1 : mode 3
        TL0 = 255-TL;
        TH0 = 255-TH;
        EA = 1;                 //Enable global interrupts
        ET0 = 1;                //Enable Timer 0 interrupts
        ET1 = 1;                //Enable Timer 1 interrupts
        TR0 = 1;                //Enable Timer 0 run control
        TR1 = 1;                //Enable Timer 1 run control
#endif
#ifdef TIME1_MODE0 //Timer1 mode0
        #define T 3200  //Timer delay time = (1/27MHz)*3200= 118.5us
        TMOD = 0x40;    //C/T=bit6=1 : External timer, bit5=0, bit4=0 : mode 0
        TL1 = (8192 - T) % 32;
        TH1 = (8192 - T) / 32;
        EA = 1;                 //Enable global interrupts
        ET1 = 1;                //Enable Timer 1 interrupts
        TR1 = 1;                //Enable Timer 1 run control
#endif
#ifdef TIME1_MODE1 //Timer1 mode1
        #define T 57600  //Timer delay time = (1/27MHz)*57600= 2133.33us
        TMOD = 0x50;    //C/T=bit6=1 : External timer, bit5=0, bit4=1 : mode 1
        TL1 = 65536 - T;
        TH1 = (65536-T) >> 8;
        EA = 1;                 //Enable global interrupts
        ET1 = 1;                //Enable Timer 1 interrupts
        TR1 = 1;                //Enable Timer 1 run control
#endif

#ifdef TIME1_MODE2 //Timer1 mode2
        #define T 200  //Timer delay time = (1/27MHz)*200= 7.4us
        TMOD = 0x60;    //C/T=bit6=1 : External timer, bit5=1, bit4=0 : mode 2
        TL1 = TH1 = 255 - T;
        EA = 1;                 //Enable global interrupts
        ET1 = 1;                //Enable Timer 1 interrupts
        TR1 = 1;                //Enable Timer 1 run control
        #endif
#if 1 //Timer1 mode3
#endif

#ifdef EXT_TIMER1 //External timer work, timer1
        IT0 = 1; //set INT0 interrupt type (1:Falling 0:Low level)
        EX0 = 1; //enable INT0 interrupt
        EA = 1; //open global interrupt switch
        TimerA_L=0x10;  //timer1
        TimerA_H=0x57;  //timer = 110us (1/200MHz=0.005us,  0x5710= 22288,  22288x0.005=110us)
        IntMask|=Int_Bit1_Timer1;
        Timer_Ctrl|=Int_Bit1_Timer1;
#endif

#ifdef EXT_TIMER2 //External timer work, timer2
        IT0 = 1; //set INT0 interrupt type (1:Falling 0:Low level)
        EX0 = 1; //enable INT0 interrupt
        EA = 1; //open global interrupt switch
        TimerB_L=0x10;  //timer2
        TimerB_H=0x37;  //timer = 70.48us  (1/200MHz=0.005us,  0x5710= 10496,  10496x0.005=70.48us)
        IntMask|=Int_Bit0_Timer2;
        Timer_Ctrl|=Int_Bit0_Timer2;
#endif
}
