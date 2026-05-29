/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "SlpWup.h"
#include "Rte_CDD_SLPWUP.h"

#include "Slpwup_Callouts.h"
#include "Slpwup_Cfg.h"
#include "NvM.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
uint8 Slpwup_SlpwupState;

uint8 f_BCAN_WakeupEvtOn = 0u;

uint8 f_ComMModeState_BCAN = 0u;

uint8 Slpwup_GucSwitchFullComm_Flag = 0u;
uint8 Slpwup_GucEnforceNoComm_Flag = 0u;
uint8 Slpwup_GucWaitNvMJobByTimeout_Flag = 0u;
uint8 Slpwup_GulSleepProcessingCount_Flag = 0u;

uint8 Slpwup_GulSleepProcessState = 0u;
uint32 Slpwup_GulSleepRequestProcessingCount = 0u;
uint32 Slpwup_GulSleepRequestProcessTimeout = SLPWUP_SLEEP_REQUEST_PROCESSING_DEADLINE * 0.1;
uint32 Slpwup_GulNvMLowPowerAllowCount = 0u;
uint32 Slpwup_GulNvMLowPowerAllowDuration = SLPWUP_NVM_LOWPOWER_ALLOW_DURATION * 0.1;

Rte_ModeType_EcuMode Slpwup_GddEcuMode = RTE_TRANSITION_EcuMode;

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define ECUM_START_SEC_CALLOUT_CODE
#include "MemMap.h"

void Slpwup_10ms_Task(void)
{
  uint8 lucNoCommPass = 1u;
  uint8 lucNvMPass = 1u;

  if(Slpwup_GulSleepProcessingCount_Flag == 1u)
  {
    Slpwup_GulSleepRequestProcessingCount++;

    if(Slpwup_CheckPrecondition_NO_COM())
    {
      lucNoCommPass = 1u;
    }
    else
    {
      lucNoCommPass = 0u;
    }

    if (Slpwup_CheckPrecondition_NvMLowPower())
    {
      lucNvMPass = 1u;
      Slpwup_GulNvMLowPowerAllowCount++;
    }
    else
    {
      lucNvMPass = 0u;
      Slpwup_GulNvMLowPowerAllowCount=0u;
    }
  }
  else
  {
    Slpwup_GulSleepRequestProcessingCount = 0u;
    Slpwup_GulNvMLowPowerAllowCount = 0u;
  }

  if((Slpwup_GulSleepRequestProcessingCount > 0u) && (Slpwup_GulSleepRequestProcessingCount <= Slpwup_GulSleepRequestProcessTimeout))
  {
    if(Slpwup_GucSwitchFullComm_Flag == 1u)
    {
      if(Slpwup_CheckPrecondition_First_FULL_COM() && (Slpwup_GulSleepRequestProcessingCount > 50u))
      {
        Slpwup_GucSwitchFullComm_Flag = 0u;
        Slpwup_modeRequestPort_ComMMode_NO_COM();
      }
    }
    else
    {
      if((lucNoCommPass == 1u) && (Slpwup_GulNvMLowPowerAllowCount > Slpwup_GulNvMLowPowerAllowDuration))
      {
        if (Slpwup_GucWaitNvMJobByTimeout_Flag == 1u && Slpwup_GucEnforceNoComm_Flag == 0u)
        {
            SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_READY,SLPWUP_NVM_JOB_FINISHED);
        }
        else if (Slpwup_GucWaitNvMJobByTimeout_Flag == 0u && Slpwup_GucEnforceNoComm_Flag == 1u)
        {
            SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_READY,SLPWUP_NO_COM_JOB_FINISHED);
        }
        else
        {
            SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_READY,SLPWUP_NVM_NO_COM_JOB_FINISHED);
        }

        Slpwup_GucEnforceNoComm_Flag = 0u;
        Slpwup_GucWaitNvMJobByTimeout_Flag = 0u;
        Slpwup_GulSleepProcessState = SLPWUP_PRECONDITION_PASS;
        //Rte_Call_CDD_Slpwup_EcuM_StateRequest_RequestSleep(SLPWUP_USER);
        Rte_Call_CDD_SLPWUP_R_Slpwup_EcuM_StateRequest_RequestState(EcuMStateRequest_SLEEP);
      }
    }

  }
   else if(Slpwup_GulSleepRequestProcessingCount > Slpwup_GulSleepRequestProcessTimeout)
  {
    Slpwup_GulSleepProcessingCount_Flag = 0u;
    (void)Rte_Read_CDD_SLPWUP_R_Slpwup_EcuMode_SR_u8(Slpwup_GddEcuMode);

    if (Slpwup_GddEcuMode != RTE_MODE_EcuMode_ECUM_STATE_RUN)
    {
      /* Rte_Call_CDD_Slpwup_EcuM_StateRequest_RequestRUN(SLPWUP_USER); */
      Rte_Call_CDD_SLPWUP_R_Slpwup_EcuM_StateRequest_RequestState(EcuMStateRequest_RUN);
    }

    /* Slpwup_modeRequestPort_ComMMode_FULL_COM(); */

    if(Slpwup_GucSwitchFullComm_Flag == 1u )
    {
      SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_NOT_READY,SLPWUP_NOT_ONCE_FULL_COM_TIMEOUT);
    }
    else
    {
        if((lucNoCommPass == 0u) && (Slpwup_GulNvMLowPowerAllowCount > Slpwup_GulNvMLowPowerAllowDuration ))
       {
        Slpwup_GucWaitNvMJobByTimeout_Flag = 0u;

        SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_NOT_READY,SLPWUP_FULL_COM_DETECTED_TIMEOUT);
      }
      else if((lucNoCommPass == 1u) && (Slpwup_GulNvMLowPowerAllowCount < Slpwup_GulNvMLowPowerAllowDuration))
      {
        Slpwup_GucEnforceNoComm_Flag = 0;

        SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_NOT_READY,SLPWUP_NVM_JOB_DETECTED_TIMEOUT);
      }
      else if((lucNoCommPass == 0u) && (Slpwup_GulNvMLowPowerAllowCount < Slpwup_GulNvMLowPowerAllowDuration))
      {
        SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_NOT_READY,SLPWUP_NVM_FULL_COM_DETECTED_TIMEOUT);
     }
      else
      {
        Slpwup_GucEnforceNoComm_Flag = 0u;
        Slpwup_GucWaitNvMJobByTimeout_Flag = 0u;
        SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_PROCESS_TIMEOUT,Slpwup_GulSleepProcessState);
      }
    }
  }

}

extern uint8 get_init_nvm_test(void);
void Slpwup_RequestSleep(void)
{
  uint8 lucFirstFullCommPass = 1u;
  uint8 lucNoCommPass = 1u;
  uint8 lucNvMPass = 1u;

  Slpwup_GulSleepProcessingCount_Flag = 1u;
  Slpwup_GulSleepProcessState = SLPWUP_PRECONDITION_CHECK;

  if(Slpwup_CheckPrecondition_First_FULL_COM())
  {
    lucFirstFullCommPass = 1u;
  }
  else
  {
    lucFirstFullCommPass = 0u;

    Slpwup_modeRequestPort_ComMMode_First_FULL_COM();
    Slpwup_GulSleepProcessState = SLPWUP_PRECONDITION_CHECK;
    SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_NOT_READY,SLPWUP_NOT_ONCE_FULL_COM_DETECTED);
  }

  if(Slpwup_CheckPrecondition_NO_COM())
  {
    lucNoCommPass = 1u;
  }
  else
  {
    lucNoCommPass = 0u;
  }

  if (Slpwup_CheckPrecondition_NvMLowPower())
  //if(get_init_nvm_test()==0x1F)
  {
    lucNvMPass = 1u;
  }
  else
  {
    lucNvMPass = 0u;
  }

  if((lucFirstFullCommPass == 1u) && (lucNoCommPass == 1u) && (lucNvMPass == 1u))
  {
    Slpwup_GulSleepProcessState = SLPWUP_PRECONDITION_PASS;
    SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_READY,SLPWUP_PRECONDITION_OK);
    //Rte_Call_CDD_Slpwup_EcuM_StateRequest_RequestSleep(SLPWUP_USER);
    Rte_Call_CDD_SLPWUP_R_Slpwup_EcuM_StateRequest_RequestState(EcuMStateRequest_SLEEP);
  }
  else
  {
    if (lucFirstFullCommPass == 0u)
    {
      Slpwup_GucSwitchFullComm_Flag = 1u;
    }
    else
    {
      Slpwup_GucSwitchFullComm_Flag = 0u;
    }

    if (lucNoCommPass == 0u)
    {
      Slpwup_GucEnforceNoComm_Flag = 1u;
    }
    else
    {
      Slpwup_GucEnforceNoComm_Flag = 0u;
    }

    if (lucNvMPass == 0u)
    {
      Slpwup_GucWaitNvMJobByTimeout_Flag = 1u;
    }
    else
    {
      Slpwup_GucWaitNvMJobByTimeout_Flag = 0u;
    }

    #if (SLPWUP_ENFORCE_SLEEP_NOCOMM == STD_ON)
    if (lucFirstFullCommPass == 1u && lucNoCommPass == 0u)
    {
      Slpwup_modeRequestPort_ComMMode_NO_COM();
      Slpwup_GulSleepProcessState = SLPWUP_PRECONDITION_CHECK;
      SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_NOT_READY,SLPWUP_FULL_COM_DETECTED);
    }
    #else
    if (lucNoCommPass == 0u)
    {
      Slpwup_GucWaitNvMJobByTimeout_Flag = 0u;
      Slpwup_GucEnforceNoComm_Flag = 0u;
      Slpwup_GucSwitchFullComm_Flag = 0u;
      Slpwup_GulSleepProcessingCount_Flag = 0u;
      Slpwup_modeRequestPort_ComMMode_FULL_COM();
      Slpwup_GulSleepProcessState = SLPWUP_PRECONDITION_FAIL;
      SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_NOT_READY,SLPWUP_FULL_COM_DETECTED);
    }
    #endif

    #if (SLPWUP_WAIT_NVM_JOB_UNTIL_TIMEOUT == STD_ON)
    if (lucNvMPass == 0u)
    {
      Slpwup_GulSleepProcessState = SLPWUP_PRECONDITION_CHECK;
      SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_NOT_READY,SLPWUP_NVM_JOB_DETECTED);
    }
    #else
    if (lucNvMPass == 0u)
    {
      Slpwup_GucWaitNvMJobByTimeout_Flag = 0u;
      Slpwup_GucEnforceNoComm_Flag = 0u;
      Slpwup_GucSwitchFullComm_Flag = 0u;
      Slpwup_GulSleepProcessingCount_Flag = 0u;
      Slpwup_modeRequestPort_ComMMode_FULL_COM();
      Slpwup_GulSleepProcessState = SLPWUP_PRECONDITION_FAIL;
      SLPWUP_APP_NOTIFICATIONCALLBACK(SLPWUP_SLEEP_REQUEST_NOT_READY,SLPWUP_NVM_JOB_DETECTED);
    }
    #endif
  }
}

void App_Slpwup_NotificationCBK(uint8 NotiMessage, uint8 NotiParameter)
{
  switch (NotiMessage)
  {
    case SLPWUP_SLEEP_REQUEST_READY:

      Slpwup_SlpwupState = NotiParameter;

      break;

    case SLPWUP_SLEEP_REQUEST_NOT_READY:

      Slpwup_SlpwupState = NotiParameter;

      break;

    case SLPWUP_SLEEP_PROCESS_ERROR:

      Slpwup_SlpwupState = NotiParameter;

      Slpwup_GulSleepProcessingCount_Flag = 0u;

      if (Slpwup_GddEcuMode != RTE_MODE_EcuMode_ECUM_STATE_RUN)
      {
        //Rte_Call_CDD_Slpwup_EcuM_StateRequest_RequestRUN(SLPWUP_TEST_USER);
        Rte_Call_CDD_SLPWUP_R_Slpwup_EcuM_StateRequest_RequestState(EcuMStateRequest_RUN);
      }

      Slpwup_modeRequestPort_ComMMode_FULL_COM();

      break;

    case SLPWUP_SLEEP_PROCESS_TIMEOUT:

      Slpwup_SlpwupState = NotiParameter;

      break;

    default:
       break;
  }
}

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
