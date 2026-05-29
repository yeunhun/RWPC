/***********************************************************************************************************************
* File Name    : 10W_WPC_Diag.h
* Description  : Diag Control
***********************************************************************************************************************/

#ifndef WPC_DIAGONOSTIC_H_
#define WPC_DIAGONOSTIC_H_




#include "WPCType.h"

/********************************************************************************
* Global Variables
********************************************************************************/
extern u8 DTC_Set_Status;



/********************************************************************************
* Modules
********************************************************************************/
uint8 Get_DTC_B1621_Present(void);
void Set_DTC_B1621_WPCInternalError_Present(uint8 value);
void Set_DTC_B1621_TemperatureSensorFault_Present(uint8 value);
void Set_DTC_B1621_FANFault_Present(uint8 value);
void DiagStateTimer(void);


#endif /* 10W_WPC_Diag_H_ */
