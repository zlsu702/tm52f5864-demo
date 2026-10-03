//=============================================================================
//Name		:IAP.c
//Purpose	:EEPROM功能
//Version	:V1.0
//Author	:
//Date		:2016.07.29
//=============================================================================
#include "AllHeadFile.h"
//=============================================================================
unsigned char xdata eeprom_address[256]  _at_   0XEE00;             //eeprom指定地址
								
/* eeprom写数据*/
/*
 连续写字节不能太多
 写单个字节的时间根据写的内容的前后不同，时间不等。	以及电源电压相关
 理论上随着写的次数增加，写的时间会相应增加，建议以单个字节1ms-2ms的时间为基准
*/
/******************************************************************************************
** 函数名称: iap_eeprom_write
** 函数描述: iap_EEPROM写数据配置函数  
** 输入参数: addr:存储地址，范围0~127
             buf:数据的首地址
			len：数据长度（addr+len不要超过128）
** 输出参数: 无 
*******************************************************************************************/
void iap_eeprom_write(unsigned char addr, unsigned char *buf, unsigned char len)       
{
	unsigned char i=0,temp_ea=0,temp_lvrpd=0;
	
	temp_ea = EA;
	EA = 0;

 	IAPWE_SFR=0XE2;    //使能iap
	temp_lvrpd = LVRPD;  
  	LVRPD = 1;   //关闭LVR

	for(i = 0;i<len;i++)
	{
		IAPTE_22_MS;        //设置IAP看门狗复位时间
		eeprom_address[(addr+i)*2] = *buf;
		buf++;
	}
	LVRPD = temp_lvrpd;  //还原LVR
  	IAPWE_SFR = 0x00;    //关闭IAP
	IAPTE_DISABLE;

	EA = temp_ea;
}
/******************************************************************************************
** 函数名称: iap_eeprom_read
** 函数描述: iap_EEPROM读数据配置函数  
** 输入参数: addr:存储地址，范围0~127
             buf:数据的首地址
			len：数据长度（addr+len不要超过128）
** 输出参数: 无 
*******************************************************************************************/
void iap_eeprom_read(unsigned char addr, unsigned char *buf, unsigned char len)    //eeprom读
{
	unsigned char i=0,temp_ea=0;
	
	temp_ea = EA;
	EA = 0;
	
	for(i = 0;i<len;i++)
	{
		*buf = eeprom_address[(addr+i)*2];
		buf++;
	}	
	
	EA = temp_ea;
}

//=============================================================================
void ReadSaveData(void)
{
  	uchar readBuff[11];
  
  	iap_eeprom_read(0,readBuff,10);
  	
  	if((readBuff[0]==0x24)&&(readBuff[1]==0x45))
  	{
  		SecondBak = readBuff[2];
  		MinuteBak = readBuff[3];
  		TSec[0] = readBuff[4];
  		TMin[0] = readBuff[5];
  		TSec[1] = readBuff[6];
  		TMin[1] = readBuff[7];
  		TSec[2] = readBuff[8];
  		TMin[2] = readBuff[9];
  		Level = readBuff[10];
  	}	
  	else 
  	{
  		UserDefault();
  	}		  		
}

void WriteSaveData(void)
{
  	uchar writeBuff[11];
  
  	writeBuff[0] = 0x24;
  	writeBuff[1] = 0x45;
  	writeBuff[2] = SecondBak;
  	writeBuff[3] = MinuteBak;
  	writeBuff[4] = TSec[0];
  	writeBuff[5] = TMin[0];
  	writeBuff[6] = TSec[1];
  	writeBuff[7] = TMin[1];
  	writeBuff[8] = TSec[2];
  	writeBuff[9] = TMin[2];
  	writeBuff[10] = Level;
  	
  	iap_eeprom_write(0,writeBuff,10);
}


