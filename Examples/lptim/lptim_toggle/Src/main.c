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
LPTIM_HandleTypeDef sLpTimHandle = {0};

/* Private variables ---------------------------------------------------------*/
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
	
	__HAL_RCC_LPTIM_CLK_ENABLE();
	
	/************************** Configure Update frequency: FREQ **********************************/
  /* Initialize LPTIMx peripheral as follows:
       + Clock = PCLK	
       + Period = 1ms(1KHz output frequency)
       + Toggle output	
  */		
	sLpTimHandle.Instance = LPTIMx;	
	sLpTimHandle.Init.ClkSel = LPTIM_CLOCK_SOURCE_PCLK;	// 时钟源选择
	sLpTimHandle.Init.CntTimSel = LPTIM_TIMER_SELECT; // 选择定时器功能
	sLpTimHandle.Init.AutoReload = LPTIM_AUTORELOAD_ENABLE; // 自动装载使能
	sLpTimHandle.Init.Period = LPTIMx_RELOADVALUE; // 周期
	sLpTimHandle.Init.TogEnable = LPTIM_TOG_ENABLE; // TOG输出使能 
	HAL_LPTIM_Base_Init(&sLpTimHandle);
	
	HAL_LPTIM_Base_Start(&sLpTimHandle); // 定时器运行 
	
  while (1);
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
  sGpioInitConfig.Pin   = LPTIMx_TOGGLE_PIN;// PD.2
	sGpioInitConfig.Mode 	= GPIO_MODE_AF; // GPIO端口复用功能  
	sGpioInitConfig.Debounce.Enable = GPIO_DEBOUNCE_DISABLE; // 禁止输入去抖动
	sGpioInitConfig.SlewRate = GPIO_SLEW_RATE_HIGH; // 电压转换速率
	sGpioInitConfig.DrvStrength = GPIO_DRV_STRENGTH_HIGH; // 驱动强度
	sGpioInitConfig.Pull = GPIO_PULLUP; // 上拉
	sGpioInitConfig.Alternate = LPTIMx_TOGGLE_AFn;// 端口复用GPIO_AF6_LPTIM_TOG
	HAL_GPIO_Init(LPTIMx_TOGGLE_PORT, &sGpioInitConfig);		

}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};	
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HIRC | RCC_OSCILLATORTYPE_LIRC;
  RCC_OscInitStruct.HIRCState = RCC_HIRC_ON;
  RCC_OscInitStruct.HIRCCalibrationValue = RCC_HIRCCALIBRATION_24M;

  RCC_OscInitStruct.LIRCState = RCC_LIRC_ON;
	RCC_OscInitStruct.LIRCStartupValue = RCC_LIRC_STARTUP_64CYCLE;
  RCC_OscInitStruct.LIRCCalibrationValue = RCC_LIRCCALIBRATION_32K;
	
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



