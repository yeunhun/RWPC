#ifndef DEMO_HASH_H_
#define DEMO_HASH_H_

#include "Hsm_Types.h"
#include "Demo_CryptoTestDefine.h"

Std_ReturnType sha160Test_Simple(HSM_Hash_TestVector sha160Tv);
Std_ReturnType sha256Test_Simple(HSM_Hash_TestVector sha256Tv);
Std_ReturnType hmacSha256Test_Simple(HSM_Hash_HMAC_TestVector hmacSha256Tv);

Std_ReturnType HSM_Sha160(const UINT8 *msg, const UINT32 mLen, UINT8 *digest);
Std_ReturnType HSM_Sha256(const UINT8 *msg, const UINT32 mLen, UINT8 *digest);
Std_ReturnType HSM_HmacSha256Gen(const UINT16 keyNum, const UINT8 *msg, const UINT32 mLen, UINT8 *digest);


#endif /* DEMO_HASH_H_ */
