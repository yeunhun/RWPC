/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Sec.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Implements decompression function                             **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_Cfg.h"
#include "Fbl_Dcmpr.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/

/*******************************************************************************
**                            Internal Variables                              **
*******************************************************************************/
#define BTL_START_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"

/* Memory for decompression context data */
Fbl_DecompDataContext Fbl_GstDecompressContext;

#define BTL_STOP_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                        Global Function Definition                          **
*******************************************************************************/
#define BTL_START_SEC_USER_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
** Function Name        : Fbl_DecompressInit                                  **
**                                                                            **
** Description          : Initialize decompression module                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Lu8_DataFormatIdentifier,                           **
**                        Lu32_TotalInputDataLength                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
void Fbl_DecompressInit(
  uint8 Lu8_DataFormatIdentifier,   /* DataFormatIdentifier */
  uint32 Lu32_TotalInputDataLength  /* 압축된 입력 데이터의 전체 길이 */
  )
{
  /* Example */
  Fbl_GstDecompressContext.bl_first = TRUE;
  Fbl_GstDecompressContext.Lu8_dataFormatIdentifier = Lu8_DataFormatIdentifier;
  Fbl_GstDecompressContext.u32_totalInputDataLength = Lu32_TotalInputDataLength;
}

/*******************************************************************************
** Function Name        : Fbl_DecompExpandData                                **
**                                                                            **
** Description          : Decompress the input data                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : inBuffer                                            **
**                                                                            **
** InOut parameter      : inbuffBytesLeft, outbuffBytesLeft                   **
**                                                                            **
** Output Parameters    : outBuffer                                           **
**                                                                            **
** Return parameter     : Fbl_DecompReturnType                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
Std_ReturnType Fbl_DecompExpandData(const uint8* Lpu8_SourceDataPtr, uint32 Lu32_Length, uint32 Lu32_TargetAddr)
{
	/* Variable for holding the return value of the function */

	return E_OK;

}


#define BTL_STOP_SEC_USER_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
