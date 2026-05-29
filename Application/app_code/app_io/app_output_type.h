/******************************************************************************
 * Project      	: 	SP2 IBU
 * File Name    	: 	app_output_type.h
 * Compiler			: 	Eclipse
 * Author       	: 	MyoungKwon Choi (mk210@seoyonelec.com)
 * Created at   	: 	2017-06-23
 * Code Editor		: 	Source Insight (Recomended Font : D2Coding / Size 10)
 * Revision     	: 	Version 0.1
 * Copyright  	 	: 	Copyright Seoyon Electronics Co.Ltd. All Rights Reserved
 * Description  	: 	
 *
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------*/
#ifndef	__APP_OUTPUT_TYPE_H__
#define	__APP_OUTPUT_TYPE_H__

#include "Rte_Type.h"

/*******************************************************************************
	Define Variables Type
*******************************************************************************/
typedef struct
{
	/* OUTPUT */
	tVAR kL_Amber_OUT;
	tVAR kL_Green_OUT;
	tVAR kL_Fan_OUT;
	tVAR kP_AmberIND_OUT;
	tVAR kP_GreenIND_OUT;
	/* B-CAN */
	tVAR kC_USM_ValCmdStaforATS;
	tVAR kC_USM_CmdWPCSta;
	tVAR kC_WPC_PhnLftWrngRWPCSta;
	tVAR kC_RWPC_SWVerMajor1;
	tVAR kC_RWPCSWVerMinor1;
	tVAR kC_RWPCSWVerMinor2;
	tVAR kC_RWPC_IndSyncVal;
	/* L-CAN */
	tVAR kC_WPC_NFCReset;	
	tVAR kC_WPC_NFCDetection;
	/* Not real Diag */
	//tVAR WPCDiagState;	
}tAPP_OUTPUT;



#endif	/* __APP_OUTPUT_TYPE_H__ */

