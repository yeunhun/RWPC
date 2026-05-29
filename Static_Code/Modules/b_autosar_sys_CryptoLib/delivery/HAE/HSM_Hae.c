/*******************************************************************************
**                                                                            **
**  (C) 2017 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: HSM_Hae.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Implementation file for HSM                                   **
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
** 1.0.3     30-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.2     13-Mar-2020   JaeHyun      Redmine #22362                        **
** 1.0.1     04-Dec-2019   Sinil        Redmine #20521                        **
** 1.0.0     07-Aug-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "HSM_Hae.h"

#if (CRYPTOLIB_SUPORT_HSM_HAE_HSM_2_X == STD_ON)
#include "Hsm_HostAPI.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
static uint32 HSM_GddHaeLastError[CRYPTOLIB_HAE_HSM_MAX_ERROR_COUNT];

static uint32 HSM_GulHaeErrorCount = 0U;

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

void HSM_HaeGetErrorCode(void)
{
  HSM_GddHaeLastError[HSM_GulHaeErrorCount % CRYPTOLIB_HAE_HSM_MAX_ERROR_COUNT]
    = (uint32)HSM_GetLastErrorCode();

  HSM_GulHaeErrorCount++;
}

#endif /* (CRYPTOLIB_SUPORT_HSM_HAE_HSM_2_X == STD_ON) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
