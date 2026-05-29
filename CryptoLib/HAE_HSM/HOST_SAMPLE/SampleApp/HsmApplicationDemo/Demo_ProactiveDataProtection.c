#include "TC_Def.h"
#include "Demo_ProactiveDataProtection.h"

#include "Hsm_HostAPI.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                      Proactive Data Protection                             */
/******************************************************************************/
extern HSM_ERROR_CODE g_ErrorCode;

Std_ReturnType HostTest_HSM_PDPConfig(HSM_PROACTIVE_DATA_PROTECTION_TestVector_t hsmPdpTv)
{
	Std_ReturnType result;

	result = HSM_PDPConfig(&hsmPdpTv.pdpConfig);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_PDPDataVerify(void)
{
	Std_ReturnType result;

	result = HSM_PDPDataVerify();
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_PDPDataUpdate(void)
{
	Std_ReturnType result;

	result = HSM_PDPDataUpdate();
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_PDPDisable(void)
{
	Std_ReturnType result;

	result = HSM_PDPDisable();
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}
