//=============================================================================
//Name		:alarm.c
//Purpose	:
//Version	:V1.0
//Author	:
//Date		:2022.05.24
//=============================================================================
#include "AllHeadFile.h"
//=============================================================================
//功能：
//输入参数：无
//输出参数：无
//
//=============================================================================

static uchar CheckAlarmWeek(uchar alarm_mode);
static uchar CheckAlarmTime(uchar alarm_mode);
/*
*****************************************************************************************************************
*/
void AlarmTime(void)
{
	if((SysFlag&D_IrEn)==0)
		return;
		
//	if((Mode==M_PowerOff)||(Mode==M_SetTime)||(Mode==M_SetAlarm))			
	if((Mode==M_SetTime)||(Mode==M_SetAlarm))			
		return;
		
	if((ProFlag&D_ResetSec)||Second)
		return;

	if(ProFlag1&D_Alarm1On)
	{
		if(CheckAlarmWeek(0))
		{
			if(CheckAlarmTime(0))
			{	
				CheckPowerOnWithAlarm();
				PlayAlarm(D_PlayAlarm1);	
				return;
			}	
		}	
	}	
	
	if(ProFlag1&D_Alarm2On)
	{
		if(CheckAlarmWeek(1))
		{
			if(CheckAlarmTime(1))
			{	
				CheckPowerOnWithAlarm();
				PlayAlarm(D_PlayAlarm2);	
			}	
		}	
	}	
}

/*
*****************************************************************************************************************
*/
static uchar CheckAlarmWeek(uchar alarm_mode)
{
	if(AlMode[alarm_mode]==2)			//day alarm
		return(1);
	else if(AlMode[alarm_mode]==0)			//1-5 alarm
	{
		if((Week>0)&&(Week<6))
			return(1);
	}	
	else 						//1-6 alarm
	{
		if(Week>0)
			return(1);
	}	
	return(0);	
}

static uchar CheckAlarmTime(uchar alarm_mode)
{
	if((Hour==AlHour[alarm_mode])&&(Minute==AlMinute[alarm_mode]))
		return(1);
	return(0);	
}

/*
*****************************************************************************************************************
*/
void PlayAlarm(uchar alarm_cnt)
{
	CheckStopAlarm();
	ProFlag2 = alarm_cnt;
	PlayAlarmTime[0] = 0;
	PlayAlarmTime[1] = 0;
}


void PlayKeyTone(void)
{
	ProFlag2 = D_PlayKeyTone;
	PlayAlarmTime[0] = 28;
	PlayAlarmTime[1] = 59;
}

/*
*****************************************************************************************************************
*/
void CheckStopAlarm(void)
{
	if(ProFlag2>D_PlayKeyTone)
	{	
		StopAlarm();
	}	
}

void StopAlarm(void)
{
	if(ProFlag2==D_PlayTimer)
		ResetTimer();
	ProFlag |= D_AdjustFlag;
	ProFlag2 = 0;
	T2O_Off();
}

/*
*****************************************************************************************************************
*/
//void PlaySnooze(void)
//{
//	if(ProFlag2&D_PlayAlarm1)
//	{
//		CheckStopAlarm();
//		ProFlag2 = D_PlaySnooze1;
//		SnoozeTime = 9;
//	}
//	else if(ProFlag2&D_PlayAlarm2)
//	{
//		CheckStopAlarm();
//		ProFlag2 = D_PlaySnooze2;
//		SnoozeTime = 9;
//	}
//}
//
///*
//*****************************************************************************************************************
//*/
//void CheckPlaySnooze(void)
//{
//	if(ProFlag2&(D_PlaySnooze1|D_PlaySnooze2))
//	{
//		SnoozeTime--;
//		if(SnoozeTime==0)
//		{
//			if(ProFlag2&D_PlaySnooze1)
//				PlayAlarm(1);
//			else if(ProFlag2&D_PlaySnooze2)	
//				PlayAlarm(2);		
//		}			
//	}	
//}
/*
*****************************************************************************************************************
*/
void IncAlarmHour(void)
{
	AlHour[AlarmCnt]++;
	if(AlHour[AlarmCnt]>23)
		AlHour[AlarmCnt] = 0;
}
void DecAlarmHour(void)
{
	if(AlHour[AlarmCnt]==0)
		AlHour[AlarmCnt] = 23;
	else
		AlHour[AlarmCnt]--;	
}

void IncAlarmMinute(void)
{
	AlMinute[AlarmCnt]++;
	if(AlMinute[AlarmCnt]>59)
		AlMinute[AlarmCnt] = 0;
}
void DecAlarmMinute(void)
{
	if(AlMinute[AlarmCnt]==0)
		AlMinute[AlarmCnt] = 59;
	else
		AlMinute[AlarmCnt]--;	
}

void IncAlarmMode(void)
{
	AlMode[AlarmCnt]++;
	if(AlMode[AlarmCnt]>2)
		AlMode[AlarmCnt] = 0;
}
void DecAlarmMode(void)
{
	if(AlMode[AlarmCnt]==0)
		AlMode[AlarmCnt] = 2;
	else
		AlMode[AlarmCnt]--;	
}

void TurnAlarmOnOff(void)
{
	if(AlarmCnt)
		ProFlag1 ^= D_Alarm2On;
	else	
		ProFlag1 ^= D_Alarm1On;
}


/*
*****************************************************************************************************************
*/
//32hz
void CheckPlayAlarm(void)
{
	if(ProFlag2)
	{
		PlayAlarmTime[0]++;
		if(PlayAlarmTime[0]>31)
		{
			PlayAlarmTime[0] = 0;
			PlayAlarmTime[1]++;
			if(PlayAlarmTime[1]>59)
			{
				StopAlarm();	
				return;
			}	
		}	
	
		if(ProFlag2==D_PlayKeyTone)
		{
			if((ProFlag1&D_ToneDis)==0)
				T2O_On();
		}	
		else 
		{
			if((PlayAlarmTime[0]&0x01)==0)
			{
				if(PlayAlarmTime[1]<10)
				{
					if(PlayAlarmTime[0]==2)
						T2O_On();
					else
						T2O_Off();	
				}	
				else if(PlayAlarmTime[1]<20)
				{
					if((PlayAlarmTime[0]==2)||(PlayAlarmTime[0]==6))
						T2O_On();
					else
						T2O_Off();	
				}	
				else 
				{
					if((PlayAlarmTime[0]==2)||(PlayAlarmTime[0]==6)||(PlayAlarmTime[0]==10)||(PlayAlarmTime[0]==14))
						T2O_On();
					else
						T2O_Off();	
				}
			}
		}		
	}	
}

//=============================================================================
