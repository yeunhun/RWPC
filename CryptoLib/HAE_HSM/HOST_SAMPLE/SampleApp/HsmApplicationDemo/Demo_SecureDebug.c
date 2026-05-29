#include "TC_Def.h"
#include "Demo_SecureDebug.h"
#include "Hsm_HostAPI.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                            Secure Debug                                    */
/******************************************************************************/
extern HSM_ERROR_CODE g_ErrorCode;
UINT32 s_jtagPass[8] = {0x00000001u, 0x00000002u, 0x00000003u, 0x00000004u, 0x00000005u, 0x00000006u, 0x00000007u, 0x00000008u};
HSM_SECUREDEBUG_STATE_t s_debugState;

Std_ReturnType HostTest_HSM_FactoryDebuggerProtectionEnable(void)
{
	Std_ReturnType result;

	result = HSM_FactoryDebuggerProtectionEnable((UINT8 *)s_jtagPass, 32u);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_FactoryDebuggerProtectionDisable(void)
{
	Std_ReturnType result;

	result = HSM_FactoryDebuggerProtectionDisable();
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_DebuggerProtectionTempStop(HSM_Secure_Debug_TestVector_t *hsmSecureDebugTv)
{
	Std_ReturnType result;
	HSM_SECUREDEBUG_STATE_t debugState;

	result = HSM_DebuggerProtectionTempStop((UINT8 *)hsmSecureDebugTv->password, hsmSecureDebugTv->pwByteLen, &debugState);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	if(result != E_OK)
	{
		s_debugState = debugState;
	}
	return result;
}

Std_ReturnType HostTest_HSM_GetDebugStateInfo(UINT32 *rcvData)
{
	Std_ReturnType result;
	HSM_SECURITY_INFO_t securityInfo;
	Hae_Memset(&securityInfo, 0u, sizeof(HSM_SECURITY_INFO_t));

	result = HSM_GetAllSecurityInfo(&securityInfo);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	s_debugState = securityInfo.secureDebugState;
	*rcvData = (UINT32)securityInfo.secureDebugState;
	return result;
}


#if (defined TRAVEO2_SERIES)	
UINT32 RespData[4] ={0, };
void HostCanSim_SetD5Data(UINT32 output[4]);

Std_ReturnType HostTest_HSM_ChallengeRequset(void)
{
	Std_ReturnType result = E_NOT_OK;
	UINT32 output[4];
	
	result = HSM_ChallengeRequest((UINT8*)output);

	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	else
	{
		HostCanSim_SetD5Data(output);
	}

	return result;
}

Std_ReturnType HostTest_HSM_ResponseForward(void)
{
	Std_ReturnType result;
	
	result = HSM_ResponseForward((UINT8 *)RespData);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}

	return result;
}


#endif
