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


/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t ucSendData[LENGTH] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
static uint8_t ucReceiveData[LENGTH] = {0};


/* Private macros-------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
LPUART_HandleTypeDef sLPUartxHandle = {0};



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

  /* Peripheral clock enable */
  __HAL_RCC_LPUARTx_CLK_ENABLE();	
	
	sLPUartxHandle.Instance = LPUARTx;
	sLPUartxHandle.Init.ClkSel = LPUART_CLOCK_PCLK; // ʱ��Դѡ��
	sLPUartxHandle.Init.ClkDiv = LPUART_CLOCK_DIV1; // Ԥ��Ƶ
	sLPUartxHandle.Init.LowPowerMode = LPUART_MODE_NORMAL; // ����ģʽ
	sLPUartxHandle.Init.BaudRate = BAUDRATE; // ������
	sLPUartxHandle.Init.BaudDouble = LPUART_BAUDDOUBLE_DISABLE;	// ��ֹ˫��������
	sLPUartxHandle.Init.WordLength = LPUART_WORDLENGTH_9B; // ���ݳ���
	sLPUartxHandle.Init.Parity = LPUART_PARITY_ODD; // ��У��λ
	sLPUartxHandle.Init.Mode = LPUART_MODE_TX_RX;// ���պͷ���ʹ�� 
	HAL_LPUART_Init(&sLPUartxHandle);
	
	HAL_LPUART_Transmit(&sLPUartxHandle, ucSendData, sizeof(ucSendData), TIMEOUT_MAX);
	HAL_LPUART_Receive(&sLPUartxHandle, ucReceiveData, sizeof(ucReceiveData), TIMEOUT_MAX);	

  while (1)
	{
		HAL_LPUART_Transmit(&sLPUartxHandle, ucSendData, sizeof(ucSendData), TIMEOUT_MAX);
		HAL_Delay(1000);
	}
}


/**
  * @brief  LPUART MSP Init.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval None
  */
void HAL_LPUART_MspInit(LPUART_HandleTypeDef *hlpuart)
{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
    /**if LPUARTx is LPUART 
		GPIO Configuration:    
    PC5     ------> LPUART_TXD
    PA3     ------> LPUART_RXD
    */
		__HAL_RCC_LPUARTx_RXGPIO_CLK_ENABLE();// GPIOʱ��ʹ��
    GPIO_InitStruct.Pin = LPUARTx_RX_PIN;// GPIOѡ��
    GPIO_InitStruct.Mode = GPIO_MODE_AF; // GPIO�˿ڸ��ù���
		GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	// �������
		GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE; // ��ֹ����ȥ����
		GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH;// ��ѹת������
		GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;// ����ǿ��
		GPIO_InitStruct.Pull = GPIO_PULLUP;// ����
		GPIO_InitStruct.Alternate = LPUARTx_RX_ALTERNATE_AFn;// �˿ڸ���GPIO_AF5_LPUART_RXD
    HAL_GPIO_Init(LPUARTx_RX_PORT, &GPIO_InitStruct);
		
    __HAL_RCC_LPUARTx_TXGPIO_CLK_ENABLE();	
    GPIO_InitStruct.Pin = LPUARTx_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF;
		GPIO_InitStruct.Alternate = LPUARTx_TX_ALTERNATE_AFn;
    HAL_GPIO_Init(LPUARTx_TX_PORT, &GPIO_InitStruct);			
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



