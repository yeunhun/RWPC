/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_ScanQueue.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Performs Queue Write operations.                              **
**              Based on the priority, scans the corresponding queue and      **
**              invokes the respective functionality                          **
**              NvM_ScanQueue                                                 **
**              NvM_ImmQueueRead                                              **
**              NvM_StdQueueRead                                              **
**              NvM_ImmQueueWrite                                             **
**              NvM_StdQueueWrite                                             **
**              NvM_ImmQueueCancel                                            **
**              NvM_StdQueueCancel                                            **
**              NvM_StdQueuePosClear                                          **
**              NvM_ImmQueuePosClear                                          **
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
** 1.3.6       11-Sep-2017   Yun YJ       Redmine #9669                       **
** 1.3.3       16-Nov-2016   Song CY      Redmine #6680                       **
** 1.3.1       21-Sep-2016   Song CY      Redmine #6058                       **
** 1.3.0       25-Jul-2016   Song CY      Redmine #5438                       **
** 1.2.8       11-Jul-2016   Song CY      Redmine #5504                       **
** 1.2.3       24-Mar-2016   Song CY      Redmine #3884                       **
** 1.2.2       11-Feb-2016   Song CY      Redmine #4183                       **
** 1.1.7       09-Jul-2015   Song CY      Redmine #2265                       **
** 1.1.6       03-Mar-2015   Song CY      Redmine #2208, #2216                **
** 1.1.4       02-Dec-2014   Song CY      RedMine #1719                       **
** 1.1.0       18-Apr-2014   Song CY      RedMine #717, #743                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
  polyspace:begin<RTE:IDP:Not a defect:Justify with annotations > configured memory access index
  polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/
/* polyspace-begin RTE:UNR [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM.h"                   /* NvM header file */
#include "NvM_Ram.h"               /* Global variables header file */
#include "NvM_Config.h"

#if(NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                            /* Det header file */
#endif
/* Internal function header files */
#include "NvM_Process.h"
#include "NvM_ScanQueue.h"
#include "NvM_EraseInvalidate.h"
#include "NvM_RestoreBlock.h"
#include "NvM_ReadBlock.h"
#include "NvM_Write.h"
#include "NvM_CRCStatic.h"

#include "SchM_NvM.h"               /* SchM_NvM header file*/

/*******************************************************************************
**                   Function Definitions                                     **
*******************************************************************************/

static FUNC(NvM_JobQueuePtrType, NVM_CODE)
  NvM_StdQueueRead(void);

#define NVM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : NvM_ScanQueue                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the scanning operation of all     **
**                        the queues and triggers the task according to the   **
**                        priority                                            **
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
** Return parameter     : LblStatus                                           **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblPrevReqImm,         **
**                        NvM_GstStdPrevReq, NvM_GpNvmBlkDescTbl, NvM_GucState**
**                        NvM_GaaBlkDescTbl, NvM_GpRamAddr, NvM_GddBlockIdx,  **
**                        NvM_GucSubState, NvM_GucRetryCount,                 **
**                        NvM_GucChkRedundant, NvM_GpRamAddrBackup            **
**                        Function(s) invoked    : NvM_StdQueueRead(),        **
**                        NvM_UpdateGlobalVars(), NvM_UpdateRamStateStatus(), **
**                        NvM_ProcessWriteBlock(), NvM_ProcessEraseInvalidBlk,**
**                        NvM_ProcessReadBlock(), NvM_ProcessRestoreBlock()   **
**                        Gpt_DisableNotification(), Gpt_StopTimer()          **
**                        Gpt_EnableNotification(), Gpt_StartTimer()          **
*******************************************************************************/

#if(NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1)

FUNC(boolean, NVM_CODE) NvM_ScanQueue(void)
{
  P2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) LpJobqueueval;
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  boolean LblStatus;
  LblStatus = (boolean)NVM_FALSE;

  #if((NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))
  /* If a standard request was pre-empted by a immediate priority request */
  if(NvM_GblPrevReqImm == (boolean)NVM_TRUE)
  {
    /* Process the previously aborted stored standard request */
    LpJobqueueval = &NvM_GstStdPrevReq;
    NvM_GblPrevReqImm = (boolean)NVM_FALSE;
  }
  else
  #endif
  {
    /* Process the request in the standard queue */
    LpJobqueueval = NvM_StdQueueRead();
  }

  if(LpJobqueueval != NULL_PTR)
  {
    /* Update the flag to indicate job request is present in standard queue */
    LblStatus = (boolean)NVM_TRUE;

    /* Store the Service Id and Block Id of the current request */
    NvM_GstStdPrevReq.ucService_Id = (LpJobqueueval->ucService_Id);
    NvM_GstStdPrevReq.ddBlock_Idx = (LpJobqueueval->ddBlock_Idx);
    NvM_GddBlockIdx = LpJobqueueval->ddBlock_Idx;

    /*
     * Update the global pointer to point to the block index of the block
     * to be processed
     */
    /* NvM_GddBlockIdx is zero, it detects when calling memif function */
    if(NvM_GddBlockIdx < NvM_GusTotalNumOfBlock)
    {
      NvM_GpNvmBlkDescTbl = &NvM_GaaBlkDescTbl[NvM_GddBlockIdx];
      LpRamStatus = &NvM_GaaRamStatus[NvM_GddBlockIdx];
      /* polyspace +3 MISRA-C3:11.5 [Not a defect:Low] "No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)" */
      /* polyspace +3 MISRA-C3:11.8 [Not a defect:Low] "No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)" */
      NvM_GpRamAddr = (uint8 *)((void*)(LpJobqueueval->pTempRamBlkData));

      #if(NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
      if((NvM_GpNvmBlkDescTbl->usBlkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)
      == NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)
      {
        NvM_GpRamAddr = NvM_GaaMirrorBuffer;
      }
      else
      #endif
      {
        if(NvM_GpRamAddr == NULL_PTR)
        {
          #if(NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON)
          if(NvM_GpNvmBlkDescTbl->pRamBlkData != NULL_PTR)
          {
	    /* polyspace +3 MISRA-C3:11.5 [Not a defect:Low] "No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)" */
            NvM_GpRamAddr = (uint8*)NvM_GpNvmBlkDescTbl->pRamBlkData;
          }
          #endif
        }
      }
      NvM_UpdateGlobalVars();
      NvM_GucState = NvM_GstStdPrevReq.ucService_Id;
      if (NvM_GucState == NVM_WRITEBLOCK_SID)
      {
        if ((*(LpRamStatus) & NVM_CHECK_NEED_REDUNDANT_MASK) == NVM_CHECK_NEED_REDUNDANT_MASK)
        {
          NvM_GucState = NVM_READBLOCK_SID;
          NvM_GucChkRedundant = NVM_TRUE;
          NvM_GpRamAddrBackup = NvM_GpRamAddr;
          NvM_GpRamAddr = NvM_GaaDataBuffer;
        }
      }
      /* Based on the service request, update the main state and sub state */
      switch (NvM_GucState)
      {
        case NVM_WRITEBLOCK_SID:
          /* Load the retry counter */
          NvM_GucRetryCount = NvM_GpNvmBlkDescTbl->ucMaxNumOfWriteRetries;
          NvM_GucSubState = NVM_WRITE_NVBLOCK;
          #if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
              (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
            NvM_UpdateRamStateStatus(NVM_VALID_CHANGED);
          #endif
          NvM_ProcessWriteBlock();
        break;

        case NVM_READBLOCK_SID:
          NvM_GucSubState = NVM_READ_START;
          #if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
              (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
            NvM_UpdateRamStateStatus(NVM_INVALID_UNCHANGED);
          #endif
          NvM_GucRetryCount = NvM_GpNvmBlkDescTbl->ucMaxNumOfReadRetries;
          NvM_ProcessReadBlock();
        break;

        case NVM_RESTOREBLOCKDEFAULTS_SID:
          #if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
           (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
          NvM_UpdateRamStateStatus(NVM_INVALID_UNCHANGED);
          #endif
          NvM_ProcessRestoreBlock();
        break;
        #if(NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3)
        /* Update the sub states to process erase request */
        case NVM_ERASENVBLOCK_SID :
          NvM_GucState = NVM_ERASENVBLOCK_SID;
          NvM_GucSubState = NVM_ERASEINVALIDATE_START;
          NvM_ProcessEraseInvalidBlk();
        break;
        #endif

        #if( NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3)
        case NVM_INVALIDATENVBLOCK_SID:
          NvM_GucSubState = NVM_ERASEINVALIDATE_START;
          NvM_ProcessEraseInvalidBlk();
        break;
        #endif
        default:
          /* Do nothing */
          break;
      }  /* end switch (NvM_GucState) */
    }
    #if(NVM_DEV_ERROR_DETECT == STD_ON)
    else
    {
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_CALCRCSID_SID, NVM_E_PARAM_DATA);
    }
    #endif
  }  /* end if(LpJobqueueval != NULL_PTR) */

  return (LblStatus);
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) */

/*******************************************************************************
** Function Name        : NvM_ImmQueueRead                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the read operation of             **
**                        Immediate queues                                    **
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
** Return parameter     : LpDataPtr                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GucImmQueEnDis,        **
**                        NvM_GaaImmQueueBuffer, NvM_GucImmQueStartPos,       **
**                        NvM_GblQueueShuffle                                 **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#if((NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) && \
 (NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))

FUNC(NvM_JobQueuePtrType, NVM_CODE)
  NvM_ImmQueueRead(void)
{
  P2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) LpDataPtr;
  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
  if((NvM_GucImmQueEnDis != NVM_ZERO)&&
     (NvM_GucImmQueStartPos<NvM_GucSizeImmediateJobQueue))
  {
    if(NvM_GucImmQueEnDis == NVM_ONE)
    {
      LpDataPtr = &NvM_GaaImmQueueBuffer[NvM_GucImmQueStartPos];
      NvM_GucImmQueEnDis--;
    }
    else
    {
      LpDataPtr = &NvM_GaaImmQueueBuffer[NvM_GucImmQueStartPos];
      #if (NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
      if(NvM_GblQueueShuffle == NVM_FALSE)
      #endif
      {
        NvM_GucImmQueStartPos =
          NvM_GaaImmQueueBuffer[NvM_GucImmQueStartPos].ucNextIndex;
        NvM_GucImmQueEnDis--;
      }
      #if (NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
      else
      {
        NvM_GblQueueShuffle = (boolean)NVM_FALSE;
      }
      #endif
    }
  }
  else
  {
      LpDataPtr = (P2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA))NULL_PTR;
  }
  SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  return(LpDataPtr);

} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) */

/*******************************************************************************
** Function Name        : NvM_StdQueueRead                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the read operation of             **
**                        Standard queues                                     **
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
** Return parameter     : LpDataPtr                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GucStdQueEnDis,        **
**                        NvM_GaaStdQueueBuffer, NvM_GblQueueShuffle,         **
**                        NvM_GucStdQueStartPos                               **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1)

static FUNC(NvM_JobQueuePtrType, NVM_CODE)
  NvM_StdQueueRead(void)
{
  P2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) LpDataPtr;
  #if(NVM_JOB_PRIORITIZATION == STD_ON)
  uint8 LucCurrentIndex;
  uint8 LucLastIndex;
  uint8 LucHighestPriority;
  uint8 LucHighestPriorityIndex; 
  uint8 LucTempStartPosition;
  uint16 LusLoopCnt;
  
  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
  LucCurrentIndex = NvM_GucStdQueStartPos;
  LucLastIndex = NvM_GucStdQueEndPos;
  SchM_Exit_NvM_RAM_STATUS_PROTECTION();

  /* Find Highest Priority */
  if (LucCurrentIndex < NvM_GucSizeStadardJobQueue)
  {
    LucHighestPriority = NvM_GaaStdQueueBuffer[LucCurrentIndex].ucPriority;
    LucHighestPriorityIndex = LucCurrentIndex;
  
    LusLoopCnt = NVM_ZERO;
    do {
      if (LucCurrentIndex == LucLastIndex)
      {
        LusLoopCnt = NvM_GucSizeStadardJobQueue;
      }

      if (LucCurrentIndex < NvM_GucSizeStadardJobQueue)
      {
        if(LucHighestPriority>NvM_GaaStdQueueBuffer[LucCurrentIndex].ucPriority)
        {
          LucHighestPriorityIndex = LucCurrentIndex;
          LucHighestPriority = NvM_GaaStdQueueBuffer[LucCurrentIndex].ucPriority;
        }
        LucCurrentIndex = NvM_GaaStdQueueBuffer[LucCurrentIndex].ucNextIndex;
      }
      LusLoopCnt++;
    }while ((LusLoopCnt < NvM_GucSizeStadardJobQueue));
  #endif

    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    if((NvM_GucStdQueEnDis != NVM_ZERO)&&
       (NvM_GucStdQueStartPos<NvM_GucSizeStadardJobQueue)
       #if(NVM_JOB_PRIORITIZATION == STD_ON)
       /* prepare for cancel */
       &&(NvM_GaaStdQueueBuffer[LucHighestPriorityIndex].ddBlock_Idx != NVM_ZERO)
       #endif
       )
    {
      if(NvM_GucStdQueEnDis == NVM_ONE)
      {
        LpDataPtr = &NvM_GaaStdQueueBuffer[NvM_GucStdQueStartPos];
        NvM_GucStdQueEnDis--;
      }
      else
      {
        #if(NVM_JOB_PRIORITIZATION == STD_ON)
        LucTempStartPosition = NvM_GucStdQueStartPos;
        NvM_GucStdQueStartPos = 
            NvM_GaaStdQueueBuffer[LucHighestPriorityIndex].ucNextIndex;
        NvM_GucStdQueEndPos = 
            NvM_GaaStdQueueBuffer[LucHighestPriorityIndex].ucPreviousIndex;
        LpDataPtr = &NvM_GaaStdQueueBuffer[LucHighestPriorityIndex];
        #else
        LpDataPtr = &NvM_GaaStdQueueBuffer[NvM_GucStdQueStartPos];
        #endif
        #if (NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
        if(NvM_GblQueueShuffle == NVM_FALSE)
        #endif
        {
          #if(NVM_JOB_PRIORITIZATION == STD_ON)
          if (LucTempStartPosition == NvM_GucStdQueStartPos)
          {
            if (NvM_GucStdQueEnDis <= NVM_TWO)
            {
              NvM_GucStdQueStartPos =
              NvM_GaaStdQueueBuffer[NvM_GucStdQueStartPos].ucNextIndex;
            }
          }
          #else
          NvM_GucStdQueStartPos =
            NvM_GaaStdQueueBuffer[NvM_GucStdQueStartPos].ucNextIndex;
          #endif
          NvM_GucStdQueEnDis--;
        }
        #if (NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
        else
        {
          NvM_GblQueueShuffle = (boolean)NVM_FALSE;
        }
        #endif
      }
    }
    else
    {
      LpDataPtr = (P2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA))NULL_PTR;
    }
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  #if(NVM_JOB_PRIORITIZATION == STD_ON)
  }
  else
  {
    #if(NVM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_CALCRCSID_SID, NVM_E_PARAM_DATA);
    #endif
    LpDataPtr = (P2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA))NULL_PTR;
  }
  #endif
  
  return(LpDataPtr);
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) */

/*******************************************************************************
** Function Name        : NvM_ImmQueueWrite                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the write operation of Immediate  **
**                        queue                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LpDataPtr                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddPutQueueResult                                   **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GaaRamStatus,          **
**                        NvM_GucImmQueStatus, NvM_GucImmQueEnDis,            **
**                        NvM_GaaImmFreeList, NvM_GaaImmQueueBuffer,          **
**                        NvM_GucImmQueStartPos, NvM_GucImmQueEndPos          **
**                        NvM_GucImmFreeIndx                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION()              **
*******************************************************************************/

#if((NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) && \
    (NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))

FUNC(Std_ReturnType, NVM_CODE) NvM_ImmQueueWrite(
  CONSTP2CONST(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) LpDataPtr)
{
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  Std_ReturnType LddPutQueueResult;
  uint8 LucPresentIndex;

  LddPutQueueResult = E_NOT_OK;

  if (LpDataPtr->ddBlock_Idx < NvM_GusTotalNumOfBlock)
  {  
    LpRamStatus = &NvM_GaaRamStatus[LpDataPtr->ddBlock_Idx];
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    if((NvM_GucImmFreeSlotsAvail != NVM_ZERO) &&
       (NvM_GucImmFreeIndx<NvM_GucSizeImmediateJobQueue))
    {
        LucPresentIndex = NvM_GaaImmFreeList[NvM_GucImmFreeIndx];
      if ((LucPresentIndex < NvM_GucSizeImmediateJobQueue)
          &&(NvM_GucImmQueEndPos< NvM_GucSizeImmediateJobQueue))
      {
        if(NvM_GucImmQueEnDis == NVM_ZERO)
        {
          NvM_GaaImmQueueBuffer[LucPresentIndex].ddBlock_Idx =
            LpDataPtr->ddBlock_Idx;
          NvM_GaaImmQueueBuffer[LucPresentIndex].ucService_Id =
            LpDataPtr->ucService_Id;
          NvM_GaaImmQueueBuffer[LucPresentIndex].pTempRamBlkData =
            LpDataPtr->pTempRamBlkData;

          NvM_GucImmQueEnDis++;

          NvM_GucImmQueStartPos = LucPresentIndex;
          NvM_GucImmQueEndPos = LucPresentIndex;
        }
        else
        {
          NvM_GaaImmQueueBuffer[LucPresentIndex].ddBlock_Idx =
            LpDataPtr->ddBlock_Idx;
          NvM_GaaImmQueueBuffer[LucPresentIndex].ucService_Id =
            LpDataPtr->ucService_Id;
          NvM_GaaImmQueueBuffer[LucPresentIndex].pTempRamBlkData =
            LpDataPtr->pTempRamBlkData;
          NvM_GaaImmQueueBuffer[LucPresentIndex].ucPreviousIndex =
            NvM_GucImmQueEndPos;
          NvM_GaaImmQueueBuffer[NvM_GucImmQueEndPos].ucNextIndex = LucPresentIndex;

          NvM_GucImmQueEnDis++;
          NvM_GucImmQueEndPos = LucPresentIndex;
        }

        *(LpRamStatus) = (*(LpRamStatus) & NVM_NOT_ERROR_BIT_MASK ) |
          (NVM_REQ_PENDING);

        LddPutQueueResult = E_OK;
        /* polyspace +3 MISRA-C3:14.3 [Justified:Low] "NvM_GucImmFreeIndx is initialized to a non-zero value in the NvM_Init" */
        /* polyspace +2 MISRA-C3:2.1 [Justified:Low] "NvM_GucImmFreeIndx is initialized to a non-zero value in the NvM_Init" */
        if (NvM_GucImmFreeIndx > NVM_ZERO)
        {
          NvM_GucImmFreeIndx--;
        }
        else
        {
          NvM_GucImmFreeIndx = NVM_FF;
        }
        
        NvM_GucImmFreeSlotsAvail--;        
      }
    }
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  }
  else
  {
    NVM_REPORT_ERROR(NVM_MAINFUNCTION_SID, NVM_E_PARAM_POINTER);
  }
  
  return(LddPutQueueResult);
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) */

/*******************************************************************************
** Function Name        : NvM_StdQueueWrite                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the write operation of Standerd   **
**                        queue                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpDataPtr                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddPutQueueResult                                   **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GaaRamStatus,          **
**                        NvM_GucStdQueEnDis, NvM_GaaStdFreeList,             **
**                        NvM_GaaStdQueueBuffer, NvM_GucStdQueStartPos,       **
**                        NvM_GucStdQueEndPos, NvM_GucStdQueStatus            **
**                        NvM_GucStdFreeIndx                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION()              **
*******************************************************************************/
#if(NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1)

FUNC(Std_ReturnType, NVM_CODE) NvM_StdQueueWrite(
  CONSTP2CONST(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) LpDataPtr)
{
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  Std_ReturnType LddPutQueueResult;
  uint8 LucPresentIndex;

  LddPutQueueResult = E_NOT_OK;

  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
  if(
    (NULL_PTR != LpDataPtr) &&
    (LpDataPtr->ddBlock_Idx < NVM_TOTAL_NUM_OF_NVRAM_BLOCKS) &&
    (NvM_GucStdFreeSlotsAvail != NVM_ZERO) &&
    (NvM_GucStdFreeIndx<NvM_GucSizeStadardJobQueue)
  )
  {
    LpRamStatus = &NvM_GaaRamStatus[LpDataPtr->ddBlock_Idx];
  
    LucPresentIndex = NvM_GaaStdFreeList[NvM_GucStdFreeIndx];
    if ((LucPresentIndex < NvM_GucSizeStadardJobQueue)
        &&(NvM_GucStdQueEndPos< NvM_GucSizeStadardJobQueue)
        &&(NvM_GucStdQueStartPos< NvM_GucSizeStadardJobQueue))
    {
      if(NvM_GucStdQueEnDis == NVM_ZERO)
      {
        NvM_GaaStdQueueBuffer[LucPresentIndex].ddBlock_Idx =
          LpDataPtr->ddBlock_Idx;
        NvM_GaaStdQueueBuffer[LucPresentIndex].ucService_Id =
          LpDataPtr->ucService_Id;
        NvM_GaaStdQueueBuffer[LucPresentIndex].pTempRamBlkData =
          LpDataPtr->pTempRamBlkData;
        #if((NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) && \
            (NVM_JOB_PRIORITIZATION == STD_ON))
        NvM_GaaStdQueueBuffer[LucPresentIndex].ucPriority =
          LpDataPtr->ucPriority;
        #endif
        NvM_GucStdQueEnDis++;
        NvM_GucStdQueStartPos = LucPresentIndex;
        NvM_GucStdQueEndPos = LucPresentIndex;
      }
      else
      {
        NvM_GaaStdQueueBuffer[LucPresentIndex].ddBlock_Idx =
          LpDataPtr->ddBlock_Idx;
        NvM_GaaStdQueueBuffer[LucPresentIndex].ucService_Id =
          LpDataPtr->ucService_Id;
        NvM_GaaStdQueueBuffer[LucPresentIndex].pTempRamBlkData =
          LpDataPtr->pTempRamBlkData;
        #if((NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) && \
            (NVM_JOB_PRIORITIZATION == STD_ON))
        NvM_GaaStdQueueBuffer[LucPresentIndex].ucPriority =
          LpDataPtr->ucPriority;
        #endif
        NvM_GaaStdQueueBuffer[LucPresentIndex].ucPreviousIndex =
          NvM_GucStdQueEndPos;
        NvM_GaaStdQueueBuffer[NvM_GucStdQueEndPos].ucNextIndex = LucPresentIndex;

        NvM_GucStdQueEndPos = LucPresentIndex;
        NvM_GucStdQueEnDis++;
        NvM_GaaStdQueueBuffer[LucPresentIndex].ucNextIndex =
          NvM_GucStdQueStartPos;
        NvM_GaaStdQueueBuffer[NvM_GucStdQueStartPos].ucPreviousIndex =
          NvM_GucStdQueEndPos;
      }

      *(LpRamStatus) = (*(LpRamStatus) & NVM_NOT_ERROR_BIT_MASK ) |
        (NVM_REQ_PENDING);

      LddPutQueueResult = E_OK;
      /* polyspace +3 MISRA-C3:14.3 [Justified:Low] "NvM_GucStdFreeIndx is initialized to a non-zero value in the NvM_Init" */
      /* polyspace +2 MISRA-C3:2.1 [Justified:Low] "NvM_GucStdFreeIndx is initialized to a non-zero value in the NvM_Init" */
      if (NvM_GucStdFreeIndx > NVM_ZERO)
      {
        NvM_GucStdFreeIndx--;
      }
      else
      {
        NvM_GucStdFreeIndx = NVM_FF;
      }
      NvM_GucStdFreeSlotsAvail--;
    }
  }
  SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  return(LddPutQueueResult);
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) */

/*******************************************************************************
** Function Name        : NvM_ImmQueueCancel                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the Immediate QueueCancel         **
**                        operation                                           **
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
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GucImmQueEnDis,        **
**                        NvM_GaaImmQueueBuffer, NvM_GucImmQueStartPos,       **
**                        NvM_GucImmQueEndPos, NvM_GucImmFreeIndx,            **
**                        NvM_GucImmQueStatus, NvM_GucStdQueStartPos          **
**                        NvM_GaaImmFreeList                                  **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if((NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) && \
    (NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))

FUNC(Std_ReturnType, NVM_CODE) NvM_ImmQueueCancel(NvM_BlockIdType
  BlockId)
{
  Std_ReturnType LddReturnValue;
  uint8 LucIndex;
  uint8 LucTempIndx;
  boolean LucLoopSts;
  LddReturnValue = E_NOT_OK;

  if(NvM_GucImmQueEnDis != NVM_ZERO)
  {
    LucIndex = NvM_GucImmQueStartPos;
    LucLoopSts = (boolean)NVM_FALSE;

    while((LucLoopSts == NVM_FALSE) &&
          (LucIndex < NvM_GucSizeImmediateJobQueue))
    {
      if(NvM_GaaImmQueueBuffer[LucIndex].ddBlock_Idx == BlockId)
      {
        SchM_Enter_NvM_RAM_STATUS_PROTECTION();
        /* Prepare QueuePosition Clear */
        if(NvM_GaaImmQueueBuffer[LucIndex].ddBlock_Idx != NVM_ZERO)
        {
          LddReturnValue = E_OK;
          NvM_GaaImmQueueBuffer[LucIndex].ddBlock_Idx=NVM_ZERO;
          NvM_GaaImmQueueBuffer[LucIndex].ucPriority=NVM_FF;
          if((LucIndex == NvM_GucImmQueStartPos) &&
            (LucIndex == NvM_GucImmQueEndPos))
          {
            /* Do Nothing */
          }
          else if(LucIndex == NvM_GucImmQueStartPos)
          {
            NvM_GucImmQueStartPos =
              NvM_GaaImmQueueBuffer[LucIndex].ucNextIndex;
          }
          else if(LucIndex == NvM_GucImmQueEndPos)
          {
            NvM_GucImmQueEndPos =
              NvM_GaaImmQueueBuffer[LucIndex].ucPreviousIndex;
          }
          else
          {
            LucTempIndx = NvM_GaaImmQueueBuffer[LucIndex].ucPreviousIndex;
            if (LucTempIndx < NvM_GucSizeImmediateJobQueue)
            {
              NvM_GaaImmQueueBuffer[LucTempIndx].ucNextIndex =
               NvM_GaaImmQueueBuffer[LucIndex].ucNextIndex;
            }
            LucTempIndx = NvM_GaaImmQueueBuffer[LucIndex].ucNextIndex;
            if (LucTempIndx < NvM_GucSizeImmediateJobQueue)
            {
              NvM_GaaImmQueueBuffer[LucTempIndx].ucPreviousIndex =
                NvM_GaaImmQueueBuffer[LucIndex].ucPreviousIndex;
            }
          }
        /* polyspace +3 MISRA-C3:14.3 [Justified:Low] "NvM_GucImmFreeIndx is initialized to a non-zero value in the NvM_Init" */
        /* polyspace +2 MISRA-C3:2.1 [Justified:Low] "NvM_GucImmFreeIndx is initialized to a non-zero value in the NvM_Init" */
          if ((NvM_GucImmFreeIndx < (NvM_GucSizeImmediateJobQueue - NVM_ONE))
                && (LucIndex < NvM_GucSizeImmediateJobQueue))
          {
            NvM_GucImmFreeIndx++;
          }
          else
          {
            NvM_GucImmFreeIndx = NVM_ZERO;
          }

          NvM_GucImmFreeSlotsAvail++;
          NvM_GucImmQueEnDis--;
          NvM_GaaImmFreeList[NvM_GucImmFreeIndx] = LucIndex;
          LucIndex = NvM_GucImmQueEndPos;
        }
        SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      }
      if(LucIndex == NvM_GucImmQueEndPos)
      {
        LucLoopSts = (boolean)NVM_TRUE;
      }
      if (LucIndex < NvM_GucSizeImmediateJobQueue)
      {
        LucIndex = NvM_GaaImmQueueBuffer[LucIndex].ucNextIndex;
      }
    }
  }
  return(LddReturnValue);
} /* End of function body */

#endif

/*******************************************************************************
** Function Name        : NvM_StdQueueCancel                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the  operation of Standard        **
**                        queue Cancel operation                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GucStdQueEnDis,        **
**                        NvM_GucStdQueStartPos, NvM_GaaStdQueueBuffer,       **
**                        NvM_GucStdQueEndPos, NvM_GucStdFreeIndx,            **
**                        NvM_GucStdQueStatus, NvM_GaaStdFreeList             **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1)

FUNC(Std_ReturnType, NVM_CODE) NvM_StdQueueCancel(NvM_BlockIdType
  BlockId)
{
  Std_ReturnType LddReturnValue;
  uint8 LucIndex;
  uint8 LucTempIndx;
  boolean LucLoopSts;

  LddReturnValue = E_NOT_OK;

  if(NvM_GucStdQueEnDis != NVM_ZERO)
  {
      LucIndex = NvM_GucStdQueStartPos;
      LucLoopSts = (boolean)NVM_FALSE;
      while((LucLoopSts == NVM_FALSE) &&
            (LucIndex < NvM_GucSizeStadardJobQueue))
      {
        if(NvM_GaaStdQueueBuffer[LucIndex].ddBlock_Idx == BlockId)
        {
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          /* Prepare QueuePosition Clear */
          if(NvM_GaaStdQueueBuffer[LucIndex].ddBlock_Idx != NVM_ZERO)
          {
            /* Bugzilla Reference #45540 */
            LddReturnValue = E_OK;
            NvM_GaaStdQueueBuffer[LucIndex].ddBlock_Idx=NVM_ZERO;
            #if(NVM_JOB_PRIORITIZATION == STD_ON)
            NvM_GaaStdQueueBuffer[LucIndex].ucPriority=NVM_FF;
            #endif
            if((LucIndex == NvM_GucStdQueStartPos) &&
              (LucIndex == NvM_GucStdQueEndPos))
            {
              /* Do Nothing */
            }
            else if(LucIndex == NvM_GucStdQueStartPos)
            {
              NvM_GucStdQueStartPos =
                NvM_GaaStdQueueBuffer[LucIndex].ucNextIndex;
            }
            else if(LucIndex == NvM_GucStdQueEndPos)
            {
              NvM_GucStdQueEndPos =
                NvM_GaaStdQueueBuffer[LucIndex].ucPreviousIndex;
            }
            else
            {
              /* Do Nothing */
            }

            LucTempIndx = NvM_GaaStdQueueBuffer[LucIndex].ucPreviousIndex;
            if (LucTempIndx < NvM_GucSizeStadardJobQueue)
            {
              NvM_GaaStdQueueBuffer[LucTempIndx].ucNextIndex =
                NvM_GaaStdQueueBuffer[LucIndex].ucNextIndex;
            }
            LucTempIndx = NvM_GaaStdQueueBuffer[LucIndex].ucNextIndex;
            if (LucTempIndx < NvM_GucSizeStadardJobQueue)
            {
              NvM_GaaStdQueueBuffer[LucTempIndx].ucPreviousIndex =
                NvM_GaaStdQueueBuffer[LucIndex].ucPreviousIndex;
            }
            /* polyspace +3 MISRA-C3:14.3 [Justified:Low] "NvM_GucStdFreeIndx is initialized to a non-zero value in the NvM_Init" */
            /* polyspace +2 MISRA-C3:2.1 [Justified:Low] "NvM_GucStdFreeIndx is initialized to a non-zero value in the NvM_Init" */
            if ((NvM_GucStdFreeIndx < (NvM_GucSizeStadardJobQueue - NVM_ONE))
                && (LucIndex < NvM_GucSizeStadardJobQueue))
            {
              NvM_GucStdFreeIndx++;
            }
            else
            {
              NvM_GucStdFreeIndx = NVM_ZERO;
            }

            NvM_GucStdFreeSlotsAvail++;
            NvM_GucStdQueEnDis--;
            NvM_GaaStdFreeList[NvM_GucStdFreeIndx] = LucIndex;
            LucIndex = NvM_GucStdQueEndPos;
          }
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        }
        if(LucIndex == NvM_GucStdQueEndPos)
        {
          LucLoopSts = (boolean)NVM_TRUE;
        }
        if (LucIndex < NvM_GucSizeStadardJobQueue)
        {
          LucIndex = NvM_GaaStdQueueBuffer[LucIndex].ucNextIndex;
        }
      }
  }
  return(LddReturnValue);
} /* End of function body */

#endif

/*******************************************************************************
** Function Name        : NvM_StdQueuePosClear                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the  operation of Standard        **
**                        queue position  clear operation                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        NvM_GucStdQueStartPos, NvM_GaaStdQueueBuffer,       **
**                        NvM_GucStdQueEndPos, NvM_GucStdFreeIndx,            **
**                        NvM_GucStdQueStatus, NvM_GaaStdFreeList             **
**                        NvM_GucSizeStadardJobQueue                          **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

FUNC(void, NVM_CODE) NvM_StdQueuePosClear(NvM_BlockIdType
  BlockId)
{
  uint8 LucIndex;
  uint8  LucIndex1;
  boolean LucLoopSts;

  LucIndex = NVM_ZERO;
  LucIndex1 = NVM_ZERO;

  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if (BlockId == NVM_ZERO)
  {
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_MAINFUNCTION_SID, NVM_E_PARAM_DATA);
  }
  #endif

  while(LucIndex < NvM_GucSizeStadardJobQueue)
  {
    if(NvM_GaaStdQueueBuffer[LucIndex].ddBlock_Idx == BlockId)
    {
      LucIndex1 = LucIndex;
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_GaaStdQueueBuffer[LucIndex].ddBlock_Idx=NVM_ZERO;
      #if(NVM_JOB_PRIORITIZATION == STD_ON)
      NvM_GaaStdQueueBuffer[LucIndex].ucPriority=NVM_FF;
      #endif
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      break;
    }
    LucIndex++;
  }

  LucLoopSts = (boolean)NVM_FALSE;

  while(LucLoopSts == NVM_FALSE)
  {
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    if(LucIndex1 == NvM_GucStdQueStartPos)
    {
      NvM_GucStdQueStartPos =
        NvM_GaaStdQueueBuffer[LucIndex1].ucNextIndex;
    }
    else if(LucIndex1 == NvM_GucStdQueEndPos)
    {
      NvM_GucStdQueEndPos =
        NvM_GaaStdQueueBuffer[LucIndex1].ucPreviousIndex;
    }
    else
    {
      #if(NVM_JOB_PRIORITIZATION == STD_ON)
      /* redmine 5438 */
      if (NvM_GucStdQueEndPos < NvM_GucSizeStadardJobQueue)
      {
        NvM_GaaStdQueueBuffer[NvM_GucStdQueEndPos].ucNextIndex = NvM_GucStdQueStartPos;
      }
      if (NvM_GucStdQueStartPos < NvM_GucSizeStadardJobQueue)
      {
        NvM_GaaStdQueueBuffer[NvM_GucStdQueStartPos].ucPreviousIndex = NvM_GucStdQueEndPos;
      }
      #endif
    }
    /* polyspace +3 MISRA-C3:14.3 [Justified:Low] "NvM_GucStdFreeIndx is initialized to a non-zero value in the NvM_Init" */
    /* polyspace +2 MISRA-C3:2.1 [Justified:Low] "NvM_GucStdFreeIndx is initialized to a non-zero value in the NvM_Init" */
    if ((NvM_GucStdFreeIndx < (NvM_GucSizeStadardJobQueue - NVM_ONE))
        && (LucIndex1 < NvM_GucSizeStadardJobQueue))
    {
      NvM_GucStdFreeIndx++;
    }
    else
    {
      NvM_GucStdFreeIndx = NVM_ZERO;
    }
    NvM_GucStdFreeSlotsAvail++;
    NvM_GaaStdFreeList[NvM_GucStdFreeIndx] = LucIndex1;
    LucLoopSts = (boolean)NVM_TRUE;
    LucIndex1 = NvM_GaaStdQueueBuffer[LucIndex1].ucNextIndex;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  }
}

#endif

/*******************************************************************************
** Function Name        : NvM_ImmQueuePosClear                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the  operation of Immediate       **
**                        queue position clear operation                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     :NvM_GaaImmQueueBuffer       **
**                         NvM_GucImmQueStartPos,NvM_GucImmQueStatus,         **
**                         NvM_GucImmFreeIndx, NvM_GaaImmFreeList,            **
**                         NvM_GucImmFreeSlotsAvail,NvM_GucImmQueEndPos       **
**                         NvM_GucSizeImmediateJobQueue                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if((NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) && \
    (NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))

FUNC(void, NVM_CODE) NvM_ImmQueuePosClear(NvM_BlockIdType
  BlockId)
{
  uint8 LucIndex;
  uint8  LucIndex1;
  boolean LucLoopSts;

  LucIndex = NVM_ZERO;
  LucIndex1 = NVM_ZERO;
  
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if (BlockId == NVM_ZERO)
  {
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_MAINFUNCTION_SID, NVM_E_PARAM_DATA);
  }
  #endif
  
  while(LucIndex < NvM_GucSizeImmediateJobQueue)
  {
    if(NvM_GaaImmQueueBuffer[LucIndex].ddBlock_Idx == BlockId)
    {
      LucIndex1 = LucIndex;
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      NvM_GaaImmQueueBuffer[LucIndex].ddBlock_Idx=NVM_ZERO;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      break;
    }
    LucIndex++;
  }

  LucLoopSts = (boolean)NVM_FALSE;

  while(LucLoopSts == NVM_FALSE)
  {
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    if(LucIndex1 == NvM_GucImmQueStartPos)
    {
      NvM_GucImmQueStartPos =
        NvM_GaaImmQueueBuffer[LucIndex1].ucNextIndex;
    }
    else if(LucIndex1 == NvM_GucImmQueEndPos)
    {
      NvM_GucImmQueEndPos =
        NvM_GaaImmQueueBuffer[LucIndex1].ucPreviousIndex;
    }
    else
    {
      /* Do Nothing */
    }
    /* polyspace +3 MISRA-C3:14.3 [Justified:Low] "NvM_GucImmFreeIndx is initialized to a non-zero value in the NvM_Init" */
    /* polyspace +2 MISRA-C3:2.1 [Justified:Low] "NvM_GucImmFreeIndx is initialized to a non-zero value in the NvM_Init" */
    if ((NvM_GucImmFreeIndx < (NvM_GucSizeImmediateJobQueue - NVM_ONE))
        && (LucIndex1 < NvM_GucSizeImmediateJobQueue))
    {
      NvM_GucImmFreeIndx++;
    }
    else
    {
      NvM_GucImmFreeIndx = NVM_ZERO;
    }

    NvM_GucImmFreeSlotsAvail++;
    NvM_GaaImmFreeList[NvM_GucImmFreeIndx] = LucIndex1;
    LucLoopSts = (boolean)NVM_TRUE;
    LucIndex1 = NvM_GaaImmQueueBuffer[LucIndex1].ucNextIndex;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  }
} /* End of function body */

#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end RTE:UNR [Justified:Low] "Not a defect" */
/*
  polyspace:end<RTE:IDP:Not a defect:Justify with annotations > configured memory access index
  polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/


/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
