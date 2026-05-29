/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of Dem interface functionality                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date:DD-MM-YYYY By            Description                         **
********************************************************************************
** 3.3.4    31-12-2021    LanhLT          Changes made As per Redmine #33335  **
**                                                                            **
** 1.6.2    12-08-2020    EunKyung.Kim    Changes made As per Redmine #25205, **
**                                        #25454                              **
**                                                                            **     
** 1.6.1    01-06-2020    EunKyung.Kim    Changes made As per Redmine #20595  **
**                                                                            **     
** 1.6.0    10-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.5.3    18-11-2017     EunKyung.Kim   Changes made As per Redmine #10458  **
**                                                                            **
** 1.5.2    20-07-2017     EunKyung.Kim   Changes made As per Redmine #9294   **
**                                                                            **
** 1.5.1    06-02-2016      YoungJin.Yun  Changes made As per Redmine #7308   **
**                                                                            **
** 1.5.0    16-11-2016      YoungJin.Yun  Changes made As per Redmine #6549   **
**                                                                            **
** 1.4.0    30-09-2016      YoungJin.Yun  Changes made As per Redmine #5921   **
**                                                                            **
** 1.3.0    30-08-2016      YoungJin.Yun  Changes made As per Redmine #5011   **
**                                                                            **
** 1.2.0    15-06-2016      YoungJin.Yun  Changes made As per Redmine #1164   **
**                                                                            **
** 1.1.1    10-06-2016      YoungJin.Yun  Changes made As per Redmine #5169   **
**                                                                            **
** 1.1.0    07-01-2016      YoungJin.Yun  Changes made As per Redmine #3353,  **
**                                        #698, #3638,#2473,#3271,#2827,      **
**                                        #1151, #2589                        **
**                                                                            **
** 1.0.9    11-01-2014     YoungJin.Yun  Changes made As per Redmine #366,    **
**                                        #367,#403,#404,#406,#409,#410,#411, **
**                                        #368,#371,#372,#405,#366,#367,#368, **
**                                        #371,#372,#405,#369,#373,#374,#375, **
**                                        #376,#370,#377,#381,#382,#383,#384, **
**                                        #385,#386,#387,#388,#389,#390,#391, **
**                                        #397,#398,#399,#400,#378,#380,#401, **
**                                        #403,#404,#406,#409,#410,#411,#412  **
**                                        #412                                **
**                                                                            **
** 1.0.0    01-01-2013     Autron        Initial Version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"                   /* Dem module header file */
#if(DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Det module header file */
#endif
#include "Dem_Ram.h"              /* Dem global Ram variables header file */

#if (DEM_FIM_INTEGRATED == STD_ON)
#include "FiM.h"                  /* FiM module header file */
#endif

#if (DEM_TRIGGER_DLT_REPORTS == STD_ON)
#include "Dlt.h"                  /* Dlt module header file */
#endif

#include "NvM.h"                  /* NvM module  header File */

#include "EcuM.h"               /* Reset Reason */
#include "Mcu.h"

#include "Rte_Dem.h"
#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */

#include "Dem_EventMemory.h"
#include "Dem_Event.h"
#include "BswM.h"
#include "Dem_EventDebounce.h"
#include "Dem_Dtc.h"

#if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)
#include "Dcm.h" /* Dcm_ProgConditionsType */
#include "Dcm_CallOuts.h" /* for Dcm_GetProgConditions */
#endif


/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin RTE:UNR [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dem_GetVersionInfo                                  **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This Service returns the version information of     **
**                        Diagnostic Event Manager Module.                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
*******************************************************************************/
#if(DEM_VERSION_INFO_API == STD_ON)
FUNC(void, DEM_CODE) Dem_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, DEM_APPL_DATA)versioninfo)
{
  #if(DEM_DEV_ERROR_DETECT == STD_ON)
  /* check NULL pointer */
  if(versioninfo == NULL_PTR)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_GETVERSIONINFO_SID, DEM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* Load the vendor Id */
    versioninfo->vendorID = DEM_VENDOR_ID;
    /* Load the module Id */
    versioninfo->moduleID = DEM_MODULE_ID;
    /* Load Software Major Version */
    versioninfo->sw_major_version = DEM_SW_MAJOR_VERSION;
    /* Load Software Minor Version */
    versioninfo->sw_minor_version = DEM_SW_MINOR_VERSION;
    /* Load Software Patch Version */
    versioninfo->sw_patch_version = DEM_SW_PATCH_VERSION;
  }
}
#endif /* (DEM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : Dem_PreInit                                         **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This API shall be used to initialize the internal   **
**                        states necessary to process events reported by      **
**                        BSW-modules.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_ConfigPtr                                       **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_PreInit(P2CONST(Dem_ConfigType,
  AUTOMATIC, DEM_APPL_CONST)Dem_ConfigPtr)
{
  /*To avoid compilation warning*/
  DEM_UNUSED_PTR(Dem_ConfigPtr);

  /* Set the module to pre-initialized state */
  Dem_GucInit = DEM_UNINIT;
  
  /* BswEventQueue(Dem_InitBswEventQueue) is alrealy set to 0 */
  /* Dem_EventState(Dem_EvInitProcState) is  already set to 0 */
  
  /* page.91 of Dem SWS v4.2.0
   * During initialization of the Dem module,
   * the API Dem_ReportErrorStatus supports debouncing (pre-failed and pre-passed). 
   * The corresponding debounce counters will be initialized by calling Dem_PreInit. */
  Dem_InitDebounce();  
  
  #if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
  Dem_InitEnableConditionStatus();
  #endif    
  
  /* Initialize the storage conditions */
  #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
  /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "Not a defect" */
  Dem_InitStorageConditionStatus();
  #endif

  Dem_EvMem_PreInit();

  #if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)
  {
    Dcm_ProgConditionsType progCondition;
    
    progCondition.ApplUpdated = DEM_FALSE;
    Dem_DoReadFromNv = DEM_TRUE;    
    
    if (DCM_WARM_START == Dcm_GetProgConditions(&progCondition))
    {
      if (DCM_TRUE != progCondition.ApplUpdated)  
      {
        Mcu_ResetType resetReason = MCU_POWER_ON_RESET;    
        /* polyspace<MISRA-C:11.4:Not a defect:No action planned  defect> EcuM_GetResetReason issue */
        if (E_OK == EcuM_GetResetReason(&resetReason))
        {
          if (MCU_SW_RESET == resetReason)
          {
            Dem_DoReadFromNv = DEM_FALSE;
          }
        }
      }
    }
  }
  #endif

  /* Set the module to pre-initialized state */
  Dem_GucInit = DEM_PREINIT;
}

/*******************************************************************************
** Function Name        : Dem_PreInit2                                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This API shall be used to initialize the internal   **
**                        states necessary to process events reported by      **
**                        BSW-modules.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_ConfigPtr                                       **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_PreInit2(P2CONST(Dem_ConfigType,
  AUTOMATIC, DEM_APPL_CONST)Dem_ConfigPtr)
{
  /*To avoid compilation warning*/
  DEM_UNUSED_PTR(Dem_ConfigPtr);


  /* Set the module to pre-initialized state */
  Dem_GucInit = DEM_PREINIT2;
}

/*******************************************************************************
** Function Name        : Dem_WriteNvData                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Write Dem data to NvM                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : 1. This function is called  by BswM                 **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_WriteNvData(void)
{
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* progressing or  shutdown  */
  if ((DEM_INIT != Dem_GucInit) && (DEM_DEINIT != Dem_GucInit))
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to false */  
  {
    DEM_REPORT_ERROR(DEM_INIT_SID, DEM_E_WRONG_CONDITION);
  }
  else
  #endif
  {    
    uint8 idx;
    for (idx = 0U; idx < Dem_NumOfSupportedDTCOrigins; idx++)
    {
      /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
      Dem_DTCOriginType dtcOrigin = Dem_SupportedDTCOrigins[idx];
      Dem_NumOfEventMemoryEntryType memLoc;
      for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[dtcOrigin]; memLoc++)                 
      {
        Dem_EvMem_SetEvMemNvBlockStatus(dtcOrigin, memLoc, DEM_EVMEM_STATUS_TRIGGER_NVM|DEM_EVMEM_STATUS_FINISH_NVM);  
      }
    }      

    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_TRIGGER_NVM|DEM_EVMEM_STATUS_FINISH_NVM);
    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_GENERIC_NVRAM_DATA_ID, DEM_EVMEM_STATUS_TRIGGER_NVM|DEM_EVMEM_STATUS_FINISH_NVM);    
    Dem_EvMem_RequestWriteAllBlocks();
  }
}


/*******************************************************************************
** Function Name        : Dem_ReadNvData                                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Read Dem data from NvM                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_ReadNvData(void)
{
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  if(DEM_PREINIT2 != Dem_GucInit)
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to false */
  {
    DEM_REPORT_ERROR(DEM_INIT_SID, DEM_E_UNINIT);
  }
  else
  #endif
  {
    #if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)    
    if (DEM_FALSE == Dem_DoReadFromNv)
    {
      /* [NOTE]
       *
       * There is a high probability that ram and non-vatile data will not match
       * Therefore, we should inform the user of this fact.  */
       
       /* Dem_NonVolatileDataState,Dem_EventMemoryState
        * are cleared as 0(zero) by 'VAR CLEARED SECTION' */    
    }
    else
    #endif
    {      
      uint8 orgIdx;
      for (orgIdx = 0U; orgIdx < Dem_NumOfSupportedDTCOrigins; orgIdx++)
      {
        /* polyspace +2 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
		/* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
		Dem_DTCOriginType dtcOrigin = Dem_SupportedDTCOrigins[orgIdx]; 
        Dem_NumOfEventMemoryEntryType memLoc;      
        for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[dtcOrigin]; memLoc++)  
        {          
          Dem_EvMem_ClearEventMemoryEntry(Dem_EvMem_GetEmEntryByMemPosition(dtcOrigin, memLoc));
          #if ((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))           
          if(DEM_DTC_ORIGIN_PERMANENT_MEMORY == dtcOrigin)
          {
            Dem_EventIdType eventId = Dem_EvMem_GetEventIdByEvMemEntry(dtcOrigin,memLoc);
            Dem_EvMem_ClearPermanentDTC(eventId,1);
          }
          #endif
          
          Dem_EvMem_InitEvMemNvBlockStatus(dtcOrigin, memLoc, DEM_EVMEM_STATUS_INVALID);  
        }
      }    
      Dem_EvMem_ResetEventStatusNvRamBlock();
      Dem_EvMem_InitNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_INVALID);
    }
    /* 
     * else : Don't read the EventStatusBlock, EventMemoryEntryBlocks 
     */

    /* Dem shoud read a FootPrint Block regardless of whether S/W Reset or PowerOnReset. */
    Dem_EvMem_ResetManagementBlock(DEM_FALSE);    
    Dem_EvMem_InitNonVolatieDataStatus(DEM_NVDATA_GENERIC_NVRAM_DATA_ID, DEM_EVMEM_STATUS_INVALID);
    Dem_EvMem_RequestReadAllBlocks();    
    
    Dem_GucInit = DEM_READNVDATA;  
  }
}

/*******************************************************************************
** Function Name        : Dem_Init                                            **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : Initialization of Dem                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_Init(void)
{
  /*Dem_DTCOriginType DTCOrigin = 0u;*/

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  if ((DEM_PREINIT2 != Dem_GucInit) && (DEM_READNVDATA != Dem_GucInit))
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to false */  
  {
    DEM_REPORT_ERROR(DEM_INIT_SID, DEM_E_UNINIT);
  }
  else
  #endif
  {  
    Dem_EvMem_VerifyAllEventMemories();     
    Dem_EvMem_Init();

    /* Dem_GaaDisableDtcSettingGroupDTC, Dem_GblDisableDtcSettingAllDTC
     * are already set to 0(Enable all DTC settings)
     * Dem_GstRecordDisableDTC is already set to 0 */

    /* Dem_FilteredFFRecord is already set 0 */  
    /* Dem_GaaPrestoreBuffer(Dem_ClearAllPrestoredFreezeFrame) is already set 0 */    
  
    #if(DEM_OBD_SUPPORT == STD_ON)
    Dem_InitOBD();
    #endif

    /* Dem_GucInit shall be initialized before FiM_DemInit is called */
    Dem_GucInit = DEM_INIT;

    /* @IF_REQ:
     * [SWS_Dem_01189] In case the Fim is used, the Dem shall call Fim_DemInit during
     * Dem_Init to trigger the initalization of the permissions inside the Fim (independent of
     * trigger or polling mode). The Fim_DemInit shall not be called at any other point in time. */
    #if (DEM_FIM_INTEGRATED == STD_ON)
    FiM_DemInit();
    #endif

    /* @IF_REQ: in case of ASR 4.2.2
     * 
     * Note: All events which are reported via Dem_ReportErrorStatus before Dem_Init
     * should use a operation cycle which is auto started (DemOperationCycleAutostart set
     * to true) or persistently stored (DemOperationCycleStatusStorage set to true). */

    #if (DEM_BSW_ERROR_BUFFER_SIZE > 0U)   
    Dem_MainfunctionBswEvents();
    #endif
  }
}

/*******************************************************************************
** Function Name        : Dem_Shutdown                                        **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : Shutdown functionality of Dem                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_Shutdown(void)
{
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  if(DEM_INIT != Dem_GucInit) 
  {
    DEM_REPORT_ERROR(DEM_SHUTDOWN_SID, DEM_E_UNINIT);
  }
  else
  #endif   
  {  
    /*
     * [Dem102] The API Dem_Shutdown shall finalize all pending operations in the Dem
     * module to prepare the internal states and data for transfer to the NVRAM. The event
     * memory shall be locked and not modified until the API Dem_Init is recalled.
     * (BSW101)
     *
     * The ECU State Manager is responsible to initiate the copying process of data from
     * RAM to NVRAM (refer to API NvM_WriteAll).
     *
     * [Dem341] For individual non-volatile blocks the API NvM_WriteBlock shall be called
     * within the API Dem_Shutdown.
     *
     * If the ECU power supply is disconnected before the NvM has finished copying all
     * data to NVRAM, these data will be incomplete/inconsistent or not stored. At next
     * startup, the events of the last operating cycle could not be found anymore. Therefore,
     * the NVRAM Manager configuration provides mechanisms for data consistency, like
     * redundant data blocks.
     */

    /* if Dem_WriteNvData was called by Application, Bsw mode shall be initilaized
     * to call Dem_WriteNvData again */
    BswM_RequestMode(DEM_MODULE_ID, DEM_BSWM_MODE_DEFAULT);

    #if ((DEM_DEV_ERROR_DETECT == STD_ON) && (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_OFF))  
    /* polyspace<RTE:UNR:Not a defect:No action planned> This variable is configurable */
    /* polyspace +2 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    {
      uint8 operationCycleId = 0U;
      /* [SWS_Dem_00988] 
      * If any as volatile configured operation cycle is running 
      * (configuration parameter DemOperationCycleStatusStorage is set to false) 
      * while Dem_Shutdown is called, the Dem shall trigger the Det error
      * DEM_E_OPERATION_CYCLE_STARTED.c(SRS_Diag_04057) */
      for (operationCycleId = 0 ; operationCycleId < Dem_Num_Operation_Cycles; operationCycleId++)
      {
        /* polyspace +2 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */	  
        Dem_OperationCycleStateType cycleState = DEM_CYCLE_STATE_END;
        (void)Dem_EvMem_GetOpCycleState(operationCycleId, &cycleState);
        if (DEM_CYCLE_STATE_START == cycleState)
        {
          DEM_REPORT_ERROR(DEM_SHUTDOWN_SID,DEM_E_OPERATION_CYCLE_STARTED);
        }
      }
    }
    #endif
    
    Dem_GucInit = DEM_DEINIT;
  }
}


/*******************************************************************************
** Function Name        : Dem_MainFunction                                    **
**                                                                            **
** Service ID           : 0x55                                                **
**                                                                            **
** Description          : Interface for BSW Components to report Errors       **
**                        during start up (even before DEM initialization)    **
**                                                                            **
** Timing:              : FIXED_CYCLIC                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GblMilStarted                                   **
**                        Dem_GulTimeSinceMilOn                               **
**                        Dem_GucMilonFlag                                    **
**                        Dem_GblClearTimeStartObd                            **
**                        Dem_GulDemClearTimeCount                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        Dem_ProcessDebounceTimer                            **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_MainFunction(void)
{
  switch(Dem_GucInit)
  {
    /* main function after Dem is initialieze */
    case DEM_INIT:    
      #if(DEM_OBD_SUPPORT == STD_ON)
      Dem_MainFunctionOBD();
      #endif
    
      #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
      Dem_ProcessDebounceTimer();
      #endif
    
      #if (DEM_BSW_ERROR_BUFFER_SIZE > 0U)
      Dem_MainfunctionBswEvents();
      #endif
      
      /* Apply the filter mask and get the number of filtered DTC */
      SchM_Enter_Dem_REQUEST_DATA_PROTECTION();       
      if (Dem_DTCFilterState.dfs_JobAction == DEM_JOB_TRIGGER)
      {
        Dem_DTCFilterState.dfs_JobAction = DEM_JOB_RUNNING;
        SchM_Exit_Dem_REQUEST_DATA_PROTECTION(); 
        Dem_CountAndStoreFilterDtc();
      }
      else
      {
        SchM_Exit_Dem_REQUEST_DATA_PROTECTION();       
      }

      #if (DEM_J1939_SUPPORT == STD_ON)
      Dem_J1939MainFunction();
      #endif

      /* Dem_EvMem_MainFunctionClearDtc shall be processed before Dem_EvMem_MainFunctionWriteAll
       * to get the valid the result of NvM jobs (Dem_EvMem_GetNvmResult) */
      Dem_EvMem_MainFunctionClearDtc();

      /* Dem_WriteNvData can be called by application during Dem is running */
      Dem_EvMem_MainFunctionWriteAll();
    
      break;
    /* Dem PostInit is used, Conditions : Dem_ReadNvData shall be invoked by BswM */
    case DEM_READNVDATA:
      Dem_EvMem_MainFunctionReadAll();
      break;
    case DEM_DEINIT:
      Dem_EvMem_MainFunctionWriteAll();
      break;
    /* polyspace<RTE:UNR:Not a defect:No action planned> Default switch clause is unreachable. switch-expression */
    default: break;
  }
}
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"


/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-end RTE:UNR [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
