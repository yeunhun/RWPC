/*============================================================================*/
/*                        CARNES SOFTWARE GROUP                               */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* %name:              OsekNm_Version.h %
* %instance:          xenon_3 %
* %version:           1.1 %
* %created_by:        ca027 %

* %date_created:      Wednesday, November 21, 2012 8:17:14 AM %
*=============================================================================*/
/* DESCRIPTION : header file for AUTOSAR CAN NM                               */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/* Provision of header for OsekNm_Version.c                                   */
/*                                                                            */
/*============================================================================*/
/* COPYRIGHT (C) CARNES 2006                                                  */
/* AUTOMOTIVE ELECTRONICS                                                     */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/* 1.0.0     | 16/May/2011 | Initial Creation              | Kyung Tae Kim    */
/* 1.4.0     | 28/Dec/2018 | #15280                        | JeongSu Lim      */
/* 1.5.0     | 13/May/2020 | #21188                        | JeongSu Lim      */
/*============================================================================*/


#ifndef OSEKNM_VERSION_H
#define OSEKNM_VERSION_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "OsekNm.h"        /* OsekNm Header File */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define OSEKNM_VERSION_AR_MAJOR_VERSION      4
#define OSEKNM_VERSION_AR_MINOR_VERSION      0
#define OSEKNM_VERSION_AR_PATCH_VERSION      3

/* Software Version Information */
#define OSEKNM_VERSION_SW_MAJOR_VERSION      1
#define OSEKNM_VERSION_SW_MINOR_VERSION      6

/* Included files AUTOSAR specification version information */
#define OSEKNM_DET_AR_MAJOR_VERSION          2
#define OSEKNM_DET_AR_MINOR_VERSION          1

#define OSEKNM_DEM_AR_MAJOR_VERSION          2
#define OSEKNM_DEM_AR_MINOR_VERSION          1

#define OSEKNM_SCHM_AR_MAJOR_VERSION         1
#define OSEKNM_SCHM_AR_MINOR_VERSION         1

#define OSEKNM_OSEKNM_AR_MAJOR_VERSION       2
#define OSEKNM_OSEKNM_AR_MINOR_VERSION       1

#define OSEKNM_CANIF_AR_MAJOR_VERSION        4
#define OSEKNM_CANIF_AR_MINOR_VERSION        0

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /*OSEKNM_VERSION_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
