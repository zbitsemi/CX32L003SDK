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
LPTIM_HandleTypeDef sLpTimHandle = {0};

TIM_HandleTypeDef sTimxHandle = {0};	
TIM_IC_InitTypeDef sTimxIcInitHandle = {0};

TIM_ClockConfigTypeDef sClockSourceConfig = {0};


/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t uiPrescalerValue, uiCaptureValue, uiCaptureValueOld, uiCaptureValueNew, uiFrequency;
static uint8_t ucCaptureCmpFlag, ucUpdateFlag;
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
	
	LogInit();
	printf("TIMx input capture example. \n");
	
	__HAL_RCC_LPTIMx_CLK_ENABLE();
	
	/*********************** Configure Update frequency: LPTIMx_FREQ *******************************/
  /* Initialize LPTIMx peripheral as follows:
       + Clock = PCLK	
       + Period = 1ms(1KHz output frequency)
       + Toggle output	
  */	
	sLpTimHandle.Instance = LPTIMx;	
	sLpTimHandle.Init.ClkSel = LPTIM_CLOCK_SOURCE_PCLK;
	sLpTimHandle.Init.CntTimSel = LPTIM_TIMER_SELECT;
	sLpTimHandle.Init.AutoReload = LPTIM_AUTORELOAD_ENABLE;
	sLpTimHandle.Init.Period = LPTIMx_RELOADVALUE;
	sLpTimHandle.Init.TogEnable = LPTIM_TOG_ENABLE;
	HAL_LPTIM_Base_Init(&sLpTimHandle);
  /* Start LPTIMx instance, output toggle signal */	
	HAL_LPTIM_Base_Start(&sLpTimHandle);	
	
	__HAL_RCC_TIMx_CLK_ENABLE();	
  /* Compute the prescaler value to have TIMx counter clock equal to TIMx_FREQ(1000000) Hz */
  uiPrescalerValue = (uint32_t)(HAL_RCC_GetPCLKFreq() / TIMx_FREQ) - 1;
  /* Set TIMx instance */
  sTimxHandle.Instance = TIMx;	
  /* Initialize TIMx peripheral as follows:
       + Period = TIMx_PERIOD(1000000-1)
       + Prescaler = (APBClock/TIMx_FREQ) - 1
       + ClockDivision = 0
       + Counter direction = Up
  */
  sTimxHandle.Init.Period            = TIMx_PERIOD;
  sTimxHandle.Init.Prescaler         = uiPrescalerValue;
  sTimxHandle.Init.ClockDivision     = 0;
  sTimxHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
  sTimxHandle.Init.RepetitionCounter = 0;
  sTimxHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	
  if (HAL_TIM_IC_Init(&sTimxHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
		
	sTimxIcInitHandle.ICPolarity = TIM_ICPOLARITY_RISING;	
	sTimxIcInitHandle.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sTimxIcInitHandle.ICPrescaler = TIM_ICPSC_DIV1;
	sTimxIcInitHandle.ICFilter = 0x00;

	if(HAL_TIM_IC_ConfigChannel(&sTimxHandle, &sTimxIcInitHandle, TIM_CHANNEL_1))
	{
    /* Initialization Error */
    Error_Handler();			
	}
  /* Start TIMx instance, enable update interrupt, start TIMx channel1 input capture*/		
	HAL_TIM_Base_Start_IT(&sTimxHandle);
	HAL_TIM_IC_Start_IT(&sTimxHandle, TIM_CHANNEL_1);	
	HAL_NVIC_EnableIRQ(TIMx_IRQn);
	
  while (1)
	{
		if(ucCaptureCmpFlag == 1)
		{
			ucCaptureCmpFlag = 0;
			uiCaptureValueNew = uiCaptureValue;
			if(uiCaptureValueNew != uiCaptureValueOld)
			{
				if(uiCaptureValueNew > uiCaptureValueOld)
				{	
					uiFrequency = TIMx_FREQ/(uiCaptureValueNew - uiCaptureValueOld);
				}
			}
			uiCaptureValueOld = uiCaptureValueNew;
		}
		if(ucUpdateFlag == 1)
		{
			ucUpdateFlag = 0;
			printf("Frequecy is %d Hz. \n", uiFrequency);
		}
		
	}
}



/**
  * @brief  Input Capture callback in non blocking mode 
  * @param  htim : TIM IC handle
  * @retval None
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	ucCaptureCmpFlag = 1;
	uiCaptureValue = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1);
	
}


/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	ucUpdateFlag = 1;

}



/**
  * @brief  Initializes the LPTIM Base MSP.
  * @param  hlptim : LPTIM handle
  * @retval None
  */
void HAL_LPTIM_Base_MspInit(LPTIM_HandleTypeDef *hlptim)
{
	GPIO_InitTypeDef  sGpioInitConfig={0};

  /* Enable the low power timer toggle gpio clock */
  LPTIMx_TOGGLE_GPIO_CLK_ENABLE();	
  /* Configure the low power timer TOGGLE input pin */
  sGpioInitConfig.Pin   = LPTIMx_TOGGLE_PIN;
	sGpioInitConfig.Mode 	= GPIO_MODE_AF;
	sGpioInitConfig.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	sGpioInitConfig.SlewRate = GPIO_SLEW_RATE_HIGH;
	sGpioInitConfig.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	sGpioInitConfig.Pull = GPIO_PULLUP;
	sGpioInitConfig.Alternate = LPTIMx_TOGGLE_AFn;
	HAL_GPIO_Init(LPTIMx_TOGGLE_PORT, &sGpioInitConfig);		

}



/**
  * @brief  Initializes the TIM Input Capture MSP.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_TIMxCH1IN_GPIOCLK_ENABLE();		
	GPIO_InitStruct.Pin = TIMx_CH1IN_PIN;	
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	GPIO_InitStruct.Alternate = TIMx_CH1IN_GPIO_AFn;
	HAL_GPIO_Init(TIMx_CH1IN_PORT, &GPIO_InitStruct);		

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


