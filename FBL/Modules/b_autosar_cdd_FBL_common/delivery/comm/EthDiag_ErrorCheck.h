/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: EthDiag_ErrorCheck.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides internal functions required in EthDiag related to    **
**              error checking                                                **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef ETHDIAG_ERROR_CHECK_H
#define ETHDIAG_ERROR_CHECK_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "EthDiag_Types.h"

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

extern boolean EthDiag_Gbl_InitFlag;

#define BTL_STOP_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern Std_ReturnType EthDiag_ErrCheckRxStartOfReception(
  TcpIpw_SocketIdType Ldt_SocketId,
  const uint8* Lpu8_DataPtr,
  uint16 Lu16_DataLength,
  uint16  Lu16_TotalDataLength,
  const uint16*  Lpu16_BufferSizePtr
);

extern Std_ReturnType EthDiag_ErrorCheckCopyRxData(
  TcpIpw_SocketIdType Ldt_SocketId,
  const uint8* Lpu8_DataPtr,
  uint16 Lu16_DataLength,
  const uint16* Lpu16_BufferSizePtr
);

extern Std_ReturnType EthDiag_ErrorCheckTcpRxIndication(
  TcpIpw_SocketIdType  Ldt_SocketId,
  Std_ReturnType Ldt_Result
);

extern Std_ReturnType EthDiag_ErrorCheckTcpIpEvent(
  TcpIpw_SocketIdType Ldt_SocketId,
  TcpIpw_Event_Etyp Len_Event
);

extern Std_ReturnType EthDiag_ErrorTcpIpwTxConfirmation(
  TcpIpw_SocketIdType Ldt_SocketId,
  Std_ReturnType Ldt_Result
);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* ETHDIAG_ERROR_CHECK_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
