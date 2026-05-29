/******************************************************************************
 * Project      	: 	SP2 IBU
 * File Name    	: 	app_output.h
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
#ifndef	__APP_OUTPUT_H__
#define	__APP_OUTPUT_H__


/*******************************************************************************
	Declare External  Function
*******************************************************************************/


/*******************************************************************************
	Declare External  Variables
*******************************************************************************/
extern	tAPP_OUTPUT	APP_OUTPUT_IF;




/*******************************************************************************
	Define  Variables
*******************************************************************************/
/* OUTPUT */
#define kL_Amber_OUT				      	APP_OUTPUT_IF.kL_Amber_OUT
#define kL_Green_OUT				      	APP_OUTPUT_IF.kL_Green_OUT
#define	kL_Fan_OUT					      	APP_OUTPUT_IF.kL_Fan_OUT
#define	kP_AmberIND_OUT				    	APP_OUTPUT_IF.kP_AmberIND_OUT
#define	kP_GreenIND_OUT				    	APP_OUTPUT_IF.kP_GreenIND_OUT

/* WPC_01_200ms */
#define kC_USM_ValCmdStaforATS				APP_OUTPUT_IF.kC_USM_ValCmdStaforATS
#define kC_USM_CmdWPCSta					APP_OUTPUT_IF.kC_USM_CmdWPCSta
#define kC_WPC_PhnLftWrngRWPCSta      		APP_OUTPUT_IF.kC_WPC_PhnLftWrngRWPCSta	//RWPC
#define kC_RWPC_SWVerMajor1        			APP_OUTPUT_IF.kC_RWPC_SWVerMajor1
#define	kC_RWPCSWVerMinor1					APP_OUTPUT_IF.kC_RWPCSWVerMinor1
#define	kC_RWPCSWVerMinor2					APP_OUTPUT_IF.kC_RWPCSWVerMinor2

#define kC_RWPC_IndSyncVal					APP_OUTPUT_IF.kC_RWPC_IndSyncVal

/* OUTPUT L-CAN */
#define kC_WPC_NFCReset						APP_OUTPUT_IF.kC_WPC_NFCReset	
#define kC_WPC_NFCDetection       			APP_OUTPUT_IF.kC_WPC_NFCDetection


// not real output value
//#define	kC_WPCDiagState, 					APP_OUTPUT_IF.WPCDiagState		/* Diag Timeout for Diag logic : 5s */


/*******************************************************************************
	Define Parameter
*******************************************************************************/




/*******************************************************************************
	Define Constant and Macro						
*******************************************************************************/

#endif	/* __APP_OUTPUT_H__ */



