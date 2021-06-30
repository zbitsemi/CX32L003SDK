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


// TIM输出频率 = TIMx_FREQ/TIMx_PERIOD
#define TIM1_FREQ																1000000 // TIM时钟频率 注意预分频值是否为整数 	即 预分频值 = (主频)24000000/(TIM时钟频率)1000000

#define TIM1_PERIOD															100 // 计数值 Max=65535 最快us级 程序指令跑不过来
 

#define TIM1_CH1_PULSEWIDTH											(TIM1_PERIOD*1/5)  // CCR1通道值 注意 0<CCRx 
#define TIM1_CH2_PULSEWIDTH											(TIM1_PERIOD*1/2)
#define TIM1_CH3_PULSEWIDTH											(TIM1_PERIOD*4/10)
#define TIM1_CH4_PULSEWIDTH											(TIM1_PERIOD*1/10)


/* Exported macros ------------------------------------------------------------*/

#define __HAL_RCC_TIM1_CH1OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()
#define TIM1_CH1OUT_PORT												GPIOD	
#define TIM1_CH1OUT_PIN													GPIO_PIN_4
#define TIM1_CH1OUT_GPIO_AFn								GPIO_AF1_TIM1_CH1	


#define __HAL_RCC_TIM1_CH2OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()
#define TIM1_CH2OUT_PORT												GPIOD	
#define TIM1_CH2OUT_PIN													GPIO_PIN_6
#define TIM1_CH2OUT_GPIO_AFn								GPIO_AF1_TIM1_CH2	

#define __HAL_RCC_TIM1_CH3OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define TIM1_CH3OUT_PORT												GPIOA	
#define TIM1_CH3OUT_PIN													GPIO_PIN_2
#define TIM1_CH3OUT_GPIO_AFn								GPIO_AF1_TIM1_CH3

#define __HAL_RCC_TIM1_CH4OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define TIM1_CH4OUT_PORT												GPIOC	
#define TIM1_CH4OUT_PIN													GPIO_PIN_4
#define TIM1_CH4OUT_GPIO_AFn								GPIO_AF1_TIM1_CH4


//================================================//
// TIM输出频率 = TIMx_FREQ/TIMx_PERIOD
#define TIM2_FREQ																1000000 // TIM时钟频率 注意预分频值是否为整数 	即 预分频值 = (主频)24000000/(TIM时钟频率)1000000

#define TIM2_PERIOD															200 // 计数值 Max=65535 最快us级 程序指令跑不过来
 

#define TIM2_CH1_PULSEWIDTH											(TIM2_PERIOD*1/5)  // CCR1通道值 注意 0<CCRx 
#define TIM2_CH2_PULSEWIDTH											(TIM2_PERIOD*1/2)
#define TIM2_CH3_PULSEWIDTH											(TIM2_PERIOD*4/10)
#define TIM2_CH4_PULSEWIDTH											(TIM2_PERIOD*1/10)

#define __HAL_RCC_TIM2_CH1OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define TIM2_CH1OUT_PORT												GPIOC	
#define TIM2_CH1OUT_PIN													GPIO_PIN_5
#define TIM2_CH1OUT_GPIO_AFn								GPIO_AF8_TIM2_CH1	

#define __HAL_RCC_TIM2_CH2OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()
#define TIM2_CH2OUT_PORT												GPIOD	
#define TIM2_CH2OUT_PIN													GPIO_PIN_3
#define TIM2_CH2OUT_GPIO_AFn								GPIO_AF8_TIM2_CH2	


#define __HAL_RCC_TIM2_CH3OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define TIM2_CH3OUT_PORT												GPIOC	
#define TIM2_CH3OUT_PIN													GPIO_PIN_3
#define TIM2_CH3OUT_GPIO_AFn								GPIO_AF8_TIM2_CH3


#define __HAL_RCC_TIM2_CH4OUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define TIM2_CH4OUT_PORT												GPIOC	
#define TIM2_CH4OUT_PIN													GPIO_PIN_6
#define TIM2_CH4OUT_GPIO_AFn								GPIO_AF8_TIM2_CH4








/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

