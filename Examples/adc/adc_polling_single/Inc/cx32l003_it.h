/**
  ******************************************************************************
  * @file    cx32f103_it.h
	* @author  Application Team
	* @Version V1.0.0
  * @Date    1-April-2019
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32F103_IT_H
#define __CX32F103_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void GPIOA_IRQHandler(void);
void GPIOB_IRQHandler(void);
void GPIOC_IRQHandler(void);
void GPIOD_IRQHandler(void);
void FLASH_IRQHandler(void);
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void LPUART_IRQHandler(void);
void SPI_IRQHandler(void);
void I2C_IRQHandler(void);
void TIM10_IRQHandler(void);
void TIM11_IRQHandler(void);
void LPTIM_IRQHandler(void);
void TIM1_IRQHandler(void);
void TIM2_IRQHandler(void);
void PCA_IRQHandler(void);
void WWDG_IRQHandler(void);
void IWDG_IRQHandler(void);
void ADC_IRQHandler(void);
void LVD_IRQHandler(void);
void VC_IRQHandler(void);
void AWK_IRQHandler(void);
void OWIRE_IRQHandler(void);
void RTC_IRQHandler(void);
void CLKTRIM_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __CX32F103_IT_H */


