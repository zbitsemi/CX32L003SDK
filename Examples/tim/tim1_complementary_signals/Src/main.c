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
TIM_HandleTypeDef sTimxHandle = {0};

/* Timer Output Compare Configuration Structure declaration */
TIM_OC_InitTypeDef sTimxOcInitHandle = {0};

/* Timer Break Configuration Structure declaration */
TIM_BreakDeadTimeConfigTypeDef sBreakConfig;

TIM_ClockConfigTypeDef sClockSourceConfig = {0};

static uint32_t uwPrescalerValue;

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
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
	
  /* Configure the system clock */
  SystemClock_Config();
	
	__HAL_RCC_TIMx_CLK_ENABLE();	
	
  /* Compute the prescaler value to have TIMx counter clock equal to TIMx_FREQ(10000) Hz */
  uwPrescalerValue = (uint32_t)(HAL_RCC_GetPCLKFreq() / TIMx_FREQ) - 1;	// 预分频值
	
  /* Set TIMx instance */
  sTimxHandle.Instance = TIMx;
	
  /* Initialize TIMx peripheral as follows:
       + Period = TIMx_PERIOD(10000-1)
       + Prescaler = (APBClock/TIMx_FREQ) - 1
       + ClockDivision = 0
       + Counter direction = Up
  */
  sTimxHandle.Init.Period            = TIMx_PERIOD;		// TIM1_ARR 周期
  sTimxHandle.Init.Prescaler         = uwPrescalerValue; // 计数器的时钟频率(CK_CNT)等于fCK_PSC/(PSC[15:0]+1) 即计数器的时钟频率=TIMx_FREQ
  sTimxHandle.Init.ClockDivision     = 0; // CKD 时钟分频因子(Clock division) 
  sTimxHandle.Init.CounterMode       = TIM_COUNTERMODE_UP; // 边沿对齐模式 计数器向上计数
  sTimxHandle.Init.RepetitionCounter = 0;// TIM1_RCR 重复计数器的值
  sTimxHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; // 禁止自动重装载
	
  if (HAL_TIM_PWM_Init(&sTimxHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
	
	sTimxOcInitHandle.OCMode = TIM_OCMODE_PWM1; // PWM模式1 TIM1_CCMR1
	sTimxOcInitHandle.OCPolarity = TIM_OCPOLARITY_LOW; // 输出极性 OC1低电平有效
	sTimxOcInitHandle.OCNPolarity = TIM_OCNPOLARITY_LOW; // OC1N低电平有效
	sTimxOcInitHandle.OCFastMode = TIM_OCFAST_ENABLE; // 输出比较1清’0’使能
	sTimxOcInitHandle.OCIdleState = TIM_OCIDLESTATE_RESET; // MOE=0时，如果实现了OC1N，则死区后OC1=0；
	sTimxOcInitHandle.OCNIdleState = TIM_OCNIDLESTATE_RESET; // MOE=0时，死区后OC1N=0
	
	sTimxOcInitHandle.Pulse = TIMx_CH1_PULSEWIDTH;	// CCR 捕获/比较通道 值
	if((HAL_TIM_PWM_ConfigChannel(&sTimxHandle, &sTimxOcInitHandle, TIM_CHANNEL_1)) != HAL_OK)
	{
    /* Initialization Error */
    Error_Handler();		
	}
	
	sTimxOcInitHandle.Pulse = TIMx_CH2_PULSEWIDTH;
	if((HAL_TIM_PWM_ConfigChannel(&sTimxHandle, &sTimxOcInitHandle, TIM_CHANNEL_2)) != HAL_OK)
	{
    /* Initialization Error */
    Error_Handler();		
	}	
	
	sTimxOcInitHandle.Pulse = TIMx_CH3_PULSEWIDTH;	
	if((HAL_TIM_PWM_ConfigChannel(&sTimxHandle, &sTimxOcInitHandle, TIM_CHANNEL_3)) != HAL_OK)
	{
    /* Initialization Error */
    Error_Handler();		
	}	
	
	sTimxOcInitHandle.Pulse = TIMx_CH4_PULSEWIDTH;	
	if((HAL_TIM_PWM_ConfigChannel(&sTimxHandle, &sTimxOcInitHandle, TIM_CHANNEL_4)) != HAL_OK)
	{
    /* Initialization Error */
    Error_Handler();		
	}		
		
  /* Set the Break feature & Dead time */
  sBreakConfig.BreakState       = TIM_BREAK_ENABLE;	 // 开启刹车输入 刹车输入高电平有效
  sBreakConfig.DeadTime         = 300; // 死区时间
  sBreakConfig.OffStateRunMode  = TIM_OSSR_ENABLE; // 当定时器不工作时，一旦CCxE=1或CCxNE=1，首先开启OC/OCN并输出无效电平，然后置OC/OCN使能输出信号=1
  sBreakConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;// 当定时器不工作时，一旦CCxE=1或CCxNE=1，OC/OCN首先输出其空闲电平，然后OC/OCN使能输出信号=1。
  sBreakConfig.LockLevel        = TIM_LOCKLEVEL_1;  // 锁定级别1
  sBreakConfig.BreakPolarity    = TIM_BREAKPOLARITY_HIGH;	// 刹车输入高电平有效
  sBreakConfig.AutomaticOutput  = TIM_AUTOMATICOUTPUT_ENABLE; // MOE能被软件置’1’或在下一个更新事件被自动置’1’
			
  if(HAL_TIM_ConfigBreakDeadTime(&sTimxHandle, &sBreakConfig) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }	
	
  /*##-3- Start PWM signals generation #######################################*/ 
  /* Start channel 1 */
  if(HAL_TIM_PWM_Start(&sTimxHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }	
  /* Start channel 1N */	
  if(HAL_TIM_PWMN_Start(&sTimxHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
  
  /* Start channel 2 */
  if(HAL_TIM_PWM_Start(&sTimxHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
  /* Start channel 2N */
  if(HAL_TIM_PWMN_Start(&sTimxHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
  
  /* Start channel 3 */
  if(HAL_TIM_PWM_Start(&sTimxHandle, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
  /* Start channel 3N */
  if(HAL_TIM_PWMN_Start(&sTimxHandle, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
	
  /* Start channel 4 */
  if(HAL_TIM_PWM_Start(&sTimxHandle, TIM_CHANNEL_4) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }	
	
  while (1);
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


