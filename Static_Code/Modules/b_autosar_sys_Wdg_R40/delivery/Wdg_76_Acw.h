/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Wdg_76_Acw.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTRON CUSTOM WDG                                     **
**                                                                            **
**  PURPOSE   : Header file to publish Autron Custom Watchdog function        **
**              prototypes                                                    **
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
** 1.4.0     07-Mar-2019   YH.Han       Redmine #16356                        **
** 1.1.0     17-Jul-2017   Kuksun       Redmine #8886                         **
** 1.0.9     19-Dec-2016   Kuksun       Redmine #6708                         **
** 1.0.8     28-Apr-2016   Sinil        Redmine #4744                         **
** 1.0.7     25-Apr-2016   Sinil        Redmine #4610                         **
** 1.0.0     20-Nov-2014   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a Defect] "see MEMMAP003 of AUTOSAR" */

#ifndef WDG_76_ACW_H
#define WDG_76_ACW_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Wdg_76_Acw_Cfg.h"
#include "Wdg_76_Acw_Types.h"
#include "WdgIf_Types.h"

/*******************************************************************************
**                      Service IDs                                           **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Not a Defect] 
                              "macro is used according to user configuration" */
/* Service Id of Wdg_76_Acw_Init */
#define WDG_76_ACW_INIT_SID                             ((uint8)0x00)
/* Service Id of Wdg_76_Acw_SetMode */
#define WDG_76_ACW_SETMODE_SID                          ((uint8)0x01)
/* Service Id of Wdg_76_Acw_SetTriggerCondition */
#define WDG_76_ACW_SETTRIGGERCONDITION_SID              ((uint8)0x03)
/* Service Id of Wdg_76_Acw_GetVersionInfo */
#define WDG_76_ACW_GETVERSIONINFO_SID                   ((uint8)0x04)
/* Service Id of Wdg_76_Acw_Cbk_GptNotification */
#define WDG_76_ACW_CBK_GPTNOTIFICATION_SID              ((uint8)0x05)
/* Service Id of Wdg_76_Acw_Trigger */
#define WDG_76_ACW_CBK_TRIGGER_SID                      ((uint8)0x06)
/* polyspace-end<MISRA-C3:2.5 */

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Not a Defect] 
                              "macro is used according to user configuration" */
/* API service used in wrong context(e.g. module not initialized). */
#define WDG_76_ACW_E_DRIVER_STATE                       ((uint8)0x10)
/* API service called with wrong parameter(s) */
#define WDG_76_ACW_E_PARAM_MODE                         ((uint8)0x11)
/* API service called with inconsistent parameter(s) */
#define WDG_76_ACW_E_PARAM_CONFIG                       ((uint8)0x12)
/* The passed timeout value is higher than the maximum timeout value */
#define WDG_76_ACW_E_PARAM_TIMEOUT                      ((uint8)0x13)
/* API is called with wrong pointer value (e.g. NULL pointer) */
#define WDG_76_ACW_E_PARAM_POINTER                      ((uint8)0x14)
/* Wdg trigger failed */
#define WDG_76_ACW_E_TRIGGER_FAIL                       ((uint8)0x15)
/* polyspace-end<MISRA-C3:2.5 */

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Not a Defect] 
                              "macro is used according to user configuration" */
#define WDG_76_ACW_TRUE                                 TRUE
#define WDG_76_ACW_FALSE                                FALSE
#define WDG_76_ACW_NULL                                 NULL
#define WDG_76_ACW_NULL_PTR                             NULL_PTR

/* polyspace<MISRA-C:19.4, 19.7:Not a defect:Justify with annotations> 
   use function like-macro for removing unused argument compiler warning */
#define WDG_76_ACW_UNUSED(x)                            (void)(x)

/* polyspace<MISRA-C:19.4, 19.7:Not a defect:Justify with annotations> 
   use function like-macro for removing unused argument compiler warning */
#define WDG_76_ACW_UNUSED_PTR(x)                        if ((x) != NULL_PTR) {}
/* polyspace-end<MISRA-C3:2.5 */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411== STD_ON)
#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
extern VAR(Dio_LevelType, WDG_76_ACW_VAR) Wdg_76_Acw_GddLevel;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
extern VAR(boolean, WDG_76_ACW_VAR) Wdg_76_Acw_Shutdown;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON) */

#if (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
extern VAR(Spi_DataType, WDG_76_ACW_VAR) Wdg_76_Acw_GddArisuCanSpiDestData[];
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON) */

#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
extern VAR(WdgIf_ModeType, WDG_76_ACW_VAR) Wdg_76_Acw_GddCurrentMode;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
extern VAR(Wdg_76_Acw_StatusType, WDG_76_ACW_VAR) Wdg_76_Acw_GddStatus;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */

#define WDG_76_ACW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
extern VAR(uint32, WDG_76_ACW_VAR) Wdg_76_Acw_GulTriggerCount;
#define WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Wdg_76_Acw_ConfigType, WDG_76_ACW_CONST) Wdg_76_Acw_GddConfigRoot;
#define WDG_76_ACW_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
#define WDG_76_ACW_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Wdg_76_Acw_ArisuCanConfigType, WDG_76_ACW_CONST) Wdg_76_Acw_GddArisuCanCfg;
#define WDG_76_ACW_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON) */

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] 
                                           "variable name is not unambiguous" */
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_Init
  (P2CONST(Wdg_76_Acw_ConfigType, AUTOMATIC, WDG_76_ACW_CONST) ConfigPtr);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end MISRA-C3:D4.5 */

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDG_76_ACW_CODE) Wdg_76_Acw_SetMode
  (WdgIf_ModeType ddNewMode);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_SetTriggerCondition
  (uint16 timeout);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#if (WDG_76_ACW_VERSION_INFO_API == STD_ON)
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_76_ACW_CONST) versioninfo);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (WDG_76_ACW_VERSION_INFO_API == STD_ON) */

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_Gpt_Cbk(void);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_Trigger(void);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#if (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDG_76_ACW_CODE) Wdg_76_Acw_ArisuCanTrigger(void);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON) */

#if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411== STD_ON)
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_MPQ6411_Shutdown(void);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */

#endif /* WDG_76_ACW_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
