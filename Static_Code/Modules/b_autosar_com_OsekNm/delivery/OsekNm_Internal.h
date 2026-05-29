/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  INC-MODULE: OsekNm_Internal.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OsekNm                                                **
**                                                                            **
**  PURPOSE   : Declarations for OsekNm internal functions                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/* 1.0.0     | 16/May/2011 | Initial Creation              | Kyung Tae Kim    */
/* 1.4.0     | 28/Dec/2018 | #15280                        | JeongSu Lim      */
/* 1.4.2     | 08/Mar/2019 | #16398                        | JeongSu Lim      */
/* 1.5.0     | 13/May/2020 | #21188                        | JeongSu Lim      */
/*============================================================================*/
#ifndef OSEKNM_INTERNAL_H
#define OSEKNM_INTERNAL_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "OsekNm.h"          /* API Header file */
#include "OsekNm_Ram.h"      /* Provision of OsekNm extern variables */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define OSEKNM_INTERNAL_AR_MAJOR_VERSION  4
#define OSEKNM_INTERNAL_AR_MINOR_VERSION  0
#define OSEKNM_INTERNAL_AR_PATCH_VERSION  3

/* OSEKNM software version information */
#define OSEKNM_INTERNAL_SW_MAJOR_VERSION  1
#define OSEKNM_INTERNAL_SW_MINOR_VERSION  6

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, OSEKNM_CODE) OsekNm_ModeProcessing
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) LddLocalChannelId);

#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"                          

#endif /* OSEKNM_INTERNAL_H */

/******************************************************************************
**                          END OF FILE                                      **
******************************************************************************/
 
