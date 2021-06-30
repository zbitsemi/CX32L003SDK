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

#define TEST_RTC_CLOCK 				RTC_CLOCK_LIRC			// RTC时钟选择
#define TEST_RTC_CYCLE_TIME 	HAL_RTC_ALARM2_10S	// 周期中断 定时10S
uint32_t test_inflag = 0;
uint32_t test_count = 0;
RTC_HandleTypeDef rtc_test = {0};


/**
  * @brief RTC Clock Configuration
  * @retval None
  */
void RTCClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};	
  if(TEST_RTC_CLOCK == RTC_CLOCK_LIRC)
	{
		RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LIRC;
		RCC_OscInitStruct.LIRCState = RCC_LIRC_ON;
		RCC_OscInitStruct.LIRCCalibrationValue = RCC_LIRCCALIBRATION_32K;
		
		if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		{
			Error_Handler();
		}
 }
	__HAL_RCC_RTC_CLK_ENABLE();
	//__HAL_RCC_GPIOC_CLK_ENABLE();
}
/**
  * @brief IWDG Init Configuration
  * @retval None
  */
void RTC_Init(void)
{
	/*set init handle*/

	rtc_test.Instance = RTC;
	rtc_test.Init.ClockSource = TEST_RTC_CLOCK;	// RTC时钟源
  rtc_test.Init.HourFormat = RTC_HOURFORMAT_24;//RTC_HOURFORMAT_12; // 24小时制	
  rtc_test.Init.TimeAdjustMode = RTC_TIME_ADJUST_SEC30; // RTC 时钟调校 周期
  rtc_test.Init.TimeTrim = 0X00; // 时钟补偿时间
		
	rtc_test.State = HAL_RTC_STATE_RESET; // 使能RTC计数器 
	HAL_RTC_Init(&rtc_test);
	
	HAL_RTC_Alarm2_Config(&rtc_test,ENABLE, (HAL_RTCAlarm2TypeDef)TEST_RTC_CYCLE_TIME);	// 周期闹钟2计数周期设定
	/* Set interrupt priority and turn on interrupt*/
	HAL_NVIC_SetPriority(RTC_IRQn, PRIORITY_LOW);	 // 中断优先级选择
	HAL_RTC_Alarm_INT_Config(&rtc_test,RTC_ALARM_2,ENABLE); 	// 使能ALAM2周期中断 
	HAL_RTC_Alarm_Clear_Flag(RTC_ALARM_2); // 周期闹钟2中断原始状态被清除
	HAL_NVIC_EnableIRQ(RTC_IRQn);	// 使能 RTC_IRQn
	
	printf("Enter Test RTC ALARM2 \r\n");
		
}
/*回调函数 */
void RTC_INT_CallBack(void)
{
	if(HAL_RTC_Alarm_Get_Flag(RTC_ALARM_2)==SET)	// 获取周期闹钟2中断是否被激活
	{
		HAL_RTC_Alarm_Clear_Flag(RTC_ALARM_2);  // 周期闹钟2中断原始状态被清除
		test_inflag = 1;
	}
	
}
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
	LogInit();	
	printf("Test rtc function!!\r\n");
	
	RTCClock_Config();
	RTC_Init();
	
  while (1)
	{
			if(test_inflag == 1)	// 中断测试标志位
			{
				test_inflag = 0;
				test_count++;
				printf("Get RTC ALARM2 interrupt test_conut:%d \r\n",test_count);
				BSP_LED_Toggle(LED1);
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



