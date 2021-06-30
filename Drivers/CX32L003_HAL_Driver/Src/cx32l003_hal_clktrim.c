/**
  ******************************************************************************
  * @file    cx32l003_hal_clktrim.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   CLKTRIM HAL module driver
  *          This file provides firmware functions to manage the following 
  *          functionalities of the CLKTRIM peripheral:
  *           + CLKTRIM Initialization	
  *           + CLKTRIM Enable
  @verbatim
  ==============================================================================
                      ##### CLKTRIM Generic features #####
  ==============================================================================
  [..] The CLKTRIM features include:
       (#) Monitor system operating clock.
       (#) Calibrate internal clock.			 
  @endverbatim
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"


/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @defgroup CLKTRIM CLKTRIM
  * @brief CLKTRIM HAL module driver
  * @{
  */
#ifdef HAL_CLKTRIM_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/** @defgroup CLKTRIM_Private_Functions CLKTRIM Private Functions
  * @{
  */
static void CLKTRIM_SetConfig(CLKTRIM_HandleTypeDef *hclktrim);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup CLKTRIM_Exported_Functions CLKTRIM Exported Functions
  * @{
  */

/** @defgroup CLKTRIM_Exported_Functions_Group CLKTRIM functions 
 *  @brief    CLKTRIM functions 
 *
@verbatim 
  ==============================================================================
              ##### CLKTRIM functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the CLKTRIM.
    (+) De-initialize the CLKTRIM.
    (+) Enable the CLKTRIM.
    (+) Disable the CLKTRIM and interrupt.
    (+) Enable the CLKTRIM and interrupt.

@endverbatim
  * @{
  */
	
/**
  * @brief  Initializes the CLKTRIM Unit according to the specified
  *         parameters in the CLKTRIM_HandleTypeDef and create the associated handle.
  * @note no comment
  * @param  hclktrim : CLKTRIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CLKTRIM_Init(CLKTRIM_HandleTypeDef *hclktrim)
{
  /* Check the CLKTRIM handle allocation */
  if(hclktrim == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_CLKTRIM_INSTANCE(hclktrim->Instance));

  if(hclktrim->State == HAL_CLKTRIM_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hclktrim->Lock = HAL_UNLOCKED;
		
    /* Init the low level hardware : CLOCK, NVIC */
    HAL_CLKTRIM_MspInit(hclktrim);
  }

  /* Set the CLKTRIM state */
  hclktrim->State= HAL_CLKTRIM_STATE_BUSY;

  /* Set the CLKTRIM configuration */
  CLKTRIM_SetConfig(hclktrim);
	
  /* Initialize the CLKTRIM state*/
  hclktrim->State= HAL_CLKTRIM_STATE_READY;

  return HAL_OK;
}

	
/**
  * @brief  DeInitializes the CLKTRIM peripheral 
  * @param  hclktrim : CLKTRIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CLKTRIM_DeInit(CLKTRIM_HandleTypeDef *hclktrim)
{
  /* Check the parameters */
  assert_param(IS_CLKTRIM_INSTANCE(hclktrim->Instance));

  hclktrim->State = HAL_CLKTRIM_STATE_BUSY;
	
  /* Disable CLKTRIM Clock*/	
  __HAL_CLKTRIM_CLOCK_DISABLE(hclktrim);	
	
	/* Reset clktrim configuration */		
	CLEAR_BIT(hclktrim->Instance->CR, CLKTRIM_CR_ALL_Msk);	
	
  /* DeInit the low level hardware: CLOCK, NVIC */
  HAL_CLKTRIM_MspDeInit(hclktrim);

  /* Change CLKTRIM state */
  hclktrim->State = HAL_CLKTRIM_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hclktrim);

  return HAL_OK;
}


/**
  * @brief  Enable the CLKTRIM, start calibration or clock monitor.
  * @param  hclktrim : CLKTRIM handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_CLKTRIM_Enable(CLKTRIM_HandleTypeDef *hclktrim)
{
  /* Check the parameters */
  assert_param(IS_CLKTRIM_INSTANCE(hclktrim->Instance));

  /* Set the CLKTRIM state */
  hclktrim->State= HAL_CLKTRIM_STATE_BUSY;
	
  /* Start the clktrim monitor or calibration*/	
  __HAL_CLKTRIM_START(hclktrim);
	
  /* Change the CLKTRIM state*/
  hclktrim->State= HAL_CLKTRIM_STATE_READY;
	
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Enable the CLKTRIM and interrupt and start calibration or clock monitor.
  * @param  hclktrim : CLKTRIM handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_CLKTRIM_Enable_IT(CLKTRIM_HandleTypeDef *hclktrim)
{
  /* Check the parameters */
  assert_param(IS_CLKTRIM_INSTANCE(hclktrim->Instance));

  /* Set the CLKTRIM state */
  hclktrim->State= HAL_CLKTRIM_STATE_BUSY;
	
  /* Enable the clktrim interrupt*/		
	__HAL_CLKTRIM_ENABLE_IT(hclktrim);
	
  /* Start the clktrim monitor or calibration*/	
  __HAL_CLKTRIM_START(hclktrim);
	
  /* Change the CLKTRIM state*/
  hclktrim->State= HAL_CLKTRIM_STATE_READY;
	
  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Disable the CLKTRIM.
  * @param  hclktrim : CLKTRIM handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_CLKTRIM_Disable(CLKTRIM_HandleTypeDef *hclktrim)
{
  /* Check the parameters */
  assert_param(IS_CLKTRIM_INSTANCE(hclktrim->Instance));

  /* Set the CLKTRIM state */
  hclktrim->State= HAL_CLKTRIM_STATE_BUSY;
	
  /* Disable the clktrim interrupt*/		
	__HAL_CLKTRIM_DISABLE_IT(hclktrim);
	
  /* Disable the clktrim*/	
  __HAL_CLKTRIM_STOP(hclktrim);
	
  /* Change the CLKTRIM state*/
  hclktrim->State= HAL_CLKTRIM_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Initializes the CLKTRIM MSP.
  * @param  hclktrim : CLKTRIM handle
  * @retval None
  */
__weak void HAL_CLKTRIM_MspInit(CLKTRIM_HandleTypeDef *hclktrim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hclktrim);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CLKTRIM_MspInit could be implemented in the user file
   */
}


/**
  * @brief  DeInitializes CLKTRIM MSP.
  * @param  hclktrim : CLKTRIM handle
  * @retval None
  */
__weak void HAL_CLKTRIM_MspDeInit(CLKTRIM_HandleTypeDef *hclktrim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hclktrim);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_CLKTRIM_MspDeInit could be implemented in the user file
   */
}

/**
  * @}
  */ /* End of group CLKTRIM_Exported_Functions_Group */


/**
  * @}
  */ /* End of group CLKTRIM_Exported_Functions */


/* Private functions ---------------------------------------------------------*/

/** @addtogroup CLKTRIM_Private_Functions
  * @{
  */

/**
  * @brief  CLKTRIM configuration
  * @param  CLKTRIM : CLKTRIM periheral
  * @param  Structure : CLKTRIM configuration structure
  * @retval None
  */
static void CLKTRIM_SetConfig(CLKTRIM_HandleTypeDef *hclktrim)
{	
	/* Reset clktrim configuration */		
	CLEAR_BIT(hclktrim->Instance->CR, CLKTRIM_CR_ALL_Msk);
	SET_BIT(hclktrim->Instance->CR, hclktrim->Init.ReferClockSel | hclktrim->Init.MonitorCalClockSel);
	
	__HAL_CLKTRIM_CLOCK_ENABLE(hclktrim);
	WRITE_REG(hclktrim->Instance->REFCON, hclktrim->Init.MonitorInterval);
	WRITE_REG(hclktrim->Instance->CALCON, hclktrim->Init.MonitorOverflowTime);	
	__HAL_CLKTRIM_MONITOR_ENABLE(hclktrim);

}


/**
  * @}
	*/ /* End of group CLKTRIM_Private_Functions */

#endif /* HAL_CLKTRIM_MODULE_ENABLED */

/**
  * @}
  */ /* End of group CLKTRIM */

/**
  * @}
  */ /* group CX32L003_HAL_Driver */
