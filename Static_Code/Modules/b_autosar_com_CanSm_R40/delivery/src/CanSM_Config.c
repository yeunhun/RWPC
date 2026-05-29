/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.								                      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_Config.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : CanTSM Library Relase.                                        **
**                                                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.12.0    30-May-2019   SM Kwon        #17202                              **
** 1.11.0    23-Oct-2018   Lim Jong Sun   #14496                              **
** 1.10.3    06-Feb-2018   Lim Jong Sun   #11551                              **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7048                               **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM_Cfg.h"
#include "CanSM_InternalTypes.h"
/*******************************************************************************
**            Variable for Library                                            **
*******************************************************************************/
#if (STD_ON == CANSM_CANTRCV_SUPPORT)
#define CANSM_START_SEC_CONST_8
#include "MemMap.h"
CONST(uint8, CANSM_CONST) CanSm_GucLastTrcvHandle = CANSM_LAST_TRANSCEIVER_HANDLE;
#define CANSM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/