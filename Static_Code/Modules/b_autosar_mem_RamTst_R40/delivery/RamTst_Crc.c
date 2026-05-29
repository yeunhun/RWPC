/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_Crc.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Ram Test Module                                               **
**                                                                            **
**  PURPOSE   : Implementation for CRC functions of RamTst Module             **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date            By                  Description                  **
********************************************************************************
** 1.3.2     30-Dec-2020   CY Song    RedMine #27378                          **
** 1.2.7     15-Nov-2015   CY Song    Redmine #6608                           **
** 1.2.5     16-May-2016   CY Song    RedMine #4902                           **
** 1.2.3     05-Oct-2015   CY Song    Correct Misra Rule Error                **
** 1.0.3     06-Dec-2013   CY Song        Modify CRC32 Compile Error          **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
polyspace:begin<RTE: NIV : Not a defect : Justify with annotations > Cannot initialize because of Application variable
polyspace:begin<RTE: IDP : Not a defect : Justify with annotations > configured memory access index
*/

/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Value shall be cheched by user" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst.h"              /* Ram Test Module Header File */
#include "RamTst_Ram.h"          /* Ram Test Module Header File */
#include "RamTst_Crc.h"                     /* Crc Header file */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
#if(RAMTST_CRC_16_SUPPORT == STD_ON)
static FUNC(uint16, RAMTST_CODE) RAMTST_BYTE_ORDER_PATCH_16
                                  (uint8 RamTst_Msbbyte, uint8 RamTst_Lsbbyte);
#endif
#if(RAMTST_CRC_32_SUPPORT == STD_ON)
static FUNC(uint32, RAMTST_CODE) RAMTST_BYTE_ORDER_PATCH_32
                                  (uint8 RamTst_Msbbyte, uint8 RamTst_Midhigh,
                                   uint8 RamTst_Midlow, uint8 RamTst_Lsbbyte);

static FUNC(void, RAMTST_CODE) RAMTST_BYTE_ORDER_DISPATCH_32(uint32 RamTst_Val);
#endif

#if(RAMTST_CRC_32_SUPPORT == STD_ON)
static FUNC(uint32, RAMTST_CODE) RamTst_CrcReflect(uint32 LulData,
  CONST(uint8, RAMTST_CONST) LucNbits);
#endif

#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"

#if(CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
/*******************************************************************************
** Function Name        : RAMTST_BYTE_ORDER_PATCH_16                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the uint16 variable           **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : RamTst_Msbbyte, RamTst_Lsbbyte                      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LusVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(RAMTST_CRC_16_SUPPORT == STD_ON)
static FUNC(uint16, RAMTST_CODE) RAMTST_BYTE_ORDER_PATCH_16
                     (uint8 RamTst_Msbbyte, uint8 RamTst_Lsbbyte)
{
  uint16 LusVal;
  LusVal = (uint16)RamTst_Lsbbyte;
  LusVal = ((uint16)LusVal << RAMTST_EIGHT);
  LusVal = ((uint16)LusVal | RamTst_Msbbyte);
  return LusVal;
}
#endif
/*******************************************************************************
** Function Name        : RAMTST_BYTE_ORDER_PATCH_32                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the uint32 variable           **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : RamTst_Msbbyte, RamTst_Lsbbyte  , RamTst_Midhigh    **
**                        RamTst_Midlow                                       **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LulVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(RAMTST_CRC_32_SUPPORT == STD_ON)
static FUNC(uint32, RAMTST_CODE) RAMTST_BYTE_ORDER_PATCH_32(uint8 RamTst_Msbbyte, 
              uint8 RamTst_Midhigh, uint8 RamTst_Midlow, uint8 RamTst_Lsbbyte)
{
  uint32 LulVal;
  LulVal = (uint32) RamTst_Lsbbyte;
  LulVal = (LulVal << RAMTST_EIGHT);
  LulVal = (LulVal | RamTst_Midlow);
  LulVal = (LulVal << RAMTST_EIGHT);
  LulVal = (LulVal | RamTst_Midhigh);
  LulVal = (LulVal << RAMTST_EIGHT);
  LulVal = (LulVal | RamTst_Msbbyte);
  return LulVal;
}
/*******************************************************************************
** Function Name        : RAMTST_BYTE_ORDER_DISPATCH_32                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the bytes                     **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : RamTst_Val                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
**                                                                            **
** Remarks              : Global Variable(s)     : RamTst_GucMsb,             **
**                         RamTst_GucMidHi, RamTst_GucMidLow, RamTst_GucLsb   **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
static FUNC(void, RAMTST_CODE) RAMTST_BYTE_ORDER_DISPATCH_32(uint32 RamTst_Val)
{
  RamTst_GucMsb = ((uint8)RamTst_Val & (uint8)RAMTST_FF);
  RamTst_GucMidHi = ((uint8)((uint32)RamTst_Val >> RAMTST_EIGHT)
                               &(uint8)RAMTST_FF);
  RamTst_GucMidLow = ((uint8)((uint32)RamTst_Val >> RAMTST_SIXTEEN)
                               &(uint8)RAMTST_FF);
  RamTst_GucLsb = ((uint8)((uint32)RamTst_Val >> RAMTST_TWENTYFOUR)
                               &(uint8)RAMTST_FF);
}
#endif

#else
/*******************************************************************************
** Function Name        : RAMTST_BYTE_ORDER_PATCH_16                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the uint16 variable           **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : RamTst_Msbbyte, RamTst_Lsbbyte                      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LusVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(RAMTST_CRC_16_SUPPORT == STD_ON)
static FUNC(uint16, RAMTST_CODE) RAMTST_BYTE_ORDER_PATCH_16
                     (uint8 RamTst_Msbbyte, uint8 RamTst_Lsbbyte)
{
  uint16 LusVal;
  LusVal = (uint16)RamTst_Msbbyte;
  LusVal = (uint16)((uint16)LusVal << RAMTST_EIGHT);
  LusVal = (uint16)((uint16)LusVal | RamTst_Lsbbyte);
  return LusVal;
}
#endif
/*******************************************************************************
** Function Name        : RAMTST_BYTE_ORDER_PATCH_32                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the uint32 variable           **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : RamTst_Msbbyte, RamTst_Lsbbyte  , RamTst_Midhigh    **
**                        RamTst_Midlow                                       **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LulVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(RAMTST_CRC_32_SUPPORT == STD_ON)
static FUNC(uint32, RAMTST_CODE) RAMTST_BYTE_ORDER_PATCH_32(uint8 RamTst_Msbbyte, 
              uint8 RamTst_Midhigh, uint8 RamTst_Midlow, uint8 RamTst_Lsbbyte)
{
  uint32 LulVal;
  LulVal = (uint32) RamTst_Msbbyte;
  LulVal = (LulVal << RAMTST_EIGHT);
  LulVal = (LulVal | RamTst_Midhigh);
  LulVal = (LulVal << RAMTST_EIGHT);
  LulVal = (LulVal | RamTst_Midlow);
  LulVal = (LulVal << RAMTST_EIGHT);
  LulVal = (LulVal | RamTst_Lsbbyte);
  return LulVal;
}

/*******************************************************************************
** Function Name        : RAMTST_BYTE_ORDER_DISPATCH_32                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the bytes                     **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : RamTst_Val                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
**                                                                            **
** Remarks              : Global Variable(s)     : RamTst_GucMsb,             **
**                         RamTst_GucMidHi, RamTst_GucMidLow, RamTst_GucLsb   **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
static FUNC(void, RAMTST_CODE) RAMTST_BYTE_ORDER_DISPATCH_32(uint32 RamTst_Val)
{
  RamTst_GucLsb = ((uint8)RamTst_Val & (uint8)RAMTST_FF);
  RamTst_GucMidLow = ((uint8)((uint32)RamTst_Val>>RAMTST_EIGHT)
                                     &(uint8)RAMTST_FF);
  RamTst_GucMidHi = ((uint8)((uint32)RamTst_Val>>RAMTST_SIXTEEN)
                                     &(uint8)RAMTST_FF);
  RamTst_GucMsb = ((uint8)((uint32)RamTst_Val>>RAMTST_TWENTYFOUR)
                                     &(uint8)RAMTST_FF);
}
#endif /* (RAMTST_CRC_32_SUPPORT == STD_ON) */
#endif /* End if(CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */

/*******************************************************************************
** Function Name        : RamTst_CalculateCRC8                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the 8 bit checksum calculated **
**                        by runtime method.                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : RamTst_DataPtr, RamTst_Length                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : 8 bit result of CRC calculation                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#if(RAMTST_CRC_8_SUPPORT == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, RAMTST_CODE) RamTst_CalculateCRC8
(P2CONST(uint8, RAMTST_CONST, RAMTST_APPL_CONST)RamTst_DataPtr,
uint32 RamTst_Length, uint8 RamTst_CrcStartValue8,
                                                  boolean RamTst_CrcIsFirstCall)
{
  /* Pointer to data byte */
  P2CONST(uint8, RAMTST_CONST, RAMTST_CONST) LpDataPtr;
  /* Variable to hold CRC Length */
  uint32 LulCrcLen;
  /* Variable to hold data byte */
  uint8 LucNxtDataWord;
  /* Start value CRC result */
  uint8 LucCrcRegister;
  /* Counter for Pointer Address */
  uint32 LulCount;
  /* Counter for no. of bits */
  uint8 LucLoopIndex;

  /* Local Copy of Length Parameter */
  LulCrcLen = RamTst_Length;

  /* Check if it is the first function call */
  if(RamTst_CrcIsFirstCall != (boolean)RAMTST_FALSE)
  {
    /* Initial value for 8bit */
    LucCrcRegister = RAMTST_CRC_INITIAL_VALUE8;
  }
  else
  {
    /* Initialize CRC result  with previous result */
    LucCrcRegister = (RamTst_CrcStartValue8 ^ RAMTST_CRC_XOR_OUT8);
  }
  /* Initialize count */
  LulCount = RAMTST_ZERO;
  /* Local copy of pointer to start of data */
  LpDataPtr = RamTst_DataPtr;
  /* Loop for no. of data bytes */
  while(LulCrcLen > (uint32)RAMTST_CRC_ZERO)
  {
    /* Copy the data byte into local variable */
    /* polyspace<RTE: IDP : Not a defect : Justify with annotations > configured memory access index */
    /* polyspace<MISRA-C:21.1:Not a defect:No action planned> Configured memory address  */
    LucNxtDataWord = LpDataPtr[LulCount];
    /* Perform XOR of data byte with CRC result */
    LucCrcRegister = (LucCrcRegister ^ LucNxtDataWord);
    /* Reinitialize Loop Index */
    LucLoopIndex = RAMTST_CRC_EIGHT;
    /* Loop for 8 bits */
    while(LucLoopIndex > RAMTST_CRC_ZERO)
    {
      /* Check if MSB is set */
      if(RAMTST_CRC_MSB8 == (LucCrcRegister & RAMTST_CRC_MSB8))
      {
        /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Intended code" */
        LucCrcRegister =
                ((uint8)(LucCrcRegister << (uint8)RAMTST_CRC_ONE) ^ RAMTST_CRC_POLY8);
      }
      else
      {
        /* If MSB is unset */
        LucCrcRegister = (LucCrcRegister << (uint8)RAMTST_CRC_ONE);
      }
      LucLoopIndex--;
    } /* End while(LucLoopIndex > RAMTST_CRC_ZERO) */

    /* Decrement the count of the no. of bytes */
    LulCrcLen--;

    /* array index to next data byte */
    LulCount++;
  } /* End while(LulCrcLen > (uint32)RAMTST_ZERO) */

  /* XOR final value with 0xFF */
  LucCrcRegister = (LucCrcRegister ^ RAMTST_CRC_XOR_OUT8);
  /* Return the CRC result */
  return (LucCrcRegister);
}
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : RamTst_CalculateCRC8H2F                             **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This function returns the 8 bit checksum calculated **
**                        using polynomial 0x2F by runtime and table method.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy           : Reentrant                                          **
**                                                                            **
** Input Parameters     : RamTst_DataPtr, RamTst_Length                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : 8 bit result of CRC for polynomial calculation      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(RAMTST_CRC_8H2F_SUPPORT == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, RAMTST_CODE) RamTst_CalculateCRC8H2F
(P2CONST(uint8, RAMTST_CONST, RAMTST_APPL_CONST)RamTst_DataPtr,
uint32 RamTst_Length, uint8 RamTst_CrcStartValue8H2F,
                                                 boolean RamTst_CrcIsFirstCall)
{
  /* Pointer to data byte */
  P2CONST(uint8, RAMTST_CONST, RAMTST_CONST) LpDataPtr;
  /* Variable to hold CRC Length */
  uint32 LulCrcLen;
  /* Variable to hold data byte */
  uint8 LucNxtDataWord;
  /* Start value or Initial value of CRC result as passed by NVRAM Manager */
  uint8 LucCrcRegister;
  /* Counter for Pointer Address */
  uint32 LulCount;
  uint8 LucLoopIndex;

  /* Local Copy of Length Parameter */
  LulCrcLen = RamTst_Length;

  /* Check if it is the first function call */
  if(RamTst_CrcIsFirstCall == (boolean)RAMTST_CRC_TRUE)
  {
    /* Initial value for 8bit 0x2F */
    LucCrcRegister = RAMTST_CRC_INITIAL_VALUE8H2F;
  }
  else
  {
    /* Initialize CRC result  with previous result */
    LucCrcRegister = (RamTst_CrcStartValue8H2F ^ RAMTST_CRC_XOR_OUT8H2F);
  }
  /* Initialize count */
  LulCount = RAMTST_ZERO;
  /* Local copy of pointer to start of data */
  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "It shall be checked by user" */  
  LpDataPtr = RamTst_DataPtr;
  /* Loop for no. of data bytes */
  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "It shall be checked by user" */  
  while(LulCrcLen > (uint32)RAMTST_CRC_ZERO)
  {
    /* Copy the data byte into local variable */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "It shall be checked by user" */
    LucNxtDataWord = LpDataPtr[LulCount];
    /* Perform XOR of data byte with CRC result */
    LucCrcRegister = (LucCrcRegister ^ LucNxtDataWord);

    /* Reinitialize Loop Index */
    LucLoopIndex = RAMTST_CRC_EIGHT;
    /* Loop for 8 bits */
    while(LucLoopIndex > RAMTST_CRC_ZERO)
    {
      /* Check if MSB is set */
      if(RAMTST_CRC_MSB8 == (LucCrcRegister & RAMTST_CRC_MSB8))
      {
        /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Intended code" */      
        LucCrcRegister =
              ((uint8)(LucCrcRegister << (uint8)RAMTST_CRC_ONE) ^ RAMTST_CRC_POLY8H2F);
      }
      else
      {
        /* If MSB is unset */
        LucCrcRegister = (LucCrcRegister << (uint8)RAMTST_CRC_ONE);
      }
      LucLoopIndex--;
    } /* End while(LucLoopIndex > RAMTST_ZERO) */

    /* Decrement the count of the no. of bytes */
    LulCrcLen--;

    /* array index to next data byte */
    LulCount++;
  } /* End while(LulCrcLen > (uint32)RAMTST_ZERO) */

  /* XOR final value with 0xFF */
  LucCrcRegister = (LucCrcRegister ^ RAMTST_CRC_XOR_OUT8H2F);
  /* Return the CRC result */
  return (LucCrcRegister);
}
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : RamTst_CalculateCRC16                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the 16 bit checksum calculated**
**                        by runtime and table based method.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy           : Reentrant                                          **
**                                                                            **
** Input Parameters     : RamTst_DataPtr, RamTst_Length                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : 16 bit result of CRC calculation                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(RAMTST_CRC_16_SUPPORT == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, RAMTST_CODE) RamTst_CalculateCRC16
  (P2CONST(uint8, RAMTST_CONST, RAMTST_APPL_CONST)RamTst_DataPtr,
  uint32 RamTst_Length, uint16 RamTst_CrcStartValue16,
                                                  boolean RamTst_CrcIsFirstCall)
{
  /* Pointer to hold data byte */
  P2CONST(uint8, RAMTST_CONST, RAMTST_CONST) LpDataPtr;

  /* object of type RamTst_Crc_Word16 to hold start value */
  RamTst_Crc_Word16 LunCrc16;

  /* Variable to hold CRC Length */
  uint32 LulCrcLen;
  
  /* Counter for array index */
  uint32 LulCount;


  /* object of type RamTst_Crc_Word16 to hold data byte */
  RamTst_Crc_Word16 LunNxtData;
  /* Counter for no. of bits */
  uint8 LucLoopIndex;

  LulCrcLen = RamTst_Length;

  /* Check if it is the first function call */
  if(RamTst_CrcIsFirstCall == (boolean)RAMTST_CRC_TRUE)
  {
    /* Initial value for 16bit */
    LunCrc16.WordReg16 = RAMTST_CRC_INITIAL_VALUE16;
  }
  else
  {
    /* Initialize CRC result  with previous result */
    LunCrc16.WordReg16 = RamTst_CrcStartValue16;
  }
  /* Initialize count */
  LulCount = RAMTST_ZERO;
  /* Local copy of pointer to start of data */
  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "It shall be checked by user" */    
  LpDataPtr = RamTst_DataPtr;
  /* Loop for no. of data bytes */
  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "It shall be checked by user" */    
  while(LulCrcLen > (uint32)RAMTST_CRC_ZERO)
  {
    /* Copy the data byte into MsByte */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "It shall be checked by user" */  
    LunNxtData.MsByteForWord16 = LpDataPtr[LulCount];
    /* Pad zero into LsByte */
    LunNxtData.LsByteForWord16 = RAMTST_ZERO;
    LunNxtData.WordReg16 = RAMTST_BYTE_ORDER_PATCH_16(LunNxtData.MsByteForWord16, LunNxtData.LsByteForWord16);
    /* Perform XOR of entire data byte with CRC result */   
    LunCrc16.WordReg16 = (LunCrc16.WordReg16 ^ LunNxtData.WordReg16);
    
    /* Reinitialize Loop Index */
    LucLoopIndex = RAMTST_CRC_EIGHT;
    /* Loop for 8 bits */
    while(LucLoopIndex > RAMTST_CRC_ZERO)
    {
      /* Check if MSB is set */
      if(RAMTST_CRC_MSB16 == (LunCrc16.WordReg16 & RAMTST_CRC_MSB16))
      {
        /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Intended code" */      
        LunCrc16.WordReg16 = ((uint16)(LunCrc16.WordReg16 << (uint16)RAMTST_CRC_ONE) ^
          RAMTST_CRC_POLY16);
      }
      else
      {
        /* If MSB is unset */
        LunCrc16.WordReg16 = (LunCrc16.WordReg16 << (uint16)RAMTST_CRC_ONE);
      }
      LucLoopIndex--;
    } /* End while(LucLoopIndex > RAMTST_CRC_ZERO) */

    /* Decrement the count of the no. of bytes */
    LulCrcLen--;
    /* array index to next data byte */
    LulCount++;
  } /* End while(LulCrcLen > (uint32)RAMTST_CRC_ZERO) */

  /* Return the CRC result */
  return (LunCrc16.WordReg16);
}
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : RamTst_CalculateCRC32                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the 32 bit checksum calculated**
**                        by runtime method.                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : RamTst_DataPtr, RamTst_Length                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : 32 bit result of CRC calculation                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : RamTst_CrcReflect          **
*******************************************************************************/
#if(RAMTST_CRC_32_SUPPORT == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
FUNC(uint32, RAMTST_CODE) RamTst_CalculateCRC32
  (P2CONST(uint8, RAMTST_CONST, RAMTST_APPL_CONST)RamTst_DataPtr,
  uint32 RamTst_Length, uint32 RamTst_CrcStartValue32,
                                                  boolean RamTst_CrcIsFirstCall)
{
  /* Pointer to data byte */
  P2CONST(uint8, RAMTST_CONST, RAMTST_CONST) LpDataPtr;

  /* Create a object of type Crc_Dword32 */
  RamTst_Crc_Dword32 LunCrc32;

  /* Variable to hold CRC Length */
  uint32 LulCrcLen;

  /* Counter for array index */
  uint32 LulCount;

  /* Create a object of type Crc_Dword32 */
  RamTst_Crc_Dword32 LunNxtData;
  /* Counter for no. of bits */
  uint8 LucLoopIndex;

  LulCrcLen = RamTst_Length;

  /* Check if it is the first function call */
  if(RamTst_CrcIsFirstCall == (boolean)RAMTST_CRC_TRUE)
  {
    /* Initial value for 32bit */
    LunCrc32.LongReg32 = RAMTST_CRC_INITIAL_VALUE32;
  }
  else
  {
    /* Initialize CRC result  with previous result's reflected value */
    LunCrc32.LongReg32 = RamTst_CrcReflect((RamTst_CrcStartValue32 ^ RAMTST_CRC_XOR_OUT32),
      RAMTST_CRC_THIRTYTWO);
  }
  /* Initialize count */
  LulCount = RAMTST_ZERO;
  /* Local copy of pointer to start of data */
  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "It shall be checked by user" */    
  LpDataPtr = RamTst_DataPtr;
  /* Loop for no. of data bytes */
  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "It shall be checked by user" */
  while(LulCrcLen > (uint32)RAMTST_CRC_ZERO)
  {
    /* 32 bit field filled with zero */
    LunNxtData.LongReg32 = (uint32)RAMTST_ZERO;
    RAMTST_BYTE_ORDER_DISPATCH_32(LunNxtData.LongReg32);
    /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "Not a defect" */
    LunNxtData.MsByteFor32 = RamTst_GucMsb;
    LunNxtData.MidHiByteFor32 = RamTst_GucMidHi;
    LunNxtData.MidLowByteFor32 = RamTst_GucMidLow;
    LunNxtData.LsByteFor32 = RamTst_GucLsb;

    /* Store next data byte into MSB, simulating left shift by 24 bits */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "It shall be checked by user" */
    LunNxtData.MsByteFor32 = LpDataPtr[LulCount];
    /* Call to Reflect input data around central bit */
    LunNxtData.MsByteFor32 = (uint8)RamTst_CrcReflect(LunNxtData.MsByteFor32,
      RAMTST_EIGHT);
    LunNxtData.LongReg32=RAMTST_BYTE_ORDER_PATCH_32(LunNxtData.MsByteFor32,
                       LunNxtData.MidHiByteFor32, LunNxtData.MidLowByteFor32,
                       LunNxtData.LsByteFor32);
    LunCrc32.LongReg32 = (LunCrc32.LongReg32 ^ LunNxtData.LongReg32);
    /* Loop for Mod-2 division for each bit */
    LucLoopIndex = RAMTST_CRC_EIGHT;
    /* Loop for 8 bits */
    while(LucLoopIndex > RAMTST_CRC_ZERO)
    {
      /* Check if MSB is set */
      if(RAMTST_CRC_MS_BIT_LWORD ==
                                 (LunCrc32.LongReg32 & RAMTST_CRC_MS_BIT_LWORD))
      {
        /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Intended code" */
        LunCrc32.LongReg32 =
                   ((LunCrc32.LongReg32 << RAMTST_CRC_ONE) ^ RAMTST_CRC_POLY32);
      }
      else
      {
        /* If MSB is unset */
        LunCrc32.LongReg32 = (LunCrc32.LongReg32 << RAMTST_CRC_ONE);
      }
      LucLoopIndex--;
    } /* End while(LucLoopIndex > RAMTST_CRC_ZERO) */

    /* Decrement the count of the no. of bytes */
    LulCrcLen--;
    /* array index to next data byte */
    LulCount++;
  } /* End while(LulCrcLen > (uint32)RAMTST_CRC_ZERO) */

  /* Reflect final checksum and XOR with 0xFFFFFFFFUL */
  LunCrc32.LongReg32 =
                    RamTst_CrcReflect(LunCrc32.LongReg32, RAMTST_CRC_THIRTYTWO);

  /* XOR final value with 0xFFFFFFFFUL */
  LunCrc32.LongReg32 = (LunCrc32.LongReg32 ^ RAMTST_CRC_XOR_OUT32);
  /* Return the reflected data */
  return (LunCrc32.LongReg32);
}
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : RamTst_CrcReflect                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the symmetric reflection      **
**                        of input.                                           **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : LulData, LucNbits                                   **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LulReflection                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(RAMTST_CRC_32_SUPPORT == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"

static FUNC(uint32, RAMTST_CODE) RamTst_CrcReflect
  (uint32 LulData, CONST(uint8, RAMTST_CONST) LucNbits)
{
  /* Value of reflection */
  uint32 LulReflection;
  /* Value of MS bit */
  uint32 LulBit;
  /* Count of no. of bits */
  uint8 LucBitCount;

  uint32 LulSrcData = LulData;
  
  /* Initial value of reflection */
  LulReflection = (uint32)RAMTST_CRC_ZERO;
  /* Start of count */
  LucBitCount = RAMTST_CRC_ZERO;
  /* Check for no. of bits */
  if(LucNbits == RAMTST_CRC_EIGHT)
  {
    /* Set MS bit for one byte data  */
    LulBit = RAMTST_CRC_MSB8;
  }
  else
  {
    /* Set MS bit for Long word data */
    LulBit = RAMTST_CRC_MS_BIT_LWORD;
  }
  while(LucBitCount != LucNbits)
  {
    /* AND data with 0x01L to check if the LSB of data is set */
    if(0x1UL == (LulSrcData & 0x1UL))
    {
      /* Take mirror image of nth bit at bit position (Nbits-n) */
      LulReflection = LulReflection | LulBit;
    }
    /* Right shift by one bit */
    LulBit = LulBit >> RAMTST_CRC_ONE;
    LulSrcData = LulSrcData >> RAMTST_CRC_ONE;
    /* Increment bit count */
    LucBitCount++;
  }
  /* Return the reflected data */
  return (LulReflection);
}

#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif


/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Value shall be cheched by user" */

/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/*
polyspace:end<RTE: NIV : Not a defect : Justify with annotations > Cannot initialize because of Application variable
polyspace:end<RTE: IDP : Not a defect : Justify with annotations > configured memory access index
*/
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
