/*******************************************************************************
 * Project      	: 	SP2 IBU
 * File Name    	: 	local_input.c
 * Compiler		: 	Eclipse
 * Author       	: 	MyoungKwon Choi (mk210@seoyonelec.com)
 * Created at   	: 	2017-06-23
 * Code Editor	: 	Source Insight (Recomended Font : D2Coding / Size 10)
 * Revision     	: 	Version 0.1
 * Copyright   	: 	(c) Copyright Seoyon Electronics Co.Ltd. All Rights Reserved
 * Description  	: 	
 *					
 ******************************************************************************/




/*******************************************************************************
	Include Headers
*******************************************************************************/
#include "HKMC_SecureFlash2.h"

#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"

#include "app_input_type.h"
#include "app_input.h"


#define Digest_Max				32u		
//#define Update_Length  			(uint32)0x00000300UL	/* DEC: 768 */
//#define Block0_Total_Length		(uint32)0x00000300UL	/* DEC: 768 */
#define Update_Length  			(uint32)0x00000400UL	/* DEC: 1024 */
#define Block0_Total_Length		(uint32)0x00000400UL	/* DEC: 1024 */

#define MAX_Hash_CheckTime		Time5msTASK_sec(180u)   /* 3min */

/* Partition Area */
#define PartA_Block0_Start    0x10048000UL
#define PartA_Block0_End   	  0x100488FFUL
#define PartA_Block1_Start    0x10048C00UL
#define PartA_Block1_End   	  0x1020FFFFUL

typedef enum
{
	kHashCalculationCtrl_Init=0u,
	kHashCalculationCtrl_Start, 
	kHashCalculationCtrl_Block0_Update,
	kHashCalculationCtrl_Block0_Update_Waiting,
	kHashCalculationCtrl_Block1_Update,
	kHashCalculationCtrl_DataReceiveFinish,
	kHashCalculationCtrl_Finish,
} e_HashCalculationCtrl;



static uint32  Block0_StartAddress;
static uint32  Block0_EndAddress;
static uint32  Block1_StartAddress;
static uint32  Block1_EndAddress;
static uint32  Block0_Check_Length;
static uint32  Block1_Check_Length;
static uint32  Block1_Update_cnt;
static uint32  Block1_TotalUpdate_cnt;
static uint32  Block1_divide_value;

static tTimer32	Timer_Block0_Update;
static tTimer32	Timer_Block1_Update;

static uint8 Digest_data[Digest_Max];

uint8 Diag_HashData[Digest_Max];

static uint8* b_Block0_Address;
static uint8* b_Block1_Address;

void Hash_Calculation_function(void);
static void Hash_Variable_Clear(void);

u8 Hash_Calculation_Check;

/****************************************************************************************
* Function name   :  Hash_Calculation_function                                          *
* parameter       :   void                                                              *
* Return          :   void                                                              *
* Description     :  1Task(5ms) Delay: 320us                                            *
* Revision		  :  2022.03.29 Modified Hash Logic					 					*
****************************************************************************************/
void Hash_Calculation_function(void)
{

	static e_HashCalculationCtrl	sts_HashCalculationCtrl;

	SecureFlash_RT	Return_Value;

	UpTimer32(Timer_Block0_Update);
	UpTimer32(Timer_Block1_Update);

	//b_DualM_Read_Value = DualM_ReadRunningArea();

	switch(sts_HashCalculationCtrl)
	{
		case kHashCalculationCtrl_Init:

				Block0_StartAddress = PartA_Block0_Start;
				Block0_EndAddress = PartA_Block0_End;
				Block1_StartAddress = PartA_Block1_Start;
				Block1_EndAddress = PartA_Block1_End;
				sts_HashCalculationCtrl = kHashCalculationCtrl_Start;
			break;
		case kHashCalculationCtrl_Start:
			if(GetX(kb_IGN_IN)==On)
			{
				Hash_Variable_Clear(); /* For Sleep->Wakeup */
				Return_Value= SecureFlash_HashStart();
				if(Return_Value==RT_SUCCESS)
				{
					Block0_Check_Length = (uint32)(Block0_EndAddress - Block0_StartAddress + 1u);	//0x900(DEC:2304)
					b_Block0_Address = (uint8*)Block0_StartAddress;	
					StartTimer(Timer_Block0_Update);
					sts_HashCalculationCtrl = kHashCalculationCtrl_Block0_Update;
				}				
			}

		break;

		case kHashCalculationCtrl_Block0_Update:
			if(GetX(kb_IGN_IN)==Off)
			{
				Hash_Variable_Clear();
				sts_HashCalculationCtrl = kHashCalculationCtrl_Init;
			}
			else
			{
				Return_Value = SecureFlash_HashUpdate(b_Block0_Address, Block0_Check_Length);
				if(Return_Value==RT_SUCCESS)
				{
					Block1_TotalUpdate_cnt = (uint32)(((uint32)(Block1_EndAddress - Block1_StartAddress))/Update_Length);	//나눈 값 : 1820
					Block1_divide_value = (uint32)(((uint32)(Block1_EndAddress - Block1_StartAddress))%Update_Length); // 나머지 : 1023
					Block1_Check_Length = Update_Length;
					Block1_Update_cnt = 1u;
					b_Block1_Address = (uint8*)Block1_StartAddress;
					CancelTimer(Timer_Block0_Update);
					StartTimer(Timer_Block1_Update);
					sts_HashCalculationCtrl = kHashCalculationCtrl_Block1_Update;
				}
				else if(Timer_Block0_Update.time>=MAX_Hash_CheckTime)
				{
					CancelTimer(Timer_Block0_Update);
					sts_HashCalculationCtrl = kHashCalculationCtrl_Start;
				}
				else{/* MISRA-C */}
			}
		break;

		case kHashCalculationCtrl_Block1_Update:
			if(GetX(kb_IGN_IN)==Off)
			{
				Hash_Variable_Clear();
				sts_HashCalculationCtrl = kHashCalculationCtrl_Init;
			}
			else
			{
				Return_Value = SecureFlash_HashUpdate(b_Block1_Address, Block1_Check_Length);
				if(Return_Value==RT_SUCCESS)
				{
					if(Block1_Update_cnt>Block1_TotalUpdate_cnt)
					{						
						CancelTimer(Timer_Block1_Update);
						sts_HashCalculationCtrl = kHashCalculationCtrl_DataReceiveFinish;
					}
					else
					{
						Block1_StartAddress = Block1_StartAddress + Update_Length;
						b_Block1_Address = (uint8*)Block1_StartAddress;
						Block1_Update_cnt = Block1_Update_cnt + 1u;

						if(Block1_Update_cnt>Block1_TotalUpdate_cnt)
						{
							Block1_Check_Length = Block1_divide_value + 1u;
						}
						else
						{
							Block1_Check_Length =  Update_Length;
						}
						
						sts_HashCalculationCtrl = kHashCalculationCtrl_Block1_Update;
					}
				}
				else if(Timer_Block1_Update.time>=MAX_Hash_CheckTime)
				{
					CancelTimer(Timer_Block1_Update);
					sts_HashCalculationCtrl = kHashCalculationCtrl_Start;
				}
				else{/* MISRA-C */}
			}
		break;
		case kHashCalculationCtrl_DataReceiveFinish:
			if(RT_SUCCESS==SecureFlash_HashFinish(Digest_data))
			{	
				Hash_Calculation_Check = On;  /* Hash Calculation Finish */
				memcpy(&Diag_HashData, &Digest_data, sizeof(Diag_HashData));
				sts_HashCalculationCtrl = kHashCalculationCtrl_Finish;		
			}
				
		break;

		case kHashCalculationCtrl_Finish:
			if(GetX(kb_IGN_IN)==Off)
			{
				Hash_Variable_Clear();
				sts_HashCalculationCtrl = kHashCalculationCtrl_Init;
			}	
		break;
		default:
		/* MISRA-C */
		break;
	}
}


static void Hash_Variable_Clear(void)
{
	u8 i=0u;
	
	Block0_Check_Length = 0x0u;
	Block1_Check_Length = 0x0u;
	CancelTimer(Timer_Block0_Update);
	CancelTimer(Timer_Block1_Update);
	b_Block0_Address = NULL;	
	b_Block1_Address = NULL;
	Block1_TotalUpdate_cnt = 0x0u;
	Block1_divide_value = 0x0u;
	Block1_Update_cnt = 0x0u;
	Hash_Calculation_Check = 0u; /* Hash End */
	
	/* Partition A */
	Block0_StartAddress = PartA_Block0_Start;
	Block0_EndAddress = PartA_Block0_End;
	Block1_StartAddress = PartA_Block1_Start;
	Block1_EndAddress = PartA_Block1_End;

	for(i=0u; i<Digest_Max; i++)
	{
		Digest_data[i] = 0x00u;
		Diag_HashData[i] = 0x00u;
	}

}
