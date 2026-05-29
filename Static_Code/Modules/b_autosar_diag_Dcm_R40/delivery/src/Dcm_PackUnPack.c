/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_PackUnPack.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Provision of unpacking of signals from request message and    **
**              packing of signals to the response message.                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                Description                      **
********************************************************************************
** 2.3.4.0   28-Jan-2021   EunKyung Kim    #27997                             **
**                                                                            **
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.0     09-01-2013    Autron            Initial Version                  **
*******************************************************************************/
/*******************************************************************************
* PRE-JUSTIFICATION BEGINE SECTION (MISRA-C RULE CHECKER)
* These rules will not be applied for verification based on the MISRA Rule
* in Rte generated source
*******************************************************************************/
/*
  polyspace:begin<MISRA-C:8.10:Not a defect:Justify with annotations> hether the Dcm api function is required internal or external linkage, depends on user configuration
  polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> Not a defect, This is to achieve throughput in the code
  polyspace:begin<MISRA-C:11.5:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)
  polyspace:begin<MISRA-C:16.7:Not a defect:Justify with annotations> A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object.
  polyspace:begin<MISRA-C:17.4:Not a defect:Justify with annotations> This code is not a defect
  polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable
  polyspace:begin<RTE: OVFL : Not a defect : No Action Planned > Overflow can not occur
  polyspace:begin<RTE: SHF : Not a defect : No Action Planned > amount can not be outside its bounds
  polyspace:begin<RTE: IDP : Not a defect : No Action Planned > configured memory access index
*/
/* polyspace-begin MISRA-C3:18.1 [Justify with annotations:Unset] "size of array is determined by configuration" */
/* polyspace-begin MISRA-C3:D4.1 [Justify with annotations:Unset] "range is pre-defined" */
/* polyspace-begin MISRA-C3:11.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Module do not know user data type so before using user data, pointer need to be cast" */
/* polyspace-begin CERT-C:EXP05-C [Justified:Low] "Module do not know user data type so before using user data, pointer need to be cast" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"          /* Dcm header file */
#include "Dcm_PCTypes.h"  /* Dcm PCTypes header file */
#include "Dcm_Ram.h"      /* Dcm Ram header file */
#include "Dcm_PackUnpack.h"   /* Dcm pack/unpack header file */
#include "SchM_Dcm.h"      /* Dcm Ram header file */
#include "Dcm_Config.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dcm_UnPackOneByte                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks one byte signal from the      **
**                        request message buffer.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LddUnPackSignal, LpRequestData, LpSignalDataPtr     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_Dcm()           **
**                                                 SchM_Exit_Dcm()            **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, DCM_CODE) Dcm_UnPackOneByte(
   Dcm_PackUnpackSignalData LddUnPackSignal,
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRequestData,
   P2VAR(void, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr)
{
  uint8 LucRequestData;
  uint8 LucSignMask;

  if ((LpSignalDataPtr == NULL_PTR) || (LpRequestData == NULL_PTR))
  {
    /* TODO : Det Error */
  }
  else 
  {
    /* Get the sign mask value */
    LucSignMask = LddUnPackSignal.ucSignMask;

    /* Enter protection area */
    SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();

    /* Get the Request data to local variable */
    LucRequestData = *(LpRequestData);
  
  
    /* Exit protection area */
    SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
    /*
     * Shift the request data in local variable by the number of shift bits
     * to the get the start position
     */
    LucRequestData = LucRequestData >>(LddUnPackSignal.ucShiftBits);

    /* Apply the end mask to request data in local variable e to clear
    unoccupied area of signal */
    LucRequestData &= (LddUnPackSignal.ucEndMask);

    /* Check whether the received signal is negative  */
    if((LucRequestData & LucSignMask) != DCM_ZERO)
    {
      /* Perform sign conversion */
      LucRequestData |= LucSignMask;
    }

    /* Copy local request data to signal data pointer */
    *(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))LpSignalDataPtr = LucRequestData;
  }
}

/*******************************************************************************
** Function Name        : Dcm_UnPackBytes                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        8 bits, spread across four bytes in request message **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LddUnPackSignal, LpRequestData, LpSignalDataPtr     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Dcm_GblProtocolEndianess   **
**                        Function(s) invoked    : SchM_Enter_Dcm()           **
**                                                 SchM_Exit_Dcm()            **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UnPackBytes
(
  Dcm_PackUnpackSignalData LddUnPackSignal,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRequestData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRequestBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpSignalBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpApplBuffer;

  /*  MISRA Rule        : 18.4
      Message           : An object of union type has been defined.
      Reason            : Data access of larger data types is used to achieve
                          better throughput.
      Verification      : However, part of the code is verified manually and
                          it is not having any impact.
  */
  Dcm_MIdWord_Access LunSignalValue;
  uint8 LucSigTypeOrSize;
  uint8 LucSignalValue;
  uint8 LucSignMask;

  /* Initialize double word variable to zero */
  LunSignalValue.whole_dword = DCM_ZERO;

  LpRequestBuffer = LpRequestData;

  /* Get the signal size */
  LucSigTypeOrSize  = LddUnPackSignal.ucSignalSize;

  /* Get the pointer to lower byte of double word variable and assign it to
  local signal buffer pointer */
  LpSignalBuffer = (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))
                                              &LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];

  LpApplBuffer = LpSignalBuffer;

  /* Enter protection area */
  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  if(LucSigTypeOrSize != DCM_ONE)
  {
  do
  {
    /* Copy the data from request buffer to signal buffer */
    *LpSignalBuffer = *LpRequestBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement signal buffer pointer */
    LpSignalBuffer--;
    LpRequestBuffer--;
    #else
    LpSignalBuffer++;
    LpRequestBuffer++;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
    }while(LucSigTypeOrSize != DCM_ONE);
  }
  /* Get the request buffer pointer data to a local variable */
  *LpSignalBuffer = *LpRequestBuffer;
  /* Exit protection area */
  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();

  LucSigTypeOrSize = (LddUnPackSignal.ucSignalType) - DCM_ONE;

  /* Shift the double word variable right by the number of shift bits to get
  the start position */
  LunSignalValue.whole_dword  >>= LddUnPackSignal.ucShiftBits;

  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  {
    uint8 maxNum = LucSigTypeOrSize;
    while(maxNum != 0U)
    {
      LpApplBuffer--;
      maxNum--;
    }
  }  
  #else
  /* MISRA Rule         : 17.4
     Message            : Performing pointer arithmetic.
     Reason             : Increment operator is used to achieve better
                            throughput.
     Verification       : However, part of the code is verified manually and it
                            is not having any impact.
  */
  LpApplBuffer = &LpApplBuffer[LucSigTypeOrSize];
  #endif

  /* polyspace +1 DEFECT:OUT_BOUND_PTR [Justified:Low] "Not a defect" */
  LucSignalValue =*LpApplBuffer;

  /* Get the sign mask value */
  LucSignMask = LddUnPackSignal.ucSignMask;

  /* Apply the end mask value to local variable to clear unoccupied
  area of signal */
  LucSignalValue &= LddUnPackSignal.ucEndMask;

   /* Check whether the signal is negative */
  if((LucSignalValue & LucSignMask) != DCM_ZERO)
  {
    /* Perform sign conversion */
    LucSignalValue |= LucSignMask;
  }
  else
  {
    /* To avoid QAC warning */
  }
  /* Copy the local I-PDU buffer data to application Buffer */
  *LpApplBuffer = LucSignalValue;

  /* Check whether the signal size is one byte */
  if(LucSigTypeOrSize == DCM_TYPE_8)
  {
    /* Copy the lower byte of double word variable to signal data pointer */
    *(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))LpSignalDataPtr =
      LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];
  }
  /* Check whether the signal size is two bytes */
  else if (LucSigTypeOrSize == DCM_TYPE_16)
  {
    /* Call the Function to UnPack the Bytes */
    Dcm_UnPack16(LpSignalDataPtr,LunSignalValue);
  }
  else
  {
    if((LddUnPackSignal.ucSignalSize == DCM_THREE) && \
         (LddUnPackSignal.ucShiftBits == DCM_ZERO))
    {
      /* Call the Function to Pack the Bytes */
      Dcm_UnPack24(LpSignalDataPtr,LunSignalValue);
    }
    else
    {
      /* Call the Function to Pack the Bytes */
      Dcm_UnPack32(LpSignalDataPtr,LunSignalValue);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_UnPackFiveBytes                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        32 bits, spread across five bytes in the request    **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LddUnPackSignal, LpRequestData, LpSignalDataPtr     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Dcm_GblProtocolEndianess   **
**                        Function(s) invoked    : SchM_Enter_Dcm()           **
**                                                 SchM_Exit_Dcm()            **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UnPackFiveBytes
(
   Dcm_PackUnpackSignalData LddUnPackSignal,
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRequestData,
   P2VAR(void, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr)
{

  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRequestBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpSignalBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpOutSignalBuffer;

  Dcm_MIdWord_Access LunSignalValue;
  Dcm_MIWord_Access LunSignalValueHi;
  uint8 LucSignalType;
  uint8 LucShiftBits;
  uint8 LucSignMask;

  /* Initialize the double word variable to zero */
  LunSignalValue.whole_dword = DCM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunSignalValueHi.byte_val.BO_Byte[DCM_WORD_LS_BYTE_IDX] = DCM_ZERO;
  /* Get the local pointer to lower byte of double word variable and assign it
  to buffer pointer */
  LpSignalBuffer = (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)) 
    &LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];
  /* Get the local pointer to the request data buffer */
  LpRequestBuffer = LpRequestData;
  /* Get the signal size that spread across number of bytes */
  LucSignalType = LddUnPackSignal.ucSignalSize;
  /* Enter protection area */
  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* Copy the data from request buffer pointer to signal buffer pointer */
    *LpSignalBuffer = *LpRequestBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application buffer pointer */
    LpSignalBuffer--;
    LpRequestBuffer--;
    #else
    /* Increment application buffer pointer */
    LpSignalBuffer++;
    LpRequestBuffer++;
    #endif
    /* Decrement signal size */
    LucSignalType--;
  }while(LucSignalType != DCM_ONE);

  /* Get the request data value to the higher byte of word variable */
  LunSignalValueHi.byte_val.BO_Byte[DCM_WORD_MS_BYTE_IDX] = *LpRequestBuffer;
  /* Exit protection area */
  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucShiftBits = LddUnPackSignal.ucShiftBits;
  /* Shift the double word variable to right by the number of shift bits */
  LunSignalValue.whole_dword  >>= LucShiftBits;
  /* Shift the word variable to right by the number of shift bits */
  LunSignalValueHi.whole_word  >>= LucShiftBits;
  /* Get the lower byte of word variable to local signal variable */
  LucSignalType = LunSignalValueHi.byte_val.BO_Byte[DCM_WORD_LS_BYTE_IDX];
  /* Apply end mask to clear unoccupied area of local signal variable */
  LucSignalType &= LddUnPackSignal.ucEndMask;

  LucSignMask = LddUnPackSignal.ucSignMask;

  /* Check whether the received signal is negative */
  if((LucSignalType & LucSignMask) != DCM_ZERO)
  {
    /* Perform sign conversion */
    LucSignalType  |= LucSignMask;
  }

  /* Copy the local signal variable data to higher byte of double word
  variable */
  LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX] |= LucSignalType;

  LpOutSignalBuffer = (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))LpSignalDataPtr;

  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Copy the lower word of double word variable to signal data pointer */
  LpOutSignalBuffer[0U] = LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX];
  LpOutSignalBuffer[1U] = LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX];
  LpOutSignalBuffer[2U] = LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX];
  LpOutSignalBuffer[3U] = LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];
  #else
  LpOutSignalBuffer[0U] = LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];
  LpOutSignalBuffer[1U] = LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX];
  LpOutSignalBuffer[2U] = LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX];
  LpOutSignalBuffer[3U] = LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX];
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_UnPackByteOrdering                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        8 bits, spread across four bytes in request message **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LddUnPackSignal, LpRequestData, LpSignalDataPtr     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Dcm_GblProtocolEndianess   **
**                        Function(s) invoked    : SchM_Enter_Dcm()           **
**                                                 SchM_Exit_Dcm()            **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UnPackByteOrdering
(
   Dcm_PackUnpackSignalData LddUnPackSignal,
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRequestData,
   P2VAR(void, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRequestBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpSignalBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpApplBuffer;

  Dcm_MIdWord_Access LunSignalValue;
  uint8 LucSigTypeOrSize;
  uint8 LucSignalValue;
  uint8 LucSignMask;

  /* Initialize double word variable to zero */
  LunSignalValue.whole_dword = DCM_ZERO;

  LpRequestBuffer = LpRequestData;

  /* Get the signal size */
  LucSigTypeOrSize  = LddUnPackSignal.ucSignalSize;

  /* Get the pointer to lower byte of double word variable and assign it to
  local signal buffer pointer */
  LpSignalBuffer = (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))
    &LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];

  LpApplBuffer = LpSignalBuffer;

  /* Enter protection area */
  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* Copy the data from request buffer to signal buffer */
    *LpSignalBuffer = *LpRequestBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)

    /* Decrement signal buffer pointer */
    LpSignalBuffer--;
    /* Increment request buffer pointer */
    LpRequestBuffer++;
    #else
    /* MISRA Rule         : 17.4
       Message            : Increment or decrement operation performed on
                            pointer.
       Reason             : Increment or decrement operator is used to achieve
                            better throughput.
       Verification       : However, part of the code is verified manually and
                            it is not having any impact.
    */
    /* Increment signal buffer pointer */
    LpSignalBuffer++;
  /* MISRA Rule         : 17.4
       Message            : Increment or decrement operation performed on
                            pointer.
       Reason             : Increment or decrement operator is used to achieve
                            better throughput.
       Verification       : However, part of the code is verified manually and
                            it is not having any impact.
    */
    LpRequestBuffer--;
    #endif
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != DCM_ONE);
  /* Get the request buffer pointer data to a local variable */
  *LpSignalBuffer = *LpRequestBuffer;
  /* Exit protection area */
  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();

  LucSigTypeOrSize = (LddUnPackSignal.ucSignalType) - DCM_ONE;

  /* Shift the double word variable right by the number of shift bits to get
  the start position */
  LunSignalValue.whole_dword  >>= LddUnPackSignal.ucShiftBits;

  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  {
    uint8 maxNum = LucSigTypeOrSize;
    while(maxNum != 0U)
    {
      LpApplBuffer--;
      maxNum--;
    }
  }
  #else
  LpApplBuffer = &LpApplBuffer[LucSigTypeOrSize];
  #endif
  /* polyspace +1 DEFECT:OUT_BOUND_PTR [Justified:Low] "Not a defect" */
  LucSignalValue =*LpApplBuffer;

  /* Get the sign mask value */
  LucSignMask = LddUnPackSignal.ucSignMask;

  /* Apply the end mask value to local variable to clear
  unoccupied area of signal */
  LucSignalValue &= LddUnPackSignal.ucEndMask;

   /* Check whether the signal is negative */
  if((LucSignalValue & LucSignMask) != DCM_ZERO)
  {
    /* Perform sign conversion */
    LucSignalValue |= LucSignMask;
  }
  else
  {
    /* To avoid QAC warning */
  }
  /* Copy the local I-PDU buffer data to application Buffer */
  *LpApplBuffer = LucSignalValue;

  /* Check whether the signal size is one byte */
  if(LucSigTypeOrSize == DCM_TYPE_8)
  {
    /* Copy the lower byte of double word variable to signal data pointer */
    *(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))LpSignalDataPtr =
      LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];
  }
  /* Check whether the signal size is two bytes */
  else if (LucSigTypeOrSize == DCM_TYPE_16)
  {
  /* Call the Function to UnPack the Bytes */
   Dcm_UnPack16(LpSignalDataPtr,LunSignalValue);
  }
  else
  {
    if((LddUnPackSignal.ucSignalSize == DCM_THREE) && \
         (LddUnPackSignal.ucShiftBits == DCM_ZERO))
    {
      /* Call the Function to Pack the Bytes */
      Dcm_UnPack24(LpSignalDataPtr,LunSignalValue);
    }
    else
    {
      /* Call the Function to Pack the Bytes */
      Dcm_UnPack32(LpSignalDataPtr,LunSignalValue);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_UnPackFiveByteOrdering                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        32 bits, spread across five bytes in the request    **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LddUnPackSignal, LpRequestData, LpSignalDataPtr     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Dcm_GblProtocolEndianess   **
**                        Function(s) invoked    : SchM_Enter_Dcm()           **
**                                                 SchM_Exit_Dcm()            **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UnPackFiveByteOrdering
(
   Dcm_PackUnpackSignalData LddUnPackSignal,
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRequestData,
   P2VAR(void, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr)
{

  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRequestBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpSignalBuffer;
  
  Dcm_MIdWord_Access LunSignalValue;
  Dcm_MIWord_Access LunSignalValueHi;
  uint8 LucSignalType;
  uint8 LucShiftBits;
  uint8 LucSignMask;

  /* Initialize the double word variable to zero */
  LunSignalValue.whole_dword = DCM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunSignalValueHi.byte_val.BO_Byte[DCM_WORD_LS_BYTE_IDX] = DCM_ZERO;
  /* Get the local pointer to lower byte of double word variable and assign it
  to buffer pointer */
  LpSignalBuffer = (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))
                                              &LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];
  /* Get the local pointer to the request data buffer */
  LpRequestBuffer = LpRequestData;
  /* Get the signal size that spread across number of bytes */
  LucSignalType = LddUnPackSignal.ucSignalSize;
  /* Enter protection area */
  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* Copy the data from request buffer pointer to signal buffer pointer */
    *LpSignalBuffer = *LpRequestBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)

    /* Decrement application buffer pointer */
    LpSignalBuffer--;
    /* Increment request buffer pointer */
    LpRequestBuffer++;
    #else
    LpSignalBuffer++;
    /* Increment request buffer pointer */
    LpRequestBuffer--;
    #endif
    /* Decrement signal size */
    LucSignalType--;
  }while(LucSignalType != DCM_ONE);

  /* Get the request data value to the higher byte of word variable */
  LunSignalValueHi.byte_val.BO_Byte[DCM_WORD_MS_BYTE_IDX] = *LpRequestBuffer;
  /* Exit protection area */
  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucShiftBits = LddUnPackSignal.ucShiftBits;
  /* Shift the double word variable to right by the number of shift bits */
  LunSignalValue.whole_dword  >>= LucShiftBits;
  /* Shift the word variable to right by the number of shift bits */
  LunSignalValueHi.whole_word  >>= LucShiftBits;
  /* Get the lower byte of word variable to local signal variable */
  LucSignalType = LunSignalValueHi.byte_val.BO_Byte[DCM_WORD_LS_BYTE_IDX];
  /* Apply end mask to clear unoccupied area of local signal variable */
  LucSignalType &= LddUnPackSignal.ucEndMask;

  LucSignMask = LddUnPackSignal.ucSignMask;

  /* Check whether the received signal is negative */
  if((LucSignalType & LucSignMask) != DCM_ZERO)
  {
    /* Perform sign conversion */
    LucSignalType  |= LucSignMask;
  }

   /* Copy the local signal variable data to higher byte of double word
   variable */
  LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX] |= LucSignalType;

  /* Call the Function to UnPack the Bytes */
   Dcm_UnPack32(LpSignalDataPtr,LunSignalValue);
}

/*******************************************************************************
** Function Name        : Dcm_UnPackNBytes                                    **
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
** Input Parameters     : LddUnPackSignal, LpRequestData, LpSignalDataPtr     **
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
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UnPackNBytes
(
   Dcm_PackUnpackSignalData LddUnPackSignal,
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRequestData,
   P2VAR(void, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRequestBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpSignalBuffer;
  uint32 LulSignalSize;

  if ((LpSignalDataPtr == NULL_PTR) || (LpRequestData == NULL_PTR))
  {
    /* TODO : Det Error */
  }
  else
  {    
    /* Get the pointer to application buffer */
    LpSignalBuffer = (P2VAR(uint8, AUTOMATIC, COM_PRIVATE_DATA))LpSignalDataPtr;
    /* Get the pointer to I-PDU/signal buffer */
    LpRequestBuffer = LpRequestData;

    /* Get the size of the signal or signal group */
    LulSignalSize = LddUnPackSignal.ulSignalLength;

      /* Enter protection area */
    SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();
    /* Loop for signal size */
    while(LulSignalSize != DCM_ZERO)
    {

      /* Copy the data from signal buffer to application buffer */
      *LpSignalBuffer = *LpRequestBuffer;

      /* Increment the application buffer pointer */
      LpRequestBuffer++;

      /* Increment the signal buffer pointer */
      LpSignalBuffer++;
      /* Decrement the signal size count */
      LulSignalSize--;
    }

    /* Exit protection area */
    SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
  }
}

/*******************************************************************************
** Function Name        : Dcm_PackOneByte                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs one byte signal from the        **
**                        response message buffer.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LddPackSignal, LpResponseData, LpSignalDataPtr      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_Dcm()           **
**                                                 SchM_Exit_Dcm()            **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_PackOneByte(
   Dcm_PackUnpackSignalData LddPackSignal,
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpResponseData,
   P2CONST(void, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr)
{
  uint8 LucSignalValue;
  uint8 LucResponseByte;
  uint8 LucStartMask;
  
  if ((LpSignalDataPtr == NULL_PTR) || (LpResponseData == NULL_PTR))
  {
    /* TODO : Det Error */
  }
  else
  {
    /* Get the the value of SignalDataPtr to local signal variable */
    LucSignalValue = *((P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST))
      LpSignalDataPtr);
  
    /* Shift the signal value to get signal start position in the request buffer */
    LucSignalValue <<= (LddPackSignal.ucShiftBits);

    /* Enter protection area */
    SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();

    /* Get the Response buffer pointer into local response variable */
    LucResponseByte = *(P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))LpResponseData;
      
    /* Get the start mask the value into local variable */
    LucStartMask = LddPackSignal.ucStartMask;

    /* Apply start mask value to local response variable to clear signal value*/
    LucResponseByte &= LucStartMask;

    /* Apply start mask value to local response variable and
    move local signal variable value to local response variable */
    LucResponseByte |= LucSignalValue & ((uint8)(~LucStartMask));

    /* Copy the local response variable value to response buffer */
    *((P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))LpResponseData) = LucResponseByte;
    
    /* Exit protection area */
    SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
  }
}

/*******************************************************************************
** Function Name        : Dcm_PackBytes                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal of size more than 8  **
**                        bits, spread across four bytes in response message  **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LddPackSignal, LpResponseData, LpSignalDataPtr      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Dcm_GblProtocolEndianess   **
**                        Function(s) invoked    : SchM_Enter_Dcm()           **
**                                                 SchM_Exit_Dcm()            **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_PackBytes(
   Dcm_PackUnpackSignalData LddPackSignal,
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpResponseData,
   P2CONST(void, AUTOMATIC, DCM_APPL_CONST)LpSignalDataPtr)
{
  Dcm_MIdWord_Access LunSignalValue;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpSignalPtr;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpResponseBuffer;
  uint8 LucSizeOrData;
  uint8 LucNoOfByte;
  uint8 LucEndMask;

  /* Get the pointer to response buffer to a local variable */
  LpResponseBuffer = LpResponseData;

  /* Get the number of bytes of data */
  LucNoOfByte = (LddPackSignal.ucSignalTypeorSize);

  /* Get the size of data */
  LucSizeOrData = (LucNoOfByte & DCM_SIG_SIZE_MASK_VALUE);

  /* Get the number of counts that signal spread across */
  LucNoOfByte = LucNoOfByte & DCM_SIG_BYTE_MASK_VALUE;

  /* Initialize double word variable to zero */
  LunSignalValue.whole_dword = DCM_ZERO;

  /* Check whether signal size is 8 bit */
  if(DCM_SIZE_8 == LucSizeOrData)
  {
    /*  Get the signal data to lower byte of double word variable */
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX] =
      *(P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST))LpSignalDataPtr; 
  }
  /* Check whether signal size is 16 bit */
  else if(DCM_SIZE_16 == LucSizeOrData)
  {
  /* Call the Function to Pack the Bytes */
    Dcm_Pack16(&LunSignalValue, LpSignalDataPtr);
  }
  else
  {
    if((LucNoOfByte == DCM_THREE) && (LddPackSignal.ucShiftBits == DCM_ZERO))
    {
    /* Call the Function to Pack the Bytes */
     Dcm_Pack24(&LunSignalValue, LpSignalDataPtr);
    }
    else
    {
    /* Call the Function to Pack the Bytes */
     Dcm_Pack32(&LunSignalValue, LpSignalDataPtr);
    }
  }
  /* Shift the signal value in double word variable by number of shift bits */
  LunSignalValue.whole_dword <<= (LddPackSignal.ucShiftBits);

  /* Get the local pointer to lower byte of double word variable and assign it
  to local signal pointer */
  LpSignalPtr =
  (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))&LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];
  /* Get the end mask value */
  LucEndMask = LddPackSignal.ucEndMask;
  /* Decrement the signal size */
  if((LucNoOfByte > DCM_ZERO) &&
     (LucNoOfByte <= sizeof(LunSignalValue.byte_val.BO_Byte)))
  {
    LucNoOfByte--;
    /* Enter protection area */
    SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();
    /* Get the first byte of response buffer into local variable */
    LucSizeOrData = *LpResponseBuffer;
    /* Clear signal data from the response data by applying start mask */
    LucSizeOrData &= LddPackSignal.ucStartMask;
    /* Write data from signal buffer pointer */
    LucSizeOrData |= *LpSignalPtr;
    /* Copy data from signal pointer to a local variable */
    *LpResponseBuffer = LucSizeOrData;

    /* Loop for number of bytes of data */
    /* sg.baek 022705 - Task #2226 in redmine */
    while(LucNoOfByte > DCM_ZERO)
    {
      /* Copy signal data to I-PDU buffer */
      *LpResponseBuffer = *LpSignalPtr;
      #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      /* Decrement signal pointer */
      LpSignalPtr--;
      #else
    
      /* Increment application signal pointer */
      LpSignalPtr++;
      #endif
      /* Increment response buffer pointer */
      LpResponseBuffer = &LpResponseBuffer[1u];
      LucNoOfByte--;
    }

    /* Get the first byte of response buffer into local variable */
    LucSizeOrData = *LpResponseBuffer;
    /* Clear local variable data by applying End Mask to it */
    LucSizeOrData &= LucEndMask;

    /* Get signal data value by applying end mask to local variable
    to clear unoccupied area and write to response buffer  */
    LucSizeOrData |= *LpSignalPtr & ((uint8)(~LucEndMask));
    /* Store local variable to response buffer */
    *LpResponseBuffer = LucSizeOrData;
    /* Exit protection area */
    SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
  }
}

/*******************************************************************************
** Function Name        : Dcm_PackFiveBytes                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal of size more than    **
**                        32 bits, spread across five bytes in the response   **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LddPackSignal, LpResponseData, LpSignalDataPtr      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Dcm_GblProtocolEndianess   **
**                        Function(s) invoked    : SchM_Enter_Dcm()           **
**                                                 SchM_Exit_Dcm()            **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_PackFiveBytes(
   Dcm_PackUnpackSignalData LddPackSignal,
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpResponseData,
   P2CONST(void, AUTOMATIC, DCM_APPL_CONST)LpSignalDataPtr)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpResponseBuffer;
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA)LpSignalPtr;

  Dcm_MIdWord_Access LunApplSignal;
  Dcm_MIWord_Access LunApplSignalHi;
  uint8 LucShiftOrData;
  uint8 LucEndMask;
  /* Get the local pointer to response buffer */
  LpResponseBuffer = LpResponseData;
  LpSignalPtr = (P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA))LpSignalDataPtr;
  
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  LunApplSignal.byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX]     = LpSignalPtr[0U];
  LunApplSignal.byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX] = LpSignalPtr[1U];
  LunApplSignal.byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX] = LpSignalPtr[2U];
  LunApplSignal.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX]     = LpSignalPtr[3U];
  #else
  LunApplSignal.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX]     = LpSignalPtr[0U];
  LunApplSignal.byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX] = LpSignalPtr[1U];
  LunApplSignal.byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX] = LpSignalPtr[2U];
  LunApplSignal.byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX]     = LpSignalPtr[3U];
  #endif

  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LddPackSignal.ucShiftBits;

  /* Get the end mask value to local variable */
  LucEndMask = LddPackSignal.ucEndMask;

  /* Copy the higher byte of double word variable to the lower byte of word
  variable */
  LunApplSignalHi.whole_word = (uint8)LunApplSignal.byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX];

  /* Shift the double word variable by the number of shift bits to get start
  position of signal in the response buffer */
  LunApplSignal.whole_dword <<= LucShiftOrData;

  /* Shift the word variable by number of shift bits */
  LunApplSignalHi.whole_word <<= LucShiftOrData;

  /* Apply negate end mask to clear unwanted data in higher byte of word
  variable */
  LunApplSignalHi.byte_val.BO_Byte[DCM_WORD_MS_BYTE_IDX] &= (uint8)(~(LucEndMask));

  /* Get the pointer to lower byte of the double word variable and assign to
  local application signal pointer */
  LpSignalPtr =
     (P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA))&LunApplSignal.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];

  /* Enter protection area */
  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();

  /* Get the data from response buffer pointer to local variable */
  LucShiftOrData = *LpResponseBuffer;

  /* Clear signal data from local response buffer variable by applying start
  mask */
  LucShiftOrData &= LddPackSignal.ucStartMask;

  /* Copy data from application signal pointer to a local response buffer
  variable */
  LucShiftOrData |= *LpSignalPtr;

  /* Copy data into response buffer from local variable */
  *LpResponseBuffer = LucShiftOrData;

  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)

  /* Decrement application signal pointer */
  LpSignalPtr--;
  /* Decrement response buffer pointer */
  LpResponseBuffer--;

  #else
  /* Increment application signal pointer */
  LpSignalPtr = &LpSignalPtr[1U];

  /* Increment response buffer pointer */
  LpResponseBuffer = &LpResponseBuffer[1U];
  #endif

  /* Get the number of bytes of data in local variable */
  LucShiftOrData = DCM_FOUR;
  /* Loop for number of bytes of data */
  do
  {
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpResponseBuffer = *LpSignalPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* MISRA Rule         : 17.4
       Message            : Increment or decrement operation performed on
                            pointer.
       Reason             : Increment or decrement operator is used to achieve
                            better throughput.
       Verification       : However, part of the code is verified manually and
                            it is not having any impact.
    */
    /* Decrement application signal pointer */
    LpSignalPtr--;
    /* Increment I-PDU buffer pointer */
    LpResponseBuffer++;
    #else
    /* MISRA Rule         : 17.4
       Message            : Increment or decrement operation performed on
                            pointer.
       Reason             : Increment or decrement operator is used to achieve
                            better throughput.
       Verification       : However, part of the code is verified manually and
                            it is not having any impact.
    */
    /* Increment application signal pointer */
    LpSignalPtr++;
  /* MISRA Rule         : 17.4
         Message            : Increment or decrement operation performed on
                              pointer.
         Reason             : Increment operator is used to achieve better
                              throughput.
         Verification       : However, part of the code is verified manually and
                              it is not having any impact.
      */
    /* Increment I-PDU buffer pointer */
    LpResponseBuffer++;
    #endif
    /* Decrement the data byte */
    LucShiftOrData--;
  }while(LucShiftOrData != DCM_ONE);

  /* Get the data from response buffer pointer to local variable */
  LucShiftOrData = *LpResponseBuffer;

  /* Clear signal data from the local  variable by applying end mask */
  LucShiftOrData &= LucEndMask;

  /* Copy higher byte data of word variable to local variable */
  LucShiftOrData |= (LunApplSignalHi.byte_val.BO_Byte[DCM_WORD_MS_BYTE_IDX]);

  /* Copy the local variable value data to local respone buffer */
  *LpResponseBuffer = LucShiftOrData;

  /* Exit protection area */
  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
}

/*******************************************************************************
** Function Name        : Dcm_PackByteOrdering                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal of size more than 8  **
**                        bits, spread across four bytes in response message  **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LddPackSignal, LpResponseData, LpSignalDataPtr      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Dcm_GblProtocolEndianess   **
**                        Function(s) invoked    : SchM_Enter_Dcm()           **
**                                                 SchM_Exit_Dcm()            **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_PackByteOrdering(
   Dcm_PackUnpackSignalData LddPackSignal,
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpResponseData,
   P2CONST(void, AUTOMATIC, DCM_APPL_CONST)LpSignalDataPtr)
{
  Dcm_MIdWord_Access LunSignalValue;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpSignalPtr;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpResponseBuffer;
  uint8 LucSizeOrData;
  uint8 LucNoOfByte;
  uint8 LucEndMask;

  /* Get the pointer to response buffer to a local variable */
  LpResponseBuffer = LpResponseData;

  /* Get the number of bytes of data */
  LucNoOfByte = (LddPackSignal.ucSignalTypeorSize);

  /* Get the size of data */
  LucSizeOrData = (LucNoOfByte & DCM_SIG_SIZE_MASK_VALUE);

  /* Get the number of counts that signal spread across */
  LucNoOfByte = LucNoOfByte & DCM_SIG_BYTE_MASK_VALUE;

  /* Initialize double word variable to zero */
  LunSignalValue.whole_dword = DCM_ZERO;

  /* Check whether signal size is 8 bit */
  if(LucSizeOrData == DCM_SIZE_8)
  {
    /*  Get the signal data to lower byte of double word variable */
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX] =
      *(P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST))LpSignalDataPtr;
  }
  /* Check whether signal size is 16 bit */
  else if(LucSizeOrData == DCM_SIZE_16)
  {
   /* Call the Function to Pack the Bytes */
    Dcm_Pack16(&LunSignalValue, LpSignalDataPtr);
  }
  else
  {
    if((LucNoOfByte == DCM_THREE) && (LddPackSignal.ucShiftBits == DCM_ZERO))
    {
    /* Call the Function to Pack the Bytes */
     Dcm_Pack24(&LunSignalValue, LpSignalDataPtr);
    }
    else
    {
    /* Call the Function to Pack the Bytes */
     Dcm_Pack32(&LunSignalValue, LpSignalDataPtr);
    }
  }
  /* Shift the signal value in double word variable by number of shift bits */
  LunSignalValue.whole_dword <<= (LddPackSignal.ucShiftBits);

  /* Get the local pointer to lower byte of double word variable and assign it
  to local signal pointer */
  LpSignalPtr =
    (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))&LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];
  /* Get the end mask value */
  LucEndMask = LddPackSignal.ucEndMask;
  /* Decrement the signal size */
  LucNoOfByte--;
  /* Enter protection area */
  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();
  /* Get the first byte of response buffer into local variable */
  LucSizeOrData = *LpResponseBuffer;
  /* Clear signal data from the response data by applying start mask */
  LucSizeOrData &= LddPackSignal.ucStartMask;
  /* Write data from signal buffer pointer */
  LucSizeOrData |= *LpSignalPtr;
  /* Copy data from signal pointer to a local variable */
  *LpResponseBuffer = LucSizeOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)

  /* Decrement signal pointer */
  LpSignalPtr--;
  
  /* Increment the response buffer pointer */
  LpResponseBuffer++;
  #else
  
  /* Increment signal pointer */
  LpSignalPtr++;
  
  /* Decrement the response buffer pointer */
  LpResponseBuffer--;
  #endif

  /* Loop for number of bytes of data */
  while(LucNoOfByte != DCM_ONE)
  {
    /* Copy signal data to I-PDU buffer */
    *LpResponseBuffer = *LpSignalPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)

    /* Decrement signal pointer */
    LpSignalPtr--;
    /* Increment response buffer pointer */
    LpResponseBuffer++;
    #else
    /* Increment application signal pointer */
    LpSignalPtr++;

    /* Increment response buffer pointer */
    LpResponseBuffer++;
    #endif
    LucNoOfByte--;
  }
  /* Get the first byte of response buffer into local variable */
  LucSizeOrData = *LpResponseBuffer;

  /* Clear local variable data by applying End Mask to it */
  LucSizeOrData &= LucEndMask;

  /* Get signal data value by applying end mask to local variable
  to clear unoccupied area and write to response buffer  */
  LucSizeOrData |= *LpSignalPtr & ((uint8)(~LucEndMask));

  /* Store local variable to response buffer */
  *LpResponseBuffer = LucSizeOrData;

  /* Exit protection area */
  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
}

/*******************************************************************************
** Function Name        : Dcm_PackFiveByteOrdering                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal of size more than    **
**                        32 bits, spread across five bytes in the response   **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LddPackSignal, LpResponseData, LpSignalDataPtr      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Dcm_GblProtocolEndianess   **
**                        Function(s) invoked    : SchM_Enter_Dcm()           **
**                                                 SchM_Exit_Dcm()            **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_PackFiveByteOrdering(
   Dcm_PackUnpackSignalData LddPackSignal,
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpResponseData,
   P2CONST(void, AUTOMATIC, DCM_APPL_CONST)LpSignalDataPtr)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpResponseBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpSignalPtr;

  Dcm_MIdWord_Access LunSignalValue;
  Dcm_MIWord_Access LunApplSignalHi;
  uint8 LucShiftOrData;
  uint8 LucEndMask;

  /* Get the local pointer to response buffer */
  LpResponseBuffer = LpResponseData;

  /* Call the Function to Pack the Bytes */
  Dcm_Pack32(&LunSignalValue, LpSignalDataPtr);

  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LddPackSignal.ucShiftBits;

  /* Get the end mask value to local variable */
  LucEndMask = LddPackSignal.ucEndMask;

  /* Copy the higher byte of double word variable to the lower byte of word
  variable */
  LunApplSignalHi.whole_word = (uint8)LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX];

  /* Shift the double word variable by the number of shift bits to get start
  position of signal in the response buffer */
  LunSignalValue.whole_dword <<= LucShiftOrData;

  /* Shift the word variable by number of shift bits */
  LunApplSignalHi.whole_word <<= LucShiftOrData;

  /* Apply negate end mask to clear unwanted data in higher byte of word
  variable */
  LunApplSignalHi.byte_val.BO_Byte[DCM_WORD_MS_BYTE_IDX] &= (uint8)(~(LucEndMask));

  /* Get the pointer to lower byte of the double word variable and assign to
  local application signal pointer */
  LpSignalPtr =
     (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))&LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];

  /* Enter protection area */
  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();

  /* Get the data from response buffer pointer to local variable */
  LucShiftOrData = *LpResponseBuffer;

  /* Clear signal data from local response buffer variable by applying start
  mask */
  LucShiftOrData &= LddPackSignal.ucStartMask;

  /* Copy data from application signal pointer to a local response buffer
  variable */
  LucShiftOrData |= *LpSignalPtr;

  /* Copy data into response buffer from local variable */
  *LpResponseBuffer = LucShiftOrData;

  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)

  /* Decrement application signal pointer */
  LpSignalPtr--;
  /* Increment response buffer pointer */
  LpResponseBuffer++;
  #else
  /* MISRA Rule         : 17.4
     Message            : Increment or decrement operation performed on
                          pointer.
     Reason             : Increment or decrement operator is used to achieve
                          better throughput.
     Verification       : However, part of the code is verified manually and
                          it is not having any impact.
  */
  /* Increment application signal pointer */
  LpSignalPtr++;
  /* MISRA Rule         : 17.4
         Message            : Increment or decrement operation performed on
                              pointer.
         Reason             : Increment operator is used to achieve better
                              throughput.
         Verification       : However, part of the code is verified manually and
                              it is not having any impact.
      */
  /* Increment response buffer pointer */
  LpResponseBuffer--;
  #endif

  /* Get the number of bytes of data in local variable */
  LucShiftOrData = DCM_FOUR;
  /* Loop for number of bytes of data */
  do
  {
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpResponseBuffer = *LpSignalPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* Decrement application signal pointer */
    LpSignalPtr--;
      /* Increment response buffer pointer */
    LpResponseBuffer++;
      #else
      /* Increment application signal pointer */
    LpSignalPtr++;
  
    /* Decrement response buffer pointer */
    LpResponseBuffer--;
    #endif
    /* Decrement the data byte */
    LucShiftOrData--;

  }while(LucShiftOrData != DCM_ONE);
  /* Get the data from response buffer pointer to local variable */
  LucShiftOrData = *LpResponseBuffer;

  /* Clear signal data from the local  variable by applying end mask */
  LucShiftOrData &= LucEndMask;

  /* Copy higher byte data of word variable to local variable */
  LucShiftOrData |= (LunApplSignalHi.byte_val.BO_Byte[DCM_WORD_MS_BYTE_IDX]);

  /* Copy the local variable value data to local respone buffer */
  *LpResponseBuffer = LucShiftOrData;

  /* Exit protection area */
  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
}

/*******************************************************************************
** Function Name        : Dcm_PackNBytes                                      **
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
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_Com()           **
**                                                 SchM_Exit_Com()            **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_PackNBytes(
   Dcm_PackUnpackSignalData LddPackSignal,
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpResponseData,
   P2CONST(void, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpResponseBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpSignalPtr;
  uint32 LulSize;
  uint8 LucIpduBuffer;

  /* Get the size of the signal or signal group */
  LulSize = LddPackSignal.ulSignalLength;

  if ((LpSignalDataPtr == NULL_PTR) || (LpResponseData == NULL_PTR))
  {
    /* TODO : Det Error */
  }
  /* Check whether signal size is not equal to zero */
  else if(LulSize != DCM_ZERO)
  {
    /* Get the pointer to application buffer */
    LpSignalPtr = (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA))LpSignalDataPtr;

    /* Get the pointer to an I-PDU buffer */
    LpResponseBuffer = LpResponseData;

    /* Enter protection area */
    SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();


    /* Get the data from the I-PDU buffer pointer to a local I-PDU buffer
    variable */
    LucIpduBuffer = *LpResponseBuffer;

    
    /* Apply the start mask to local I-PDU buffer variable */
    LucIpduBuffer &= LddPackSignal.ucStartMask;


    /* Copy the application  data to local I-PDU buffer variable */
    LucIpduBuffer |= *LpSignalPtr;
    
    /* Write the application data back to I-PDU buffer */
    *LpResponseBuffer = LucIpduBuffer;

    /* Increment the application pointer */

    LpSignalPtr = &LpSignalPtr[1u];

    /* Increment the WrBuffer pointer */

    LpResponseBuffer = &LpResponseBuffer[1u];
    /* Decrement the size size */
    LulSize--;
    if(LulSize > DCM_ONE)
    {
      /* Check whether size of the signal is not equal to one */
      while(LulSize != DCM_ONE)
      {

        /* Copy the application buffer data to I-PDU buffer pointer */
        *LpResponseBuffer = *LpSignalPtr;
  
        /* Get the pointer to next application buffer */
        LpSignalPtr = &LpSignalPtr[1u];

        /* Get the pointer to next I-PDU buffer */
        LpResponseBuffer = &LpResponseBuffer[1u];
        /* Decrement the signal size count */
        LulSize--;
      }
    }

    /* Get the value of I-PDU buffer to a local I-PDU buffer variable */
    LucIpduBuffer = *LpResponseBuffer;

    /* Apply the end mask to local I-PDU buffer variable to clear unoccupied
    areas */
    LucIpduBuffer &= LddPackSignal.ucEndMask;


    /* Copy the application  data to local variable */
    LucIpduBuffer |= *LpSignalPtr;

    
    /* Copy the local I-PDU buffer variable data to the I-PDU buffer */
    *LpResponseBuffer = LucIpduBuffer;

    /* Exit protection area */
    SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
  }/* Check whether signal size is not equal to zero */
  else
  {
    /* For Misra-C check */
  }
}

/*******************************************************************************
** Function Name        : Dcm_UnPack16                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function Unpacks the signal of 16 Bytes        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSignalDataPtr, LunSignalValue                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UnPack16(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr,
  Dcm_MIdWord_Access LunSignalValue)
{

  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[0u] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX];

  
  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_ONE] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];
  #else
  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[0u] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];

  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_ONE] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX];
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_UnPack24                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function Unpacks the signal of 24 bits         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSignalDataPtr, LunSignalValue                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UnPack24(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr,
  Dcm_MIdWord_Access LunSignalValue)
{
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[0u] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX];

  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_ONE] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX];

  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_TWO] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];
  #else
  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[0u] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];

  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_ONE] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX];

  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_TWO] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX];
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_UnPack32                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function Unpacks the signal of 32 Bytes        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSignalDataPtr, LunSignalValue                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UnPack32(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr,
  Dcm_MIdWord_Access LunSignalValue)
{
 #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[0u] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX];

  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_ONE] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX];

  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_TWO] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX];

  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_THREE] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];
  #else
  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[0u] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX];

  
  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_ONE] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX];

  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_TWO] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX];

  /* Copy the lower word of double word variable to signal data pointer */
  LpSignalDataPtr[DCM_THREE] =
    LunSignalValue.byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX];
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_Pack16                                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function Packs the signal of 16 Bytes          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSignalDataPtr, LunSignalValue                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pack16(
Dcm_MIdWord_Access *LunSignalValue,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr)
{
 #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
   /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX] = LpSignalDataPtr[(uint8)DCM_ZERO];

  /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX] = LpSignalDataPtr[DCM_ONE];

  #else
   /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX] = LpSignalDataPtr[(uint8)DCM_ZERO];

  /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX] = LpSignalDataPtr[DCM_ONE];

  #endif
}

/*******************************************************************************
** Function Name        : Dcm_Pack24                                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal of 24 Bytes          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSignalDataPtr, LunSignalValue                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pack24(
  Dcm_MIdWord_Access *LunSignalValue,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr)
{
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)

    /*  Get the signal data to lower word of double word variable */
    LunSignalValue->byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX] = (uint8) DCM_ZERO;
  
    /*  Get the signal data to lower word of double word variable */
    LunSignalValue->byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX] = LpSignalDataPtr[(uint8)DCM_ZERO];
  
    /*  Get the signal data to lower word of double word variable */
    LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX] = LpSignalDataPtr[DCM_ONE];
  
    /*  Get the signal data to lower word of double word variable */
    LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX] = LpSignalDataPtr[DCM_TWO];

  #else
     /*  Get the signal data to lower word of double word variable */
    LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX] = LpSignalDataPtr[(uint8)DCM_ZERO];
  
    /*  Get the signal data to lower word of double word variable */
    LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX] = LpSignalDataPtr[DCM_ONE];
  
    /*  Get the signal data to lower word of double word variable */
    LunSignalValue->byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX] = LpSignalDataPtr[DCM_TWO];
  
    /*  Get the signal data to lower word of double word variable */
    LunSignalValue->byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX] = DCM_ZERO;

  #endif
}

/*******************************************************************************
** Function Name        : Dcm_Pack32                                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal of 32 Bytes          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSignalDataPtr, LunSignalValue                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pack32(
  Dcm_MIdWord_Access *LunSignalValue,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA)LpSignalDataPtr)
{
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)

  /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX] = LpSignalDataPtr[(uint8)DCM_ZERO];

  /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX] = LpSignalDataPtr[DCM_ONE];

  /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX] = LpSignalDataPtr[DCM_TWO];

  /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX] = LpSignalDataPtr[DCM_THREE];

  #else
   /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_BYTE_IDX] = LpSignalDataPtr[(uint8)DCM_ZERO];

  /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_LS_MID_BYTE_IDX] = LpSignalDataPtr[DCM_ONE];

  /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_MS_MID_BYTE_IDX] = LpSignalDataPtr[DCM_TWO];

  /*  Get the signal data to lower word of double word variable */
  LunSignalValue->byte_val.BO_Byte[DCM_DWORD_MS_BYTE_IDX] = LpSignalDataPtr[DCM_THREE];

  #endif
  
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
* PRE-JUSTIFICATION END SECTION (MISRA-C RULE CHECKER)
*******************************************************************************/
/*
  polyspace:end<MISRA-C:8.10:Not a defect:Justify with annotations> hether the Dcm api function is required internal or external linkage, depends on user configuration
  polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations> Not a defect, This is to achieve throughput in the code

  polyspace:end<MISRA-C:11.5:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : NVM455, EA087)
  polyspace:end<MISRA-C:16.7:Not a defect:Justify with annotations> A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object.
  polyspace:end<MISRA-C:17.4:Not a defect:Justify with annotations> This code is not a defect
  polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable
  polyspace:end<RTE: OVFL : Not a defect : No Action Planned > Overflow can not occur
  polyspace:end<RTE: SHF : Not a defect : No Action Planned > amount can not be outside its bounds
  polyspace:end<RTE: IDP : Not a defect : No Action Planned > configured memory access index
*/
/* polyspace-end MISRA-C3:18.1 [Justify with annotations:Unset] "size of array is determined by configuration" */
/* polyspace-end MISRA-C3:D4.1 [Justify with annotations:Unset] "range is pre-defined" */
/* polyspace-end MISRA-C3:11.5 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-end CERT-C:EXP36-C [Justified:Low] "Module do not know user data type so before using user data, pointer need to be cast" */
/* polyspace-end CERT-C:EXP05-C [Justified:Low] "Module do not know user data type so before using user data, pointer need to be cast" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
