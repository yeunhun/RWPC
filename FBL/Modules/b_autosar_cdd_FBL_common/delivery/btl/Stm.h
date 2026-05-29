/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Stm.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Stm.c                                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.21.0    27-Sep-2021   JYS          Redmine #29449, #29277                **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef STM_H
#define STM_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_Cfg.h"
#include "Btl.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define STM_DATA_BUFFER_RELEASED                                         (0x00U)
#define STM_DATA_BUFFER_BUSY                                             (0x01U)

#define STM_DATAFORMATID_COMPRESS_MASK                                   (0xF0U)
#define STM_DATAFORMATID_ENCRYPT_MASK                                    (0x0FU)

#define STM_DATAFORMATID_UNCOMPRESSED                                    (0x00U)
#define STM_DATAFORMATID_COMPRESSED_LZMA                                 (0xA0U)

#define STM_DATAFORMATID_PLAIN_DATA                                      (0x00U)
#define STM_DATAFORMATID_ENCRYPTED_AES128_CBC                            (0x0AU)

#define STM_IS_UNCOMPRESSED(dataFormatId) \
  ((dataFormatId & STM_DATAFORMATID_COMPRESS_MASK) == STM_DATAFORMATID_UNCOMPRESSED)
#define STM_IS_UNENCRYPTED(dataFormatId) \
  ((dataFormatId & STM_DATAFORMATID_ENCRYPT_MASK) == STM_DATAFORMATID_PLAIN_DATA)

#define STM_IS_COMPRESSED_LZMA(dataFormatId) \
  ((dataFormatId & STM_DATAFORMATID_COMPRESS_MASK) == STM_DATAFORMATID_COMPRESSED_LZMA)
#define STM_IS_ENCRYPTED_AES128_CBC(dataFormatId) \
  ((dataFormatId & STM_DATAFORMATID_ENCRYPT_MASK) == STM_DATAFORMATID_ENCRYPTED_AES128_CBC)

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
#if (FBL_DIAG_TRANSFERDATA_CHUNK_MODE == STD_ON)
typedef struct
{
  uint8*   pu8_Data;                  /* Pointer to data buffer */
  uint16   u16_MaxSize;               /* Maximum size of the data buffer */
  uint16   u16_nrOfBytesAllocated;    /* Number of bytes allocated */
  uint16   u16_nrOfBytesExpected;     /* Number of bytes Expected */
  uint16   u16_nrOfBytesProcessed;    /* Number of bytes processed */
  uint8    u8_BufferStatus;           /* Lock status of buffer */
} Stm_BufferInfo_Styp;

/*******************************************************************************
**                            Type Definition                                 **
*******************************************************************************/
#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

extern Stm_BufferInfo_Styp Stm_Gst_InBuffer;

extern Stm_BufferInfo_Styp Stm_Gst_ProgBuffer;

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void Stm_Init(void);

extern void Stm_MainFunction(void);

extern void Stm_IndicateRequestDownload(uint32 Lu32_MemorySize,
  uint8 Lu8_DataFormatIdentifier);

extern Std_JobReturnType Stm_GetWriteMemoryStatus(void);

extern void Stm_IndicateStartDataTransfer(uint8 Lu8_ReceivedBlockSequenceNr);

extern Std_JobReturnType Stm_GetWriteBlockSatus(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"
#else
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void Stm_MainFunction(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"
#endif /* FBL_DIAG_TRANSFERDATA_CHUNK_MODE */

#endif /* STM_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
