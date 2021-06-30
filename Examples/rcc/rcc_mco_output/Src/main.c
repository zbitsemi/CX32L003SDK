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
static uint8_t ucClkNum = 0;
//#define CLOCKn 6  // 外挂HXT/LXT晶振SystemClock_Config函数里才能启动对应时钟源
//static const uint32_t MCO_CLOCK_NAME[CLOCKn]  = {	RCC_MCOSOURCE_HIRC, \
//																									RCC_MCOSOURCE_HXT, \
//																									RCC_MCOSOURCE_LIRC, \
//																									RCC_MCOSOURCE_LXT, \
//																									RCC_MCOSOURCE_SYSCLK, \
//																									RCC_MCOSOURCE_HCLK}; 
//static const char ClockSwitchStatus[CLOCKn][10] = {"HIRC", "HXT", "LIRC", "LXT", "SYSCLK", "HCLK"};
#define CLOCKn 4 
static const uint32_t MCO_CLOCK_NAME[CLOCKn]  = {	RCC_MCOSOURCE_HIRC, \
																									RCC_MCOSOURCE_LIRC, \
																									RCC_MCOSOURCE_SYSCLK, \
																									RCC_MCOSOURCE_HCLK}; 
static const char ClockSwitchStatus[CLOCKn][10] = {"HIRC", "LIRC", "SYSCLK", "HCLK"};
static uint8_t ucButtonPressFlag = 0;

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
	printf("Default MCO output HIRC clock at Pin PC4\n");
	printf("Press button to switch MCO output clock\n");	
	
  /* Initialize User Button */		
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI); // 初始化按键
	
	/* Default MCO ouput HIRC clock at Pin PC4 */
	HAL_RCC_MCOConfig(RCC_MCO, RCC_MCOSOURCE_HIRC, RCC_MCODIV_1);  	
	
  while (1)
	{
		if(ucButtonPressFlag)
		{
			ucButtonPressFlag = 0;
			HAL_Delay(30);
			if(HAL_GPIO_ReadPin(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN) == GPIO_PIN_RESET)
			{
				printf("MCO clock source switched to %s\n", &(ClockSwitchStatus[ucClkNum][0]));		
				__HAL_RCC_MCO_CONFIG(MCO_CLOCK_NAME[ucClkNum++], RCC_MCODIV_1);	
				if(ucClkNum >= CLOCKn)
					ucClkNum = 0;
			}				
		}
	}
}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};	
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HIRC | RCC_OSCILLATORTYPE_HXT | RCC_OSCILLATORTYPE_LXT | RCC_OSCILLATORTYPE_LIRC;
  RCC_OscInitStruct.HIRCState = RCC_HIRC_ON;
  RCC_OscInitStruct.HIRCCalibrationValue = RCC_HIRCCALIBRATION_24M;
	
//	RCC_OscInitStruct.HXTState = RCC_HXT_ON; // 只有外接高速晶振才能使能
//	RCC_OscInitStruct.LXTState = RCC_LXT_ON; // 只有外接低速晶振才能使能
	RCC_OscInitStruct.LIRCState = RCC_LIRC_ON;
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
  * @brief  EXTI line detection callbacks.
  * @param  GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */	
void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	ucButtonPressFlag = 1;
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



