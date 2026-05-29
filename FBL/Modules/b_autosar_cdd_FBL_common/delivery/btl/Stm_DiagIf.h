/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Stm_DiagIf.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Stm_DiagIf.c                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.1     06-Dec-2019   Sinil        Redmine #20402                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef STM_DIAGIF_H
#define STM_DIAGIF_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Dcm.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#if (DCM_DIAGSESSIONCONTROL_SERVICE == STD_ON)
#define STM_DIAGIF_DIAGSESSIONCONTROL_SERVICE                             STD_ON
#else
#define STM_DIAGIF_DIAGSESSIONCONTROL_SERVICE                            STD_OFF
#endif

#if (DCM_ECURESET_SERVICE == STD_ON)
#define STM_DIAGIF_ECURESET_SERVICE                                       STD_ON
#else
#define STM_DIAGIF_ECURESET_SERVICE                                      STD_OFF
#endif

#if (DCM_SECURITYACCESS_SERVICE == STD_ON)
#define STM_DIAGIF_SECURITYACCESS_SERVICE                                 STD_ON
#else
#define STM_DIAGIF_SECURITYACCESS_SERVICE                                STD_OFF
#endif

#if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
#define STM_DIAGIF_ROUTINECONTROL_SERVICE                                 STD_ON
#else
#define STM_DIAGIF_ROUTINECONTROL_SERVICE                                STD_OFF
#endif

#if (DCM_REQUESTDOWNLOAD_SERVICE == STD_ON)
#define STM_DIAGIF_REQUESTDOWNLOAD_SERVICE                                STD_ON
#else
#define STM_DIAGIF_REQUESTDOWNLOAD_SERVICE                               STD_OFF
#endif

#if (DCM_TRANSFERDATA_SERVICE == STD_ON)
#define STM_DIAGIF_TRANSFERDATA_SERVICE                                   STD_ON
#else
#define STM_DIAGIF_TRANSFERDATA_SERVICE                                  STD_OFF
#endif

#if (DCM_TRANSFERDATA_SERVICE == STD_ON)
#if (DCM_TRANSFERDATA_CUSTOMISATION == STD_ON)
#define STM_DIAGIF_TRANSFERDATA_CUSTOMISATION                             STD_ON
#else
#define STM_DIAGIF_TRANSFERDATA_CUSTOMISATION                            STD_OFF
#endif
#endif

#if (DCM_REQTRANSFEREXIT_SERVICE == STD_ON)
#define STM_DIAGIF_REQTRANSFEREXIT_SERVICE                                STD_ON
#else
#define STM_DIAGIF_REQTRANSFEREXIT_SERVICE                               STD_OFF
#endif

#if (DCM_UPLOAD_SERVICE == STD_ON)
#define STM_DIAGIF_UPLOAD_SERVICE                                         STD_ON
#else
#define STM_DIAGIF_UPLOAD_SERVICE                                        STD_OFF
#endif

#if (DCM_READ_MEMORY == STD_ON)
#define STM_DIAGIF_READ_MEMORY                                            STD_ON
#else
#define STM_DIAGIF_READ_MEMORY                                           STD_OFF
#endif

#if (DCM_WRITE_MEMORY == STD_ON)
#define STM_DIAGIF_WRITE_MEMORY                                           STD_ON
#else
#define STM_DIAGIF_WRITE_MEMORY                                          STD_OFF
#endif

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#if (STM_DIAGIF_DIAGSESSIONCONTROL_SERVICE == STD_ON)
extern Std_ReturnType Stm_DiagIfResetToDefaultSession(
  Dcm_OpStatusType Ldt_OpStatus);
#endif

#if (STM_DIAGIF_ECURESET_SERVICE == STD_ON)
extern Std_ReturnType Stm_DiagIfECUReset(
  Dcm_NegativeResponseCodeType* Lpdt_ErrorCode,
  Dcm_EcuResetType Ldt_ResetType,
  Dcm_OpStatusType Ldt_OpStatus
);
#endif

#if (STM_DIAGIF_REQUESTDOWNLOAD_SERVICE == STD_ON)
extern Std_ReturnType Stm_DiagIfRequestDownload(
  uint16* Lpu16_BlockLength,
  Dcm_NegativeResponseCodeType* Lpdt_ErrorCode,
  uint32 Lu32_MemoryAddress,
  uint32 Lu32_MemorySize,
  uint8 Lu8_DataFormatIdentifier,
  Dcm_OpStatusType Ldt_OpStatus
);
#endif

#if (STM_DIAGIF_UPLOAD_SERVICE == STD_ON)
extern Std_ReturnType Stm_DiagIfRequestUpload(
  uint32* Lpu32_BlockLength,
  Dcm_NegativeResponseCodeType* Lpdt_ErrorCode,
  uint32 Lu32_MemoryAddress,
  uint32 Lu32_MemorySize,
  uint8 Lu8_DataFormatIdentifier,
  Dcm_OpStatusType Ldt_OpStatus
);
#endif

#if (FBL_DIAG_TRANSFERDATA_CHUNK_MODE == STD_ON)
#if (STM_DIAGIF_TRANSFERDATA_SERVICE == STD_ON)
extern Std_ReturnType Stm_DiagIfWriteMemoryFF(
  const uint8* Lpu8_DataIn,
  uint16 Lu16_TotalLength,
  uint16 Lu16_CurrentLength,
  uint8 Lu8_ReceivedBlockSequenceNr
);

extern Std_ReturnType Stm_DiagIfWriteMemoryCF(
  const uint8* Lpu8_DataIn,
  uint16 Lu16_CurrentLength
);

extern Std_ReturnType Stm_DiagIfWriteMemoryGetSts(
  uint8 Lu8_ReceivedBlockSequenceNr
);
#endif
#endif /* FBL_DIAG_TRANSFERDATA_CHUNK_MODE */

#if (STM_DIAGIF_TRANSFERDATA_CUSTOMISATION == STD_ON)
extern Std_ReturnType Stm_DiagIfWriteMemoryLF(
  const uint8* Lpu8_DataIn,
  uint16 Lu16_CurrentLength
);
#endif

#if (STM_DIAGIF_WRITE_MEMORY == STD_ON)
extern void Stm_DiagIfWriteMemoryCancel(Dcm_OpStatusType Ldt_OpStatus);
#endif

#if (STM_DIAGIF_READ_MEMORY == STD_ON)
extern Std_ReturnType Stm_DiagIfReadMemory(
  uint8* Lpu8_DataOut,
  uint32 Lu32_MemoryAddress,
  uint32 Lu32_MemorySize,
  uint8 Lu8_MemoryIdentifier,
  Dcm_OpStatusType Ldt_OpStatus
);
#endif

#if (STM_DIAGIF_REQTRANSFEREXIT_SERVICE == STD_ON)
extern Std_ReturnType Stm_DiagIfRequestTransferExit(
  Dcm_NegativeResponseCodeType* Lpdt_ErrorCode
);
#endif

#if (STM_DIAGIF_ROUTINECONTROL_SERVICE == STD_ON)
extern Std_ReturnType Stm_DiagIfRCStartEraseMemory(
  uint8 Lu8_BlockId,
  Dcm_NegativeResponseCodeType * Lpdt_ErrorCode,
  Dcm_OpStatusType Ldt_OpStatus
);
 
extern Std_ReturnType Stm_DiagIfRCResultEraseMemory(
  uint8* Lpu8_DataOut,
  uint16* Lpu16_CurrentLength,
  Dcm_NegativeResponseCodeType * Lpdt_ErrorCode,
  Dcm_OpStatusType Ldt_OpStatus
);
#endif

extern void Stm_DiagIfTxConfirmation(
  Dcm_IdContextType Ldt_IdContext
);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* STM_DIAGIF_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
