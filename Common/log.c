/* Includes ------------------------------------------------------------------*/
#include "log.h"
#include "cx32l003_hal_uart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SerialInit(uint32_t baud_rate);
static void SerialSend(uint8_t data);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Configures the UART peripheral. 
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
static void Log_UART_SetConfig(UART_HandleTypeDef *huart)
{
  /*------- UART-associated registers setting : SCON Configuration ------*/
  /* Configure the UART Word Length and mode: 
		 Set the DBAUD bits according to huart->Init.BaudDouble value 
     Set the SM bits according to huart->Init.WordLength value 
     Set REN bits according to huart->Init.Mode value */
  MODIFY_REG(huart->Instance->SCON, (UART_SCON_DBAUD | UART_SCON_SM0_SM1 | UART_SCON_REN), huart->Init.BaudDouble | huart->Init.WordLength | huart->Init.Mode);

  /*-------------------------- UART BAUDCR Configuration ---------------------*/
  huart->Instance->BAUDCR = (((((huart->Init.BaudDouble >> UART_SCON_DBAUD_Pos)+1)*HAL_RCC_GetPCLKFreq())/(32*(huart->Init.BaudRate))-1) & UART_BAUDCR_BRG) | UART_BAUDCR_SELF_BRG;	

	__HAL_UART_ENABLE_IT(huart, UART_IT_TC | UART_IT_RXNE);
}

UART_HandleTypeDef huart1 = {0};

/**
  * @brief  This function initializes the log interface
  * @param  None
  * @retval None
  */
void LogInit(void)
{
#ifdef LOG_METHOD_SERIAL
		SerialInit(LOG_SERIAL_BPS);
#endif
}

void logout(bool success)
{
	if(true == success)
	{
		printf("$P\n");
	}
	else
	{
		printf("$F\n");	
	}
}


/**
  * @brief UART1 Initialization Function
  * @param None
  * @retval None
  */
static void SerialInit(uint32_t baud_rate)
{
	huart1.Instance = UART1;
	huart1.Init.BaudRate = baud_rate;
	huart1.Init.BaudDouble = UART_BAUDDOUBLE_ENABLE;	
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	
  if(huart1.gState == HAL_UART_STATE_RESET)
  {  
    /* Allocate lock resource and initialize it */
    huart1.Lock = HAL_UNLOCKED;

		GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Peripheral clock enable */
    __HAL_RCC_UART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**UART1 GPIO Configuration    
    PD5     ------> UART1_TXD
    PD6     ------> UART1_RXD
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF;
		GPIO_InitStruct.OpenDrain = GPIO_PUSHPULL;	
		GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
		GPIO_InitStruct.SlewRate = GPIO_SLEW_RATE_HIGH;
		GPIO_InitStruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Alternate = GPIO_AF5_UART1_TXD;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF;
		GPIO_InitStruct.Alternate = GPIO_AF5_UART1_RXD;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);		
  }
	
  huart1.gState = HAL_UART_STATE_BUSY;
 
  /* Set the UART Communication parameters */
  Log_UART_SetConfig(&huart1);
  
  /* Initialize the UART state */
  huart1.ErrorCode = HAL_UART_ERROR_NONE;
  huart1.gState= HAL_UART_STATE_READY;
  huart1.RxState= HAL_UART_STATE_READY;
	
}

void SerialSend(uint8_t data) 
{
	HAL_UART_Transmit(&huart1, &data, 1, 1000);  
	
}



#ifdef  __GNUC__
int _write(int file, char *data, int len)
{
	 int bytes_written;

	 for (bytes_written = 0; bytes_written < len; bytes_written++)
	 {
				#ifdef LOG_METHOD_SERIAL
				// expand LF to CR-LF
				if (*data == '\n') {
						SerialSend('\r');
				}
				SerialSend(*data);
				#else //Another method to log
						#ifdef LOG_METHOD_RAM
						*LOG_RAM_CHAR = *data;
						#endif
				#endif
				data++;
	 }

	 return bytes_written;
}

#else
int fputc(int ch, FILE *f) {
	
	/* Your implementation of fputc(). */
	#ifdef LOG_METHOD_SERIAL
					SerialSend(ch);				
	#else //Another method to log
			#ifdef LOG_METHOD_RAM
					*LOG_RAM_CHAR = *data;
			#endif
	#endif		
	
	return 0;	
}
#endif //__GNUC__

//int fputc(int ch, FILE *f) {
//	
//	/* Your implementation of fputc(). */
//	uint8_t ch_data;
//	ch_data = ch;
//	HAL_LPUART_Transmit_printf(&sLPUartxHandle,&ch_data);  
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
//	return ch;
//}

//int fputc(int ch)
//{

//USART_SendData(USART1, (u8) ch);

//while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

//return ch;

//}
void panic(const char* func)
{
	// If panic info enabled, print it out
	printf("Panic call from %s\n",func);
	/* Add any panic string desired or while loop as needed */
}
