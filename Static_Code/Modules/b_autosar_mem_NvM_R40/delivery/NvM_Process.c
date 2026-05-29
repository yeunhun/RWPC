/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_Process.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Implementation of Internal functionality of NvM Module :      **
**              NvM_UpdateRamStateStatus                                      **
**              NvM_CalcBlkNumber                                             **
**              NvM_UpdateGlobalVars                                          **
**              NvM_EndProcessBlock                                           **
**              NvM_QueueSwap                                                 **
**              NvM_CRCSIDCancelJob                                           **
**              NvM_QueueCRCSIDblocks                                         **
**              NvM_CrcImmQueuePosClear                                       **
**              NvM_CrcStdQueuePosClear                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date           By          Description                         **
********************************************************************************
** 1.5.1       30-Dec-2020   Yun YJ       Redmine #27374                      **
** 1.3.4       11-Sep-2017   Yun YJ       Redmine #9669                       **
** 1.3.3       16-Nov-2016   Song CY      Redmine #6680                       **
** 1.3.2       10-Oct-2016   Song CY      Redmine #6215                       **
** 1.3.0       25-Jul-2016   Song CY      Redmine #3883                       **
** 1.2.6       28-Jun-2016  Song CY       Redmine #5334                       **
** 1.2.3       24-Mar-2016   Song CY      Redmine #4276                       **
** 1.2.2       11-Feb-2016  Song CY       Redmine #4183                       **
** 1.2.1       12-Jan-2016   Song CY      Redmine 3857, Change QueueClesr     **
**                                        Position before Callback            **
** 1.1.8       02-Oct-2015   Song CY      Correct RunTime Error Violation     **
** 1.1.7       09-Jul-2015  Song CY       As per RedMine 2265, Change         **
**                                        CRC & SID Logic                     **
** 1.1.6       03-Mar-2015  Song CY       As per RedMine 2209, Avoid crc block**
**                                        of rom block in dataset             **
** 1.1.6                                  As per RedMine 2216, Remove version **
**                                        Information                         **
** 1.1.4       02-Dec-2014  Song CY       RedMine 1719, Update for PolySpace  **
** 1.1.0     18-Apr-2014   Song CY     RedMine718 Version is updated          **
** 1.0.9       17-Dec-2013    Song CY   Modify Cancel Defect                  **
** 1.0.8       30-Sep-2013    Song CY   Update for Library                    **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
  polyspace-begin MISRA-C3:1.1:Not a defect:Justify with annotations> Needed for AR/SW version check
  polyspace:begin<RTE:IDP:Not a defect:Justify with annotations > configured memory access index
  polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/
/* polyspace-begin RTE:UNR [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM.h"                    /* NvM header file */
#include "NvM_Ram.h"                /* Global variables header file */
#include "NvM_Config.h"
#include "NvM_Process.h"
#include "NvM_ScanQueue.h"          /* Internal function header file */
#if(NVM_DEMERROR_REPORT == STD_ON)
#include "NvM_Dem_Cfg.h"                            /* Dem header file */
#endif
#if(NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                            /* Det header file */
#endif
/* Internal function header files */
#include "NvM_ReadAll.h"

#include "BswM_NvM.h"              /* BswM_NvM header file */
#include "SchM_NvM.h"              /* SchM_NvM header file */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : NvM_UpdateRamStateStatus                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function to change the RAM     **
**                        status                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Status                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GaaRamStatus,          **
**                        NvM_GpNvmBlkDescTbl, NvM_GddBlockIdx,               **
**                                                                            **
**                        Function(s) invoked:                                **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION()              **
*******************************************************************************/
#if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
  (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
FUNC(void, NVM_CODE) NvM_UpdateRamStateStatus(uint8 Status)
{
  if ((NvM_GpNvmBlkDescTbl != NULL_PTR) && (NvM_GddBlockIdx < NvM_GusTotalNumOfBlock))
  {
    P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
    LpRamStatus = &NvM_GaaRamStatus[NvM_GddBlockIdx];

    /*
     * Checking with NvM_GpRamAddr is required because RAM Address
     * pointer can be passed though the permanent block is configured and the
     * status maintained in this block is only for content of the RAM block
     */
    if(NvM_GpNvmBlkDescTbl->pRamBlkData != NULL_PTR)
    {
      switch (Status)
      {
        case NVM_INVALID_UNCHANGED:
          /* Set the RAM status to invalid and unchanged */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();

          *(LpRamStatus) = ((*LpRamStatus) & NVM_CLEAR_RAM_INTERNAL_STATE) |
            (NVM_INVALID_UNCHANGED);

          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        break;

        case NVM_VALID_UNCHANGED:
          /* Set the RAM status to valid and unchanged */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();

          *(LpRamStatus) = ((*LpRamStatus) & NVM_CLEAR_RAM_INTERNAL_STATE) |
            (NVM_VALID_UNCHANGED);

          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        break;

        case NVM_VALID_CHANGED:
          /* Set the RAM status to valid and changed */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();

          *(LpRamStatus) = ((*LpRamStatus) & NVM_CLEAR_RAM_INTERNAL_STATE) |
            (NVM_VALID_CHANGED);

          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        break;

        default:
          /* Do nothing */
          break;
      }

    } /* end if(NvM_GpNvmBlkDescTbl->pRamBlkData == NvM_GpRamAddr) */
  }
  else
  {
    NVM_REPORT_ERROR(NVM_CALCRCSID_SID, NVM_E_PARAM_POINTER);
  }  
} /* End of function body */

#endif

/*******************************************************************************
** Function Name        : NvM_CalcBlkNumber                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to be used to calculate the block number   **
**                        based on Block Management type.                     **
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
** Return parameter     : LusBlkNumber                                        **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GenBlkMngmntType,      **
**                        NvM_GpNvmBlkDescTbl, NvM_GddReStatus,               **
**                        NvM_GddFirstBlock                                   **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
FUNC(uint16, NVM_CODE) NvM_CalcBlkNumber(void)
{
  uint16 LusBlkNumber;

  if (NvM_GpNvmBlkDescTbl != NULL_PTR)
  {
    uint8 LucIndex;

    #if(NVM_DATASET_PRESENT == STD_ON)
    if(NvM_GenBlkMngmntType == NVM_BLOCK_DATASET)
    {
      /* Update the index to value in RAM index field */
     /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
     /* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
      LucIndex = *(NvM_GpNvmBlkDescTbl->pRamIndex);
    }
    else
    #endif
    if(NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT)
    {
      if (NvM_GddReStatus != NVM_RE_CHK_NONE)
      {
        if (NvM_GddFirstBlock != NVM_RE_COPY_FIRST)
        {
          /* Update the index to one for 2nd NV block of Redundant block */
          LucIndex = NVM_ONE;
        }
        else
        {
          LucIndex = NVM_ZERO;
        }
      }
      else
      {
        if (NvM_GddFirstBlock != NVM_RE_COPY_FIRST)
        {
          /*
           * Update the index to one for Native block and for 1st NV block of
           * Redundant block
           */
          LucIndex = NVM_ZERO;
        }
        else
        {
          LucIndex = NVM_ONE;
        }
      }
    }
    else /* (NvM_GenBlkMngmntType == NVM_BLOCK_NATIVE) */
    {
      LucIndex = NVM_ZERO;
    }
    
    LusBlkNumber = NvM_GpNvmBlkDescTbl->usNvBlkBaseNumber + LucIndex;
  }
  else
  {
    LusBlkNumber = NVM_ZERO;
    #if(NVM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_CALCRCSID_SID, NVM_E_PARAM_POINTER);
    #endif
  }
  return(LusBlkNumber);

} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_UpdateGlobalVars                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to be used to update global variables.     **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
**                                                                            **
** Remarks              :Global Variable(s)     : NvM_GenBlkMngmntType,       **
**                       NvM_GusBlockLength, NvM_GpRamAddr, NvM_GucState,     **
**                       NvM_GpNvmBlkDescTbl                                  **
**                        Function(s) invoked   : None                        **
*******************************************************************************/
FUNC(void, NVM_CODE) NvM_UpdateGlobalVars(void)
{
  /* Update the commonly used Global variables */
  if (NvM_GpNvmBlkDescTbl != NULL_PTR)
  {
    NvM_GusBlockLength = NvM_GpNvmBlkDescTbl->usNvBlkDataLength;

    NvM_GenBlkMngmntType = NvM_GpNvmBlkDescTbl->enBlkMngmntType;

    if((NvM_GucState == NVM_READALL_SID) || (NvM_GucState == NVM_WRITEALL_SID))
    {
    #if(NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON)
    /* polyspace +3 MISRA-C3:11.5 [Not a defect:Low] "No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)" */	
       NvM_GpRamAddr = (uint8*)NvM_GpNvmBlkDescTbl->pRamBlkData;
    #endif
    }
    /* Clear the Redundant status flag  */
    NvM_GddReStatus = NVM_RE_CHK_NONE;
    NvM_GddFirstBlock = NVM_RE_ORIGINAL_FIRST;
  }
  else
  {
    #if(NVM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_CALCRCSID_SID, NVM_E_PARAM_POINTER);
    #endif
  }
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_EndProcessBlock                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to end the processing of any request.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RequestResult                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GucState,              **
**                        NvM_GaaRamStatus, NvM_GddBlockIdx, NvM_GucSubState, **
**                        NvM_GucReadAllState, NvM_GblHighPriorityRequest     **
**                        NvM_GucWriteAllSubState, NvM_GucNotifiedGlobalStatus**
**                        NvM_GddReStatus, NvM_GpNvmBlkDescTbl,               **
**                        NvM_GaaBlkDescTbl, NvM_GddFirstBlock                **
**                        NvM_GblRestoreFlag, NvM_GucWriteVerify              **
**                        NvM_GusIntegrityFailed, NvM_GusReqFailed            **
**                        NvM_GucChkRedundant, NvM_GpRamAddrBackup            **
**                        Function(s) invoked    : Dem_ReportErrorStatus()    **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION,               **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION,                **
**                        BswM_NvM_CurrentBlockMode,NvM_CrcImmQueuePosClear   **
**                        NvM_CrcStdQueuePosClear                             **
*******************************************************************************/
FUNC(void, NVM_CODE) NvM_EndProcessBlock(NvM_RequestResultType
  RequestResult)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) LpBlkDescTbl;

  if (NvM_GucChkRedundant == NVM_TRUE)
  {
    NvM_GucState = NVM_WRITEBLOCK_SID;
    NvM_GucSubState = NVM_WRITE_NVBLOCK;
    NvM_GucChkRedundant = NVM_FALSE;
    NvM_GpRamAddr = NvM_GpRamAddrBackup;
    NvM_GddReStatus = NVM_RE_CHK_NONE;
  }
  else if (NvM_GddBlockIdx < NvM_GusTotalNumOfBlock)
  {
    LpBlkDescTbl = &NvM_GaaBlkDescTbl[NvM_GddBlockIdx];
    /* Clear restoreFlag */
    NvM_GblRestoreFlag = (boolean)NVM_FALSE;
    if((NvM_GucState != NVM_READALL_SID) && (NvM_GucState != NVM_WRITEALL_SID))
    {
      #if(NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1)
      #if(NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON)
      if((NvM_GucState == NVM_WRITEBLOCK_SID) &&
      (LpBlkDescTbl->ucBlkJobPriority == NVM_IMM_PRIORITY))
      {
        /* Clear the Queue for the particular request */
        NvM_ImmQueuePosClear(NvM_GddBlockIdx);
      }
      else
      #endif
      {
        NvM_StdQueuePosClear(NvM_GddBlockIdx);
      }
      #endif
    }
    else
    {
      if(RequestResult != NVM_REQ_OK)
      {
#if (NVM_DYNAMIC_CONFIGURATION == STD_OFF)
        if ( 
          (NvM_GddBlockIdx == NVM_CONFIGURATION_BLOCK_ID) &&
          (NvM_GucState == NVM_READALL_SID)
        )
        {
          /* [NVM248] The job of the function NvM_ReadAll shall ignore a configuration ID 
           * mismatch and behave normal if NvMDynamicConfiguration == FALSE [NVM028]. */
        }
        else
#endif
        {         
          /* Update the Global status in case of ReadAll/WriteAll */
           NvM_GucNotifiedGlobalStatus = NVM_REQ_NOT_OK;
        }
      }
    }
    /* Update the block specific RAM status */
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    {
      NvM_GaaRamStatus[NvM_GddBlockIdx] =
      ((NvM_GaaRamStatus[NvM_GddBlockIdx] & NVM_NOT_ERROR_BIT_MASK)
        | (RequestResult));       
    }
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    #if(NVM_DEMERROR_REPORT == STD_ON)
    if((RequestResult == NVM_REQ_NOT_OK)
      #if(NVM_WRITE_VERIFICATION == STD_ON)
      && (NvM_GucWriteVerify == NVM_ZERO)
      #endif
    )
    {
      #if(NVM_DEMERROR_REPORT == STD_ON)
      /* Report failure of job request to DEM */
      Dem_ReportErrorStatus(NvM_GusReqFailed, DEM_EVENT_STATUS_FAILED);
      #endif
    }
    else if(RequestResult == NVM_REQ_INTEGRITY_FAILED)
    {
        #if(NVM_DEMERROR_REPORT == STD_ON)
        /* Report failure of job request to DEM */
        Dem_ReportErrorStatus(NvM_GusIntegrityFailed, DEM_EVENT_STATUS_FAILED);
        #endif
    }
    else
    {
      /* Else loop added to avoid QAC warning */
    }
    #endif

    if(((LpBlkDescTbl->usBlkParams) & NVM_BSWM_BLOCK_STATUS_INFORMATION) ==
      NVM_BSWM_BLOCK_STATUS_INFORMATION)
    {
      BswM_NvM_CurrentBlockMode(NvM_GddBlockIdx, RequestResult);
    }

    #if (NVM_SINGLE_BLOCK_CALLBACK == STD_ON)
    if(LpBlkDescTbl->pNvMNotification_BlockId != NULL_PTR)
    {
      /* Invoke the single block callback notification, if configured */
      /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
      (void)LpBlkDescTbl->pNvMNotification_BlockId (NvM_GucState, RequestResult);
    }
    #endif

    /* Clear the Redundant status flag  */
    NvM_GddReStatus = NVM_RE_CHK_NONE;
    NvM_GddFirstBlock = NVM_RE_ORIGINAL_FIRST;

    /* Clear sub state */
    NvM_GucSubState = NVM_SUB_IDLE;

    if((NvM_GucState != NVM_READALL_SID) && (NvM_GucState != NVM_WRITEALL_SID))
    {
      /* Clear the main state only in case of single block requests */
      NvM_GucState = NVM_IDLE;
    }
    #if((NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) && \
        (NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))
    if (NvM_GblHighPriorityRequest == (boolean)NVM_TRUE)
    {
      if (NvM_GucReadAllState != NVM_IDLE)
      {
        NvM_GucState = NVM_READALL_SID;
        NvM_GucReadAllState = NVM_READALL_INIT;
      }
      else if (NvM_GucWriteAllSubState != NVM_WRITE_ALL_IDLE)
      {
        NvM_GucState = NVM_WRITEALL_SID;
      }
      else
      {
        /* Else loop added to avoid QAC warning */
      }
      NvM_GblHighPriorityRequest = (boolean)NVM_FALSE;
    }
    #endif
  }
  else
  {
    /* Do Nothing */
  }
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_QueueSwap                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function is to  Swap the request in the Queue       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RequestResult                                       **
**                                                                            **
** InOut parameter      : QueEnDis, QueStartPos                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LucStdQueStartPos                                   **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)

FUNC(uint8, NVM_CODE) NvM_QueueSwap(uint8 QueStartPos, uint8 QueEnDis,
  P2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA)LpQueueBuffer)
{
  uint8 LucTempIndx;
  uint8 LucTempIndx2;
  uint8 LucStdQueStartPos;

  LucTempIndx =
    LpQueueBuffer[QueStartPos].ucNextIndex;

  LucStdQueStartPos = LucTempIndx;

  LpQueueBuffer[QueStartPos].ucPreviousIndex =
     LpQueueBuffer[QueStartPos].ucNextIndex;

  LucTempIndx2 = LpQueueBuffer[LucTempIndx].ucNextIndex;
  LpQueueBuffer[LucTempIndx].ucNextIndex =
    QueStartPos;

  if(QueEnDis > NVM_TWO)
  {
    LpQueueBuffer[QueStartPos].ucNextIndex = LucTempIndx2;
    LpQueueBuffer[LucTempIndx2].ucPreviousIndex = QueStartPos;
  } /* Checking and updating the local variables */

  return(LucStdQueStartPos);
} /* End of function body */

#endif

#define NVM_STOP_SEC_CODE 
#include "MemMap.h"
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end RTE:UNR [Justified:Low] "Not a defect" */
/*
  polyspace-end MISRA-C3:1.1:Not a defect:Justify with annotations> Needed for AR/SW version check
  polyspace:end<RTE:IDP:Not a defect:Justify with annotations > configured memory access index
  polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
