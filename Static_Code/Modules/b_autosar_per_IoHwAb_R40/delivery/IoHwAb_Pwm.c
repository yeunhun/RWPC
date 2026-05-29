/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_Pwm.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_PwmSetDutyCycle                                        **
**              IoHwAb_PwmSetPeriodAndDuty                                    **
**              IoHwAb_PwmSetOutputToIdle                                     **
**              IoHwAb_PwmGetOutputState                                      **
**              IoHwAb_PwmDisableNotification                                 **
**              IoHwAb_PwmEnableNotification                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.15.0.2  09-Sep-2021   Yangjin    #31974                                  **
** 1.10.1    04-Aug-2020   Yangjin    #24902                                  **
** 1.3.1     30-Apr-2019   Yangjin    #16954                                  **
** 1.0.4     16-SEP-2015   Jongyoung  1.MISRA-C Rule violation fix            **
** 1.0.3     25-Mar-2015   Jongyoung  1.Manage the single module version      **
** 1.0.2     27-Sep-2014   Jongyoung  1. Polyspace result Adaption            **
** 1.0.1     19-Aug-2014   Sinil      1. Change null types                    **
** 1.0.0     07-Mar-2014   Sinil      Initial version                         **
*******************************************************************************/
/* polyspace-begin MISRA-C3:11.5 [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Pwm.h"
#include "Rte_IoHwAb.h"
#include "IoHwAb_Config.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (defined(IOHWAB_MCAL_INFINEON_TC38X)) || (defined(IOHWAB_MCAL_INFINEON_TC39X))
#define PWM_LOW PWM_17_GTMCCU6_LOW
#endif
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_PWM == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_PwmSetDutyCycle                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes the duty cycle value of        **
**                        corresponding PWM channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Duty                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmSetDutyCycle                          **
*******************************************************************************/
#if (IOHWAB_PWM_SET_DUTY_CYCLE_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmSetDutyCycle(IoHwAb_IndexType ChIdx,
  uint16 Duty)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmSetDutyCycle != IOHWAB_NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumPwmLgc))
  {
    IoHwAb_GpPwmSetDutyCycle(IoHwAb_GaaPwmChIdx[ChIdx], (uint16)Duty);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_SET_DUTY_CYCLE_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_PwmSetPeriodAndDuty                          **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes both the period and duty cycle **
**                        value of corresponding PWM channel.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Period, Duty                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmSetPeriodAndDuty                      **
*******************************************************************************/
#if (IOHWAB_PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmSetPeriodAndDuty(IoHwAb_IndexType ChIdx,
  IoHwAb_PwmPeriodType Period, uint16 Duty)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmSetPeriodAndDuty != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumPwmLgc))
  {
    IoHwAb_GpPwmSetPeriodAndDuty(IoHwAb_GaaPwmChIdx[ChIdx], (Pwm_PeriodType)Period,
      (uint16)Duty);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_SET_PERIOD_AND_DUTY_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_PwmSetOutputToIdle                           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes output pin of corresponding    **
                           PWM channel to idle state.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmSetOutputToIdle                       **
*******************************************************************************/
#if (IOHWAB_PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmSetOutputToIdle(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmSetOutputToIdle != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumPwmLgc))
  {
    IoHwAb_GpPwmSetOutputToIdle(IoHwAb_GaaPwmChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_PwmGetOutputState                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the output state of              **
**                        corresponding PWM channel to idle state.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Level                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmGetOutputState                        **
*******************************************************************************/
#if (IOHWAB_PWM_GET_OUTPUT_STATE_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmGetOutputState(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmGetOutputState != IOHWAB_NULL_PTR) && 
      (Level != NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumPwmLgc))
  {
    if (PWM_LOW == IoHwAb_GpPwmGetOutputState(IoHwAb_GaaPwmChIdx[ChIdx]))
    {
      *Level = IOHWAB_LOW;
    }
    else
    {
      *Level = IOHWAB_HIGH;
    }
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_GET_OUTPUT_STATE_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_PwmDisableNotification                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables notification feature of the   **
**                        corresponding PWM channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmDisableNotification                   **
*******************************************************************************/
#if (IOHWAB_PWM_NOTIFICATION_SUPPORTED == STD_ON)
/** IoHwAb_PwmDisableNotification */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmDisableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmDisableNotification != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumPwmLgc))
  {
    IoHwAb_GpPwmDisableNotification(IoHwAb_GaaPwmChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_NOTIFICATION_SUPPORTED == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_PwmEnableNotification                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables notification feature of the    **
**                        corresponding PWM channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, NotificationEdge                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaPwmChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpPwmEnableNotification                    **
*******************************************************************************/
#if (IOHWAB_PWM_NOTIFICATION_SUPPORTED == STD_ON)
/** IoHwAb_PwmEnableNotification */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_PwmEnableNotification(IoHwAb_IndexType ChIdx,
  IoHwAb_PwmEdgeType NotificationEdge)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpPwmEnableNotification != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumPwmLgc))
  {
    if (NotificationEdge == IOHWAB_RISING_EDGE)
    {
      IoHwAb_GpPwmEnableNotification(IoHwAb_GaaPwmChIdx[ChIdx],
        (Pwm_EdgeNotificationType)PWM_RISING_EDGE);
    }
    else if (NotificationEdge == IOHWAB_FALLING_EDGE)
    {
      IoHwAb_GpPwmEnableNotification(IoHwAb_GaaPwmChIdx[ChIdx],
        (Pwm_EdgeNotificationType)PWM_FALLING_EDGE);
    }
    else
    {
      IoHwAb_GpPwmEnableNotification(IoHwAb_GaaPwmChIdx[ChIdx],
        (Pwm_EdgeNotificationType)PWM_BOTH_EDGES);
    }
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Pwm_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_PWM_NOTIFICATION_SUPPORTED == STD_ON) */

#endif /* (IOHWAB_USE_PWM == STD_ON) */
/* polyspace-end MISRA-C3:11.5 [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
