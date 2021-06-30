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

/* Public variables ----------------------------------------------------------*/
LVD_HandleTypeDef 	sLvdHandle;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/


/**
  * @brief  The application entry point.
  * @retval int
  */
	uint32_t LvdMode = 0;
	uint8_t LvdModeCnt = 0;
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();		
	
  /* Configure the system clock to HIRC 24MHz*/
  SystemClock_Config();
	
  /* Configure uart1 for printf */	
	LogInit();	
	printf("LVD interrupt example\n");
	
	__HAL_RCC_LVDVC_CLK_ENABLE();
	
	sLvdHandle.Instance = LVD;
	sLvdHandle.Init.VoltageLevel = LVD_VOLLEVEL_3_3V; 
	sLvdHandle.Init.TriggerSel = LVD_TRIGGER_RISING;// 触发使能 VDD从低于阈值电压变为高于阈值电压
	sLvdHandle.Init.Action = LVD_ACTION_INTERRUPT; // LVD中断复位0：产生中断
//	sLvdHandle.Init.FltNum = 0x5FFF0000; // 滤波值
//	sLvdHandle.Init.FltClkSel = LVD_FLTCLK_PCLK; // 滤波时钟24M使能数字滤波 滤波时钟==0则为不使能
	sLvdHandle.Init.FltNum = 0x000F0000; 	// 32.768K
	sLvdHandle.Init.FltClkSel = LVD_FLTCLK_LIRC; // 滤波时钟
	HAL_LVD_Init(&sLvdHandle);	
	
	HAL_NVIC_EnableIRQ(LVD_IRQn);	// NVIC LVD中断使能
	HAL_LVD_Enable_IT(&sLvdHandle);	// LVD使能
	printf("请输入小于3.3V \n\n");
  while (1)
	{
		if(LvdMode == 1)
		{
				LvdMode = 0;
				printf("%d\n",LvdModeCnt);
				printf("LVD interrupt generated VDD <= 3.3V \n\n");
				printf("请输入大于4.4V \n\n");   
				
				sLvdHandle.Init.VoltageLevel = LVD_VOLLEVEL_4_4V;  
				sLvdHandle.Init.TriggerSel = LVD_TRIGGER_FALLING; // 触发使能 VDD从高于阈值电压变为低于阈值电压
				HAL_LVD_Init(&sLvdHandle);	// 初始化会把寄存器清除
				HAL_LVD_Enable_IT(&sLvdHandle);		
		}	
		if(LvdMode == 2)
		{
			LvdMode = 0;
			printf("%d\n",LvdModeCnt);
			printf("LVD interrupt generated VDD >= 4.4V \n\n");
			printf("请输入小于3.3V \n\n"); 
			
			sLvdHandle.Init.VoltageLevel = LVD_VOLLEVEL_3_3V;
			sLvdHandle.Init.TriggerSel = LVD_TRIGGER_RISING;
			HAL_LVD_Init(&sLvdHandle);	
			HAL_LVD_Enable_IT(&sLvdHandle);	
		}	
	}
}


/**
  * @brief  Interrupt callback in non blocking mode 
  * @param  htim : LVD handle
  * @retval None
  */
void HAL_LVD_InterruptCallback(LVD_HandleTypeDef *hlvd)
{
		LvdModeCnt++;
		if(sLvdHandle.Init.VoltageLevel == LVD_VOLLEVEL_3_3V)
		{
			LvdMode = 1;
		}	
		if(sLvdHandle.Init.VoltageLevel == LVD_VOLLEVEL_4_4V)
		{
			LvdMode = 2;
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



