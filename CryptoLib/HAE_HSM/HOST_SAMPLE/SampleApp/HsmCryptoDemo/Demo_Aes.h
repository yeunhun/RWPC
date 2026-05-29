#ifndef DEMO_AES_H_
#define DEMO_AES_H_

#include "Hsm_Types.h"
#include "Demo_CryptoTestDefine.h"

Std_ReturnType aesEncTest_Simple(HSM_AES_TestVector hsmAesTestVector);
Std_ReturnType aesDecTest_Simple(HSM_AES_TestVector hsmAesTestVector);
Std_ReturnType aesCmacTest_Simple(HSM_AES_CMAC_TestVector aesCmacTv);

Std_ReturnType HSM_AesEnc(const AES_MODE mode, const UINT16 keyIndex, const UINT8 *iv, const UINT32 dataLen, const UINT8 *plain, UINT8 *cipher);
Std_ReturnType HSM_AesDec(const AES_MODE mode, const UINT16 keyIndex, const UINT8 *iv, const UINT32 dataLen, const UINT8 *cipher, UINT8 *plain);
Std_ReturnType HSM_AesCmacGenerate(const UINT16 keyIndex, const UINT8 *msg, const UINT32 mLen, UINT8 *cmac);

#endif /* DEMO_AES_H_ */
