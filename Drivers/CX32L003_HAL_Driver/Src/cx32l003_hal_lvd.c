/**
  ******************************************************************************
  * @file    cx32l003_hal_lvd.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   LVD HAL module driver
  *          This file provides firmware functions to manage the following 
  *          functionalities of the LVD peripheral:
  *           + LVD Initialization	
  *           + LVD Enable
  @verbatim
  ==============================================================================
                      ##### LVD Generic features #####
  ==============================================================================
  [..] The LVD features include:
       (#) Low voltage detection for rising or falling compared with threshold 
					 voltage.
  @endverbatim
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"


/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @defgroup LVD LVD
  * @brief LVD HAL module driver
  * @{
  */
#ifdef HAL_LVD_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/** @defgroup LVD_Private_Functions LVD Private Functions
  * @{
  */
static void LVD_SetConfig(LVD_HandleTypeDef *hlvd);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup LVD_Exported_Functions LVD Exported Functions
  * @{
  */

/** @defgroup LVD_Exported_Functions_Group LVD functions 
 *  @brief    LVD functions 
 *
@verbatim 
  ==============================================================================
              ##### LVD functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the LVD.
    (+) De-initialize the LVD.
    (+) Enable the LVD.
    (+) Disable the LVD and interrupt.
    (+) Enable the LVD and interrupt.

@endverbatim
  * @{
  */
	
/**
  * @brief  Initializes the LVD Unit according to the specified
  *         parameters in the LVD_HandleTypeDef and create the associated handle.
  * @note no comment
  * @param  hlvd : LVD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LVD_Init(LVD_HandleTypeDef *hlvd)
{
  /* Check the LVD handle allocation */
  if(hlvd == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_LVD_INSTANCE(hlvd->Instance));

  if(hlvd->State == HAL_LVD_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hlvd->Lock = HAL_UNLOCKED;
		
    /* Init the low level hardware : CLOCK, NVIC */
    HAL_LVD_MspInit(hlvd);
  }

  /* Set the LVD state */
  hlvd->State= HAL_LVD_STATE_BUSY;

  /* Set the LVD configuration */
  LVD_SetConfig(hlvd);
	
  /* Initialize the LVD state*/
  hlvd->State= HAL_LVD_STATE_READY;

  return HAL_OK;
}

	
/**
  * @brief  DeInitializes the LVD peripheral 
  * @param  hlvd : LVD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LVD_DeInit(LVD_HandleTypeDef *hlvd)
{
  /* Check the parameters */
  assert_param(IS_LVD_INSTANCE(hlvd->Instance));

  hlvd->State = HAL_LVD_STATE_BUSY;
	
  /* Disable LVD */	
  __HAL_LVD_DISABLE(hlvd);	
	
	/* Reset lvd configuration */		
	CLEAR_BIT(hlvd->Instance->CR, LVD_CR_ALL_Msk);	
	
  /* DeInit the low level hardware: CLOCK, NVIC */
  HAL_LVD_MspDeInit(hlvd);

  /* Change LVD state */
  hlvd->State = HAL_LVD_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hlvd);

  return HAL_OK;
}


/**
  * @brief  Enable the LVD.
  * @param  hlvd : LVD handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_LVD_Enable(LVD_HandleTypeDef *hlvd)
{
  /* Check the parameters */
  assert_param(IS_LVD_INSTANCE(hlvd->Instance));

  /* Set the LVD state */
  hlvd->State= HAL_LVD_STATE_BUSY;
	
  /* Enable the lvd*/	
  __HAL_LVD_ENABLE(hlvd);
	
  /* Change the LVD state*/
  hlvd->State= HAL_LVD_STATE_READY;
	
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Enable the LVD and interrupt
  * @param  hlvd : LVD handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_LVD_Enable_IT(LVD_HandleTypeDef *hlvd)
{
  /* Check the parameters */
  assert_param(IS_LVD_INSTANCE(hlvd->Instance));

  /* Set the LVD state */
  hlvd->State= HAL_LVD_STATE_BUSY;
	
  /* Enable the lvd interrupt*/		
	__HAL_LVD_ENABLE_IT(hlvd);
	
  /* Enable the lvd*/	
  __HAL_LVD_ENABLE(hlvd);
	
  /* Change the LVD state*/
  hlvd->State= HAL_LVD_STATE_READY;
	
  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Disable the LVD.
  * @param  hlvd : LVD handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_LVD_Disable(LVD_HandleTypeDef *hlvd)
{
  /* Check the parameters */
  assert_param(IS_LVD_INSTANCE(hlvd->Instance));

  /* Set the LVD state */
  hlvd->State= HAL_LVD_STATE_BUSY;
	
  /* Disable the lvd interrupt*/		
	__HAL_LVD_DISABLE_IT(hlvd);
	
  /* Disable the lvd*/	
  __HAL_LVD_DISABLE(hlvd);
	
  /* Change the LVD state*/
  hlvd->State= HAL_LVD_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  This function handles LVD interrupts requests.
  * @param  htim : LVD handle
  * @retval None
  */
void HAL_LVD_IRQHandler(LVD_HandleTypeDef *hlvd)
{
  if(__HAL_LVD_GET_FLAG(hlvd) != RESET)
  {
    if(__HAL_LVD_GET_IT_SOURCE(hlvd) !=RESET)	
    {
      HAL_LVD_InterruptCallback(hlvd);	
			 __HAL_LVD_CLEAR_IT(hlvd);	
    }
  }
}


/**
  * @brief  Initializes the LVD MSP.
  * @param  hlvd : LVD handle
  * @retval None
  */
__weak void HAL_LVD_MspInit(LVD_HandleTypeDef *hlvd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlvd);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_LVD_MspInit could be implemented in the user file
   */
}


/**
  * @brief  DeInitializes LVD MSP.
  * @param  hlvd : LVD handle
  * @retval None
  */
__weak void HAL_LVD_MspDeInit(LVD_HandleTypeDef *hlvd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlvd);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_LVD_MspDeInit could be implemented in the user file
   */
}


/**
  * @brief  Interrupt callback in non blocking mode 
  * @param  htim : LVD handle
  * @retval None
  */
__weak void HAL_LVD_InterruptCallback(LVD_HandleTypeDef *hlvd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlvd);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_LPTIM_PeriodElapsedCallback could be implemented in the user file
   */

}


/**
  * @}
  */ /* End of group LVD_Exported_Functions_Group */


/**
  * @}
  */ /* End of group LVD_Exported_Functions */


/* Private functions ---------------------------------------------------------*/

/** @addtogroup LVD_Private_Functions
  * @{
  */

/**
  * @brief  LVD configuration
  * @param  LVD : LVD periheral
  * @param  Structure : LVD configuration structure
  * @retval None
  */
static void LVD_SetConfig(LVD_HandleTypeDef *hlvd)
{	
	/* Reset lvd configuration */		
	CLEAR_BIT(hlvd->Instance->CR, LVD_CR_ALL_Msk);
	SET_BIT(hlvd->Instance->CR, hlvd->Init.VoltageLevel | hlvd->Init.Action | hlvd->Init.TriggerSel);
	
	if(hlvd->Init.FltClkSel != LVD_FLTCLK_DISABLE)
	{
		SET_BIT(hlvd->Instance->CR, hlvd->Init.FltClkSel | hlvd->Init.FltNum);
		__HAL_LVD_ENABLE_DIGFLT(hlvd);	
	}
}


/**
  * @}
	*/ /* End of group LVD_Private_Functions */

#endif /* HAL_LVD_MODULE_ENABLED */

/**
  * @}
  */ /* End of group LVD */


/**
  * @}
  */ /* group CX32L003_HAL_Driver */
