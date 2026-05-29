/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Main.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of Generic CSM Functions                       **
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
** 2.6.4.0   16-Apr-2021   JHLim        Redmine #29350                        **
** 1.2.5     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.4     09-Aug-2018   Sinil        Redmine #13650                        **
** 1.2.3     19-Mar-2018   Sinil        Redmine #11930                        **
** 1.2.2     21-Sep-2017   Sinil        Redmine #7968                         **
** 1.2.1     21-Sep-2017   Sinil        Redmine #10038                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198                         **
** 1.0.7     09-Aug-2016   Sinil        Redmine #5744                         **
** 1.0.6     29-Jul-2016   Sinil        Redmine #5514, #5716                  **
** 1.0.5     13-Jun-2016   Sinil        Redmine #4900                         **
** 1.0.4     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.3     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.2     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.1     05-Jan-2016   Sinil        Use const macro                       **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm.h"                  /* Header file for function prototypes */
#include "Rte_Csm.h"
#include "SchM_Csm.h"
#if (CSM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Header file for DET */
#endif
#include "Cry_Init.h"
#include "CryptoLib_Cfg.h"
#include "string.h"
#include "Os.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Global variable to indicate the initialization of the module */
boolean Csm_GblInitStatus;

#define CSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

static FUNC(StatusType, CSM_CODE)Csm_CheckTaskStatus(TaskType TaskId);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Csm_Init                                              **
**                                                                            **
** Service ID         : 0x00                                                  **
**                                                                            **
** Description        : This service initializes the Crypto Service Manager.  **
**                      All the Global variables will be initialized after    **
**                      the successful completion of this API.                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s):                                   **
**                                 Csm_GddActiveHashService,                  **
**                                 Csm_GddActiveMacGenerateService            **
**                                 Csm_GddActiveMacVerifyService              **
**                                 Csm_GddActiveRandomSeedService             **
**                                 Csm_GddActiveRandomGenerateService         **
**                                 Csm_GddActiveSymBlockEncryptService        **
**                                 Csm_GddActiveSymBlockDecryptService        **
**                                 Csm_GddActiveSymEncryptService             **
**                                 Csm_GddActiveSymDecryptService             **
**                                 Csm_GddActiveAsymEncryptService            **
**                                 Csm_GddActiveAsymDecryptService            **
**                                 Csm_GddActiveSignatureGenerateService      **
**                                 Csm_GddActiveSignatureVerifyService        **
**                                 Csm_GddActiveChecksumService               **
**                                 Csm_GddActiveKeyDeriveService              **
**                                 Csm_GddActiveKeyDeriveSymKeyService        **
**                                 Csm_GddActiveKeyExchangeCalcPubValService  **
**                                 Csm_GddActiveKeyExchangeCalcSecretService  **
**                                 Csm_GddActiveKeyExchangeCalcSymKeyService  **
**                                 Csm_GddActiveSymKeyExtractService          **
**                                 Csm_GddActiveSymKeyWrapSymService          **
**                                 Csm_GddActiveSymKeyWrapAsymService         **
**                                 Csm_GddActiveAsymPublicKeyExtractService   **
**                                 Csm_GddActiveAsymPrivateKeyExtractService  **
**                                 Csm_GddActiveAsymPrivateKeyWrapSymService  **
**                                 Csm_GddActiveAsymPrivateKeyWrapAsymService **
**                                 Csm_GddFunctionStack, Csm_GblInitStatus    **
**                                                                            **
**                     Function(s) invoked:                                   **
**                                 SchM_Enter_Csm_FUNCTION_PTR_PROTECTION     **
**                                 SchM_Exit_Csm_FUNCTION_PTR_PROTECTION      **
*******************************************************************************/
void Csm_Init(void)
{
  uint8 LucIndex;

  /* Hash Services */
  #if (CSM_HASH_STATUS == STD_ON) /* Hash Interface is configured */
  /* Setting the Hash Service state to IDLE*/
  Csm_GddActiveHashService.ucServiceState = CSM_HASH_IDLE;
  #endif /* Hash interface */

  /* MAC Services */
  #if (CSM_MAC_GENERATE_STATUS == STD_ON)
  /* Setting the MAC Generate service state to IDLE */
  Csm_GddActiveMacGenerateService.ucServiceState = CSM_MAC_GENERATE_IDLE;
  #endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */
  #if (CSM_MAC_VERIFY_STATUS == STD_ON)
  /* Setting the MAC Verify service state to IDLE */
  Csm_GddActiveMacVerifyService.ucServiceState = CSM_MAC_VERIFY_IDLE;
  #endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

  /* Random Number Generator Services */
  #if (CSM_RANDOM_SEED_STATUS == STD_ON)
  /* Setting the Random Seed service state to IDLE */
  Csm_GddActiveRandomSeedService.ucServiceState = CSM_RANDOM_SEED_IDLE;
  #endif /* (CSM_RANDOM_SEED_STATUS == STD_ON) */
  #if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
  /* Setting the Random Generate service state to IDLE */
  Csm_GddActiveRandomGenerateService.ucServiceState = CSM_RANDOM_GENERATE_IDLE;
  #endif /* (CSM_RANDOM_GENERATE_STATUS == STD_ON) */

  /* Symmetrical Block Services */
  #if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
  /* Setting the Symmetrical Block Encryption service state to IDLE */
  Csm_GddActiveSymBlockEncryptService.ucServiceState =
    CSM_SYM_BLOCK_ENCRYPT_IDLE;
  #endif /* (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) */
  #if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
  /* Setting the Symmetrical Block Decryption service state to IDLE */
  Csm_GddActiveSymBlockDecryptService.ucServiceState =
    CSM_SYM_BLOCK_DECRYPT_IDLE;
  #endif /* (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) */

  /* Symmetrical Services */
  #if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
  /* Setting the Symmetrical Encryption service state to IDLE */
  Csm_GddActiveSymEncryptService.ucServiceState = CSM_SYM_ENCRYPT_IDLE;
  #endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */
  #if (CSM_SYM_DECRYPT_STATUS == STD_ON)
  /* Setting the Symmetrical Decryption service state to IDLE */
  Csm_GddActiveSymDecryptService.ucServiceState = CSM_SYM_DECRYPT_IDLE;
  #endif /* (CSM_SYM_DECRYPT_STATUS == STD_ON) */

  /* Asymmetrical Services */
  #if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
  Csm_GddActiveAsymEncryptService.ucServiceState = CSM_ASYM_ENCRYPT_IDLE;
  #endif /* (CSM_ASYM_ENCRYPT_STATUS == STD_ON) */
  #if (CSM_ASYM_DECRYPT_STATUS == STD_ON)
  Csm_GddActiveAsymDecryptService.ucServiceState = CSM_ASYM_DECRYPT_IDLE;
  #endif /* (CSM_ASYM_DECRYPT_STATUS == STD_ON) */

  /* Signature Services */
  #if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
  /* Setting the Signature Generate service state to IDLE */
  Csm_GddActiveSignatureGenerateService.ucServiceState =
    CSM_SIGNATURE_GENERATE_IDLE;
  #endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */
  #if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
  /* Setting the Signature Verify service state to IDLE */
  Csm_GddActiveSignatureVerifyService.ucServiceState =
    CSM_SIGNATURE_VERIFY_IDLE;
  #endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

  /* Checksum Services */
  #if (CSM_CHECKSUM_STATUS == STD_ON) /* Checksum */
  /* Setting the Checksum service state to IDLE */
  Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_IDLE;
  #endif /* Checksum */

  /* Key Derivation Services */
  #if (CSM_KEY_DERIVATION_STATUS == STD_ON) /* Key Derivation */
  /* Setting the Key Derivation service state to IDLE */
  Csm_GddActiveKeyDeriveService.ucServiceState = CSM_KEY_DERIVE_IDLE;
  #endif /* Key Derivation */
  #if (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON)
  /* Setting the Key Derivation with Symmetrical Key service state to IDLE */
  Csm_GddActiveKeyDeriveSymKeyService.ucServiceState =
    CSM_KEY_DERIVE_SYMKEY_IDLE;
  #endif

  /* Key Exchange Services */
  #if (CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON) /* Key Exchange */
  /* Setting the Key Exchange public value calculation service state to IDLE */
  Csm_GddActiveKeyExchangeCalcPubValService.ucServiceState =
    CSM_KEY_EXCHANGE_CALCPUBVAL_IDLE;
  #endif

  #if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON)
  /* Setting the Key Exchange secret value calculation service state to IDLE */
  Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState =
    CSM_KEY_EXCHANGE_CALC_SECRET_IDLE;
  #endif

  #if (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON)
  /* Setting the Key Exchange Symmetrical Key service state to IDLE */
  Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState =
    CSM_KEY_EXCHANGE_CALC_SYM_KEY_IDLE;
  #endif

  /* Symmetrical Key Extraction Services */
  #if (CSM_SYM_KEY_EXTRACT_STATUS == STD_ON) /* Symmetrical Key Extraction */
  /* Setting the Symmetrical Key Extraction service state to IDLE */
  Csm_GddActiveSymKeyExtractService.ucServiceState = CSM_SYM_KEY_EXTRACT_IDLE;
  #endif /* Symmetrical Key Extraction */

  /* Symmetrical Key Wrapping Services */
  #if (CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON) /* Symmetric Wrapping Key */
  /*
   * Setting Symmetrical Key Wrapping with Symmetrical Key service state to
   * IDLE
   */
  Csm_GddActiveSymKeyWrapSymService.ucServiceState = CSM_SYM_KEY_WRAP_SYM_IDLE;
  #endif /* Symmetric Wrapping Key */

  #if (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON) /* Asymmetric Wrapping Key */
  /*
   * Setting Symmetrical Key Wrapping with Asymmetrical Key service state to
   * IDLE
   */
  Csm_GddActiveSymKeyWrapAsymService.ucServiceState =
    CSM_SYM_KEY_WRAP_ASYM_IDLE;
  #endif /* Asymmetric Wrapping Key */

  /* Asymmetrical Key Extraction Services */
  #if (CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON)
  /* Setting the Asymmetrical Public Key Extraction  service state to IDLE */
  Csm_GddActiveAsymPublicKeyExtractService.ucServiceState =
    CSM_ASYM_PUBLIC_KEY_EXTRACT_IDLE;
  #endif

  #if (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON)
  /* Setting the Asymmetrical Private Key Extraction  service state to IDLE */
  Csm_GddActiveAsymPrivateKeyExtractService.ucServiceState =
    CSM_ASYM_PRIVATE_KEY_EXTRACT_IDLE;
  #endif /* Asymmetrical Key Extraction */

  /* Asymmetrical Key Wrapping services */
  #if (CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON) /* Symmetric Wrapping Key */
  /*
   * Setting the Asymmetrical Private Key Wrapping with Symmetrical Key service
   * state to IDLE
   */
  Csm_GddActiveAsymPrivateKeyWrapSymService.ucServiceState =
    CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE;
  #endif /* Symmetric Wrapping Key */
  #if (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON) /* Asymmetric Wrapping Key */
  /*
   * Setting the Asymmetrical Private Key Wrapping with Asymmetrical Key service
   * state to IDLE
   */
  Csm_GddActiveAsymPrivateKeyWrapAsymService.ucServiceState =
    CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_IDLE;
  #endif /* Asymmetric Wrapping Key */

  /*
   * Initializing Global variable for array of structure of function pointers
   * Entering into the Protected area
   */

  SchM_Enter_Csm_FUNCTION_PTR_PROTECTION();

  for (LucIndex = CSM_ZERO; LucIndex < CSM_STACK_MAXSIZE; LucIndex++)
  {
    /* Initialize all function pointers to NULL */
    Csm_GddFunctionStack.paaFunctionPtr[LucIndex] = NULL_PTR;
  }

  /* Set the top of stack to 0 */
  Csm_GddFunctionStack.ucTop = CSM_ZERO;

  /* Exiting Protected area */
  SchM_Exit_Csm_FUNCTION_PTR_PROTECTION();

  #if ((CRYPTOLIB_SUPORT_HSM_SPC58X == STD_ON) || (CRYPTOLIB_SUPORT_HSM_ICUM == STD_ON) || (CRYPTOLIB_SUPORT_HSM_CSEC == STD_ON))

  if (Cry_Init() == E_OK)
  {
    /* Updating the status for Csm_Init() upon successful invocation */
    Csm_GblInitStatus = CSM_TRUE;
  }
  else
  {
    Csm_GblInitStatus = CSM_FALSE;
  }

  #else

  (void)Cry_Init();

  Csm_GblInitStatus = CSM_TRUE;

  #endif
}

/*******************************************************************************
** Function Name       : Csm_GetVersionInfo                                   **
**                                                                            **
** Service ID          : 0x3B                                                 **
**                                                                            **
** Description         : This service gives version information of the CSM    **
**                       module. The version information includes module Id,  **
**                       vendor Id, InstanceId & vendor specific version no's **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy         : Reentrant                                            **
**                                                                            **
** Input Parameters    : None                                                 **
**                                                                            **
** Output Parameters   : versioninfo                                          **
**                                                                            **
** InOut Parameters    : None                                                 **
**                                                                            **
** Return parameter    : None                                                 **
**                                                                            **
** Preconditions       : None                                                 **
**                                                                            **
** Remarks            : Global Variable(s):                                   **
**                      None                                                  **
**                      Function(s) invoked:                                  **
**                      Det_ReportError                                       **
*******************************************************************************/
#if (CSM_VERSION_INFO_API == STD_ON)
void Csm_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
  /*check if development error detection is enabled*/
  #if (CSM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether the pointer passed to API is Null Pointer */
  if (versioninfo == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_GETVERSIONINFO_SID, CSM_E_PARAM_PTR_INVALID);
  }
  else
  {
  #endif /* (CSM_DEV_ERROR_DETECT == STD_ON) */

  /* Copy the vendor Id */
  /* polyspace-begin MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  versioninfo->vendorID = CSM_VENDOR_ID;
  /* Copy the module Id */
  versioninfo->moduleID = CSM_MODULE_ID;
  /* Copy Software Major Version */
  versioninfo->sw_major_version = CSM_SW_MAJOR_VERSION;
  /* Copy Software Minor Version */
  versioninfo->sw_minor_version = CSM_SW_MINOR_VERSION;
  /* Copy Software Patch Version */
  versioninfo->sw_patch_version = CSM_SW_PATCH_VERSION;
  /* polyspace-end MISRA-C3:D4.14,18.1,D4.1 RTE:IDP */

  #if (CSM_DEV_ERROR_DETECT == STD_ON)
  } /* If no development error has occurred */
  #endif
}
#endif /* (CSM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name       : Csm_MainFunction                                     **
**                                                                            **
** Service ID          : 0x01                                                 **
**                                                                            **
** Description         : This API is called cyclically to process the         **
**                       requested services.                                  **
**                                                                            **
** Re-entrancy         : Non Reentrant                                        **
**                                                                            **
** Input Parameters    : None                                                 **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** InOut Parameters    : None                                                 **
**                                                                            **
** Return parameter    : None                                                 **
**                                                                            **
** Preconditions       : The CSM module must be initialized before            **
**                       call of this API                                     **
**                                                                            **
** Remarks             : Global Variable(s): Csm_GddFunctionStack             **
**                                                                            **
**                       Function(s) invoked:                                 **
**                       SchM_Enter_Csm_FUNCTION_PTR_PROTECTION,              **
**                       SchM_Exit_Csm_FUNCTION_PTR_PROTECTION                **
**                       Csm_CheckTaskStatus                                  **
*******************************************************************************/
void Csm_MainFunction(void)
{
  SchM_Enter_Csm_FUNCTION_PTR_PROTECTION();

  if (Csm_GddFunctionStack.ucTop > CSM_ZERO)
  {
    SchM_Exit_Csm_FUNCTION_PTR_PROTECTION();

    /* Check the state of OsTask_BSW_BG_Csm*/
    if (E_OK == Csm_CheckTaskStatus(OsTask_BSW_BG_Csm))
    {
      /* OsTask_BSW_BG_Csm is suspended
         Csm BG Task can be activate for async job */
      SchM_ActMainFunction_Csm_BswITP_Csm_TriggerPointWorker();
    }
  }
  else
  {
    SchM_Exit_Csm_FUNCTION_PTR_PROTECTION();
  }
}

void Csm_Worker(void)
{
  uint8 LucIndex;
  Csm_FunctionStackType LddFunctionStack;

  /* Initialize local stack */
  (void)memset((void*)&LddFunctionStack, 0x00, sizeof(LddFunctionStack));

  SchM_Enter_Csm_FUNCTION_PTR_PROTECTION();

  LddFunctionStack.ucTop = CSM_ZERO;

  if ((Csm_GddFunctionStack.ucTop > CSM_ZERO)
    && (Csm_GddFunctionStack.ucTop < CSM_STACK_MAXSIZE))
  {
    for (LucIndex = CSM_ZERO; LucIndex < Csm_GddFunctionStack.ucTop; LucIndex++)
    {
      LddFunctionStack.paaFunctionPtr[LucIndex]
        = Csm_GddFunctionStack.paaFunctionPtr[LucIndex];
      Csm_GddFunctionStack.paaFunctionPtr[LucIndex] = NULL_PTR;
    }

    LddFunctionStack.ucTop = Csm_GddFunctionStack.ucTop;
    Csm_GddFunctionStack.ucTop = CSM_ZERO;
  }

  SchM_Exit_Csm_FUNCTION_PTR_PROTECTION();

  if (LddFunctionStack.ucTop > CSM_ZERO)
  {
    for (LucIndex = CSM_ZERO; LucIndex < LddFunctionStack.ucTop; LucIndex++)
    {
      if ((LddFunctionStack.paaFunctionPtr[LucIndex]) != NULL_PTR)
      {
        LddFunctionStack.paaFunctionPtr[LucIndex]();
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Csm_CheckTaskStatus                                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : Check the Task status suspended or not              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Task Id                                             **
**                                                                            **
** InOut parameter      : N/A                                                 **
**                                                                            **
** Output Parameters    : N/A                                                 **
**                                                                            **
** Return parameter     : E_OK (Suspended), E_NOT_OK (Not Suspended)          **
**                                                                            **
** Preconditions        : N/A                                                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                          GetTaskState,                                     **
**                          ActivateTask                                      **
*******************************************************************************/
static FUNC(StatusType, CSM_CODE)Csm_CheckTaskStatus(TaskType TaskId)
{
  StatusType LddError = E_NOT_OK;
  TaskStateType LddTaskState = RUNNING;

  LddError = GetTaskState(TaskId, &LddTaskState);

  if ((LddError == E_OK)
    && (LddTaskState == SUSPENDED))
  {
    LddError = E_OK;
  }
  else
  {
    LddError = E_NOT_OK;
  }
  
  return LddError;
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
