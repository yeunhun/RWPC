#ifndef DEMO_PBKDF2_H_
#define DEMO_PBKDF2_H_

#include "Hsm_Types.h"
#include "Demo_CryptoTestDefine.h"

Std_ReturnType pbkdf2Test_Simple(Hmg_Pbkdf2_TestVector pbkdf2Tv);

Std_ReturnType HSM_Pbkdf2(const UINT16 keyNum, const UINT8* password, const UINT32 pwLen, const UINT8* salt, const UINT32 sLen, const UINT32 cnt, const UINT32 dkLen, UINT8 *dk);

#endif /* DEMO_PBKDF2_H_ */
