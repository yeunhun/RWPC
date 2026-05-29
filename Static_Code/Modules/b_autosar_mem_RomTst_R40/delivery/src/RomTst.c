/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RomTst.c                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR ROMTST                                                **
**                                                                            **
**  PURPOSE   : Rom Test API Functionality                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By       Description                               **
********************************************************************************
** 1.0.0     16-May-2016   JS Park    RedMine #5149                           **
********************************************************************************
** 1.1.0     10-Nov-2016   JS Park    RedMine #6499                           **
********************************************************************************
** 1.1.1     20-Jun-2019   JS Park    RedMine #18014                          **
********************************************************************************
** 1.2.3     30-Dec-2020   YJ Yun     RedMine #27410                          **
********************************************************************************
** 1.3.0     20-May-2021   YJ Yun     RedMine #28457                          **
********************************************************************************
** 1.4.0     22-Nov-2021   JH Lim     RedMine #31510, #33116                  **
********************************************************************************
** 1.4.1     24-Dec-2021   JH Lim     RedMine #33330                          **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RomTst.h"
#include "WdgStack_Callout.h"
#include "Dem.h"
#include "BswM.h"
#include "HwResource.h"
#include "SchM_RomTst.h" /* ActiveTask */

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

#if ((ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS) || (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS))
#define ROMTST_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Variables definition */
/* polyspace-begin VARIABLE:ALL [Justified:Low] "This variable is used to calculate CRC value of ROM section" */
/* polyspace-begin MISRA-C3:8.9 [Justified:Low] "This variable is Used in different functions according to configuration" */
static CONST(uint16, ROMTST_VAR_INIT) RomTst_TabCRCA001_1[ROMTST_CRCTB_LENGTH] =
{
  0x0000U , 0xC0C1U , 0xC181U , 0x0140U , 0xC301U , 0x03C0U , 0x0280U , 0xC241U ,
  0xC601U , 0x06C0U , 0x0780U , 0xC741U , 0x0500U , 0xC5C1U , 0xC481U , 0x0440U ,
  0xCC01U , 0x0CC0U , 0x0D80U , 0xCD41U , 0x0F00U , 0xCFC1U , 0xCE81U , 0x0E40U ,
  0x0A00U , 0xCAC1U , 0xCB81U , 0x0B40U , 0xC901U , 0x09C0U , 0x0880U , 0xC841U ,
  0xD801U , 0x18C0U , 0x1980U , 0xD941U , 0x1B00U , 0xDBC1U , 0xDA81U , 0x1A40U ,
  0x1E00U , 0xDEC1U , 0xDF81U , 0x1F40U , 0xDD01U , 0x1DC0U , 0x1C80U , 0xDC41U ,
  0x1400U , 0xD4C1U , 0xD581U , 0x1540U , 0xD701U , 0x17C0U , 0x1680U , 0xD641U ,
  0xD201U , 0x12C0U , 0x1380U , 0xD341U , 0x1100U , 0xD1C1U , 0xD081U , 0x1040U ,
  0xF001U , 0x30C0U , 0x3180U , 0xF141U , 0x3300U , 0xF3C1U , 0xF281U , 0x3240U ,
  0x3600U , 0xF6C1U , 0xF781U , 0x3740U , 0xF501U , 0x35C0U , 0x3480U , 0xF441U ,
  0x3C00U , 0xFCC1U , 0xFD81U , 0x3D40U , 0xFF01U , 0x3FC0U , 0x3E80U , 0xFE41U ,
  0xFA01U , 0x3AC0U , 0x3B80U , 0xFB41U , 0x3900U , 0xF9C1U , 0xF881U , 0x3840U ,
  0x2800U , 0xE8C1U , 0xE981U , 0x2940U , 0xEB01U , 0x2BC0U , 0x2A80U , 0xEA41U ,
  0xEE01U , 0x2EC0U , 0x2F80U , 0xEF41U , 0x2D00U , 0xEDC1U , 0xEC81U , 0x2C40U ,
  0xE401U , 0x24C0U , 0x2580U , 0xE541U , 0x2700U , 0xE7C1U , 0xE681U , 0x2640U ,
  0x2200U , 0xE2C1U , 0xE381U , 0x2340U , 0xE101U , 0x21C0U , 0x2080U , 0xE041U ,
  0xA001U , 0x60C0U , 0x6180U , 0xA141U , 0x6300U , 0xA3C1U , 0xA281U , 0x6240U ,
  0x6600U , 0xA6C1U , 0xA781U , 0x6740U , 0xA501U , 0x65C0U , 0x6480U , 0xA441U ,
  0x6C00U , 0xACC1U , 0xAD81U , 0x6D40U , 0xAF01U , 0x6FC0U , 0x6E80U , 0xAE41U ,
  0xAA01U , 0x6AC0U , 0x6B80U , 0xAB41U , 0x6900U , 0xA9C1U , 0xA881U , 0x6840U ,
  0x7800U , 0xB8C1U , 0xB981U , 0x7940U , 0xBB01U , 0x7BC0U , 0x7A80U , 0xBA41U ,
  0xBE01U , 0x7EC0U , 0x7F80U , 0xBF41U , 0x7D00U , 0xBDC1U , 0xBC81U , 0x7C40U ,
  0xB401U , 0x74C0U , 0x7580U , 0xB541U , 0x7700U , 0xB7C1U , 0xB681U , 0x7640U ,
  0x7200U , 0xB2C1U , 0xB381U , 0x7340U , 0xB101U , 0x71C0U , 0x7080U , 0xB041U ,
  0x5000U , 0x90C1U , 0x9181U , 0x5140U , 0x9301U , 0x53C0U , 0x5280U , 0x9241U ,
  0x9601U , 0x56C0U , 0x5780U , 0x9741U , 0x5500U , 0x95C1U , 0x9481U , 0x5440U ,
  0x9C01U , 0x5CC0U , 0x5D80U , 0x9D41U , 0x5F00U , 0x9FC1U , 0x9E81U , 0x5E40U ,
  0x5A00U , 0x9AC1U , 0x9B81U , 0x5B40U , 0x9901U , 0x59C0U , 0x5880U , 0x9841U ,
  0x8801U , 0x48C0U , 0x4980U , 0x8941U , 0x4B00U , 0x8BC1U , 0x8A81U , 0x4A40U ,
  0x4E00U , 0x8EC1U , 0x8F81U , 0x4F40U , 0x8D01U , 0x4DC0U , 0x4C80U , 0x8C41U ,
  0x4400U , 0x84C1U , 0x8581U , 0x4540U , 0x8701U , 0x47C0U , 0x4680U , 0x8641U ,
  0x8201U , 0x42C0U , 0x4380U , 0x8341U , 0x4100U , 0x81C1U , 0x8081U , 0x4040U 
};
/* polyspace-end VARIABLE:ALL [Justified:Low] "This variable is used to calculate CRC value of ROM section" */
#define ROMTST_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* (ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS) || (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS) */

#define ROMTST_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* polyspace-begin VARIABLE:ALL [Justified:Low] "This variable is local status of module" */
static VAR(RomTst_StatusType, ROMTST_VAR_NOINIT) RomTst_Status;
/* polyspace-end VARIABLE:ALL [Justified:Low] "This variable is local status of module" */
/* polyspace-begin VARIABLE:ALL [Justified:Low] "This variable is used to hold the return value of function defined by user" */
#if (ROMTST_OTA_SUPPORT == STD_ON)
static VAR(RomTst_CodeFlashIdType, ROMTST_VAR_NOINIT) RomTst_ActiveCodeFlashId;
#endif
/* polyspace-end VARIABLE:ALL [Justified:Low] "This variable is used to hold the return value of function defined by user" */
#define ROMTST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define ROMTST_START_SEC_MEM_CHK_ID
#include "MemMap.h"

#define ROMTST_STOP_SEC_MEM_CHK_ID
#include "MemMap.h"

/* polyspace-end MISRA-C3:8.9 [Justified:Low] "This variable is Used in different functions according to configuration" */

#define ROMTST_START_SEC_MEM_CHK_CRC
#include "MemMap.h"
/* polyspace-begin VARIABLE:ALL [Justified:Low] "This is written by UTIP Tools. RomTst_MemChkCrcArea MUST be not declared Private variable." */
/* polyspace +10 MISRA-C3:8.4 [Justified:Low] "This variable is used in other module" */
CONST(RomTst_CrcAreaType, ROMTST_VAR_INIT) RomTst_MemChkCrcArea = {
  0xFFFFU,
  0xFFFFU,
  {
    { 0xFFFFFFFFUL , 0xFFFFFFFFUL },
#if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
    { 0xFFFFFFFFUL , 0xFFFFFFFFUL },
#endif
  }
};
/* polyspace-end VARIABLE:ALL [Justified:Low] "This is written by UTIP Tools. RomTst_MemChkCrcArea MUST be not declared Private variable." */
#define ROMTST_STOP_SEC_MEM_CHK_CRC
#include "MemMap.h"

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
#define ROMTST_START_SEC_MEM_CHECK
#include "MemMap.h"
#if ((ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS) || (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS))
static FUNC(RomTst_AddressType, ROMTST_CODE) RomTst_ConvertFlashAddress(uint32 AddToConvert);
static FUNC(Std_ReturnType, ROMTST_CODE) RomTst_CheckCRC( P2CONST(RomTst_TestBlockType, AUTOMATIC, AUTOMATIC) TestBlock );
static FUNC(uint16, ROMTST_CODE) RomTst_CalculateCRC16( uint8 * StartAddr, uint32 Length, uint16 InitValue );
#endif /* (ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS) || (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS) */
/*******************************************************************************
** Function Name        : RomTst_MainFunction                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will be called by Os Task                  **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : RomTst should be initialized.                       **
**                                                                            **
** Remarks              : Global Variable(s)    :  None                       **
**                        Function(s) invoked   :  RomTst_Rtm_Perform         **
*******************************************************************************/
/* polyspace +2 MISRA-C3:8.4 [Justified:Low] "Prototype is declared in RTE" */
FUNC(void, ROMTST_CODE) RomTst_MainFunction(void)
{
  /* Call background test function */
  RomTst_Rtm_Perform();
}

/*******************************************************************************
** Function Name        : RomTst_ConvertFlashAddress                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert general address into linear address         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : AddToConvert - address (24bits) we don't know       **
**                          if it's a paged or a linear address               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : AddToConvert - a linear address                     **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#if ((ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS) || (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS))
static FUNC(RomTst_AddressType, ROMTST_CODE) RomTst_ConvertFlashAddress(uint32 AddToConvert)
{
  return ((RomTst_AddressType)AddToConvert);
}
#endif /* (ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS) || (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS) */
/*******************************************************************************
** Function Name        : RomTst_CalculateCRC16                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Computes the CRC of a given area The initial value  **
**                        of the CRC is given as arg. 3                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : StartAddr - start address to be calculated area     **
**                        Length - length to be calculated area               **
**                        InitValue - initial value of CRC                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : calcCrcVal - Calculated CRC                         **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#if ((ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS) || (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS))
static FUNC(uint16, ROMTST_CODE) RomTst_CalculateCRC16( uint8 * StartAddr, uint32 Length, uint16 InitValue )
{
  uint8 *dataPtr;
  uint16 crcTblIndex;
  uint16 calcCrcVal;
  uint32 index = ROMTST_ZERO;

  /* Point to start address */
  dataPtr     = StartAddr;
  /* Get initial value of CRC */
  calcCrcVal  = InitValue;
  /* Calculate CRC value */
  while (index < Length)
  {
    /* polyspace-begin MISRA-C3:D4.1 RTE:IDP,NIV [Justified:Low] "A copied value of the first argument and length value was validated by caller" */
    crcTblIndex = ( ( calcCrcVal ^ (uint16)*dataPtr ) & ROMTST_MASK_ONE_BYTE );
    /* polyspace-end MISRA-C3:D4.1 RTE:IDP,NIV [Justified:Low] "A copied value of the first argument and length value was validated by caller" */
    /* Get the next byte */
    calcCrcVal = ( ( calcCrcVal >> ROMTST_EIGHT ) ^ RomTst_TabCRCA001_1[crcTblIndex] );
    dataPtr++;
    index++;
  }

  return (calcCrcVal);
}
#endif /* (ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS) || (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS) */
/*******************************************************************************
** Function Name        : RomTst_CheckCRC                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Computes the CRC of the SW Module                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : TestBlock - Address of Block parameter              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : retVal - E_NOT_OK: CRC value does not match         **
**                                        with pre-defined CRC value          **
**                               - E_OK: CRC calculated value match with      **
**                                        pre-defined CRC value               **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : RomTst_ConvertFlashAddress,   **
**                                              RomTst_CalculateCRC16         **
*******************************************************************************/
#if ((ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS) || (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS))
static FUNC(Std_ReturnType, ROMTST_CODE) RomTst_CheckCRC( P2CONST(RomTst_TestBlockType, AUTOMATIC, AUTOMATIC) TestBlock )
{
  uint8  * dataFlsPtr;
  uint16 index;
  uint16 numOfCrcAreas;
  uint16 calcCrcVal;
  uint32 dataLength;
  uint32 startAddr;
  uint32 endAddr;
  Std_ReturnType retVal           = E_NOT_OK;
  RomTst_CrcAreaType * crcAreaPtr = NULL_PTR;
  /* NULL check */
  /* polyspace +2 RTE:UNR [Justified:Low] "This condition to avoid runtime error because input value of TestBlock shall be fill by mCRT and alway different NULL" */
  if (NULL_PTR != TestBlock)
  {
    /* OTA support */
#if (ROMTST_OTA_SUPPORT == STD_ON)
    if ( ROMTST_CODE_FLASH_ID_2 == RomTst_ActiveCodeFlashId )
    {
      if (NULL_PTR != TestBlock->CrcArea2)
      {
        crcAreaPtr = TestBlock->CrcArea2;
      }
      else
      {
        crcAreaPtr = TestBlock->CrcArea1;
      }
    }
    else
#endif
    {
      /* OTA not support */
      crcAreaPtr = TestBlock->CrcArea1;
    }

    /* CRC information shall be NULL checkd */
    /* polyspace +2 RTE:UNR [Justified:Low] "This condition to avoid runtime error because input value of crcAreaPtr shall be fill by mCRT and alway different NULL" */
    if (NULL_PTR != crcAreaPtr)
    {
      /*
       |---------------------------------------------  CRC Information Structure  ----------------------------------------------|
       |                                                                                                                        |
       +--------+---------------+---------------+-------------+---------------+-------------+---- +---------------+-------------+
       | CRCVal | NumOfAreas(N) | 1st StartAddr | 1st EndAddr | 2nd StartAddr | 2nd EndAddr | ... | Nth StartAddr | Nth EndAddr |
       +--------+---------------+---------------+-------------+---------------+-------------+---- +---------------+-------------+
       |   2B   |       2B      |       4B      |      4B     |       4B      |      4B     | ... |       4B      |      4B     |
       |<------------------------------------------------------Length---------------------------------------------------------->|
       --------------------------------------------------------------------------------------------------------------------------
       * Size of CRC Information area(Length): 2(CRCVal) + 2(CRCArea) + [4B(StartAddr) + 4B(EndAddr)] * N
       */

      numOfCrcAreas = crcAreaPtr->NumberOfCrcAreas;
      if((ROMTST_NUM_OF_CRC_AREA_NOT_FILL == numOfCrcAreas) || (ROMTST_ZERO == numOfCrcAreas))
      {
        /* If the number of CRC information is 0xFFFFu --> Need UTIP operation */
        retVal = E_NOT_OK;
      }
      else
      {
        /* Example )
          Set CRC init value
          T_IDENT const cat_ApplId =
          {
            CUSTOMER_ID,
            PRODUCT_ID,
            PRODUCT_VARIANT | SW_TYPE_ID,
            SW_VERSION,
            INTERMEDIATE_SW_VERSION,
            SYNCHRO_BOOT_ASW | SYNCHRO_ASW_CALIB,
            SYNCHRO_ASW1_ASW2,
            RESERVED,
            ASW_BUILD_DAY,
            ASW_BUILD_MONTH,
            ASW_BUILD_YEAR,
            ASW_CRC_VALUE,
            ASW_NUMBER_OF_AREA
          };
          CRC Init Value = INTERMEDIATE_SW_VERSION << 8 | SW_VERSION
          */
#ifdef MEMCHK_CRC16_FIXED_INIT_VALUE
        calcCrcVal = MEMCHK_CRC16_FIXED_INIT_VALUE;
#else
        /* Get CRC initial value */
        /* polyspace-begin MISRA-C3:D4.1 RTE:IDP,NIV [Justified:Low] "CRC initial value used to calculate CRC value of ROM block located before CrcAreaPtr" */
        calcCrcVal = ROMTST_GET_HIGH_BYTE_CRC_INIT_VALUE(crcAreaPtr);
        calcCrcVal = (calcCrcVal << ROMTST_EIGHT) | (ROMTST_GET_LOW_BYTE_CRC_INIT_VALUE(crcAreaPtr));
        /* polyspace-end MISRA-C3:D4.1 RTE:IDP,NIV [Justified:Low] "CRC initial value used to calculate CRC value of ROM block located before CrcAreaPtr" */
#endif
        /* 1. Find CRC Area */
        for(index = ROMTST_ZERO; index < numOfCrcAreas; index++)
        {
          /* Get start address and end address of each ROM area */
          /* polyspace-begin MISRA-C3:D4.1 RTE:OBAI [Justified:Low] "Actual size of this structure defined by linker script and the range of CrcArea limited by NumberOfCrcAreas" */
          startAddr = (RomTst_AddressType) (crcAreaPtr->CrcArea[index].StartAddr);
          endAddr   = (RomTst_AddressType) (crcAreaPtr->CrcArea[index].EndAddr);
          /* polyspace-end MISRA-C3:D4.1 RTE:OBAI [Justified:Low] "Actual size of this structure defined by linker script and the range of CrcArea limited by NumberOfCrcAreas" */

          /* Convert Address to Global Address */
          if((ROMTST_ADDR_INFO_NOT_FILL == startAddr) || (ROMTST_ZERO == startAddr) || (endAddr <= startAddr))
          {
            /* No CRC information --> Need UTIP operation */
            retVal = E_NOT_OK;
            break;
          }
          else
          {
            dataLength = ROMTST_GET_DATA_LENGTH(startAddr, endAddr);
            /* Find start address to calculate CRC */
            /* polyspace-begin ISO-17961:intptrconv MISRA-C3:11.4 [Justified:Low] "Casting a fixed address point to the first address of ROM section" */
            dataFlsPtr = (uint8 *) RomTst_ConvertFlashAddress(startAddr);
            /* polyspace-end ISO-17961:intptrconv MISRA-C3:11.4 [Justified:Low] "Casting a fixed address point to the first address of ROM section" */
            /* Calculate CRC value with initial CRC value */
            calcCrcVal = RomTst_CalculateCRC16(dataFlsPtr, dataLength, calcCrcVal);
          }
        }

        /* CRC value written to ROM is equal to CRC value calculated */
        if(crcAreaPtr->CrcValue == calcCrcVal)
        {
          /* ROM section is valid - set return value to E_OK */
          retVal = E_OK;
        }
      }
    }
  }

  /* No CRC --> OK */
  return (retVal);
}
#endif /* (ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS) || (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS) */
/*******************************************************************************
** Function Name        : RomTst_Init                                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check the MEM CHECK SW module - Foreground check    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : RomTst_Config[],              **
**                          RomTst_Status                                     **
**                        Function(s) invoked : RomTst_CheckCRC(),            **
**                          RomTst_GetActiveCodeFlashId()                     **
*******************************************************************************/
FUNC(void, ROMTST_CODE) RomTst_Init(void)
{
  #if (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS)
  /* Index of block shall be tested - start from 0 */
  uint8 blockIdx;
  /* Assign RomTst configuration pointer */
  P2CONST(RomTst_ConfigType, AUTOMATIC, AUTOMATIC) ConfigPtr = &RomTst_Config[0];
  #else
  /* RomTst initialized - No sections were tested */
  RomTst_Status = E_MEM_CHK_NA;
  #endif /* (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS) */
  #if (ROMTST_OTA_SUPPORT == STD_ON)
  RomTst_ActiveCodeFlashId = RomTst_GetActiveCodeFlashId();
  #endif

  /* Check number of test blocks */
  /* polyspace-begin RTE:UNR [Justified:Low] "This condition to avoid runtime error because input value of NumOfTestBlockFgnd shall be fill by mCRT and alway different zero" */
  #if (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS)
    /* Initial value for test result */
  RomTst_Status = E_MEM_CHK_OK;
  /* Foreground - Perform test all blocks defined in RomTst Configuration pointer */
  for (blockIdx = ROMTST_ZERO; blockIdx < ConfigPtr->NumOfTestBlockFgnd; blockIdx++)
  {
    /* Compare CRC value written to ROM section with CRC value calculated */
    if(E_OK != RomTst_CheckCRC( &ConfigPtr->TestBlockFgnd[blockIdx] ))
    {
      /* If an error occur, test result shall be set to E_MEM_CHK_ERROR */
      RomTst_Status = E_MEM_CHK_ERROR;
    }
  }
  #endif /* (ROMTST_ZERO != ROMTST_NUM_OF_FRG_BLOCKS) */
  /* polyspace-end RTE:UNR [Justified:Low] "This condition to avoid runtime error because input value of NumOfTestBlockFgnd shall be fill by mCRT and alway different zero" */
}

/*******************************************************************************
** Function Name        : RomTst_Start                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Start the Check Task for MEM                        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : actSrvErr:                                          **
**                          - E_MEM_CHK_SRV_OK - Service is Activated         **
**                          - E_MEM_CHK_SRV_BUSY - Service is not Activated   **
**                                                                            **
** Preconditions        : RomTst should be initialized.                       **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                          SchM_ActMainFunction_RomTst_BITP_RomTst()         **
*******************************************************************************/
FUNC(RomTst_StartResultType, ROMTST_CODE) RomTst_Start(void)
{
  Std_ReturnType retVal;
  RomTst_StartResultType actSrvErr;

  /* Allow RomTst to run check in background */
  retVal = SchM_ActMainFunction_RomTst_BITP_RomTst();

  if(SCHM_E_OK == retVal)
  {
    /* Accepted */
    actSrvErr = E_MEM_CHK_SRV_OK;
  }
  else
  {
    /* Rejected */
    actSrvErr = E_MEM_CHK_SRV_BUSY;
  }

  return (actSrvErr);
}

/*******************************************************************************
** Function Name        : RomTst_Rtm_Perform                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check Task for Runtime Check - Background Task for  **
**                        ROM Check                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : RomTst should be initialized.                       **
**                                                                            **
** Remarks              : Global Variable(s)  : RomTst_Config[],              **
**                          RomTst_Status                                     **
**                        Function(s) invoked : BswM_RequestMode(),           **
**                          RomTst_CheckCRC(), RomTst_TestErrorNotification() **
*******************************************************************************/
/* polyspace +3 MISRA-C3:8.7,8.8 [Justified:Low] "This function is invoked by user" */
FUNC(void, ROMTST_CODE) RomTst_Rtm_Perform(void)     /* Background Task for ROM Check */
{
  #if (ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS)
  /* Index of block shall be tested - start from 0 */
  uint8 blockIdx;
  /* Assign RomTst configuration pointer */
  P2CONST(RomTst_ConfigType, AUTOMATIC, AUTOMATIC) ConfigPtr = &RomTst_Config[0];

  BswM_RequestMode((BswM_UserType)ROMTST_MODULE_ID, (BswM_ModeType)ROMTST_LOWPOWER_PREVENT);
  #endif /* (ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS) */

  /* ROM SW Module Check */
  RomTst_Status = E_MEM_CHK_NA;
  #if (ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS)
  for (blockIdx = ROMTST_ZERO; blockIdx < ConfigPtr->NumOfTestBlockBgnd; blockIdx++)
  {
    if( E_OK != RomTst_CheckCRC( &ConfigPtr->TestBlockBgnd[blockIdx] ))
    {
      /* CRC value not match */
      RomTst_Status = E_MEM_CHK_ERROR;
    }
  }

  /* No error occur, value of RomTst status not change */
  if(E_MEM_CHK_NA == RomTst_Status)
  {
    /* Set RomTst status to E_MEM_CHK_OK */
    RomTst_Status = E_MEM_CHK_OK;
  }

  #if (ROMTST_TEST_COMPLETED_NOTIFICATION_SUPPORTED == STD_ON)
    /* If notification is configured, callback notification shall be invoked */
    ROMTST_TEST_COMPLETED_NOTIFICATION();
  #endif /* ROMTST_TEST_COMPLETED_NOTIFICATION_SUPPORTED == STD_ON */

  BswM_RequestMode((BswM_UserType)ROMTST_MODULE_ID, (BswM_ModeType)ROMTST_LOWPOWER_ALLOW);
  #endif /* ROMTST_ZERO != ROMTST_NUM_OF_BGN_BLOCKS */
}
/*******************************************************************************
** Function Name        : RomTst_GetStatus                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the Result for ROM Check                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : currentStatus - Check Result                        **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)  : RomTst_Status                 **
**                        Function(s) invoked : None                          **
*******************************************************************************/
FUNC(RomTst_StatusType, ROMTST_CODE) RomTst_GetStatus(void)
{
  RomTst_StatusType currentStatus;
  /* Current status is OK */
  if(E_MEM_CHK_OK == RomTst_Status)
  {
    currentStatus = E_MEM_CHK_OK;
  }
  else
  {
    if(E_MEM_CHK_NA == RomTst_Status)
    {
      /* Current status is NA - Not yet tested */
      currentStatus = E_MEM_CHK_NA;
    }
    else
    {
      /* Current status is NOT OK */
      currentStatus = E_MEM_CHK_ERROR;
    }
  }

  return (currentStatus);
}
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

#define ROMTST_STOP_SEC_MEM_CHECK
#include "MemMap.h"
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
