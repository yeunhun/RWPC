/****************************************************************************************
* Project         :   QX SBR                                                            *
* File Name       :   api.h											                    *
* Compiler        :   COSMIC                                                            *
* Author          :   Suwan Woo (crazyabout7@seoyonelec.com)                            *
* Created at      :   2017-08-14                                                		*
* Code Editor     :   Source Insight (Recomended Font : D2Coding / Size 10)             *
* Revision        :   0.1                                               				*
* Copyright       :   (c) Copyright Seoyon Electronics Co.Ltd. All Rights Reserved      *
* Description     :                                                                     *
****************************************************************************************/



/* Define to prevent recursive inclusion -----------------------------------------------------*/
#ifndef    __API_H__
#define    __API_H__


/*******************************************************************************
* Declare External  Variables                                                  *
*******************************************************************************/

/*******************************************************************************
* Define Variables                                                             *
*******************************************************************************/


/*******************************************************************************
* Define Parameter                                                             *
*******************************************************************************/


/*******************************************************************************
	enum type variables
*******************************************************************************/

extern const tSTATE * CheckEn(const tSTATE *CUR, const tSTATE *des);
extern const tSTATE * CheckInit(const tSTATE *CUR);
extern const tSTATE * transition(const tSTATE *CUR, const tSTATE *des);
extern const tSTATE * transition_exit(const tSTATE *CUR, const tSTATE *des);
extern void CurrentRun(const tSTATE *CUR);

//#define Exit_Present()x)			do{x->ex();}while(0)

#if 0
#define diff_par(a) 					    ((a) == NULL ? NULL : a->f ))

#define find_par(a) 					    ((a) == NULL ? NULL : a->f ))
if(par->parent == des->parent)		{	par = par->parent;	break;	}
#endif
#endif
