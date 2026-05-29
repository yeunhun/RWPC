/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Schd.c                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Implements Scheduler for Bootloader                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision    Date          By           Description                         **
********************************************************************************
** 1.3.4       31-Dec-2021   JHLim        Redmine #33539                      **
** 1.1.0.0     23-Feb-2021   JHLim        Redmine #23964                      **
** 1.0.0       10-April-2020 JaeHyun      Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:2.2,20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Stm.h"
#include "Bsm.h"
#include "Schd.h"
#include "Schd_Cfg.h"
#include "Syst.h"
#include "FlsIf.h"
#include "Mpm.h"
#include "Stm_Pgm.h"
#include "Stm_Ddp.h"
#include "WdgIf.h"
#include "Dcm.h"
#include "Util.h"

#include "Can.h"
#include "CanTp.h"

#include "TcpIpw.h"
#include "EthDiag.h"

#include "Sec_SecurityAccess.h"
#include "Sec_SecureFlash.h"
#include "Fbl_AppIf.h"

/*******************************************************************************
**                           Macro Definition                                 **
*******************************************************************************/
#define SCHD_ZERO                                                     (uint8)0U
#define SCHD_ONE                                                      (uint8)1U

#if (BTL_DEBUG == STD_ON)
#define SCHD_UINT_MAX_VALUE                                         0xFFFFFFFFU
#endif
/*******************************************************************************
**                Global Variable  Declaration                                **
*******************************************************************************/
#define BTL_START_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"

#if (BTL_DEBUG == STD_ON)

#if (SCHD_TASK_100_USEC == STD_ON)
static uint32 Schd_Gu32_TaskHitCounter_100uSec;
#endif

#if (SCHD_TASK_200_USEC == STD_ON)
static uint32 Schd_Gu32_TaskHitCounter_200uSec;
#endif

#if (SCHD_TASK_500_USEC == STD_ON)
static uint32 Schd_Gu32_TaskHitCounter_500uSec;
#endif

#if (SCHD_TASK_1_MSEC == STD_ON)
static uint32 Schd_Gu32_TaskHitCounter_1mSec;
#endif

#if (SCHD_TASK_5_MSEC == STD_ON)
static uint32 Schd_Gu32_TaskHitCounter_5mSec;
#endif

#if (SCHD_TASK_10_MSEC == STD_ON)
static uint32 Schd_Gu32_TaskHitCounter_10mSec;
#endif

static uint32 Schd_Gu32_TaskHitCounter_Background;

#endif /*(BTL_DEBUG == STD_ON)*/

#if (SCHD_TASK_100_USEC == STD_ON)
static uint32 Schd_Gu32_100uSecTimeLast;
#endif

#if (SCHD_TASK_200_USEC == STD_ON)
static uint32 Schd_Gu32_200uSecTimeLast;
#endif

#if (SCHD_TASK_500_USEC == STD_ON)
static uint32 Schd_Gu32_500uSecTimeLast;
#endif

#if (SCHD_TASK_1_MSEC == STD_ON)
static uint32 Schd_Gu32_1mSecTimeLast;
#endif

#if (SCHD_TASK_5_MSEC == STD_ON)
static uint32 Schd_Gu32_5mSecTimeLast;
#endif

#if (SCHD_TASK_10_MSEC == STD_ON)
static uint32 Schd_Gu32_10mSecTimeLast;
#endif

#if (BTL_DEBUG == STD_ON)
static uint32 Schd_Gu32_Jitter_max;

static uint32 Schd_Gu32_Jitter_min;
#endif

#define BTL_STOP_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                    Local Function Declarations                             **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#if (SCHD_TASK_100_USEC == STD_ON)
static void Schd_Task100uSec(void);
#endif

#if (SCHD_TASK_200_USEC == STD_ON)
static void Schd_Task200uSec(void);
#endif

#if (SCHD_TASK_500_USEC == STD_ON)
static void Schd_Task500uSec(void);
#endif

#if (SCHD_TASK_1_MSEC == STD_ON)
static void Schd_Task1mSec(void);
#endif

#if (SCHD_TASK_5_MSEC == STD_ON)
static void Schd_Task5mSec(void);
#endif

#if (SCHD_TASK_10_MSEC == STD_ON)
static void Schd_Task10mSec(void);
#endif

static void Schd_TaskBackground(void);

#if (BTL_DEBUG == STD_ON)
static void Schd_JitterTest(uint32 Lu32_TimeStamp);
#endif

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**                   Local Function Definitions                               **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
** Function Name        : Schd_Task100uSec                                    **
**                                                                            **
** Description          : Schedules tasks at interval of 100uSec              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Schd_Init                                           **
**                                                                            **
*******************************************************************************/
#if (SCHD_TASK_100_USEC == STD_ON)
static void Schd_Task100uSec(void)
{
  /* Tasks that are to be executed at every 100 uSec can be called here. */
  #if (FBL_COMM_CAN_ENABLE == STD_ON)
  Can_MainFunction_Write();
  Can_MainFunction_Read();
  #endif
}
#endif

/*******************************************************************************
** Function Name        : Schd_Task200uSec                                    **
**                                                                            **
** Description          : Schedules tasks at interval of 200uSec              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Schd_Init                                           **
**                                                                            **
*******************************************************************************/
#if (SCHD_TASK_200_USEC == STD_ON)
static void Schd_Task200uSec(void)
{
  #if(FBL_COMM_ENET_ENABLE == STD_ON)
  TcpIpw_MainFunction();
  EthDiag_MainFunction();
  #endif
  Dcm_MainFunction();
  #if(FBL_COMM_CAN_ENABLE == STD_ON)
  CanTp_MainFunction();
  #endif
}
#endif

/*******************************************************************************
** Function Name        : Schd_Task500uSec                                    **
**                                                                            **
** Description          : Schedules tasks at interval of 500uSec              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Schd_Init                                           **
**                                                                            **
*******************************************************************************/
#if (SCHD_TASK_500_USEC == STD_ON)
static void Schd_Task500uSec(void)
{
  /* Tasks that are to be executed at every 500 uSec can be called here */
}
#endif

/*******************************************************************************
** Function Name        : Schd_Task1mSec                                      **
**                                                                            **
** Description          : Schedules tasks at interval of 1mSec                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Schd_Init                                           **
**                                                                            **
*******************************************************************************/
#if (SCHD_TASK_1_MSEC == STD_ON)
static void Schd_Task1mSec(void)
{
  Bsm_MainFunction();
  Syst_MainFunction();
  WdgIf_Trigger();
}
#endif

/*******************************************************************************
** Function Name        : Schd_Task5mSec                                      **
**                                                                            **
** Description          : Schedules tasks at interval of 5mSec                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Schd_Init                                           **
**                                                                            **
*******************************************************************************/
#if (SCHD_TASK_5_MSEC == STD_ON)
static void Schd_Task5mSec(void)
{
  /* Tasks that are to be executed at every 5msec can be called here */
}
#endif

/*******************************************************************************
** Function Name        : Schd_Task10mSec                                     **
**                                                                            **
** Description          : Schedules tasks at interval of 10mSec               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Schd_Init                                           **
**                                                                            **
*******************************************************************************/
#if (SCHD_TASK_10_MSEC == STD_ON)
static void Schd_Task10mSec(void)
{
  /* Tasks that are to be executed at every 10msec can be called here */
  #if (FBL_COMM_CAN_ENABLE == STD_ON)
  Can_MainFunction_BusOff();
  #endif
}
#endif

/*******************************************************************************
** Function Name        : Schd_TaskBackground                                 **
**                                                                            **
** Description          : Background processing of tasks                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Schd_Init                                           **
**                                                                            **
*******************************************************************************/
static void Schd_TaskBackground(void)
{
  #if (FBL_COMM_CAN_ENABLE == STD_ON)
  #endif
  Stm_MainFunction();
  Stm_DdpMainFunction();
  Stm_PgmMainFunction();
  Mpm_MainFunction();
  Sec_SecurityAccessMainFunction();
  Sec_SecureFlashMainFunction();
}

/*******************************************************************************
** Function Name        : Schd_WdgSchedule                                    **
**                                                                            **
** Description          : Calls scheduled APIs of Bootloader modules from     **
**                        Flash drive callback function                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Schd_Init                                           **
**                                                                            **
*******************************************************************************/
void Schd_WdgSchedule(void)
{
  /* Time interval for triggering the watchdog is scheduled in this API. */
  uint32 Lu32_Difference200uSec;
  uint32 Lu32_Counter;
  uint32 Lu32_1mSecCounter;
  uint32 Lu32_TimeStamp;

  Lu32_TimeStamp = Syst_TimerGetTimeuSec();
  Lu32_Difference200uSec = ((Lu32_TimeStamp - Schd_Gu32_200uSecTimeLast)
    /SCHD_USEC_200_COUNT);

  Lu32_1mSecCounter = SCHD_ZERO;

  for (Lu32_Counter = SCHD_ONE; Lu32_Counter <= Lu32_Difference200uSec; Lu32_Counter++)
  {
    Schd_Gu32_200uSecTimeLast += SCHD_USEC_200_COUNT;
    /*
     * Call Schd_Task200uSec to compensate the time taken by blocking memory
     * operation
     */
    WdgIf_Trigger();
    Schd_Task200uSec();
    #if (FBL_COMM_CAN_ENABLE == STD_ON)
    Can_MainFunction_Write();
    Can_MainFunction_Read();
    #endif

    Lu32_1mSecCounter++;

    /* 1ms = (200us * 5) */
    if (Lu32_1mSecCounter == 5U)
    {
      Schd_Gu32_1mSecTimeLast += SCHD_MSEC_1_COUNT;
      /*
       * Call Schd_Task1mSec to compensate the time taken by blocking memory
       * operation
       */
      Schd_Task1mSec();
      Lu32_1mSecCounter = SCHD_ZERO;
    }
  }
}

void Schd_WdgSchedule_fast(void)
{
  /* Time interval for triggering the watchdog is scheduled in this API. */
  WdgIf_Trigger();
  Schd_Task200uSec();
  #if (FBL_COMM_CAN_ENABLE == STD_ON)
  Can_MainFunction_Write();
  Can_MainFunction_Read();
  #endif
}

/*******************************************************************************
** Function Name        : Schd_JitterTest                                     **
**                                                                            **
** Description          : Calculates minimum and maximum jitter               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Schd_Init                                           **
**                                                                            **
*******************************************************************************/
#if (BTL_DEBUG == STD_ON)
static void Schd_JitterTest(uint32 Lu32_TimeStamp)
{
  static uint32 Lu32_TimeStampPrevious = SCHD_ZERO;
  uint32 Lu32_Timetemp = SCHD_ZERO;
  Lu32_Timetemp = Lu32_TimeStamp;

  /* Update the time stamp interval with the difference between the present
   * and previous time stamp
   */
  Lu32_TimeStamp -= Lu32_TimeStampPrevious;

  /* Check if max. jitter value is less than the time stamp interval. */
  if (Schd_Gu32_Jitter_max < Lu32_TimeStamp)
  {
    Schd_Gu32_Jitter_max = Lu32_TimeStamp;
  }
  /* Check if min. jitter value is more than the time stamp interval. */
  if (Schd_Gu32_Jitter_min > Lu32_TimeStamp)
  {
    Schd_Gu32_Jitter_min = Lu32_TimeStamp;
  }
  /* Update the previous time stamp value with present time stamp. */
  Lu32_TimeStampPrevious = Lu32_Timetemp;
}
#endif /* (BTL_DEBUG == STD_ON) */

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**                   Global Function Definition                               **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
** Function Name        : Schd_Init                                           **
**                                                                            **
** Description          : Scheduler initialization                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
void Schd_Init(void)
{
  uint32 Lu32_TimeStamp = STD_CLEAR;

#if (BTL_DEBUG == STD_ON)

#if (SCHD_TASK_100_USEC == STD_ON)
  Schd_Gu32_TaskHitCounter_100uSec     = STD_CLEAR;
#endif

#if (SCHD_TASK_200_USEC == STD_ON)
  Schd_Gu32_TaskHitCounter_200uSec    = STD_CLEAR;
#endif

#if (SCHD_TASK_500_USEC == STD_ON)
  Schd_Gu32_TaskHitCounter_500uSec    = STD_CLEAR;
#endif

#if (SCHD_TASK_1_MSEC == STD_ON)
  Schd_Gu32_TaskHitCounter_1mSec      = STD_CLEAR;
#endif

#if (SCHD_TASK_5_MSEC == STD_ON)
  Schd_Gu32_TaskHitCounter_5mSec      = STD_CLEAR;
#endif

#if (SCHD_TASK_10_MSEC == STD_ON)
  Schd_Gu32_TaskHitCounter_10mSec     = STD_CLEAR;
  Schd_Gu32_TaskHitCounter_Background = STD_CLEAR;
#endif

#endif /* (BTL_DEBUG == STD_ON) */

  (void)Syst_TimerGetTime(&Lu32_TimeStamp);

#if (SCHD_TASK_100_USEC == STD_ON)
  Schd_Gu32_100uSecTimeLast    = Lu32_TimeStamp;
#endif

#if (SCHD_TASK_200_USEC == STD_ON)
  Schd_Gu32_200uSecTimeLast   = Lu32_TimeStamp;
#endif

#if (SCHD_TASK_500_USEC == STD_ON)
  Schd_Gu32_500uSecTimeLast   = Lu32_TimeStamp;
#endif

#if (SCHD_TASK_1_MSEC == STD_ON)
  Schd_Gu32_1mSecTimeLast     = Lu32_TimeStamp;
#endif

#if (SCHD_TASK_5_MSEC == STD_ON)
  Schd_Gu32_5mSecTimeLast     = Lu32_TimeStamp;
#endif

#if (SCHD_TASK_10_MSEC == STD_ON)
  Schd_Gu32_10mSecTimeLast    = Lu32_TimeStamp;
#endif

#if (BTL_DEBUG == STD_ON)
  Schd_Gu32_Jitter_max       = STD_CLEAR;
  Schd_Gu32_Jitter_min       = SCHD_UINT_MAX_VALUE;

  (void)Schd_Gu32_Jitter_max;
  (void)Schd_Gu32_Jitter_min;
#endif
}

/*******************************************************************************
** Function Name        : Schd_MainFunction                                   **
**                                                                            **
** Description          : Calls scheduler APIs to perform cyclic tasks        **
**                        required for Bootloader                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Schd_Init                                           **
**                                                                            **
*******************************************************************************/
void Schd_MainFunction(void)
{
  uint32 Lu32_TimeStamp = SCHD_ZERO;

  for ( ; ; )
  {
    (void)Syst_TimerGetTime(&Lu32_TimeStamp);

    #if (SCHD_TASK_100_USEC == STD_ON)
    if ((Lu32_TimeStamp - Schd_Gu32_100uSecTimeLast) > SCHD_USEC_100_COUNT)
    {
      Schd_Gu32_100uSecTimeLast += SCHD_USEC_100_COUNT;
      Schd_Task100uSec();
      #if (BTL_DEBUG == STD_ON)
      Schd_Gu32_TaskHitCounter_100uSec++;
      #endif
    }
    #endif

    #if (SCHD_TASK_200_USEC == STD_ON)
    if ((Lu32_TimeStamp - Schd_Gu32_200uSecTimeLast) > SCHD_USEC_200_COUNT)
    {
      Schd_Gu32_200uSecTimeLast += SCHD_USEC_200_COUNT;
      Schd_Task200uSec();
      #if (BTL_DEBUG == STD_ON)
      Schd_Gu32_TaskHitCounter_200uSec++;
      #endif
    }
    #endif

    #if (SCHD_TASK_500_USEC == STD_ON)
    if ((Lu32_TimeStamp - Schd_Gu32_500uSecTimeLast) > SCHD_USEC_500_COUNT)
    {
      Schd_Gu32_500uSecTimeLast += SCHD_USEC_500_COUNT;
      Schd_Task500uSec();
      #if (BTL_DEBUG == STD_ON)
      Schd_Gu32_TaskHitCounter_500uSec++;
      #endif
    }
    #endif

    #if (SCHD_TASK_1_MSEC == STD_ON)
    if ((Lu32_TimeStamp - Schd_Gu32_1mSecTimeLast) > SCHD_MSEC_1_COUNT)
    {
      Schd_Gu32_1mSecTimeLast += SCHD_MSEC_1_COUNT;
      Schd_Task1mSec();
      #if (BTL_DEBUG == STD_ON)
      Schd_JitterTest(Lu32_TimeStamp);
      Schd_Gu32_TaskHitCounter_1mSec++;
      #endif
    }
    #endif

    #if (SCHD_TASK_5_MSEC == STD_ON)
    if ((Lu32_TimeStamp - Schd_Gu32_5mSecTimeLast) > SCHD_MSEC_5_COUNT)
    {
      Schd_Gu32_5mSecTimeLast += SCHD_MSEC_5_COUNT;
      Schd_Task5mSec();
      #if (BTL_DEBUG == STD_ON)
      Schd_Gu32_TaskHitCounter_5mSec++;
      #endif
    }
    #endif

    #if (SCHD_TASK_10_MSEC == STD_ON)
    if ((Lu32_TimeStamp - Schd_Gu32_10mSecTimeLast) > SCHD_MSEC_10_COUNT)
    {
      Schd_Gu32_10mSecTimeLast += SCHD_MSEC_10_COUNT;
      Schd_Task10mSec();
      #if (BTL_DEBUG == STD_ON)
      Schd_Gu32_TaskHitCounter_10mSec++;
      #endif
    }
    #endif

    Schd_TaskBackground();

#if (BTL_DEBUG == STD_ON)
    Schd_Gu32_TaskHitCounter_Background++;
#endif
  }
}

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:2.2,20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
