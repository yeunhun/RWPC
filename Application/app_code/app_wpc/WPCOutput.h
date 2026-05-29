/*
 * DN8_WPC_Output.h
 *
 *  Created on: 2017. 9. 15.
 *      Author: Seoyon
 */

#ifndef WPC_OUTPUT_H_
#define WPC_OUTPUT_H_

enum e_OutputList
{

// Indicator Local Output
	IO_Amber_OUT,
	IO_Green_OUT,
	IO_Fan_OUT,
	kMaxOutput
};

typedef struct
{
	u8	service_id;	/* diagnostic service ID */
	u8	index;		/* number of output */
	u8	status;		/* IOCBI status */
	u8	repeat_cnt;	/* 0=infinite, 1~255=repeat count */
	u8	initiated;	/* initiated ? */
	u16	on_time;	/* on time --> smaller then period */
	u16	off_time;	/* on time --> smaller then period */
} tFD_Condition_WPC;

//#define kMaxOutput  30u
extern uint8 u8_OutputValue[kMaxOutput];
extern tFD_Condition_WPC tbl_ForcedDrive_WPC[7];

void Output_Processing(void);
void AmberLED_Output_IOCBI(void);
void GreenLED_Output_IOCBI(void);
void FAN_Output_IOCBI(void);
void AmberLED_Output_ChangeDuty(void);
void GreenLED_Output_ChangeDuty(void);
void FAN_Output_ChangeDuty(void);


#endif /* 10W_WPC_OUTPUT_H_ */
