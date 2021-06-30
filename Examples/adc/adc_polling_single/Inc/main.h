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


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/

/* Public constants ------------------------------------------------------------*/
#define ADC_TIMEOUT_MAX		0xFFFFFFFF


/* Public defines ------------------------------------------------------------*/
#define ADCx		ADC

#define __HAL_RCC_ADCxAINx_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()
#define	ADCx_AINx_PIN														GPIO_PIN_3
#define	ADCx_AINx_PORT													GPIOD



#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

