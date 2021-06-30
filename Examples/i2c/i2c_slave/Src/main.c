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

#define EEPROM_DEVICE_ADDRESS	 0XA0 // 本机地址

#define EEPROM_REGISTER1_ADDRESS	0X40   // 寄存器地址 1
#define EEPROM_REGISTER2_ADDRESS	0X41   // 寄存器地址 2

I2C_HandleTypeDef i2c_test = {0};
FlagStatus i2c_int = RESET;
volatile uint8_t test_falg = 0;
uint8_t pData[DATA_LEN_MAX]={0};
uint16_t RV_Size = 0;
uint16_t i2c_RX_receive_data;
uint16_t i2c_TX_Send_data;
uint16_t TR_Size = 2;
uint32_t printf_i2c_flag;
volatile static uint8_t cnt= 0;
volatile static uint8_t i2c_status= 0;//0-idle 1-receive 2-trastmate
volatile uint8_t receive_size = 0,transmit_size = 0;
void I2C_Init(void);
/**
  * @brief I2C IRQ Configuration
  * @retval None
  */
void I2C_IRQ_Config()
{
	HAL_NVIC_SetPriority(I2C_IRQn,I2C_TEST_IRQ_LEVEL);
	HAL_NVIC_EnableIRQ(I2C_IRQn);
}


void HAL_I2C_SlaveCallback(I2C_HandleTypeDef *hi2c)
{
	uint32_t i2c_flag = 0XFF;

	HAL_NVIC_DisableIRQ(I2C_IRQn);
	HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
	switch(i2c_flag)
	{
		case I2C_FLAG_SLAVE_RX_SLAW_ACK: // 60H 接收自身的SLA+W 
			receive_size = 0;
			break;
		case I2C_FLAG_SLAVE_RX_SDATA_ACK: // 80H 接收数据字节
			pData[receive_size] = hi2c->Instance->DATA; 
			i2c_RX_receive_data = 	pData[receive_size];
			test_falg = TEST_FLAG_TRANSM;
			receive_size++;
			break;
		case I2C_FLAG_SLAVE_TX_SLAW_ACK: // A8H
			transmit_size = 0;
			HAL_I2C_Send_Byte(hi2c,pData[transmit_size]);  // 发送寄存器地址 即上次接收的第一个数据
			test_falg = TEST_FLAG_RECIVE;	
			i2c_TX_Send_data = pData[transmit_size];
			transmit_size++;
			break;
		case I2C_FLAG_SLAVE_TX_DATA_ACK: // B8H 
			if(pData[0] == EEPROM_REGISTER1_ADDRESS)	
			{
				transmit_size = 1;
			}
			if(pData[0] == EEPROM_REGISTER2_ADDRESS)	
			{
				transmit_size = 2;
			}
			HAL_I2C_Send_Byte(hi2c,pData[transmit_size]); // 发送一个数据字节
			test_falg = TEST_FLAG_RECIVE;	
			i2c_TX_Send_data = pData[transmit_size];
			transmit_size++;
			break;
		default:
			break;
	}
//	printf("I2C Slave i2c_flag =0x%x\r\n",i2c_flag);  //不能在回调函数调用，造成堵塞 I2C丢帧
	printf_i2c_flag = i2c_flag;
	i2c_flag = 0XFF;
	HAL_I2C_ACK_Config(hi2c, ENABLE);
	HAL_I2C_Clear_Interrupt_Flag(hi2c);
	NVIC_ClearPendingIRQ(I2C_IRQn);
  	HAL_NVIC_EnableIRQ(I2C_IRQn);
		
}

/**
  * @brief IWDG Init Configuration
  * @retval None
  */
void I2C_Init(void)
{
	/*set init handle*/
	i2c_test.Instance = I2C;
	i2c_test.Init.master = I2C_MASTER_MODE_DISABLE;// 主机模式禁止
	i2c_test.Init.slave = I2C_SLAVE_MODE_ENABLE; // 从机模式使能
	i2c_test.Mode = HAL_I2C_MODE_SLAVE; // 从机模式
	i2c_test.Init.slaveAddr = (EEPROM_DEVICE_ADDRESS>>1); // 从机地址
	printf("Enter Test I2C Slave\r\n");
	
	
	i2c_test.Init.broadack = I2C_BROAD_ACK_DISABLE; // 广播地址应答禁止
	i2c_test.Init.speedclock = I2C_SPEED_RATE; // I2C传输速率  
	i2c_test.State = HAL_I2C_STATE_RESET; //I2C状态重置
	
	HAL_I2C_Init(&i2c_test);
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
	__HAL_RCC_GPIOA_CLK_ENABLE(); // GPIO时钟初始化
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	/* Initialize BSP Led for LED1 */	
	BSP_LED_Init(LED1);
  /* Configure uart1 for printf */	
	LogInit();	
	printf("Printf success using UART1, PD5-TXD, PD6-RXD\r\n");

	I2C_Init();
	I2C_IRQ_Config();
	
	while (1)
	{
		if(printf_i2c_flag)
		{
			printf("I2C Slave i2c_flag =0x%x\r\n",printf_i2c_flag); 
			printf_i2c_flag = 0;
		}
		if(test_falg == TEST_FLAG_TRANSM)
		{
			test_falg = 0;
			printf("I2C Slave i2c_RX_receive_data =0x%x\r\n",i2c_RX_receive_data);
		}
		if(test_falg==TEST_FLAG_RECIVE)
		{
			printf("I2C Slave i2c_TX_Send_data =0x%x\r\n",i2c_TX_Send_data);
			BSP_LED_Toggle(LED1);
			test_falg = 0;
		}
	}
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	__HAL_RCC_I2C_CLK_ENABLE();
	
		GPIO_InitTypeDef  gpioi2c={0};
  /* Configure the GPIO_LED pin */
  gpioi2c.Pin    = GPIO_PIN_3;
	gpioi2c.Mode = GPIO_MODE_AF;	// GPIO端口复用功能 
	gpioi2c.Alternate = GPIO_AF4_I2C_SDA; // 配置为I2C_SDA
	gpioi2c.OpenDrain = GPIO_OPENDRAIN; // 开漏输出
	gpioi2c.Debounce.Enable = GPIO_DEBOUNCE_DISABLE; // 禁止输入去抖动
	gpioi2c.SlewRate = GPIO_SLEW_RATE_LOW; // 电压转换速率
	gpioi2c.DrvStrength = GPIO_DRV_STRENGTH_LOW; // 驱动强度
	gpioi2c.Pull = GPIO_NOPULL; // 无上下拉
	HAL_GPIO_Init(GPIOC, &gpioi2c);
	
	
	gpioi2c.Pin = GPIO_PIN_4;
	gpioi2c.Mode = GPIO_MODE_AF; 
	gpioi2c.Alternate = GPIO_AF4_I2C_SCL;
	gpioi2c.OpenDrain = GPIO_OPENDRAIN; 
	gpioi2c.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	gpioi2c.SlewRate = GPIO_SLEW_RATE_LOW;
	gpioi2c.DrvStrength = GPIO_DRV_STRENGTH_LOW;
	gpioi2c.Pull = GPIO_NOPULL;	
	HAL_GPIO_Init(GPIOC, &gpioi2c);
	
//	gpioi2c.Pin    = GPIO_PIN_5;
//	gpioi2c.Mode = GPIO_MODE_AF; // GPIO端口复用功能 
//	gpioi2c.Alternate = GPIO_AF4_I2C_SDA; // 配置为I2C_SDA
//	gpioi2c.OpenDrain = GPIO_OPENDRAIN; // 开漏输出
//	gpioi2c.Debounce.Enable = GPIO_DEBOUNCE_DISABLE; // 禁止输入去抖动
//	gpioi2c.SlewRate = GPIO_SLEW_RATE_HIGH; // 电压转换速率
//	gpioi2c.DrvStrength = GPIO_DRV_STRENGTH_HIGH; // 驱动强度
//	gpioi2c.Pull = GPIO_PULLUP;			// 上拉
//	HAL_GPIO_Init(GPIOB, &gpioi2c);

//	gpioi2c.Pin = GPIO_PIN_4;
//	gpioi2c.Mode = GPIO_MODE_AF;
//	gpioi2c.Alternate = GPIO_AF4_I2C_SCL;
//	gpioi2c.OpenDrain = GPIO_OPENDRAIN;
//	gpioi2c.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
//	gpioi2c.SlewRate = GPIO_SLEW_RATE_LOW;
//	gpioi2c.DrvStrength = GPIO_DRV_STRENGTH_LOW;
//	gpioi2c.Pull = GPIO_PULLUP;
//	HAL_GPIO_Init(GPIOB, &gpioi2c);
	
	
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



