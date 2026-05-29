/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_TimeService.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Implementation of TimeService module                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE: OBAI : Not a defect : Justify with annotations > configured array index */

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.5.4     14-Dec-2021    YH.Han        Redmine #33448                      **
** 1.5.3     08-Jan-2021    YH.Han        Redmine #27601                      **
** 1.5.0     31-Oct-2019    YH.Han        Redmine #19815, #19291              **
** 1.4.0     23-May-2019    YH.Han        Redmine #17493                      **
** 1.3.0     29-Oct-2018    YH.Han        Redmine #12853                      **
** 1.1.2     22-Aug-2017    MJ.Woo        Redmine #6959                       **
** 1.1.0     24-Nov-2016    SH.Yoo        Redmine #6849, #6755                **
** 1.0.3     28-Oct-2016    SH.Yoo        Redmine #6253                       **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_Cfg.h"
#include "Opf_Port.h"
#include "Opf_Ram.h"
#include "Opf_ReceiveEvent.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
static FUNC(OpfTickType, OPF_CODE) Opf_GetSystime(void);

#define OPF_START_SEC_CODE
#include "MemMap.h"

/***************************************************************************//**
 * Function             : Opf_GetSystimeSpan
 *
 * Service ID           : NA
 *
 * Description          : This function gets elapsed system time tick
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : Elapsed system time tick
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddSystimeTick
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-005, OPF-SRS-FUN-006
 ******************************************************************************/
FUNC(OpfTickType, OPF_CODE) Opf_GetSystimeSpan(void)
{
  OpfTickType LddCurTick;
  OpfTickType LddSpanTick;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  OpfSystimeTickType *pCoreSystimeTick;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreSystimeTick = OPF_GET_SYS_TIME_TICK_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* Get current system tick from Timer */
  LddCurTick = Opf_GetSystime();

  #if (OPF_UPWARD_DIRECTION_COUNT == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if(LddCurTick >= *pCoreSystimeTick)
  #else
  if(LddCurTick >= Opf_GddSystimeTick)
  #endif
  {
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    LddSpanTick = LddCurTick - *pCoreSystimeTick;
    #else
    LddSpanTick = LddCurTick - Opf_GddSystimeTick;
    #endif
  }
  else
  {
    /* Assume overflow */
    #if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    LddSpanTick = Opf_Max_Stm_Tick_Value - (*pCoreSystimeTick - LddCurTick - OPF_ONE);
    #else
    LddSpanTick = Opf_Max_Stm_Tick_Value - (Opf_GddSystimeTick - LddCurTick - OPF_ONE);
    #endif
    #else
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    LddSpanTick = OPF_MAX_STM_TICK - (*pCoreSystimeTick - LddCurTick - OPF_ONE);
    #else
    LddSpanTick = OPF_MAX_STM_TICK - (Opf_GddSystimeTick - LddCurTick - OPF_ONE);
    #endif
    #endif
  }
  #else
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if(*pCoreSystimeTick >= LddCurTick)
  #else
  if(Opf_GddSystimeTick >= LddCurTick)
  #endif
  {
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    LddSpanTick = *pCoreSystimeTick - LddCurTick;
    #else
    LddSpanTick = Opf_GddSystimeTick - LddCurTick;
    #endif
  }
  else
  {
    /* Assume overflow */
    #if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    LddSpanTick = Opf_Max_Stm_Tick_Value - (LddCurTick - *pCoreSystimeTick - OPF_ONE);
    #else
    LddSpanTick = Opf_Max_Stm_Tick_Value - (LddCurTick - Opf_GddSystimeTick - OPF_ONE);
    #endif
    #else
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    LddSpanTick = OPF_MAX_STM_TICK - (LddCurTick - *pCoreSystimeTick - OPF_ONE);
    #else
    LddSpanTick = OPF_MAX_STM_TICK - (LddCurTick - Opf_GddSystimeTick - OPF_ONE);
    #endif
    #endif
  }  
  #endif

  /* Save current system tick to variable */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  *pCoreSystimeTick = LddCurTick;
  #else
  Opf_GddSystimeTick = LddCurTick;
  #endif

  return LddSpanTick;
}

/***************************************************************************//**
 * Function             : Opf_GetSystimeDiff
 *
 * Service ID           : NA
 *
 * Description          : This function calculates difference with two timer
 *                        ticks
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            Ldd1stTick       first time tick
 *                        Ldd2ndTick       second time tick
 *
 * @return              : void
 *
 * @pre                 : none
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-005, OPF-SRS-FUN-006
 ******************************************************************************/
FUNC(OpfTickType, OPF_CODE) Opf_GetSystimeDiff(OpfTickType Ldd1stTick,
                                                         OpfTickType Ldd2ndTick)
{
  OpfTickType LddDiffTick;

  #if (OPF_UPWARD_DIRECTION_COUNT == STD_ON)
  if(Ldd2ndTick >= Ldd1stTick)
  {
    LddDiffTick = Ldd2ndTick - Ldd1stTick;
  }
  else
  {
    /* Assume overflow */
    #if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
    LddDiffTick = Opf_Max_Stm_Tick_Value - (Ldd1stTick - Ldd2ndTick - OPF_ONE);
    #else
    LddDiffTick = OPF_MAX_STM_TICK - (Ldd1stTick - Ldd2ndTick - OPF_ONE);
    #endif
  }
  #else 
  if(Ldd1stTick >= Ldd2ndTick)
  {
    LddDiffTick = Ldd1stTick - Ldd2ndTick;
  }
  else
  {
    /* Assume overflow */
    #if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
    LddDiffTick = Opf_Max_Stm_Tick_Value - (Ldd2ndTick - Ldd1stTick - OPF_ONE);
    #else
    LddDiffTick = OPF_MAX_STM_TICK - (Ldd2ndTick - Ldd1stTick - OPF_ONE);
    #endif
  }
  #endif

  return LddDiffTick;
}

/***************************************************************************//**
 * Function             : Opf_GetSystime
 *
 * Service ID           : NA
 *
 * Description          : This function gets timestamp of system timer
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : OpfTickType - Current Tiemstamp
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddSystimeTick
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-001, OPF-SRS-FUN-003, OPF-SRS-FUN-005,
 *                        OPF-SRS-FUN-006, OPF-SRS-FUN-009, OPF-SRS-FUN-011,
 *                        OPF-SRS-FUN-013, OPF-SRS-FUN-015
 ******************************************************************************/
static FUNC(OpfTickType, OPF_CODE) Opf_GetSystime(void)
{
  /* polyspace<RTE:ABS_ADDR:Not a defect:Justify with annotations> Absolute address is needed to access MCU register */
  /* polyspace<MISRA-C:11.3:Not a defect:Justify with annotations> For implementation, conversion from function pointer to void pointer is needed to represent register address */
#if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
  return (OpfTickType) (*Opf_Stm_Address);
#else
  return (OpfTickType)OPF_STM_TICK;
#endif
}

/***************************************************************************//**
 * Function             : Opf_GetSavedSystime
 *
 * Service ID           : NA
 *
 * Description          : This function gets saved system time
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : Opf_GddSystimeTick
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddSystimeTick
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-001, OPF-SRS-FUN-003, OPF-SRS-FUN-005,
 *                        OPF-SRS-FUN-006, OPF-SRS-FUN-009, OPF-SRS-FUN-011,
 *                        OPF-SRS-FUN-013, OPF-SRS-FUN-015
 ******************************************************************************/
FUNC(OpfTickType, OPF_CODE) Opf_GetSavedSystime(void)
{
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  OpfSystimeTickType *pCoreSystimeTick;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreSystimeTick = OPF_GET_SYS_TIME_TICK_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */

  return *pCoreSystimeTick;
  #else
  return Opf_GddSystimeTick;
  #endif
}

/***************************************************************************//**
 * Function             : Opf_GetSavedTimeSpan
 *
 * Service ID           : NA
 *
 * Description          : This function gets saved time span
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : OpfTickType - Current Tiemstamp
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddSystimeTick
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-001, OPF-SRS-FUN-003, OPF-SRS-FUN-005,
 *                        OPF-SRS-FUN-006, OPF-SRS-FUN-009, OPF-SRS-FUN-011,
 *                        OPF-SRS-FUN-013, OPF-SRS-FUN-015
 ******************************************************************************/
FUNC(OpfTickType, OPF_CODE) Opf_GetSavedSystimeSpan(void)
{
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  OpfTimeSpanType *pCoreSystimeSpan;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreSystimeSpan = OPF_GET_SYS_TIME_SPAN_INFO(LddCoreID);
  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */

  return *pCoreSystimeSpan;
  #else
  return Opf_GddSystimeSpan;
  #endif
}

/***************************************************************************//**
 * Function             : Opf_SaveTimeStamp
 *
 * Service ID           : NA
 *
 * Description          : This function is used to save elapsed tick from
 *                        previous Event and set Time Index event
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : Elapsed tick from previous Event
 *
 * @pre                 : StartOS() function should be called
 *                        Opf_GulIndexTicks should be greater than 0
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddOsProfiler, Opf_GulIndexTicks
 *
 *                        Function(s) invoked    :
 *                        Opf_GetSystimeSpan(), Opf_GetSystimeDiff(),
 *                        Opf_SetTimeIndexEvent(), Opf_GetSystime()
 *
 * @ingroup               OPF-SRS-FUN-005, OPF-SRS-FUN-006
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_SaveTimeStamp(void)
{
  OpfTickType LddSpanTick;
  OpfTickType LddTickDiff;
  OpfTickType LddCurTick;
  #if (OPF_UPWARD_DIRECTION_COUNT == STD_OFF)
  OpfTickType LddPrevNextIndexTick;
  #endif
  uint32 LddTickLoopCount;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;
  uint32 *pCoreIndexTicks;
  OpfTimeSpanType *pCoreSystimeSpan;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  pCoreIndexTicks = OPF_GET_INDEX_TICKS_INFO(LddCoreID);
  pCoreSystimeSpan = OPF_GET_SYS_TIME_SPAN_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* Get system span tick since previous Event */
  LddSpanTick = (OpfTickType)Opf_GetSystimeSpan();

  /* polyspace:begin<DEFECT:DEAD_CODE:Not a defect:Justify with annotations> can be reachable according to user configuration */
  /* polyspace:begin<MISRA-C3:14.3:Not a defect:Justify with annotations> can be reachable according to user configuration */
  /* polyspace:begin<MISRA-C3:2.1:Not a defect:Justify with annotations> can be reachable according to user configuration */
  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> can be reachable according to user configuration */
  /* polyspace:begin<CERT-C:MSC12-C:Not a defect:Justify with annotations> can be reachable according to user configuration */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if((Opf_Profile_Time_Index == STD_ON) && (*pCoreIndexTicks != OPF_ZERO))
  #else
  if((Opf_Profile_Time_Index == STD_ON) && (Opf_GulIndexTicks != OPF_ZERO))
  #endif
  {
    LddCurTick = Opf_GetSavedSystime();

    /* Get tick difference from last Time Index */
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    LddTickDiff = Opf_GetSystimeDiff(pCoreOsProfiler->ddNextIndexTick,
                                                                    LddCurTick);
    #else
    LddTickDiff = Opf_GetSystimeDiff(Opf_GddOsProfiler.ddNextIndexTick,
                                                                    LddCurTick);
    #endif

    /* Initialize loop count for time index */
    LddTickLoopCount = 0;

    #if (OPF_MULTICORE_ENABLED == STD_ON)
    while ( (LddTickDiff >= *pCoreIndexTicks) && (LddTickLoopCount <= 10) )
    #else
    while ( (LddTickDiff >= Opf_GulIndexTicks) && (LddTickLoopCount <= 10) )
    #endif
    {
      /* Update Time Index tick */
      #if (OPF_UPWARD_DIRECTION_COUNT == STD_ON)
      #if (OPF_MULTICORE_ENABLED == STD_ON)
      pCoreOsProfiler->ddNextIndexTick += *pCoreIndexTicks;

      #if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
      pCoreOsProfiler->ddNextIndexTick = (pCoreOsProfiler->ddNextIndexTick % Opf_Max_Stm_Tick_Value);
      #else
      pCoreOsProfiler->ddNextIndexTick = (pCoreOsProfiler->ddNextIndexTick % OPF_MAX_STM_TICK);
      #endif
      #else
      Opf_GddOsProfiler.ddNextIndexTick += Opf_GulIndexTicks;

      #if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
      Opf_GddOsProfiler.ddNextIndexTick = (Opf_GddOsProfiler.ddNextIndexTick % Opf_Max_Stm_Tick_Value);
      #else
      Opf_GddOsProfiler.ddNextIndexTick = (Opf_GddOsProfiler.ddNextIndexTick % OPF_MAX_STM_TICK);
      #endif
      #endif
      #else
      LddPrevNextIndexTick = Opf_GddOsProfiler.ddNextIndexTick;

      #if (OPF_MULTICORE_ENABLED == STD_ON)
      pCoreOsProfiler->ddNextIndexTick -= *pCoreIndexTicks;

      if (LddPrevNextIndexTick <= pCoreOsProfiler.ddNextIndexTick)
      {
        #if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
        pCoreOsProfiler.ddNextIndexTick = Opf_Max_Stm_Tick_Value - (0xFFFFFFFF - pCoreOsProfiler.ddNextIndexTick);
        #else
        pCoreOsProfiler.ddNextIndexTick = OPF_MAX_STM_TICK - (0xFFFFFFFF - pCoreOsProfiler.ddNextIndexTick);
        #endif
      }
      #else
      Opf_GddOsProfiler.ddNextIndexTick -= Opf_GulIndexTicks;

      if (LddPrevNextIndexTick <= Opf_GddOsProfiler.ddNextIndexTick)
      {
        #if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
        Opf_GddOsProfiler.ddNextIndexTick = Opf_Max_Stm_Tick_Value - (0xFFFFFFFF - Opf_GddOsProfiler.ddNextIndexTick);
        #else
        Opf_GddOsProfiler.ddNextIndexTick = OPF_MAX_STM_TICK - (0xFFFFFFFF - Opf_GddOsProfiler.ddNextIndexTick);
        #endif
      }
      #endif
      #endif
      
      /* Get tick difference from last Time Index */
      #if (OPF_MULTICORE_ENABLED == STD_ON)
      LddTickDiff = Opf_GetSystimeDiff(pCoreOsProfiler->ddNextIndexTick,
                                                                    LddCurTick);
      #else
      LddTickDiff = Opf_GetSystimeDiff(Opf_GddOsProfiler.ddNextIndexTick,
                                                                    LddCurTick);
      #endif
      /* Set Time Index Event */
      Opf_SetTimeIndexEvent(LddSpanTick - LddTickDiff);
      /* Update span tick since Time Index Event */
      LddSpanTick = LddTickDiff;

      /* Increment loop count for time index */
      LddTickLoopCount++;
    }
  } /* if((Opf_Profile_Time_Index == STD_ON) &&
       (*pCoreIndexTicks != OPF_ZERO)) */
  /* polyspace:end<DEFECT:DEAD_CODE> */
  /* polyspace:end<MISRA-C3:14.3> */
  /* polyspace:end<MISRA-C3:2.1> */
  /* polyspace:end<RTE:UNR> */
  /* polyspace:end<CERT-C:MSC12-C> */

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  *pCoreSystimeSpan = LddSpanTick;
  #else
  Opf_GddSystimeSpan = LddSpanTick;
  #endif
}

#define OPF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<RTE: OBAI : Not a defect : Justify with annotations > configured array index */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
