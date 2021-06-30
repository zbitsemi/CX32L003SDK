/**
  ******************************************************************************
  * @file    cx32l003_hal_vc.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   VC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Voltage comparator (VC) peripheral:
  *           + Initialization and Start functions
  *           + IO operation functions
  *
  @verbatim
  ==============================================================================
                    ##### VC Generic features #####
  ==============================================================================
  [..]
    (+) The VC can be started by  software (configurable through option byte).

    (+) The VC Filter is clocked by Low-Speed clock (LIRC)or PCLK .

                     ##### How to use this driver #####
  ==============================================================================
  [..]
    (#) Use VC using HAL_VC_Init() function to :
      (++) Enable VC 25DIV in VC_CR0 register. 
      (++) Select input source for "+" and "-"
      (++) Configure the VC filter set.
      (++) set triger and interrupt.
    

     *** VC HAL driver macros list ***
     ====================================
   @endverbatim
  ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"



#ifdef HAL_VC_MODULE_ENABLED
/** @defgroup VC VC
  * @brief VC HAL module driver.
  * @{
  */


/** @addtogroup VC_Exported_Functions
  * @{
  */

/** @addtogroup VC_Exported_Functions_Group1
  *  @brief    Initialization and Start functions.
  *
@verbatim
 ===============================================================================
          ##### Initialization and Start functions #####
 ===============================================================================
 [..]  This section provides functions allowing to:
      (+) Initialize the VC according to the specified parameters in the
          VC_InitTypeDef of associated handle.
      (+) Once initialization is performed in HAL_VC_Init function, 
          the Voltage comparator will work.

@endverbatim
  * @{
  */
/**
  * @brief  Initialize the VC according to the specified parameters in the
  *         VC_HandleTypeDef and start VC. 
  * @param  hvc  pointer to a VC_HandleTypeDef structure that contains
  *                the configuration information for the specified VC module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_VC_Init(VC_HandleTypeDef *hvc)
{
   /* Check the VC handle allocation */
    if (hvc == NULL)
    {
      return HAL_ERROR;
    }

   /* Check the parameters */
    assert_param(IS_VC_INSTANCE(hvc->Instance));
    assert_param(IS_VC_VC25DIV(hvc->Init.V25div));
    assert_param(IS_VC_INPUT(hvc->Init.NinSel));
    assert_param(IS_VC_INPUT(hvc->Init.PinSel));
    assert_param(IS_VC_INT_STATE(hvc->Init.INT_Enable));
    assert_param(IS_VC_FILTER_STATE(hvc->Init.Filter_Enable));
    assert_param(IS_VC_FILTER_NUM(hvc->Init.Fliter_Num));

    //write CR0
    WRITE_REG(hvc->Instance->CR0,(((hvc->Init.V25div)<<VC_CR0_V25DIV_Pos) |((hvc->Init.NinSel)<<VC_CR0_NINSEL_Pos) | \
                                    (hvc->Init.PinSel) | (HAL_VC_VC25DIV_ENABLE)));
    
 /* Write to CR1  about interrupt */
    if(hvc->Init.INT_Enable != HAL_VC_INT_ENABLE)
        VC_DISABLE_INT_CLEAR(hvc);
    else 
    {
        assert_param(IS_VC_INT_MODE(hvc->Init.INT_Mode));
        VC_DISABLE_INT_CLEAR(hvc);
        VC_ENABLE_INT_SET(hvc);
    }
    
    /* Write to CR1  about filter */
    if(hvc->Init.Filter_Enable != HAL_VC_FILTER_ENABLE)
         CLEAR_BIT((hvc)->Instance->CR1, HAL_VC_FILTER_ENABLE);
    else 
    {
        assert_param(IS_VC_FILTER_NUM(hvc->Init.Fliter_Num));
        assert_param(IS_VC_FILTER_CLK(hvc->Init.Filter_Clk));
        SET_BIT((hvc)->Instance->CR1,(HAL_VC_FILTER_ENABLE | ((hvc->Init.Fliter_Num)<<VC_CR1_FLT_NUM_Pos) | (hvc->Init.Filter_Clk)));
        if((hvc->Init.Filter_Clk)==HAL_VC_FILTER_CLK_NONE)
            CLEAR_BIT((hvc)->Instance->CR1,VC_CR1_VC_FLTCLK_SEL);
    }
    
    HAL_VC_Enable(hvc);
  /* Return function status */
  return HAL_OK;
}
/**
  * @brief  DE Initialize the VC according to the specified parameters in the
  *         VC_HandleTypeDef . 
  * @param  hvc  pointer to a VC_HandleTypeDef structure that contains
  *                the configuration information for the specified VC module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_VC_DeInit(VC_HandleTypeDef *hvc)
{
    CLEAR_REG(hvc->Instance->CR0);
    CLEAR_REG(hvc->Instance->CR1);
    CLEAR_REG(hvc->Instance->OUTCFG);
    CLEAR_REG(hvc->Instance->SR);
    
    return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup VC_Exported_Functions_Group2
  *  @brief   IO operation functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
 [..]  This section provides functions allowing to:
      (+) VC OUTPUT Config.

@endverbatim
  * @{
  */

/**
  * @brief  Config VC output enable.
  * @param  hvc  pointer to a VC_HandleTypeDef structure that contains
  *                the configuration information for the specified VC module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_VC_OutPut_Config_Enable(VC_HandleTypeDef *hvc, uint32_t config)
{
    /* config the VC output */
   assert_param(IS_VC_OUTPUT_CONFIG(config));
   SET_BIT(hvc->Instance->OUTCFG, (config&HAL_VC_OUTCFG_Msk)); 
    
  /* Return function status */
  return HAL_OK;
}
/**
  * @brief  Config VC output disenable.
  * @param  hvc  pointer to a VC_HandleTypeDef structure that contains
  *                the configuration information for the specified VC module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_VC_OutPut_Config_Disable(VC_HandleTypeDef *hvc, uint32_t config)
{
    /* config the VC output */
   assert_param(IS_VC_OUTPUT_CONFIG(config));
   CLEAR_BIT(hvc->Instance->OUTCFG, (config&HAL_VC_OUTCFG_Msk)); 
    
  /* Return function status */
  return HAL_OK;
}
/**
  * @}
  */


/** @addtogroup VC_Exported_Functions_Group3
  *  @brief    Get/Clear Status functions.
  *
   * @{
  */
/**
  * @brief  Checks whether the interrupt VC flag is set or reset.
  * @param  hvc  pointer to a VC_HandleTypeDef structure that contains
  *                the configuration information for the specified VC module.
  * @retval The new state of VC interrupt FLAG (SET or RESET).
  */
FlagStatus HAL_VC_Get_INT_Flag(VC_HandleTypeDef *hvc)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
   if ((hvc->Instance->SR & VC_SR_INTF) != (uint32_t)RESET)
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
  * @brief  Clears interrupt flag.
  * @param  hvc  pointer to a VC_HandleTypeDef structure that contains
  *                the configuration information for the specified VC module.
  * @retval None
  */
void HAL_VC_Clear_INT_Flag(VC_HandleTypeDef *hvc)
{   
    CLEAR_BIT(hvc->Instance->SR, VC_SR_INTF);
}

/**
  * @brief  Checks VC output is set or reset.
  * @param  hvc  pointer to a VC_HandleTypeDef structure that contains
  *                the configuration information for the specified VC module.
  * @retval The new state of VC_OUTPUT (SET or RESET).
  */
FlagStatus HAL_VC_Get_OutPut_State(VC_HandleTypeDef *hvc)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
   if ((hvc->Instance->SR & VC_SR_VC_FLOUT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the vc output status */
  return bitstatus;
}

/**
  * @brief  Enable VC (write access to VC_CR1 registers).
  * @param  hvc  pointer to a VC_HandleTypeDef structure that contains
  *                the configuration information for the specified VC module.
  * @retval None
  */
void HAL_VC_Enable(VC_HandleTypeDef *hvc)
{
  SET_BIT(hvc->Instance->CR1, HAL_VC_ENABLE);
}
/**
  * @brief  Disables VC (write access to VC_CR1 registers).
  * @param  hvc  pointer to a VC_HandleTypeDef structure that contains
  *                the configuration information for the specified VC module.
  * @retval None
  */
void HAL_VC_Disable(VC_HandleTypeDef *hvc)
{
  CLEAR_BIT(hvc->Instance->CR1, HAL_VC_ENABLE);
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

#endif /* HAL_VC_MODULE_ENABLED */

