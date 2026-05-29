/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_EraseInvalidate.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Erase and Invalidate functions of NVRAM Module                **
**              NvM_ProcessEraseInvalidBlk                                    **
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
** 1.3.3       16-Nov-2016   Song CY      Redmine #6680                       **
** 1.1.8       02-Oct-2015   Song CY      Correct RunTime Error Violation     **
** 1.1.6       03-Mar-2015  Song CY       As per RedMine 2216, Remove version **
**                                        Information                         **
** 1.1.0     18-Apr-2014   Song CY     RedMine718 Version is updated          **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM.h"                     /* NvM header file */
#include "MemIf.h"                   /* MemIf header file */
#include "NvM_Ram.h"                 /* Global variables header file */

/* Internal function header files */
#include "NvM_Process.h"
#include "NvM_EraseInvalidate.h"

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/

/*******************************************************************************
** Function Name        : NvM_ProcessEraseInvalidBlk                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is NVRAM Manager NvM_InvalidateNvBlock or      **
**                        NvM_EraseNvBlock API support function. This function**
**                        Invalidates/Erases the NV block.                    **
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
** Return parameter     : LenStatus                                           **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     :  NvM_GucSubState,          **
**                        NvM_GucState, NvM_GenBlkMngmntType,                 **
**                        NvM_GpNvmBlkDescTbl, NvM_GddReStatus,               **
**                        NvM_GddJobResultLowLevel                            **
**                                                                            **
**                        Function(s) invoked   :  NvM_CalcBlkNumber(),       **
**                        MemIf_EraseImmediateBlock(), NvM_EndProcessBlock(), **
**                        MemIf_InvalidateBlock()                             **
*******************************************************************************/

#if(NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3)

#define NVM_START_SEC_CODE
#include "MemMap.h"

FUNC(void,NVM_CODE) NvM_ProcessEraseInvalidBlk(void)
{
  Std_ReturnType LenStatus;
  uint16 LusBlkNumber;

  switch (NvM_GucSubState)
  {

    case NVM_ERASEINVALIDATE_START :
      /* Invoke function to calculate the block number */
      LusBlkNumber = NvM_CalcBlkNumber();

      if(NvM_GucState == NVM_ERASENVBLOCK_SID)
      {
        /* If Erase operation is to be processed */
        if (NvM_GpNvmBlkDescTbl != NULL_PTR)
        {
          LenStatus = MemIf_EraseImmediateBlock
          (NvM_GpNvmBlkDescTbl->ucNvramDeviceId, LusBlkNumber);
        }
        else
        {
          LenStatus =  E_NOT_OK;
        }
      }
      else
      {
        /* If Invalidate operation is to be processed */
        if (NvM_GpNvmBlkDescTbl != NULL_PTR)
        {
          LenStatus = MemIf_InvalidateBlock
          (NvM_GpNvmBlkDescTbl->ucNvramDeviceId, LusBlkNumber);
        }
        else
        {
          LenStatus =  E_NOT_OK;
        }
      }

      if(LenStatus == E_OK)
      {
        /* If MEMIF layer accepts the request  */
        NvM_GddJobResultLowLevel = NVM_REQ_PENDING;
        NvM_GucSubState = NVM_ERASEINVALIDATE_PROCESSING;
      }
      else
      {
        /*
         * If MEMIF layer does not accept the request, update RAM status as
         * unsuccessful and end the processing
         */
        NvM_EndProcessBlock(NVM_REQ_NOT_OK);

      }

    break;

    case NVM_ERASEINVALIDATE_PROCESSING :
      /* Wait for the MEMIF layer to process the request */
      if(NvM_GddJobResultLowLevel != NVM_REQ_PENDING)
      {
        if(NvM_GddJobResultLowLevel == NVM_REQ_OK)
        {
          /*
           * If the Block management type is Redundant block, invalidate
           * 2nd NV block of Redundant block
           */

          if((NvM_GenBlkMngmntType == NVM_BLOCK_REDUNDANT)
            && (NvM_GddReStatus == NVM_RE_CHK_NONE))
          {

            NvM_GucSubState = NVM_ERASEINVALIDATE_START;
            NvM_GddReStatus = NVM_RE_CHKED_ORIGIN;
          }
          else
          {
            if(NvM_GucState == NVM_ERASENVBLOCK_SID)
            {
              NvM_EndProcessBlock(NVM_REQ_OK);
            }
            else
            {
              NvM_EndProcessBlock(NVM_REQ_NV_INVALIDATED);
            }
          }
        }
        else
        {
          /* If MEMIF layer returns job failure, Update the RAM status */
             NvM_EndProcessBlock(NVM_REQ_NOT_OK);
        }
      }  /* end if(NvM_GddJobResultLowLevel != NVM_REQ_PENDING) */

    break;

    default :
      /* Do nothing */
      break;

  }   /* end switch (NvM_GucSubState) */

} /* End of function body */

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* (NVM_API_CONFIG_CLASS  ==  NVM_API_CONFIG_CLASS_3) */

/* polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
