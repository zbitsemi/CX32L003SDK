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

#define I2C_TEST_MASTER						0x00U
#define I2C_TEST_SLAVE						0x01U
#define I2C_TEST_IRQ_LEVEL				0x00U
#define	DATA_LEN_MAX						  0X30U

	
#define TEST_FLAG_RECIVE					0X01U
#define	TEST_FLAG_TRANSM					0X02U
	/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void HAL_I2C_SlaveCallback(I2C_HandleTypeDef *hi2c);
void I2C_IRQ_Config(void);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

