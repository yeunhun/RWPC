#ifndef DEMO_SECURE_DEBUG_H_
#define DEMO_SECURE_DEBUG_H_

#include "Hsm_Types.h"
#include "Demo_AppTestDefine.h"

Std_ReturnType HostTest_HSM_FactoryDebuggerProtectionEnable(void);
Std_ReturnType HostTest_HSM_FactoryDebuggerProtectionDisable(void);
Std_ReturnType HostTest_HSM_DebuggerProtectionTempStop(HSM_Secure_Debug_TestVector_t *hsmSecureDebugTv);
Std_ReturnType HostTest_HSM_GetDebugStateInfo(UINT32 *rcvData);

#if (defined TRAVEO2_SERIES)	
Std_ReturnType HostTest_HSM_ChallengeRequset(void);
Std_ReturnType HostTest_HSM_ResponseForward(void);
#endif

#endif /* DEMO_SECURE_DEBUG_H_ */
