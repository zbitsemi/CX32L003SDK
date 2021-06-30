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


void log_GPIO_EnInit(void);
void log_GPIO_DeInit(void);
void GPIO_Init(void);
/* Public variables ----------------------------------------------------------*/
AWK_HandleTypeDef sAwkHandle = {0};
uint32_t sleep_count = 0;
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
	
	GPIO_Init();
	
  /* Configure uart1 for printf */	
	LogInit();	
	printf("AWK function example.\n");
	printf("System wake up from deep sleep mode using auto wakeup timer, setting 8s wakeup interval.\n");		
	
//	BSP_LED_Init(LED1);
	
	__HAL_RCC_AWK_CLK_ENABLE();
	sAwkHandle.Instance = AWK;
	sAwkHandle.Init.ClkSel = AWK_CLOCK_LIRC;
	sAwkHandle.Init.ClkDiv = AWK_CLOCK_DIV_1024;	// 32768Hz/1024 = 32Hz
	sAwkHandle.Init.Period = 0;		//初值 向上计数溢出 (256-0)/32 = 8S  初值避免接近250以上
	HAL_AWK_Init(&sAwkHandle);

	HAL_AWK_Start(&sAwkHandle);
	HAL_NVIC_EnableIRQ(AWK_IRQn);	
	//  从Deep Sleep唤醒是使用HIRC开始唤醒，硬件自动enable HIRC，并且system clock自动切换到HIRC，原时钟继续开启
	while(1)
	{

		log_GPIO_DeInit();
		HAL_PWR_EnterDEEPSLEEPMode(); // 关闭相关外设后进入睡眠
		
		log_GPIO_EnInit();
		sleep_count++;
		printf("System wake up from deep sleep mode count: %d \n",sleep_count);		
	}		
}


/**
  * @brief  Wakeup callback in non blocking mode 
  * @param  htim : AWK handle
  * @retval None
  */
void HAL_AWK_WakeUpCallback(AWK_HandleTypeDef *hawk)
{
//	BSP_LED_Toggle(LED1);
}

/**
  * @brief log_GPIO_EnInit
  * @retval None
  */
void log_GPIO_EnInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    /**UART1 GPIO Configuration    
    PD5     ------> UART1_TXD
    PD6     ------> UART1_RXD
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF;	// GPIO端口复用功能
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	// 推挽输出
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE; // 禁止输入去抖动
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH; // 电压转换速率
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH; // 驱动强度
	GPIO_InitStruct.Pull = GPIO_PULLUP; // 上拉
	GPIO_InitStruct.Alternate = GPIO_AF5_UART1_TXD; // 端口复用UART1_TXD
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		
    GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Alternate = GPIO_AF5_UART1_RXD;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);		
}	
/**
  * @brief log_GPIO_DeInit
  * @retval None
  */
void log_GPIO_DeInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//		PD5     ------> UART1_TXD
	//    PD6     ------> UART1_RXD
   /* Configure the GPIO_LED pin */	
  	GPIO_InitStruct.Pin  = GPIO_PIN_5 | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;	// GPIO输出模式
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	// 推挽输出
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;// 禁止输入去抖动
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH; // 电压转换速率
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH; // 驱动强度
	GPIO_InitStruct.Pull = GPIO_NOPULL; // 无上下拉
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOD,(GPIO_PIN_5|GPIO_PIN_6), GPIO_PIN_RESET);

}	

/******************************************************************
  * @brief  
  * @param 
  * @param  
  * @retval None
	******************************************************************
  */
void GPIO_Init(void)
{
//  特别注意 
//	复位期间和复位后，复用功能未开启，并且除了调试引脚以外的所有I/O端口都被配置为浮空输入模式。 
// 	进入睡眠之前GPIO要设置为GPIO输出模式 置0状态	

	GPIO_InitTypeDef  GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
//	关闭SWD功能 配置PC7和PD1的端子功能模式  周边模块功能模式使能
//		RCC->UNLOCK =  0x55AA6699;
//		RCC->SWDIOCR = (0x5A69 << RCC_SWDIOCR_KEY_Pos);	
//		RCC->UNLOCK =  0x55AA6698;	
	
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT; // GPIO模式
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	  // 推挽输出
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE; // 禁止输入去抖动
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH; // 电压转换速率
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;// 驱动强度
	GPIO_InitStruct.Pull = GPIO_NOPULL; // 无上下拉
	
		/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin  = GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin  = GPIO_PIN_4 | GPIO_PIN_5;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin  = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin  = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	/* Configure the GPIO  */
	HAL_GPIO_WritePin(GPIOA,(GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3), GPIO_PIN_RESET);
	
	/* Configure the GPIO  */
	HAL_GPIO_WritePin(GPIOB,(GPIO_PIN_4|GPIO_PIN_5), GPIO_PIN_RESET);
	
	/* Configure the GPIO  */
	HAL_GPIO_WritePin(GPIOC,(GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6), GPIO_PIN_RESET);
	//	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7, GPIO_PIN_RESET); // SWD 

	/* Configure the GPIO  */
	//	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_RESET); // SWD 
	HAL_GPIO_WritePin(GPIOD,(GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6), GPIO_PIN_RESET);

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



