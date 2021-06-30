/**
  ******************************************************************************
  * @file    cx32l003_hal_lptim.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   LPTIM HAL module driver
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Low Power Timer (LPTIM) peripheral:
  *           + Low Power Time Base Initialization
  *           + Low Power Time Base Start
  *           + Low Power Time Base Start Interruption
  @verbatim
  ==============================================================================
                  ##### LOW POWER TIMER Generic features #####
  ==============================================================================
  [..] The Timer features include:
       (#) 16-bit up auto-reload counter.
  @endverbatim
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"


/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @defgroup LPTIM LPTIM
  * @brief LPTIM HAL module driver
  * @{
  */
#ifdef HAL_LPTIM_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/** @defgroup LPTIM_Private_Functions LPTIM Private Functions
  * @{
  */
static void LPTIM_Base_SetConfig(LPTIM_TypeDef *LPTIMx, LPTIM_Base_InitTypeDef *Structure);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup LPTIM_Exported_Functions LPTIM Exported Functions
  * @{
  */

/** @defgroup LPTIM_Exported_Functions_Group Low Power Time Base functions 
 *  @brief    Low Power Time Base functions 
 *
@verbatim 
  ==============================================================================
              ##### Low Power Time Base functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the Low Power Time.
    (+) De-initialize the Low Power Time.
    (+) Start the Low Power Time.
    (+) Stop the Low Power Time.
    (+) Start the Low Power Time and enable interrupt.
    (+) Stop the Low Power Time and disable interrupt.

@endverbatim
  * @{
  */
	
/**
  * @brief  Initializes the LPTIM Time base Unit according to the specified
  *         parameters in the LPTIM_HandleTypeDef and create the associated handle.
  * @note no comment
  * @param  hlptim : LPTIM Base handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_Base_Init(LPTIM_HandleTypeDef *hlptim)
{
  /* Check the LPTIM handle allocation */
  if(hlptim == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

  if(hlptim->State == HAL_LPTIM_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hlptim->Lock = HAL_UNLOCKED;
		
    __HAL_LPTIM_CLOCK_ENABLE(hlptim);
		
    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_LPTIM_Base_MspInit(hlptim);
  }

  /* Set the LPTIM state */
  hlptim->State= HAL_LPTIM_STATE_BUSY;

  /* Set the Low Power Time Base configuration */
  LPTIM_Base_SetConfig(hlptim->Instance, &hlptim->Init);

  /* Initialize the LPTIM state*/
  hlptim->State= HAL_LPTIM_STATE_READY;

  return HAL_OK;
}


/**
  * @brief  DeInitializes the LPTIM Base peripheral 
  * @param  hlptim : LPTIM Base handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_Base_DeInit(LPTIM_HandleTypeDef *hlptim)
{
  /* Check the parameters */
  assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

  hlptim->State = HAL_LPTIM_STATE_BUSY;
	
  /* Disable the LPTIM Clock */
  __HAL_LPTIM_CLOCK_DISABLE(hlptim);	

  /* Stop LPTIM */	
  __HAL_LPTIM_DISABLE(hlptim);

  /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
  HAL_LPTIM_Base_MspDeInit(hlptim);

  /* Change LPTIM state */
  hlptim->State = HAL_LPTIM_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hlptim);

  return HAL_OK;
}


/**
  * @brief  Starts the LPTIM Base generation.
  * @param  hlptim : LPTIM handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_LPTIM_Base_Start(LPTIM_HandleTypeDef *hlptim)
{
  /* Check the parameters */
  assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

  /* Set the LPTIM state */
  hlptim->State= HAL_LPTIM_STATE_BUSY;
	
  /* Enable the clock*/	
	__HAL_LPTIM_CLOCK_ENABLE(hlptim);
	
  /* Start the lptim*/	
  __HAL_LPTIM_ENABLE(hlptim);

  /* Change the LPTIM state*/
  hlptim->State= HAL_LPTIM_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Stops the LPTIM Base generation.
  * @param  hlptim : LPTIM handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_LPTIM_Base_Stop(LPTIM_HandleTypeDef *hlptim)
{
  /* Check the parameters */
  assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

  /* Set the LPTIM state */
  hlptim->State= HAL_LPTIM_STATE_BUSY;
	
  /* Stop lptim */
  __HAL_LPTIM_DISABLE(hlptim);

  /* Change the LPTIM state*/
  hlptim->State= HAL_LPTIM_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Starts the LPTIM Base generation in interrupt mode.
  * @param  hlptim : LPTIM handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_LPTIM_Base_Start_IT(LPTIM_HandleTypeDef *hlptim)
{
  /* Check the parameters */
  assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
	
  /* Enable the clock*/	
	__HAL_LPTIM_CLOCK_ENABLE(hlptim);	
	
  /* Enable the LPTIM interrupt */
  __HAL_LPTIM_ENABLE_IT(hlptim);

  /* start the Peripheral */
  __HAL_LPTIM_ENABLE(hlptim);

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Stops the LPTIM Base generation in interrupt mode.
  * @param  hlptim : LPTIM handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_LPTIM_Base_Stop_IT(LPTIM_HandleTypeDef *hlptim)
{
  /* Check the parameters */
  assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
  /* Disable the LPTIM interrupt */
  __HAL_LPTIM_DISABLE_IT(hlptim);

  /* Stop lptim */
  __HAL_LPTIM_DISABLE(hlptim);

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Initializes the LPTIM Base MSP.
  * @param  hlptim : LPTIM handle
  * @retval None
  */
__weak void HAL_LPTIM_Base_MspInit(LPTIM_HandleTypeDef *hlptim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlptim);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_LPTIM_Base_MspInit could be implemented in the user file
   */
}


/**
  * @brief  DeInitializes LPTIM Base MSP.
  * @param  hlptim : LPTIM handle
  * @retval None
  */
__weak void HAL_LPTIM_Base_MspDeInit(LPTIM_HandleTypeDef *hlptim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlptim);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_LPTIM_Base_MspDeInit could be implemented in the user file
   */
}


/**
  * @brief  This function handles LPTIM interrupts requests.
  * @param  htim : LPTIM handle
  * @retval None
  */
void HAL_LPTIM_IRQHandler(LPTIM_HandleTypeDef *hlptim)
{
  /* TIM Update event */
  if(__HAL_LPTIM_GET_FLAG(hlptim) != RESET)	
  {
    if(__HAL_LPTIM_GET_IT_SOURCE(hlptim) !=RESET)	
    {
      __HAL_BASETIM_CLEAR_IT(hlptim);
      HAL_LPTIM_PeriodElapsedCallback(hlptim);
    }
  }
}

/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : LPTIM handle
  * @retval None
  */
__weak void HAL_LPTIM_PeriodElapsedCallback(LPTIM_HandleTypeDef *hlptim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlptim);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_LPTIM_PeriodElapsedCallback could be implemented in the user file
   */

}



/**
  * @}
  */ /* End of group LPTIM_Exported_Functions_Group */


/**
  * @}
  */ /* End of group LPTIM_Exported_Functions */


/* Private functions ---------------------------------------------------------*/

/** @addtogroup LPTIM_Private_Functions
  * @{
  */

/**
  * @brief  Low Power Time Base configuration
  * @param  LPTIMx : LPTIM periheral
  * @param  Structure : LPTIM Base configuration structure
  * @retval None
  */
static void LPTIM_Base_SetConfig(LPTIM_TypeDef *LPTIMx, LPTIM_Base_InitTypeDef *Structure)
{
	
	/* Reset all low power timer function */		
	LPTIMx->CR &= ~LPTIM_CR_ALL_Msk;	
	LPTIMx->CR = Structure->GateLevel | Structure->GateEnable | Structure->TogEnable |\
								 Structure->CntTimSel | Structure->AutoReload | Structure->ClkSel;
	
	while(__HAL_LPTIM_SYNC_FLAG(LPTIMx) == SET);
	/* Timer Mode1 AutoReload's load register is different from Mode0 */
	if(Structure->AutoReload == LPTIM_AUTORELOAD_ENABLE)
		LPTIMx->BGLOAD = Structure->Period;
	else
		LPTIMx->LOAD = Structure->Period;		

}


/**
  * @}
	*/ /* End of group LPTIM_Private_Functions */

#endif /* HAL_LPTIM_MODULE_ENABLED */
/**
  * @}
  */ /* End of group LPTIM */



/**
  * @}
  */ /* group CX32L003_HAL_Driver */
