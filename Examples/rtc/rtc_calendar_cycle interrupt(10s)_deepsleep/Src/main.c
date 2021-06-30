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

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
#define TEST_RTC_CLOCK 				RTC_CLOCK_LIRC	// RTC时钟选择				
#define TEST_RTC_CYCLE_TIME 	HAL_RTC_ALARM2_10S	// 周期中断 定时10S

RTC_HandleTypeDef rtc_test = {0};
RTC_TimeTypeDef sTime_test = {0};
RTC_DateTypeDef sDate_test = {0};
GPIO_InitTypeDef  GPIO_InitStruct = {0};
uint32_t test_inflag = 0;
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
	rtc_test.Init.HourFormat = RTC_HOURFORMAT_24;	// 24小时制
	rtc_test.Init.TimeAdjustMode = RTC_TIME_ADJUST_SEC30;	// RTC 时钟调校 周期
	rtc_test.Init.TimeTrim = 0X00;	// 时钟补偿时间
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
	HAL_RTC_SetTime_SetDate(&rtc_test, &sTime_test, rtc_test.Init.HourFormat, &sDate_test);	// TRC 时间 日期设置

	HAL_RTC_Alarm2_Config(&rtc_test,ENABLE, (HAL_RTCAlarm2TypeDef)TEST_RTC_CYCLE_TIME);	// 周期闹钟2计数周期设定
	/* Set interrupt priority and turn on interrupt*/
	HAL_NVIC_SetPriority(RTC_IRQn, PRIORITY_LOW);// 中断优先级选择
	HAL_RTC_Alarm_INT_Config(&rtc_test,RTC_ALARM_2,ENABLE); // 使能ALAM2周期中断 
	HAL_RTC_Alarm_Clear_Flag(RTC_ALARM_2); // 周期闹钟2中断原始状态被清除
	HAL_NVIC_EnableIRQ(RTC_IRQn); // 使能 RTC_IRQn
	
	printf("Enter Test RTC Calendar and ALARM2 10S \r\n");
	
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
	
	GPIO_Init();	
	
  /* Initialize BSP Led for LED1 */	
	BSP_LED_Init(LED1);
	
  /* Configure uart1 for printf */	
	LogInit();	

	RTCClock_Config();
	RTC_Init();
	
	printf("Test RTC Calendar ALARM2 10S wake up the sleeping \r\n\n");
	
	log_GPIO_DeInit(); //进入睡眠关闭串口IO复用功能
	HAL_PWR_EnterDEEPSLEEPMode();	 //进入睡眠
	while (1)
	{
		if(test_inflag == 1)
			{
				test_inflag = 0;
				log_GPIO_EnInit(); 
				printf("Get RTC ALARM2 interrupt! \r\n");
		
				HAL_RTC_GetTime_Date(&rtc_test, &sTime_current,&sDate_current);	// 获取 RTC 时间
				if(rtc_test.Init.HourFormat == RTC_HOURFORMAT_12)
				{
					if(sTime_current.Hours>=12)
					{  printf("NOW Time is:%d-%d-%d PM %d:%d:%d %d \r\n",sDate_current.Year,sDate_current.Month,	\
										sDate_current.Date,(sTime_current.Hours-12),sTime_current.Minutes,sTime_current.Seconds,sDate_current.WeekDay);
					}
					else
					{
						printf("NOW Time is:%d-%d-%d AM %d:%d:%d %d \r\n",sDate_current.Year,sDate_current.Month,	\
										sDate_current.Date,sTime_current.Hours,sTime_current.Minutes,sTime_current.Seconds, sDate_current.WeekDay);
					}
				}
				else
				{
					printf("NOW Time is:%d-%d-%d  %d:%d:%d \r\n",sDate_current.Year,sDate_current.Month,	\
										sDate_current.Date,sTime_current.Hours,sTime_current.Minutes,sTime_current.Seconds);
				}
				printf(" \r\n");	
				log_GPIO_DeInit(); 
				HAL_PWR_EnterDEEPSLEEPMode();	
		 }
	}

}
/**
  * @brief log_GPIO_EnInit
  * @retval None
  */
void log_GPIO_EnInit(void)
{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
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
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
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
/**
  * @brief GPIO Init 
  * @retval None
  */
void GPIO_Init(void)
{
//  特别注意 
//	复位期间和复位后，复用功能未开启，并且除了调试引脚以外的所有I/O端口都被配置为浮空输入模式。 
// 	GPIO复位完成后要设置为GPIO输出模式 置0状态

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
//	关闭SWD功能 配置PC7和PD1的端子功能模式  周边模块功能模式使能
//		RCC->UNLOCK =  0x55AA6699;
//		RCC->SWDIOCR = (0x5A69 << RCC_SWDIOCR_KEY_Pos);	
//		RCC->UNLOCK =  0x55AA6698;	
	
		
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT; // GPIO输出模式
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
		
		HAL_GPIO_WritePin(GPIOA,(GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3), GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(GPIOB,(GPIO_PIN_4|GPIO_PIN_5), GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(GPIOC,(GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6), GPIO_PIN_RESET);
	//	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7, GPIO_PIN_RESET); // SWD 
		
	//	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_RESET); // SWD 
		HAL_GPIO_WritePin(GPIOD,(GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6), GPIO_PIN_RESET);
}	
/**
  * @brief RTC INT callback function
  * @retval None
  */
void RTC_INT_CallBack(void)
{
	if(HAL_RTC_Alarm_Get_Flag(RTC_ALARM_2)==SET) // 获取周期闹钟2中断是否被激活
	{
		HAL_RTC_Alarm_Clear_Flag(RTC_ALARM_2); // 周期闹钟2中断原始状态被清除
		test_inflag = 1;
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



