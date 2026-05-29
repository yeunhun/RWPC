/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_CddIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of CDD interface Functionality                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date:DD-MM-YYYY By            Description                         **
********************************************************************************
** 1.2.1    04-09-2020   EunKyung.Kim   Changes made As per Redmine #25254    **
**                                                                            **
** 1.2.0    10-12-2018    EunKyung.Kim   Changes made As per Redmine #8561    **
**                                                                            **
** 1.0.1    20-07-2017    EunKyung.Kim   Changes made As per Redmine #9294    **
**                                                                            **
** 1.0.0    06-02-2017      yj.yun        #7379                               **
*******************************************************************************/ 

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"
#include "Dem_Ram.h"
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "NvM.h"              /* NVRAM manager symbols Header File */
#if (DEM_TRIGGER_DLT_REPORTS == STD_ON)
#include "Dlt.h"
#endif
#include "SchM_Dem.h"
#include "Rte_Dem.h"

#include "Dem_NvData.h"
#include "Dem_Event.h"
#include "Dem_EventRelatedData.h"
#include "Dem_EventCallback.h"
#include "Dem_Indicator.h"
#include "Dem_EventDebounce.h"
#include "Dem_Dtc.h"
#include "Dem_EventAging.h"
#include "Dem_EventMemory.h"


/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dem_CddClearDTC                                     **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This API shall be used to clear single DTC's as     **
**                        well as group of DTC's                              **
**                                                                            **
** Sync/Async           : Synchronous/Asynchronous                            **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DTC, DTCFormat, DTCOrigin                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_CddClearDTC(uint32 DTC,
  Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
  Dem_ReturnClearDTCType retVal = DEM_CLEAR_FAILED;

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  if ((DEM_CLEARDTC_STATE_USER_DCM == Dem_ClearDtcState.cds_User) ||
    (DEM_CLEARDTC_STATE_USER_J1939DCM == Dem_ClearDtcState.cds_User))
  {
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    retVal = DEM_CLEAR_PENDING; /* It means 'busy' state */
  }
  else /* DEM_CLEARDTC_STATE_USER_CDD or IDLE */
  {
    Dem_ClearDtcState.cds_User = DEM_CLEARDTC_STATE_USER_CDD;
#if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
    Dem_ClearDtcState.cds_DTCTypeFilter = 0U;   /* Not used */
#endif
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    
    retVal = Dem_InternalClearDTC(DTC, DTCFormat, DTCOrigin);
    if (DEM_CLEAR_PENDING != retVal)
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();    
      Dem_ClearDtcState.cds_User = DEM_CLEARDTC_STATE_USER_IDLE;
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
  }

  return retVal;
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

