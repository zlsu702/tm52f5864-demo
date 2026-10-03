//=============================================================================
//Name		:SysInit.h
//Purpose	:函数、变量外部声明
//Version	:V1.0
//Author	:szl
//Date		:2015.05.26
//=============================================================================
#ifndef __SYSINIT_H__
#define	__SYSINIT_H__
//=============================================================================
extern void InitDevice(void);
extern void InitData(void);
extern void SysClk_Init(void);
//extern void SetFastClk(void);
//extern void SetSlowClk(void);
extern void IO_Init(void);
//extern void Int_Enable(void);
//extern void Int_Disable(void);
extern void TM0_Init(void);
extern void TM0_Enable(void);
extern void TM0_Disable(void);
extern void TM1_Init(void);
extern void TM1_Enable(void);
extern void TM1_Disable(void);
//extern void TM2_Init(void);
//extern void uart1_timer2_init();
//extern void TM2_Disable(void);
extern void TM3_Init(void);
//extern void TM3_Disable(void);
//extern void TM3_Enable(void);
extern void PWM_Init(void);
extern void PWM_ALL_Off(void);
extern void PWM_On(void);
extern void PWM_Off(void);
extern void T2O_On(void);
extern void T2O_Off(void);
extern void ADC_Init(void);
extern u16 ADC_Convert( uchar Adc_ch );
extern u8 ADC_Convert1( uchar Adc_ch );
//=============================================================================
#endif
//=============================================================================
