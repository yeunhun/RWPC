/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_DigDir.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : Provision of external declaration of APIs                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.15.0.2  09-Sep-2021   Yangjin        #31974                              **
** 1.8.1     08-May-2020   Yangjin        #23096                              **
** 1.0.2     05-Jun-2015   Jongyoung      1.Misra-C coding Rule adaption      **
**                                        Duplicated Extern declaration (8.8) **
** 1.0.1     27-Sep-2014   Jongyoung      Polyspace result Adaption           **
** 1.0.0     07-Mar-2014   Sinil          Initial version                     **
*******************************************************************************/

#ifndef IOHWAB_DIGDIR_H
#define IOHWAB_DIGDIR_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (IOHWAB_USE_DIG_DIR == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_DigDirInit(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#ifdef IOHWAB_MCAL_TI_TDA4X
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_DioSetPinDirection(Dio_ChannelType ChIdx, Port_PinDirectionType Dir);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* IOHWAB_MCAL_TI_TDA4X */
#endif /* (IOHWAB_USE_DIG_DIR == STD_ON) */

#endif /* IOHWAB_DIGDIR_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
