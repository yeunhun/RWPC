/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComStack_Cfg.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR BSW R4.0.3 Modules                                    **
**                                                                            **
**  PURPOSE   : Provision for Communication Stack Configuration file          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.2.0     17-Apr-2018   Chan Kim    #12356                                 **
** 1.0.0     25-Jul-2013   Autron      Initial version                        **
*******************************************************************************/

/******************************************************************************/

#ifndef COMSTACK_CFG_H
#define COMSTACK_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/*
 * AUTOSAR specification version information
 */
#define COMSTACK_CFG_AR_RELEASE_MAJOR_VERSION      4
#define COMSTACK_CFG_AR_RELEASE_MINOR_VERSION      0
#define COMSTACK_CFG_AR_RELEASE_REVISION_VERSION   3

/*
 * File version information
 */
#define COMSTACK_CFG_SW_MAJOR_VERSION        1
#define COMSTACK_CFG_SW_MINOR_VERSION        2

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/


/*******************************************************************************
**                      Global Data Types (ECU dependent)                     **
*******************************************************************************/
/* Chapter 8.1.1 */
typedef uint16        PduIdType;     /* Type of PDU ID.
                                       Allowed ranges: uint8 .. uint16 */

/* Chapter 8.1.2 */
typedef uint16        PduLengthType; /* Type of PDU Length.
                                       Allowed ranges: uint8 .. uint32 */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* COMSTACK_CFG_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
