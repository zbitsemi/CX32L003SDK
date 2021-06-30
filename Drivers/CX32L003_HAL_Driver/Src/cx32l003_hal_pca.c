/**
  ******************************************************************************
  * @file    cx32l003_hal_pca.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   PCA HAL module driver
  *          This file provides firmware functions to manage the following 
  *          functionalities of the PCA peripheral:
  *           + Pca Initialization
  *           + Pca Start
  *           + Pca Start Interruption
  @verbatim
  ==============================================================================
                  ##### PCA Generic features #####
  ==============================================================================
  [..] The Timer features include:
       (#) up to 5 channel 16bit input capture module.
  @endverbatim
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @defgroup PCA PCA
  * @brief PCA HAL module driver
  * @{
  */
#ifdef HAL_PCA_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/** @defgroup PCA_Private_Functions PCA Private Functions
  * @{
  */
static void PCA_Base_SetConfig(PCA_TypeDef *PCAx, PCA_Base_InitTypeDef *Structure);
static void PCA_TI0_SetConfig(PCA_TypeDef *PCAx, uint32_t PCA_ICPolarity);
static void PCA_TI1_SetConfig(PCA_TypeDef *PCAx, uint32_t PCA_ICPolarity);
static void PCA_TI2_SetConfig(PCA_TypeDef *PCAx, uint32_t PCA_ICPolarity);
static void PCA_TI3_SetConfig(PCA_TypeDef *PCAx, uint32_t PCA_ICPolarity);
static void PCA_TI4_SetConfig(PCA_TypeDef *PCAx, uint32_t PCA_ICPolarity);

static void PCA_OC0_SetConfig(PCA_TypeDef *PCAx, PCA_OC_InitTypeDef *OC_Config);
static void PCA_OC1_SetConfig(PCA_TypeDef *PCAx, PCA_OC_InitTypeDef *OC_Config);
static void PCA_OC2_SetConfig(PCA_TypeDef *PCAx, PCA_OC_InitTypeDef *OC_Config);
static void PCA_OC3_SetConfig(PCA_TypeDef *PCAx, PCA_OC_InitTypeDef *OC_Config);
static void PCA_OC4_SetConfig(PCA_TypeDef *PCAx, PCA_OC_InitTypeDef *OC_Config);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup PCA_Exported_Functions PCA Exported Functions
  * @{
  */

/** @defgroup PCA_Exported_Functions_Group Pca Base functions 
 *  @brief    Pca base functions 
 *
@verbatim 
  ==============================================================================
              ##### Pca Base functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the Pca.
    (+) De-initialize the Pca.
    (+) Start the Pca.
    (+) Stop the Pca.
    (+) Start the Pca and enable interrupt.
    (+) Stop the Pca and disable interrupt.

@endverbatim
  * @{
  */
	
/**
  * @brief  Initializes the PCA Unit basic function according to the specified parameters 
	*					in the PCA_HandleTypeDef and create the associated handle.
  * @note no comment
  * @param  hpca : PCA handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCA_Base_Init(PCA_HandleTypeDef *hpca)
{
  /* Check the PCA handle allocation */
  if(hpca == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  if(hpca->State == HAL_PCA_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hpca->Lock = HAL_UNLOCKED;
		
    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_PCA_Base_MspInit(hpca);
  }

  /* Set the PCA state */
  hpca->State= HAL_PCA_STATE_BUSY;

  /* Set the Pca configuration */
  PCA_Base_SetConfig(hpca->Instance, &hpca->Init);

  /* Initialize the PCA state*/
  hpca->State= HAL_PCA_STATE_READY;

  return HAL_OK;
}


/**
  * @brief  DeInitializes the PCA peripheral 
  * @param  hpca : PCA handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCA_Base_DeInit(PCA_HandleTypeDef *hpca)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  hpca->State = HAL_PCA_STATE_BUSY;

  /* Stop PCA */	
  __HAL_PCA_DISABLE(hpca);

  /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
  HAL_PCA_Base_MspDeInit(hpca);

  /* Change PCA state */
  hpca->State = HAL_PCA_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hpca);

  return HAL_OK;
}


/**
  * @brief  Initializes the PCA Unit input capture function according to the specified parameters 
	*					in the PCA_HandleTypeDef and create the associated handle.
  * @note no comment
  * @param  hpca : PCA handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCA_IC_Init(PCA_HandleTypeDef *hpca)
{
  /* Check the PCA handle allocation */
  if(hpca == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  if(hpca->State == HAL_PCA_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hpca->Lock = HAL_UNLOCKED;
    
    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_PCA_IC_MspInit(hpca);
  }
	
  /* Set the PCA state */
  hpca->State= HAL_PCA_STATE_BUSY;

  /* Init the PCA for the input capture */
  PCA_Base_SetConfig(hpca->Instance, &hpca->Init);

  /* Initialize the PCA state*/
  hpca->State= HAL_PCA_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  DeInitializes the PCA peripheral 
  * @param  hpca : PCA handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCA_IC_DeInit(PCA_HandleTypeDef *hpca)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  hpca->State = HAL_PCA_STATE_BUSY;

  /* Disable the PCA Peripheral Clock */
  __HAL_PCA_DISABLE(hpca);

  /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
  HAL_PCA_IC_MspDeInit(hpca);

  /* Change PCA state */
  hpca->State = HAL_PCA_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hpca);

  return HAL_OK;
}


/**
  * @brief  Initializes the PCA Unit output compare function according to the specified parameters 
	*					in the PCA_HandleTypeDef and create the associated handle.
  * @note no comment
  * @param  hpca : PCA handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCA_OC_Init(PCA_HandleTypeDef *hpca)
{
  /* Check the PCA handle allocation */
  if(hpca == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  if(hpca->State == HAL_PCA_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hpca->Lock = HAL_UNLOCKED;
    
    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_PCA_OC_MspInit(hpca);
  }
	
  /* Set the PCA state */
  hpca->State= HAL_PCA_STATE_BUSY;

  /* Init the PCA for the input capture */
  PCA_Base_SetConfig(hpca->Instance, &hpca->Init);

  /* Initialize the PCA state*/
  hpca->State= HAL_PCA_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  DeInitializes the PCA peripheral 
  * @param  hpca : PCA handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCA_OC_DeInit(PCA_HandleTypeDef *hpca)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  hpca->State = HAL_PCA_STATE_BUSY;

  /* Disable the PCA Peripheral Clock */
  __HAL_PCA_DISABLE(hpca);

  /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
  HAL_PCA_OC_MspDeInit(hpca);

  /* Change PCA state */
  hpca->State = HAL_PCA_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hpca);

  return HAL_OK;
}


/**
  * @brief  Starts the PCA generation.
  * @param  hpca : PCA handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_PCA_Start(PCA_HandleTypeDef *hpca)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  /* Set the PCA state */
  hpca->State= HAL_PCA_STATE_BUSY;
	
  /* Start the pca*/	
  __HAL_PCA_ENABLE(hpca);

  /* Change the PCA state*/
  hpca->State= HAL_PCA_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Stops the PCA generation.
  * @param  hpca : PCA handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_PCA_Stop(PCA_HandleTypeDef *hpca)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  /* Set the PCA state */
  hpca->State= HAL_PCA_STATE_BUSY;
	
  /* Stop pca */
  __HAL_PCA_DISABLE(hpca);

  /* Change the PCA state*/
  hpca->State= HAL_PCA_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Starts the PCA generation in interrupt mode.
  * @param  hpca : PCA handle
  * @param  interrupt: specifies the PCA interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg PCA_IT_CC0: Capture/Compare 0 interrupt	
  *            @arg PCA_IT_CC1: Capture/Compare 1 interrupt
  *            @arg PCA_IT_CC2: Capture/Compare 2 interrupt
  *            @arg PCA_IT_CC3: Capture/Compare 3 interrupt
  *            @arg PCA_IT_CC4: Capture/Compare 4 interrupt	
  *            @arg PCA_IT_OVERFLOW: Overflow interrupt
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_PCA_Start_IT(PCA_HandleTypeDef *hpca, uint32_t intid)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));
	
  /* Enable the PCA interrupt */
  __HAL_PCA_ENABLE_IT(hpca, intid);

  /* start the Peripheral */
  __HAL_PCA_ENABLE(hpca);

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Stops the PCA generation in interrupt mode.
  * @param  hpca : PCA handle
  * @param  interrupt: specifies the PCA interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg PCA_IT_CC0: Capture/Compare 0 interrupt	
  *            @arg PCA_IT_CC1: Capture/Compare 1 interrupt
  *            @arg PCA_IT_CC2: Capture/Compare 2 interrupt
  *            @arg PCA_IT_CC3: Capture/Compare 3 interrupt
  *            @arg PCA_IT_CC4: Capture/Compare 4 interrupt	
  *            @arg PCA_IT_OVERFLOW: Overflow interrupt
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_PCA_Stop_IT(PCA_HandleTypeDef *hpca, uint32_t intid)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));
	
  /* Disable the PCA interrupt */
  __HAL_PCA_DISABLE_IT(hpca, intid);

  /* Stop pca */
  __HAL_PCA_DISABLE(hpca);

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Starts the PCA output compare generation.
  * @param  hpca : PCA handle
  * @param  __CHANNEL__ : PCA Channel associated with the capture compare register
  *          This parameter can be one of the following values:
  *            @arg PCA_CHANNEL_0: Capture/Compare channel0	
  *            @arg PCA_CHANNEL_1: Capture/Compare channel1
  *            @arg PCA_CHANNEL_2: Capture/Compare channel2
  *            @arg PCA_CHANNEL_3: Capture/Compare channel3
  *            @arg PCA_CHANNEL_4: Capture/Compare channel4
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_PCA_OC_Start(PCA_HandleTypeDef *hpca, uint32_t Channel)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  /* Set the PCA state */
  hpca->State= HAL_PCA_STATE_BUSY;
	
	switch(Channel)
	{
		case PCA_CHANNEL_0:
			PCA->POCR |= PCA_POCR_POE0;
			break;
		case PCA_CHANNEL_1:
			PCA->POCR |= PCA_POCR_POE1;
			break;
		case PCA_CHANNEL_2:
			PCA->POCR |= PCA_POCR_POE2;
			break;
		case PCA_CHANNEL_3:
			PCA->POCR |= PCA_POCR_POE3;
			break;
		case PCA_CHANNEL_4:
			PCA->POCR |= PCA_POCR_POE4;
			break;	
		default:
			PCA->POCR = PCA->POCR;
	}	
	
  /* Start the pca*/	
  __HAL_PCA_ENABLE(hpca);

  /* Change the PCA state*/
  hpca->State= HAL_PCA_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Stops the PCA output compare generation.
  * @param  hpca : PCA handle
  * @param  __CHANNEL__ : PCA Channel associated with the capture compare register
  *          This parameter can be one of the following values:
  *            @arg PCA_CHANNEL_0: Capture/Compare channel0	
  *            @arg PCA_CHANNEL_1: Capture/Compare channel1
  *            @arg PCA_CHANNEL_2: Capture/Compare channel2
  *            @arg PCA_CHANNEL_3: Capture/Compare channel3
  *            @arg PCA_CHANNEL_4: Capture/Compare channel4
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_PCA_OC_Stop(PCA_HandleTypeDef *hpca, uint32_t Channel)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  /* Set the PCA state */
  hpca->State= HAL_PCA_STATE_BUSY;
	
	switch(Channel)
	{
		case PCA_CHANNEL_0:
			PCA->POCR &= ~PCA_POCR_POE0;
			break;
		case PCA_CHANNEL_1:
			PCA->POCR &= ~PCA_POCR_POE1;
			break;
		case PCA_CHANNEL_2:
			PCA->POCR &= ~PCA_POCR_POE2;
			break;
		case PCA_CHANNEL_3:
			PCA->POCR &= ~PCA_POCR_POE3;
			break;
		case PCA_CHANNEL_4:
			PCA->POCR &= ~PCA_POCR_POE4;
			break;	
		default:
			PCA->POCR = PCA->POCR;
	}	
	
  /* Stop the pca*/	
  __HAL_PCA_DISABLE(hpca);

  /* Change the PCA state*/
  hpca->State= HAL_PCA_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Starts the PCA output compare generation and enable interrupt.
  * @param  hpca : PCA handle
  * @param  __CHANNEL__ : PCA Channel associated with the capture compare register
  *          This parameter can be one of the following values:
  *            @arg PCA_CHANNEL_0: Capture/Compare channel0	
  *            @arg PCA_CHANNEL_1: Capture/Compare channel1
  *            @arg PCA_CHANNEL_2: Capture/Compare channel2
  *            @arg PCA_CHANNEL_3: Capture/Compare channel3
  *            @arg PCA_CHANNEL_4: Capture/Compare channel4
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_PCA_OC_Start_IT(PCA_HandleTypeDef *hpca, uint32_t Channel)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  /* Set the PCA state */
  hpca->State= HAL_PCA_STATE_BUSY;
	
	switch(Channel)
	{
		case PCA_CHANNEL_0:
			PCA->POCR |= PCA_POCR_POE0;
			__HAL_PCA_ENABLE_IT(hpca, PCA_IT_CC0);				
			break;
		case PCA_CHANNEL_1:
			PCA->POCR |= PCA_POCR_POE1;
			__HAL_PCA_ENABLE_IT(hpca, PCA_IT_CC1);			
			break;
		case PCA_CHANNEL_2:
			PCA->POCR |= PCA_POCR_POE2;
			__HAL_PCA_ENABLE_IT(hpca, PCA_IT_CC2);		
			break;
		case PCA_CHANNEL_3:
			PCA->POCR |= PCA_POCR_POE3;
			__HAL_PCA_ENABLE_IT(hpca, PCA_IT_CC3);			
			break;
		case PCA_CHANNEL_4:
			PCA->POCR |= PCA_POCR_POE4;
			__HAL_PCA_ENABLE_IT(hpca, PCA_IT_CC4);			
			break;	
		default:
			PCA->POCR = PCA->POCR;
	}	
	
  /* Start the pca*/	
  __HAL_PCA_ENABLE(hpca);

  /* Change the PCA state*/
  hpca->State= HAL_PCA_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Stops the PCA output compare generation and disable interrupt.
  * @param  hpca : PCA handle
  * @param  __CHANNEL__ : PCA Channel associated with the capture compare register
  *          This parameter can be one of the following values:
  *            @arg PCA_CHANNEL_0: Capture/Compare channel0	
  *            @arg PCA_CHANNEL_1: Capture/Compare channel1
  *            @arg PCA_CHANNEL_2: Capture/Compare channel2
  *            @arg PCA_CHANNEL_3: Capture/Compare channel3
  *            @arg PCA_CHANNEL_4: Capture/Compare channel4
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_PCA_OC_Stop_IT(PCA_HandleTypeDef *hpca, uint32_t Channel)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  /* Set the PCA state */
  hpca->State= HAL_PCA_STATE_BUSY;
	
	switch(Channel)
	{
		case PCA_CHANNEL_0:
			PCA->POCR &= ~PCA_POCR_POE0;
			__HAL_PCA_DISABLE_IT(hpca, PCA_IT_CC0);			
			break;
		case PCA_CHANNEL_1:
			PCA->POCR &= ~PCA_POCR_POE1;
			__HAL_PCA_DISABLE_IT(hpca, PCA_IT_CC1);				
			break;
		case PCA_CHANNEL_2:
			PCA->POCR &= ~PCA_POCR_POE2;
			__HAL_PCA_DISABLE_IT(hpca, PCA_IT_CC2);				
			break;
		case PCA_CHANNEL_3:
			PCA->POCR &= ~PCA_POCR_POE3;
			__HAL_PCA_DISABLE_IT(hpca, PCA_IT_CC3);		
			break;
		case PCA_CHANNEL_4:
			PCA->POCR &= ~PCA_POCR_POE4;
			__HAL_PCA_DISABLE_IT(hpca, PCA_IT_CC4);				
			break;	
		default:
			PCA->POCR = PCA->POCR;
	}	
	
  /* Stop the pca*/	
  __HAL_PCA_DISABLE(hpca);

  /* Change the PCA state*/
  hpca->State= HAL_PCA_STATE_READY;

  /* Return function status */
  return HAL_OK;
}



/**
  * @brief  Initializes the PCA basic MSP.
  * @param  hpca : PCA handle
  * @retval None
  */
__weak void HAL_PCA_Base_MspInit(PCA_HandleTypeDef *hpca)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpca);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCA_Base_MspInit could be implemented in the user file
   */
}


/**
  * @brief  DeInitializes PCA basic MSP.
  * @param  hpca : PCA handle
  * @retval None
  */
__weak void HAL_PCA_Base_MspDeInit(PCA_HandleTypeDef *hpca)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpca);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCA_Base_MspDeInit could be implemented in the user file
   */
}


/**
  * @brief  Initializes the PCA Input Capture MSP.
  * @param  hpca : PCA handle
  * @retval None
  */
__weak void HAL_PCA_IC_MspInit(PCA_HandleTypeDef *hpca)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpca);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCA_IC_MspInit could be implemented in the user file
   */
}


/**
  * @brief  DeInitializes PCA Input Capture MSP.
  * @param  hpca : PCA handle
  * @retval None
  */
__weak void HAL_PCA_IC_MspDeInit(PCA_HandleTypeDef *hpca)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpca);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCA_IC_MspDeInit could be implemented in the user file
   */
}


/**
  * @brief  Initializes the PCA Output Compare MSP.
  * @param  hpca : PCA handle
  * @retval None
  */
__weak void HAL_PCA_OC_MspInit(PCA_HandleTypeDef *hpca)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpca);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCA_OC_MspInit could be implemented in the user file
   */
}


/**
  * @brief  DeInitializes PCA Output Compare MSP.
  * @param  hpca : PCA handle
  * @retval None
  */
__weak void HAL_PCA_OC_MspDeInit(PCA_HandleTypeDef *hpca)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpca);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCA_OC_MspDeInit could be implemented in the user file
   */
}


/**
  * @brief  This function handles PCA interrupts requests.
  * @param  hpca : PCA handle
  * @retval None
  */
void HAL_PCA_IRQHandler(PCA_HandleTypeDef *hpca)
{
  /* PCA input capture event */
  if(__HAL_PCA_GET_FLAG(hpca, PCA_FLAG_CC0) != RESET)	
  {
    if(__HAL_PCA_GET_IT_SOURCE(hpca, PCA_IT_CC0) !=RESET)	
    {
      __HAL_PCA_CLEAR_IT(hpca, PCA_FLAG_CC0);
			if((hpca->Instance->CCAPM0 & PCA_CCAPM0_ECOM) == PCA_CCAPM0_ECOM)
				HAL_PCA_OutputCompareCallback(hpca);
			else
				HAL_PCA_InputCaptureCallback(hpca);
    }
  }
	
  if(__HAL_PCA_GET_FLAG(hpca, PCA_FLAG_CC1) != RESET)	
  {
    if(__HAL_PCA_GET_IT_SOURCE(hpca, PCA_IT_CC1) !=RESET)	
    {
      __HAL_PCA_CLEAR_IT(hpca, PCA_FLAG_CC1);
			if((hpca->Instance->CCAPM1 & PCA_CCAPM1_ECOM) == PCA_CCAPM1_ECOM)
				HAL_PCA_OutputCompareCallback(hpca);
			else			
				HAL_PCA_InputCaptureCallback(hpca);
    }
  }	
	
  if(__HAL_PCA_GET_FLAG(hpca, PCA_FLAG_CC2) != RESET)	
  {
    if(__HAL_PCA_GET_IT_SOURCE(hpca, PCA_IT_CC2) !=RESET)	
    {
      __HAL_PCA_CLEAR_IT(hpca, PCA_FLAG_CC2);
			if((hpca->Instance->CCAPM2 & PCA_CCAPM2_ECOM) == PCA_CCAPM2_ECOM)
				HAL_PCA_OutputCompareCallback(hpca);
			else						
				HAL_PCA_InputCaptureCallback(hpca);
    }
  }	
	
  if(__HAL_PCA_GET_FLAG(hpca, PCA_FLAG_CC3) != RESET)	
  {
    if(__HAL_PCA_GET_IT_SOURCE(hpca, PCA_IT_CC3) !=RESET)	
    {
      __HAL_PCA_CLEAR_IT(hpca, PCA_FLAG_CC3);
			if((hpca->Instance->CCAPM3 & PCA_CCAPM3_ECOM) == PCA_CCAPM3_ECOM)
				HAL_PCA_OutputCompareCallback(hpca);
			else				
				HAL_PCA_InputCaptureCallback(hpca);
    }
  }	
	
  if(__HAL_PCA_GET_FLAG(hpca, PCA_FLAG_CC4) != RESET)	
  {
    if(__HAL_PCA_GET_IT_SOURCE(hpca, PCA_IT_CC4) !=RESET)	
    {
      __HAL_PCA_CLEAR_IT(hpca, PCA_FLAG_CC4);
			if((hpca->Instance->CCAPM4 & PCA_CCAPM4_ECOM) == PCA_CCAPM4_ECOM)
				HAL_PCA_OutputCompareCallback(hpca);
			else				
				HAL_PCA_InputCaptureCallback(hpca);
    }
  }	
  /* PCA overflow event */	
  if(__HAL_PCA_GET_FLAG(hpca, PCA_FLAG_OVERFLOW) != RESET)	
  {
    if(__HAL_PCA_GET_IT_SOURCE(hpca, PCA_IT_OVERFLOW) !=RESET)	
    {
      __HAL_PCA_CLEAR_IT(hpca, PCA_FLAG_OVERFLOW);
      HAL_PCA_OverflowCallback(hpca);
    }
  }	
}


/**
  * @brief  Initializes the PCA Input Capture Channels according to the specified
  *         parameters in the PCA_IC_InitTypeDef.
  * @param  hpca : PCA IC handle
  * @param  sConfig : PCA Input Capture configuration structure
  * @param  Channel : PCA Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg PCA_CHANNEL_0: PCA Channel 0 selected
  *            @arg PCA_CHANNEL_1: PCA Channel 1 selected
  *            @arg PCA_CHANNEL_2: PCA Channel 2 selected
  *            @arg PCA_CHANNEL_3: PCA Channel 3 selected
  *            @arg PCA_CHANNEL_4: PCA Channel 4 selected 
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCA_IC_ConfigChannel(PCA_HandleTypeDef *hpca, PCA_IC_InitTypeDef* sConfig, uint32_t Channel)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  __HAL_LOCK(hpca);

  hpca->State = HAL_PCA_STATE_BUSY;

  if (Channel == PCA_CHANNEL_0)
  {
    /* TI0 Channel0 input capture configuration */
    PCA_TI0_SetConfig(hpca->Instance,
               sConfig->ICPolarity);
  }
  if (Channel == PCA_CHANNEL_1)
  {
    /* TI1 Channel1 input capture configuration */
    PCA_TI1_SetConfig(hpca->Instance,
               sConfig->ICPolarity);
  }
  if (Channel == PCA_CHANNEL_2)
  {
    /* TI2 Channel2 input capture configuration */
    PCA_TI2_SetConfig(hpca->Instance,
               sConfig->ICPolarity);
  }	
  if (Channel == PCA_CHANNEL_3)
  {
    /* TI3 Channel3 input capture configuration */
    PCA_TI3_SetConfig(hpca->Instance,
               sConfig->ICPolarity);
  }
  if (Channel == PCA_CHANNEL_4)
  {
    /* TI4 Channel4 input capture configuration */
    PCA_TI4_SetConfig(hpca->Instance,
               sConfig->ICPolarity);
  }

  hpca->State = HAL_PCA_STATE_READY;

  __HAL_UNLOCK(hpca);

  return HAL_OK;
}


/**
  * @brief  Initializes the PCA output compare Channels according to the specified
  *         parameters in the PCA_OC_InitTypeDef.
  * @param  hpca : PCA handle
  * @param  sConfig : PCA output compare configuration structure
  * @param  Channel : PCA Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg PCA_CHANNEL_0: PCA Channel 0 selected
  *            @arg PCA_CHANNEL_1: PCA Channel 1 selected
  *            @arg PCA_CHANNEL_2: PCA Channel 2 selected
  *            @arg PCA_CHANNEL_3: PCA Channel 3 selected
  *            @arg PCA_CHANNEL_4: PCA Channel 4 selected 
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCA_OC_ConfigChannel(PCA_HandleTypeDef *hpca, PCA_OC_InitTypeDef* sConfig, uint32_t Channel)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(hpca->Instance));

  __HAL_LOCK(hpca);

  hpca->State = HAL_PCA_STATE_BUSY;

  if (Channel == PCA_CHANNEL_0)
  {
    /* PCA Channel0 input capture configuration */
    PCA_OC0_SetConfig(hpca->Instance, sConfig);
  }
  if (Channel == PCA_CHANNEL_1)
  {
    /*PCA Channel1 input capture configuration */
    PCA_OC1_SetConfig(hpca->Instance, sConfig);
  }
  if (Channel == PCA_CHANNEL_2)
  {
    /* TI2 Channel2 input capture configuration */
    PCA_OC2_SetConfig(hpca->Instance, sConfig);
  }	
  if (Channel == PCA_CHANNEL_3)
  {
    /* TI3 Channel3 input capture configuration */
    PCA_OC3_SetConfig(hpca->Instance, sConfig);
  }
  if (Channel == PCA_CHANNEL_4)
  {
    /* TI4 Channel4 input capture configuration */
    PCA_OC4_SetConfig(hpca->Instance, sConfig);
  }

  hpca->State = HAL_PCA_STATE_READY;

  __HAL_UNLOCK(hpca);

  return HAL_OK;
}



/**
  * @brief  Configure the Channel0 (PCA Input capture).
  * @param  PCAx to select the PCA peripheral.
  * @param  PCA_ICPolarity : The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg PCA_ICPOLARITY_NONE
  *            @arg PCA_ICPOLARITY_RISING
  *            @arg PCA_ICPOLARITY_FALLING
  *            @arg PCA_ICPOLARITY_BOTHEDGE
  * @retval None
  */
static void PCA_TI0_SetConfig(PCA_TypeDef *PCAx, uint32_t PCA_ICPolarity)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(PCAx));	
	
	/* Select the Polarity */
	MODIFY_REG(PCAx->CCAPM0, PCA_CCAPM0_CAPP | PCA_CCAPM0_CAPN, PCA_ICPolarity);

}


/**
  * @brief  Configure the Channel1 (PCA Input capture).
  * @param  PCAx to select the PCA peripheral.
  * @param  PCA_ICPolarity : The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg PCA_ICPOLARITY_NONE
  *            @arg PCA_ICPOLARITY_RISING
  *            @arg PCA_ICPOLARITY_FALLING
  *            @arg PCA_ICPOLARITY_BOTHEDGE
  * @retval None
  */
static void PCA_TI1_SetConfig(PCA_TypeDef *PCAx, uint32_t PCA_ICPolarity)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(PCAx));	
	
	/* Select the Polarity */
	MODIFY_REG(PCAx->CCAPM1, PCA_CCAPM1_CAPP | PCA_CCAPM1_CAPN, PCA_ICPolarity);

}


/**
  * @brief  Configure the Channel2 (PCA Input capture).
  * @param  PCAx to select the PCA peripheral.
  * @param  PCA_ICPolarity : The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg PCA_ICPOLARITY_NONE
  *            @arg PCA_ICPOLARITY_RISING
  *            @arg PCA_ICPOLARITY_FALLING
  *            @arg PCA_ICPOLARITY_BOTHEDGE
  * @retval None
  */
static void PCA_TI2_SetConfig(PCA_TypeDef *PCAx, uint32_t PCA_ICPolarity)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(PCAx));	
	
	/* Select the Polarity */
	MODIFY_REG(PCAx->CCAPM2, PCA_CCAPM2_CAPP | PCA_CCAPM2_CAPN, PCA_ICPolarity);

}


/**
  * @brief  Configure the Channel3 (PCA Input capture).
  * @param  PCAx to select the PCA peripheral.
  * @param  PCA_ICPolarity : The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg PCA_ICPOLARITY_NONE
  *            @arg PCA_ICPOLARITY_RISING
  *            @arg PCA_ICPOLARITY_FALLING
  *            @arg PCA_ICPOLARITY_BOTHEDGE
  * @retval None
  */
static void PCA_TI3_SetConfig(PCA_TypeDef *PCAx, uint32_t PCA_ICPolarity)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(PCAx));	
	
	/* Select the Polarity */
	MODIFY_REG(PCAx->CCAPM3, PCA_CCAPM3_CAPP | PCA_CCAPM3_CAPN, PCA_ICPolarity);

}


/**
  * @brief  Configure the Channel4 (PCA Input capture).
  * @param  PCAx to select the PCA peripheral.
  * @param  PCA_ICPolarity : The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg PCA_ICPOLARITY_NONE
  *            @arg PCA_ICPOLARITY_RISING
  *            @arg PCA_ICPOLARITY_FALLING
  *            @arg PCA_ICPOLARITY_BOTHEDGE
  * @retval None
  */
static void PCA_TI4_SetConfig(PCA_TypeDef *PCAx, uint32_t PCA_ICPolarity)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(PCAx));	
	
	/* Select the Polarity */
	MODIFY_REG(PCAx->CCAPM4, PCA_CCAPM4_CAPP | PCA_CCAPM4_CAPN, PCA_ICPolarity);

}


/**
  * @brief  Input capture callback in non blocking mode 
  * @param  hpca : PCA handle
  * @retval None
  */
__weak void HAL_PCA_InputCaptureCallback(PCA_HandleTypeDef *hpca)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpca);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCA_InputCaptureCallback could be implemented in the user file
   */
}


/**
  * @brief  Output compare callback in non blocking mode 
  * @param  hpca : PCA handle
  * @retval None
  */
__weak void HAL_PCA_OutputCompareCallback(PCA_HandleTypeDef *hpca)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpca);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCA_OutputCompareCallback could be implemented in the user file
   */
}



/**
  * @brief  Pca Ouput Compare 0 configuration
  * @param  PCAx to select the PCA peripheral
  * @param  OC_Config : The ouput configuration structure
  * @retval None
  */
static void PCA_OC0_SetConfig(PCA_TypeDef *PCAx, PCA_OC_InitTypeDef *OC_Config)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(PCAx));	
	
	/* Enable output compare and toggle function */	
	MODIFY_REG(PCAx->CCAPM0, PCA_CCAPM0_ECOM | PCA_CCAPM0_MAT | PCA_CCAPM0_TOG | PCA_CCAPM0_PWM, OC_Config->CompareEnable | OC_Config->TogEnable | OC_Config->PwmEnable);
	
	/* Setting period */		
	WRITE_REG(PCAx->CCAP0H, OC_Config->Period);
}


/**
  * @brief  Pca Ouput Compare 1 configuration
  * @param  PCAx to select the PCA peripheral
  * @param  OC_Config : The ouput configuration structure
  * @retval None
  */
static void PCA_OC1_SetConfig(PCA_TypeDef *PCAx, PCA_OC_InitTypeDef *OC_Config)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(PCAx));	
	
	/* Enable output compare and toggle function */	
	MODIFY_REG(PCAx->CCAPM1, PCA_CCAPM1_ECOM | PCA_CCAPM1_MAT | PCA_CCAPM1_TOG | PCA_CCAPM1_PWM, OC_Config->CompareEnable | OC_Config->TogEnable | OC_Config->PwmEnable);
	
	/* Setting period */		
	WRITE_REG(PCAx->CCAP1H, OC_Config->Period);
}


/**
  * @brief  Pca Ouput Compare 2 configuration
  * @param  PCAx to select the PCA peripheral
  * @param  OC_Config : The ouput configuration structure
  * @retval None
  */
static void PCA_OC2_SetConfig(PCA_TypeDef *PCAx, PCA_OC_InitTypeDef *OC_Config)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(PCAx));	

	/* Enable output compare and toggle function */	
	MODIFY_REG(PCAx->CCAPM2, PCA_CCAPM2_ECOM | PCA_CCAPM2_MAT | PCA_CCAPM2_TOG | PCA_CCAPM2_PWM, OC_Config->CompareEnable | OC_Config->TogEnable | OC_Config->PwmEnable);
	
	/* Setting period */
	WRITE_REG(PCAx->CCAP2H, OC_Config->Period);
}


/**
  * @brief  Pca Ouput Compare 3 configuration
  * @param  PCAx to select the PCA peripheral
  * @param  OC_Config : The ouput configuration structure
  * @retval None
  */
static void PCA_OC3_SetConfig(PCA_TypeDef *PCAx, PCA_OC_InitTypeDef *OC_Config)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(PCAx));	
	
	/* Enable output compare and toggle function */	
	MODIFY_REG(PCAx->CCAPM3, PCA_CCAPM3_ECOM | PCA_CCAPM3_MAT | PCA_CCAPM3_TOG | PCA_CCAPM3_PWM, OC_Config->CompareEnable | OC_Config->TogEnable | OC_Config->PwmEnable);
	
	/* Setting period */		
	WRITE_REG(PCAx->CCAP3H, OC_Config->Period);
}


/**
  * @brief  Pca Ouput Compare 4 configuration
  * @param  PCAx to select the PCA peripheral
  * @param  OC_Config : The ouput configuration structure
  * @retval None
  */
static void PCA_OC4_SetConfig(PCA_TypeDef *PCAx, PCA_OC_InitTypeDef *OC_Config)
{
  /* Check the parameters */
  assert_param(IS_PCA_INSTANCE(PCAx));	
	
	/* Enable output compare and toggle function */	
	MODIFY_REG(PCAx->CCAPM4, PCA_CCAPM4_ECOM | PCA_CCAPM4_MAT | PCA_CCAPM4_TOG | PCA_CCAPM4_PWM, OC_Config->CompareEnable | OC_Config->TogEnable | OC_Config->PwmEnable);
	
	/* Setting period */
	WRITE_REG(PCAx->CCAP4H, OC_Config->Period);
}


/**
  * @brief  Overflow callback in non blocking mode 
  * @param  hpca : PCA handle
  * @retval None
  */
__weak void HAL_PCA_OverflowCallback(PCA_HandleTypeDef *hpca)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpca);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCA_OverflowCallback could be implemented in the user file
   */
}

/**
  * @}
  */ /* End of group PCA_Exported_Functions_Group */


/**
  * @}
  */ /* End of group PCA_Exported_Functions */


/* Private functions ---------------------------------------------------------*/

/** @addtogroup PCA_Private_Functions
  * @{
  */

/**
  * @brief  Pca basic configuration
  * @param  PCAx : PCA periheral
  * @param  Structure : PCA configuration structure
  * @retval None
  */
static void PCA_Base_SetConfig(PCA_TypeDef *PCAx, PCA_Base_InitTypeDef *Structure)
{
	/* Reset all PCA function */		
	PCAx->CR &= ~PCA_CR_CR;	
	PCAx->MOD &= ~(PCA_MOD_CFIE | PCA_MOD_CPS | PCA_MOD_CIDL);		
	PCAx->MOD = Structure->ClkSrcSel | Structure->RunInIdleMode;
	
}


/**
  * @}
	*/ /* End of group PCA_Private_Functions */

#endif /* HAL_PCA_MODULE_ENABLED */

/**
  * @}
  */ /* End of group PCA */

/**
  * @}
  */ /* group CX32L003_HAL_Driver */
