#include "TC_Def.h"
#include "Demo_Util.h"
#include "Hsm_HostAPI.h"
#include "SecurityApp_SecureBoot.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*  	                        Util - Etc Secure App                         */
/******************************************************************************/

UINT8 s_uid[MCU_UNIQUE_ID_LEN];
HSM_SECURITY_INFO_t s_securityInfo;
HSM_VERSION_CTX_t s_hsmVersionInfo;
HSM_CONFIG_LOCK_STATE_t g_hsmConfLckState;
extern HSM_ERROR_CODE g_ErrorCode;

Std_ReturnType HostTest_HSM_GetMcuUid(void)
{
	Std_ReturnType result;
	UINT8 uid[MCU_UNIQUE_ID_LEN];

	result = HSM_GetMcuUid(uid);
	if(result == E_OK)
	{
		Hae_Memcpy(s_uid, uid, MCU_UNIQUE_ID_LEN);
	}
	return result;
}

Std_ReturnType HostTest_HSM_FactoryHsmConfigurationLock(void)
{
    Std_ReturnType result;
	HSM_CONFIG_LOCK_STATE_t confLckState;
	HSM_SECUREBOOT_STATE_t sbState;
	result = HSM_GetConfigurationLockState(&confLckState);
	if((result == E_OK) && (confLckState == HSM_CONFIG_LOCK_DISABLE))
	{
		result = HSM_SecureBootResult(&sbState);
		if((result == E_OK) && (sbState != HSM_SECUREBOOT_NOT_PERFORMED))
		{
			/** CAUTION : MUST SET SECURE BOOT ENABLE or DISABLE BEFORE SETTING HSM CONFIGURATION LOCK
			 *  Once the configuration lock setting is performed, it cannot be restored to unlock state..
			 *  When calling HSM_Factory* after this setting, E_NOT_OK is returned.
			 **/
    		result = HSM_FactoryHsmConfigurationLock();
		}
	}
    return result;
}

Std_ReturnType HostTest_HSM_GetConfigurationLockState()
{
    Std_ReturnType result;
	HSM_CONFIG_LOCK_STATE_t confLckState;
	result = HSM_GetConfigurationLockState(&confLckState);
	g_hsmConfLckState = confLckState;
    return result;
}

Std_ReturnType HostTest_HSM_GetAllSecurityInfo(void)
{
	Std_ReturnType result;
	HSM_SECURITY_INFO_t securityInfo;

	Hae_Memset(&securityInfo, 0u, sizeof(HSM_SECURITY_INFO_t));
	result = HSM_GetAllSecurityInfo(&securityInfo);
	if(result == E_OK)
	{
		s_securityInfo.secureBootState = securityInfo.secureBootState;
		s_securityInfo.fwTamperDetectionState = securityInfo.fwTamperDetectionState;
		s_securityInfo.secureDebugState = securityInfo.secureDebugState;
	}
	return result;
}

Std_ReturnType HostTest_HSM_GetVersionInfo(void)
{
	Std_ReturnType result;
	HSM_VERSION_CTX_t version;

	result = HSM_GetVersionInfo(&version);
	if(result == E_OK)
	{
		Hae_Memcpy(&s_hsmVersionInfo, &version, sizeof(HSM_VERSION_CTX_t));
	}
	return result;
}

Std_ReturnType HostTest_HSM_TempStop(void)
{
	Std_ReturnType result;
	if(HSM_CheckHsmTempStopState() == FALSE)
	{
		result = HSM_TempStop();
	}
	else
	{
		result = E_NOT_OK;
	}
	return result;
}

Std_ReturnType HostTest_HSM_Restart(void)
{
	Std_ReturnType result;
	result = HSM_Restart();
	return result;
}
