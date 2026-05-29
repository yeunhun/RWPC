/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_GetProfileData.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Implementation of GetProfileData module                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.5.4     14-Dec-2021    YH.Han        Redmine #33448, #33412              **
** 1.3.0     29-Oct-2018    YH.Han        Redmine #12853                      **
** 1.1.0     30-Nov-2016    SH.Yoo        Redmine #6816                       **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_GetProfileData.h"
#include "Opf_Ram.h"
#include "Opf_Task.h"
#include "Opf_Port.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OPF_START_SEC_CODE
#include "MemMap.h"

/***************************************************************************//**
 * Function             : Opf_GetTaskInfo
 *
 * Service ID           : NA
 *
 * Description          : This function is called to get task information
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LddTaskID    Profile target task id
 *
 * @return              : Tdd_Opf_ProfileTaskInfo *
 *
 * @pre                 : Opf_InitEventQueue() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GaaProfileTaskInfo
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-004, OPF-SRS-FUN-010, OPF-SRS-FUN-012,
 *                        OPF-SRS-FUN-014, OPF-SRS-FUN-016
 ******************************************************************************/
/* polyspace-begin MISRA-C3:20.7 [Not a Defect] "AUTOSAR compiler abstraction" */
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
FUNC(Tdd_Opf_ProfileTaskInfo *, OPF_CODE) Opf_GetTaskInfo(uint16 LddTaskID)
/* polyspace-end MISRA-C3:20.7 */
/* polyspace-end MISRA-C3:D4.5 */
{
  Tdd_Opf_ProfileTaskInfo* pProfileTaskInfo = OPF_NULL;
  OpfTaskInfoIdxType LddListIdx;
  OpfTaskIDType LddTID;
  
  LddTID = Opf_PortGetObjID(LddTaskID);

  /* Verify task is eligible for profiling */
  Opf_ValidateTask(LddTID);

  /* If valid task, add that event into event queue */
  if((OPF_ISVALID_TASK(LddTID)) == TRUE)
  {
    LddListIdx = Opf_GaaTaskCache[LddTID].ddIndex;
    pProfileTaskInfo = &(Opf_GaaProfileTaskInfo[LddListIdx]);
  }

  return pProfileTaskInfo;
}

/***************************************************************************//**
 * Function             : Opf_GetProfileInfo
 *
 * Service ID           : NA
 *
 * Description          : This function is called to get profile information
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : Opf_InitEventQueue() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddProfileEventQ
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-008
 ******************************************************************************/
/* polyspace-begin MISRA-C3:20.7 [Not a Defect] "AUTOSAR compiler abstraction" */
FUNC(Tdd_Opf_ProfileEventQ *, OPF_CODE) Opf_GetProfileInfo(void)
/* polyspace-end MISRA-C3:20.7 */
{
  Tdd_Opf_ProfileEventQ* pProfileEventQ;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_ProfileEventQ *pCoreProfileEventQ;

  /* polyspace:begin<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreProfileEventQ = OPF_GET_PROFILE_EVENTQ_INFO(LddCoreID);
  /* polyspace:end<RTE: OBAI : Not a defect : Justify with annotations > configured array index */
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* Get profiled event queue */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  pProfileEventQ = pCoreProfileEventQ;
  #else
  pProfileEventQ = &Opf_GddProfileEventQ;
  #endif

  return pProfileEventQ;
}

#define OPF_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
