/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Hsm_AutShared.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for HSM                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.2.1     09-Apr-2019   Sinil        Redmine #16916                        **
** 1.2.0     09-Aug-2018   Sinil        Redmine #13647                        **
** 1.1.0     27-Oct-2017   Sinil        Redmine #10374, #10376                **
** 1.0.0     16-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

#ifndef HSM_AUTSHARED_H
#define HSM_AUTSHARED_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/
#define HSM_AUT_HSM_SYNC_RES_BUFFER                     (10)
#define HSM_AUT_HSM_ASYNC_RES_BUFFER                    (15)
#define HSM_AUT_HSM_PARAM_BUFFER                        (6)

#define HSM_AUT_HSM_READY_MAX_TIMEOUT                   (0xFFFFUL)

/*******************************************************************************
**                      Structures                                            **
*******************************************************************************/
typedef struct
{
  struct {
    uint8 ucReqCmd;
    uint32 ulReqSeq;
    uint32 ulParam[HSM_AUT_HSM_PARAM_BUFFER];
  } SyncReq;

  struct {
    uint8 ucReqCmd;
    uint32 ulReqSeq;
    uint32 ulReqCbkAddr;
    uint32 ulParam[HSM_AUT_HSM_PARAM_BUFFER];
  } AsyncReq[HSM_AUT_HSM_ASYNC_RES_BUFFER];

  struct
  {
    uint8 ucResError;
    uint8 ucResCmd;
    uint32 ulResSeq;
  } SyncRes[HSM_AUT_HSM_SYNC_RES_BUFFER];

  struct
  {
    uint8 ucResError;
    uint8 ucResCmd;
    uint32 ulResSeq;
    uint32 ulCbkAddr;
  } AsyncRes[HSM_AUT_HSM_ASYNC_RES_BUFFER];
} Hsm_SharedMem;

/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/
#define HSM_HT2HSM_SYNC_REQ_BASE_MASK                   (0x00000001UL)
#define HSM_HT2HSM_SYNC_REQ(x)        (HSM_HT2HSM_SYNC_REQ_BASE_MASK << (x))
#define HSM_HT2HSM_ASYNC_REQ_BASE_MASK                  (0x00010000UL)
#define HSM_HT2HSM_ASYNC_REQ(x)       (HSM_HT2HSM_ASYNC_REQ_BASE_MASK << (x))
#define HSM_HSM2HT_ASYNC_RES_BASE_MASK                  (0x00000002UL)
#define HSM_HSM2HT_ASYNC_RES(x)       (HSM_HSM2HT_ASYNC_RES_BASE_MASK << (x))

#endif /* HSM_AUTSHARED_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
