/*******************************************************************************
**                                                                            **
**  (C) 2017 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_Hae.h                                                     **
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
** 1.0.1     13-Mar-2020   JaeHyun      Redmine #22362                       **
** 1.0.0     07-Aug-2017   Sinil        Initial version                       **
*******************************************************************************/

#ifndef CRY_HAE_H
#define CRY_HAE_H

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern void Cry_HsmEnableService(uint32 conf, uint32 priority);
extern void Cry_HaeHsmDriverInit(void);

#endif /* CRY_HAE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
