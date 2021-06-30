/**
  ******************************************************************************
  * @file    io_mapping.h
  * @author  Application Team
	* @Version V1.0.0
  * @Date    1-April-2019
  * @brief   Header file of RCC HAL Extension module.
  ******************************************************************************
 **/
#ifndef __CX32L003_IO_MAPPING_H
#define __CX32L003_IO_MAPPING_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"

#define TEST_GPIO_Pin		    GPIO_PIN_11
#define TEST_GPIO_Port	    GPIOB


#define USART1_TX_Pin				GPIO_PIN_9
#define USART1_TX_GPIO_Port	GPIOA

#define USART1_RX_Pin				GPIO_PIN_10
#define USART1_RX_GPIO_Port	GPIOA


#define DEBUG_GPIO_Pin		  GPIO_PIN_5
#define DEBUG_GPIO_Port	    GPIOC

#define LD2_Pin             GPIO_PIN_5
#define LD2_GPIO_Port       GPIOA

#ifdef __cplusplus
}
#endif


#endif /* __CX32L003_IO_MAPPING_H */
