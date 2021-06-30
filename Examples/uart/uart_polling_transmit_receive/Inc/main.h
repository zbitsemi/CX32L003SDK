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
#define UARTx													UART0
#define BAUDRATE											9600
#define UARTx_TX_PORT									GPIOA
#define UARTx_TX_PIN									GPIO_PIN_2
#define UARTx_RX_PORT									GPIOA
#define UARTx_RX_PIN									GPIO_PIN_1
#define UARTx_TX_ALTERNATE_AFn				GPIO_AF5_UART0_TXD
#define UARTx_RX_ALTERNATE_AFn				GPIO_AF5_UART0_RXD

#define LENGTH												10
#define TIMEOUT_MAX										0xFFFFFFFF

/* Exported macros-------------------------------------------------------------*/
#define __HAL_RCC_UARTx_CLK_ENABLE()  		__HAL_RCC_UART0_CLK_ENABLE()	
#define __HAL_RCC_UARTx_GPIO_CLK_ENABLE()  	__HAL_RCC_GPIOA_CLK_ENABLE()	

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

