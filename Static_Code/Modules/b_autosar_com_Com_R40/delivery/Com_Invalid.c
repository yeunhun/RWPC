/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Com_Invalid.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of invalidate and update functions                  **
**              functionality.                                                **
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
** 2.6.0     10-Sep-2020   SM Kwon     Internal Redmine #25250                **
** 2.4.0     25-Jan-2019   SM Kwon     Internal Redmine #14789                **
** 2.2.3     08-Dec-2017   Chan Kim    Internal Redmine #10849, #10851        **
** 2.2.0     16-Apr-2017   Chan Kim    Internal Redmine #7525                 **
** 2.1.4     26-Jul-2016   Chan Kim    Internal Redmine #5687                 **
** 2.1.0     25-May-2016   Chan Kim    Internal Redmine #4998                 **
** 2.0.3     24-Nov-2015   Chan Kim    Internal Redmine #3544, #3535          **
** 1.0.11    03-Mar-2014   Chan Kim    Internal Redmine #642                  **
** 1.0.0     29-Apr-2013   Autron      Initial Version                        **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.14 [Not a defect: Justify with annotations] "Function call depends on the configured Invalid values" */
/* polyspace-begin MISRA-C3:18.1 [Not a defect: Justify with annotations] "Genderated array index in range" */
/* polyspace-begin RTE:IDP [Not a defect: Justify with annotations] "Configured memory access index" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_Invalid.h"  /* Com Invalid header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define COM_INVALID_C_AR_RELEASE_MAJOR_VERSION       4
#define COM_INVALID_C_AR_RELEASE_MINOR_VERSION       0
#define COM_INVALID_C_AR_RELEASE_REVISION_VERSION    3

/* Software Version Information */
#define COM_INVALID_C_SW_MAJOR_VERSION  2
#define COM_INVALID_C_SW_MINOR_VERSION  7

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (COM_AR_RELEASE_MAJOR_VERSION != COM_INVALID_C_AR_RELEASE_MAJOR_VERSION)
  #error "Com_Invalid.c : Mismatch in Com Specification Major Version"
#endif

#if (COM_AR_RELEASE_MINOR_VERSION != COM_INVALID_C_AR_RELEASE_MINOR_VERSION)
  #error "Com_Invalid.c : Mismatch in Com Specification Minor Version"
#endif

#if(COM_AR_RELEASE_REVISION_VERSION !=COM_INVALID_C_AR_RELEASE_REVISION_VERSION)
  #error "Com_Invalid.c : Mismatch in Com Specification Revision Version"
#endif

#if (COM_SW_MAJOR_VERSION != COM_INVALID_C_SW_MAJOR_VERSION)
  #error "Com_Invalid.c : Mismatch in Com Software Major Version"
#endif

#if (COM_SW_MINOR_VERSION != COM_INVALID_C_SW_MINOR_VERSION)
  #error "Com_Invalid.c : Mismatch in Com Software Minor Version"
#endif


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_Invalid_8                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs invalidation check on the    **
**                        signal and returns true if signal is invalid.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Invalid_8
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2CONST(void, AUTOMATIC, COM_CONST) LpTarget,
  PduLengthType LddSize)
{
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_TRUE;
  /* Check whether invalid data is not equal to signal data */
  if((*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpTarget) !=
                      (*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* Set return value to false */
    LblReturnValue = COM_FALSE;
  }

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Invalid_16                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs invalidation check on the    **
**                        signal and returns true if signal is invalid.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Invalid_16
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2CONST(void, AUTOMATIC, COM_CONST) LpTarget,
  PduLengthType LddSize)
{
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_TRUE;
  /* Check whether invalid data is not equal to signal data */
  if((*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpTarget) !=
                     (*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* Set return value to false */
    LblReturnValue = COM_FALSE;
  }

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Invalid_32                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs invalidation check on the    **
**                        signal and returns true if signal is invalid.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Invalid_32
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2CONST(void, AUTOMATIC, COM_CONST) LpTarget,
  PduLengthType LddSize)
{
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_TRUE;
  /* Check whether invalid data is not equal to signal data */
  if((*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpTarget) !=
                     (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* Set return value to false */
    LblReturnValue = COM_FALSE;
  }

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Invalid_64                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs invalidation check on the    **
**                        signal and returns true if signal is invalid.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Invalid_64
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2CONST(void, AUTOMATIC, COM_CONST) LpTarget,
  PduLengthType LddSize)
{
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpDest;
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpSrc;
  boolean LblReturnValue;
  uint16 LusBufferIndex;

  LusBufferIndex = (uint16)COM_ZERO;
  LpDest = (P2CONST(uint32, AUTOMATIC, COM_CONST)) LpTarget;
  LpSrc = (P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource;
  /* Set return value to false */
  LblReturnValue = COM_FALSE;

  /* Check whether invalid data is not equal to signal data */
  if((LpDest[LusBufferIndex]) == (LpSrc[LusBufferIndex]))
  {
    LusBufferIndex++;
    if((LpDest[LusBufferIndex]) == (LpSrc[LusBufferIndex]))
    {
      LblReturnValue = COM_FALSE;
    }
  }

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Invalid_NBytes                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs invalidation check on the    **
**                        signal and returns true if signal is invalid.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_Invalid_NBytes
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                        P2CONST(void, AUTOMATIC, COM_CONST) LpTarget,
                                                          PduLengthType LddSize)
{
  boolean LblReturnValue;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpTargetPtr;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSourcePtr;
  uint16 LusBufferIndex;
  PduLengthType LddSigSize;

  LusBufferIndex = (uint16)COM_ZERO;
  /* Initialize return value to true */
  LblReturnValue = COM_TRUE;
  /* Get the pointer to destination buffer */
  LpTargetPtr = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpTarget;
  /* Get the pointer to source buffer */
  LpSourcePtr = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource;
  /* Get the size of this signal */
  LddSigSize = LddSize;
  
  /* Loop to check whether the data is invalid or not, based on signal size */
  do
  {
    /* Decrement signal size */
    LddSigSize--;
    /* Check whether invalid data is not equal to signal data */
    if(LpTargetPtr[LusBufferIndex] != LpSourcePtr[LusBufferIndex])
    {
      /* Set return value to false */
      LblReturnValue = COM_FALSE;
      /* Set signal size to zero */
      LddSigSize = (PduLengthType)COM_ZERO;
    }
    LusBufferIndex++;
  }while(LddSigSize != (PduLengthType)COM_ZERO);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end MISRA-C3:D4.14 [Not a defect: Justify with annotations] "Function call depends on the configured Invalid values" */
/* polyspace-end MISRA-C3:18.1 [Not a defect: Justify with annotations] "Genderated array index in range" */
/* polyspace-end RTE:IDP [Not a defect: Justify with annotations] "Configured memory access index" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
