//=============================================================================
//Name		:time.c
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
static uchar GetMonthMaxDate(void);
/*
*****************************************************************************************************************
*/
unsigned char code WeekAdjustTab[] = 
{	
	0x00,		//0
	0x05,		//1
	0x01,		//2
	0x01,		//3
	0x04,		//4
	0x06,		//5
	0x02,		//6
	0x04,		//7
	0x00,		//8
	0x03, 		//9
	0x05, 		//10
	0x01, 		//11	
	0x03 		//12
};
/*
*****************************************************************************************************************
*/
void ClockTime(void)
{
	if(ProFlag&D_ResetSec)	
		return;
	if(IncRealSec()==0)
	{
//	  	CheckPlaySnooze();
	  	if(IncRealMin()==0)
	  	{
	  		if(IncRealHour()==0)
	  		{
	  			if(IncRealDay()==0)
	  				if(IncRealMonth()==0)
	  					IncRealYear();
	  			
	  			AdjustWeek();		
	  		}	
	  	}	
	}		
}

/*
*****************************************************************************************************************
*/
void AdcOneHour(void)
{
	if(IncRealHour()==0)
	{
		if(IncRealDay()==0)
			if(IncRealMonth()==0)
				IncRealYear();
		AdjustWeek();		
	}	
}

void SbcOneHour(void)
{
	DecRealHour();
	if(Hour==23)
	{
		Day--;
		if(Day==0)
		{
			Month--;
			if(Month==0)
			{
				Month = 12;
				DecRealYear();
			}	
			Day = GetMonthMaxDate();
		}	
		AdjustWeek();
	}	
}

/*
*****************************************************************************************************************
*/
uchar IncRealSec(void)
{
	Second++;
	if(Second>59)
		Second = 0;
	return(Second);	
}
/*
*****************************************************************************************************************
*/
uchar IncRealMin(void)
{
	Minute++;
	if(Minute>59)
		Minute = 0;
	return(Minute);	
}
/*
*****************************************************************************************************************
*/
uchar IncRealHour(void)
{
	Hour++;
	if(Hour>23)
		Hour = 0;
	return(Hour);	
}
/*
*****************************************************************************************************************
*/
uchar IncRealDay(void)
{
	uchar max_day;
	max_day = GetMonthMaxDate();
	if(max_day>Day)
	{
		Day++;
		return(1);
	}	
	else
	{
		Day = 1;
		return(0);
	}	
}
/*
*****************************************************************************************************************
*/
uchar IncRealMonth(void)
{
	Month++;
	if(Month>12)
	{
		Month = 1;
		return(0);
	}	
	return(1);
}
/*
*****************************************************************************************************************
*/
void IncRealYear(void)
{
	Year++;
	if(Year>99)
		Year = 0;
}
/*
*****************************************************************************************************************
*/
void DecRealMin(void)
{
	if(Minute==0)
		Minute = 59;
	else
		Minute--;
}
/*
*****************************************************************************************************************
*/
void DecRealHour(void)
{
	if(Hour==0)
		Hour = 23;
	else
		Hour--;
}
/*
*****************************************************************************************************************
*/
void DecRealDay(void)
{
	Day--;
	if(Day==0)
		Day = GetMonthMaxDate();
}
/*
*****************************************************************************************************************
*/
void DecRealMonth(void)
{
	Month--;
	if(Month==0)
		Month = 12;
}
/*
*****************************************************************************************************************
*/
void DecRealYear(void)
{
	if(Year==0)
		Year = 99;
	else	
		Year--;
}
/*
*****************************************************************************************************************
*/
void AdjustWeekDay(void)
{
	uchar max_day;
	max_day = GetMonthMaxDate();
	if(Day>max_day)
	{
		Day = 1;
		if(IncRealMonth()==0)
	  		IncRealYear();	
	}	
	AdjustWeek();
}

/*
*****************************************************************************************************************
*/
static uchar GetMonthMaxDate(void)
{
	uchar max_day;
	uchar max_month;
	if(Month==2)
	{
		if(Year&0x03)
			max_day = 28;
		else
			max_day = 29;		
	}	
	else
	{
		if(Month<8)
			max_month = Month;
		else 	
			max_month = Month-1;
		if(max_month&0x01)
			max_day = 31;	
		else
			max_day = 30;	
	}	
	return(max_day);
}
/*
*****************************************************************************************************************
;;      6/2/2/5/0/3/5/1/4/6/2/4			
;功能: 根据阳历日期自动校正星期
;入口参数:  RealYear[1:0]为16进制数年份
;	   RealMonth为16进制月份
;	   RealDate[1:0]为16进制数日期
;出口参数: RealWeek为校正后的星期
;影响寄存器: R[3:0]
;计算方法: RealWeek=(闰年个数+校正日期+日期+年)%7
*/
void AdjustWeek(void)
{
	uchar day_sum;
	
	day_sum = WeekAdjustTab[Month];
	
	day_sum = day_sum+Year+Year/4+Day+1;
	if(((Year&0x03)==0)&&(Month<3))
		day_sum--;
	
	Week = day_sum%7;
}

//=============================================================================
