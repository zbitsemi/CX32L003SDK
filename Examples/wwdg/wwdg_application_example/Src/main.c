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
#define WWDG_TEST_TIME				0X53			// time 3.63S,PCLK=24M
#define WWDG_TEST_WINDOW_TIME	0X20  	  // 1401.6ms
#define WWDG_TEST_PRESCALER		0XFFFFF		// 43.8ms
#define WWDG_TEST_MODE		WWDG_REFRESH_DOG//WWDG_UNREFRESH_RESET//WWDG_REFRESH_INTERRUPT//WWDG_REFRESH_DOG


WWDG_HandleTypeDef wwdg_test = {0};
FlagStatus wwdg_int = RESET;

/**
  * @brief WWDG Clock Configuration
  * @retval None
  */
void WWdgClock_Config(void)
{
	__HAL_RCC_WWDG_CLK_ENABLE();
}
/**
  * @brief WWDG Interrupt call
  * @retval None
  */
void HAL_WWDG_INT_Callback(void)
{
	wwdg_int = SET;
	
}
/**
  * @brief WWDG Init Configuration
  * @retval None
  */
void WWdg_Init(void)
{
	if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != true)
			printf("Test WWDG RESET ,NO RESET!\r\n");
	else
	{
		printf("Test WWDG RESET ,HAVE RESET!!!!\r\n");
		__HAL_RCC_CLEAR_RESET_FLAGS(RCC_FLAG_WWDGRST);
	}
		
	/*set init */
	wwdg_test.Instance = WWDG;
	wwdg_test.Init.Reload = WWDG_TEST_TIME;
	wwdg_test.Init.Window = WWDG_TEST_WINDOW_TIME;
	wwdg_test.Init.Prescaler = WWDG_TEST_PRESCALER;
	wwdg_test.Init.INTSet = WWDG_INT_ENABLE;
	/* Set interrupt priority and turn on interrupt*/	
	HAL_NVIC_SetPriority(WWDG_IRQn, PRIORITY_LOW);
  HAL_NVIC_EnableIRQ(WWDG_IRQn);
	
	if(WWDG_TEST_MODE == WWDG_REFRESH_INTERRUPT)
		printf("Enter Test WWDG Interrupt\r\n");
	else if(WWDG_TEST_MODE == WWDG_UNREFRESH_RESET)
	{
		printf("Enter Test WWDG UNREFRESH RESET ,wait 5S\r\n");
		HAL_Delay(5000);
	}
	else if(WWDG_TEST_MODE == WWDG_REFRESH_RESET)
	{
		wwdg_test.Init.INTSet = WWDG_INT_DISABLE;
		printf("Enter Test WWDG REFRESH RESET ,wait 5S\r\n");
		HAL_Delay(5000);
	}
	else
	{
	wwdg_test.Init.INTSet = WWDG_INT_DISABLE;
	/*See feed the dog successfully or not, so turn on interrupt*/
		printf("Enter Test WWDG refresh\r\n");
	}
	HAL_WWDG_Init(&wwdg_test);
}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	uint32_t cur_counter = 0;
	uint32_t times = 0;
	uint32_t plk_freq = 0;
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();		
	
  /* Configure the system clock to HIRC 24MHz*/
  SystemClock_Config();
	
	/* Initialize BSP Led for LED1 */	
	BSP_LED_Init(LED1);
	plk_freq = HAL_RCC_GetPCLKFreq();
  /* Configure uart1 for printf */	
	LogInit();	
	printf("Printf success using UART1, PD5-TXD, PD6-RXD\r\n");
	printf("PCLK freq :%dHZ\r\n",plk_freq);
	WWdgClock_Config();
	WWdg_Init();
	
  while (1)
	{
//		HAL_WWDG_Refresh(&wwdg_test);
		if (WWDG_TEST_MODE == WWDG_REFRESH_INTERRUPT)
		{
			if(wwdg_int != RESET)
			{
				HAL_WWDG_Refresh(&wwdg_test);
				times ++;
				wwdg_int = RESET;
				printf("INT %d \r\n",times);
				BSP_LED_Toggle(LED1);
			}
			if(times>0XFFFFFFF)
				times = 0;
		}
		else if (WWDG_TEST_MODE == WWDG_UNREFRESH_RESET)
		{
			if(wwdg_int != RESET)
			{
				cur_counter = 0;
				times ++;
				wwdg_int = RESET;
				printf("INT %d\r\n",times);
				BSP_LED_Toggle(LED1);
				//HAL_WWDG_Refresh(&wwdg_test);
			
			}
			if(times>0XFFFFFFF)
				times = 0;
		}
		else if (WWDG_TEST_MODE == WWDG_REFRESH_RESET)
		{
			times = 0;
			if(wwdg_int != RESET)
			{
				printf("INT happen\r\n");
				wwdg_int = RESET;
			}
			else
			{
				HAL_WWDG_Get_Counter(&wwdg_test, &cur_counter);
				if(cur_counter > WWDG_TEST_WINDOW_TIME)
				{
					BSP_LED_Toggle(LED1);
					HAL_WWDG_Refresh(&wwdg_test);
					printf(" cur_counter > WWDG_TEST_WINDOW_TIME HAL_WWDG_Refresh\r\n");
				}
			
			}
		}
		else
		{
			times = 0;
			if(wwdg_int != RESET)
			{
				printf("INT happen\r\n");
				wwdg_int = RESET;
			}
			else
			{
				HAL_WWDG_Get_Counter(&wwdg_test, &cur_counter);
				if(cur_counter < WWDG_TEST_WINDOW_TIME)
				{
					HAL_WWDG_Refresh(&wwdg_test);
					BSP_LED_Toggle(LED1);
					printf(" cur_counter < WWDG_TEST_WINDOW_TIME HAL_WWDG_Refresh\r\n");
				}
			}
		}
		
		
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



