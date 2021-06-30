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
#define	RTC_ALARM_POLLING_MODE	0x00U
#define RTC_ALARM_INTERRUPT_MODE		0X01U


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void RTC_INT_CallBack(void);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

