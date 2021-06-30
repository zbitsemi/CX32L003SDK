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


/* Private variables ---------------------------------------------------------*/
 GPIO_InitTypeDef  gpioinitstruct={0};

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
	
  /* Configure uart1 for printf */	
	LogInit();	
	printf("HIRC output clock at Pin PD1\n");
	printf("LIRC output clock at Pin PC7\n");

	HAL_Delay(1000); // 开发测试延迟烧录时间3S,否则第二次烧录只能全擦除才能进行开发
	HAL_Delay(1000);
	HAL_Delay(1000);

	//	关闭SWD功能 配置PC7和PD1的端子功能模式  周边模块功能模式使能
	RCC->UNLOCK =  0x55AA6699;
	RCC->SWDIOCR = 0x5A690000;	
	RCC->UNLOCK =  0x55AA6698;	
	
	__HAL_RCC_GPIOD_CLK_ENABLE();
	gpioinitstruct.Pin  = GPIO_PIN_1;
	gpioinitstruct.Mode = GPIO_MODE_AF;
	gpioinitstruct.OpenDrain = GPIO_PUSHPULL;	
	gpioinitstruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	gpioinitstruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	gpioinitstruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	gpioinitstruct.Pull = GPIO_NOPULL;
	gpioinitstruct.Alternate = GPIO_AF6_HIRC_OUT;
	HAL_GPIO_Init(GPIOD, &gpioinitstruct);
	
	__HAL_RCC_GPIOC_CLK_ENABLE();
	gpioinitstruct.Pin  = GPIO_PIN_7;
	gpioinitstruct.Mode = GPIO_MODE_AF;
	gpioinitstruct.OpenDrain = GPIO_PUSHPULL;	
	gpioinitstruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	gpioinitstruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	gpioinitstruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	gpioinitstruct.Pull = GPIO_NOPULL;
	gpioinitstruct.Alternate = GPIO_AF6_LIRC_OUT;
	HAL_GPIO_Init(GPIOC, &gpioinitstruct);

  while (1)
	{
		
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

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HIRC | RCC_OSCILLATORTYPE_LIRC;
  RCC_OscInitStruct.HIRCState = RCC_HIRC_ON;
  RCC_OscInitStruct.HIRCCalibrationValue = RCC_HIRCCALIBRATION_24M;
	

	RCC_OscInitStruct.LIRCState = RCC_LIRC_ON;
  RCC_OscInitStruct.LIRCCalibrationValue = RCC_LIRCCALIBRATION_32K;
	
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



