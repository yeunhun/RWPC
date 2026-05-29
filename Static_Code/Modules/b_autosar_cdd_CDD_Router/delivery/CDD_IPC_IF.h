/*******************************************************************************
**                                                                            **
**  (C) 2015 HYUNDAI AUTOEVER Co., Ltd.                                       **
**                                                                            **
**  SRC-MODULE: CDD_RouterIF.h                                                **
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
** 1.0.0     16-Mar-2021   HM Shin     Initial Version                        **
*******************************************************************************/

#ifndef CDD_IPC_IF_H
#define CDD_IPC_IF_H
  
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
  
  /* AUTOSAR Specification Version Information */
#define CDD_ROUTERIF_AR_RELEASE_MAJOR_VERSION     4
#define CDD_ROUTERIF_AR_RELEASE_MINOR_VERSION     0
#define CDD_ROUTERIF_AR_RELEASE_REVISION_VERSION  3
  
  /* Software Version Information */
#define CDD_IPC_IF_SW_MAJOR_VERSION  2
#define CDD_IPC_IF_SW_MINOR_VERSION  2

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CDD_Router_Cfg.h"
#include "CDD_Router_PCTypes.h"
#if((CDD_ROUTER_MAX_IPC_IF_TX_PDU_COUNT > CDD_ROUTER_ZERO) \
|| (CDD_ROUTER_MAX_IPC_IF_RX_PDU_COUNT > CDD_ROUTER_ZERO))
#include "PduR_CDD_IPC_IF.h"
#endif


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CDD_ROUTER_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CDD_ROUTER_CODE) CDD_IPC_IF_Transmit
(PduIdType CddTxPduId, 
P2CONST(PduInfoType, AUTOMATIC, CDD_ROUTER_APPL_DATA)PduInfoPtr);

extern FUNC(void, CDD_ROUTER_CODE) CDD_IPC_RxIndication(
  P2CONST(uint8, AUTOMATIC, CDD_ROUTER_APPL_DATA)DataPtr);

#define CDD_ROUTER_STOP_SEC_CODE
#include "MemMap.h"
#endif /* CDD_ROUTERIF_H */

/*******************************************************************************
**                       End of File                                          **
*******************************************************************************/
