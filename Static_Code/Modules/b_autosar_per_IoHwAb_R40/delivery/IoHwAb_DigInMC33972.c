/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_DigInMC33972.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb MC33972 module                 **
**              IoHwAb_DigInMC33972Init                                       **
**              IoHwAb_DigInMC33972Acq                                        **
**              IoHwAb_DigInMC33972L2H                                        **
**              IoHwAb_DigInMC33972H2L                                        **
**              IoHwAb_DigInMC33972IntermediateWakeUp                         **
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
** 1.8.1     08-May-2020   Yangjin    #23096                                  **
** 1.0.9     26-Jul-2016   Jongyoung  #5219                                   **
** 1.0.8     19-Apr-2016   Jongyoung  #4514                                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"
#include "IoHwAb_DigInMC33972.h"
#include "IoHwAb_Config.h"
#if (IOHWAB_USE_MC33972 == STD_ON)
#include "Spi.h"
#endif /* (IOHWAB_USE_MC33972 == STD_ON) */
#include "SchM_IoHwAb.h"
#if (IOHWAB_USE_LP_FLAG == STD_ON)
#include "BswM.h"
#endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "whether this macro is used depends on the configurations." */
/* Macro for the MC33972 mode status betwenn power modes */
#define MC33972_IN_SLEEP_MODE               IOHWAB_ZERO
#define MC33972_IN_NORMAL_MODE              IOHWAB_ONE

/* Macro to check whether the transition process is done normally or not */
#define DEVICE_IN_SLEEP                     IOHWAB_ZERO
#define DEVICE_IN_NORMAL                    IOHWAB_ONE

#define MC33972_SPISIZE                     IOHWAB_THREE
#define SPISIZE_INIT                        (MC33972_SPISIZE * 10U)
#define SPISIZE_ACQ                         (MC33972_SPISIZE)
#define SPISIZE_L2H                         (MC33972_SPISIZE * 2U)
#define SPISIZE_H2L                         (MC33972_SPISIZE * 3U)
/* polyspace-end MISRA-C3:2.5 [Justified:Low] "whether this macro is used depends on the configurations." */
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (IOHWAB_USE_DIG_IN == STD_ON)
#if (IOHWAB_USE_MC33972 == STD_ON)
#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* variable to check the transition function for MC33972 is called or not */
VAR(uint8, IOHWAB_VAR) IoHwAb_GucTransitionStatus;
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
VAR(uint8, IOHWAB_VAR) IoHwAb_GucDeviceStatus;
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (IOHWAB_USE_MC33972 == STD_ON) */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:begin<MISRA-C:17.4:Not a defect:Justify with annotations> No Impact of this rule violation*/
#if (IOHWAB_USE_MC33972 == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigInMC33972Init                             **
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
**                          IoHwAb_GaaDigInMC33972Infos,                      **
**                          IoHwAb_GucTransitionStatus,                       **
**                          IoHwAb_GucDeviceStatus                            **
**                        Function(s) invoked    :                            **
**                          Spi_SetupEB,                                      **
**                          Spi_SyncTransmit,                                 **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigInMC33972Init(void)
{
  /* local index to update the raw buffer */
  uint8 LucIdx;
  uint8 LucSubIdx;

  /* set the Tx buffer to get the input status from Multiplexer */
  Spi_DataType LaaTxDataByte[SPISIZE_INIT];

  Std_ReturnType LddReturnvalue = (Std_ReturnType)E_OK;

  /* To send the command (MCU -> MC33972), one command cycle should be done in
  one CS cycle. If many of commands are transmitted simultaneously in one CS
  cycle, these commands are not accepted by MC33972. */
  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigInMC33972; LucIdx++)
  {
    /* Reset MC33972 in initialization process */
    LucSubIdx = 0U;
    LaaTxDataByte[LucSubIdx] = RESET_CMD;
    LaaTxDataByte[LucSubIdx + 1U] = ALL_BIT_CLEAR;
    LaaTxDataByte[LucSubIdx + 2U] = ALL_BIT_CLEAR;

    /* Programmable SW Register setting for SP pins */
    LucSubIdx += (uint8)MC33972_SPISIZE;
    LaaTxDataByte[LucSubIdx] = SETTINGS_CMD;
    LaaTxDataByte[LucSubIdx + 1U] = ALL_BIT_CLEAR;
    LaaTxDataByte[LucSubIdx + 2U] = IoHwAb_GaaDigInMC33972Infos[LucIdx].ucSettings;

    /* Interrupt and Wake-Up disable for SP pins */
    LucSubIdx += (uint8)MC33972_SPISIZE;
    LaaTxDataByte[LucSubIdx] = WAKEUP_BIT_SP;
    LaaTxDataByte[LucSubIdx + 1U] = ALL_BIT_CLEAR;
    LaaTxDataByte[LucSubIdx + 2U] = ALL_BIT_CLEAR;

    /* Interrupt and Wake-Up disable for SG pins */
    LucSubIdx += (uint8)MC33972_SPISIZE;
    LaaTxDataByte[LucSubIdx] = WAKEUP_BIT_SG;
    LaaTxDataByte[LucSubIdx + 1U] = ALL_BIT_CLEAR;
    LaaTxDataByte[LucSubIdx + 2U] = ALL_BIT_CLEAR;

    /* Wetting Current setting for SP pins */
    LucSubIdx += (uint8)MC33972_SPISIZE;
    LaaTxDataByte[LucSubIdx] = METALLIC_CMD_SP;
    LaaTxDataByte[LucSubIdx + 1U] = ALL_BIT_CLEAR;
    LaaTxDataByte[LucSubIdx + 2U] = IoHwAb_GaaDigInMC33972Infos[LucIdx].ucMetallicSP;

    /* Wetting Current setting for SG pins */
    LucSubIdx += (uint8)MC33972_SPISIZE;
    LaaTxDataByte[LucSubIdx] = METALLIC_CMD_SG;
    LaaTxDataByte[LucSubIdx + 1U]
      = IoHwAb_GaaDigInMC33972Infos[LucIdx].usMetallicSG >> 8;
    LaaTxDataByte[LucSubIdx + 2U]
      = IoHwAb_GaaDigInMC33972Infos[LucIdx].usMetallicSG & 0xFFU;

    /* Wetting Current Timer setting for SP pins */
    LucSubIdx += (uint8)MC33972_SPISIZE;
    LaaTxDataByte[LucSubIdx] = WETTING_CURRENT_TIMER_CMD_SP;
    LaaTxDataByte[LucSubIdx + 1U] = ALL_BIT_CLEAR;
    LaaTxDataByte[LucSubIdx + 2U]
      = IoHwAb_GaaDigInMC33972Infos[LucIdx].ucWettingCurTimerSP;

    /* Wetting Current Timer setting for SG pins */
    LucSubIdx += (uint8)MC33972_SPISIZE;
    LaaTxDataByte[LucSubIdx] = WETTING_CURRENT_TIMER_CMD_SG;
    LaaTxDataByte[LucSubIdx + 1U]
      = IoHwAb_GaaDigInMC33972Infos[LucIdx].usWettingCurTimerSG >> 8;
    LaaTxDataByte[LucSubIdx + 2U]
      = IoHwAb_GaaDigInMC33972Infos[LucIdx].usWettingCurTimerSG & 0xFFU;

    /* Tri-State Register setting for SP pins */
    LucSubIdx += (uint8)MC33972_SPISIZE;
    LaaTxDataByte[LucSubIdx] = TRI_STATE_CMD_SP;
    LaaTxDataByte[LucSubIdx + 1U] = ALL_BIT_CLEAR;
    LaaTxDataByte[LucSubIdx + 2U] = IoHwAb_GaaDigInMC33972Infos[LucIdx].ucTriStateSP;

    /* Tri-State Register setting for SG pins */
    LucSubIdx += (uint8)MC33972_SPISIZE;
    LaaTxDataByte[LucSubIdx] = TRI_STATE_CMD_SG;
    LaaTxDataByte[LucSubIdx + 1U]
      = IoHwAb_GaaDigInMC33972Infos[LucIdx].usTriStateSG >> 8;
    LaaTxDataByte[LucSubIdx + 2U]
      = IoHwAb_GaaDigInMC33972Infos[LucIdx].usTriStateSG & 0xFFU;

    /* Communication between MCU and MC33972 */
    for (LucSubIdx = 0U; LucSubIdx < (SPISIZE_INIT / MC33972_SPISIZE);
      LucSubIdx++)
    {
      LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddSpiChType,
        (Spi_DataType*)(&(LaaTxDataByte[((Spi_DataType)LucSubIdx * (Spi_DataType)MC33972_SPISIZE)])),
        IOHWAB_NULL_PTR, MC33972_SPISIZE);
      if (LddReturnvalue != (Std_ReturnType)E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGIN_MC33972_INIT_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
      else
      {
        if (IoHwAb_GaaDigInMC33972Infos[LucIdx].blManualCS != 0U)
        {
          Dio_WriteChannel(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddCSDioChType,(Dio_LevelType)STD_LOW);
        }

        LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddSpiSeqType);

        if (IoHwAb_GaaDigInMC33972Infos[LucIdx].blManualCS != 0U)
        {
          Dio_WriteChannel(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddCSDioChType,(Dio_LevelType)STD_HIGH);
        }

        if (LddReturnvalue != (Std_ReturnType)E_OK)
        {
          #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
            (uint8)IOHWAB_DIGIN_MC33972_INIT_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
          #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
          #if (IOHWAB_USE_DEM_EVENT == STD_ON)
          Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
          #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
        }
      }
    }
  }

  if (LddReturnvalue == (Std_ReturnType)E_OK)
  {
    /* MC33972's mode is in NORMAL MODE */
    IoHwAb_GucTransitionStatus = MC33972_IN_NORMAL_MODE;

    /* update the Device status */
    IoHwAb_GucDeviceStatus = DEVICE_IN_NORMAL;
  } 
  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_USE_MC33972 == STD_ON) */

#if (IOHWAB_USE_MC33972 == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigInMC33972Acq                              **
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
**                          IoHwAb_GucTransitionStatus,                       **
**                          IoHwAb_GucDeviceStatus,                           **
**                          IoHwAb_GaaDigInMC33972Infos,                      **
**                          IoHwAb_GaaDigInInfos,                             **
**                          IoHwAb_GaaDigInRawBuffer                          **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigInMC33972L2H,                           **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus,                            **
**                          Spi_SetupEB,                                      **
**                          Spi_SyncTransmit,                                 **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigInMC33972Acq(void)
{
  /* local index to update the raw buffer */
  uint8 LucIdx;
  uint8 LucSubIdx;
  uint8 LucRawBufIdx;
  IoHwAb_IndexType LddBufIdx;
  uint8 LucShiftBit;
  uint8 LucMC33972ShiftBit;
  uint8 LucValue;
  uint8 LucNumLgc;

  /* set the Tx buffer to get the input status from Multiplexer */
  Spi_DataType LaaTxDataByte[SPISIZE_ACQ]
    = {SWITCH_STATUS_CMD, ALL_BIT_CLEAR, ALL_BIT_CLEAR};
  Spi_DataType LaaRxDataByte[SPISIZE_ACQ] = {0U,};
  uint16 LusTempRxDataSG;
  uint16 LusTempRxDataSG_Temp;
  uint8 LucTempRxDataSP;
  uint8 LucTempRxDataSP_Temp;

  Std_ReturnType LddReturnvalue = (Std_ReturnType)E_OK;

  /* Only in NORMAL mode, this MC33972's input status is upated */
  if (IoHwAb_GucTransitionStatus == MC33972_IN_NORMAL_MODE)
  {
    /* if mc33972 device is still in sleep mode */
    /* 1. when the mc33972 is waken up by input status change before LPM Task
      execution */
    /* 2. when the can transceiver is waken up by CAN NW activity before LPM
      Task execution */
    if (IoHwAb_GucDeviceStatus == DEVICE_IN_SLEEP)
    {
      /* for the case which the transition function is not called normally in
        TRANSITION_L2H */
      (void)IoHwAb_DigInMC33972L2H();
    }

    LucRawBufIdx = IoHwAb_GucNumDigInMcuLgc;

    /* update the raw buffer with the value in temp buffer */
    for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigInMC33972; LucIdx++)
    {
      /* Communication between MCU and MC33972 */
      LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddSpiChType,
        (Spi_DataType*)LaaTxDataByte, (Spi_DataType*)LaaRxDataByte,
        MC33972_SPISIZE);
      if (LddReturnvalue != (Std_ReturnType)E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGIN_MC33972_ACQ_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
      else
      {
        if (IoHwAb_GaaDigInMC33972Infos[LucIdx].blManualCS != 0U)
        {
          Dio_WriteChannel(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddCSDioChType, (Dio_LevelType)STD_LOW);
        }

        LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddSpiSeqType);

        if (IoHwAb_GaaDigInMC33972Infos[LucIdx].blManualCS != 0U)
        {
          Dio_WriteChannel(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddCSDioChType, (Dio_LevelType)STD_HIGH);
        }

        if (LddReturnvalue != (Std_ReturnType)E_OK)
        {
          #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
            (uint8)IOHWAB_DIGIN_MC33972_ACQ_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
          #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
          #if (IOHWAB_USE_DEM_EVENT == STD_ON)
          Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
          #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
        }
        else
        {
          LusTempRxDataSG = (uint16)(LaaRxDataByte[2]);  /* SG7~SG0 */
          LusTempRxDataSG_Temp = LaaRxDataByte[1] & 0x3FU ;
          LusTempRxDataSG_Temp <<= (uint16)8;  /* SG13~SG8 */
          LusTempRxDataSG += LusTempRxDataSG_Temp;

          LucTempRxDataSP = (uint8)(LaaRxDataByte[1] >> (Spi_DataType)6);  /* SP1~SP0 */
          LucTempRxDataSP_Temp = (uint8)((uint32)(LaaRxDataByte[0]) << (Spi_DataType)2);  /* SP7~SP2 */
          LucTempRxDataSP += LucTempRxDataSP_Temp;

          LucNumLgc = (uint8)(IoHwAb_GaaDigInMC33972Infos[LucIdx].usUsedPinsSG
            + IoHwAb_GaaDigInMC33972Infos[LucIdx].ucUsedPinsSP);

          /* update the raw buffer */
          for (LucSubIdx = 0U; LucSubIdx < LucNumLgc; LucSubIdx++)
          {
            LddBufIdx = (((IoHwAb_IndexType)LucRawBufIdx + (IoHwAb_IndexType)LucSubIdx) / (IoHwAb_IndexType)8);
            LucShiftBit = (LucRawBufIdx + LucSubIdx) % 8U;
            LucMC33972ShiftBit
              = (uint8)(IoHwAb_GaaDigInInfos[LucRawBufIdx + LucSubIdx].ddRefChIdx);

            if (LucSubIdx < IoHwAb_GaaDigInMC33972Infos[LucIdx].usUsedPinsSG)
            {
              LucValue = (uint8)((LusTempRxDataSG & (uint16)((uint16)1 << (uint16)LucMC33972ShiftBit))
              >> (uint16)LucMC33972ShiftBit);
            }
            else
            {
              LucValue = (uint8)((LucTempRxDataSP & (uint8)(1U << LucMC33972ShiftBit))
                >> LucMC33972ShiftBit);
            }

            SchM_Enter_IoHwAb_IoHwAbProtection();

            IoHwAb_GaaDigInRawBuffer[LddBufIdx].ucRawBuffer
              &= (uint8)(~((uint8)(1U << LucShiftBit)));

            IoHwAb_GaaDigInRawBuffer[LddBufIdx].ucRawBuffer
              |= (uint8)((LucValue & 0x01U) << LucShiftBit);

            SchM_Exit_IoHwAb_IoHwAbProtection();
          }
        }
      }
    }
  }
  else
  {
     /* In case of Not Normal mode */
     LddReturnvalue = (Std_ReturnType)E_OK;
  }
  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_USE_MC33972 == STD_ON) */

#if (IOHWAB_USE_MC33972 == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigInMC33972L2H                              **
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
**                          IoHwAb_GaaDigInMC33972Infos,                      **
**                          IoHwAb_GucTransitionStatus,                       **
**                          IoHwAb_GucDeviceStatus                            **
**                        Function(s) invoked    :                            **
**                          Icu_DisableNotification,                          **
**                          Icu_DisableEdgeDetection,                         **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus,                            **
**                          Spi_SetupEB,                                      **
**                          Spi_SyncTransmit                                  **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigInMC33972L2H(void)
{
  /* local index to update the raw buffer */
  uint8 LucIdx;
  uint8 LucSubIdx;

  /* set the Tx buffer to get the input status from Multiplexer */
  Spi_DataType LaaTxDataByte[SPISIZE_L2H];

  Std_ReturnType LddReturnvalue = (Std_ReturnType)E_OK;

  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigInMC33972; LucIdx++)
  {
    if (IoHwAb_GaaDigInMC33972Infos[LucIdx].ddIcuChType != ICU_NOT_USED_CHANNEL)
    {
      Icu_DisableNotification(
        (Icu_ChannelType)IoHwAb_GaaDigInMC33972Infos[LucIdx].ddIcuChType);
      Icu_DisableEdgeDetection(
        (Icu_ChannelType)IoHwAb_GaaDigInMC33972Infos[LucIdx].ddIcuChType);
    }
  }

  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigInMC33972; LucIdx++)
  {
    /* Interrupt and Wake-Up disable for SP pins */
    LucSubIdx = 0U;
    LaaTxDataByte[LucSubIdx] = WAKEUP_BIT_SP;
    LaaTxDataByte[LucSubIdx + 1U] = ALL_BIT_CLEAR;
    LaaTxDataByte[LucSubIdx + 2U] = ALL_BIT_CLEAR;

    /* Interrupt and Wake-Up disable for SG pins */
    LucSubIdx += (uint8)MC33972_SPISIZE;
    LaaTxDataByte[LucSubIdx] = WAKEUP_BIT_SG;
    LaaTxDataByte[LucSubIdx + 1U] = ALL_BIT_CLEAR;
    LaaTxDataByte[LucSubIdx + 2U] = ALL_BIT_CLEAR;

    /* Communication between MCU and MC33972 */
    for (LucSubIdx = 0U; LucSubIdx < (SPISIZE_L2H / MC33972_SPISIZE);
      LucSubIdx++)
    {
      LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddSpiChType,
        (Spi_DataType*)(&(LaaTxDataByte[((Spi_DataType)LucSubIdx * (Spi_DataType)MC33972_SPISIZE)])),
        IOHWAB_NULL_PTR, (Spi_NumberOfDataType)MC33972_SPISIZE);
      if (LddReturnvalue != (Std_ReturnType)E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGIN_MC33972_L2H_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
      else
      {
        if (IoHwAb_GaaDigInMC33972Infos[LucIdx].blManualCS != 0U)
        {
          Dio_WriteChannel(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddCSDioChType, (Dio_LevelType)STD_LOW);
        }

        LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddSpiSeqType);

        if (IoHwAb_GaaDigInMC33972Infos[LucIdx].blManualCS != 0U)
        {
          Dio_WriteChannel(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddCSDioChType, (Dio_LevelType)STD_HIGH);
        }

        if (LddReturnvalue != (Std_ReturnType)E_OK)
        {
          #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
            (uint8)IOHWAB_DIGIN_MC33972_L2H_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
          #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
          #if (IOHWAB_USE_DEM_EVENT == STD_ON)
          Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
          #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
        }
      }
    }
  }

  if (LddReturnvalue == (Std_ReturnType)E_OK)
  {
    /* MC33972's mode is in NORMAL MODE */
    IoHwAb_GucTransitionStatus = MC33972_IN_NORMAL_MODE;

    /* update the Device status */
    IoHwAb_GucDeviceStatus = DEVICE_IN_NORMAL;
  }
  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_USE_MC33972 == STD_ON) */

#if (IOHWAB_USE_MC33972 == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigInMC33972H2L                              **
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
**                          IoHwAb_GaaDigInMC33972Infos,                      **
**                          IoHwAb_GucTransitionStatus,                       **
**                          IoHwAb_GucDeviceStatus                            **
**                        Function(s) invoked    :                            **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus,                            **
**                          Spi_SetupEB,                                      **
**                          Spi_SyncTransmit,                                 **
**                          Icu_EnableNotification,                           **
**                          Icu_EnableEdgeDetection                           **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigInMC33972H2L(void)
{
  /* local index to update the raw buffer */
  uint8 LucIdx;
  uint8 LucSubIdx;

  /* set the Tx buffer to get the input status from Multiplexer */
  Spi_DataType LaaTxDataByte[SPISIZE_H2L];

  Std_ReturnType LddReturnvalue = (Std_ReturnType)E_OK;

  /* Only if this MC33972 is in NORMAL mode */
  if (IoHwAb_GucTransitionStatus == MC33972_IN_NORMAL_MODE)
  {
    for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigInMC33972; LucIdx++)
    {
      /* Interrupt and Wake-Up disable for SP pins */
      LucSubIdx = 0U;
      LaaTxDataByte[LucSubIdx] = WAKEUP_BIT_SP;
      LaaTxDataByte[LucSubIdx + 1U] = ALL_BIT_CLEAR;
      LaaTxDataByte[LucSubIdx + 2U] = IoHwAb_GaaDigInMC33972Infos[LucIdx].ucWakeUpBitSP;

      /* Interrupt and Wake-Up disable for SG pins */
      LucSubIdx += (uint8)MC33972_SPISIZE;
      LaaTxDataByte[LucSubIdx] = WAKEUP_BIT_SG;
      LaaTxDataByte[LucSubIdx + 1U]
        = (uint8)(IoHwAb_GaaDigInMC33972Infos[LucIdx].usWakeUpBitSG >> 8);
      LaaTxDataByte[LucSubIdx + 2U]
        = (uint8)(IoHwAb_GaaDigInMC33972Infos[LucIdx].usWakeUpBitSG & 0xFFU);

      /* Sleep with scan period value */
      LucSubIdx += (uint8)MC33972_SPISIZE;
      LaaTxDataByte[LucSubIdx] = SLEEP_CMD;
      LaaTxDataByte[LucSubIdx + 1U] = ALL_BIT_CLEAR;
      LaaTxDataByte[LucSubIdx + 2U] = IoHwAb_GaaDigInMC33972Infos[LucIdx].ucSleep;

      /* Communication between MCU and MC33972 */
      for (LucSubIdx = 0U; LucSubIdx < (SPISIZE_H2L / MC33972_SPISIZE);
        LucSubIdx++)
      {
        LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddSpiChType,
          (Spi_DataType*)(&(LaaTxDataByte[((Spi_DataType)LucSubIdx * (Spi_DataType)MC33972_SPISIZE)])),
          IOHWAB_NULL_PTR, MC33972_SPISIZE);
        if (LddReturnvalue != (Std_ReturnType)E_OK)
        {
          #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
            (uint8)IOHWAB_DIGIN_MC33972_H2L_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
          #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
          #if (IOHWAB_USE_DEM_EVENT == STD_ON)
          Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
          #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
        }
        else
        {
          if (IoHwAb_GaaDigInMC33972Infos[LucIdx].blManualCS != 0U)
          {
            Dio_WriteChannel(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddCSDioChType, (Dio_LevelType)STD_LOW);
          }

          LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddSpiSeqType);

          if (IoHwAb_GaaDigInMC33972Infos[LucIdx].blManualCS != 0U)
          {
            Dio_WriteChannel(IoHwAb_GaaDigInMC33972Infos[LucIdx].ddCSDioChType, (Dio_LevelType)STD_HIGH);
          }

          if (LddReturnvalue != (Std_ReturnType)E_OK)
          {
            #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
            /* Report to DET */
            (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
              (uint8)IOHWAB_DIGIN_MC33972_H2L_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
            #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
            #if (IOHWAB_USE_DEM_EVENT == STD_ON)
            Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
            #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
          }
        }
      }
    }

    if (LddReturnvalue == (Std_ReturnType)E_OK)
    {
      /* MC33972's mode is in NORMAL MODE */
      IoHwAb_GucTransitionStatus = MC33972_IN_SLEEP_MODE;

      /* update the Device status */
      IoHwAb_GucDeviceStatus = DEVICE_IN_SLEEP;

      /* Start External Interrupt to get the information
        whether the local input status is changed or not */
      for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigInMC33972; LucIdx++)
      {
        if (IoHwAb_GaaDigInMC33972Infos[LucIdx].ddIcuChType != ICU_NOT_USED_CHANNEL)
        {
          Icu_EnableNotification(
            (Icu_ChannelType)IoHwAb_GaaDigInMC33972Infos[LucIdx].ddIcuChType);
          Icu_EnableEdgeDetection(
            (Icu_ChannelType)IoHwAb_GaaDigInMC33972Infos[LucIdx].ddIcuChType);
        }
      }
    }
  }
  else 
  {
     /* In case of Not Normal mode */
     LddReturnvalue = (Std_ReturnType)E_NOT_OK;     
  }
  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_USE_MC33972 == STD_ON) */

#if (IOHWAB_USE_MC33972 == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigInMC33972IntermediateWakeUp               **
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
**                          IoHwAb_GaaDigInMC33972Infos,                      **
**                          IoHwAb_GucTransitionStatus,                       **
**                          IoHwAb_GucDeviceStatus                            **
**                        Function(s) invoked    :                            **
**                          Icu_DisableNotification,                          **
**                          Icu_DisableEdgeDetection,                         **
**                          IoHwAb_DigInMC33972L2H                            **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigInMC33972IntermediateWakeUp(void)
{
  uint8 LucIdx;

  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigInMC33972; LucIdx++)
  {
    if (IoHwAb_GaaDigInMC33972Infos[LucIdx].ddIcuChType != ICU_NOT_USED_CHANNEL)
    {
      Icu_DisableNotification(
        (Icu_ChannelType)IoHwAb_GaaDigInMC33972Infos[LucIdx].ddIcuChType);
      Icu_DisableEdgeDetection(
        (Icu_ChannelType)IoHwAb_GaaDigInMC33972Infos[LucIdx].ddIcuChType);
    }
  }

  (void)IoHwAb_DigInMC33972L2H();

  #if (IOHWAB_USE_LP_FLAG == STD_ON)
  BswM_RequestMode((BswM_UserType)IOHWAB_MODULE_ID, (BswM_ModeType)IOHWAB_LOWPOWER_PREVENT);
  #endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */

  /* MC33972's mode is in NORMAL MODE */
  IoHwAb_GucTransitionStatus = MC33972_IN_NORMAL_MODE;

  /* Transition process status update */
  /* 1. If 'bi_mc33972_l2h' function is called in TRANSITON_L2H callback
    function, this status variable is updated with "DEVICE_IN_NORMAL" */
  /* 2. If 'bi_mc33972_l2h' function is not called because of wake up before
    LPM Task is not executed, the mc33972 will be waken up
    in bi_mc33972_Acq() */

  IoHwAb_GucDeviceStatus = DEVICE_IN_SLEEP;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_USE_MC33972 == STD_ON) */
#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

/*polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:end<MISRA-C:17.4:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
