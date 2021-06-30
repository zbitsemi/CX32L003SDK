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
BASETIM_HandleTypeDef sBaseTim10Handle = {0};
BASETIM_HandleTypeDef sBaseTim11Handle = {0};
/* Private variables ---------------------------------------------------------*/
static uint32_t ulBaseTimUpdateCnt = 0;
static uint32_t ulBaseTimUpdateCnt1 = 0;
uint32_t BaseTimer10Count = 0;
uint32_t BaseTimer11Count = 0;
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
	
	__HAL_RCC_BASETIM_CLK_ENABLE();
	/************************** Configure Update frequency: FREQ **********************************/
	/***!!! (HAL_RCC_GetPCLKFreq()/BASETIM_MAXCNTVALUE_16BIT < FREQ < HAL_RCC_GetPCLKFreq()) !!!!**/
	sBaseTim10Handle.Instance = BASETIMx; // TIM10
	sBaseTim10Handle.Init.CntTimSel = BASETIM_TIMER_SELECT;		// 定时器功能，定时器由PCLK来进行计数。
	sBaseTim10Handle.Init.AutoReload = BASETIM_AUTORELOAD_ENABLE; // 模式2自动重装载计数器/定时器 
	sBaseTim10Handle.Init.MaxCntLevel = BASETIM_MAXCNTLEVEL_16BIT; // TimerSize=0：max count value=0xFFFF; 
	sBaseTim10Handle.Init.OneShot = BASETIM_REPEAT_MODE; 	// 重复模式
	sBaseTim10Handle.Init.Prescaler = BASETIM_PRESCALER_DIV1; // TIM预除频选择
	sBaseTim10Handle.Init.Period = BASETIM_MAXCNTVALUE_16BIT - HAL_RCC_GetPCLKFreq()/FREQ; // 周期
	HAL_BASETIM_Base_Init(&sBaseTim10Handle);
	HAL_BASETIM_Base_Start_IT(&sBaseTim10Handle);
	HAL_NVIC_EnableIRQ(BASETIMx_IRQn);
	printf("Base timer TIM10 update interrupt example\n");
	
	sBaseTim11Handle.Instance = TIM11; // TIM11
	sBaseTim11Handle.Init.CntTimSel = BASETIM_TIMER_SELECT; // 定时器功能，定时器由PCLK来进行计数。
	sBaseTim11Handle.Init.AutoReload = BASETIM_AUTORELOAD_ENABLE;  //定时器 模式2自动重装载 
	sBaseTim11Handle.Init.MaxCntLevel = BASETIM_MAXCNTLEVEL_16BIT; //计数最大值选择	
	sBaseTim11Handle.Init.OneShot = BASETIM_REPEAT_MODE; 	// 计数器重复模式
	sBaseTim11Handle.Init.Prescaler = BASETIM_PRESCALER_DIV1; // TIM预除频 000:分频数1
	sBaseTim11Handle.Init.Period = BASETIM_MAXCNTVALUE_16BIT - HAL_RCC_GetPCLKFreq()/2000; // 周期
	HAL_BASETIM_Base_Init(&sBaseTim11Handle);
	HAL_BASETIM_Base_Start_IT(&sBaseTim11Handle);
	HAL_NVIC_EnableIRQ(TIM11_IRQn);
	printf("Base timer TIM11 update interrupt example\n");
  while (1)
	{
		if(ulBaseTimUpdateCnt >= 1000)
		{
			ulBaseTimUpdateCnt = 0;
			BSP_LED_Toggle(LED1);
			BaseTimer10Count++;
			printf("Base timer TIM10 update interrupt generated count: %d\r\n",BaseTimer10Count);			
		}
		if(ulBaseTimUpdateCnt1>= 1000)
		{
			ulBaseTimUpdateCnt1 = 0;
			BaseTimer11Count++;
			printf("Base timer TIM11 update interrupt generated count: %d\r\n",BaseTimer11Count);	
		}	
	}
}


/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : BASETIM handle
  * @retval None
  */
void HAL_BASETIM_PeriodElapsedCallback(BASETIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM10)
	{
		ulBaseTimUpdateCnt++;
	}
	if(htim->Instance == TIM11)
	{
		ulBaseTimUpdateCnt1++;
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



