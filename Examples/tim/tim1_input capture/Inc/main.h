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
#define LPTIMx_FREQ 					1000						/* 1KHz */
#define LPTIMx_RELOADVALUE 		(0xFFFF - HAL_RCC_GetPCLKFreq()/(LPTIMx_FREQ*2))										
#define LPTIMx								LPTIM

#define TIMx																		TIM1
#define TIMx_IRQn																TIM1_IRQn

/* TIMx clock: 1MHz, period 1us*/
#define TIMx_FREQ																1000000	
/* If TIMx clock 1MHz ---> TIMx overflow period is 1s */
#define TIMx_PERIOD															(1000000-1)	


/* Exported macros ------------------------------------------------------------*/
#define	__HAL_RCC_LPTIMx_CLK_ENABLE()			__HAL_RCC_LPTIM_CLK_ENABLE()
#define LPTIMx_TOGGLE_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()
#define LPTIMx_TOGGLE_PIN									GPIO_PIN_2
#define LPTIMx_TOGGLE_PORT								GPIOD
#define LPTIMx_TOGGLE_AFn									GPIO_AF6_LPTIM_TOG  // LPTIM·­×ªÊä³ö 

#define __HAL_RCC_TIMx_CLK_ENABLE()							__HAL_RCC_TIM1_CLK_ENABLE()
#define __HAL_RCC_TIMxCH1IN_GPIOCLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define TIMx_CH1IN_PORT													GPIOC	
#define TIMx_CH1IN_PIN													GPIO_PIN_6
#define TIMx_CH1IN_GPIO_AFn											GPIO_AF1_TIM1_CH1	// ÊäÈë


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

