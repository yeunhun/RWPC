/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_Types.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : Provision of IoHwAb global definitions                        **
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
** 1.9.0     04-Jun-2020   Yangjin        #23413                              **
** 1.8.1     08-May-2020   Yangjin        #23096                              **
** 1.0.3     11-Sep-2015   Jongyoung      Polyspace result Adaption           **
**                                        Add IOHWAB_LOWPOWER_PREVENT/ALLOW   **
** 1.0.2     27-Sep-2014   Jongyoung      Polyspace result Adaption           **
** 1.0.1     19-Aug-2014   Sinil          1. Add null types                   **
** 1.0.0     07-Mar-2014   Sinil          Initial version                     **
*******************************************************************************/

#ifndef IOHWAB_TYPES_H
#define IOHWAB_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_IoHwAb_Type.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "whether this macro is used depends on the configurations." */
#define IOHWAB_ZERO                                0x00U
#define IOHWAB_ONE                                 0x01U
#define IOHWAB_TWO                                 0x02U
#define IOHWAB_THREE                               0x03U
#define IOHWAB_SEVEN                               0x07U

#define IOHWAB_POL_LOW                             ((uint8)0x00)
#define IOHWAB_POL_HIGH                            ((uint8)0x01)

#define IOHWAB_IS_SW_OFF                           ((uint8)0x00)
#define IOHWAB_IS_SW_ON                            ((uint8)0x01)

#define IOHWAB_NULL                                0U
#define IOHWAB_NULL_PTR                            ((void*)0)

#define IOHWAB_LOWPOWER_PREVENT                    0U
#define IOHWAB_LOWPOWER_ALLOW                      1U

#define IOHWAB_NORMAL_MAX                          ((uint8)0xFF)
/* polyspace-end MISRA-C3:2.5 [Justified:Low] "whether this macro is used depends on the configurations." */
/*******************************************************************************
**                       Global Data Types                                    **
*******************************************************************************/

typedef enum
{
  IOHWAB_ACQ_NO_ACTION = 0,
  IOHWAB_ACQ_DIGITAL,
  IOHWAB_ACQ_ANALOG,
  IOHWAB_ACQ_DIGITAL_OUT,
  IOHWAB_ACQ_ANALOG_MUX,
  IOHWAB_ACQ_ANALOG_END
}IoHwAb_AcqState;

#endif /* IOHWAB_TYPES_H */
/* polyspace-end MISRA-C3:2.4 [Justified:Low] "whether this type is used depends on the configurations." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
