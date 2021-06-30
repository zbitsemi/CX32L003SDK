/**
  ******************************************************************************
  * @file    main.c
	* @author  MCU Software Team
	* @Version V1.0.0
  * @Date    21-Oct-2019
  * @brief   main function
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Public variables ----------------------------------------------------------*/
TIM_HandleTypeDef sTimxHandle = {0};	
TIM_OC_InitTypeDef sTimxOcInitHandle = {0};

TIM_ClockConfigTypeDef sClockSourceConfig = {0};
TIM_OnePulse_InitTypeDef TIM_OnePulse_InitStruct;

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
  uwPrescalerValue = (uint32_t)(HAL_RCC_GetPCLKFreq() / TIMx_FREQ) - 1;
	
  /* Set TIMx instance */
  sTimxHandle.Instance = TIMx;
	
  /* Initialize TIMx peripheral as follows:
       + Period = TIMx_PERIOD(10000-1)
       + Prescaler = (APBClock/TIMx_FREQ) - 1
       + ClockDivision = 0
       + Counter direction = Up
  */
  sTimxHandle.Init.Period            = TIMx_PERIOD;
  sTimxHandle.Init.Prescaler         = uwPrescalerValue;
  sTimxHandle.Init.ClockDivision     = 0;
  sTimxHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
  sTimxHandle.Init.RepetitionCounter = 0;
  sTimxHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	
  if (HAL_TIM_OC_Init(&sTimxHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
	
	sTimxOcInitHandle.OCMode = TIM_OCMODE_PWM1;
	sTimxOcInitHandle.OCPolarity = TIM_OCPOLARITY_LOW;
	sTimxOcInitHandle.OCNPolarity = TIM_OCNPOLARITY_LOW;
	sTimxOcInitHandle.OCFastMode = TIM_OCFAST_ENABLE;
	sTimxOcInitHandle.OCIdleState = TIM_OCIDLESTATE_RESET;
	sTimxOcInitHandle.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	
	sTimxOcInitHandle.Pulse = TIMx_CH1_PULSEWIDTH;	
	if((HAL_TIM_OC_ConfigChannel(&sTimxHandle, &sTimxOcInitHandle, TIM_CHANNEL_1)) != HAL_OK)
	{
    /* Initialization Error */
    Error_Handler();		
	}
	
	sTimxOcInitHandle.Pulse = TIMx_CH2_PULSEWIDTH;
	if((HAL_TIM_OC_ConfigChannel(&sTimxHandle, &sTimxOcInitHandle, TIM_CHANNEL_2)) != HAL_OK)
	{
    /* Initialization Error */
    Error_Handler();		
	}	
	
	sTimxOcInitHandle.Pulse = TIMx_CH3_PULSEWIDTH;	
	if((HAL_TIM_OC_ConfigChannel(&sTimxHandle, &sTimxOcInitHandle, TIM_CHANNEL_3)) != HAL_OK)
	{
    /* Initialization Error */
    Error_Handler();		
	}	
	
	sTimxOcInitHandle.Pulse = TIMx_CH4_PULSEWIDTH;	
	if((HAL_TIM_OC_ConfigChannel(&sTimxHandle, &sTimxOcInitHandle, TIM_CHANNEL_4)) != HAL_OK)
	{
    /* Initialization Error */
    Error_Handler();		
	}		
	
	HAL_TIM_OC_Start(&sTimxHandle, TIM_CHANNEL_1);
	HAL_TIM_OC_Start(&sTimxHandle, TIM_CHANNEL_2);	
	HAL_TIM_OC_Start(&sTimxHandle, TIM_CHANNEL_3);	
	HAL_TIM_OC_Start(&sTimxHandle, TIM_CHANNEL_4);
	
  while (1);
}



/**
  * @brief  Initializes the TIM Output Compare MSP.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_TIMxCH1OUT_GPIOCLK_ENABLE();		
	GPIO_InitStruct.Pin = TIMx_CH1OUT_PIN;	
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	GPIO_InitStruct.Alternate = TIMx_CH1OUT_GPIO_AFn;
	HAL_GPIO_Init(TIMx_CH1OUT_PORT, &GPIO_InitStruct);		
	
	__HAL_RCC_TIMxCH2OUT_GPIOCLK_ENABLE();
	GPIO_InitStruct.Pin = TIMx_CH2OUT_PIN;		
	GPIO_InitStruct.Alternate = TIMx_CH2OUT_GPIO_AFn;
	HAL_GPIO_Init(TIMx_CH2OUT_PORT, &GPIO_InitStruct);		
	
	__HAL_RCC_TIMxCH3OUT_GPIOCLK_ENABLE();	
	GPIO_InitStruct.Pin = TIMx_CH3OUT_PIN;		
	GPIO_InitStruct.Alternate = TIMx_CH3OUT_GPIO_AFn;
	HAL_GPIO_Init(TIMx_CH3OUT_PORT, &GPIO_InitStruct);	

	__HAL_RCC_TIMxCH4OUT_GPIOCLK_ENABLE();
	GPIO_InitStruct.Pin = TIMx_CH4OUT_PIN;		
	GPIO_InitStruct.Alternate = TIMx_CH4OUT_GPIO_AFn;
	HAL_GPIO_Init(TIMx_CH4OUT_PORT, &GPIO_InitStruct);
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


