/**
  ******************************************************************************
  * @file    main.c
	* @author  MCU Software Team
  * @Version V1.2.0
  * @Date    2021-01-11
  * @brief   main function
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"	
// M0没有位操作区 
typedef struct {
		uint16_t bit0 : 1;
		uint16_t bit1 : 1;
		uint16_t bit2 : 1;
		uint16_t bit3 : 1;
		uint16_t bit4 : 1;
		uint16_t bit5 : 1;
		uint16_t bit6 : 1;
		uint16_t bit7 : 1;
		uint16_t bit8 : 1;
		uint16_t bit9 : 1;
		uint16_t bit10 : 1;
		uint16_t bit11 : 1;
		uint16_t bit12 : 1;
		uint16_t bit13 : 1;
		uint16_t bit14 : 1;
		uint16_t bit15 : 1;
} Bits_16_TypeDef;


#define PAout(n) ((Bits_16_TypeDef *)(&(GPIOA->ODR)))->bit##n
#define PBout(n) ((Bits_16_TypeDef *)(&(GPIOB->ODR)))->bit##n
#define PCout(n) ((Bits_16_TypeDef *)(&(GPIOC->ODR)))->bit##n
#define PDout(n) ((Bits_16_TypeDef *)(&(GPIOD->ODR)))->bit##n

#define PAin(n) ((Bits_16_TypeDef *)(&(GPIOA->IDR)))->bit##n
#define PBin(n) ((Bits_16_TypeDef *)(&(GPIOB->IDR)))->bit##n
#define PCBin(n) ((Bits_16_TypeDef *)(&(GPIOC->IDR)))->bit##n
#define PDBin(n) ((Bits_16_TypeDef *)(&(GPIOD->IDR)))->bit##n

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();		
	
  /* Configure the system clock to HIRC 24MHz*/
  SystemClock_Config();

  /* Initialize BSP Led for LED1 */	
  BSP_LED_Init(LED1);
	
  /* Configure uart1 for printf */	
//  LogInit();	
//  printf("LED toggle every 1 second\n");

  while (1)
  {
    BSP_LED_Toggle(LED1);
//		GPIOD->ODR  ^= LED1_PIN; // 500 ns

//		GPIOD->ODSET = LED1_PIN; // 置位1 效率更高 83 ns
//		GPIOD->ODCLR = LED1_PIN; // 置位0  

//		PDout(4) = 1; // 500 NS
//		PDout(4) = 0; // 
    HAL_Delay(1000);
  }
}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};	
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HIRC;
  RCC_OscInitStruct.HIRCState = RCC_HIRC_ON;
  RCC_OscInitStruct.HIRCCalibrationValue = RCC_HIRCCALIBRATION_24M;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
	
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HIRC;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APBCLKDivider = RCC_PCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }	
}
 


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


/* Private function -------------------------------------------------------*/



