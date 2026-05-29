/*******************************************************************************
**                                                                            **
**  (C) 2015 HYUNDAI AUTOEVER Co., Ltd.                                       **
**                                                                            **
**  SRC-MODULE: CDD_Router_PCTypes.h                                          **
**                                                                            **
**  PRODUCT   : CDD_Router Module                                             **
**                                                                            **
**  NOTE      : The provided static and generated codes of CDD_Router Module  **
**              are just for the understanding of the relationship between    **
**              communication Modules. The user must make sure that there are **
**              no problems with the operation through the full verification. **
**                                                                            **
*******************************************************************************/


/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 2.2.0     25-Mar-2020   HM Shin     #28308                                 **
** 2.1.0     02-Mar-2021   HM Shin     #28518                                  #
** 2.0.0     08-Aug-2018   Chan Kim    #13633                                 **
** 1.5.0     23-Aug-2016   Chan Kim    #5849                                  **
** 1.0.0     16-Mar-2015   Autoever      Initial Version                      **
*******************************************************************************/

#ifndef CDD_ROUTER_PCTYPES_H
#define CDD_ROUTER_PCTYPES_H

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define CDD_ROUTER_PCTYPES_AR_RELEASE_MAJOR_VERSION  4
#define CDD_ROUTER_PCTYPES_AR_RELEASE_MINOR_VERSION  0
#define CDD_ROUTER_PCTYPES_AR_RELEASE_REVISION_VERSION  3

/* Software Version Information */
#define CDD_ROUTER_PCTYPES_SW_MAJOR_VERSION  2
#define CDD_ROUTER_PCTYPES_SW_MINOR_VERSION  2

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComStack_Types.h" /* Com Stack Types header file */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* NONE */

/*******************************************************************************
**               Structure related to Router                                  **
*******************************************************************************/
#define CDD_ROUTER_ZERO                       0

typedef enum
{
  CddComIfUpperLayer,
  CddSoAdIfUpperLayer,
  CddNone,
}Cdd_Router_Layer;

/* Structure for Lower Layer IF Tx PDU */
typedef struct
{
  PduIdType ddTxPduHandleId;
  PduLengthType ddPduLength;
}CDD_Router_LowerIfTxPduInfo;

/* Structure for Lower Layer IF Rx PDU */
typedef struct
{
  PduIdType ddRxPduHandleId;
  PduLengthType ddPduLength;
}CDD_Router_LowerIfRxPduInfo;

/* Structure for Upper Layer IF Tx PDU */
typedef struct
{
  PduIdType ddTxPduHandleId;
  PduLengthType ddPduLength;

  /* PduId used for lower layer data transfer communication */
  PduIdType ddLoTargetPduHandleId;
  Cdd_Router_Layer ddLayerType;
}CDD_Router_UpperIfTxPduInfo;

/* Structure for Upper Layer TP Rx PDU */
typedef struct
{
  PduIdType ddRxPduHandleId;
  PduLengthType ddPduLength;
}CDD_Router_UpperTpRxPduInfo;

/* Structure for Upper Layer IF Rx PDU */
typedef struct
{
  PduIdType ddRxPduHandleId;
  PduLengthType ddPduLength;
}CDD_Router_UpperIfRxPduInfo;

/* Structure for IPC-If Rx PDU */
typedef struct
{
  PduIdType ddRxPduHandleId;
  PduLengthType ddPduLength;
  PduIdType ddTargetAddressId;
}CDD_IPC_UpperIfRxPduInfo;

/* Structure for IPC-If Tx PDU */
typedef struct
{
  PduIdType ddTxPduHandleId;
  PduLengthType ddPduLength;
  PduIdType ddTargetAddressId;
}CDD_IPC_UpperIfTxPduInfo;

/* Structure for IPC-Tp Rx PDU */
typedef struct
{
  PduIdType ddRxPduHandleId;
  PduLengthType ddPduLength;
  PduIdType ddTargetAddressId;
}CDD_IPC_UpperTpRxPduInfo;

/* Structure for IPC-Tp Tx PDU */
typedef struct
{
  PduIdType ddTxPduHandleId;
  PduLengthType ddPduLength;
  PduIdType ddTargetAddressId;
}CDD_IPC_UpperTpTxPduInfo;


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if(CDD_ROUTER_MAX_LOWER_IF_TX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This array defines the attributes of Tx Lower IF Module I-PDU */
extern CONST(CDD_Router_LowerIfTxPduInfo, CDD_ROUTER_CONST) 
CDD_Router_GaaLowerIfTxPduInfo[CDD_ROUTER_MAX_LOWER_IF_TX_PDU_COUNT];
#define CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(CDD_ROUTER_MAX_LOWER_SOAD_IF_TX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This array defines the attributes of Tx Lower SoAd IF Module I-PDU */
extern CONST(CDD_Router_LowerIfTxPduInfo, CDD_ROUTER_CONST)
CDD_Router_GaaLowerSoAdIfTxPduInfo[CDD_ROUTER_MAX_LOWER_SOAD_IF_TX_PDU_COUNT];
#define CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(CDD_ROUTER_MAX_LOWER_IF_RX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This array defines the attributes of Rx Lower IF Module I-PDU */
extern CONST(CDD_Router_LowerIfRxPduInfo, CDD_ROUTER_CONST) 
CDD_Router_GaaLowerIfRxPduInfo[CDD_ROUTER_MAX_LOWER_IF_RX_PDU_COUNT];
#define CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(CDD_ROUTER_MAX_LOWER_SOAD_IF_RX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This array defines the attributes of Rx Lower SoAd IF Module I-PDU */
extern CONST(CDD_Router_LowerIfRxPduInfo, CDD_ROUTER_CONST)
CDD_Router_GaaLowerSoAdIfRxPduInfo[CDD_ROUTER_MAX_LOWER_SOAD_IF_RX_PDU_COUNT];
#define CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(CDD_ROUTER_MAX_UPPER_IF_TX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This array defines the attributes of Tx Upper IF Module I-PDU */
extern CONST(CDD_Router_UpperIfTxPduInfo, CDD_ROUTER_CONST) 
CDD_Router_GaaUpperIfTxPduInfo[CDD_ROUTER_MAX_UPPER_IF_TX_PDU_COUNT];
#define CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(CDD_ROUTER_MAX_UPPER_TP_RX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This array defines the attributes of Rx Upper TP Module I-PDU */
extern CONST(CDD_Router_UpperTpRxPduInfo, CDD_ROUTER_CONST) 
CDD_Router_GaaUpperTpRxPduInfo[CDD_ROUTER_MAX_UPPER_TP_RX_PDU_COUNT];
#define CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(CDD_ROUTER_MAX_UPPER_IF_RX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This array defines the attributes of Rx Upper IF Module I-PDU */
extern CONST(CDD_Router_UpperIfRxPduInfo, CDD_ROUTER_CONST) 
CDD_Router_GaaUpperIfRxPduInfo[CDD_ROUTER_MAX_UPPER_IF_RX_PDU_COUNT];
#define CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(CDD_ROUTER_MAX_IPC_IF_RX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This array defines the attributes of Rx IPC IF Module I-PDU */
extern CONST(CDD_IPC_UpperIfRxPduInfo, CDD_ROUTER_CONST) 
CDD_IPC_GaaUpperIfRxPduInfo[CDD_ROUTER_MAX_IPC_IF_RX_PDU_COUNT];
#define CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(CDD_ROUTER_MAX_IPC_IF_TX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This array defines the attributes of Rx IPC IF Module I-PDU */
extern CONST(CDD_IPC_UpperIfTxPduInfo, CDD_ROUTER_CONST) 
CDD_IPC_GaaUpperIfTxPduInfo[CDD_ROUTER_MAX_IPC_IF_TX_PDU_COUNT];
#define CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(CDD_ROUTER_MAX_IPC_TP_RX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This array defines the attributes of Rx IPC IF Module I-PDU */
extern CONST(CDD_IPC_UpperTpRxPduInfo, CDD_ROUTER_CONST) 
CDD_IPC_GaaUpperTpRxPduInfo[CDD_ROUTER_MAX_IPC_TP_RX_PDU_COUNT];
#define CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(CDD_ROUTER_MAX_IPC_TP_TX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This array defines the attributes of Rx IPC IF Module I-PDU */
extern CONST(CDD_IPC_UpperTpTxPduInfo, CDD_ROUTER_CONST) 
CDD_IPC_GaaUpperTpTxPduInfo[CDD_ROUTER_MAX_IPC_TP_TX_PDU_COUNT];
#define CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(CDD_ROUTER_MAX_LOWER_IF_TX_PDU_COUNT > CDD_ROUTER_ZERO)
#if(CDD_ROUTER_MAX_UPPER_IF_TX_PDU_COUNT > CDD_ROUTER_ZERO)
#define CDD_ROUTER_CANIF_TXPDU(x) (CDD_Router_GaaLowerIfTxPduInfo[CDD_Router_GaaUpperIfTxPduInfo[x].ddLoTargetPduHandleId].ddTxPduHandleId)
#define CDD_ROUTER_TXPDU_TARGET(x)  (CDD_Router_GaaUpperIfTxPduInfo[x].ddLayerType)
#endif
#endif

#endif /* CDD_ROUTER_PCTYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
