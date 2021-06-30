/**
  ******************************************************************************
  * @file    cx32l003_hal_awk.c
  * @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   AWK HAL module driver
  *          This file provides firmware functions to manage the following 
  *          functionalities of the AWK peripheral:
  *           + AWK Initialization
  *           + AWK Start
  @verbatim
  ==============================================================================
                      ##### AWK Generic features #####
  ==============================================================================
  [..] The AWK features include:
       (#) 8-bit auto-reload counter.
  @endverbatim
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"


/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @defgroup AWK AWK
  * @brief AWK HAL module driver
  * @{
  */

#ifdef HAL_AWK_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/** @defgroup AWK_Private_Functions AWK Private Functions
  * @{
  */
static void AWK_SetConfig(AWK_HandleTypeDef *hawk);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup AWK_Exported_Functions AWK Exported Functions
  * @{
  */

/** @defgroup AWK_Exported_Functions_Group AWK functions 
 *  @brief    AWK functions 
 *
@verbatim 
  ==============================================================================
              ##### AWK functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the AWK.
    (+) De-initialize the AWK.
    (+) Start the AWK.
    (+) Stop the AWK.

@endverbatim
  * @{
  */
	
/**
  * @brief  Initializes the AWK Unit according to the specified
  *         parameters in the AWK_HandleTypeDef and create the associated handle.
  * @note no comment
  * @param  hawk : AWK handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_AWK_Init(AWK_HandleTypeDef *hawk)
{
  /* Check the AWK handle allocation */
  if(hawk == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_AWK_INSTANCE(hawk->Instance));

  if(hawk->State == HAL_AWK_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hawk->Lock = HAL_UNLOCKED;
		
    /* Init the low level hardware : CLOCK, NVIC */
    HAL_AWK_MspInit(hawk);
  }

  /* Set the AWK state */
  hawk->State= HAL_AWK_STATE_BUSY;

  /* Set the AWK configuration */
  AWK_SetConfig(hawk);

  /* Initialize the AWK state*/
  hawk->State= HAL_AWK_STATE_READY;

  return HAL_OK;
}


/**
  * @brief  DeInitializes the AWK peripheral 
  * @param  hawk : AWK handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_AWK_DeInit(AWK_HandleTypeDef *hawk)
{
  /* Check the parameters */
  assert_param(IS_AWK_INSTANCE(hawk->Instance));

  hawk->State = HAL_AWK_STATE_BUSY;
	
  /* Stop AWK */	
  __HAL_AWK_DISABLE(hawk);

  /* DeInit the low level hardware: CLOCK, NVIC */
  HAL_AWK_MspDeInit(hawk);

  /* Change AWK state */
  hawk->State = HAL_AWK_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hawk);

  return HAL_OK;
}


/**
  * @brief  Starts the AWK generation.
  * @param  hawk : AWK handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_AWK_Start(AWK_HandleTypeDef *hawk)
{
  /* Check the parameters */
  assert_param(IS_AWK_INSTANCE(hawk->Instance));

  /* Set the AWK state */
  hawk->State= HAL_AWK_STATE_BUSY;
	
  /* Start the awk*/	
  __HAL_AWK_ENABLE(hawk);
	
  /* Change the AWK state*/
  hawk->State= HAL_AWK_STATE_READY;
	
  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Stops the AWK generation.
  * @param  hawk : AWK handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_AWK_Stop(AWK_HandleTypeDef *hawk)
{
  /* Check the parameters */
  assert_param(IS_AWK_INSTANCE(hawk->Instance));

  /* Set the AWK state */
  hawk->State= HAL_AWK_STATE_BUSY;
	
  /* Stop awk */
  __HAL_AWK_DISABLE(hawk);

  /* Change the AWK state*/
  hawk->State= HAL_AWK_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Initializes the AWK MSP.
  * @param  hawk : AWK handle
  * @retval None
  */
__weak void HAL_AWK_MspInit(AWK_HandleTypeDef *hawk)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hawk);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_AWK_MspInit could be implemented in the user file
   */
}


/**
  * @brief  DeInitializes AWK MSP.
  * @param  hawk : AWK handle
  * @retval None
  */
__weak void HAL_AWK_MspDeInit(AWK_HandleTypeDef *hawk)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hawk);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_AWK_MspDeInit could be implemented in the user file
   */
}


/**
  * @brief  This function handles AWK interrupts requests.
  * @param  htim : AWK handle
  * @retval None
  */
void HAL_AWK_IRQHandler(AWK_HandleTypeDef *hawk)
{
  /* AWK Wakeup event */
  if(__HAL_AWK_GET_FLAG(hawk) != RESET)	
  {
      __HAL_AWK_CLEAR_IT(hawk);
      HAL_AWK_WakeUpCallback(hawk);
  }
}
	

/**
  * @brief  Wakeup callback in non blocking mode 
  * @param  htim : AWK handle
  * @retval None
  */
__weak void HAL_AWK_WakeUpCallback(AWK_HandleTypeDef *hawk)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hawk);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_AWK_WakeUpCallback could be implemented in the user file
   */

}




/**
  * @}
  */ /* End of group AWK_Exported_Functions_Group */


/**
  * @}
  */ /* End of group AWK_Exported_Functions */


/* Private functions ---------------------------------------------------------*/

/** @addtogroup AWK_Private_Functions
  * @{
  */

/**
  * @brief  AWK configuration
  * @param  AWKx : AWK periheral
  * @param  Structure : AWK configuration structure
  * @retval None
  */
static void AWK_SetConfig(AWK_HandleTypeDef *hawk)
{
	/* Reset all awk configuration */		
	CLEAR_BIT(hawk->Instance->CR, (AWK_CR_DIVSEL | AWK_CR_AWKEN | AWK_CR_TCLKSEL | AWK_CR_HXPRSC));
	SET_BIT(hawk->Instance->CR, hawk->Init.ClkDiv | hawk->Init.ClkSel | hawk->Init.HxtDiv);
	WRITE_REG(hawk->Instance->RLOAD, hawk->Init.Period);
	
}


/**
  * @}
	*/ /* End of group AWK_Private_Functions */


#endif /* HAL_AWK_MODULE_ENABLED */

/**
  * @}
  */ /* End of group AWK */

/**
  * @}
  */ /* group CX32L003_HAL_Driver */
