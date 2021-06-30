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
#define TEST_RTC_CLOCK RTC_CLOCK_LIRC  		// RTC时钟选择
 

RTC_HandleTypeDef rtc_test = {0};
RTC_TimeTypeDef sTime_test = {0};
RTC_DateTypeDef sDate_test = {0};

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
	rtc_test.Init.ClockSource = TEST_RTC_CLOCK;		// RTC时钟源
	rtc_test.Init.HourFormat = RTC_HOURFORMAT_24;//RTC_HOURFORMAT_12;// 24小时制
	rtc_test.Init.TimeAdjustMode = RTC_TIME_ADJUST_SEC30;	// RTC 时钟调校 周期
	rtc_test.Init.TimeTrim = 0X00;
		
	rtc_test.State = HAL_RTC_STATE_RESET;	// 使能RTC计数器 
	HAL_RTC_Init(&rtc_test);
	/*set time and date */
	sTime_test.Hours = 12;	
	sTime_test.Minutes = 0;
	sTime_test.Seconds = 0;
	sDate_test.Date = 31;
	sDate_test.Month = 12;
	sDate_test.Year = 2019;
	sDate_test.WeekDay = RTC_WEEKDAY_SUNDAY;
//	HAL_RTC_SetTime(&rtc_test, &sTime_test, rtc_test.Init.HourFormat);
//	HAL_RTC_SetDate(&rtc_test, &sDate_test);
	HAL_RTC_SetTime_SetDate(&rtc_test, &sTime_test, rtc_test.Init.HourFormat, &sDate_test);
	printf("Enter Test RTC Calendar \r\n");
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	RTC_TimeTypeDef sTime_current = {0};
	RTC_DateTypeDef sDate_current = {0};
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

		HAL_RTC_GetTime_Date(&rtc_test, &sTime_current,&sDate_current);
		if(rtc_test.Init.HourFormat == RTC_HOURFORMAT_12)
		{
			if(sTime_current.Hours>=12)
      		{   printf("NOW Time is:%d-%d-%d PM %d:%d:%d \r\n",sDate_current.Year,sDate_current.Month,	\
				sDate_current.Date,(sTime_current.Hours-12),sTime_current.Minutes,sTime_current.Seconds);
			}
			else
			{
				printf("NOW Time is:%d-%d-%d AM %d:%d:%d \r\n",sDate_current.Year,sDate_current.Month,	\
				sDate_current.Date,sTime_current.Hours,sTime_current.Minutes,sTime_current.Seconds);
			}
		}
		else
		{
			printf("NOW Time is:%d-%d-%d  %d:%d:%d \r\n",sDate_current.Year,sDate_current.Month,	\
			sDate_current.Date,sTime_current.Hours,sTime_current.Minutes,sTime_current.Seconds);
		}
		BSP_LED_Toggle(LED1);
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



