/**
  ******************************************************************************
  * @file    cx32l003_hal_iwdg.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   IWDG HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Independent Watchdog (IWDG) peripheral:
  *           + Initialization and Start functions
  *           + IO operation functions
  *
  @verbatim
  ==============================================================================
                    ##### IWDG Generic features #####
  ==============================================================================
  [..]
    (+) The IWDG can be started by software (configurable through option byte).

    (+) The IWDG is clocked by Low-Speed clock (LIRC) and thus stays active even
        if the main clock fails.

    (+) Once the IWDG is started, the counter starts counting down from the reload value (max 0xFFFFF).
        When it reaches the end of count value (0x00) a reset signal is
        generated (IWDG reset).

    (+) The key value 0xAA is written in the IWDG_CMDCR register when IWDG start,
        the IWDG_RLOAD value is reloaded in the counter and the watchdog reset is
        prevented.

    (+) Debug mode : When the microcontroller enters debug mode (core halted),
        the IWDG counter either continues to work normally or stops, depending
        on DBG_IWDG_STOP configuration bit in DBG module, accessible through
        __HAL_DBGMCU_FREEZE_IWDG() and __HAL_DBGMCU_UNFREEZE_IWDG() macros

    [..] Min-max timeout value @34.8KHz (LSI): ~26us / ~27s
         The IWDG timeout may vary due to LSI frequency dispersion. CX32L003
         devices provide the capability to measure the LSI frequency . 
				 The measured value can be used to have an IWDG timeout with an acceptable accuracy.

                     ##### How to use this driver #####
  ==============================================================================
  [..]
    (#) Use IWDG using HAL_IWDG_Init() function to :
      (++) Enable instance by writing Start keyword in IWDG_UNLOCK register. IWDG counter starts downcounting.
      (++) Enable write access to configuration register: IWDG_CFGR & IWDG_RLOAD.
      (++) Configure the IWDG counter reload value. This reload value will be loaded in the IWDG counter each 
			     time the watchdog is reloaded, then the IWDG will start counting down from this value.
    (#) Then the application program must refresh the IWDG counter at regular
        intervals during normal operation to prevent an MCU reset, using
        HAL_IWDG_Refresh() function.

     *** IWDG HAL driver macros list ***
     ====================================
     [..]
       Below the list of most used macros in IWDG HAL driver:
      (+) HAL_IWDG_Enable: Enable the IWDG peripheral
      (+) HAL_IWDG_Refresh: Reloads IWDG counter with value defined in
          the reload register

  @endverbatim
  ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"



#ifdef HAL_IWDG_MODULE_ENABLED
/** @defgroup IWDG IWDG
  * @brief IWDG HAL module driver.
  * @{
  */


/** @addtogroup IWDG_Exported_Functions
  * @{
  */

/** @addtogroup IWDG_Exported_Functions_Group1
  *  @brief    Initialization and Start functions.
  *
@verbatim
 ===============================================================================
          ##### Initialization and Start functions #####
 ===============================================================================
 [..]  This section provides functions allowing to:
      (+) Initialize the IWDG according to the specified parameters in the
          IWDG_InitTypeDef of associated handle.
      (+) Once initialization is performed in HAL_IWDG_Init function, Watchdog
          is reloaded in order to exit function with correct time base.

@endverbatim
  * @{
  */
/**
  * @brief  Initialize the IWDG according to the specified parameters in the
  *         IWDG_HandleTypeDef and start watchdog. Before exiting function,
  *         watchdog is refreshed in order to have correct time base.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IWDG_Init(IWDG_HandleTypeDef *hiwdg)
{
   /* Check the IWDG handle allocation */
    if (hiwdg == NULL)
    {
      return HAL_ERROR;
    }

   /* Check the parameters */
    assert_param(IS_IWDG_MASKINT(hiwdg->Init.MaskINT));
    assert_param(IS_IWDG_MODE(hiwdg->Init.Mode));
    assert_param(IS_IWDG_RELOAD(hiwdg->Init.Reload));

    IWDG_ENABLE_WRITE_ACCESS();
    
  /* Write to IWDG registers the mode and  mask IRQ to work with */
    if (hiwdg->Init.Mode != IWDG_MODE_RESET)
			SET_BIT(hiwdg->Instance->CFGR, IWDG_CFGR_IWDGMODE);
    else
      CLEAR_BIT(hiwdg->Instance->CFGR, IWDG_CFGR_IWDGMODE); 
    
    if (hiwdg->Init.MaskINT != IWDG_UNMASK_INT)
      SET_BIT(hiwdg->Instance->CFGR, IWDG_CFGR_IWDGINTMSK);
    else
      CLEAR_BIT(hiwdg->Instance->CFGR, IWDG_CFGR_IWDGINTMSK);
		
	/* Reload IWDG counter with value defined in the reload register */
    HAL_IWDG_SetReload(hiwdg);
    
	/* Enable IWDG.  */
    HAL_IWDG_Enable(hiwdg);
    
    IWDG_DISABLE_WRITE_ACCESS();
	
  /* Return function status */
  return HAL_OK;
}

HAL_StatusTypeDef HAL_IWDG_STOP(IWDG_HandleTypeDef *hiwdg)
{
	/* Check the IWDG handle allocation */
  
	 IWDG_ENABLE_WRITE_ACCESS();
	 hiwdg->Instance->CMDCR = 0;
	 hiwdg->Instance->SR = 0;
	 hiwdg->Instance->INTCLR = 0;
	 hiwdg->Instance->CFGR = 0;
	 IWDG_DISABLE_WRITE_ACCESS();	
		
	return HAL_OK;
}	

HAL_StatusTypeDef HAL_IWDG_RUN(IWDG_HandleTypeDef *hiwdg)
{
	/* Check the IWDG handle allocation */
    if (hiwdg == NULL)
    {
      return HAL_ERROR;
    }
	 IWDG_ENABLE_WRITE_ACCESS();
	 WRITE_REG(hiwdg->Instance->CMDCR, IWDG_START_ENABLE);	
	 WRITE_REG(hiwdg->Instance->CMDCR, IWDG_RELOAD_REFRESH);	
	 IWDG_DISABLE_WRITE_ACCESS();	
		
	return HAL_OK;
}	
/**
  * @}
  */

/** @addtogroup IWDG_Exported_Functions_Group2
  *  @brief   IO operation functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
 [..]  This section provides functions allowing to:
      (+) Refresh the IWDG.
			(+)	Get the IWDG current counter.

@endverbatim
  * @{
  */

/**
  * @brief  Refresh the IWDG.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IWDG_Refresh(IWDG_HandleTypeDef *hiwdg)
{
  /* Reload IWDG counter with value defined in the reload register */
  if(hiwdg->Instance->CFGR&IWDG_CFGR_IWDGRUNF_Msk)  
      hiwdg->Instance->CMDCR = IWDG_RELOAD_REFRESH;
  else
      return HAL_ERROR;

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Get the IWDG current counter.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @param  counter  pointer to a uint32_t structure handle,
	*										will stores the current count value
	* @retval HAL status
  */
HAL_StatusTypeDef HAL_IWDG_Get_Counter(IWDG_HandleTypeDef  *hiwdg, uint32_t *counter)
{
  /* Get IWDG counter with value defined in the CNTVAL register */
   *counter = (hiwdg->Instance->CNTVAL)&IWDG_CNTVAL_IWDGCNT;
 
	/* Return function status */
  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup IWDG_Exported_Functions_Group3
  *  @brief    Get INTStatus functions.
  *
   * @{
  */
/**
  * @brief  Checks whether the specified IWDG flag is set or not.
  * @param      None
  * @retval The new state of IWDG_FLAG (SET or RESET).
  */
FlagStatus HAL_IWDG_Get_INT_Flag(void)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  if ((IWDG->SR & IWDG_SR_IWDGOVF_Msk) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}
/**
  * @}
  */

/** @addtogroup IWDG_Exported_Functions_Group4
  *  @brief    Clear INT flag functions.
  *
   * @{
  */
/**
  * @brief  Clears interrupt flag.
  * @param  None
  * @retval None
  */
void HAL_IWDG_Clear_INT_Flag(void)
{
    IWDG_ENABLE_WRITE_ACCESS();    
    IWDG->INTCLR = (uint32_t)IWDG_INTCLR_IWDGINTCLR_Msk;
    IWDG_DISABLE_WRITE_ACCESS();
}
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_IWDG_MODULE_ENABLED */

