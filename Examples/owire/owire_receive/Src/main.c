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
#include "string.h"

#define OWIRE_IT_ENABLED	 1 // OWIRE使能中断模式
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private macros-------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void OneWire_Init(void);

/* Private user code ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
UART_HandleTypeDef sUartxHandle = {0};
OWIRE_HandleTypeDef gOwireHandler;
int flag_owire_rx_cplt;

void HAL_OWIRE_RxCpltCallback(OWIRE_HandleTypeDef *howire)
{
	flag_owire_rx_cplt = 1;	
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
	
	//	 PD5->UART1_TXD PD6->UART1_RXD 9600
	LogInit();
	
	/* Initialize the One-Wire interface */
	OneWire_Init();
	#if (OWIRE_IT_ENABLED == 1)	
	HAL_NVIC_SetPriority(OWIRE_IRQn, 0);	// 中断优先级
	HAL_NVIC_EnableIRQ(OWIRE_IRQn);	// OWIRE NVIC中断使能
	#endif
	uint8_t rxData[10];	

  while (1)
	{
	#if (OWIRE_IT_ENABLED == 1)	
			flag_owire_rx_cplt = 0;
			HAL_OWIRE_Receive_IT(&gOwireHandler, rxData, 3);
			while(!flag_owire_rx_cplt);
			HAL_Delay(500);
		  printf("OWIRE Receive IT rxData is: %d %d% d\n",rxData[0],rxData[1],rxData[2]);	
	#else
			HAL_OWIRE_Receive(&gOwireHandler, rxData, 3, 1000);
			printf("OWIRE Receive rxData is: %d %d% d\n",rxData[0],rxData[1],rxData[2]);	
			HAL_Delay(1000);
	#endif
	}
}

/**
  * @brief One-Wire Configuration
  * @retval None
  */
static void OneWire_Init(void)
{
	memset(&gOwireHandler, 0, sizeof(gOwireHandler));
	gOwireHandler.Instance = OWIRE;
	
	gOwireHandler.Init.ClockDiv = OWIRE_CLOCK_DIVIDER_1;// 时钟源分频
	gOwireHandler.Init.FirstBit = OWIRE_FIRSTBIT_LSB;// 字节发送的位模式
	gOwireHandler.Init.DataSize = OWIRE_DATASIZE_8BIT; // 单次处理数据8位
	gOwireHandler.Init.ReadMode = OWIRE_RDMODE_0; // 普通模式
	gOwireHandler.Init.NoiseFilterEn = OWIRE_NOISE_FILTER_DISABLE; // 输入端子滤波功能禁止 
	gOwireHandler.Init.NoiseFilterClk = OWIRE_NOISE_FILTER_CLK_DIV_1;//输入端子滤波时钟源预分频
	gOwireHandler.Init.ResetCounter = 480; // 主发送复位时间设定计数值 (480us~960us)
	gOwireHandler.Init.PresencePulseCounter = 60; // 从应答时间设定计数值(60us~240us) 
	gOwireHandler.Init.BitRateCounter = 60; // 设置1Bit数据宽度(15us~60us)
	gOwireHandler.Init.DriveCounter = 3;  // 主器件读/写PULL0驱动时间设定计数值(0us~15us)
	gOwireHandler.Init.ReadSamplingCounter = 10; //设置读采样时间(1us~15us)
	gOwireHandler.Init.RecoverCounter = 13; // 设置RECOVER时间为(TREC>1us)

  if (HAL_OWIRE_Init(&gOwireHandler) != HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief  OWIRE MSP Init.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_OWIRE_MspInit(OWIRE_HandleTypeDef *howire)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* Peripheral clock enable */
	__HAL_RCC_OWIRE_CLK_ENABLE();

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	/**One-Wire GPIO Configuration    
	PC3 / PD2 
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_2;//GPIO_PIN_3; // GPIO选择
	GPIO_InitStruct.Mode = GPIO_MODE_AF; // 复用功能选择
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;//GPIO_PUSHPULL;	开漏输出
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;// 禁止输入去抖动
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH; // 电压转换速率
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH; // 驱动强度
	GPIO_InitStruct.Pull = GPIO_PULLUP; // 上拉
	GPIO_InitStruct.Alternate = GPIO_AF7_1WIRE; // 复用AF7_1WIRE
	//HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
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



