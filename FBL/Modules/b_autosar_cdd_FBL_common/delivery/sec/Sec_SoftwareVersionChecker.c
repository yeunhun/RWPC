/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Sec_SwVersionCheck.c                                          **
**                                                                            **
**  TARGET    : ALL													                                  **
**                                                                            **
**  PRODUCT   : Cdd_FBL                                                       **
**                                                                            **
**  PURPOSE   : SW Version Check                                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.23.1.0  06-Jun-2022   JSCHOI           Redmine #36032                    **
** 1.23.0    27-Dec-2021   JH Lim           R40-Redmine #31776                **
*******************************************************************************/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Sec_SoftwareVersionChecker.h"
#include "Sec_CRC16.h"
#include "FlsIf.h"
#include "Det.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

uint32 Fbl_Gu32_PreviousVersion;

uint32 Fbl_Gu32_CurrentVersion;

uint32 Fbl_Gu32_NewVersion;

Fbl_VerStateType Fbl_Gbl_VersionStatus;

uint32 Fbl_Gu32_EraseReservedStartAddress;

uint32 Fbl_Gu32_EraseReservedLength;

uint32 Fbl_Gu32_EraseStartAddress;

uint32 Fbl_Gu32_EraseLength;

Fbl_BlkStateType Fbl_Gen_BlkState;

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

void Sec_SvcInit(void);

Std_ReturnType Sec_SvcGetVersion(const Fbl_BlkFlashInfo* pHeader, \
  const Fbl_BlkFlashInfo* pTrailer, uint32* pCurrentVersion, uint32* pPreviousVersion);

Std_ReturnType Sec_SvcUpdateBlk(const Fbl_BlkFlashInfo* pTarget, \
  uint32 previousVersion);

Std_ReturnType Sec_SvcRecoveryBlk(const Fbl_BlkFlashInfo* pTarget, \
  Fbl_BlkCrcInfo* pSource);

static Std_ReturnType Sec_SvcVerifyAndCopyBlk(const Fbl_BlkFlashInfo* pTarget, \
  Fbl_BlkCrcInfo* pBlock, uint32 magicNumber);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"
/*******************************************************************************
** Function Name        : Sec_SvcInit                                         **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function shall initialize global variable      **
**                        defined in the VersionCheck                         **
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
** Remarks              : Global Variable(s)  :                               ** 
**                            Fbl_Gu32_PreviousVersion                        **
**                            Fbl_Gu32_CurrentVersion                         **
**                            Fbl_Gu32_NewVersion                             **
**                            Fbl_Gbl_VersionStatus                           **
**                            Fbl_Gu32_EraseReservedStartAddress              **
**                            Fbl_Gu32_EraseReservedLength                    **
**                            Fbl_Gu32_EraseStartAddress                      **
**                            Fbl_Gu32_EraseStartAddress                      **
**                            Fbl_Gen_BlkState                                **
**                        Function(s) invoked :                               **
**                            None                                            **
*******************************************************************************/
void Sec_SvcInit(void)
{
  Fbl_Gu32_PreviousVersion = 0U;
  
  Fbl_Gu32_CurrentVersion = 0U;

  Fbl_Gu32_NewVersion = 0U;
  
  Fbl_Gbl_VersionStatus = FBL_VERSION_INIT;

  Fbl_Gu32_EraseReservedStartAddress = 0U;

  Fbl_Gu32_EraseReservedLength = 0U;

  Fbl_Gu32_EraseStartAddress = 0U;

  Fbl_Gu32_EraseLength = 0U;

  Fbl_Gen_BlkState = FBL_BLK_INIT;    
}

/*******************************************************************************
** Function Name        : Sec_SvcGetVersion                                   **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function parse the version information which   **
**                        saved in the code flash.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pHeader, pTrailer                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pCurrentVersion, pPreviousVersion                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : This function is called after routineControlErase   **
**                                                                            **
** Remarks              : Global Variable(s)  :                               ** 
**                            Fbl_Gen_BlkState                                **
**                        Function(s) invoked :                               **
**                            Sec_SvcVerifyAndCopyBlk                         **
**                            Det_ReportError                                 **
**                            Sec_SvcRecoveryBlk                              **
*******************************************************************************/
Std_ReturnType Sec_SvcGetVersion(const Fbl_BlkFlashInfo* pHeader, \
  const Fbl_BlkFlashInfo* pTrailer, uint32* pCurrentVersion, uint32* pPreviousVersion)
{ 
  Fbl_BlkCrcInfo header = {0, };
  Fbl_BlkCrcInfo trailer = {0, };
  Fbl_BlkStateType blkState = FBL_BLK_INIT;

  Std_ReturnType headerCheck = E_OK;
  Std_ReturnType trailerCheck = E_OK;
  Std_ReturnType Ldt_RetValue = E_OK;

  /* Copy blk and check the header vaildity */
  headerCheck = Sec_SvcVerifyAndCopyBlk(pHeader, &header, FBL_BLK_MAGIC_NUMBER_HEADER);

  /* Copy blk and check the trailer vaildity */
  trailerCheck = Sec_SvcVerifyAndCopyBlk(pTrailer, &trailer, FBL_BLK_MAGIC_NUMBER_TRAILER);
 
  /* Check the Header Validity*/
  if (E_OK == headerCheck)
  {
    /* Check the Trailer Validity */
    if (E_OK == trailerCheck)
    {
      /* Check the Current Version of both block */
      if (header.blkInfo.currentVersion == trailer.blkInfo.currentVersion)
      {
        blkState = FBL_BLK_NORMAL;
      }
      else
      {
        /* Check the Header is later than Trailer */
        if (header.blkInfo.previousVersion == trailer.blkInfo.currentVersion)
        {
          /* Header is the latest then trailer */
          blkState = FBL_BLK_HEADER_UPDATED;
        }
        else
        {
          /* Trailer is the latest then Header */
          blkState = FBL_BLK_TRAILER_UPDATED;
        }
      }
    }
    else
    {
      /* Only Header is valid */
      blkState = FBL_BLK_TRAILER_INVALID;
    }
  }
  else /* Header is not valid */
  {
    /* Check the Trailer Validity */
    if (E_OK == trailerCheck)
    {
      /* Only Trailer is valid */
      blkState = FBL_BLK_HEADER_INVALID;
    }
    else /* both are not vaild */
    {
      /* Both block have no information, generally at the first time */
      blkState = FBL_BLK_VIRGIN;
    }
  }	

  /* 
   * Get the current version or restore the trailer 
   */
  switch(blkState)
  {
    case FBL_BLK_INIT:
    case FBL_BLK_TRAILER_UPDATED:
      /* 
       * It is impossible to reach INIT and 
       * TRAILER UPDATE State after Stm_GetVbrStatus() 
       * In this case, Invoke Det and Reset Current Version to Zero
       * Ideally, this can not be reached.
       */
      #if (FBL_DEV_ERROR_DETECT == STD_ON)
      /* Report Det Error */
      (void)Det_ReportError(SVC_MODULE_ID, SVC_INSTANCE_ID,
        SVC_MAIN_FUNCTION_SID, SVC_E_BLK_NOT_FOUND);
      #endif
      /* Set the current version to 0 for all firmware */
      *pCurrentVersion = FBL_BLK_SWVERSION_INIT;
      *pPreviousVersion = FBL_BLK_SWVERSION_INIT;
      break;
      
    case FBL_BLK_VIRGIN:
      /* Set the current version to 0 for all firmware */
      *pCurrentVersion = FBL_BLK_SWVERSION_INIT;
      *pPreviousVersion = FBL_BLK_SWVERSION_INIT;
      break;
      
    case FBL_BLK_HEADER_INVALID:
    case FBL_BLK_HEADER_UPDATED:
    case FBL_BLK_NORMAL:
      /* 
       * Set the current version using trailer current version
       * Thease states have common characteristic which trailer is valid. 
       */
      *pCurrentVersion =  trailer.blkInfo.currentVersion;
      *pPreviousVersion = trailer.blkInfo.previousVersion;
      break;
      
    case FBL_BLK_TRAILER_INVALID:
      /* 
       * This case is occur when reset during the erase & flash the trailer block 
       * In this case, before Routinecontrol erase, Trailer block should be
       * restored 
       */
       
      /* Set the current version using header current version */  
      *pCurrentVersion = header.blkInfo.previousVersion;
      *pPreviousVersion = FBL_BLK_SWVERSION_INIT;

      /* 
       * Recover the trailer Variable using Header's previous version 
       * These information will be flashed in tail
       * It needs for the specific situation which header is broken
       */
      trailer.blkInfo.magicNumber = FBL_BLK_MAGIC_NUMBER_TRAILER;
      trailer.blkInfo.currentVersion = header.blkInfo.previousVersion;
      trailer.blkInfo.previousVersion = FBL_BLK_SWVERSION_INIT;
      trailer.blkCrcInit = 0;
      
      /* Recovery the Trailer Block */
      Ldt_RetValue = Sec_SvcRecoveryBlk(pTrailer, &trailer);
      break;
      
    default:
      /* Not reach here */
      break;   
  }

  /* State Update for Debug */
  Fbl_Gen_BlkState = blkState;
  
  return Ldt_RetValue;  
}

/*******************************************************************************
** Function Name        : Sec_SvcUpdateBlk                                    **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function updates previousVersion and crc       **
**                          at the flash                                      **
**                        crc target : pTarget's magic num, currentVersion,   ** 
**                          previousVersion                                   ** 
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pTarget, previousVersion                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pCurrentVersion, pPreviousVersion                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Code Flash should be accesable (erase/write)        **
**                                                                            **
** Remarks              : Global Variable(s)  :                               ** 
**                            N/A                                             **
**                        Function(s) invoked :                               **
**                            Sec_Crc16CoverArea                              **
**                            FlsIf_Write                                     **
**                            Det_ReportError                                 **
*******************************************************************************/
Std_ReturnType Sec_SvcUpdateBlk(const Fbl_BlkFlashInfo* pTarget, \
  uint32 previousVersion)
{
  Fbl_BlkFlashInfo block = {0, };
  Fbl_BlkCrcInfo tmpBlk = {0, };
  Std_ReturnType Ldt_RetValue = E_OK;
  uint16 Lu16_Crc16 = 0;

  /* For calculate Crc with new previous Version */
  tmpBlk.blkInfo.magicNumber = pTarget->magicNumber;
  tmpBlk.blkInfo.currentVersion = pTarget->currentVersion;
  tmpBlk.blkInfo.previousVersion = previousVersion;
  tmpBlk.blkCrcInit = 0;
  Lu16_Crc16 = tmpBlk.blkCrcInit;
  
  tmpBlk.blkCrc16 = \
    Sec_Crc16CoverArea((uint8*)(&tmpBlk.blkInfo), \
      (uint32)(FBL_BLK_CRC_TARGET_LENGTH), Lu16_Crc16);   

  /* Set the Recovery Data to variable */
  block.previousVersion = tmpBlk.blkInfo.previousVersion;
  block.crcInit = tmpBlk.blkCrcInit;
  block.crcVal = tmpBlk.blkCrc16;
  
  /* Erase was already done by rontine-control erase
   * This prever and crc area have no written yet */
  if (MEM_OK == FlsIf_Write( \
  (Mem_PositionType)&pTarget->previousVersion,
  (Mem_MemPtrType)&block.previousVersion,
  (Mem_SizeType)FBL_BLK_HALF_LENGTH))
  {
    /* Write Success*/
    /* Verify Crc based on written header */
    if (E_OK == Sec_SvcVerifyAndCopyBlk( \
      pTarget, &tmpBlk, tmpBlk.blkInfo.magicNumber))
    {
      /* Success Recovery Trailer*/
    }
    else
    {
      /* Bad CRC */
      Ldt_RetValue = E_NOT_OK;
      #if (FBL_DEV_ERROR_DETECT == STD_ON)
      /* Report Det Error */
      (void)Det_ReportError(SVC_MODULE_ID, SVC_INSTANCE_ID,
        SVC_MAIN_FUNCTION_SID, SVC_E_BLK_UPDATE_FAIL);
      #endif
    }    
  }
  else
  {
    /* Write Fail */
    Ldt_RetValue = E_NOT_OK;
    #if (FBL_DEV_ERROR_DETECT == STD_ON)
    /* Report Det Error */
    (void)Det_ReportError(SVC_MODULE_ID, SVC_INSTANCE_ID,
      SVC_MAIN_FUNCTION_SID, SVC_E_BLK_UPDATE_FAIL);
    #endif    
  }
  /*
  block.previousVersion = 0xAAAAAAAA;
  block.crcInit = 0xAAAA;
  block.crcVal = 0xAAAA;
  
  (void)FlsIf_Write( \
  (Mem_PositionType)&pTarget->previousVersion,
  (Mem_MemPtrType)&block.previousVersion,
  (Mem_SizeType)FBL_BLK_HALF_LENGTH);
  */
	return Ldt_RetValue;
}

/*******************************************************************************
** Function Name        : Sec_SvcRecoveryBlk                                  **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function calculate provided block's crc and    **
**                        re-flash all data of block                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pTarget, pSource                                    **
**                                                                            **
** InOut parameter      : pBlock                                              **
**                                                                            **
** Output Parameters    : pCurrentVersion, pPreviousVersion                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Code Flash should be accesable (erase/write)        **
**                                                                            **
** Remarks              : Global Variable(s)  :                               ** 
**                            N/A                                             **
**                        Function(s) invoked :                               **
**                            Sec_Crc16CoverArea                              **
**                            FlsIf_Erase                                     **
**                            FlsIf_Write                                     **
**                            Det_ReportError                                 **
**                            Sec_SvcVerifyAndCopyBlk                         **
*******************************************************************************/
Std_ReturnType Sec_SvcRecoveryBlk(const Fbl_BlkFlashInfo* pTarget, \
  Fbl_BlkCrcInfo* pSource)
{
  Fbl_BlkFlashInfo block = {0, };
  Fbl_BlkCrcInfo tmpBlock = {0, };
  Std_ReturnType Ldt_RetValue = E_OK;
  uint16 Lu16_Crc16 = 0;
  uint32 Lu32_EraseStartAddress = 0;

  /* Set Crc init Value */
  Lu16_Crc16 = pSource->blkCrcInit;
  /* Calculate CRC */
  Lu16_Crc16 = Sec_Crc16CoverArea((uint8*)(&pSource->blkInfo), \
    (uint32)(FBL_BLK_CRC_TARGET_LENGTH), Lu16_Crc16);
    
  /* Set the Recovery Data to global variable */
  block.magicNumber = pSource->blkInfo.magicNumber;
  block.currentVersion = pSource->blkInfo.currentVersion;     
  block.previousVersion = pSource->blkInfo.previousVersion;
  block.crcInit = pSource->blkCrcInit;
  block.crcVal = Lu16_Crc16;   

  /* Erase Align */
  Lu32_EraseStartAddress = \
    (uint32)pTarget - ((uint32)pTarget % Fbl_Gu32_FlashEraseUnit);
  
  /* Flash Erase the Target Sector */
  if (MEM_OK == FlsIf_Erase( \
  (Mem_PositionType)Lu32_EraseStartAddress, \
  (Mem_SizeType)Fbl_Gu32_FlashEraseUnit /* Need to be update */))
  {
    /* Erase Success */
    if (MEM_OK == FlsIf_Write( \
    (Mem_PositionType)pTarget,
    (Mem_MemPtrType)&block,
    (Mem_SizeType)FBL_BLK_TOTAL_LENGTH))
    {
      /* Write Success*/
      /* Verify Crc based on written header */
      if (E_OK == Sec_SvcVerifyAndCopyBlk( \
        pTarget, &tmpBlock, pSource->blkInfo.magicNumber))
      {
        /* Success Recovery Trailer*/
      }
      else
      {
        /* Bad CRC */
        Ldt_RetValue = E_NOT_OK;
        #if (FBL_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(SVC_MODULE_ID, SVC_INSTANCE_ID,
          SVC_MAIN_FUNCTION_SID, SVC_E_BLK_RECOVERY_FAIL);
        #endif
      }  
    }
    else
    {
      /* Write Fail */
      Ldt_RetValue = E_NOT_OK;
      #if (FBL_DEV_ERROR_DETECT == STD_ON)
      /* Report Det Error */
      (void)Det_ReportError(SVC_MODULE_ID, SVC_INSTANCE_ID,
        SVC_MAIN_FUNCTION_SID, SVC_E_BLK_RECOVERY_FAIL);
      #endif
    }
  }
  else
  {
    /* Erase Fail */
    Ldt_RetValue = E_NOT_OK;
    #if (FBL_DEV_ERROR_DETECT == STD_ON)
    /* Report Det Error */
    (void)Det_ReportError(SVC_MODULE_ID, SVC_INSTANCE_ID,
      SVC_MAIN_FUNCTION_SID, SVC_E_BLK_RECOVERY_FAIL);
    #endif
  }

	return Ldt_RetValue;
}


/*******************************************************************************
** Function Name        : Sec_SvcVerifyAndCopyBlk                           **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : 1) This function verifies target block by using the **
**                           CRC value and Magic Number                       ** 
**                        2) This function save the target block information  **
**                           at the provided pBlock                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pTarget, previousVersion                            **
**                                                                            **
** InOut parameter      : pBlock                                              **
**                                                                            **
** Output Parameters    : pCurrentVersion, pPreviousVersion                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Code Flash should be accesable (erase/write)        **
**                                                                            **
** Remarks              : Global Variable(s)  :                               ** 
**                            N/A                                             **
**                        Function(s) invoked :                               **
**                            Sec_Crc16CoverArea                              **
*******************************************************************************/
static Std_ReturnType Sec_SvcVerifyAndCopyBlk(const Fbl_BlkFlashInfo* pTarget, \
  Fbl_BlkCrcInfo* pBlock, uint32 magicNumber)
{

  uint16 Lu16_Crc16 = 0;
  Std_ReturnType Ldt_RetValue = E_OK;
  /* 
   * Scan Header & Trailer Information 
   */
  /* Update Header Info */
  pBlock->blkInfo.magicNumber = (uint32)(pTarget->magicNumber);
  pBlock->blkInfo.currentVersion = (uint32)(pTarget->currentVersion);
  pBlock->blkInfo.previousVersion = (uint32)(pTarget->previousVersion);
  pBlock->blkCrcInit = (uint16)(pTarget->crcInit);
  pBlock->blkCrc16 = (uint16)(pTarget->crcVal);

  /* Set Crc16 Init Value */
  Lu16_Crc16 = pBlock->blkCrcInit;
  /* Calculate CRC */
  Lu16_Crc16 = Sec_Crc16CoverArea((uint8*)(&pBlock->blkInfo), \
    (uint32)(FBL_BLK_CRC_TARGET_LENGTH), Lu16_Crc16);
    
  /* Check the Header Validity*/
  if ((magicNumber == pBlock->blkInfo.magicNumber) && \
     (Lu16_Crc16 == pBlock->blkCrc16)) 
  {
    Ldt_RetValue = E_OK;
  }
  else /* Header is not valid */
  {
    Ldt_RetValue = E_NOT_OK;
  }	

  return Ldt_RetValue;
}
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/

