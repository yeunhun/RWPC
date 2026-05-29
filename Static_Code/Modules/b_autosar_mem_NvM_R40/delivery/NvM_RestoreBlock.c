/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_RestoreBlock.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : RestoreBlockDefaults functions of NVRAM Module                **
**              NvM_ProcessRestoreBlock                                       **
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
** 1.3.4       27-Jan-2016   Yun  YJ      Redmine #11480                      **
** 1.3.3       16-Nov-2016   Song CY      Redmine #6680                       **
** 1.2.3       24-Mar-2016   Song CY      Redmine #4276                       **
** 1.1.8       02-Oct-2015   Song CY      Correct RunTime Error Violation     **
** 1.1.7       09-Jul-2015   Song CY       As per RedMine 2316,               **
**                                        Change Return value to restore      **
**                                        #2265, Change CRC & SID Logic       **
** 1.1.6       03-Mar-2015   Song CY       As per RedMine 2216, Remove version**
**                                        Information                         **
** 1.1.4       02-Dec-2014   Song CY      RedMine 1719, Update for PolySpace  **
** 1.1.0       18-Apr-2014   Song CY      RedMine718 Version is updated       **
** 1.0.0       25-Jan-2013   Song CY      Initial version                     **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/*
  polyspace-begin MISRA-C3:1.1:Not a defect:Justify with annotations> Necessary in logic
  polyspace-begin MISRA-C3:11.5:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)
  polyspace:begin<RTE:IDP:Not a defect:Justify with annotations > configured memory access index
*/
/* polyspace-begin RTE:UNR [Justified:Low] "Not a defect" */
#include "NvM.h"                     /* NvM header file */
#include "NvM_Config.h"
#include "NvM_Ram.h"                 /* Global variables header file */
#if(NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                            /* Det header file */
#endif
/* Internal function header files */
#include "NvM_Process.h"
#include "NvM_RestoreBlock.h"
#include "NvM_CRCStatic.h"

/*******************************************************************************
**                        Function Definitions                                **
*******************************************************************************/

/*******************************************************************************
** Function Name        : NvM_ProcessRestoreBlock                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function Restore the contents of ROM in to RAM **
**                                                                            **
** Sync/Async           : Synchronous                                         **
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
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        NvM_GpRamAddr, NvM_GusBlockLength,                  **
**                        NvM_GpRomBlkDataAddrs, NvM_GaaBlkDescTbl,           **
**                        NvM_GddBlockIdx,                                    **
**                        NvM_GpPreviousRamAddr, NvM_GucState,                **
**                        NvM_GucReadAllState, NvM_GddJobResultLowLevel       **
**                                                                            **
**                        Function(s) invoked    : NvM_UpdateRamStateStatus(),**
**                        NvM_CalculateCRCStaticID(), NvM_EndProcessBlock()   **
*******************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, NVM_CODE) NvM_ProcessRestoreBlock(void)
{
  P2CONST(uint8, NVM_CONST, NVM_CONST)LpRomBlkDataAddrs;
  P2CONST(NvM_BlkDescTbl, NVM_CONST, NVM_CONST) LpBlkDescTbl;
  P2VAR(uint8, AUTOMATIC, NVM_VAR_NOINIT)LpStartRamAddr;

  #if(NVM_INIT_CALLBACK == STD_ON)
  Std_ReturnType LddStatus;
  #endif
  uint16 LusRomBlockLength;
  uint32 LulCount;
  #if(NVM_CRC_SUPPORT == STD_ON)
  uint16 LusBlkParams;
  #endif

  if (NvM_GddBlockIdx < NvM_GusTotalNumOfBlock)
  {
    LpBlkDescTbl = &NvM_GaaBlkDescTbl[NvM_GddBlockIdx];

    LpStartRamAddr = NvM_GpRamAddr;
    #if(NVM_CRC_SUPPORT == STD_ON)
    LusBlkParams = LpBlkDescTbl->usBlkParams;
    #endif
    LpRomBlkDataAddrs = LpBlkDescTbl->pRomBlkData;

    /* Check if ROM block is configured */
    if(LpRomBlkDataAddrs == NULL_PTR)
    {
      /*
       * If ROM is not configured, check if InitCallback function is
       * configured for the block
       */
      #if(NVM_INIT_CALLBACK == STD_ON)
      if(LpBlkDescTbl->pNvMInitNotification_BlockId != NULL_PTR)
      {
        LddStatus =
          LpBlkDescTbl->pNvMInitNotification_BlockId();

        if(LddStatus == E_OK)
        {
          /*
           * If InitCallback function returns E_OK, then update the RAM
           * status
           */
          #if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
            (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
          NvM_UpdateRamStateStatus(NVM_VALID_CHANGED);
          #endif
          NvM_GddJobResultLowLevel = NVM_REQ_OK;
        }
      }
      else
      #endif
      {

        /* Even not INIT_CALLBACK&ROM Block, result should be NVM_REQ_NOT_OK */
        if(NvM_GddJobResultLowLevel != NVM_REQ_INTEGRITY_FAILED)
        {
          NvM_GddJobResultLowLevel = NVM_REQ_NOT_OK;
        }
      }
    }  /* end if(LpRomBlkDataAddrs == NULL_PTR) */
    else
    {
      /* Load the total number of bytes to be copied from ROM */
      LusRomBlockLength = (LpBlkDescTbl->usNvBlkDataLength);

      #if(NVM_DATASET_PRESENT == STD_ON)
      if((LpBlkDescTbl->enBlkMngmntType == NVM_BLOCK_DATASET) &&
        (LpBlkDescTbl->pRamIndex != NULL_PTR) &&
        ((*(LpBlkDescTbl->pRamIndex) >= (LpBlkDescTbl->ucNumOfNvBlks))))
      {
        /* In case of dataset ROM calculate ROM Offset */
        LpRomBlkDataAddrs = &LpRomBlkDataAddrs[LusRomBlockLength *
          ((uint16)(*(LpBlkDescTbl->pRamIndex)) -
          (uint16)(LpBlkDescTbl->ucNumOfNvBlks))];
      }
      #endif

      /*
       * Update the Permanent RAM (if configured) status to 'valid and
       * changed' after loading the default values
       */
      #if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
      NvM_UpdateRamStateStatus(NVM_VALID_CHANGED);
      #endif

      LulCount = NVM_ZERO;
      /* Copy ROM data to RAM block */
      while (LusRomBlockLength != NVM_ZERO)
      {
        /* polyspace +5 MISRA-C3:18.1 [Not a defect:Low] "Pointer is valid" */
	/* polyspace +5 MISRA-C3:D4.1 [Not a defect:Low] "Pointer is valid" */
        LpStartRamAddr[LulCount] = LpRomBlkDataAddrs[LulCount];
        LulCount++;
        LusRomBlockLength--;
      }

      #if(NVM_DATASET_PRESENT == STD_ON)
      if(LpBlkDescTbl->enBlkMngmntType == NVM_BLOCK_DATASET)
      {
        NvM_GddJobResultLowLevel = NVM_REQ_OK;
      }
      else
      #endif
      {
        if (NvM_GucState == NVM_RESTOREBLOCKDEFAULTS_SID)
        {
          NvM_GddJobResultLowLevel = NVM_REQ_OK;
        }
        else
        {
          NvM_GddJobResultLowLevel = NVM_REQ_RESTORED_FROM_ROM;
        }
      }

      NvM_GpRomBlkDataAddrs = LpBlkDescTbl->pRomBlkData;

      /* If CRC is configured to calculate CRC on ROM data */
      #if(NVM_CRC_SUPPORT == STD_ON)
      if(((LusBlkParams & NVM_CALC_RAM_BLK_CRC) == NVM_CALC_RAM_BLK_CRC) &&
        ((LusBlkParams & NVM_DEFAULT_ROM_CRC_ENABLED) ==
        NVM_DEFAULT_ROM_CRC_ENABLED))
      {
        NvM_CalculateCRCStaticID(NvM_GddBlockIdx);
        (void)NvM_CompareCRCSID();
      }
      #endif
    }  /* end else part of if(LpRomBlkDataAddrs == NULL_PTR) */
     /* Restoring the data form ROM is done in cycles */

    /*
     * If the restore operation is complete update the global variables by
     * considering from where 'restore' function was invoked
     * (Read/ReadAll/restore)
     */
    if((NvM_GucState == NVM_RESTOREBLOCKDEFAULTS_SID)
     || (NvM_GucReadAllState == NVM_READALL_ROMBLK_PROCESS))
    {
      #if(NVM_CRC_SUPPORT == STD_ON)
      if(((LusBlkParams & NVM_CALC_RAM_BLK_CRC) == NVM_CALC_RAM_BLK_CRC) &&
        ((LusBlkParams & NVM_DEFAULT_ROM_CRC_ENABLED) ==
          NVM_DEFAULT_ROM_CRC_ENABLED))
      {
        NvM_EndProcessBlock(NvM_GddJobResultLowLevel);
      }
      else
      #endif
      {
        NvM_EndProcessBlock(NvM_GddJobResultLowLevel);
      }
    }
  }
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_RESTOREBLOCKDEFAULTS_SID, NVM_E_PARAM_DATA);
  }
  #endif
} /* End of function body */

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end RTE:UNR [Justified:Low] "Not a defect" */
/*
  polyspace-end MISRA-C3:1.1:Not a defect:Justify with annotations> Necessary in logic
  polyspace-end MISRA-C3:11.5:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)
  polyspace:end<RTE:IDP:Not a defect:Justify with annotations> configured memory access index
  polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
