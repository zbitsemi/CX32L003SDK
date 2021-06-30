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
#define LPTIMx_CLK				38000
#define LPTIMx_FREQUENCY 	1000	// 1KHZ  
#define LPTIMx_FREQ 		(0xFFFF - LPTIMx_CLK/LPTIMx_FREQUENCY)	// 注意寄存器值不要溢出
#define LPTIMx					LPTIM
#define LPTIMx_IRQn 		LPTIM_IRQn 

#define LED_FREQ				500 

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

