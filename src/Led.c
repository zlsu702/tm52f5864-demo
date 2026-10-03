//=============================================================================
//Name		:LED.c
//Purpose	:LED显示函数
//Version	:V1.0
//Author	:
//Date		:2022.05.24
//=============================================================================
#include "AllHeadFile.h"
//=============================================================================
//LEDRAM处于外部寄存器
#define c0 	0
#define c1 	1
#define c2 	2
#define c3 	3
#define c4 	4
#define c5 	5
#define c6 	6
#define c7 	7
#define c8 	8

#define s0  	0
#define s1  	1
#define s2  	2
#define s3  	3
#define s4  	4
#define s5  	5
#define s6  	6
#define s7  	7
#define s8  	8
#define s9  	9
#define s10  	10
#define s11  	11
#define s12  	12
#define s13  	13
#define s14  	14
#define s15  	15

#define IO_PLED	P3_3
#define SEG6	P3_7	//di1
#define SEG7	P3_5	//di2

#define IO_LED_OE	P0_6
#define IO_LED_LE1	P0_0
#define IO_LED_CLK1	P0_1
#define IO_LED_SDI1	P0_3
#define IO_LED_LE2	P3_4
#define IO_LED_CLK2	P0_7
#define IO_LED_SDI2	P0_4

uchar Led_Data[3];
xdata uchar Led_Ram[24][3];	

xdata uchar DispLevel1;

xdata uint Led_Buff[9];
xdata ulong Led_Buff1[2];

xdata uint Led_GRB6[18];
xdata uint Led_GRB7[18];

xdata uchar PlayRgb6[18];
xdata uchar PlayRgb7[18];

static void TurnLedRam(ulong *led_buff,uint *led_rgb);

/*
*****************************************************************************************************************
*/
unsigned char code Led_Num1[] =
{
	c3,s1,		//a1/LD50
	c3,s0,		//a2/LD49
	c1,s12,		//b1/LD29
	c2,s2,		//b2/LD35	
	c2,s6,		//c1/LD39
	c2,s7,		//c2/LD40
	c2,s14,		//d1/LD47
	c2,s15,		//d2/LD48
	c2,s12,		//e1/LD45
	c2,s11,		//e2/LD44
	c2,s10,		//f1/LD43
	c2,s9,		//f2/LD42
	c2,s5,		//g1/LD38
	c2,s4		//g2/LD37
};
unsigned char code Led_Num2[] =
{
	c1,s14,		//a1/LD31
	c1,s15,		//a2/LD32
	c1,s6,		//b1/LD23
	c1,s4,		//b2/LD21
	c0,s3,		//c1/LD4
	c1,s0,		//c2/LD17
	c1,s1,		//d1/LD18
	c1,s2,		//d2/LD19
	c1,s8,		//e1/LD25
	c1,s9,		//e2/LD26
	c1,s10,		//f1/LD27
	c1,s11,		//f2/LD28
	c1,s13,		//g1/LD30
	c1,s3		//g2/LD20	
};
unsigned char code Led_Num3[] =
{
	c8,s4,		//a1/LD133
	c8,s5,		//a2/LD134
	c0,s9,		//b1/LD10
	c0,s10,		//b2/LD11
	c8,s8,		//c1/LD137
	c8,s9,		//c2/LD138
	c8,s10,		//d1/LD139
	c8,s11,		//d2/LD140
	c0,s0,		//e1/LD1
	c0,s1,		//e2/LD2
	c0,s11,		//f1/LD12
	c0,s12,		//f2/LD13
	c0,s15,		//g1/LD16
	c0,s14		//g2/LD15
};
unsigned char code Led_Num4[] =
{
	c8,s13,		//a1/LD142
	c8,s14,		//a2/LD143
	c8,s6,		//b1/LD135
	c8,s15,		//b2/LD144
	c8,s7,		//c1/LD136
	c7,s12,		//c2/LD125
	c7,s0,		//d1/LD113
	c7,s1,		//d2/LD114
	c8,s0,		//e1/LD129
	c8,s12,		//e2/LD141
	c0,s13,		//f1/LD14
	c0,s8,		//f2/LD9
	c0,s7,		//g1/LD8
	c0,s6		//g2/LD7
};

unsigned char code Led_NumT1[] =
{
	c7,s10,		//b/LD123
	c7,s8		//c/LD121
};
unsigned char code Led_NumT2[] =
{
	c7,s13,		//a/LD126
	c7,s5,		//b/LD118
	c7,s4,		//c/LD117
	c7,s7,		//d/LD120
	c7,s14,		//e/LD127
	c7,s9,		//f/LD122
	c7,s6		//g/LD119
};
unsigned char code Led_NumT3[] =
{
	c6,s15,		//a/LD112
	c6,s4,		//b/LD101
	c6,s5,		//c/LD102
	c6,s13,		//d/LD110
	c6,s10,		//e/LD107
	c6,s11,		//f/LD108
	c6,s14		//g/LD111
};
unsigned char code Led_NumH1[] =
{
	c4,s9,		//a/LD74
	c5,s6,		//b/LD87
	c5,s5,		//c/LD86
	c5,s7,		//d/LD88
	c5,s10,		//e/LD91
	c5,s12,		//f/LD93
	c5,s11		//g/LD92
};
unsigned char code Led_NumH2[] =
{
	c4,s6,		//a/LD71
	c4,s4,		//b/LD69
	c4,s5,		//c/LD70
	c4,s12,		//d/LD77
	c4,s11,		//e/LD76
	c4,s10,		//f/LD75
	c4,s13		//g/LD78
};

unsigned char code Led_NumD1[] =
{
	c7,s11,		//b/LD124
	c7,s3		//c/LD116
};
unsigned char code Led_NumD2[] =
{
	c7,s2,		//a/LD115
	c6,s12,		//b/LD109
	c6,s1,		//c/LD98
	c6,s2,		//d/LD99
	c6,s9,		//e/LD106
	c7,s15,		//f/LD128
	c6,s8		//g/LD105
};
unsigned char code Led_NumD3[] =
{
	c5,s14,		//a/LD95
	c5,s3,		//b/LD84
	c5,s2,		//c/LD83
	c4,s8,		//d/LD73
	c5,s15,		//e/LD96
	c6,s6,		//f/LD103
	c5,s8		//g/LD89
};
unsigned char code Led_NumD4[] =
{
	c5,s0,		//a/LD81
	c4,s7,		//b/LD72
	c4,s2,		//c/LD67
	c4,s1,		//d/LD66
	c4,s14,		//e/LD79
	c5,s1,		//f/LD82
	c4,s15		//g/LD80
};

unsigned char code Led_WeekR[] =
{
	c3,s3,		//a/LD52
	c3,s5,		//b/LD54
	c3,s7,		//c/LD56
	c3,s8,		//d/LD57
	c3,s11,		//e/LD60
	c3,s13,		//f/LD62
	c3,s15		//g/LD64	
};

unsigned char code Led_WeekW[] =
{
	c3,s2,		//a/LD51
	c3,s4,		//b/LD53
	c3,s6,		//c/LD55
	c3,s9,		//d/LD58
	c3,s10,		//e/LD59
	c3,s12,		//f/LD61
	c3,s14		//g/LD63	
};

unsigned char code Led_Col[] =
{
	c1,s5,		//col1/LD22
	c0,s2		//col2/LD3
};

unsigned char code Led_AmPm[] =
{
	c2,s3,		//am/LD36
	c2,s8		//pm/LD41	
};

unsigned char code Led_Alarm[] =
{
	c8,s3,		//al1/LD132
	c8,s2		//al2/LD131
};

unsigned char code Led_Dst[] =
{
	c8,s1		//dst/LD130
};

unsigned char code Led_TH[] =
{
	c6,s3,		//C/LD100
	c5,s13,		//F/LD94
	c4,s3		//%/LD68
};

unsigned char code Led_Date[] =
{
	c6,s7,		//-/LD104
	c6,s0,		//m/LD97
	c4,s0		//d/LD65
};

/*
*****************************************************************************************************************
*/
//ggffeeddccbbaa
unsigned int code FontTab1[] = 
{	
	0x0fff,		//0
	0x003c,		//1
	0x33cf,		//2
	0x30ff,		//3
	0x3c3c,		//4
	0x3cf3,		//5
	0x3ff3,		//6
	0x003f,		//7
	0x3fff,		//8
	0x3cff, 	//9
	0x0000, 	//
	0x3000,		//- B	
	0x3f3c,		//H C	
	0x3f3f,		//A D	
	0x0fc0,		//L E	
	0x3f03, 	//F F	
	0x0f3f, 	//N 10
	0x33fc,		//d 11
	0x0ffc,		//U 12
	0x0fc3 		//C 13
};

unsigned char code FontTab[] = 
{	
	0x3F,		//0
	0x06,		//1
	0x5B,		//2
	0x4F,		//3
	0x66,		//4
	0x6D,		//5
	0x7D,		//6
	0x07,		//7
	0x7F,		//8
	0x6F, 		//9
	0x00, 		//
	0x40, 		//- B	
	0x76, 		//H C
	0x38 		//L D	
};

unsigned long code Map_Bit[] = 
{	
	0x0001,		//0
	0x0002,		//1
	0x0004,		//2
	0x0008,		//3
	0x0010,		//4
	0x0020,		//5
	0x0040,		//6
	0x0080,		//7
	0x0100,		//8
	0x0200,		//9
	0x0400,		//10
	0x0800,		//11
	0x1000,		//12
	0x2000,		//13
	0x4000,		//14
	0x8000,		//15
	0x10000,		//16
	0x20000,		//17
	0x40000,		//18
	0x80000,		//19
	0x100000,		//20
	0x200000,		//21
	0x400000,		//22
	0x800000		//23
};

//unsigned int code Led_Bit[] = 
//{	
//	0x0001,		//0
//	0x0002,		//1
//	0x0004,		//2
//	0x0008,		//3
//	0x0010,		//4
//	0x0020,		//5
//	0x0040,		//6
//	0x0080,		//7
//	0x0100,		//8
//	0x0200,		//9
//	0x0400,		//10
//	0x0800,		//11
//	0x1000,		//12
//	0x2000,		//13
//	0x4000,		//14
//	0x8000		//15
//};


/*
*****************************************************************************************************************
*/
unsigned int code Rgb_Tab[] =
{
	//H/S/V
	0,		//0 红
	12,		//1 橙
	60,		//2 黄
	120,		//3 绿
	180,		//4 青
	240,		//5 蓝
	300,		//6 粉
	345,		//7 祡
	360		//8 白
};

unsigned int code Rgb_Tab1[] =
{
	//H/S/V
	0,		//0 红
	40,		//1 橙
	80,		//2 黄
	120,		//3 绿
	160,		//4 青
	200,		//5 蓝
	240,		//6 蓝
	280,		//7 粉
	320,		//8 祡
	360		//9 白
};

//=============================================================================
//功能：main loop
//输入参数：
//输出参数：
//=============================================================================
/*LED刷新函数*/
void Led_Reflush(void)
{
	uchar i,j;
	uint tmpBuff;
	
	if(SysFlag&D_DispUpdata)
  	{
    		SysFlag &= ~D_DispUpdata;
		IO_LED_LE1 = 0;
		for(j=0;j<4;j++)
		{
			tmpBuff = Led_Buff[3-j];
  			for(i=0;i<16;i++)
  			{
  				if(tmpBuff&0x8000)
    		  			IO_LED_SDI1 = 1;
    				else
    		  			IO_LED_SDI1 = 0;
    		  		IO_LED_CLK1 = 1; 	
    				tmpBuff = tmpBuff<<1;
    				IO_LED_CLK1 = 0; 
  			}	
		}  		
  		IO_LED_LE1 = 1;
  		IO_LED_LE1 = 0;
  		
  		IO_LED_LE2 = 0;
		for(j=0;j<5;j++)
		{
			tmpBuff = Led_Buff[8-j];
  			for(i=0;i<16;i++)
  			{
  				if(tmpBuff&0x8000)
    		  			IO_LED_SDI2 = 1;
    				else
    		  			IO_LED_SDI2 = 0;
    		  		IO_LED_CLK2 = 1; 	
    				tmpBuff = tmpBuff<<1;
    				IO_LED_CLK2 = 0; 
  			}	
		}  		
  		IO_LED_LE2 = 1;
  		IO_LED_LE2 = 0;
  		
  		PWM_On();
	}	
}

//=============================================================================
//功能：main loop
//输入参数：
//输出参数：
//=============================================================================
/*LED刷新函数*/
void Led_Reflush1(void)
{
	uchar i,j,k;
	if(SysFlag&D_DispUpdata1)
  	{
    		SysFlag &= ~D_DispUpdata1;
	    	TurnLedRam(&Led_Buff1[0],Led_GRB6);
	    		for(i=0;i<18;i++)	
	    		{
	    			Led_Data[0] = Led_Ram[i][1];	//G
	    			Led_Data[1] = Led_Ram[i][0];	//R
	    			Led_Data[2] = Led_Ram[i][2];	//B
	    			for(j=0;j<3;j++)
	    			{
	    				for(k=0;k<8;k++)
	    				{
	    					EA=0;	
	    					if(Led_Data[j]&0x80)
	    					{
	    						SEG6 = 1;
	    						_nop_();
	    						_nop_();
	    						_nop_();
	    						_nop_();
	    						_nop_();
	    						SEG6 = 0;
	    					}	
	    					else
	    					{
	    						SEG6 = 1;
	    						_nop_();
	    						_nop_();
	    						SEG6 = 0;
	    					}	
	    					EA=1;		
	    					Led_Data[j] = Led_Data[j]<<1;
	    				}
	    			}
	    		}
	    		
	    	
	    	TurnLedRam(&Led_Buff1[1],Led_GRB7);
	    		for(i=0;i<18;i++)	
	    		{
	    			Led_Data[0] = Led_Ram[i][1];	//G
	    			Led_Data[1] = Led_Ram[i][0];	//R
	    			Led_Data[2] = Led_Ram[i][2];	//B
	    			for(j=0;j<3;j++)
	    			{
	    				for(k=0;k<8;k++)
	    				{
	    					EA=0;	
	    					if(Led_Data[j]&0x80)
	    					{
	    						SEG7 = 1;
	    						_nop_();
	    						_nop_();
	    						_nop_();
	    						_nop_();
	    						_nop_();
	    						SEG7 = 0;
	    					}	
	    					else
	    					{
	    						SEG7 = 1;
	    						_nop_();
	    						_nop_();
	    						SEG7 = 0;
	    					}	
	    					EA=1;	
	    					Led_Data[j] = Led_Data[j]<<1;
	    				}
	    			}
	    		}
	}	
}

//=============================================================================
//功能：
//输入参数：
//输出参数：
//=============================================================================
void Led_TurnOn( void )
{
	IO_PLED = 0;
}

void Led_TurnOff( void )
{
	IO_PLED = 1;
	IO_LED_SDI1 = 0;
	IO_LED_SDI2 = 0;
	PWM_Off();
	SysFlag &= ~(D_DispUpdata|D_DispUpdata1);
}

/*
//;;--------------------------------------------------------------------
*/
void DispAllLed(uchar OnOff)
{
	uchar i;
	uint disp_data;
	SysFlag |= D_DispUpdata;
	if(OnOff)
		disp_data = 0xffff;
	else
		disp_data = 0x0000;	
	for(i=0;i<9;i++)
	{
		Led_Buff[i] = disp_data;
	}
}

void DispAllLight(uchar OnOff)
{
	ulong disp_data;
	SysFlag |= D_DispUpdata1;
	if(OnOff)
		disp_data = 0x00ffffff;
	else
		disp_data = 0x00000000;	
		
	Led_Buff1[0] = disp_data;
	Led_Buff1[1] = disp_data;
}


// p = v * (1 - s) = 0
// q = v * (1 - s * fractional)
// t = v * (1 - s * (1 - fractional))
static void TurnLedRam(ulong *led_buff,uint *led_rgb)
{
	uchar i,j,k;
	uchar redata;
	
	for(i=0;i<18;i++)
	{
		if((((*led_buff)&Map_Bit[i])==0)||(DispLevel1==0))
    		{
    			Led_Ram[i][0] = 0;
    			Led_Ram[i][1] = 0;
    			Led_Ram[i][2] = 0;
    		}
    		else
    		{	
    			j = (uchar)(*led_rgb/60);
    			k = (uchar)(*led_rgb%60);
    			redata = DispLevel1;	//v
    			switch(j)
    			{
    				case 0:		// r, g, b = v, t, p
    					Led_Ram[i][0] = redata;	
    					Led_Ram[i][1] = (uchar)((uint)redata*(uint)k/60);
    					Led_Ram[i][2] = 0;
    					if((Led_Ram[i][1]==0)&&(k>0))
    						Led_Ram[i][1] = 1;
    					break;	
    				case 1:		// r, g, b = q, v, p
    					Led_Ram[i][0] = (uchar)((uint)redata*(uint)(60-k)/60);	
    					Led_Ram[i][1] = redata;
    					Led_Ram[i][2] = 0;
    					if((Led_Ram[i][0]==0)&&(k<60))
    						Led_Ram[i][0] = 1;
    					break;		
    				case 2:		// r, g, b = p, v, t
    					Led_Ram[i][0] = 0;	
    					Led_Ram[i][1] = redata;
    					Led_Ram[i][2] = (uchar)((uint)redata*(uint)k/60);
    					if((Led_Ram[i][2]==0)&&(k>0))
    						Led_Ram[i][2] = 1;
    					break;	
    				case 3:		// r, g, b = p, q, v
    					Led_Ram[i][0] = 0;	
    					Led_Ram[i][1] = (uchar)((uint)redata*(uint)(60-k)/60);	
    					Led_Ram[i][2] = redata;
    					if((Led_Ram[i][1]==0)&&(k<60))
    						Led_Ram[i][1] = 1;
    					break;	
    				case 4:		// r, g, b = t, p, v
    					Led_Ram[i][0] = (uchar)((uint)redata*(uint)k/60);	
    					Led_Ram[i][1] = 0;
    					Led_Ram[i][2] = redata;
    					if((Led_Ram[i][0]==0)&&(k>0))
    						Led_Ram[i][0] = 1;
    					break;		
    				case 5:		// r, g, b = v, p, q
    					Led_Ram[i][0] = redata;	
    					Led_Ram[i][1] = 0;
    					Led_Ram[i][2] = (uchar)((uint)redata*(uint)(60-k)/60);	
    					if((Led_Ram[i][2]==0)&&(k<60))
    						Led_Ram[i][2] = 1;
    					break;	
    				case 6:		//255,255,255
    					Led_Ram[i][0] = redata;	
    					Led_Ram[i][1] = redata;	
    					Led_Ram[i][2] = redata;	
    					break;					
    				default:
    					break;	
    			}
    		}	
    		led_rgb++;
	}
}


/*
//;;--------------------------------------------------------------------
*/
void DispSybmol( uchar *LedNum, uchar OnOff)
{
	uchar DispRam;
	uchar DispBit;
	
	SysFlag |= D_DispUpdata;
	
	DispRam=*LedNum++;
	DispBit=*LedNum++;
	
	if(OnOff)
		Led_Buff[DispRam] |= Map_Bit[DispBit]&0xffff;	//disp
	else
		Led_Buff[DispRam] &= (~Map_Bit[DispBit])&0xffff;	//clear
}			

/*
//;;--------------------------------------------------------------------
*/
void DispSybmols( uchar *LedNum, uchar Long, uchar LcdTmpSegs)
{
	uchar DispRam;
	uchar DispBit;
	uchar i;
	
	SysFlag |= D_DispUpdata;
	
	for(i=0;i<Long;i++)
	{
		DispRam=*LedNum++;
		DispBit=*LedNum++;
		if(LcdTmpSegs&0x01)
			Led_Buff[DispRam] |= Map_Bit[DispBit]&0xffff;	//disp
		else	
			Led_Buff[DispRam] &= (~Map_Bit[DispBit])&0xffff;	//clear
	    	LcdTmpSegs >>= 1;
	 }
}
/*
//;;--------------------------------------------------------------------
*/
void DispDigit1(uchar *LedNum, uchar Font)
{
	uchar DispRam;
	uchar DispBit;
	uint LcdTmpSegs;
	uchar i;
	
	SysFlag |= D_DispUpdata;
	
	LcdTmpSegs=FontTab1[Font];
	for(i=0;i<14;i++)
	{
		DispRam=*LedNum++;
		DispBit=*LedNum++;
		if(LcdTmpSegs&0x01)
			Led_Buff[DispRam] |= Map_Bit[DispBit]&0xffff;	//disp
		else	
			Led_Buff[DispRam] &= (~Map_Bit[DispBit])&0xffff;	//clear
	    	LcdTmpSegs >>= 1;
	 }
}
/*
//;;--------------------------------------------------------------------
*/
void DispDigit(uchar *LedNum, uchar Font)
{
	uchar DispRam;
	uchar DispBit;
	uchar LcdTmpSegs;
	uchar i;
	
	SysFlag |= D_DispUpdata;
	
	LcdTmpSegs=FontTab[Font];
	for(i=0;i<7;i++)
	{
		DispRam=*LedNum++;
		DispBit=*LedNum++;
		if(LcdTmpSegs&0x01)
			Led_Buff[DispRam] |= Map_Bit[DispBit]&0xffff;	//disp
		else	
			Led_Buff[DispRam] &= (~Map_Bit[DispBit])&0xffff;	//clear
	    	LcdTmpSegs >>= 1;
	}
}
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
static uchar GetPlayRgbValue(uint s_data,uint o_data)
{
	uchar tmp_ual;
	if(s_data>=o_data)
		tmp_ual = (uchar)(s_data-o_data);	
	else
		tmp_ual = (uchar)(360+s_data-o_data);	
	return(tmp_ual);	
}
//=============================================================================
void SetAllDispRgb1(uchar rgb_num)
{
	uchar i;
	SysFlag |= D_DispUpdata1;
	for(i=0;i<18;i++)
	{
		Led_GRB6[i] = Rgb_Tab[rgb_num];
		Led_GRB7[i] = Rgb_Tab[rgb_num];
	}
}

//void SetAllDispRgb1_1(uchar rgb_num)
//{
//	uchar i;
//	SysFlag |= D_DispUpdata1;
//	for(i=0;i<18;i++)
//	{
//		Led_GRB6[i] = Rgb_Tab1[rgb_num];
//		Led_GRB7[i] = Rgb_Tab1[rgb_num];
//	}
//}

//=============================================================================
void SetAllDispRgb1_S(void)
{
	uchar i;
	uchar play_rgb;
	play_rgb = 40;
	for(i=0;i<18;i++)
	{
		PlayRgb6[i] = play_rgb;
		PlayRgb7[i] = play_rgb;
	}
}

//=============================================================================
void SetAllDispRgb1_ud(void)
{
	uchar i;
	SysFlag |= D_DispUpdata1;
	//2
	for(i=0;i<14;i++)
	{
		Led_GRB6[i] = Rgb_Tab1[2];
	}
	//2
	Led_GRB6[14] = Rgb_Tab1[2];
	Led_GRB7[17] = Rgb_Tab1[2];
	
	//1
	Led_GRB6[15] = Rgb_Tab1[1];
	Led_GRB7[16] = Rgb_Tab1[1];
	
	//1
	Led_GRB6[16] = Rgb_Tab1[1];
	Led_GRB7[15] = Rgb_Tab1[1];
	
	//0
	Led_GRB6[17] = Rgb_Tab1[0];
	Led_GRB7[14] = Rgb_Tab1[0];
	
	//0
	for(i=0;i<14;i++)
	{
		Led_GRB7[i] = Rgb_Tab1[0];
	}
}	

//=============================================================================
void SetAllDispRgb1_ud_S(void)
{
	uchar i;
	uchar play_rgb;
	//0
	play_rgb = GetPlayRgbValue(Led_GRB7[14],Led_GRB7[13]);
	for(i=0;i<14;i++)
	{
		PlayRgb7[i] = play_rgb;
	}
	//0
	play_rgb = GetPlayRgbValue(Led_GRB7[15],Led_GRB7[14]);
	PlayRgb6[17] = play_rgb;
	PlayRgb7[14] = play_rgb;
	//1
	play_rgb = GetPlayRgbValue(Led_GRB7[16],Led_GRB7[15]);
	PlayRgb6[16] = play_rgb;
	PlayRgb7[15] = play_rgb;
	//1
	play_rgb = GetPlayRgbValue(Led_GRB7[17],Led_GRB7[16]);
	PlayRgb6[15] = play_rgb;
	PlayRgb7[16] = play_rgb;
	//2
	play_rgb = GetPlayRgbValue(Led_GRB6[0],Led_GRB7[17]);
	PlayRgb6[14] = play_rgb;
	PlayRgb7[17] = play_rgb;
	//2
	if(PlayLight&0x01)
	{
		for(i=0;i<14;i++)
		{
			PlayRgb6[i] = 0;
		}
	}	
	else
	{
		play_rgb = 40;
		for(i=0;i<14;i++)
		{
			PlayRgb6[i] = play_rgb;
		}
	}	
}	

//=============================================================================
void SetAllDispRgb1_gl(void)
{
	SysFlag |= D_DispUpdata1;
	
	//5
	Led_GRB7[17] = Rgb_Tab1[5];
	Led_GRB7[16] = Rgb_Tab1[5];
	Led_GRB7[15] = Rgb_Tab1[5];
	Led_GRB7[14] = Rgb_Tab1[5];
	
	//4
	Led_GRB6[0] = Rgb_Tab1[4];
	Led_GRB7[13] = Rgb_Tab1[4];
	//4
	Led_GRB6[1] = Rgb_Tab1[4];
	Led_GRB7[12] = Rgb_Tab1[4];
	//4
	Led_GRB6[2] = Rgb_Tab1[4];
	Led_GRB7[11] = Rgb_Tab1[4];
	
	//3
	Led_GRB6[3] = Rgb_Tab1[3];
	Led_GRB7[10] = Rgb_Tab1[3];
	//3
	Led_GRB6[4] = Rgb_Tab1[3];
	Led_GRB7[9] = Rgb_Tab1[3];
	//3
	Led_GRB6[5] = Rgb_Tab1[3];
	Led_GRB7[8] = Rgb_Tab1[3];
	
	//2
	Led_GRB6[6] = Rgb_Tab1[2];
	Led_GRB7[7] = Rgb_Tab1[2];
	//2
	Led_GRB6[7] = Rgb_Tab1[2];
	Led_GRB7[6] = Rgb_Tab1[2];
	//2
	Led_GRB6[8] = Rgb_Tab1[2];
	Led_GRB7[5] = Rgb_Tab1[2];
	
	//1
	Led_GRB6[9] = Rgb_Tab1[1];
	Led_GRB7[4] = Rgb_Tab1[1];
	//1
	Led_GRB6[10] = Rgb_Tab1[1];
	Led_GRB7[3] = Rgb_Tab1[1];
	//1
	Led_GRB6[11] = Rgb_Tab1[1];
	Led_GRB7[2] = Rgb_Tab1[1];
	
	//0
	Led_GRB6[12] = Rgb_Tab1[0];
	Led_GRB7[1] = Rgb_Tab1[0];	
	//0
	Led_GRB6[13] = Rgb_Tab1[0];
	Led_GRB7[0] = Rgb_Tab1[0];
	//0
	Led_GRB6[14] = Rgb_Tab1[0];
	Led_GRB6[15] = Rgb_Tab1[0];
	Led_GRB6[16] = Rgb_Tab1[0];
	Led_GRB6[17] = Rgb_Tab1[0];
}

//=============================================================================
void SetAllDispRgb1_gl_S(void)
{
	uchar play_rgb;
	//0
	play_rgb = GetPlayRgbValue(Led_GRB6[13],Led_GRB6[14]);
	PlayRgb6[14] = play_rgb;
	PlayRgb6[15] = play_rgb;
	PlayRgb6[16] = play_rgb;
	PlayRgb6[17] = play_rgb;
	//0
	play_rgb = GetPlayRgbValue(Led_GRB6[12],Led_GRB6[13]);
	PlayRgb6[13] = play_rgb;
	PlayRgb7[0] = play_rgb;
	//0
	play_rgb = GetPlayRgbValue(Led_GRB6[11],Led_GRB6[12]);
	PlayRgb6[12] = play_rgb;
	PlayRgb7[1] = play_rgb;
	
	//1
	play_rgb = GetPlayRgbValue(Led_GRB6[10],Led_GRB6[11]);
	PlayRgb6[11] = play_rgb;
	PlayRgb7[2] = play_rgb;
	//1
	play_rgb = GetPlayRgbValue(Led_GRB6[9],Led_GRB6[10]);
	PlayRgb6[10] = play_rgb;
	PlayRgb7[3] = play_rgb;
	//1
	play_rgb = GetPlayRgbValue(Led_GRB6[8],Led_GRB6[9]);
	PlayRgb6[9] = play_rgb;
	PlayRgb7[4] = play_rgb;
	
	//2
	play_rgb = GetPlayRgbValue(Led_GRB6[7],Led_GRB6[8]);
	PlayRgb6[8] = play_rgb;
	PlayRgb7[5] = play_rgb;
	//2
	play_rgb = GetPlayRgbValue(Led_GRB6[6],Led_GRB6[7]);
	PlayRgb6[7] = play_rgb;
	PlayRgb7[6] = play_rgb;
	//2
	play_rgb = GetPlayRgbValue(Led_GRB6[5],Led_GRB6[6]);
	PlayRgb6[6] = play_rgb;
	PlayRgb7[7] = play_rgb;
	
	//3
	play_rgb = GetPlayRgbValue(Led_GRB6[4],Led_GRB6[5]);
	PlayRgb6[5] = play_rgb;
	PlayRgb7[8] = play_rgb;
	//3
	play_rgb = GetPlayRgbValue(Led_GRB6[3],Led_GRB6[4]);
	PlayRgb6[4] = play_rgb;
	PlayRgb7[9] = play_rgb;
	//3
	play_rgb = GetPlayRgbValue(Led_GRB6[2],Led_GRB6[3]);
	PlayRgb6[3] = play_rgb;
	PlayRgb7[10] = play_rgb;
	
	//4
	play_rgb = GetPlayRgbValue(Led_GRB6[1],Led_GRB6[2]);
	PlayRgb6[2] = play_rgb;
	PlayRgb7[11] = play_rgb;
	//4
	play_rgb = GetPlayRgbValue(Led_GRB6[0],Led_GRB6[1]);
	PlayRgb6[1] = play_rgb;
	PlayRgb7[12] = play_rgb;
	//4
	play_rgb = GetPlayRgbValue(Led_GRB7[17],Led_GRB6[0]);
	PlayRgb6[0] = play_rgb;
	PlayRgb7[13] = play_rgb;
	
	//5
	if(PlayLight%3)
	{
		PlayRgb7[17] = 0;
		PlayRgb7[16] = 0;
		PlayRgb7[15] = 0;
		PlayRgb7[14] = 0;
	}	
	else
	{
		play_rgb = 40;
		PlayRgb7[17] = play_rgb;
		PlayRgb7[16] = play_rgb;
		PlayRgb7[15] = play_rgb;
		PlayRgb7[14] = play_rgb;
	}	
}	
	
	
//=============================================================================
//void SetAllDispRgb1_rol(void)
//{
//	SysFlag |= D_DispUpdata1;
//	
//	//8
//	Led_GRB7[17] = Rgb_Tab1[8];
//	//8
//	Led_GRB7[16] = Rgb_Tab1[8];
//	//8
//	Led_GRB7[15] = Rgb_Tab1[8];
//	//8
//	Led_GRB7[14] = Rgb_Tab1[8];
//	
//	//7
//	Led_GRB7[13] = Rgb_Tab1[7];
//	//7
//	Led_GRB7[12] = Rgb_Tab1[7];
//	//7
//	Led_GRB7[11] = Rgb_Tab1[7];
//	//7
//	Led_GRB7[10] = Rgb_Tab1[7];
//	
//	//6
//	Led_GRB7[9] = Rgb_Tab1[6];
//	//6
//	Led_GRB7[8] = Rgb_Tab1[6];
//	//6
//	Led_GRB7[7] = Rgb_Tab1[6];
//	//6
//	Led_GRB7[6] = Rgb_Tab1[6];
//	
//	//5
//	Led_GRB7[5] = Rgb_Tab1[5];
//	//5
//	Led_GRB7[4] = Rgb_Tab1[5];
//	//5
//	Led_GRB7[3] = Rgb_Tab1[5];
//	//5
//	Led_GRB7[2] = Rgb_Tab1[5];
//	
//	//4
//	Led_GRB7[1] = Rgb_Tab1[4];
//	//4
//	Led_GRB7[0] = Rgb_Tab1[4];
//	//4
//	Led_GRB6[17] = Rgb_Tab1[4];
//	//4
//	Led_GRB6[16] = Rgb_Tab1[4];
//	
//	//3
//	Led_GRB6[15] = Rgb_Tab1[3];
//	//3
//	Led_GRB6[14] = Rgb_Tab1[3];
//	//3
//	Led_GRB6[13] = Rgb_Tab1[3];
//	//3
//	Led_GRB6[12] = Rgb_Tab1[3];
//	
//	//2
//	Led_GRB6[11] = Rgb_Tab1[2];
//	//2
//	Led_GRB6[10] = Rgb_Tab1[2];
//	//2
//	Led_GRB6[9] = Rgb_Tab1[2];
//	//2
//	Led_GRB6[8] = Rgb_Tab1[2];
//	
//	//1
//	Led_GRB6[7] = Rgb_Tab1[1];
//	//1
//	Led_GRB6[6] = Rgb_Tab1[1];
//	//1
//	Led_GRB6[5] = Rgb_Tab1[1];
//	//1
//	Led_GRB6[4] = Rgb_Tab1[1];
//	
//	//0
//	Led_GRB6[3] = Rgb_Tab1[0];
//	//0
//	Led_GRB6[2] = Rgb_Tab1[0];
//	//0
//	Led_GRB6[1] = Rgb_Tab1[0];
//	//0
//	Led_GRB6[0] = Rgb_Tab1[0];
//}
//
////=============================================================================
//void SetAllDispRgb1_rol_S(void)
//{
//	uchar play_rgb;
//	//0
//	play_rgb = GetPlayRgbValue(Led_GRB6[1],Led_GRB6[0]);
//	PlayRgb6[0] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[2],Led_GRB6[1]);
//	PlayRgb6[1] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[3],Led_GRB6[2]);
//	PlayRgb6[2] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[4],Led_GRB6[3]);
//	PlayRgb6[3] = play_rgb;
//	
//	//1
//	play_rgb = GetPlayRgbValue(Led_GRB6[5],Led_GRB6[4]);
//	PlayRgb6[4] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[6],Led_GRB6[5]);
//	PlayRgb6[5] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[7],Led_GRB6[6]);
//	PlayRgb6[6] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[8],Led_GRB6[7]);
//	PlayRgb6[7] = play_rgb;
//	
//	//2
//	play_rgb = GetPlayRgbValue(Led_GRB6[9],Led_GRB6[8]);
//	PlayRgb6[8] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[10],Led_GRB6[9]);
//	PlayRgb6[9] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[11],Led_GRB6[10]);
//	PlayRgb6[10] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[12],Led_GRB6[11]);
//	PlayRgb6[11] = play_rgb;
//	
//	//3
//	play_rgb = GetPlayRgbValue(Led_GRB6[13],Led_GRB6[12]);
//	PlayRgb6[12] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[14],Led_GRB6[13]);
//	PlayRgb6[13] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[15],Led_GRB6[14]);
//	PlayRgb6[14] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[16],Led_GRB6[15]);
//	PlayRgb6[15] = play_rgb;
//	
//	//4
//	play_rgb = GetPlayRgbValue(Led_GRB6[17],Led_GRB6[16]);
//	PlayRgb6[16] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[0],Led_GRB6[17]);
//	PlayRgb6[17] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[1],Led_GRB7[0]);
//	PlayRgb7[0] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[2],Led_GRB7[1]);
//	PlayRgb7[1] = play_rgb;
//	
//	//5
//	play_rgb = GetPlayRgbValue(Led_GRB7[3],Led_GRB7[2]);
//	PlayRgb7[2] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[4],Led_GRB7[3]);
//	PlayRgb7[3] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[5],Led_GRB7[4]);
//	PlayRgb7[4] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[6],Led_GRB7[5]);
//	PlayRgb7[5] = play_rgb;
//	
//	//6
//	play_rgb = GetPlayRgbValue(Led_GRB7[7],Led_GRB7[6]);
//	PlayRgb7[6] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[8],Led_GRB7[7]);
//	PlayRgb7[7] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[9],Led_GRB7[8]);
//	PlayRgb7[8] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[10],Led_GRB7[9]);
//	PlayRgb7[9] = play_rgb;
//	
//	//7
//	play_rgb = GetPlayRgbValue(Led_GRB7[11],Led_GRB7[10]);
//	PlayRgb7[10] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[12],Led_GRB7[11]);
//	PlayRgb7[11] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[13],Led_GRB7[12]);
//	PlayRgb7[12] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[14],Led_GRB7[13]);
//	PlayRgb7[13] = play_rgb;
//	
//	//8
//	play_rgb = GetPlayRgbValue(Led_GRB7[15],Led_GRB7[14]);
//	PlayRgb7[14] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[16],Led_GRB7[15]);
//	PlayRgb7[15] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB7[17],Led_GRB7[16]);
//	PlayRgb7[16] = play_rgb;
//	play_rgb = GetPlayRgbValue(Led_GRB6[0],Led_GRB7[17]);
//	PlayRgb7[17] = play_rgb;
//}	
	
//=============================================================================
void SetAllDispRgb1_rol_f(void)
{
	SysFlag |= D_DispUpdata1;
	
	//8
	Led_GRB7[17] = Rgb_Tab1[8];
	//8
	Led_GRB7[16] = Rgb_Tab1[8];
	//8
	Led_GRB7[15] = Rgb_Tab1[8];
	//8
	Led_GRB7[14] = Rgb_Tab1[8];
	
	//7
	Led_GRB7[13] = Rgb_Tab1[7];
	//7
	Led_GRB7[12] = Rgb_Tab1[7];
	//7
	Led_GRB7[11] = Rgb_Tab1[7];
	//7
	Led_GRB7[10] = Rgb_Tab1[7];
	
	//6
	Led_GRB7[9] = Rgb_Tab1[6];
	//6
	Led_GRB7[8] = Rgb_Tab1[6];
	//6
	Led_GRB7[7] = Rgb_Tab1[6];
	//6
	Led_GRB7[6] = Rgb_Tab1[6];
	
	//5
	Led_GRB7[5] = Rgb_Tab1[5];
	//5
	Led_GRB7[4] = Rgb_Tab1[5];
	//5
	Led_GRB7[3] = Rgb_Tab1[5];
	//5
	Led_GRB7[2] = Rgb_Tab1[5];
	
	//4
	Led_GRB7[1] = Rgb_Tab1[4];
	//4
	Led_GRB7[0] = Rgb_Tab1[4];
	//4
	Led_GRB6[17] = Rgb_Tab1[4];
	//4
	Led_GRB6[16] = Rgb_Tab1[4];
	
	//3
	Led_GRB6[15] = Rgb_Tab1[3];
	//3
	Led_GRB6[14] = Rgb_Tab1[3];
	//3
	Led_GRB6[13] = Rgb_Tab1[3];
	//3
	Led_GRB6[12] = Rgb_Tab1[3];
	
	//2
	Led_GRB6[11] = Rgb_Tab1[2];
	//2
	Led_GRB6[10] = Rgb_Tab1[2];
	//2
	Led_GRB6[9] = Rgb_Tab1[2];
	//2
	Led_GRB6[8] = Rgb_Tab1[2];
	
	//1
	Led_GRB6[7] = Rgb_Tab1[1];
	//1
	Led_GRB6[6] = Rgb_Tab1[1];
	//1
	Led_GRB6[5] = Rgb_Tab1[1];
	//1
	Led_GRB6[4] = Rgb_Tab1[1];
	
	//0
	Led_GRB6[3] = Rgb_Tab1[0];
	//0
	Led_GRB6[2] = Rgb_Tab1[0];
	//0
	Led_GRB6[1] = Rgb_Tab1[0];
	//0
	Led_GRB6[0] = Rgb_Tab1[0];
}

//=============================================================================
void SetAllDispRgb1_rol_f_S(void)
{
	uchar play_rgb;
	//0
	play_rgb = GetPlayRgbValue(Led_GRB6[2],Led_GRB6[0]);
	PlayRgb6[0] = play_rgb;
	PlayRgb6[1] = play_rgb;
	play_rgb = GetPlayRgbValue(Led_GRB6[4],Led_GRB6[2]);
	PlayRgb6[2] = play_rgb;
	PlayRgb6[3] = play_rgb;
	
	//1
	play_rgb = GetPlayRgbValue(Led_GRB6[6],Led_GRB6[4]);
	PlayRgb6[4] = play_rgb;
	PlayRgb6[5] = play_rgb;
	play_rgb = GetPlayRgbValue(Led_GRB6[8],Led_GRB6[6]);
	PlayRgb6[6] = play_rgb;
	PlayRgb6[7] = play_rgb;
	
	//2
	play_rgb = GetPlayRgbValue(Led_GRB6[10],Led_GRB6[8]);
	PlayRgb6[8] = play_rgb;
	PlayRgb6[9] = play_rgb;
	play_rgb = GetPlayRgbValue(Led_GRB6[12],Led_GRB6[10]);
	PlayRgb6[10] = play_rgb;
	PlayRgb6[11] = play_rgb;
	
	//3
	play_rgb = GetPlayRgbValue(Led_GRB6[14],Led_GRB6[12]);
	PlayRgb6[12] = play_rgb;
	PlayRgb6[13] = play_rgb;
	play_rgb = GetPlayRgbValue(Led_GRB6[16],Led_GRB6[14]);
	PlayRgb6[14] = play_rgb;
	PlayRgb6[15] = play_rgb;
	
	//4
	play_rgb = GetPlayRgbValue(Led_GRB7[0],Led_GRB6[16]);
	PlayRgb6[16] = play_rgb;
	PlayRgb6[17] = play_rgb;
	play_rgb = GetPlayRgbValue(Led_GRB7[2],Led_GRB7[0]);
	PlayRgb7[0] = play_rgb;
	PlayRgb7[1] = play_rgb;
	
	//5
	play_rgb = GetPlayRgbValue(Led_GRB7[4],Led_GRB7[2]);
	PlayRgb7[2] = play_rgb;
	PlayRgb7[3] = play_rgb;
	play_rgb = GetPlayRgbValue(Led_GRB7[6],Led_GRB7[4]);
	PlayRgb7[4] = play_rgb;
	PlayRgb7[5] = play_rgb;
	
	//6
	play_rgb = GetPlayRgbValue(Led_GRB7[8],Led_GRB7[6]);
	PlayRgb7[6] = play_rgb;
	PlayRgb7[7] = play_rgb;
	play_rgb = GetPlayRgbValue(Led_GRB7[10],Led_GRB7[8]);
	PlayRgb7[8] = play_rgb;
	PlayRgb7[9] = play_rgb;
	
	//7
	play_rgb = GetPlayRgbValue(Led_GRB7[12],Led_GRB7[10]);
	PlayRgb7[10] = play_rgb;
	PlayRgb7[11] = play_rgb;
	play_rgb = GetPlayRgbValue(Led_GRB7[14],Led_GRB7[12]);
	PlayRgb7[12] = play_rgb;
	PlayRgb7[13] = play_rgb;
	
	//8
	play_rgb = GetPlayRgbValue(Led_GRB7[16],Led_GRB7[14]);
	PlayRgb7[14] = play_rgb;
	PlayRgb7[15] = play_rgb;
	play_rgb = GetPlayRgbValue(Led_GRB6[0],Led_GRB7[16]);
	PlayRgb7[16] = play_rgb;
	PlayRgb7[17] = play_rgb;
}	
	
//=============================================================================
void SetDispRamdon1(void)
{
	uchar i,j;
	SysFlag |= D_DispUpdata1;
	Random();
	for(i=0;i<18;i++)
	{
		j++;
		if(j>8)
			j=0;
		Led_GRB6[i] = Rgb_Tab1[j];
		j++;
		if(j>8)
			j=0;
		Led_GRB7[i] = Rgb_Tab1[j];
	}
}

//=============================================================================
void SetDispRamdon1_S(void)
{
	uchar i;
	for(i=0;i<18;i++)
	{
		PlayRgb6[i] = 40;	//GetPlayRgbValue2(Led_GRB6[i]);
		PlayRgb7[i] = 40;;	//GetPlayRgbValue2(Led_GRB7[i]);
	}
}
//=============================================================================
