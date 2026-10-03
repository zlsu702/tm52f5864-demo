#include "AllHeadFile.h"
/*
************************************************************************
平时只开2HZ唤醒，有按键中断后开启128HZ唤醒	
现DEMO板是用P34（INT0）做按键中断唤醒，一般做法还是用P1口做按键唤醒
************************************************************************
*/

xdata uchar KeyState=0;
xdata uchar DebounceCnt=0;
xdata uchar KeyCode=0;
xdata uchar OldKey;
xdata uchar FastCnt;

unsigned char CheckIfHoldKey(void);
unsigned char CheckIfMultKey(void);
/*
;;===================================================================
;---in mailoop
;---ScanKey
;	input		none
;	output		KeyCode
;	destroyed	none
;;===================================================================
*/
void Scankey(void)
{
	if(KeyState&KST_DEBOUNCE)
	{	
		//按键消抖
		if(DebounceCnt<DFirstKeyDL)
		{
			KeyCode=NONE_KEY;
			return;		
		}
	}
	//扫键
	PollingKey();				
	//已经有多键按下了
	if(KeyState&KST_MULTKEY)
	{
		//没有键按下清除按键标志
		KeyState &= ~(KST_MAST|KST_WAIT);
		KeyCode=NONE_KEY;
	}
	//没有键按下
	else if(KeyCode==NONE_KEY)
	{
		if(KeyState&KST_WAIT)
		{
			//松开键有效
			KeyState &= ~KST_MAST;
			KeyCode=OldKey;	
		}	
		else
		{
			//没有键按下清除按键标志
			KeyState &= ~KST_MAST;
			KeyCode=NONE_KEY;
		}	
	}
	//消抖处理完成
	else if(KeyState&KST_DEBOUNCE)
	{
		KeyState &= ~KST_DEBOUNCE;	
		if(KeyCode==OldKey)
		{
			KeyState |= KST_RELEASE;
			//判断是否松开键有效
			if(CheckIfHoldKey())
			{	
				KeyState |= KST_WAIT;
				KeyCode=NONE_KEY;
			}
			else
			{
				KeyCode=OldKey;	
			}	
		}
		else
		{
			//是抖动无效键
			KeyState &= ~KST_MAST;	
			KeyCode=NONE_KEY;
		}
	}
	//按键还没松开		
	else if(KeyState&KST_RELEASE)
	{
		if(KeyCode==OldKey)
		{
			if((KeyState&KST_MULT)==0)
			{
				//开始算按住键时间
				if(CheckIfHoldKey())
				{
					KeyState |= KST_MULT;	
					DebounceCnt=16;	
					FastCnt=0;	
				}
				else if(CheckIfMultKey())
				{
					KeyState |= KST_MULT;	
					DebounceCnt=0;	
					FastCnt=1;
				}
					
				KeyCode=NONE_KEY;
			}			
			else		
			{
				//算按住键的时间
				if(FastCnt<2)			
				{
					if(DebounceCnt>31)
					{
						DebounceCnt=0;
						FastCnt++;
					}	
					KeyCode=NONE_KEY;
				}
				else
				{
					if(CheckIfHoldKey()==1)
					{
						if((KeyState&KST_HOLD)==0)	
						{	
							KeyState &= ~KST_WAIT;
							KeyState |= KST_HOLD;	
							DebounceCnt = 0;	
							KeyCode=KeyCode+5;
						}
						else	
							KeyCode=NONE_KEY;
					}
					else if(CheckIfMultKey()==1)
					{
						if(DebounceCnt>3)	//8hz	
						{	
							DebounceCnt=0;
							ProFlag |= D_NoFlash;
						}	
						else						
							KeyCode=NONE_KEY;
					}
					else
						KeyCode=NONE_KEY;
				}
			}
		}
		else
		{
			KeyState |= KST_MULTKEY;		//有不同键按下
			KeyState &= ~KST_MAST;	
			KeyCode=NONE_KEY;
		}
	}
	//第一次按下	
	else
	{
		KeyState |= KST_DEBOUNCE;
		DebounceCnt=0;
		OldKey=KeyCode;
		KeyCode=NONE_KEY;
	}	
}
/*
************************************************************************
*/
unsigned char CheckIfHoldKey(void)
{	
	if(ProFlag2>D_PlayKeyTone)
		return(0);
	if((KeyCode==KEY_LIGHT)&&(Mode==M_Normal))
		return(1);
//	if((KeyCode==KEY_UP)&&(Mode==M_Normal))
	if((KeyCode==KEY_DOWN)&&(Mode==M_Normal))
		return(1);	
	if((KeyCode==KEY_SET)&&((Mode==M_Normal)||(Mode==M_SetDisp)))
		return(1);		
  	return(0);	  
}

unsigned char CheckIfMultKey(void)
{
	if((KeyCode==KEY_UP)||(KeyCode==KEY_DOWN))
	{
		if(((Mode==M_SetTime)&&((SubMode>0)&&(SubMode<6)))||((Mode==M_SetAlarm)&&((SubMode>0)&&(SubMode<3)))||(Mode==M_Timer))
	  		return(1);	
	} 		
	return(0);
}
				
/*
************************************************************************

	
************************************************************************
*/
void PollingKey(void)
{
        u8 TmpKey = 0;
  	KeyCode = 0;
  	
  	TmpKey = ADC_Convert1(ADCHS13);
  	if(TmpKey<KEY1_ADC_VOL)
  	  	KeyCode = 1;
  	else if(TmpKey<KEY2_ADC_VOL)
  	  	KeyCode = 2;  
  	else if(TmpKey<KEY3_ADC_VOL)
  	  	KeyCode = 3;
  	else if(TmpKey<KEY4_ADC_VOL)
  	  	KeyCode = 4;
  	else if(TmpKey<KEY5_ADC_VOL)
  	  	KeyCode = 5;
  	else if(TmpKey<KEY6_ADC_VOL)
  	  	KeyState |= KST_MULTKEY; 	
  	else
  	  	KeyState &= ~KST_MULTKEY;	                   	
  	
}

/**************************************************************************************************
 **************************************************************************************************/ 
 