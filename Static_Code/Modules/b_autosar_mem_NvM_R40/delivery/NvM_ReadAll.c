/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_ReadAll.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : ReadAll functions of NVRAM Module                             **
**              NvM_ProcessReadAllBlocks                                      **
**              NvM_CheckConfigId                                             **
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
** 1.5.1       30-Dec-2020    Yun YJ      Redmine #27374                      **
** 1.3.7       28-Mar-2019    Yun YJ      Redmine #16765                      **
** 1.3.6       11-Sep-2017    Yun YJ      Redmine #9063                       **
** 1.3.4       07-Dec-2016    Song CY     Redmine #6889                       **
** 1.3.2       10-Oct-2016    Song CY     Redmine #6215                       **
** 1.3.0       25-Jul-2016    Song CY     Redmine #5383                       **
** 1.1.7       09-Jul-2015    Song CY     Justify MISRA-Rule Violation        **
**                                        #2265, Change CRC & SID Logic       **
** 1.1.6       03-Mar-2015    Song CY     As per RedMine 2216, Remove version **
**                                        Information                         **
** 1.1.4       02-Dec-2014    Song CY     RedMine 1719, Update for PolySpace  **
** 1.1.0       18-Apr-2014    Song CY     RedMine718 Version is updated       **
** 1.0.8       30-Sep-2013    Song CY     Update for Library                  **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */
/* polyspace-begin RTE:UNR [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM.h"                  /* NvM header file */
#include "NvM_Ram.h"              /* Global variables header file */
#include "NvM_Config.h"

/* Internal function header files */
#include "NvM_Process.h"
#include "NvM_ReadBlock.h"
#include "NvM_RestoreBlock.h"
#include "NvM_ReadAll.h"


#include "EcuM_Cbk.h"             /* EcuM_Cbk header file */
#include "BswM_NvM.h"             /* BswM_NvM header file */
#include "SchM_NvM.h"             /* SchM_NvM header file */
#include "MemIf.h"                /* MemIf header file */

#if(NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                            /* Det header file */
#endif
/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : NvM_ProcessReadAllBlocks                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is NVRAM Manager internal function.            **
**                        This function checks and loads the RAM contents     **
**                        and reports the Global error/status                 **
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
** Remarks              : Global Variable(s)     : NvM_GucReadAllState,       **
**                        NvM_GaaRamStatus, NvM_GaaNotReadAll, NvM_GaaReadAll,**
**                        NvM_GddBlockIdx, NvM_GpNvmBlkDescTbl,               **
**                        NvM_GaaBlkDescTbl, NvM_GucSubState,                 **
**                        NvM_GblConfigIdMatch, NvM_GucNotifiedGlobalStatus,  **
**                        NvM_GusReadAllCnt,                                  **
**                        NvM_GucReadAllRequest, NvM_GucRetryCount            **
**                        NvM_GusTotalNumOfBlock                              **
**                        Function(s) invoked    : NvM_UpdateGlobalVars(),    **
**                        MemIf_SetMode(), NvM_ProcessRestoreBlock(),         **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION,                **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION,               **
**                        BswM_NvM_CurrentJobMode, NvM_ProcessReadBlock,      **
**                        NVM_MULTI_BLOCK_CBK                                **
*******************************************************************************/
#if(NVM_TOTAL_NUM_OF_READALL_BLOCKS > 0)
FUNC(void, NVM_CODE) NvM_ProcessReadAllBlocks(void)
{
  switch (NvM_GucReadAllState)
  {
    case NVM_READALL_INIT:
    {
      uint16 i;
#if (NVM_BLOCKS_NOT_CONFIG_READALL > 0)
      for(i = 0; i < NVM_BLOCKS_NOT_CONFIG_READALL; i++)
      {
        NVM_SET_JOB_RESULT(NvM_GaaNotReadAll[i], NVM_REQ_BLOCK_SKIPPED);
      }
#endif      
#if (NVM_TOTAL_NUM_OF_READALL_BLOCKS > 0)
      for(i = 0; i < NVM_TOTAL_NUM_OF_READALL_BLOCKS; i++)
      {
        NVM_SET_JOB_RESULT(NvM_GaaReadAll[i], NVM_REQ_PENDING);
      }
#endif
      NvM_GucReadAllState = NVM_READALL_PROCESS;
      break;
    }
    case NVM_READALL_PROCESS :
      if(NvM_GusReadAllCnt < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
      {
        NvM_GddBlockIdx = NvM_GaaReadAll[NvM_GusReadAllCnt];
        NvM_GpNvmBlkDescTbl = &NvM_GaaBlkDescTbl[NvM_GddBlockIdx];
	/* polyspace +2 MISRA-C3:14.3 [Justified:Low] "To avoid the MISRA violation" */
        if(NvM_GddBlockIdx < NvM_GusTotalNumOfBlock)
        {
          if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(NvM_GddBlockIdx))
          {
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)     
            if(NvM_GddBlockIdx == NVM_CONFIGURATION_BLOCK_ID)
            {
              NvM_GucReadAllState = NVM_READALL_BLKPROCESS;
              NvM_GucSubState = NVM_READ_START;
            }
            else
#endif            
            {
              /*
               * Check if Configuration Id matches or NVM_DYNAMIC_CONFIGURATION
               * is false
               */
#if (NVM_DYNAMIC_CONFIGURATION == STD_OFF) 
              /* Process reading of each block */
              NvM_GucReadAllState = NVM_READALL_BLKPROCESS;
              NvM_GucSubState = NVM_READ_START;
              NvM_GucRetryCount = NvM_GpNvmBlkDescTbl->ucMaxNumOfReadRetries;
#else
              if((NvM_GblConfigIdMatch == (boolean)NVM_TRUE)||
                 ((NvM_GpNvmBlkDescTbl->usBlkParams & NVM_RESISTANT_TO_CHANGED_SW)
                   == NVM_RESISTANT_TO_CHANGED_SW))
              {
                /* Process reading of each block */
                NvM_GucReadAllState = NVM_READALL_BLKPROCESS;
                NvM_GucSubState = NVM_READ_START;
                NvM_GucRetryCount = NvM_GpNvmBlkDescTbl->ucMaxNumOfReadRetries;
              }
              else
              {
                /* Process restoring of each block */
                NvM_GucReadAllState = NVM_READALL_ROMBLK_PROCESS;
              }
#endif           
            }
            NvM_UpdateGlobalVars();
          }
        }  /* end if(NvM_GddBlockIdx < (NvM_GusTotalNumOfBlock)) */
      }
      else
      {
        /* If processing of all blocks is complete, update the Global status */
        NvM_GddBlockIdx = NVM_ZERO;

        /* Update the Global Pointer */
        NvM_GpNvmBlkDescTbl = &NvM_GaaBlkDescTbl[NVM_ZERO];

        NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NvM_GucNotifiedGlobalStatus);

        /* Invoke multiblock callback, if configured */
#if(NVM_MULTIBLKCBK_ENABLE == STD_ON)
        NVM_MULTI_BLOCK_CBK(NVM_READALL_SID, NvM_GucNotifiedGlobalStatus);
#endif

        #if(NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
        BswM_NvM_CurrentJobMode(NVM_READALL_SID, NvM_GucNotifiedGlobalStatus);
        #endif

        /*
         * Invoke function(if configured) to put the memory devices back to
         * 'Slow' mode when cancelling the WriteAll request
         */
        #if(NVM_DRV_MODE_SWITCH == STD_ON)
        if (MEMIF_IDLE == MemIf_GetStatus(MEMIF_BROADCAST_ID))
        {
          MemIf_SetMode(MEMIF_MODE_SLOW);
        }          
        #endif

        /* Clear the main state and flags */
        NvM_GucReadAllState = NVM_IDLE;
        NvM_GucState = NVM_IDLE;
        NvM_GucSubState = NVM_SUB_IDLE;

        /* Update the ReadAll request flag */
        NvM_GucReadAllRequest = NVM_MULTIBLK_UNREQUESTED;
      }
    break;

    case NVM_READALL_BLKPROCESS :
      NvM_ProcessReadBlock();

      if(NvM_GucSubState == NVM_SUB_IDLE)
      {
        /* Increment the block index to process the next block */
          NvM_GusReadAllCnt++;
          NvM_GucReadAllState = NVM_READALL_PROCESS;
      }

    break;
    case NVM_READALL_ROMBLK_PROCESS :
      /*
       * Load the default values if ROM block is configured for the blocks
       * when read of the block fails or when Configuration Id mismatches and
       * Resistant to changed software is configured FALSE
       */
      NvM_ProcessRestoreBlock();

      NvM_GusReadAllCnt++;

      /* Update the state to repeat the process until all blocks are
         processed */
      NvM_GucReadAllState = NVM_READALL_PROCESS;

    break;

    default:
      /* Do nothing */
      break;

  }  /* end switch (NvM_GucReadAllState) */

} /* End of function body */

#endif

/*******************************************************************************
** Function Name        : NvM_CheckConfigId                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is NVRAM Manager internal function.            **
**                        This function calculates the Configuration Id       **
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
** Remarks              : Global Variable(s)   : NvM_GpNvmBlkDescTbl,         **
**                        NvM_GaaBlkDescTbl, NvM_GblConfigIdMatch,            **
**                        NvM_GddBlockIdx                                     **
**                                                                            **
**                        Function(s) invoked  : None                         **
*******************************************************************************/
FUNC(void, NVM_CODE) NvM_CheckConfigId(void)
{
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) LpRamBlkData;

  if (NvM_GddBlockIdx < NVM_TOTAL_NUM_OF_NVRAM_BLOCKS)
  {
    NvM_GpNvmBlkDescTbl = &NvM_GaaBlkDescTbl[NvM_GddBlockIdx];
    /* polyspace +3 MISRA-C3:11.5 [Not a defect:Low] "No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)" */  
    LpRamBlkData = NvM_GpNvmBlkDescTbl->pRamBlkData;

    if (NULL_PTR != LpRamBlkData)
    {
      if (NVM_COMPILED_CONFIG_ID == LpRamBlkData[0])
      {
        NvM_GblConfigIdMatch = (boolean)NVM_TRUE;
      }
      else
      {
        NVM_SET_JOB_RESULT(NvM_GddBlockIdx, NVM_REQ_NOT_OK);      
        NvM_GblConfigIdMatch = (boolean)NVM_FALSE;      
        LpRamBlkData[0] = (uint8)NVM_COMPILED_CONFIG_ID;
      }
    }
    else
    {
#if(NVM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
        NVM_READALL_SID, NVM_E_PARAM_BLOCK_DATA_IDX);

#endif
    }

  }
  else
  {
#if(NVM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_READALL_SID, NVM_E_PARAM_BLOCK_DATA_IDX);

#endif
  }
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end RTE:UNR [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
