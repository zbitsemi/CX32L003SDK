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
BEEP_HandleTypeDef sBeepHandle = {0};

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
	
	__HAL_RCC_BEEP_CLK_ENABLE();
	
	sBeepHandle.Instance = BEEPx;
	sBeepHandle.Init.ClkSel = BEEP_CLOCK_PCLK; // 时钟源选择
	sBeepHandle.Init.OutFreqDiv = HAL_RCC_GetPCLKFreq()/BEEPx_DIVFREQ;	//蜂鸣器时钟分频得到 fBEEP 
	sBeepHandle.Init.OutFreqSel = BEEP_OUTFREQSEL_DIV8;	// 得到fBEEP_O蜂鸣信号 /8 
	HAL_BEEP_Init(&sBeepHandle);
	
	/* Start Beep */
	HAL_BEEP_Start(&sBeepHandle);
	printf("Beep PD.4 output 8K HZ example.\n");
  while (1);
}



/**
  * @brief  Initializes the BEEP Base MSP.
  * @param  hbeep : BEEP handle
  * @retval None
  */
void HAL_BEEP_MspInit(BEEP_HandleTypeDef *hbeep)
{
	GPIO_InitTypeDef  sGpioInitConfig={0};
	
  /* Enable the beep output gpio clock */
  BEEPx_GPIO_CLK_ENABLE();	
  /* Configure beep output gpio pin */
  sGpioInitConfig.Pin   = BEEPx_PIN;	
	sGpioInitConfig.Mode 	= GPIO_MODE_AF; // GPIO端口复用功能
	sGpioInitConfig.Debounce.Enable = GPIO_DEBOUNCE_DISABLE; // 禁止输入去抖动
	sGpioInitConfig.SlewRate = GPIO_SLEW_RATE_HIGH; // 电压转换速率
	sGpioInitConfig.DrvStrength = GPIO_DRV_STRENGTH_HIGH; // 驱动强度
	sGpioInitConfig.Pull = GPIO_PULLUP; // 上拉
	sGpioInitConfig.Alternate = BEEPx_AFn; // GPIO_AF7_BEEP
	HAL_GPIO_Init(BEEPx_PORT, &sGpioInitConfig);	
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



