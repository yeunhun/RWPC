/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Stm_Ddp.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Stm_Ddp.c                                     **
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

#ifndef STM_DDP_H
#define STM_DDP_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Fbl_Cfg.h"

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
/**
 * Enumeration contains the possible status for data processing
 */
typedef enum
{
  STM_DDP_STATUS_IDLE,
  STM_DDP_STATUS_INIT,
  STM_DDP_STATUS_DDP_INPROGRESS,
  STM_DDP_STATUS_OUTPUT_BFRFULL,
  STM_DDP_STATUS_DDP_FINISHED,
  STM_DDP_STATUS_DDP_ERROR
} Stm_Ddp_Status_Etyp;

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#if (FBL_DIAG_TRANSFERDATA_CHUNK_MODE == STD_ON)
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void Stm_DdpInit(uint8 Lu8_DataFormatIdentifier,
  uint32 Lu32_TotalInputDataLength);

extern void Stm_DdpIndicateBlockStart(const uint8* Lpu8_DataInPtr,
  uint8 Lu8_BlkSeqNo);
                                      
extern void Stm_DdpIndicateDataFormatId(uint8 Lu8_DataFormatId);

extern void Stm_DdpUpdateInDataLength(uint16 Lu16_Length);

extern void Stm_DdpSetOutDataBfr(uint8* Lpu8_DataOutPtr,
  uint16 Lu16_MaxLength);

extern void Stm_DdpMainFunction(void);

extern uint16 Stm_DdpGetInBfrProcessedSize(void);

extern uint16 Stm_DdpGetOutBfrProcessedSize(void);

extern Stm_Ddp_Status_Etyp Stm_DdpGetJobStatus(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"
#else
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void Stm_DdpMainFunction(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"
#endif /* FBL_DIAG_TRANSFERDATA_CHUNK_MODE */

#endif /* STM_DDP_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
