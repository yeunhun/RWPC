/*******************************************************************************
**                                                                            **
**  (C) 2015 HYUNDAI AUTOEVER Co., Ltd.                                       **
**                                                                            **
**  SRC-MODULE: CDD_RouterTP.h                                                **
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
** 2.0.0     08-Aug-2018   Chan Kim    #13633                                 **
** 1.5.0     23-Aug-2016   Chan Kim    #5849                                  **
** 1.0.0     16-Mar-2015   Autoever    Initial Version                        **
*******************************************************************************/
  
#ifndef CDD_ROUTERTP_H
#define CDD_ROUTERTP_H
    
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
    
    /* AUTOSAR Specification Version Information */
#define CDD_ROUTERTP_AR_RELEASE_MAJOR_VERSION  4
#define CDD_ROUTERTP_AR_RELEASE_MINOR_VERSION  0
#define CDD_ROUTERTP_AR_RELEASE_REVISION_VERSION  3
    
    /* Software Version Information */
#define CDD_ROUTERTP_SW_MAJOR_VERSION  2
#define CDD_ROUTERTP_SW_MINOR_VERSION  2

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CDD_Router_Cfg.h"
#include "CDD_Router_PCTypes.h"
#if(CDD_ROUTER_MAX_UPPER_TP_RX_PDU_COUNT > CDD_ROUTER_ZERO)
#include "PduR_CDD_RouterTP.h"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CDD_ROUTER_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CDD_ROUTER_CODE) CDD_RouterTP_Transmit
  (PduIdType CddTxPduId, 
  P2CONST(PduInfoType, AUTOMATIC, CDD_ROUTER_APPL_DATA)PduInfoPtr);
#define CDD_ROUTER_STOP_SEC_CODE
#include "MemMap.h"


#define CDD_ROUTER_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CDD_ROUTER_CODE) CDD_RouterTP_CancelTransmit
  (PduIdType CddTxPduId);
#define CDD_ROUTER_STOP_SEC_CODE
#include "MemMap.h"

#define CDD_ROUTER_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CDD_ROUTER_CODE) CDD_RouterTP_CancelReceive
  (CONST(PduIdType, CDD_ROUTER_APPL_DATA) CddRxPduId);
#define CDD_ROUTER_STOP_SEC_CODE
#include "MemMap.h"


#endif /* CDD_ROUTERTP_H */

/*******************************************************************************
**                       End of File                                          **
*******************************************************************************/
