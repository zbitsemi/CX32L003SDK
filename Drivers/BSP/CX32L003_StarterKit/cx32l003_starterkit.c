/**
  ******************************************************************************
  * @file    cx32l003_starterkit.c
	* @author  MCU Software Team
	* @Version V1.0.0
  * @Date    21-Oct-2019
  * @brief   This file provides set of firmware functions to manage:
  *          - LED, push-button, EEPROM and External SPI flash available on CX32L003-StarterKit 
  *            from XMC
  *
  @verbatim
 **/

	
/* Includes ------------------------------------------------------------------*/
#include "cx32l003_starterkit.h"

/** @addtogroup BSP
  * @{
  */ 

/** @defgroup CX32L003_STARTERKIT CX32L003 STARTERKIT
  * @brief This file provides set of firmware functions to manage Leds and push-button
  *        available on CX32L003-Starter Kit.
  *        It provides also EEPROM, spi flashfunctions. 
  * @{
  */ 


/** @defgroup CX32L003_STARTERKIT_Private_Defines CX32L003 STARTERKIT Private Defines
  * @{
  */ 
  
/**
* @brief CX32L003 STARTERKIT BSP Driver version
*/
#define __CX32L003_STARTERKIT_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __CX32L003_STARTERKIT_BSP_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __CX32L003_STARTERKIT_BSP_VERSION_SUB2   (0x04) /*!< [15:8]  sub2 version */
#define __CX32L003_STARTERKIT_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __CX32L003_STARTERKIT_BSP_VERSION       ((__CX32L003_STARTERKIT_BSP_VERSION_MAIN << 24)	 \
																									|(__CX32L003_STARTERKIT_BSP_VERSION_SUB1 << 16)\
																									|(__CX32L003_STARTERKIT_BSP_VERSION_SUB2 << 8 )\
																									|(__CX32L003_STARTERKIT_BSP_VERSION_RC))

/**
  * @}
  */ 


/** @defgroup CX32L003_STARTERKIT_Private_Variables CX32L003 STARTERKIT Private Variables
  * @{
  */ 
GPIO_TypeDef* LED_PORT[LEDn] = {LED1_GPIO_PORT};
		
const uint16_t LED_PIN[LEDn] = {LED1_PIN};	
	
GPIO_TypeDef* BUTTON_PORT[BUTTONn]  = {USER_BUTTON_GPIO_PORT}; 
const uint16_t BUTTON_PIN[BUTTONn]  = {USER_BUTTON_PIN}; 
const uint8_t  BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn };

/**
 * @brief BUS variables
 */

#ifdef RESERVED_HAL_SPI_MODULE_ENABLED
uint32_t SpixTimeout = STARTERKIT_SPIx_TIMEOUT_MAX;        /*<! Value of Timeout when SPI communication fails */
static SPI_HandleTypeDef hstarterkit_Spi;
#endif /* RESERVED_HAL_SPI_MODULE_ENABLED */

#ifdef RESERVED_HAL_ADC_MODULE_ENABLED
static ADC_HandleTypeDef hstarterkit_Adc;
/* ADC channel configuration structure declaration */
static ADC_ChannelConfTypeDef sConfig;
#endif /* RESERVED_HAL_ADC_MODULE_ENABLED */

/**
  * @}
  */ 

/** @defgroup CX32L003_STARTERKIT_Private_Functions CX32L003 STARTERKIT Private Functions
  * @{
  */ 
#ifdef RESERVED_HAL_SPI_MODULE_ENABLED
//static void               SPIx_Init(void);
//static void               SPIx_Write(uint8_t Value);
//static void               SPIx_WriteData(uint8_t *DataIn, uint16_t DataLength);
//static void               SPIx_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLegnth);
//static void               SPIx_Error (void);
//static void               SPIx_MspInit(void);
#endif /* RESERVED_HAL_SPI_MODULE_ENABLED */

/**
  * @}
  */ 

/** @defgroup CX32L003_STARTERKIT_Exported_Functions CX32L003 STARTERKIT Exported Functions
  * @{
  */ 

/**
  * @brief  This method returns the CX32L003 STARTERKIT BSP Driver revision
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __CX32L003_STARTERKIT_BSP_VERSION;
}

/** @defgroup CX32L003_STARTERKIT_LED_Functions CX32L003 STARTERKIT LED Functions
  * @{
  */ 

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Led to be configured. 
  *          This parameter can be one of the following values:
  *     @arg LED1
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpioinitstruct={0};
  
  /* Enable the GPIO_LED Clock */
  LEDx_GPIO_CLK_ENABLE(Led);
	
  /* Configure the GPIO_LED pin */
  gpioinitstruct.Pin    = LED_PIN[Led];
	gpioinitstruct.Mode = GPIO_MODE_OUTPUT;
	gpioinitstruct.OpenDrain = GPIO_PUSHPULL;	
	gpioinitstruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
	gpioinitstruct.SlewRate = GPIO_SLEW_RATE_HIGH;
	gpioinitstruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH;
	gpioinitstruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(LED_PORT[Led], &gpioinitstruct);
  
  /* Reset PIN to switch off the LED */
  HAL_GPIO_WritePin(LED_PORT[Led],LED_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  DeInit LEDs.
  * @param  Led: LED to be de-init. 
  *   This parameter can be one of the following values:
  *     @arg  LED1
  * @note Led DeInit does not disable the GPIO clock nor disable the Mfx 
  */
void BSP_LED_DeInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /* Turn off LED */
  HAL_GPIO_WritePin(LED_PORT[Led],LED_PIN[Led], GPIO_PIN_RESET);
  /* DeInit the GPIO_LED pin */
  gpio_init_structure.Pin = LED_PIN[Led];
  HAL_GPIO_DeInit(LED_PORT[Led], gpio_init_structure.Pin);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  */
void BSP_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET); 
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET); 
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg  LED1
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(LED_PORT[Led], LED_PIN[Led]);
}

/**
  * @}
  */ 

/** @defgroup CX32L003_STARTERKIT_BUTTON_Functions CX32L003 STARTERKIT BUTTON Functions
  * @{
  */ 

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter should be: BUTTON_USER
  * @param  ButtonMode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                     generation capability  
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  GPIO_InitTypeDef gpioinitstruct={0};

  /* Enable the BUTTON Clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);

  gpioinitstruct.Pin = BUTTON_PIN[Button];
	gpioinitstruct.Pull = GPIO_PULLUP;	// 上拉
	gpioinitstruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;	// 禁止输入去抖动
	gpioinitstruct.SlewRate = GPIO_SLEW_RATE_HIGH; // 电压转换速率
	gpioinitstruct.DrvStrength = GPIO_DRV_STRENGTH_HIGH; // 驱动强度
	
  if (ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    gpioinitstruct.Mode   = GPIO_MODE_INPUT;  //输出模式
  
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct);
  }
 
  if (ButtonMode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    gpioinitstruct.Mode   = EXTI_MODE; // 外部中断模式
		gpioinitstruct.Exti.Enable = GPIO_EXTI_INT_ENABLE; // GPIO端口中断使能
		gpioinitstruct.Exti.EdgeLevelSel = GPIO_EXTI_INT_EDGE;	// 中断类型 边沿触发
		gpioinitstruct.Exti.RiseFallSel = GPIO_EXTI_INT_LOWFALL;	// 下降沿触发中断
//		gpioinitstruct.Exti.RiseFallSel = GPIO_EXTI_INT_HIGHRISE;	// 上升沿触发中断
//		gpioinitstruct.Exti.RiseFallSel = GPIO_EXTI_INT_FALLRISE;	// 下降沿上升沿都触发中断
		
//		gpioinitstruct.Exti.EdgeLevelSel = GPIO_EXTI_INT_LEVEL;		// 中断类型 电平触发
//		gpioinitstruct.Exti.RiseFallSel = GPIO_EXTI_INT_LOWFALL; // 低电平触发中断
//		gpioinitstruct.Exti.RiseFallSel = GPIO_EXTI_INT_HIGHRISE; // 高电平触发中断
		
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct); // 初始化

		__HAL_GPIO_EXTI_CLEAR_FLAG(BUTTON_PORT[Button], BUTTON_PIN[Button]);	// 清除对应的中断标志位
    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), PRIORITY_LOW); 
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button])); // NVIC GPIO 中断使能
  }
}

/**
  * @brief  Push Button DeInit.
  * @param  Button: Button to be configured
  *   This parameter should be: BUTTON_USER  
  * @note PB DeInit does not disable the GPIO clock
  */
void BSP_PB_DeInit(Button_TypeDef Button)
{
  GPIO_InitTypeDef gpio_init_structure;

  gpio_init_structure.Pin = BUTTON_PIN[Button];
  HAL_NVIC_DisableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  HAL_GPIO_DeInit(BUTTON_PORT[Button], gpio_init_structure.Pin);
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter should be: BUTTON_USER
  * @retval Button state.
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
  {
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
  }
/**
  * @}
  */ 

/**
  * @}
  */ /* End of group CX32L003_STARTERKIT_Exported_Functions */

/** @addtogroup CX32L003_STARTERKIT_Private_Functions
  * @{
  */ 
  
/**
  * @}
  */
  
/**
  * @}
  */ /* End of group CX32L003_STARTERKIT */  

/**
  * @}
  */ /* End of group BSP */ 
     
    
