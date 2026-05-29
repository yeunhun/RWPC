/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Icus_IntDriver.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for F1K ICUS                                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.2     28-Mar-2019   Sinil        Redmine #16794, #17130                **
** 1.0.1     21-Dec-2018   Sinil        Redmine #15254                        **
** 1.0.0     16-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef ICUS_INTDRIVER_H
#define ICUS_INTDRIVER_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "CryptoLib_Cfg.h"
#include "Icus_Driver.h"

#if (CRYPTOLIB_SUPORT_HSM_ICUS == STD_ON)
/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/
#ifndef ICUS_TIMEOUT_LEVEL_ONE
#define ICUS_TIMEOUT_LEVEL_ONE                          (0x200U)
#endif

#ifndef ICUS_TIMEOUT_LEVEL_TWO
#define ICUS_TIMEOUT_LEVEL_TWO                          (0x2000U)
#endif

#ifndef ICUS_TIMEOUT_LEVEL_THREE
#define ICUS_TIMEOUT_LEVEL_THREE                        (0x40000U)
#endif

#ifndef ICUS_TIMEOUT_LEVEL_FOUR
#define ICUS_TIMEOUT_LEVEL_FOUR                         (0xFFFFFU)
#endif

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

/***************************************************************************//**
 * @details   AES-128 기반 Cipher-based Message Authentication Code 생성 수행
 *            Streaming 방식(Start->Update(반복가능)->Finish) 으로 CMAC 생성 수행
 *            Start : Key 정보와 메세지 데이터 전체 bit 단위 길이 입력
 * @param     [in]  ddKeyId               CMAC-AES 생성 수행시 사용할 Key ID
 *                                        KEY_<n>, RAM_KEY
 * @param     [in]  ulTotalMsgBitLength   메세지 데이터 전체 bit 단위 길이
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    CMAC 생성 완료를 위해서는 이어서 Icus_GenerateMacUpdate,
 *            Icus_GenerateMacFinish 를 수행 해야 한다
 ******************************************************************************/
extern Icus_ErrType Icus_GenerateMacStart(Icus_KeyIDType ddKeyId, uint32 ulTotalMsgBitLength);

/***************************************************************************//**
 * @details   AES-128 기반 Cipher-based Message Authentication Code 생성 수행
 *            Streaming 방식(Start->Update(반복가능)->Finish) 으로 CMAC 생성 수행
 *            Update : 분할된 메세지 데이터를 입력, 반복 호출 가능
 *            ex) 256 bit * n 회 +  63 bit
 * @param     [in]  pMsgBlock             메세지 데이터 버퍼 포인터
 * @param     [in]  ulInputMsgBitLength   메세지 데이터 bit 단위 길이
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_GenerateMacUpdate(const uint8* pMsgBlock,
  uint32 ulInputMsgBitLength);

/***************************************************************************//**
 * @details   AES-128 기반 Cipher-based Message Authentication Code 생성 수행
 *            Streaming 방식(Start->Update(반복가능)->Finish) 으로 CMAC 생성 수행
 *            Finish : Start, Update 수행의 결과물인 MAC 값 추출
 * @param     [out] pMac                  MAC 버퍼 포인터
 * @param     [in]  ulMacByteLength       원하는 결과 MAC 값의 byte 단위 길이
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_GenerateMacFinish(uint8* pMac, uint32 ulMacByteLength);

/***************************************************************************//**
 * @details   AES-128 기반 Cipher-based Message Authentication Code 검증 수행
 *            Streaming 방식(Start->Update(반복가능)->Finish) 으로 CMAC 검증 수행
 *            Start : Key 정보와 메세지 데이터 전체 bit 단위 길이 입력
 * @param     [in]  ddKeyId               CMAC-AES 검증 수행시 사용할 Key ID
 *                                        KEY_<n>, RAM_KEY
 * @param     [in]  ulTotalMsgBitLength   메세지 데이터 전체 bit 단위 길이
 * @return    Icus_ErrType                기능 수행 결과
 * @remark    CMAC 검증 완료를 위해서는 이어서 Icus_VerifyMacUpdate,
 *            Icus_VerifyMacFinish 를 수행 해야 한다
 ******************************************************************************/
extern Icus_ErrType Icus_VerifyMacStart(Icus_KeyIDType ddKeyId,
  uint32 ulTotalMsgBitLength);

/***************************************************************************//**
 * @details   AES-128 기반 Cipher-based Message Authentication Code 검증 수행
 *            Streaming 방식(Start->Update(반복가능)->Finish) 으로 CMAC 검증 수행
 *            Update : 분할된 메세지 데이터를 입력, 반복 호출 가능
 *            ex) 256 bit * n 회 +  63 bit
 * @param     [in]  pMsgBlock             메세지 데이터 버퍼 포인터
 * @param     [in]  ulInputMsgBitLength   메세지 데이터 bit 단위 길이
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_VerifyMacUpdate(const uint8* pMsgBlock,
  uint32 ulInputMsgBitLength);

/***************************************************************************//**
 * @details   AES-128 기반 Cipher-based Message Authentication Code 검증 수행
 *            Streaming 방식(Start->Update(반복가능)->Finish) 으로 CMAC 검증 수행
 *            Finish : Start, Update 수행 후 입력 받은 MAC 값을 검증
 * @param     [in]  ulMacBitLength        검증에 사용할 MAC 값의 bit 단위 길이
 * @param     [in]  pMac                  MAC 버퍼 포인터
 * @param     [out] pblResult             검증 결과 버퍼 포인터
 * @return    Icus_ErrType                기능 수행 결과
 ******************************************************************************/
extern Icus_ErrType Icus_VerifyMacFinish(uint32 ulMacBitLength, const uint8* pMac,
  boolean* pblResult);

extern boolean Icus_IsIcusEnable(void);
extern uint32 Icus_GetCurrentCmd(void);
extern void Icus_ClearTxRxReq(void);
extern Icus_ErrType Icus_GerErrorStatus(void);
extern Icus_ErrType Icus_IsReady(uint32 LulTimeoutValue);
extern Icus_ErrType Icus_WaitTxReqDone(uint32 LulTimeoutValue);
extern Icus_ErrType Icus_WaitRxReqDone(uint32 LulTimeoutValue);
extern Icus_ErrType Icus_SetInputBlock(const uint8* pInput, uint32 ulBitLength);
extern Icus_ErrType Icus_GetOutputBlock(uint8* pOutput);
extern Icus_ErrType Icus_GenerateKDF(const uint8* pX0Key, const uint8* pX1Const,
  uint8* pDerivedKey);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CRYPTOLIB_SUPORT_HSM_ICUS == STD_ON) */

#endif /* ICUS_INTDRIVER_H */

/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
