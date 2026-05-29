/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Com_UnPack.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of unpacking, invalidate and update functions       **
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
** 2.7.1     07-Jan-2021   SM Kwon     Internal redmine #27557                **
** 2.6.0     10-Sep-2020   SM Kwon     Internal Redmine #25250                **
** 2.4.0     01-Feb-2019   Chan Kim    Internal Redmine #14067                **
** 2.2.3     08-Dec-2017   Chan Kim    Internal Redmine #10849, #10851        **
** 2.2.0     16-Apr-2017   Chan Kim    Internal Redmine #7525                 **
** 2.1.4     26-Jul-2016   Chan Kim    Internal Redmine #5687                 **
** 2.1.0     25-May-2016   Chan Kim    Internal Redmine #4998                 **
** 2.0.13    13-May-2016   Chan Kim    Internal Redmine #3959                 **
** 2.0.8     12-Feb-2016   Chan Kim    Internal Redmine #4158                 **
** 2.0.3     24-Nov-2015   Chan Kim    Internal Redmine #3544, #3535          **
** 1.0.15    09-Feb-2015   Chan Kim    Internal Redmine #2142                 **
** 1.0.11    03-Mar-2014   Chan Kim    Internal Redmine #642                  **
** 1.0.9     11-Feb-2014   Chan Kim    Internal Redmine #605                  **
** 1.0.0     29-Apr-2013   Autron      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_UnPack.h"   /* Com Unpack header file */
#include "SchM_Com.h"     /* SchM Com header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COM_UNPACK_C_AR_RELEASE_MAJOR_VERSION  4
#define COM_UNPACK_C_AR_RELEASE_MINOR_VERSION  0
#define COM_UNPACK_C_AR_RELEASE_REVISION_VERSION  3

/* Software Version Information */
#define COM_UNPACK_C_SW_MAJOR_VERSION  2
#define COM_UNPACK_C_SW_MINOR_VERSION  7

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (COM_AR_RELEASE_MAJOR_VERSION != COM_UNPACK_C_AR_RELEASE_MAJOR_VERSION)
  #error "Com_Unpack.c : Mismatch in Com Specification Major Version"
#endif

#if (COM_AR_RELEASE_MINOR_VERSION != COM_UNPACK_C_AR_RELEASE_MINOR_VERSION)
  #error "Com_Unpack.c : Mismatch in Com Specification Minor Version"
#endif

#if(COM_AR_RELEASE_REVISION_VERSION != COM_UNPACK_C_AR_RELEASE_REVISION_VERSION)
  #error "Com_Unpack.c : Mismatch in Com Specification Patch Version"
#endif

#if (COM_SW_MAJOR_VERSION != COM_UNPACK_C_SW_MAJOR_VERSION)
  #error "Com_Unpack.c : Mismatch in Com Software Major Version"
#endif

#if (COM_SW_MINOR_VERSION != COM_UNPACK_C_SW_MINOR_VERSION)
  #error "Com_Unpack.c : Mismatch in Com Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/* polyspace-begin MISRA-C3:D4.14 [Not a defect: Justify with annotations] "Function call depends on the configured UnPack values" */
/* polyspace-begin MISRA-C3:18.1 [Not a defect: Justify with annotations] "Genderated array index in range" */
/* polyspace-begin MISRA-C3:11.5 [Not a defect: Justify with annotations] "Conversion perform pointer to object" */
/* polyspace-begin RTE:NIV [Not a defect: Justify with annotations] "Initialized variable" */
/* polyspace-begin RTE:SHF [Not a defect: Justify with annotations] "Amount can not be outside its bounds" */
/* polyspace-begin RTE:IDP [Not a defect: Justify with annotations] "Configured memory access index" */
/*******************************************************************************
** Function Name        : Com_UnPackOneByte                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks one byte signal from an I-PDU **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack                                          **
**                                                                            **
** Output Parameters    : LpSigDataPtr                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_UnPackOneByte
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  uint8 LucIpduData;
  uint8 LucSignMask;
  /* Get the sign mask value */
  LucSignMask = LpRxUnpack->ucRdSignMask;
  /* Enter protection area */
  /* Reduce the invoking count of Protection Area - by AUTRON START */
  /*SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();*/
  /* Get the I-PDU buffer data to a local I-PDU variable */
  LucIpduData = *(LpRxUnpack->pRdBuffer);
  /* Exit protection area */
  /*SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();*/
  /* Reduce the invoking count of Protection Area - by AUTRON END */
  /* Shift the local I-PDU variable by the number of shift bits to the get
  the start position */
  LucIpduData >>= (LpRxUnpack->ucNoOfShiftBits);
  /* Apply the end mask to local I-PDU variable to clear unoccupied area of
  signal */
  LucIpduData &= (LpRxUnpack->ucRdEndMask);
  /* Check whether the received signal is negative  */
  if((LucIpduData & LucSignMask) != COM_ZERO)
  {
    /* Perform sign conversion */
    LucIpduData |= LucSignMask;
  }
  /* Copy local I-PDU variable data to signal data pointer */
  *(P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr = LucIpduData;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackBytes                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        8 bits and spread across four bytes in an I-PDU     **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack                                          **
**                                                                            **
** Output Parameters    : LpSigDataPtr                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_UnPackBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignBuffer;
  Com_MIdWord_Access LunApplSignal;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  uint8 LucIpduBuffer;
  /* Initialize double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Get the signal size */
  LucSigTypeOrSize  = (uint8)(LpRxUnpack->ddSignalSize);
  /* Get the pointer to lower byte of double word variable and assign it to
  local application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
                                                &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  LpSignBuffer = LpApplBuffer;
  /* Get the pointer to I-PDU buffer */
  LpRdBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST))
                                                        (LpRxUnpack->pRdBuffer);
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #else
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ONE);
  /* Get the I-PDU buffer pointer data to a local Application Buffer variable */
  *LpApplBuffer = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the type/size of the signal */
  LucSigTypeOrSize = (LpRxUnpack->ucSignalType);
  /* Shift the double word variable right by the number of shift bits to get the
  start position */
  LunApplSignal.whole_dword  >>= LpRxUnpack->ucNoOfShiftBits;
  /* polyspace-begin MISRA-C3:18.4 [Not a defect: Justify with annotations] "Not an Impact" */
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  LpSignBuffer -= (Com_PtrType)LucSigTypeOrSize;
  #else
  LpSignBuffer = LpSignBuffer + (Com_PtrType)LucSigTypeOrSize;
  #endif
  /* polyspace-end MISRA-C3:18.4 [Not a defect: Justify with annotations] "Not an Impact" */
  LucIpduBuffer = *LpSignBuffer;
  /* Get the sign mask value */
  LucSignMask = LpRxUnpack->ucRdSignMask;
  /* Apply end mask */
  LucIpduBuffer &= LpRxUnpack->ucRdEndMask;
  /* Check whether the signal is negative */
  if((LucIpduBuffer & LucSignMask) != COM_ZERO)
  {
    /* Perform sign conversion */
    LucIpduBuffer |= LucSignMask;
    /* Check whether the signal size is 24 bits */
    if(COM_TYPE_24 == LucSigTypeOrSize)
    {
      /* Get sign extension to higher byte of double word variable */
      LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] = COM_SIGN_EXTENSION;
    }
  }
  else
  {
    /* Check whether the signal size is 24 bits */
    if(COM_TYPE_24 == LucSigTypeOrSize)
    {
      /* Get sign extension to higher byte of double word variable */
      LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] = COM_ZERO;
    }
  }

  /* Copy the local I-PDU buffer data to application buffer */
  *LpSignBuffer = LucIpduBuffer;
  /* Check whether the signal size is one byte */
  if(COM_TYPE_8 == LucSigTypeOrSize)
  {
    /* Copy the lower byte of double word variable to signal data pointer */
    *(P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr =
                                                 LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  }
  /* Check whether the signal size is two bytes */
  else if (COM_TYPE_16 == LucSigTypeOrSize)
  {
    /* Copy the lower word of double word variable to signal data pointer */
    *(P2VAR(uint16, AUTOMATIC, COM_VAR)) LpSigDataPtr =
                                                 LunApplSignal.word_val.BO_Word[COM_DWORD_LS_WORD_IDX];
  }
  else
  {
    /* Copy the double word variable data to signal data pointer */
    *(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpSigDataPtr =
                                                      LunApplSignal.whole_dword;
  }
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackFiveBytes                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        32 bits and spread across five bytes in an I-PDU    **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack                                          **
**                                                                            **
** Output Parameters    : LpSigDataPtr                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackFiveBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{

  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  Com_MIdWord_Access LunApplSignal;
  Com_MIWord_Access LunApplSigHi;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  /* Initialize the double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX] = COM_ZERO;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
                                                &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the pointer I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_FOUR;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #else
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);
  /* Get the I-PDU buffer pointer data to the higher byte of word variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucSignMask = LpRxUnpack->ucNoOfShiftBits;
  /* Shift the double word variable to right by the number of shift bits */
  LunApplSignal.whole_dword  >>= LucSignMask;
  /* Shift the word variable to right by the number of shift bits */
  LunApplSigHi.whole_word  >>= LucSignMask;
  /* Get the lower byte of word variable to local signal variable  */
  LucSigTypeOrSize = LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX];
  /* Apply end mask to clear unoccupied area of local signal variable */
  LucSigTypeOrSize &= LpRxUnpack->ucRdEndMask;
  /* Get the sign mask value */
  LucSignMask = LpRxUnpack->ucRdSignMask;
  /* Check whether the received signal value is negative */
  if((LucSigTypeOrSize & LucSignMask) != COM_ZERO)
  {
    /* Perform sign conversion */
    LucSigTypeOrSize  |= LucSignMask;
  }
  /* Copy the local signal variable data to higher byte of double word
  variable */
  LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] |= LucSigTypeOrSize;
  /* Copy the double word variable data to signal data pointer */
  *(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpSigDataPtr =
                                                      LunApplSignal.whole_dword;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackByteOrdering                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        8 bits, spread across four bytes in an I-PDU        **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack                                          **
**                                                                            **
** Output Parameters    : LpSigDataPtr                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_UnPackByteOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignBuffer;
  Com_MIdWord_Access LunApplSignal;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  uint8 LucIpduBuffer;
  /* Initialize double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Get the signal size */
  LucSigTypeOrSize  = (uint8)(LpRxUnpack->ddSignalSize);
  /* Get the pointer to lower byte of double word variable and assign it to
  local application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
                                                &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  LpSignBuffer = LpApplBuffer;
  /* Get the pointer to I-PDU buffer */
  LpRdBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST))
                                                        (LpRxUnpack->pRdBuffer);
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* Copy the data from I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #else
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ONE);
  /* Get the I-PDU buffer pointer data to a local I-PDU variable */
  *LpApplBuffer = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the type/size of the signal */
  LucSigTypeOrSize = (LpRxUnpack->ucSignalType);
  /* Shift the double word variable right by the number of shift bits to get
  the start position */
  LunApplSignal.whole_dword  >>= LpRxUnpack->ucNoOfShiftBits;
  /* polyspace-begin MISRA-C3:18.4 [Not a defect: Justify with annotations] "Not an Impact" */
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  LpSignBuffer -= (Com_PtrType)LucSigTypeOrSize;
  #else
  LpSignBuffer = LpSignBuffer + (Com_PtrType)LucSigTypeOrSize;
  #endif
  /* polyspace-end MISRA-C3:18.4 [Not a defect: Justify with annotations] "Not an Impact" */
  LucIpduBuffer =*LpSignBuffer;
  /* Get the sign mask value */
  LucSignMask = LpRxUnpack->ucRdSignMask;
  /* Apply the end mask value to local I-PDU variable to clear unoccupied area
  of signal */
  LucIpduBuffer &= LpRxUnpack->ucRdEndMask;
  /* Check whether the signal is negative */
  if((LucIpduBuffer & LucSignMask) != COM_ZERO)
  {
    /* Perform sign conversion */
    LucIpduBuffer |= LucSignMask;
    /* Check whether the signal size is 24 bits */
    if(COM_TYPE_24 == LucSigTypeOrSize)
    {
      /* Get sign extension to higher byte of double word variable */
      LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] = COM_SIGN_EXTENSION;
    }
  }
  else
  {
    /* Check whether the signal size is 24 bits */
    if(COM_TYPE_24 == LucSigTypeOrSize)
    {
      /* Get sign extension to higher byte of double word variable */
      LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] = COM_ZERO;
    }
  }
  /* Copy the local I-PDU buffer data to application Buffer */
  *LpSignBuffer = LucIpduBuffer;
  /* Check whether the signal size is one byte */
  if(COM_TYPE_8 == LucSigTypeOrSize)
  {
    /* Copy the lower byte of double word variable to signal data pointer */
    *(P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr =
                                                 LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  }
  /* Check whether the signal size is two bytes */
  else if (COM_TYPE_16 == LucSigTypeOrSize)
  {
    /* Copy the lower word of double word variable to signal data pointer */
    *(P2VAR(uint16, AUTOMATIC, COM_VAR)) LpSigDataPtr =
                                                 LunApplSignal.word_val.BO_Word[COM_DWORD_LS_WORD_IDX];
  }
  else
  {
    /* Copy the double word variable data to signal data pointer */
    *(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpSigDataPtr =
                                                      LunApplSignal.whole_dword;
  }
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackFiveByteOrdering                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        32 bits, spread across five bytes in an I-PDU       **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack                                          **
**                                                                            **
** Output Parameters    : LpSigDataPtr                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackFiveByteOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{

  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  Com_MIdWord_Access LunApplSignal;
  Com_MIWord_Access LunApplSigHi;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  /* Initialize the double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX] = COM_ZERO;
  /* Get the local pointer to lower byte of double word variable and assign it
  to application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
                                                &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the local pointer to the I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_FOUR;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* Copy the data from I-PDU buffer pointer to application buffer pointer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #else
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);
  /* Get the I-PDU buffer pointer data to the higher byte of word variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucSignMask = LpRxUnpack->ucNoOfShiftBits;
  /* Shift the double word variable to right by the number of shift bits */
  LunApplSignal.whole_dword  >>= LucSignMask;
  /* Shift the word variable to right by the number of shift bits */
  LunApplSigHi.whole_word  >>= LucSignMask;
  /* Get the lower byte of word variable to local signal variable */
  LucSigTypeOrSize = LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX];
  /* Apply end mask to clear unoccupied area of local signal variable */
  LucSigTypeOrSize &= LpRxUnpack->ucRdEndMask;
  /* Get the sign mask value */
  LucSignMask = LpRxUnpack->ucRdSignMask;
  /* Check whether the received signal is negative */
  if((LucSigTypeOrSize & LucSignMask) != COM_ZERO)
  {
    /* Perform sign conversion */
    LucSigTypeOrSize  |= LucSignMask;
  }
  /* Copy the local signal variable data to higher byte of double word
  variable */
  LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] |= LucSigTypeOrSize;
  /* Copy double word variable data to the signal data pointer */
  *(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpSigDataPtr =
                                                      LunApplSignal.whole_dword;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackNBytes                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of type uint8[n],  **
**                        where n > 1.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxDynSigLength      **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_UnPackNBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
  P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSignalBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  PduLengthType LddSignalSize;
  /* Get the pointer to application buffer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr;
  /* Get the pointer to I-PDU/signal buffer */
  LpSignalBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    LpRxUnpack->pRdBuffer;
  /* #2142 : separate DYN PDU from TP */
  if((LpRxUnpack->ddRxIpduDynLegthRef) != COM_INVALID_RXID_PARAM)
  {
    /* Get the size of the signal or signal group */
	/* polyspace<RTE:OBAI : Not a defect: Justify with annotations> Genderated array index in range */	
    LddSignalSize = Com_GaaRxDynSigLength[LpRxUnpack->ddRxIpduDynLegthRef];
  }
  else
  {
    /* Get the size of the signal or signal group */
    LddSignalSize = LpRxUnpack->ddSignalSize;
  }
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  while(LddSignalSize != (PduLengthType)COM_ZERO)
  {
    /* Copy the data from signal buffer to application buffer */
    *LpApplBuffer = *LpSignalBuffer;
    /* Increment the application buffer pointer */
    LpApplBuffer++;
    /* Increment the signal buffer pointer */
    LpSignalBuffer++;
    /* Decrement the signal size count */
    LddSignalSize--;
  }
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackNineBytes                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        64 bits and spread across five bytes in an I-PDU    **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackNineBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{

  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalSigBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  Com_MIdWord_Access LaaApplSignal[COM_TWO];
  Com_MIWord_Access LunApplSigHi;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  uint8 LucCount;
  /* Initialize the double word variables to zero */
  LaaApplSignal[COM_ZERO].whole_dword = COM_ZERO;
  LaaApplSignal[COM_ONE].whole_dword = COM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX] = COM_ZERO;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the pointer I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_EIGHT;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #else
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_FOUR);

  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  do
  {
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #else
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);

  /* Get the I-PDU buffer pointer data to the higher byte of word variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucSignMask = LpRxUnpack->ucNoOfShiftBits;
  /* Shift the double word variable to right by the number of shift bits */
  LaaApplSignal[COM_ZERO].whole_dword  >>= LucSignMask;
  LaaApplSignal[COM_ZERO].whole_dword |=
    (LaaApplSignal[COM_ONE].whole_dword << (COM_THIRTY_TWO - LucSignMask));
  LaaApplSignal[COM_ONE].whole_dword >>= LucSignMask;
  /* Shift the word variable to right by the number of shift bits */
  LunApplSigHi.whole_word  >>= LucSignMask;
  /* Get the lower byte of word variable to local signal variable  */
  LucSigTypeOrSize = LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX];
  /* Apply end mask to clear unoccupied area of local signal variable */
  LucSigTypeOrSize &= LpRxUnpack->ucRdEndMask;
  /* Copy the local signal variable data to higher byte of double word
  variable */
  LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX]
  |= LucSigTypeOrSize;
  /* Copy the double word variable data to signal data pointer */
  /* Get the base address */
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  LpLocalBuffer = (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  #else
  LpLocalBuffer = (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  #endif

  if(LpSigDataPtr != NULL_PTR)
  {
    LpLocalSigBuffer = (uint8 *) LpSigDataPtr;
    /* Copy the double word variable data to signal data pointer */
    for(LucCount = COM_ZERO; LucCount < COM_FOUR; LucCount++)
    {
      *LpLocalSigBuffer = *LpLocalBuffer;
      #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      LpLocalBuffer--;
      LpLocalSigBuffer++;
      #else
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #endif
    }

    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    LpLocalBuffer = (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
    #else
    LpLocalBuffer = (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
    #endif

    for(; LucCount < COM_EIGHT; LucCount++)
    {
      *LpLocalSigBuffer = *LpLocalBuffer;
      #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      LpLocalBuffer--;
      LpLocalSigBuffer++;
      #else
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #endif
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackNineByteOrdering                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        64 bits and spread across five bytes in an I-PDU    **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackNineByteOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{

  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalSigBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  Com_MIdWord_Access LaaApplSignal[COM_TWO];
  Com_MIWord_Access LunApplSigHi;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  uint8 LucCount;
  /* Initialize the double word variables to zero */
  LaaApplSignal[COM_ZERO].whole_dword = COM_ZERO;
  LaaApplSignal[COM_ONE].whole_dword = COM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX] = COM_ZERO;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the pointer I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_EIGHT;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer++;
    #else
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer--;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_FOUR);

  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  do
  {
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer++;
    #else
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer--;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);

  /* Get the I-PDU buffer pointer data to the higher byte of word variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucSignMask = LpRxUnpack->ucNoOfShiftBits;
  /* Shift the double word variable to right by the number of shift bits */
  LaaApplSignal[COM_ZERO].whole_dword  >>= LucSignMask;
  LaaApplSignal[COM_ZERO].whole_dword |=
    (LaaApplSignal[COM_ONE].whole_dword << (COM_THIRTY_TWO - LucSignMask));
  LaaApplSignal[COM_ONE].whole_dword >>= LucSignMask;
  /* Shift the word variable to right by the number of shift bits */
  LunApplSigHi.whole_word  >>= LucSignMask;
  /* Get the lower byte of word variable to local signal variable  */
  LucSigTypeOrSize = LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX];
  /* Apply end mask to clear unoccupied area of local signal variable */
  LucSigTypeOrSize &= LpRxUnpack->ucRdEndMask;
  /* Copy the local signal variable data to higher byte of double word
  variable */
  LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] |= LucSigTypeOrSize;
  /* Copy the double word variable data to signal data pointer */
  /* Get the base address */
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  LpLocalBuffer = (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX]);
  #else
  LpLocalBuffer = (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  #endif
  if(LpSigDataPtr != NULL_PTR)
  {
    LpLocalSigBuffer = (uint8 *) LpSigDataPtr;
    /* Copy the double word variable data to signal data pointer */
    for(LucCount = COM_ZERO; LucCount < COM_FOUR; LucCount++)
    {
      *LpLocalSigBuffer = *LpLocalBuffer;
      #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #else
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #endif
    }

    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    LpLocalBuffer = (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX]);
    #else
    LpLocalBuffer = (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
    #endif

    for(; LucCount < COM_EIGHT; LucCount++)
    {
      *LpLocalSigBuffer = *LpLocalBuffer;
      #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #else
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #endif
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : Com_UnPackEightBytes                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        64 bits and spread across eight bytes in an I-PDU   **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackEightBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{

  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  uint8 LucSigTypeOrSize;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr;
  /* Get the pointer I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_EIGHT;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #else
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_UnPackEightByteOrdering                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        64 bits and spread across eight bytes in an I-PDU   **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_UnPackEightByteOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{

  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  uint8 LucSigTypeOrSize;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr;
  /* Get the pointer I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_EIGHT;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer++;
    #else
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer--;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end MISRA-C3:D4.14 [Not a defect: Justify with annotations] */
/* polyspace-end MISRA-C3:18.1 [Not a defect: Justify with annotations]  */
/* polyspace-end MISRA-C3:11.5 [Not a defect: Justify with annotations]  */
/* polyspace-end RTE:NIV [Not a defect: Justify with annotations]  */
/* polyspace-end RTE:SHF [Not a defect: Justify with annotations]  */
/* polyspace-end RTE:IDP [Not a defect: Justify with annotations] "Configured memory access index" */
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

