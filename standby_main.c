#include <stdio.h>
#if defined (SDCC)
#include "8051.h"
#else
#include "dp8051xp.h"
#endif
#include "sunplus8051.h"
#include "standby.h"

void wait_1ms (unsigned char n)
{   /* Wait function                    */
	volatile  unsigned char  i,j,k,h;

	k = n;
	for(h=0;h<4;h++)
	{
		for(i=0;i<k;i++)
		{
			for(j=0;j<235;j++)
			{
				k=k;
			}
		}
	}
}

void Wakeup_System(void)
{

	IOP_WATCH_DOG_RST_EN|=0x02; //IOP disable "system reset IOP" before reset system
	wait_1ms(50);
	POWER_CONTROL|=(1<<DEF_PWR_EN_OE_bit); //PWR_EN output enable
	POWER_CONTROL|=(1<<DEF_PWR_EN_O_bit); //PWR_EN output high
	wait_1ms(50);
	POWER_CONTROL|=(1<<System_reset_bit); //system reset
	wait_1ms(50);

	while((POWER_GATE&(1<<PWR12_READY_bit))!=(1<<PWR12_READY_bit))
	POWER_GATE|=(1<<REG_IOP_PWR_GATE_bit); //external power supply
	POWER_GATE&=~(1<<MO_DC_12_ENB_A_bit); //control bit output to DCDC analog macro & power_ready_check module
	POWER_GATE&=~(1<<MO_DC_12_ENB_ALL_bit); //control bit output to DCDC analog macro & power_ready_check module
	POWER_GATE&=~(1<<MO_DC_15_ENB_A_bit);
	POWER_GATE&=~(1<<MO_DC_15_ENB_ALL_bit);
	POWER_GATE&=~(1<<MO_DC_09_ENB_A_bit);
	POWER_GATE&=~(1<<MO_DC_09_ENB_ALL_bit);
	wait_1ms(50);

	POWER_CONTROL&=~(1<<Isolation_bit); //no Isolation
	wait_1ms(1);
	POWER_CONTROL&=~(1<<System_reset_bit);  //Normal operation
	POWER_CONTROL&=~(1<<DEF_PWR_EN_OE_bit); //clear "PWR_EN output enable"
	POWER_CONTROL&=~(1<<DEF_PWR_EN_O_bit);  //PWR_EN output low
	IOP_WATCH_DOG_RST_EN = 0; //Clear "IOP disable system reset IOP"

	while(1);//avoid repeated boot
}

void S3_Mode(void)//AO domain power on. Default and IOP domain power off
{

	POWER_CONTROL|=(1<<Isolation_bit); //Isolation
	wait_1ms(50);

	POWER_GATE&=~(1<<REG_IOP_PWR_GATE_bit); //powered by an embedded regulator
	wait_1ms(50);
	POWER_CONTROL|=(1<<DEF_PWR_EN_OE_bit); //PWR_EN output disable
	POWER_CONTROL&=~(1<<DEF_PWR_EN_O_bit); //PWR_EN output low

	POWER_GATE|=(1<<MO_DC_12_ENB_A_bit); //control bit output to DCDC analog macro  & power_ready_check module
	POWER_GATE|=(1<<MO_DC_12_ENB_ALL_bit); //control bit output to DCDC analog macro & power_ready_check module
	POWER_GATE|=(1<<MO_DC_15_ENB_A_bit);
	POWER_GATE|=(1<<MO_DC_15_ENB_ALL_bit);
	POWER_GATE|=(1<<MO_DC_09_ENB_A_bit);
	POWER_GATE|=(1<<MO_DC_09_ENB_ALL_bit);

	POWER_CONTROL|=(1<<IOP_PWR_DWN_bit); //IOP domain power down request
}

void S1_Mode(void)//AO and IOP domain power on. Default domain power off
{

	POWER_CONTROL|=(1<<Isolation_bit); //Isolation
	wait_1ms(50);

	POWER_GATE&=~(1<<REG_IOP_PWR_GATE_bit); //powered by an embedded regulator
	wait_1ms(50);
	POWER_CONTROL|=(1<<DEF_PWR_EN_OE_bit); //PWR_EN output disable
	POWER_CONTROL&=~(1<<DEF_PWR_EN_O_bit); //PWR_EN output low

	POWER_GATE|=(1<<MO_DC_12_ENB_A_bit); //control bit output to DCDC analog macro  & power_ready_check module
	POWER_GATE|=(1<<MO_DC_12_ENB_ALL_bit); //control bit output to DCDC analog macro  & power_ready_check module
	POWER_GATE|=(1<<MO_DC_15_ENB_A_bit);
	POWER_GATE|=(1<<MO_DC_15_ENB_ALL_bit);
	POWER_GATE|=(1<<MO_DC_09_ENB_A_bit);
	POWER_GATE|=(1<<MO_DC_09_ENB_ALL_bit);
}

void Fill_ICache(void)
{
	volatile unsigned char tmp0,tmp1,tmp2,tmp3,tmp4,tmp5,tmp6
		         ,tmp7,tmp8,tmp9,tmpa,tmpb,tmpc,tmpd ,tmpe,tmpf;
  volatile  unsigned int i,temp;

	for(i=0; i<32; i++)
	{
		temp = 0x200;
		tmp0=(unsigned char)*((unsigned char CODE *)(0x0000+(temp*i)));
		tmp1=(unsigned char)*((unsigned char CODE *)(0x0020+(temp*i)));
		tmp2=(unsigned char)*((unsigned char CODE *)(0x0040+(temp*i)));
		tmp3=(unsigned char)*((unsigned char CODE *)(0x0060+(temp*i)));
		tmp4=(unsigned char)*((unsigned char CODE *)(0x0080+(temp*i)));
		tmp5=(unsigned char)*((unsigned char CODE *)(0x00A0+(temp*i)));
		tmp6=(unsigned char)*((unsigned char CODE *)(0x00C0+(temp*i)));
		tmp7=(unsigned char)*((unsigned char CODE *)(0x00E0+(temp*i)));
		tmp8=(unsigned char)*((unsigned char CODE *)(0x0100+(temp*i)));
		tmp9=(unsigned char)*((unsigned char CODE *)(0x0120+(temp*i)));
		tmpa=(unsigned char)*((unsigned char CODE *)(0x0140+(temp*i)));
		tmpb=(unsigned char)*((unsigned char CODE *)(0x0160+(temp*i)));
		tmpc=(unsigned char)*((unsigned char CODE *)(0x0180+(temp*i)));
		tmpd=(unsigned char)*((unsigned char CODE *)(0x01A0+(temp*i)));
		tmpe=(unsigned char)*((unsigned char CODE *)(0x01C0+(temp*i)));
		tmpf=(unsigned char)*((unsigned char CODE *)(0x01E0+(temp*i)));
	}
}

void wakeup_check_by_interrupt()
{
	if((IR_RTC_Status&(1<<PMC_IR_LATCH_bit))==(1<<PMC_IR_LATCH_bit))
	{
		Wakeup_System();
	}
	else if((IR_RTC_Status&(1<<PMC_SYS_RTC_LATCH_bit))==(1<<PMC_SYS_RTC_LATCH_bit))
	{
		Wakeup_System();
	}
}

//for S1 mode
void wakeup_check_by_gpio()
{
	GPIO_IO0_CFG=0x00;
	if((GPIO_PORT0_IN&0x01)==0x01)//Wake up for S1_mode. AO and IOP domain power on. Default domain power off
	{
		Wakeup_System();
	}
}

void main()
{

	wakeup_check_by_interrupt();

initial:

	IOP_DATA2_L=0x04; //handshake in standby mode

	IOP_WATCH_DOG_RST_EN|=0x01; //IOP disable Watchdog reset IOP

	while(1)
	{
		if((IOP_DATA5_H==0x00)&&(IOP_DATA5_L==0x00)&&(IOP_DATA6_H==0x00)&&(IOP_DATA6_L==0x60))
		{
			IOP_DATA7_H=0xaa;
			IOP_DATA7_L=0xaa; //handshake with RISC
			break;
		}
	}

	while(1)
	{

		switch(IOP_DATA1_L)
		{
			case 0xaa:
				Fill_ICache();

				POWER_CONTROL|=(1<<DEF_PWR_EN_OE_bit); //PWR_EN output disable
				POWER_CONTROL&=~(1<<DEF_PWR_EN_O_bit); //PWR_EN output low

				wait_1ms(100);
				wait_1ms(100);
				wait_1ms(100);
				wait_1ms(100);
				wait_1ms(100);

				POWER_CONTROL|=(1<<DEF_PWR_EN_OE_bit); //PWR_EN output disable
				POWER_CONTROL|=(1<<DEF_PWR_EN_O_bit); //PWR_EN output low
				goto mainflow;
				break;
			case 0xcc:
				Fill_ICache();
				Wakeup_System();
				break;
			case 0xdd:
 			  Fill_ICache();
				S3_Mode(); //AO domain power on. Default and IOP domain power off
				goto S3_FLOW;
				break;
			case 0xee:
				Fill_ICache();
				S1_Mode(); //AO and IOP domain power on. Default domain power off
				goto S1_FLOW;
				break;
			default:
				break;
		}
	}

S3_FLOW:
  while(1)
  {
    wakeup_check_by_interrupt();
  }

S1_FLOW:
  while(1)
  {
    wakeup_check_by_interrupt();
		wakeup_check_by_gpio();
  }

mainflow:
	GPIO_IO0_CFG=0x01;
	while(1)
	{
		//debug by IV_MX0
		GPIO_PORT0_OUT=0x01;
		wait_1ms(200);
		wait_1ms(200);
		wait_1ms(200);
		wait_1ms(200);
		wait_1ms(200);
	  GPIO_PORT0_OUT=0;
		wait_1ms(200);
		wait_1ms(200);
		wait_1ms(200);
		wait_1ms(200);
	}
}
