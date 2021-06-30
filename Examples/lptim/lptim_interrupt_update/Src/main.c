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

/* Public variables ----------------------------------------------------------*/
LPTIM_HandleTypeDef sLpTimHandle = {0};

/* Private variables ---------------------------------------------------------*/
static uint32_t ulLpTimUpdateCnt = 0;
uint32_t LptimBaseTimerCount = 0;
/* Private constants ---------------------------------------------------------*/
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
	
	/* Initialize BSP Led for LED1 */	
	BSP_LED_Init(LED1);
	
	__HAL_RCC_LPTIM_CLK_ENABLE();
	/************************** Configure Update frequency: FREQ **********************************/
	sLpTimHandle.Instance = LPTIMx;	 
	sLpTimHandle.Init.ClkSel = LPTIM_CLOCK_SOURCE_LIRC ;		// 时钟选择
	sLpTimHandle.Init.CntTimSel = LPTIM_TIMER_SELECT;		// 选择定时器功能 
	sLpTimHandle.Init.AutoReload = LPTIM_AUTORELOAD_ENABLE;  // 模式2自动重装载16位计数器/定时器 
	sLpTimHandle.Init.Period = LPTIMx_FREQ;	 // 周期 从BGLOAD的值向上计数
	HAL_LPTIM_Base_Init(&sLpTimHandle);
	
	HAL_LPTIM_Base_Start_IT(&sLpTimHandle);	// 中断使能控制 定时器运行控制
	HAL_NVIC_EnableIRQ(LPTIMx_IRQn);	
	printf("Base timer LPTIM example\n");
  while (1)
	{
		if(ulLpTimUpdateCnt == LED_FREQ)
		{
			ulLpTimUpdateCnt = 0;
			BSP_LED_Toggle(LED1);		
			LptimBaseTimerCount++;
			printf("Base timer update count: %d\r\n",LptimBaseTimerCount);	
		}
	}
}


/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : BASETIM handle
  * @retval None
  */
void HAL_LPTIM_PeriodElapsedCallback(LPTIM_HandleTypeDef *hlptim)
{
	ulLpTimUpdateCnt++;
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
  RCC_OscInitStruct.LIRCCalibrationValue = RCC_LIRCCALIBRATION_38K;	
	
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



