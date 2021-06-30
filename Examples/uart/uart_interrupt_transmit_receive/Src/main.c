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

static uint8_t ucRxCompleteFlag = 0;

/* Private macros-------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
UART_HandleTypeDef sUartxHandle = {0};



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
  __HAL_RCC_UARTx_CLK_ENABLE();	
	
	sUartxHandle.Instance = UARTx; // UART0 
	sUartxHandle.Init.BaudRate = BAUDRATE; // 波特率
	sUartxHandle.Init.BaudDouble = UART_BAUDDOUBLE_DISABLE;// 双波特率禁用 
	sUartxHandle.Init.WordLength = UART_WORDLENGTH_8B; //数据长度
	sUartxHandle.Init.Parity = UART_PARITY_NONE; // 无校验
	sUartxHandle.Init.Mode = UART_MODE_TX_RX; // 接收和发送使能 
	HAL_UART_Init(&sUartxHandle);
	
	HAL_UART_Transmit_IT(&sUartxHandle, ucSendData, sizeof(ucSendData));
	HAL_UART_Receive_IT(&sUartxHandle, ucReceiveData, sizeof(ucReceiveData));	
	HAL_NVIC_EnableIRQ(UARTx_IRQn); // 中断使能
	
  while (1)
	{
		/* UART receive LENGTH datas then transmit the received datas */		
		if(ucRxCompleteFlag == 1)
		{
			ucRxCompleteFlag = 0;
			HAL_UART_Transmit_IT(&sUartxHandle, ucReceiveData, sizeof(ucReceiveData));	
			HAL_UART_Receive_IT(&sUartxHandle, ucReceiveData, sizeof(ucReceiveData));				
		}
	}
}


/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	ucRxCompleteFlag = 1;
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
  * @brief  UART MSP Init.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
		GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_UARTx_GPIO_CLK_ENABLE();
    /**if UARTx is UART0 
		GPIO Configuration:    
    PA1     ------> UART0_RXD
    PA2     ------> UART0_TXD
    */
    GPIO_InitStruct.Pin = UARTx_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF;
		GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	
		GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
		GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH;
		GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Alternate = UARTx_RX_ALTERNATE_AFn;
    HAL_GPIO_Init(UARTx_RX_PORT, &GPIO_InitStruct);
		
    GPIO_InitStruct.Pin = UARTx_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF;
		GPIO_InitStruct.Alternate = UARTx_TX_ALTERNATE_AFn;
    HAL_GPIO_Init(UARTx_TX_PORT, &GPIO_InitStruct);		
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



