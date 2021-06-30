/**
  ******************************************************************************
  * @file    cx32l003_hal_beep.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   BEEP HAL module driver
  *          This file provides firmware functions to manage the following 
  *          functionalities of the BEEP peripheral:
  *           + Beep Initialization
  *           + Beep DeInitialization	
  *           + Beep Start
  *           + Beep Stop	
  @verbatim
  ==============================================================================
                       ##### BEEP Generic features #####
  ==============================================================================
  [..] The Beep features include:
       (#) output different frequency.
  @endverbatim
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"


/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @defgroup BEEP BEEP
  * @brief BEEP HAL module driver
  * @{
  */
#ifdef HAL_BEEP_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/** @defgroup BEEP_Private_Functions BEEP Private Functions
  * @{
  */
static void BEEP_SetConfig(BEEP_HandleTypeDef *hbeep);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup BEEP_Exported_Functions BEEP Exported Functions
  * @{
  */

/** @defgroup BEEP_Exported_Functions_Group Beep Base functions 
 *  @brief    Beep Base functions 
 *
@verbatim 
  ==============================================================================
										##### Beep Base functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the Beep.
    (+) De-initialize the Beep.
    (+) Start the Beep.
    (+) Stop the Beep.

@endverbatim
  * @{
  */
	
/**
  * @brief  Initializes the BEEP Unit according to the specified
  *         parameters in the BEEP_HandleTypeDef and create the associated handle.
  * @note no comment
  * @param  hbeep : BEEP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_BEEP_Init(BEEP_HandleTypeDef *hbeep)
{
  /* Check the BEEP handle allocation */
  if(hbeep == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_BEEP_INSTANCE(hbeep->Instance));

  if(hbeep->State == HAL_BEEP_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hbeep->Lock = HAL_UNLOCKED;
		
    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_BEEP_MspInit(hbeep);
  }

  /* Set the BEEP state */
  hbeep->State= HAL_BEEP_STATE_BUSY;

  /* Set the Beep configuration */
  BEEP_SetConfig(hbeep);

  /* Initialize the BEEP state*/
  hbeep->State= HAL_BEEP_STATE_READY;

  return HAL_OK;
}


/**
  * @brief  DeInitializes the BEEP Base peripheral 
  * @param  hbeep : BEEP Base handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_BEEP_DeInit(BEEP_HandleTypeDef *hbeep)
{
  /* Check the parameters */
  assert_param(IS_BEEP_INSTANCE(hbeep->Instance));

  hbeep->State = HAL_BEEP_STATE_BUSY;
	
  /* Stop BEEP , reset beep configuration to reset value*/	
  __HAL_BEEP_DISABLE(hbeep);
	CLEAR_BIT(hbeep->Instance->CSR, BEEP_CSR_CLKSEL);
	CLEAR_BIT(hbeep->Instance->CSR, BEEP_CSR_BEEPSEL);	
	MODIFY_REG(hbeep->Instance->CSR, BEEP_CSR_BEEPDIV, 0xfff);
	
  /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
  HAL_BEEP_MspDeInit(hbeep);

  /* Change BEEP state */
  hbeep->State = HAL_BEEP_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hbeep);

  return HAL_OK;
}


/**
  * @brief  Starts the BEEP.
  * @param  hbeep : BEEP handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_BEEP_Start(BEEP_HandleTypeDef *hbeep)
{
  /* Check the parameters */
  assert_param(IS_BEEP_INSTANCE(hbeep->Instance));

  /* Set the BEEP state */
  hbeep->State= HAL_BEEP_STATE_BUSY;
	
  /* Start the beep*/	
  __HAL_BEEP_ENABLE(hbeep);

  /* Change the BEEP state*/
  hbeep->State= HAL_BEEP_STATE_READY;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Stops the BEEP.
  * @param  hbeep : BEEP handle
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_BEEP_Stop(BEEP_HandleTypeDef *hbeep)
{
  /* Check the parameters */
  assert_param(IS_BEEP_INSTANCE(hbeep->Instance));

  /* Set the BEEP state */
  hbeep->State= HAL_BEEP_STATE_BUSY;
	
  /* Stop beep */
  __HAL_BEEP_DISABLE(hbeep);

  /* Change the BEEP state*/
  hbeep->State= HAL_BEEP_STATE_READY;

  /* Return function status */
  return HAL_OK;
}



/**
  * @brief  Initializes the BEEP Base MSP.
  * @param  hbeep : BEEP handle
  * @retval None
  */
__weak void HAL_BEEP_MspInit(BEEP_HandleTypeDef *hbeep)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hbeep);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_BEEP_Base_MspInit could be implemented in the user file
   */
}


/**
  * @brief  DeInitializes BEEP Base MSP.
  * @param  hbeep : BEEP handle
  * @retval None
  */
__weak void HAL_BEEP_MspDeInit(BEEP_HandleTypeDef *hbeep)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hbeep);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_BEEP_Base_MspDeInit could be implemented in the user file
   */
}



/**
  * @}
  */ /* End of group BEEP_Exported_Functions_Group */


/**
  * @}
  */ /* End of group BEEP_Exported_Functions */


/* Private functions ---------------------------------------------------------*/

/** @addtogroup BEEP_Private_Functions
  * @{
  */

/**
  * @brief  Beep configuration
  * @param  BEEP : BEEP periheral
  * @retval None
  */
static void BEEP_SetConfig(BEEP_HandleTypeDef *hbeep)
{	
	/* Reset all beep function */		
	hbeep->Instance->CSR &= ~BEEP_CSR_ALL_Msk;
	hbeep->Instance->CSR = 0x0000;	
	hbeep->Instance->CSR = hbeep->Init.ClkSel | hbeep->Init.OutFreqDiv | hbeep->Init.OutFreqSel;		
	
}


/**
  * @}
  */ /* End of group BEEP_Private_Functions */

#endif /* HAL_BEEP_MODULE_ENABLED */

/**
  * @}
  */ /* End of group BEEP */

/**
  * @}
  */ /* group CX32L003_HAL_Driver */
