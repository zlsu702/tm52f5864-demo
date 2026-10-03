//=============================================================================
//Name		:alarm.h
//Purpose	:函数、变量外部声明
//Version	:V1.0
//Author	:
//Date		:2021.10.27
//=============================================================================
#ifndef __TIME_H__
#define __TIME_H__
//=============================================================================

//=============================================================================
/*外部函数声明*/
//=============================================================================
void ClockTime(void);
uchar IncRealSec(void);
uchar IncRealMin(void);
uchar IncRealHour(void);
uchar IncRealDay(void);
uchar IncRealMonth(void);
void IncRealYear(void);
void DecRealMin(void);
void DecRealHour(void);
void DecRealDay(void);
void DecRealMonth(void);
void DecRealYear(void);
void AdjustWeekDay(void);
void AdjustWeek(void);

void AdcOneHour(void);
void SbcOneHour(void);
//=============================================================================
#endif
//=============================================================================