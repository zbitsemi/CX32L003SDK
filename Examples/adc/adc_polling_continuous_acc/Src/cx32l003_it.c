/**
  ******************************************************************************
  * @file    cx32l003_it.c
	* @author  MCU Software Team
	* @Version V1.0.0
  * @Date    21-Oct-2019
  * @brief   Interrupt Service Routines.
  ******************************************************************************

  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cx32l003_it.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/



/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}


/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
}


/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* CX32L003 Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_xm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles GPIOA Interrupt line[3:1] interrupts.
  */
void GPIOA_IRQHandler(void)
{
  /* USER CODE BEGIN GPIOA_IRQn 0 */

  /* USER CODE END GPIOA_IRQn 0 */
}

/**
  * @brief This function handles GPIOB Interrupt line[5:4] interrupts.
  */
void GPIOB_IRQHandler(void)
{
  /* USER CODE BEGIN GPIOB_IRQn 0 */

  /* USER CODE END GPIOB_IRQn 0 */
}

/**
  * @brief This function handles GPIOC Interrupt line[7:3] interrupts.
  */
void GPIOC_IRQHandler(void)
{

}

/**
  * @brief This function handles GPIOD Interrupt line[6:1] interrupts.
  */
void GPIOD_IRQHandler(void)
{
  /* USER CODE BEGIN GPIOD_IRQn 0 */

  /* USER CODE END GPIOD_IRQn 0 */
}

/**
  * @brief This function handles FLASH Interrupt .
  */
void FLASH_IRQHandler(void)
{
  /* USER CODE BEGIN FLASH_IRQn 0 */

  /* USER CODE END FLASH_IRQn 0 */
}

/**
  * @brief This function handles UART0 Interrupt .
  */
void UART0_IRQHandler(void)
{
  /* USER CODE BEGIN UART0_IRQn 0 */

  /* USER CODE END UART0_IRQn 0 */
}

/**
  * @brief This function handles UART1 Interrupt .
  */
void UART1_IRQHandler(void)
{
  /* USER CODE BEGIN UART1_IRQn 0 */

  /* USER CODE END UART1_IRQn 0 */
}

/**
  * @brief This function handles LPUART Interrupt .
  */
void LPUART_IRQHandler(void)
{
  /* USER CODE BEGIN LPUART_IRQn 0 */

  /* USER CODE END LPUART_IRQn 0 */
}

/**
  * @brief This function handles SPI Interrupt .
  */
void SPI_IRQHandler(void)
{
  /* USER CODE BEGIN SPI_IRQn 0 */

  /* USER CODE END SPI_IRQn 0 */
}

/**
  * @brief This function handles I2C Interrupt .
  */
void I2C_IRQHandler(void)
{
  /* USER CODE BEGIN I2C_IRQn 0 */

  /* USER CODE END I2C_IRQn 0 */
}

/**
  * @brief This function handles TIM10 Interrupt .
  */
void TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM10_IRQn 0 */

  /* USER CODE END TIM10_IRQn 0 */
}

/**
  * @brief This function handles TIM11 Interrupt .
  */
void TIM11_IRQHandler(void)
{
  /* USER CODE BEGIN TIM11_IRQn 0 */

  /* USER CODE END TIM11_IRQn 0 */
}

/**
  * @brief This function handles LPTIM Interrupt .
  */
void LPTIM_IRQHandler(void)
{
  /* USER CODE BEGIN LPTIM_IRQn 0 */

  /* USER CODE END LPTIM_IRQn 0 */
}

/**
  * @brief This function handles TIM1 Interrupt .
  */
void TIM1_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_IRQn 0 */

  /* USER CODE END TIM1_IRQn 0 */
}

/**
  * @brief This function handles TIM2 Interrupt .
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
}

/**
  * @brief This function handles PCA Interrupt .
  */
void PCA_IRQHandler(void)
{
  /* USER CODE BEGIN PCA_IRQn 0 */

  /* USER CODE END PCA_IRQn 0 */
}

/**
  * @brief This function handles WWDG Interrupt .
  */
void WWDG_IRQHandler(void)
{
  /* USER CODE BEGIN WWDG_IRQn 0 */

  /* USER CODE END WWDG_IRQn 0 */
}

/**
  * @brief This function handles IWDG Interrupt .
  */
void IWDG_IRQHandler(void)
{
  /* USER CODE BEGIN IWDG_IRQn 0 */

  /* USER CODE END IWDG_IRQn 0 */
}

/**
  * @brief This function handles ADC Interrupt .
  */
void ADC_IRQHandler(void)
{

}

/**
  * @brief This function handles LVD Interrupt .
  */
void LVD_IRQHandler(void)
{
  /* USER CODE BEGIN LVD_IRQn 0 */

  /* USER CODE END LVD_IRQn 0 */
}

/**
  * @brief This function handles VC Interrupt .
  */
void VC_IRQHandler(void)
{
  /* USER CODE BEGIN VC_IRQn 0 */

  /* USER CODE END VC_IRQn 0 */
}

/**
  * @brief This function handles AWK Interrupt .
  */
void AWK_IRQHandler(void)
{
  /* USER CODE BEGIN AWK_IRQn 0 */

  /* USER CODE END AWK_IRQn 0 */
}

/**
  * @brief This function handles OWIRE Interrupt .
  */
void OWIRE_IRQHandler(void)
{
  /* USER CODE BEGIN OWIRE_IRQn 0 */

  /* USER CODE END OWIRE_IRQn 0 */
}

/**
  * @brief This function handles RTC Interrupt .
  */
void RTC_IRQHandler(void)
{
  /* USER CODE BEGIN RTC_IRQn 0 */

  /* USER CODE END RTC_IRQn 0 */
}

/**
  * @brief This function handles CLKTRIM Interrupt .
  */
void CLKTRIM_IRQHandler(void)
{
  /* USER CODE BEGIN CLKTRIM_IRQn 0 */

  /* USER CODE END CLKTRIM_IRQn 0 */
}

