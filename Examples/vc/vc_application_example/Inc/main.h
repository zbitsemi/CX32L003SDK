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
#define POSITIVE_INPUT_SOURCE	HAL_VC_INPUT_V25DIV//HAL_VC_INPUT_2
#define NEGATIVE_INPUT_SOURCE	HAL_VC_INPUT_1
//#define POSITIVE_INPUT_GPIO_PIN		GPIO_PIN_2
//#define NEGATIVE_INPUT_GPIO_PIN		GPIO_PIN_5
//#define POSITIVE_INPUT_GPIO			GPIOD
//#define NEGATIVE_INPUT_GPIO			GPIOC
#define V25_DIV_SET					HAL_VC_4P4_V25DIV
#define VC_CLOCK_SOURCE				HAL_VC_FILTER_CLK_PCLK
#define VC_INT_MODE					HAL_VC_RISE_INT_ENABLE
#define VC_FILTER_NUM				0x10
/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void VC_INT_CallBack(void);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

