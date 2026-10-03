//=============================================================================
//Name		:rf433.h
//Purpose	:函数、变量外部声明
//Version	:V1.0
//Author	:
//Date		:2021.10.27
//=============================================================================
#ifndef _RF_C_
#define _RF_C_
//=============================================================================
//RfState

#define	KEY_IR_POWER	0x01
#define	KEY_IR_AL1SET	0x00
#define	KEY_IR_AL2SET	0x02

#define	KEY_IR_AL1ON	0x04
#define	KEY_IR_SET	0x05
#define	KEY_IR_AL2ON	0x06

#define	KEY_IR_DOWN	0x08
#define	KEY_IR_OK	0x09
#define	KEY_IR_UP	0x0a

#define	KEY_IR_COUNT	0x0c
#define	KEY_IR_TEMP	0x0d
#define	KEY_IR_DST	0x0e

#define	KEY_IR_DIMMER	0x10
#define	KEY_IR_AUTO	0x11
#define	KEY_IR_12_24	0x12

#define	KEY_IR_LI_LV	0x14
#define	KEY_IR_LIGHT	0x15
#define	KEY_IR_LI_COLOR	0x16

#define	KEY_IR_VOL_D	0x18
#define	KEY_IR_MUTE	0x19
#define	KEY_IR_VOL_U	0x1A

//IrKeyState
#define	D_IrWaitKey	0x01
#define	D_IrHoldKey	0x02
#define	D_IrMultKey	0x04


extern idata uchar IrKeyState;
extern idata uchar IrState;
extern idata uchar IrByteCnt;
extern idata uchar IrBitCnt;
extern idata ulong IrData;
extern idata ulong IrDataBuf;
extern idata uchar IrHoldTime;
extern idata uchar IrReleaseTime;
extern idata uchar IrOldKey;
extern idata uchar IrKeyCode;

//=============================================================================
/*外部函数声明*/
//=============================================================================
void CheckReceiveData(void);
void ReceiveDecode(void);
void CheckReleaseIrHold(void);
void TurnIrOn(void); 
void TurnIrOff(void); 
//=============================================================================
#endif
//=============================================================================