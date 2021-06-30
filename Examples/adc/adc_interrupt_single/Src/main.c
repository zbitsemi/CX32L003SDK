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

/* Public variables ---------------------------------------------------------*/
ADC_HandleTypeDef						sAdcHandle = {0};
ADC_ThresholdConfTypeDef 		sAdcThreasHoldInit;
uint32_t uiAdcDat = {0};
uint8_t ucAdcCh4CnvCmpFlag;

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
	
  /* Configure the system clock to HIRC 24MHz*/
  SystemClock_Config();
	
  /* Configure uart1 for printf */	
	LogInit();	
	printf("ADC single mode interrupt example\n");
	
	__HAL_RCC_ADC_CLK_ENABLE();
	
  /* Configure ADC:
	*						-- single mode
	*						-- select channel4
	*						-- software start ADC conversion
	*						-- Channel4 will be converted
	*/		
	
	sAdcHandle.Instance = ADCx;
	sAdcHandle.Init.SamplingTime = ADC_SAMPLE_8CYCLE;  // 采样周期 
	sAdcHandle.Init.ClkSel = ADC_CLOCK_PCLK_DIV16; // ADC时钟分频
	sAdcHandle.Init.SingleContinueMode = ADC_MODE_SINGLE; // 单次转换模式 
	sAdcHandle.Init.SingleChannelSel = ADC_SINGLE_CHANNEL_4;  // 单通道选择
	sAdcHandle.Init.AutoAccumulation = ADC_AUTOACC_DISABLE;// 禁止ADC转换结果自动累加
	sAdcHandle.Init.CircleMode = ADC_MULTICHANNEL_NONCIRCLE; // 禁止ADC循环转换模式
	sAdcHandle.Init.ExternalTrigConv1 = ADC_SOFTWARE_START; //禁用自动触发ADC转换 
	HAL_ADC_Init(&sAdcHandle);
	
	sAdcThreasHoldInit.CompareMode = ADC_COMP_THRESHOLD_NONE; // 禁止 ADC比较控制
	HAL_ADC_ThresholdConfig(&sAdcHandle, &sAdcThreasHoldInit);
	
	HAL_ADC_Start_IT(&sAdcHandle);	// 启动ADC中断
	HAL_NVIC_EnableIRQ(ADC_IRQn); // 使能ADC中断
	
  while (1)
	{
		if(ucAdcCh4CnvCmpFlag == 1)
		{
			ucAdcCh4CnvCmpFlag = 0;
			uiAdcDat = HAL_ADC_GetValue(&sAdcHandle, ADC_SINGLE_CHANNEL_4);	
			printf("ADC channel 4 data is %d\n", uiAdcDat);	
			HAL_ADC_Start_IT(&sAdcHandle);  // 启动ADC中断
		}		
		HAL_Delay(1000);
		
	}
}



/**
  * @brief  Single channel conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_SingleChannel_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	ucAdcCh4CnvCmpFlag = 1;
}



/**
  * @brief  Initializes the ADC MSP.
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_ADCxAINx_GPIO_CLK_ENABLE();
  /**if ADCx is ADC 
  GPIO Configuration:    
  PD3     ------> ADC_AIN4
  */
  GPIO_InitStruct.Pin = ADCx_AINx_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; // 模拟输入
  GPIO_InitStruct.OpenDrain = GPIO_OPENDRAIN;	// 开漏输出
  GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE; // 禁止输入去抖动
  GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH; // 电压转换速率
  GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;// 驱动强度
  GPIO_InitStruct.Pull = GPIO_NOPULL; // 无上下拉
  HAL_GPIO_Init(ADCx_AINx_PORT, &GPIO_InitStruct); 
			
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



