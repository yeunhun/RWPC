/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Com_Pack.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of Packing, invalidate and update functions         **
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
** 2.7.1     08-Jan-2021   SM Kwon     Internal Redmine #27557                **
** 2.6.0     10-Sep_2020   SM Kwon     Internal Redmine #23914, #25250        **
** 2.4.0     25-Jan-2019   SM Kwon     Internal Redmine #14789                **
** 2.2.3     08-Dec-2017   Chan Kim    Internal Redmine #10849, #10851        **
** 2.2.1     24-Aug-2017   Chan Kim    Internal Redmine #9712                 **
** 2.2.0     16-Apr-2017   Chan Kim    Internal Redmine #7709, #7525          **
** 2.1.9     20-Mar-2017   Chan Kim    Internal Redmine #7851                 **
** 2.1.7     30-Nov-2016   Chan Kim    Internal Redmine #6807                 **
** 2.1.4     26-Jul-2016   Chan Kim    Internal Redmine #5687                 **
** 2.1.3     08-Jul-2016   Chan Kim    Internal Redmine #5341                 **
** 2.1.0     25-May-2016   Chan Kim    Internal Redmine #4998                 **
** 2.0.13    13-May-2016   Chan Kim    Internal Redmine #3959                 **
** 2.0.8     12-Feb-2016   Chan Kim    Internal Redmine #4158                 **
** 2.0.3     24-Nov-2015   Chan Kim    Internal Redmine #3544, #3535          **
** 2.0.2     18-Sep-2015   Chan Kim    Internal Redmine #3178                 **
** 1.0.15    09-Feb-2015   Chan Kim    Internal Redmine #2142                 **
** 1.0.11    03-Mar-2014   Chan Kim    Internal Redmine #642                  **
** 1.0.0     29-Apr-2013   Autron      Initial Version                        **
*******************************************************************************/
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/* polyspace-begin MISRA-C3:D4.14 [Not a defect: Justify with annotations] "Function call depends on the configured Pack values" */
/* polyspace-begin MISRA-C3:18.1 [Not a defect: Justify with annotations] "Genderated array index in range" */
/* polyspace-begin MISRA-C3:11.5 [Not a defect: Justify with annotations] "Conversion perform pointer to object" */
/* polyspace-begin RTE:OVFL [Not a defect: Justify with annotations] "Overflow can not occur" */
/* polyspace-begin RTE:NIV [Not a defect: Justify with annotations] "Initialized variable" */
/* polyspace-begin RTE:SHF [Not a defect: Justify with annotations] "Amount can not be outside its bounds" */
/* polyspace-begin RTE:IDP [Not a defect: Justify with annotations] "Configured memory access index" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_Pack.h"     /* Com Pack header file */
#include "SchM_Com.h"     /* SchM Com header file */



/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define COM_PACK_C_AR_RELEASE_MAJOR_VERSION       4
#define COM_PACK_C_AR_RELEASE_MINOR_VERSION       0
#define COM_PACK_C_AR_RELEASE_REVISION_VERSION    3

/* Software Version Information */
#define COM_PACK_C_SW_MAJOR_VERSION  2
#define COM_PACK_C_SW_MINOR_VERSION  7

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (COM_AR_RELEASE_MAJOR_VERSION != COM_PACK_C_AR_RELEASE_MAJOR_VERSION)
  #error "Com_Pack.c : Mismatch in Com Specification Major Version"
#endif

#if (COM_AR_RELEASE_MINOR_VERSION != COM_PACK_C_AR_RELEASE_MINOR_VERSION)
  #error "Com_Pack.c : Mismatch in Com Specification Minor Version"
#endif

#if (COM_AR_RELEASE_REVISION_VERSION != COM_PACK_C_AR_RELEASE_REVISION_VERSION)
  #error "Com_Pack.c : Mismatch in Com Specification Revision Version"
#endif

#if (COM_SW_MAJOR_VERSION != COM_PACK_C_SW_MAJOR_VERSION)
  #error "Com_Pack.c : Mismatch in Com Software Major Version"
#endif

#if (COM_SW_MINOR_VERSION != COM_PACK_C_SW_MINOR_VERSION)
  #error "Com_Pack.c : Mismatch in Com Software Minor Version"
#endif


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_PackOneByte                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs signal of size less than or     **
**                        equal to 8 bit into the I-PDU buffer.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSigDataPtr                                        **
**                                                                            **
** InOut parameter      : LpTxPack                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_PackOneByte
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  uint8 LucApplSignal;
  uint8 LucIpduByte;
  uint8 LucStartMask;
  /* Get the the value of SignalDataPtr to local application variable */
  LucApplSignal = *((P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr);
  /* Shift the application signal value to get signal start position in
  an I-PDU */
  LucApplSignal = (uint8)(LucApplSignal << (LpTxPack->ucNoOfShiftBit));
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Get the I-PDU buffer value into local I-PDU variable */
  LucIpduByte = *(P2VAR(uint8, AUTOMATIC, COM_VAR))(LpTxPack->pWrBuffer);
  /* Get the start mask the value into local variable */
  LucStartMask = LpTxPack->ucWrStartMask;
  /* Apply the start mask value to I-PDU variable to clear signal value */
  LucIpduByte &= LucStartMask;
  /* Apply start mask value to local application variable and
  move local application variable value to local I-PDU variable */
  LucIpduByte |= LucApplSignal & ((uint8)(~LucStartMask));
  /* Copy the local I-PDU variable value to I-PDU buffer */
  *((P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer) = LucIpduByte;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackBytes                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        four bytes in an I-PDU.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackBytes
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  Com_MIdWord_Access LunApplSignal;
  uint8 LucSizeOrData;
  uint8 LucNoOfByte;
  uint8 LucEndMask;
  /* Get the pointer to I-PDU buffer */
  LpWrBuffer = (LpTxPack->pWrBuffer);
  /* Get the number of bytes of data */
  LucNoOfByte = (uint8)(LpTxPack->ddSigTypeOrSize);
  /* Get the signal size */
  LucSizeOrData = (LucNoOfByte & COM_SIG_SIZE_MASK_VALUE);
  /* Get the number of bytes that signal spread across */
  LucNoOfByte = LucNoOfByte & COM_SIG_BYTE_MASK_VALUE;
  /* Initialize double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Check whether signal size is 8 bit */
  if(COM_SIZE_8 == LucSizeOrData)
  {
    /*  Get the signal value to lower byte of double word variable */
    LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX] =
                    *(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  /* Check whether signal size is 16 bit */
  else if(COM_SIZE_16 == LucSizeOrData)
  {
    /* Get the signal value to lower word of double word variable */
    LunApplSignal.word_val.BO_Word[COM_DWORD_LS_WORD_IDX] =
                   *(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  else
  {
    /* Get the the signal value to double word variable */
    LunApplSignal.whole_dword =
                  *(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  /* Shift left the double word variable value by number of shift bits */
  LunApplSignal.whole_dword <<= (LpTxPack->ucNoOfShiftBit);
  /* Get the pointer to lower byte of double word variable data */
  LpAppSigPtr =
     (P2VAR(uint8, AUTOMATIC, COM_VAR))&LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the end mask value */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Decrement the signal size by one */
  LucNoOfByte--;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Get the data from I-PDU buffer to local variable */
  LucSizeOrData = *LpWrBuffer;
  /* Clear signal data from I-PDU buffer by applying start mask */
  LucSizeOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer to local I-PDU buffer */
  LucSizeOrData |= *LpAppSigPtr;
  /* Copy local I-PDU buffer data into I-PDU buffer */
  *LpWrBuffer = LucSizeOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer--;
  #else
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer++;
  #endif
  /* Loop for number of bytes of data */
  while(LucNoOfByte != COM_ONE)
  {
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    LucNoOfByte--;
  }
  /* Get the first byte of I-PDU buffer data to local I-PDU variable */
  LucSizeOrData = *LpWrBuffer;
  /* Clear local I-PDU variable data by applying end mask */
  LucSizeOrData &= LucEndMask;
  /* Get application data value by applying negate mask to local I-PDU variable
  to clear unoccupied area and write to I-PDU buffer  */
  LucSizeOrData |= *LpAppSigPtr & ((uint8)(~LucEndMask));
  /* Store local I-PDU buffer variable to I-PDU buffer */
  *LpWrBuffer = LucSizeOrData;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackFiveBytes                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_PackFiveBytes
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                    P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  Com_MIdWord_Access LunApplSignal;
  Com_MIWord_Access LunApplSigHi;
  uint8 LucShiftOrData;
  uint8 LucEndMask;
  /* Get the local pointer to I-PDU buffer */
  LpWrBuffer =
  (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
  /* Copy signal data to double word variable */
  LunApplSignal.whole_dword = *(P2CONST(uint32, AUTOMATIC, COM_CONST))
                                                                   LpSigDataPtr;
  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LpTxPack->ucNoOfShiftBit;
  /* Get the end mask value to a local variable */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Copy the higher byte of double word variable to the lower byte of word
  variable */
  LunApplSigHi.whole_word = (uint8)LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX];
  /* Shift the double word variable left by the number of shift bits to get
  start position of signal in I-PDU */
  LunApplSignal.whole_dword <<= LucShiftOrData;
  /* Shift the word variable left by the number of shift bits */
  LunApplSigHi.whole_word =
    (uint16)((LunApplSigHi.whole_word) << LucShiftOrData);
  /* Apply negate end mask to clear unwanted data in higher byte of word
  variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] &= (uint8)(~(LucEndMask));
  /* Get the pointer to lower byte of the double word variable and assign to
  local application signal pointer */
  LpAppSigPtr =
     (P2VAR(uint8, AUTOMATIC, COM_VAR))&LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Get the data from I-PDU buffer pointer to local variable */
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from local I-PDU buffer variable by applying start
  mask */
  LucShiftOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer pointer to a local I-PDU buffer
  variable */
  LucShiftOrData |= *LpAppSigPtr;
  /* Copy data into I-PDU buffer from local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer--;
  #else
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer++;
  #endif
  /* Get the number of bytes of data */
  LucShiftOrData = COM_FOUR;
  /* Loop for number of bytes of data */
  do
  {
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_ONE);
  /* Get the data from I-PDU buffer pointer to local I-PDU buffer variable */
  LucShiftOrData = *LpWrBuffer;
  /*Clear signal data from the local I-PDU buffer variable by applying end mask
  to it */
  LucShiftOrData &= LucEndMask;
  /* Copy higher byte data of word variable to local I-PDU buffer */
  LucShiftOrData |= (LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX]);
  /* Store the local I-PDU buffer data into local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackByteOrdering                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        four bytes in an I-PDU and does the endianness      **
**                        conversion.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackByteOrdering
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  Com_MIdWord_Access LunApplSignal;
  uint8 LucSizeOrData;
  uint8 LucNoOfByte;
  uint8 LucEndMask;
  /* Get the pointer to I-PDU buffer to a local variable */
  LpWrBuffer = (LpTxPack->pWrBuffer);
  /* Get the number of bytes of data */
  LucNoOfByte = (uint8)(LpTxPack->ddSigTypeOrSize);
  /* Get the size of data */
  LucSizeOrData = (LucNoOfByte & COM_SIG_SIZE_MASK_VALUE);
  /* Get the number of counts that signal spread across */
  LucNoOfByte = LucNoOfByte & COM_SIG_BYTE_MASK_VALUE;
  /* Initialize double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Check whether signal size is 8 bit */
  if(COM_SIZE_8 == LucSizeOrData)
  {
    /*  Get the signal data to lower byte of double word variable */
    LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX] =
                    *(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  /* Check whether signal size is 16 bit */
  else if(COM_SIZE_16 == LucSizeOrData)
  {
    /*  Get the signal data to lower word of double word variable */
    LunApplSignal.word_val.BO_Word[COM_DWORD_LS_WORD_IDX] =
                   *(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  else
  {
      /*  Get the signal data to double word variable */
      LunApplSignal.whole_dword =
                  *(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  /* Shift the signal value in double word variable by number of shift bits */
  LunApplSignal.whole_dword <<= (LpTxPack->ucNoOfShiftBit);
  /* Get the local pointer to lower byte of double word variable and assign it
  to local application signal pointer */
  LpAppSigPtr =
     (P2VAR(uint8, AUTOMATIC, COM_VAR))&LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the end mask value */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Decrement the signal size */
  LucNoOfByte--;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Get the first byte of I-PDU buffer into local variable */
  LucSizeOrData = *LpWrBuffer;
  /* Clear signal data from the I-PDU by applying start mask */
  LucSizeOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer pointer */
  LucSizeOrData |= *LpAppSigPtr;
  /* Copy data from application signal pointer to a local variable */
  *LpWrBuffer = LucSizeOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer++;
  #else
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer--;
  #endif
  /* Loop for number of bytes of data */
  while(LucNoOfByte != COM_ONE)
  {
    /* Copy application data to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #else
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #endif
    LucNoOfByte--;
  }
  /* Get the first byte of I-PDU buffer into local I-PDU variable */
  LucSizeOrData = *LpWrBuffer;
  /* Clear local I-PDU variable data by applying End Mask to it */
  LucSizeOrData &= LucEndMask;
  /* Get application data value by applying negate mask to local I-PDU variable
  to clear unoccupied area and write to I-PDU buffer  */
  LucSizeOrData |= *LpAppSigPtr & ((uint8)(~LucEndMask));
  /* Store local I-PDU buffer variable to I-PDU */
  *LpWrBuffer = LucSizeOrData;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackFiveByteOrdering                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU and does the endianness      **
**                        conversion.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackFiveByteOrdering
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                    P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  Com_MIdWord_Access LunApplSignal;
  Com_MIWord_Access LunApplSigHi;
  uint8 LucShiftOrData;
  uint8 LucEndMask;
  /* Get the local pointer to I-PDU buffer */
  LpWrBuffer =
  (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
  /* Copy signal data to double word variable */
  LunApplSignal.whole_dword=*(P2CONST(uint32, AUTOMATIC, COM_CONST))
                                                                   LpSigDataPtr;
  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LpTxPack->ucNoOfShiftBit;
  /* Get the end mask value to local variable */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Copy the higher byte of double word variable to the lower byte of word
  variable */
  LunApplSigHi.whole_word = (uint8)LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX];
  /* Shift the double word variable by the number of shift bits to get start
  position of signal in I-PDU */
  LunApplSignal.whole_dword <<= LucShiftOrData;
  /* Shift the word variable by number of shift bits */
  LunApplSigHi.whole_word =
    (uint16)((LunApplSigHi.whole_word) << LucShiftOrData);
  /* Apply negate end mask to clear unwanted data in higher byte of word
  variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] &= (uint8)(~(LucEndMask));
  /* Get the pointer to lower byte of the double word variable and assign to
  local application signal pointer */
  LpAppSigPtr =
     (P2VAR(uint8, AUTOMATIC, COM_VAR))&LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Get the data from I-PDU buffer pointer to local variable */
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from local I-PDU buffer variable by applying start
  mask */
  LucShiftOrData &= LpTxPack->ucWrStartMask;
  /* Copy data from application signal pointer to a local I-PDU buffer
  variable */
  LucShiftOrData |= *LpAppSigPtr;
  /* Copy data into I-PDU buffer from local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer++;
  #else
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer--;
  #endif
  /* Get the number of bytes of data in local variable */
  LucShiftOrData = COM_FOUR;
  /* Loop for number of bytes of data */
  do
  {
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #else
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #endif
    /* Decrement the data byte */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_ONE);
  /* Get the data from I-PDU buffer pointer to local I-PDU buffer variable */
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from the local I-PDU buffer variable by applying end
  mask */
  LucShiftOrData &= LucEndMask;
  /* Copy higher byte data of word variable to local I-PDU buffer */
  LucShiftOrData |= (LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX]);
  /* Copy the local I-PDU buffer data into local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackNBytes                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal of uint8[n] type     **
**                        which spreads across N bytes in an I-PDU.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxDynSigLength      **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackNBytes
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpApplBuffer;
  PduLengthType LddSize;
  uint8 LucIpduBuffer;

  /* #2142 : separate DYN PDU from TP */
  if((LpTxPack->ddTxIpduDynLegthRef) != COM_INVALID_TXID_PARAM)
  {
    /* Get the size of the signal or signal group */
	/* polyspace<RTE:OBAI : Not a defect: Justify with annotations> Genderated array index in range */	
    LddSize = Com_GaaTxDynSigLength[LpTxPack->ddTxIpduDynLegthRef];
  }
  else
  {
    /* Get the size of the signal or signal group */
    LddSize = LpTxPack->ddSigTypeOrSize;
  }

  /* Check whether signal size is not equal to zero */
  if(LddSize != (PduLengthType)COM_ZERO)
  {
    /* Get the pointer to application buffer */
    LpApplBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Get the pointer to an I-PDU buffer */
    LpWrBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
    /* Enter protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
    /* Get the data from the I-PDU buffer pointer to a local I-PDU buffer
    variable */
    LucIpduBuffer = *LpWrBuffer;
    /* Apply the start mask to local I-PDU buffer variable */
    LucIpduBuffer &= LpTxPack->ucWrStartMask;
    /* Copy the application  data to local I-PDU buffer variable */
    LucIpduBuffer |= *LpApplBuffer;
    /* Write the application data back to I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* Increment the application pointer */
    LpApplBuffer++;
    /* Increment the WrBuffer pointer */
    LpWrBuffer++;
    /* Decrement the size size */
    LddSize--;
    /* Check whether size of the signal is not equal to one */
    while(LddSize > (PduLengthType)COM_ONE)
    {
      /* Copy the application buffer data to I-PDU buffer pointer */
      *LpWrBuffer = *LpApplBuffer;
      /* Get the pointer to next application buffer */
      LpApplBuffer++;
      /* Get the pointer to next I-PDU buffer */
      LpWrBuffer++;
      /* Decrement the signal size count */
      LddSize--;
    }
    /* Get the value of I-PDU buffer to a local I-PDU buffer variable */
    LucIpduBuffer = *LpWrBuffer;
    /* Apply the end mask to local I-PDU buffer variable to clear unoccupied
    areas */
    LucIpduBuffer &= LpTxPack->ucWrEndMask;
    /* Copy the application  data to local variable */
    LucIpduBuffer |= *LpApplBuffer;
    /* Copy the local I-PDU buffer variable data to the I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* Exit protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
  }/* Check whether signal size is not equal to zero */
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Pack16bit                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs signal of size less than or     **
**                        equal to 16 bit into the I-PDU buffer.              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSigDataPtr                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTxPack                                            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Pack16bit
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                        P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Copy data from source to destination buffer */
  *(P2VAR(uint16, AUTOMATIC, COM_VAR))(LpTxPack->pWrBuffer) =
                   *(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Pack32bit                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs signal of size less than or     **
**                        equal to 32 bit into the I-PDU buffer.              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSigDataPtr                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTxPack                                            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Pack32bit
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                        P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Copy data from source to destination buffer */
  *(P2VAR(uint32, AUTOMATIC, COM_VAR))(LpTxPack->pWrBuffer) =
                   *(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : Com_Write_8                                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies 8 bit data from the source     **
**                        pointer to destination pointer.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpDest                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_Write_8
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize)
{
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Copy data from source to destination buffer */
  *((P2VAR(uint8, AUTOMATIC, COM_VAR)) LpDest) =
                      *((P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource);
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Write_16                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies 16 bit data from the source    **
**                        pointer to destination pointer.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpDest                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Write_16
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize)
{
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Copy data from source to destination buffer */
  *((P2VAR(uint16, AUTOMATIC, COM_VAR)) LpDest) =
                    *((P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSource);
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Write_32                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies 32 bit data from the source    **
**                        pointer to destination pointer.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpDest                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Write_32
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize)
{
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Copy data from source to destination buffer */
  *((P2VAR(uint32, AUTOMATIC, COM_VAR)) LpDest) =
                    *((P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource);
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Write_64                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies 64 bit data from the source    **
**                        pointer to destination pointer.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSource, LpDest, LddSize                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Write_64
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize)
{
  /* Enter protection area */
  P2VAR(uint32, AUTOMATIC, COM_VAR) LpTarget;
  P2CONST(uint32, AUTOMATIC, COM_VAR) LpSrc;
  LpSrc = (P2CONST(uint32, AUTOMATIC, COM_VAR)) LpSource;
  LpTarget = (P2VAR(uint32, AUTOMATIC, COM_VAR)) LpDest;
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Copy data from source to destination buffer */
  *LpTarget = *LpSrc;
  /* Increment pointers */
  LpSrc++;
  LpTarget++;
  /* Copy data from source to destination buffer */
  *LpTarget = *LpSrc;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : Com_Write_NBytes                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies N byte data from the source    **
**                        pointer to destination pointer.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSource, LpDest, LddSize                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_Write_NBytes
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpDestBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSourceBuffer;
  PduLengthType LddSigSize;

  /* Get the pointer to destination buffer */
  LpDestBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpDest;
  /* Get the pointer to source buffer */
  LpSourceBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource;
  /* Get the size of this signal */
  LddSigSize = LddSize;
 
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_SIG_DATA_PROTECTION_AREA();
  #endif
  do
  {
    /* Copy the data from source buffer to destination buffer */
    *LpDestBuffer = *LpSourceBuffer;
    /* Get the pointer to next destination data */
    LpDestBuffer++;
    /* Get the pointer to next source data */
    LpSourceBuffer++;
    /* Decrement the signal size count */
    LddSigSize--;
  }while(LddSigSize != (PduLengthType)COM_ZERO);
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Validate_8                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal and returns true if signal is valid.         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTarget                                            **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Validate_8
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                  P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                                                          PduLengthType LddSize)
{
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Check whether data is valid or not */
  if((*(P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTarget) !=
                      (*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource))
  {

    (*(P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTarget) =
                      (*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource);
    /* Set return value to false */
    LblReturnValue = COM_TRUE;
  }
  /* Exit Protection Area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Validate_16                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal and returns true if signal is valid.         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTarget                                            **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Validate_16
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                      P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                                                          PduLengthType LddSize)
{  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Check whether invalid data is not equal to signal data */
  if((*(P2VAR(uint16, AUTOMATIC, COM_VAR)) LpTarget) !=
                     (*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* Set return value to false */
    LblReturnValue = COM_TRUE;
    (*(P2VAR(uint16, AUTOMATIC, COM_VAR)) LpTarget) =
                     (*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSource);
  }
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_Validate_32                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal and returns true if signal is valid.         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTarget                                            **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Validate_32
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                      P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                                                          PduLengthType LddSize)
{
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Check whether invalid data is not equal to signal data */
  if((*(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpTarget) !=
                     (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* Set return value to false */
    LblReturnValue = COM_TRUE;
    (*(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpTarget) =
                     (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource);
  }
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Validate_64                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal and returns true if signal is valid.         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTarget                                            **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Validate_64
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                       P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                                                          PduLengthType LddSize)
{
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Check whether invalid data is not equal to signal data */
  if((*(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpTarget) !=
                     (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* Set return value to false */
    LblReturnValue = COM_TRUE;
    (*(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpTarget) =
                     (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource);
  }
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Validate_NBytes                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal and returns true if signal is valid.         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Validate_NBytes
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                  P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                                                          PduLengthType LddSize)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpTargetPtr;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSourcePtr;
  boolean LblReturnValue;
  PduLengthType LddSigSize;

  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Get the pointer to destination buffer */
  LpTargetPtr = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTarget;
  /* Get the pointer to source buffer */
  LpSourcePtr = (P2CONST(uint8, AUTOMATIC, COM_VAR)) LpSource;
  /* Get the size of this signal */
  LddSigSize = LddSize;
  
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Loop to check whether the data is invalid or not, based on signal size */
  do
  {
    /* Decrement signal size */
    LddSigSize--;
    /* Check whether invalid data is not equal to signal data */
    if(*LpTargetPtr != *LpSourcePtr)
    {
      /* Set return value to false */
      LblReturnValue = COM_TRUE;
      *LpTargetPtr = *LpSourcePtr;
    }
    /* Increment invalid data pointer */
    LpTargetPtr++;
    /* Increment signal data pointer */
    LpSourcePtr++;
  }while(LddSigSize != (PduLengthType)COM_ZERO);
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/* #7709 start */
/*******************************************************************************
** Function Name        : Com_PackAndValidateSigGrp                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal group and returns true if signal is valid.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_PackAndValidateSigGrp
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpMaskingDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpApplBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpMaskingBuffer;
  PduLengthType LddSize;
  uint8 LucIpduBuffer;
  /* For checking value has been changed or not */
  uint8 LucIpduBuffer1;
  boolean LblReturnValue;

  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Get the size of the signal or signal group */
  LddSize = LpTxPack->ddSigTypeOrSize;
  /* Check whether signal size is not equal to zero */
  if(LddSize != (PduLengthType)COM_ZERO)
  {
    /* Get the pointer to application buffer */
    LpApplBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Get the pointer to an I-PDU buffer */
    LpWrBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTargetDataPtr;
    /* Get the pointer to a Masking buffer */
    LpMaskingBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpMaskingDataPtr;    
    /* Enter protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
    /* Get the data from the I-PDU buffer pointer to a local I-PDU buffer
    variable */
    LucIpduBuffer = *LpWrBuffer;
    /* For checking value has been changed or not */
    LucIpduBuffer1 = LucIpduBuffer;

    /* Apply the start mask to local I-PDU buffer variable */
    LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
    /* Copy the application  data to local I-PDU buffer variable */
    LucIpduBuffer |= *LpApplBuffer;
    /* Write the application data back to I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* For checking value has been changed or not */
    if(LucIpduBuffer != LucIpduBuffer1)
    {
      LblReturnValue = COM_TRUE;
    }
    /* Increment the application pointer */
    LpApplBuffer++;
    /* Increment the WrBuffer pointer */
    LpWrBuffer++;
    /* Get the pointer to next Masking buffer */
    LpMaskingBuffer++;
    /* Decrement the size size */
    LddSize--;
    if(LddSize > (PduLengthType)COM_ZERO)
    {
      /* Check whether size of the signal is not equal to one */
      while(LddSize != (PduLengthType)COM_ONE)
      {
        /* Copy the application buffer data to I-PDU buffer pointer */
        LucIpduBuffer = *LpWrBuffer;
        /* For checking value has been changed or not */
        LucIpduBuffer1 = LucIpduBuffer;
        
        LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
        LucIpduBuffer |= *LpApplBuffer;
        *LpWrBuffer = LucIpduBuffer;
        if(LucIpduBuffer != LucIpduBuffer1)
        {
          LblReturnValue = COM_TRUE;
        }
        /* Get the pointer to next application buffer */
        LpApplBuffer++;
        /* Get the pointer to next I-PDU buffer */
        LpWrBuffer++;
        /* Get the pointer to next Masking buffer */
        LpMaskingBuffer++;
        /* Decrement the signal size count */
        LddSize--;
      }
      /* Get the value of I-PDU buffer to a local I-PDU buffer variable */
      LucIpduBuffer = *LpWrBuffer;
      /* For checking value has been changed or not */
      LucIpduBuffer1 = LucIpduBuffer;
      /* Apply the end mask to local I-PDU buffer variable to clear unoccupied
      areas */
      LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
      /* Copy the application  data to local variable */
      LucIpduBuffer |= *LpApplBuffer;
      /* Copy the local I-PDU buffer variable data to the I-PDU buffer */
      *LpWrBuffer = LucIpduBuffer;
      /* For checking value has been changed or not */
      if(LucIpduBuffer != LucIpduBuffer1)
      {
        LblReturnValue = COM_TRUE;
      }
    }
    /* Exit protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
  }/* Check whether signal size is not equal to zero */

  return (LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackSigGrp                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal group and returns true if signal is valid.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_PackSigGrp
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpMaskingDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpApplBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpMaskingBuffer;
  PduLengthType LddSize;
  uint8 LucIpduBuffer;
  boolean LblReturnValue;

  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Get the size of the signal or signal group */
  LddSize = LpTxPack->ddSigTypeOrSize;
  /* Check whether signal size is not equal to zero */
  if(LddSize != (PduLengthType)COM_ZERO)
  {
    /* Get the pointer to application buffer */
    LpApplBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Get the pointer to an I-PDU buffer */
    LpWrBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTargetDataPtr;
    /* Get the pointer to a Masking buffer */
    LpMaskingBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpMaskingDataPtr;
    /* Enter protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
    /* Get the data from the I-PDU buffer pointer to a local I-PDU buffer
    variable */
    LucIpduBuffer = *LpWrBuffer;

    /* Apply the start mask to local I-PDU buffer variable */
    LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
    /* Copy the application  data to local I-PDU buffer variable */
    LucIpduBuffer |= *LpApplBuffer;
    /* Write the application data back to I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* Increment the application pointer */
    LpApplBuffer++;
    /* Increment the WrBuffer pointer */
    LpWrBuffer++;
    /* Get the pointer to next Masking buffer */
    LpMaskingBuffer++;
    /* Decrement the size size */
    LddSize--;
    if(LddSize > (PduLengthType)COM_ZERO)
    {
      /* Check whether size of the signal is not equal to one */
      while(LddSize != (PduLengthType)COM_ONE)
      {
        /* Copy the application buffer data to I-PDU buffer pointer */
        LucIpduBuffer = *LpWrBuffer;
        LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
        LucIpduBuffer |= *LpApplBuffer;
        *LpWrBuffer = LucIpduBuffer;
        /* Get the pointer to next application buffer */
        LpApplBuffer++;
        /* Get the pointer to next I-PDU buffer */
        LpWrBuffer++;
        /* Get the pointer to next Masking buffer */
        LpMaskingBuffer++;
        /* Decrement the signal size count */
        LddSize--;
      }
      /* Get the value of I-PDU buffer to a local I-PDU buffer variable */
      LucIpduBuffer = *LpWrBuffer;
      /* Apply the end mask to local I-PDU buffer variable to clear unoccupied
      areas */
      LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
      /* Copy the application  data to local variable */
      LucIpduBuffer |= *LpApplBuffer;
      /* Copy the local I-PDU buffer variable data to the I-PDU buffer */
      *LpWrBuffer = LucIpduBuffer;
    }
    /* Exit protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
  }/* Check whether signal size is not equal to zero */

  return (LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : Com_PackAndValidateSigGrpArray                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal group and returns true if signal is valid.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_PackAndValidateSigGrpArray
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpApplBuffer;
  PduLengthType LddSize;
  uint8 LucIpduBuffer;
  /* For checking value has been changed or not */
  uint8 LucIpduBuffer1;
  boolean LblReturnValue;

  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Get the size of the signal or signal group */
  LddSize = LpTxPack->ddSigTypeOrSize;
  /* Check whether signal size is not equal to zero */
  if(LddSize != (PduLengthType)COM_ZERO)
  {
    /* Get the pointer to application buffer */
    LpApplBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Get the pointer to an I-PDU buffer */
    LpWrBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTargetDataPtr;
    /* Enter protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
    /* Get the data from the I-PDU buffer pointer to a local I-PDU buffer
    variable */
    LucIpduBuffer = *LpWrBuffer;
    /* For checking value has been changed or not */
    LucIpduBuffer1 = LucIpduBuffer;

    /* Apply the start mask to local I-PDU buffer variable */
    LucIpduBuffer &= LpTxPack->ucWrStartMask;
    /* Copy the application  data to local I-PDU buffer variable */
    LucIpduBuffer |= *LpApplBuffer;
    /* Write the application data back to I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* For checking value has been changed or not */
    if(LucIpduBuffer != LucIpduBuffer1)
    {
      LblReturnValue = COM_TRUE;
    }
    /* Increment the application pointer */
    LpApplBuffer++;
    /* Increment the WrBuffer pointer */
    LpWrBuffer++;
    /* Decrement the size size */
    LddSize--;
    if(LddSize > (PduLengthType)COM_ZERO)
    {
      /* Check whether size of the signal is not equal to one */
      while(LddSize != (PduLengthType)COM_ONE)
      {
        /* For checking value has been changed or not */
        if(*LpWrBuffer != *LpApplBuffer)
        {
          LblReturnValue = COM_TRUE;
          /* Copy the application buffer data to I-PDU buffer pointer */
          *LpWrBuffer = *LpApplBuffer;
        }
        /* Get the pointer to next application buffer */
        LpApplBuffer++;
        /* Get the pointer to next I-PDU buffer */
        LpWrBuffer++;
        /* Decrement the signal size count */
        LddSize--;
      }
      /* Get the value of I-PDU buffer to a local I-PDU buffer variable */
      LucIpduBuffer = *LpWrBuffer;
      /* For checking value has been changed or not */
      LucIpduBuffer1 = LucIpduBuffer;
      /* Apply the end mask to local I-PDU buffer variable to clear unoccupied
      areas */
      LucIpduBuffer &= LpTxPack->ucWrEndMask;
      /* Copy the application  data to local variable */
      LucIpduBuffer |= *LpApplBuffer;
      /* Copy the local I-PDU buffer variable data to the I-PDU buffer */
      *LpWrBuffer = LucIpduBuffer;
      /* For checking value has been changed or not */
       if(LucIpduBuffer != LucIpduBuffer1)
      {
        LblReturnValue = COM_TRUE;
      }
    }
    /* Exit protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
  }/* Check whether signal size is not equal to zero */

  return (LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackAndValidateGrpSigArray                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      ** 
**                        group signals of a signal group array those have    **
**                        'triggered on cahnge' for their transfer property   **
**                        and return 'true' if there's any change on the value**
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpTxSigGrp, LpTxPack, LpSigDataPtr, LpTargetDataPtr **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#if(COM_TX_SIGGROUP_ARR_GROUPSIG_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_PackAndValidateGrpSigArray
(P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) LpTxSigGrp,
                      P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpIpduBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpApplBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpMaskingBuffer;

  uint8 LucIpduBufferNew;

  boolean LblReturnValue; 
  PduLengthType LddSizeToCpy;
  uint32 LulByteCnt;

  P2CONST(Com_RangeOfTOCByte, AUTOMATIC, COM_CONST) LddCurRange;
  boolean LblInRange;
  uint16 LusTOCRangeChkCnt;
  boolean LblRangeChkFin;

  LpIpduBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTargetDataPtr;
  LpApplBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  LpMaskingBuffer = LpTxSigGrp->pMaskingBuffer;

  LblReturnValue = COM_FALSE;

  LddSizeToCpy = LpTxPack->ddSigTypeOrSize;
  LulByteCnt = COM_ZERO;

  LddCurRange = &Com_GaaRangeOfTOCByte[LpTxSigGrp->usTOCRangeIdx];
  LusTOCRangeChkCnt = COM_ONE;

  LblInRange = COM_FALSE;
  LblRangeChkFin = COM_FALSE;

  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  
  if(LddSizeToCpy > (PduLengthType)COM_ZERO)
  {
    /* 1. Check whether all bytes are copied */
    while(LddSizeToCpy != (PduLengthType)COM_ZERO)
    {
      if((LblRangeChkFin != COM_TRUE) && (LblReturnValue != COM_TRUE))
      {
        if(LblInRange == COM_FALSE)
        {
          if(LddCurRange->ulStartByte == LulByteCnt)
          {
            LblInRange = COM_TRUE;
          }
        }
        else if(LblInRange == COM_TRUE)
        {
          /* The next of the last byte of the range */
          if((LddCurRange->ulStartByte + LddCurRange->ulLength) == LulByteCnt)
          {
            LblInRange = COM_FALSE;

            if(LusTOCRangeChkCnt < LpTxSigGrp->usNoOfTOCRange)
            {
              LddCurRange ++;
              LusTOCRangeChkCnt ++;
            }
            else
            {
              LblRangeChkFin = COM_TRUE;
            }
          }
        }
        else
        {
          /* LblInRange is always 'COM_FALSE' or 'COM_TRUE'. */
        }
      }
      
      /* 3. Check if the received byte of Signal Group Array is different to the byte in I-PDU Buffer */
      if(*LpIpduBuffer != *LpApplBuffer)
      {
        if((LblInRange == COM_TRUE) && (LblReturnValue == COM_FALSE))
        {
          /* 4. Check if the TOC group signal in this byte has been changed */
          if(((*LpIpduBuffer)&(~(*LpMaskingBuffer))) != ((*LpApplBuffer)&(~(*LpMaskingBuffer))))
          {
            LblReturnValue = COM_TRUE;
          }
        }

        /* 5. Copy the received byte to I-PDU Buffer with consideration of the position */
        if(COM_ONE < LddSizeToCpy)
        {
          /* 5-1. The fist byte to copy */
          if(LddSizeToCpy == LpTxPack->ddSigTypeOrSize)
          {
            LucIpduBufferNew = (((*LpIpduBuffer) & LpTxPack->ucWrStartMask) | (*LpApplBuffer));
            *LpIpduBuffer = LucIpduBufferNew;
          }
          /* 5-2. Bytes between the fisrt and the last */
          else
          {
            *LpIpduBuffer = *LpApplBuffer;
          }
        }
        /* 5-3. The last byte to copy */
        else
        {
          LucIpduBufferNew = (((*LpIpduBuffer) & LpTxPack->ucWrEndMask) | (*LpApplBuffer));
          *LpIpduBuffer = LucIpduBufferNew;
        }
      }

      LpApplBuffer++;
      LpIpduBuffer++;
      LpMaskingBuffer ++;

      LulByteCnt++;
      LddSizeToCpy--;
    }
  }
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  return (LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_PackSigGrpArray                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal group and returns true if signal is valid.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_PackSigGrpArray
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpApplBuffer;
  PduLengthType LddSize;
  uint8 LucIpduBuffer;
  boolean LblReturnValue;

  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Get the size of the signal or signal group */
  LddSize = LpTxPack->ddSigTypeOrSize;
  /* Check whether signal size is not equal to zero */
  if(LddSize != (PduLengthType)COM_ZERO)
  {
    /* Get the pointer to application buffer */
    LpApplBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Get the pointer to an I-PDU buffer */
    LpWrBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTargetDataPtr;
    /* Enter protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
    /* Get the data from the I-PDU buffer pointer to a local I-PDU buffer
    variable */
    LucIpduBuffer = *LpWrBuffer;

    /* Apply the start mask to local I-PDU buffer variable */
    LucIpduBuffer &= LpTxPack->ucWrStartMask;
    /* Copy the application  data to local I-PDU buffer variable */
    LucIpduBuffer |= *LpApplBuffer;
    /* Write the application data back to I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* Increment the application pointer */
    LpApplBuffer++;
    /* Increment the WrBuffer pointer */
    LpWrBuffer++;
    /* Decrement the size size */
    LddSize--;
    if(LddSize > (PduLengthType)COM_ZERO)
    {
      /* Check whether size of the signal is not equal to one */
      while(LddSize != (PduLengthType)COM_ONE)
      {
        /* Copy the application buffer data to I-PDU buffer pointer */
        *LpWrBuffer = *LpApplBuffer;
        /* Get the pointer to next application buffer */
        LpApplBuffer++;
        /* Get the pointer to next I-PDU buffer */
        LpWrBuffer++;
        /* Decrement the signal size count */
        LddSize--;
      }
      /* Get the value of I-PDU buffer to a local I-PDU buffer variable */
      LucIpduBuffer = *LpWrBuffer;
      /* Apply the end mask to local I-PDU buffer variable to clear unoccupied
      areas */
      LucIpduBuffer &= LpTxPack->ucWrEndMask;
      /* Copy the application  data to local variable */
      LucIpduBuffer |= *LpApplBuffer;
      /* Copy the local I-PDU buffer variable data to the I-PDU buffer */
      *LpWrBuffer = LucIpduBuffer;
    }
    /* Exit protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
  }/* Check whether signal size is not equal to zero */

  return (LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/* #7709 end */
/*******************************************************************************
** Function Name        : Com_PackEightBytes                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        eight bytes in an I-PDU.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

/* Pack function for a float32 signal that can be fit in 8 bytes */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_PackEightBytes
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  P2CONST(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  uint8 LucNoOfByte;
  /* Get the pointer to I-PDU buffer */
  LpWrBuffer = (LpTxPack->pWrBuffer);
  /* Get the number of bytes of data */
  LucNoOfByte = (uint8)(LpTxPack->ddSigTypeOrSize);
  /* Get the number of bytes that signal spread across */
  LucNoOfByte = LucNoOfByte & COM_SIG_BYTE_MASK_VALUE;
  /* Get the address of the signal buffer */
  LpAppSigPtr = (P2CONST(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Loop for number of bytes of data */
  while(LucNoOfByte != COM_ZERO)
  {
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    LucNoOfByte--;
  }
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_PackEightByteOrdering                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU and needs                    **
**                        Endianness Conversion                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

/* Pack function for a float32 signal that can be fit in 8 bytes */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_PackEightByteOrdering
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpAppSigPtr;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpSigDataPtr32;
  /* Buffer to temporarily hold data */
  Com_MIdWord_Access LaaApplSignal[COM_TWO];
  uint8 LucNoOfByte;
  /* Get the pointer to I-PDU buffer */
  LpWrBuffer = (LpTxPack->pWrBuffer);
  /* Get the number of bytes of data */
  LucNoOfByte = (uint8)(LpTxPack->ddSigTypeOrSize);
  /* Get the number of bytes that signal spread across */
  LucNoOfByte = LucNoOfByte & COM_SIG_BYTE_MASK_VALUE;

  LpSigDataPtr32 = (P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  /* Enter protection area */
  /* Get the the signal value to double word variable */
  LaaApplSignal[COM_ZERO].whole_dword = *LpSigDataPtr32;
  LpSigDataPtr32++;
  /* Get the upper bytes */
  LaaApplSignal[COM_ONE].whole_dword = *LpSigDataPtr32;
	
	#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  LpAppSigPtr =
    (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
	#else
	LpAppSigPtr =
    (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];	
	#endif

  if(LucNoOfByte <= COM_EIGHT) 
  {
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
    /* Loop for number of bytes of data */
    while(LucNoOfByte != COM_ZERO)
    {     
      /* Copy data from application signal pointer to I-PDU buffer */
      *LpWrBuffer = (uint8)*LpAppSigPtr;
      #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      /* Decrement application signal pointer */
      LpAppSigPtr--;
      /* Decrement I-PDU buffer pointer */
      LpWrBuffer++;
      #else
      /* Increment application signal pointer */
      LpAppSigPtr++;
      /* Increment I-PDU buffer pointer */
      LpWrBuffer--;
      #endif
      LucNoOfByte--;
    }
    /* Exit protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
  }  
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_PackNineBytes                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackNineBytes
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpSigDataPtr32;
  Com_MIdWord_Access LaaApplSignal[COM_THREE];
  uint8 LucShiftOrData;
  uint8 LucEndMask;
  /* Get the local pointer to I-PDU buffer */
  LpWrBuffer =
  (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
  LpSigDataPtr32 = (P2CONST(uint32, AUTOMATIC, COM_CONST))
    LpSigDataPtr;
  /* Copy signal data to double word variable */
  LaaApplSignal[COM_ZERO].whole_dword = *LpSigDataPtr32;
  /* Copy signal data to double word variable */
  LaaApplSignal[COM_ONE].whole_dword = *LpSigDataPtr32;
  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LpTxPack->ucNoOfShiftBit;
  /* Shift the double word variable left by the number of shift bits to get
  start position of signal in I-PDU */
  LaaApplSignal[COM_ZERO].whole_dword <<= LucShiftOrData;
  /* Shift the double word variable left by the number of shift bits to get
  start position of signal in I-PDU */
  LaaApplSignal[COM_ONE].whole_dword >>= (COM_THIRTY_TWO - LucShiftOrData);
  /* Increment the pointer to point to the next 32 bits */
  LpSigDataPtr32++;
  /* Get the data in the local buffer */
  LaaApplSignal[COM_ONE].whole_dword |= ((*LpSigDataPtr32) << LucShiftOrData);
  /* Copy the second set of data to a local variable */
  LaaApplSignal[COM_TWO].whole_dword = *LpSigDataPtr32;
  /* Shift the data to get the upper byte */
  LaaApplSignal[COM_TWO].whole_dword >>= (COM_THIRTY_TWO - LucShiftOrData);
  /* Get the end mask value to a local variable */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Point to the first byte to be copied */
  LpAppSigPtr =
    (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  /* Get the data from I-PDU buffer pointer to local variable */
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from local I-PDU buffer variable by applying start
  mask */
  LucShiftOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer pointer to a local I-PDU buffer
  variable */
  LucShiftOrData |= *LpAppSigPtr;
  /* Copy data into I-PDU buffer from local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer--;
  #else
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer++;
  #endif
  /* Get the number of bytes of data */
  LucShiftOrData = COM_EIGHT;
  /* Loop for number of bytes of data */
  do
  {
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_FIVE);

  LpAppSigPtr =
    (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  do
  {
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_ONE);


  /* Get the data from I-PDU buffer pointer to local I-PDU buffer variable */
  LucShiftOrData = *LpWrBuffer;
  /*Clear signal data from the local I-PDU buffer variable by applying end mask
  to it */
  LucShiftOrData &= LucEndMask;
  /* Copy higher byte data of word variable to local I-PDU buffer */
  LucShiftOrData |= (LaaApplSignal[COM_TWO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  /* Store the local I-PDU buffer data into local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackNineByteOrdering                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackNineByteOrdering
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpSigDataPtr32;
  Com_MIdWord_Access LaaApplSignal[COM_THREE];
  uint8 LucShiftOrData;
  uint8 LucEndMask;
  /* Get the local pointer to I-PDU buffer */
  LpWrBuffer =
  (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
  LpSigDataPtr32 = (P2CONST(uint32, AUTOMATIC, COM_CONST))
    LpSigDataPtr;
  /* Copy signal data to double word variable */
  LaaApplSignal[COM_ZERO].whole_dword = *LpSigDataPtr32;
  /* Copy signal data to double word variable */
  LaaApplSignal[COM_ONE].whole_dword = *LpSigDataPtr32;
  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LpTxPack->ucNoOfShiftBit;
  /* Shift the double word variable left by the number of shift bits to get
  start position of signal in I-PDU */
  LaaApplSignal[COM_ZERO].whole_dword <<= LucShiftOrData;
  /* Shift the double word variable left by the number of shift bits to get
  start position of signal in I-PDU */
  LaaApplSignal[COM_ONE].whole_dword >>= (COM_THIRTY_TWO - LucShiftOrData);
  /* Increment the pointer to point to the next 32 bits */
  LpSigDataPtr32++;
  /* Get the data in the local buffer */
  LaaApplSignal[COM_ONE].whole_dword |= ((*LpSigDataPtr32) << LucShiftOrData);
  /* Copy the second set of data to a local variable */
  LaaApplSignal[COM_TWO].whole_dword = *LpSigDataPtr32;
  /* Shift the data to get the upper byte */
  LaaApplSignal[COM_TWO].whole_dword >>= (COM_THIRTY_TWO - LucShiftOrData);
  /* Get the end mask value to a local variable */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Point to the first byte to be copied */
  LpAppSigPtr = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from local I-PDU buffer variable by applying start
  mask */
  LucShiftOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer pointer to a local I-PDU buffer
  variable */
  LucShiftOrData |= *LpAppSigPtr;
  /* Copy data into I-PDU buffer from local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer++;
  #else
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer--;
  #endif
  /* Get the number of bytes of data */
  LucShiftOrData = COM_EIGHT;
  /* Loop for number of bytes of data */
  do
  {
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer++;
    #else
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer--;
    #endif
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_FIVE);

  LpAppSigPtr = (P2VAR(uint8, AUTOMATIC, COM_VAR))
      &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  do
  {
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer++;
    #else
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer--;
    #endif
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_ONE);

  /* Get the data from I-PDU buffer pointer to local I-PDU buffer variable */
  LucShiftOrData = *LpWrBuffer;
  /*Clear signal data from the local I-PDU buffer variable by applying end mask
  to it */
  LucShiftOrData &= LucEndMask;
  /* Copy higher byte data of word variable to local I-PDU buffer */
  LucShiftOrData |= (LaaApplSignal[COM_TWO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  /* Store the local I-PDU buffer data into local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:D4.14 [Not a defect: Justify with annotations]  */
/* polyspace-end MISRA-C3:18.1 [Not a defect: Justify with annotations]  */
/* polyspace-end MISRA-C3:11.5 [Not a defect: Justify with annotations]  */
/* polyspace-end RTE:OVFL [Not a defect: Justify with annotations] */
/* polyspace-end RTE:NIV [Not a defect: Justify with annotations]  */
/* polyspace-end RTE:SHF [Not a defect: Justify with annotations]  */
/* polyspace-end RTE:IDP [Not a defect: Justify with annotations]  */
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
