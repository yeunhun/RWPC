
#include "TC_Def.h"
#include "Demo_KeyManagement.h"

#include "Hsm_KeyTypes.h"
#include "Hsm_HostAPI.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                Key Management Test - Set User Defined Key (Key Num#20x)    */
/******************************************************************************/

extern HSM_ERROR_CODE g_ErrorCode;

Std_ReturnType HostTest_HSM_KeyManagementSetUserDefinedAesKey(HSM_KEY_MANAGEMENT_AES_TestVector_t hsmKmAesTv)
{
	Std_ReturnType result;
#if defined (__LITTLE_ENDIAN__)
	UINT8 aesKeyBigEndianess[16];
	if(hsmKmAesTv.aesKeyConfig != NULL)
	{
		Hae_Memcpy(aesKeyBigEndianess, hsmKmAesTv.aesKeyConfig, 16);
		Hae_swap_byteOrder((void *)aesKeyBigEndianess, 16u);
		hsmKmAesTv.aesKeyConfig = aesKeyBigEndianess;
	}
#endif

	result = HSM_KeyManagementSetAesKey(hsmKmAesTv.keyIndex, (UINT8 *)hsmKmAesTv.aesKeyConfig, hsmKmAesTv.keyLock);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_KeyManagementSetUserDefinedRsaKey(HSM_KEY_MANAGEMENT_RSA_TestVector_t hsmKmRsaTv)
{
	Std_ReturnType result;

	result = HSM_KeyManagementSetRsaKey(hsmKmRsaTv.keyIndex, hsmKmRsaTv.rsaKeyConfig, hsmKmRsaTv.keyLock);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_KeyManagementSetUserDefinedEccKey(HSM_KEY_MANAGEMENT_ECC_TestVector_t hsmKmEccTv)
{
	Std_ReturnType result;

	result = HSM_KeyManagementSetEccKey(hsmKmEccTv.keyIndex, hsmKmEccTv.eccKeyConfig, hsmKmEccTv.keyLock);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_KeyManagementSetHostTempAesKey(HSM_KEY_MANAGEMENT_AES_TestVector_t hsmKmAesTv)
{
	Std_ReturnType result;
#if defined (__LITTLE_ENDIAN__)
	if(hsmKmAesTv.aesKeyConfig != NULL)
	{
		UINT8 aesKeyBigEndianess[16];
		Hae_Memcpy(aesKeyBigEndianess, hsmKmAesTv.aesKeyConfig, 16);
		Hae_swap_byteOrder((void *)aesKeyBigEndianess, 16u);
		hsmKmAesTv.aesKeyConfig = aesKeyBigEndianess;
	}
#endif


	result = HSM_KeyManagementSetAesKey(301u, (UINT8 *)hsmKmAesTv.aesKeyConfig, 0u);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_KeyManagementSetHostTempRsaKey(HSM_KEY_MANAGEMENT_RSA_TestVector_t hsmKmRsaTv)
{
	Std_ReturnType result;

	result = HSM_KeyManagementSetRsaKey(301u, hsmKmRsaTv.rsaKeyConfig, 0u);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_KeyManagementSetHostTempEccKey(HSM_KEY_MANAGEMENT_ECC_TestVector_t hsmKmEccTv)
{
	Std_ReturnType result;

	result = HSM_KeyManagementSetEccKey(301u, hsmKmEccTv.eccKeyConfig, 0u);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_KeyManagementValidateKey(KEY_TYPE keyType, UINT16 keyIndex)
{
	Std_ReturnType result;

	result = HSM_KeyManagementValidateKey(keyType, keyIndex);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}	
	return result;
}
