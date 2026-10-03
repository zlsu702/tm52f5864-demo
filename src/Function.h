//=============================================================================
//Name		:Function.h
//Purpose	:函数、变量外部声明
//Version	:V1.0
//Author	:szl
//Date		:2015.05.26
//=============================================================================
#ifndef __FUNCTION_H__
#define __FUNCTION_H__
//=============================================================================
//=============================================================================
/*外部变量声明*/

//Mode
#define	M_PowerOff	0
#define	M_Normal	1
#define	M_SetTime	2
#define	M_Alarm		3
#define	M_SetAlarm	4
#define	M_SetDisp	5	//key
#define	M_SetDisp1	6	//ir
#define	M_SetLight	7	//mode
#define	M_SetLight1	8	//lv
#define	M_SetSound	9	
#define	M_Timer		10

#define BACK_TIME	30	//15S

//SysFlag
#define	D_DispUpdata	0x01
#define	D_DispUpdata1	0x02
#define	D_IrEn		0x04	//D_DcOn
//ProFlag
#define	D_2HzFlag	0x01
#define	D_AdjustFlag	0x02
#define	D_HalfSecFlag	0x04
#define	D_24Hour	0x08
#define	D_ResetSec	0x10
#define	D_NoFlash	0x20

//ProFlag1
#define	D_Alarm1On	0x01
#define	D_Alarm2On	0x02
#define	D_TempF		0x04
#define	D_Dst		0x08
#define	D_ToneDis	0x20
#define	D_LightOn	0x40
#define	D_AutoDimmer	0x80

//ProFlag2
#define	D_PlayKeyTone	0x01
#define	D_PlayAlarm1	0x02
#define	D_PlayAlarm2	0x04
#define	D_PlayTimer	0x08

//ProFlag3
#define	D_PlayDispLv	0x01
#define	D_PlayDispRgb	0x02
#define	D_PlayDispMode	0x08
#define	D_PlayDispLv1	0x10
#define	D_PlayDispRgb1	0x20
#define	D_PlayDispMode1	0x80

//TimerState
#define	D_TimerOn	0x01
#define	D_TimerDown	0x02
#define	D_TimerSec	0x04

extern bit 	b32HzFlag;
extern bit 	b2HzFlag;

extern idata uchar Freq128Hz;
extern idata uchar SysFlag;
extern idata uchar Mode;
extern idata uchar ProFlag;
extern idata uchar ProFlag1;
extern idata uchar ProFlag2;
extern idata uchar ProFlag3;

extern xdata uchar BackTime;
extern xdata uchar SubMode;

extern xdata uchar Second;
extern xdata uchar Minute;
extern xdata uchar Hour;
extern xdata uchar Day;
extern xdata uchar Month;
extern xdata uchar Year;
extern xdata uchar Week;

extern idata uchar AlarmCnt;
extern idata uchar AlMinute[2];
extern idata uchar AlHour[2];
extern idata uchar AlMode[2];
extern xdata uchar PlayAlarmTime[2];

extern xdata uchar DetectLow;
extern xdata uchar DetectCnt;

extern xdata uchar DispLevel;
extern xdata uchar DispLv;
extern xdata uchar DispRv;
extern xdata uint DispRvBak;

extern xdata uchar LightLv;
extern xdata uchar SoundLv;

extern xdata uchar LightMode;
extern xdata uchar LightModeCnt;
extern xdata uchar PlayLight;

extern xdata uchar TimerState;
extern xdata uchar TimerSec;
extern xdata uchar TimerMin;
extern xdata uchar TimerSecBak;
extern xdata uchar TimerMinBak;

extern xdata uint RandomNum;

//=============================================================================
/*外部函数声明*/
void InitData(void);
void TimerBase(void);
void Timer32HzPro(void);
void TurnPowerOff(void);
void TurnPowerOn(void);
void CheckPowerOnWithAlarm(void);
void ClearTimer(void);
void ResetTimer(void);
void CheckTimerUpDown(void);
void TurnTimerOnOff(void);

void CheckDcOn(void);
void CheckDcOff(void);

void TurnDispMode(void);
void IncDispMode(void);
void TurnAutoDimmerOnOff(void);
void IncDispLv(void);
void DecDispLv(void);

void TurnLightOn(void);
void TurnLightOff(void);
void TurnLightOnOff(void);
void TurnLightMode(void);
void IncLightMode(void);
void DecLightMode(void);
void SyncLightDispMode(void);
void IncLightLv(void);
//void DecLightLv(void);

void Random(void);
void DelayNOP(uint Time);

//=============================================================================
#endif
//=============================================================================