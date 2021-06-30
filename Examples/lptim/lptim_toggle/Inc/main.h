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
#define LPTIMx_IRQn 					LPTIM_IRQn


/* Exported macros ------------------------------------------------------------*/
#define LPTIMx_TOGGLE_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()
#define LPTIMx_TOGGLE_PIN									GPIO_PIN_2
#define LPTIMx_TOGGLE_PORT								GPIOD
#define LPTIMx_TOGGLE_AFn									GPIO_AF6_LPTIM_TOG

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

