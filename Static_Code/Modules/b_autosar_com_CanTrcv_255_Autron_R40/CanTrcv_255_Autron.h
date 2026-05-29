
#ifndef CANTRCV_255_AUTRON_H
#define CANTRCV_255_AUTRON_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* CAN Transceiver Driver Config. header file */
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "CanIf_Cfg.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define CANTRCV_255_AUTRON_AR_RELEASE_MAJOR_VERSION (4)
#define CANTRCV_255_AUTRON_AR_RELEASE_MINOR_VERSION (0)
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      SERVICE IDs                                           **
*******************************************************************************/

/*******************************************************************************
**                      DET ERROR CODES                                       **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CANTRCV_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,CANTRCV_CODE)CanTrcv_255_Autron_Init(P2CONST(void, AUTOMATIC, CANTRCV_CONST)ConfigPtr);
extern FUNC(Std_ReturnType, CANTRCV_CODE)CanTrcv_255_Autron_SetOpMode(uint8 Transceiver, CanTrcv_TrcvModeType OpMode);
extern FUNC(Std_ReturnType, CANTRCV_CODE)CanTrcv_255_Autron_GetOpMode(uint8 Transceiver, P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA)OpMode);
#define CANTRCV_STOP_SEC_CODE
#include "MemMap.h" 

#endif  /* CANTRCV_255_AUTRON_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
