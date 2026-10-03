//=============================================================================
//Name		:main.c
//Purpose	:主函数
//Version	:V1.0
//Author	:szl
//Date		:2019.01.19

//XDATA:0xFD00-0xFFFF
//CODE-NOT DEBUG:0X00-0X0032,0X003B-0X3FFE
//CODE-DEBUG:0X0000-0X0032,0X003B-0X1CFF,0x2000-0x3FFD
//0x00-0x32,0x3b-0x3ffe
//0x00-0x32,0x3b-0x1cff,0x2000-0x3ffd
//=============================================================================
#include "AllHeadFile.h"	
//=============================================================================
//unsigned char code SerialNumber[4] _at_ 0x3ff6;
//=============================================================================
// Function:	void ClearXRAM(void)
// Purpose:	initial ram
// Input:	none
// OutPut:	none
// Author:
//=============================================================================
void ClearXRAM(void)
{
	unsigned char xdata * data l_p_ucXdata;
	unsigned int idata i;
	l_p_ucXdata = 0xfd00;
	for(i = 0;i < 768;i++)
	{
		*(l_p_ucXdata++) = 0x00;	
	}
}

void main(void)
{
	InitDevice();									//初始化功能模块
	/*上电延时若干ms的时间以确保IC电源电压稳定*/
	DelayNOP(500);
	ClearXRAM();
//=============================================================
	BackTime = 16;
	while(BackTime)
	{
		if(b32HzFlag)
		{
			CLRWDT=1;		//清看门狗	
			b32HzFlag = 0;
			BackTime--;
		}			
	}
	//------------------------------------------	
	InitData();
	SetAllDispRgb1(0);
	DispAllLight(1);
	TurnPowerOff();
	if(IO_DC_DET==1)
	{	
		TurnIrOn();
		Led_TurnOn();
		DispAllLed(1);
		Led_Reflush();
		Led_Reflush1();
		BackTime = 64;
		while(BackTime)
	  	{
	    		if(b32HzFlag)
	    		{
	      			CLRWDT=1;		//清看门狗	
	      			b32HzFlag = 0;
	      			BackTime--;
	      			
	    		}			
	  	}	
		BackTime = 4;
		T2O_On();
		while(BackTime)
	  	{
	    		if(b32HzFlag)
	    		{
	      			CLRWDT=1;		//清看门狗	
	      			b32HzFlag = 0;
	      			BackTime--;
	    		}			
	  	}
	  	T2O_Off();	
	  	TurnPowerOn();
	  	TurnLightOn();
	}	
	Gxhtv4CheckOn();
//=============================================================
	while(1)
	{
	  	CLRWDT=1;			//清看门狗
	  	ReceiveDecode();
	  	RefreshDisplay();
	  	Led_Reflush();
	  	Led_Reflush1();
	  	if(b2HzFlag==1)		//2Hz
  		{
   	 		b2HzFlag = 0;
   	 		P3_1 = ~P3_1;
   	 		CheckDcOn();
   	 		TimerBase();
    		}	
    		
    		if((SysFlag&D_IrEn)&&(b32HzFlag==1))		//32Hz
  		{
    			b32HzFlag = 0;
    			P3_0 = ~P3_0;
    			Random();
    			CheckDcOff();
    			Timer32HzPro();
  		} 
	  
	  	if((SysFlag&D_IrEn)==0)
	  	{
  			TM0_Disable();
			TM1_Disable();
	    		_nop_();	
	    		_nop_();
	    		PCON |= PD;
	    		_nop_();	
	    		_nop_();
	    		_nop_();
	    		TM0_Enable();
	    		TM1_Enable();
	  	}										
	}
}

//=============================================================================