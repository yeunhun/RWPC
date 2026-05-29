/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : API Function Definitions of NVRAM Module                      **
**              NvM_Init                                                      **
**              NvM_SetDataIndex                                              **
**              NvM_GetDataIndex                                              **
**              NvM_SetBlockProtection                                        **
**              NvM_GetErrorStatus                                            **
**              NvM_SetRamBlockStatus                                         **
**              NvM_SetBlockLockStatus                                        **
**              NvM_WriteBlock                                                **
**              NvM_RestoreBlockDefaults                                      **
**              NvM_EraseNvBlock                                              **
**              NvM_CancelWriteAll                                            **
**              NvM_InvalidateNvBlock                                         **
**              NvM_CancelJobs                                                **
**              NvM_ReadAll                                                   **
**              NvM_WriteAll                                                  **
**              NvM_MainFunction                                              **
**              NvM_GetVersionInfo                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By          Description                          **
********************************************************************************
** 1.5.1       30-Dec-2020   Yun YJ      Redmine #27374                       **
** 1.3.7       28-Mar-2019   Yun YJ      Redmine #16765                       **
** 1.3.6       11-Sep-2017   Yun YJ      Redmine #9669, #9885                 **
** 1.3.5       13-Jun-2017   YJ Yun      Correct MISRA Rule, Redmine #8268    **
** 1.3.4       07-Dec-2016   Song CY     Redmine #6889                        **
** 1.3.3       16-Nov-2016   Song CY     Redmine #6680                        **
** 1.3.0       25-Jul-2016   Song CY     Redmine #3883                        **
** 1.2.6       28-Jun-2016   Song CY     Redmine #5334                        **
** 1.2.3       24-Mar-2016   Song CY     Redmine #4276                        **
** 1.2.2       11-Feb-2016   Song CY     Redmine #4183                        **
** 1.2.0       10-Dec-2015   Song CY     Redmine #3503, Modify WriteProtection**
** 1.1.9       10-Nov-2015   Song CY     Redmine #3371, Remove dummy code     **
** 1.1.8       02-Oct-2015   Song CY     RedMine #2720, Remove PM Flag and    **
**                                       change the function                  **
** 1.1.7       09-Jul-2015   Song CY     As per RedMine 2265, Change CRC Logic**
** 1.1.6       03-Mar-2015   Song CY     As per RedMine 2216, Remove version  **
**                                       Information                          **
** 1.1.4       02-Dec-2014   Song CY     RedMine 1719, Update for PolySpace   **
**                                       RedMine 1458, Change PM API          **
** 1.1.3       23-Sep-2014   Song CY     RM1102 call BswM_NvM_CurrentJobMode  **
                                         when ReadAll/WriteAll block is not   **
                                         configured                           **
** 1.1.0       18-Apr-2014   Song CY     RedMine718 Add Pm Plag.              **
** 1.0.8       30-Sep-2013   Song CY     Update for Library.                  **
**                                       As per DefectList32,33 NvM_Init()    **
                                         function is updated.                 **
** 1.0.0       25-Jan-2013   CY Song     Initial version                      **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
  polyspace-begin MISRA-C3:1.1:Not a defect:Justify with annotations> Needed for AR/SW version check
  polyspace-begin MISRA-C3:11.5:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)
  polyspace:begin<RTE:IDP:Not a defect:Justify with annotations > configured memory access index
  polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
  
*/
/* polyspace-begin RTE:UNR [Justified:Low] "Not a defect" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM.h"                            /* NvM header file */
#include "Rte_NvM.h"
#include "NvM_Config.h"

#if(NVM_CRC_SUPPORT == STD_ON)              /* Crc header file */
#include "Crc.h"
#endif

#include "MemIf.h"                          /* MemIf header file */
#if(NVM_DEMERROR_REPORT == STD_ON)
#include "NvM_Dem_Cfg.h"                            /* Dem header file */
#endif

#include "BswM.h"

#if(NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                            /* Det header file */
#endif

#include "EcuM_Cbk.h"                       /* EcuM_Cbk header file */
#include "BswM_NvM.h"                       /* BswM_NvM header header file */
#include "SchM_NvM.h"                       /* SchM_NvM header file */
#include "Rte_NvM.h"                        /* Rte_NvM header header file */
#include "NvM_Ram.h"                        /* Global variables header file */

/* Internal function header files */
#include "NvM_Cbk.h"
#include "NvM_Process.h"
#include "NvM_ScanQueue.h"
#include "NvM_EraseInvalidate.h"
#include "NvM_RestoreBlock.h"
#include "NvM_ReadBlock.h"
#include "NvM_Write.h"
#include "NvM_ReadAll.h"
#include "NvM_CRCStatic.h"


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : NvM_Init                                            **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Service for basic NVRAM Manager Initialization      **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : NvM_GblInitDone,              **
**                        NvM_GucStdQueStatus, NvM_GucImmQueStatus            **
**                        NvM_GaaImmFreeList, NvM_GaaStdFreeList              **
**                        NvM_GucImmFreeIndx, NvM_GucStdFreeIndx              **
**                        NvM_Gblflag, NvM_GucSizeImmediateJobQueue           **
**                        NvM_GucSizeStadardJobQueue, NvM_GusTotalNumOfBlock  **
**                        NvM_GucChkRedundant                                 **
**                        Function(s) invoked : None                          **
*******************************************************************************/
FUNC(void, NVM_CODE) NvM_Init(void)
{

  #if(NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
  uint8 LucStdIndx1;
  uint8 LucStdIndx2;
  #if((NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))
  uint8 LucImmIndx1;
  uint8 LucImmIndx2;
  #endif
  #endif

  uint16 Lusindex;
  
  NvM_GaaDataBuffer = &NvM_GaaDataBufferSource[4U];
  
  /* if the NVM_API_CONFIG_CLASS is equal to NVM_API_CONFIG_CLASS_1 then
   * the global standard queue variables updating
   */
  #if(NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
  NvM_GucStdFreeIndx = NvM_GucSizeStadardJobQueue - NVM_ONE;
  LucStdIndx2 = (NvM_GucSizeStadardJobQueue - NVM_ONE);
  for(LucStdIndx1 = NVM_ZERO; LucStdIndx1 < NvM_GucSizeStadardJobQueue;
    LucStdIndx1++)
  {
    NvM_GaaStdFreeList[LucStdIndx1] = LucStdIndx2;
    /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "It is checked on the conditional expression." */
    LucStdIndx2--;
  }
  /* Std Queue does not needed to clear */

  NvM_GucStdFreeSlotsAvail = NvM_GucSizeStadardJobQueue;

  /* if the NVM_JOB_PRIORITIZATION is ON and NVM_IMM_JOB_PRIORITY also ON
   * the global immediate queue variables updating
   */
  #if((NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))
  NvM_GucImmFreeIndx = NvM_GucSizeImmediateJobQueue - NVM_ONE;
  LucImmIndx2 = NvM_GucSizeImmediateJobQueue - NVM_ONE;
  for(LucImmIndx1 = NVM_ZERO; LucImmIndx1 < NvM_GucSizeImmediateJobQueue;
    LucImmIndx1++)
  {
    NvM_GaaImmFreeList[LucImmIndx1] = LucImmIndx2;
   /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "It is checked on the conditional expression." */     
    LucImmIndx2--;
  }
  /* Imm Queue does not needed to clear */

  NvM_GucImmFreeSlotsAvail = NvM_GucSizeImmediateJobQueue;
  #endif
  #endif
  
  for (Lusindex=0;Lusindex<NvM_GusTotalNumOfBlock;Lusindex++)
  {
    #if(NVM_DATASET_PRESENT == STD_ON)
    if (NvM_GaaBlkDescTbl[Lusindex].enBlkMngmntType == NVM_BLOCK_DATASET)
    {
      #if(NVM_DEV_ERROR_DETECT == STD_ON)
      if (NvM_GaaBlkDescTbl[Lusindex].pRamIndex == NULL_PTR)
      {
        (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
         NVM_INSTANCE_ID, NVM_E_PARAM_BLOCK_DATA_IDX);
      }
      else
      #endif
      {
        *(NvM_GaaBlkDescTbl[Lusindex].pRamIndex) = NVM_ZERO;
      }
    }
    #endif
    /* In Case Of redundant, indicate to check which block first write */
    if (NvM_GaaBlkDescTbl[Lusindex].enBlkMngmntType == NVM_BLOCK_REDUNDANT)
    {
      NvM_GaaRamStatus[Lusindex] = 
                (NvM_GaaRamStatus[Lusindex] | NVM_CHECK_NEED_REDUNDANT_MASK);
    }
    if ((NvM_GaaBlkDescTbl[Lusindex].usBlkParams & NVM_BLOCK_WRITE_PROT)
         == NVM_BLOCK_WRITE_PROT)
    {
      NvM_GaaRamStatus[Lusindex] = 
                (NvM_GaaRamStatus[Lusindex] | NVM_WRITE_PROTECT_MASK);
    }
  }
  NvM_GucWriteAllRequest = NVM_MULTIBLK_UNREQUESTED;
  NvM_GucReadAllRequest = NVM_MULTIBLK_UNREQUESTED;

  NvM_GucState = NVM_IDLE;
  NvM_GucSubState = NVM_SUB_IDLE;
  NvM_GucReadAllState = NVM_IDLE;
  NvM_GucWriteAllSubState = NVM_WRITE_ALL_IDLE;
  NvM_GucNotifiedGlobalStatus = NVM_REQ_OK;
  NvM_GucChkRedundant = NVM_FALSE;
  NvM_GddFirstBlock = NVM_RE_ORIGINAL_FIRST;

  NvM_Gblflag = (boolean)NVM_TRUE;
  #if((NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) && \
      (NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))
  NvM_GblPrevReqImm = (boolean)NVM_FALSE;
  NvM_GblHighPriorityRequest = (boolean)NVM_FALSE;
  #endif

  NvM_GblRestoreFlag = (boolean)NVM_FALSE;

  NvM_GucPM_Count = NVM_ZERO;

  /* Set flag to indicate initialization is complete */
  NvM_GblInitDone = (boolean)NVM_TRUE;

} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_SetDataIndex                                    **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : The function sets the association of Dataset NV     **
**                        block with its corresponding RAM block by storing   **
**                        the 8 bit DataIndex passed by the application to    **
**                        the index field of the RAM block.                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId, DataIndex                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        NvM_GblInitDone, NvM_GaaBlkDescTbl,                 **
**                        NvM_GaaRamStatus, NvM_GusTotalNumOfBlock            **
**                                                                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError(), SchM_Enter_NvM_RAM_INDEX(),      **
**                        SchM_Exit_NvM_RAM_INDEX()                           **
*******************************************************************************/
#if((NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) && \
    (NVM_DATASET_PRESENT == STD_ON))

FUNC(Std_ReturnType, NVM_CODE) NvM_SetDataIndex(NvM_BlockIdType BlockId,
  uint8 DataIndex)
{
  P2CONST(NvM_BlkDescTbl, NVM_CONST, NVM_CONST) LpBlkDescTbl;
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  #if(NVM_DATASET_PRESENT == STD_ON)
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) LpRamIndex;
  #endif
  Std_ReturnType LddReturnValue;

  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  P2CONST(uint8, NVM_CONFIG_DATA, NVM_CONST)LpRomBlkDataAddr;
  uint8 LucNumOfNvBlks;
  #endif

  LddReturnValue = E_OK;

  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_SETDATAINDEX_SID, NVM_E_NOT_INITIALIZED);
    LddReturnValue = E_NOT_OK;
  }
  else if((BlockId == NVM_ZERO) || (BlockId >= NvM_GusTotalNumOfBlock))
  {
    /* Report invalid Block Identifier */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_SETDATAINDEX_SID, NVM_E_PARAM_BLOCK_ID);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  { /* Start of Block comment - 2 */
    LpBlkDescTbl = &NvM_GaaBlkDescTbl[BlockId];
    #if(NVM_DATASET_PRESENT == STD_ON)
    LpRamIndex = LpBlkDescTbl->pRamIndex;
    #endif

    #if(NVM_DEV_ERROR_DETECT == STD_ON)
    LucNumOfNvBlks = LpBlkDescTbl->ucNumOfNvBlks;
    LpRomBlkDataAddr = LpBlkDescTbl->pRomBlkData;
    #endif

    /* If the Block Management Type is equal to Native or Redundant Management
     * Type, report error to DET
     */
    if((LpBlkDescTbl->enBlkMngmntType) != NVM_BLOCK_DATASET)
    {
      #if(NVM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_SETDATAINDEX_SID, NVM_E_PARAM_BLOCK_TYPE);
      #endif
      LddReturnValue = E_NOT_OK;
    }
    /* If the Dataset Management Type block is not configured with ROM but
     * the passed data index value is greater than the number of NV blocks
     * or If the Dataset Management Type block is configured with ROM but the
     * passed data index value is greater than the number of NV blocks and
     * number of ROM blocks, report error to DET
     */
    #if(NVM_DEV_ERROR_DETECT == STD_ON)
    else if(((LpRomBlkDataAddr == NULL_PTR) && (DataIndex >=
      LucNumOfNvBlks)) || ((LpRomBlkDataAddr != NULL_PTR) &&
      (DataIndex >= (LucNumOfNvBlks + LpBlkDescTbl->ucNumOfRomBlks))))
    {
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_SETDATAINDEX_SID, NVM_E_PARAM_BLOCK_DATA_IDX);
      LddReturnValue = E_NOT_OK;
    }
    else
    #endif
    {
      LpRamStatus = &NvM_GaaRamStatus[BlockId];
      if((*(LpRamStatus) & NVM_ERROR_BIT_MASK) == NVM_REQ_PENDING)
      {
        #if(NVM_DEV_ERROR_DETECT == STD_ON)
        /* If the request for the block is present in queue or currently in
         * progress, report error to DET
         */
        (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
          NVM_SETDATAINDEX_SID, NVM_E_BLOCK_PENDING);
        #endif
        LddReturnValue = E_NOT_OK;
      }

      #if(NVM_DATASET_PRESENT == STD_ON)
      else
      {
        if (NULL_PTR != LpRamIndex)
        {
          SchM_Enter_NvM_RAM_INDEX();
          /* Store the data index into the RAM index */
          *(LpRamIndex) = DataIndex;
          SchM_Exit_NvM_RAM_INDEX();
        }
      }
      #endif
    }
  } /* end of Block comment - 2 */
  return(LddReturnValue);
} /* End of function body */

#endif

/*******************************************************************************
** Function Name        : NvM_GetDataIndex                                    **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This function reads the index (association of NV    **
**                        block with its corresponding RAM block) from        **
**                        the RAM block index field.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DataIndexPtr                                        **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblInitDone,           **
**                        NvM_GaaBlkDescTbl, NvM_GusTotalNumOfBlock           **
**                                                                            **
**                        Function(s) invoked    : Det_ReportError()          **
*******************************************************************************/
#if((NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) && \
    (NVM_DATASET_PRESENT == STD_ON))

FUNC(Std_ReturnType, NVM_CODE) NvM_GetDataIndex(NvM_BlockIdType
    BlockId, P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DataIndexPtr)
{
  P2CONST(NvM_BlkDescTbl, NVM_CONST, NVM_CONST) LpBlkDescTbl;
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /* If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked
   */
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_GETDATAINDEX_SID, NVM_E_NOT_INITIALIZED);
    LddReturnValue = E_NOT_OK;
  }
  /* If Block Identifier is not configured, report error to DET */
  else if((BlockId == NVM_ZERO) || (BlockId >= NvM_GusTotalNumOfBlock))
  {
    /* Report invalid Block Identifier */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_GETDATAINDEX_SID, NVM_E_PARAM_BLOCK_ID);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  { /* start of Block comment - 2 */
    /* If passed pointer is NULL, report error to DET */
    #if(NVM_DEV_ERROR_DETECT == STD_ON)
    if(DataIndexPtr  ==  NULL_PTR)
    {
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_GETDATAINDEX_SID, NVM_E_PARAM_DATA);
      LddReturnValue = E_NOT_OK;
    }
    else
    #endif
    { /* start of Block comment - 3 */
      LpBlkDescTbl =  &NvM_GaaBlkDescTbl[BlockId];

     /*
      * If the Block Management Type is equal to Native or Redundant
      * Management Type, report error to the DET
      */
      if(LpBlkDescTbl->enBlkMngmntType != NVM_BLOCK_DATASET)
      {
        /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "This parameter shall be checked by user" */
        *DataIndexPtr = NVM_ZERO;
        #if(NVM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
          NVM_GETDATAINDEX_SID, NVM_E_PARAM_BLOCK_TYPE);
          LddReturnValue = E_NOT_OK;
        #endif
      }
      else
      {
        #if(NVM_DATASET_PRESENT == STD_ON)
        if (NULL_PTR != LpBlkDescTbl->pRamIndex)
        {
          /* Return the stored data index */
          /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "This parameter shall be checked by user" */
          *DataIndexPtr = *(LpBlkDescTbl->pRamIndex);
        }
        #endif
      }
    } /* end of Block comment - 3 */
  } /* end of Block comment - 2 */
  return(LddReturnValue);
}/* End of function body */
#endif
/*******************************************************************************
** Function Name      : NvM_SetBlockProtection                                **
**                                                                            **
** Service ID         : 0x03                                                  **
**                                                                            **
** Description        : This function enables/disables the write block        **
**                      protection bit in the RAM block attribute/error       **
**                      /status field.                                        **
**                      This function is available only if API                **
**                      Configuration Class 3 is enabled.                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Reentrant                                             **
**                                                                            **
** Input Parameters   : BlockId, ProtectionEnabled                            **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : LddReturnValue                                        **
**                                                                            **
** Precondition       : NVRAM Manager should be initialized.                  **
**                                                                            **
** Remarks            : Global Variable(s) : NvM_GblInitDone,                 **
**                      NvM_GaaRamStatus, NvM_GaaBlkDescTbl                   **
**                      NvM_GusTotalNumOfBlock                                **
**                      Function(s) invoked: Det_ReportError(),               **
**                      SchM_Enter_NvM_RAM_STATUS_PROTECTION(),               **
**                      SchM_Exit_NvM_RAM_STATUS_PROTECTION()                 **
*******************************************************************************/
#if(NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3)

FUNC(Std_ReturnType, NVM_CODE) NvM_SetBlockProtection(NvM_BlockIdType
    BlockId, boolean ProtectionEnabled)
{
  P2CONST(NvM_BlkDescTbl, NVM_CONST, NVM_CONST) LpBlkDescTbl;
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  uint16 LusBlkParams;
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_SETBLOCKPROTECTION_SID, NVM_E_NOT_INITIALIZED);
    LddReturnValue = E_NOT_OK;
  }
  else if((BlockId == NVM_ZERO) || (BlockId >= NvM_GusTotalNumOfBlock))
  {
    /* Report invalid Block Identifier */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_SETBLOCKPROTECTION_SID, NVM_E_PARAM_BLOCK_ID);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  { /* start of Block comment - 2 */
    LpRamStatus = &NvM_GaaRamStatus[BlockId];
    LpBlkDescTbl =  &NvM_GaaBlkDescTbl[BlockId];
    LusBlkParams = LpBlkDescTbl->usBlkParams;


    /* Report DET error if block is locked */
    if((*(LpRamStatus) & NVM_LOCK_RAM_MASK) == NVM_LOCK_RAM_MASK)
    {
      #if(NVM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_SETBLOCKPROTECTION_SID, NVM_E_BLOCK_LOCKED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
    /* If the parameter NVM_WRITE_BLOCK_ONCE = NVM_TRUE, report error to
     DET */
    else if((LusBlkParams & NVM_WRITE_BLOCK_ONCE) == NVM_WRITE_BLOCK_ONCE)
    {
      #if(NVM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_SETBLOCKPROTECTION_SID, NVM_E_BLOCK_CONFIG);
      #endif
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      if((*(LpRamStatus) & NVM_ERROR_BIT_MASK) == NVM_REQ_PENDING)
      {
        /*
         * If the request for the block is present in queue or currently in
         * progress, report error to DET
         */
        #if(NVM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
          NVM_SETBLOCKPROTECTION_SID, NVM_E_BLOCK_PENDING);
        #endif
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* Check if the passed ProtectionEnabled parameter is NVM_TRUE */
        if(ProtectionEnabled == TRUE)
        {
          /* Invoke function to enable data protection */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          /*
           * Activate write protection by setting write lock bit in
           * administrative part of RAM block
           */
          *(LpRamStatus) = (*(LpRamStatus) | NVM_WRITE_PROTECT_MASK);
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        }
        else
        {
          /* Invoke function to enable data protection */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          /*
           * Deactivate write protection by clearing NV block Protection write
           * lock bit(most significant bit) in administrative part of RAM
           * block
           */
          *(LpRamStatus) = (*(LpRamStatus) & (NVM_NOT_WRITE_PROTECT_MASK));
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        }
      }
    }
  } /* end of Block comment - 2 */
  return(LddReturnValue);
}/* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3) */

/*******************************************************************************
** Function Name        : NvM_GetErrorStatus                                  **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Description          : This API reads the attribute field bits from the RAM**
**                        block attribute/ error/ status field and returns the**
**                        error/status information to the application.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : RequestResultPtr                                    **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Precondition         : NvM  should be initialized.                         **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblInitDone,           **
**                        NvM_GaaRamStatus, NvM_GusTotalNumOfBlock            **
**                                                                            **
**                        Function(s) invoked    : Det_ReportError()          **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, NVM_CODE) NvM_GetErrorStatus (NvM_BlockIdType
  BlockId, P2VAR(NvM_RequestResultType, AUTOMATIC , NVM_APPL_DATA)
  RequestResultPtr)
{
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_GETERRORSTATUS_SID, NVM_E_NOT_INITIALIZED);
    LddReturnValue = E_NOT_OK;
  }
  /* If Block Identifier is not configured, report error to DET */
  else if(BlockId >= NvM_GusTotalNumOfBlock)
  {
    /* Report invalid Block Identifier */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_GETERRORSTATUS_SID, NVM_E_PARAM_BLOCK_ID);
    LddReturnValue = E_NOT_OK;
  }
  /* If passed pointer is NULL, report error to DET */
  else if(RequestResultPtr == NULL_PTR)
  {
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_GETERRORSTATUS_SID, NVM_E_PARAM_DATA);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    /* Read error bits from RAM Attr/Error/Status field */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "This argument is from user" */
    *RequestResultPtr = NVM_GET_JOB_RESULT(BlockId);
  }
  return(LddReturnValue);
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_SetRamBlockStatus                               **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This API recalculates the CRC (if configured) for   **
**                        the RAM block data and sets the state of the        **
**                        RAM block to valid/invalid.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId, BlockChanged                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblInitDone,           **
**                        NvM_GaaBlkDescTbl, NvM_GaaRamStatus                 **
**                        NvM_GusTotalNumOfBlock                              **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)

FUNC(Std_ReturnType, NVM_CODE) NvM_SetRamBlockStatus(NvM_BlockIdType
  BlockId, boolean BlockChanged)
{
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  #if(NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON)
  P2CONST(NvM_BlkDescTbl, NVM_CONST, NVM_CONST) LpBlkDescTbl;
  uint16 LusBlkParams;
  #endif
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_SETRAMBLOCKSTATUS_SID, NVM_E_NOT_INITIALIZED);
    LddReturnValue = E_NOT_OK;
  }
  /* If Block Identifier is not configured, report error to DET */
  else if((BlockId == NVM_ZERO) || (BlockId >= NvM_GusTotalNumOfBlock))
  {
    /* Report invalid Block Identifier */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_SETRAMBLOCKSTATUS_SID, NVM_E_PARAM_BLOCK_ID);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  { /* start of Block comment - 2 */
    #if(NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON)
    LpBlkDescTbl =  &NvM_GaaBlkDescTbl[BlockId];
    #endif
    LpRamStatus = &NvM_GaaRamStatus[BlockId];

    if((*(LpRamStatus) & NVM_ERROR_BIT_MASK) == NVM_REQ_PENDING)
    {
      /*
       * If the request for the block is present in queue or currently in
       * progress, report error to DET
       */
      #if(NVM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_SETRAMBLOCKSTATUS_SID, NVM_E_BLOCK_PENDING);
      #endif
      LddReturnValue = E_NOT_OK;
    }
    /* Report DET error if block is locked*/
    else if((*(LpRamStatus) & NVM_LOCK_RAM_MASK) == NVM_LOCK_RAM_MASK)
    {
      #if(NVM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_SETRAMBLOCKSTATUS_SID, NVM_E_BLOCK_LOCKED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
    /*Check if Permanent RAM block is configured */
    #if(NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON)
    else if(LpBlkDescTbl->pRamBlkData != NULL_PTR)
    { /* start of Block comment - 3 */
      if(BlockChanged == TRUE)
      {
        /* Invoke function to enable data protection */
        SchM_Enter_NvM_RAM_STATUS_PROTECTION();

        /* Update the RAM block status to 'Valid and Changed' */
        *LpRamStatus = ((*(LpRamStatus) & NVM_CLEAR_RAM_INTERNAL_STATE) |
          NVM_VALID_CHANGED);

        /* Invoke function to disable data protection */
        SchM_Exit_NvM_RAM_STATUS_PROTECTION();

        /*
         * Check if CRC is configured, and check
         * whether the recalculation is in progress for the previous request
         */
        LusBlkParams = LpBlkDescTbl->usBlkParams;

        /* Invoke function to enable data protection */
        SchM_Enter_NvM_RAM_STATUS_PROTECTION();

        if((LusBlkParams & NVM_CALC_CRC_BLOCK_CHECK) ==
          NVM_CALC_CRC_BLOCK_CHECK)
        {
          /* Set the bit to recalculate CRC in background */
          *(LpRamStatus) = *(LpRamStatus) | NVM_CRC_REQUESTED_MASK;
        }

        /* Invoke function to disable data protection */
        SchM_Exit_NvM_RAM_STATUS_PROTECTION();

      }
      else
      {
        /* Invoke function to enable data protection */
        SchM_Enter_NvM_RAM_STATUS_PROTECTION();

        /* Update the RAM block status to 'Unchanged' */
        *LpRamStatus = ((*(LpRamStatus) & NVM_CLEAR_RAM_INTERNAL_STATE) |
          NVM_VALID_UNCHANGED);

        /* Invoke function to disable data protection */
        SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      }
    } /* end of Block comment - 3 */
    else
    {
      /* To avoid QAC warning */
    }
    #endif
  } /* end of Block comment - 2 */
  return(LddReturnValue);
}

#endif /* (NVM_SET_RAM_BLOCK_STATUS_API  == STD_ON) */

/*******************************************************************************
** Function Name        : NvM_SetBlockLockStatus                              **
**                                                                            **
** Service ID           : 0x13                                                **
**                                                                            **
** Description          : Service for setting the lock status of a permanent  **
**                        RAM block of an NVRAM block                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId, BlockLocked                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM module should be initialized.                   **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblInitDone,           **
**                        NvM_GaaBlkDescTbl, NvM_GaaRamStatus                 **
**                        NvM_GusTotalNumOfBlock                              **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION()              **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/

FUNC(void, NVM_CODE) NvM_SetBlockLockStatus(NvM_BlockIdType
  BlockId, boolean BlockLocked)
{
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  P2CONST(NvM_BlkDescTbl, NVM_CONST, NVM_CONST)LpBlkDescTbl;
  #endif
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA)LpRamStatus;
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  uint16 LusBlkParams;
  #endif

  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_SETBLOCKLOCKSTATUS_SID, NVM_E_NOT_INITIALIZED);
  }
  /* If Block Identifier is not configured, report error to DET */
  else if((BlockId == NVM_ZERO) || (BlockId >= NvM_GusTotalNumOfBlock))
  {
    /* Report invalid Block Identifier */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_SETBLOCKLOCKSTATUS_SID, NVM_E_PARAM_BLOCK_ID);
  }
  else
  #endif
  { /* start of block comment - 2 */
    #if(NVM_DEV_ERROR_DETECT == STD_ON)
    LpBlkDescTbl = &NvM_GaaBlkDescTbl[BlockId];
    LusBlkParams = LpBlkDescTbl->usBlkParams;
    /* If the parameter NVM_WRITE_BLOCK_ONCE = NVM_TRUE, report error to
     DET */
    if((LusBlkParams & NVM_WRITE_BLOCK_ONCE) == NVM_WRITE_BLOCK_ONCE)
    {
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_SETBLOCKLOCKSTATUS_SID, NVM_E_BLOCK_CONFIG);
    }
    else
    #endif
    { /* start of block comment - 3 */
      LpRamStatus = &NvM_GaaRamStatus[BlockId];
      if((*(LpRamStatus) & NVM_ERROR_BIT_MASK) == NVM_REQ_PENDING)
      {
        /*
         * If the request for the block is present in queue or currently in
         * progress, report error to DET
         */
        #if(NVM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_SETBLOCKLOCKSTATUS_SID, NVM_E_BLOCK_PENDING);
        #endif
      }
      else
      {

        /* Check if the passed BlockLocked parameter is NVM_TRUE */
        if(BlockLocked == (boolean)NVM_TRUE)
        {
          /* Invoke function to enable data protection */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();

           /* Lock the permanent RAM block of an NVRAM block */
          *(LpRamStatus) = (*(LpRamStatus) | NVM_LOCK_RAM_MASK);

          /* Invoke function to disable data protection */
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        }
        else
        {
          /* Invoke function to enable data protection */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();

          /* UnLock the permanent RAM block of an NVRAM block */
          *(LpRamStatus) = (*(LpRamStatus) & NVM_UNLOCK_RAM_MASK);

          /* Invoke function to disable data protection */
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        }

      }
    } /* end of block comment - 3 */
  } /* end of block comment - 2 */
}/* End of function body */

/*******************************************************************************
** Function Name        : NvM_ReadBlock                                       **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId and  **
**                        NvM_DstPtr and Service Id to 'Read' the             **
**                        NV/ROM block data to its corresponding RAM block.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NvM_DstPtr                                          **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : NvM module should be initialized.                   **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblInitDone,           **
**                        NvM_GaaBlkDescTbl, NvM_GaaRamStatus                 **
**                        NvM_GusQueueOverflow, NvM_GusTotalNumOfBlock        **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        NvM_StdQueueWrite(), Dem_ReportErrorStatus(),       **
**                        NvM_QueueCRCSIDblocks()                             **
*******************************************************************************/

#if(NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1)

FUNC(Std_ReturnType, NVM_CODE) NvM_ReadBlock(NvM_BlockIdType
    BlockId, P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr)
{
  #if((NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON) || \
    (NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON))
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) LpBlkDescTbl;
  #endif
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  NvM_JobQueue LstStdQueue;
  Std_ReturnType LddReturnValue;

  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, NVM_READBLOCK_SID,
      NVM_E_NOT_INITIALIZED);
    LddReturnValue = E_NOT_OK;
  }
  /* If Block Identifier is not configured, report error to DET */
  else if((BlockId == NVM_ZERO) || (BlockId >= NvM_GusTotalNumOfBlock))
  {
    /* Report invalid Block Identifier */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, NVM_READBLOCK_SID,
      NVM_E_PARAM_BLOCK_ID);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count++;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                     (BswM_ModeType)NVM_LOWPOWER_PREVENT);
    /* start of block comment - 2 */
    #if((NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON) || \
      (NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON))
    LpBlkDescTbl = &NvM_GaaBlkDescTbl[BlockId];
    #endif
    /*
     * If the permanent RAM block is not configured, NULL pointer is passed
     * as parameter, and Mirror is disabled report error to DET
     */
    if(
      #if(NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON)
      ((LpBlkDescTbl->pRamBlkData) == NULL_PTR) &&
      #endif
      (NvM_DstPtr == NULL_PTR)
      #if(NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
      && ((LpBlkDescTbl->usBlkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE) !=
      NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)
      #endif
    )
    {
      #if(NVM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, NVM_READBLOCK_SID,
        NVM_E_PARAM_ADDRESS);
      #endif
      LddReturnValue = E_NOT_OK;
    }
    else
    { /* start of block comment - 3*/
      LpRamStatus = &NvM_GaaRamStatus[BlockId];
      /* Start of Block comment */
      if((*(LpRamStatus) & NVM_ERROR_BIT_MASK) == NVM_REQ_PENDING)
      {
        /*
         * If the request for the block is present in queue or currently in
         * progress, report error to DET
         */
        #if(NVM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
          NVM_READBLOCK_SID, NVM_E_BLOCK_PENDING);
        #endif
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /*
         * Load the Service Id, Block Id and the passed pointer to the
         * corresponding elements of the Standard queue
         */
        LstStdQueue.ucService_Id = NVM_READBLOCK_SID;
        LstStdQueue.ddBlock_Idx = BlockId;
	/* polyspace +3 MISRA-C3:11.5 [Not a defect:Low] "No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)" */	
        LstStdQueue.pTempRamBlkData = (uint8*)NvM_DstPtr;
        #if (NVM_JOB_PRIORITIZATION == STD_ON)
        LstStdQueue.ucPriority = NvM_GaaBlkDescTbl[BlockId].ucBlkJobPriority;
        #endif

        /* Put the read request in the queue  */
        LddReturnValue = NvM_StdQueueWrite(&LstStdQueue);
        /* Check if the queue write is not successful */
        if(LddReturnValue == E_NOT_OK)
        {
          #if(NVM_DEMERROR_REPORT == STD_ON)
          /* Report the queue overflow to DEM */
          Dem_ReportErrorStatus(NvM_GusQueueOverflow,
            DEM_EVENT_STATUS_FAILED);
          #endif
        }
      }
    } /* end of block comment - 3 */

    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count--;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  } /* end of block comment - 2 */
  return(LddReturnValue);
} /* End of function body */

#endif /* (NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) */

/*******************************************************************************
** Function Name        : NvM_WriteBlock                                      **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId,     **
**                        NvM_SrcPtr and Service Id to 'Write' the            **
**                        RAM block data to its corresponding NV block.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId, NvM_SrcPtr                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : NvM module should be initialized.                   **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblInitDone,           **
**                       NvM_GaaBlkDescTbl, NvM_GaaRamStatus                  **
**                       NvM_GusQueueOverflow, NvM_GusWriteProtected          **
**                       NvM_GusTotalNumOfBlock                               **
**                       Function(s) invoked    : Det_ReportError()           **
**                       Dem_ReportErrorStatus(), NvM_ImmQueueWrite(),        **
**                       NvM_StdQueueWrite(), NvM_QueueCRCSIDblocks()         **
*******************************************************************************/
#if(NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1)

FUNC(Std_ReturnType, NVM_CODE) NvM_WriteBlock(NvM_BlockIdType
  BlockId, P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) LpBlkDescTbl;
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  Std_ReturnType LddReturnValue;
  NvM_JobQueue LstJobQueue;

  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, NVM_WRITEBLOCK_SID,
      NVM_E_NOT_INITIALIZED);
    LddReturnValue = E_NOT_OK;
  }
  /* If Block Identifier is not configured, report error to DET */
  else if((BlockId == NVM_ZERO) || (BlockId >= NvM_GusTotalNumOfBlock))
  {
    /* Report invalid Block Identifier */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, NVM_WRITEBLOCK_SID,
      NVM_E_PARAM_BLOCK_ID);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  { 
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count++;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                     (BswM_ModeType)NVM_LOWPOWER_PREVENT);

    /* Start of Block comment- 2 */
    LpBlkDescTbl = &NvM_GaaBlkDescTbl[BlockId];

    /*
     * If the permanent RAM block is not configured, NULL pointer is passed
     * as parameter and Mirror is disabled report error to DET
     */

    if(
      #if(NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON)
      ((LpBlkDescTbl->pRamBlkData) == NULL_PTR) &&
      #endif
      (NvM_SrcPtr == NULL_PTR)
      #if(NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
      && ((LpBlkDescTbl->usBlkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE) !=
      NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)
      #endif
    )
    {
      NVM_REPORT_ERROR(NVM_WRITEBLOCK_SID, NVM_E_PARAM_ADDRESS);
      LddReturnValue = E_NOT_OK;
    }
    else
    { /* Start of Block comment - 3 */
      LpRamStatus = &NvM_GaaRamStatus[BlockId];

      /* Check if the block is write protected */
      if((*LpRamStatus & NVM_WRITE_PROTECT_MASK) == NVM_WRITE_PROTECT_MASK)
      {
        #if(NVM_DEMERROR_REPORT == STD_ON)
        /* Report the write protected to DEM */
        Dem_ReportErrorStatus(NvM_GusWriteProtected, DEM_EVENT_STATUS_FAILED);
        #endif
        LddReturnValue = E_NOT_OK;
      }
      /*Check if index is not pointing to ROM area in case of Dataset block*/
      #if(NVM_DATASET_PRESENT == STD_ON)        
      /* if DataIndex is pointing to ROM */
      else if(
        (LpBlkDescTbl->enBlkMngmntType == NVM_BLOCK_DATASET) &&
        /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
        /* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
        (*LpBlkDescTbl->pRamIndex >= LpBlkDescTbl->ucNumOfNvBlks)
      )
      {
        LddReturnValue = E_NOT_OK;
      }    
      #endif    
      /* Report DET error if block is locked*/
      else if((*(LpRamStatus) & NVM_LOCK_RAM_MASK) == NVM_LOCK_RAM_MASK)
      {
        NVM_REPORT_ERROR(NVM_WRITEBLOCK_SID, NVM_E_BLOCK_LOCKED);
        LddReturnValue = E_NOT_OK;
      }
      /*
       * Report DET error whenever a job is pending and ReadAll is not taken
       * for processing and whenever ReadAll is in progress and block is
       * configured to be of standard type
       */
      else if(NVM_GET_JOB_RESULT(BlockId) == NVM_REQ_PENDING)
      {
        /*
         * If the request for the block is present in queue or currently in
         * progress, report error to DET
         */
        NVM_REPORT_ERROR(NVM_WRITEBLOCK_SID, NVM_E_BLOCK_PENDING);
        LddReturnValue = E_NOT_OK;
      }
      #if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
      else if(
        ((*LpRamStatus & NVM_RAM_STATUS_MASK) == NVM_VALID_UNCHANGED) &&
        (LpBlkDescTbl->pRamBlkData != NULL_PTR)
      )
      {
        LddReturnValue = E_OK;
      }
      #endif
      else
      { /* Start of Block comment - 5 */
        /* Load the Service Id, Block Id and RAM buffer pointer */
        LstJobQueue.ucService_Id = NVM_WRITEBLOCK_SID;
        LstJobQueue.ddBlock_Idx = BlockId;
        LstJobQueue.pTempRamBlkData = NvM_SrcPtr;
        #if(NVM_JOB_PRIORITIZATION == STD_ON)
        LstJobQueue.ucPriority = NvM_GaaBlkDescTbl[BlockId].ucBlkJobPriority;
        #endif
        #if((NVM_JOB_PRIORITIZATION==STD_ON)&&(NVM_IMM_JOB_PRIORITY==STD_ON))
        if((LpBlkDescTbl->ucBlkJobPriority) == NVM_IMM_PRIORITY)
        {
          /*
           * Queue the request in immediate Queue, if block is configured of
           * type immediate priority
           */
          LddReturnValue = NvM_ImmQueueWrite(&LstJobQueue);
          #if((NVM_CRC_SUPPORT == STD_ON) || \
            (NVM_STATIC_ID_CHECK == STD_ON))
          if(LddReturnValue == E_OK)
          {
          /*
           * MISRA Rule        : 1.1
           * Message           : Nesting of control structures (statements)
           *                     exceeds 15 - program is non-conforming.
           * Reason            : The prototype is as per the specifications
           *                     of NvM.
           * Verification      : However, part of the code is verified
           *                     manually and it is not having any impact.
           */
            if(
              #if(NVM_CRC_SUPPORT == STD_ON)
              ((LpBlkDescTbl->usBlkParams & NVM_CALC_RAM_BLK_CRC) ==
              NVM_CALC_RAM_BLK_CRC)
              #endif
              #if((NVM_CRC_SUPPORT == STD_ON) && \
                (NVM_STATIC_ID_CHECK == STD_ON))
              ||
              #endif
              #if(NVM_STATIC_ID_CHECK == STD_ON)
              ((LpBlkDescTbl->usBlkParams & NVM_STATIC_BLOCK_ID_CHECK) ==
              NVM_STATIC_BLOCK_ID_CHECK)
              #endif
              )
            {
              #if(NVM_DATASET_PRESENT == STD_ON)
              if((LpBlkDescTbl->enBlkMngmntType) == NVM_BLOCK_DATASET)
              {
                LstJobQueue.ddBlock_Idx = BlockId +
                /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
                /* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
                    (*(LpBlkDescTbl->pRamIndex))+NVM_ONE;
                LstJobQueue.pTempRamBlkData = NvM_GaaCrcSID;
                LddReturnValue = NvM_ImmQueueWrite(&LstJobQueue);
              }
              else
              #endif
              {
                LstJobQueue.ddBlock_Idx++;
                LstJobQueue.pTempRamBlkData = NvM_GaaCrcSID;
                LddReturnValue = NvM_ImmQueueWrite(&LstJobQueue);
                if((LddReturnValue == E_OK) &&
                  ((LpBlkDescTbl->enBlkMngmntType) == NVM_BLOCK_REDUNDANT))
                {
                    LstJobQueue.ddBlock_Idx++;
                    LddReturnValue = NvM_ImmQueueWrite(&LstJobQueue);
                }
              }
            }
          }
          #endif
        }
        else
        #endif
        /*(NVM_JOB_PRIORITIZATION==STD_ON)&&(NVM_IMM_JOB_PRIORITY==STD_ON) */
        {
          /*
           * Queue the request in Standard Queue, if block is configured of
           * type standard priority or if Prioritization is disabled
           */
          LddReturnValue = NvM_StdQueueWrite(&LstJobQueue);
        }

        /* Check if the queue write is not successful */
        if(LddReturnValue == E_NOT_OK)
        {
           #if(NVM_DEMERROR_REPORT == STD_ON)
          /* Report the queue overflow to DEM */
          Dem_ReportErrorStatus(NvM_GusQueueOverflow, DEM_EVENT_STATUS_FAILED);
           #endif
        }
      } /* end of Block comment - 5 */
    } /* end of Block comment - 3 */

    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count--;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  } /* end of Block comment - 2 */
  return(LddReturnValue);
}

#endif  /*(NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) */

/*******************************************************************************
** Function Name        : NvM_RestoreBlockDefaults                            **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId,     **
**                        NvM_DstPtr and Service Id to 'Restore' the          **
**                        ROM block default data to its corresponding RAM     **
**                        block.                                              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NvM_DstPtr                                          **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : NvM  should be initialized.                         **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblInitDone            **
**                        NvM_GaaBlkDescTbl, NvM_GaaRamStatus                 **
**                        NvM_GusQueueOverflow, NvM_GusTotalNumOfBlock        **
**                        Function(s) invoked    : Det_ReportError()          **
**                        NvM_StdQueueWrite, Dem_ReportErrorStatus()          **
*******************************************************************************/

#if(NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1)

FUNC(Std_ReturnType, NVM_CODE) NvM_RestoreBlockDefaults(
  NvM_BlockIdType BlockId, P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST)LpBlkDescTbl;
  NvM_JobQueue LstStdQueue;
  Std_ReturnType LddReturnValue;

  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    NVM_REPORT_ERROR(NVM_RESTOREBLOCKDEFAULTS_SID, NVM_E_NOT_INITIALIZED);
    LddReturnValue = E_NOT_OK;
  }
  /* If Block Identifier is not configured, report error to DET */
  else if((BlockId == NVM_ZERO) || (BlockId >= NvM_GusTotalNumOfBlock))
  {
    NVM_REPORT_ERROR(NVM_RESTOREBLOCKDEFAULTS_SID, NVM_E_PARAM_BLOCK_ID);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count++;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                     (BswM_ModeType)NVM_LOWPOWER_PREVENT);

    LpBlkDescTbl = &NvM_GaaBlkDescTbl[BlockId];
    /*
     * If the permanent RAM block is not configured and NULL pointer is passed
     * as parameter, report error to DET
     */
 
    if(
      #if(NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON)
      ((LpBlkDescTbl->pRamBlkData) == NULL_PTR) &&
      #endif
      (NvM_DstPtr == NULL_PTR)
      #if(NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
      && ((LpBlkDescTbl->usBlkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE) !=
      NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)
      #endif
    )
    {
      NVM_REPORT_ERROR(NVM_RESTOREBLOCKDEFAULTS_SID, NVM_E_PARAM_ADDRESS);
      LddReturnValue = E_NOT_OK;
    }
    /*
     * Check if ROM block and Initblockcallback are not configured for the
     * block
     */
    else if 
    (
      (LpBlkDescTbl->pRomBlkData == NULL_PTR)
      #if(NVM_INIT_CALLBACK == STD_ON)
      && (LpBlkDescTbl->pNvMInitNotification_BlockId == NULL_PTR)
      #endif
    )
    {
      NVM_REPORT_ERROR(NVM_RESTOREBLOCKDEFAULTS_SID, NVM_E_BLOCK_CONFIG);
      LddReturnValue = E_NOT_OK;
    }
    /*Check if index is not pointing to ROM area in case of Dataset block*/
    #if(NVM_DATASET_PRESENT == STD_ON)            
    else if(
      /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
      /* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
      (LpBlkDescTbl->enBlkMngmntType == NVM_BLOCK_DATASET) &&
      (*LpBlkDescTbl->pRamIndex < LpBlkDescTbl->ucNumOfNvBlks)
    )
    {
      LddReturnValue = E_NOT_OK;
    }    
    #endif
    else if(NVM_GET_JOB_RESULT(BlockId) == NVM_REQ_PENDING)
    {
      /*
       * If the request for the block is present in queue or currently
       * in progress, report error to DET
       */
      NVM_REPORT_ERROR(NVM_RESTOREBLOCKDEFAULTS_SID, NVM_E_BLOCK_PENDING);
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      /*
       * Load the Service Id, Block Id and the passed pointer to the
       * corresponding elements of the Standard queue
       */
      LstStdQueue.ucService_Id = NVM_RESTOREBLOCKDEFAULTS_SID;
      LstStdQueue.ddBlock_Idx = BlockId;
      /* polyspace +3 MISRA-C3:11.5 [Not a defect:Low] "No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)" */
      LstStdQueue.pTempRamBlkData = (uint8*)NvM_DstPtr;
      #if (NVM_JOB_PRIORITIZATION == STD_ON)
      LstStdQueue.ucPriority=NvM_GaaBlkDescTbl[BlockId].ucBlkJobPriority;
      #endif
      /* Put the restore request in the queue  */
      LddReturnValue = NvM_StdQueueWrite(&LstStdQueue);

      /* Check if the queue write is not successful */
      if(LddReturnValue == E_NOT_OK)
      {
        #if(NVM_DEMERROR_REPORT == STD_ON)
        /* Report the queue overflow to DEM */
        Dem_ReportErrorStatus(NvM_GusQueueOverflow,
          DEM_EVENT_STATUS_FAILED);
        #endif
      }
    }

    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count--;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  }
  return (LddReturnValue);
}

#endif  /* (NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) */

/*******************************************************************************
** Function Name        : NvM_EraseNvBlock                                    **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId and  **
**                        Service Id to 'Erase' the NV block data             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : NVRAM Manager should be initialized.                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblInitDone            **
**                        NvM_GaaBlkDescTbl, NvM_GaaRamStatus,                **
**                        NvM_GucReadAllRequest, NvM_GucWriteAllRequest       **
**                        NvM_GusQueueOverflow, NvM_GusWriteProtected         **
**                        NvM_GusTotalNumOfBlock                              **
**                        Function(s) invoked    :Det_ReportError(),          **
**                        Dem_ReportErrorStatus(), NvM_StdQueueWrite()        **
*******************************************************************************/
#if(NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3)

FUNC(Std_ReturnType, NVM_CODE) NvM_EraseNvBlock(NvM_BlockIdType
  BlockId)
{
  #if((NVM_DATASET_PRESENT == STD_ON)||(NVM_JOB_PRIORITIZATION == STD_ON))
  P2CONST(NvM_BlkDescTbl, NVM_CONST, NVM_CONST) LpBlkDescTbl;
  #endif
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  NvM_JobQueue LstJobQueue;
  Std_ReturnType LddReturnValue;

  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, NVM_ERASENVBLOCK_SID,
      NVM_E_NOT_INITIALIZED);
    LddReturnValue = E_NOT_OK;
  }
  /* If Block Identifier is not configured, report error to DET */
  else if((BlockId == NVM_ZERO) || (BlockId >= NvM_GusTotalNumOfBlock))
  {
    /* Report invalid Block Identifier */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_ERASENVBLOCK_SID, NVM_E_PARAM_BLOCK_ID);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  { 
    /* Start of Block comment - 2 */
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count++;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                     (BswM_ModeType)NVM_LOWPOWER_PREVENT);
    #if((NVM_DATASET_PRESENT == STD_ON)||(NVM_JOB_PRIORITIZATION == STD_ON))
    LpBlkDescTbl = &NvM_GaaBlkDescTbl[BlockId];
    #endif
    LpRamStatus = &NvM_GaaRamStatus[BlockId];

    /*
     * Check if the block is write protected or DataIndex is pointing to ROM
     */
    if((*(LpRamStatus) & NVM_WRITE_PROTECT_MASK) == NVM_WRITE_PROTECT_MASK)
    {
       #if(NVM_DEMERROR_REPORT == STD_ON)
      /* Report the write protected to DEM */
      Dem_ReportErrorStatus(NvM_GusWriteProtected, DEM_EVENT_STATUS_FAILED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
    #if(NVM_DATASET_PRESENT == STD_ON)
    else if(((LpBlkDescTbl->enBlkMngmntType) == NVM_BLOCK_DATASET) &&
       /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
       /* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
       (*(LpBlkDescTbl->pRamIndex) >= LpBlkDescTbl->ucNumOfNvBlks))
    {
      LddReturnValue = E_NOT_OK;
    }
    #endif
    #if(NVM_JOB_PRIORITIZATION == STD_ON)
    else if(LpBlkDescTbl->ucBlkJobPriority != NVM_IMM_PRIORITY)
    {
      /* NVM357 */
      #if(NVM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_ERASENVBLOCK_SID, NVM_E_BLOCK_CONFIG);
      #endif
      LddReturnValue = E_NOT_OK;
    }
    #endif
    else
    {  /* Start of Block comment - 3 */
      /* Report DET error if block is locked */
      if((*(LpRamStatus) & NVM_LOCK_RAM_MASK) == NVM_LOCK_RAM_MASK)
      {
        #if(NVM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
          NVM_ERASENVBLOCK_SID, NVM_E_BLOCK_LOCKED);
        #endif
        LddReturnValue = E_NOT_OK;
      }
      /* Ignore the request, if the block is already queued */
      else if((*(LpRamStatus) & NVM_ERROR_BIT_MASK) == NVM_REQ_PENDING)
      {
        #if(NVM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
          NVM_ERASENVBLOCK_SID, NVM_E_BLOCK_PENDING);
        #endif
        LddReturnValue = E_NOT_OK;
      }
      /* Ignore the request, if ReadAll/WriteAll is in progress */
      else if((NvM_GucReadAllRequest == NVM_MULTIBLK_IN_PROGRESS) ||
        (NvM_GucWriteAllRequest == NVM_MULTIBLK_IN_PROGRESS))
      {
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* Load the Service Id, Block Id and RAM buffer pointer */
        LstJobQueue.ucService_Id = NVM_ERASENVBLOCK_SID;
        LstJobQueue.ddBlock_Idx = BlockId;
        LstJobQueue.pTempRamBlkData = (uint8*)NULL_PTR;
        #if (NVM_JOB_PRIORITIZATION == STD_ON)
        LstJobQueue.ucPriority = NvM_GaaBlkDescTbl[BlockId].ucBlkJobPriority;
        #endif
        /* Queue the request in standard Queue */
        LddReturnValue = NvM_StdQueueWrite(&LstJobQueue);

        /* Check if the queue write is not successful */
        if(LddReturnValue == E_NOT_OK)
        {
           #if(NVM_DEMERROR_REPORT == STD_ON)
          /* Report the queue overflow to DEM */
          Dem_ReportErrorStatus(NvM_GusQueueOverflow,
            DEM_EVENT_STATUS_FAILED);
            #endif
        }
      }
    }  /* end of Block comment - 3 */
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count--;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  } /* end of Block comment - 2 */
  return (LddReturnValue);
}

#endif  /* (NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3) */

/*******************************************************************************
** Function Name        : NvM_CancelWriteAll                                  **
**                                                                            **
** Service ID           : 0x0A                                                **
**                                                                            **
** Description          : Cancels a running NvM_WriteAll request.             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
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
** Preconditions        : NVRAM Manager should be initialized                 **
**                                                                            **
** Remarks              : Global Variable(s)     :  NvM_GblInitDone,          **
**                                                  NvM_GucWriteAllRequest,   **
**                                                  NvM_GblCancelWriteAll,    **
**                                                  NvM_GaaRamStatus,         **
**                        Function(s) invoked    :  Det_ReportError()         **
**                                                                            **
*******************************************************************************/
FUNC(void, NVM_CODE) NvM_CancelWriteAll(void)
{
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;

  #if(NVM_DEV_ERROR_DETECT  == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
     /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_CANCELWRITEALL_SID, NVM_E_NOT_INITIALIZED);
  }
  #endif
  
  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
  NvM_GucPM_Count++;
  SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                   (BswM_ModeType)NVM_LOWPOWER_PREVENT);

  if(NvM_GucWriteAllRequest != NVM_MULTIBLK_UNREQUESTED)
  {
    LpRamStatus = &NvM_GaaRamStatus[NVM_ZERO];

    *LpRamStatus = (*LpRamStatus & NVM_NOT_ERROR_BIT_MASK ) |
      (NVM_REQ_CANCELED);

    /*
     * Flag is set, which is checked in 'WriteAll' processing function to
     * cancel the 'WriteAll' request that is in progress
     */
    NvM_GblCancelWriteAll  = (boolean)NVM_TRUE;
  }

  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
  NvM_GucPM_Count--;
  SchM_Exit_NvM_RAM_STATUS_PROTECTION();
}

/*******************************************************************************
** Function Name        : NvM_InvalidateNvBlock                               **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : Request updates the job queue with the BlockId      **
**                        and Service Id to 'Invalidate' the NV block data.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : NvM  should be initialized                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblInitDone,           **
**                        NvM_GaaBlkDescTbl, NvM_GaaRamStatus,                **
**                        NvM_GucReadAllRequest, NvM_GucWriteAllRequest       **
**                        NvM_GusQueueOverflow, NvM_GusWriteProtected         **
**                        NvM_GusTotalNumOfBlock                              **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        Dem_ReportErrorStatus(), NvM_StdQueueWrite()        **
*******************************************************************************/
#if(NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3)

FUNC(Std_ReturnType, NVM_CODE) NvM_InvalidateNvBlock(
  NvM_BlockIdType BlockId)
{
  #if(NVM_DATASET_PRESENT == STD_ON)
  P2CONST(NvM_BlkDescTbl, NVM_CONST, NVM_CONST) LpBlkDescTbl;
  #endif
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  NvM_JobQueue LstJobQueue;
  Std_ReturnType LddReturnValue;

  /*
   * If Development error detection is enabled, validation of input parameters
   * is done and initialization is checked.
   */
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_INVALIDATENVBLOCK_SID, NVM_E_NOT_INITIALIZED);
    LddReturnValue = E_NOT_OK;
  }
  /* If Block Identifier is not configured, report error to DET */
  else if((BlockId == NVM_ZERO) || (BlockId >= NvM_GusTotalNumOfBlock))
  {
    /* Report invalid Block Identifier */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_INVALIDATENVBLOCK_SID, NVM_E_PARAM_BLOCK_ID);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  { 
    /* start of Block comment - 2 */
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count++;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                     (BswM_ModeType)NVM_LOWPOWER_PREVENT);

    #if(NVM_DATASET_PRESENT == STD_ON)
    LpBlkDescTbl = &NvM_GaaBlkDescTbl[BlockId];
    #endif
    LpRamStatus = &NvM_GaaRamStatus[BlockId];

    if((*(LpRamStatus) & NVM_WRITE_PROTECT_MASK) == NVM_WRITE_PROTECT_MASK)
    {
      #if(NVM_DEMERROR_REPORT == STD_ON)
      /* Report the write protected to DEM */
      Dem_ReportErrorStatus(NvM_GusWriteProtected, DEM_EVENT_STATUS_FAILED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
    #if(NVM_DATASET_PRESENT == STD_ON)
    /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
    /* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
    else if(((LpBlkDescTbl->enBlkMngmntType) == NVM_BLOCK_DATASET) &&
       (*(LpBlkDescTbl->pRamIndex) >= LpBlkDescTbl->ucNumOfNvBlks))
    {
      LddReturnValue = E_NOT_OK;
    }
    #endif
    else
    { /* start of Block comment - 3 */
      /* Report DET error if block is locked*/
      if((*(LpRamStatus) & NVM_LOCK_RAM_MASK) == NVM_LOCK_RAM_MASK)
      {
        #if(NVM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
          NVM_INVALIDATENVBLOCK_SID, NVM_E_BLOCK_LOCKED);
        #endif
        LddReturnValue = E_NOT_OK;
      }
      else if((*(LpRamStatus) & NVM_ERROR_BIT_MASK) == NVM_REQ_PENDING)
      {
        /*
         * If the request for the block is present in queue or currently in
         * progress, report error to DET
         */
        #if(NVM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
          NVM_INVALIDATENVBLOCK_SID, NVM_E_BLOCK_PENDING);
        #endif
        LddReturnValue = E_NOT_OK;
      }
      /*
       * Ignore the request, if the block is already queued or if
       * ReadAll/WriteAll is in progress
       */
      else if( (NvM_GucReadAllRequest == NVM_MULTIBLK_IN_PROGRESS)
        || (NvM_GucWriteAllRequest == NVM_MULTIBLK_IN_PROGRESS))
      {
         LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* Load the Service Id, Block Id and RAM buffer pointer */
        LstJobQueue.ucService_Id = NVM_INVALIDATENVBLOCK_SID;
        LstJobQueue.ddBlock_Idx = BlockId;
        LstJobQueue.pTempRamBlkData = (uint8*)NULL_PTR;
        #if (NVM_JOB_PRIORITIZATION == STD_ON)
        LstJobQueue.ucPriority = NvM_GaaBlkDescTbl[BlockId].ucBlkJobPriority;
        #endif
        /* Queue the request in standard Queue */
        LddReturnValue = NvM_StdQueueWrite(&LstJobQueue);

        /* Check if the queue write is not successful */
        if(LddReturnValue == E_NOT_OK)
        {
          #if(NVM_DEMERROR_REPORT == STD_ON)
          /* Report the queue overflow to DEM */
          Dem_ReportErrorStatus(NvM_GusQueueOverflow,
            DEM_EVENT_STATUS_FAILED);
           #endif
        }
      }
    } /* end of Block comment - 3 */
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count--;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  } /* end of Block comment - 2 */
  return (LddReturnValue);
}

#endif  /* (NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3) */

/*******************************************************************************
** Function Name        : NvM_CancelJobs                                      **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : Service to cancel all jobs pending for a NV block   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : NvM  should be initialized                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblInitDone,           **
**                        NvM_GaaBlkDescTbl, NvM_GaaRamStatus                 **
**                        NvM_GusTotalNumOfBlock                              **
**                                                                            **
**                        Function(s) invoked    : Det_ReportError(),         **
**                        NvM_ImmQueueCancel(), NvM_StdQueueCancel()          **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
*******************************************************************************/
#if(NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1)

FUNC(Std_ReturnType, NVM_CODE) NvM_CancelJobs(NvM_BlockIdType BlockId)
{
  #if((NVM_JOB_PRIORITIZATION == STD_ON) && \
    (NVM_IMM_JOB_PRIORITY == STD_ON))
  P2CONST(NvM_BlkDescTbl, NVM_CONST, NVM_CONST) LpBlkDescTbl;
  #endif
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  Std_ReturnType LddReturnValue;
  LddReturnValue = E_NOT_OK;

  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    /* Report non initialization */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, NVM_CANCELJOBS_SID,
      NVM_E_NOT_INITIALIZED);
    LddReturnValue = E_NOT_OK;
  }
  /* If Block Identifier is not configured, report error to DET */
  else if((BlockId == NVM_ZERO) || (BlockId >= NvM_GusTotalNumOfBlock))
  {
    /* Report invalid Block Identifier */
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, NVM_CANCELJOBS_SID,
      NVM_E_PARAM_BLOCK_ID);
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count++;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                     (BswM_ModeType)NVM_LOWPOWER_PREVENT);

    LpRamStatus = &NvM_GaaRamStatus[BlockId];

    if(((*LpRamStatus) & NVM_ERROR_BIT_MASK) != NVM_REQ_PENDING)
    {
      #if((NVM_CRC_SUPPORT == STD_OFF) && (NVM_STATIC_ID_CHECK == STD_OFF))
      LddReturnValue = E_NOT_OK;
      #endif
    }
    else
    {
      #if((NVM_JOB_PRIORITIZATION == STD_ON) && \
        (NVM_IMM_JOB_PRIORITY == STD_ON))
      LpBlkDescTbl = &NvM_GaaBlkDescTbl[BlockId];
      if((LpBlkDescTbl->ucBlkJobPriority) == NVM_IMM_PRIORITY)
      {
        /*
         * Cancel the request in immediate Queue, if block is configured of
         * type immediate priority
         */
        LddReturnValue = NvM_ImmQueueCancel(BlockId);
      }
      else
      #endif
      {
        /*
         * Cancel the request in Standard Queue, if block is configured of
         * type standard priority or if Prioritization is disabled
         */
        LddReturnValue = NvM_StdQueueCancel(BlockId);
      }
      if(LddReturnValue == E_OK)
      {              
        SchM_Enter_NvM_RAM_STATUS_PROTECTION();
        *(LpRamStatus) = (*(LpRamStatus) | NVM_REQ_CANCELED);
        SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      }
    } /* End for main block check*/

    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count--;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  } /* Else End for Valid Block Id check */
  return(LddReturnValue);
}

#endif  /* (NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) */
/*******************************************************************************
** Function Name        : NvM_ReadAll                                         **
**                                                                            **
** Service ID           : 0x0C                                                **
**                                                                            **
** Description          : This call signals the request to the NVRAM Manager  **
**                        and returns                                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
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
** Preconditions        : NVRAM Manager should be initialized                 **
**                                                                            **
** Remarks              : Global Variable(s) : NvM_GblInitDone,               **
**                        NvM_GucReadAllRequest, NvM_GaaRamStatus             **
**                                                                            **
**                        Function(s) invoked: Det_ReportError(),             **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION,               **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION                 **
*******************************************************************************/
FUNC(void, NVM_CODE) NvM_ReadAll(void)
{
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, NVM_READALL_SID,
      NVM_E_NOT_INITIALIZED);
  }
  else
  #endif
  {
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count++;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                     (BswM_ModeType)NVM_LOWPOWER_PREVENT);

    if(NvM_GucReadAllRequest == NVM_MULTIBLK_UNREQUESTED)
    {
      NvM_GucReadAllRequest = NVM_MULTIBLK_REQUESTED;
      NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NVM_REQ_PENDING);
    }
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_GucPM_Count--;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  }
}

/*******************************************************************************
** Function Name        : NvM_WriteAll                                        **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : Request to synchronize the contents of RAM blocks to**
**                        their corresponding NV blocks during shutdown.      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
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
** Preconditions        : NVRAM Manager should be initialized                 **
**                                                                            **
** Remarks              : Global Variable(s)  : NvM_GblInitDone,              **
**                        NvM_GucWriteAllRequest, NvM_GaaRamStatus            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError(),                                  **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION,               **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION                 **
*******************************************************************************/
FUNC(void, NVM_CODE) NvM_WriteAll(void)
{
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(NvM_GblInitDone == NVM_FALSE)
  {
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, NVM_WRITEALL_SID,
      NVM_E_NOT_INITIALIZED);
  }
  #endif

  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
  NvM_GucPM_Count++;
  SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                   (BswM_ModeType)NVM_LOWPOWER_PREVENT);

  if(NvM_GucWriteAllRequest == NVM_MULTIBLK_UNREQUESTED)
  {
    NvM_GucWriteAllRequest = NVM_MULTIBLK_REQUESTED;
    NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NVM_REQ_PENDING);
  }

  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
  NvM_GucPM_Count--;
  SchM_Exit_NvM_RAM_STATUS_PROTECTION();
}

/*******************************************************************************
** Function Name        : NvM_MainFunction                                    **
**                                                                            **
** Service ID           : 0x0E                                                **
**                                                                            **
** Description          : Function performs the processing of the NVM Manager **
**                        jobs. This function has to be called cyclically in  **
**                        every case.                                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
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
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GblInitDone,           **
**                        NvM_GblHighPriorityRequest, NvM_GucState            **
**                        NvM_GucNotifiedGlobalStatus, NvM_GpNvmBlkDescTbl    **
**                        NvM_GddJobResultLowLevel, NvM_GddBlockIdx           **
**                        NvM_GucReadAllRequest, NvM_GucWriteAllSubState      **
**                        NvM_GucWriteAllRequest , NvM_GucReadAllState        **
**                        NvM_GpRamAddr, NvM_GblPrevReqImm, NvM_GstStdPrevReq,**
**                        NvM_GaaBlkDescTbl, NvM_GaaMirrorBuffer              **
**                         MemIf_GetJobResult                                 **
**                        Function(s) invoked :NvM_ProcessWriteBlock(),       **
**                        NvM_ProcessWriteAllBlocks(), NvM_ImmQueueRead()     **
**                        NvM_ProcessReadAllBlocks(), MemIf_Cancel()          **
**                        NvM_ScanQueue(), NvM_ProcessImmdWrite(),            **
**                        NvM_UpdateGlobalVars(), NvM_ProcessReadBlock(),     **
**                        MemIf_SetMode(), NvM_ProcessEraseInvalidBlk(),      **
**                        MemIf_GetStatus()                                   **
**                        NvM_ProcessRestoreBlock, NVM_MULTI_BLOCK_CBK(),     **
**                        BswM_NvM_CurrentJobMode                             **
**                        Gpt_DisableNotification(), Gpt_StopTimer()          **
**                        Gpt_EnableNotification(), Gpt_StartTimer()          **
*******************************************************************************/
FUNC(void, NVM_CODE) NvM_MainFunction(void)
{ 
  /* check the initialization is completed */
  if(NvM_GblInitDone == (boolean)NVM_TRUE)
  {
    /*
     * This section performs the polling of job status of the MEMIF layer and
     * is available only if NVM_POLLING_MODE is enabled
     */
    #if(NVM_POLLING_MODE == STD_ON)
    if((NULL_PTR != NvM_GpNvmBlkDescTbl) &&
      (NvM_GddJobResultLowLevel == NVM_REQ_PENDING) )
    {
      MemIf_JobResultType result;
      
      result = MemIf_GetJobResult(NvM_GpNvmBlkDescTbl->ucNvramDeviceId);
      if (result == MEMIF_JOB_OK)
      {
        NvM_GddJobResultLowLevel = NVM_REQ_OK;
      }
      else if (result != MEMIF_JOB_PENDING)
      {
        NvM_GddJobResultLowLevel = NVM_REQ_NOT_OK;
      }
      else
      {
        /* Else loop added to avoid QAC warning */
      }
    }
    #endif

    /*
     * This section performs the processing of immediate priority requests and
     * is available only if NVM_JOB_PRIORITIZATION is enabled
     */
    #if (NVM_JOB_PRIO== STD_ON)
    if(NvM_GblHighPriorityRequest == (boolean)NVM_TRUE)
    {
      /* Immediate priority 'Write'  request is being processed */
      switch (NvM_GucState)
      {
        case NVM_IMMD_WRITE_PENDING :
          if(NvM_GddJobResultLowLevel != NVM_REQ_PENDING)
          {
            NvM_ProcessImmdWrite();
          }
          break;
        case NVM_WRITEBLOCK_SID :
          NvM_ProcessWriteBlock();
          break;
        case NVM_READBLOCK_SID:
          NvM_ProcessReadBlock();
          break;
        case NVM_RESTOREBLOCKDEFAULTS_SID:
          NvM_ProcessRestoreBlock();
          break;
        default:
          /* Do nothing */
          break;
      }
    }
    else
    #endif
    {     
      #if (NVM_JOB_PRIO== STD_ON)      
      P2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) LpCheckQueue = NvM_ImmQueueRead();
      
      /* Check if immediate priority queue is not empty */
      if ((LpCheckQueue != NULL_PTR) && (LpCheckQueue->ddBlock_Idx < NvM_GusTotalNumOfBlock))
      {
        boolean pending = (boolean)NVM_FALSE;      
        /*
         * If the request is in progress, cancel the request to process
         * immediate priority job
         */
        if ((NULL_PTR != NvM_GpNvmBlkDescTbl) && (NvM_GddJobResultLowLevel == NVM_REQ_PENDING))
        {
          pending = (boolean)NVM_TRUE;
          NvM_GddFirstBlock = NVM_RE_ORIGINAL_FIRST;
        
          MemIf_Cancel(NvM_GpNvmBlkDescTbl->ucNvramDeviceId);
          if (MEMIF_IDLE == MemIf_GetStatus(NvM_GpNvmBlkDescTbl->ucNvramDeviceId))
          {
            NvM_GddJobResultLowLevel = NVM_REQ_OK;
          }
        }

        /*
         * If the ReadAll request is in progress save the ReadAll state
         * variable to resume it after the completion of immediate priority
         * request
         */
        if(NvM_GucState == NVM_READALL_SID)
        {
          if((NvM_GucReadAllState == NVM_READALL_BLKPROCESS) ||
            (NvM_GucReadAllState == NVM_READALL_ROMBLK_PROCESS))
          {
            /*
             * If the ReadAll state is in middle of processing a block, update
             * the state to start,so it can be restarted
             */
            NvM_GucReadAllState = NVM_READALL_PROCESS;
          }
        }
        /*
         * If the WriteAll request is in progress save the WriteAll state
         * variable to resume it after the completion of immediate priority
         * request
         */
        else if(NvM_GucState == NVM_WRITEALL_SID)
        {
          NvM_GucWriteAllSubState = NVM_WRITE_ALL_BLOCK;
        }
        else if(NvM_GucState != NVM_IDLE)
        {
          /*
           * Set a flag to indicate that a immediate request is aborting the
           * standard request and save the states to resume the aborted request
           */
          NvM_GblPrevReqImm = (boolean)NVM_TRUE;
          NvM_GstStdPrevReq.pTempRamBlkData = NvM_GpRamAddr;
        }
        else
        {
          /* Else loop added to avoid QAC warning */
        }

        /*
         * Update the Global Descriptor pointer to process the immediate
         * priority request
         */
        NvM_GpNvmBlkDescTbl = &NvM_GaaBlkDescTbl[LpCheckQueue->ddBlock_Idx];

        NvM_UpdateGlobalVars();
        NvM_GddBlockIdx = LpCheckQueue->ddBlock_Idx;

        #if(NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
        if((NvM_GpNvmBlkDescTbl->usBlkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)
        == NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)
        {
          NvM_GpRamAddr = NvM_GaaMirrorBuffer;
        }
        else
        #endif
        {
          if(NULL_PTR == LpCheckQueue->pTempRamBlkData)
          {
            #if(NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON)
	    /* polyspace +3 MISRA-C3:11.5 [Not a defect:Low] "No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)" */
            NvM_GpRamAddr = NvM_GpNvmBlkDescTbl->pRamBlkData;
            #endif
          }
          else
          {
	    /* polyspace +3 MISRA-C3:11.5 [Not a defect:Low] "No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)" */
            /* polyspace +3 MISRA-C3:11.8 [Not a defect:Low] "No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)" */     
            NvM_GpRamAddr = (uint8 *)((void*)(LpCheckQueue->pTempRamBlkData));
          }
        }

        /* Indicate immediate priority request is under progress */
        NvM_GblHighPriorityRequest = (boolean)NVM_TRUE;
        
        if((boolean)NVM_TRUE == pending)
        {
         /* update the global status to check for the pending immediate write */
          NvM_GucState = NVM_IMMD_WRITE_PENDING;
        }
        else
        {
          NvM_ProcessImmdWrite();
        }   
      }  /* end if(LpCheckQueue != NULL_PTR) */
      else
      #endif 
      /* #if((NVM_JOB_PRIORITIZATION == STD_ON) &&
       *(NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) &&
       * NVM_IMM_JOB_PRIORITY == STD_ON)
       */
      { /* Start of Block comment-1 */
        switch (NvM_GucState)
        {
          case NVM_IDLE:
            /* ReadAll or WriteAll is in process ? */
            if((NvM_GucReadAllRequest != NVM_MULTIBLK_IN_PROGRESS) ||
              (NvM_GucWriteAllRequest != NVM_MULTIBLK_IN_PROGRESS))
            {
              /*
               * The queue implementations are available only for API
               * Configuration Class 2 and 3
               */
              #if(NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
              /* Scan the standard priority queue */
              if(NVM_FALSE == NvM_ScanQueue())
              #endif
              { /* Start of Block comment-2 */

                /*
                 * If none of the queued requests are in progress and ReadAll
                 * is requested
                 */
                if(NvM_GucReadAllRequest == NVM_MULTIBLK_REQUESTED)
                {
                  NvM_GucState = NVM_READALL_SID;
                  NvM_GucReadAllRequest = NVM_MULTIBLK_IN_PROGRESS;

                  /* MemIf_SetMode function to be invoked with fast mode before
                   *  the start of the read activity
                   */
                  #if(NVM_DRV_MODE_SWITCH == STD_ON)
                  if (MEMIF_IDLE == MemIf_GetStatus(MEMIF_BROADCAST_ID))
                  {
                    MemIf_SetMode(MEMIF_MODE_FAST);
                  }                  
                  #endif

                  NvM_GucReadAllState = NVM_READALL_INIT;
                  #if(NVM_TOTAL_NUM_OF_READALL_BLOCKS > 0)
                  NvM_ProcessReadAllBlocks();
                  #else
                  #if(NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
                  BswM_NvM_CurrentJobMode(NVM_READALL_SID, NVM_REQ_OK);
                  #endif
                  /* Clear the main state and flags */
                  NvM_GucReadAllState = NVM_IDLE;
                  NvM_GucState = NVM_IDLE;
                  NvM_GucSubState = NVM_SUB_IDLE;

                  /* Update the ReadAll request flag */
                  NvM_GucReadAllRequest = NVM_MULTIBLK_UNREQUESTED;
                  #endif
                }
                /*
                 * If none of the queued requests are in progress and WriteAll
                 * is requested
                 */
                else if(NvM_GucWriteAllRequest == NVM_MULTIBLK_REQUESTED)
                {
                  /* Update the Write and WriteAll sub states */
                  NvM_GucState = NVM_WRITEALL_SID;
                  NvM_GucWriteAllSubState = NVM_WRITE_ALL_INIT;

                  /* Update the global error status */
                  NvM_GucNotifiedGlobalStatus = NVM_REQ_OK;

                  NvM_GucWriteAllRequest = NVM_MULTIBLK_IN_PROGRESS;

                  #if(NVM_DRV_MODE_SWITCH == STD_ON)
                  MemIf_SetMode(MEMIF_MODE_FAST);
                  #endif

                  #if(NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS > 0)
                  NvM_ProcessWriteAllBlocks();
                  #else
                  #if(NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
                  BswM_NvM_CurrentJobMode(NVM_WRITEALL_SID, NVM_REQ_OK);
                  #endif
                  NvM_GucState = NVM_IDLE;
                  #endif
                }
                else
                {                   
                  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
                  if (NvM_GucPM_Count == NVM_ZERO)
                  {
                    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
                    BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                                     (BswM_ModeType)NVM_LOWPOWER_ALLOW);
                  }
                  else
                  {
                    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
                  }
                }
              }
            }
          break;

        #if(NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1)
        case NVM_READBLOCK_SID:
            NvM_ProcessReadBlock();
        break;

        case NVM_WRITEBLOCK_SID:
             NvM_ProcessWriteBlock();
        break;

        case NVM_RESTOREBLOCKDEFAULTS_SID:
             NvM_ProcessRestoreBlock();
        break;
        #endif

        #if(NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3)
        case NVM_ERASENVBLOCK_SID :
             NvM_ProcessEraseInvalidBlk();
        break;
        #endif

        #if( NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3)
        case NVM_INVALIDATENVBLOCK_SID :
             NvM_ProcessEraseInvalidBlk();
        break;
        #endif

        #if(NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS > 0)
        case NVM_WRITEALL_SID :
             NvM_ProcessWriteAllBlocks();

          /* Check if writing of all blocks are complete */
          if(NvM_GucWriteAllSubState == NVM_WRITE_ALL_IDLE)
          {
            /*
             * Wait for the MEMIF status to become idle before completion of
             * WriteAll request
             */
            if (MEMIF_BUSY_INTERNAL != MemIf_GetStatus(NVM_RESVD_DEVICEID))
            {
              /* Invoke the callback function, if configured */
#if(NVM_MULTIBLKCBK_ENABLE == STD_ON)
              NVM_MULTI_BLOCK_CBK(NVM_WRITEALL_SID, NvM_GucNotifiedGlobalStatus);
#endif              
              #if(NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION != STD_OFF)
              BswM_NvM_CurrentJobMode(NVM_WRITEALL_SID,
                NvM_GucNotifiedGlobalStatus);
              #endif
              NvM_GucState = NVM_IDLE;
              NvM_GucWriteAllRequest = NVM_MULTIBLK_UNREQUESTED;
            }
          }
        break;
        #endif

        case NVM_READALL_SID :
             #if(NVM_TOTAL_NUM_OF_READALL_BLOCKS > 0)
             NvM_ProcessReadAllBlocks();
             #endif
        break;

        default: 
          /* Do nothing */
          break;
        }  /* end of switch (NvM_GucState) */
      } /* End of Block comment-1 */
    }  /* end else part of if(NvM_GblHighPriorityRequest == NVM_TRUE) */
  } /* end if(NvM_GblInitDone == NVM_TRUE) */
} /* End of function body */

/*******************************************************************************
** Function Name      : NvM_GetVersionInfo                                    **
**                                                                            **
** Service ID         : 0x0F                                                  **
**                                                                            **
** Description        : This function returns the version information of      **
**                      NvM module.                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Reentrant                                             **
**                                                                            **
** InputParameters(in): None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : versioninfo                                           **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Precondition       : NA                                                    **
**                                                                            **
** Remarks            : Global Variable(s)     : None                         **
**                                                                            **
**                      Function(s) invoked    : Det_ReportError              **
**                                                                            **
*******************************************************************************/
#if(NVM_VERSION_INFO_API == STD_ON)

FUNC(void, NVM_CODE) NvM_GetVersionInfo
 (P2VAR(Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA) versioninfo)
{

  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  if(versioninfo == NULL_PTR)
  {
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_GETVERSIONINFO_SID, NVM_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "This parameter shall be checked by user" */
    (versioninfo->vendorID) = NVM_VENDOR_ID;
    (versioninfo->moduleID) = NVM_MODULE_ID;
    (versioninfo->sw_major_version) = NVM_SW_MAJOR_VERSION;
    (versioninfo->sw_minor_version) = NVM_SW_MINOR_VERSION;
    (versioninfo->sw_patch_version) = NVM_SW_PATCH_VERSION;
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "This parameter shall be checked by user" */    
  }
} /* End of function body */

#endif  /* (NVM_VERSION_INFO_API == STD_ON) */

#define NVM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end RTE:UNR [Justified:Low] "Not a defect" */
/*
  polyspace-end MISRA-C3:1.1:Not a defect:Justify with annotations> Needed for AR/SW version check
  polyspace-end MISRA-C3:11.5:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)
  polyspace:end<RTE:IDP:Not a defect:Justify with annotations > configured memory access index
  polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
