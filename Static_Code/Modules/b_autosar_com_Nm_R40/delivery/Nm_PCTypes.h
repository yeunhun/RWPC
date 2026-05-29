/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Nm_PCTypes.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Interface                                          **
**                                                                            **
**  PURPOSE   : Provides Type Definitions                                     **
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
** 2.3.0     30-Nov-2020   HM Shin       #26864                               **
** 2.2.1     23-Jan-2018   JeongSu Lim   #15692                               **
** 2.2.0     28-Dec-2018   JeongSu Lim   #13630, #15277, #15276, #15275,      **
**                                       #15274                               **
** 2.0.5     06-Sep-2016   Kt Kim        #5163                                **
** 2.0.4     17-May-2016   Kt Kim        #4641                                **
** 2.0.3     24-Aug-2015   Kt Kim        #3000                                **
** 1.0.0     26-Nov-2012   Kt Kim        Initial Version                      **
*******************************************************************************/
#ifndef NM_PCTYPES_H
#define NM_PCTYPES_H
/*******************************************************************************
**                       Include Section                                      **
*******************************************************************************/
#include "ComStack_Types.h" /* For  NetworkHandleType */
#include "NmStack_Types.h" /* Nm_ReturnType, Nm_StateType, Nm_ModeType */
#include "Com.h" /* For Com_SignalIdType */
#include "SchM_Nm.h"  /* Inclusion of Data Protection API's */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define NM_PCTYPES_AR_RELEASE_MAJOR_VERSION      (4)
#define NM_PCTYPES_AR_RELEASE_MINOR_VERSION      (0)
#define NM_PCTYPES_AR_RELEASE_REVISION_VERSION   (3)

/* Software Version Information */
#define NM_PCTYPES_SW_MAJOR_VERSION   (2)
#define NM_PCTYPES_SW_MINOR_VERSION   (3)
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/* Invalid value for NmStateReportSignalRef */
#define NM_INVALID_NONE               ((Com_SignalIdType)0xffff)
#define NM_TRUE                       ((boolean)1)
#define NM_FALSE                      ((boolean)0)
/*Invalid value for ucChnlCoordInfoIndex */
#define NM_INVALID                    ((uint8) 0xff)
#define NM_SLEEP_BIT_SET              ((boolean) 1)
#define NM_SLEEP_BIT_RESET            ((boolean) 0)

/* To avoid unused variable warning*/
/* polyspace +1 MISRA-C3:D4.9 [Not a defect:Justified] "Use function like-macro for removing unused argument compiler warning" */
#define NM_UNUSED(x)                    do{if ((uint32)(x) != \
                                           (uint32)NM_ZERO) {}}while(0)
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Structure for each Nm Channel */
typedef struct 
{
  /* Com Signal Id for NMS configuration */
  Com_SignalIdType ddNmStateReportSignalId;
  
  /* Pointer to structures of the type NmChannelCoord_ConfigInfo */
  uint8 ucChnlCoordInfoIndex;
  
  /* Channel Identifier */
  uint8 ddChannelId;

  boolean blStateReportEnabled;

  boolean blPassiveModeEnabled;

  boolean blActiveCoordinator;
  
  /* Gives the indication of NmChannelSleepMaster*/
  boolean blChannelSleepMaster;
  
  /* Gives the whether Network is synchronized or not */
  boolean blSynchronizingNetwork;

  uint32 ulShutdownDelayTimerTick;

  uint8 ucClusterListInfoIndex;

  /* Function pointer to <BusNm>_PassiveStartUp() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_PassiveStartUp)(
    CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);
  
  /* Function pointer to <BusNm>_NetworkRequest() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_NetworkRequest)(
    CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);
  
  /* Function pointer to <BusNm>_NetworkRelease() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_NetworkRelease)(
    CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);
  
  /* Function pointer to <BusNm>_DisableCommunication) */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_DisableCommunication)(
    CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);
  
  /* Function pointer to <BusNm>_EnableCommunication() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_EnableCommunication)(
    CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);
  
   /* Function pointer to <BusNm>_RepeatMessageRequest() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_RepeatMessageRequest)(
    CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle);
  
  /* Function pointer to <BusNm>_SetUserData() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_SetUserData)(
    CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
    CONSTP2CONST(uint8, AUTOMATIC, NM_APPL_CONST) nmUserDataPtr);
  
   /* Function pointer to <BusNm>_GetUserData() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_GetUserData)(
    CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
    CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmUserDataPtr);
  
  /* Function pointer to <BusNm>_GetPduData() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_GetPduData)(
    CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
    CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_CONST) nmNodeIdPtr);
  
  /* Function pointer to <BusNm>_GetNodeIdentifier() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_GetNodeIdentifier)(
    CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
    CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_CONST) nmNodeIdPtr);
  
  /* Function pointer to <BusNm>_GetLocalNodeIdentifier() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_GetLocalNodeIdentifier)(
    CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
    CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_CONST) nmNodeIdPtr);
  
  /* Function pointer to <BusNm>_CheckRemoteSleepIndication() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_CheckRemoteSleepIndication)(
    CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle,
    CONSTP2VAR(boolean, AUTOMATIC, NM_APPL_CONST) nmRemoteSleepIndPtr);
  
  /* Function pointer to <BusNm>_GetState() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_GetState)(
    CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle,
    CONSTP2VAR(Nm_StateType, AUTOMATIC, NM_APPL_CONST) nmStatePtr,
    CONSTP2VAR(Nm_ModeType, AUTOMATIC, NM_APPL_DATA) nmModePtr);

  /* Function pointer to <BusNm>_RequestBusSynchronization() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_RequestBusSynchronization)(
    CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle);
  
  /* Function pointer to <BusNm>_SetSleepReadyBit() */
  P2FUNC(Std_ReturnType, NM_APPL_CODE, pfnBusNm_SetSleepReadyBit)(
    CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle,
    CONST(boolean, NM_APPL_CONST) nmSleepReadyBit);

  P2FUNC(void, NM_APPL_CODE, pfnBusNm_StateChangeIndUserCallout)(
    CONST(Nm_StateType, NM_APPL_CONST) nmPreviousState,
    CONST(Nm_StateType, NM_APPL_CONST) nmCurrentState);

  P2FUNC(void, NM_APPL_CODE, pfnBusNm_PduRxIndUserCallout)(void);

} Nm_ChannelConfig;

typedef struct 
{
  P2FUNC(void, NM_APPL_CODE, pSchMFuncPtr)(void);
} Nm_SchMFuncPtr;

/* Structure containing cluster specific information */
/* polyspace-begin MISRA-C3:D4.8 [Not a defect: Justified] "Structure will be derefernenced based on Configuration" */
typedef struct 
{
  /* Coordination delay timer. Nm_GlobalCoordinatorTime - min(ulNmShutdownDelayTimerCount for the cluster)*/
  uint16 usCoordDelayTimer;
  /* Number of channels configured to this cluster */
  uint8 ucNumOfChnls;
  /* Index of the Channel list array */
  uint8 ucNmChnlMappingIndex;
} Nm_ClusterList;
/* polyspace-end MISRA-C3:D4.8 [Not a defect: Justified] "Structure will be derefernenced based on Configuration" */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define NM_START_SEC_CONST_UNSPECIFIED
#include"MemMap.h"

extern CONSTP2CONST(NetworkHandleType, AUTOMATIC, NM_CONST) Nm_GpChnlIndexArray;

#define NM_STOP_SEC_CONST_UNSPECIFIED
#include"MemMap.h"

#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
