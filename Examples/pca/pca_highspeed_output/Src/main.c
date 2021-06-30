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

/* Public variables ---------------------------------------------------------*/
PCA_HandleTypeDef	sPcaHandle = {0}; 
PCA_OC_InitTypeDef sPcaOcInit = {0};

/* Private variables ---------------------------------------------------------*/
static uint32_t ucOcCmpCnt;

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
	printf("PCA high speed output example.\n");
	
	BSP_LED_Init(LED1);
	
	__HAL_RCC_PCA_CLK_ENABLE();
	/*********************** Configure PCA clock source  *******************************/	
  /* Initialize LPTIMx peripheral as follows:
       + Clock = PCLK/8 = 24M/8 = 3MHz
  */		
	sPcaHandle.Instance = PCAx;
	sPcaHandle.Init.ClkSrcSel = PCA_CLOCK_SOURCE_PCLKDIV32;
	sPcaHandle.Init.RunInIdleMode = PCA_IDLEMODE_DISABLE;
	HAL_PCA_OC_Init(&sPcaHandle);
	
	sPcaOcInit.CompareEnable = PCA_OC_ENABLE;
	sPcaOcInit.TogEnable = PCA_TOG_ENABLE;
	/* Interrupt will generate when counter is equal to 3000.
	*	 PCA_CH2 toggle depends not on Period, will always be 3MHz/65536 = 45.7Hz
	*/
	sPcaOcInit.Period = 3000;		
	HAL_PCA_OC_ConfigChannel(&sPcaHandle, &sPcaOcInit, PCA_CHANNEL_2);
	
  /* PCA output compare enable */	
	HAL_PCA_OC_Start_IT(&sPcaHandle, PCA_CHANNEL_2);
	HAL_NVIC_EnableIRQ(PCA_IRQn);
	
  while (1)
	{
		if(ucOcCmpCnt == 23)
		{
			ucOcCmpCnt = 0;
			BSP_LED_Toggle(LED1);
		}
	}
}



/**
  * @brief  Output compare callback in non blocking mode 
  * @param  hpca : PCA handle
  * @retval None
  */
void HAL_PCA_OutputCompareCallback(PCA_HandleTypeDef *hpca)
{
	ucOcCmpCnt++;
}



/**
  * @brief  Initializes the PCA Output Compare MSP.
  * @param  hpca : PCA handle
  * @retval None
  */
void HAL_PCA_OC_MspInit(PCA_HandleTypeDef *hpca)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_PCAx_GPIO_CLK_ENABLE();
	/**if PCAx is PCA 
	GPIO Configuration:    
	PA3     ------> PCA_CH2
	*/	
	GPIO_InitStruct.Pin = PCAx_CH0_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Alternate = PCAx_CH0_ALTERNATE_AFn;
	HAL_GPIO_Init(PCAx_CH0_PORT, &GPIO_InitStruct);

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



