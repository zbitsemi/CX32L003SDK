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
#define BEEPx												BEEP
#define BEEPx_PORT									GPIOD
#define BEEPx_PIN										GPIO_PIN_4
#define BEEPx_AFn     							GPIO_AF7_BEEP

#define BEEPx_DIVFREQ								64000		 // ÆµÂÊÊä³öÖµ

/* Exported macro -------------------------------------------------------------*/
#define BEEPx_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

