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

static uint8_t ucClkNum = 0;
//#define CLOCKn 	4 // 外挂HXT/LXT晶振SystemClock_Config函数里才能启动对应时钟源
//static const uint32_t SYSTEM_CLOCK_NAME[CLOCKn]  = {	RCC_SYSCLKSOURCE_HIRC, \
//																											RCC_SYSCLKSOURCE_HXT, \
//																											RCC_SYSCLKSOURCE_LIRC, \
//																											RCC_SYSCLKSOURCE_LXT}; 
#define CLOCKn 	2  
static const uint32_t SYSTEM_CLOCK_NAME[CLOCKn]  = {	RCC_SYSCLKSOURCE_HIRC, \
																											RCC_SYSCLKSOURCE_LIRC}; 
static uint8_t ucButtonPressFlag = 0;
static RCC_ClkInitTypeDef sRccConfig = {0};
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
	
	/* Initialize BSP Led for LED1 */	
	BSP_LED_Init(LED1);	
	
  /* Configure uart1 for printf */	
	LogInit();	
	
	printf("Default System clock is HIRC 24M\n");	
//	printf("Press User Button(USR SW1) to switch clock circularly, HIRC->HXT->LIRC->LXT->HIRC.....\n");		
	printf("Press User Button(USR SW1) to switch clock circularly, HIRC->LIRC->HIRC.....\n");	
  /* Initialize User Button */		
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);	// 初始化按键
	printf("LED will flashing 4 times when switching.\n");		
	while (1)
	{		
		if(ucButtonPressFlag)
		{
			ucButtonPressFlag = 0;
			HAL_Delay(30);
			if(HAL_GPIO_ReadPin(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN) == GPIO_PIN_RESET) // // 按键触发切换系统时钟频率
			{
				/**Initializes the CPU, AHB and APB busses clocks 
				*/
				sRccConfig.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK;
				sRccConfig.SYSCLKSource = SYSTEM_CLOCK_NAME[ucClkNum++]; // 时钟源切换
				sRccConfig.AHBCLKDivider = RCC_HCLK_DIV1;
				sRccConfig.APBCLKDivider = RCC_PCLK_DIV1;
				if (HAL_RCC_ClockConfig(&sRccConfig) != HAL_OK)
				{
					Error_Handler();
				}					
				for(uint8_t count = 0; count < (CLOCKn*2); count++)
				{
					BSP_LED_Toggle(LED1);
					/* If system clock switch to LIRC or LXT, system tick overflow will be modified from 1KHz to 100Hz */
					if((sRccConfig.SYSCLKSource == RCC_SYSCLKSOURCE_LIRC) || (sRccConfig.SYSCLKSource == RCC_SYSCLKSOURCE_LXT))
						HAL_Delay(100);
					else
						HAL_Delay(1000);					
				}		
				
				if(ucClkNum >= CLOCKn)
					ucClkNum = 0;
			}				
		}
	}
}


/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */	
void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	ucButtonPressFlag = 1;
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};	
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HIRC | RCC_OSCILLATORTYPE_HXT | RCC_OSCILLATORTYPE_LXT | RCC_OSCILLATORTYPE_LIRC;
  RCC_OscInitStruct.HIRCState = RCC_HIRC_ON;
  RCC_OscInitStruct.HIRCCalibrationValue = RCC_HIRCCALIBRATION_24M;
//	RCC_OscInitStruct.HXTState = RCC_HXT_ON; // 只有外接高速晶振才能使能
//	RCC_OscInitStruct.LXTState = RCC_LXT_ON; // 只有外接低速晶振才能使能
	RCC_OscInitStruct.LIRCState = RCC_LIRC_ON;
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
  /* User can add his own implementation to report the HAL error return state */
	while(1);
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
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */


/* Private function -------------------------------------------------------*/



