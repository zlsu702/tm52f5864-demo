//=============================================================================
//Name		:alarm.h
//Purpose	:函数、变量外部声明
//Version	:V1.0
//Author	:
//Date		:2021.10.27
//=============================================================================
#ifndef __ALARM_H__
#define __ALARM_H__
//=============================================================================

//=============================================================================
/*外部函数声明*/
//=============================================================================
void AlarmTime(void);
void CheckPlayAlarm(void);
void CheckStopAlarm(void);
void StopAlarm(void);
void PlayAlarm(uchar alarm_cnt);
//void PlaySnooze(void);
//void CheckPlaySnooze(void);

void PlayKeyTone(void);

void IncAlarmHour(void);
void DecAlarmHour(void);
void IncAlarmMinute(void);
void DecAlarmMinute(void);
void IncAlarmMode(void);
void DecAlarmMode(void);
void TurnAlarmOnOff(void);

//=============================================================================
#endif
//=============================================================================