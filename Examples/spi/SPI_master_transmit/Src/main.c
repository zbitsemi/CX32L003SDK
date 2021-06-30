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
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/


SPI_HandleTypeDef spi_test = {0};
FlagStatus ispi_int = RESET;
uint32_t SPI_SR_ErrorFlags;
/**
  * @brief HAL_SPI_MspInit Configuration
  * @retval None
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_SPI_CLK_ENABLE();
	
	GPIO_InitTypeDef  gpiospi={0};
	
	/* Configure the MOSI pin */
	gpiospi.Pin    = SPI_MOSI_PIN;
	gpiospi.Mode = GPIO_MODE_AF;
	gpiospi.Alternate = GPIO_AF3_SPI_MOSI; // 主机输出
	gpiospi.OpenDrain = GPIO_PUSHPULL;
	gpiospi.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	gpiospi.SlewRate = GPIO_SLEW_RATE_HIGH;
	gpiospi.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	gpiospi.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(SPI_MOSI_GPIO, &gpiospi);
	HAL_GPIO_WritePin(SPI_MOSI_GPIO, SPI_MOSI_PIN, GPIO_PIN_SET);
	
	/* Configure the CLK pin */
	gpiospi.Pin    = SPI_CLK_PIN ;
	gpiospi.Mode = GPIO_MODE_AF;
	gpiospi.Alternate = GPIO_AF3_SPI_CLK;
	gpiospi.OpenDrain = GPIO_PUSHPULL;
	gpiospi.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	gpiospi.SlewRate = GPIO_SLEW_RATE_HIGH;
	gpiospi.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	gpiospi.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(SPI_CLK_GPIO, &gpiospi);
}

/**
  * @brief SPI Interrupt call
  * @retval None
  */
void SPI_call(void)
{
	
}
/**
  * @brief SPI Init Configuration
  * @retval None
  */
void SPI_Init(void)
{
	spi_test.Instance = SPI;
	spi_test.Init.NSS = SPI_NSS_MODE_HIGH;// SSN值控制SPI_CS端口电平高
	spi_test.Init.Mode = SPI_MODE_MASTER;// 主机模式
	spi_test.Init.CLKPhase = SPI_POLARITY_HIGH; // CPOL==1 时钟极性为高
	spi_test.Init.CLKPolarity = SPI_PHASE_2EDGE;// CPHA==1 时钟相位 第二边沿 
	spi_test.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;// Fsys/8 
	HAL_SPI_Init(&spi_test);
}

void LL_SPI_Master_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t TxSize)
{
	uint16_t count = 0;
	uint8_t receive_data = 0;

	for(count = 0;count < TxSize; count++)
	{
		hspi->Instance->DATA = pTxData[count];
		while((hspi->Instance->SR&SPI_FLAG_SPIF)!=SPI_FLAG_SPIF);
		receive_data = hspi->Instance->DATA;	
	}
}
/**;
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	uint8_t WData[4] = {0};
	uint8_t WSize = 0;
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();		

  /* Configure the system clock to HIRC 24MHz*/
  SystemClock_Config();
	
	/* Initialize BSP Led for LED1 */	
	BSP_LED_Init(LED1);
  /* Configure uart1 for printf */	
	LogInit();	
	printf("Printf success using UART1, PD5-TXD, PD6-RXD\r\n");
	
	SPI_Init();// CLK MOSI两线 主机输出
	WData[0] = 0xAA;
	WData[1] = 0x00;
	WData[2] = 0x00;
	WData[3] = 0x03;
	WSize=4;
	
  while (1)
	{
		LL_SPI_Master_Transmit(&spi_test, WData, (uint16_t)WSize);
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



