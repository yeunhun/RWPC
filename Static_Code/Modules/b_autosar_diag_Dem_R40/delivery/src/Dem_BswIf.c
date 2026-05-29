/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_BswIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of Bsw error report functionality                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.0.9    12-08-2020   EunKyung.Kim   Changes made As per Redmine #25205,   **
**                                      #25454                                **
**                                                                            **    
** 1.0.8    09-11-2018   EunKyung.Kim   Changes made As per Redmine #14481    **
**                                                                            **
** 1.0.7    20-07-2017   EunKyung.Kim   Changes made As per Redmine #9294     **
**                                                                            **
** 1.0.6    16-04-2015   Sungeol Baek     As per reminde #2171                **
**                                           MISRA Rule modification          **
** ---------------------------------------------------------------------------**
** 1.0.5     04-Dec-2014   YJ.Yun      Modified the type for const variables  **
**                                     (Dem_EventParameterPCType..            **
**                                     Changed the init method for local      **
**                                     variables                              **
** ---------------------------------------------------------------------------**
** 1.0.4     11-Jan-2014   YJ.Yun      Changes made As per Redmine #366,#367, **
**                                     #368,#371,#372,#405,#366,#367,#368,    **
**                                     #371,#372,#405,#369,#373,#374,#375,    **
**                                     #376,#370,#377,#381,#382,#383,#384,    **
**                                     #385,#386,#387,#388,#389,#390,#391,    **
**                                     #397,#398,#399,#400,#378,#380,#401,    **
**                                     #403,#404,#406,#409,#410,#411,#412     **
** ---------------------------------------------------------------------------**
** 1.0.0     01-Jan-2013   Autron      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"            /* DEM module Header File */
#include "Dem_Ram.h"        /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"            /* Det Module Header File */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */
#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "Dem_Event.h"

/* polyspace-begin RTE:UNR [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Dem_ReportErrorStatus                               **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : Interface for BSW Components to report Errors       **
**                        during start up (even before DEM initialization)    **
**                        and normal operation.                               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId,                                            **
**                        EventStatus                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_ReportErrorStatus(
  /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */	
  Dem_EventIdType EventId, 
  Dem_EventStatusType EventStatus)
{ 
  if(DEM_UNINIT == Dem_GucInit)
  /* polyspace<RTE:UNR:Not a defect:No action planned> The parameters shall be checked according to the Dem specification */
  {
    DEM_REPORT_ERROR(DEM_REPORTERRORSTATUS_SID, DEM_E_UNINIT);
  }  
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  else if ((EventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == EventId)) 
  /* else if (DEM_FALSE == Dem_EventIdIsValid(EventId)) */
  {
    DEM_REPORT_ERROR(DEM_REPORTERRORSTATUS_SID, DEM_E_PARAM_CONFIG);
  }
  else if ((boolean)DEM_FALSE == Dem_EventStatusIsValid(EventStatus))
  {
    DEM_REPORT_ERROR(DEM_REPORTERRORSTATUS_SID, DEM_E_PARAM_DATA);
  }
  else if (DEM_EVENT_KIND_BSW != Dem_GetEventKind(EventId))
  {
    DEM_REPORT_ERROR(DEM_REPORTERRORSTATUS_SID, DEM_E_PARAM_CONFIG);    
  }
  #endif    
  else
  {
    /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */	  
    Std_ReturnType result = E_OK;
    /* [SWS_Dem_00851]  
     * All  events  which  are  reported  via  Dem_ReportErrorStatus 
     * before  Dem_Init  shall  not  consider  the  state  of  the  operation  cycles. */
    if (DEM_INIT == Dem_GucInit)
    {
      /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */	
      Dem_OperationCycleStateType cycleState = (Dem_OperationCycleStateType)DEM_CYCLE_STATE_END;     

      /* [SWS_Dem_01078] If DemOperationCycleStatusStorage is set to FALSE, a call of
       * Dem_Shutdown shall end all operation cycles which are not stored in non-volatile memory.
       *
       * Note: If Power cycle (DEM_OPCYC_POWER) should not be ended/stopped during
       * 'ECU Sleep' then it should be configured with DemOperationCycleStatusStorage == TRUE. 
       *
       * if DemOperationCycleStatusStorage is true then state is stored, so Bsw Events always 
         able to be processed regardless Dem Init State */
      /*result == */(void)Dem_GetOpCycleStateByEvent(EventId, &cycleState);
      if (/*(E_NOT_OK == result) || */(DEM_CYCLE_STATE_END == cycleState))
      {
        result = E_NOT_OK;
      }
    }
    if (E_OK == result)
    {   
      #if (DEM_BSW_ERROR_BUFFER_SIZE > 0U)
	  if(DEM_PREINIT == Dem_GucInit)
	  {
		SchM_Enter_Dem_REQUEST_BEFOREOS_PROTECTION();
	  }
	  else
	  {
		SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION();
	  }

      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true */
      if (Dem_GucErrorWriteIndex < Dem_BSW_Error_Buffer_Size)
      {       
        /* Check if the error buffer is empty */      
        if (DEM_NO_EVENT == Dem_GaaErrorBuffer[Dem_GucErrorWriteIndex])
        {
          /* Load the event into the buffer */
          Dem_GaaErrorBuffer[Dem_GucErrorWriteIndex] = EventId;
          Dem_GaaErrorBufferStatus[Dem_GucErrorWriteIndex] = EventStatus;

          /* Check if the buffer is full */
          Dem_GucErrorWriteIndex++;
          if (Dem_GucErrorWriteIndex >= Dem_BSW_Error_Buffer_Size)
          {
            /* Initialize the buffer to zero */
            Dem_GucErrorWriteIndex = 0U;
          }      
        }        
      }
      if(DEM_PREINIT == Dem_GucInit)
      {
        SchM_Exit_Dem_REQUEST_BEFOREOS_PROTECTION();
      }
      else
      {
        SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();
      }
      #endif        
    }      
  }
}
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end RTE:UNR [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
