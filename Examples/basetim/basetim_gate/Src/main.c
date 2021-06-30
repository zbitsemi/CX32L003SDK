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
BASETIM_HandleTypeDef sBaseTimHandle = {0};
uint32_t ulBaseTimUpdateCnt = 0;
uint32_t BaseTimer11Count = 0;	
/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
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
	sBaseTimHandle.Instance = BASETIMx;	// TIM11
	sBaseTimHandle.Init.GateEnable = BASETIM_GATE_ENABLE;  // 端口GATE有效
	sBaseTimHandle.Init.GateLevel = BASETIM_GATELEVEL_LOW; // 端口GATE 极性控制 低电平有效 
	sBaseTimHandle.Init.CntTimSel = BASETIM_TIMER_SELECT;  // 定时器功能，定时器由PCLK来进行计数
	sBaseTimHandle.Init.AutoReload = BASETIM_AUTORELOAD_ENABLE; //定时器 模式2自动重装载 
	sBaseTimHandle.Init.MaxCntLevel = BASETIM_MAXCNTLEVEL_16BIT; //计数最大值选择	
	sBaseTimHandle.Init.OneShot = BASETIM_REPEAT_MODE;	// 计数器重复模式
	sBaseTimHandle.Init.Prescaler = BASETIM_PRESCALER_DIV1; // TIM预除频 000:分频数1
	sBaseTimHandle.Init.Period = BASETIM_MAXCNTVALUE_16BIT - HAL_RCC_GetPCLKFreq()/FREQ;	// 周期
	HAL_BASETIM_Base_Init(&sBaseTimHandle);
	HAL_BASETIM_Base_Start_IT(&sBaseTimHandle);	//中断使能
	HAL_NVIC_EnableIRQ(BASETIMx_IRQn); //NVR中断使能
	printf("Base timer TIM11 external gate signal control PC.5 example\n");
  while (1)
	{
		if(ulBaseTimUpdateCnt == LED_PERIOD)
		{
			ulBaseTimUpdateCnt = 0;
			BSP_LED_Toggle(LED1);
			BaseTimer11Count++;
			printf("Base timer update interrupt generated count: %d\r\n",BaseTimer11Count);			
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
	ulBaseTimUpdateCnt++;
}

/**
  * @brief  Initializes the BASETIM Base MSP.
  * @param  hbasetim : BASETIM handle
  * @retval None
  */
void HAL_BASETIM_Base_MspInit(BASETIM_HandleTypeDef *hbasetim)
{
	GPIO_InitTypeDef  sGpioInitConfig={0};	
	
  /* Enable the base timer gate gpio clock */
  BASETIMx_GATE_GPIO_CLK_ENABLE();
	
  /* Configure the base timer GATE input pin */
  sGpioInitConfig.Pin   = BASETIMx_GATE_PIN;
	sGpioInitConfig.Mode 	= GPIO_MODE_AF;	// GPIO端口复用功能
	sGpioInitConfig.Debounce.Enable = GPIO_DEBOUNCE_DISABLE; // 禁止输入去抖动
	sGpioInitConfig.SlewRate = GPIO_SLEW_RATE_HIGH;	// 电压转换速率
	sGpioInitConfig.DrvStrength = GPIO_DRV_STRENGTH_HIGH; // 驱动强度
	sGpioInitConfig.Pull = GPIO_PULLUP; // 上拉
	sGpioInitConfig.Alternate = BASETIMx_GATE_AFn; // 端口复用GPIO_AF6_TIM11_GATE
	HAL_GPIO_Init(BASETIMx_GATE_PORT, &sGpioInitConfig);
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



