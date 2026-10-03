/*scankey.h*/
#ifndef _SCANKEY_H_
#define _SCANKEY_H_

#define KEY1_ADC_VOL	11
#define KEY2_ADC_VOL	34
#define KEY3_ADC_VOL	59
#define KEY4_ADC_VOL	83
#define KEY5_ADC_VOL	103
#define KEY6_ADC_VOL	130

//KeyCode
#define NONE_KEY 	0x00
#define	KEY_ALARM	5
#define	KEY_DOWN	4
#define	KEY_UP		3
#define	KEY_SET		2
#define	KEY_LIGHT	1

#define	KEY_HLIGHT	6
#define	KEY_HSET	7
#define	KEY_HUP		8
#define	KEY_HDOWN	9
#define	KEY_HALARM	10


//DebounceCnt
#define DFirstKeyDL 	1		//Ïû¶¶5/128ms

//KeyState
#define KST_MAST	0x1F
#define KST_DEBOUNCE	0x01
#define KST_RELEASE	0x02
#define KST_MULT	0x04
#define KST_HOLD	0x08
#define KST_WAIT	0x10
#define KST_MULTKEY	0x40


extern xdata uchar KeyState;
extern xdata uchar DebounceCnt;
extern xdata uchar KeyCode;

extern void Scankey(void);
extern void PollingKey(void);

#endif