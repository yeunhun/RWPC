/***********************************************************************************************************************
* File Name    : 10W_WPC_PWMControl.c
* Description  : PWM Control
***********************************************************************************************************************/





/*******************************************************************************
  Include Headers
*******************************************************************************/
#include "WPCVehicleOption.h"
#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"
#include "Rte_SWC_output.h"

#include "app_output_type.h"
#include "app_output.h"
#include "app_input_type.h"
#include "app_input.h"
#include "app_can_input_type.h"
#include "app_can_input.h"


/*******************************************************************************
  Declare Function Prototypes
*******************************************************************************/
uint8 GetDuty_Que(void);
//uint16 GetDuty_Que_AutoBright(void);
uint16 GetDuty_Que_GreenAutoBright(void);
uint16 GetDuty_Que_AmberAutoBright(void);
uint16 GetDutyCycle(uint16 dutyRate);
uint16 GetDutyCycle_AutoBright(uint16 dutyRate);
void Pwm_IND_Start(uint8 channel, uint16 dutycycle);
void Pwm_IND_Stop(uint8 channel);
void Change_PWM_IND_DutyCycle(uint16 dutycycle, uint8 channel);
void Pwm_FAN_Start(uint16 dutycycle);
void Pwm_FAN_Stop(void);
void Change_PWM_FAN_DutyCycle(uint16 dutycycle);
void IPS_Control(uint16 enable);


/*******************************************************************************
  Define Constant and Macro
*******************************************************************************/
#define VN7140AS_IN_WriteDirect(val)           Rte_Call_R_DigDir_VN7140AS_IN_WriteDirect(val)
#define VN7140AS_SEN_WriteDirect(val)          Rte_Call_R_DigDir_VN7140AS_SEN_WriteDirect(val)



/********************************************************************************
* Modules
********************************************************************************/
#if defined (USE_AUTOBRIGHT)
/* TYPE2 Animation GreenAutoBright GetDuty */
uint16 GetDuty_Que_GreenAutoBright(void)
{
  u16 dutyRate = Par_GreenAutoBrightLevel013;  /*8.83%*/

  if(GetX(kC_CLU_AutoBrightSta) == 2u)  {dutyRate = Par_GreenAutoBrightLevel002;}    //1.00%
  if(GetX(kC_CLU_AutoBrightSta) == 3u)  {dutyRate = Par_GreenAutoBrightLevel003;}    //1.17%
  if(GetX(kC_CLU_AutoBrightSta) == 4u)  {dutyRate = Par_GreenAutoBrightLevel004;}    //2.42%
  if(GetX(kC_CLU_AutoBrightSta) == 5u)  {dutyRate = Par_GreenAutoBrightLevel005;}    //3.14%
  if(GetX(kC_CLU_AutoBrightSta) == 6u)  {dutyRate = Par_GreenAutoBrightLevel006;}    //3.85%
  if(GetX(kC_CLU_AutoBrightSta) == 7u)  {dutyRate = Par_GreenAutoBrightLevel007;}    //4.56%
  if(GetX(kC_CLU_AutoBrightSta) == 8u)  {dutyRate = Par_GreenAutoBrightLevel008;}    //5.72%
  if(GetX(kC_CLU_AutoBrightSta) == 9u)  {dutyRate = Par_GreenAutoBrightLevel009;}    //5.98%
  if(GetX(kC_CLU_AutoBrightSta) == 10u) {dutyRate = Par_GreenAutoBrightLevel010;}    //6.70%
  if(GetX(kC_CLU_AutoBrightSta) == 11u) {dutyRate = Par_GreenAutoBrightLevel011;}    //7.41%
  if(GetX(kC_CLU_AutoBrightSta) == 12u) {dutyRate = Par_GreenAutoBrightLevel012;}    //8.12%
  if(GetX(kC_CLU_AutoBrightSta) == 13u) {dutyRate = Par_GreenAutoBrightLevel013;}    //8.83%
  if(GetX(kC_CLU_AutoBrightSta) == 14u) {dutyRate = Par_GreenAutoBrightLevel014;}    //9.55%
  if(GetX(kC_CLU_AutoBrightSta) == 15u) {dutyRate = Par_GreenAutoBrightLevel015;}    //10.26%
  if(GetX(kC_CLU_AutoBrightSta) == 16u) {dutyRate = Par_GreenAutoBrightLevel016;}    //10.97%
  if(GetX(kC_CLU_AutoBrightSta) == 17u) {dutyRate = Par_GreenAutoBrightLevel017;}    //11.68%
  if(GetX(kC_CLU_AutoBrightSta) == 18u) {dutyRate = Par_GreenAutoBrightLevel018;}    //12.39%
  if(GetX(kC_CLU_AutoBrightSta) == 19u) {dutyRate = Par_GreenAutoBrightLevel019;}    //13.56%
  if(GetX(kC_CLU_AutoBrightSta) == 20u) {dutyRate = Par_GreenAutoBrightLevel020;}    //13.82%
  if(GetX(kC_CLU_AutoBrightSta) == 21u) {dutyRate = Par_GreenAutoBrightLevel021;}    //14.53%
  if(GetX(kC_CLU_AutoBrightSta) == 22u)  {dutyRate = Par_GreenAutoBrightLevel022;}   //15.24%
  if(GetX(kC_CLU_AutoBrightSta) == 23u)  {dutyRate = Par_GreenAutoBrightLevel023;}   //15.95%
  if(GetX(kC_CLU_AutoBrightSta) == 24u)  {dutyRate = Par_GreenAutoBrightLevel024;}   //16.67%
  if(GetX(kC_CLU_AutoBrightSta) == 25u)  {dutyRate = Par_GreenAutoBrightLevel025;}   //16.92%
  if(GetX(kC_CLU_AutoBrightSta) == 26u)  {dutyRate = Par_GreenAutoBrightLevel026;}   //17.17%
  if(GetX(kC_CLU_AutoBrightSta) == 27u)  {dutyRate = Par_GreenAutoBrightLevel027;}   //17.42%
  if(GetX(kC_CLU_AutoBrightSta) == 28u)  {dutyRate = Par_GreenAutoBrightLevel028;}   //17.68%
  if(GetX(kC_CLU_AutoBrightSta) == 29u)  {dutyRate = Par_GreenAutoBrightLevel029;}   //17.93%
  if(GetX(kC_CLU_AutoBrightSta) == 30u)  {dutyRate = Par_GreenAutoBrightLevel030;}   //18.18%
  if(GetX(kC_CLU_AutoBrightSta) == 31u) {dutyRate = Par_GreenAutoBrightLevel031;}    //18.43%
  if(GetX(kC_CLU_AutoBrightSta) == 32u) {dutyRate = Par_GreenAutoBrightLevel032;}    //18.69%
  if(GetX(kC_CLU_AutoBrightSta) == 33u) {dutyRate = Par_GreenAutoBrightLevel033;}    //18.94%
  if(GetX(kC_CLU_AutoBrightSta) == 34u) {dutyRate = Par_GreenAutoBrightLevel034;}    //19.19%
  if(GetX(kC_CLU_AutoBrightSta) == 35u) {dutyRate = Par_GreenAutoBrightLevel035;}    //19.44%
  if(GetX(kC_CLU_AutoBrightSta) == 36u) {dutyRate = Par_GreenAutoBrightLevel036;}    //19.70%
  if(GetX(kC_CLU_AutoBrightSta) == 37u) {dutyRate = Par_GreenAutoBrightLevel037;}    //19.95%
  if(GetX(kC_CLU_AutoBrightSta) == 38u) {dutyRate = Par_GreenAutoBrightLevel038;}    //20.20%
  if(GetX(kC_CLU_AutoBrightSta) == 39u) {dutyRate = Par_GreenAutoBrightLevel039;}    //20.45%
  if(GetX(kC_CLU_AutoBrightSta) == 40u) {dutyRate = Par_GreenAutoBrightLevel040;}    //20.71%
  if(GetX(kC_CLU_AutoBrightSta) == 41u) {dutyRate = Par_GreenAutoBrightLevel041;}    //20.96%
  if(GetX(kC_CLU_AutoBrightSta) == 42u) {dutyRate = Par_GreenAutoBrightLevel042;}    //21.21%
  if(GetX(kC_CLU_AutoBrightSta) == 43u)  {dutyRate = Par_GreenAutoBrightLevel043;}   //21.46%
  if(GetX(kC_CLU_AutoBrightSta) == 44u)  {dutyRate = Par_GreenAutoBrightLevel044;}   //21.72%
  if(GetX(kC_CLU_AutoBrightSta) == 45u)  {dutyRate = Par_GreenAutoBrightLevel045;}   //21.97%
  if(GetX(kC_CLU_AutoBrightSta) == 46u)  {dutyRate = Par_GreenAutoBrightLevel046;}   //22.22%
  if(GetX(kC_CLU_AutoBrightSta) == 47u)  {dutyRate = Par_GreenAutoBrightLevel047;}   //22.47%
  if(GetX(kC_CLU_AutoBrightSta) == 48u)  {dutyRate = Par_GreenAutoBrightLevel048;}   //22.73%
  if(GetX(kC_CLU_AutoBrightSta) == 49u)  {dutyRate = Par_GreenAutoBrightLevel049;}   //22.98%
  if(GetX(kC_CLU_AutoBrightSta) == 50u)  {dutyRate = Par_GreenAutoBrightLevel050;}   //23.23%
  if(GetX(kC_CLU_AutoBrightSta) == 51u)  {dutyRate = Par_GreenAutoBrightLevel051;}   //23.48%
  if(GetX(kC_CLU_AutoBrightSta) == 52u) {dutyRate = Par_GreenAutoBrightLevel052;}    //23.74%
  if(GetX(kC_CLU_AutoBrightSta) == 53u) {dutyRate = Par_GreenAutoBrightLevel053;}    //23.99%
  if(GetX(kC_CLU_AutoBrightSta) == 54u) {dutyRate = Par_GreenAutoBrightLevel054;}    //24.24%
  if(GetX(kC_CLU_AutoBrightSta) == 55u) {dutyRate = Par_GreenAutoBrightLevel055;}    //24.49%
  if(GetX(kC_CLU_AutoBrightSta) == 56u) {dutyRate = Par_GreenAutoBrightLevel056;}    //24.75%
  if(GetX(kC_CLU_AutoBrightSta) == 57u) {dutyRate = Par_GreenAutoBrightLevel057;}    //25.00%
  if(GetX(kC_CLU_AutoBrightSta) == 58u) {dutyRate = Par_GreenAutoBrightLevel058;}    //25.25%
  if(GetX(kC_CLU_AutoBrightSta) == 59u) {dutyRate = Par_GreenAutoBrightLevel059;}    //25.51%
  if(GetX(kC_CLU_AutoBrightSta) == 60u) {dutyRate = Par_GreenAutoBrightLevel060;}    //25.76%
  if(GetX(kC_CLU_AutoBrightSta) == 61u) {dutyRate = Par_GreenAutoBrightLevel061;}    //26.01%
  if(GetX(kC_CLU_AutoBrightSta) == 62u) {dutyRate = Par_GreenAutoBrightLevel062;}    //26.26%
  if(GetX(kC_CLU_AutoBrightSta) == 63u) {dutyRate = Par_GreenAutoBrightLevel063;}    //26.52%
  if(GetX(kC_CLU_AutoBrightSta) == 64u)  {dutyRate = Par_GreenAutoBrightLevel064;}   //26.77%
  if(GetX(kC_CLU_AutoBrightSta) == 65u)  {dutyRate = Par_GreenAutoBrightLevel065;}   //27.02%
  if(GetX(kC_CLU_AutoBrightSta) == 66u)  {dutyRate = Par_GreenAutoBrightLevel066;}   //27.27%
  if(GetX(kC_CLU_AutoBrightSta) == 67u)  {dutyRate = Par_GreenAutoBrightLevel067;}   //27.53%
  if(GetX(kC_CLU_AutoBrightSta) == 68u)  {dutyRate = Par_GreenAutoBrightLevel068;}   //28.78%
  if(GetX(kC_CLU_AutoBrightSta) == 69u)  {dutyRate = Par_GreenAutoBrightLevel069;}   //28.03%
  if(GetX(kC_CLU_AutoBrightSta) == 70u)  {dutyRate = Par_GreenAutoBrightLevel070;}   //28.28%
  if(GetX(kC_CLU_AutoBrightSta) == 71u)  {dutyRate = Par_GreenAutoBrightLevel071;}   //28.54%
  if(GetX(kC_CLU_AutoBrightSta) == 72u)  {dutyRate = Par_GreenAutoBrightLevel072;}   //28.79%
  if(GetX(kC_CLU_AutoBrightSta) == 73u) {dutyRate = Par_GreenAutoBrightLevel073;}    //29.04%
  if(GetX(kC_CLU_AutoBrightSta) == 74u) {dutyRate = Par_GreenAutoBrightLevel074;}    //29.29%
  if(GetX(kC_CLU_AutoBrightSta) == 75u) {dutyRate = Par_GreenAutoBrightLevel075;}    //29.55%
  if(GetX(kC_CLU_AutoBrightSta) == 76u) {dutyRate = Par_GreenAutoBrightLevel076;}    //30.80%
  if(GetX(kC_CLU_AutoBrightSta) == 77u) {dutyRate = Par_GreenAutoBrightLevel077;}    //30.05%
  if(GetX(kC_CLU_AutoBrightSta) == 78u) {dutyRate = Par_GreenAutoBrightLevel078;}    //30.30%
  if(GetX(kC_CLU_AutoBrightSta) == 79u) {dutyRate = Par_GreenAutoBrightLevel079;}    //30.56%
  if(GetX(kC_CLU_AutoBrightSta) == 80u) {dutyRate = Par_GreenAutoBrightLevel080;}    //30.81%
  if(GetX(kC_CLU_AutoBrightSta) == 81u) {dutyRate = Par_GreenAutoBrightLevel081;}    //31.06%
  if(GetX(kC_CLU_AutoBrightSta) == 82u) {dutyRate = Par_GreenAutoBrightLevel082;}    //31.31%
  if(GetX(kC_CLU_AutoBrightSta) == 83u) {dutyRate = Par_GreenAutoBrightLevel083;}    //31.57%
  if(GetX(kC_CLU_AutoBrightSta) == 84u) {dutyRate = Par_GreenAutoBrightLevel084;}    //31.82%
  if(GetX(kC_CLU_AutoBrightSta) == 85u) {dutyRate = Par_GreenAutoBrightLevel085;}    //32.07%
  if(GetX(kC_CLU_AutoBrightSta) == 86u) {dutyRate = Par_GreenAutoBrightLevel086;}    //32.32%
  if(GetX(kC_CLU_AutoBrightSta) == 87u) {dutyRate = Par_GreenAutoBrightLevel087;}    //32.58%
  if(GetX(kC_CLU_AutoBrightSta) == 88u) {dutyRate = Par_GreenAutoBrightLevel088;}    //32.83%
  if(GetX(kC_CLU_AutoBrightSta) == 89u) {dutyRate = Par_GreenAutoBrightLevel089;}    //33.08%
  if(GetX(kC_CLU_AutoBrightSta) == 90u) {dutyRate = Par_GreenAutoBrightLevel090;}    //33.33%
  if(GetX(kC_CLU_AutoBrightSta) == 91u) {dutyRate = Par_GreenAutoBrightLevel091;}    //100.00%
  //if(GetX(kC_CLU_AutoBrightSta) >= 92u) {dutyRate = Par_AmberAutoBrightLevelMax;}    //100.00%
  if(GetX(kC_CLU_AutoBrightSta) >= 92u) 
  {
  	dutyRate = Par_GreenAutoBrightLevelMax;
	SetX(kC_CLU_AutoBrightSta, 92u);
  }    //100.00%

  return dutyRate;
}
/* TYPE2 Animation AmberAutoBright GetDuty */
uint16 GetDuty_Que_AmberAutoBright(void)
{
  u16 dutyRate = Par_AmberAutoBrightLevel013;  /*8.83%*/

  if(GetX(kC_CLU_AutoBrightSta) == 2u)  {dutyRate = Par_AmberAutoBrightLevel002;}    //1.00%
  if(GetX(kC_CLU_AutoBrightSta) == 3u)  {dutyRate = Par_AmberAutoBrightLevel003;}    //1.17%
  if(GetX(kC_CLU_AutoBrightSta) == 4u)  {dutyRate = Par_AmberAutoBrightLevel004;}    //2.42%
  if(GetX(kC_CLU_AutoBrightSta) == 5u)  {dutyRate = Par_AmberAutoBrightLevel005;}    //3.14%
  if(GetX(kC_CLU_AutoBrightSta) == 6u)  {dutyRate = Par_AmberAutoBrightLevel006;}    //3.85%
  if(GetX(kC_CLU_AutoBrightSta) == 7u)  {dutyRate = Par_AmberAutoBrightLevel007;}    //4.56%
  if(GetX(kC_CLU_AutoBrightSta) == 8u)  {dutyRate = Par_AmberAutoBrightLevel008;}    //5.72%
  if(GetX(kC_CLU_AutoBrightSta) == 9u)  {dutyRate = Par_AmberAutoBrightLevel009;}    //5.98%
  if(GetX(kC_CLU_AutoBrightSta) == 10u) {dutyRate = Par_AmberAutoBrightLevel010;}    //6.70%
  if(GetX(kC_CLU_AutoBrightSta) == 11u) {dutyRate = Par_AmberAutoBrightLevel011;}    //7.41%
  if(GetX(kC_CLU_AutoBrightSta) == 12u) {dutyRate = Par_AmberAutoBrightLevel012;}    //8.12%
  if(GetX(kC_CLU_AutoBrightSta) == 13u) {dutyRate = Par_AmberAutoBrightLevel013;}    //8.83%
  if(GetX(kC_CLU_AutoBrightSta) == 14u) {dutyRate = Par_AmberAutoBrightLevel014;}    //9.55%
  if(GetX(kC_CLU_AutoBrightSta) == 15u) {dutyRate = Par_AmberAutoBrightLevel015;}    //10.26%
  if(GetX(kC_CLU_AutoBrightSta) == 16u) {dutyRate = Par_AmberAutoBrightLevel016;}    //10.97%
  if(GetX(kC_CLU_AutoBrightSta) == 17u) {dutyRate = Par_AmberAutoBrightLevel017;}    //11.68%
  if(GetX(kC_CLU_AutoBrightSta) == 18u) {dutyRate = Par_AmberAutoBrightLevel018;}    //12.39%
  if(GetX(kC_CLU_AutoBrightSta) == 19u) {dutyRate = Par_AmberAutoBrightLevel019;}    //13.56%
  if(GetX(kC_CLU_AutoBrightSta) == 20u) {dutyRate = Par_AmberAutoBrightLevel020;}    //13.82%
  if(GetX(kC_CLU_AutoBrightSta) == 21u) {dutyRate = Par_AmberAutoBrightLevel021;}    //14.53%
  if(GetX(kC_CLU_AutoBrightSta) == 22u)  {dutyRate = Par_AmberAutoBrightLevel022;}   //15.24%
  if(GetX(kC_CLU_AutoBrightSta) == 23u)  {dutyRate = Par_AmberAutoBrightLevel023;}   //15.95%
  if(GetX(kC_CLU_AutoBrightSta) == 24u)  {dutyRate = Par_AmberAutoBrightLevel024;}   //16.67%
  if(GetX(kC_CLU_AutoBrightSta) == 25u)  {dutyRate = Par_AmberAutoBrightLevel025;}   //16.92%
  if(GetX(kC_CLU_AutoBrightSta) == 26u)  {dutyRate = Par_AmberAutoBrightLevel026;}   //17.17%
  if(GetX(kC_CLU_AutoBrightSta) == 27u)  {dutyRate = Par_AmberAutoBrightLevel027;}   //17.42%
  if(GetX(kC_CLU_AutoBrightSta) == 28u)  {dutyRate = Par_AmberAutoBrightLevel028;}   //17.68%
  if(GetX(kC_CLU_AutoBrightSta) == 29u)  {dutyRate = Par_AmberAutoBrightLevel029;}   //17.93%
  if(GetX(kC_CLU_AutoBrightSta) == 30u)  {dutyRate = Par_AmberAutoBrightLevel030;}   //18.18%
  if(GetX(kC_CLU_AutoBrightSta) == 31u) {dutyRate = Par_AmberAutoBrightLevel031;}    //18.43%
  if(GetX(kC_CLU_AutoBrightSta) == 32u) {dutyRate = Par_AmberAutoBrightLevel032;}    //18.69%
  if(GetX(kC_CLU_AutoBrightSta) == 33u) {dutyRate = Par_AmberAutoBrightLevel033;}    //18.94%
  if(GetX(kC_CLU_AutoBrightSta) == 34u) {dutyRate = Par_AmberAutoBrightLevel034;}    //19.19%
  if(GetX(kC_CLU_AutoBrightSta) == 35u) {dutyRate = Par_AmberAutoBrightLevel035;}    //19.44%
  if(GetX(kC_CLU_AutoBrightSta) == 36u) {dutyRate = Par_AmberAutoBrightLevel036;}    //19.70%
  if(GetX(kC_CLU_AutoBrightSta) == 37u) {dutyRate = Par_AmberAutoBrightLevel037;}    //19.95%
  if(GetX(kC_CLU_AutoBrightSta) == 38u) {dutyRate = Par_AmberAutoBrightLevel038;}    //20.20%
  if(GetX(kC_CLU_AutoBrightSta) == 39u) {dutyRate = Par_AmberAutoBrightLevel039;}    //20.45%
  if(GetX(kC_CLU_AutoBrightSta) == 40u) {dutyRate = Par_AmberAutoBrightLevel040;}    //20.71%
  if(GetX(kC_CLU_AutoBrightSta) == 41u) {dutyRate = Par_AmberAutoBrightLevel041;}    //20.96%
  if(GetX(kC_CLU_AutoBrightSta) == 42u) {dutyRate = Par_AmberAutoBrightLevel042;}    //21.21%
  if(GetX(kC_CLU_AutoBrightSta) == 43u)  {dutyRate = Par_AmberAutoBrightLevel043;}   //21.46%
  if(GetX(kC_CLU_AutoBrightSta) == 44u)  {dutyRate = Par_AmberAutoBrightLevel044;}   //21.72%
  if(GetX(kC_CLU_AutoBrightSta) == 45u)  {dutyRate = Par_AmberAutoBrightLevel045;}   //21.97%
  if(GetX(kC_CLU_AutoBrightSta) == 46u)  {dutyRate = Par_AmberAutoBrightLevel046;}   //22.22%
  if(GetX(kC_CLU_AutoBrightSta) == 47u)  {dutyRate = Par_AmberAutoBrightLevel047;}   //22.47%
  if(GetX(kC_CLU_AutoBrightSta) == 48u)  {dutyRate = Par_AmberAutoBrightLevel048;}   //22.73%
  if(GetX(kC_CLU_AutoBrightSta) == 49u)  {dutyRate = Par_AmberAutoBrightLevel049;}   //22.98%
  if(GetX(kC_CLU_AutoBrightSta) == 50u)  {dutyRate = Par_AmberAutoBrightLevel050;}   //23.23%
  if(GetX(kC_CLU_AutoBrightSta) == 51u)  {dutyRate = Par_AmberAutoBrightLevel051;}   //23.48%
  if(GetX(kC_CLU_AutoBrightSta) == 52u) {dutyRate = Par_AmberAutoBrightLevel052;}    //23.74%
  if(GetX(kC_CLU_AutoBrightSta) == 53u) {dutyRate = Par_AmberAutoBrightLevel053;}    //23.99%
  if(GetX(kC_CLU_AutoBrightSta) == 54u) {dutyRate = Par_AmberAutoBrightLevel054;}    //24.24%
  if(GetX(kC_CLU_AutoBrightSta) == 55u) {dutyRate = Par_AmberAutoBrightLevel055;}    //24.49%
  if(GetX(kC_CLU_AutoBrightSta) == 56u) {dutyRate = Par_AmberAutoBrightLevel056;}    //24.75%
  if(GetX(kC_CLU_AutoBrightSta) == 57u) {dutyRate = Par_AmberAutoBrightLevel057;}    //25.00%
  if(GetX(kC_CLU_AutoBrightSta) == 58u) {dutyRate = Par_AmberAutoBrightLevel058;}    //25.25%
  if(GetX(kC_CLU_AutoBrightSta) == 59u) {dutyRate = Par_AmberAutoBrightLevel059;}    //25.51%
  if(GetX(kC_CLU_AutoBrightSta) == 60u) {dutyRate = Par_AmberAutoBrightLevel060;}    //25.76%
  if(GetX(kC_CLU_AutoBrightSta) == 61u) {dutyRate = Par_AmberAutoBrightLevel061;}    //26.01%
  if(GetX(kC_CLU_AutoBrightSta) == 62u) {dutyRate = Par_AmberAutoBrightLevel062;}    //26.26%
  if(GetX(kC_CLU_AutoBrightSta) == 63u) {dutyRate = Par_AmberAutoBrightLevel063;}    //26.52%
  if(GetX(kC_CLU_AutoBrightSta) == 64u)  {dutyRate = Par_AmberAutoBrightLevel064;}   //26.77%
  if(GetX(kC_CLU_AutoBrightSta) == 65u)  {dutyRate = Par_AmberAutoBrightLevel065;}   //27.02%
  if(GetX(kC_CLU_AutoBrightSta) == 66u)  {dutyRate = Par_AmberAutoBrightLevel066;}   //27.27%
  if(GetX(kC_CLU_AutoBrightSta) == 67u)  {dutyRate = Par_AmberAutoBrightLevel067;}   //27.53%
  if(GetX(kC_CLU_AutoBrightSta) == 68u)  {dutyRate = Par_AmberAutoBrightLevel068;}   //28.78%
  if(GetX(kC_CLU_AutoBrightSta) == 69u)  {dutyRate = Par_AmberAutoBrightLevel069;}   //28.03%
  if(GetX(kC_CLU_AutoBrightSta) == 70u)  {dutyRate = Par_AmberAutoBrightLevel070;}   //28.28%
  if(GetX(kC_CLU_AutoBrightSta) == 71u)  {dutyRate = Par_AmberAutoBrightLevel071;}   //28.54%
  if(GetX(kC_CLU_AutoBrightSta) == 72u)  {dutyRate = Par_AmberAutoBrightLevel072;}   //28.79%
  if(GetX(kC_CLU_AutoBrightSta) == 73u) {dutyRate = Par_AmberAutoBrightLevel073;}    //29.04%
  if(GetX(kC_CLU_AutoBrightSta) == 74u) {dutyRate = Par_AmberAutoBrightLevel074;}    //29.29%
  if(GetX(kC_CLU_AutoBrightSta) == 75u) {dutyRate = Par_AmberAutoBrightLevel075;}    //29.55%
  if(GetX(kC_CLU_AutoBrightSta) == 76u) {dutyRate = Par_AmberAutoBrightLevel076;}    //30.80%
  if(GetX(kC_CLU_AutoBrightSta) == 77u) {dutyRate = Par_AmberAutoBrightLevel077;}    //30.05%
  if(GetX(kC_CLU_AutoBrightSta) == 78u) {dutyRate = Par_AmberAutoBrightLevel078;}    //30.30%
  if(GetX(kC_CLU_AutoBrightSta) == 79u) {dutyRate = Par_AmberAutoBrightLevel079;}    //30.56%
  if(GetX(kC_CLU_AutoBrightSta) == 80u) {dutyRate = Par_AmberAutoBrightLevel080;}    //30.81%
  if(GetX(kC_CLU_AutoBrightSta) == 81u) {dutyRate = Par_AmberAutoBrightLevel081;}    //31.06%
  if(GetX(kC_CLU_AutoBrightSta) == 82u) {dutyRate = Par_AmberAutoBrightLevel082;}    //31.31%
  if(GetX(kC_CLU_AutoBrightSta) == 83u) {dutyRate = Par_AmberAutoBrightLevel083;}    //31.57%
  if(GetX(kC_CLU_AutoBrightSta) == 84u) {dutyRate = Par_AmberAutoBrightLevel084;}    //31.82%
  if(GetX(kC_CLU_AutoBrightSta) == 85u) {dutyRate = Par_AmberAutoBrightLevel085;}    //32.07%
  if(GetX(kC_CLU_AutoBrightSta) == 86u) {dutyRate = Par_AmberAutoBrightLevel086;}    //32.32%
  if(GetX(kC_CLU_AutoBrightSta) == 87u) {dutyRate = Par_AmberAutoBrightLevel087;}    //32.58%
  if(GetX(kC_CLU_AutoBrightSta) == 88u) {dutyRate = Par_AmberAutoBrightLevel088;}    //32.83%
  if(GetX(kC_CLU_AutoBrightSta) == 89u) {dutyRate = Par_AmberAutoBrightLevel089;}    //33.08%
  if(GetX(kC_CLU_AutoBrightSta) == 90u) {dutyRate = Par_AmberAutoBrightLevel090;}    //33.33%
  if(GetX(kC_CLU_AutoBrightSta) == 91u) {dutyRate = Par_AmberAutoBrightLevel091;}    //100.00%
  //if(GetX(kC_CLU_AutoBrightSta) >= 92u) {dutyRate = Par_AmberAutoBrightLevelMax;}    //100.00%
  if(GetX(kC_CLU_AutoBrightSta) >= 92u)
  {
  	dutyRate = Par_GreenAutoBrightLevelMax;
	SetX(kC_CLU_AutoBrightSta, 92u);
  } 
  return dutyRate;
}
#else
/* Green/Amber Rheostat */
uint8 GetDuty_Que(void)
{
  uint8 dutyRate = 50u;                                                         /*25%*/

  if(GetX(kC_CLU_RhstaLvlSta) == 1u)  {dutyRate = Par_RheostatBrightLevel01;}     /*3%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 2u)  {dutyRate = Par_RheostatBrightLevel02;}     /*5%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 3u)  {dutyRate = Par_RheostatBrightLevel03;}     /*7.5%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 4u)  {dutyRate = Par_RheostatBrightLevel04;}     /*10%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 5u)  {dutyRate = Par_RheostatBrightLevel05;}     /*12.5%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 6u)  {dutyRate = Par_RheostatBrightLevel06;}     /*15%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 7u)  {dutyRate = Par_RheostatBrightLevel07;}     /*17.5%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 8u)  {dutyRate = Par_RheostatBrightLevel08;}     /*20%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 9u)  {dutyRate = Par_RheostatBrightLevel09;}     /*22.5%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 10u) {dutyRate = Par_RheostatBrightLevel10;}     /*25%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 11u) {dutyRate = Par_RheostatBrightLevel11;}     /*27.5%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 12u) {dutyRate = Par_RheostatBrightLevel12;}     /*30%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 13u) {dutyRate = Par_RheostatBrightLevel13;}     /*32.5%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 14u) {dutyRate = Par_RheostatBrightLevel14;}     /*35.5%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 15u) {dutyRate = Par_RheostatBrightLevel15;}     /*37.5%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 16u) {dutyRate = Par_RheostatBrightLevel16;}     /*40%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 17u) {dutyRate = Par_RheostatBrightLevel17;}     /*42.5%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 18u) {dutyRate = Par_RheostatBrightLevel18;}     /*45%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 19u) {dutyRate = Par_RheostatBrightLevel19;}     /*47.5%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 20u) {dutyRate = Par_RheostatBrightLevel20;}     /*50%*/
  if(GetX(kC_CLU_RhstaLvlSta) == 21u) {dutyRate = Par_RheostatBrightLevel21;}     /*100%*/

  return dutyRate;
}
#endif
uint16 gINDdutyRate = 0u;
uint16 gINDgdutycycle = 0u;
uint16 GetDutyCycle(uint16 dutyRate)
{
  #if 1
  return  ((uint16)dutyRate);
  #else
  u16 dutyCycle = 0u;

  dutyCycle = 0x8000 - ((0x8000 * (u16)dutyRate) / 200);

  return dutyCycle;
  #endif
}
#if defined (USE_AUTOBRIGHT)
uint16 GetDutyCycle_AutoBright(uint16 dutyRate)
{
	gINDdutyRate = dutyRate;
	u16 dutyCycle = 0u;
  	dutyCycle = ((0x8000 * (u16)dutyRate) / 10000);
  	return dutyCycle;
}
#endif
void Pwm_IND_Start(uint8 channel, uint16 dutycycle)
{
  switch(channel)
  {
    case Amber:
	#if defined (USE_AUTOBRIGHT)
	  gINDgdutycycle = dutycycle;
	  Rte_Call_Pwm_Duty_R_AMBER_IND_OUT_SetDutyCycle(gINDgdutycycle);
	#else
      Rte_Call_Pwm_Duty_R_AMBER_IND_OUT_SetDutyCycle(dutycycle * 25);
	#endif
      break;
    case Green1:
	#if defined (USE_AUTOBRIGHT)
	  gINDgdutycycle = dutycycle;
	  Rte_Call_Pwm_Duty_R_GREEN_IND_OUT1_SetDutyCycle(gINDgdutycycle);
	#else
      Rte_Call_Pwm_Duty_R_GREEN_IND_OUT1_SetDutyCycle(dutycycle * 25);
	#endif
	  break;
    case Green2:
	#if defined (USE_AUTOBRIGHT)
	  gINDgdutycycle = dutycycle;
	  Rte_Call_Pwm_Duty_R_GREEN_IND_OUT2_SetDutyCycle(gINDgdutycycle);
	#else
      Rte_Call_Pwm_Duty_R_GREEN_IND_OUT2_SetDutyCycle(dutycycle * 25);
	#endif
	  break;
    case Green3:
	#if defined (USE_AUTOBRIGHT)
	  gINDgdutycycle = dutycycle;
	  Rte_Call_Pwm_Duty_R_GREEN_IND_OUT3_SetDutyCycle(gINDgdutycycle);
	#else  
      Rte_Call_Pwm_Duty_R_GREEN_IND_OUT3_SetDutyCycle(dutycycle * 25);
	#endif
	  break;
    default:
      break;
  }
}

void Pwm_IND_Stop(uint8 channel)
{
  switch(channel)
  {
    case Amber:
      Rte_Call_Pwm_Duty_R_AMBER_IND_OUT_SetOutputToIdle();
      break;
    case Green1:
      Rte_Call_Pwm_Duty_R_GREEN_IND_OUT1_SetOutputToIdle();
      break;
    case Green2:
      Rte_Call_Pwm_Duty_R_GREEN_IND_OUT2_SetOutputToIdle();
      break;
    case Green3:
      Rte_Call_Pwm_Duty_R_GREEN_IND_OUT3_SetOutputToIdle();
      break;
    default:
      break;
  }
}

void Change_PWM_IND_DutyCycle(uint16 dutycycle, uint8 channel)
{
  switch(channel)
  {
    case Amber:
	#if defined (USE_AUTOBRIGHT)
	  gINDgdutycycle = dutycycle;
	  Rte_Call_Pwm_Duty_R_AMBER_IND_OUT_SetDutyCycle(dutycycle);
	#else
      Rte_Call_Pwm_Duty_R_AMBER_IND_OUT_SetDutyCycle(dutycycle * 25);
	#endif
	  break;
    case Green1:
	#if defined (USE_AUTOBRIGHT)
	  gINDgdutycycle = dutycycle;
	  Rte_Call_Pwm_Duty_R_GREEN_IND_OUT1_SetDutyCycle(dutycycle);
	#else
      Rte_Call_Pwm_Duty_R_GREEN_IND_OUT1_SetDutyCycle(dutycycle * 25);
	#endif
	  break;
    case Green2:
	#if defined (USE_AUTOBRIGHT)
	  gINDgdutycycle = dutycycle;
	  Rte_Call_Pwm_Duty_R_GREEN_IND_OUT2_SetDutyCycle(dutycycle);
	#else
      Rte_Call_Pwm_Duty_R_GREEN_IND_OUT2_SetDutyCycle(dutycycle * 25);
	#endif
	  break;
    case Green3:
	#if defined (USE_AUTOBRIGHT)
	  gINDgdutycycle = dutycycle;
	  Rte_Call_Pwm_Duty_R_GREEN_IND_OUT3_SetDutyCycle(dutycycle);
	#else  
      Rte_Call_Pwm_Duty_R_GREEN_IND_OUT3_SetDutyCycle(dutycycle * 25);
	#endif
	  break;
    default:
      break;
  }
}

uint16 gdutycycle = 0;

void Pwm_FAN_Start(uint16 dutycycle)
{
	//gdutycycle = dutycycle*0x512u;
	gdutycycle = dutycycle*0x147u;
    //Rte_Call_Pwm_Duty_R_FAN_OUT_SetDutyCycle(gdutycycle);
    Rte_Call_Pwm_Duty_R_FAN_OUT_SetDutyCycle(gdutycycle);
}

void Pwm_FAN_Stop(void)
{
  Rte_Call_Pwm_Duty_R_FAN_OUT_SetOutputToIdle();
}

void Change_PWM_FAN_DutyCycle(uint16 dutycycle)
{
  //gdutycycle = dutycycle*0x512;
  gdutycycle = dutycycle*0x147u;
  //Rte_Call_Pwm_Duty_R_FAN_OUT_SetDutyCycle(gdutycycle);
  Rte_Call_Pwm_Duty_R_FAN_OUT_SetDutyCycle(gdutycycle);
  
}

void IPS_Control(uint16 enable)
{
  VN7140AS_IN_WriteDirect(enable);
  VN7140AS_SEN_WriteDirect(enable);
}


