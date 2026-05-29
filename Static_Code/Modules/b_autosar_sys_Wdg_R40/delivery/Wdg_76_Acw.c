/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Wdg_76_Acw.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTRON CUSTOM WDG                                     **
**                                                                            **
**  PURPOSE   : Autron Custom Watchdog API Functionality                      **
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
** 1.8.2.0   18-Oct-2021   YH.Han       Redmine #32459, #32698                **
** 1.8.1.0   08-Jan-2021   YH.Han       Redmine #27593                        **
** 1.4.0     07-Mar-2019   YH.Han       Redmine #16356                        **
** 1.1.0     17-Jul-2017   Kuksun       Redmine #8886                         **
** 1.0.15    29-May-2017   Kuksun       Redmine #8684                         **
** 1.0.14    19-Dec-2016   Kuksun       Redmine #6708                         **
** 1.0.13    10-May-2016   Sinil        Redmine #4610                         **
** 1.0.12    25-Apr-2016   Sinil        Redmine #4744                         **
** 1.0.11    22-Apr-2016   Sinil        Redmine #4610                         **
** 1.0.10    23-Feb-2016   Sinil        Redmine #4165                         **
** 1.0.0     20-Nov-2014   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
  polyspace:begin<MISRA-C:19.1:Not a defect:Justify with annotations> Needed for memory section
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw.h"
#include "Wdg_76_Acw_Config.h"
#include "HwResource.h"
#if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
#if (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
#include "Spi.h"
#include "CanTrcv.h"
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON) */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
static P2CONST(Wdg_76_Acw_ConfigType, AUTOMATIC, WDG_76_ACW_VAR)
  Wdg_76_Acw_GpCfgPtr = WDG_76_ACW_NULL_PTR;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#if (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON)
#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
static VAR(Dio_LevelType, WDG_76_ACW_VAR) Wdg_76_Acw_GddLevel;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
static VAR(Dio_LevelType, WDG_76_ACW_VAR) Wdg_76_Acw_GddLevel = (Dio_LevelType)STD_LOW;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON) */

#if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411== STD_ON)
#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
static VAR(Dio_LevelType, WDG_76_ACW_VAR) Wdg_76_Acw_GddLevel = (Dio_LevelType)STD_HIGH;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
VAR(Dio_LevelType, WDG_76_ACW_VAR) Wdg_76_Acw_GddLevel_Mode = (Dio_LevelType)STD_LOW;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
VAR(boolean, WDG_76_ACW_VAR) Wdg_76_Acw_Shutdown = FALSE;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#endif /* (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON) */

#if (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
VAR(Spi_DataType, WDG_76_ACW_VAR) Wdg_76_Acw_GddArisuCanSpiDestData[WDG_76_TWO] = {0,};
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON) */

/* polyspace-begin MISRA-C3:8.7 [Not a Defect] 
                                          "it is called for test application" */
#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
VAR(WdgIf_ModeType, WDG_76_ACW_VAR) Wdg_76_Acw_GddCurrentMode
  = WDGIF_SLOW_MODE;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
#define WDG_76_ACW_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
VAR(Wdg_76_Acw_StatusType, WDG_76_ACW_VAR) Wdg_76_Acw_GddStatus =
  WDG_76_ACW_UNINIT;
#define WDG_76_ACW_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */

#define WDG_76_ACW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
VAR(uint32, WDG_76_ACW_VAR) Wdg_76_Acw_GulTriggerCount = 0U;
#define WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* polyspace-end<MISRA-C3:8.7 */



/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint16, WDG_76_ACW_CODE) Wdg_76_Acw_GetTriggerCount
  (WdgIf_ModeType ddMode, uint16 usTimeout);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
static FUNC(Gpt_ValueType, WDG_76_ACW_CODE) Wdg_76_Acw_GetNextGptTick
  (boolean blRemainingCheck);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"


#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
/***************************************************************************//**
 Function Name      : Wdg_76_Acw_Init                                       
                                                                            
 Service ID         : 0x00                                                  
                                                                            
 Description        : Initializes the module.                               
                                                                            
 Sync/Async         : Synchronous                                           
                                                                            
 Re-entrancy        : Non Reentrant                                         
                                                                            
 @param [Input]     : ConfigPtr                                             
                                                                            
 @param [InOut]     : None                                                  
                                                                            
 @param [Output]    : None                                                  
                                                                       
 @return            : None                                                  
                                                                               
 @pre               : None

 @ingroup           : Initialize                                            

 Remarks            : Global Variable(s) :\n                                 
                      Wdg_76_Acw_GddStatus,\n                                 
                      Wdg_76_Acw_GddConfigRoot,\n                             
                      Wdg_76_Acw_InstanceId,\n                                
                      Wdg_76_Acw_DefaultMode,\n                               
                      Wdg_76_Acw_GddEDisableRejected,\n                       
                      Wdg_76_Acw_GulTriggerCount,\n                           
                      Wdg_76_Acw_GptChannel,\n                                
                      Wdg_76_Acw_GddLevel,\n                                  
                      Wdg_76_Acw_DioChannel,\n                                
                      Wdg_76_Acw_InitialTimeout,\n                            
                      Wdg_76_Acw_GpCfgPtr,\n                                  
                      Wdg_76_Acw_GddCurrentMode\n                             
                                                                            
                      Function(s) invoked :\n                                 
                      Det_ReportError,\n                                      
                      Dem_ReportErrorStatus,\n                                
                      Gpt_StopTimer,\n                                        
                      Gpt_DisableNotification,\n                              
                      Gpt_EnableNotification,\n                               
                      Dio_WriteChannel,\n                                     
                      Gpt_StartTimer,\n                                       
                      Wdg_76_Acw_GetNextGptTick\n                             

*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] 
                                           "variable name is not unambiguous" */
FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_Init
  (P2CONST(Wdg_76_Acw_ConfigType, AUTOMATIC, WDG_76_ACW_CONST) ConfigPtr)
/* polyspace-end MISRA-C3:D4.5 */
{
  P2CONST(Wdg_76_Acw_ConfigType, AUTOMATIC, WDG_76_ACW_VAR) LpConfig
    = WDG_76_ACW_NULL_PTR;
  Gpt_ValueType LddNextGptTick = 0;
  #if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON)
  Gpt_ValueType LddOffSetGptTick = 0;
  #endif /* WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON */

  #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
  Wdg_76_Acw_GddStatus = WDG_76_ACW_UNINIT;
  #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */

  #if (WDG_76_ACW_PRECOMPILE_SUPPORT == STD_ON)
  /* polyspace-begin RTE:UNR [Not a Defect] 
                      "code can be reachable according to user configuration" */
  WDG_76_ACW_UNUSED_PTR(ConfigPtr);
  /* polyspace-end RTE:UNR */
  /* If precompile support enable, initialize the configuration pointer
    with the default pointer */
  LpConfig = &Wdg_76_Acw_GddConfigRoot;
  #else /* (WDG_76_ACW_PRECOMPILE_SUPPORT == STD_ON) */
  LpConfig = ConfigPtr;
  #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
  if (LpConfig == WDG_76_ACW_NULL_PTR)
  {
    (void)Det_ReportError(WDG_76_ACW_MODULE_ID, Wdg_76_Acw_InstanceId,
      WDG_76_ACW_INIT_SID, WDG_76_ACW_E_PARAM_POINTER);
  }
  else
  #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
  #endif /* (WDG_76_ACW_PRECOMPILE_SUPPORT == STD_ON) */
  {
    #if (WDG_76_ACW_DISABLE_ALLOWED == STD_OFF)
    /* polyspace-begin RTE:UNR [Not a Defect] 
                      "code can be reachable according to user configuration" */
    /* polyspace:begin<DEFECT:DEAD_CODE:Not a defect:Justify with annotations> could be reachable according to user configuration */
    /* polyspace:begin<MISRA-C3:2.1:Not a defect:Justify with annotations> could be reachable according to user configuration */
    /* polyspace:begin<MISRA-C3:14.3:Not a defect:Justify with annotations> could be reachable according to user configuration */
    if (Wdg_76_Acw_DefaultMode == WDGIF_OFF_MODE)
    {
      #if (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON)
      Dem_ReportErrorStatus(Wdg_76_Acw_GddEDisableRejected,
        DEM_EVENT_STATUS_FAILED);
      #endif /* (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON) */
    }
    /* polyspace-end RTE:UNR */
    /* polyspace:end<DEFECT:DEAD_CODE> */
    /* polyspace:end<MISRA-C3:2.1> */
    /* polyspace:end<MISRA-C3:14.3> */
    else
    #endif /* (WDG_76_ACW_DISABLE_ALLOWED == STD_ON) */
    {
      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      Wdg_76_Acw_GddStatus = WDG_76_ACW_BUSY;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */

      Wdg_76_Acw_GpCfgPtr = LpConfig;

      Gpt_StopTimer(Wdg_76_Acw_GptChannel);
      #if(!HWRESOURCE_VENDOR(HWRESOURCE_RENESAS))
      Gpt_DisableNotification(Wdg_76_Acw_GptChannel);
      #endif /* !HWRESOURCE_VENDOR(HWRESOURCE_RENESAS) */

      #if (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON)
      Wdg_76_Acw_GddLevel = (Dio_LevelType)STD_LOW;
      #endif /* (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON) */

      #if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON)
      Wdg_76_Acw_GddLevel = (Dio_LevelType)STD_HIGH;
      Wdg_76_Acw_GddLevel_Mode = (Dio_LevelType)STD_LOW;
      
      if (Dio_ReadChannel(Wdg_76_Acw_DioModeChannel) != Wdg_76_Acw_GddLevel_Mode)
      {
        Dio_WriteChannel(Wdg_76_Acw_DioModeChannel, (Dio_LevelType)STD_HIGH);
        Dio_WriteChannel(Wdg_76_Acw_DioModeChannel, Wdg_76_Acw_GddLevel_Mode);
      }
      #endif /* (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411== STD_ON) */
      
      Wdg_76_Acw_GddCurrentMode = Wdg_76_Acw_DefaultMode;

      switch (Wdg_76_Acw_DefaultMode)
      {
      case WDGIF_SLOW_MODE:
      case WDGIF_FAST_MODE:
        #if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON)
          LddOffSetGptTick = Wdg_76_Acw_GpCfgPtr->ddInitialPeriodTick;
          Gpt_EnableNotification(Wdg_76_Acw_GptChannel);
          Gpt_StartTimer(Wdg_76_Acw_GptChannel, LddOffSetGptTick);

          Wdg_76_Acw_GulTriggerCount = Wdg_76_Acw_GetTriggerCount(
          Wdg_76_Acw_DefaultMode, Wdg_76_Acw_InitialTimeout);
        #endif /* WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON */
        
        #if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_OFF)
          Wdg_76_Acw_Trigger();
          
          LddNextGptTick = Wdg_76_Acw_GetNextGptTick(FALSE);
          Gpt_EnableNotification(Wdg_76_Acw_GptChannel);
          Gpt_StartTimer(Wdg_76_Acw_GptChannel, LddNextGptTick);

          Wdg_76_Acw_GulTriggerCount = Wdg_76_Acw_GetTriggerCount(
          Wdg_76_Acw_DefaultMode, Wdg_76_Acw_InitialTimeout);
        #endif /* WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_OFF */
        break;

      /* polyspace-begin RTE:UNR [Not a Defect] 
                      "code can be reachable according to user configuration" */
      /* polyspace:begin<DEFECT:DEAD_CODE:Not a defect:Justify with annotations> could be reachable according to user configuration */
      case WDGIF_OFF_MODE:
      default:
        /* do nothing */
        break;
      /* polyspace-end RTE:UNR */
      /* polyspace:end<DEFECT:DEAD_CODE> */
      }

      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      Wdg_76_Acw_GddStatus = WDG_76_ACW_IDLE;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
    
    }
  }
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/***************************************************************************//**
 Function Name      : Wdg_76_Acw_SetMode                                    
                                                                            
 Service ID         : 0x01                                                  
                                                                            
 Description        : Switches the watchdog into the mode Mode.             
                                                                            
 Sync/Async         : Synchronous                                           
                                                                            
 Re-entrancy        : Non Reentrant                                         
                                                                            
 @param [Input]     : Mode                                             
                                                                            
 @param [InOut]     : None                                                  
                                                                            
 @param [Output]    : None                                                  
                                                                       
 @return            : Std_ReturnType                                                  
                                                                               
 @pre               : None

 @ingroup           : Normal-Operation    
                                                                            
 Remarks            : Global Variable(s) :\n                                  
                      Wdg_76_Acw_GddStatus,\n                                 
                      Wdg_76_Acw_InstanceId,\n                                
                      Wdg_76_Acw_GddEDisableRejected,\n                       
                      Wdg_76_Acw_GddCurrentMode,\n                            
                      Wdg_76_Acw_GptChannel\n                                 
                                                                            
                      Function(s) invoked :\n                                 
                      Det_ReportError,\n                                      
                      Dem_ReportErrorStatus,\n                                
                      Gpt_StartTimer,\n                                       
                      Wdg_76_Acw_GetNextGptTick\n                             
*******************************************************************************/
FUNC(Std_ReturnType, WDG_76_ACW_CODE) Wdg_76_Acw_SetMode
  (WdgIf_ModeType ddNewMode)
{
  Std_ReturnType LddReturnvalue = E_OK;
  Gpt_ValueType LddNextGptTick = 0;

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> status check */
  #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
  if (Wdg_76_Acw_GddStatus != WDG_76_ACW_IDLE)
  {
    (void)Det_ReportError(WDG_76_ACW_MODULE_ID, Wdg_76_Acw_InstanceId,
      WDG_76_ACW_SETMODE_SID, WDG_76_ACW_E_DRIVER_STATE);
    LddReturnvalue = E_NOT_OK;
  }
  if (LddReturnvalue == E_OK)
  #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (WDG_76_ACW_DISABLE_ALLOWED == STD_OFF)
    if (ddNewMode == WDGIF_OFF_MODE)
    {
      #if (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON)
      Dem_ReportErrorStatus(Wdg_76_Acw_GddEDisableRejected,
        DEM_EVENT_STATUS_FAILED);
      #endif /* (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON) */
      LddReturnvalue = E_NOT_OK;
    }
    #endif /* (WDG_76_ACW_DISABLE_ALLOWED == STD_ON) */

    if (LddReturnvalue == E_OK)
    {
      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      Wdg_76_Acw_GddStatus = WDG_76_ACW_BUSY;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */

      switch (ddNewMode)
      {
      case WDGIF_SLOW_MODE:
      case WDGIF_FAST_MODE:
        if (Wdg_76_Acw_GddCurrentMode != ddNewMode)
        {
          Wdg_76_Acw_Trigger();

          Wdg_76_Acw_GddCurrentMode = ddNewMode;

          LddNextGptTick = Wdg_76_Acw_GetNextGptTick(FALSE);
        }
        else
        {
          Wdg_76_Acw_GddCurrentMode = ddNewMode;

          LddNextGptTick = Wdg_76_Acw_GetNextGptTick(TRUE);
        }

        if (LddNextGptTick != 0)
        {
          Gpt_StopTimer(Wdg_76_Acw_GptChannel);
          Gpt_DisableNotification(Wdg_76_Acw_GptChannel);

          Gpt_EnableNotification(Wdg_76_Acw_GptChannel);
          Gpt_StartTimer(Wdg_76_Acw_GptChannel, LddNextGptTick);
        }
        break;

      /* polyspace:begin<DEFECT:DEAD_CODE:Not a defect:Justify with annotations> could be reachable according to user configuration */
      case WDGIF_OFF_MODE:
        Wdg_76_Acw_GddCurrentMode = ddNewMode;

        Gpt_StopTimer(Wdg_76_Acw_GptChannel);
        Gpt_DisableNotification(Wdg_76_Acw_GptChannel);
        break;

      default:
        /* do nothing */
        break;
      /* polyspace:end<DEFECT:DEAD_CODE> */
      }

      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      Wdg_76_Acw_GddStatus = WDG_76_ACW_IDLE;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      /* do nothing */
    }
  }
  /* polyspace:end<RTE:UNR> */

  return LddReturnvalue;
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"


#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/***************************************************************************//**
 Function Name      : Wdg_76_Acw_SetTriggerCondition                       
                                                                            
 Service ID         : 0x03                                                  
                                                                            
 Description        : Sets the timeout value for the trigger counter.       
                                                                            
 Sync/Async         : Synchronous                                           
                                                                            
 Re-entrancy        : Non Reentrant                                         

 @param [Input]     : timeout                                             
                                                                            
 @param [InOut]     : None                                                  
                                                                            
 @param [Output]    : None                                                  
                                                                       
 @return            : None                                                  
                                                                               
 @pre               : None

 @ingroup           : Normal-Operation 
                                                                            
 Remarks            : Global Variable(s) :\n                                  
                      Wdg_76_Acw_GddStatus,\n                                 
                      Wdg_76_Acw_InstanceId,\n                                
                      Wdg_76_Acw_MaxTimeout,\n                                
                      Wdg_76_Acw_GptChannel,\n                                
                      Wdg_76_Acw_GulTriggerCount,\n                           
                      Wdg_76_Acw_GddCurrentMode,\n                            
                      Wdg_76_Acw_GpCfgPtr,\n                                  
                                                                            
                      Function(s) invoked :\n                                 
                      Det_ReportError,\n                                      
                      Gpt_StopTimer,\n                                        
                      Gpt_DisableNotification\n                               
*******************************************************************************/
FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_SetTriggerCondition(uint16 timeout)
{
  #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
  boolean LblSuccess = WDG_76_ACW_TRUE;

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> status check */
  if (Wdg_76_Acw_GddStatus != WDG_76_ACW_IDLE)
  {
    (void)Det_ReportError(WDG_76_ACW_MODULE_ID, Wdg_76_Acw_InstanceId,
      WDG_76_ACW_SETTRIGGERCONDITION_SID, WDG_76_ACW_E_DRIVER_STATE);
    LblSuccess = WDG_76_ACW_FALSE;
  }

  if (timeout > Wdg_76_Acw_MaxTimeout)
  {
    (void)Det_ReportError(WDG_76_ACW_MODULE_ID, Wdg_76_Acw_InstanceId,
      WDG_76_ACW_SETTRIGGERCONDITION_SID, WDG_76_ACW_E_PARAM_TIMEOUT);
    LblSuccess = WDG_76_ACW_FALSE;
  }
  /* polyspace:end<RTE:UNR> */

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> status check */
  if (LblSuccess == WDG_76_ACW_TRUE)
  #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
  {
    if (timeout == 0U)
    {
      Gpt_StopTimer(Wdg_76_Acw_GptChannel);
      Gpt_DisableNotification(Wdg_76_Acw_GptChannel);

      Wdg_76_Acw_GulTriggerCount = 0U;

      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      Wdg_76_Acw_GddStatus = WDG_76_ACW_EXPIRED;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      Wdg_76_Acw_GulTriggerCount = Wdg_76_Acw_GetTriggerCount(
        Wdg_76_Acw_GddCurrentMode, timeout);
    }
  }
  /* polyspace:end<RTE:UNR> */
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#if (WDG_76_ACW_VERSION_INFO_API == STD_ON)
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/***************************************************************************//**
 Function Name      : Wdg_76_Acw_GetVersionInfo                             
                                                                            
 Service ID         : 0x04                                                  
                                                                            
 Description        : Returns the version information of the module.        
                                                                            
 Sync/Async         : Synchronous                                           
                                                                            
 Re-entrancy        : Reentrant

 @param [Input]     : None                                             
                                                                            
 @param [InOut]     : None                                                  
                                                                            
 @param [Output]    : versioninfo                                                  
                                                                       
 @return            : None                                                  
                                                                               
 @pre               : None

 @ingroup           : Version-Information 
                                                                            
 Remarks            : Global Variable(s) :\n                                  
                      Wdg_76_Acw_InstanceId\n                                 
                                                                            
                      Function(s) invoked :\n                                 
                      Det_ReportError\n                                       
*******************************************************************************/
FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_76_ACW_CONST) versioninfo)
{
  #if(WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
  /* check NULL pointer */
  if (versioninfo == WDG_76_ACW_NULL_PTR)
  {
    /* Report to DET */
    (void)Det_ReportError(WDG_76_ACW_MODULE_ID, Wdg_76_Acw_InstanceId,
      WDG_76_ACW_GETVERSIONINFO_SID, WDG_76_ACW_E_PARAM_POINTER);
  }
  else
  #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Load the vendor Id */
    versioninfo->vendorID = WDG_76_ACW_VENDOR_ID;
    /* Load the module Id */
    versioninfo->moduleID = WDG_76_ACW_MODULE_ID;
    /* Load Software Major Version */
    versioninfo->sw_major_version = WDG_76_ACW_SW_MAJOR_VERSION;
    /* Load Software Minor Version */
    versioninfo->sw_minor_version = WDG_76_ACW_SW_MINOR_VERSION;
    /* Load Software Patch Version */
    versioninfo->sw_patch_version = WDG_76_ACW_SW_PATCH_VERSION;
  }
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (WDG_76_ACW_VERSION_INFO_API == STD_ON) */

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/***************************************************************************//**
 Function Name      : Wdg_76_Acw_Gpt_Cbk                                    
                                                                            
 Service ID         : 0x05                                                  
                                                                            
 Description        : Watchdog triggering routine in case it is called from 
                      a GPT callback.                                       
                                                                            
 Sync/Async         : Synchronous                                           
                                                                            
 Re-entrancy        : Non Reentrant                                         
                                                                            
 @param [Input]     : None                                             
                                                                            
 @param [InOut]     : None                                                  
                                                                            
 @param [Output]    : None                                                  
                                                                       
 @return            : None                                                  
                                                                               
 @pre               : None

 @ingroup           : Trigger-Function 
 
 Remarks            : Global Variable(s) :\n                                  
                      Wdg_76_Acw_GddLevel,\n                                  
                      Wdg_76_Acw_GulTriggerCount,\n                           
                      Wdg_76_Acw_GptChannel,\n                                
                      Wdg_76_Acw_GddStatus\n                                  
                                                                            
                      Function(s) invoked :\n                                 
                      Wdg_76_Acw_Trigger,\n                                   
                      Gpt_StartTimer,\n                                       
                      Wdg_76_Acw_GetNextGptTick,\n                            
                      Gpt_StopTimer,\n                                        
                      Gpt_DisableNotification\n                               
*******************************************************************************/
FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_Gpt_Cbk(void)
{
  Gpt_ValueType LddNextGptTick = 0;

  #if (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON)
  if (Wdg_76_Acw_GddLevel == (Dio_LevelType)STD_HIGH)
  {
  #endif

  #if ((WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON) || \
      (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON))
    if (Wdg_76_Acw_GulTriggerCount > 0)
    {
      Wdg_76_Acw_Trigger();

      LddNextGptTick = Wdg_76_Acw_GetNextGptTick(FALSE);
      Gpt_StartTimer(Wdg_76_Acw_GptChannel, LddNextGptTick);

      Wdg_76_Acw_GulTriggerCount--;
    }
    else
    {
      Gpt_StopTimer(Wdg_76_Acw_GptChannel);
      Gpt_DisableNotification(Wdg_76_Acw_GptChannel);

      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      Wdg_76_Acw_GddStatus = WDG_76_ACW_EXPIRED;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
    }
  #endif
  
  #if (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON)
  }
  else
  {
    Wdg_76_Acw_Trigger();

    LddNextGptTick = Wdg_76_Acw_GetNextGptTick(FALSE);
    Gpt_StartTimer(Wdg_76_Acw_GptChannel, LddNextGptTick);
  }
  #endif

  #if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON)
  if (Wdg_76_Acw_GddLevel == (Dio_LevelType)STD_LOW)
  {
    if (Wdg_76_Acw_GulTriggerCount > 0)
    {
      Wdg_76_Acw_Trigger();

      LddNextGptTick = Wdg_76_Acw_GetNextGptTick(FALSE);
      Gpt_StartTimer(Wdg_76_Acw_GptChannel, LddNextGptTick);

      Wdg_76_Acw_GulTriggerCount--;
    }
    else
    {
      Gpt_StopTimer(Wdg_76_Acw_GptChannel);
      Gpt_DisableNotification(Wdg_76_Acw_GptChannel);

      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      Wdg_76_Acw_GddStatus = WDG_76_ACW_EXPIRED;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
    }
  }
  else
  {    
      Wdg_76_Acw_Trigger();

      LddNextGptTick = Wdg_76_Acw_GetNextGptTick(FALSE);
      Gpt_StartTimer(Wdg_76_Acw_GptChannel, LddNextGptTick);   
  }  
  if (Wdg_76_Acw_Shutdown == TRUE)
  {
    Wdg_76_Acw_MPQ6411_Shutdown();
  }  
  #endif /* (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON) */
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"


#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/***************************************************************************//**
 Function Name      : Wdg_76_Acw_GetTriggerCount                            
                                                                            
 Service ID         : NA                                                    
                                                                            
 Description        : Calculate trigger count                               
                                                                            
 Sync/Async         : Synchronous                                           
                                                                            
 Re-entrancy        : Non Reentrant
                                                                             
 @param [Input]     : ddMode, usTimeout                                             
                                                                            
 @param [InOut]     : None                                                  
                                                                            
 @param [Output]    : None                                                  
                                                                       
 @return            : uint16                                                  
                                                                               
 @pre               : None

 @ingroup           : Trigger-Function                                                
                                                                            
 Remarks            : Global Variable(s) :\n                                  
                      Wdg_76_Acw_GpCfgPtr\n                                   
                                                                            
                      Function(s) invoked : None\n                            
*******************************************************************************/
static FUNC(uint16, WDG_76_ACW_CODE) Wdg_76_Acw_GetTriggerCount(WdgIf_ModeType ddMode,
  uint16 usTimeout)
{
  uint16 LusTriggerCount = 0;

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> status check */
  switch (ddMode)
  {
  case WDGIF_SLOW_MODE:
    if (Wdg_76_Acw_GpCfgPtr != WDG_76_ACW_NULL_PTR)
    {
      if (Wdg_76_Acw_GpCfgPtr->ulSlowPeriodMs > 0)
      {
        LusTriggerCount = (uint16)(usTimeout
          / Wdg_76_Acw_GpCfgPtr->ulSlowPeriodMs);
      }
    }
    break;

  case WDGIF_FAST_MODE:
    if (Wdg_76_Acw_GpCfgPtr != WDG_76_ACW_NULL_PTR)
    {
      if (Wdg_76_Acw_GpCfgPtr->ulFastPeriodMs > 0)
      {
        LusTriggerCount = (uint16)(usTimeout
          / Wdg_76_Acw_GpCfgPtr->ulFastPeriodMs);
      }
    }
    break;

  case WDGIF_OFF_MODE:
  default:
    /* do nothing */
    break;
  }
  /* polyspace:end<RTE:UNR> */

  return LusTriggerCount;
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"


#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/***************************************************************************//**
 Function Name      : Wdg_76_Acw_GetNextGptTick                             
                                                                            
 Service ID         : NA                                                    
                                                                            
 Description        : Get next gpt tick                                     
                                                                            
 Sync/Async         : Synchronous                                           
                                                                            
 Re-entrancy        : Non Reentrant
                                                                             
 @param [Input]     : blRemainingCheck                                             
                                                                            
 @param [Inout]     : None                                                  
                                                                            
 @param [Output]    : None                                                  
                                                                       
 @return            : Gpt_ValueType                                                  
                                                                               
 @pre               : None

 @ingroup           : Trigger-Function                                                 
                                                                            
 Remarks            : Global Variable(s) :\n                                  
                      Wdg_76_Acw_GddCurrentMode,\n                            
                      Wdg_76_Acw_GptChannel,\n                                
                      Wdg_76_Acw_GddLevel,\n                                  
                      Wdg_76_Acw_GpCfgPtr\n                                   
                                                                            
                      Function(s) invoked :\n                                 
                      Gpt_GetTimeRemaining\n                                 
*******************************************************************************/
static FUNC(Gpt_ValueType, WDG_76_ACW_CODE) Wdg_76_Acw_GetNextGptTick
  (boolean blRemainingCheck)
{
  Gpt_ValueType LddNextGptTick = 0;

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> status check */
  switch (Wdg_76_Acw_GddCurrentMode)
  {
  case WDGIF_SLOW_MODE:
    if (blRemainingCheck == TRUE)
    {
      LddNextGptTick = Gpt_GetTimeRemaining(Wdg_76_Acw_GptChannel);
    }
    else
    {
      if (Wdg_76_Acw_GpCfgPtr != WDG_76_ACW_NULL_PTR)
      {
        #if (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON)
        if (Wdg_76_Acw_GddLevel == (Dio_LevelType)STD_HIGH)
        {
          LddNextGptTick = Wdg_76_Acw_GpCfgPtr->ddSlowDutyTick;
        }
        else
        {
          LddNextGptTick = Wdg_76_Acw_GpCfgPtr->ddSlowPeriodTick
            - Wdg_76_Acw_GpCfgPtr->ddSlowDutyTick;
        }
        #elif (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON)
        if (Wdg_76_Acw_GddLevel == (Dio_LevelType)STD_LOW)
        {
          LddNextGptTick = Wdg_76_Acw_GpCfgPtr->ddSlowDutyTick;
        }
        
        else       
        {
          LddNextGptTick = Wdg_76_Acw_GpCfgPtr->ddSlowPeriodTick 
            - Wdg_76_Acw_GpCfgPtr->ddSlowDutyTick;
        }        
        #elif (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
        LddNextGptTick = Wdg_76_Acw_GpCfgPtr->ddSlowPeriodTick;
        #endif
      }
    }
    break;

  case WDGIF_FAST_MODE:
    if (blRemainingCheck == TRUE)
    {
      LddNextGptTick = Gpt_GetTimeRemaining(Wdg_76_Acw_GptChannel);
    }
    else
    {
      if (Wdg_76_Acw_GpCfgPtr != WDG_76_ACW_NULL_PTR)
      {
        #if (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON)
        if (Wdg_76_Acw_GddLevel == (Dio_LevelType)STD_HIGH)
        {
          LddNextGptTick = Wdg_76_Acw_GpCfgPtr->ddFastDutyTick;
        }
        else
        {
          LddNextGptTick = Wdg_76_Acw_GpCfgPtr->ddFastPeriodTick
            - Wdg_76_Acw_GpCfgPtr->ddFastDutyTick;
        }
        #elif (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON)
        if (Wdg_76_Acw_GddLevel == (Dio_LevelType)STD_LOW)
        {
          LddNextGptTick = Wdg_76_Acw_GpCfgPtr->ddFastDutyTick;
        }
        else
        {
          LddNextGptTick = Wdg_76_Acw_GpCfgPtr->ddFastPeriodTick
            - Wdg_76_Acw_GpCfgPtr->ddFastDutyTick;
        }
        #elif (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
        LddNextGptTick = Wdg_76_Acw_GpCfgPtr->ddFastPeriodTick;
        #endif
      }
    }
    break;

  case WDGIF_OFF_MODE:
  default:
    /* do nothing */
    break;
  }
  /* polyspace:end<RTE:UNR> */

  return LddNextGptTick;
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"


#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/***************************************************************************//**
 Function Name      : Wdg_76_Acw_Trigger                                    
                                                                            
 Service ID         : NA                                                    
                                                                            
 Description        : Watchdog triggering routine                           
                                                                            
 Sync/Async         : Synchronous                                           
                                                                            
 Re-entrancy        : Non Reentrant                                         
                                                                             
 @param [Input]     : None                                             
                                                                            
 @param [InOut]     : None                                                  
                                                                            
 @param [Output]    : None                                                  
                                                                       
 @return            : None                                                  
                                                                               
 @pre               : None

 @ingroup           : Trigger-Function
 
 Remarks            : Global Variable(s) :\n                                
                      Wdg_76_Acw_GddLevel,\n                                  
                      Wdg_76_Acw_DioChannel\n                                 
                                                                            
                      Function(s) invoked :\n                                 
                      Dio_WriteChannel\n                                      
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.7 [Not a Defect] 
                                          "it is called for test application" */
FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_Trigger(void)
/* polyspace-end<MISRA-C3:8.7 */
{
  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> status check */
  #if (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON)
  if (Wdg_76_Acw_GddLevel == (Dio_LevelType)STD_HIGH)
  {
    Wdg_76_Acw_GddLevel = (Dio_LevelType)STD_LOW;
  }
  else
  {
    Wdg_76_Acw_GddLevel = (Dio_LevelType)STD_HIGH;
  }
  Dio_WriteChannel(Wdg_76_Acw_DioChannel, Wdg_76_Acw_GddLevel);
  #endif /* (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON) */
  
  #if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON)
  if (Wdg_76_Acw_GddLevel == (Dio_LevelType)STD_HIGH)
  {
    Wdg_76_Acw_GddLevel = (Dio_LevelType)STD_LOW;
  }
  else
  {
    Wdg_76_Acw_GddLevel = (Dio_LevelType)STD_HIGH;
  }
  Dio_WriteChannel(Wdg_76_Acw_DioChannel, Wdg_76_Acw_GddLevel);
  #endif /* (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON) */
    
  #if (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
  #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
  if (Wdg_76_Acw_ArisuCanTrigger() != E_OK)
  {
    (void)Det_ReportError(WDG_76_ACW_MODULE_ID, Wdg_76_Acw_InstanceId,
      WDG_76_ACW_CBK_TRIGGER_SID, WDG_76_ACW_E_TRIGGER_FAIL);
  }
  #else /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
  (void)Wdg_76_Acw_ArisuCanTrigger();
  #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
  #endif /* (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON) */
  /* polyspace:end<RTE:UNR> */
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"


#if (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/***************************************************************************//**
 Function Name      : Wdg_76_Acw_ArisuCanTrigger                            
                                                                            
 Service ID         : NA                                                    
                                                                            
 Description        : Triggering ArisuCan watchdog                          
                                                                            
 Sync/Async         : Synchronous                                           
                                                                            
 Re-entrancy        : Non Reentrant                                         
                                                                             
 @param [Input]     : None                                             
                                                                            
 @param [InOut]     : None                                                  
                                                                            
 @param [Output]    : None                                                  
                                                                       
 @return            : Std_ReturnType                                                  
                                                                               
 @pre               : None

 @ingroup           : Trigger-Function
 
 Remarks            : Global Variable(s) :\n                                  
                      ArisuCan_GddSBCMode,\n                                  
                      Wdg_76_Acw_GddArisuCanCfg,\n                            
                      Wdg_76_Acw_GddArisuCanSpiDestData\n                     
                                                                            
                      Function(s) invoked :\n                                 
                      ArisuCan_SendSPI\n                                      
*******************************************************************************/
FUNC(Std_ReturnType, WDG_76_ACW_CODE) Wdg_76_Acw_ArisuCanTrigger(void)
{
  Std_ReturnType LddReturnvalue = (Std_ReturnType)E_NOT_OK;
  Spi_DataType LaaSpiSrcData[WDG_76_TWO];
    
  switch (sizeof(Spi_DataType))
  {
  case WDG_76_ONE:
    LaaSpiSrcData[WDG_76_ZERO] = (Spi_DataType)(((Wdg_76_Acw_GddArisuCanCfg.TriggerData) >> 8) & (uint8)0xFF);
    LaaSpiSrcData[WDG_76_ONE] = (Spi_DataType)((Wdg_76_Acw_GddArisuCanCfg.TriggerData) & (uint8)0xFF);
    break;
  case WDG_76_TWO:
    LaaSpiSrcData[WDG_76_ZERO] = (Spi_DataType)(Wdg_76_Acw_GddArisuCanCfg.TriggerData);
    break;
  case WDG_76_FOUR:
    LaaSpiSrcData[WDG_76_ZERO] = (Spi_DataType)(Wdg_76_Acw_GddArisuCanCfg.TriggerData);
    break;
  default:
    break;
  }


  switch (CanTrcv_ArisuCan_GetInternalSBCMode())
  {
  case ARISUCAN_SBCMODE_INIT:
  /*
  polyspace:start<MISRA-C:11.4:Not a defect:Justify with annotations> This conversion is explicit. 
  */
  case ARISUCAN_SBCMODE_NORMAL:
    LddReturnvalue = ArisuCan_SendSPI((const uint16*) LaaSpiSrcData,
      (uint16*) &Wdg_76_Acw_GddArisuCanSpiDestData);
    break;
  case ARISUCAN_SBCMODE_STOP:
    if ((Wdg_76_Acw_GddArisuCanCfg.TriggerData
      & (uint16)WDG_76_ACW_ARISUCAN_WD_CTRL_WD_STM_EN_0_BIT)
      != (uint16)WDG_76_ACW_ARISUCAN_WD_CTRL_WD_STM_EN_0_BIT)
    {
      LddReturnvalue = ArisuCan_SendSPI((const uint16*) LaaSpiSrcData,
        (uint16*) &Wdg_76_Acw_GddArisuCanSpiDestData);
    }
    break;
  case ARISUCAN_SBCMODE_SLEEP:
  case ARISUCAN_SBCMODE_RESTART:
  default:
    break;
  }
  /*
  polyspace:start<MISRA-C:11.4:Not a defect:Justify with annotations> This conversion is explicit. 
  */

  return LddReturnvalue;
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON) */


#if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON)
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/***************************************************************************//**
 Function Name      : Wdg_76_Acw_MPQ6411_Shutdown                           
                                                                            
 Service ID         : NA                                                    
                                                                            
 Description        : Prepare the Reset Sequence when using MPQ6411         
                                                                            
 Sync/Async         : Synchronous                                           
                                                                            
 Re-entrancy        : Non Reentrant                                         
                                                                             
 @param [Input]     : None                                             
                                                                            
 @param [InOut]     : None                                                  
                                                                            
 @param [Output]    : None                                                  
                                                                       
 @return            : Std_ReturnType                                                  
                                                                               
 @pre               : None

 @ingroup           : Trigger-Function
 
 Remarks            : Global Variable(s) :\n 
                      Wdg_76_Acw_Shutdown\n                                  
                                                                            
                                                                            
                      Function(s) invoked : \n
                      Wdg_76_Acw_GetNextGptTick,\n  
                      Dio_WriteChannel,\n
                      Gpt_StopTimer,\n
                      Gpt_DisableNotification,\n
                      Gpt_EnableNotification,\n
                      Gpt_StartTimer                   
                                                                            
*******************************************************************************/
FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_MPQ6411_Shutdown(void)
{
  
  if ((Wdg_76_Acw_Shutdown == TRUE) && \
      (Wdg_76_Acw_GddLevel == (Dio_LevelType)STD_HIGH)) 
  {
    if (Wdg_76_Acw_GddLevel_Mode == (Dio_LevelType)STD_LOW)
    {
      Wdg_76_Acw_GddLevel_Mode = (Dio_LevelType)STD_HIGH;
      Dio_WriteChannel(Wdg_76_Acw_DioModeChannel,Wdg_76_Acw_GddLevel_Mode);      
    }

    else
    {
      Dio_WriteChannel(Wdg_76_Acw_DioModeChannel,(Dio_LevelType)STD_HIGH);
    }
    
    Gpt_StopTimer(Wdg_76_Acw_GptChannel);
    Gpt_DisableNotification(Wdg_76_Acw_GptChannel);
  }
  else
  {
    Gpt_ValueType LddNextGptTick = 0;
    LddNextGptTick = Wdg_76_Acw_GetNextGptTick(TRUE);
    
    Gpt_StopTimer(Wdg_76_Acw_GptChannel);
    Gpt_DisableNotification(Wdg_76_Acw_GptChannel);
  
    Gpt_EnableNotification(Wdg_76_Acw_GptChannel);
    Gpt_StartTimer(Wdg_76_Acw_GptChannel, LddNextGptTick);
    
    Wdg_76_Acw_Shutdown = TRUE;
  }
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON) */
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/*
  polyspace:end<MISRA-C:19.1:Not a defect:Justify with annotations> Needed for memory section
*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
