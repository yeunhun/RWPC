/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/
/*******************************************************************************
**  (C) 2014 Hyundai AUTRON                                                   **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cdd_RamTst.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Cdd_RamTst stub                                       **
**                                                                            **
**  PURPOSE   : Declaration of Cdd_RamTst stub functions                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "RamTst.h"

/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
uint8 GucErrFlag;

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

void RamTst_ErrorNotification(void)
{
  GucErrFlag = 1;
} /* End of RamTst_ErrorNotification() */


void RamTst_TestCompletedNotification(void)
{
  GucErrFlag = 2;
} /* End of RamTst_TestCompletedNotification() */
  
/*******************************************************************************
**                       End of File                                          **
*******************************************************************************/
