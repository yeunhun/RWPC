/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_CRCStatic.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : CRCStatic functions of NVRAM Module                           **
**              NvM_CalculateCRCStaticID                                      **
**              NvM_CompareCRCSID                                             **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date           By          Description                         **
********************************************************************************
** 1.5.1       30-Dec-2020   Yun YJ       Redmine #27374                      **
** 1.3.3       16-Nov-2016   Song CY      Redmine #6680                       **
** 1.3.0       25-Jul-2016   Song CY      Redmine #5383                       **
** 1.2.3       24-Mar-2016   Song CY      Redmine #4276                       **
** 1.1.9       10-Nov-2015   Song CY      Redmine #3371, modify dem report    **
** 1.1.8       02-Oct-2015   Song CY      Correct RunTime Error Violation     **
** 1.1.7       09-Jul-2015   Song CY      Add function for correct MISRA-Rule **
**                                        Violation                           **
**                                        #2265, Modify CRC Logic             **
** 1.1.6       03-Mar-2015   Song CY      As per RedMine 2208, Add states of  **
**                                        ProcessReadblock                    **
**                                        As per RedMine 2216, Remove version **
**                                        Information                         **
** 1.1.4       02-Dec-2014   Song CY      RedMine 1719, Update for PolySpace  **
** 1.1.0       18-Apr-2014   Song CY      RedMine718 Version is updated       **
** 1.0.9       17-Dec-2013   Song CY      Modify Dataset CRC Defect           **
** 1.0.8       30-Sep-2013   Song CY      Update for Library                  **
** 1.0.0       25-Jan-2013   CY Song      Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
polyspace-begin MISRA-C3:1.1:Not a defect:Justify with annotations> Needed for AR/SW version check
polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/
/* polyspace-begin RTE:UNR [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM.h"                      /* NvM header file */
#include "NvM_CRCStatic.h"            /* Internal function header file */
#if(NVM_DEMERROR_REPORT == STD_ON)
#include "NvM_Dem_Cfg.h"              /* Dem header file */
#endif
#include "NvM_Ram.h"                  /* Global variables header file */
#include "NvM_Config.h"
#if(NVM_CRC_SUPPORT == STD_ON)
#include "Crc.h"                      /* Crc header file */
#endif
#if(NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                      /* Det header file */
#endif
/* Internal function header files */
#include "NvM_Process.h"
#include "NvM_Readblock.h"

/*******************************************************************************
**                        Function Definitions                                **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

#if((NVM_CRC16_SUPPORT == STD_ON)||(NVM_STATIC_ID_CHECK == STD_ON))
static FUNC(void, NVM_CODE) NVM_BYTE_ORDER_DISPATCH_16(uint16 NvM_Val16);
#endif
#if(NVM_CRC32_SUPPORT == STD_ON)
static FUNC(void, NVM_CODE) NVM_BYTE_ORDER_DISPATCH_32(uint32 NvM_Val32);
#endif

#if(CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
/*******************************************************************************
** Function Name        : NVM_BYTE_ORDER_DISPATCH_16                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the bytes                     **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : NvM_Msbbyte, NvM_Lsbbyte                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GucMsb, NvM_GucLsb     **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if((NVM_CRC16_SUPPORT == STD_ON)||(NVM_STATIC_ID_CHECK == STD_ON))
static FUNC(void, NVM_CODE) NVM_BYTE_ORDER_DISPATCH_16(uint16 NvM_Val16)
{
  NvM_GucMsb = ((uint8)NvM_Val16 & (uint8)NVM_FF);
  NvM_GucLsb = ((uint8)((uint16)NvM_Val16 >> NVM_EIGHT) & (uint8)NVM_FF);
}
#endif
/*******************************************************************************
** Function Name        : NVM_BYTE_ORDER_DISPATCH_32                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the bytes                     **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : NvM_Val                                             **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GucMsb,                **
**                         NvM_GucMidHi, NvM_GucMidLow, NvM_GucLsb            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(NVM_CRC32_SUPPORT == STD_ON)
static FUNC(void, NVM_CODE) NVM_BYTE_ORDER_DISPATCH_32(uint32 NvM_Val32)
{
  NvM_GucMsb = ((uint8)NvM_Val32 & (uint8)NVM_FF);
  NvM_GucMidHi = ((uint8)((uint32)NvM_Val32 >> NVM_EIGHT)
                               &(uint8)NVM_FF);
  NvM_GucMidLow = ((uint8)((uint32)NvM_Val32 >> NVM_SIXTEEN)
                               &(uint8)NVM_FF);
  NvM_GucLsb = ((uint8)((uint32)NvM_Val32 >> NVM_TWENTYFOUR)
                               &(uint8)NVM_FF);
}
#endif

#else
/*******************************************************************************
** Function Name        : NVM_BYTE_ORDER_DISPATCH_16                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the bytes                     **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : NvM_Msbbyte, NvM_Lsbbyte                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GucMsb, NvM_GucLsb     **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if((NVM_CRC16_SUPPORT == STD_ON)||(NVM_STATIC_ID_CHECK == STD_ON))
static FUNC(void, NVM_CODE) NVM_BYTE_ORDER_DISPATCH_16(uint16 NvM_Val16)
{
  NvM_GucLsb = ((uint8)NvM_Val16 & (uint8)NVM_FF);
  NvM_GucMsb = ((uint8)((uint16)NvM_Val16 >> NVM_EIGHT) & (uint8)NVM_FF);
}
#endif
/*******************************************************************************
** Function Name        : NVM_BYTE_ORDER_DISPATCH_32                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the bytes                     **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : NvM_Val                                             **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_GucMsb,                **
**                         NvM_GucMidHi, NvM_GucMidLow, NvM_GucLsb            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(NVM_CRC32_SUPPORT == STD_ON)
static FUNC(void, NVM_CODE) NVM_BYTE_ORDER_DISPATCH_32(uint32 NvM_Val32)
{
  NvM_GucLsb = ((uint8)NvM_Val32 & (uint8)NVM_FF);
  NvM_GucMidLow = ((uint8)((uint32)NvM_Val32>>NVM_EIGHT)
                                     &(uint8)NVM_FF);
  NvM_GucMidHi = ((uint8)((uint32)NvM_Val32>>NVM_SIXTEEN)
                                     &(uint8)NVM_FF);
  NvM_GucMsb = ((uint8)((uint32)NvM_Val32>>NVM_TWENTYFOUR)
                                     &(uint8)NVM_FF);
}
#endif /* (NVM_CRC32_SUPPORT == STD_ON) */

#endif /* End if(CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */

/*******************************************************************************
** Function Name        : NvM_CalculateCRCStaticID                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to calculate CRC Static ID                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : BlockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : NvM_GpNvmBlkDescTbl,          **
**                        NvM_GpRamAddr, NvM_GaaBlkDescTbl, NvM_GaaReadCRCSID,**
**                        NvM_GucSubState, NvM_GddBlockIdx, NvM_GucState      **
**                                                                            **
**                        Function(s) invoked : Crc_CalculateCRC8(),          **
**                        Crc_CalculateCRC16(), Crc_CalculateCRC32()          **
*******************************************************************************/
#if((NVM_STATIC_ID_CHECK == STD_ON) || (NVM_CRC_SUPPORT == STD_ON))
FUNC(void, NVM_CODE) NvM_CalculateCRCStaticID(NvM_BlockIdType BlockId)
{
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA)LpRamBlkData;
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA)LpCrcCalAddr;
  uint16 LusBlkParams;
  #if((NVM_STATIC_ID_CHECK == STD_ON) || (NVM_CRC16_SUPPORT == STD_ON) \
      || (NVM_CRC32_SUPPORT == STD_ON))
  uint32 LulCount;
  #endif
  
  #if(NVM_STATIC_ID_CHECK == STD_ON)
  NvM_Word16 LddStaticID;
  #endif

  #if((NVM_CRC_SUPPORT == STD_ON))
  #if(NVM_CRC16_SUPPORT == STD_ON)
  NvM_Word16 LddCrc16Value;
  #endif

  #if(NVM_CRC32_SUPPORT == STD_ON)
  NvM_DWord32 LddCrc32Value;
  #endif

  #if(NVM_CRC8_SUPPORT == STD_ON)
  uint8 LucCrc8bit;
  #endif
  #endif

  #if(NVM_CRC_SUPPORT == STD_ON)
  uint8 LucCrcLength;
  #endif

  if (NvM_GpNvmBlkDescTbl != NULL_PTR)
  {
    #if(NVM_CRC_SUPPORT == STD_ON)
    LucCrcLength = NvM_GpNvmBlkDescTbl->ucCrcLength;
    #endif
    LusBlkParams = NvM_GpNvmBlkDescTbl->usBlkParams;
    LpRamBlkData = &NvM_GaaReadCRCSID[NVM_ZERO];
  
    if((NvM_GucState==NVM_WRITEBLOCK_SID)||(NvM_GucState==NVM_WRITEALL_SID)||
       (NvM_GucState == NVM_RESTOREBLOCKDEFAULTS_SID))
    {
      LpCrcCalAddr = NvM_GpRamAddr;
    }
    else
    {
      if((LusBlkParams & NVM_STATIC_BLOCK_ID_CHECK) == NVM_STATIC_BLOCK_ID_CHECK)
      {
        LpCrcCalAddr = &NvM_GaaDataBuffer[NVM_TWO];
      }
      else
      {
        LpCrcCalAddr = &NvM_GaaDataBuffer[NVM_ZERO];
      }
    }
    #if(NVM_STATIC_ID_CHECK == STD_ON)
    if((NvM_GucSubState != NVM_READ_ROM)&&
       (NvM_GucState != NVM_RESTOREBLOCKDEFAULTS_SID))
    {
      LulCount = NVM_ZERO;
      if((LusBlkParams & NVM_STATIC_BLOCK_ID_CHECK) == NVM_STATIC_BLOCK_ID_CHECK)
      {
        LddStaticID.usWordReg16 = NvM_GddBlockIdx;
        NVM_BYTE_ORDER_DISPATCH_16(LddStaticID.usWordReg16);

        LpRamBlkData[LulCount] = NvM_GucMsb;
        LulCount++;
        LpRamBlkData[LulCount] = NvM_GucLsb;
        LulCount++;
      }
      LpRamBlkData=&LpRamBlkData[LulCount];
    }
    #endif
    #if(NVM_CRC_SUPPORT == STD_ON)
    if((LusBlkParams & NVM_CALC_RAM_BLK_CRC) == NVM_CALC_RAM_BLK_CRC)
    {
      #if(NVM_CRC8_SUPPORT == STD_ON)
      if(LucCrcLength == NVM_CRC_1BYTE)
      {
        /* Invoke 8-bit CRC calculation routine */
        LucCrc8bit = Crc_CalculateCRC8(
          (P2CONST(void, AUTOMATIC, NVM_CONST))LpCrcCalAddr,
          (uint32)NvM_GpNvmBlkDescTbl->usNvBlkDataLength, NVM_1BYECRC_STARTVALUE,
          (boolean)NVM_TRUE);
        *LpRamBlkData = LucCrc8bit;
      }
      #endif
      #if(NVM_CRC16_SUPPORT == STD_ON)
      {
        if(LucCrcLength == NVM_CRC_2BYTE)
        {
          LulCount = NVM_ZERO;
          /* Invoke 16-bit CRC calculation routine */
          LddCrc16Value.usWordReg16 = Crc_CalculateCRC16(
            (P2CONST(void, AUTOMATIC, NVM_CONST))LpCrcCalAddr,
            (uint32)NvM_GpNvmBlkDescTbl->usNvBlkDataLength,
              NVM_2BYECRC_STARTVALUE, (boolean)NVM_TRUE);

          NVM_BYTE_ORDER_DISPATCH_16(LddCrc16Value.usWordReg16);
    
          LpRamBlkData[LulCount] = NvM_GucMsb;
          LulCount++;
          LpRamBlkData[LulCount] = NvM_GucLsb;
        }
      }
      #endif
      #if(NVM_CRC32_SUPPORT == STD_ON)
      {
        if(LucCrcLength == NVM_CRC_4BYTE)
        {
          LulCount = NVM_ZERO;
          /* Invoke 32-bit CRC calculation routine */
          LddCrc32Value.ulLongReg32 = Crc_CalculateCRC32(
            (P2CONST(void, AUTOMATIC,NVM_CONST))LpCrcCalAddr,
            (uint32)NvM_GpNvmBlkDescTbl->usNvBlkDataLength,
              NVM_4BYECRC_STARTVALUE, (boolean)NVM_TRUE);

          NVM_BYTE_ORDER_DISPATCH_32(LddCrc32Value.ulLongReg32);

          LpRamBlkData[LulCount] = NvM_GucMsb;
          LulCount++;
          LpRamBlkData[LulCount] = NvM_GucMidHi;
          LulCount++;
          LpRamBlkData[LulCount] = NvM_GucMidLow;
          LulCount++;
          LpRamBlkData[LulCount] = NvM_GucLsb;
        }
      }
      #endif
    }
    #endif
  }
  #if(NVM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_CALCRCSID_SID, NVM_E_PARAM_POINTER);
  }
  #endif

  NVM_UNUSED(BlockId);
}
#endif

/*******************************************************************************
** Function Name        : NvM_CompareCRCSID                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to compare CRC static ID                   **
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
** Remarks              : Global Variable(s)  :                               **
**                        NvM_GpNvmBlkDescTbl, NvM_GddJobResultLowLevel,      **
**                        NvM_GaaReadCRCSID, NvM_GaaBlkDescTbl, NvM_GucState, **
**                        NvM_GucSubState,                                    **
**                        NvM_GpRomBlkDataAddrs, NvM_GaaCrcSID                **
**                        NvM_GusWrongBlockId                                 **
**                        Function(s) invoked :                               **
**                        NvM_UpdateRamStateStatus(), NvM_EndProcessBlock(),  **
**                        Dem_ReportErrorStatus()                             **
*******************************************************************************/
#if((NVM_STATIC_ID_CHECK == STD_ON) || (NVM_CRC_SUPPORT == STD_ON))

FUNC(Std_ReturnType, NVM_CODE) NvM_CompareCRCSID(void)
{
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA)LpCRCSIDMainBlock = &NvM_GaaReadCRCSID[0];
  P2CONST(uint8, NVM_CONST, NVM_CONST) LpCRCSIDData = NULL_PTR;
  uint16 LusBlkParams = 0U;
  uint8 LucIndex = 0U;
  uint32 LulCount = 0U;
  Std_ReturnType LddReturnValue = E_OK; 
  #if(NVM_CRC_SUPPORT == STD_ON)
  uint8 LucCrcLength = 0;
  boolean LblCrcMatch = (boolean)NVM_FALSE;
  #endif
  #if(NVM_STATIC_ID_CHECK == STD_ON)
  boolean LblStaticMatch = (boolean)NVM_FALSE;
  #endif

  if((NvM_GucSubState == NVM_READ_ROM) ||
    (NvM_GucState == NVM_RESTOREBLOCKDEFAULTS_SID))
  {
    LpCRCSIDData = NvM_GpRomBlkDataAddrs;
  }
  else
  {
    LpCRCSIDData = &NvM_GaaDataBuffer[NVM_ZERO];
  }

  if (NvM_GddBlockIdx < NvM_GusTotalNumOfBlock)
  {
    LusBlkParams = NvM_GaaBlkDescTbl[NvM_GddBlockIdx].usBlkParams;
    #if(NVM_CRC_SUPPORT == STD_ON)
    LucCrcLength = NvM_GaaBlkDescTbl[NvM_GddBlockIdx].ucCrcLength;
    LblCrcMatch = (boolean)NVM_TRUE;
    #endif

    LulCount = NVM_ZERO;
  
    #if(NVM_STATIC_ID_CHECK == STD_ON)
    LblStaticMatch = (boolean)NVM_TRUE;

    if((NvM_GucSubState != NVM_READ_ROM) &&
       (NvM_GucState != NVM_RESTOREBLOCKDEFAULTS_SID) &&
       ((LusBlkParams & NVM_STATIC_BLOCK_ID_CHECK) == NVM_STATIC_BLOCK_ID_CHECK))
    {
      LucIndex = NVM_ZERO;
      while(LucIndex < NVM_TWO)
      {
        if(LpCRCSIDMainBlock[LulCount] != LpCRCSIDData[LulCount])
        {
          LblStaticMatch = (boolean)NVM_FALSE;
          LucIndex = NVM_TWO;
        }
        LulCount++;
        LucIndex++;
      }

      LpCRCSIDMainBlock = &LpCRCSIDMainBlock[LulCount];

      if(LblStaticMatch != NVM_TRUE)
      {
          #if(NVM_DEMERROR_REPORT == STD_ON)
          if(((NvM_GaaBlkDescTbl[NvM_GddBlockIdx].enBlkMngmntType
              == NVM_BLOCK_REDUNDANT) &&
             (NvM_GddReStatus != NVM_RE_CHK_NONE)) ||
             (NvM_GaaBlkDescTbl[NvM_GddBlockIdx].enBlkMngmntType
              != NVM_BLOCK_REDUNDANT))
          {
            Dem_ReportErrorStatus(NvM_GusWrongBlockId, DEM_EVENT_STATUS_FAILED);
          }
          #endif
          NvM_GucSubState = NVM_READ_ROM;
          LddReturnValue = E_NOT_OK;
      }
    }
    if(LblStaticMatch == NVM_TRUE)
    #endif
    {
      #if(NVM_CRC_SUPPORT == STD_ON)
      if(((NvM_GucSubState == NVM_READ_ROM) ||
        (NvM_GucState == NVM_RESTOREBLOCKDEFAULTS_SID)) &&
        ((LusBlkParams & NVM_DEFAULT_ROM_CRC_ENABLED)
             == NVM_DEFAULT_ROM_CRC_ENABLED))
      {
        LpCRCSIDData = &LpCRCSIDData[(LulCount+NvM_GusBlockLength)-NVM_ONE];
      }
      else
      #endif
      {
        LpCRCSIDData = &LpCRCSIDData[LulCount+NvM_GusBlockLength];
      }

      #if(NVM_CRC_SUPPORT == STD_ON)
      if((LusBlkParams & NVM_CALC_RAM_BLK_CRC) == NVM_CALC_RAM_BLK_CRC)
      {
        LulCount = NVM_ZERO;
        #if(NVM_CRC8_SUPPORT == STD_ON)
        if(LucCrcLength == NVM_CRC_1BYTE)
        {
          if(LpCRCSIDMainBlock[LulCount] != LpCRCSIDData[LulCount])
          {
            LblCrcMatch = (boolean)NVM_FALSE;
          }
        }
        #endif
        #if(NVM_CRC16_SUPPORT == STD_ON)
        if(LucCrcLength == NVM_CRC_2BYTE)
        {
          LucIndex = NVM_ZERO;
          while(LucIndex < NVM_TWO)
          {
            if(LpCRCSIDMainBlock[LulCount] != LpCRCSIDData[LulCount])
            {
              LblCrcMatch = (boolean)NVM_FALSE;
              LucIndex = NVM_TWO;
            }
            LulCount++;
            LucIndex++;
          }
        }
        #endif
        #if(NVM_CRC32_SUPPORT == STD_ON)
        if(LucCrcLength == NVM_CRC_4BYTE)
        {
          LucIndex = NVM_ZERO;
          while(LucIndex < NVM_FOUR)
          {
            if(LpCRCSIDMainBlock[LulCount] != LpCRCSIDData[LulCount])
            {
              LblCrcMatch = (boolean)NVM_FALSE;
              LucIndex = NVM_FOUR;
            }

            LulCount++;
            LucIndex++;
          }
        }
        #endif
      }
      if(LblCrcMatch != (boolean)NVM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
        NvM_GddJobResultLowLevel = NVM_REQ_INTEGRITY_FAILED;
        if(NvM_GucSubState != NVM_READ_ROM)
        {
          NvM_GucSubState = NVM_READ_ROM;
        }

        #if(NVM_DEMERROR_REPORT == STD_ON)
        if((NvM_GaaBlkDescTbl[NvM_GddBlockIdx].enBlkMngmntType
            == NVM_BLOCK_REDUNDANT) &&
           (NvM_GddReStatus == NVM_RE_CHK_NONE))
        {
          /* Do nothing */
        }
        else
        {
          Dem_ReportErrorStatus
            (NvM_GusIntegrityFailed, DEM_EVENT_STATUS_FAILED);
        }
        #endif
      }
      #endif
    }
  }
  else
  {
    LddReturnValue = E_NOT_OK;
    #if(NVM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID,
      NVM_CALCRCSID_SID, NVM_E_PARAM_DATA);
    #endif
  }
  return LddReturnValue;
}

#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end RTE:UNR [Justified:Low] "Not a defect" */
/*
  polyspace-end MISRA-C3:1.1:Not a defect:Justify with annotations> Needed for AR/SW version check
  polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
