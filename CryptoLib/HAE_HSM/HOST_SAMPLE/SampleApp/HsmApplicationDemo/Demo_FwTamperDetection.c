
#include "TC_Def.h"
#include "Demo_FwTamperDetection.h"

#include "Hsm_HostAPI.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                            Firmware Tamper Detection Test                  */
/******************************************************************************/
HSM_PASSWORD_VERIFY_STATE_t s_ftdPwVerifyState;
HSM_FTD_STATE_t s_ftdRunState;
HSM_FTD_LOG_t s_ftdLog;
extern HSM_ERROR_CODE g_ErrorCode;

Std_ReturnType HostTest_HSM_FactoryFwTamperDetectionEnable(HSM_FTD_CONFIG_TestVector_t hsmTpConfigTv)
{
	Std_ReturnType result;
	result = HSM_FactoryFwTamperDetectionEnable(&hsmTpConfigTv.ftdConfig, NULL);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_FactoryFwTamperDetectionDisable()
{
	Std_ReturnType result;
    HSM_FTD_STATE_t state;

	result = HSM_FactoryFwTamperDetectionDisable();
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}

	if (result == E_OK)
	{
		result = HSM_FwTamperDetectionStatus(&state);
		if (state.status == HSM_FTD_DISABLE)
		{
			result = E_OK;
		}
	}
	return result;
}

Std_ReturnType HostTest_HSM_FwTamperDetectionConfig(HSM_FTD_CONFIG_TestVector_t hsmTpConfigTv)
{
	Std_ReturnType result;

	result = HSM_FwTamperDetectionConfig(&hsmTpConfigTv.ftdConfig, NULL);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_FwTamperDetectionUpdtTarget(HSM_FTD_TARGET_testVector_t hsmTpUpdtTargetTv)
{
	Std_ReturnType result;

	result = HSM_FwTamperDetectionUpdtTarget(&hsmTpUpdtTargetTv.ftdUpdateInfo, NULL);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_FwTamperDetectionTempStop(HSM_FTD_TEMP_STOP_TestVector_t hsmFTDtempStopTv)
{
	Std_ReturnType result;
	HSM_PASSWORD_VERIFY_STATE_t hsmTempStopPwVerifyState;
	HSM_FTD_STATE_t ftdRunState;
	volatile UINT32 i = 0;
	UINT32 tryingNum = 0;

	do {
		result = HSM_FwTamperDetectionTempStop((UINT8 *)hsmFTDtempStopTv.stopPassword, hsmFTDtempStopTv.stopPasswordByteLen, &hsmTempStopPwVerifyState);
		
		while (i != 1000000)
		{
			i++;
		}
		i = 0;
		tryingNum++;
	} while ((result == HSM_E_BUSY) && (tryingNum < 10));
	
	if(result == E_OK)
	{
		result = HSM_FwTamperDetectionStatus(&ftdRunState);
		if(ftdRunState.status != HSM_FTD_ACTIVATED_TEMP_STOP)
		{
			result = E_NOT_OK;
		}
	}
	else
	{
		s_ftdPwVerifyState = hsmTempStopPwVerifyState;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_FwTamperDetectionRestart()
{
	Std_ReturnType result;

	result = HSM_FwTamperDetectionRestart();
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_FwTamperDetectionStatus()
{
	Std_ReturnType result;
	HSM_FTD_STATE_t ftdRunState;

	result = HSM_FwTamperDetectionStatus(&ftdRunState);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	if(ftdRunState.totalTargetNum > HSM_MAX_FTD_TARGET_NUM)
	{
		result = E_NOT_OK;
	}
	
	s_ftdRunState = ftdRunState;
	return result;
}

Std_ReturnType HostTest_HSM_FwTamperDetectionLog()
{
	Std_ReturnType result;
	HSM_FTD_LOG_t ftdLog;

	result = HSM_FwTamperDetectionLog(&ftdLog);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	if(ftdLog.totalTargetNum > HSM_MAX_FTD_TARGET_NUM)
	{
		result = E_NOT_OK;
	}
	
	s_ftdLog = ftdLog;
	return result;
}

UINT32 s_callbackCallCount;
UINT32 s_waitCallbackTime = 2000;

void CallbackFunction(void)
{
	s_callbackCallCount++;
}

Std_ReturnType HostTest_HSM_FwTamperDetectionCallback(HSM_FTD_CONFIG_TestVector_t hsmTpConfigTv)
{
	Std_ReturnType result;
	HSM_SetCallbackFuncWaitCount(s_waitCallbackTime);

	result = HSM_FwTamperDetectionConfig(&hsmTpConfigTv.ftdConfig, CallbackFunction);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}
