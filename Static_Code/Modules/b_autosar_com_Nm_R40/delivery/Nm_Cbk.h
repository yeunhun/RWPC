/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Nm_Cbk.h                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : Header file for Nm_Cbk.c                                      **
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
** 1.0.0     26-Nov-2012   Kt Kim        Initial Version                      **
*******************************************************************************/
#ifndef NM_CBK_H
#define NM_CBK_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Nm.h" /* Inclusion for det error codes and SIDs of Nm call backs */
#include "Nm_PCTypes.h"  /* For Macros ChannelConfig structure */
#include "ComM_Nm.h"     /* For declaration of callbacks of ComM */
#include "Nm_Internal.h" /* For Nm_ClusterWakeUp() */
#include "Det.h"        /* Inclusion of Det header file */
#include "Com.h" /*For the declaration of Com_SendSignal()*/
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define NM_CBK_AR_RELEASE_MAJOR_VERSION     (4)
#define NM_CBK_AR_RELEASE_MINOR_VERSION     (0)
#define NM_CBK_AR_RELEASE_REVISION_VERSION  (3)

/* Software Version Information */
#define NM_CBK_SW_MAJOR_VERSION  (2)
#define NM_CBK_SW_MINOR_VERSION  (3)

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"

/* Declaration of  call back functions */
extern FUNC(void, NM_CODE) Nm_NetworkStartIndication(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_NetworkMode(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_PrepareBusSleepMode(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_BusSleepMode(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_StateChangeNotification(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle,
  CONST(Nm_StateType, NM_APPL_CONST) nmPreviousState,
  CONST(Nm_StateType, NM_APPL_CONST) nmCurrentState);

extern FUNC(void, NM_CODE) Nm_RemoteSleepIndication(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_RemoteSleepCancellation(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_SynchronizationPoint(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_PduRxIndication(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_CoordReadyToSleepIndication(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_RepeatMessageIndication(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_TxTimeoutException(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);

extern FUNC(void, NM_CODE) Nm_CarWakeUpIndication(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);
  
#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
