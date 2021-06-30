/**
  ******************************************************************************
  * @file    cx32l003_hal_msp.c
	* @author  MCU Software Team
	* @Version V1.0.0
  * @Date    21-Oct-2019
  * @brief   This file provides code for the MSP Initialization 
  *          and de-Initialization codes.
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "main.h"


/**
  * @brief  Initializes the TIM PWM MSP.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_TIMxCH1OUT_GPIOCLK_ENABLE();		
	GPIO_InitStruct.Pin = TIMx_CH1OUT_PIN;	
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	GPIO_InitStruct.Alternate = TIMx_CH1OUT_GPIO_AFn;
	HAL_GPIO_Init(TIMx_CH1OUT_PORT, &GPIO_InitStruct);		
	
	__HAL_RCC_TIMxCH1NOUT_GPIOCLK_ENABLE();
	GPIO_InitStruct.Pin = TIMx_CH1NOUT_PIN;		
	GPIO_InitStruct.Alternate = TIMx_CH1NOUT_GPIO_AFn;
	HAL_GPIO_Init(TIMx_CH1NOUT_PORT, &GPIO_InitStruct);		
	
	__HAL_RCC_TIMxCH2OUT_GPIOCLK_ENABLE();
	GPIO_InitStruct.Pin = TIMx_CH2OUT_PIN;		
	GPIO_InitStruct.Alternate = TIMx_CH2OUT_GPIO_AFn;
	HAL_GPIO_Init(TIMx_CH2OUT_PORT, &GPIO_InitStruct);		
	
	__HAL_RCC_TIMxCH2NOUT_GPIOCLK_ENABLE();
	GPIO_InitStruct.Pin = TIMx_CH2NOUT_PIN;		
	GPIO_InitStruct.Alternate = TIMx_CH2NOUT_GPIO_AFn;
	HAL_GPIO_Init(TIMx_CH2NOUT_PORT, &GPIO_InitStruct);			
	
}


