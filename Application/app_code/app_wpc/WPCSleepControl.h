/***********************************************************************************************************************
* File Name    : 10W_WPC_Sleep.h
* Description  : Sleep Control
***********************************************************************************************************************/

#ifndef WPC_SLEEP_CONTROL_H_
#define WPC_SLEEP_CONTROL_H_

/********************************************************************************
* Defines
********************************************************************************/
enum e_CAN_Status
{
    eN_CAN_Normal = 1u,
    eN_CAN_Node_Sleep,
    eN_CAN_NetWork_Sleep
};

#define WPC_SLEEP_LP_FLAG   0
#define WPC_BCAN_LP_FLAG    1
#define WPC_LCAN_LP_FLAG    2
#define WPC_CAN_LP_FLAG     3
#define MAX_SLEEP_FLAG      4

/********************************************************************************
* Global Variables
********************************************************************************/
extern uint8 u8_Sleep_Flag[MAX_SLEEP_FLAG];
extern uint8 fWakeUpInput_BCAN;
extern uint8 fWakeUpInput_LCAN;
extern uint8 f_CANStatus;

extern tTimer16 Timer_SleepWaitVoltage;
extern tTimer16 Timer_SleepWait;
/********************************************************************************
* Modules
********************************************************************************/
extern void Func_Enter_Sleep_Check_WPC(void);
extern void Func_Enter_Sleep_Check_CAN(void);
extern void WPC_SleepMode_Control(void);
extern void SleepModeProcessing(void);
extern void LowPower_Allow(u8 lub_ID);
extern void LowPower_Prevent(u8 lub_ID);


#endif /* 10W_WPC_Sleep_H_ */
