/**
  ******************************************************************************
  * @file    main.h
  * @author  Application Team
	* @Version V1.0.0
  * @Date    1-April-2019	
  * @brief   Header for main.c file.
  *          This file contains the common defines of the application.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"
#include "cx32l003_starterkit.h"

/* Private includes ----------------------------------------------------------*/
#include "io_mapping.h"
#include "log.h"
#include "util.h"
#include <stdbool.h>



/* Exported constants ---------------------------------------------------------*/
#define TIMx																		TIM1
#define TIMx_IRQn																TIM1_IRQn

// TIM输出频率 = TIMx_FREQ/TIMx_PERIOD
/* TIMx clock: 10KHz, period 100us*/
#define TIMx_FREQ																6 // 预分频后 TIM时钟频率 注意预分频值是否为整数
/* If TIMx clock 4MHZ */
#define TIMx_PERIOD															125 // 计数值 Max=65535 最快us级 程序指令跑不过来

#define Duty_Cycle                              25

#define TIMx_CH1_PULSEWIDTH											1  // CCR1通道值 注意 0<CCRx
#define TIMx_CH2_PULSEWIDTH											2 
#define TIMx_CH3_PULSEWIDTH											3
#define TIMx_CH4_PULSEWIDTH											4

/* Exported macros ------------------------------------------------------------*/
#define __HAL_RCC_TIMx_CLK_ENABLE()							__HAL_RCC_TIM1_CLK_ENABLE()

#define __HAL_RCC_TIMxCH1OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()
#define TIMx_CH1OUT_PORT												GPIOD	
#define TIMx_CH1OUT_PIN													GPIO_PIN_4
#define TIMx_CH1OUT_GPIO_AFn										GPIO_AF1_TIM1_CH1	

#define __HAL_RCC_TIMxCH1NOUT_GPIOCLK_ENABLE()	__HAL_RCC_GPIOD_CLK_ENABLE()
#define TIMx_CH1NOUT_PORT												GPIOD	
#define TIMx_CH1NOUT_PIN												GPIO_PIN_5
#define TIMx_CH1NOUT_GPIO_AFn										GPIO_AF1_TIM1_CH1N	

#define __HAL_RCC_TIMxCH2OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()
#define TIMx_CH2OUT_PORT												GPIOD	
#define TIMx_CH2OUT_PIN													GPIO_PIN_6
#define TIMx_CH2OUT_GPIO_AFn										GPIO_AF1_TIM1_CH2	

#define __HAL_RCC_TIMxCH2NOUT_GPIOCLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()
#define TIMx_CH2NOUT_PORT												GPIOA	
#define TIMx_CH2NOUT_PIN												GPIO_PIN_1
#define TIMx_CH2NOUT_GPIO_AFn										GPIO_AF1_TIM1_CH2N	

#define __HAL_RCC_TIMxCH3OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define TIMx_CH3OUT_PORT												GPIOC	
#define TIMx_CH3OUT_PIN													GPIO_PIN_3
#define TIMx_CH3OUT_GPIO_AFn										GPIO_AF1_TIM1_CH3

#define __HAL_RCC_TIMxCH3NOUT_GPIOCLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()
#define TIMx_CH3NOUT_PORT												GPIOA	
#define TIMx_CH3NOUT_PIN												GPIO_PIN_3
#define TIMx_CH3NOUT_GPIO_AFn										GPIO_AF1_TIM1_CH3N

#define __HAL_RCC_TIMxCH4OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define TIMx_CH4OUT_PORT												GPIOC	
#define TIMx_CH4OUT_PIN													GPIO_PIN_4
#define TIMx_CH4OUT_GPIO_AFn										GPIO_AF1_TIM1_CH4

#define __HAL_RCC_BKIN_GPIOCLK_ENABLE()					__HAL_RCC_GPIOB_CLK_ENABLE()
#define TIMx_BKIN_PORT													GPIOB	
#define TIMx_BKIN_PIN														GPIO_PIN_5
#define TIMx_BKIN_GPIO_AFn											GPIO_AF1_TIM1_BKIN

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

