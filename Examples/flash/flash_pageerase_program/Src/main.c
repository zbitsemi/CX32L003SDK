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
static FLASH_EraseInitTypeDef 	sFlashEraseInit;
static uint32_t uiErrorPage;
static uint32_t uiAddress = 0;
unsigned char uiAddress_cnt = 0;
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
	printf("Flash program example.\n");
	
	/* Flash page erase from FLASH_PROGRAM_ADDRESS_START to FLASH_PROGRAM_ADDRESS_END*/
	sFlashEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;	// 页擦除 
	sFlashEraseInit.PageAddress = FLASH_PROGRAM_ADDRESS_START; // 开始擦除地址 必须以512Byte为单位
	sFlashEraseInit.NbPages	= (FLASH_PROGRAM_ADDRESS_END - FLASH_PROGRAM_ADDRESS_START)/FLASH_PAGE_SIZE + 1;
	if(HAL_FLASH_Erase(&sFlashEraseInit, &uiErrorPage) != HAL_OK)
	{
    Error_Handler();
	}
  uiAddress = FLASH_PROGRAM_ADDRESS_START;
  while (uiAddress < FLASH_PROGRAM_ADDRESS_END)
  {
    if (FLASH_Byte_Read(uiAddress) != 0xFF) // 判断地址数据是否擦除成功
    {			
      /* Error occurred while writing data in Flash memory.
         User can add here some code to deal with this error */
			Error_Handler();	
			uiAddress = uiAddress + 1;			
    }
		else
		{
			uiAddress = uiAddress + 1;
		}
  }		
	printf("Flash program using byte programming.\n");		
	/* Flash program using halfword from FLASH_PROGRAM_ADDRESS_START to FLASH_PROGRAM_ADDRESS_END*/	
  uiAddress = FLASH_PROGRAM_ADDRESS_START;	 // 起始写入地址
  while (uiAddress < FLASH_PROGRAM_ADDRESS_END)
  {
    if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, uiAddress, FLASH_PROGRAM_DATA_BYTE) == HAL_OK) // 写入操作 字节写入 0xAA
    {			
      uiAddress = uiAddress + 1;
    }
    else
    {
      /* Error occurred while writing data in Flash memory.
         User can add here some code to deal with this error */
			printf("Error: Flash program using byte programming.\n");	
    }
  }
	uiAddress = FLASH_PROGRAM_ADDRESS_START;	 // 起始写入地址
	uiAddress_cnt = 0; 
  while (uiAddress < FLASH_PROGRAM_ADDRESS_END)
  {
    if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, uiAddress, uiAddress_cnt) == HAL_OK) // 写入操作 字节写入 0
    {			
      uiAddress = uiAddress + 1;
    }
    else
    {
      /* Error occurred while writing data in Flash memory.
         User can add here some code to deal with this error */
			printf("Error: Flash program using byte programming.\n");	
    }
  }
  uiAddress = FLASH_PROGRAM_ADDRESS_START;
  while (uiAddress < FLASH_PROGRAM_ADDRESS_END)
  {
    if (FLASH_Byte_Read(uiAddress) != FLASH_PROGRAM_DATA_BYTE)	// 判断数据是否写入正确
    {			
      /* Error occurred while writing data in Flash memory.
         User can add here some code to deal with this error */
			Error_Handler();	
			uiAddress = uiAddress + 1;			
    }
		else
		{
			uiAddress = uiAddress + 1;
		}
  }	
	printf("Byte programming ok.\n");		

  while (1);
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
	printf("Error Address is 0x%x\n", uiAddress);
	printf("Error Data is 0x%x\n", *(uint8_t*)(uiAddress));	
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



