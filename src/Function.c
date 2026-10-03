//=============================================================================
//Name		:Function.c
//Purpose	:其它功能函数
//Version	:V1.0
//Author	:szl
//Date		:2015.05.26
//=============================================================================
#include "AllHeadFile.h"
//=============================================================================	

bit 	b32HzFlag = 0;
bit 	b2HzFlag = 0;

idata uchar Freq128Hz;
idata uchar SysFlag;

idata uchar Mode;
idata uchar ProFlag;
idata uchar ProFlag1;
idata uchar ProFlag2;
idata uchar ProFlag3;

xdata uchar BackTime;
xdata uchar SubMode;

xdata uchar Second;
xdata uchar Minute;
xdata uchar Hour;
xdata uchar Day;
xdata uchar Month;
xdata uchar Year;
xdata uchar Week;

idata uchar AlarmCnt;
idata uchar AlMinute[2];
idata uchar AlHour[2];
idata uchar AlMode[2];
xdata uchar PlayAlarmTime[2];

xdata uchar DetectLow;
xdata uchar DetectCnt;

xdata uchar DispLevel;
xdata uchar DispLv;
xdata uchar DispRv;
xdata uint DispRvBak;

xdata uchar LightLv;
xdata uchar SoundLv;

xdata uchar LightMode;
xdata uchar LightModeCnt;
xdata uchar PlayLight;

xdata uchar TimerState;
xdata uchar TimerSec;
xdata uchar TimerMin;
xdata uchar TimerSecBak;
xdata uchar TimerMinBak;

xdata uint RandomNum;

static void ReturnToNormalMode(void);
static void Timer(void);

static void IncDispRbg(uint *led_rbg);
static void CheckPlayLightRGB(void);
static void DispLevelDetect(void);
static void CheckPlayDispLevel(void);


unsigned char code Lv_Tab[] =
{
	10,		//0 %10
	37,		//1 %20
	64,		//2 %30
	91,		//3 %40
	118,		//4 %50
	145,		//5 %50
	172,		//6 %50
	199,		//7 %50
	226,		//8 %50
	255		//9 %100
};

unsigned char code Lv_Tab1[] =
{
	11,		//0 
	18,		//1 
	44,		//2
	61,		//3
	77,		//4
	94,		//5
	110,		//6
	127,		//7
	143,		//8
	160		//9 %100
};

unsigned char code Lv_Tab2[] =
{
	46,		//0 
	64,		//1 
	82,		//2
	100,		//3
	118,		//4
	136,		//5
	154,		//6
	172,		//7
	190,		//8
	255		//9 %100

//	10,		//0 
//	21,		//1 
//	32,		//2
//	43,		//3
//	54,		//4
//	65,		//5
//	76,		//6
//	87,		//7
//	98,		//8
//	255		//9 %100
};

//=============================================================================
//功能：初始化
//输入参数：无
//输出参数：无
//备注： 
//=============================================================================
void InitData(void)
{
	RandomNum = 5684;
	SysFlag = 0;
	ProFlag = 0;
	ProFlag1 = D_LightOn;
	ProFlag2 = 0;
	ProFlag3 = 0;
	
	AlarmCnt = 0;
  	AlMinute[0] = 0;
  	AlHour[0] = 6;
  	AlMode[0] = 2;
  	AlMinute[1] = 0;
  	AlHour[1] = 18;
  	AlMode[1] = 2;
  	
	DispLevel = 255;	
	DispLevel1 = 160;	//255;
  	DispLv = 9;
  	LightLv = 9;
  	DispRv = 255;
  	SoundLv = 4;
  	
  	LightMode = 0;
  	
  	Second = 0;
  	Minute = 0;
  	Hour = 0;
  	Day = 1;
  	Month = 1;
  	Year = 25;
  	AdjustWeek();
  	
  	IrKeyCode = 0xff;
  	TempNum[1] = TEMP_ERR;
}
//=============================================================================
//功能：时基函数
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
void TimerBase(void)
{
    	ProFlag |= D_2HzFlag;
    	ProFlag ^= D_HalfSecFlag;
    	if(ProFlag&D_HalfSecFlag)		
    	{	// clr
      		ProFlag &= ~D_ResetSec;	
      		TimerState &= ~D_TimerSec;
    	}		
    	else
    	{	//disp
      		ClockTime();
      		AlarmTime();
      		Timer();
      		CheckReadyRFC();
      		ReturnToNormalMode();
  	}  
}

//=============================================================================
//功能：时基函数
//输入参数：无
//输出参数：无
//备注：
//=============================================================================
void Timer32HzPro(void)
{
	CheckPlayAlarm();
	CheckPlayLightRGB();
	if(LightMode==12)
	{
		CheckPlayLightRGB();
		CheckPlayLightRGB();
		CheckPlayLightRGB();
		CheckPlayLightRGB();
		CheckPlayLightRGB();
		CheckPlayLightRGB();
		CheckPlayLightRGB();
		CheckPlayLightRGB();
		CheckPlayLightRGB();
	}	
	CheckPlayDispLevel();
    	DispLevelDetect();

    	Gxhtv4Server();
    	CheckReleaseIrHold();
    	DebounceCnt++;
    	Scankey();	
    	if(KeyCode!=NONE_KEY)
      		KeyDecode();		
}

//=============================================================================
//功能：
//输入参数：无
//输出参数：无
//
//=============================================================================
static void ReturnToNormalMode(void)
{
	if((Mode==M_PowerOff)||(Mode==M_Timer))
		return;
	
  	if(BackTime)
  	{
    		BackTime--;
    		if(BackTime==0)
    		{
      			if(Mode!=M_Normal)
      			{	
      				ChangeToNormal();	
      			}	
    		}			
  	}					
}

//=============================================================================
//功能：
//输入参数：无
//输出参数：无
//
//=============================================================================
void TurnPowerOff(void)
{
	CheckStopAlarm();
  	Mode = M_PowerOff;
//  	ProFlag3 = 0;
	ProFlag3 &= ~(D_PlayDispLv|D_PlayDispRgb|D_PlayDispMode);
  	ClearTimer();
  	IO_CON = 1;
  	PWM_ALL_Off();
  	Gxhtv4PowerOff();
	DispAllLed(0);
}

void TurnPowerOn(void)
{
  	IO_CON = 0;
  	DelayNOP(100);
  	DetectCnt = 3;
  	Gxhtv4PowerOn();
  	ChangeToNormal();
}

void CheckPowerOnWithAlarm(void)
{
	if(Mode)
		return;
	
	TurnPowerOn();		
}

//=============================================================================
//功能：
//输入参数：无
//输出参数：无
//
//=============================================================================
void TurnLightOn(void)
{
	ProFlag1 |= D_LightOn;
	DispAllLight(1);
	TurnLightMode();
}

void TurnLightOff(void)
{
	ProFlag1 &= ~D_LightOn;
	ProFlag3 &= ~(D_PlayDispRgb1|D_PlayDispMode1);
	DispAllLight(0);
}

void TurnLightOnOff(void)
{
	if(ProFlag1&D_LightOn)
    		TurnLightOff();	
    	else
    		TurnLightOn();	
}
//=============================================================================
//功能：
//输入参数：无
//输出参数：无
//
//=============================================================================
void TurnLightMode(void)
{
	ProFlag3 &= ~(D_PlayDispRgb1|D_PlayDispMode1);
	switch(LightMode)
	{
		case 0:
			SetAllDispRgb1(0);	//红
			break;
		case 1:
			SetAllDispRgb1(8);	//白
			break;	
		case 2:	
			SetAllDispRgb1(3);	//绿
			break;	
		case 3:	
			SetAllDispRgb1(2);	//黄
			break;	
		case 4:	
			SetAllDispRgb1(6);	//粉
			break;	
		case 5:	
			SetAllDispRgb1(1);	//橙
			break;		
		case 6:	
			SetAllDispRgb1(4);	//蓝
			break;		
		case 7:	
			LightModeCnt = 0;
			PlayLight = 0;	
			SetAllDispRgb1(0);	//全色渐变
			ProFlag3 |= D_PlayDispMode1;
			break;	
		case 8:
			PlayLight = 5;	
			SetAllDispRgb1_ud();		//上-下渐变
			ProFlag3 |= D_PlayDispMode1;
			break;				
		case 9:
			PlayLight = 15;	
			SetAllDispRgb1_gl();		//左-右渐变
			ProFlag3 |= D_PlayDispMode1;
			break;			
		case 10:
			SetDispRamdon1();		//随机渐变
			ProFlag3 |= D_PlayDispMode1;
			break;	
		case 11:
//			PlayLight = 5;	
//			SetAllDispRgb1_rol();		//循环
//			ProFlag3 |= D_PlayDispMode1;
//			break;	
		case 12:
			PlayLight = 5;	
			SetAllDispRgb1_rol_f();		//循环
			ProFlag3 |= D_PlayDispMode1;
			break;					
		default:
			break;		
	}
}

//=============================================================================
void IncLightMode(void)
{
	if((ProFlag1&D_LightOn)==0)
		return;
		
	LightMode++;
	if(LightMode>12)
		LightMode = 0;
	TurnLightMode();	
}

//=============================================================================
void DecLightMode(void)
{
	if((ProFlag1&D_LightOn)==0)
		return;
	if(LightMode==0)	
		LightMode = 12;
	else
		LightMode--;	
	TurnLightMode();	
}

//=============================================================================
static void IncDispRbg(uint *led_rbg)
{
	(*led_rbg)++;
        if((*led_rbg)>359)
        	(*led_rbg) = 0;
}

//=============================================================================
//功能：
//输入参数：无
//输出参数：无
//
//=============================================================================
static void CheckPlayLightRGB(void)
{
	uchar i,zf;
	
	LightModeCnt++;
	if((LightModeCnt&0x01)&&(LightMode==7))
		return;	
	
	if(ProFlag3&D_PlayDispMode1)
	{
        	if(ProFlag3&D_PlayDispRgb1)
        	{		
        		zf = 36;
        		for(i=0;i<18;i++)
			{
				if(PlayRgb6[i]==0)
					zf--;	
				else
				{
					PlayRgb6[i]--;
					IncDispRbg(&Led_GRB6[i]);
				}
				if(PlayRgb7[i]==0)
        				zf--;	
        			else
        			{
        				PlayRgb7[i]--;
        				IncDispRbg(&Led_GRB7[i]);
        			}
			}
        		
        		SysFlag |= D_DispUpdata1;
        		if(zf==0)
        		{
        			ProFlag3 &= ~D_PlayDispRgb1;
        		}	
        	}	
        	
        	if((ProFlag3&D_PlayDispRgb1)==0)	
        	{
				ProFlag3 |= D_PlayDispRgb1;
				if(LightMode==7)
				{
					PlayLight++;
					if(PlayLight>8)
						PlayLight = 0;
					SetAllDispRgb1_S();	
				}	
				else if(LightMode==8)
				{
					PlayLight++;
					if(PlayLight>17)
						PlayLight = 0;
					SetAllDispRgb1_ud_S();	
				}
				else if(LightMode==9)
				{
					PlayLight++;
					if(PlayLight>26)
						PlayLight = 0;
					SetAllDispRgb1_gl_S();	
				}	
				else if(LightMode==10)
				{
					SetDispRamdon1_S();	
				}	
//				else if(LightMode==11)
//				{
//					SetAllDispRgb1_rol_f();	
//				}
				else if((LightMode==11)||(LightMode==12))
				{
					SetAllDispRgb1_rol_f_S();	
				}
        	}
        }			
}

//=============================================================================
//功能：
//输入参数：无
//输出参数：无
//
//=============================================================================	
static void DispLevelDetect(void)
{
	uchar i;
	uint tmpadc16;
	
	DetectCnt++;
	if(DetectCnt&0x03)	
		return;
		
  	tmpadc16 = 0;
  	for(i=0;i<8;i++)
  	{
    		tmpadc16 += ADC_Convert(ADCHS27);
    		DelayNOP(20);
  	}	
  	tmpadc16 = tmpadc16/8; 	
  	
  	if(DispRvBak>tmpadc16)
  		i = DispRvBak-tmpadc16;
  	else
  		i = tmpadc16-DispRvBak;
  	if(i>3)
  		DispRvBak = tmpadc16;
  	
  	tmpadc16 = DispRvBak/8;
  		
  	if(tmpadc16>254)
  		tmpadc16 = 254;	
  		
  	DispRv = tmpadc16&0xff;

	for(i=0;i<10;i++)
	{
		if(DispRv<=Lv_Tab2[i])
			break;
	}
	
	if(i>9)
		i=9;
	
	DispRv = Lv_Tab[i];
  	
  	if((ProFlag1&D_AutoDimmer)==0)
		return;
  	if(DispLevel!=DispRv)
  	{	
  		ProFlag3 |= D_PlayDispLv;
  	}
  	
}	

//=============================================================================
//功能：
//输入参数：无
//输出参数：无
//
//=============================================================================	
static void CheckPlayDispLevel(void)
{
	uchar i;
	if(ProFlag3&D_PlayDispLv)
	{
		if(DispLevel>DispRv)
		{
			i = DispLevel-DispRv;
			if(i>63)
				DispLevel -= 8; 
			else if(i>15)
				DispLevel -= 4; 	
			else
				DispLevel--;	
			SysFlag |= D_DispUpdata;	
		}	
  		else if(DispLevel<DispRv)
  		{	
  			i = DispRv-DispLevel;
  			if(i>63)
				DispLevel += 8; 
			else if(i>15)
				DispLevel += 4; 	
			else
				DispLevel++;	
			SysFlag |= D_DispUpdata;
		}		
  		else 
  		{	
  			ProFlag3 &= ~D_PlayDispLv;
  		}	
	}	
}	
//=============================================================================
void IncDispLv(void)
{
	if(ProFlag1&D_AutoDimmer)
		return;
	ProFlag3 &= ~D_PlayDispLv;	
	DispLv++;
	if(DispLv>9)	
		DispLv = 0;
	DispLevel = Lv_Tab[DispLv];
	SysFlag |= D_DispUpdata;	
}

void DecDispLv(void)
{
	if(ProFlag1&D_AutoDimmer)
		return;
	ProFlag3 &= ~D_PlayDispLv;	
	if(DispLv==0)
		DispLv = 9;
	else
		DispLv--;	
	DispLevel = Lv_Tab[DispLv];
	SysFlag |= D_DispUpdata;	
}

//=============================================================================
void TurnAutoDimmerOnOff(void)
{
	ProFlag3 &= ~D_PlayDispLv;
	ProFlag1 ^= D_AutoDimmer;
	
	if(ProFlag1&D_AutoDimmer)
		DispLevel = DispRv;
	else
		DispLevel = Lv_Tab[DispLv];
	SysFlag |= D_DispUpdata;	
}

//=============================================================================
void IncLightLv(void)
{
//	ProFlag3 &= ~D_PlayDispLv1;	
	LightLv++;
	if(LightLv>9)	
		LightLv = 0;
	DispLevel1 = Lv_Tab1[LightLv];
	SysFlag |= D_DispUpdata1;	
}

//void DecLightLv(void)
//{
//	ProFlag3 &= ~D_PlayDispLv1;	
//	if(LightLv==0)
//		LightLv = 9;
//	else
//		LightLv--;
//	DispLevel1 = Lv_Tab1[LightLv];
//	SysFlag |= D_DispUpdata1;	
//}

//=============================================================================
//功能：
//输入参数：无
//输出参数：无
//
//=============================================================================
void CheckDcOn(void)
{
	if(SysFlag&D_IrEn)
		return;
	
	if(IO_DC_DET==1)	
	{
		TurnIrOn();
		Led_TurnOn();
		TurnPowerOn();
  		if(ProFlag1&D_LightOn)
  			TurnLightOn();
	}	
}

void CheckDcOff(void)
{
	if(IO_DC_DET==0)	
	{
		DetectLow++;
		if(DetectLow>2)
		{
			TurnIrOff();
			Led_TurnOff();
			StopAlarm();
			ProFlag3 = 0;
			TurnPowerOff();
		}	
	}
	else
	{
		DetectLow = 0;
	}	
}

//=============================================================================
//功能：
//输入参数：无
//输出参数：无
//
//=============================================================================
static void Timer(void)
{
	if(TimerState&D_TimerOn)
	{
		if(TimerState&D_TimerSec)
			return;
			
		if(TimerState&D_TimerDown)
		{
			if(TimerSec==0)
			{
				TimerSec = 59;
				TimerMin--;
			}	
			else
			{
				TimerSec--;
				if((TimerSec==0)&&(TimerMin==0))
				{
					TimerState = D_TimerDown;
					PlayAlarm(D_PlayTimer);
					ProFlag |= D_AdjustFlag;
				}	
			}	
		}	
		else 
		{
			TimerSec++;
			if(TimerSec>59)
			{
				TimerSec = 0;
				TimerMin++;
				if(TimerMin>99)
				{
					TimerMin = 99;
					TimerSec = 59;
					TimerState = 0;
				}	
			}	
		}		
	}	
}

void TurnTimerOnOff(void)
{
	TimerState |= D_TimerSec;
	TimerState ^= D_TimerOn;
}

void CheckTimerUpDown(void)
{
	TimerSecBak = TimerSec;
	TimerMinBak = TimerMin;
	if(TimerSec||TimerMin)
		TimerState = D_TimerDown;
	else
		TimerState = 0;	
}

void ClearTimer(void)
{
	TimerState = 0;
	TimerSec = 0;
	TimerMin = 0;
	TimerSecBak = 0;
	TimerMinBak = 0;
}

void ResetTimer(void)
{
	TimerState &= D_TimerDown;
	TimerSec = TimerSecBak;
	TimerMin = TimerMinBak;
}

//=============================================================================
//功能：随机数
//输入参数：
//输出参数：无
//=============================================================================
void Random(void)
{
	unsigned  int d;
	unsigned  int temp;
	temp=RandomNum^(RandomNum<<1);	
	d=(RandomNum<<3)^(RandomNum<<12);
	d^=temp;
	RandomNum<<=1;
	if(d&(0x8000))	RandomNum++;
}
	
//=============================================================================
//功能：延时，约6us
//输入参数：延时长度
//输出参数：无
//=============================================================================
void DelayNOP(uint Time)
{
	do{
		_nop_();
	}while( --Time );	
}
//=============================================================================
