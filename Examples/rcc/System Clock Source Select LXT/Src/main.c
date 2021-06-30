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
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
void App_Gpio_Init( void)
{
  	GPIO_InitTypeDef  gpioinitstruct={0};
  
  	/* Enable the GPIO_LED Clock */
  	__HAL_RCC_GPIOA_CLK_ENABLE()  ;
	__HAL_RCC_GPIOB_CLK_ENABLE()  ;
	__HAL_RCC_GPIOC_CLK_ENABLE()  ;
	__HAL_RCC_GPIOD_CLK_ENABLE()  ;
	
 	/* Configure the GPIO pin */
  	gpioinitstruct.Pin    = GPIO_PIN_1;
	gpioinitstruct.Mode = GPIO_MODE_OUTPUT;
	gpioinitstruct.OpenDrain = GPIO_PUSHPULL;	
	gpioinitstruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	gpioinitstruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	gpioinitstruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	gpioinitstruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpioinitstruct);
  
	/* Reset PIN to switch off the LED */
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_2;
	HAL_GPIO_Init(GPIOA, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3, GPIO_PIN_RESET);
	//---------------------------------------------
	gpioinitstruct.Pin    = GPIO_PIN_4;
	HAL_GPIO_Init(GPIOB, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_5;
	HAL_GPIO_Init(GPIOB, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET);
	//---------------------------------------------
	gpioinitstruct.Pin    = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOC, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_4;
	HAL_GPIO_Init(GPIOC, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_5;
	HAL_GPIO_Init(GPIOC, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOC, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_7;
	HAL_GPIO_Init(GPIOC, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7, GPIO_PIN_RESET);
	
	//-----------------------------------------

	gpioinitstruct.Pin    = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOD, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_2;
	HAL_GPIO_Init(GPIOD, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOD, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_4;
	HAL_GPIO_Init(GPIOD, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_5;
	HAL_GPIO_Init(GPIOD, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5, GPIO_PIN_RESET);
	
	gpioinitstruct.Pin    = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOD, &gpioinitstruct);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6, GPIO_PIN_RESET);
	
}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
//	HAL_Init();		
	/* Configure the system clock to LXT */
	SystemClock_Config();

	/* Default MCO ouput  clock at Pin PC4 */
	HAL_RCC_MCOConfig(RCC_MCO, RCC_MCOSOURCE_LXT, RCC_MCODIV_1);  // 
	App_Gpio_Init();
	while(1)
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

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LXT;
  RCC_OscInitStruct.LXTState = RCC_LXT_ON;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
	
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_LXT; 
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APBCLKDivider = RCC_PCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HIRC;
  RCC_OscInitStruct.HIRCCalibrationValue  = RCC_HIRCCALIBRATION_24M;
  RCC_OscInitStruct.HIRCState = RCC_HIRC_OFF;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
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



