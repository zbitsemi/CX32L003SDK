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

#define OWIRE_IT_ENABLED	 1 // OWIREʹ���ж�ģʽ
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
	HAL_NVIC_SetPriority(OWIRE_IRQn, 0);	// �ж����ȼ�
	HAL_NVIC_EnableIRQ(OWIRE_IRQn);	// OWIRE NVIC�ж�ʹ��
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
	
	gOwireHandler.Init.ClockDiv = OWIRE_CLOCK_DIVIDER_1;// ʱ��Դ��Ƶ
	gOwireHandler.Init.FirstBit = OWIRE_FIRSTBIT_LSB;// �ֽڷ��͵�λģʽ
	gOwireHandler.Init.DataSize = OWIRE_DATASIZE_8BIT; // ���δ�������8λ
	gOwireHandler.Init.ReadMode = OWIRE_RDMODE_0; // ��ͨģʽ
	gOwireHandler.Init.NoiseFilterEn = OWIRE_NOISE_FILTER_DISABLE; // ��������˲����ܽ�ֹ 
	gOwireHandler.Init.NoiseFilterClk = OWIRE_NOISE_FILTER_CLK_DIV_1;//��������˲�ʱ��ԴԤ��Ƶ
	gOwireHandler.Init.ResetCounter = 480; // �����͸�λʱ���趨����ֵ (480us~960us)
	gOwireHandler.Init.PresencePulseCounter = 60; // ��Ӧ��ʱ���趨����ֵ(60us~240us) 
	gOwireHandler.Init.BitRateCounter = 60; // ����1Bit���ݿ��(15us~60us)
	gOwireHandler.Init.DriveCounter = 3;  // ��������/дPULL0����ʱ���趨����ֵ(0us~15us)
	gOwireHandler.Init.ReadSamplingCounter = 10; //���ö�����ʱ��(1us~15us)
	gOwireHandler.Init.RecoverCounter = 13; // ����RECOVERʱ��Ϊ(TREC>1us)

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
	GPIO_InitStruct.Pin = GPIO_PIN_2;//GPIO_PIN_3; // GPIOѡ��
	GPIO_InitStruct.Mode = GPIO_MODE_AF; // ���ù���ѡ��
	GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;//GPIO_PUSHPULL;	��©���
	GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;// ��ֹ����ȥ����
	GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH; // ��ѹת������
	GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH; // ����ǿ��
	GPIO_InitStruct.Pull = GPIO_PULLUP; // ����
	GPIO_InitStruct.Alternate = GPIO_AF7_1WIRE; // ����AF7_1WIRE
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



