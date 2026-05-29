/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Bsm_Cfg.h                                                     **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Project specific configuration for Bsm.c                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef BSM_CFG_H
#define BSM_CFG_H

/*******************************************************************************
**                           Include Section                                  **
*******************************************************************************/
#include "Btl.h"
/*******************************************************************************
**                           Macro Definition                                 **
*******************************************************************************/
/* SYST timer resolution is 1mSec */
/* Communication stack takes ~200mSec to receive first diag request */
#define BSM_TIMEOUT_PROG_TIME                                             25000U

/* Session request from DCM/tester to remain in bootloader for new download */
#define BSM_PROG_SESSION_REQUEST                                           0x02U

/* TCP connection close wait time when indicate reset is called */
#define BSM_TCP_CLOSE_WAIT_TIME                                              50U

/*******************************************************************************
**               API/Function Extern Declaration                              **
*******************************************************************************/
#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

extern void Bsm_CommInit(void);

extern void Bsm_CommDeInit(void);

#if(FBL_COMM_ENET_ENABLE == STD_ON)
extern boolean Bsm_IsComChannelReady(void);

void Bsm_PostCommInit(void);
#endif /* (FBL_COMM_ENET_ENABLE == STD_ON) */

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#endif /* BSM_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
