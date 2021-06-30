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

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
		
	GPIO_InitStruct.Pin = TIM1_CH1OUT_PIN;	
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	GPIO_InitStruct.Alternate = TIM1_CH1OUT_GPIO_AFn;
		
	HAL_GPIO_Init(TIM1_CH1OUT_PORT, &GPIO_InitStruct);		
	


	GPIO_InitStruct.Pin = TIM1_CH2OUT_PIN;		
	GPIO_InitStruct.Alternate = TIM1_CH2OUT_GPIO_AFn;
	HAL_GPIO_Init(TIM1_CH2OUT_PORT, &GPIO_InitStruct);		
	

	GPIO_InitStruct.Pin = TIM1_CH3OUT_PIN;		
	GPIO_InitStruct.Alternate = TIM1_CH3OUT_GPIO_AFn;
	HAL_GPIO_Init(TIM1_CH3OUT_PORT, &GPIO_InitStruct);	
	

	GPIO_InitStruct.Pin = TIM1_CH4OUT_PIN;		
	GPIO_InitStruct.Alternate = TIM1_CH4OUT_GPIO_AFn;
	HAL_GPIO_Init(TIM1_CH4OUT_PORT, &GPIO_InitStruct);
	

//	GPIO_InitStruct.Pin = TIM1_BKIN_PIN;		
//	GPIO_InitStruct.Alternate = TIM1_BKIN_GPIO_AFn;
//	HAL_GPIO_Init(TIM1_BKIN_PORT, &GPIO_InitStruct);	
	
 //==============================================//
	GPIO_InitStruct.Pin = TIM2_CH1OUT_PIN;		
	GPIO_InitStruct.Alternate = TIM2_CH1OUT_GPIO_AFn;
	HAL_GPIO_Init(TIM2_CH1OUT_PORT, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.Pin = TIM2_CH2OUT_PIN;		
	GPIO_InitStruct.Alternate = TIM2_CH2OUT_GPIO_AFn;
	HAL_GPIO_Init(TIM2_CH2OUT_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = TIM2_CH3OUT_PIN;		
	GPIO_InitStruct.Alternate = TIM2_CH3OUT_GPIO_AFn;
	HAL_GPIO_Init(TIM2_CH3OUT_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = TIM2_CH4OUT_PIN;		
	GPIO_InitStruct.Alternate = TIM2_CH4OUT_GPIO_AFn;
	HAL_GPIO_Init(TIM2_CH4OUT_PORT, &GPIO_InitStruct);
	
}


