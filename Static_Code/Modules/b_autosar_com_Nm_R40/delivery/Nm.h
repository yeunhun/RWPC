/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
** SRC-MODULE: Nm.h                                                           **
**                                                                            **
** TARGET    : All                                                            **
**                                                                            **
** PRODUCT   : AUTOSAR Nm Module                                              **
**                                                                            **
** PURPOSE   : Provision of module header                                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision      Date         By         Description                          **
********************************************************************************
** 2.2.0     28-Dec-2018   JeongSu Lim   #13630, #15277, #15276, #15275,      **
**                                       #15274                               **
** 1.0.3     24-May-2016   Kt Kim        #4520                                **
** 1.0.0     18-Apr-2013   Kt Kim        Initial version                      **
*******************************************************************************/
#ifndef NM_H
#define NM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NmStack_Types.h" /* For StateType, ModeType and Std_ReturnType */
#include "Nm_Cfg.h"
#include "ComStack_Types.h" /* For NetworkHandleType */
#include "Det.h"  /* Inclusion of Det header file */
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Necessary in logic */

#define NM_INIT                             ((boolean)1)

#define NM_ZERO                             ((boolean)0)

/* DET Error codes */
#define NM_E_UNINIT                         ((uint8)0x00)
#define NM_E_HANDLE_UNDEF                   ((uint8)0x01)
#define NM_E_PARAM_POINTER                  ((uint8)0x02)
#define NM_E_INVALID_REQUEST                ((uint8)0x03)


/* API Service Ids */
#define NM_PASSIVESTARTUP_SID               ((uint8)0x01)
#define NM_GETVERSIONINFO_SID               ((uint8)0x0f)
#define NM_NETWORKREQUEST_SID               ((uint8)0x02)
#define NM_NETWORKRELEASE_SID               ((uint8)0x03)
#define NM_DISABLECOMMUNICATION_SID         ((uint8)0x04)
#define NM_ENABLECOMMUNICATION_SID          ((uint8)0x05)
#define NM_REPEATMESSAGEREQUEST_SID         ((uint8)0x09)
#define NM_SETUSERDATA_SID                  ((uint8)0x06)
#define NM_GETUSERDATA_SID                  ((uint8)0x07)
#define NM_GETPDUDATA_SID                   ((uint8)0x08)
#define NM_GETNODEIDENTIFIER_SID            ((uint8)0x0a)
#define NM_GETLOCALNODEIDENTIFIER_SID       ((uint8)0x0b)
#define NM_CHECKREMOTESLEEPINDICATION_SID   ((uint8)0x0d)
#define NM_GETSTATE_SID                     ((uint8)0x0e)
#define NM_NETWORKSTARTINDICATION_SID       ((uint8)0x11)
#define NM_NETWORKMODE_SID                  ((uint8)0x12)
#define NM_PREPAREBUSSLEEPMODE_SID          ((uint8)0x13)
#define NM_BUSSLEEPMODE_SID                 ((uint8)0x14)
#define NM_PDURXINDICATION_SID              ((uint8)0x15)
#define NM_STATECHANGENOTIFICATION_SID      ((uint8)0x16)
#define NM_REMOTESLEEPINDICATION_SID        ((uint8)0x17)
#define NM_REMOTESLEEPCANCELLATION_SID      ((uint8)0x18)
#define NM_SYNCHRONIZATIONPOINT_SID         ((uint8)0x19)
#define NM_REPEATMESSAGEINDICATION_SID      ((uint8)0x1a)
#define NM_CARWAKEUPINDICATION_SID          ((uint8)0x1d)
#define NM_COORDREADYTOSLEEPINDICATION_SID  ((uint8)0x1e)
#define NM_MAINFUNCTION_SID                 ((uint8)0x10)

/* Macro for Instance Id to be used for reporting Det error
*  "NM_E_HANDLE_UNDEF".
*/
#define NM_INSTANCE_ID                      ((uint8)0x00)

/*Macros for assigning values to the NMS*/
#define NM_RM_BSM                            ((uint8) 0x01)
#define NM_RM_PBSM                           ((uint8) 0x02)
#define NM_NO_RM                             ((uint8) 0x04)
#define NM_NO_RS                             ((uint8) 0x08)
#define NM_RM_RS                             ((uint8) 0x10)
#define NM_RM_NO                             ((uint8) 0x20)

/*Macros for assigning values to cluster shutdown flags*/
#define NM_SLEEP                             ((uint8) 0x00)
#define NM_AWAKE                             ((uint8) 0x01)
#define NM_SHUTDOWN_READY                    ((uint8) 0x02)
#define NM_TIMERS_SET                        ((uint8) 0x03)
#define NM_SHUTDOWN_ABORTED                  ((uint8) 0x04)
#define NM_BUS_RELEASED                      ((uint8) 0x05)
#define NM_COORD_DELAY                       ((uint8) 0x06)

/*Macros for assigning values to network release flags*/
#define NM_NO_RELEASE                        ((uint8) 0x00)
#define NM_COMM_RELEASE                      ((uint8) 0x01)
#define NM_BUSNM_RELEASE                     ((uint8) 0x02)
#define NM_COMM_BUSNM_RELEASE                ((uint8) 0x03)
#define NM_SLEEP_INDICATED                   ((uint8) 0x04)

/*Macro for assigning zero values to shutdown delay timers*/
#define NM_TIMER_RESET                       ((uint16) 0x0000)


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, NM_CODE) Nm_Init(void);

extern FUNC(void, NM_CODE) Nm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, NM_APPL_DATA) NmVerInfoPtr);

extern FUNC(Std_ReturnType, NM_CODE) Nm_PassiveStartUp(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);

extern FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRequest(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);

extern FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRelease(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);

extern FUNC(Std_ReturnType, NM_CODE) Nm_DisableCommunication(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);

extern FUNC(Std_ReturnType, NM_CODE) Nm_EnableCommunication(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);

extern FUNC(Std_ReturnType, NM_CODE) Nm_SetUserData(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
  CONSTP2CONST(uint8, AUTOMATIC, NM_APPL_CONST) nmUserDataPtr);

extern FUNC(Std_ReturnType, NM_CODE) Nm_GetUserData(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
  CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmUserDataPtr);

extern FUNC(Std_ReturnType, NM_CODE) Nm_GetPduData(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
  CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmPduData);

extern FUNC(Std_ReturnType, NM_CODE) Nm_RepeatMessageRequest(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);

extern FUNC(Std_ReturnType, NM_CODE) Nm_GetNodeIdentifier(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
  CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmNodeIdPtr);

extern FUNC(Std_ReturnType, NM_CODE) Nm_GetLocalNodeIdentifier(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
  CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmNodeIdPtr);

extern FUNC(Std_ReturnType, NM_CODE) Nm_CheckRemoteSleepIndication(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle,
  CONSTP2VAR(boolean, AUTOMATIC, NM_APPL_DATA) nmRemoteSleepIndPtr);

extern FUNC(Std_ReturnType, NM_CODE) Nm_GetState(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle,
  CONSTP2VAR(Nm_StateType, AUTOMATIC, NM_APPL_CONST) nmStatePtr,
  CONSTP2VAR(Nm_ModeType, AUTOMATIC, NM_APPL_DATA) nmModePtr);

#define NM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Necessary in logic */
#endif  /* NM_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
