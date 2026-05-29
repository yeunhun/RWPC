/***********************************************************************************************************************
* File Name    : 10W_WPC_PWMControl.h
* Description  : PWM Control
***********************************************************************************************************************/

#ifndef WPC_PWMCONTROL_H_
#define WPC_PWMCONTROL_H_

/********************************************************************************
* Defines
********************************************************************************/


/********************************************************************************
* Global Variables
********************************************************************************/

/********************************************************************************
* Modules
********************************************************************************/
extern uint8 GetDuty_Que(void);
//extern uint16 GetDuty_Que_AutoBright(void);
extern uint16 GetDuty_Que_GreenAutoBright(void);
extern uint16 GetDuty_Que_AmberAutoBright(void);
extern uint16 GetDutyCycle(uint16 dutyRate);
extern uint16 GetDutyCycle_AutoBright(uint16 dutyRate);
extern void Pwm_IND_Start(uint8 channel, uint16 dutycycle);
extern void Pwm_IND_Stop(uint8 channel);
extern void Change_PWM_IND_DutyCycle(uint16 dutycycle, uint8 channel);
extern void Pwm_FAN_Start(uint16 dutycycle);
extern void Pwm_FAN_Stop(void);
extern void Change_PWM_FAN_DutyCycle(uint16 dutycycle);
extern void IPS_Control(uint16 enable);

#endif /* 10W_WPC_PWMControl_H_ */
