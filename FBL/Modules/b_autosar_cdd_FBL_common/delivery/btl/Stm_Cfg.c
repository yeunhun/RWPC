/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Stm_Cfg.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file implements Boot State Manager functionality         **
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

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Stm.h"
#include "Stm_Cfg.h"
#include "Fbl_Cfg.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#if (FBL_DIAG_TRANSFERDATA_CHUNK_MODE == STD_ON)
#define BTL_START_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"

static uint8 Stm_Gau8_Dcm_Buffer[STM_DCM_DATA_BUFFER_SIZE];

static uint8 Stm_Gau8_Prog_Buffer[STM_PROG_DATA_BUFFER_SIZE];

#define BTL_STOP_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"

#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

Stm_BufferInfo_Styp Stm_Gst_InBuffer =
{
  Stm_Gau8_Dcm_Buffer,
  STM_DCM_DATA_BUFFER_SIZE,
  STD_CLEAR,
  STD_CLEAR,
  STD_CLEAR,
  STM_DATA_BUFFER_RELEASED
};

Stm_BufferInfo_Styp Stm_Gst_ProgBuffer =
{
  Stm_Gau8_Prog_Buffer,
  STM_PROG_DATA_BUFFER_SIZE,
  STD_CLEAR,
  STD_CLEAR,
  STD_CLEAR,
  STM_DATA_BUFFER_RELEASED
};

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"
#endif /* FBL_DIAG_TRANSFERDATA_CHUNK_MODE */
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
