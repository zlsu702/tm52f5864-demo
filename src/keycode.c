//=============================================================================
//Name		:keycode.c
//Purpose	:keycode
//Version	:V1.0
//Author	:
//Date		:2022.05.24
//=============================================================================
#include "AllHeadFile.h"
//=============================================================================
static void NormalDecode(void);
static void SetTimeDecode(void);
static void AlarmDecode(void);
static void SetAlarmDecode(void);
static void SetDispDecode(void);
static void SetLightDecode(void);
static void TimerDecode(void);
//=============================================================================
//功能：按键处理
//输入参数：源数据地址、字符数
//输出参数：无
//=============================================================================
void KeyDecode(void)
{
	if(Mode==M_PowerOff)	
		return;
		
    	if(ProFlag2>D_PlayKeyTone)
    	{
    		CheckStopAlarm();
    		return;
    	}
    	
    	if((KeyState==(KST_RELEASE|KST_MULT))==0)
    		PlayKeyTone();	
    		
    	if((KeyCode==KEY_LIGHT)&&(Mode!=M_SetLight))
    	{
    		TurnLightOnOff();
    		return;	
    	}	
    	
    	switch(Mode)	
    	{
    		case M_Normal:
    			NormalDecode();
    			break;
    		case M_SetTime:
    			SetTimeDecode();
    			break;
    		case M_Alarm:
    			AlarmDecode();
    			break;		
    		case M_SetAlarm:
    			SetAlarmDecode();
    			break;	
    		case M_SetDisp:
    			SetDispDecode();
    			break;	
    		case M_SetLight:	
    			SetLightDecode();
    			break;
    		case M_Timer:	
    			TimerDecode();
    			break;	
    		default:
    			ProFlag &= ~D_AdjustFlag;
    			break;	
    	}	
}	
//=============================================================================
//功能：
//输入参数：源数据地址、字符数
//输出参数：无
//=============================================================================
void SetBackTime(uchar back_time)
{
	ProFlag |= D_AdjustFlag;
	BackTime = back_time;
	if(ProFlag&D_HalfSecFlag)
		BackTime++;
}

//=============================================================================
//功能：
//输入参数：无
//输出参数：无
//
//=============================================================================
void ChangeToNormal(void)
{
  	Mode = M_Normal;	
  	SubMode = 0;
  	ProFlag |= D_AdjustFlag;
}

void ResetSecond(void)
{
	ProFlag |= D_ResetSec;
	Second = 0;
}

void ChangeToSetTime(void)
{
  	SetBackTime(10);
	Mode = M_SetTime;
	SubMode = 0;
}

void ChangeToAlarm(void)
{
  	Mode = M_Alarm;	
  	SubMode = 0;
  	SetBackTime(4);
}

void ChangeToSetAlarm(void)
{
  	Mode = M_SetAlarm;	
  	SubMode = 0;
  	SetBackTime(10);
}

//=============================================================================
//功能：
//输入参数：源数据地址、字符数
//输出参数：无
//=============================================================================
static void NormalDecode(void)
{
	switch(KeyCode)
	{
		case KEY_SET:
			ChangeToSetTime();
			break;	
		case KEY_ALARM:
			AlarmCnt = 0;
			ChangeToAlarm();
			break;
		case KEY_HSET:
			SetBackTime(4);
			Mode = M_SetDisp;
			break;	
//		case KEY_HUP:
		case KEY_HDOWN:
			ProFlag1 ^=D_Dst;
			ProFlag |= D_AdjustFlag;
			if(ProFlag1&D_Dst)
				AdcOneHour();
			else
				SbcOneHour();	
			break;			
		case KEY_HLIGHT:
			if(ProFlag1&D_LightOn)
			{
				SetBackTime(4);
				Mode = M_SetLight;
			}	
			break;
		default:
			ProFlag &= ~D_AdjustFlag;
			break;		
	}
}
//=============================================================================
void IncSetTimeNum(void)
{
	SetBackTime(10);
	switch(SubMode)
	{
		case 0:
			ProFlag ^= D_24Hour;
			break;
		case 1:
			IncRealHour();
			break;
		case 2:
			ResetSecond();	
			IncRealMin();
			break;
		case 3:
			IncRealYear();
			AdjustWeekDay();
			break;
		case 4:
			IncRealMonth();
			AdjustWeekDay();
			break;
		case 5:
			IncRealDay();
			AdjustWeek();
			break;
		case 6:
			ProFlag1 ^= D_TempF;
			break;	
		default:
			break;	
	}
}
//=============================================================================
void DecSetTimeNum(void)
{
	SetBackTime(10);
	switch(SubMode)
	{
		case 0:
			ProFlag ^= D_24Hour;
			break;
		case 1:
			DecRealHour();
			break;
		case 2:
			ResetSecond();	
			DecRealMin();
			break;
		case 3:
			DecRealYear();
			AdjustWeekDay();
			break;
		case 4:
			DecRealMonth();
			AdjustWeekDay();
			break;
		case 5:
			DecRealDay();
			AdjustWeek();
			break;
		case 6:
			ProFlag1 ^= D_TempF;
			break;	
		default:
			break;	
	}
}
//=============================================================================
static void SetTimeDecode(void)
{
	switch(KeyCode)
	{
		case KEY_SET:
			SetBackTime(10);
			SubMode++;
			if(SubMode>6)
				ChangeToNormal();
			break;
		case KEY_UP:
			IncSetTimeNum();
			break;	
		case KEY_DOWN:
			DecSetTimeNum();
			break;	
		default:
			ProFlag &= ~D_AdjustFlag;
			break;		
	}
}
//=============================================================================
static void AlarmDecode(void)
{
	switch(KeyCode)
	{
		case KEY_SET:
			ChangeToSetAlarm();
			break;	
		case KEY_ALARM:
			AlarmCnt ^= 0x01;
			SetBackTime(4);
			break;
		default:
			ProFlag &= ~D_AdjustFlag;
			break;		
	}
}
//=============================================================================
void IncSetAlarmNum(void)
{
	SetBackTime(10);
	switch(SubMode)
	{
		case 0:
			TurnAlarmOnOff();
			break;
		case 1:
			IncAlarmHour();
			break;
		case 2:
			IncAlarmMinute();
			break;
		case 3:
			IncAlarmMode();
			break;
		default:
			break;				
	}
}
//=============================================================================
void DecSetAlarmNum(void)
{
	SetBackTime(10);
	switch(SubMode)
	{
		case 0:
			TurnAlarmOnOff();
			break;
		case 1:
			DecAlarmHour();
			break;
		case 2:
			DecAlarmMinute();
			break;
		case 3:
			DecAlarmMode();
			break;
		default:
			break;				
	}
}
//=============================================================================
static void SetAlarmDecode(void)
{
	switch(KeyCode)
	{
		case KEY_SET:
			SetBackTime(10);
			SubMode++;
			if(SubMode>3)
				ChangeToAlarm();
			break;
		case KEY_UP:
			IncSetAlarmNum();
			break;	
		case KEY_DOWN:
			DecSetAlarmNum();
			break;	
		default:
			ProFlag &= ~D_AdjustFlag;
			break;		
	}
}

//=============================================================================
static void SetDispDecode(void)
{
	switch(KeyCode)
	{
		case KEY_HSET:
//			ResetAdjActive();
			SetBackTime(4);
			TurnAutoDimmerOnOff();
			break;	
		case KEY_UP:
//			ResetAdjActive();
			SetBackTime(4);
			IncDispLv();
			break;
		case KEY_DOWN:
//			ResetAdjActive();
			SetBackTime(4);
			DecDispLv();
			break;	
		default:
			ProFlag &= ~D_AdjustFlag;
			break;		
	}
}

//=============================================================================
static void SetLightDecode(void)
{
	switch(KeyCode)
	{
		case KEY_UP:
//			ResetAdjActive();
			SetBackTime(4);
			IncLightMode();
			break;
		case KEY_DOWN:
//			ResetAdjActive();
			SetBackTime(4);
			DecLightMode();
			break;	
		default:
			ProFlag &= ~D_AdjustFlag;
			break;		
	}
}

//=============================================================================
static void TimerDecode(void)
{
	switch(KeyCode)
	{
		case KEY_UP:
			if((TimerState&D_TimerOn)==0)
			{
				SetBackTime(10);
				if(KeyState==(KST_RELEASE|KST_MULT))
				{
					if(TimerMin<99)
						TimerMin++;
					else if(TimerSec<59)
						TimerSec++;	
				}	
				else if((TimerSec<59)||(TimerMin<99))
				{
					TimerSec++;
					if(TimerSec>59)
					{
						TimerSec = 0;
						TimerMin++;
					}	
				}	
				CheckTimerUpDown();
			}
			break;
		case KEY_DOWN:
			if((TimerState&D_TimerOn)==0)
			{
				SetBackTime(10);
				if(KeyState==(KST_RELEASE|KST_MULT))
				{
					if(TimerMin)
						TimerMin--;
					else if(TimerSec)
						TimerSec--;	
				}	
				else if(TimerSec||TimerMin)
				{
					if(TimerSec)
						TimerSec--;
					else
					{
						TimerSec = 59;
						TimerMin--;
					}		
				}	
				CheckTimerUpDown();
			}
			break;	
		default:
			ProFlag &= ~D_AdjustFlag;
			break;		
	}
}
//=============================================================================
