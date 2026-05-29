/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Wdg_76_Acw_Config.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTRON CUSTOM WDG                                     **
**                                                                            **
**  PURPOSE   : Autron Custom Watchdog const variable definitions for         **
**              making a library                                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.8.2.0   18-Oct-2021   YH.Han       Redmine #32698                        **
** 1.1.0     17-Jul-2017   Kuksun       Redmine #8886                         **
** 1.0.4     28-Apr-2016   Sinil        Redmine #4744                         **
** 1.0.3     25-Apr-2016   Sinil        Redmine #4610                         **
** 1.0.0     02-Feb-2015   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a Defect] "see MEMMAP003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw_Config.h"

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
#define WDG_76_ACW_START_SEC_CONST_8
#include "MemMap.h"
CONST(uint8, WDG_76_ACW_CONST) Wdg_76_Acw_InstanceId = WDG_76_ACW_INSTANCE_ID;
#define WDG_76_ACW_STOP_SEC_CONST_8
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CONST_16
#include "MemMap.h"
CONST(uint16, WDG_76_ACW_CONST) Wdg_76_Acw_InitialTimeout
  = WDG_76_ACW_INITIAL_TIMEOUT;
#define WDG_76_ACW_STOP_SEC_CONST_16
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CONST_16
#include "MemMap.h"
CONST(uint16, WDG_76_ACW_CONST) Wdg_76_Acw_MaxTimeout = WDG_76_ACW_MAX_TIMEOUT;
#define WDG_76_ACW_STOP_SEC_CONST_16
#include "MemMap.h"

#if (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON)
#define WDG_76_ACW_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(Dio_ChannelType, WDG_76_ACW_CONST) Wdg_76_Acw_DioChannel
  = WDG_76_ACW_DIO_CHANNEL;
#define WDG_76_ACW_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON)
#define WDG_76_ACW_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(Dio_ChannelType, WDG_76_ACW_CONST) Wdg_76_Acw_DioChannel
  = WDG_76_ACW_DIO_CHANNEL;
#define WDG_76_ACW_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#define WDG_76_ACW_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(Dio_ChannelType, WDG_76_ACW_CONST) Wdg_76_Acw_DioModeChannel
  = WDG_76_ACW_DIO_MODE_CHANNEL;
#define WDG_76_ACW_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#define WDG_76_ACW_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(Gpt_ChannelType, WDG_76_ACW_CONST) Wdg_76_Acw_GptChannel
  = WDG_76_ACW_GPT_CHANNEL;
#define WDG_76_ACW_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(WdgIf_ModeType, WDG_76_ACW_CONST) Wdg_76_Acw_DefaultMode
  = WDG_76_ACW_DEFAULT_MODE;
#define WDG_76_ACW_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* polyspace-begin VARIABLE:ALL [Not a Defect] 
                           "varialbe is used according to user configuration" */
#if (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON)
#define WDG_76_ACW_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* WDG_76_ACW_E_DISABLE_REJECTED */
CONST(Dem_EventIdType, WDG_76_ACW_CONST) Wdg_76_Acw_GddEDisableRejected
  = WDG_76_ACW_E_DISABLE_REJECTED;
#define WDG_76_ACW_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* WDG_76_ACW_E_MODE_FAILED */
CONST(Dem_EventIdType, WDG_76_ACW_CONST) Wdg_76_Acw_GddEModeFailed
  = WDG_76_ACW_E_MODE_FAILED;
#define WDG_76_ACW_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
/* polyspace-end VARIABLE:ALL */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
