#ifndef __TM52F5864_H__
#define __TM52F5864_H__
/*
******************************************************************************************************
BYTE Registers
******************************************************************************************************
*/
sfr 	P0    		= 0x80;			//Port 0 data
	//--------------------------------------------------------------------------------------------
	sbit 		P0_7		= P0^7;
	sbit 		P0_6		= P0^6;
	sbit 		P0_5		= P0^5;
	sbit 		P0_4		= P0^4;
	sbit 		P0_3		= P0^3;
	sbit 		P0_2		= P0^2;
	sbit 		P0_1		= P0^1;
	sbit 		P0_0		= P0^0;
/*
******************************************************************************************************
*/
sfr 	SP   		= 0x81;			//Stack Point
/*
******************************************************************************************************
*/
sfr 	DPL   		= 0x82;			//Data Point Low byte
sfr 	DPH   		= 0x83;   		//Data Point High byte
/*
******************************************************************************************************
*/
sfr 	INTE2  		= 0x84;   		//
	#define	PWM1IE	0x40	//PWM1~6 Interrupt Enable. 1: enable, 0: disable
	#define	PWM0IE	0x20	//PWM0 Interrupt Enable. 1: enable, 0: disable

/*
******************************************************************************************************
*/
sfr 	INTFLG2		= 0x85;   		//
	#define	PWM1IF	0x40	//PWM1~6 Interrupt Flag. 1: interrupt asserted, 0: interrupt not asserted
	#define	PWM0IF	0x20	//PWM0 Interrupt Flag. 1: interrupt asserted, 0: interrupt not asserted


/*
******************************************************************************************************
*/
sfr 	PCON  		= 0x87;			//不支持位操作,用读改写方式
	//--------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------
	#define 	GF1		0x08		//PCON Bit[3],用户可以随便使用
	#define 	GF0		0x04		//PCON Bit[2],用户可以随便使用
	//--------------------------------------------------------------------------------------------
	#define 	PD		0x02		//PCON Bit[1],此位置1,芯片进入stop模式
	//--------------------------------------------------------------------------------------------
	#define 	IDL		0x01		//PCON Bit[0],此位置1,芯片进入IDL模式
	//---------------------------------------------------------------------------------------------
	#define		ENTER_IDLE_MODE		PCON |= IDL
	#define		LEAVE_IDLE_MODE		PCON = (PCON&0xfe)
	#define		ENTER_STOP_MODE		PCON |= PD
	#define		LEAVE_STOP_MODE		PCON = (PCON&0xfd)
	
/*
******************************************************************************************************
*/
sfr 	TCON  		= 0x88;
	//--------------------------------------------------------------------------------------------
	sbit 		TF1 		= TCON^7;	//定时器T1溢出标志,可由程序查询和清零,TF1也是中断请求源,当CPU响应T1中断时由硬件清零
	sbit 		TR1 		= TCON^6;	//T1充许计数控制位,为1时充许T1计数
	//--------------------------------------------------------------------------------------------
	sbit 		TF0 		= TCON^5;	//定时器T0溢出标志,可由程序查询和清零,TF0也是中断请求源,当CPU响应T0中断时由硬件清零
	sbit 		TR0			= TCON^4;	//T0充许计数控制位,为1时充许T0计数
	//--------------------------------------------------------------------------------------------
	sbit 		IE1 		= TCON^3;	//外部中断1请示源(INT1,P3.3)标志;IE1也是中断请求源,当CPU响应该中断时由硬件清IE1(边沿触发方式)
	sbit 		IT1 		= TCON^2;	//外部中断源1触发方式控制位,IT1＝0,外部中断1程控为电平触发方式;当INT1（P3.3）输入低电平时,置位IE1
	//--------------------------------------------------------------------------------------------
	sbit 		IE0 		= TCON^1;	//外部中断0请示源(INT1,P3.2)标志;IE0也是中断请求源,当CPU响应该中断时由硬件清IE0(边沿触发方式)
	sbit 		IT0 		= TCON^0;	//外部中断源0触发方式控制位,IT0＝0,外部中断0程控为电平触发方式;当INT0（P3.2）输入低电平时,置位IE0
/*
******************************************************************************************************
*/
sfr 	TMOD  		= 0x89;				//不支持位操作,用读改写方式
	//--------------------------------------------------------------------------------------------
	#define 	T1_Mask		~0xf0		//T1工作模式选择Mask
	//--------------------------------------------------------------------------------------------
	#define 	GATE1		0x80		//定时器1操作开关控制位
					 	 				//当GATE1=1时,INT1引脚为高电平,同时TCON中的TR1控制位为1时,计时/计数器1才开始工作
					 	 				//当GATE1=0时,则只要将TR1控制位设为1，计时/计数器1就开始工作
	#define 	CT1N		0x40		//定时/计数器1功能的选择位
	#define 	CT1			0x40		//定时/计数器1功能的选择位
					 	 				//CT1=1为计数器,通过外部引脚T1输入计数脉冲
					 	 				//CT1=0为定时器,由内部系统时钟提供计时工作脉冲
	//--------------------------------------------------------------------------------------------
	#define 	T1_Mode0		0x00		//T1为13位计时/计数器
	#define 	T1_Mode1		0x10		//T1为16位计时/计数器
	#define 	T1_Mode2		0x20		//T1为8位自动加载计数/计时器 
	#define 	T1_Mode3		0x30		//timer stop
	//--------------------------------------------------------------------------------------------
	#define 	T0_Mask			~0x0f		//T0工作模式选择Mask
	//--------------------------------------------------------------------------------------------
	#define 	GATE0			0x08		//定时器0操作开关控制位
					 	 				//当GATE0=1时,INT0引脚为高电平,同时TCON中的TR0控制位为1时,计时/计数器0才开始工作
					 	 				//当GATE0=0时,则只要将TR0控制位设为1，计时/计数器0就开始工作
	#define 	CT0N			0x04		//定时/计数器0功能的选择位
	#define 	CT0				0x04		//定时/计数器0功能的选择位
					 	 				//CT0=1为计数器,通过外部引脚T0输入计数脉冲
					 	 				//CT0=0为定时器,由内部系统时钟提供计时工作脉冲
	//--------------------------------------------------------------------------------------------
	#define 	T0_Mode0			0x00		//T0为13位计时/计数器 
	#define 	T0_Mode1			0x01		//T0为16位计时/计数器 
	#define 	T0_Mode2			0x02		//T0为8位自动加载计数/计时器
	#define 	T0_Mode3			0x03		//仅适用于T0,T0分为两个独立的8位定时器/计数器TH0及TL0,在此模式下T1停止工作
/*
******************************************************************************************************
*/	
sfr 	TL0   		= 0x8A;				//Timer 0 data low byte
sfr 	TH0   		= 0x8C;				//Timer 0 data high byte
/*
******************************************************************************************************
*/
sfr 	TL1   		= 0x8B;				//Timer 1 data low byte
sfr 	TH1   		= 0x8D;			  //Timer 1 data high byte

/*
******************************************************************************************************
*/
sfr 	P1    		= 0x90;				//Port 1 data
	//--------------------------------------------------------------------------------------------
	sbit 		P1_7		= P1^7;
	sbit 		P1_6		= P1^6;	
	sbit 		P1_5		= P1^5;	
	sbit 		P1_4		= P1^4;	
	sbit 		P1_3		= P1^3;	
	sbit 		P1_2		= P1^2;	
	sbit 		P1_1		= P1^1;	
	sbit 		P1_0		= P1^0;	
/*
******************************************************************************************************
*/
sfr 	P0MOD10    	= 0x91;

	#define		P01MOD_Mask		~0xF0
	#define		P00MOD_Mask		~0x0F


/*
******************************************************************************************************
*/
sfr 	P0MOD32    	= 0x92;
	//--------------------------------------------------------------------------------------------
	#define		P03MOD_Mask		~0xF0
	#define		P02MOD_Mask		~0x0F

/*
******************************************************************************************************
*/
sfr 	P0MOD54    	= 0x93;
	//--------------------------------------------------------------------------------------------
	#define		P05MOD_Mask		~0xF0
	#define		P04MOD_Mask		~0x0F

/*
******************************************************************************************************
*/
sfr 	P0MOD76    	= 0x96;
	//--------------------------------------------------------------------------------------------
	#define		P07MOD_Mask		~0xF0
	#define		P06MOD_Mask		~0x0F

/*
******************************************************************************************************
*/
sfr 	OPTION    	= 0x94;
	//--------------------------------------------------------------------------------------------
	
	#define 	TM3CKS		0x40		//Timer3 Clock Source Select. 0: SLOW (SRC), 1: FRC/512 (32.4KHz)

	//--------------------------------------------------------------------------------------------
	//WDTPSC:OPTION Bit[5:4],WDT Prescale.  
	#define		WDTPSC_Mask	  ~0x30
	#define		WDTPSC_1	    0x00	  //00: 528ms WDT overflow rate
	#define		WDTPSC_2		0x10		//01: 264ms WDT overflow rate
	#define		WDTPSC_3 		0x20		//10: 132ms WDT overflow rate
	#define		WDTPSC_4 		0x30		//11: 66ms WDT overflow rate
	
	#define		WDTPSC_00		0x00	  	//00: 528ms WDT overflow rate
	#define		WDTPSC_01		0x10		//01: 264ms WDT overflow rate
	#define		WDTPSC_02 		0x20		//10: 132ms WDT overflow rate
	#define		WDTPSC_03		0x30		//11: 66ms WDT overflow rate
		
	#define  	WDTPSC0    OPTION=OPTION&0xcf			//00: 528ms WDT overflow rate
	#define  	WDTPSC1    OPTION=(OPTION&0xcf)|0x10	//01: 264ms WDT overflow rate
	#define  	WDTPSC2    OPTION=(OPTION&0xcf)|0x20	//10: 132ms WDT overflow rate
	#define  	WDTPSC3    OPTION=(OPTION&0xcf)|0x30	//11: 66ms WDT overflow rate
	
	//--------------------------------------------------------------------------------------------
	//ADCKS:OPTION Bit[3:2],ADC Clock Rate 
	#define		ADCKS_Mask			~0x0C		//b'00001100'		//ADC Clock Rate Mask
	#define		ADCKS_sys_32	  	0x00	    //Interrupt rate is 32768 system clock cycle
	#define		ADCKS_sys_16		0x04		//Interrupt rate is 16384 system clock cycle
	#define		ADCKS_sys_8 		0x08		// Interrupt rate is 8192 system clock cycle
	#define		ADCKS_sys_4 		0x0c		//Interrupt rate is 128 system clock cycle
	//--------------------------------------------------------------------------------------------
	//SXGAIN:OPTION Bit[1:0].
	#define		SXTGAIN_Mask		~0x03		
	#define		SXTGAIN_0			0x00	    //
	#define		SXTGAIN_1			0x01		//
	#define		SXTGAIN_2			0x02		//
	#define		SXTGAIN_3			0x03		//
/*
******************************************************************************************************
*/
//sfr 	INTFLAG    	= 0x95;
sfr 	INTFLG    	= 0x95;

	#define		LVDIF	0x80
	//LVD interrupt flag
	//Set by H/W when VCC less than the LVD voltage. S/W writes 7Fh to INTFLG to clear this flag.
	
	#define		CMPIF	0x40
	//CMP interrupt flag
	//Set by H/W while CMPO match trigger condition. It is cleared automatically when the program performs the interrupt service routine. S/W writes BFh to INTFLG to clear this flag.
	
	//--------------------------------------------------------------------------------------------
	#define		ADIF	0x10		//ADC 中断标志，HW clear while ADSOC set
	//--------------------------------------------------------------------------------------------
	#define 	WGIF	0x08
		
	
	#define 	PCIF	0x02		//Port0/1/2/3 Pin Change INT Flag (INTVEC=43h)
	//--------------------------------------------------------------------------------------------
	#define 	TF3		0x01		//TM3中断标志,1=TM3中断

/*
******************************************************************************************************
*/
sfr		SWCMD		= 0x97;			
	//--------------------------------------------------------------------------------------------
	//SWRST:SWCMD Bit[7:0],Write 56h to generate S/W Reset

	//--------------------------------------------------------------------------------------------
	//IAPALL:SWCMD Bit[7:0],Write 65h to this register to enable IAP all area, other value to disable IAP all.

	#define		WDTO	0x02		//WatchDog Time-Out flag
	#define		IAPALL	0x01		//Flag indicates Flash can be written by IAP or not
									//0: Flash IAP disable
									//1: Flash IAP enable, only for BOOT mode upgrade APP area.
/*
******************************************************************************************************
*/
sfr 	SCON  		= 0x98;
	//--------------------------------------------------------------------------------------------
	sbit 		SM0 		= SCON^7;	//串行口工作方式控制位 Bit[0]
	sbit 		SM1 		= SCON^6;	//串行口工作方式控制位 Bit[1]
	#define		Uart_ModeMask	~0xC0	//串口模式Mask
	#define		Uart_Mode0		0x00	//00: Mode0: 8 bit shift register, Baud Rate=FSYSCLK/2
	#define		Uart_Mode1		0x40	//01: Mode1: 8 bit UART, Baud Rate is variable
	#define		Uart_Mode2		0x80	//10: Mode2: 9 bit UART, Baud Rate=FSYSCLK/32 or /64
	#define		Uart_Mode3		0xc0	//11: Mode3: 9 bit UART, Baud Rate is variable
	
	//--------------------------------------------------------------------------------------------
	sbit 		SM2 		= SCON^5;	//多机通信控制位*/
										//多机通信是工作于方式2和方式3，SM2位主要用于方式2和方式3接收状态
					 	 				//当串行口工作于方式2或3:
					 	 				//当SM2=1时,只有当接收到第9位数据(RB8)为1时,才把接收到的前8位数据送入SBUF,且置位RI发出中断申请,否则会将接收到的数据放弃
					 	 				//当SM2=0时,就不管第9位数据是0还是1,都得数据送入SBUF,并发出中断申请,工作于方式0时，SM2必须为0
	//--------------------------------------------------------------------------------------------
	sbit 		REN 		= SCON^4;	//允许接收位:
					 	 				//REN用于控制数据接收的允许和禁止,REN=1时,允许接收,REN=0时,禁止接收
	//--------------------------------------------------------------------------------------------
	sbit 		TB8 		= SCON^3;	//发送数据第8位
	sbit 		RB8 		= SCON^2;	//接收数据第8位
	//--------------------------------------------------------------------------------------------
	sbit 		TI 			= SCON^1;	//发送中断标志位：
					 	 				//方式0时,发送完第8位数据后,由硬件置位
					 	 				//其它方式下,由硬件置位,TI=1表示帧发送结束,TI可由软件清零
	//--------------------------------------------------------------------------------------------
	sbit 		RI 			= SCON^0;	//接收中断标志位：
					 	 				//方式0时,接收完第8位数据后,由硬件置位
					 	 				//其它方式下,由硬件置位,RI=1表示帧接收完成
/*
******************************************************************************************************
*/
sfr 	SBUF  		= 0x99;				//串口缓存寄存器,UART transmit and receive data


/*
******************************************************************************************************
*/
sfr 	P1MOD10    	= 0x9A;

	#define		P11MOD_Mask		~0xF0
	#define		P10MOD_Mask		~0x0F

/*
******************************************************************************************************
*/
sfr 	P1MOD32    	= 0x9B;
	//--------------------------------------------------------------------------------------------
	#define		P13MOD_Mask		~0xF0
	#define		P12MOD_Mask		~0x0F

/*
******************************************************************************************************
*/
sfr 	P1MOD54    	= 0x9C;
	//--------------------------------------------------------------------------------------------
	#define		P15MOD_Mask		~0xF0
	#define		P14MOD_Mask		~0x0F

/*
******************************************************************************************************
*/
sfr 	P1MOD76    	= 0x9D;
	//--------------------------------------------------------------------------------------------
	#define		P17MOD_Mask		~0xF0
	#define		P16MOD_Mask		~0x0F

/*
******************************************************************************************************
*/
sfr 	P2MOD10    	= 0x9E;

	#define		P21MOD_Mask		~0xF0
	#define		P20MOD_Mask		~0x0F


/*
******************************************************************************************************
*/
sfr 	P2MOD32    	= 0x9F;
	//--------------------------------------------------------------------------------------------
	#define		P23MOD_Mask		~0xF0
	#define		P22MOD_Mask		~0x0F


	
/*
******************************************************************************************************
*/
sfr 	P2    		= 0xA0;			//Port 2 data
	//--------------------------------------------------------------------------------------------
	sbit 		P2_7		= P2^7;
	sbit 		P2_6		= P2^6;
	sbit 		P2_5		= P2^5;	
	sbit 		P2_4		= P2^4;	
	sbit 		P2_3		= P2^3;	
	sbit 		P2_2		= P2^2;	
	sbit 		P2_1		= P2^1;	
	sbit 		P2_0		= P2^0;							
/*
******************************************************************************************************
*/
sfr		PWMCON		= 0xA1;
	#define		PWM1CKS_Mask	~0xc0
	#define		PWM1CKS_1   	 0x00// PWM1 Clock source Cpuclk
	#define		PWM1CKS_2   	 0x40// PWM1 Clock source Cpuclk
	#define		PWM1CKS_3   	 0x80// PWM1 Clock source FRC16M
	#define		PWM1CKS_4   	 0xc0// PWM1 Clock source FRC16M*2

	#define		PWM1EN			0x20	//PWM1~6 Enable. 0: PWM1~6 Disable, 1: PWM1~6 Enable
	#define		PWM0EN			0x10	//PWM0 Enable. 0: PWM0 Disable, 1: PWM0 Enable

	#define		PWM0CKS_Mask	~0x0C
	#define		PWM0CKS_1   	 0x00// PWM0 Clock source Cpuclk
	#define		PWM0CKS_2   	 0x04// PWM0 Clock source Cpuclk
	#define		PWM0CKS_3   	 0x08// PWM0 Clock source FRC16M
	#define		PWM0CKS_4   	 0x0C// PWM0 Clock source FRC16M*2
	
	#define		PWM0DL_Mask		  ~0x03
	#define		PWM0NMSK		0x02	//PWM0N mask data. If CLRPWM0=1 and PMW0MSKE=1, PWM0N will output this mask data.
	#define		PWM0PMSK		0x01	//PWM0P mask data. If CLRPWM0=1 and PMW0MSKE=1, PWM0P will output this mask data.
		

/*
******************************************************************************************************
*/
sfr 	P3MOD10    	= 0xA2;

	#define		P31MOD_Mask		~0xF0
	#define		P30MOD_Mask		~0x0F

/*
******************************************************************************************************
*/
sfr 	P3MOD32    	= 0xA3;
	//--------------------------------------------------------------------------------------------
	#define		P33MOD_Mask		~0xF0
	#define		P32MOD_Mask		~0x0F

/*
******************************************************************************************************
*/
sfr 	P3MOD54    	= 0xA4;
	//--------------------------------------------------------------------------------------------
	#define		P35MOD_Mask		~0xF0
	#define		P34MOD_Mask		~0x0F

/*
******************************************************************************************************
*/
sfr 	P3MOD76    	= 0xA5;
	//--------------------------------------------------------------------------------------------
	#define		P37MOD_Mask		~0xF0
	#define		P36MOD_Mask		~0x0F


/*
******************************************************************************************************
*/

sfr 	PINMOD  		= 0xA6;

	//SPIPS:PINMOD Bit[6].
	#define		SPIPS_Mask		~0x40		
	#define		SPIPS_0			0x00	    //SPI SCK/MOSI/MISO select P35/P20/P21
	#define		SPIPS_1			0x40		//SPI SCK/MOSI/MISO select P12/P10/P11

	
	//UARTRXS:PINMOD Bit[5:4].
	#define		UARTRXS_Mask		~0x30		
	#define		UARTRXS_0			0x00	    //UART RXD select P30
	#define		UARTRXS_1			0x10		//UART RXD select P02
	#define		UARTRXS_2			0x20		//UART RXD select P31
	#define		UARTRXS_3			0x30		//UART RXD select P16

	//MSDAPS:PINMOD Bit[3:2].
	#define		MSDAPS_Mask		~0x0C		
	#define		MSDAPS_0			0x00	    //I2C SDA select P35
	#define		MSDAPS_1			0x04		//I2C SDA select P16
	#define		MSDAPS_2			0x08		//I2C SDA select P21
	#define		MSDAPS_3			0x0C		//I2C SDA select P25
	
	//MSCLPS:PINMOD Bit[1:0].
	#define		MSCLPS_Mask		~0x03		
	#define		MSCLPS_0			0x00	    //I2C SCL select P13
	#define		MSCLPS_1			0x01		//I2C SCL select P02
	#define		MSCLPS_2			0x02		//I2C SCL select P20
	#define		MSCLPS_3			0x03		//I2C SCL select P24
	
/*
******************************************************************************************************
*/
sfr 	P2MOD54    	= 0xA7;
	//--------------------------------------------------------------------------------------------
	#define		P25MOD_Mask		~0xF0
	#define		P24MOD_Mask		~0x0F

/*
******************************************************************************************************
*/
sfr 	IE    		= 0xA8;
	//--------------------------------------------------------------------------------------------
	sbit 		EA 			= IE^7;		//EA=0时,所有中断禁止;EA=1时,各中断的产生由个别的允许位决定
	sbit		ET2			= IE^5;		//定时2中断允许
	sbit 		ES 			= IE^4;		//串行口中断充许(ES=1充许,ES=0禁止)
	sbit 		ET1 		= IE^3;		//定时1中断充许
	sbit 		EX1 		= IE^2;		//外中断INT1中断充许
	sbit 		ET0 		= IE^1;		//定时器0中断充许
	sbit 		EX0 		= IE^0;		//外部中断INT0的中断允许
/*
******************************************************************************************************
*/
sfr		INTE1		= 0xA9;
	//--------------------------------------------------------------------------------------------
	#define		PWMIE		0x80		//PWM0/1 Interrupt Enable
	//--------------------------------------------------------------------------------------------
	#define		CMPIE		0x40		//Set 1 to enable CMP interrupt
	//--------------------------------------------------------------------------------------------
	#define		LVDIE		0x20		//LVD Interrupt Enable
	//--------------------------------------------------------------------------------------------
	#define		SPI2CE		0x10		//Set 1 to enable SPI/I2C interrupt
	//--------------------------------------------------------------------------------------------
	#define		ADIE 		0x08		//ADC Interrupt Enable
	//--------------------------------------------------------------------------------------------
	#define		WGIE		0x04	
	//--------------------------------------------------------------------------------------------
	#define	 	PCIE		0x02		//Port0/1/2/3 Pin Change Interrupt Enable
	//--------------------------------------------------------------------------------------------
	#define		TM3IE		0x01		//TM3中断允许		
/*
******************************************************************************************************
*/
sfr		ADCDL		= 0xAA;
	//--------------------------------------------------------------------------------------------
	//ADCDL:ADCDL Bit[7:4],ADC Data LSB 3~0


/*
******************************************************************************************************
*/
sfr		ADCDH		= 0xAB;//ADC Data 11~4
//--------------------------------------------------------------------------------------------
	//ADCDH:ADCDH Bit[7:0],ADC Data 11~4


/*
******************************************************************************************************
*/
sfr		ADCHSEL		= 0xAE;//ADC Channel Select
	//--------------------------------------------------------------------------------------------
	//ADCHS:ADCHSEL Bit[7:3],ADC Channel Select
							//00000: AD0 (P0.0)
							//00001: AD1 (P0.1)
							//00010: AD2 (P0.2)
							//00011: AD3 (P0.3)
							//00100: AD4 (P0.4)
							//00101: AD5 (P0.5)
							//00110: AD6 (P0.6)
							//00111: AD7 (P0.7)
							//01000: AD8 (P1.7)
							//01001: AD9 (P3.4)
							//01010: AD10 (P3.1)
							//01011: AD11 (P3.0)
							//01100: AD12 (P3.7)
							//01101: AD13 (P3.2)
							//01110: AD14 (P3.3)
							//01111: AD15 (P1.6)
							//10000: AD16 (P3.6)
							//10001: AD17 (P3.5)
							//10010: AD18 (P2.1)
							//10011: AD19 (P2.0)
							//10100: AD20 (P1.5)
							//10101: AD21 (P1.4)
							//10110: AD22 (P1.3)
							//10111: AD23 (P2.4)
							//11000: AD24 (P2.5)
							//11001: AD25 (P1.2)
							//11010: AD26 (P1.1)
							//11011: AD27 (P1.0)
							
							//11100: Vbg
							//11101: DAC
							//others: Reserved
							//11111:  (1/4VCC)
	
	#define		ADCVERFS	0x04	//AVREF Select: 0: VCC     1:VBG
	#define 	ADCVERFS_VCC	ADCHSEL= ADCHSEL&0xfb 
	#define 	ADCVERFS_VBG	ADCHSEL |= ADCVERFS
	
	//VBGSEL:CHSEL Bit[1:0]
	//VBG voltage select, When ADCVREF is selected as VBG, VBGSEL is prohibited from using 1.20V.
	#define	VBG_Mask	~0x03	
	#define	VBG_00		0x00	//00: 1.18V
	#define	VBG_01		0x01	//01: 2.0V
	#define	VBG_10		0x02	//10: 3.0V 
	#define	VBG_11		0x03	//11: 4.0V
	
/*
******************************************************************************************************
*/
sfr 	PWMCON2   = 0xAF;
//------------------------------------------------------------------------------------------------------------

	#define		PWM0MOD			0x80	//PWM0 Mode Select, 0: Normal Mode,1: Half-bridge Mode
	#define 	PWM0MOD_Normal		PWMCON2=(PWMCON2&0x7f) 
	#define 	PWM0MOD_Half_Bridge	PWMCON2 |= PWM0MOD
	
	//PWM0 Output Mask Enable
	//0: Disable
	//1: Enable, PWM0P/PWM0N output data by PWM0PMSK/PWM0nMSK while CLRPWM0=1 or PWMOFFF=1
	#define		PMW0MSKE			0x40
	#define		PMW0MSKE_DISABLE	PWMCON2=(PWMCON2&0xbf) 
	#define		PMW0MSKE_ENABLE		PWMCON2 |= PMW0MSKE
	
	//PWM0OM:PWMCON2 Bit[5:4],
	//PWM0 output mode.
	//00 ~ 11: Mode0 ~ Mode3
	#define		PWM0OM_Mask		~0x30
	#define		PWM0OM_0		0x00
	#define		PWM0OM_1		0x10
	#define		PWM0OM_2		0x20
	#define		PWM0OM_3		0x30
	
	//PWM0DZ:PWMCON2 Bit[3:0]
	//PWM0 Dead Zone.
	// 0000:disable  …  1111: 15*Tpwmclk 半橋模式禁用死區
	#define		PWM0DZ_Mask	~0x0F
	#define		PWM0DZ_0	0x00
	#define		PWM0DZ_1	0x01
	#define		PWM0DZ_2	0x02	
	#define		PWM0DZ_3	0x03	
	#define		PWM0DZ_4	0x04	
	#define		PWM0DZ_5	0x05	
	#define		PWM0DZ_6	0x06	
	#define		PWM0DZ_7	0x07	
	#define		PWM0DZ_8	0x08	
	#define		PWM0DZ_9	0x09	
	#define		PWM0DZ_10	0x0a
	#define		PWM0DZ_11	0x0b
	#define		PWM0DZ_12	0x0c
	#define		PWM0DZ_13	0x0d
	#define		PWM0DZ_14	0x0e
	#define		PWM0DZ_15	0x0f


   
/*
******************************************************************************************************
*/
sfr 	P3    		= 0xB0;				//Port 3 data
	//--------------------------------------------------------------------------------------------
	sbit 		P3_7		= P3^7;
	sbit 		P3_6		= P3^6;
	sbit 		P3_5		= P3^5;
	sbit 		P3_4		= P3^4;
	sbit 		P3_3		= P3^3;
	sbit 		P3_2		= P3^2;
	sbit 		P3_1		= P3^1;
	sbit 		P3_0		= P3^0;


/*
******************************************************************************************************
*/
sfr 	WGCON 		= 0xB6;
	//--------------------------------------------------------------------------------------------
	//WGPRD:WGCON Bit[7:5],WG period of each bit select   (TFRC =60.28 ns)
							//0: 15*TFRC = 904ns
							//1: 16*TFRC = 964ns
							//2: 17*TFRC = 1025ns
							//3: 18*TFRC = 1085ns
							//4: 19*TFRC = 1145ns
							//5: 20*TFRC = 1206ns
							//6: 21*TFRC = 1266ns
							//7: 22*TFRC = 1326ns

	//--------------------------------------------------------------------------------------------
	//WGT1H:WGCON Bit[4:2],WG code 1 high level time select   (TFRC =60.28 ns)
							//0: 10*TFRC = 603ns
							//1: 11*TFRC = 663ns
							//2: 12*TFRC = 723ns
							//3: 13*TFRC = 784ns
							//4: 14*TFRC = 844ns
							//5: 15*TFRC = 904ns
							//6: 16*TFRC = 964ns
							//7: 17*TFRC =1025ns

	//--------------------------------------------------------------------------------------------
	//WGT0H:WGCON Bit[1:0],WG code 0 high level time select   (TFRC =60.28 ns)
							//0: 4*TFRC = 241ns
							//1: 5*TFRC = 301ns
							//2: 6*TFRC = 362ns
							//3: 7*TFRC = 422ns


sfr 	WGBUF 		= 0xB7;

	
/*
******************************************************************************************************
*/
sfr 	IP    		= 0xB8;
	//--------------------------------------------------------------------------------------------
	sbit		PT2			  = IP^5;		//定时2中断优先级低位
	sbit 		PS			  = IP^4;		//串行口中断优先级低位
	sbit 		PT1	    	= IP^3;		//定时1中断优先级低位
	sbit 		PX1	    	= IP^2;		//外中断INT1中断优先级低位
	sbit 		PT0	    	= IP^1;		//定时0中断优先级低位
	sbit 		PX0	    	= IP^0;		//外中断INT0中断优先级低位
/*
******************************************************************************************************
*/
sfr 	IPH    		= 0xB9;
	//--------------------------------------------------------------------------------------------
	#define		IPH_Mask	  ~0x3F		//
	#define		IPH_PT2H    0x20		//定时2中断优先级高位       
	#define		IPH_PSH     0x10 	  //串行口中断优先级高位      
	#define		IPH_PT1H    0x08	  //定时1中断优先级高位       
	#define		IPH_PX1H    0x04		//外中断INT1中断优先级高位  
	#define		IPH_PT0H    0x02		//定时0中断优先级高位       
	#define		IPH_PX0H    0x01 	  //外中断INT0中断优先级高位/*
/*
******************************************************************************************************
*/	
sfr 	IP1  		= 0xBA;		//Interrupt Priority Control Low bits
	//--------------------------------------------------------------------------------------------
	#define		PPWM		0x80		//PWM0~1 Interupt Priority Low bit
	#define		PCMP		0x40		//CMP Interrupt Priority Low bit
	#define		PLVD		0x20		//LVD Interupt Priority Low bit
	#define 	PSPI2C		0x10		//SPI/I2C Interrupt Priority Low bit
	#define 	PADI		0x08		//ADC/TK Interrupt Priority Low bit
	#define 	PWG		    0x04		//PWG Interrupt Priority Low bit
	#define 	PPC			0x02		//Px中断优先级低位
	#define		PT3			0x01		//定时3中断优先级低位
/*
******************************************************************************************************
*/
sfr 	IP1H   		= 0xBB;		//Interrupt Priority Control High bits
	//--------------------------------------------------------------------------------------------
	#define		PPWMH 		0x80		//PWM0~1 Interupt Priority High bit
	#define		PCMPH 		0x40		//CMP Interrupt Priority High bit
	#define		PLVDH 		0x20		//LVD Interupt Priority High bit
	#define		PSPI2CH 	0x10		//SPI/I2C Interrupt Priority High bit
	#define 	PADIH		0x08		//ADC/TK Interrupt Priority High bit
	#define 	PWGH		0x04		//PWG Interrupt Priority High bit
	#define 	PPCH		0x02		//Px中断优先级高位
	#define 	PT3H    	0x01		//定时3中断优先级高位

/*
******************************************************************************************************
*/
sfr 	SPCON  		= 0xBC;
	#define		SPEN 		0x80		//SPI Enable
	#define		MSTR 		0x40		//Master Mode Enable
	#define		CPOL 		0x20		//SPI Clock Polarity
	#define		CPHA 		0x10		//SPI Clock Phase
	
	#define		LSBF 		0x04		//LSB First. 0: MSB first, 1: LSB first
	//--------------------------------------------------------------------------------------------
	//SPCR:SPCON Bit[1:0],SPI Clock Rate. 0: FSYS/2, 1: FSYS/4, 2: FSYS/8, 3: FSYS/16

/*
******************************************************************************************************
*/
sfr 	SPSTA  		= 0xBD;
	#define		SPIF 		0x80		//SPI Interrupt Flag
	#define		WCOL 		0x40		//Write Collision Interrupt Flag
//	#define		MODF 		0x20		//Mode Fault Interrupt
	#define		RCVOVF 		0x10		//Receive Buffer Overrun Flag
	#define		RCVBF 		0x08		//Receive Buffer Full Flag
	#define		SPBSY 		0x04		//SPI Busy Flag


sfr 	SPDAT  		= 0xBE;

/*
******************************************************************************************************
*/
sfr 	LVDDT  		= 0xC4;

/*
******************************************************************************************************
*/
sfr 	DACDT  		= 0xC5;

/*
******************************************************************************************************
*/
sfr 	CMPCON  		= 0xC6;


/*
******************************************************************************************************
*/
sfr 	CMPPNS  		= 0xC7;

/*
******************************************************************************************************
*/

sfr 	T2CON  		= 0xC8;
	//--------------------------------------------------------------------------------------------
	sbit 		TF2  		  = T2CON^7;		//定时器T2溢出中断标志。TF2必须由用户程序清“0”。当T2作为串口波特率发生器时，TF2不会被置“1”。
	sbit 		EXF2    	= T2CON^6;		//外部中断2标志。EXEN2为1时，当T2EX（P1.1）发生负跳变时置1中断标志DXF2，EXF2必须由用户程序清“0”。
//	sbit 		RCLK    	= T2CON^5;		//Force 0
//	sbit 		TCLK 		  = T2CON^4;	//Force 0
	sbit 		EXEN2   	= T2CON^3;		//外部中断2充许标志。
	sbit 		TR2     	= T2CON^2;		//Timer2运行控制。0：Timer2停止，1：Timer2运行
	sbit 		CT2     	= T2CON^1;		//Timer2计数器/定时器选择位。C/T2=0时，为定时器模式。C/T2=1时，为计数器模式。
	sbit 		CT2N     	= T2CON^1;		//Timer2计数器/定时器选择位。C/T2=0时，为定时器模式。C/T2=1时，为计数器模式。
	sbit 		CPRL2   	= T2CON^0;		//捕捉和常数自动再装入方式选择位。为1时工作于捕捉方式，为0时T2工作于常数自动再装入方式。当TCLK或RCLK为1时，CP/RL2被忽略，T2总是工作于常数自动再装入方式。
	sbit 		CPRL2N   	= T2CON^0;		//捕捉和常数自动再装入方式选择位。为1时工作于捕捉方式，为0时T2工作于常数自动再装入方式。当TCLK或RCLK为1时，CP/RL2被忽略，T2总是工作于常数自动再装入方式。

/*
******************************************************************************************************
*/
sfr		IAPCON	= 0xC9;		
sfr		IAPWE_SFR	= 0xC9;
	//--------------------------------------------------------------------------------------------
	//IAPCON:IAPCON Bit[7:0],Write 47h or 74h to set IAPWE flag; Write 47h can write 1 byte at once, write 74h can write 2 bytes at once. Write other value to clear IAPWE flag. It is recommended to clear it immediately after IAP write.
							//Write A1h to set INFOWE flag; write other value to clear INFOWE flag. It is recommended to clear it immediately after IAP write.
							//Write E2h to set EEPWE flag; write other value to clear EEPWE flag. It is recommended to clear it immediately after EEPROM write.
							
	#define	IAPWE	0x80	//IAPWE Enable Flag
							
	#define	IAPTO	0x40	//Time-Out flag of IAP write/EEPROM write/INFO write. 
							//Set by H/W when IAP or EEPROM or INFO write Time-out occurs. Cleared this flag by H/W when IAPWE=0 or EEPWE=0 or INFOWE=0. 

	#define	EEPWE	0x20	//EEPWE Enable Flag	

	#define	INFOWE	0x10	//Flag indicates INFO memory can be written or not
							//0: INFO IAP Write disable
							//1: INFO IAP Write enable

/*
******************************************************************************************************
*/

sfr 	RCP2L  	 = 0xCA;				//外部输入（P1.1）计数器/自动再装入模式时初值寄存器低八位
sfr 	RCP2H  	 = 0xCB;				//外部输入（P1.1）计数器/自动再装入模式时初值寄存器高八位
/*
******************************************************************************************************
*/
sfr 	TL2   		= 0xCC;			  	//Timer2 data low byte
sfr 	TH2   		= 0xCD;			    //Timer2 data high byte

/*
******************************************************************************************************
*/
sfr 	PSW   		= 0xD0;
	//--------------------------------------------------------------------------------------------
	sbit 		CY 		= PSW^7;		//进位标志,有进或借位,CY＝1;无进或借位,CY＝0
	sbit 		AC 		= PSW^6;		//半进位标志
	sbit 		F0 		= PSW^5;		//用户可以随便使用
	sbit 		RS1 	= PSW^4;		//工作寄存器区选择[RS1:RS0]
	sbit 		RS0 	= PSW^3;		//00--0区,01--1区,10--2区,11--3区
	sbit 		OV 		= PSW^2;		//运算结果按补码运算,有溢出,OV=1;无溢出,OV＝0
	sbit 		F1 		= PSW^1;		//用户自定义标志
	sbit 		P 		= PSW^0;		//用来表示ALU运算结果中二进制数位1的个数的奇偶性,若为奇数,则P=1,否则为0
	
/*
******************************************************************************************************
*/
sfr 	PWM0DH		= 0xD1;
	//PWM0DH:PWM0DH Bit[7:0],PWM0 Duty 15~8

/*
******************************************************************************************************
*/
sfr 	PWM0DL		= 0xD2;
	//PWM0DL:PWM0DL Bit[7:0],PWM0 Duty 7~0

/*
******************************************************************************************************
*/
sfr 	PWM1D		= 0xD4;
	//PWM1DL:PWM1DL Bit[7:0],PWM1 Duty 7~0

/*
******************************************************************************************************
*/
sfr 	PWM2D		= 0xD6;
	//PWM2DL:PWM2DL Bit[7:0],PWM2 Duty 7~0

/*
******************************************************************************************************
*/
sfr		TM3RLD		= 0xD7;


/*
******************************************************************************************************
*/
sfr		CLKCON		= 0xD8;
	sbit 		SCKTYPE = CLKCON^7;		//慢时钟类型选择，Slow Clock Type. 1=SXT, 0=SRC
	//sbit 		FCKTYPE = CLKCON^6;		//Fast clock Type. 0=FRC, 1=FXT.
	sbit 		STPSCK  = CLKCON^5;		//Stop Slow Clock in STOP mode
	sbit 		STPPCK 	= CLKCON^4;		//1=进入IDL模式，Stop UART/Timer0/Timer1/Timer2 Clock in Idle mode
	sbit 		STPFCK 	= CLKCON^3;		//1=停止快时钟，0=快时钟工作
	sbit 		SELFCK 	= CLKCON^2;		//1=选择快时钟为系统时钟源，0=慢时钟为系统时钟源
	
	//CLKPSC:CLKCON Bit[1:0],系统时钟预分频，SYSCLK Prescaler, 0:div16, 1:div4, 2:div2, 3:div1
	sbit 		CLKPSC_H 	= CLKCON^1;	
	sbit 		CLKPSC_L	= CLKCON^0;	

/*
******************************************************************************************************
*/
sfr 	PWM0PRDH	= 0xD9;
	//PWM0PRDH:PWM0PRDH Bit[7:0],PWM0 Period 15~8

sfr 	PWM0PRDL	= 0xDA;
	//PWM0PRDL:PWM0PRDL Bit[7:0],PWM0 Period 7~0


sfr 	PWM1PRD	= 0xDC;
	//PWM1PRD:PWM1PRDH Bit[7:0],PWM1 Period 7~0


/*
******************************************************************************************************
*/
sfr 	PWM3D		= 0xDE;
	//PWM3D:PWM3D Bit[7:0],PWM3 Duty 7~0
	
/*
******************************************************************************************************
*/
sfr 	UARTBRP	= 0xDF;

	//UARTBRP:UART0CON Bit[7:0],Define UART0 Baud Rate Prescaler
								//UART0 Baud Rate = Fsys/32/UART0BRP	

/*
******************************************************************************************************
*/
sfr 	ACC   		= 0xE0;		//Accumulator

/*
******************************************************************************************************
*/
sfr 	MICON   	= 0xE1;
	//Master IIC Enable. 0: disable, 1: enable
	#define  	MIEN			0x80
	#define  	MIEN_DISABLE    MICON=(MICON&0x7f)
	#define  	MIEN_ENABLE    	MICON |= MIEN

	//"When Master IIC receive data, send acknowledge to IIC Bus
	//0: ACK to slave device
	//1: NACK to slave device"
	#define  	MIACKO			0x40
	#define  	MIACKO_ACK		MICON=(MICON&0xbf)
	#define  	MIACKO_NACK		MICON |= MIACKO
	
	//"Master IIC Interrupt Flag.
	//0: H/W write 0 to clear it
	//1: Master IIC transmit or receive one byte complete"
	#define  	MIIF			0x20
	
	//"When Master IIC transmission, acknowledgement from IIC Bus (read only)
	//0: ACK received
	//1: NACK received"
	#define  	MIACKI			0x10
	#define  	MIACKI_ACK		MICON=(MICON&0xef)
	#define  	MIACKI_NACK		MICON |= MIACKI
	
	//Master IIC Start Bit
	#define  	MISTART			0x08

	//Master IIC Stop Bit
	#define  	MISTOP			0x04

	//"Master IIC Clock Frequency Selection
	//00: Fsys/4
	//01: Fsys/16 
	//10: Fsys/64
	//11: Fsys/256"
	#define  	MICR_Mask		~0x03
	#define  	MICR_FsysDiv4	0x00
	#define  	MICR_FsysDiv16	0x01
	#define  	MICR_FsysDiv64	0x02
	#define  	MICR_FsysDiv256	0x03

//******************************************************************************************************
sfr		MIDAT	= 0xE2;		//Master I2C transmit/receive data
	//--------------------------------------------------------------------------------------------
	//MIDAT:MIDAT Bit[7:0],
	//Master I2C data shift register
	//(W): After Start and before Stop condition, write this register will resume transmission to I2C bus
	//(R): After Start and before Stop condition, read this register will resume receiving from I2C bus

//******************************************************************************************************
sfr		LVRCON	= 0xE3;

//	#define  	PORPD	0x20	//POR Power Down. 0: POR Enable, 1: POR Disable

	#define  	LVRPD	0x10	//LVR Power Down. 0: LVR Enable, 1: LVR Disable

	//--------------------------------------------------------------------------------------------
	//LVRSEL:LVRCON Bit[3:0],
	//LVR select :
	//16 level LVR select.   1111~0000:  4.33~2.11V  (1step = 0.14533333V)
	#define		LVRSEL_DISABLE	0x00
	#define		LVRSEL_1111		0x0F
	#define		LVRSEL_1110		0x0E
	#define		LVRSEL_1101		0x0D
	#define		LVRSEL_1100		0x0C
	#define		LVRSEL_1011		0x0B
	#define		LVRSEL_1010		0x0A
	#define		LVRSEL_1001		0x09
	#define		LVRSEL_1000		0x08
	#define		LVRSEL_0111		0x07
	#define		LVRSEL_0110		0x06
	#define		LVRSEL_0101		0x05
	#define		LVRSEL_0100		0x04
	#define		LVRSEL_0011		0x03
	#define		LVRSEL_0010		0x02
	#define		LVRSEL_0001		0x01
	
//******************************************************************************************************
sfr		LVDCON	= 0xE4;
	#define  	LVDM	0x80	//0: VCC < VLVD (LVDIF = 1 while LVDO = 1)
								//1: VCC > VLVD (LVDIF = 1 while LVDO = 0)

	#define  	LVDO	0x40	//LVD real-time Output
	
	#define  	LVDHYS	0x20	//LVD Hysteresis Enable. 0: LVD Hysteresis disable, 1: LVD Hysteresis enable
	
	#define  	LVDPD	0x10	//LVD Power Down. 0: LVD Enable, 1: LVD Disable
	
	//LVDSEL:LVDCON Bit[3:0],
	//15 level LVD select.   1111~0001:  
	#define	LVDSEL_0000	0x00	//	1.85V
	#define	LVDSEL_0001	0x01	//	2.00V
	#define	LVDSEL_0010	0x02	//	2.15V
	#define	LVDSEL_0011	0x03	//	2.30V
	#define	LVDSEL_0100	0x04	//	2.45V
	#define	LVDSEL_0101	0x05	//	2.60V
	#define	LVDSEL_0110	0x06	//	2.75V
	#define	LVDSEL_0111	0x07	//	2.90V
	#define	LVDSEL_1000	0x08	//	3.05V
	#define	LVDSEL_1001	0x09	//	3.20V
	#define	LVDSEL_1010	0x0a	//	3.35V
	#define	LVDSEL_1011	0x0b	//	3.50V
	#define	LVDSEL_1100	0x0c	//	3.65V
	#define	LVDSEL_1101	0x0d	//	4.80V
	#define	LVDSEL_1110	0x0e	//	3.95V
	#define	LVDSEL_1111	0x0f	//  4.10V

	#define	LVDSEL_000	0x00	//	1.85V
	#define	LVDSEL_001	0x01	//	2.00V
	#define	LVDSEL_002	0x02	//	2.15V
	#define	LVDSEL_003	0x03	//	2.30V
	#define	LVDSEL_004	0x04	//	2.45V
	#define	LVDSEL_005	0x05	//	2.60V
	#define	LVDSEL_006	0x06	//	2.75V
	#define	LVDSEL_007	0x07	//	2.90V
	#define	LVDSEL_008	0x08	//	3.05V
	#define	LVDSEL_009	0x09	//	3.20V
	#define	LVDSEL_010	0x0a	//	3.35V
	#define	LVDSEL_011	0x0b	//	3.50V
	#define	LVDSEL_012	0x0c	//	3.65V
	#define	LVDSEL_013	0x0d	//	3.80V
	#define	LVDSEL_014	0x0e	//	3.95V
	#define	LVDSEL_015	0x0f	//  4.10V


	
//******************************************************************************************************
sfr		PWM4D		= 0xEA;
	//PWM4D:PWM4D Bit[7:0],PWM4 Duty 7~0

	
//******************************************************************************************************
sfr		PWM5D		= 0xEC;
	//PWM5D:PWM5D Bit[7:0],PWM5 Duty 7~0

	
//******************************************************************************************************
sfr		PWM6D		= 0xEE;
	//PWM6D:PWM6D Bit[7:0],PWM6 Duty 7~0


//******************************************************************************************************
sfr		AUX3		= 0xEF;
	
	//PWM1PSC  Bit[7:5]	
						
						
	#define	PRGD		0x10
	

	#define	WARMTIME	0x08	//Warm-up time for wake-up from Power Down mode
								//0: 128 Clock
								//1: 64 Clock
	#define	DACVREFS	0x04

//******************************************************************************************************
sfr 	B   		= 0xF0;		//B register


sfr 	CFGBG   		= 0xF5;
	//--------------------------------------------------------------------------------------------
	//BGTRIM:CFGBG Bit[4:0],VBG trimming value for SW

sfr 	CFGWL   		= 0xF6;
	//--------------------------------------------------------------------------------------------
	//FRCTRIM:CFGWL Bit[6:0],FRC frequency adjustment
							//00h: lowest frequency 
							//7Fh: highest frequency 

	
/*
******************************************************************************************************
*/	
sfr 	AUX2		= 0xF7;
	//--------------------------------------------------------------------------------------------
	//WDTE:AUX2 Bit[7:6],WDT Control
	//#define 	WDT_EN		         	0xC0		
	//#define 	WDT_ENFS_DISILDE		0x80		
	//#define 	WDT_DIS         		0x00		
	
	#define  	WDT_IS_OPEN                         AUX2=(AUX2&0x3f)|0xC0	//11：WDT Always Enable
	#define   	WDT_RUN_FAST_DIS_ILDE               AUX2=(AUX2&0x3f)|0x80	//10: WDT Enable in Fast/Slow, Disable in Idle/Stop mode
	#define  	WDT_IS_STOP                         AUX2=AUX2&0x3f  		//0X: WDT Disable

	#define		PWRSAV		0x20	//1: LVR/LVD disable at PD/IDLE,  0: LVR/LVD enable at PD/IDLE
	#define		PDOWN_LVD_ENABLE	AUX2=(AUX2&0xdf)
	#define		PDOWN_LVD_DISABLE	AUX2=(AUX2&0xdf)|PWRSAV
	
	#define		VBGOUT		0x10	//1: VBG output to P3.2,   0: P32 as normal IO
	#define		VBG_OUTPUT	AUX2=(AUX2&0xef)|VBGOUT
	#define		VBG_NORMAL	AUX2=(AUX2&0xef)

	
	//"0: 16/16 division operation
	//1: 32/16 division operation"
//	#define		DIV32		0x08
//	#define		DIV32_16	AUX2=(AUX2&0xf7)
//	#define		DIV32_32	AUX2=(AUX2&0xf7)|DIV32
	
	//
	//IAPTE:AUX2 Bit[2:1],IAP  (or EEPROM write) timeout enable  00:Disable  01: 1.6mS   10:  3.2mS  11:  12.8mS
	#define		IAPTE_2_MS		AUX2=(AUX2&0xf9)|0x02
	#define		IAPTE_4_MS		AUX2=(AUX2&0xf9)|0x04
	#define		IAPTE_16_MS		AUX2=(AUX2&0xf9)|0x06
	#define		IAPTE_DISABLE	AUX2=(AUX2&0xf9)
	
	
/*
******************************************************************************************************
*/	
sfr 	AUX1   		= 0xF8;
	//--------------------------------------------------------------------------------------------
    sbit 		CLRWDT		= AUX1^7;	//Clear WatchDog, HW auto clear
    #define     CLR_WDT		CLRWDT=1	//设置以清除看门狗定时器,H/W自动在一个时钟周期清除它     	
	sbit 		CLRTM3		= AUX1^6;//清零TM3也是启动TM3

    sbit 		ADSOC		= AUX1^4;//ADC开始，结束时硬件自动清零
    sbit 		CLRPWM0		= AUX1^3;//Clear PWM0
    sbit 		CLRPWM1		= AUX1^2;//Clear PWM1
    sbit 		WGEN		= AUX1^1;//

    sbit 		DPSEL		= AUX1^0;//0表选择DPTR;1表选择DPTR1

/*
******************************************************************************************************
*/	
sfr 	ICECON 		= 0xF9;		//ICE Mode
sfr 	ICECTRL 	= 0xF9;		//ICE Mode
	#define 	HWBRK		      0x80		//H/W Break
	#define 	RETROREQ          0x40		//Retro-OPCode Request flag; = ~BRK_N
											//HW auto set at SWBRK, HW auto clear at NMI_service return
	#define 	TXRDY		      0x20		//Transmitt Ready, HW auto clear.
	#define 	CMDRDY	          0x10		//Command ready, HW auto clear.
	#define 	XFIRCK	          0x08		//Swich to FIRC 4MHZ
	//#define 	WRFAIL	          0x01		//EEPROM Write Fail
/*
******************************************************************************************************
*/	
sfr 	RETROCODE 	= 0xFA;	//ICE Mode Retro-OPCode
/*
******************************************************************************************************
*/	
sfr 	ICERCD 		= 0xFB;	//ICE Mode Receive Data
/*
******************************************************************************************************
*/	
sfr 	ICECMDL		= 0xFC;	//ICE Mode Command Low Byte
/*
******************************************************************************************************
*/	
sfr 	ICECMDH		= 0xFD;	//ICE Mode Command High Byte
	//ICECMDH:ICECMDH Bit[3:0],
/*
******************************************************************************************************
*/	
sfr 	ICETXD		= 0xFE;	//ICE Mode Transmit Data
/*
******************************************************************************************************
*/	
sfr 	INDSFR		= 0xFF;	//SFR direct Adr replaced by ICECMDL in NMI "mov dir,a" & "mov a,dir"
/*
******************************************************************************************************
*/	

#define	 All_Interrupt_Enable()		EA = 1		//全局中断使能
#define	 All_Interrupt_Disable()	EA = 0		//全局中断关闭
/*
******************************************************************************************************
*/
#define	 PowerDown()			PCON = PCON | PD	//进入掉电模式
#define	 PowerIdel()			PCON = PCON | IDL	//进入IDEL模式
/*
******************************************************************************************************
*/


#endif
/*
******************************************************************************************************
*/
