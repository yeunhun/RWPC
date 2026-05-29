/*******************************************************************************
 * Project      	: 	SP2 IBU
 * File Name    	: 	timer.h
 * Compiler		: 	Eclipse
 * Author       	: 	MyoungKwon Choi (mk210@seoyonelec.com)
 * Created at   	: 	2017-06-15 
 * Code Editor	: 	Source Insight (Recomended Font : D2Coding / Size 10)
 * Revision     	: 	Version 0.1
 * Copyright   	: 	(c) Copyright Seoyon Electronisc Co.Ltd. All Rights Reserved       
 * Description  	: 	This is a header file associated with a timer.
 *
 *******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------*/
#ifndef	__TIMER_H__
#define	__TIMER_H__


/*******************************************************************************
	Define Constants
*******************************************************************************/
#define	running					1u
#define	Frozen					2u


/*******************************************************************************
	Define Macro
*******************************************************************************/
/* timer ----------------------------------------------------------------------------------*/
#define	StartTimer(tmr)			{(tmr).run = 1u;	(tmr).time = 0u;}
#define	CancelTimer(tmr)		{(tmr).run = 0u;	(tmr).time = 0u;}
#define	UnfreezeTimer(tmr)		{(tmr).run = 1u;}
#define	FreezeTimer(tmr)		{(tmr).run = 2u;}

/* 8bit timer : 0 ~ 2s ---------------------------------------------------------------------*/
#define	UpTimer8(tmr)			if( ((tmr).run==1u) && ((tmr).time<(u8)255) ){(tmr).time++;}

/*16bit timer : 0 ~ 10min  -----------------------------------------------------------------*/
#define	UpTimer16(tmr)			if(	((tmr).run==1u) &&	((tmr).time<(u16)65535) ){(tmr).time++;}

/* 32bit timer : 0 ~ 497day ----------------------------------------------------------------*/
#define	UpTimer32(tmr)			if(	((tmr).run==1u) && ((tmr).time<(u32)0xFFFFFFFFu) ){(tmr).time++;}

#endif	/* __TIMER_H__ */
