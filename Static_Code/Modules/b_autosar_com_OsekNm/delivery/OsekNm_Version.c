/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  INC-MODULE: OsekNm_Version.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OsekNm                                                **
**                                                                            **
**  PURPOSE   : Provision of version for OsekNm module                        **
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
/* 1.5.0     | 13/May/2020 | #21188                        | JeongSu Lim      */
/*============================================================================*/



/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "OsekNm.h"               /* OsekNm Header File */
#include "OsekNm_Version.h"       /* OsekNm Version Information Header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define OSEKNM_VERSION_C_AR_MAJOR_VERSION  4
#define OSEKNM_VERSION_C_AR_MINOR_VERSION  0
#define OSEKNM_VERSION_C_AR_PATCH_VERSION  3

/* Software Version Information */
#define OSEKNM_VERSION_C_SW_MAJOR_VERSION  1
#define OSEKNM_VERSION_C_SW_MINOR_VERSION  6

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* OsekNm Version Check */
#if (OSEKNM_VERSION_AR_MAJOR_VERSION != OSEKNM_VERSION_C_AR_MAJOR_VERSION)
  #error "OsekNm_Version.c : Mismatch in Specification Major Version"
#endif

#if (OSEKNM_VERSION_AR_MINOR_VERSION != OSEKNM_VERSION_C_AR_MINOR_VERSION)
  #error "OsekNm_Version.c : Mismatch in Specification Minor Version"
#endif

#if (OSEKNM_VERSION_AR_PATCH_VERSION != OSEKNM_VERSION_C_AR_PATCH_VERSION)
  #error "OsekNm_Version.c : Mismatch in Specification Patch Version"
#endif

#if (OSEKNM_VERSION_SW_MAJOR_VERSION != OSEKNM_VERSION_C_SW_MAJOR_VERSION)
  #error "OsekNm_Version.c : Mismatch in Software Major Version"
#endif

#if (OSEKNM_VERSION_SW_MINOR_VERSION != OSEKNM_VERSION_C_SW_MINOR_VERSION)
  #error "OsekNm_Version.c : Mismatch in Software Minor Version"
#endif



/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
