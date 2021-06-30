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

#define SPI_NSS_PIN			GPIO_PIN_3	// �͵�ƽ��Ч�ӻ�ѡ����
#define SPI_NSS_GPIO		GPIOA
#define SPI_MOSI_PIN		GPIO_PIN_3 // �������/�ӻ�������
#define SPI_MOSI_GPIO		GPIOD
#define SPI_MISO_PIN		GPIO_PIN_2 // ��������/�ӻ������
#define SPI_MISO_GPIO		GPIOD
#define SPI_CLK_PIN			GPIO_PIN_5 // ����ʱ����
#define SPI_CLK_GPIO		GPIOC

#define SPI_WRITE_DELAY	200 /*56US*/
/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

