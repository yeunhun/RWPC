/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_AppIf.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Application interface in FBL                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.5.1.0   06-Jun-2022   JSCHOI       Redmine #36032                        **
** 1.0.3     05-Feb-2021   JH Lim       Redmine #28215                        **
** 1.0.2     29-Jul-2020   JYS          Redmine #24231                        **
** 1.0.1     02-Jul-2020   EK.KIM       #23953, #23954                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef FBL_APPIF_H
#define FBL_APPIF_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Platform_Types.h"

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
typedef enum
{
  FBL_SW_NO_RTSW,
  FBL_SW_ENTRY_POINT_1,
  FBL_SW_ENTRY_POINT_2
} Fbl_SwEntryPointType;

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_USER_CODE
#include "Btl_MemMap.h"

extern uint32 Fbl_BeforeRoutineCtrlEraseInit(void);

extern uint32 Fbl_AfterRoutineCtrlChkInit(void);

extern uint32 Fbl_GetMainSwEntryPointAddress(void);

extern Fbl_SwEntryPointType Fbl_SelectEntryPoint(void);

extern uint32 Fbl_WritePartitionFlag(uint8 Block_Id);

extern void Fbl_GetActivePartitionBlkAddress(uint32 *headerAddr, uint32 *trailerAddr);

extern uint32 Fbl_CheckBlockId(uint8 Block_Id);

extern uint32 Fbl_SvcCheckVersion(uint32 currentVersion, uint32 newVer);

extern void Fbl_BeforeFblSpecificInit(void);

extern void Fbl_BeforeCommExtInit(void);

extern void Fbl_AfterCommExtInit(void);

extern void Fbl_ExtDeinit(void);

extern void Fbl_EthPortInit(void);

extern boolean Fbl_GetSwitchInit (void);

#define BTL_STOP_SEC_USER_CODE
#include "Btl_MemMap.h"

#define BTL_START_SEC_USER_RAM_CODE
#include "Btl_MemMap.h"

extern void Fbl_ExtPolling(void);

#define BTL_STOP_SEC_USER_RAM_CODE
#include "Btl_MemMap.h"

#endif /* FBL_APPIF_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
