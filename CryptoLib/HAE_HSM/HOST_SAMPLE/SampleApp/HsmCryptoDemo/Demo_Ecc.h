#ifndef DEMO_ECC_H_
#define DEMO_ECC_H_

#include "Hsm_Types.h"
#include "Demo_CryptoTestDefine.h"

Std_ReturnType eccEcdsaSignTest_Simple(HSM_Ecc_Ecdsa_TestVector ecdsaSignTv);
Std_ReturnType eccEcdsaVerifyTest_Simple(HSM_Ecc_Ecdsa_TestVector ecdsaVerifyTv);
Std_ReturnType eccEcdhTest_Simple(HSM_Ecc_Ecdh_TestVector ecdhTv);

Std_ReturnType HSM_EcdsaSign(const UINT16 keyNum, const UINT8 *digest, const UINT8 *secret, ECC_ECDSA_SIGN_t *sign);
Std_ReturnType HSM_EcdsaSignVerify(const UINT16 keyNum, const UINT8 *digest, const ECC_ECDSA_SIGN_t *sign, UINT8 *verifyResult);
Std_ReturnType HSM_Ecdh(const UINT16 keyNum, const ECC_PUBLICKEY_t *pubkey, UINT8 *secretValue);
#endif /* DEMO_ECC_H_ */
