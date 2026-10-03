/*********************************************************************************************************************/
#include "AllHeadFile.h"
//=============================================================================
#define IR_ID_H		0x00
#define IR_ID_L		0xFF

#define IO_IR		P1_2

idata uchar IrKeyState;
idata uchar IrState;
idata uchar IrByteCnt;
idata uchar IrBitCnt;
idata ulong IrData;
idata ulong IrDataBuf;
idata uchar IrHoldTime;
idata uchar IrReleaseTime;
idata uchar IrOldKey;
idata uchar IrKeyCode;


//static void CheckIrHoldKey(void);
static void CheckIrMuteKey(uchar ir_key);
//static void SetHoldKey(uchar holdkey);

/*
*****************************************************************************************************************
*/
//8k
void CheckReceiveData(void)
{
  	uchar tmpBit;	
//  	uchar tmpData[4];	
  	if(SysFlag&D_IrEn)
  	{
    		if(IrBitCnt<255)
    			IrBitCnt++;
    		if(IO_IR==0)	//low
    		{
//      			if((IrState&0x01)==0)
//        			IrState &= ~0x02;
      			IrState &= ~0x01;
    		}
   		else		//high
    		{
      			if((IrState&0x01)==0)
//      				IrState |= 0x01;
//      			else if((IrState&0x01)==0)
      			{
      				IrState |= 0x01;	//有上升沿
      				//check receive bit
      				tmpBit = 0;
      				if((IrBitCnt<4)||(IrBitCnt>46))
      				{	
      	  				IrState &= ~0x04;	//BitErr
      				}
      				else if(IrBitCnt<13)
      				{
      	  				if(IrState&0x04)
      	    					tmpBit = 1;		//bit0		
      				}
      				else if(IrBitCnt<27)
      				{
      	  				if(IrState&0x04)
      	    					tmpBit = 2;		//bit1	
//      	    				CheckIrHoldKey();	//hold		
					IrReleaseTime = 0;
				  	if(IrKeyState==D_IrMultKey)
				  	{
				  		IrKeyCode = IrOldKey;
				  	}	
				  	else if(IrKeyState==D_IrWaitKey)
				  	{	
				  		IrHoldTime++;
				    		if(IrHoldTime>19)		//2s
				    		{
				    			IrKeyState = D_IrHoldKey;
				    			IrKeyCode = IrOldKey;
						}	
				    	}	
      				}
      				else
      				{
      	  				IrState |= 0x04;	//start
      	  				IrByteCnt = 0;	
      				}	
      				IrBitCnt = 0;
      	
      				if(tmpBit)
      				{
      	 	 			IrData = IrData>>1;
      	  				if(tmpBit==2)
      	    					IrData |= 0x80000000;	
      	    
      	  				IrByteCnt++;
      	  				if(IrByteCnt>31)
      	  				{
//      	    					tmpData[3] = (uchar)((IrData>>24)&0xff);	
//      	   	 				tmpData[2] = (uchar)((IrData>>16)&0xff);	
//      	    					tmpData[1] = (uchar)((IrData>>8)&0xff);	
//      	    					tmpData[0] = (uchar)(IrData&0xff);	
//      	    
//      	    					if(((tmpData[0]==IR_ID_H)&&(tmpData[1]==IR_ID_L))&&
//      	     						((tmpData[3]^0xff)==tmpData[2]))
//      	    					{
//      	      						//Receive Ok
//							IrOldKey = tmpData[2];	
//  							IrKeyState = D_IrWaitKey;
//  							IrHoldTime = 0;
//  							IrReleaseTime = 0;
//      	    					}
						IrDataBuf = IrData;
						IrState |= 0x08;	//have key
						
      	  				}		
      				}	
      			}		
    		}				
  	}		
}
/*
*****************************************************************************************************************
*/
void TurnIrOn(void) 		//dc on
{
	SysFlag |= D_IrEn;
	IrState = 0;
	IrKeyState = 0;
	IrKeyCode = 0xff;
}

void TurnIrOff(void)		//dc off
{
	SysFlag &= ~D_IrEn;
	IrState = 0;
	IrKeyState = 0;
	IrKeyCode = 0xff;
}

/*
*****************************************************************************************************************
*/
//32hz
void CheckReleaseIrHold(void)
{
  	if(SysFlag&D_IrEn)
  	{
    		IrReleaseTime++;	
    		if(IrReleaseTime>4)	//
    		{
    			if(IrKeyState==D_IrWaitKey)
    			{
    				IrKeyCode = IrOldKey;
    			}	
      			IrKeyState = 0;
    		}		
  	}			
}
/*
*****************************************************************************************************************
*/
//ir scan high
//static void CheckIrHoldKey(void)
//{
//	IrReleaseTime = 0;
//  	if(IrKeyState==D_IrMultKey)
//  	{
//  		IrKeyCode = IrOldKey;
//  	}	
//  	else if(IrKeyState==D_IrWaitKey)
//  	{	
//  		IrHoldTime++;
//    		if(IrHoldTime>19)		//2s
//    		{
//    			IrKeyState = D_IrHoldKey;
//    			IrKeyCode = IrOldKey;
//		}	
//    	}
//}	
/*
*****************************************************************************************************************
*/
static void CheckIrMuteKey(uchar ir_key)
{
	if(IrKeyState&D_IrHoldKey)
	{
		//check if mult key
		if((ir_key==KEY_IR_UP)||(ir_key==KEY_IR_DOWN))
			IrKeyState = D_IrMultKey;
	} 
	else if(IrKeyState&D_IrMultKey)
	{
		ProFlag |= D_NoFlash;
	}	
}
/*
*****************************************************************************************************************
*/
//static void SetHoldKey(uchar holdkey)
//{
//  	IrOldKey = holdkey;	
//  	SysFlag |= D_IrHoldKey;
//  	IrHoldTime = 0;
//  	IrReleaseTime = 0;
//}	


//=============================================================================
//功能：IR处理
//输入参数：源数据地址、字符数
//输出参数：无
//=============================================================================
void ReceiveDecode(void)
{
	uchar ir_key;
	uchar tmpData[4];
	
	if(IrState&0x08)
	{
		IrState &= ~0x08;
		tmpData[3] = (uchar)((IrDataBuf>>24)&0xff);	
      	   	tmpData[2] = (uchar)((IrDataBuf>>16)&0xff);	
      	    	tmpData[1] = (uchar)((IrDataBuf>>8)&0xff);	
      	    	tmpData[0] = (uchar)(IrDataBuf&0xff);	
      	    
      	    	if(((tmpData[0]==IR_ID_H)&&(tmpData[1]==IR_ID_L))&&((tmpData[3]^0xff)==tmpData[2]))
      	    	{
      	      		//Receive Ok
			IrOldKey = tmpData[2];	
  			IrKeyState = D_IrWaitKey;
  			IrHoldTime = 0;
  			IrReleaseTime = 0;
      	    	}
	}	
	
	
	if(IrKeyCode!=0xff)
	{
		ir_key = IrKeyCode;
		IrKeyCode = 0xff;
		
	   	if(ProFlag2>D_PlayKeyTone)
    		{
    			CheckStopAlarm();
    			return;
    		}
    	
		if(ir_key==KEY_IR_POWER)
		{
			if((IrKeyState&D_IrHoldKey)==0)
			{
				PlayKeyTone();	
				if(Mode)
					TurnPowerOff();
				else
					TurnPowerOn();	
			}	
			return;
		}
		else if(ir_key==KEY_IR_LIGHT)
		{
			if((IrKeyState&D_IrMultKey)==0)
				PlayKeyTone();	
			if((Mode!=M_SetLight)&&(Mode!=M_SetLight1))
			{
//				ResetAdjActive();
				TurnLightOnOff();
			}
			return;
		}	
		else if(ir_key==KEY_IR_LI_COLOR)
		{
			if((IrKeyState&D_IrMultKey)==0)
				PlayKeyTone();	
			if(ProFlag1&D_LightOn)
			{
//				ResetAdjActive();
				IncLightMode();
			}	
			return;
		}	
		
		if(Mode==M_PowerOff)	
			return;
		
		if((IrKeyState&D_IrMultKey)==0)
			PlayKeyTone();	
		CheckIrMuteKey(ir_key);		
		
		if(IrKeyState&D_IrHoldKey)		//hold key
		{
			switch(ir_key)
			{
				case KEY_IR_COUNT:
					ClearTimer();
					ChangeToNormal();
					break;
				case KEY_IR_OK:
					if((TimerState&D_TimerOn)==0)
					{
						SetBackTime(10);
						ClearTimer();
					}
					break;	
				default:
					break;	
			}	
			return;
		}	
		
		switch(ir_key)				//nor key
		{
			case KEY_IR_AL1SET:
				if((Mode==M_Normal)||(Mode==M_Alarm))
				{
					AlarmCnt = 0;
					ChangeToSetAlarm();
				}	
				else if((Mode==M_SetAlarm)&&(AlarmCnt==0))
				{
					SetBackTime(10);
					SubMode++;
					if(SubMode>3)
						ChangeToNormal();
				}	
				break;
			case KEY_IR_AL2SET:
				if((Mode==M_Normal)||(Mode==M_Alarm))
				{
					AlarmCnt = 1;
					ChangeToSetAlarm();
				}	
				else if((Mode==M_SetAlarm)&&(AlarmCnt==1))
				{
					SetBackTime(10);
					SubMode++;
					if(SubMode>3)
						ChangeToNormal();
				}
				break;	
			case KEY_IR_AL1ON:
				if(Mode==M_Normal)
				{
					ProFlag |= D_AdjustFlag;
					ProFlag1 ^= D_Alarm1On;
				}	
				break;
			case KEY_IR_AL2ON:
				if(Mode==M_Normal)
				{
					ProFlag |= D_AdjustFlag;
					ProFlag1 ^= D_Alarm2On;
				}	
				break;	
			case KEY_IR_SET:
				switch(Mode)
				{
					case M_Normal:
						ChangeToSetTime();
						break;
					case M_SetTime:
						SetBackTime(10);
						SubMode++;
						if(SubMode>6)
							ChangeToNormal();	
						break;	
					default:
						break;		
				}	
				break;	
			case KEY_IR_DOWN:
				switch(Mode)
				{
					case M_SetTime:
						DecSetTimeNum();
						break;
					case M_SetAlarm:
						DecSetAlarmNum();
						break;
					case M_Timer:
						if((TimerState&D_TimerOn)==0)
						{
							SetBackTime(10);
							if(IrKeyState&D_IrMultKey)
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
						break;		
				}
				break;	
			case KEY_IR_UP:
				switch(Mode)
				{
					case M_SetTime:
						IncSetTimeNum();
						break;
					case M_SetAlarm:
						IncSetAlarmNum();
						break;
					case M_Timer:
						if((TimerState&D_TimerOn)==0)
						{
							SetBackTime(10);
							if(IrKeyState&D_IrMultKey)
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
					default:
						break;		
				}
				break;	
			case KEY_IR_OK:
				switch(Mode)
				{
					case M_SetTime:
					case M_SetAlarm:	
						ChangeToNormal();
						break;
					case M_Timer:
						ProFlag |= D_AdjustFlag;
						TurnTimerOnOff();
						break;	
					default:
						break;		
				}
				break;	
			case KEY_IR_COUNT:
				if(Mode==M_Normal)
				{
					Mode = M_Timer;
					ProFlag |= D_AdjustFlag;
					ClearTimer();
				}
				break;	
			case KEY_IR_TEMP:
				if(Mode<M_SetDisp)
				{
					ProFlag1 ^=D_TempF;
					ProFlag |= D_AdjustFlag;
				}	
				break;	
			case KEY_IR_DST:
				if(Mode==M_Normal)
				{
					ProFlag1 ^=D_Dst;
					ProFlag |= D_AdjustFlag;
					if(ProFlag1&D_Dst)
						AdcOneHour();
					else
						SbcOneHour();	
				}
				break;	
			case KEY_IR_12_24:
				if(Mode==M_Normal)
				{
					ProFlag ^=D_24Hour;
					ProFlag |= D_AdjustFlag;
				}
				break;		
			case KEY_IR_DIMMER:
				if(((Mode==M_Normal)||(Mode==M_Alarm)||(Mode==M_SetDisp))&&((ProFlag1&D_AutoDimmer)==0))
				{
//					ResetAdjActive();
					SetBackTime(4);
					Mode = M_SetDisp;
					IncDispLv();
				}
				break;	
			case KEY_IR_AUTO:
				if((Mode==M_Normal)||(Mode==M_Alarm)||(Mode==M_SetDisp1))
				{
//					ResetAdjActive();
					SetBackTime(4);
					Mode = M_SetDisp1;
					TurnAutoDimmerOnOff();
				}
				break;	
			case KEY_IR_LI_LV:
				if(((Mode==M_Normal)||(Mode==M_Alarm)||(Mode==M_SetLight1))&&(ProFlag1&D_LightOn))
				{
//					ResetAdjActive();
					SetBackTime(4);
					Mode = M_SetLight1;
					IncLightLv();
				}	
				break;		
			case KEY_IR_VOL_D:
				if((Mode==M_Normal)||(Mode==M_Alarm)||(Mode==M_SetSound))
				{
					SetBackTime(4);
					ProFlag1 &= ~D_ToneDis;
					Mode = M_SetSound;
					if(SoundLv)
						SoundLv--;
				}	
				break;		
			case KEY_IR_VOL_U:
				if((Mode==M_Normal)||(Mode==M_Alarm)||(Mode==M_SetSound))
				{
					SetBackTime(4);
					ProFlag1 &= ~D_ToneDis;
					Mode = M_SetSound;
					if(SoundLv<4)
						SoundLv++;
				}
				break;		
			case KEY_IR_MUTE:
				if(Mode==M_SetSound)
				{
					SetBackTime(4);
				}
				ProFlag1 ^= D_ToneDis;
				break;													
			default:
				break;	
		}	
	}	
}  
//--------------------------------------------------------------------
