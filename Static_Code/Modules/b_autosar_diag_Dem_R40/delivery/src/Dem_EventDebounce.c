/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_EventDebounce.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provides the interface of varialble data that ara configurable**
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                     Revision History                                       **
********************************************************************************
** Revision Date:DD-MM-YYYY By            Description                         **
********************************************************************************
** 3.3.4    31-12-2021    LanhLT         Changes made As per Redmine #33335   **
**                                                                            **
** 1.0.5    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.0.4    01-06-2020    EunKyung.Kim    Changes made As per Redmine #20595  **
**                                                                            **    
** 1.0.3    31-01-2019    EunKyung.Kim    Changes made As per Redmine #14481  **
**                                                                            **
** 1.0.2    22-06-2017      Ek.Kim        Redmine #8910                       **
**                                                                            **
** 1.0.1    06-02-2017      yj.yun        Redmine #7251                       **
**                                                                            **
** 1.0.0    06-11-2015      Autron        Initial Version                     **
*******************************************************************************/

 
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
**                     Include Section                                       **
*******************************************************************************/
#include "Dem.h"        /* DEM module Header File */
#include "Dem_Ram.h"    /* DEM Ram Header File */
#include "Dem_Config.h"

/* DEM_DEV_ERROR_DETECT is defined in Dem_Cfg.h
 * Dem_Cfg.h is included by Dem.h */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"        /* Det Module Header File */
#endif

#include "SchM_Dem.h"   /* Basic s/w module Scheduler symbols Header File */ 
#include "Rte_Dem.h"
#include "Dem_Event.h"
#include "Dem_EventDebounce.h"

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
 ** Function Name       : Dem_ProcessDebounceCounterBased                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Perform Counter based Debouncing of events and      **
 **                       qualify them as pass or fail.                       **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : LusEventParameterIndex                              **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : LpEventStatus                                       **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO)
FUNC(boolean, DEM_CODE)Dem_ProcessDebounceCounterBased(
  const Dem_NumOfDebounceType DebounceId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus)
{
  boolean qulifiedAsPassOrFailed = DEM_FALSE;
  
  if(DebounceId < Dem_Number_Of_Pre_Debounce_Counter)
  { 
    P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) dcb = &Dem_GaaPreDebounceCounter[DebounceId];
    /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    const sint16 maxFDC = dcb->ssDemCounterFailedThreshold; /* (+) value */
    const sint16 minFDC = dcb->ssDemCounterPassedThreshold; /* (-) value */
    switch(*EventStatus)
    {
      case DEM_EVENT_STATUS_FAILED:
        /* Temporary counter is set to Maximum threshold */
        Dem_GssTempCounter[DebounceId] = maxFDC; 
        Dem_CtrDebDirection[DebounceId] = DEM_CTRDEB_DIRECTION_UP;
        qulifiedAsPassOrFailed = DEM_TRUE;
      break;
      case DEM_EVENT_STATUS_PASSED:
        /* Set the FDC value to minimum */
        /* Temporary counter is set to Minimum threshold */
        Dem_GssTempCounter[DebounceId] = minFDC;
        Dem_CtrDebDirection[DebounceId] = DEM_CTRDEB_DIRECTION_DOWN;        
        qulifiedAsPassOrFailed = DEM_TRUE;
        break;
      case DEM_EVENT_STATUS_PREFAILED:
      
        /* check if JumpUp is configured and 
         * the counting direction changes from decrementing to incrementing,
         * set to the new internal dcb counter init value.
         * direction :DEM_CTRDEB_DIRECTION_UNDEF - do not jump 
         * Dem_GssTempCounter is zero */
        if ((dcb->blDemJumpUp == DEM_TRUE) &&
            (Dem_CtrDebDirection[DebounceId] == DEM_CTRDEB_DIRECTION_DOWN))
        {
          /***           
           *                |                     Jump Up!!! (if 0 > -20) 
           * JumpUpValue  0 +---------------------#------
           *                |                     #
           *            -10 +####-----------------#------           
           *                |   #                 #
           *                |   #                 #
           * Counter    -20 +---###################-------
           *                  prepassed     prefailed 
           */
          if (dcb->ssDemCounterJumpUpValue > Dem_GssTempCounter[DebounceId])
          {
            /* Load the internal counter with jump up value */
            Dem_GssTempCounter[DebounceId] = dcb->ssDemCounterJumpUpValue;
          }    
        }
        Dem_CtrDebDirection[DebounceId] = DEM_CTRDEB_DIRECTION_UP;   

        /* We follow the AR4.2.2 but not 4.0.3(having bug about jump value)
         * [SWS_Dem_00425] 
         * If the jump-up behavior is enabled, the Dem module shall pro-
         * vide the configuration parameter DemDebounceCounterJumpUpValue defining the
         * new internal dcb counter init value. Each reporting of a pre-failed value
         *  while the current dcb counter value is smaller than the DemDebounceCoun-
         * terJumpUpValue shall ?rst reset the dcb counter to DemDebounceCounter-
         * JumpUpValue before performing the pre-failed dcb event ([SWS_Dem_00418]).
         */
        if ( (maxFDC - (sint16)dcb->usDemCountIncStepSize) > 
             Dem_GssTempCounter[DebounceId])  /*  (+)FDC max - step > (+/-)FDC value */
        {
          /* Increment FDC */
	      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */ 
          Dem_GssTempCounter[DebounceId] += (sint16)dcb->usDemCountIncStepSize;
        }
        else
        {
          /* Qualify the Event to failed if the counter has reached the max value */
          *EventStatus = DEM_EVENT_STATUS_FAILED;      
          Dem_GssTempCounter[DebounceId] = maxFDC;
          qulifiedAsPassOrFailed = DEM_TRUE;
        }
        break;
      case DEM_EVENT_STATUS_PREPASSED:
        /* check if JumpDown is configured and 
         * the counting direction changes from incrementing to decrementing,          
         * set to the new internal dcb counter init value 
         * direction :DEM_CTRDEB_DIRECTION_UNDEF - do not jump 
         * Dem_GssTempCounter is zero */
        if ((dcb->blDemJumpDown == DEM_TRUE) &&
            (Dem_CtrDebDirection[DebounceId] == DEM_CTRDEB_DIRECTION_UP))
        {
          /***           
           *                 |                     
           * Counter      20 +---####################---
           *                 |   #                  #
           *              10 +####------------------#---
           *                 |                      #
           *                 |                      # 
           * JumpDownValue 0 +---+------------------#--- Jump down !!! (if 0 < 20) 
           *                  prefailed         prepassed
           */        
          if (dcb->ssDemCounterJumpDownValue < Dem_GssTempCounter[DebounceId])
          {
            /* Load the internal counter with jump down value */
            Dem_GssTempCounter[DebounceId] = dcb->ssDemCounterJumpDownValue;
          }
        }
        Dem_CtrDebDirection[DebounceId] = DEM_CTRDEB_DIRECTION_DOWN;   

        /* We follow the AR4.2.2 but not 4.0.3(having bug about jump value)
         *
         * [SWS_Dem_00423] 
         * If the jump-down behavior is enabled, the Dem module shall
         * provide the configuration parameter DemDebounceCounterJumpDownValue defining
         * the new internal dcb counter init value. Each reporting of a pre-passed
         * value while the current dcb counter value is greater than the DemDe-
         * bounceCounterJumpDownValue shall first reset the dcb counter to DemDe-
         * bounceCounterJumpDownValue before performing the pre-passed dcb event */
        if ( (minFDC + (sint16)dcb->usDemCountDecStepSize) <
             Dem_GssTempCounter[DebounceId]) /*  (-)FDC min + step < (+/-)FDC value */
        {
          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
	      Dem_GssTempCounter[DebounceId] -= (sint16)dcb->usDemCountDecStepSize;
        }
        else
        {
          /*Qualify the Event to passed if the counter has reached the min value*/
          *EventStatus = DEM_EVENT_STATUS_PASSED;
          /* Load the internal counter with passed threshold */
          Dem_GssTempCounter[DebounceId] = minFDC;
          qulifiedAsPassOrFailed = DEM_TRUE;
        }    

        break;
      /* polyspace<RTE:UNR:Not a defect:No action planned> Default switch clause is unreachable. switch-expression */          
      default: break;      
    }
  }
  else
  /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to true. Avoid the runtime error of the polyspace */
  {
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_POINTER);
  }


  return qulifiedAsPassOrFailed;
}


#endif

/*******************************************************************************
 ** Function Name       : Dem_GetFDCDebounceTimeBased == *1                   **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Gets the FaultDetectionCounter value of an event    **
 **                       with time based debounce                            **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : event                                               **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : FDC                                                 **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                                                                           **
 **                       Function(s) invoked :                               **
 **                        Dem_GetCfgDebounceTimer()                          **
 *******************************************************************************/
#if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON) 
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetFDCDebounceTimeBased(
    Dem_EventParameterCPCType event,
    P2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_VAR) FDC)
{
  P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) timerStatus = NULL_PTR;
  P2CONST(Dem_PreDebounceTimeBasedType, AUTOMATIC, DEM_VAR) cfgTimer = NULL_PTR;
  uint32 timerCounter= 0U;
  /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
  Dem_EventStatusType eventStatus = (Dem_EventStatusType)DEM_EVENT_STATUS_FAILED;
  Std_ReturnType retVal = E_NOT_OK;
  
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to false. Avoid the runtime error of the polyspace */      
  if (NULL_PTR  == event)
  {
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_POINTER);
    retVal = E_NOT_OK;
  }
  else
  #endif
  {    
    timerStatus = Dem_GetDebounceTimerStatus(event->ucIndexOfDebounceAry);  
    cfgTimer = Dem_GetCfgDebounceTimer(event->ucIndexOfDebounceAry);
    if ((NULL_PTR != cfgTimer) && (NULL_PTR != timerStatus))
    {
      SchM_Enter_Dem_REQUEST_DEBOUNCETIMEBASED();

      timerCounter = timerStatus->tds_Counter;
      eventStatus = timerStatus->tds_EventStatus;
      
      SchM_Exit_Dem_REQUEST_DEBOUNCETIMEBASED();
    
      *FDC = 0;
    
      /* Check whether Reported Event Status is Failed */
      switch (eventStatus)
      {
        case DEM_EVENT_STATUS_FAILED:
          if (0u == timerCounter)
          {
            /* Set the FDC to maximum value */
            *FDC = DEM_COUNTER_MAX;
            retVal = E_OK;
          }
          else
          {
            DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
          }          
          break;
        case DEM_EVENT_STATUS_PASSED:    
          if (0u == timerCounter)
          {
            /* Set the FDC value to minimum */
            *FDC = DEM_COUNTER_MIN;
            retVal = E_OK;
          }
          else
          {
            DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
          }          
          break;
        case DEM_EVENT_STATUS_PREFAILED:
          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
          if (0u != cfgTimer->ulDemTimeFailedThreshold)
          {
            /* Calculate the FDC from the internal counter
             *
             * 1) unit of ulDemTimeFailedThreshold is ms.
             * 2) timer counter is  0 => FDC is max
             * 3) timer counter is max => FDC is 0  */
            const uint32 MaxCounter = cfgTimer->ulDemTimeFailedThreshold / Dem_Task_Time;
            const uint32 digit = 1000U;
    
            uint32 TimerValue;
            uint32 CounterRatio;
    
            if ( (0U != MaxCounter) && (timerCounter <= MaxCounter) )
            {
              /* fomula : FDC = ( timer value / threshold) * FDC max */
              TimerValue =  (MaxCounter - timerCounter) * digit;
              CounterRatio = ((TimerValue / MaxCounter) * (uint32)DEM_COUNTER_MAX) / digit;
	          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
	          *FDC = (Dem_FaultDetectionCounterType)CounterRatio;
              retVal = E_OK;
            }
            else
            {
              DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
            }
          }
          else
          /* @IF_REQ : ulDemTimeFailedThreshold shall be greater than zero */
          /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to true. Avoid the runtime error of the polyspace */
          {
            /* in case of a threshold is 0(zero) , 
             * event status is changed to failed immediately */
            *FDC = DEM_COUNTER_MAX;
            retVal = E_OK;
          }
          break;
        case DEM_EVENT_STATUS_PREPASSED:
          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
          if (0u != cfgTimer->ulDemTimePassedThreshold)
          {
            /* Calculate the FDC from the internal counter
             *
             * 1) unit of ulDemTimePassedThreshold is ms.
             * 2) timer counter is  0 => FDC is max
             * 3) timer counter is max => FDC is 0
             */
            const uint32 MaxCounter = cfgTimer->ulDemTimePassedThreshold / Dem_Task_Time;
            const uint32 digit = 1000;
            uint32 TimerValue;
            sint32 CounterRatio;
            
            if ( (0U != MaxCounter) && (timerCounter <= MaxCounter) )
            {
              /* fomula : FDC = ( timer value / threshold) * FDC min */
              TimerValue =  (MaxCounter - timerCounter) * digit;
              /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
	          CounterRatio = (((sint32)TimerValue / (sint32)MaxCounter) * (sint32)DEM_COUNTER_MIN) / (sint32)digit;    
              *FDC = (Dem_FaultDetectionCounterType)CounterRatio;
              retVal = E_OK;
            }
            else
            {
              DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
            }
          }
          else
          /* @IF_REQ : ulDemTimePassedThreshold shall be greater than zero */
          /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to true. Avoid the runtime error of the polyspace */
          {
            /* in case of a threshold is 0(zero) , 
             * event status is changed to passed immediately */
            *FDC = DEM_COUNTER_MIN;
            retVal = E_OK;
          }
          break;
        default: /* DEM_EVENT_STATUS_UNDEFINED */
          /* *FDC = 0; */
          break;
      }
    }
  }

  return retVal;
}

/*******************************************************************************
 ** Function Name       : Dem_ProcessDebounceTimeBased  == *1                 **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Starts timer for Time based  Debouncing             **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : none                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :
 ** Global Variable(s)  :                                                     **
 **
 *******************************************************************************/
/* polyspace:begin<MISRA-C:16.7:Not a defect:Justify with annotations> A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object. */
FUNC(boolean, DEM_CODE)
Dem_ProcessDebounceTimeBased(
  const Dem_NumOfDebounceType DebounceId,
/* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */	
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus)
{
  boolean qulifiedAsPassOrFailed = DEM_FALSE;

  P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) timerStatus = NULL_PTR;
  P2CONST(Dem_PreDebounceTimeBasedType, AUTOMATIC, DEM_VAR) cfgTimer = NULL_PTR;
  /*
   * Conditions to (re)starts timer
   *  1)  when the monitor reports DEM_EVENT_STATUS_PREPASSED for the first time
   *  2) EventStatus changes from DEM_EVENT_STATUS_PREPASSED to DEM_EVENT_STATUS_PREFAILED
   *  3) EventStatus changes from DEM_EVENT_STATUS_PREFAILED to DEM_EVENT_STATUS_PREPASSED
   *  4) EventStatus changes from DEM_EVENT_STATUS_FAILED to DEM_EVENT_STATUS_PREPASSED
   *  5) EventStatus changes from DEM_EVENT_STATUS_PASSED to DEM_EVENT_STATUS_PREFAILED
   *
   * Dem should set the internal debounce timer value to its configured threshold
   * to start timer. */
  
  /* [Dem431] If the monitor reports DEM_EVENT_STATUS_FAILED, the Dem module
   * shall set the internal debounce timer value to its configured threshold being the failed
   * criteria (refer to DemDebounceTimeFailedThreshold)
   *
   * Our algorithm decreases from threshold to 0,but suggested algorithm of AUTOSAR increases from 0 to threshold.
   * So counter shall be zero */
  const uint8 actionByEventStatus[4][5] =
  {
    /* New Status = DEM_EVENT_STATUS_PASSED = 0 */
    {
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_PASSED,   = 0 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_FAILED,   = 1 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_PREPASSED = 2 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_PREFAILED = 3 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_UNDEFINED = 4 */
    },
    /* New Status = DEM_EVENT_STATUS_FAILED  = 1*/
    {
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_PASSED,   = 0 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_FAILED,   = 1 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_PREPASSED = 2 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_PREFAILED = 3 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_UNDEFINED = 4 */
    },
    /* New Status = DEM_EVENT_STATUS_PREPASSED = 2*/
    {
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_PASSED,   = 0 */
      DCM_DBTIME_ACT_START_PASS_TIMER, /* Old Status = DEM_EVENT_STATUS_FAILED,   = 1 */
      DCM_DBTIME_ACT_CONTINOUS,        /* Old Status = DEM_EVENT_STATUS_PREPASSED = 2 */
      DCM_DBTIME_ACT_START_PASS_TIMER, /* Old Status = DEM_EVENT_STATUS_PREFAILED = 3 */
      DCM_DBTIME_ACT_START_PASS_TIMER, /* Old Status = DEM_EVENT_STATUS_UNDEFINED = 4 */
    },
    /* New Status = DEM_EVENT_STATUS_PREFAILED = 3*/
    {
      DCM_DBTIME_ACT_START_FAIL_TIMER, /* Old Status = DEM_EVENT_STATUS_PASSED,   = 0 */
      DCM_DBTIME_ACT_EVENT_QUALIFIED,  /* Old Status = DEM_EVENT_STATUS_FAILED,   = 1 */
      DCM_DBTIME_ACT_START_FAIL_TIMER, /* Old Status = DEM_EVENT_STATUS_PREPASSED = 2 */
      DCM_DBTIME_ACT_CONTINOUS,        /* Old Status = DEM_EVENT_STATUS_PREFAILED = 3 */
      DCM_DBTIME_ACT_START_FAIL_TIMER, /* Old Status = DEM_EVENT_STATUS_UNDEFINED = 4 */
    }
  };  

  cfgTimer = Dem_GetCfgDebounceTimer(DebounceId);
  timerStatus = Dem_GetDebounceTimerStatus(DebounceId); 
  
  if ((cfgTimer != NULL_PTR) && 
      (timerStatus != NULL_PTR)  &&
      (*EventStatus < 4) &&
      (timerStatus->tds_EventStatus < 5))
  {    
    SchM_Enter_Dem_REQUEST_DEBOUNCETIMEBASED();
    /* stores old event status */

    switch(actionByEventStatus[*EventStatus][timerStatus->tds_EventStatus])
    {
      case DCM_DBTIME_ACT_START_FAIL_TIMER:
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
        if (0U != cfgTimer->ulDemTimeFailedThreshold)
        {
          timerStatus->tds_Counter = cfgTimer->ulDemTimeFailedThreshold/Dem_Task_Time;
          timerStatus->tds_EventStatus = *EventStatus;            
        }
        else
        /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to true. */                
        {
          /* if threshold is 0, event status is changed to failed immediately */            
          timerStatus->tds_Counter = 0U;
          timerStatus->tds_EventStatus = DEM_EVENT_STATUS_FAILED;
          
          *EventStatus = DEM_EVENT_STATUS_FAILED; 
          qulifiedAsPassOrFailed = DEM_TRUE;
        }
        break;
      case DCM_DBTIME_ACT_START_PASS_TIMER:
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
        if (0U != cfgTimer->ulDemTimePassedThreshold)
        {
          timerStatus->tds_Counter = cfgTimer->ulDemTimePassedThreshold/Dem_Task_Time;
          timerStatus->tds_EventStatus = *EventStatus;                          
        }
        else
        /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to true.*/
        {
          /* if threshold is 0, event status is changed to passed immediately */
          timerStatus->tds_Counter = 0U;
          timerStatus->tds_EventStatus = DEM_EVENT_STATUS_PASSED;
          
          *EventStatus = DEM_EVENT_STATUS_PASSED; 
          qulifiedAsPassOrFailed = DEM_TRUE;              
        }
        break;
      case DCM_DBTIME_ACT_EVENT_QUALIFIED:
        /* Stop timer. Refer to Dem431 */
        timerStatus->tds_Counter = 0;
        timerStatus->tds_EventStatus = *EventStatus;   
        
        qulifiedAsPassOrFailed = DEM_TRUE;
        break;
      default: /* DCM_DBTIME_ACT_CONTINOUS*/
        /* @IF_REQ: Does it need...?  */
        timerStatus->tds_EventStatus = *EventStatus;
        break;
    }   
    SchM_Exit_Dem_REQUEST_DEBOUNCETIMEBASED();
  }    

  return qulifiedAsPassOrFailed;
}
/* polyspace:end<MISRA-C:16.7:Not a defect:Justify with annotations> A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object. */




/*******************************************************************************
 ** Function Name       : Dem_ProcessDebounceTimer                            **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Performs internal calculation for Time based        **
 **                       Debouncing                                          **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : none                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                                                                           **
 **                       Function(s) invoked :                               **
 **                       Dem_ProcessEventStatus                              **
 *******************************************************************************/
FUNC(void, DEM_CODE)Dem_ProcessDebounceTimer(void)
{
  P2CONST(Dem_PreDebounceTimeBasedType, AUTOMATIC, DEM_VAR) cfgTimer = NULL_PTR;
  P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) timerStatus = NULL_PTR;

  const Dem_EventStatusType filterOfEventStatus[] =
  {
    DEM_FALSE, /* DEM_EVENT_STATUS_PASSED     0x00 unused */
    DEM_FALSE, /* DEM_EVENT_STATUS_FAILED     0x01 unused */
    DEM_TRUE,  /* DEM_EVENT_STATUS_PREPASSED  0x02 used   */
    DEM_TRUE,  /* DEM_EVENT_STATUS_PREFAILED  0x03 used   */
    DEM_FALSE  /* DEM_EVENT_STATUS_UNDEFINED  0x04 unused   */
  };    
  const Dem_EventStatusType resultOfTimeout[] =
  {
    0,                       /* DEM_EVENT_STATUS_PASSED     0x00 unused */
    0,                       /* DEM_EVENT_STATUS_FAILED     0x01 unused */
    DEM_EVENT_STATUS_PASSED, /* DEM_EVENT_STATUS_PREPASSED  0x02 used   */
    DEM_EVENT_STATUS_FAILED, /* DEM_EVENT_STATUS_PREFAILED  0x03 used   */
    0                        /* DEM_EVENT_STATUS_UNDEFINED  0x04 unused   */
  };
  Dem_NumOfDebounceType dbIndex;
  

  /* @IF_REQ: The event  queue shall be used for loop optimization */
  /* Loop for the time debounce */
  for(dbIndex = 0U; dbIndex < Dem_Number_Of_Pre_Debounce_Time; dbIndex++)
  {
    cfgTimer= Dem_GetCfgDebounceTimer(dbIndex);
    timerStatus = Dem_GetDebounceTimerStatus(dbIndex);    
    
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */
    if ((cfgTimer != NULL_PTR) && (timerStatus != NULL_PTR))
    {
      /* @IF_REQ: at first, shall check timerStatus->tds_Counter > 0U) for optimization */
      /* Check the status of all enable conditions configured for the event.
      It is a condition of the specific event(Don't care a combined event) */
      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition can evaluate to true or false according to the request of application.*/      
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      if (E_OK == Dem_GetEventConditionsAndControlDTCSetting(cfgTimer->t_EventId))
      {
	  /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */  
        Dem_OperationCycleStateType cycleState = (Dem_OperationCycleStateType)DEM_CYCLE_STATE_END;
        
        (void)Dem_GetOpCycleStateByEvent(cfgTimer->t_EventId, &cycleState);
        if (DEM_CYCLE_STATE_START == cycleState)
        {
          SchM_Enter_Dem_REQUEST_DEBOUNCETIMEBASED();     
          if ((timerStatus->tds_Counter > 0U) &&
              (timerStatus->tds_EventStatus < COUNTOF(filterOfEventStatus)))
          {
            timerStatus->tds_Counter--; 
	        /* polyspace +2 MISRA-C3:10.4 [Justified:Low] "Not a defect" */
	        /* polyspace +1 MISRA-C3:10.3 [Justified:Low] "Not a defect" */
            if ((0U == timerStatus->tds_Counter) && (DEM_TRUE == filterOfEventStatus[timerStatus->tds_EventStatus]))
            {     
              SchM_Exit_Dem_REQUEST_DEBOUNCETIMEBASED();          
              (void)Dem_ProcessEventStatus(cfgTimer->t_EventId, resultOfTimeout[timerStatus->tds_EventStatus]);              
            }
            else
            {
              SchM_Exit_Dem_REQUEST_DEBOUNCETIMEBASED();
            }
          }
          else
          {
            SchM_Exit_Dem_REQUEST_DEBOUNCETIMEBASED();
          }
        }
      }
    }
  }
}

#endif

/*******************************************************************************
 ** Function Name       : Dem_ResetFaultDectectionCounter                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Reset fault detection counter both based time and   **
 **                       counter debounce counters                           **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : event                                               **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : none                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 **                                                                           **
 *******************************************************************************/
FUNC(void, DEM_CODE)
Dem_ResetFaultDectectionCounter(
    Dem_EventParameterCPCType event)
{
  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
  switch(DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(event->ParamFieldsA))
  {
    /* Debounce Counter Based */
    #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > DEM_ZERO) /* #if (DEM_DEBOUNCE_COUNTER_SUPPORT == STD_ON) */
    case DEM_DEBOUNCE_COUNTER_BASED:
      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */
      if( event->ucIndexOfDebounceAry < Dem_Number_Of_Pre_Debounce_Counter) 
      {
        Dem_GssTempCounter[event->ucIndexOfDebounceAry] = 0;
        Dem_CtrDebDirection[event->ucIndexOfDebounceAry] = DEM_CTRDEB_DIRECTION_UNDEF;
      }
      break;
    #endif

      /* Debounce Time Based */
    #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
    case DEM_DEBOUNCE_TIME_BASED:
    {
      P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) timerStatus ;
      timerStatus = Dem_GetDebounceTimerStatus(event->ucIndexOfDebounceAry);          
      if (timerStatus != NULL_PTR)
      {
        timerStatus->tds_Counter = 0;
        timerStatus->tds_EventStatus = DEM_EVENT_STATUS_UNDEFINED;
      }

    }
    break;
    #endif

    #if (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > 0u)
    case DEM_DEBOUNCE_MONITOR_BASED:
      /*
       * Dem_SetOperationCycle
       * Note: For resetting the fault detection counter implemented in a monitor, the Dem
       * module uses the callback-function InitMonitorForEvent (refer to section 7.2 and Init-
       * MonitorForEvent).
       */
      break;
    #endif

    default:
      /* retVal = E_NOT_OK; */
      break;
  }
}

/*******************************************************************************
 ** Function Name       : Dem_InitDebounce                                    **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Initialize debounce related variables               **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : none                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 **                                                                           **
 *******************************************************************************/
FUNC(void, DEM_CODE) Dem_InitDebounce(void)
{
  #if ((DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > 0U) || (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON))
  Dem_NumOfDebounceType  idx;
  #endif

  /* @IF_REQ : Redesign -> the counter debounce shall be not dependent on Library */
  /* #if (DEM_DEBOUNCE_COUNTER_SUPPORT == STD_ON) */
  #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > 0U) 
  for (idx = 0U; idx < Dem_Number_Of_Pre_Debounce_Counter; idx++)
  {
    Dem_GssTempCounter[idx] = 0;
    Dem_CtrDebDirection[idx] = DEM_CTRDEB_DIRECTION_UNDEF;
  }
  #endif

  #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
  /* The time debounce is not dependent on Library */  
  for (idx = 0U; idx < Dem_Number_Of_Pre_Debounce_Time; idx++)
  {
    P2VAR(Dem_TimeDebounceStatusType, AUTOMATIC, DEM_VAR) timerStatus ;
    timerStatus = Dem_GetDebounceTimerStatus(idx);
    /* polyspace +5 RTE:UNR [Justified:Low] "Not a defect" */
    if (timerStatus != NULL_PTR)
    {
      timerStatus->tds_Counter = 0;
      timerStatus->tds_EventStatus = DEM_EVENT_STATUS_UNDEFINED;
    }
  }
  #endif
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */