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
CRC_HandleTypeDef sCRCConfig;

uint8_t ucDataForCrcCal1[] = {0xA5, 0xB1,0x02,0x7a};
uint8_t ucDataForCrcCal2[] = {0xA5, 0xB1};
uint8_t ucDataCRC[] = {0x00,0x00};
uint32_t ulCrcResult;
uint8_t  CRCResultFlag;
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
	printf("CRC Accumulate example\n");
	printf("CRC polynomial is x16+x12+x5+1, Input data reverse, Output data reverse\n\n");	
	
	__HAL_RCC_CRC_CLK_ENABLE();
	
	sCRCConfig.Instance = CRC;
	HAL_CRC_Init(&sCRCConfig);
	
	//====================================================//
	ulCrcResult = HAL_CRC_Calculate(&sCRCConfig, ucDataForCrcCal1, sizeof(ucDataForCrcCal1));	//CRC模块复位 初始化CRC计算 对原始数据编码以计算比对检验其CRC值 
	for(uint8_t count=0; count<sizeof(ucDataForCrcCal1); count++)
	{
		printf("CRC input ucDataForCrcCal1 data is 0x%x\n", ucDataForCrcCal1[count]);
	}
	printf("CRC caculate result is 0x%x\n", ulCrcResult);
	
	CRCResultFlag = HAL_Get_CRC_RESULT_FLAG(&sCRCConfig);	// 获取CRC 当前检验标志位
	printf("CRC CRCResultFlag is 0x%x\n", CRCResultFlag);
	
	ucDataCRC[0] = ulCrcResult;
	ucDataCRC[1] = ulCrcResult>>8;
	
	ulCrcResult = HAL_CRC_Accumulate(&sCRCConfig, ucDataCRC, sizeof(ucDataCRC)); // 累计 检验已编码的CRC
	printf("CRC Accumulate result is 0x%x\n", ulCrcResult);
	CRCResultFlag = HAL_Get_CRC_RESULT_FLAG(&sCRCConfig); // 获取CRC 当前检验标志位
	printf("CRCResultFlag  is 0x%x\n\n", CRCResultFlag); 
	
	//====================================================//
	ulCrcResult = HAL_CRC_Calculate(&sCRCConfig, ucDataForCrcCal2, sizeof(ucDataForCrcCal2));
	for(uint8_t count=0; count<sizeof(ucDataForCrcCal2); count++)
	{
		printf("CRC input ucDataForCrcCal2 data is 0x%x\n", ucDataForCrcCal2[count]);	
	}
	printf("CRC caculate result is 0x%x\n", ulCrcResult);
	CRCResultFlag = HAL_Get_CRC_RESULT_FLAG(&sCRCConfig);
	printf("CRCResultFlag  is 0x%x\n", CRCResultFlag);
	
	ucDataCRC[0] = ulCrcResult;
	ucDataCRC[1] = ulCrcResult>>8;
	
	ulCrcResult = HAL_CRC_Accumulate(&sCRCConfig, ucDataCRC, sizeof(ucDataCRC));
	printf("CRC Accumulate result is 0x%x\n", ulCrcResult);
	CRCResultFlag = HAL_Get_CRC_RESULT_FLAG(&sCRCConfig);
	printf("CRCResultFlag  is 0x%x\n\n", CRCResultFlag);
	
	//====================================================//
	ulCrcResult = HAL_CRC_Calculate(&sCRCConfig, ucDataForCrcCal2, sizeof(ucDataForCrcCal2));
	for(uint8_t count=0; count<sizeof(ucDataForCrcCal2); count++)
	{
		printf("CRC input ucDataForCrcCal2 data is 0x%x\n", ucDataForCrcCal2[count]);	
	}
	printf("CRC caculate result is 0x%x\n", ulCrcResult);
	CRCResultFlag = HAL_Get_CRC_RESULT_FLAG(&sCRCConfig);
	printf("CRCResultFlag  is 0x%x\n", CRCResultFlag);
	
	ucDataCRC[0] = 0;
	ucDataCRC[1] = 0xff;
	
	ulCrcResult = HAL_CRC_Accumulate(&sCRCConfig, ucDataCRC, sizeof(ucDataCRC));
	printf("CRC Accumulate result is 0x%x\n", ulCrcResult);
	CRCResultFlag = HAL_Get_CRC_RESULT_FLAG(&sCRCConfig);
	printf("CRCResultFlag  is 0x%x\n\n", CRCResultFlag);
	
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



