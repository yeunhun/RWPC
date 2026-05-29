/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Wdg_76_Acw_Version.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTRON CUSTOM WDG                                     **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
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
** 1.8.2.0   18-Oct-2021   YH.Han       Redmine #32698                        **
** 1.5.0     25-Apr-2019   YH.Han       Redmine #16478                        **
** 1.1.0     17-Jul-2017   Kuksun       Redmine #8886                         **
** 1.0.2     28-Apr-2016   Sinil        Redmine #4744                         **
** 1.0.1     25-Apr-2016   Sinil        Redmine #4610                         **
** 1.0.0     02-Feb-2015   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw_Version.h"
#if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#if (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON)
#include "Dem.h"
#endif
#if ( (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON) || (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON) )
#include "Dio.h"
#elif (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
#include "Spi.h"
#endif

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* Wdg_76_Acw version check */
#if (WDG_76_ACW_AR_RELEASE_MAJOR_VERSION != \
  WDG_76_ACW_VERSION_AR_RELEASE_MAJOR_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Specification Major Version"
#endif
#if (WDG_76_ACW_AR_RELEASE_MINOR_VERSION != \
  WDG_76_ACW_VERSION_AR_RELEASE_MINOR_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Specification Minor Version"
#endif
#if (WDG_76_ACW_AR_RELEASE_REVISION_VERSION != \
  WDG_76_ACW_VERSION_AR_RELEASE_REVISION_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Specification Revision Version"
#endif
#if (WDG_76_ACW_SW_MAJOR_VERSION != WDG_76_ACW_VERSION_SW_MAJOR_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Software Major Version"
#endif
#if (WDG_76_ACW_SW_MINOR_VERSION != WDG_76_ACW_VERSION_SW_MINOR_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Software Minor Version"
#endif
#if (WDG_76_ACW_SW_PATCH_VERSION != WDG_76_ACW_VERSION_SW_PATCH_VERSION)
  #error "Wdg_76_Acw.h : Mismatch in Software Patch Version"
#endif

/* DET Version check */
#if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
#if defined(DET_AR_RELEASE_MAJOR_VERSION) \
  && defined(DET_AR_RELEASE_MINOR_VERSION)
#if (DET_AR_RELEASE_MAJOR_VERSION != WDG_76_ACW_DET_AR_RELEASE_MAJOR_VERSION)
  #error "Det.h : Mismatch in Specification Major Version"
#endif
#if (DET_AR_RELEASE_MINOR_VERSION != WDG_76_ACW_DET_AR_RELEASE_MINOR_VERSION)
  #error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif /* #if(WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */

/* DEM Version check */
#if (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON)
#if defined(DEM_AR_RELEASE_MAJOR_VERSION) \
  && defined(DEM_AR_RELEASE_MINOR_VERSION)
#if (DEM_AR_RELEASE_MAJOR_VERSION != WDG_76_ACW_DEM_AR_RELEASE_MAJOR_VERSION)
  #error "Dem.h : Mismatch in Specification Major Version"
#endif
#if (DEM_AR_RELEASE_MINOR_VERSION != WDG_76_ACW_DEM_AR_RELEASE_MINOR_VERSION)
  #error "Dem.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif /* #if(WDG_76_ACW_DEM_ERROR_REPORT == STD_ON) */

/* DIO Version check */
#if (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON)
#if defined(DIO_AR_RELEASE_MAJOR_VERSION) \
  && defined(DIO_AR_RELEASE_MINOR_VERSION)
#if (DIO_AR_RELEASE_MAJOR_VERSION != WDG_76_ACW_DIO_AR_RELEASE_MAJOR_VERSION)
  #error "Dio.h : Mismatch in Specification Major Version"
#endif
#if (DIO_AR_RELEASE_MINOR_VERSION < WDG_76_ACW_DIO_AR_RELEASE_MINOR_VERSION_L)
  #error "Dio.h : Mismatch in Specification Minor Version"
#endif
#if (DIO_AR_RELEASE_MINOR_VERSION > WDG_76_ACW_DIO_AR_RELEASE_MINOR_VERSION_U)
  #error "Dio.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif /* #if(WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON) */

/* GPT version check */
#if defined(GPT_AR_RELEASE_MAJOR_VERSION) \
  && defined(GPT_AR_RELEASE_MINOR_VERSION)
#if (GPT_AR_RELEASE_MAJOR_VERSION != WDG_76_ACW_GPT_AR_RELEASE_MAJOR_VERSION)
  #error "Gpt.h : Mismatch in Specification Major Version"
#endif
#if (GPT_AR_RELEASE_MINOR_VERSION < WDG_76_ACW_GPT_AR_RELEASE_MINOR_VERSION_L)
  #error "Gpt.h : Mismatch in Specification Minor Version"
#endif
#if (GPT_AR_RELEASE_MINOR_VERSION > WDG_76_ACW_GPT_AR_RELEASE_MINOR_VERSION_U)
  #error "Gpt.h : Mismatch in Specification Minor Version"
#endif
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
