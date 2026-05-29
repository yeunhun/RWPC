/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Det.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Development Error Tracer                              **
**                                                                            **
**  PURPOSE   : This file contains declaration of functions defined in        **
**              Development Error Tracer module which are used by             **
**              the other modules.                                            **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.23.0    27-Dec-2021   JH Lim       R40-Redmine #31776                    **
** 1.14.0.0  07-Apr-2021   JYS          Redmine #29231                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef DET_H
#define DET_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define DET_ZERO                                                   ((uint8)0x00)

#define DET_INITIALIZED                                          ((boolean)0x01)

/* The Ram Buffer Storage Size */
#define DET_RAM_BUFFER_SIZE                                          ((uint8)16)

/*******************************************************************************
**                          Module ID Macro Definition                        **
*******************************************************************************/
/* CanTp module id */
#define CANTP_MODULE_ID                                           ((uint16)0x10)

/* DCM module id */
#define DCM_MODULE_ID                                             ((uint16)0x20)

/* Security Access module id */
#define SA_MODULE_ID                                              ((uint16)0x30)

/* SecureFlash module id */
#define SF_MODULE_ID                                              ((uint16)0x40)

/* Version Check module id */
#define SVC_MODULE_ID                                             ((uint16)0x50)

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
/* Structure to store the parameters of DET Report Error function */
typedef struct STag_Det_ErrorType
{
  /* To store the ModuleId of the reporting module */
  uint16 usModuleId;
  /* To store the index based InstanceId of the reporting module */
  uint8 ucInstanceId;
  /* To store the ApiId of the reporting function */
  uint8 ucApiId;
  /* To store the ErrorId of the reporting error */
  uint8 ucErrorId;
} Det_ErrorType;

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/* This Det_Init declaration for initialization function */
extern void Det_Init(void);

/* This function is used to log the reported errors and count the reported
  errors */
extern Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId,
  uint8 ApiId, uint8 ErrorId);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* DET_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
