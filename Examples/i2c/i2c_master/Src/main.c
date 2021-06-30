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

#define I2C_SPEED_RATE	100   //uint khz

#define EEPROM_DEVICE_ADDRESS	    0XA0	// 从机设备地址
#define EEPROM_REGISTER1_ADDRESS	0X40   	// 寄存器地址 1
#define EEPROM_REGISTER2_ADDRESS	0X41	// 寄存器地址 2
extern UART_HandleTypeDef huart1;
I2C_HandleTypeDef i2c_test = {0};
FlagStatus i2c_int = RESET;

uint8_t pS1_Data[] = {EEPROM_REGISTER1_ADDRESS,0X77, 0X55};
uint8_t pR1_Data[] = {0X00, 0X00};
uint8_t pR2_Data[] = {0X00, 0X00};
uint8_t preg1_Data[] = {EEPROM_REGISTER1_ADDRESS};

void I2C_Master_Clear_Error(void);
/**
  * @brief I2C Clock Configuration
  * @retval None
  */
void I2CClock_Config(void)
{
	__HAL_RCC_I2C_CLK_ENABLE();
}

/**
  * @brief I2C_Write_EEPROM
	* @param  dev_address i2c device address
	*					reg_address register address
	*					wdata handle to write data
	*					size write size <=16
  * @retval ret result HAL_OK  or HAL_ERROR 
  */
HAL_StatusTypeDef I2C_Write_EEPROM(uint8_t dev_address,uint8_t reg_address,uint8_t *wdata,uint8_t size)
{
	uint8_t data[17] = {0};
	uint8_t i = 0;
	HAL_StatusTypeDef  ret = HAL_ERROR;
	
	data[0] = reg_address;  
	for(i=0;i<size;i++)
	{
		data[i+1]= wdata[i];
	}
	ret = HAL_I2C_Master_Transmit(&i2c_test, dev_address, data, size+1);

	return ret;
}
/**
  * @brief I2C_Read_EEPROM
	* @param  dev_address i2c device address
	*					reg_address register address
	*					rdata handle to read data
	*					size read size <=16
  * @retval ret result HAL_OK  or HAL_ERROR
  */
HAL_StatusTypeDef I2C_Read_EEPROM(uint8_t dev_address,uint8_t *reg_address,uint8_t tsize, uint8_t *rdata,uint8_t rsize)
{
	HAL_StatusTypeDef  ret = HAL_ERROR;
	ret = HAL_I2C_Master_Receive(&i2c_test, dev_address, reg_address,tsize, rdata, rsize);
	return ret;
}


/**
  * @brief IWDG Init Configuration
  * @retval None
  */
void I2C_Init(void)
{
	GPIO_InitTypeDef  gpioi2c={0};
  /* Configure the GPIO_LED pin */
//  gpioi2c.Pin    = GPIO_PIN_3;
//	gpioi2c.Mode = GPIO_MODE_AF;	// GPIO端口复用功能 
//	gpioi2c.Alternate = GPIO_AF4_I2C_SDA; 
//	gpioi2c.OpenDrain = GPIO_OPENDRAIN; // 开漏输出
//	gpioi2c.Debounce.Enable = GPIO_DEBOUNCE_DISABLE; // 禁止输入去抖动
//	gpioi2c.SlewRate = GPIO_SLEW_RATE_LOW; // 电压转换速率
//	gpioi2c.DrvStrength = GPIO_DRV_STRENGTH_LOW; // 驱动强度
//	gpioi2c.Pull = GPIO_NOPULL; // 无上下拉
//	HAL_GPIO_Init(GPIOC, &gpioi2c);
//	
//	
//	gpioi2c.Pin = GPIO_PIN_4;
//	gpioi2c.Mode = GPIO_MODE_AF; 
//	gpioi2c.Alternate = GPIO_AF4_I2C_SCL;
//	gpioi2c.OpenDrain = GPIO_OPENDRAIN; 
//	gpioi2c.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
//	gpioi2c.SlewRate = GPIO_SLEW_RATE_LOW;
//	gpioi2c.DrvStrength = GPIO_DRV_STRENGTH_LOW;
//	gpioi2c.Pull = GPIO_NOPULL;	
//	HAL_GPIO_Init(GPIOC, &gpioi2c);

	gpioi2c.Pin    = GPIO_PIN_5;
	gpioi2c.Mode = GPIO_MODE_AF; // GPIO端口复用功能 
	gpioi2c.Alternate = GPIO_AF4_I2C_SDA;
	gpioi2c.OpenDrain = GPIO_OPENDRAIN; // 开漏输出
	gpioi2c.Debounce.Enable = GPIO_DEBOUNCE_DISABLE; // 禁止输入去抖动
	gpioi2c.SlewRate = GPIO_SLEW_RATE_HIGH; // 电压转换速率
	gpioi2c.DrvStrength = GPIO_DRV_STRENGTH_HIGH; // 驱动强度
	gpioi2c.Pull = GPIO_PULLUP;			// 上拉
	HAL_GPIO_Init(GPIOB, &gpioi2c);
	
	
	gpioi2c.Pin = GPIO_PIN_4;
	gpioi2c.Mode = GPIO_MODE_AF;
	gpioi2c.Alternate = GPIO_AF4_I2C_SCL;
	gpioi2c.OpenDrain = GPIO_OPENDRAIN; 
	gpioi2c.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	gpioi2c.SlewRate = GPIO_SLEW_RATE_HIGH;
	gpioi2c.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	gpioi2c.Pull = GPIO_PULLUP;	
	HAL_GPIO_Init(GPIOB, &gpioi2c);
	/*set init handle*/

	i2c_test.Instance = I2C;
	i2c_test.Init.master = I2C_MASTER_MODE_ENABLE; // 主机模式使能
	i2c_test.Init.slave = I2C_SLAVE_MODE_DISABLE; // 从机模式禁止
	i2c_test.Mode = HAL_I2C_MODE_MASTER; // 主机模式
	printf("Enter Test I2C Master\r\n");
	
	
	i2c_test.Init.broadack = I2C_BROAD_ACK_DISABLE; // 广播地址应答禁止
	i2c_test.Init.speedclock = I2C_SPEED_RATE; // I2C传输速率  
	i2c_test.State = HAL_I2C_STATE_RESET; //
	
	HAL_I2C_Init(&i2c_test);
}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
//	HAL_StatusTypeDef  ret = HAL_ERROR;
	
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();		
	
  /* Configure the system clock to HIRC 24MHz*/
	SystemClock_Config();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	/* Initialize BSP Led for LED1 */	
	BSP_LED_Init(LED1);
  /* Configure uart1 for printf */	
	LogInit();
	printf("Printf success using UART1, PD5-TXD, PD6-RXD\r\n");
	
	I2CClock_Config();
	I2C_Init();
	// 给从机初始化写入操作寄存器+数据
	HAL_I2C_Master_Transmit(&i2c_test, EEPROM_DEVICE_ADDRESS, pS1_Data, 3);
	HAL_Delay(100);
	while (1)
	{
		I2C_Master_Clear_Error();
		
		// 写入从机地址+操作寄存器1 返回读数据不一样
		preg1_Data[0] = EEPROM_REGISTER1_ADDRESS;
		I2C_Read_EEPROM(EEPROM_DEVICE_ADDRESS,preg1_Data,1,pR1_Data,2);
		if((pR1_Data[0]!=pS1_Data[0])||(pR1_Data[1]!=pS1_Data[1]))
		{
			printf("pR1_Data Write or read error!!! data0 =0x%x,data1=0x%x\r\n",pR1_Data[0],pR1_Data[1]);
		}
		else
		{
			printf("pR1_Data Write or read OK!!! \r\n");
		}
		HAL_Delay(1); 
		// 写入从机地址+操作寄存器2 返回读数据不一样
		preg1_Data[0] = EEPROM_REGISTER2_ADDRESS;
		I2C_Read_EEPROM(EEPROM_DEVICE_ADDRESS,preg1_Data,1,pR2_Data,2);
		
		if((pR2_Data[0]!=pS1_Data[0])||(pR2_Data[1]!=pS1_Data[2]))
		{
			printf("pR2_Data Write or read error!!! data0 =0x%x,data1=0x%x\r\n",pR2_Data[0],pR2_Data[1]);
		}
		else
		{
			printf("pR2_Data Write or read OK!!! \r\n");
		}
		
		BSP_LED_Toggle(LED1);
		HAL_Delay(100);
	}
}



void I2C_Master_Clear_Error(void)
{
	if(i2c_test.State == HAL_I2C_STATE_ERROR) // 判断是否报错，清除标志
	{
		i2c_test.State = HAL_I2C_STATE_READY;
		i2c_test.ErrorCode = HAL_I2C_ERROR_NONE;
		HAL_I2C_Clear_Interrupt_Flag(&i2c_test);
		HAL_I2C_Stop_Config(&i2c_test,ENABLE);
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



