/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_Indicator.c                                               **
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
** 1.2.4    18-02-2021    EunKyung.Kim   Changes made As per Redmine #25380   **
**                                                                            **
** 1.2.3    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.2.2    01-06-2020    EunKyung.Kim    Changes made As per Redmine #20595  **
**                                                                            **    
** 1.2.1    02-04-2019    EunKyung.Kim    Changes made As per Redmine #16812  **
**                                                                            **
** 1.2.0    14-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.1.1    12-12-2018    YoungJin.Yun    Changes made As per Redmine #14900  **
**                                                                            **
** 1.1.0    16-05-2016      YoungJin.Yun  Changes made As per Redmine #1164   **
**                                                                            **
** 1.0.1    11-05-2016      YoungJin.Yun  Changes made As per Redmine #4848   **
**                                                                            **
** 1.0.0    11-06-2015      Autron        Initial Version                     **
*******************************************************************************/

/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.1 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                     Include Section                                       **
*******************************************************************************/
#include "Dem.h"        /* DEM module Header File */
#include "Dem_Ram.h"    /* DEM Ram Header File */

/* DEM_DEV_ERROR_DETECT is defined in Dem_Cfg.h
 * Dem_Cfg.h is included by Dem.h */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"        /* Det Module Header File */
#endif

#include "SchM_Dem.h"   /* Basic s/w module Scheduler symbols Header File */ 
#include "Rte_Dem.h"
#include "Dem_Event.h"
#include "Dem_EventMemory.h"
#include "Dem_Indicator.h"


#define DEM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
 * Function Name        : Dem_InitIndicator > 2
 *
 * Service ID           : None
 *
 * Description          : Update WarningIndicatorRequest bit according to
 *                        event status
 *
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event, EventStatus
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *                        DEM_TRUE : WIR bit is on
 *                        DEM_FALSE: WIR bit is off
 *
 * Preconditions        : None
 *
 * Remarks              :
 ******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_InitIndicator(Dem_EventIdType EventId)
{
  boolean dirty = DEM_FALSE;

  #if (DEM_NUMBER_OF_INDICATORS != 0U)
  Dem_EventParameterPCType event = &Dem_Event[EventId-1U];

  P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  indicator;    
  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
  Dem_NumOfIndicatorAttributeType max = event->e_PointToIndicator + event->ucNumberofIndicator;
  Dem_NumOfIndicatorAttributeType idx;

  if (max <= Dem_Number_Of_Indicators)
  {      
    for (idx = event->e_PointToIndicator; idx < max ; idx++)
    {
      indicator = Dem_GetCfgIndicatorAtt(idx);      
      dirty |= Dem_EvMem_ResetIndicatorAttribute(indicator);  
    }

    /*
    #if(DEM_OBD_SUPPORT == STD_ON)
    Dem_EventStatusNvRamData.IndicatorMilCounter[index] = 0u;
    #endif
    */
    
    if (DEM_TRUE == dirty)
    {
      Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY); 
    }
  }
  else
  {
    /* Do nothing */
  }
  #else
  DEM_UNUSED(EventId);
  #endif
  return dirty;
}

/*******************************************************************************
 * Function Name        : Dem_ActivateIndicatorOnEventFailed > 2
 *
 * Service ID           : None
 *
 * Description          : Update WarningIndicatorRequest bit according to
 *                        event status
 *
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event, EventStatus
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *                        DEM_TRUE : WIR bit is on
 *                        DEM_FALSE: WIR bit is off
 *
 * Preconditions        : It is called when TFTOC changed from 0 to 1.
 *                        It shall be called once during one operation cycle.
 *                        It is called when WIR bit is zero. 
 * Remarks              :
 ******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_ActivateIndicatorOnEventFailed(
  Dem_EventIdType EventId, 
  uint8  testFailedThisOpCycle)  
{
  boolean dirty = DEM_FALSE;

  #if (DEM_NUMBER_OF_INDICATORS != 0)
  Dem_EventParameterPCType event = &Dem_Event[EventId-1U];

  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
  const Dem_NumOfIndicatorAttributeType max = event->e_PointToIndicator + event->ucNumberofIndicator;
  if (max <= Dem_Number_Of_Indicators)
  {
    P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR) indicator;  
    Dem_NumOfIndicatorAttributeType idx;


    boolean indicatorAttStatus = DEM_FALSE;    
    boolean indicatorStatus = DEM_FALSE;
    uint8 counterValue;
    #if (DEM_OBD_SUPPORT == STD_ON)
    boolean perRegister = DEM_FALSE;
    #endif
    
    /*
     * WarningIndicatorRequest On
     *
     * [1] IndicatorStatus == false
     * [2] Shall be only called from Dem_SetEventStatus by design decision
     * [3] Event qualified as failed this operation cycle at first */
    for (idx = event->e_PointToIndicator; idx < max ; idx++)
    {       
      indicator = Dem_GetCfgIndicatorAtt(idx);   
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      indicatorAttStatus = Dem_EvMem_GetIndicatorAttStatus(EventId, indicator->IndicatorAttStatusPos);

      counterValue = 0U;      
      if (DEM_FALSE == indicatorAttStatus)
      {
        if (0U == testFailedThisOpCycle)
        {
          dirty |= Dem_EvMem_IncreaseIndicatorFailureCounter(indicator->FailureCycleCounterPos, &counterValue);
        }
        /* if failure cycle counter is not existed, indicator status shall set to true */        
        if(counterValue  >= indicator->NumFailureCycles)
        {
          /* @SWS_Dem_00566 */
          dirty |= Dem_EvMem_SetIndicatorAttStatus(indicator, DEM_TRUE); /* from false to true */
          dirty |= Dem_EvMem_SetIndicatorFailureCounter(indicator->FailureCycleCounterPos, 0U);          
          indicatorAttStatus = DEM_TRUE;

          /*  obd */
          #if (DEM_OBD_SUPPORT == STD_ON) 
          #ifdef DEM_MIL_INDICATORID 
          if(DEM_MIL_INDICATORID == indicator->IndicatorIdRef)
          {
            Dem_GucMilonFlag = DEM_BIT7_MASK1; 
            perRegister = DEM_TRUE;
          }
          #endif
          #endif
        }
      }
      
      /* [1] testFailedThisOperationCycle==1
       * [2] testNotCompletedThisOperationCycle==0
       * [3] As result, healing counter = 0
       * [4] N/A: IndicatorStatusPtr is true */
      dirty |= Dem_EvMem_SetIndicatorHealingCounter(indicator->HealingCycleCounterPos, 0U);

      /* calculates the combined indicator status for an indicatorId of an event */
      indicatorStatus |= indicatorAttStatus;
    }

    if (DEM_TRUE == indicatorStatus)
    {
      if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR))
      {
        /* WarningIndicatorRequest bit = 1 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        DEM_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR);
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
      #if(DEM_OBD_SUPPORT == STD_ON)
      if(perRegister == DEM_TRUE)
      {
        #if(DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U)
        (void)Dem_EvMem_RegisterPermanentDTC(EventId);
        #endif
      }
      #endif
    }
  }
  #else
  DEM_UNUSED(EventId);
  DEM_UNUSED(testFailedThisOpCycle);
  #endif
  
  return dirty;
}

/*******************************************************************************
 * Function Name        : Dem_DeActivateIndicatorOnEventPassed
 *
 * Service ID           : None
 *
 * Description          : Update WarningIndicatorRequest bit when event is
 *                        passed
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *                        DEM_TRUE : WIR bit is on
 *                        DEM_FALSE: WIR bit is off
 *
 * Preconditions        : 
 *
 * Remarks              :
 ******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_DeActivateIndicatorOnEventPassed(Dem_EventIdType EventId)
{
  boolean dirty = DEM_FALSE;
  Dem_EventParameterPCType event = &Dem_Event[EventId-1U];
 
  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */ 
  Dem_NumOfIndicatorAttributeType max = event->e_PointToIndicator + event->ucNumberofIndicator;
  if (max <= Dem_Number_Of_Indicators)
  {
    P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  indicator;    
    Dem_NumOfIndicatorAttributeType idx;
    boolean indicatorAttributeStatus = DEM_FALSE;    
    boolean indicatorStatus = DEM_FALSE;
    #if (DEM_OBD_SUPPORT == STD_ON)
    boolean perClear = DEM_FALSE;
    #endif
    Dem_NumOfEventMemoryEntryType pmemLoc = DEM_NO_EVMEM_ENTRY;

    #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
    pmemLoc = Dem_EvMem_FindPerMemLoc(EventId);
    #endif
    
    /*
     * WarningIndicatorRequest Off immediately
     *
     * [1] WarningIndicatorRequest == 1
     * [2] @IF_REQ: Shall be only called when TestResult is passed firstly(TestFailedThisOperationCycle = 0)
     * [3] Only indicator shall be processed with healingCycleThreshold = 0
     * [4] @IF_REQ: Shall be called in Dem_SetEventStatus(first passed this operation) */
     /* polyspace-begin DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because e_PointToIndicator and ucNumberofIndicator can be configured by user,
         this condition maybe awlays evaluate to false, No Impact" */
    for (idx = event->e_PointToIndicator; idx < max ; idx++)
    {
      indicator = Dem_GetCfgIndicatorAtt(idx); 
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      indicatorAttributeStatus = Dem_EvMem_GetIndicatorAttStatus(EventId, indicator->IndicatorAttStatusPos);

      /* healing is processed immediately when threshold value is 0 */
      if ((DEM_TRUE == indicatorAttributeStatus) || ( DEM_NO_EVMEM_ENTRY != pmemLoc))
      {      
        if (0U == indicator->NumHealingCycles)
        {
          /* HealingCycleCounterPtr don't be needed because healing is processed immediately 
           * indicator->HealingCycleCounterPtr = 0u; */        
          dirty |= Dem_EvMem_SetIndicatorAttStatus(indicator, DEM_FALSE); /* from true to false */
          indicatorAttributeStatus = DEM_FALSE; 

          /*  obd */
          #if (DEM_OBD_SUPPORT == STD_ON) 
          #ifdef DEM_MIL_INDICATORID 
          if(DEM_MIL_INDICATORID == indicator->IndicatorIdRef)
          {
            perClear = DEM_TRUE;
            Dem_GucMilonFlag = indicatorAttributeStatus << 7U;
          }
          #endif
          #endif
        }
      }

      /* If indicator failure counter is not equal to zero, 
       * counter should be cleared (qualified as passed) */
      dirty |= Dem_EvMem_SetIndicatorFailureCounter(indicator->FailureCycleCounterPos, 0U);
    
      indicatorStatus |= indicatorAttributeStatus;
    }
    /* polyspace-end DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because e_PointToIndicator and ucNumberofIndicator can be configured by user,
       this condition maybe awlays evaluate to false, No Impact" */

    /* WIR bit off */
    /* polyspace-begin CERT-C:MSC12-C [Justified:Low] "Because of user configuration, above for condiontion maybe awlays evaluate to false.
      indicatorStatus don't update value, this condition awlays evaluate to false. No Impact" */
    if (DEM_FALSE == indicatorStatus)
    {
      if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR))
      {
        /* WarningIndicatorRequest bit = 0 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        DEM_CLR_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR);
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
    }
    /* polyspace-end CERT-C:MSC12-C [Justified:Low] "Because of user configuration, above for condiontion maybe awlays evaluate to false.
      indicatorStatus don't update value, this condition awlays evaluate to false. No Impact" */

    #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
    if(DEM_TRUE == perClear)
    {     
      Dem_EvMem_ClearPermanentDTC(EventId, 1);     
    }
    #endif
    
  }
  
  return dirty;
}

/*******************************************************************************
 * Function Name        : Dem_DeActivateIndicatorOnOperationChange
 *
 * Service ID           : None
 *
 * Description          : Update WarningIndicatorRequest bit when operation
 *                        cycle is changed.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *                        DEM_TRUE : WIR bit is on
 *                        DEM_FALSE: WIR bit is off
 *
 * Preconditions        : 
 *
 * Remarks              :
 ******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_DeActivateIndicatorOnOperationChange(Dem_EventIdType EventId)
{
  boolean dirty = DEM_FALSE;
  Dem_EventParameterPCType event = &Dem_Event[EventId-1U];
  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
  Dem_NumOfIndicatorAttributeType max = event->e_PointToIndicator + event->ucNumberofIndicator;
  /* if event don't have  any indicator */
  if (max <= Dem_Number_Of_Indicators)
  {
    P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  indicator;    
    Dem_NumOfIndicatorAttributeType idx;
    boolean indicatorAttributeStatus = DEM_FALSE;    
    boolean indicatorStatus = DEM_FALSE;
    uint8 counterValue;
    #if (DEM_OBD_SUPPORT == STD_ON)
    uint8 perClear = 0;
    #endif
    Dem_NumOfEventMemoryEntryType pmemLoc = DEM_NO_EVMEM_ENTRY;

    #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
    pmemLoc = Dem_EvMem_FindPerMemLoc(EventId);
    #endif
    
    /* WarningIndicatorRequest Off OperationCycleChange
     *
     * [1] IndicatorStatus == true
     * [2] Tested and qualified as passed this operation
     * [3] Shall be called when OperationCycleChange(START) */
    /* polyspace-begin DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because e_PointToIndicator and ucNumberofIndicator can be configured by user,
       this condition maybe awlays evaluate to false, No Impact" */
    for (idx = event->e_PointToIndicator; idx < max ; idx++)
    {
      counterValue = 0U;          
      indicator = Dem_GetCfgIndicatorAtt(idx);      
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      indicatorAttributeStatus = Dem_EvMem_GetIndicatorAttStatus(EventId, indicator->IndicatorAttStatusPos);

      if ((DEM_TRUE == indicatorAttributeStatus) || ( DEM_NO_EVMEM_ENTRY != pmemLoc))
      {
        if (0U != indicator->NumHealingCycles)
        {
          dirty |= Dem_EvMem_IncreaseIndicatorHealingCounter(indicator->HealingCycleCounterPos, &counterValue);

          if(counterValue >= indicator->NumHealingCycles)
          {
            /* @SWS_Dem_00566 */
            dirty |= Dem_EvMem_SetIndicatorAttStatus(indicator, DEM_FALSE); /* from true to false */
            dirty |= Dem_EvMem_SetIndicatorHealingCounter(indicator->HealingCycleCounterPos, 0U);   

            /*  obd */
            #if (DEM_OBD_SUPPORT == STD_ON)
            #ifdef DEM_MIL_INDICATORID
            if (DEM_MIL_INDICATORID == indicator->IndicatorIdRef)
            {
              if(indicatorAttributeStatus == DEM_TRUE)
              {
                perClear = 1;
              }
              else
              {
                perClear = 2;
              }
              Dem_GucMilonFlag = indicatorAttributeStatus << 7U;
            }
            #endif
            #endif
            
            indicatorAttributeStatus = DEM_FALSE;
            
          }
        }
        else
        {      
          /* HealingCycleCounterPtr don't be needed because healing is processed immediately 
           * indicator->HealingCycleCounterPtr = 0u; */        
          dirty |= Dem_EvMem_SetIndicatorAttStatus(indicator, DEM_FALSE); /* from true to false */
          indicatorAttributeStatus = DEM_FALSE;            
        }
      }

      /* [1] testFailedThisOperationCycle==0
       * [2] testNotCompletedThisOperationCycle==0
       * [3] As result,  indicator failure counter = 0
       * [4] Shall be only called when OperationCycle is changed
       * [5] N/A:IndicatorStatusPtr is false */
      dirty |= Dem_EvMem_SetIndicatorFailureCounter(indicator->FailureCycleCounterPos, 0U);

      indicatorStatus |= indicatorAttributeStatus;
    }
    /* polyspace-end DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because e_PointToIndicator and ucNumberofIndicator can be configured by user,
       this condition maybe awlays evaluate to false. No Impact" */
  
    /* WIR bit off */
    /* polyspace-begin CERT-C:MSC12-C [Justified:Low] "Because of user configuration, above for condiontion maybe awlays evaluate to false.
      indicatorStatus don't update value, this condition awlays evaluate to false. No Impact" */
    if (DEM_FALSE == indicatorStatus)
    {
      if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR))
      {
        /* WarningIndicatorRequest bit = 0 */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        DEM_CLR_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_WIR);
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
    }
    /* polyspace-end CERT-C:MSC12-C [Justified:Low] "Because of user configuration, above for condiontion maybe awlays evaluate to false.
      indicatorStatus don't update value, this condition awlays evaluate to false. No Impact" */

    #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
    if(1 == perClear)
    {     
      Dem_EvMem_ClearPermanentDTC(EventId, 1);     
    }
    else if(2 == perClear)
    {     
      Dem_EvMem_ClearPermanentDTC(EventId, 0);     
    }
    else
    {
      /* Do Nothing */
    }
    #endif
  
  }
  
  return dirty;
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
