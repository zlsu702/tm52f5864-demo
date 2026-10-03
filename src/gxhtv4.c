/**************************************************************************************************
  Filename:       gxhtv4.c
  Revised:        $Date: 2010-08-06 08:56:11 -0700 (Fri, 06 Aug 2010) $
  Revision:       $Revision: 23333 $
**************************************************************************************************/
#include "AllHeadFile.h"
/*********************************************************************
/*********************************************************************
 * TYPEDEFS
 */
#define IO_SDA		P1_6 
#define SetSDIO_HIGH	do{P1MOD76=(P1MOD76&~0x0f)|1<<0;P1_6=1;}while(0) 
#define SetSDIO_LOW	do{P1_6=0;P1MOD76=(P1MOD76&~0x0f)|2<<0;}while(0) 
#define SetSCLK_HIGH	P3_6=1
#define SetSCLK_LOW	P3_6=0	

/*********************************************************************
 */
 
xdata uchar TempFlag;
xdata uchar TempCyc;
xdata uchar TempNum[2];
xdata uchar HumiNum;
//xdata uchar AdjActiveTime;
//xdata uchar AdjReleaseTime;
//xdata uchar TempSave;
//xdata uchar HumiSave;
//xdata uchar AdjTemp;
//xdata uchar AdjHumi;

static uchar CRC_8(uchar numh,uchar numl); 
//static void TempNumAdjust(void);
//static void HumiNumAdjust(void);
//static void CheckReleaseAdjust(void);

/*********************************************************************
 * LOCAL FUNCTIONS
 */
void Gxhtv4PowerOn(void)
{
//	AdjActiveTime = 0;
	TempCyc = 0;
	ReadyRFC();
}

void Gxhtv4PowerOff(void)
{
//	AdjReleaseTime = 0;
	TempFlag &= D_SensorDis;
}

static void I2CDelay(void)
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
 
static void I2CStart(void)
{
	SetSDIO_HIGH;
	I2CDelay();
	SetSCLK_HIGH;
	I2CDelay();
	SetSDIO_LOW;
	I2CDelay();
	SetSCLK_LOW;
	I2CDelay();
}

static void I2CStop(void)
{
	SetSDIO_LOW;
	I2CDelay();
	SetSCLK_HIGH;
	I2CDelay();
	SetSDIO_HIGH;
	I2CDelay();
}

static void I2CAck(void)
{
	SetSCLK_LOW;
	I2CDelay();
	SetSDIO_LOW;
	I2CDelay();
	SetSCLK_HIGH;
	I2CDelay();
	SetSCLK_LOW;
	I2CDelay();
}

static void I2CNAck(void)
{
	SetSCLK_LOW;
	I2CDelay();
	SetSDIO_HIGH;
	I2CDelay();
	SetSCLK_HIGH;
	I2CDelay();
	SetSCLK_LOW;
	I2CDelay();
}

/*********************************************************************/

static uchar I2CWriteByte(uchar wdata)
{
	uchar i;
	uchar err = 1;
	for(i=0;i<8;i++)
	{
		SetSCLK_LOW;
		I2CDelay();
		if(wdata&0x80)
			SetSDIO_HIGH;
		else
			SetSDIO_LOW;	
		I2CDelay();	 
		SetSCLK_HIGH;
		I2CDelay();
		wdata <<=1;
	}
	//I2CWaitAck
	SetSCLK_LOW;	
	I2CDelay();
	SetSDIO_HIGH;
	I2CDelay();
	I2CDelay();
	SetSCLK_HIGH;
	for(i=0;i<4;i++)
	{
		if(IO_SDA==0)
		{
			err = 0;
			break;
		}	
		DelayNOP(50);	
	}
	SetSCLK_LOW;	
	return(err);
}

static uchar I2CReadByte(void)
{
	uchar i;
	uchar rdata;
	
	SetSDIO_HIGH;
	for(i=0;i<8;i++)
	{
		I2CDelay();
		SetSCLK_LOW;
		I2CDelay();
		rdata <<=1;
		SetSCLK_HIGH;
		I2CDelay();
		if(IO_SDA)		
			rdata |= 0x01;	
	}
	return(rdata);
}


/*********************************************************************
 * @fn      Gxhtv4CheckOn
 *
 * @brief   
 *
 *
 * @param   none
 *
 * @return  none
 */
void Gxhtv4CheckOn( void ) 
{
	uchar err = 0;
//	uchar read_id[2];
	
//	AdjTemp = 0xff;
//	AdjHumi = 0xff;
		
	SetSDIO_HIGH;
	SetSCLK_HIGH;
	DelayNOP(500);
	
	I2CStart();			//reset
	err |= I2CWriteByte(0x88);
	err |= I2CWriteByte(0x94);
	I2CStop();
	DelayNOP(500);
	
////	I2CStart();			//read id
////	err |= I2CWriteByte(0x88);
////	err |= I2CWriteByte(0x89);
////	err |= I2CWriteByte(0x81);
////	I2CStop();
////	
////	I2CStart();
////	err |= I2CWriteByte(0x89);
////	read_id[1] = I2CReadByte();
////	I2CAck();
////	read_id[0] = I2CReadByte();
////	I2CNAck();
////	I2CStop();
	
//	if((err)||((read_id[1]!=0x59)||(read_id[0]!=0x59)))
	if(err)
		TempFlag = D_SensorDis;
}	

//=====================================================================
//sec service
void CheckReadyRFC( void ) 
{
	if((SysFlag&D_IrEn)==0)
	{
//		CheckReleaseAdjust();
		return;	
	}	
	
	TempCyc++;
	if(TempCyc>9)
	{
		TempCyc = 0;
//		if(AdjActiveTime<255)
//			AdjActiveTime++;
		ReadyRFC();
	}	
}

//=====================================================================
void ReadyRFC( void ) 
{
	if(TempFlag&D_SensorDis)
		return;
	
	TempFlag = D_ReadyFlag; 	
}

//=====================================================================
//Server in 32hz
void Gxhtv4Server( void ) 
{
	uchar err = 0;
	uchar temp_data[6];
	if(TempFlag&D_TempWait)
	{
		TempFlag = 0;
		I2CStart();
		err |= I2CWriteByte(0x89);
		temp_data[5] = I2CReadByte();
		I2CAck();
		temp_data[4] = I2CReadByte();
		I2CAck();
		temp_data[3] = I2CReadByte();
		I2CAck();
		temp_data[2] = I2CReadByte();
		I2CAck();
		temp_data[1] = I2CReadByte();
		I2CAck();
		temp_data[0] = I2CReadByte();
		I2CNAck();
		I2CStop();	
		
		if(err)	
			return;
		//Cht8320GetTempNum	
		//tempC = -45+175*temp/255(-10~70)	
		//tempF = -49+315*temp/255	
		err = CRC_8(temp_data[5],temp_data[4]);
		if(err==temp_data[3])	
		{
//			TempNum[0] = (uchar)(175*(uint)temp_data[5]/255);
			TempNum[0] = (uchar)(175*(uint)temp_data[5]/255)-2;
//			TempNumAdjust();	
			if(TempNum[0]<36)	//<=-10
			{
				TempNum[1] = TEMP_LOW;
			}	
			else if(TempNum[0]<45)	//<0
			{
				TempNum[1] = 0x80;
				TempNum[0] = 45-TempNum[0];
			}	
			else if(TempNum[0]<116)	//<70
			{
				TempNum[1] = 0;
				TempNum[0] = TempNum[0]-45;
			}
			else			//>70
			{
				TempNum[1] = TEMP_HIGH;
			}	
		}	
		//Cht8320GetHumiNum
		//Humidity = = -6+125*temp/255(1~99)
		err = CRC_8(temp_data[2],temp_data[1]);	
		if(err==temp_data[0])	
		{
//			HumiNum =  (uchar)(125*(uint)temp_data[2]/255);
			HumiNum =  (uchar)(125*(uint)temp_data[2]/255)+2;
			if(HumiNum>5)
				HumiNum = HumiNum-6;
			else	
				HumiNum = 0;
//			HumiNumAdjust();
			if(HumiNum>99)
				HumiNum = 99;
		}
	}	
	else if(TempFlag&D_ReadyFlag)
	{
		TempFlag |= D_TempWait;
		I2CStart();			//read th
		I2CWriteByte(0x88);
		I2CWriteByte(0xfd);
		I2CStop();
	}	
}

//=====================================================================
static uchar CRC_8(uchar numh,uchar numl) 
{
	uchar i;
    	uchar crc8 = 0xff;
    	crc8 ^= numh;
    	for (i = 8; i > 0; --i)
    	{
        	if ((crc8 & 0x80) != 0)
        	{
            		crc8 *= 2;
            		crc8 ^= 0x31;
        	}
        	else
        	{
            		crc8 *= 2;
        	}
    	}

    	crc8 ^= numl;
    	for (i = 8; i > 0; --i)
    	{
        	if ((crc8 & 0x80) != 0)
        	{
            	crc8 *= 2;
            	crc8 ^= 0x31;
        	}
        	else
        	{
            	crc8 *= 2;
        	}
    	}
    	return crc8;
}

//=====================================================================
//key
//void ResetAdjActive(void)
//{
//	AdjActiveTime = 0;	
//}

//=====================================================================
////sec
//static void CheckReleaseAdjust(void)
//{
//	if(Second)
//		return;	
//		
//	AdjReleaseTime++;
//	if(AdjReleaseTime>10)		//10min
//	{
//		AdjTemp = 0xff;
//		AdjHumi = 0xff;
//	}	
//}

//=====================================================================
//static void TempNumAdjust(void)
//{
//	if(AdjTemp==0xff)		//firstEnter
//	{
//		TempSave = TempNum[0];
//		AdjTemp = 0;
//	}	
////	else if(AdjActiveTime<60)	//60*10s=10min		
//	else if(AdjActiveTime<180)	//180*10s=30min		
//	{
//		if(TempNum[0]>TempSave)
//		{
//			AdjTemp = TempNum[0]-TempSave;
//			TempNum[0] = TempSave;
//		}	
//		else
//		{
//			TempSave = TempNum[0];
//			AdjTemp = 0;
//		}	
//	}	
//	else
//	{
//		if(TempNum[0]>=AdjTemp)
//			TempNum[0] = TempNum[0]-AdjTemp;
//		else
//			TempNum[0] = 0;
//		
////		if((TempNum[0]<TempSave)&&AdjTemp)	
////		{
////			AdjTemp--;
////			TempNum[0] = TempSave;
////		}	
//	}	
//}
//
////=====================================================================
//static void HumiNumAdjust(void)
//{
//	if(AdjHumi==0xff)		//firstEnter
//	{
//		HumiSave = HumiNum;
//		AdjHumi = 0;
//	}	
////	else if(AdjActiveTime<120)	//120*10s=20min		
//	else if(AdjActiveTime<180)	//180*10s=30min		
//	{
//		if(HumiNum<HumiSave)
//		{
//			AdjHumi = HumiSave-HumiNum;
//			HumiNum = HumiSave;
//		}	
//		else
//		{
//			HumiSave = HumiNum;
//			AdjHumi = 0;
//		}	
//	}	
//	else
//	{
//		HumiNum = HumiNum+AdjHumi;
//		
////		if((HumiNum>HumiSave)&&AdjHumi)	
////		{
////			AdjHumi--;
////			HumiNum = HumiSave;
////		}	
//	}	
//}

/*********************************************************************
*********************************************************************/
