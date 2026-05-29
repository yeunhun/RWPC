/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_DigOutTLE7240SL.c                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb TLE7240SL module               **
**              IoHwAb_DigOutTLE7240SLSwitchOn                                **
**              IoHwAb_DigOutTLE7240SLSwitchOff                               **
**              IoHwAb_DigOutTLE7240SL                                        **
**                                                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.15.0.2  09-Sep-2021   Yangjin        #31974                              **
** 1.0.0     20-Apr-2015   Jongyoung      1.Initial version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"
#include "IoHwAb_DigOutTLE7240SL.h"
#include "IoHwAb_Config.h"
#if (IOHWAB_USE_TLE7240SL == STD_ON)
#include "Spi.h"
#endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
#include "SchM_IoHwAb.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (IOHWAB_USE_TLE7240SL == STD_ON)
#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* variable to check the first Diagnosis trial for TLE7240SL */
VAR(uint8, IOHWAB_VAR) IoHwAb_GucTLE7240SLDiagStatus;
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_TLE7240SL == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigOutTLE7240SLSwitchOn                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucNumDigOutTLE7240SL,                     **
**                          IoHwAb_GaaDigOutTLE7240SLInfos                    **
**                        Function(s) invoked    :                            **
**                          Spi_SetupEB                                       **
**                          Spi_SyncTransmit                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutTLE7240SLSwitchOn(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  Spi_DataType LaaTxTLE7240SL[2];
  Spi_DataType LaaRxTLE7240SL[2];

  /* Initialize IN1~IN4 */
  LaaTxTLE7240SL[0] = 0x00U;
  /* Initialize IN5~IN8 */
  LaaTxTLE7240SL[1] = 0x00U;

  /* Initialize DiagStatus */
  IoHwAb_GucTLE7240SLDiagStatus = 0U ; 
  
  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigOutTLE7240SL; LucIdx++)
  {
    /* Disable all int */
    SchM_Enter_IoHwAb_IoHwAbProtection();
    /* Set RTS to turn on the IC */
    Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddResetDioChType, STD_HIGH);

    /* SetupExternal buffer */
    LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiChType,
      (Spi_DataType*)(LaaTxTLE7240SL), (Spi_DataType*)(LaaRxTLE7240SL), 2);
    if (LddReturnvalue != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_LOW);
      }

      LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiSeqType);

      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_HIGH);
      }

      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
    }

    /* Enable all int */
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }

  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutTLE7240SLSwitchOff                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucNumDigOutTLE7240SL,                     **
**                          IoHwAb_GaaDigOutTLE7240SLInfos                    **
**                        Function(s) invoked    :                            **
**                          Spi_SetupEB                                       **
**                          Spi_SyncTransmit                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutTLE7240SLSwitchOff(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  Spi_DataType LaaTxTLE7240SL[2];
  Spi_DataType LaaRxTLE7240SL[2];

  /* Initialize IN1~IN4 */
  LaaTxTLE7240SL[0] = 0x00U;
  /* Initialize IN5~IN8 */
  LaaTxTLE7240SL[1] = 0x00U;

  for (LucIdx = 0; LucIdx < IoHwAb_GucNumDigOutTLE7240SL; LucIdx++)
  {
    /* Disable all int */
    SchM_Enter_IoHwAb_IoHwAbProtection();

    LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiChType,
      (Spi_DataType*)(LaaTxTLE7240SL), IOHWAB_NULL_PTR, 2);
    if (LddReturnvalue != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_LOW);
      }

      LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiSeqType);

      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_HIGH);
      }

      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
    }

    /* Enable all int */
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }

  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutTLE7240SL                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnvalue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucNumDigOutTLE7240SL,                     **
**                          IoHwAb_GucNumDigOutTLE7240SLStartIdx,             **
**                          IoHwAb_GaaDigOutTLE7240SLInfos,                   **
**                          IoHwAb_GaaDigOutResultBuffer                      **
**                        Function(s) invoked    :                            **
**                          Spi_SetupEB                                       **
**                          Spi_SyncTransmit                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutTLE7240SL(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  uint8 LucResBufIdx;
  Spi_DataType LaaTxTLE7240SL[2] = {0U,0U};
  Spi_DataType LaaRxTLE7240SL[2] = {0U,0U};
  uint8 LucDigOutBuf;
  uint8 LucInputMode;
  uint8 LucRevInputMode;

  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigOutTLE7240SL; LucIdx++)
  {
    LucResBufIdx = LucIdx + IoHwAb_GucNumDigOutTLE7240SLStartIdx;
    LucDigOutBuf = (uint8)IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult;    
    LucInputMode = (uint8)IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ucInputMode;
    LucRevInputMode = 0xFFU - LucInputMode;
    
    /* fill-up the Tx buffer */
    if (((IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ucDiagnosis) != 0U) &&
         (IoHwAb_GucTLE7240SLDiagStatus == 0U) )
    {
       LaaTxTLE7240SL[0] = 0x00U;
       LaaTxTLE7240SL[1] = 0x00U;
    }
    else
    {
       /* IN5 ~ IN8 */
       LaaTxTLE7240SL[0] =
       (uint8)(0xFFU - (((LucInputMode & 0x10U) >> 3) | (((LucDigOutBuf & LucRevInputMode)& 0x10U) >> 4)
       |((LucInputMode & 0x20U) >> 2) | (((LucDigOutBuf & LucRevInputMode)& 0x20U) >> 3)
       |((LucInputMode & 0x40U) >> 1) | (((LucDigOutBuf & LucRevInputMode)& 0x40U) >> 2)
       |((LucInputMode & 0x80U)     ) | (((LucDigOutBuf & LucRevInputMode)& 0x80U) >> 1)));
       /* IN1 ~ IN4 */
       LaaTxTLE7240SL[1] =
       (uint8)(0xFFU - (((LucInputMode & 0x1U) << 1) | (((LucDigOutBuf & LucRevInputMode)& 0x1)) 
       |((LucInputMode & 0x2U) << 2) | (((LucDigOutBuf & LucRevInputMode)& 0x2U) << 1)
       |((LucInputMode & 0x4U) << 3) | (((LucDigOutBuf & LucRevInputMode)& 0x4U) << 2)
       |((LucInputMode & 0x8U) << 4) | (((LucDigOutBuf & LucRevInputMode)& 0x8U) << 3)));
    }
    LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiChType,
      (Spi_DataType*)LaaTxTLE7240SL, (Spi_DataType*)LaaRxTLE7240SL, 2);

    if (LddReturnvalue != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      /* Disable all int */
      SchM_Enter_IoHwAb_IoHwAbProtection();
      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_LOW);
      }
      /* SPI Sync Transmit */
      LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiSeqType);

      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_HIGH);
      }
      /* Enable all int */
      SchM_Exit_IoHwAb_IoHwAbProtection();

      if (((IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ucDiagnosis) != 0U) &&
           (IoHwAb_GucTLE7240SLDiagStatus == 0U) )
      {
		    /* Diagnosis data */
        IoHwAb_GaaDigOutTLE7240SLDiagBuffer[LucIdx] = 0U;
        IoHwAb_GucTLE7240SLDiagStatus++;
			}
      else
      {
        IoHwAb_GaaDigOutTLE7240SLDiagBuffer[LucIdx] =
        (( 0x0000 | LaaRxTLE7240SL[0])<<8 | LaaRxTLE7240SL[1]);
      }

      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
         (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
    }
  }
  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutTLE7240SLGetOpenLoad                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnvalue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutTLE7240SLDiagBuffer               **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutTLE7240SLGetOpenLoad(IoHwAb_IndexType ChIdx, 
P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  uint16 LucHWIdx = 0;
  uint16 LucShiftBit = ((ChIdx % 8) * 2) + 1U;

  if((ChIdx / 8) >= IoHwAb_GucNumDigOutTLE7240SLStartIdx)
  {
    LucHWIdx = (ChIdx / 8) - IoHwAb_GucNumDigOutTLE7240SLStartIdx;
  }
  else
  {
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
    (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
    #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
  }

  if ( Level != NULL_PTR ) 
  {
    SchM_Enter_IoHwAb_IoHwAbProtection();
    *Level = ( IoHwAb_GaaDigOutTLE7240SLDiagBuffer[LucHWIdx] & 
             ((uint16)(0x1U) << LucShiftBit) ) >> LucShiftBit;
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_DigOutTLE7240SLGetOverCurrent                **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnvalue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutTLE7240SLDiagBuffer               **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutTLE7240SLGetOverCurrent(IoHwAb_IndexType ChIdx, 
P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  uint16 LucHWIdx = 0;
  uint16 LucShiftBit = (ChIdx % 8) * 2;

  if((ChIdx / 8) >= IoHwAb_GucNumDigOutTLE7240SLStartIdx)
  {
    LucHWIdx = (ChIdx / 8) - IoHwAb_GucNumDigOutTLE7240SLStartIdx;
  }
  else
  {
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
    (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
    #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
  }

  if ( Level != NULL_PTR ) 
  {
    SchM_Enter_IoHwAb_IoHwAbProtection();
    *Level = (IoHwAb_GaaDigOutTLE7240SLDiagBuffer[LucHWIdx] & 
             ((uint16)(0x1U) << LucShiftBit) ) >> LucShiftBit;
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

