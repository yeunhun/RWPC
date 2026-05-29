/****************************************************************************************
* Project         :   QX SBR                                                            *
* File Name       :   main.c										                    *
* Compiler        :   COSMIC                                                            *
* Author          :   Suwan Woo (crazyabout7@seoyonelec.com)                            *
* Created at      :   2017-08-14                                                		*
* Code Editor     :   Source Insight (Recomended Font : D2Coding / Size 10)             *
* Revision        :   0.1                                               				*
* Copyright       :   (c) Copyright Seoyon Electronics Co.Ltd. All Rights Reserved      *
* Description     :                                                                     *
****************************************************************************************/


/*******************************************************************************
* Include Headers                                                              *
*******************************************************************************/
#include "Rte_Type.h"
#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"

/* Never Position Change */
#include	"Superstate_api.h"

/*******************************************************************************
* Declare Function Prototypes                                                  *
*******************************************************************************/


/*******************************************************************************
* Define Constant and Macro                                                    *
*******************************************************************************/

#define MAX_STATE_STRUCT_STACK (6)

/*******************************************************************************
* Declare  Variables                                                           *
*******************************************************************************/



/*******************************************************************************
* Define Functions                                                             *
*******************************************************************************/


const tSTATE * CheckEn(const tSTATE *CUR, const tSTATE *des)
{
	u8 i=0u;
	const tSTATE *par = CUR;
	const tSTATE *entSTORE[MAX_STATE_STRUCT_STACK];
	u8 entINDEX=0u;

	CUR = des;
	entSTORE[entINDEX] = CUR;

	while(par->parent!=NULL)
	{
		if(par->parent == des->parent)		{	par = par->parent;	break;	}
		par = par->parent;
	}

	while(des->parent!=NULL)
	{
		if(par == des->parent)				{	break;	}
		entINDEX++;
		entSTORE[entINDEX] = des->parent;
		des = des->parent;
	}

	entINDEX++;
	for(i = entINDEX; i!=0u; i--)
	{
		entSTORE[i-1u]->en();
	}

	return CUR;
}


const tSTATE * CheckInit(const tSTATE *CUR)
{
	const tSTATE *strTemp;

	while(1)
	{
		strTemp = CUR->init();
		if(strTemp != NULL)
		{
			CUR=strTemp;
			CUR->en(); 
		}
		else
		{
			break;
		}
	}

	return CUR;
}

const tSTATE * transition(const tSTATE *CUR, const tSTATE *des)
{
	CUR = CheckEn(CUR, des);
	CUR = CheckInit(CUR);

	return CUR;
}

const tSTATE * transition_exit(const tSTATE *CUR, const tSTATE *des)
{
#if 1
	const tSTATE *par = CUR;
	const tSTATE *desPar = des;
	static u8 exFlag = 0u;

	CUR->ex();

	while(par->parent!=NULL)
	{
		/*if(par->parent == des->parent)
		{
			break;
		}*/
		exFlag = 0u;
		while(desPar->parent!=NULL)
		{
			if(par->parent == desPar->parent)
			{
				exFlag = 1u;
				break;
			}
			desPar = desPar->parent;
		}

		if(exFlag == 1u)
		{
			break;
		}
		else
		{
			desPar = des;
			par = par->parent;
			par->ex();
		}
	}

	return CUR;
#else
	const tSTATE *par = CUR;

	CUR->ex();

	while(par->parent!=NULL)
	{
		if(par->parent == des->parent)
		{
			break;
		}
		par = par->parent;
		par->ex();
	}

	return CUR;
#endif

}

void CurrentRun(const tSTATE *CUR)
{
	u8 ret=0u;
	u8 i=0u;
	const tSTATE *strSTORE[MAX_STATE_STRUCT_STACK];		//Move to Local variable in CurrentRun()
	u8 strINDEX=0u;	//Move to Local variable in CurrentRun()
	const tSTATE *par = CUR;

	strSTORE[strINDEX] = CUR;

	while(par->parent!=NULL) {
		strINDEX++;
		strSTORE[strINDEX] = par->parent;
		par = par->parent;
	}

	strINDEX++;
	for(i = strINDEX; i!=0u; i--) 
	{
		ret = strSTORE[i-1u]->run();
		if(ret > 0u)				{	break;	}
		strSTORE[i-1u]->du();
		if(i == 1u)		{	CheckInit(CUR);	}
	}
}

