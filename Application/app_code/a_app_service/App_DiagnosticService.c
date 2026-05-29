/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  FILE NAME : App_DiagnosticService.c                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the API definitions for SW-C Sample of Dcm **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_SWC_DiagnosticService.h"
#include "HwResource.h"

#include "Data.h"
#include "define.h"
#include "app_can_input_type.h"
#include "app_can_input.h"
#include "app_input_type.h"
#include "app_input.h"
#include "WPCVehicleOption.h"
#include "Dcm_Types.h"

#include "Port.h"
#include "Hsm_HostAPI.h"
#include "SecurityApp_FwTamperDetection.h"
#include "SecurityApp_SecureDebug.h"
#include "SecurityApp_SecureBoot.h"
#include "Wdg_66_IA_Api.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define kECUReset                   0x11u
#define kHardReset                  0x01u
#define kKeyOffOnReset              0x02u
#define kSoftReset                  0x03u
#define kEnableRapidPowerShutDown   0x04u
#define kDisableRapidPowerShutDown  0x05u
#define kDTCSettingType_On			0x01u
#define kDTCSettingType_Off			0x02u

static uint8 b_EngineStop = Off;
static uint8 b_EngineStopIgnOn = Off;
extern uint8 DTC_Set_Status;
uint8 SessionNontify = 0u;


/* L9 : Advanced Seed Key*/
#if defined(Rte_Call_AutHsmPseudoRandomGenerate_L9_RandomGenerate)
#if HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
  #define APPDCM_L9_AUTRON_HSM_RANDOM_ICUM
#else
  #define APPDCM_L9_AUTRON_HSM_RANDOM
#endif

#elif defined(Rte_Call_HaeHsmPseudoRandomGenerate_L9_RandomGenerate)
  #define APPDCM_L9_HAE_HSM_RANDOM

#elif defined(Rte_Call_AutIcusRandomGenerate_L9_RandomGenerate)
  #define APPDCM_L9_ICUS_RANDOM

#elif (defined(Rte_Call_HaePseudoRandomSeed_L9_RandomSeedStart) \
&& defined(Rte_Call_HaePseudoRandomSeed_L9_RandomSeedUpdate) \
&& defined(Rte_Call_HaePseudoRandomSeed_L9_RandomSeedFinish) \
&& defined(Rte_Call_HaePseudoRandomGenerate_L9_RandomGenerate))
  #define APPDCM_L9_HAE_PSEUDO_RANDOM
  #define APPDCM_L9_HAE_PSEUDO_ENTROPY_LENGTH 16U
#else
  #define APPDCM_L9_NOT_SUPPORTED

#endif

#if (defined(Rte_Call_HaeAdvSeedKey_L9_HashStart) \
  && defined(Rte_Call_HaeAdvSeedKey_L9_HashUpdate) \
  && defined(Rte_Call_HaeAdvSeedKey_L9_HashFinish))
  #define APPDCM_L9_ADVANCED_SEEDKEY
#endif

/* Generate Seed from random generator */

uint8 AppDcm_GucSID = 0U;
uint8 AppDcm_GucReqType = 0U;
uint16 AppDcm_GusSourceAddress = 0U;
uint16 AppDcm_GusDataSize = 0U;
Dcm_ConfirmationStatusType AppDcm_GddConfirmationStatus = 0U;

/* Global Variables for SecurityAccess_L1 */
uint8 AppDcm_GaaSeed[4] = {0U, };
/* Global Variables for SecurityAccess_L9 */
#if defined(APPDCM_L9_AUTRON_HSM_RANDOM_ICUM)
#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
#endif
uint8 AppDcm_GaaAdvSeed[8];
#if defined(APPDCM_L9_AUTRON_HSM_RANDOM_ICUM)
#pragma ghs section
#endif

#if (defined(APPDCM_L9_ICUS_RANDOM) || defined(APPDCM_L9_AUTRON_HSM_RANDOM_ICUM))
Std_ReturnType AppDcm_SeedGenResult;
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
/*******************************************************************************
** Function Name        : AppDcm_DiagnosticSessionControlNotification         **
**                                                                            **
** Description          : This function notifies session transition.          **
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
*******************************************************************************/
FUNC(void,SWC_DiagnosticService_CODE)
  AppDcm_DiagnosticSessionControlNotification(void)
{
  Rte_ModeType_DcmDiagnosticSessionControl LddPrevMode;
  Rte_ModeType_DcmDiagnosticSessionControl LddNextMode;

  Rte_Mode_modeNotificationPort_SessionControl_DcmDiagnosticSessionControl(
                                                    &LddPrevMode, &LddNextMode);
  /* DiagnosticSessionControl(0x10) service */
  if (LddNextMode == DCM_DEFAULT_SESSION)
  {
    SessionNontify = kDefaultSession_NoSec;
    (void)Rte_Write_P_SessionNotify_SR(SessionNontify);
    DTC_Set_Status = On;
  }
  else if (LddNextMode == DCM_PROGRAMMING_SESSION)
  {
    SessionNontify = kProgrammingSession_NoSec;
    (void)Rte_Write_P_SessionNotify_SR(SessionNontify);
  }
  else if (LddNextMode == DCM_EXTENDED_DIAGNOSTIC_SESSION)
  {
    SessionNontify = kExtendedSession_NoSec;
    (void)Rte_Write_P_SessionNotify_SR(SessionNontify);
  }
  else if (LddNextMode == DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION)
  {
    SessionNontify = kSafetySystemSession_Nosec;
    (void)Rte_Write_P_SessionNotify_SR(SessionNontify);
  }
  else
  {/*MISRA-C*/}

}

/*******************************************************************************
** Function Name        : AppDcm_StartProtocol                                **
**                                                                            **
** Description          : This function notifies the start of a particular    **
**                        protocol.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ProtocolID                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_CallbackDCMRequestServices_E_NOT_OK :                            **
**     Request was not successful                                             **

**   - RTE_E_CallbackDCMRequestServices_E_PROTOCOL_NOT_ALLOWED : conditions in**
**     conditions in application allows no further procession of protocol     **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) AppDcm_StartProtocol(
  IN Dcm_ProtocolType ProtocolID)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : AppDcm_StopProtocol                                 **
**                                                                            **
** Description          : This function notifies the stop of a particular     **
**                        protocol.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ProtocolID                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_CallbackDCMRequestServices_E_NOT_OK :                            **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) AppDcm_StopProtocol(
  IN Dcm_ProtocolType ProtocolID)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : AppDcm_GetSeed_L9                                   **
**                                                                            **
** Description          : Request to application for asynchronous provision of**
**                        seed value.                                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus : Status of the current operation                               **
**   - DCM_INITIAL : Indicates the initial call to the operation              **
**   - DCM_PENDING : Indicates that a pending return has been done on         **
**                   the previous call of the operation                       **
**   - DCM_CANCEL : Indicates that the DCM requests to cancel                 **
**                  the pending operation                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Seed : Pointer for provided seed                                         **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value. (Refer to the Rte_Dcm_Type.h)                 **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_SecurityAccess_L9_E_NOT_OK : Request was not successful          **
**   - RTE_E_SecurityAccess_L9_DCM_E_PENDING :                                **
**     Request is not yet finished, Further call required to finish           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_SecurityAccess_L9_E_NOT_OK)

#if (defined(APPDCM_L9_AUTRON_HSM_RANDOM) || defined(APPDCM_L9_HAE_HSM_RANDOM))
FUNC(Std_ReturnType, RTE_CODE) AppDcm_GetSeed_L9(
  IN Dcm_OpStatusType OpStatus,
  OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Seed,
  OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_SecurityAccess_L9_E_NOT_OK;

  #if defined(APPDCM_L9_AUTRON_HSM_RANDOM)
  /***************************************************************************
   *                 true random generator(Chorus SPC58)                     *
   ***************************************************************************/
  if (RTE_E_OK == Rte_Call_AutHsmPseudoRandomGenerate_L9_RandomGenerate(&AppDcm_GaaAdvSeed[0], 8U))

  #elif defined(APPDCM_L9_HAE_HSM_RANDOM)
  /***************************************************************************
   *                 true random generator(Autoever HSM)                      *
   ***************************************************************************/
  if (RTE_E_OK == Rte_Call_HaeHsmPseudoRandomGenerate_L9_RandomGenerate(&AppDcm_GaaAdvSeed[0], 8U))

  #endif
  {
    uint8 LucIndex;
    for (LucIndex = 0U; LucIndex < 8U; LucIndex++)
    {
      Seed[LucIndex] = AppDcm_GaaAdvSeed[LucIndex];
    }
    LddRetVal = RTE_E_OK;
  }
  else
  {
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return LddRetVal;
}

#elif (defined(APPDCM_L9_ICUS_RANDOM) || defined(APPDCM_L9_AUTRON_HSM_RANDOM_ICUM))
FUNC(Std_ReturnType, RTE_CODE) AppDcm_GetSeed_L9(
  IN Dcm_OpStatusType OpStatus,
  OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Seed,
  OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_SecurityAccess_L9_E_NOT_OK;

  switch(OpStatus)
  {
  case DCM_INITIAL:
    #if defined(APPDCM_L9_ICUS_RANDOM)
    /***************************************************************************
     *                 true random generator(RH850 ICUS)                       *
     ***************************************************************************/
    if (RTE_E_OK == Rte_Call_AutIcusRandomGenerate_L9_RandomGenerate(&AppDcm_GaaAdvSeed[0], 8U))

    #elif defined(APPDCM_L9_AUTRON_HSM_RANDOM_ICUM)
    /***************************************************************************
     *                 true random generator(RH850 ICUM)                       *
     ***************************************************************************/
    if (RTE_E_OK == Rte_Call_AutHsmPseudoRandomGenerate_L9_RandomGenerate(&AppDcm_GaaAdvSeed[0], 8U))

    #endif
    {
      AppDcm_SeedGenResult = RTE_E_SecurityAccess_L9_DCM_E_PENDING;
      LddRetVal = RTE_E_SecurityAccess_L9_DCM_E_PENDING;
    }
    break;

  case DCM_PENDING:
    LddRetVal = AppDcm_SeedGenResult;
    if (RTE_E_OK == AppDcm_SeedGenResult)
    {
      uint8 LucIndex;
      for (LucIndex = 0U; LucIndex < 8U; LucIndex++)
      {
        Seed[LucIndex] = AppDcm_GaaAdvSeed[LucIndex];
      }
    }
    break;

  case DCM_CANCEL:
    LddRetVal = RTE_E_OK;
    break;
  default :
    break;
  }

  if (RTE_E_SecurityAccess_L9_E_NOT_OK == LddRetVal)
  {
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  return LddRetVal;
}

FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_GetSeedCbk_L9(
  IN VAR(Std_ReturnType, AUTOMATIC) retVal)
{
  if (retVal == RTE_E_OK)
  {
    AppDcm_SeedGenResult = RTE_E_OK;
  }
  else
  {
    AppDcm_SeedGenResult = RTE_E_SecurityAccess_L9_E_NOT_OK;
  }

  return RTE_E_OK;
}

#elif defined(APPDCM_L9_HAE_PSEUDO_RANDOM)

FUNC(Std_ReturnType, RTE_CODE) AppDcm_GetRandomSeed(
  P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) RandomSeed)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /*
  * Apply user RandomSeed to the argument in this function.
  * RandomSeed is a 16-row array. (RandomSeed[16])
  * Assign a random number to this variable (RandomSeed)
  * ex) current time, tick count, event timer, ADC noise, sensor value, etc..
  */

  /*
  * If you apply RandomSeed, you must return E_OK.
  * E_OK : Use the user RandomSeed
  * E_NOT_OK : Fail to use RandomSeed
  */

  /* Example of SPC58x RandomSeed.
   * This code is an example and is not guaranteed and should be used only for reference.
   * OS tick address is different for each MCU
   *
   *
   * uint32 LulSeed, LulSeedAddr, LulNoise;
   * uint8 LucIndex;
   *
   * LulSeedAddr = 0xF4070004; // Address of SPC58x OS Tick
   * LulSeed=(*(volatile uint32*)LulSeedAddr);
   *
   * for(LucIndex=0; LucIndex<APPDCM_L9_HAE_PSEUDO_ENTROPY_LENGTH; LucIndex++)
   * {
   *   LulSeed = (uint32)((LulSeed * 1103515245 + 12345)>>16) & 0xFF;
   *   RandomSeed[LucIndex] = (uint8)(LulSeed + LulNoise);
   * }
   *
   *  RetVal = E_OK;
   *
   */

  #ifdef INSTST_TESTCODE_INTEGRATED
  RetVal = E_OK;
  #endif

  return RetVal;
}

FUNC(Std_ReturnType, RTE_CODE) AppDcm_GetSeed_L9(
  IN Dcm_OpStatusType OpStatus,
  OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Seed,
  OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_SecurityAccess_L9_E_NOT_OK;
  volatile static boolean LblRandomSeedUpdated = FALSE;

  if (FALSE == LblRandomSeedUpdated)
  {
    uint8 LaaHaeHacSalt_L9[APPDCM_L9_HAE_PSEUDO_ENTROPY_LENGTH] = {0U};

    /* Get RandomSeed */
    LddRetVal = AppDcm_GetRandomSeed(LaaHaeHacSalt_L9);

    if (E_OK == LddRetVal)
    {
      /* Update RandomSeed */
      if (RTE_E_OK == Rte_Call_HaePseudoRandomSeed_L9_RandomSeedStart())
      {
        if (RTE_E_OK == Rte_Call_HaePseudoRandomSeed_L9_RandomSeedUpdate(LaaHaeHacSalt_L9, APPDCM_L9_HAE_PSEUDO_ENTROPY_LENGTH))
        {
          if (RTE_E_OK == Rte_Call_HaePseudoRandomSeed_L9_RandomSeedFinish())
          {
            LblRandomSeedUpdated = TRUE;
          }
        }
      }
    }
  }

  if (TRUE == LblRandomSeedUpdated)
  {
    if (RTE_E_OK == Rte_Call_HaePseudoRandomGenerate_L9_RandomGenerate(&AppDcm_GaaAdvSeed[0], 8U))
    {
      uint8 LucIndex;
      for (LucIndex = 0U; LucIndex < 8U; LucIndex++)
      {
        Seed[LucIndex] = AppDcm_GaaAdvSeed[LucIndex];
      }
      LddRetVal = RTE_E_OK;
    }
  }
  if (RTE_E_OK != LddRetVal)
  {
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return LddRetVal;
}
#endif

#endif /* defined(RTE_E_SecurityAccess_L9_E_NOT_OK) */

/*******************************************************************************
** Function Name        : AppDcm_CompareKey_L9                                **
**                                                                            **
** Description          : Request to application for asynchronous comparing   **
**                        key.                                                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - Key : Key, which needs to be compared                                    **
** - OpStatus : Status of the current operation                               **
**   - DCM_INITIAL : Indicates the initial call to the operation              **
**   - DCM_PENDING : Indicates that a pending return has been done on         **
**                   the previous call of the operation                       **
**   - DCM_CANCEL : Indicates that the DCM requests to cancel                 **
**                  the pending operation                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_SecurityAccess_L9_E_NOT_OK : Request was not successful          **
**   - RTE_E_SecurityAccess_L9_DCM_E_PENDING :                                **
**     Request is not yet finished, Further call required to finish           **
**   - RTE_E_SecurityAccess_L9_DCM_E_COMPARE_KEY_FAILED : Key did not match   **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_SecurityAccess_L9_E_NOT_OK)
FUNC(Std_ReturnType, RTE_CODE) AppDcm_CompareKey_L9(
  IN P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) Key,
  IN Dcm_OpStatusType OpStatus)
{
  Std_ReturnType LddRetVal = RTE_E_SecurityAccess_L9_E_NOT_OK;
#if 0  
  uint8 i;

  uint8 MCS_WPC_SeedKey[8] = {0x4D, 0x43, 0x53, 0x09, 0x4D, 0x43, 0x53, 0x09};	//Master Key

  #if defined(APPDCM_L9_ADVANCED_SEEDKEY)
  /***************************************************************************
   *           generate the  key  based on the advanced seedKey algorithm    *
   ***************************************************************************/
  if (RTE_E_OK == Rte_Call_HaeAdvSeedKey_L9_HashStart() )
  {
    if (RTE_E_OK == Rte_Call_HaeAdvSeedKey_L9_HashUpdate(&AppDcm_GaaAdvSeed[0], 8U) )
    {
      uint8 LaaKey[8] = {0U, };
      uint32 LulLength = 8U;

      if (RTE_E_OK == Rte_Call_HaeAdvSeedKey_L9_HashFinish(LaaKey, &LulLength, FALSE))
      {
        uint8 LucIndex;
        for (LucIndex = 0U; LucIndex < 8U; LucIndex++)
        {
          if (LaaKey[LucIndex] != Key[LucIndex])
          {
            break;
          }
        }
        if (LucIndex == LulLength)
        {
          /* key matches */
          LddRetVal = RTE_E_OK;
        }
        else
        {
          LddRetVal = RTE_E_SecurityAccess_L9_DCM_E_COMPARE_KEY_FAILED;
        }
      }
    }
  }
  #endif

	if(LddRetVal != RTE_E_OK)
	{
		for(i = 0; i < 8U; i++)
		{
			if(MCS_WPC_SeedKey[i] != Key[i])
			{
				break;
			}
		}

		if(i == 8u)
		{/* key matches */
			LddRetVal = RTE_E_OK;
		}
	}
#endif
	LddRetVal = RTE_E_OK;
  return LddRetVal;
}
#endif /* defined(RTE_E_SecurityAccess_L9_E_NOT_OK) */

/*******************************************************************************
** Function Name        : ServiceRequestSupplierNotification_Confirmation     **
**                                                                            **
** Description          : This function notifies the confirmation of          **
**                        diagnostic service.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - SID : Service ID                                                         **
** - ReqType : Rx message address type                                        **
** - SourceAddress : Source address                                           **
** - ConfirmationStatus :                                                     **
**   - DCM_RES_POS_OK : Transmission of positive response was successful      **
**   - DCM_RES_POS_NOT_OK : Transmission of positive response failled         **
**   - DCM_RES_NEG_OK : Transmission of negative response was successful      **
**   - DCM_RES_NEG_NOT_OK : Transmission of negative response failled         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_ServiceRequestNotification_E_NOT_OK : Request was not successful **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) ServiceRequestSupplierNotification_Confirmation(
  IN uint8 SID,
  IN uint8 ReqType,
  IN uint16 SourceAddress,
  IN Dcm_ConfirmationStatusType ConfirmationStatus)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  AppDcm_GucSID = SID;
  AppDcm_GucReqType = ReqType;
  AppDcm_GusSourceAddress = SourceAddress;
  AppDcm_GddConfirmationStatus = ConfirmationStatus;

  if(AppDcm_GddConfirmationStatus==DCM_RES_POS_OK)
  {
    (void)Rte_Call_R_Start_WPCDiagState_CS();
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : ServiceRequestSupplierNotification_Indication       **
**                                                                            **
** Description          : This function notifies the confirmation of          **
**                        diagnostic service.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - SID : Service ID                                                         **
** - RequestData : Pointer to received data                                   **
** - DataSize : Data length of received data                                  **
** - ReqType : Rx message address type                                        **
** - SourceAddress : Source address                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value. (Refer to the Rte_Dcm_Type.h)                 **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_ServiceRequestNotification_E_NOT_OK : Request was not successful **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType,RTE_CODE) ServiceRequestSupplierNotification_Indication(
  IN uint8 SID,
  IN P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) RequestData,
  IN uint16 DataSize,
  IN uint8 ReqType,
  IN uint16 SourceAddress,
  OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
	Std_ReturnType LddRetVal = RTE_E_OK;
  
  	AppDcm_GucSID = SID;
  	AppDcm_GusDataSize = DataSize;
  	AppDcm_GucReqType = ReqType;
  	AppDcm_GusSourceAddress = SourceAddress;

  	uint8 Sub_function;

	Sub_function = RequestData[0]&0x7Fu;  /* clear suppressPosRspMsgIndicationBit */
	/* Engine Stop */
#if 1	/* ES95486-02 Rev 16 */	
	if((GetX(kC_ENG_EngSta) != kEngineState_Running) &&	/* EMS_02_10ms_1 : Emission Engine */
		(GetX(kC_HCU_HevRdySta) != kHCU_HCU_HevRdySta_HEV_Drivable) &&	/* HCU_03_10ms_2 : Hybrid */
		(GetX(kC_VCU_EvDrvRdySta) != kVCU_EvDrvRdySta_EV_Drivable))		  /* VCU_01_10ms_1 : EV */ 
#else	/* ES95486-02 Rev 15 */
	if(!((GetX(kC_ENG_EngSta) == kEngineState_Cranking) ||
		(GetX(kC_ENG_EngSta) == kEngineState_StAlled) ||
		(GetX(kC_ENG_EngSta) == kEngineState_Running)) &&
		(GetX(kC_HCU_HevRdySta) != kHCU_HCU_HevRdySta_HEV_Drivable))
#endif	
	{
		b_EngineStop = On;	
	}
	else
	{
		b_EngineStop = Off;
	}

	/* Engine Stop && IGN On */
#if 1	/* ES95486-02 Rev 16 */	
	if((GetX(kC_ENG_EngSta) != kEngineState_Running) &&		        /* EMS_02_10ms_1 : Emission Engine */
		(GetX(kC_HCU_HevRdySta) != kHCU_HCU_HevRdySta_HEV_Drivable) &&	/* HCU_03_10ms_2 : Hybrid */
		(GetX(kC_VCU_EvDrvRdySta) != kVCU_EvDrvRdySta_EV_Drivable) &&	/* VCU_01_10ms_1 : EV */ 
		(GetX(kb_IGN_IN) == On))
#else	/* ES95486-02 Rev 15 */
	if((GetX(kC_ENG_EngSta) == (uint8)kEngineState_Stop) && 
		(GetX(kC_HEV_EngOpSta) == (uint8)kHEV_EngOpSta_ES) &&
		(GetX(kb_IGN_IN) == On))
#endif	
	{
		b_EngineStopIgnOn = On;
	}
	else
	{
	  	b_EngineStopIgnOn = Off;
	}

	if(((AppDcm_GucSID == DCM_DIAGNOSTICSESSIONCONTROL) && ((RequestData[0] == DCM_PROGRAMMING_SESSION) || (RequestData[0] == DCM_ECU_PROGRAMMING_MODE_05H)))||
		(AppDcm_GucSID == DCM_ECURESET) ||
		(AppDcm_GucSID == DCM_COMMUNICATIONCONTROL))
	{
		if(b_EngineStop == Off)
		{
			LddRetVal = E_NOT_OK;
			*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
		}
	}
	if((AppDcm_GucSID == DCM_WRITEDATABYIDENTIFIER) ||
		(AppDcm_GucSID == DCM_WRITEMEMORYBYADDRESS))
	{
		if(b_EngineStopIgnOn == Off)
		{
			LddRetVal = E_NOT_OK;
			*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
		}
	}

	if((AppDcm_GucSID == DCM_CONTROLDTCSETTING) &&
	   (AppDcm_GusDataSize == 1u))
	{
		if(Sub_function == kDTCSettingType_On)
		{
			DTC_Set_Status = On;
		}
		else if(Sub_function == kDTCSettingType_Off)
		{
			DTC_Set_Status = Off;
		}
	}
	
/*	
	if(((AppDcm_GucSID == DCM_DIAGNOSTICSESSIONCONTROL) && ((RequestData[0] == DCM_PROGRAMMING_SESSION) || (RequestData[0] == DCM_ECU_PROGRAMMING_MODE_05H)))||
		(AppDcm_GucSID == DCM_ECURESET) ||
		(AppDcm_GucSID == DCM_WRITEDATABYIDENTIFIER) ||
		(AppDcm_GucSID == DCM_ROUTINECONTROL) ||
		(AppDcm_GucSID == DCM_WRITEMEMORYBYADDRESS) ||
		(AppDcm_GucSID == DCM_REQUESTDOWNLOAD) ||
		(AppDcm_GucSID == DCM_REQUESTUPLOAD) ||
		(AppDcm_GucSID == DCM_TRANSFERDATA) ||
		(AppDcm_GucSID == DCM_REQUESTTRANSFEREXIT))
	{
		if(b_EngineStopIgnOn == Off)
		{
			LddRetVal = E_NOT_OK;
			*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
		}
	}
*/

#if 0
  if((AppDcm_GucSID == kECUReset) &&
    (DataSize == 1u) &&
    (GetX(b_DiagnosticInhibitCheck)==Off) &&
    ((Sub_function == kHardReset) ||
     (Sub_function == kKeyOffOnReset) ||
     (Sub_function == kSoftReset) ||
     (Sub_function == kEnableRapidPowerShutDown) ||
     (Sub_function == kDisableRapidPowerShutDown)))
  {
    /* TPMS */
    RetVal = Rte_Call_R_ECU_Reset_CS();

  if(RetVal == RTE_E_IF_ECU_Reset_Response_Fail)
  {
    LddRetVal = E_NOT_OK;
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  }
  else if((AppDcm_GucSID == kECUReset) &&
    (GetX(b_DiagnosticInhibitCheck)==On) )
  {
    LddRetVal = E_NOT_OK;
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else{ /* MISRA-C */ }

#endif

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : ServiceRequestManufacturerNotification_Confirmation **
**                                                                            **
** Description          : This function notifies the confirmation of          **
**                        diagnostic service.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - SID : Service ID                                                         **
** - ReqType : Rx message address type                                        **
** - SourceAddress : Source address                                           **
** - ConfirmationStatus :                                                     **
**   - DCM_RES_POS_OK : Transmission of positive response was successful      **
**   - DCM_RES_POS_NOT_OK : Transmission of positive response failled         **
**   - DCM_RES_NEG_OK : Transmission of negative response was successful      **
**   - DCM_RES_NEG_NOT_OK : Transmission of negative response failled         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_ServiceRequestNotification_E_NOT_OK : Request was not successful **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) ServiceRequestManufacturerNotification_Confirmation(
  IN uint8 SID,
  IN uint8 ReqType,
  IN uint16 SourceAddress,
  IN Dcm_ConfirmationStatusType ConfirmationStatus)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  AppDcm_GucSID = SID;
  AppDcm_GucReqType = ReqType;
  AppDcm_GusSourceAddress = SourceAddress;
  AppDcm_GddConfirmationStatus = ConfirmationStatus;

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : ServiceRequestManufacturerNotification_Indication   **
**                                                                            **
** Description          : This function notifies the confirmation of          **
**                        diagnostic service.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - SID : Service ID                                                         **
** - RequestData : Pointer to received data                                   **
** - DataSize : Data length of received data                                  **
** - ReqType : Rx message address type                                        **
** - SourceAddress : Source address                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value. (Refer to the Rte_Dcm_Type.h)                 **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_ServiceRequestNotification_E_NOT_OK : Request was not successful **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType,RTE_CODE) ServiceRequestManufacturerNotification_Indication(
  IN uint8 SID,
  IN P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) RequestData,
  IN uint16 DataSize,
  IN uint8 ReqType,
  IN uint16 SourceAddress,
  OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  AppDcm_GucSID = SID;
  AppDcm_GusDataSize = DataSize;
  AppDcm_GucReqType = ReqType;
  AppDcm_GusSourceAddress = SourceAddress;

  return LddRetVal;
}

FUNC(void, RTE_CODE) ApplicationUpdatedIndication(void)
{
}

/* Start Configuration Lock */

FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) RID_B194h_HSMConfigLockSecureDebug_Start(
  IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
  OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DataOut_RoutineRequestResOutSignal,
  OUT P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) currentDataLength,
  OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  VAR(Std_ReturnType, RTE_DATA) LddRetVal;

  Std_ReturnType B194_ConfingLockStateResult = E_NOT_OK;
  Std_ReturnType B194_GETHSMInfoResult = E_NOT_OK;

  HSM_CONFIG_LOCK_STATE_t Arg_ConfigLockState = HSM_CONFIG_LOCK_DISABLE;
  HSM_SECURITY_INFO_t Arg_GET_HSMInfo;

  HSM_CONFIG_LOCK_STATE_t B194_ConfingLockStateResultData = HSM_CONFIG_LOCK_DISABLE;
  HSM_SECURITY_INFO_t B194_GETHSMInfoResultData;

  LddRetVal = RTE_E_RoutineServices_RID_B194h_HSMConfigLockSecureDebug_E_NOT_OK;

  switch(OpStatus)
  {
    case DCM_INITIAL:

        DataOut_RoutineRequestResOutSignal[0]=0u;
        DataOut_RoutineRequestResOutSignal[1]=0u;

        B194_ConfingLockStateResult = HSM_GetConfigurationLockState(&Arg_ConfigLockState);
        B194_GETHSMInfoResult = HSM_GetAllSecurityInfo(&Arg_GET_HSMInfo);

        if(B194_ConfingLockStateResult == E_OK &&
          B194_GETHSMInfoResult == E_OK)
        {
          B194_ConfingLockStateResultData = Arg_ConfigLockState;
          B194_GETHSMInfoResultData = Arg_GET_HSMInfo;

          DataOut_RoutineRequestResOutSignal[0] |= B194_ConfingLockStateResultData;
          DataOut_RoutineRequestResOutSignal[0] |= B194_GETHSMInfoResultData.secureBootState<<4u;
          DataOut_RoutineRequestResOutSignal[1] |= B194_GETHSMInfoResultData.fwTamperDetectionState;
          DataOut_RoutineRequestResOutSignal[1] |= B194_GETHSMInfoResultData.secureDebugState<<4u;

          *currentDataLength = 2u;
           LddRetVal = E_OK;
          *ErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          LddRetVal = RTE_E_RoutineServices_RID_B194h_HSMConfigLockSecureDebug_DCM_E_PENDING;
        }
      break;

    case DCM_PENDING:

        B194_ConfingLockStateResult = HSM_GetConfigurationLockState(&Arg_ConfigLockState);
        B194_GETHSMInfoResult = HSM_GetAllSecurityInfo(&Arg_GET_HSMInfo);

        if(B194_ConfingLockStateResult == E_OK &&
          B194_GETHSMInfoResult == E_OK)
        {
          B194_ConfingLockStateResultData = Arg_ConfigLockState;
          B194_GETHSMInfoResultData = Arg_GET_HSMInfo;

          DataOut_RoutineRequestResOutSignal[0] |= B194_ConfingLockStateResultData;
          DataOut_RoutineRequestResOutSignal[0] |= B194_GETHSMInfoResultData.secureBootState<<4u;
          DataOut_RoutineRequestResOutSignal[1] |= B194_GETHSMInfoResultData.fwTamperDetectionState;
          DataOut_RoutineRequestResOutSignal[1] |= B194_GETHSMInfoResultData.secureDebugState<<4u;

          *currentDataLength = 2u;
          LddRetVal = E_OK;
          *ErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          LddRetVal = RTE_E_RoutineServices_RID_B194h_HSMConfigLockSecureDebug_E_NOT_OK;
          *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        }
      break;

    case DCM_CANCEL:

      LddRetVal = RTE_E_RoutineServices_RID_B194h_HSMConfigLockSecureDebug_E_NOT_OK;
      *ErrorCode = DCM_E_GENERALREJECT;

      break;

    default:
      /* MISRA-C */
      break;
  }

  return LddRetVal;
}

FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) RID_B199h_HSMSecureBootEnable_Start(
    IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
    OUT P2VAR(StartDataOutType_RID_B199h_HSMSecureBootEnable_B199h_StartRoutineOutSignal_ReturnType, AUTOMATIC, RTE_APPL_DATA) DataOut_B199h_StartRoutineOutSignal_ReturnType,
    OUT P2VAR(StartDataOutType_RID_B199h_HSMSecureBootEnable_B199h_StartRoutineOutSignal_State, AUTOMATIC, RTE_APPL_DATA) DataOut_B199h_StartRoutineOutSignal_State,
    OUT P2VAR(StartDataOutType_RID_B199h_HSMSecureBootEnable_B199h_StartRoutineOutSignal_ErrorCode, AUTOMATIC, RTE_APPL_DATA) DataOut_B199h_StartRoutineOutSignal_ErrorCode,
    INOUT P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) currentDataLength,
    OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;
  uint16 HSMErrCode = HSM_ERR_NOERROR;
  static uint8 cnt_pending = 0u;

  Std_ReturnType Diag_SecureBootResult = E_NOT_OK;
  Std_ReturnType Diag_SecureBootEnableResult = E_NOT_OK;

  HSM_SB_CONFIG_t B199_SecureBootCfg;
  HSM_SECUREBOOT_STATE_t B199_SecureBootState;

  //Wdg_66_IA_SetMode(WDGIF_OFF_MODE); /* watchdog off */

  switch(OpStatus)
  {
    case DCM_INITIAL:

      Diag_SecureBootResult = HSM_SecureBootResult(&B199_SecureBootState);

      if((Diag_SecureBootResult == E_OK) &&
          (B199_SecureBootState == HSM_SECUREBOOT_NOT_PERFORMED))
      {
        LddRetVal = RTE_E_RoutineServices_RID_B199h_HSMSecureBootEnable_DCM_E_PENDING;
      }
      else
      {
        HSMErrCode = HSM_GetLastErrorCode();

        *DataOut_B199h_StartRoutineOutSignal_ReturnType = Diag_SecureBootResult;
        *DataOut_B199h_StartRoutineOutSignal_State = B199_SecureBootState;
        *DataOut_B199h_StartRoutineOutSignal_ErrorCode = HSMErrCode;

        *currentDataLength = 4u;
        LddRetVal = E_OK;
        *ErrorCode = DCM_E_POSITIVERESPONSE;
      }

      break;

    case DCM_PENDING:

      if(cnt_pending == 4u)
      {
        cnt_pending = 0u;

        B199_SecureBootCfg.bootStartAddr = 0x10028000;  /*!< Bootloader Start Address */
        B199_SecureBootCfg.bootSize = 0x1FFFFu;         /*!< Bootloader Size */
        B199_SecureBootCfg.cmacKeyNum = 101u;           /*!< Number of symmetric keys that generate the internal MAC (Use among Tier PSK #101~#105) */
        B199_SecureBootCfg.signKeyNum = 1u;             /*!< Public key number for signature verification (When using aSIMS, enter 1) */
        B199_SecureBootCfg.signStartAddr = 0x10048A00;  /*!< Signature start address */

        Diag_SecureBootEnableResult = HSM_FactorySecureBootEnable(&B199_SecureBootCfg);

        if(Diag_SecureBootEnableResult == E_OK)
        {
          Diag_SecureBootResult = HSM_SecureBootResult(&B199_SecureBootState);

          *DataOut_B199h_StartRoutineOutSignal_ReturnType = Diag_SecureBootEnableResult;
          *DataOut_B199h_StartRoutineOutSignal_State = B199_SecureBootState;
          *DataOut_B199h_StartRoutineOutSignal_ErrorCode = HSMErrCode;

          *currentDataLength = 4u;
          LddRetVal = E_OK;
          *ErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          HSMErrCode = HSM_GetLastErrorCode();
          Diag_SecureBootResult = HSM_SecureBootResult(&B199_SecureBootState);

          *DataOut_B199h_StartRoutineOutSignal_ReturnType = Diag_SecureBootEnableResult;
          *DataOut_B199h_StartRoutineOutSignal_State = B199_SecureBootState;
          *DataOut_B199h_StartRoutineOutSignal_ErrorCode = HSMErrCode;

          *currentDataLength = 4u;
          LddRetVal = E_OK;
          *ErrorCode = DCM_E_POSITIVERESPONSE;
        }
      }
      else
      {
        cnt_pending++;
        LddRetVal = RTE_E_RoutineServices_RID_B199h_HSMSecureBootEnable_DCM_E_PENDING;
      }

      break;

    case DCM_CANCEL:

      LddRetVal = RTE_E_RoutineServices_RID_B199h_HSMSecureBootEnable_E_NOT_OK;
      *ErrorCode = DCM_E_GENERALREJECT;

      break;

    default:
          /* MISRA-C */
      break;
  }

  //Wdg_66_IA_SetMode(WDGIF_FAST_MODE); /* watchdog on */

  return LddRetVal;
}

FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) RID_B19Ah_HSMFTDDisable_Start(
    IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
    OUT P2VAR(StartDataOutType_RID_B19Ah_HSMFTDDisable_B19Ah_StartRoutineOutSignal_ReturnType, AUTOMATIC, RTE_APPL_DATA) DataOut_B19Ah_StartRoutineOutSignal_ReturnType,
    OUT P2VAR(StartDataOutType_RID_B19Ah_HSMFTDDisable_B19Ah_StartRoutineOutSignal_State, AUTOMATIC, RTE_APPL_DATA) DataOut_B19Ah_StartRoutineOutSignal_State,
    OUT P2VAR(StartDataOutType_RID_B19Ah_HSMFTDDisable_B19Ah_StartRoutineOutSignal_ErrorCode, AUTOMATIC, RTE_APPL_DATA) DataOut_B19Ah_StartRoutineOutSignal_ErrorCode,
    INOUT P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) currentDataLength,
    OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;
  uint16 HSMErrCode = HSM_ERR_NOERROR;
  static uint8 cnt_pending = 0u;

  Std_ReturnType Diag_FDTResult = E_NOT_OK;
  Std_ReturnType Diag_FDTDisableResult = E_NOT_OK;

  HSM_FTD_STATE_t B19A_FTDState;

  //Wdg_66_IA_SetMode(WDGIF_OFF_MODE); /* watchdog off */

  switch(OpStatus)
  {
    case DCM_INITIAL:

      Diag_FDTResult = HSM_FwTamperDetectionStatus(&B19A_FTDState);

      if((Diag_FDTResult == E_OK) &&
          (B19A_FTDState.status == HSM_FTD_NOT_PERFORMED))
      {
        LddRetVal = RTE_E_RoutineServices_RID_B19Ah_HSMFTDDisable_DCM_E_PENDING;
      }
      else
      {
        HSMErrCode = HSM_GetLastErrorCode();

        *DataOut_B19Ah_StartRoutineOutSignal_ReturnType = Diag_FDTResult;
        *DataOut_B19Ah_StartRoutineOutSignal_State = B19A_FTDState.status;
        *DataOut_B19Ah_StartRoutineOutSignal_ErrorCode = HSMErrCode;

        *currentDataLength = 4u;
        LddRetVal = E_OK;
        *ErrorCode = DCM_E_POSITIVERESPONSE;
      }
      break;

    case DCM_PENDING:

      if(cnt_pending == 4u)
      {
        cnt_pending = 0u;

        Diag_FDTDisableResult = HSM_FactoryFwTamperDetectionDisable();

        if(Diag_FDTDisableResult == E_OK)
        {
          Diag_FDTResult = HSM_FwTamperDetectionStatus(&B19A_FTDState);

          *DataOut_B19Ah_StartRoutineOutSignal_ReturnType = Diag_FDTDisableResult;
          *DataOut_B19Ah_StartRoutineOutSignal_State = B19A_FTDState.status;
          *DataOut_B19Ah_StartRoutineOutSignal_ErrorCode = HSMErrCode;

          *currentDataLength = 4u;
          LddRetVal = E_OK;
          *ErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          HSMErrCode = HSM_GetLastErrorCode();
          Diag_FDTResult = HSM_FwTamperDetectionStatus(&B19A_FTDState);

          *DataOut_B19Ah_StartRoutineOutSignal_ReturnType = Diag_FDTDisableResult;
          *DataOut_B19Ah_StartRoutineOutSignal_State = B19A_FTDState.status;
          *DataOut_B19Ah_StartRoutineOutSignal_ErrorCode = HSMErrCode;

          *currentDataLength = 4u;
          LddRetVal = E_OK;
          *ErrorCode = DCM_E_POSITIVERESPONSE;
        }
      }
      else
      {
        cnt_pending++;
        LddRetVal = RTE_E_RoutineServices_RID_B19Ah_HSMFTDDisable_DCM_E_PENDING;
      }

      break;

    case DCM_CANCEL:

      LddRetVal = RTE_E_RoutineServices_RID_B19Ah_HSMFTDDisable_E_NOT_OK;
      *ErrorCode = DCM_E_GENERALREJECT;

      break;

    default:
          /* MISRA-C */
      break;
  }

  //Wdg_66_IA_SetMode(WDGIF_FAST_MODE); /* watchdog on */

  return LddRetVal;
}

FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) RID_B19Bh_HSMSecureDebugEnable_Start(
    IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
    OUT P2VAR(StartDataOutType_RID_B19Bh_HSMSecureDebugEnable_B19Bh_StartRoutineOutSignal_ReturnType, AUTOMATIC, RTE_APPL_DATA) DataOut_B19Bh_StartRoutineOutSignal_ReturnType,
    OUT P2VAR(StartDataOutType_RID_B19Bh_HSMSecureDebugEnable_B19Bh_StartRoutineOutSignal_State, AUTOMATIC, RTE_APPL_DATA) DataOut_B19Bh_StartRoutineOutSignal_State,
    OUT P2VAR(StartDataOutType_RID_B19Bh_HSMSecureDebugEnable_B19Bh_StartRoutineOutSignal_ErrorCode, AUTOMATIC, RTE_APPL_DATA) DataOut_B19Bh_StartRoutineOutSignal_ErrorCode,
    INOUT P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) currentDataLength,
    OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;
  uint16 HSMErrCode = HSM_ERR_NOERROR;

  Std_ReturnType Diag_SecureDebugEnableResult = E_OK;

  switch(OpStatus)
  {
    case DCM_INITIAL:

      *DataOut_B19Bh_StartRoutineOutSignal_ReturnType = Diag_SecureDebugEnableResult;
      *DataOut_B19Bh_StartRoutineOutSignal_State = 0x01u;
      *DataOut_B19Bh_StartRoutineOutSignal_ErrorCode = HSMErrCode;

      *currentDataLength = 4u;
      LddRetVal = E_OK;
      *ErrorCode = DCM_E_POSITIVERESPONSE;

      break;

    case DCM_PENDING:

      break;

    case DCM_CANCEL:

      LddRetVal = RTE_E_RoutineServices_RID_B19Bh_HSMSecureDebugEnable_E_NOT_OK;
      *ErrorCode = DCM_E_GENERALREJECT;

      break;

    default:
          /* MISRA-C */
      break;
  }

  return LddRetVal;
}

FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) RID_B19Ch_HSMConfigurationLockEnable_Start(
    IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
    OUT P2VAR(StartDataOutType_RID_B19Ch_HSMConfigurationLockEnable_B19Ch_StartRoutineOutSignal_ReturnType, AUTOMATIC, RTE_APPL_DATA) DataOut_B19Ch_StartRoutineOutSignal_ReturnType,
    OUT P2VAR(StartDataOutType_RID_B19Ch_HSMConfigurationLockEnable_B19Ch_StartRoutineOutSignal_State, AUTOMATIC, RTE_APPL_DATA) DataOut_B19Ch_StartRoutineOutSignal_State,
    OUT P2VAR(StartDataOutType_RID_B19Ch_HSMConfigurationLockEnable_B19Ch_StartRoutineOutSignal_ErrorCode, AUTOMATIC, RTE_APPL_DATA) DataOut_B19Ch_StartRoutineOutSignal_ErrorCode,
    INOUT P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) currentDataLength,
    OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;
  uint16 HSMErrCode = HSM_ERR_NOERROR;

  Std_ReturnType Diag_ConfigLockResult = E_NOT_OK;
  Std_ReturnType Diag_ConfigurationLockEnableResult = E_NOT_OK;

  HSM_CONFIG_LOCK_STATE_t B19Ch_ConfigLockState = HSM_CONFIG_LOCK_DISABLE;

  //Wdg_66_IA_SetMode(WDGIF_OFF_MODE); /* watchdog off */

  switch(OpStatus)
  {
    case DCM_INITIAL:

      Diag_ConfigLockResult = HSM_GetConfigurationLockState(&B19Ch_ConfigLockState);

      if((Diag_ConfigLockResult == E_OK) &&
          (B19Ch_ConfigLockState == HSM_CONFIG_LOCK_DISABLE))
      {
        LddRetVal = RTE_E_RoutineServices_RID_B19Ch_HSMConfigurationLockEnable_DCM_E_PENDING;
      }
      else
      {
        HSMErrCode = HSM_GetLastErrorCode();

        *DataOut_B19Ch_StartRoutineOutSignal_ReturnType = Diag_ConfigLockResult;
        *DataOut_B19Ch_StartRoutineOutSignal_State = B19Ch_ConfigLockState;
        *DataOut_B19Ch_StartRoutineOutSignal_ErrorCode = HSMErrCode;

        *currentDataLength = 4u;
        LddRetVal = E_OK;
        *ErrorCode = DCM_E_POSITIVERESPONSE;
      }

      break;

    case DCM_PENDING:

      Diag_ConfigurationLockEnableResult = HSM_FactoryHsmConfigurationLock();

      if(Diag_ConfigurationLockEnableResult == E_OK)
      {
        Diag_ConfigLockResult = HSM_GetConfigurationLockState(&B19Ch_ConfigLockState);

        *DataOut_B19Ch_StartRoutineOutSignal_ReturnType = Diag_ConfigurationLockEnableResult;
        *DataOut_B19Ch_StartRoutineOutSignal_State = B19Ch_ConfigLockState;
        *DataOut_B19Ch_StartRoutineOutSignal_ErrorCode = HSMErrCode;

        *currentDataLength = 4u;
        LddRetVal = E_OK;
        *ErrorCode = DCM_E_POSITIVERESPONSE;
      }
      else
      {
        HSMErrCode = HSM_GetLastErrorCode();
        Diag_ConfigLockResult = HSM_GetConfigurationLockState(&B19Ch_ConfigLockState);

        *DataOut_B19Ch_StartRoutineOutSignal_ReturnType = Diag_ConfigurationLockEnableResult;
        *DataOut_B19Ch_StartRoutineOutSignal_State = B19Ch_ConfigLockState;
        *DataOut_B19Ch_StartRoutineOutSignal_ErrorCode = HSMErrCode;

        *currentDataLength = 4u;
        LddRetVal = E_OK;
        *ErrorCode = DCM_E_POSITIVERESPONSE;
      }

      break;

    case DCM_CANCEL:

      LddRetVal = RTE_E_RoutineServices_RID_B19Ch_HSMConfigurationLockEnable_E_NOT_OK;
      *ErrorCode = DCM_E_GENERALREJECT;

      break;

    default:
          /* MISRA-C */
      break;
  }

  //Wdg_66_IA_SetMode(WDGIF_FAST_MODE); /* watchdog on */

  return LddRetVal;
}

FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) RID_B19Dh_HSMChallengeRequest_Start(
    IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
    OUT P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DataOut_B19Dh_StartRoutineOutSignal_Data,
    INOUT P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) currentDataLength,
    OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;
  uint16 HSMErrCode = HSM_ERR_NOERROR;

  uint8 OutData[16];
  uint8 i;

  //Wdg_66_IA_SetMode(WDGIF_OFF_MODE); /* watchdog off */

  switch(OpStatus)
  {
    case DCM_INITIAL:

      LddRetVal = HSM_ChallengeRequest((UINT8*)OutData);

      if(LddRetVal == E_OK)
      {
        for(i=0; i<16; i++)
        {
          DataOut_B19Dh_StartRoutineOutSignal_Data[i] = OutData[i];
        }

        *currentDataLength = 16u;
        *ErrorCode = DCM_E_POSITIVERESPONSE;
      }
      else
      {
        HSMErrCode = HSM_GetLastErrorCode();
        LddRetVal = RTE_E_RoutineServices_RID_B19Dh_HSMChallengeRequest_E_NOT_OK;
        *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      }

      break;

    case DCM_PENDING:

      break;

    case DCM_CANCEL:

      LddRetVal = RTE_E_RoutineServices_RID_B19Dh_HSMChallengeRequest_E_NOT_OK;
      *ErrorCode = DCM_E_GENERALREJECT;

      break;

    default:
          /* MISRA-C */
      break;
  }

  //WDG_66_IA_SetMode(WDGIF_FAST_MODE); /* watchdog on */

  return LddRetVal;
}

FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) RID_B19Eh_HSMResponseData_Start(
    IN P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) DataIn_B19Eh_StartRoutineInSignal_Data,
    IN VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
    INOUT P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) currentDataLength,
    OUT P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;
  uint16 HSMErrCode = HSM_ERR_NOERROR;

  uint8 RespData[16];
  uint8 i;

  //WDG_66_IA_SetMode(WDGIF_OFF_MODE); /* watchdog off */

  switch(OpStatus)
  {
    case DCM_INITIAL:

      for(i=0; i<16; i++)
      {
        RespData[i] = DataIn_B19Eh_StartRoutineInSignal_Data[i];
      }

      LddRetVal = HSM_ResponseForward((UINT8 *)RespData);

      if(LddRetVal == E_OK)
      {
        Port_SetPinDirection(PORT_PIN_P023_4, PORT_PIN_OUT);
        Port_SetPinMode(PORT_PIN_P023_4, PORT_PIN_MODE_P023_4_CPUSS_SWJ_SWO_TDO);

        Port_SetPinDirection(PORT_PIN_P023_5, PORT_PIN_IN);
        Port_SetPinMode(PORT_PIN_P023_5, PORT_PIN_MODE_P023_5_CPUSS_SWJ_SWCLK_TCLK);

        Port_SetPinDirection(PORT_PIN_P023_6, PORT_PIN_IN);
        Port_SetPinMode(PORT_PIN_P023_6, PORT_PIN_MODE_P023_6_CPUSS_SWJ_SWDIO_TMS);

        Port_SetPinDirection(PORT_PIN_P023_7, PORT_PIN_IN);
        Port_SetPinMode(PORT_PIN_P023_7, PORT_PIN_MODE_P023_7_CPUSS_SWJ_SWDOE_TDI);

        *ErrorCode = DCM_E_POSITIVERESPONSE;
      }
      else
      {
        HSMErrCode = HSM_GetLastErrorCode();
        LddRetVal = RTE_E_RoutineServices_RID_B19Eh_HSMResponseData_E_NOT_OK;
        *ErrorCode = DCM_E_INVALIDKEY;
      }

      break;

    case DCM_PENDING:

      break;

    case DCM_CANCEL:

      LddRetVal = RTE_E_RoutineServices_RID_B19Eh_HSMResponseData_E_NOT_OK;
      *ErrorCode = DCM_E_GENERALREJECT;

      break;

    default:
          /* MISRA-C */
      break;
  }

  //WDG_66_IA_SetMode(WDGIF_FAST_MODE); /* watchdog on */

  return LddRetVal;
}

/* End Configuration Lock */

#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
