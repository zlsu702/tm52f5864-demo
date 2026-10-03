//=============================================================================
//Name		:Led.h
//Purpose	:函数、变量外部声明
//Version	:V1.0
//Author	:
//Date		:2021.10.27
//=============================================================================
#ifndef __LED_H__
#define __LED_H__
//=============================================================================

//=============================================================================
/*外部变量声明*/
//=============================================================================
//LCDRAM处于外部寄存器
extern code uchar Led_Col[];
extern code uchar Led_AmPm[];
extern code uchar Led_Alarm[];
extern code uchar Led_Dst[];
extern code uchar Led_TH[];
extern code uchar Led_Date[];
extern code uchar Led_WeekR[];
extern code uchar Led_WeekW[];
extern code uchar Led_Num1[];
extern code uchar Led_Num2[];
extern code uchar Led_Num3[];
extern code uchar Led_Num4[];
extern code uchar Led_NumT1[];
extern code uchar Led_NumT2[];
extern code uchar Led_NumT3[];
extern code uchar Led_NumH1[];
extern code uchar Led_NumH2[];
extern code uchar Led_NumD1[];
extern code uchar Led_NumD2[];
extern code uchar Led_NumD3[];
extern code uchar Led_NumD4[];

extern xdata uchar DispLevel1;

extern xdata uint Led_GRB6[18];
extern xdata uint Led_GRB7[18];
extern xdata uchar PlayRgb6[18];
extern xdata uchar PlayRgb7[18];
//=============================================================================
/*外部函数声明*/
//=============================================================================
void Led_Reflush(void);
void Led_Reflush1(void);
void Led_TurnOn( void );
void Led_TurnOff( void );
void DispAllLed(uchar OnOff);
void DispAllLight(uchar OnOff);
void DispSybmol( uchar *LedNum, uchar OnOff);
void DispSybmols( uchar *LedNum, uchar Long, uchar LedTmpSegs);
void DispDigit1( uchar *LedNum, uchar Font);
void DispDigit( uchar *LedNum, uchar Font);

void SetAllDispRgb1(uchar rgb_num);
//void SetAllDispRgb1_1(uchar rgb_num);
void SetAllDispRgb1_S(void);
void SetAllDispRgb1_ud(void);
void SetAllDispRgb1_ud_S(void);
void SetAllDispRgb1_gl(void);
void SetAllDispRgb1_gl_S(void);
//void SetAllDispRgb1_rol(void);
//void SetAllDispRgb1_rol_S(void);
void SetAllDispRgb1_rol_f(void);
void SetAllDispRgb1_rol_f_S(void);
void SetDispRamdon1(void);
void SetDispRamdon1_S(void);
//=============================================================================
#endif
//=============================================================================