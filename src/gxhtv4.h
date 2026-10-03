/**************************************************************************************************
  Filename:       gxhtv4.h
  Revised:        $Date: 2010-08-01 14:03:16 -0700 (Sun, 01 Aug 2010) $
  Revision:       $Revision: 23256 $
**************************************************************************************************/

#ifndef _GXHTV4_H_
#define _GXHTV4_H_

//*********************************************************************
//TempFlag
#define	 D_ReadyFlag	0x01
#define	 D_TempWait	0x02
#define	 D_SensorDis	0x80

#define	TEMP_ERR	0xF0
#define	TEMP_HIGH	0xE0
#define	TEMP_LOW	0xD0

/*********************************************************************
 * VARIABLES
 */  
extern xdata uchar TempFlag;    
extern xdata uchar TempCyc;
extern xdata uchar TempNum[2];
extern xdata uchar HumiNum;
/*********************************************************************
 * FUNCTIONS
 */
void Gxhtv4PowerOn( void );  
void Gxhtv4PowerOff(void);
void Gxhtv4CheckOn(void);
void CheckReadyRFC(void);
void ReadyRFC(void);
void Gxhtv4Server(void);
//void ResetAdjActive(void);

/*********************************************************************
*********************************************************************/

#endif 
