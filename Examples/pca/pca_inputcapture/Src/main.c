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
LPTIM_HandleTypeDef sLpTimHandle = {0};

PCA_HandleTypeDef	sPcaHandle = {0}; 
PCA_IC_InitTypeDef sPcaIcInit = {0};


/* Private variables ---------------------------------------------------------*/
static uint32_t uiCaptureValue, uiCaptureValueOld, uiCaptureValueNew, uiFrequency;
static uint8_t ucCaptureCmpFlag;
static uint32_t uiOverflowCnt;


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
	printf("PCA input capture example.\n");
	
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
	
	
	__HAL_RCC_PCA_CLK_ENABLE();
	/*********************** Configure PCA clock source  *******************************/	
  /* Initialize LPTIMx peripheral as follows:
       + Clock = PCLK/8 = 24M/8 = 3MHz
  */		
	sPcaHandle.Instance = PCAx;
	sPcaHandle.Init.ClkSrcSel = PCA_CLOCK_SOURCE_PCLKDIV8;
	sPcaHandle.Init.RunInIdleMode = PCA_IDLEMODE_DISABLE;
	HAL_PCA_IC_Init(&sPcaHandle);
	
	sPcaIcInit.ICPolarity = PCA_INPUT_POLARITY_FALLING;
	HAL_PCA_IC_ConfigChannel(&sPcaHandle, &sPcaIcInit, PCA_CHANNEL_3);
	
	HAL_PCA_Start_IT(&sPcaHandle, PCA_IT_CC3 | PCA_IT_OVERFLOW);
	HAL_NVIC_EnableIRQ(PCA_IRQn);
		
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
					/* PCA clock source is PCLK/8 = 24M/8 = 3MHz */
					uiFrequency = 3000000/(uiCaptureValueNew - uiCaptureValueOld);
				}
			}
			uiCaptureValueOld = uiCaptureValueNew;
		}
		/* print frequency every second */
		if(uiOverflowCnt == 50)
		{
			uiOverflowCnt = 0;
			printf("Frequecy is %d Hz. \n", uiFrequency);
		}
	}
}


/**
  * @brief  Overflow callback in non blocking mode 
  * @param  hpca : PCA handle
  * @retval None
  */
void HAL_PCA_OverflowCallback(PCA_HandleTypeDef *hpca)
{
	uiOverflowCnt++;
}



/**
  * @brief  Input capture callback in non blocking mode 
  * @param  hpca : PCA handle
  * @retval None
  */
void HAL_PCA_InputCaptureCallback(PCA_HandleTypeDef *hpca)
{
	ucCaptureCmpFlag = 1;
	uiCaptureValue = __HAL_PCA_GET_COMPARE(hpca, PCA_CHANNEL_3);
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
  * @brief  Initializes the PCA Input Capture MSP.
  * @param  hpca : PCA handle
  * @retval None
  */
void HAL_PCA_IC_MspInit(PCA_HandleTypeDef *hpca)
{
		GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_PCAx_GPIO_CLK_ENABLE();
    /**if PCAx is PCA 
		GPIO Configuration:    
    PC6     ------> PCA_CH3
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



