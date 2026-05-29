/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComM_Nm.c                                                     **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of ComM Nm Indication APIs                          **
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
** 1.9.5     08-Dec-2020   Jongsun Lim #25703                                 **
** 1.9.3     11-Sep-2020   JS Lim      #25554                                 **
** 1.9.0     22-Aug-2019   JS Lim      #18922                                 **
** 1.8.0     23-Oct-2018   JS Lim      #13653                                 **
** 1.0.7     24-Aug-2015   KT Kim      #2998                                  **
** 1.0.6     04-Jul-2013   Daejun Park CR~129, XAR~581 : Bug fix              **
**                                     -Fix the wrong use of array index      ** 
** 1.0.5     19-Jun-2013   Daejun Park CR~120, XAR~559 : Bug fix              **
**                                     -Prevent ComM from switching to        ** 
**                                      NO_COMM while Nm requested            **
** 1.0.0     12-Apr-2013   Daejun Park Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "ComM_Internal.h" /* ComM Internal functions header file */
#include "ComM_Nm.h"              /* Nm callback header file */
#include "ComM_Ram.h"             /* ComM global Ram variables header file */
#include "SchM_ComM.h"            /* SchM data protection API header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COMM_NM_C_AR_RELEASE_MAJOR_VERSION    4
#define COMM_NM_C_AR_RELEASE_MINOR_VERSION    0
#define COMM_NM_C_AR_RELEASE_REVISION_VERSION 3

/* Software Version Information */
#define COMM_NM_C_SW_MAJOR_VERSION            1
#define COMM_NM_C_SW_MINOR_VERSION            10

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (COMMNM_AR_RELEASE_MAJOR_VERSION != COMM_NM_C_AR_RELEASE_MAJOR_VERSION)
#error "ComM_Nm.c : Mismatch in Specification Major Version"
#endif
#if (COMMNM_AR_RELEASE_MINOR_VERSION != COMM_NM_C_AR_RELEASE_MINOR_VERSION)
#error "ComM_Nm.c : Mismatch in Specification Minor Version"
#endif
#if(COMMNM_AR_RELEASE_REVISION_VERSION != COMM_NM_C_AR_RELEASE_REVISION_VERSION)
   #error "ComM_Nm.c : Mismatch in Specification Revision Version"
#endif
#if (COMMNM_SW_MAJOR_VERSION != COMM_NM_C_SW_MAJOR_VERSION)
#error "ComM_Nm.c : Mismatch in Software Major Version"
#endif
#if (COMMNM_SW_MINOR_VERSION != COMM_NM_C_SW_MINOR_VERSION)
#error "ComM_Nm.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_Nm_NetworkStartIndication                      **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : Indicates that a Nm message has been received       **
**                        in the Bus sleep mode                               **
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
**                        ComM_GaaChannelMapArray[], ComM_GaaNmIndication[]   **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_NM_INDICATION_PROTECTION(),         **
**                        SchM_Exit_ComM_NM_INDICATION_PROTECTION()           **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
ComM_Nm_NetworkStartIndication(NetworkHandleType Channel)
{
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Variable to store E_OK or E_NOT_OK or COMM_UNINIT */
  Std_ReturnType LddStdRetVal;
  #endif

  /* Variable to store channel */
  NetworkHandleType LddChannelIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  LddStdRetVal = ComM_ChannelDETCheck(Channel,
    COMM_NM_NETWORKSTARTINDICATION_SID);

  /* Check, if no development error occurred */
  if (LddStdRetVal == E_OK)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
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
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace<RTE: OBAI : Not a defect:Justified > 
                                        Its boundary is pre-defined           */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and 
    validated by DET */                                        
    ComM_GaaNmIndication[LddChannelIndex] = COMM_NMSTART_IND;
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    ComM_GaaNmRequestProcessing[LddChannelIndex] = COMM_FALSE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
  }
} /* End of ComM_Nm_NetworkStartIndication(NetworkHandleType Channel) */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_Nm_NetworkMode                                 **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : Indicates Network Management has entered Network    **
**                        Mode                                                **
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
**                        ComM_GaaChannelMapArray[], ComM_GaaNmIndication[]   **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_NM_INDICATION_PROTECTION(),         **
**                        SchM_Exit_ComM_NM_INDICATION_PROTECTION()           **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
ComM_Nm_NetworkMode(NetworkHandleType Channel)
{
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType LddStdRetVal;
  #endif

  /* Variable to store channel */
  NetworkHandleType LddChannelIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  LddStdRetVal = ComM_ChannelDETCheck(Channel, COMM_NM_NETWORKMODE_SID);

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
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace<RTE: OBAI : Not a defect:Justified > 
                                        Its boundary is pre-defined  */    
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and 
    validated by DET */                                    
    ComM_GaaNmIndication[LddChannelIndex] = COMM_NMMODE_IND;
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    ComM_GaaNmRequestProcessing[LddChannelIndex] = COMM_FALSE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();

    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
  }
} /* End of ComM_Nm_NetworkMode(NetworkHandleType Channel) */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_Nm_PrepareBusSleepMode                         **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : Indicates Network Management has entered Prepare Bus**
**                        Sleep Mode                                          **
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
**                        ComM_GaaChannelMapArray[], ComM_GaaNmIndication[]   **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_NM_INDICATION_PROTECTION(),         **
**                        SchM_Exit_ComM_NM_INDICATION_PROTECTION()           **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
ComM_Nm_PrepareBusSleepMode(NetworkHandleType Channel)
{
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType LddStdRetVal;
  #endif

  /* Variable to store channel */
  NetworkHandleType LddChannelIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  LddStdRetVal = ComM_ChannelDETCheck(Channel, COMM_NM_PREPAREBUSSLEEPMODE_SID);

  /* Check, if no development error occurred */
  if (LddStdRetVal == E_OK)
  #endif
  {
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
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace<RTE: OBAI : Not a defect:Justified > 
                                        Its boundary is pre-defined */    
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and 
    validated by DET */                                    
    ComM_GaaNmIndication[LddChannelIndex] = COMM_PREPBUSSLEEPMODE_IND;
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    ComM_GaaNmRequestProcessing[LddChannelIndex] = COMM_FALSE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
  }
} /* End of ComM_Nm_PrepareBusSleepMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_Nm_BusSleepMode                                **
**                                                                            **
** Service ID           : 0x1a                                                **
**                                                                            **
** Description          : Indication that network management has entered      **
**                        Bus Sleep Mode                                      **
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
**                        ComM_GaaChannelMapArray[], ComM_GaaNmIndication[]   **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_NM_INDICATION_PROTECTION(),         **
**                        SchM_Exit_ComM_NM_INDICATION_PROTECTION()           **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
ComM_Nm_BusSleepMode(NetworkHandleType Channel)
{
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType LddStdRetVal;
  #endif

  /* Variable to store the channel */
  NetworkHandleType LddChannelIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if channel is valid or not */
  LddStdRetVal = ComM_ChannelDETCheck(Channel, COMM_NM_BUSSLEEPMODE_SID);

  /* Check, if no development error occurred */
  if (LddStdRetVal == E_OK)
  #endif
  {
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
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace<RTE: OBAI : Not a defect:Justified > 
                                        Its boundary is pre-defined  */    
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and 
    validated by DET */                                    
    ComM_GaaNmIndication[LddChannelIndex] = COMM_BUSSLEEPMODE_IND;
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    ComM_GaaNmRequestProcessing[LddChannelIndex] = COMM_FALSE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
  }
} /* End of ComM_Nm_BusSleepMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_Nm_RestartIndication                           **
**                                                                            **
** Service ID           : 0x1b                                                **
**                                                                            **
** Description          : Indicates that the Transmission of NM-messages      **
**                        has failed in Network mode                          **
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
** Preconditions        : ComM shall be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaChannelMapArray[], ComM_GaaNmIndication[]   **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_NM_INDICATION_PROTECTION(),         **
**                        SchM_Exit_ComM_NM_INDICATION_PROTECTION()           **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
ComM_Nm_RestartIndication(NetworkHandleType Channel)
{
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType LddStdRetVal;
  #endif

  /* Variable to store the channel*/
  NetworkHandleType LddChannelIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  LddStdRetVal = ComM_ChannelDETCheck(Channel, COMM_NM_RESTARTINDICATION_SID);

  /* Check, if no development error occurred */
  if (LddStdRetVal == E_OK)
  #endif
  {
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
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace<RTE: OBAI : Not a defect:Justified > 
                                        Its boundary is pre-defined */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and 
    validated by DET */                                    
    ComM_GaaNmIndication[LddChannelIndex] = COMM_NMRST_IND;
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    ComM_GaaNmRequestProcessing[LddChannelIndex] = COMM_FALSE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
  }
} /* End of ComM_Nm_RestartIndication */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

