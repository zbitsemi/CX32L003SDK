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


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* TIMx clock: 1KHz, period 1ms*/
#define TIMx_FREQ																1000	
/* If TIMx clock 1K ---> 300ms */
#define PULSE_DELAY															300	
/* If TIMx clock 1K ---> 1000ms*/
#define PULSE_WIDTH															1000	

/* Exported macro ------------------------------------------------------------*/
#define TIMx																		TIM1
#define __HAL_RCC_TIMx_CLK_ENABLE()							__HAL_RCC_TIM1_CLK_ENABLE()

#define __HAL_RCC_TIMxCHxOUT_GPIOCLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()
#define TIMx_CHxOUT_PORT												GPIOD	
#define TIMx_CHxOUT_PIN													GPIO_PIN_4
#define TIMx_CHxOUT_GPIO_AFn										GPIO_AF1_TIM1_CH1	
#define TIMx_CHxOUT_CHANNEL											TIM_CHANNEL_1

#define __HAL_RCC_TIMxCHxIN_GPIOCLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()
#define TIMx_CHxIN_PORT													GPIOD	
#define TIMx_CHxIN_PIN													GPIO_PIN_6
#define TIMx_CHxIN_GPIO_AFn											GPIO_AF1_TIM1_CH2	
#define TIMx_CHxIN_CHANNEL											TIM_CHANNEL_2



/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

