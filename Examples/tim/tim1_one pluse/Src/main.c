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

TIM_ClockConfigTypeDef sClockSourceConfig = {0};
TIM_OnePulse_InitTypeDef TIM_OnePulse_InitStruct;


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
	
  sTimxHandle.Instance = TIMx;
  sTimxHandle.Init.Prescaler = HAL_RCC_GetPCLKFreq()/TIMx_FREQ-1; // ��������ʱ��Ƶ��(CK_CNT)����fCK_PSC/(PSC[15:0]+1) ����������ʱ��Ƶ��=TIMx_FREQ
  sTimxHandle.Init.CounterMode = TIM_COUNTERMODE_UP; // ���ض���ģʽ ���������ϼ���
  sTimxHandle.Init.Period = PULSE_DELAY + PULSE_WIDTH; // TIM1_ARR ����
  sTimxHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // CKD ʱ�ӷ�Ƶ����(Clock division) 
  sTimxHandle.Init.RepetitionCounter = 0; // TIM1_RCR �ظ���������ֵ
  sTimxHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; // ��ֹ�Զ���װ��
  if (HAL_TIM_OnePulse_Init(&sTimxHandle, TIM_OPMODE_SINGLE) != HAL_OK) // ��ѡ��TIM_OPMODE_SINGLEʱ �ڷ�����һ�θ����¼�(���CENλ)ʱ��������ֹͣ��
  {
    Error_Handler();
  }
	
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL; // ETRPƵ�ʳ���2
  if (HAL_TIM_ConfigClockSource(&sTimxHandle, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
	TIM_OnePulse_InitStruct.OCMode = TIM_OCMODE_PWM1; // PWMģʽ1 TIM1_CCMR1
	TIM_OnePulse_InitStruct.Pulse = PULSE_DELAY; // CCR ����/�Ƚ�ͨ�� ֵ
	TIM_OnePulse_InitStruct.OCPolarity = TIM_OCPOLARITY_LOW; // ������� OC1�͵�ƽ��Ч
	TIM_OnePulse_InitStruct.OCNPolarity = TIM_OCNPOLARITY_LOW; // OC1N�͵�ƽ��Ч
	TIM_OnePulse_InitStruct.OCIdleState = TIM_OCIDLESTATE_SET; // ��MOE=0ʱ�����ʵ����OC1N����������OC1=1�� 
	TIM_OnePulse_InitStruct.OCNIdleState = TIM_OCNIDLESTATE_SET;  // MOE=0ʱ��������OC1N=1
	TIM_OnePulse_InitStruct.ICPolarity = TIM_ICPOLARITY_BOTHEDGE; // OC1N�͵�ƽ��Ч,OC1�͵�ƽ��Ч
	TIM_OnePulse_InitStruct.ICSelection = TIM_ICSELECTION_DIRECTTI; // CC1ͨ��������Ϊ���룬IC1ӳ����TI1��
	HAL_TIM_OnePulse_ConfigChannel(&sTimxHandle, &TIM_OnePulse_InitStruct, TIMx_CHxOUT_CHANNEL, TIMx_CHxIN_CHANNEL);
	
	HAL_TIM_OnePulse_Start(&sTimxHandle, TIMx_CHxOUT_CHANNEL);
	
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
  * @brief  Initializes the TIM One Pulse MSP.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_OnePulse_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_TIMxCHxOUT_GPIOCLK_ENABLE();		
	GPIO_InitStruct.Pin = TIMx_CHxOUT_PIN;	
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	GPIO_InitStruct.Alternate = TIMx_CHxOUT_GPIO_AFn;
	HAL_GPIO_Init(TIMx_CHxOUT_PORT, &GPIO_InitStruct);		
	
	__HAL_RCC_TIMxCHxIN_GPIOCLK_ENABLE();
	GPIO_InitStruct.Pin = TIMx_CHxIN_PIN;	
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	GPIO_InitStruct.Alternate = TIMx_CHxIN_GPIO_AFn;
	HAL_GPIO_Init(TIMx_CHxIN_PORT, &GPIO_InitStruct);	
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


