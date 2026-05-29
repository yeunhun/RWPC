/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dm_Swc.h                                                      **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Dm_Swc.c                                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.21.0    27-Sep-2021   JYS          Redmine #29449                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef DM_SWC_H
#define DM_SWC_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Dcm.h"
#include "Dcm_Types.h"
#include "Fbl_Cfg.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

extern void Dm_Swc_SetProgConditions(const Fbl_SharedCommonRAM* Lpst_ProgConditions);

extern Std_ReturnType Dm_Swc_GetProgConditions(Fbl_SharedCommonRAM* Lpst_ProgConditions);

extern Std_ReturnType Dm_Swc_DiagnosticSessionControl(Dcm_SesCtrlType Ldt_Sessiontype,
  Dcm_OpStatusType Ldt_OpStatus);
  
extern Std_ReturnType Dm_Swc_SecurityAccess(
  uint8 Lu8_SecLvl,
  const uint8* Lpu8_ReqData,
  uint8* Lpu8_ResData,
  uint32* Lpu32_SeedLength,
  Dcm_NegativeResponseCodeType* Lpdt_ErrorCode,
  Dcm_OpStatusType Ldt_OpStatus);

extern Std_ReturnType Dm_Swc_ProcessRequestDownload(Dcm_OpStatusType Ldt_OpStatus,
  uint8   Lu8_DataFormatIdentifier,
  uint32  Lu32_MemoryAddress,
  uint32*  Lpu32_MemoryLength,
  uint16* Lpu16_BlockLength,
  Dcm_NegativeResponseCodeType* Lpdt_ErrorCode);

#if (DCM_UPLOAD_SERVICE == STD_ON)
extern Std_ReturnType Dm_Swc_ProcessRequestUpload(Dcm_OpStatusType Ldt_OpStatus,
  uint8   Lu8_DataFormatIdentifier,
  uint32  Lu32_MemoryAddress,
  uint32  Lu32_MemorySize,
  uint32* Lpu32_BlockLength,
  Dcm_NegativeResponseCodeType* Lpdt_ErrorCode);
#endif

#if (FBL_DIAG_TRANSFERDATA_CHUNK_MODE == STD_ON)
extern Dcm_ReturnWriteMemoryType Dm_Swc_WriteMemory_FF(uint8 Lu8_BlockSeqCounter,
  uint16 Lu16_TotalMemorySize,
  uint16 Lu16_CurrentMemorySize,
  const uint8* Lpu8_WriteData);
  
extern Dcm_ReturnWriteMemoryType Dm_Swc_WriteMemory_CF(uint16 Lu16_MemorySize,
  const uint8* Lpu8_WriteData);
#else
extern Dcm_ReturnWriteMemoryType Dm_Swc_WriteMemory(uint8 Lu8_BlockSeqCounter,
  uint16 Lu16_TotalMemorySize,
  uint16 Lu16_CurrentMemorySize,
  const uint8* Lpu8_WriteData);
#endif /* FBL_DIAG_TRANSFERDATA_CHUNK_MODE */

#if (DCM_TRANSFERDATA_SERVICE == STD_ON)
extern Std_ReturnType Dm_Swc_WriteMemoryGetStatus(uint8 Lu8_ReceivedBlockSequenceNr);
#endif

extern Std_ReturnType Dm_Swc_ProcessRequestTransferExit(
  Dcm_NegativeResponseCodeType* Lpdt_ErrorCode,
  Dcm_OpStatusType Ldt_OpStatus);
  
extern Std_ReturnType Dm_Swc_RoutineCtrl_Start(uint16  Lu16_RoutineId,
  const uint8*  Lpu8_ReqData,
  uint8*  Lpu8_ResData,
  uint16* Lpu16_RoutineStatusRecordSize,
  Dcm_NegativeResponseCodeType *Lpdt_ErrorCode,
  uint32 Lu32_OptionRecordSize,
  Dcm_OpStatusType Ldt_OpStatus);

#if (DCM_READ_MEMORY == STD_ON)
extern Dcm_ReturnReadMemoryType Dm_Swc_ReadMemory(Dcm_OpStatusType Ldt_OpStatus,
  uint8  Lu8_MemoryIdentifier,
  uint32 Lu32_MemoryAddress,
  uint32 Lu32_MemorySize,
  uint8* Lpu8_MemoryData);
#endif

extern Std_ReturnType Dm_Swc_ReadDataByID(Dcm_OpStatusType Ldt_OpStatus,
  uint16 Lu16_DidNumber,
  uint8  Lu8_DidDataSize,
  uint8* Lpu8_ReadBuffer);

#if (DCM_WRITEDATABYID_SERVICE == STD_ON)
extern Std_ReturnType Dm_Swc_WriteDataByID(Dcm_OpStatusType Ldt_OpStatus,
  uint16 Lu16_DidNumber,
  uint8  Lu8_DidDataSize,
  const  uint8* Lpu8_WriteBuffer,
  const  Dcm_NegativeResponseCodeType* Lpdt_ErrorCode);
#endif

extern Std_ReturnType Dm_Swc_EcuReset(Dcm_NegativeResponseCodeType* Lpdt_ErrorCode,
  Dcm_EcuResetType Ldt_ResetType,
  Dcm_OpStatusType Ldt_OpStatus);

#if (DCM_WRITE_MEMORY == STD_ON)
extern void Dm_Swc_WriteMemoryCancel(Dcm_OpStatusType Ldt_OpStatus);
#endif

extern Std_ReturnType Dm_Swc_CheckUdsCommSts(void);

extern Std_ReturnType Dm_Swc_GetApplUpdateSts(void);

extern void Dm_Swc_SetApplUpdateSts(Std_ReturnType Success);

extern void Dm_Swc_TxConfirmation(Dcm_IdContextType Ldt_IdContext);

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#endif /* DM_SWC_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
