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
/* USER CODE BEGIN Includes */
#include "io_mapping.h"
#include "log.h"
#include "util.h"
#include <stdbool.h>
/* USER CODE END Includes */



/* Exported constants ---------------------------------------------------------*/
#define FREQ 												1000
#define BASETIMx										TIM11
#define BASETIMx_IRQn 							TIM11_IRQn
#define BASETIMx_GATE_PORT					GPIOC
#define BASETIMx_GATE_PIN						GPIO_PIN_5
#define BASETIMx_GATE_AFn     			GPIO_AF6_TIM11_GATE

#define LED_PERIOD									1000

/* Exported macro -------------------------------------------------------------*/
#define BASETIMx_GATE_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

