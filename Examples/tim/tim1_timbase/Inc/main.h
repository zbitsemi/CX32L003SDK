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

// TIMÊä³öÆµÂÊ = TIMx_FREQ/TIMx_PERIOD
/* TIMx clock: 10KHz, period 100us*/
#define TIMx_FREQ																10000
/* If TIMx clock 10K ---> 1s */
#define TIMx_PERIOD															(10000-1)	

/* Exported macros ------------------------------------------------------------*/
#define __HAL_RCC_TIMx_CLK_ENABLE()							__HAL_RCC_TIM1_CLK_ENABLE()





/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

