/*******************************************************************************
**                                                                            **
**  (C) 2020 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Std_Types.h                                                   **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides macro definitions for general state conditions       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision    Date          By           Description                         **
********************************************************************************
** 1.2.0       10-May-2021   JHLim        #28951                              **
** 1.1.0.0     23-Feb-2021   JHLim        Redmine #23964                      **
** 1.0.0       10-April-2020 JaeHyun      Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:2.3,2.5,21.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef STD_TYPES_H
#define STD_TYPES_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Platform_Types.h"

/*******************************************************************************
**                           Macro Definition                                 **
*******************************************************************************/
#define E_OK                                                               0x00U
#define E_NOT_OK                                                           0x01U
#define E_BUSY                                                             0x02U
#define E_PENDING                                                          0x03U
#define E_HW_FAILURE                                                       0x04U
#define E_SW_FAILURE                                                       0x05U
#define E_ALIGN_ERROR                                                      0x06U
#define E_FORBIDDEN                                                        0x07U
#define E_OUT_OF_RANGE                                                     0x08U
#define E_INVALID_PARAMETER                                                0x0AU
#define E_BAD_CRC                                                          0x0BU
#define E_INCOMPATIBLE                                                     0x0CU
#define E_EEPROM_ERROR                                                     0x0DU
#define E_NOT_ENOUGH_MEM                                                   0x0EU
#define E_SEC_ACCESS_DENIED                                                0x0FU
#define E_NO_RECEIVED_DATA                                                 0x09U

#define NULL_PTR                                                     ((void *)0)
#define NULL_FUNC                                                ((void (*)())0)
#if !defined(NULL)
  #define NULL                                                      ((void *) 0)
#endif

/* Physical state 5V or 3.3V */
#define STD_HIGH                                                           0x01U
/* Physical state 0V */
#define STD_LOW                                                            0x00U
/* Logical state active */
#define STD_ACTIVE                                                         0x01U
/* Logical state idle */
#define STD_IDLE                                                           0x00U

#ifndef STD_ON
#define STD_ON                                                             0x01U
#endif

#ifndef STD_OFF
#define STD_OFF                                                            0x00U
#endif

#ifndef TRUE
#define TRUE (boolean)1
#endif

#ifndef FALSE
#define FALSE (boolean)0
#endif

#ifndef STD_SET
#define STD_SET 1U
#endif

#ifndef STD_CLEAR
#define STD_CLEAR 0U
#endif

#ifndef ZERO_INDEX
#define ZERO_INDEX 0U
#endif

/*******************************************************************************
**                              Type Definition                               **
*******************************************************************************/
/*
 Describes the standard Type Definitions used in the project
*/

/* Standard return type */

typedef uint8  Std_ReturnType;
/*
  Structure for the Version of the module.This is requested by calling 
  <Module name>_GetVersionInfo()
*/
typedef struct
{
  uint16  vendorID;
  uint16  moduleID;
  uint8   sw_major_version;
  uint8   sw_minor_version;
  uint8   sw_patch_version;
} Std_VersionInfoType;

#endif /* STD_TYPES_H */


/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:2.3,2.5,21.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
