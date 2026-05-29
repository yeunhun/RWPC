/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_DigOutL99MC6.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb L99MC6 module                  **
**              IoHwAb_DigOutL99MC6SwitchOn                                   **
**              IoHwAb_DigOutL99MC6SwitchOff                                  **
**              IoHwAb_DigOutL99MC6                                           **
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
** 1.15.0.2  09-Sep-2021   Yangjin    #31974                                  **
** 1.10.1    04-Aug-2020   Yangjin    #24902                                  **
** 1.0.5     06-Dec-2016   Jongyoung  #6880                                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"
#include "IoHwAb_DigOutL99MC6.h"
#include "IoHwAb_Config.h"
#if (IOHWAB_USE_L99MC6 == STD_ON)
#include "Spi.h"
#endif /* (IOHWAB_USE_L99MC6 == STD_ON) */
#include "SchM_IoHwAb.h"

/* polyspace-begin RTE:UNR [Justified:Low] "It depends on the configuration." */
/* polyspace-begin DEFECT:USELESS_IF MISRA-C3:14.3 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_L99MC6 == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigOutL99MC6SwitchOn                          **
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
**                          IoHwAb_GucNumDigOutL99MC6,                        **
**                          IoHwAb_GaaDigOutL99MC6Infos                       **
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
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutL99MC6SwitchOn(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  Spi_DataType LaaTxL99MC6[2];

  /* command : write operation / address 0x00h */
  LaaTxL99MC6[0] = 0x00U;
  /* data : EN -> 1 (go to Normal mode) */
  LaaTxL99MC6[1] = 0x80U;

  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigOutL99MC6; LucIdx++)
  {
    LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiChType,
      (Spi_DataType*)(LaaTxL99MC6), IOHWAB_NULL_PTR, 2);
    if (LddReturnvalue != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      SchM_Enter_IoHwAb_IoHwAbProtection();
      if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_LOW);
      }

      LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiSeqType);

      if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_HIGH);
      }
      SchM_Exit_IoHwAb_IoHwAbProtection();

      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
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
** Function Name        : IoHwAb_DigOutL99MC6SwitchOff                         **
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
**                          IoHwAb_GucNumDigOutL99MC6,                        **
**                          IoHwAb_GaaDigOutL99MC6Infos                       **
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
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutL99MC6SwitchOff(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  Spi_DataType LaaTxL99MC6[2];

  /* command : write operation / address 0x00h */
  LaaTxL99MC6[0] = 0x00U;
  /* data : EN -> 0 (go to standby mode) */
  LaaTxL99MC6[1] = 0x00U;

  for (LucIdx = 0; LucIdx < IoHwAb_GucNumDigOutL99MC6; LucIdx++)
  {
    LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiChType,
      (Spi_DataType*)(LaaTxL99MC6), IOHWAB_NULL_PTR, 2);
    if (LddReturnvalue != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      SchM_Enter_IoHwAb_IoHwAbProtection();
      if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_LOW);
      }
      LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiSeqType);
      if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_HIGH);
      }
      SchM_Exit_IoHwAb_IoHwAbProtection();
      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
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
** Function Name        : IoHwAb_DigOutL99MC6                                  **
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
**                          IoHwAb_GucNumDigOutL99MC6,                        **
**                          IoHwAb_GucNumDigOutL99MC6StartIdx,                **
**                          IoHwAb_GaaDigOutL99MC6Infos,                      **
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
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutL99MC6(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  uint8 LucSubIdx;
  uint8 LucResBufIdx;
  uint8 LucResBufResult;
  Spi_DataType LaaTxL99MC6[2];
  uint8 LucOvCurRecvBuf;

  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigOutL99MC6; LucIdx++)
  {

    LucResBufIdx = LucIdx + IoHwAb_GucNumDigOutL99MC6StartIdx;

    SchM_Enter_IoHwAb_IoHwAbProtection();
    LucResBufResult= IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult;
    SchM_Exit_IoHwAb_IoHwAbProtection();

    for (LucSubIdx = 0U; LucSubIdx < 3U; LucSubIdx++)
    {
      /* set into the command byte with address and operation mode as Write Mode*/
      LaaTxL99MC6[0] = 0x00 + (2 - LucSubIdx);

      /* arrange the L99MC6 Output into local buffer (from rauw_DigOutBuffer[]) */
      LaaTxL99MC6[1] = (Spi_DataType)(
        ((uint32)0xFF & ( (uint32)IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ulChargePumpControl >> ((uint32)8 * (uint32)LucSubIdx)))
        |  (((uint32)(LucResBufResult) & ((uint32)1 << (uint32)LucSubIdx)) >> (uint32)LucSubIdx)
        | ((((uint32)(LucResBufResult) & ((uint32)8 << (uint32)LucSubIdx)) >> (uint32)LucSubIdx) << (uint32)1)
        );

      /* arrange the L99MC6 OverCurrentRecovery enable information */
      LucOvCurRecvBuf = ((IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ucOverCurrentRecovery & (uint8)((uint8)1 << (uint8)LucSubIdx)) >> (uint8)LucSubIdx)
        | (uint8)(((IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ucOverCurrentRecovery & (uint8)((uint8)8 << (uint8)LucSubIdx)) >> (uint8)LucSubIdx) << (uint8)1);

      /* apply the OverCurrentRecovery to output data */
      LaaTxL99MC6[1] = LaaTxL99MC6[1]
        | ((Spi_DataType)((LaaTxL99MC6[1] & LucOvCurRecvBuf) << 1));

      LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiChType,
        (Spi_DataType*)LaaTxL99MC6, IOHWAB_NULL_PTR, 2);
      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
      else
      {
        SchM_Enter_IoHwAb_IoHwAbProtection();        
        if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
        {
          Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_LOW);
        }
        LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiSeqType);
        if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
        {
          Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_HIGH);
        } 
        SchM_Exit_IoHwAb_IoHwAbProtection();  

        if (LddReturnvalue != E_OK)
        {
          #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
            (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
          #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
          #if (IOHWAB_USE_DEM_EVENT == STD_ON)
          Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
          #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
        }
      }
    }
  }

  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_L99MC6 == STD_ON) */
/* polyspace-end RTE:UNR [Justified:Low] "It depends on the configuration." */
/* polyspace-end DEFECT:USELESS_IF MISRA-C3:14.3 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

