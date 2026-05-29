/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_ReadBlock.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Read functions of NVRAM Module                                **
**              NvM_ProcessReadBlock                                          **
**                                                                            **
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
** 1.5.3       01-Feb-2021   Yun YJ       Redmine #28012                      **
**                                                                            **
** 1.5.1       30-Dec-2020   Yun YJ       Redmine #27374                      **
**                                                                            **
** 1.5.0       26-Jun-2020   Yun YJ       Redmine #9669, #24380               **
**                                                                            **
** 1.3.5       28-Mar-2019   Yun YJ       Redmine #16765                      **
**                                                                            **
** 1.3.4       22-Aug-2017   YJ Yun       Redmine #9285                       **
**                                                                            **
** 1.3.3       16-Nov-2016   Song CY      Redmine #6680                       **
**                                                                            **
** 1.3.2       10-Oct-2016   Song CY      Redmine #6215                       **
**                                                                            **
** 1.3.1       21-Sep-2016   Song CY      Redmine #6058                       **
**                                                                            **
** 1.2.3       24-Mar-2016   Song CY      Redmine #4276                       **
**                                                                            **
** 1.2.2       11-Feb-2016   Song CY      Redmine #4183                       **
**                                                                            **
** 1.2.0       10-Dec-2015   Song CY      RedMine #3633, 3538 Change SyncM and**
**                                        InitCallback Return value           **
**                                                                            **
** 1.1.9       10-Nov-2015   Song CY      RedMine #2981, add dem report and   **
**                                        Correct MISRA-Rule Violation        **
**                                                                            **
** 1.1.8       02-Oct-2015   Song CY      Correct RunTime Error Violation     **
**                                                                            **
** 1.1.7       09-Jul-2015   Song CY      Justify MISRA-Rule Violation        **
**                                        #2265, Change CRC & SID Logic       **
**                                                                            **
** 1.1.6       03-Mar-2015   Song CY      As per RedMine 2208, Add states of  **
**                                        ProcessReadblock                    **
**                                        As per RedMine 2216, Remove version **
**                                        Information                         **
**                                                                            **
** 1.1.4       02-Dec-2014   Song CY      RedMine 1719, Update for PolySpace  **
**                                                                            **
** 1.1.0       18-Apr-2014   Song CY      RedMine718 Version is updated       **
**                                                                            **
** 1.0.8       30-Sep-2013   Song CY      Update for Library                  **
**                                                                            **
** 1.0.0       25-Jan-2013   CY Song      Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
  polyspace-begin MISRA-C3:1.1:Not a defect:Justify with annotations> Necessary in logic
  polyspace-begin MISRA-C3:11.5:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)
  polyspace:begin<RTE:IDP:Not a defect:Justify with annotations > configured memory access index
  polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/
/* polyspace-begin RTE:UNR [Justified:Low] "Not a defect" */
/* polyspace-begin VARIABLE:ALL [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "NvM.h"                     /* NvM header file */
#include "MemIf.h"                   /* MemIf header file */
#if(NVM_DEMERROR_REPORT == STD_ON)
#include "NvM_Dem_Cfg.h"                            /* Dem header file */
#endif
#if(NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                            /* Det header file */
#endif
#include "NvM_Ram.h"                 /* Global variables header file */
#include "NvM_Config.h"

/* Internal function header files */
#include "NvM_Process.h"
#include "NvM_CRCStatic.h"
#include "NvM_ReadBlock.h"
#include "NvM_RestoreBlock.h"
#include "NvM_ReadAll.h"
#include "NvM_ScanQueue.h"

#include "SchM_NvM.h"               /* SchM_NvM header header file */


/*******************************************************************************
**                        Function Definitions                                **
*******************************************************************************/

/*******************************************************************************
** Function Name        : NvM_ProcessReadBlock                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request to copy the data of the NV block to its     **
**                        corresponding RAM block.                            **
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
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GucMirrorCount,        **
**                        NvM_GenBlkMngmntType, NvM_GpNvmBlkDescTbl,          **
**                        NvM_GucSubState,                                    **
**                        NvM_GddJobResultLowLevel, NvM_GaaMirrorBuffer,      **
**                        NvM_GpRamAddr, NvM_GusBlockLength,                  **
**                        NvM_GblRestoreFlag,                                 **
**                        NvM_GucStdQueEnDis, NvM_GaaStdQueueBuffer,          **
**                        NvM_GblQueueShuffle, NvM_GucState,                  **
**                        NvM_GucWriteVerify, NvM_GddBlockIdx,                **
**                        NvM_GaaRamStatus, NvM_GucRetryCount,                **
**                        NvM_GddReStatus, NvM_GucRepeatMirrorOperations      **
**                        NvM_GusIntegrityFailed                              **
**                        Function(s) invoked    : NvM_ProcessRestoreBlock    **
**                        MemIf_Read(), NvM_CheckConfigId(),                  **
**                        NvM_CompareCRCSID(), NvM_CalcBlkNumber()            **
**                        NvM_EndProcessBlock(), NvM_CRCSIDCancelJob()        **
**                        MemIf_GetJobResult(), NvM_CalculateCRCStaticID(),   **
**                        NvM_UpdateRamStateStatus(),                         **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION                **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION                 **
*******************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, NVM_CODE) NvM_ProcessReadBlock(void)
{
  MemIf_JobResultType LddMemStatus;
  Std_ReturnType LddReturnValue;
  Std_ReturnType LddStatus;
  #if(NVM_CRC_SUPPORT == STD_ON)
  uint8 LucCrcLength;
  #endif
  uint8 LucDeviceID;
  uint8 LucReadRetry;
  uint16 LusCnt;
  uint16 LusLengthIndex;
  uint16 LusBlkNumber;
  uint16 LusBlkParams;
  uint16 LusTotalLength;
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;

  /* Do not initialize a static variable to avoid the problem of RH850 compiler 
     When initialized, it is compiled as a constant variable. */
  static MemIf_JobResultType redundantBlockJobResult;
  /* Do not initialize a static variable to avoid the problem of RH850 compiler
     When initialized, it is compiled as a constant variable. */
  static MemIf_JobResultType redundantFirstBlockJobResult;
  
  if ((NvM_GpNvmBlkDescTbl!=NULL_PTR)&&(NvM_GddBlockIdx<NvM_GusTotalNumOfBlock))
  {
    LusBlkParams = NvM_GpNvmBlkDescTbl->usBlkParams;
    LucDeviceID = NvM_GpNvmBlkDescTbl->ucNvramDeviceId;
    LucReadRetry = NvM_GpNvmBlkDescTbl->ucMaxNumOfReadRetries;
    #if(NVM_CRC_SUPPORT == STD_ON)  
    LucCrcLength = NvM_GpNvmBlkDescTbl->ucCrcLength;
    #endif
    LpRamStatus = &NvM_GaaRamStatus[NvM_GddBlockIdx];
 
    #if(NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
    if((LusBlkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE) ==
        NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)
    {
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      LddReturnValue = E_OK;
    }
    #endif

    switch (NvM_GucSubState)
    {
      case NVM_READ_START :
        if (NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT)
        {
          /* in case of Block is first block only */
          if (NvM_GddReStatus == NVM_RE_CHK_NONE)
          {          
            /* initialize jobResult to ok */
            redundantBlockJobResult = MEMIF_JOB_OK;
            redundantFirstBlockJobResult = MEMIF_JOB_OK;
          }
        }
        else
        {
          /* To avoid side-effect , initialize jobResult to ok */
          redundantBlockJobResult = MEMIF_JOB_OK;
          redundantFirstBlockJobResult = MEMIF_JOB_OK;
        }

        /* If atleast one Dataset block is configured */
        #if(NVM_DATASET_PRESENT == STD_ON)
        /*
         * RamBlock Index : pRamIndex < ucNumOfNvBlks
         * RomBlock Index : pRamIndex >= ucNumOfNvBlks
         */
        if((NvM_GenBlkMngmntType == NVM_BLOCK_DATASET) &&
        /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
           /* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
           (*(NvM_GpNvmBlkDescTbl->pRamIndex) >=
           (NvM_GpNvmBlkDescTbl->ucNumOfNvBlks)))
        {
          /* Index of Dataset ROM block is pointing to ROM block area */
          NvM_ProcessRestoreBlock();
          /* After Rom block Restore, Flag setting */
          NvM_GblRestoreFlag = (boolean)NVM_TRUE;
          NvM_EndProcessBlock(NvM_GddJobResultLowLevel);
        }
        else
        #endif
        {
          LusBlkNumber = NvM_CalcBlkNumber();
          /* Calculate Length */
          LusTotalLength = NVM_ZERO;
          #if(NVM_STATIC_ID_CHECK == STD_ON)
          if((LusBlkParams & NVM_STATIC_BLOCK_ID_CHECK)
               == NVM_STATIC_BLOCK_ID_CHECK)
          {
            LusTotalLength = NVM_TWO;
          }
          #endif
          #if(NVM_CRC_SUPPORT == STD_ON)
          if((LusBlkParams & NVM_CALC_RAM_BLK_CRC) == NVM_CALC_RAM_BLK_CRC)
          {
            #if(NVM_CRC8_SUPPORT == STD_ON)
            if(LucCrcLength == NVM_CRC_1BYTE)
            {
              LusTotalLength = LusTotalLength + NVM_ONE;
            }
            #endif
            #if(NVM_CRC16_SUPPORT == STD_ON)
            if(LucCrcLength == NVM_CRC_2BYTE)
            {
              LusTotalLength = LusTotalLength + NVM_TWO;
            }
            #endif
            #if(NVM_CRC32_SUPPORT == STD_ON)
            if(LucCrcLength == NVM_CRC_4BYTE)
            {
              LusTotalLength = LusTotalLength + NVM_FOUR;
            }
            #endif
          }
          #endif
          /* Read NV block */
          if (LusBlkNumber != NVM_ZERO)
          {
            LddStatus = MemIf_Read(LucDeviceID, LusBlkNumber,
              NVM_ZERO, NvM_GaaDataBuffer, NvM_GusBlockLength+LusTotalLength);
          }
          else
          {
            LddStatus = E_NOT_OK;
          }

          /* If MEMIF layer accepts the request */
          if(LddStatus == E_OK)
          {
            /* Read data is being processed */
            NvM_GddJobResultLowLevel = NVM_REQ_PENDING;
            NvM_GucSubState = NVM_READ_NVBLOCK;
          }
          else
          {
            if (NvM_GucRetryCount == NVM_ZERO)
            {
              if((NvM_GddReStatus == NVM_RE_CHK_NONE) && (NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT))
              {
               /*first block in redundant type is NOT accepted in MEMIFlayer*/
                NvM_GblRestoreFlag = (boolean)NVM_FALSE;             
                NvM_GddJobResultLowLevel = NVM_REQ_NOT_OK;
                NvM_GucSubState = NVM_READ_NVBLOCK;              
              }
              else
              {
                NvM_GblRestoreFlag = (boolean)NVM_TRUE;
                /* If MEMIF layer NOT accept the read request, restore from ROM*/
                NvM_ProcessRestoreBlock();
                NvM_EndProcessBlock(NvM_GddJobResultLowLevel);
              }
            }
            else
            {
              NvM_GucRetryCount--;
            }
          }
        }  /* end else part of if((NvM_GenBlkMngmntType == NVM_BLOCK_DATASET) */
      break;

      case NVM_READ_NVBLOCK:
        /* Wait for the MEMIF layer to process the request */
        if(NvM_GddJobResultLowLevel != NVM_REQ_PENDING)
        {
          /* If the Read of NV block is successful */
          if((NvM_GddJobResultLowLevel == NVM_REQ_OK)
              &&(NvM_GusBlockLength <= NvM_GusMirrorBufferSize))
          {
            #if(NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
            if((LusBlkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE) ==
                NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)
            {
              /* SHALLBECHECKED : NvM_GucMirrorCount*/
              if(NvM_GucMirrorCount == NVM_ZERO)
              {
                NvM_GucMirrorCount = NvM_GucRepeatMirrorOperations;
              }
              LddReturnValue = (NvM_GpNvmBlkDescTbl->pNvMReadRamBlockFromNvm)
                ((void *)(NvM_GaaDataBuffer));
              if(LddReturnValue == E_OK)
              {
                NvM_GucMirrorCount = NVM_ZERO;
              }
              else
              {
                if(NvM_GucMirrorCount != NVM_ZERO)
                {
                  NvM_GucMirrorCount--;
                }
                else
                {
                  if(NvM_GucStdQueEnDis > NVM_ONE)
                  {
                    NvM_GucStdQueStartPos = NvM_QueueSwap(NvM_GucStdQueStartPos,
                      NvM_GucStdQueEnDis, NvM_GaaStdQueueBuffer);
                    NvM_GblQueueShuffle = (boolean)NVM_TRUE;
                    NvM_GucState = NVM_IDLE;
                  }
                  else
                  {
                    NvM_GucMirrorCount = NvM_GucRepeatMirrorOperations;
                  }
                }
              }
            }
            if(LddReturnValue == E_OK)
            #endif
            {
              #if(NVM_WRITE_VERIFICATION == STD_ON)
              if(NvM_GucWriteVerify != NVM_ZERO)
              {
                /* NvM_GddJobResultLowLevel is not NVM_REQ_OK */
                NvM_GucState = NVM_WRITEBLOCK_SID;
                NvM_GucSubState = NVM_PROCESS_WRITE_VERIFY;
              }  
              else
              #endif
              {
                #if((NVM_STATIC_ID_CHECK == STD_ON) || \
                    (NVM_CRC_SUPPORT == STD_ON))
                if(((LusBlkParams & NVM_CALC_RAM_BLK_CRC) ==
                     NVM_CALC_RAM_BLK_CRC) ||
                    ((LusBlkParams & NVM_STATIC_BLOCK_ID_CHECK)
                       == NVM_STATIC_BLOCK_ID_CHECK))
                {
                  /* calculate CRC and SID for Read data */
                  NvM_CalculateCRCStaticID(NvM_GddBlockIdx);
                  LddReturnValue = NvM_CompareCRCSID();
                  if(LddReturnValue == E_NOT_OK)
                  {
                    if((NvM_GenBlkMngmntType
                         == NVM_BLOCK_REDUNDANT) &&
                       (NvM_GddReStatus == NVM_RE_CHK_NONE))
                    {
                      SchM_Enter_NvM_RAM_INDEX();
                      /* if CRC is configured and Redundant 1st block, try to 
                         read redundant 2nd block */
                      *(LpRamStatus) = (*(LpRamStatus) & NVM_SEC_REDUNDANT_MASK);
                      *(LpRamStatus) = (*(LpRamStatus) & NVM_CHECK_DONE_REDUNDANT_MASK);
                      SchM_Exit_NvM_RAM_INDEX();
                      NvM_GucSubState = NVM_READ_START;
                      NvM_GddReStatus = NVM_RE_CHKED_ORIGIN;
                      if (NvM_GucState == NVM_READALL_SID)
                      {
                        NvM_GucReadAllState = NVM_READALL_BLKPROCESS;
                      }
                    }
                  }
                  else
                  {
                    if((LusBlkParams & 
                        NVM_STATIC_BLOCK_ID_CHECK) == NVM_STATIC_BLOCK_ID_CHECK)
                    {
                      LusLengthIndex = NVM_TWO;
                    }
                    else
                    {
                      LusLengthIndex = NVM_ZERO;
                    }

                    /* if (NULL_PTR != NvM_GpRamAddr) */
                    {
                      for(LusCnt=NVM_ZERO;LusCnt<NvM_GusBlockLength;LusCnt++)
                      {
                        /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
                        /* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
                        NvM_GpRamAddr[LusCnt]=NvM_GaaDataBuffer[LusLengthIndex];
                        LusLengthIndex++;
                      }
                    }

                    if((NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT) &&
                       (NvM_GddReStatus == NVM_RE_CHK_NONE))
                    {
                      SchM_Enter_NvM_RAM_INDEX();
                      *(LpRamStatus) = (*(LpRamStatus) | NVM_FIR_REDUNDANT_MASK);
                      *(LpRamStatus) =
                                (*(LpRamStatus) & NVM_CHECK_DONE_REDUNDANT_MASK);
                      SchM_Exit_NvM_RAM_INDEX();
                    }

                    /*If CRC matches, update RAM status and end the read process*/
                    #if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
                        (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
                    NvM_UpdateRamStateStatus(NVM_VALID_UNCHANGED);
                    #endif
                    NvM_EndProcessBlock(NVM_REQ_OK);
                  }
                }
                else
                #endif
                {
                  /* if (NULL_PTR != NvM_GpRamAddr) */
                  {
                    for(LusCnt=NVM_ZERO;LusCnt<NvM_GusBlockLength;LusCnt++)
                    {                      
                      /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
                      /* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
                      NvM_GpRamAddr[LusCnt]=NvM_GaaDataBuffer[LusCnt];
                    }
                  }

                  if((NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT) &&
                     (NvM_GddReStatus == NVM_RE_CHK_NONE))
                  {
                    SchM_Enter_NvM_RAM_INDEX();
                    *(LpRamStatus) = (*(LpRamStatus) | NVM_FIR_REDUNDANT_MASK);
                    *(LpRamStatus) =
                              (*(LpRamStatus) & NVM_CHECK_DONE_REDUNDANT_MASK);
                    SchM_Exit_NvM_RAM_INDEX();
                  }     
                  /* End processing if CRC is not configured */
                  #if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
                      (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
                  {
                    NvM_UpdateRamStateStatus(NVM_VALID_UNCHANGED);
                  }
                  #endif
                  NvM_EndProcessBlock(NVM_REQ_OK);
                }

#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)   
                if((NvM_GddBlockIdx == NVM_CONFIGURATION_BLOCK_ID) &&
                   (NvM_GucState == NVM_READALL_SID))
                {
                  NvM_CheckConfigId();
                }
#endif

                if((LusBlkParams & NVM_WRITE_BLOCK_ONCE) == NVM_WRITE_BLOCK_ONCE)
                {
                  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
                  /* Set write protect bit */
                  /* polyspace +2 MISRA-C3:14.3 [Justified:Low] "To avoid the MISRA violation" */
                  if (NvM_GddBlockIdx < NvM_GusTotalNumOfBlock)
                  {
                    NvM_GaaRamStatus[NvM_GddBlockIdx]
                    = NvM_GaaRamStatus[NvM_GddBlockIdx] | NVM_WRITE_PROTECT_MASK;
                  }
                  SchM_Exit_NvM_RAM_STATUS_PROTECTION();
                }
              }
            }
          }
          /**/ 
          else
          {

            /* [NVM530] 
             * If the read back operation fails 
             * then no read retries shall be performed.
             */
            #if(NVM_WRITE_VERIFICATION == STD_ON)
            if(NvM_GucWriteVerify != NVM_ZERO)              
            {
              NvM_GucState = NVM_WRITEBLOCK_SID;
              NvM_GucSubState = NVM_PROCESS_WRITE_VERIFY;
            }
            else
            #endif
            {            
              /*
               * Checks if Read Retry counter is exceeded when Read operation
               * fails
               */
              if(NvM_GucRetryCount != NVM_ZERO)
              {
                NvM_GucRetryCount--;
                NvM_GucSubState = NVM_READ_START;
              }
              else
              {
                /* if block type is redudant block, copy block must be read.*/ 
                if((NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT) &&
                   (NvM_GddReStatus == NVM_RE_CHK_NONE))
                {
                  NvM_GucSubState = NVM_READ_START;
                  /* Read redundant block accepted for processing */
                  NvM_GddReStatus = NVM_RE_CHKED_ORIGIN;
                  /* Reloading Read retires counter */
                  NvM_GucRetryCount = LucReadRetry;
                  
                  SchM_Enter_NvM_RAM_STATUS_PROTECTION();

                  /* NVM_SEC_REDUNDANT_MASK : 0b 1111 1101 1111 1111 */
                  *(LpRamStatus) = (*(LpRamStatus) & NVM_SEC_REDUNDANT_MASK);
                  
                  /* NVM_CHECK_DONE_REDUNDANT_MASK : 0b 1111 1011 1111 1111 
                   * set to 0 [redundant check bit] */
                  *(LpRamStatus) = (*(LpRamStatus) & NVM_CHECK_DONE_REDUNDANT_MASK);
                  /* polyspace +2 MISRA-C3:14.3 [Justified:Low] "It is different according to configuration" */
                  if(NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT)
                  {
                    /* Original block status */
                    redundantFirstBlockJobResult = MemIf_GetJobResult(LucDeviceID);
                  }
                  
                  SchM_Exit_NvM_RAM_STATUS_PROTECTION();
                }
                else
                {
                  /* production  error NVM_E_LOSS_OF_REDUNDANCY */ 
                  boolean reportToDem = (boolean)NVM_FALSE;

                         
                  if(NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT)
                  {
                    MemIf_JobResultType copyBlockJobResult = MemIf_GetJobResult(LucDeviceID);
                    
                    reportToDem = (boolean)NVM_TRUE;

                    /* The CRC failure branches directly to the NVM_READ_ROM 
                     * without the code being executed. 
                     * JobResult is NVM_REQ_OK,  
                     * NvM_GddJobResultLowLevel is NVM_REQ_INTEGRITY_FAILED; 
                     */

                    /* Copy block status */
                    SchM_Enter_NvM_RAM_STATUS_PROTECTION();                    

                    /* if original block is invalidated block */
                    if (MEMIF_BLOCK_INVALID == redundantFirstBlockJobResult)
                    {  
                      if (MEMIF_BLOCK_INVALID == copyBlockJobResult)
                      {
                        /* original = invalidated
                         * copy     = invalidated
                         * result   = invalidated
                         */
                         
                        /* If both original and copy block are invalidated block , 
                          do not report dem event */
                        reportToDem = (boolean)NVM_FALSE;
                        
                      }
                      else
                      {
                        /* original = invalidated
                         * copy     = failed */
                        redundantBlockJobResult = copyBlockJobResult;
                      }
                    }
                    else if (MEMIF_JOB_OK == redundantFirstBlockJobResult)
                    {
                      /* Never be reached */
                    }
                    else
                    {
                      /* original = failed 
                       * copy     = invalidated or (other) failed */
                      redundantBlockJobResult = redundantFirstBlockJobResult;                        
                    }
                    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
                  }

                  if((NvM_GddBlockIdx == NVM_CONFIGURATION_BLOCK_ID) &&
                     (NvM_GucState == NVM_READALL_SID))
                  {
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)     
                    NvM_CheckConfigId();
#else
                    reportToDem = (boolean)NVM_FALSE;
#endif
                  }

                  if ((boolean)NVM_TRUE == reportToDem)
                  {
                    #if(NVM_DEMERROR_REPORT == STD_ON)
                    Dem_ReportErrorStatus(NvM_GusLossOfRedundancy, DEM_EVENT_STATUS_FAILED);
                    #endif
                  }
                    
                  NvM_GucSubState = NVM_READ_ROM;
                }
              }
            }
          }
        } /* end else part of if(NvM_GddJobResultLowLevel != NVM_REQ_PENDING) */
      break;

      case NVM_READ_ROM :
        /* Restore from the ROM, if read request to MEMIF is unsuccessful */
        NvM_ProcessRestoreBlock();

        /* 
         * 1. if block is native, redundantBlockJobResult is MEMIF_JOB_OK always 
         * 2. if block is redundant, both blocks are valid redundantBlockJobResult is MEMIF_JOB_OK.
         */
        if (MEMIF_JOB_OK == redundantBlockJobResult)
        {
          LddMemStatus = MemIf_GetJobResult(LucDeviceID);
        }
        else
        {
#ifdef NVM_MODULE_ACTIVE        
          /* for Unit Test Only */
          (void)MemIf_GetJobResult(LucDeviceID);
#endif          
          LddMemStatus = redundantBlockJobResult;
        }
        if ((NvM_GddBlockIdx == NVM_CONFIGURATION_BLOCK_ID) &&
           (NvM_GucState == NVM_READALL_SID))
        {
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)     
          NvM_EndProcessBlock(NVM_REQ_INTEGRITY_FAILED);
#else
          /* Don't report a event to dem */
          NvM_EndProcessBlock(NVM_REQ_NV_INVALIDATED);
#endif
        }
        else if (NvM_GddJobResultLowLevel == NVM_REQ_OK)
        {
          NvM_EndProcessBlock(NVM_REQ_OK);
        }  
        else if(NvM_GddJobResultLowLevel == NVM_REQ_RESTORED_FROM_ROM)
        {
          NvM_EndProcessBlock(NVM_REQ_RESTORED_FROM_ROM);
          if(LddMemStatus == MEMIF_BLOCK_INCONSISTENT)
          {
            #if(NVM_DEMERROR_REPORT == STD_ON)
            /* Report failure of job request to DEM */
            Dem_ReportErrorStatus(NvM_GusIntegrityFailed,
                                    DEM_EVENT_STATUS_FAILED);
            #endif
          }
          if(LddMemStatus == MEMIF_JOB_FAILED)
          {
            #if(NVM_DEMERROR_REPORT == STD_ON)
            /* Report failure of job request to DEM */
            Dem_ReportErrorStatus(NvM_GusReqFailed, DEM_EVENT_STATUS_FAILED);
            #endif
          }
        }
        else if(LddMemStatus == MEMIF_BLOCK_INVALID)
        {
          NvM_EndProcessBlock(NVM_REQ_NV_INVALIDATED);
        }
        else if(LddMemStatus == MEMIF_BLOCK_INCONSISTENT)
        {
          NvM_EndProcessBlock(NVM_REQ_INTEGRITY_FAILED);
        }
        else if(LddMemStatus == MEMIF_JOB_FAILED)
        {
          NvM_EndProcessBlock(NVM_REQ_NOT_OK);
        }
        /* if CRC not match, LddMemStatus is NVM_REQ_OK , 
           but NvM_GddJobResultLowLevel is NVM_REQ_INTEGRITY_FAILED */
        else 
        {
          NvM_EndProcessBlock(NvM_GddJobResultLowLevel);
        }
      break;
      default:
        /* Do nothing */
        break;
    } /* end switch (NvM_GucSubState) */
  }
  else
  {
    #if(NVM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_READBLOCK_SID, NVM_E_PARAM_POINTER);
    #endif
  }    
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end RTE:UNR [Justified:Low] "Not a defect" */
/* polyspace-end VARIABLE:ALL [Justified:Low] "Not a defect" */
/*
  polyspace-end MISRA-C3:1.1:Not a defect:Justify with annotations> Necessary in logic
  polyspace-end MISRA-C3:11.5:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)
  polyspace:end<RTE:IDP:Not a defect:Justify with annotations> configured memory access index
  polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
