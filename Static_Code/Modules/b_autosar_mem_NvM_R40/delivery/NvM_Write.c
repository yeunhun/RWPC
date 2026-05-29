/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_Write.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Write functions of NVRAM Module                               **
**              NvM_ProcessWriteBlock                                         **
**              NvM_ProcessWriteAllBlocks                                     **
**              NvM_ProcessImmdWrite                                          **
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
** 1.3.5       28-Mar-2019   Yun YJ       Redmine #16765                      **
** 1.3.4       11-Sep-2017   Yun YJ       Redmine #9063                       **
** 1.3.3       16-Nov-2016   Song CY      Redmine #6680                       **
** 1.3.2       10-Oct-2016   Song CY      Redmine #6215                       **
** 1.3.1       21-Sep-2016   Song CY      Redmine #6058                       **
** 1.3.0       25-Jul-2016   Song CY      Redmine #5383                       **
** 1.2.3       24-Mar-2016   Song CY      Redmine #4276                       **
** 1.2.2       11-Feb-2016   Song CY      Redmine #4183                       **
** 1.1.9       10-Nov-2015   Song CY      Correct MISRA-Rule Violation        **
** 1.1.8       02-Oct-2015   Song CY      Correct RunTime Error Violation     **
** 1.1.7       09-Jul-2015   Song CY      As per RedMine 2265,                **
**                                        Change CRC & SID Logic              **
** 1.1.6       03-Mar-2015   Song CY      As per RedMine 2216, Remove version **
**                                        Information                         **
** 1.1.4       02-Dec-2014   Song CY      RedMine 1719, Update for PolySpace  **
** 1.1.0       30-Sep-2013   Song CY      As per SCR-605                      **
**                                        NvM_ProcessWriteAllBlocks have been **
**                                        updated.                            **
** 1.0.8       30-Sep-2013   Song CY      Update for Library                  **
** 1.0.0       25-Jan-2013   CY Song      Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
  polyspace-begin MISRA-C3:1.1:Not a defect:Justify with annotations> Needed for AR/SW version check
  polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> configured memory access index
  polyspace:begin<RTE:NIV: Not a defect:Justify with annotations > Cannot initialize because of Application variable
  polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/
/* polyspace-begin RTE:UNR [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "NvM.h"                      /* NvM header file */
#include "NvM_Config.h"
#include "string.h"                   /* string header file */

/* Crc precompiler option */
#if(NVM_CRC_SUPPORT == STD_ON)
#include "Crc.h"                      /* Crc header file */
#endif

#include "MemIf.h"                    /* MemIf header file */
#if(NVM_DEMERROR_REPORT == STD_ON)
#include "NvM_Dem_Cfg.h"                            /* Dem header file */
#endif

#if(NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                            /* Det header file */
#endif

#include "NvM_Ram.h"                  /* Global variables header file */
#include "BswM_NvM.h"                 /* BswM_NvM header file */

/* Internal function header files */
#include "NvM_Write.h"
#include "NvM_Process.h"

#include "SchM_NvM.h"                 /* SchM_NvM header file*/
#include "NvM_CRCStatic.h"            /* Internal function header files */

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : NvM_ProcessWriteBlock                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service writes data and CRC from RAM           **
**                        to NV block.                                        **
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
** Remarks              : Global Variable(s)   : NvM_GaaMirrorBuffer,         **
**                        NvM_GucMirrorCount, NvM_GucStdQueEnDis,             **
**                        NvM_GddJobResultLowLevel, NvM_GucSubState,          **
**                        NvM_GenBlkMngmntType, NvM_GddReStatus,              **
**                        NvM_GucRetryCount, NvM_GaaRamStatus,                **
**                        NvM_GpNvmBlkDescTbl, NvM_GucImmQueEnDis,            **
**                        NvM_GblQueueShuffle, NvM_GucImmQueStartPos,         **
**                        NvM_GaaImmQueueBuffer, NvM_GucState,                **
**                        NvM_GucStdQueStartPos, NvM_GaaStdQueueBuffer,       **
**                        NvM_GpRamAddr, NvM_GucWriteVerify,                  **
**                        NvM_GucRepeatMirrorOperations                       **
**                        NvM_GusVerifyFailed, NvM_GddFirstBlock              **
**                        Function(s) invoked  : NvM_CalcBlkNumber(),         **
**                        NvM_CalculateCRCStaticID(), NvM_EndProcessBlock(),  **
**                        NvM_UpdateRamStateStatus(),MemIf_Write(),           **
**                        NvM_CRCSIDCancelJob(), Dem_ReportErrorStatus()      **
*******************************************************************************/
/* polyspace +2 MISRA-C3:8.7 [Justified:Low] "Used in different functions according to configuration" */
FUNC(void, NVM_CODE) NvM_ProcessWriteBlock(void)
{
  #if(NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
  Std_ReturnType LddReturnValue;
  #endif
  Std_ReturnType LddStatus;
  uint8 LucDeviceID;
  uint8 LucWriteRetry;
  uint16 LusBlkNumber;
  uint16 LusBlkParams;
  uint16 LusCnt;
  uint16 LusLengthIndex;
  uint16 LusCRCSIDIndex;
  uint16 LusTempBlkLength;
  uint16 LusGpRAddrIndex;
  #if(NVM_CRC_SUPPORT == STD_ON)
  uint8 LucCrcLength;
  #endif
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  
  if (
    (NULL_PTR != NvM_GaaDataBuffer) &&
    (NULL_PTR != NvM_GpNvmBlkDescTbl)
  )
  {
    LusBlkParams = NvM_GpNvmBlkDescTbl->usBlkParams;
    LucDeviceID = NvM_GpNvmBlkDescTbl->ucNvramDeviceId;
    LucWriteRetry = NvM_GpNvmBlkDescTbl->ucMaxNumOfWriteRetries;

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
      case NVM_WRITE_NVBLOCK:

      #if(NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
      if((LusBlkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE) ==
        NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)
      {
        if(NvM_GucMirrorCount == NVM_ZERO)
        {
          NvM_GucMirrorCount = NvM_GucRepeatMirrorOperations;
        }
        LddReturnValue = (NvM_GpNvmBlkDescTbl->pNvMWriteRamBlockToNvm)
          ((void *)(NvM_GaaMirrorBuffer));
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
            #if((NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) && \
               (NVM_JOB_PRIORITIZATION==STD_ON)&&(NVM_IMM_JOB_PRIORITY==STD_ON))
            if(NvM_GpNvmBlkDescTbl->ucBlkJobPriority == NVM_IMM_PRIORITY)
            {
              if(NvM_GucImmQueEnDis != NVM_ONE)
              {
                NvM_GucImmQueStartPos = NvM_QueueSwap(NvM_GucImmQueStartPos,
                  NvM_GucImmQueEnDis, NvM_GaaImmQueueBuffer);
                NvM_GblQueueShuffle = (boolean)NVM_TRUE;
                NvM_GucState = NVM_IDLE;
              }
              else
              {
                NvM_GucMirrorCount = NvM_GucRepeatMirrorOperations;
              }
            }
            else
            #endif
            {
              if(NvM_GucStdQueEnDis != NVM_ONE)
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
      }
      if(LddReturnValue == E_OK)
      #endif
      {
        if (NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT)
        {
          if (NvM_GddBlockIdx < NvM_GusTotalNumOfBlock)
          {
            LpRamStatus = &NvM_GaaRamStatus[NvM_GddBlockIdx];
            if ((*(LpRamStatus) & NVM_FIR_REDUNDANT_MASK) == NVM_FIR_REDUNDANT_MASK)
            {
              NvM_GddFirstBlock = NVM_RE_COPY_FIRST;
            }
          }
        }

        LusBlkNumber = NvM_CalcBlkNumber();
         /* CRC should not be calculated for the Redundant block */
        if((NvM_GenBlkMngmntType != NVM_BLOCK_REDUNDANT) ||
           (NvM_GddReStatus == NVM_RE_CHK_NONE))
        {
          LusLengthIndex = NVM_ZERO;
          LusCRCSIDIndex = NVM_ZERO;
          #if((NVM_STATIC_ID_CHECK == STD_ON) || (NVM_CRC_SUPPORT == STD_ON))
          if(((LusBlkParams & NVM_CALC_RAM_BLK_CRC) ==
            NVM_CALC_RAM_BLK_CRC) ||
            ((LusBlkParams & NVM_STATIC_BLOCK_ID_CHECK) ==
            NVM_STATIC_BLOCK_ID_CHECK))
            {
              NvM_CalculateCRCStaticID(NvM_GddBlockIdx);
            }
          #endif
          #if(NVM_STATIC_ID_CHECK == STD_ON)
          if((LusBlkParams & NVM_STATIC_BLOCK_ID_CHECK) ==
            NVM_STATIC_BLOCK_ID_CHECK)
          {
            SchM_Enter_NvM_RAM_INDEX();
            for(LusCnt=NVM_ZERO;LusCnt<NVM_TWO;LusCnt++)
            {
              NvM_GaaDataBuffer[LusLengthIndex]=NvM_GaaReadCRCSID[LusCRCSIDIndex];
              LusLengthIndex++;
              LusCRCSIDIndex++;
            }
            SchM_Exit_NvM_RAM_INDEX();
          }
          #endif

          LusTempBlkLength = NvM_GpNvmBlkDescTbl->usNvBlkDataLength;;
          LusGpRAddrIndex = NVM_ZERO;
          if (NvM_GpRamAddr != NULL_PTR)
          {
            do {
              if (LusTempBlkLength > NVM_100)
              {
                SchM_Enter_NvM_RAM_INDEX();
                for(LusCnt=NVM_ZERO;LusCnt<NVM_100;LusCnt++)
                {
                  if (LusLengthIndex < (NvM_GucCrcSidSize+NvM_GusMirrorBufferSize))
                  {
                  /* polyspace<RTE: IDP : Not a defect : Justify with annotations > configured memory access index */
                    NvM_GaaDataBuffer[LusLengthIndex]=NvM_GpRamAddr[LusGpRAddrIndex];
                  }
                  ++LusGpRAddrIndex;
                  ++LusLengthIndex;
                }
                SchM_Exit_NvM_RAM_INDEX();
                LusTempBlkLength = LusTempBlkLength-NVM_100;
              }
              else
              {
                SchM_Enter_NvM_RAM_INDEX();
                for(LusCnt=NVM_ZERO;LusCnt<LusTempBlkLength;LusCnt++)
                {
                  if (LusLengthIndex < (NvM_GucCrcSidSize+NvM_GusMirrorBufferSize))
                  {
                    /* polyspace<RTE: IDP : Not a defect : Justify with annotations > configured memory access index */                    
                    /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
                    /* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
                    NvM_GaaDataBuffer[LusLengthIndex]=NvM_GpRamAddr[LusGpRAddrIndex];
                  }
                  ++LusGpRAddrIndex;
                  ++LusLengthIndex;
                }
                SchM_Exit_NvM_RAM_INDEX();
                LusTempBlkLength = NVM_ZERO;
              }
            }while (LusTempBlkLength != NVM_ZERO);
          }

          #if(NVM_CRC_SUPPORT == STD_ON)
          if((LusBlkParams & NVM_CALC_RAM_BLK_CRC) ==
            NVM_CALC_RAM_BLK_CRC)
          {
            LucCrcLength = NvM_GpNvmBlkDescTbl->ucCrcLength;
            #if(NVM_CRC8_SUPPORT == STD_ON)
            if(LucCrcLength == NVM_CRC_1BYTE)
            {
              SchM_Enter_NvM_RAM_INDEX();
              for(LusCnt=NVM_ZERO;LusCnt<NVM_ONE;LusCnt++)
              {
                if (LusLengthIndex < (NvM_GucCrcSidSize+NvM_GusMirrorBufferSize))
                {
                  NvM_GaaDataBuffer[LusLengthIndex]
                    = NvM_GaaReadCRCSID[LusCRCSIDIndex];
                }
              }
              SchM_Exit_NvM_RAM_INDEX();
            }
            #endif
            #if(NVM_CRC16_SUPPORT == STD_ON)
            if(LucCrcLength == NVM_CRC_2BYTE)
            {
              SchM_Enter_NvM_RAM_INDEX();
              for(LusCnt=NVM_ZERO;LusCnt<NVM_TWO;LusCnt++)
              {
                if (LusLengthIndex < (NvM_GucCrcSidSize+NvM_GusMirrorBufferSize))
                {
                  NvM_GaaDataBuffer[LusLengthIndex]
                    = NvM_GaaReadCRCSID[LusCRCSIDIndex];
                }
                LusLengthIndex++;
                LusCRCSIDIndex++;
              }
              SchM_Exit_NvM_RAM_INDEX();
            }
            #endif
            #if(NVM_CRC32_SUPPORT == STD_ON)
            if(LucCrcLength == NVM_CRC_4BYTE)
            {
              SchM_Enter_NvM_RAM_INDEX();
              for(LusCnt=NVM_ZERO;LusCnt<NVM_FOUR;LusCnt++)
              {
                if (LusLengthIndex < (NvM_GucCrcSidSize+NvM_GusMirrorBufferSize))
                {
                  NvM_GaaDataBuffer[LusLengthIndex]
                    = NvM_GaaReadCRCSID[LusCRCSIDIndex];
                }
                LusLengthIndex++;
                LusCRCSIDIndex++;
              }
              SchM_Exit_NvM_RAM_INDEX();
            }
            #endif
          }
          #endif
        }
        if (LusBlkNumber != NVM_ZERO)
        {
          LddStatus = MemIf_Write(LucDeviceID, LusBlkNumber, NvM_GaaDataBuffer);
        }
        else
        {
          LddStatus = E_NOT_OK;
        }
        
        if(LddStatus == E_OK)
        {
          /* Writing of data is being processed */
          NvM_GddJobResultLowLevel = NVM_REQ_PENDING;
          NvM_GucSubState = NVM_WRITE_PROCESS_NV_BLOCK;
        }
        else
        {
          /*
           * If MEMIF layer does not accept the write request, update RAM status
           * as unsuccessful and end the processing
           */
          NvM_EndProcessBlock(NVM_REQ_NOT_OK);
        }
      }
      break;

      case NVM_WRITE_PROCESS_NV_BLOCK:
        /* Wait for the MEMIF layer to process the request */
        if(NvM_GddJobResultLowLevel != NVM_REQ_PENDING)
        {
          /* Check if MEMIF returns the job result as NVM_REQ_OK */
          if(NvM_GddJobResultLowLevel == NVM_REQ_OK)
          {
            if((NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT) &&
              (NvM_GddReStatus == NVM_RE_CHK_NONE))
            {
              NvM_GucSubState = NVM_WRITE_NVBLOCK;
              NvM_GddReStatus = NVM_RE_CHKED_COPY;
              NvM_GucRetryCount = LucWriteRetry;
            }
            else
            {
              #if(NVM_WRITE_VERIFICATION == STD_ON)
              if((LusBlkParams & NVM_WRITE_VERIFICATION_ENABLE) ==
                NVM_WRITE_VERIFICATION_ENABLE)
              {
                if(NvM_GucWriteVerify == NVM_ZERO)
                {
                  NvM_GpWriteVerifySourceData = NvM_GpRamAddr;
                  NvM_GucWriteVerify = NVM_ONE;
                  for(LusCnt=NVM_ZERO;LusCnt<NvM_GusMirrorBufferSize;LusCnt++)
                  {
                    NvM_GaaDataBuffer[LusCnt] = NVM_ZERO;
                  }
                  NvM_GucState = NVM_READBLOCK_SID;
                  NvM_GucSubState = NVM_READ_START;
                }
              }
              else
              #endif
              {
                /*
                 * If the processing of write is completed successfully update the
                 * the RAM status and end the processing of write request
                 */
                #if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
                  (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
                NvM_UpdateRamStateStatus(NVM_VALID_UNCHANGED);
                #endif

                NvM_EndProcessBlock(NVM_REQ_OK);
              }
            }

            /*
             * If write once is configured for a block, set the write protection
             * bit
             */
            if((LusBlkParams & NVM_WRITE_BLOCK_ONCE) == NVM_WRITE_BLOCK_ONCE)
            {
              SchM_Enter_NvM_RAM_STATUS_PROTECTION();
              /* Set write protect bit */
              if (NvM_GddBlockIdx < NvM_GusTotalNumOfBlock)
              {
                NvM_GaaRamStatus[NvM_GddBlockIdx]
                = NvM_GaaRamStatus[NvM_GddBlockIdx] | NVM_WRITE_PROTECT_MASK;
              }
              SchM_Exit_NvM_RAM_STATUS_PROTECTION();
            }
          }  /* end if(NvM_GddJobResultLowLevel == NVM_REQ_OK) */
          else
          {
            /*
             * Checks if Write Retry counter is exceeded when write operation
             * fails
             */
            if(NvM_GucRetryCount != NVM_ZERO)
            {
              NvM_GucRetryCount--;
              NvM_GucSubState = NVM_WRITE_NVBLOCK;
            }
            else
            {
              if((NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT) &&
                (NvM_GddReStatus == NVM_RE_CHK_NONE))
              {
                /*
                 * If the Write to 1st NV block fails when block is of Redundant
                 * type, process the 2nd NV block of Redundant block
                 */
                NvM_GucSubState = NVM_WRITE_NVBLOCK;
                NvM_GddReStatus = NVM_RE_CHKED_ORIGIN;
                /* Reloading Write retires counter */
                NvM_GucRetryCount = LucWriteRetry;
              }
              else if(NvM_GddReStatus == NVM_RE_CHKED_COPY)
              {
                #if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
                  (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
                NvM_UpdateRamStateStatus(NVM_VALID_UNCHANGED);
                #endif
                /*
                 * If writing of both NV blocks are complete in case of
                 * Redundant block, end the write processing
                 */
                NvM_EndProcessBlock(NVM_REQ_OK);
              }
              else
              {
                /*
                 * If writing of NV blocks is not successful, Update the RAM
                 * status and end the write processing
                 */
                NvM_EndProcessBlock(NVM_REQ_NOT_OK);
              }
            }  /* end else part of if(NvM_GucRetryCount != NVM_ZERO) */
          }  /* end else part of if(NvM_GddJobResultLowLevel ==
              *  NVM_REQ_OK)
              */
        } /* end if(NvM_GddJobResultLowLevel != NVM_REQ_PENDING) */
      break;

      #if(NVM_WRITE_VERIFICATION == STD_ON)
      case NVM_PROCESS_WRITE_VERIFY:
      {
        uint16 LusBlklength = NvM_GpNvmBlkDescTbl->usNvBlkDataLength;
        uint8 LucResult = NVM_TRUE;

        if (NVM_REQ_OK == NvM_GddJobResultLowLevel)
        {
          if (LusBlklength < (NvM_GucCrcSidSize+NvM_GusMirrorBufferSize))
          {
            for (LusCnt = 0; LusCnt < LusBlklength; LusCnt++)
            {            
              /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
              /* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
              if (NvM_GaaDataBuffer[LusCnt] != NvM_GpWriteVerifySourceData[LusCnt])
              {
                LucResult = NVM_FALSE;
                break;
              }
            }
          }
          else
          {
            LucResult = NVM_FALSE;
          }
        }
        else
        {
          LucResult = NVM_FALSE;
        }
        
        if(LucResult == NVM_FALSE)
        {
          #if(NVM_DEMERROR_REPORT == STD_ON)
          /* Report failure of job request to DEM */
          Dem_ReportErrorStatus(NvM_GusVerifyFailed, DEM_EVENT_STATUS_FAILED);
          #endif
          NvM_GpRamAddr = NvM_GpWriteVerifySourceData;

          /* [NVM529] 
           * If the original content in RAM Block is not the same as read back 
           * then write retries shall be performed as specified in this document
           */          
          if(NvM_GucRetryCount != NVM_ZERO)
          {
            NvM_GucRetryCount--;
            NvM_GucState = NVM_WRITEBLOCK_SID;
            NvM_GucSubState = NVM_WRITE_NVBLOCK;
          }
          else
          {
            NvM_EndProcessBlock(NVM_REQ_NOT_OK);
          }
        }
        else
        {
          #if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
            (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
          NvM_UpdateRamStateStatus(NVM_VALID_UNCHANGED);
          #endif
          NvM_EndProcessBlock(NVM_REQ_OK);
        }
        if(NvM_GucWriteAllRequest == NVM_MULTIBLK_IN_PROGRESS)
        {
          NvM_GucState = NVM_WRITEALL_SID;
        }                
        NvM_GucWriteVerify = NVM_ZERO;
        break;
      }
      #endif
    
      default:
        /* Do nothing */
        break;

    }  /* end switch (NvM_GucSubState) */
  }
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_WRITEBLOCK_SID, NVM_E_PARAM_POINTER);
  }
  #endif
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_ProcessWriteAllBlocks                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Processes request to synchronize the contents of RAM**
**                        blocks to their corresponding NV blocks during      **
**                        shutdown.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non reentrant                                       **
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
** Remarks              : Global Variable(s)  : NvM_GucWriteAllSubState,      **
**                        NvM_GaaRamStatus, NvM_GaaNotWriteAll,               **
**                        NvM_GblCancelWriteAll, NvM_GucSubState,             **
**                        NvM_GucRetryCount, NvM_Gblflag, NvM_GusWriteAllCnt  **
**                        NvM_GddBlockIdx, NvM_GaaBlkDescTbl,                 **
**                        NvM_GpNvmBlkDescTbl, NvM_GaaWriteAll,               **
**                        NvM_GucNotifiedGlobalStatus,                        **
**                        NvM_GusTotalNumOfWriteAllBlocks                     **
**                        NvM_GusBlockNotConFigWriteAll                       **
**                        Function(s) invoked  : NvM_UpdateGlobalVars(),      **
**                        MemIf_SetMode(), NvM_ProcessWriteBlock(),           **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION                **
*******************************************************************************/
#if(NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS > 0)

FUNC(void, NVM_CODE) NvM_ProcessWriteAllBlocks(void)
{
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
  uint16 LusWriteAllCnt;

  switch (NvM_GucWriteAllSubState)
  {
    case NVM_WRITE_ALL_INIT:

#if (NVM_BLOCKS_NOT_CONFIG_WRITEALL > 0)
      for(LusWriteAllCnt = 0; LusWriteAllCnt < NvM_GusBlockNotConFigWriteAll;
        LusWriteAllCnt++)
      {
        LpRamStatus = &NvM_GaaRamStatus[NvM_GaaNotWriteAll[LusWriteAllCnt]];

        /* Update the Global error/status to Skipped */
        SchM_Enter_NvM_RAM_STATUS_PROTECTION();

        *(LpRamStatus) = (*(LpRamStatus) &
          (NVM_NOT_ERROR_BIT_MASK )) | (NVM_REQ_BLOCK_SKIPPED);

        SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      }
#endif

      for(LusWriteAllCnt = 0; LusWriteAllCnt < NvM_GusTotalNumOfWriteAllBlocks;
        LusWriteAllCnt++)
      {
        LpRamStatus = &NvM_GaaRamStatus[NvM_GaaWriteAll[LusWriteAllCnt]];

        if(((*(LpRamStatus) & NVM_LOCK_RAM_MASK) != NVM_LOCK_RAM_MASK) &&
          ((*(LpRamStatus) & NVM_WRITE_PROTECT_MASK) !=
          NVM_WRITE_PROTECT_MASK)
          #if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
          && ((*(LpRamStatus) & NVM_VALID_CHANGED) == NVM_VALID_CHANGED)
          #endif
        )
        {
          /* Update the Global error/status to Pending */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();

          *(LpRamStatus) = (*(LpRamStatus) &
            (NVM_NOT_ERROR_BIT_MASK )) | (NVM_REQ_PENDING);

          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        }
        else
        {
          /* Update the Global error/status to Pending */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();

          *(LpRamStatus) = (*(LpRamStatus) &
            (NVM_NOT_ERROR_BIT_MASK )) | (NVM_REQ_BLOCK_SKIPPED);

          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        }
      }
      NvM_GucWriteAllSubState = NVM_WRITE_ALL_BLOCK;
    break;

    case NVM_WRITE_ALL_BLOCK :
      if(NvM_GblCancelWriteAll == (boolean)NVM_TRUE)
      {
        /*
         * If the ongoing WriteAll request is cancelled update the
         * Global error status as CANCELLED
         */
        LpRamStatus = &NvM_GaaRamStatus[NVM_ZERO];

        SchM_Enter_NvM_RAM_STATUS_PROTECTION();

        *LpRamStatus = (*LpRamStatus & NVM_NOT_ERROR_BIT_MASK ) |
          (NVM_REQ_CANCELED);

        SchM_Exit_NvM_RAM_STATUS_PROTECTION();

        #if(NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS > 0)
        for(LusWriteAllCnt = 0; LusWriteAllCnt <
        NvM_GusTotalNumOfWriteAllBlocks; LusWriteAllCnt++)
        {
          LpRamStatus = &NvM_GaaRamStatus[NvM_GaaWriteAll[LusWriteAllCnt]];
          {
            /* Update the Global error/status to Pending */
            SchM_Enter_NvM_RAM_STATUS_PROTECTION();

            *(LpRamStatus) = (*(LpRamStatus) &
              (NVM_NOT_ERROR_BIT_MASK )) | (NVM_REQ_CANCELED);

            SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          }
        }
        #endif

        NvM_GucNotifiedGlobalStatus = NVM_REQ_CANCELED;

        #if(NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
        BswM_NvM_CurrentJobMode(NVM_WRITEALL_SID, NvM_GucNotifiedGlobalStatus);
        #endif

        /* Clear the sub states and the flags */
        NvM_GblCancelWriteAll = (boolean)NVM_FALSE;
        NvM_GucWriteAllSubState = NVM_WRITE_ALL_IDLE;
        NvM_GucSubState = NVM_SUB_IDLE;

        /*
         * Invoke function (if configured) to put the memory devices back to
         * 'Slow' mode when cancelling the WriteAll request
         */
        #if(NVM_DRV_MODE_SWITCH == STD_ON)
        MemIf_SetMode(MEMIF_MODE_SLOW);
        #endif

      }  /* end if(NvM_GblCancelWriteAll == NVM_TRUE) */

      /* Continue processing, if processing of all blocks is not complete */
      else
      {
        if(NvM_GusWriteAllCnt < NvM_GusTotalNumOfWriteAllBlocks)
        {
          do
          {
            NvM_GddBlockIdx = NvM_GaaWriteAll[NvM_GusWriteAllCnt];

              NvM_GpNvmBlkDescTbl = &NvM_GaaBlkDescTbl[NvM_GddBlockIdx];
              LpRamStatus = &NvM_GaaRamStatus[NvM_GddBlockIdx];

              if((*(LpRamStatus) & NVM_ERROR_BIT_MASK) == NVM_REQ_PENDING)
              {
                NvM_Gblflag = (boolean)NVM_TRUE;
                /* Load the Retry counter */
                NvM_GucRetryCount = NvM_GpNvmBlkDescTbl->ucMaxNumOfWriteRetries;
                NvM_UpdateGlobalVars();
                NvM_GucSubState = NVM_WRITE_NVBLOCK;
                NvM_GucWriteAllSubState = NVM_WRITE_ALL_PROCESS;
              }
              else
              {
                NvM_GusWriteAllCnt++;
                NvM_Gblflag = (boolean)NVM_FALSE;
              }
          }while((NvM_Gblflag == NVM_FALSE) &&
            (NvM_GusWriteAllCnt < NvM_GusTotalNumOfWriteAllBlocks));
        }

        if(NvM_GusWriteAllCnt >= NvM_GusTotalNumOfWriteAllBlocks)
        {
          /* If processing of all blocks is complete, update the
           * Global status
          */
          NvM_GddBlockIdx = NVM_ZERO;

          NvM_GpNvmBlkDescTbl = &NvM_GaaBlkDescTbl[NVM_ZERO];
          LpRamStatus = &NvM_GaaRamStatus[NvM_GddBlockIdx];

          /* Update the Global status */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();

          *LpRamStatus = ((*LpRamStatus) & NVM_NOT_ERROR_BIT_MASK) |
            (NvM_GucNotifiedGlobalStatus);

          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          /*
           * Invoke function (if configured) to put the memory devices back to
           * 'Slow' mode after completion of WriteAll request
           */
          #if(NVM_DRV_MODE_SWITCH == STD_ON)
          MemIf_SetMode(MEMIF_MODE_SLOW);
          #endif

          NvM_GucWriteAllSubState = NVM_WRITE_ALL_IDLE;
        } /* end else (NvM_GddBlockIdx < NvM_GusTotalNumOfBlock) */
      }

    break;

    case NVM_WRITE_ALL_PROCESS:

      /* Call the function to copy the RAM data to NV block */
      NvM_ProcessWriteBlock();

      if(NvM_GucSubState == NVM_SUB_IDLE)
      {
        /*
         * If the processing of the block is complete, increment block index to
         * process the next block
         */
        NvM_GusWriteAllCnt++;
        NvM_GucWriteAllSubState = NVM_WRITE_ALL_BLOCK;
      }

    break;

    default:
      /* Do nothing */
      break;

  }  /* end switch (NvM_GucWriteAllSubState) */

}  /* End of function body */
#endif
/*******************************************************************************
** Function Name        : NvM_ProcessImmdWrite                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function which performs the immediate          **
**                        write operation                                     **
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
** Remarks              : Global Variable(s)     : NvM_GucState,              **
**                        NvM_GucRetryCount, NvM_GucSubState,                 **
**                        NvM_GpNvmBlkDescTbl, NvM_GucChkRedundant,           **
**                        NvM_GpRamAddrBackup                                 **
**                        Function(s) invoked    : NvM_UpdateRamStateStatus(),**
**                        NvM_ProcessWriteBlock()                             **
*******************************************************************************/
#if((NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) && \
    (NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))

FUNC(void, NVM_CODE) NvM_ProcessImmdWrite(void)
{
  if ((NvM_GpNvmBlkDescTbl != NULL_PTR) && (NvM_GddBlockIdx < NvM_GusTotalNumOfBlock))
  {
    P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) LpRamStatus;
    LpRamStatus = &NvM_GaaRamStatus[NvM_GddBlockIdx];
    /* Update the main sub states to process immediate write request */
    NvM_GucState = NVM_WRITEBLOCK_SID;
    NvM_GucRetryCount = NvM_GpNvmBlkDescTbl->ucMaxNumOfWriteRetries;
    NvM_GucSubState = NVM_WRITE_NVBLOCK;
    if ((*(LpRamStatus) & NVM_CHECK_NEED_REDUNDANT_MASK)
                        == NVM_CHECK_NEED_REDUNDANT_MASK)
    {
      NvM_GucState = NVM_READBLOCK_SID;
      NvM_GucChkRedundant = NVM_TRUE;
      NvM_GpRamAddrBackup = NvM_GpRamAddr;
      NvM_GpRamAddr = NvM_GaaDataBuffer;
    }
    else
    {
      #if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
        (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
      NvM_UpdateRamStateStatus(NVM_VALID_CHANGED);
      #endif
      NvM_ProcessWriteBlock();
    }
  }
}
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end RTE:UNR [Justified:Low] "Not a defect" */
/*
  polyspace-end MISRA-C3:1.1:Not a defect:Justify with annotations> Needed for AR/SW version check
  polyspace:end<RTE:IDP:Not a defect:Justify with annotations> configured memory access index
  polyspace:end<RTE:NIV: Not a defect:Justify with annotations > Cannot initialize because of Application variable
  polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
