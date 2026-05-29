/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Stm_Cfg.h                                                     **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Configuration file for Stm.c                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef STM_CFG_H
#define STM_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_Cfg.h"


/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#if (FBL_COMM_CAN_ENABLE == STD_ON)
#define STM_DCM_DATA_BUFFER_SIZE             (FBL_CAN_RECEIVED_DATA_BUFFER_SIZE)
#define STM_PROG_DATA_BUFFER_SIZE             (FBL_CAN_PROGRAM_DATA_BUFFER_SIZE)
#elif (FBL_COMM_ENET_ENABLE == STD_ON)
#define STM_DCM_DATA_BUFFER_SIZE             (FBL_ETH_RECEIVED_DATA_BUFFER_SIZE)
#define STM_PROG_DATA_BUFFER_SIZE             (FBL_ETH_PROGRAM_DATA_BUFFER_SIZE)
#endif

#define STM_MAXNUMBER_OF_BLOCKLENGTH_IN_UPLOAD                            (255U)

#endif /* STM_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
