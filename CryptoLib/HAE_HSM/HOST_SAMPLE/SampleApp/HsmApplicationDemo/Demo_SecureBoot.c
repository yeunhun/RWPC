#include "TC_Def.h"
#include "Demo_SecureBoot.h"

#include "Hsm_HostAPI.h"
#include "HsmDrv_API.h"

/******************************************************************************/
/*                            Secure Boot                                     */
/******************************************************************************/

HSM_SECUREBOOT_STATE_t s_secureBootState;
extern HSM_ERROR_CODE g_ErrorCode;

/******************************************************************************/
/* 			      	Secure App-Secure Boot           				          */
/******************************************************************************/
/*
*   Secure Boot Input Parameter Description(HSM_SB_CONFIG_t).
*
*	UINT32 bootStartAddr : Bootloader Start Address.
*	UINT32 bootSize      : Bootloader Byte Size.
*	UINT16 cmacKeyNum    : Select #101~#105 Key index of the TierKey area.
*	UINT16 signKeyNum    : Select #1 key index(aSIMS). Select #101-#102 or #201-#202 (HK-FST).
*	UINT32 signStartAddr : Address of the signature created by the signature verification tool(aSIMS, HK-FST).
*
*   * signKeyNum, signStartAddr field only for use Secure Boot Mac Update API(HSM_SecureBootMacUpdate). No required for HSM_SecureBootEnable API. 
*
*	* Caution : Unused area in the bootloader area(start from bootStartAddr to bootSize) must be filled with 0 or other values. 
*               In the flash erase state, bus Fault may occur while reading Falsh of bootloader for MAC calculation.
**/

Std_ReturnType HostTest_HSM_FactorySecureBootEnable(HSM_SECURE_BOOT_TestVector_t hsmSecureBootTv)
{
	Std_ReturnType result;
	HSM_SECUREBOOT_STATE_t secureBootState;

	result = HSM_FactorySecureBootEnable(&(hsmSecureBootTv.sbConfig));

	if (result == E_OK)
	{
		result = HSM_SecureBootResult(&secureBootState);
		if (secureBootState == HSM_SECUREBOOT_ENABLE)
		{
			result = E_OK;
		}
		s_secureBootState = secureBootState;
	}
	else
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_FactorySecureBootDisable(void)
{
	Std_ReturnType result;
	HSM_SECUREBOOT_STATE_t secureBootState;

	result = HSM_FactorySecureBootDisable();

	if (result == E_OK)
	{
		result = HSM_SecureBootResult(&secureBootState);
		if (secureBootState == HSM_SECUREBOOT_DISABLE)
		{
			result = E_OK;
		}
		s_secureBootState = secureBootState;
	}
	else
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_SecureBootMacUpdate(HSM_SECURE_BOOT_TestVector_t hsmSecureBootTv)
{
	Std_ReturnType result;
	HSM_SECUREBOOT_STATE_t secureBootState;

	result = HSM_SecureBootMacUpdate(&(hsmSecureBootTv.sbConfig));

	if (result == E_OK)
	{
		result = HSM_SecureBootResult(&secureBootState);
		if (secureBootState == HSM_SECUREBOOT_SUCCESS)
		{
			result = E_OK;
		}
		s_secureBootState = secureBootState;
	}
	else
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_SecureBootResult(UINT32 *state)
{
	Std_ReturnType result;
	HSM_SECUREBOOT_STATE_t secureBootState;

	result = HSM_SecureBootResult(&secureBootState);
	if(result != E_OK)
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	*state = (UINT32)secureBootState;
	s_secureBootState = secureBootState;
	return result;
}

#if (defined TRAVEO2_SERIES)	
Std_ReturnType HostTest_HSM_FactorySecureBootDualBankEnable(HSM_SECURE_BOOT_DUALBANK_TestVector_t hsmSecureBootDualBankTv)
{
	Std_ReturnType result;
	HSM_SECUREBOOT_STATE_t secureBootState;

	result = HSM_FactorySecureBootEnableDualBank(&(hsmSecureBootDualBankTv.sbConfig));

	if (result == E_OK)
	{
		result = HSM_SecureBootResult(&secureBootState);
		if (secureBootState == HSM_SECUREBOOT_ENABLE)
		{
			result = E_OK;
		}
		s_secureBootState = secureBootState;
	}
	else
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_HSM_SecureBootDualBankMacUpdate(HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t g_HsmSecureBootMACDualBankTv)
{
	Std_ReturnType result;
	HSM_SECUREBOOT_STATE_t secureBootState;
	result = HSM_SecureBootMacUpdateDualBank(&(g_HsmSecureBootMACDualBankTv.sbConfig));

	if (result == E_OK)
	{
		result = HSM_SecureBootResult(&secureBootState);
		if (secureBootState == HSM_SECUREBOOT_SUCCESS)
		{
			result = E_OK;
		}
		s_secureBootState = secureBootState;
	}
	else
	{
		result = E_NOT_OK;
		g_ErrorCode = (HSM_ERROR_CODE)HSM_GetLastErrorCode();
	}
	return result;
}

Std_ReturnType HostTest_DualBankEnable(void)		
{
	Std_ReturnType result = E_OK;
	volatile UINT32			*FLASHC = (volatile UINT32*) 0x40240000UL;
	
	//FLASHC->unFLASH_CTL.stcField.u1MAIN_BANK_MODE = 0x1u;
	*FLASHC |= (1 << 12);
	
	return result;
}

Std_ReturnType HostTest_DualBankDisable(void)		
{
	Std_ReturnType result = E_OK;
	
	volatile UINT32			*FLASHC = (volatile UINT32*) 0x40240000UL;
	
	//FLASHC->unFLASH_CTL.stcField.u1MAIN_BANK_MODE = 0x0u;
	*FLASHC &= ~(1 << 12);
		
	return result;
}

#endif
