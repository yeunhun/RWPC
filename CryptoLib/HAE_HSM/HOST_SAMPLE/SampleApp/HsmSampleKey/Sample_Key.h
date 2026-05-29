#ifndef SAMPLE_Key_H_
#define SAMPLE_Key_H_

#include "Hsm_KeyTypes.h"
#include "CryptoService_Def.h"

#if defined(__TASKING__)
#pragma section farrom "HSM_TEST_VECTOR"
#endif
#if defined(__GHS__)
#pragma ghs startdata
#pragma ghs section rodata="HSM_TEST_VECTOR"
#endif

extern const UINT8 g_HsmAesTestKey401[HSM_AES128_KEY_LEN]; /* NO. 401 Aes128 Key */ 
extern const UINT8 g_HsmAesTestKey402[HSM_AES128_KEY_LEN]; /* NO. 402 Aes128 Key */ 
extern const UINT8 g_HsmAesTestKey403[HSM_AES128_KEY_LEN]; /* NO. 403 Aes128 Key */ 
extern const UINT8 g_HsmAesTestKey404[HSM_AES128_KEY_LEN]; /* NO. 404 Aes128 Key */ 
extern const UINT8 g_HsmAesTestKey405[HSM_AES128_KEY_LEN]; /* NO. 405 Aes128 Key */ 

extern const Rsa_Keypair_t g_HsmRsaTestKey401; /* NO.401 Rsa2048 Keypair */
extern const Rsa_Keypair_t g_HsmRsaTestKey402; /* NO.402 Rsa2048 Keypair */
extern const Rsa_Keypair_t g_HsmRsaTestKey403; /* NO.403 Rsa2048 Keypair */

extern const Ecc_Keypair_t g_HsmEccTestKey401; /* NO.401 Ecc p256 Keypair */  
extern const Ecc_Keypair_t g_HsmEccTestKey301;

#if defined(__TASKING__)
#pragma section farrom restore
#endif
#if defined(__GHS__)
#pragma ghs section rodata=default
#pragma ghs enddata
#endif

#endif /* SAMPLE_Key_H_ */
