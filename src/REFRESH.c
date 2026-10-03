//=============================================================================
//Name		:LED.c
//Purpose	:LED显示函数
//Version	:V1.0
//Author	:
//Date		:2022.05.24
//=============================================================================
#include "AllHeadFile.h"
//=============================================================================

//=============================================================================
static void FlashSecClr(void);
//static void FlashSecDisp(void);
static void HalfSecClr(void);
static void HalfSecDisp(void);


unsigned char code Week_Bit_Tab[] =
{
	0x40,	//SUN
	0x01,	//MON
	0x02,	//TUE
	0x04,	//WED
	0x08,	//THU
	0x10,	//FRI
	0x20,	//SAT
	0x1f,	//1~5
	0x3f,	//1-6
	0x7f,	//0~6
	0x00	//--
};

//=============================================================================
//功能:
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispAlarmFlag(void)
{
  	uchar disp_flag;
  	if(Mode>M_SetAlarm)
  		disp_flag = 0x00;
  	else if(Mode>M_SetTime)
  	{
  		if(AlarmCnt)
  			disp_flag = D_Alarm2On;
  		else
  			disp_flag = D_Alarm1On;	
  	}
  	else	
  		disp_flag = ProFlag1&(D_Alarm1On|D_Alarm2On);
  	
  	if(ProFlag2&D_PlayAlarm1)
  		disp_flag |= 0x01;	
  	else if(ProFlag2&D_PlayAlarm2)
  		disp_flag |= 0x02;		
 	DispSybmols(Led_Alarm,2,disp_flag);	
}	

static void ClearAlarmFlag(void)
{
  	uchar disp_flag;
  	if(Mode==M_Timer)
  		disp_flag = 0x00;
  	else if(Mode>M_SetTime)
  	{
  		if(AlarmCnt)
  			disp_flag = D_Alarm2On;
  		else
  			disp_flag = D_Alarm1On;	
  	}
  	else	
  		disp_flag = ProFlag1&(D_Alarm1On|D_Alarm2On);
  	
  	if(ProFlag2&D_PlayAlarm1)
  		disp_flag &= ~0x01;	
  	else if(ProFlag2&D_PlayAlarm2)
  		disp_flag &= ~0x02;	
 	DispSybmols(Led_Alarm,2,disp_flag);	
}

//=============================================================================
//功能:
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispDstFlag(void)
{
  	if(ProFlag1&D_Dst)
  		DispSybmol(Led_Dst,1);	
  	else	
  		DispSybmol(Led_Dst,0);	
}	
//=============================================================================
//功能:共用显示
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispHour(uchar disp_hour)
{
	uchar dispH,dispL;	
 	
  	if(ProFlag&D_24Hour) 
  	{
    		DispSybmols(Led_AmPm,2,0x00);	
  	}
  	else	
  	{	
    		if(disp_hour>11)
    		{
      			if(disp_hour>12)
        			disp_hour = disp_hour-12;
      			DispSybmols(Led_AmPm,2,0x02);	//P  
    		}			
    		else
    		{
      			if(disp_hour==0)
         			disp_hour = 12;	
       			DispSybmols(Led_AmPm,2,0x01);	//A 	
    		}	
  	}  	

  	dispH = disp_hour/10;	
  	dispL = disp_hour%10;	
  	if(dispH==0)
  	  	dispH = 0x0a;	
  	DispDigit1(Led_Num1,dispH);
  	DispDigit1(Led_Num2,dispL);
 	
}

static void DispMinute(uchar disp_minute)
{
	uchar dispH,dispL;	
	dispH = disp_minute/10;	
  	dispL = disp_minute%10;	
  	DispDigit1(Led_Num3,dispH);
  	DispDigit1(Led_Num4,dispL);
}

static void DispWeek(uchar disp_week)
{
	if(disp_week==0x0a)
	{
		DispSybmols(Led_WeekR,7,0x00);
		DispSybmols(Led_WeekW,7,0x00);
	}	
	else
	{
		DispSybmols(Led_WeekR,7,Week_Bit_Tab[disp_week]);
		DispSybmols(Led_WeekW,7,Week_Bit_Tab[disp_week]^0xff);		
	}	
}

//=============================================================================
//功能:disp time
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispTime(void)
{
  	DispSybmols(Led_Col,2,0x03);
  	DispHour(Hour);
	DispMinute(Minute);
	DispWeek(Week);
}
//=============================================================================
//功能:DispHourMode
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispHourMode(void)
{
  	DispSybmols(Led_AmPm,2,0x00);
  	DispSybmols(Led_Col,2,0x00);
  	DispWeek(Week);
  	DispDigit1(Led_Num1,0x0a);
  	DispDigit1(Led_Num4,0x0c);		//H
  	if(ProFlag&D_24Hour) 
  	{
  		DispDigit1(Led_Num2,0x02);	
  		DispDigit1(Led_Num3,0x04);		
  	}	
  	else
  	{
  		DispDigit1(Led_Num2,0x01);	
  		DispDigit1(Led_Num3,0x02);		
  	}	
}	
//=============================================================================
//功能:DispHourMode
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispYear(void)
{
  	DispSybmols(Led_AmPm,2,0x00);
  	DispSybmols(Led_Col,2,0x00);
  	DispWeek(Week);
  	DispDigit1(Led_Num1,0x02);
  	DispDigit1(Led_Num2,0x00);	
  	DispMinute(Year);	
}
//=============================================================================
//功能:disp alarm
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispAlarm(void)
{
  	DispSybmols(Led_Col,2,0x03);
  	DispHour(AlHour[AlarmCnt]);
	DispMinute(AlMinute[AlarmCnt]);	
}

static void DispAlarmMode(void)
{
	DispSybmols(Led_WeekW,7,0x00);	
	DispSybmols(Led_WeekR,7,Week_Bit_Tab[AlMode[AlarmCnt]+7]);	
}

static void DispAlarmOnOff(void)
{
	uchar disp_onoff;
  	DispSybmols(Led_AmPm,2,0x00);
  	DispSybmols(Led_Col,2,0x00);
  	DispDigit1(Led_Num1,0x0d);		//A
  	DispDigit1(Led_Num2,0x0e);		//L
  	DispDigit1(Led_Num3,0x00);		//O
  	
  	disp_onoff = 0x0f;
  	if(AlarmCnt)
  	{
  		if(ProFlag1&D_Alarm2On)
  			disp_onoff = 0x10;
  	}	
  	else
  	{
  		if(ProFlag1&D_Alarm1On)
  			disp_onoff = 0x10;
  	}		
	DispDigit1(Led_Num4,disp_onoff);
}

static void DispAlarmMode1(void)
{
  	DispSybmols(Led_AmPm,2,0x00);
  	DispSybmols(Led_Col,2,0x00);
  	DispDigit1(Led_Num1,0x0a);		
  	DispDigit1(Led_Num2,0x11);		//d
  	DispDigit1(Led_Num3,0x0b);		//-
  	DispDigit1(Led_Num4,AlMode[AlarmCnt]+5);	
}

//=============================================================================
//功能:temp_humi
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispTempHumi(void)
{
	uchar dispH,dispM,dispL;
	
	if(ProFlag1&D_TempF)
	{
		DispSybmols(Led_TH,3,0x06);	//F
	}	
	else	
	{
		DispSybmols(Led_TH,3,0x05);	//C
	}	
	
	if(TempNum[1]==TEMP_ERR)	
	{
		DispSybmols(Led_NumT1,2,0x00);	
		DispDigit(Led_NumT2,0x0b);	
    		DispDigit(Led_NumT3,0x0b);	

	}	
	else if(TempNum[1]==TEMP_HIGH)
	{
		DispSybmols(Led_NumT1,2,0x00);	
		DispDigit(Led_NumT2,0x0c);	//H
    		DispDigit(Led_NumT3,0x0c);	//H
		
	}
	else if(TempNum[1]==TEMP_LOW)
	{
		DispSybmols(Led_NumT1,2,0x00);	
		DispDigit(Led_NumT2,0x0d);	//L
    		DispDigit(Led_NumT3,0x0d);	//L
	}
	else
	{
		if(TempNum[1]&0x80)
		{
			if(ProFlag1&D_TempF)
			{
				dispH = 32-(uchar)(((uint)TempNum[0]*18+5)/10);
				dispM = dispH/10;
				dispL = dispH%10;
				dispH = 0x00;
			}	
			else
			{
				dispH = 0x80;
				dispM = TempNum[0]/10;
				dispL = TempNum[0]%10;
			}	
		}	
		else 
		{
			if(ProFlag1&D_TempF)
			{
				dispL = 32+(uchar)(((uint)TempNum[0]*18+5)/10);
			}	
			else
			{
				dispL = TempNum[0];
			}	
			dispH = dispL/100;
			dispM = (dispL%100)/10;
			dispL = (dispL%100)%10;
		}	
		
//		dispH = DispRv/100;
//		dispM = (DispRv%100)/10;
//		dispL = (DispRv%100)%10;
//			
//		DispSybmols(Led_NumT1,2,dispH);
//		DispDigit(Led_NumT2,dispM);	
//		DispDigit(Led_NumT3,dispL);	
		
		if(dispH==1)
		{
			DispSybmols(Led_NumT1,2,0x03);
			DispDigit(Led_NumT2,dispM);	
    			DispDigit(Led_NumT3,dispL);	
		}	
		else
		{
			DispSybmols(Led_NumT1,2,0x00);
			if(dispH==0)
			{
				if(dispM==0)
					dispM = 0x0a;
				DispDigit(Led_NumT2,dispM);	
    				DispDigit(Led_NumT3,dispL);	
			}	
			else
			{
				DispDigit(Led_NumT2,0x0b);	
    				DispDigit(Led_NumT3,dispL);	
			}	
		}	
	}
	
	
	if(TempNum[1]==TEMP_ERR)	
	{
		DispDigit(Led_NumH1,0x0b);	
    		DispDigit(Led_NumH2,0x0b);	
	}
	else
	{
		dispM = HumiNum/10;
		dispL = HumiNum%10;
		if(dispM==0)
			dispM = 0x0a;
		DispDigit(Led_NumH1,dispM);	
    		DispDigit(Led_NumH2,dispL);	
	}	
}

//=============================================================================
//功能:disp data
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispDate(void)
{
	uchar dispH,dispL;
	DispSybmols(Led_Date,3,0x07);
	dispH = Month/10;
	dispL = Month%10;
	if(dispH)
		DispSybmols(Led_NumD1,2,0x03);
	else	
		DispSybmols(Led_NumD1,2,0x00);
    	DispDigit(Led_NumD2,dispL);	
	
	dispH = Day/10;
	dispL = Day%10;
	DispDigit(Led_NumD3,dispH);	
	DispDigit(Led_NumD4,dispL);	
}
//=============================================================================
//功能:disp displv
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispSetDispLv(void)
{
	uchar dispH,dispL;
	DispSybmols(Led_Col,2,0x00);
	DispDigit1(Led_Num1,0x0E);		//L
	DispDigit1(Led_Num2,0x0B);		//-
	if(ProFlag1&D_AutoDimmer)
	{
		DispDigit1(Led_Num3,0x0D);	//A
		DispDigit1(Led_Num4,0x12);	//U
	}	
	else
	{
		dispL = DispLv+1;
		dispH = dispL/10;	
  		dispL = dispL%10;	
  		DispDigit1(Led_Num3,dispH);
  		DispDigit1(Led_Num4,dispL);
	}	
}

static void DispSetDimmerOnOff(void)
{
	DispSybmols(Led_Col,2,0x00);
	DispDigit1(Led_Num1,0x0a);	
	if(ProFlag1&D_AutoDimmer)
	{
		DispDigit1(Led_Num2,0x0a);	
		DispDigit1(Led_Num3,0x00);	//O
		DispDigit1(Led_Num4,0x10);	//N
	}	
	else
	{
		DispDigit1(Led_Num2,0x00);	//O	
  		DispDigit1(Led_Num3,0x0f);	//F
  		DispDigit1(Led_Num4,0x0f);	//F
	}	
}

//=============================================================================
//功能:disp light
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispSetLightMode(void)
{
	uchar dispH,dispL;
	DispSybmols(Led_Col,2,0x00);
	DispDigit1(Led_Num1,0x13);		//C
	DispDigit1(Led_Num2,0x0E);		//L
	dispL = LightMode+1;
	dispH = dispL/10;	
  	dispL = dispL%10;	
  	DispDigit1(Led_Num3,dispH);
  	DispDigit1(Led_Num4,dispL);
}

static void DispSetLightLv(void)
{
	uchar dispH,dispL;
	DispSybmols(Led_Col,2,0x00);
	DispDigit1(Led_Num1,0x0a);		
	DispDigit1(Led_Num2,0x13);		//C
	dispL = LightLv+1;
	dispH = dispL/10;	
  	dispL = dispL%10;	
  	DispDigit1(Led_Num3,dispH);
  	DispDigit1(Led_Num4,dispL);
}

//=============================================================================
//功能:disp sound
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispSetSoundLv(void)
{
	uchar dispH,dispL;
	DispSybmols(Led_Col,2,0x00);
	DispDigit1(Led_Num1,0x0a);	
	if(ProFlag1&D_ToneDis)
	{
		DispDigit1(Led_Num2,0x00);		//O	
  		DispDigit1(Led_Num3,0x0f);		//F
  		DispDigit1(Led_Num4,0x0f);		//F
	}	
	else
	{
		DispDigit1(Led_Num2,0x12);		//U
		dispL = SoundLv+1;
		dispH = dispL/10;	
  		dispL = dispL%10;	
  		DispDigit1(Led_Num3,dispH);
  		DispDigit1(Led_Num4,dispL);	
	}	
}
	
//=============================================================================
//功能:disp timer
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
static void DispTimer(void)
{
	uchar dispH,dispL;
  	DispSybmols(Led_Col,2,0x03);
  	DispMinute(TimerSec);	
  	dispH = TimerMin/10;	
  	dispL = TimerMin%10;	
  	DispDigit1(Led_Num1,dispH);
  	DispDigit1(Led_Num2,dispL);
}

static void ClearTimerNoDisp(void)
{
	DispWeek(0x0a);
  	DispSybmols(Led_AmPm,2,0x00);
	DispSybmols(Led_TH,3,0x00);
	DispSybmols(Led_NumT1,2,0x00);	
	DispDigit(Led_NumT2,0x0a);	
    	DispDigit(Led_NumT3,0x0a);
    	DispDigit(Led_NumH1,0x0a);	
    	DispDigit(Led_NumH2,0x0a);
	DispSybmols(Led_Date,3,0x00);
	DispSybmols(Led_NumD1,2,0x00);
	DispDigit(Led_NumD2,0x0a);
	DispDigit(Led_NumD3,0x0a);
	DispDigit(Led_NumD4,0x0a);
}
//=============================================================================
//功能:显示
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
void RefreshDisplay(void)
{
  	if(Mode==M_PowerOff)
  		return;	
    		
  	if(ProFlag&D_2HzFlag)
  	{
    		ProFlag &= ~D_2HzFlag;	
    		if(ProFlag&D_HalfSecFlag)		//clr
    		{
      			FlashSecClr();
      			if((ProFlag&D_AdjustFlag)==0)
      			{
      				HalfSecClr();
      			}			
    		}		
    		else
    		{
      			ProFlag &= ~D_AdjustFlag;	
//      			FlashSecDisp();
      			HalfSecDisp();	
    		}	
  	}
  
  	if(ProFlag&D_AdjustFlag)
  	{
    		ProFlag &= ~D_AdjustFlag;
    		HalfSecDisp();	
  	}	  	
}	
/*	
//----------------------------------------------------------------------------
*/
static void FlashSecClr(void)
{
  	if(ProFlag2&(D_PlayAlarm1|D_PlayAlarm2))
   		 ClearAlarmFlag();	
    
}
//static void FlashSecDisp(void)	
//{
//	
//}	
/*	
//----------------------------------------------------------------------------
*/
static void HalfSecClr(void)
{
  	if(ProFlag&D_NoFlash)	
  	{
  		ProFlag &= ~D_NoFlash;
  		return;
  	}	
     	
  	switch(Mode)
  	{
    		case M_SetTime:
    			switch(SubMode)
    			{
    				case 1:
    					DispSybmols(Led_AmPm,2,0x00);
    					DispDigit1(Led_Num1,0x0a);	
      	  				DispDigit1(Led_Num2,0x0a);
      	  				break;
      	  			case 2:
      	  				DispDigit1(Led_Num3,0x0a);	
      	  				DispDigit1(Led_Num4,0x0a);	
      	  				break;
      	  			case 3:
      	  				DispDigit1(Led_Num1,0x0a);
    					DispDigit1(Led_Num2,0x0a);	
    					DispDigit1(Led_Num3,0x0a);	
      	  				DispDigit1(Led_Num4,0x0a);	
      	  				break;
    				case 4:
    					DispSybmols(Led_NumD1,2,0x00);
    					DispDigit(Led_NumD2,0x0a);
    					break;
    				case 5:
    					DispDigit(Led_NumD3,0x0a);	
    					DispDigit(Led_NumD4,0x0a);	
    					break;
    				case 6:
    					DispSybmols(Led_TH,3,0x04);	
    					break;
    				default:
    					break;	
    			}
    			break;
    		case M_SetAlarm:
    			switch(SubMode)
    			{
    				case 1:
    					DispSybmols(Led_AmPm,2,0x00);
    					DispDigit1(Led_Num1,0x0a);	
      	  				DispDigit1(Led_Num2,0x0a);
      	  				break;
      	  			case 2:
      	  				DispDigit1(Led_Num3,0x0a);	
      	  				DispDigit1(Led_Num4,0x0a);	
      	  				break;
    				default:
    					break;	
    			}
    			break;
    		case M_Timer:
    			if(ProFlag2==D_PlayTimer)	
    			{
    				DispSybmols(Led_Col,2,0x00);
    				DispDigit1(Led_Num1,0x0a);	
      	  			DispDigit1(Led_Num2,0x0a);
    				DispDigit1(Led_Num3,0x0a);	
      	  			DispDigit1(Led_Num4,0x0a);
    			}	
    			break;
    		default:
    			break;	
      }		
}

static void HalfSecDisp(void)
{
  	switch(Mode)
  	{
    		case M_Normal:
    			DispAlarmFlag();
    			DispDstFlag();
    			DispTime();
    			DispTempHumi();
    			DispDate();
    			break;
    		case M_SetTime:
    			if(SubMode==0x00)
    				DispHourMode();
    			else if(SubMode==0x03)	
    				DispYear();
    			else	
      				DispTime();
      			DispAlarmFlag();	
      			DispDstFlag();
      			DispTempHumi();
    			DispDate();	
      			break;
      		case M_Alarm:
      			DispSybmol(Led_Dst,0);	
      			DispAlarmFlag();
      			DispAlarm();
      			DispAlarmMode();
      			DispTempHumi();
    			DispDate();	
      			break;
      		case M_SetAlarm:
      			if(SubMode==0x00)
      			{
      				DispAlarmOnOff();
      				DispWeek(0x0a);
      			}	
      			else if(SubMode==0x03)
      			{
      				DispAlarmMode1();
      				DispAlarmMode();
      			}	
      			else
      				DispAlarm();
      			DispSybmol(Led_Dst,0);		
      			DispAlarmFlag();
      			DispTempHumi();
    			DispDate();	
      			break;	
      		case M_SetDisp:
      			DispSybmol(Led_Dst,0);	
      			DispAlarmFlag();
      			ClearTimerNoDisp();
      			DispSetDispLv();	
      			break;		
      		case M_SetDisp1:
      			DispSybmol(Led_Dst,0);	
      			DispAlarmFlag();
      			ClearTimerNoDisp();
      			DispSetDimmerOnOff();	
      			break;		
      		case M_SetLight:
      			DispSybmol(Led_Dst,0);	
      			DispAlarmFlag();
      			ClearTimerNoDisp();
      			DispSetLightMode();	
      			break;	
      		case M_SetLight1:
      			DispSybmol(Led_Dst,0);	
      			DispAlarmFlag();
      			ClearTimerNoDisp();
      			DispSetLightLv();	
      			break;		
      		case M_SetSound:
      			DispSybmol(Led_Dst,0);	
      			DispAlarmFlag();
      			ClearTimerNoDisp();
      			DispSetSoundLv();	
      			break;			
      		case M_Timer:
      			DispSybmol(Led_Dst,0);	
      			DispAlarmFlag();
      			ClearTimerNoDisp();
      			DispTimer();
      			break;	
      		default:
      	  		break;	  
      	}		 
}	
//=============================================================================
