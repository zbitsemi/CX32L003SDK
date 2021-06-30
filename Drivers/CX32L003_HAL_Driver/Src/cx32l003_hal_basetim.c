/**
  ******************************************************************************
  * @file    cx32l003_hal_basetim.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   BASETIM HAL module driver
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Base Timer (BASETIM) peripheral:
  *           + Base Time Base Initialization
  *           + Base Time Base Start
  *           + Base Time Base Start Interruption
  @verbatim
  ==============================================================================
                   ##### BASE TIMER Generic features #####
  ==============================================================================
  [..] The Timer features include:
       (#) 32-bit up auto-reload counter.
       (#) 3-bit programmable prescaler allowing dividing (also on the fly) the 
           counter clock frequency either by factor up to 256 max.
  @endverbatim
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"


/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @defgroup BASETIM BASETIM
  * @brief BASETIM HAL module driver
  * @{
  */

#ifdef HAL_BASETIM_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/** @defgroup BASETIM_Private_Functions BASETIM Private Functions
  * @{
  */
static void BASETIM_Base_SetConfig(BASETIM_TypeDef *BASETIMx, BASETIM_Base_InitTypeDef *Structure);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup BASETIM_Exported_Functions BASETIM Exported Functions
  * @{
  */

/** @defgroup BASETIM_Exported_Functions_Group1 Base Time Base functions 
 *  @brief    Base Time Base functions 
 *
@verbatim 
  ==============================================================================
              ##### Base Time Base functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the Base TIM.
    (+) De-initialize the Base TIM.
    (+) Start the Base Time.
    (+) Stop the Base Time.
    (+) Start the Base Time and enable interrupt.
    (+) Stop the Base Time and disable interrupt.

@endverbatim
  * @{
  */
	
/**
  * @brief  Initializes the BASETIM Time base Unit according to the specified
  *         parameters in the BASETIM_HandleTypeDef and create the associated handle.
  * @note no comment
  * @param  hbasetim : BASETIM Base handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_BASETIM_Base_Init(BASETIM_HandleTypeDef *hbasetim)
{
  /* Check the TIM handle allocation */
  if(hbasetim == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_BASETIM_INSTANCE(hbasetim->Instance));

  if(hbasetim->State == HAL_BASETIM_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hbasetim->Lock = HAL_UNLOCKED;
    
    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_BASETIM_Base_MspInit(hbasetim);
  }

  /* Set the TIM state */
  hbasetim->State= HAL_BASETIM_STATE_BUSY;

  /* Set the Time Base configuration */
  BASETIM_Base_SetConfig(hbasetim->Instance, &hbasetim->Init);

  /* Initialize the TIM state*/
  hbasetim->State= HAL_BASETIM_STATE_READY;

  return HAL_OK;
}


/**
  * @brief  DeInitializes the BASETIM Base peripheral 
  * @param  hbasetim : BASETIM Base handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_BASETIM_Base_DeInit(BASETIM_HandleTypeDef *hbasetim)
{
  /* Check the parameters */
  assert_param(IS_BASETIM_INSTANCE(hbasetim->Instance));

  hbasetim->State = HAL_BASETIM_STATE_BUSY;

  /* Disable the BASETIM Peripheral Clock */
  __HAL_BASETIM_DISABLE(hbasetim);

  /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
  HAL_BASETIM_Base_MspDeInit(hbasetim);

  /* Change BASETIM state */
  hbasetim->State = HAL_BASETIM_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hbasetim);

  return HAL_OK;
}


/**
  * @brief  Starts the BASETIM Base generation.
  * @param  hbasetim : BASETIM handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_BASETIM_Base_Start(BASETIM_HandleTypeDef *hbasetim)
{
  /* Check the parameters */
  assert_param(IS_BASETIM_INSTANCE(hbasetim->Instance));

  /* Set the BASETIM state */
  hbasetim->State= HAL_BASETIM_STATE_BUSY;

  /* Start the base timer */
  __HAL_BASETIM_ENABLE(hbasetim);

  /* Change the BASETIM state*/
  hbasetim->State= HAL_BASETIM_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Stops the BASETIM Base generation.
  * @param  hbasetim : BASETIM handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_BASETIM_Base_Stop(BASETIM_HandleTypeDef *hbasetim)
{
  /* Check the parameters */
  assert_param(IS_BASETIM_INSTANCE(hbasetim->Instance));

  /* Set the BASETIM state */
  hbasetim->State= HAL_BASETIM_STATE_BUSY;

  /* Stop the base timer */
  __HAL_BASETIM_DISABLE(hbasetim);

  /* Change the BASETIM state*/
  hbasetim->State= HAL_BASETIM_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Starts the BASETIM Base generation in interrupt mode.
  * @param  hbasetim : BASETIM handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_BASETIM_Base_Start_IT(BASETIM_HandleTypeDef *hbasetim)
{
  /* Check the parameters */
  assert_param(IS_BASETIM_INSTANCE(hbasetim->Instance));
	
   /* Enable the BASETIM interrupt */
   __HAL_BASETIM_ENABLE_IT(hbasetim);	

   /* Start the base timer */
  __HAL_BASETIM_ENABLE(hbasetim);

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Stops the BASETIM Base generation in interrupt mode.
  * @param  hbasetim : BASETIM handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_BASETIM_Base_Stop_IT(BASETIM_HandleTypeDef *hbasetim)
{
  /* Check the parameters */
  assert_param(IS_BASETIM_INSTANCE(hbasetim->Instance));
  /* Disable the BASETIM interrupt */
  __HAL_BASETIM_DISABLE_IT(hbasetim);

  /* Stop the base timer */
  __HAL_BASETIM_DISABLE(hbasetim);

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Initializes the BASETIM Base MSP.
  * @param  hbasetim : BASETIM handle
  * @retval None
  */
__weak void HAL_BASETIM_Base_MspInit(BASETIM_HandleTypeDef *hbasetim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hbasetim);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_BASETIM_Base_MspInit could be implemented in the user file
   */
}


/**
  * @brief  DeInitializes BASETIM Base MSP.
  * @param  hbasetim : BASETIM handle
  * @retval None
  */
__weak void HAL_BASETIM_Base_MspDeInit(BASETIM_HandleTypeDef *hbasetim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hbasetim);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_BASETIM_Base_MspDeInit could be implemented in the user file
   */
}



/**
  * @}
  */ /* End of group BASETIM_Exported_Functions_Group1 */




/** @defgroup BASETIM_Exported_Functions_Group2 TIM IRQ handler management 
 *  @brief    IRQ handler management 
 *
@verbatim 
  ==============================================================================
                        ##### IRQ handler management #####
  ==============================================================================
  [..]
    This section provides Base Timer IRQ handler function.

@endverbatim
  * @{
  */
/**
  * @brief  This function handles BASETIM interrupts requests.
  * @param  htim : BASETIM  handle
  * @retval None
  */
void HAL_BASETIM_IRQHandler(BASETIM_HandleTypeDef *hbasetim)
{
  /* TIM Update event */
  if(__HAL_BASETIM_GET_FLAG(hbasetim) != RESET)
  {
    if(__HAL_BASETIM_GET_IT_SOURCE(hbasetim) !=RESET)
    {
      __HAL_BASETIM_CLEAR_IT(hbasetim);
      HAL_BASETIM_PeriodElapsedCallback(hbasetim);
    }
  }
}

/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : BASETIM handle
  * @retval None
  */
__weak void HAL_BASETIM_PeriodElapsedCallback(BASETIM_HandleTypeDef *hbasetim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hbasetim);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_BASETIM_PeriodElapsedCallback could be implemented in the user file
   */

}

/**
  * @}
  */ /* End of BASETIM_Exported_Functions_Group2 */


/**
  * @}
  */ /* End of group BASETIM_Exported_Functions */


/* Private functions ---------------------------------------------------------*/

/** @addtogroup BASETIM_Private_Functions
  * @{
  */

/**
  * @brief  Base Time Base configuration
  * @param  BASETIMx : BASETIM periheral
  * @param  Structure : BASETIM Base configuration structure
  * @retval None
  */
static void BASETIM_Base_SetConfig(BASETIM_TypeDef *BASETIMx, BASETIM_Base_InitTypeDef *Structure)
{
	/* Reset all base timer function */		
	BASETIMx->CR &= ~BASETIM_CR_ALL_Msk;	
	BASETIMx->CR = Structure->GateLevel | Structure->GateEnable | Structure->TogEnable |\
								 Structure->CntTimSel | Structure->AutoReload | Structure->MaxCntLevel |\
								 Structure->OneShot | Structure->Prescaler;
	
	/* Timer Mode1 AutoReload's load register is different from Mode0 */
	if(Structure->AutoReload == BASETIM_AUTORELOAD_ENABLE)
	{
		BASETIMx->LOAD = Structure->Period;				
		BASETIMx->BGLOAD = Structure->Period;
	}
	else
		BASETIMx->LOAD = Structure->Period;		

}

/**
  * @}
  */ /* End of group TIM_Private_Functions */

#endif /* HAL_BASETIM_MODULE_ENABLED */

/**
  * @}
  */ /* End of group BASETIM */

/**
  * @}
  */ /* group CX32L003_HAL_Driver */
