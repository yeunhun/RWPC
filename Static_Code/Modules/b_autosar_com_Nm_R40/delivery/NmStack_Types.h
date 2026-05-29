/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NmStack_Types.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   :Provision of Nm Stack types                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Revision History                                     **
********************************************************************************
** Revision      Date         By         Description                          **
********************************************************************************
** 2.2.0     28-Dec-2018   JeongSu Lim   #13630, #15277, #15276, #15275,      **
**                                       #15274                               **
** 1.0.2     24-Aug-2015   Kt Kim        #3000                                **
** 1.0.0     26-Nov-2012   Kt Kim        Initial Version                      **
*******************************************************************************/

#ifndef NMSTACK_TYPES_H
#define NMSTACK_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define NMSTACK_TYPES_AR_MAJOR_VERSION          (4)
#define NMSTACK_TYPES_AR_MINOR_VERSION          (0)
#define NMSTACK_TYPES_AR_PATCH_VERSION          (3)

#define NMSTACK_TYPES_SW_MAJOR_VERSION          (2)
#define NMSTACK_TYPES_SW_MINOR_VERSION          (3)

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

typedef enum
{
  NM_MODE_BUS_SLEEP,
  NM_MODE_PREPARE_BUS_SLEEP,
  NM_MODE_SYNCHRONIZE,
  NM_MODE_NETWORK
} Nm_ModeType;

typedef enum
{
  NM_STATE_UNINIT,
  NM_STATE_BUS_SLEEP,
  NM_STATE_PREPARE_BUS_SLEEP,
  NM_STATE_READY_SLEEP,
  NM_STATE_NORMAL_OPERATION,
  NM_STATE_REPEAT_MESSAGE,
  NM_STATE_SYNCHRONIZE
} Nm_StateType;

typedef enum
{
  NM_BUSNM_CANNM,
  NM_BUSNM_FRNM,
  NM_BUSNM_LINNM,
  NM_BUSNM_UDPNM,
  NM_BUSNM_GENERICNM,
  NM_BUSNM_UNDEF,
  NM_BUSNM_J1939M,
} Nm_BusNmType;

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
#endif  /* NMSTACK_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
