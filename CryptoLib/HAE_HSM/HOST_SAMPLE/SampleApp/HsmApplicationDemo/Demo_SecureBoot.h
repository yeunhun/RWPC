#ifndef DEMO_SECURE_BOOT_H_
#define DEMO_SECURE_BOOT_H_

#include "Hsm_Types.h"
#include "Demo_AppTestDefine.h"


Std_ReturnType HostTest_HSM_FactorySecureBootEnable(HSM_SECURE_BOOT_TestVector_t hsmSecureBootTv);
Std_ReturnType HostTest_HSM_FactorySecureBootDisable(void);
Std_ReturnType HostTest_HSM_SecureBootMacUpdate(HSM_SECURE_BOOT_TestVector_t hsmSecureBootTv);
Std_ReturnType HostTest_HSM_SecureBootResult(UINT32 *state);

#if (defined TRAVEO2_SERIES)	
Std_ReturnType HostTest_HSM_FactorySecureBootDualBankEnable(HSM_SECURE_BOOT_DUALBANK_TestVector_t hsmSecureBootTv);
Std_ReturnType HostTest_HSM_SecureBootDualBankMacUpdate(HSM_SECURE_BOOT_MAC_DUALBANK_TestVector_t hsmSecureBootDualBankTv);
Std_ReturnType HostTest_DualBankEnable(void);     
Std_ReturnType HostTest_DualBankDisable(void);
#endif

#endif /* DEMO_SECURE_BOOT_H_ */
