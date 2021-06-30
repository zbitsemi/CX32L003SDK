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


/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

VC_HandleTypeDef test_vc = {0};
GPIO_InitTypeDef  gpioInitStruct = {0};
static uint32_t test_flag = 0;

void VC_INT_CallBack(void)
{ 
	if(HAL_VC_Get_INT_Flag(&test_vc)==SET)
	{
		test_flag = 1;
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_5);	
		HAL_VC_Clear_INT_Flag(&test_vc);
	}
}
void GPIO_Select_Config()
{
	GPIO_InitTypeDef  gpiovc={0};
	if((POSITIVE_INPUT_SOURCE == HAL_VC_INPUT_1) || (NEGATIVE_INPUT_SOURCE == HAL_VC_INPUT_1))
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
		gpiovc.Mode = GPIO_MODE_AF;
		gpiovc.Alternate = GPIO_ANALOG_VCIN1;
		gpiovc.Pin = GPIO_PIN_5;
		gpiovc.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOC, &gpiovc);
		
	}
	if((POSITIVE_INPUT_SOURCE == HAL_VC_INPUT_2) || (NEGATIVE_INPUT_SOURCE == HAL_VC_INPUT_2))
	{
		__HAL_RCC_GPIOD_CLK_ENABLE();
		gpiovc.Mode = GPIO_MODE_AF;
		gpiovc.Alternate = GPIO_ANALOG_VCIN2;
		gpiovc.Pin = GPIO_PIN_2;
		gpiovc.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOD, &gpiovc);
		
	}
		
	
}
void VC_Clock_Config(void)
{
		__HAL_RCC_LVDVC_CLK_ENABLE();
}
void VC_Init()
{
	
	GPIO_Select_Config();
	VC_Clock_Config();
	
	test_vc.Instance = VC;
	test_vc.Init.V25div = V25_DIV_SET;
	test_vc.Init.NinSel = NEGATIVE_INPUT_SOURCE;
	test_vc.Init.PinSel = POSITIVE_INPUT_SOURCE;
	test_vc.Init.Fliter_Num = VC_FILTER_NUM;
	test_vc.Init.Filter_Clk = HAL_VC_FILTER_CLK_PCLK;
	test_vc.Init.Filter_Enable = HAL_VC_FILTER_ENABLE;
	test_vc.Init.INT_Mode = HAL_VC_RISE_INT_ENABLE;
	test_vc.Init.INT_Enable = HAL_VC_INT_ENABLE;

	HAL_VC_Init(&test_vc);
	/* Set interrupt priority and turn on interrupt*/
		HAL_NVIC_SetPriority(VC_IRQn, PRIORITY_LOW);
		HAL_NVIC_EnableIRQ(VC_IRQn);
}
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

  /* Initialize BSP Led for LED1 */	
	BSP_LED_Init(LED1);

	// 测试VC 比较器的响应时间 程序 
	// PB.4 输入方波 接HAL_VC_INPUT_1 PC.5 即大于小于2.5V 产生中断 PB.5 IO 取反输出 
	/* Enable the GPIO_LED Clock */
 __HAL_RCC_GPIOB_CLK_ENABLE();
  /* Configure the GPIO_LED pin */
  gpioInitStruct.Pin  = GPIO_PIN_4 | GPIO_PIN_5;
	
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT;
	gpioInitStruct.OpenDrain = GPIO_PUSHPULL;	
	gpioInitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	gpioInitStruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	gpioInitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	gpioInitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &gpioInitStruct);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET);
  /* Configure uart1 for printf */	
	LogInit();	
	printf("Enter VC TEST!\r\n");
	VC_Init();
  while (1)
	{
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);	
		if(test_flag == 1)
		{
			test_flag = 0;
			printf("Filter Interrupt!\r\n");
		}
			if(HAL_VC_Get_OutPut_State(&test_vc) != RESET)
					printf("Filter out is Hight\r\n");
			else
				printf("Filter out is Slow\r\n");
		BSP_LED_Toggle(LED1);
		HAL_Delay(500);
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



