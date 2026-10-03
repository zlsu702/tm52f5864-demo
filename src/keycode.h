//=============================================================================
//Name		:keycode.h
//Purpose	:函数、变量外部声明
//Version	:V1.0
//Author	:
//Date		:2021.10.27
//=============================================================================
#ifndef __KEYCODE_H__
#define __KEYCODE_H__
//=============================================================================

//=============================================================================
/*外部函数声明*/
//=============================================================================
void KeyDecode(void);
void SetBackTime(uchar back_time);
void ChangeToNormal(void);
void ResetSecond(void);
void ChangeToSetTime(void);
void ChangeToAlarm(void);
void ChangeToSetAlarm(void);


void IncSetTimeNum(void);
void DecSetTimeNum(void);
void IncSetAlarmNum(void);
void DecSetAlarmNum(void);
//=============================================================================
#endif
//=============================================================================