/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Bsm.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Bsm.c                                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef BSM_H
#define BSM_H
/*******************************************************************************
**                           Include Section                                  **
*******************************************************************************/
#include "Btl.h"

/*******************************************************************************
**               API/Function Extern Declaration                              **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void Bsm_MainFunction(void);

extern void Bsm_IndicateSessionChange(uint8 Lu8_SessionType);

extern void Bsm_PreAppCheckInit(void);

extern void Bsm_CheckforApplication(void);

extern void Bsm_PostAppCheckInit(void);

extern void Bsm_PreResetDeInit(void);

extern void Bsm_IndicateReset(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* BSM_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
