/*******************************************************************************
**                                                                            **
**  (C) 2017 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: HSM_Hae.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTRON Random algorithm                                       **
**                                                                            **
**  PURPOSE   : Header file for HAE HSM framework                             **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.2     13-Mar-2020   JaeHyun      Redmine #22362                        **
** 1.0.1     04-Dec-2019   Sinil        Redmine #20521                        **
** 1.0.0     07-Aug-2017   Sinil        Initial version                       **
*******************************************************************************/

#ifndef HSM_HAE_H
#define HSM_HAE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CryptoLib_Cfg.h"

#if (CRYPTOLIB_SUPORT_HSM_HAE_HSM_2_X == STD_ON)
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define HSM_HAE_SHA1_MAX_LENGTH                         (1020U)

#define HSM_HAE_SHA256_MAX_LENGTH                       (1020U)

#define HSM_HAE_TRNG_MAX_LENGTH                         (1024U)

#define HSM_HAE_PRNG_MAX_LENGTH                         (1024U)

#define HSM_HAE_AES_MAX_LENGTH                          (1024U)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

extern void HSM_HaeGetErrorCode(void);

#endif /* (CRYPTOLIB_SUPORT_HSM_HAE_HSM_2_X == STD_ON) */

#endif /* HSM_HAE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
