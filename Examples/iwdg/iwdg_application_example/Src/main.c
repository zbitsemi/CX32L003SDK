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

#define IWDG_TEST_TIME			0X1C71C		// time 3S=0X1C71C/38400,	LIRC=38.4K
#define IWDG_TEST_REFRESH_TIME	0X0200  	// 13.3ms

#define IWDG_TEST_MODE		IWDG_REFRESH_RESET	//IWDG_REFRESH_INTERRUPT//IWDG_REFRESH_DOG // 模式选择


IWDG_HandleTypeDef iwdg_test = {0};
FlagStatus iwdg_int = RESET;

/**
  * @brief IWDG Clock Configuration
  * @retval None
  */
void IwdgClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};	
  
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LIRC;
  RCC_OscInitStruct.LIRCState = RCC_LIRC_ON;
  RCC_OscInitStruct.LIRCCalibrationValue = RCC_LIRCCALIBRATION_38K;
	
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
	__HAL_RCC_IWDG_CLK_ENABLE();
}
/**
  * @brief IWDG Interrupt call
  * @retval None
  */
void Iwdg_call(void)
{
	if(HAL_IWDG_Get_INT_Flag() != RESET)
	{
		HAL_IWDG_Clear_INT_Flag(); // 清除中断标志
		iwdg_int = SET;
	}
}
/**
  * @brief IWDG Init Configuration
  * @retval None
  */
void Iwdg_Init(void)
{
//		__HAL_RCC_IWDG_CLK_ENABLE();
	if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != true)
			printf("Test IWDG RESET ,NO RESET!\r\n");
	else
	{
		printf("Test IWDG RESET ,HAVE RESET!!!!\r\n");
		__HAL_RCC_CLEAR_RESET_FLAGS(RCC_FLAG_IWDGRST);
	}
		
	/*set init pa*/
	iwdg_test.Instance = IWDG;
	iwdg_test.Init.Reload = IWDG_TEST_TIME; // 周期时间
	
	#if (IWDG_TEST_MODE == IWDG_REFRESH_INTERRUPT)
		iwdg_test.Init.MaskINT = IWDG_UNMASK_INT; // IWDG中断不屏蔽 
		iwdg_test.Init.Mode = IWDG_MODE_INT; // IWDG计数溢出中断模式
		/* Set interrupt priority and turn on interrupt*/
		HAL_NVIC_SetPriority(IWDG_IRQn, PRIORITY_LOW);
		HAL_NVIC_EnableIRQ(IWDG_IRQn);
		printf("Enter Test IWDG Interrupt\r\n");
	#elif (IWDG_TEST_MODE == IWDG_REFRESH_RESET)
		iwdg_test.Init.MaskINT = IWDG_MASK_INT;	// IWDG中断被屏蔽 
		iwdg_test.Init.Mode = IWDG_MODE_RESET; // IWDG计数溢出复位模式 
		printf("Enter Test IWDG RESET ,wait 5S\r\n");
		HAL_Delay(5000);
	#else
	/*See feed the dog successfully or not, so turn on interrupt*/
	iwdg_test.Init.MaskINT = IWDG_UNMASK_INT;
	iwdg_test.Init.Mode =IWDG_MODE_INT;
	/* Set interrupt priority and turn on interrupt*/	
	HAL_NVIC_SetPriority(IWDG_IRQn, PRIORITY_LOW);
  HAL_NVIC_EnableIRQ(IWDG_IRQn);
		printf("Enter Test IWDG refresh\r\n");
	#endif
	HAL_IWDG_Init(&iwdg_test);
}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	uint32_t cur_counter = 0;
	uint32_t times = 0;
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  	HAL_Init();		
	
  /* Configure the system clock to HIRC 24MHz*/
  	SystemClock_Config();
	
	/* Initialize BSP Led for LED1 */	
	BSP_LED_Init(LED1);
  /* Configure uart1 for printf */	
	LogInit();	
	printf("Printf success using UART1, PD5-TXD, PD6-RXD\r\n");
	
	IwdgClock_Config();
	Iwdg_Init();
	
  	while (1)
	{
		#if (IWDG_TEST_MODE == IWDG_REFRESH_INTERRUPT)
		if(iwdg_int != RESET)
		{
			HAL_IWDG_Refresh(&iwdg_test);
			times ++;
			iwdg_int = RESET;
			printf("INT %d\r\n",times);
			BSP_LED_Toggle(LED1);
			
		}
		if(times>0XFFFFFFF)
				times = 0;
		#elif (IWDG_TEST_MODE == IWDG_REFRESH_RESET)
		times = 0;
		#else
		times = 0;
		if(iwdg_int != RESET)
		{
			printf("INT happen\r\n");
			iwdg_int = RESET;
		}
		else
		{
			HAL_IWDG_Get_Counter(&iwdg_test,&cur_counter);
			if(cur_counter < IWDG_TEST_REFRESH_TIME)
			{
				HAL_IWDG_Refresh(&iwdg_test);
				BSP_LED_Toggle(LED1);
			}
			
		}
		#endif
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



