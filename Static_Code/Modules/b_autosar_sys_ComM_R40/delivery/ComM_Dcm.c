/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComM_Dcm.c                                                    **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of ComM Dcm Indication APIs                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.10.1    27-Sep-2021   Jongsun Lim #32237                                 **
** 1.9.5     08-Dec-2020   Jongsun Lim #25703                                 **
** 1.9.0     22-Aug-2019   JS Lim      #18922, #25554                         **
** 1.8.0     23-Oct-2018   JS Lim      #13653                                 **
** 1.7.16    19-Jul-2018   Chan Kim    #11240                                 **
** 1.0.1     24-Aug-2015   KT Kim      Code change for Run Time Error         **
**                                     (#2998)                                **
** 1.0.0     17-Dec-2012   KT Kim      Initial version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM.h"
#include "ComM_Dcm.h"
#include "ComM_Ram.h"
#include "SchM_ComM.h"
#include "ComM_Internal.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COMM_DCM_C_AR_RELEASE_MAJOR_VERSION    4
#define COMM_DCM_C_AR_RELEASE_MINOR_VERSION    0
#define COMM_DCM_C_AR_RELEASE_REVISION_VERSION 3

/* Software Version Information */
#define COMM_DCM_C_SW_MAJOR_VERSION            1
#define COMM_DCM_C_SW_MINOR_VERSION            10

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (COMMDCM_AR_RELEASE_MAJOR_VERSION != COMM_DCM_C_AR_RELEASE_MAJOR_VERSION)
#error "ComM_Dcm.c : Mismatch in Specification Major Version"
#endif
#if (COMMDCM_AR_RELEASE_MINOR_VERSION != COMM_DCM_C_AR_RELEASE_MINOR_VERSION)
#error "ComM_Dcm.c : Mismatch in Specification Minor Version"
#endif
#if (COMMDCM_AR_RELEASE_REVISION_VERSION !=\
     COMM_DCM_C_AR_RELEASE_REVISION_VERSION)
#error "ComM_Dcm.c : Mismatch in Specification Revision Version"
#endif
#if (COMMDCM_SW_MAJOR_VERSION != COMM_DCM_C_SW_MAJOR_VERSION)
#error "ComM_Dcm.c : Mismatch in Software Major Version"
#endif
#if (COMMDCM_SW_MINOR_VERSION != COMM_DCM_C_SW_MINOR_VERSION)
#error "ComM_Dcm.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_DCM_ActiveDiagnostic                           **
**                                                                            **
** Service ID           : 0x1f                                                **
**                                                                            **
** Description          : Indication of Active Diagnostic by the DCM          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaDcmActiveDiagnostic[],                      **
**                        ComM_GaaChannelMapArray[], ComM_GaaTimeCnt[]        **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION(),        **
**                        SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION()          **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
ComM_DCM_ActiveDiagnostic(NetworkHandleType Channel)
{
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType LddStdRetVal;
  #endif

  /* Variable to store channel */
  NetworkHandleType LddChannelIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  LddStdRetVal = ComM_ChannelDETCheck(Channel, COMM_DCM_ACTIVEDIAGNOSTIC_SID);

  /* Check, if no development error occurred */
  if (LddStdRetVal == E_OK)
  #endif
  {
    /* Check If Binary Search Is Enabled*/
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not a NULL and valid */ 
    LddChannelIndex = ComM_GaaChannelMapArray[Channel];
    #else

    /* Channel Id is updated into local variable */
    LddChannelIndex = Channel;
    #endif
    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
    /* Enter Data Protection */
    SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace<RTE: OBAI : Not a defect:Justified > 
                                        Its boundary is pre-defined */

    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and 
    validated by DET */

    ComM_GaaDcmActiveDiagnostic[LddChannelIndex] = COMM_TRUE;
    ComM_GaaDcmInactiveDiagnostic[LddChannelIndex] = COMM_FALSE;

    /* Exit Data Protection */
    SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
    #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
    (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

    /* Start the Min amount of duration in full Communication counter */
    ComM_GaaTimeCnt[LddChannelIndex] = (ComM_TimeType)COMM_ZERO;
    #endif
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
  }
} /* End of ComM_DCM_ActiveDiagnostic */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_DCM_InactiveDiagnostic                         **
**                                                                            **
** Service ID           : 0x20                                                **
**                                                                            **
** Description          : Indication of Inactive Diagnostic                   **
**                        by the DCM                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaChannelMapArray[],                          **
**                        ComM_GaaDcmInactiveDiagnostic[]                     **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck()                              **
**                        SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION()         **
**                        SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION()          **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
ComM_DCM_InactiveDiagnostic(NetworkHandleType Channel)
{
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType LddStdRetVal;
  #endif

  /* Variable to store channel */
  NetworkHandleType LddChannelIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  LddStdRetVal = ComM_ChannelDETCheck(Channel, COMM_DCM_INACTIVEDIAGNOSTIC_SID);

  /* Check, if no development error occurred */
  if (LddStdRetVal == E_OK)
  #endif
  {
    /* Check If Binary Search Is Enabled*/
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not a NULL and valid */ 
    LddChannelIndex = ComM_GaaChannelMapArray[Channel];
    #else

    /* Channel Id is updated into local variable */
    LddChannelIndex = Channel;
    #endif

    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
    /* Enter Data Protection */
    SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace<RTE: OBAI : Not a defect:Justified > 
                                        Its boundary is pre-defined  */  
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and 
    validated by DET */                                        

    if(ComM_GaaDcmActiveDiagnostic[LddChannelIndex] == COMM_TRUE)
    {
      ComM_GaaDcmInactiveDiagnostic[LddChannelIndex] = COMM_TRUE;
    }else{
      /* Default value of ComM_GaaDcmInactiveDiagnostic is COMM_FALSE */
      ComM_GaaDcmInactiveDiagnostic[LddChannelIndex] = COMM_FALSE;
    }

    /* Exit Data Protection */
    SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
  }
} /* End of ComM_DCM_InactiveDiagnostic */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

