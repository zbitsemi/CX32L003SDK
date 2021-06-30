/**
  ******************************************************************************
  * @file    cx32l003_hal_gpio.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of GPIO HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_GPIO_H
#define __CX32L003_HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Types GPIO Exported Types
  * @{
  */

/**
  * @brief GPIO Debounce Init structure definition
		These parameters can be values of @ref GPIO_debounce_define 	
  */
typedef struct 
{
  uint32_t Enable;
	uint32_t TwoLevelSync;
	uint32_t DebounceClk;
} GPIO_Debounce_InitTypeDef;

/**
  * @brief GPIO Exti Init structure definition
		These parameters can be values of @ref GPIO_exti_define 
  */
typedef struct 
{
  uint32_t Enable;
	uint32_t EdgeLevelSel;
	uint32_t RiseFallSel;
} GPIO_Exti_InitTypeDef;

/**
  * @brief GPIO Init structure definition
  */
typedef struct
{
  uint32_t Pin;       									/*!< Specifies the GPIO pins to be configured.
																						This parameter can be any value of @ref GPIO_pins_define */

  uint32_t Mode;      									/*!< Specifies the operating mode for the selected pins.
																						This parameter can be a value of @ref GPIO_mode_define */

  uint32_t Pull;      									/*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
																						This parameter can be a value of @ref GPIO_pull_define */

  uint32_t OpenDrain;      							/*!< Specifies the PushPull or OpenDrain output for the selected pins.
																						This parameter can be a value of @ref GPIO_opendrain_define */	
	
  GPIO_Debounce_InitTypeDef Debounce;   /*!< Specifies the debounce for the selected pins.
																						This parameter can be a value of @ref GPIO_debounce_define */	
	
  uint32_t SlewRate;     								/*!< Specifies the slew rate for the selected pins.
																						This parameter can be a value of @ref GPIO_slewrate_define */
	
  uint32_t DrvStrength; 								/*!< Specifies the driver strength for the selected pins.
																						This parameter can be a value of @ref GPIO_driver_strength_define */	
	
	GPIO_Exti_InitTypeDef Exti;						/*!< Specifies exti type for the selected pins.
																						This parameter can be a value of @ref GPIO_exti_define */
	
  uint32_t Alternate;  									/*!< Peripheral to be connected to the selected pins. 
																						This parameter can be a value of @ref GPIO_alternate_function_selection */	

} GPIO_InitTypeDef;

/**
  * @brief  GPIO Bit SET and Bit RESET enumeration
  */
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;
/**
  * @}
  */ /* End of group GPIO_Exported_Types */

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants GPIO Exported Constants
  * @{
  */

/** @defgroup GPIO_pins_define GPIO pins define
  * @{
  */
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_All               ((uint16_t)0x00FF)  /* All pins selected */

#define GPIO_PIN_MASK              0x000000FFU /* PIN mask for assert test */
/**
  * @}
  */

/** @defgroup GPIO_mode_define GPIO mode define
  * @brief GPIO Configuration Mode 
  *        Elements values convention: 0xX0yz00YZ
  *           - X  : GPIO mode or EXTI Mode
  *           - y  : External IT or Event trigger detection 
  *           - z  : IO configuration on External IT or Event
  *           - Y  : Output type (Push Pull or Open Drain)
  *           - Z  : IO Direction mode (Input, Output, Alternate or Analog)
  * @{
  */ 
#define  GPIO_MODE_INPUT                        0x00000000U   /*!< Input Floating Mode                   */
#define  GPIO_MODE_OUTPUT                    		0x00000001U   /*!< Output Mode					                 */
#define  GPIO_MODE_AF                        		0x00000002U   /*!< Alternate Function Mode     					 */
#define  GPIO_MODE_ANALOG                       0x00000003U   /*!< Analog Mode  												 */
#define	 GPIO_MODE_GPIO													0x00000004U		/*!< Gpio Function Mode     					 		 */
#define  EXTI_MODE             									0x10000000U		/*!< Exti Mode     					 							 */
/**
  * @}
  */

/** @defgroup GPIO_slewrate_define  GPIO slewrate define
  * @brief GPIO Output Maximum frequency
  * @{
  */
#define  GPIO_SLEW_RATE_LOW         						0x00000001U  
#define  GPIO_SLEW_RATE_HIGH        						0x00000000U  
/**
  * @}
  */

/** @defgroup GPIO_pull_define GPIO pull define
  * @brief GPIO Pull-Up or Pull-Down Activation
  * @{
  */
#define  GPIO_NOPULL        										0x00000000U   /*!< No Pull-up or Pull-down activation  */
#define  GPIO_PULLUP        										0x00000001U   /*!< Pull-up activation                  */
#define  GPIO_PULLDOWN      										0x00000002U   /*!< Pull-down activation                */
/**
  * @}
  */

/** @defgroup GPIO_opendrain_define GPIO output mode define
  * @brief GPIO PushPull or Opendrain Activation
  * @{
  */
#define  GPIO_PUSHPULL        										0x00000000U   /*!< Push pull activation  						 */
#define  GPIO_OPENDRAIN        										0x00000001U   /*!< Open drain activation             */
/**
  * @}
  */


/** @defgroup GPIO_driver_strength_define GPIO driver strengh
  * @brief GPIO driver strengh setting
  * @{
  */
#define  GPIO_DRV_STRENGTH_HIGH       					0x00000000U   /*!< GPIO driver strengh high  */
#define  GPIO_DRV_STRENGTH_LOW        					0x00000001U   /*!< GPIO driver strengh low   */
/**
  * @}
  */


/** @defgroup GPIO_debounce_define GPIO debounce mode define
  * @brief GPIO debounce Activation
  * @{
  */
#define  GPIO_DEBOUNCE_DISABLE  								0x00000000U   
#define  GPIO_DEBOUNCE_ENABLE   								0x00000001U

#define  GPIO_SYNC_DISABLE  										0x00000000U   
#define  GPIO_SYNC_ENABLE   										0x00000001U

#define  GPIO_DBCLK_DIV_1       								0x00000000U   
#define  GPIO_DBCLK_DIV_2       								0x00000001U  
#define  GPIO_DBCLK_DIV_4       								0x00000002U 
#define  GPIO_DBCLK_DIV_8       								0x00000003U   
#define  GPIO_DBCLK_DIV_16      								0x00000004U  
#define  GPIO_DBCLK_DIV_32      								0x00000005U 
#define  GPIO_DBCLK_DIV_64      								0x00000006U   
#define  GPIO_DBCLK_DIV_128     								0x00000007U  
#define  GPIO_DBCLK_DIV_256     								0x00000008U 
#define  GPIO_DBCLK_DIV_512     								0x00000009U   
#define  GPIO_DBCLK_DIV_1024    								0x0000000AU  
#define  GPIO_DBCLK_DIV_2048    								0x0000000BU 
#define  GPIO_DBCLK_DIV_4096    								0x0000000CU   
#define  GPIO_DBCLK_DIV_8192    								0x0000000DU  
#define  GPIO_DBCLK_DIV_16384   								0x0000000EU 
#define  GPIO_DBCLK_DIV_32768										0x0000000FU

/**
  * @}
  */

/** @defgroup GPIO_exti_define GPIO exti mode define
  * @brief 
  * @{
  */
#define  GPIO_EXTI_INT_DISABLE  								0x00000000U 	
#define  GPIO_EXTI_INT_ENABLE  									0x00000001U

#define  GPIO_EXTI_INT_EDGE  										0x00000000U  
#define  GPIO_EXTI_INT_LEVEL  									0x00000001U  

#define  GPIO_EXTI_INT_LOWFALL  								0x00000000U  
#define  GPIO_EXTI_INT_HIGHRISE 								0x00000001U
#define  GPIO_EXTI_INT_FALLRISE 								0x00000002U 

/**
  * @}
  */

/** @defgroup GPIO_alternate_function_selection  GPIO alternate function selection
  * @brief 
  * @{
  */

/** 
  * @brief   AF 1 selection  
  */ 
#define GPIO_AF1_TIM1_CH1          							((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM1_CH1N         							((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM1_CH2          							((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM1_CH2N         							((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM1_CH3          							((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM1_CH3N         							((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM1_BKIN         							((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_LPTIM_GATE        							((uint8_t)0x01)  /* LPTIM Alternate Function mapping */
#define GPIO_AF1_TIM1_CH4          							((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
							
							
/** 							
  * @brief   AF 2 selection  							
  */ 							
#define GPIO_AF2_PCA_CH0           							((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF2_PCA_CH1           							((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF2_PCA_CH2           							((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF2_PCA_CH3           							((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF2_PCA_CH4           							((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF2_PCA_ECI           							((uint8_t)0x02)  /* PCA Alternate Function mapping */
#define GPIO_AF2_TIM1_CH1N         							((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM1_CH2N         							((uint8_t)0x02)  /* TIM1 Alternate Function mapping */
							
							
/** 							
  * @brief   AF 3 selection  							
  */ 							
#define GPIO_AF3_RTC_1HZ           							((uint8_t)0x03)  /* RTC Alternate Function mapping  */
#define GPIO_AF3_SPI_MISO          							((uint8_t)0x03)  /* SPI Alternate Function mapping  */
#define GPIO_AF3_SPI_MOSI          							((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF3_SPI_CLK           							((uint8_t)0x03)  /* SPI Alternate Function mapping */
#define GPIO_AF3_SPI_NSS           							((uint8_t)0x03)  /* SPI Alternate Function mapping  */
							
							
/** 							
  * @brief   AF 4 selection  							
  */ 							
#define GPIO_AF4_TIM10_TOG         							((uint8_t)0x04)  /* TIM10 Alternate Function mapping  */
#define GPIO_AF4_I2C_SCL           							((uint8_t)0x04)  /* I2C Alternate Function mapping    */
#define GPIO_AF4_I2C_SDA           							((uint8_t)0x04)  /* I2C Alternate Function mapping    */
#define GPIO_AF4_RTC_1HZ       		 							((uint8_t)0x04)  /* RTC Alternate Function mapping */
#define GPIO_AF4_HXT_OUT       		 							((uint8_t)0x04)  /* HXT Alternate Function mapping */
							
							
/** 							
  * @brief   AF 5 selection  							
  */ 							
#define GPIO_AF5_UART0_TXD         							((uint8_t)0x05)  /* UART0 Alternate Function mapping   */
#define GPIO_AF5_UART0_RXD         							((uint8_t)0x05)  /* UART0 Alternate Function mapping   */
#define GPIO_AF5_UART1_TXD         							((uint8_t)0x05)  /* UART1 Alternate Function mapping   */
#define GPIO_AF5_UART1_RXD         							((uint8_t)0x05)  /* UART1 Alternate Function mapping   */
#define GPIO_AF5_LPUART_TXD        							((uint8_t)0x05)  /* LPUART Alternate Function mapping  */
#define GPIO_AF5_LPUART_RXD        							((uint8_t)0x05)  /* LPUART Alternate Function mapping  */


/** 
  * @brief   AF 6 selection  
  */
#define GPIO_AF6_TIM10_EXT          						((uint8_t)0x06)  /* TIM10 Alternate Function mapping    */
#define GPIO_AF6_TIM10_GATE         						((uint8_t)0x06)  /* TIM10 Alternate Function mapping  	*/
#define GPIO_AF6_LPTIM_EXT          						((uint8_t)0x06)  /* LPTIM Alternate Function mapping  	*/
#define GPIO_AF6_TIM10_TOG          						((uint8_t)0x06)  /* TIM10 Alternate Function mapping  	*/
#define GPIO_AF6_TIM10_TOGN       							((uint8_t)0x06)  /* TIM10 Alternate Function mapping 		*/
#define GPIO_AF6_PCA_ECI        								((uint8_t)0x06)  /* PCA Alternate Function mapping     	*/
#define GPIO_AF6_TIM11_TOG											((uint8_t)0x06)  /* TIM11 Alternate Function mapping 		*/
#define GPIO_AF6_TIM11_TOGN											((uint8_t)0x06)  /* TIM11 Alternate Function mapping 		*/
#define GPIO_AF6_PCA_CH1												((uint8_t)0x06)  /* PCA Alternate Function mapping 			*/
#define GPIO_AF6_PCA_CH0												((uint8_t)0x06)  /* PCA Alternate Function mapping 			*/
#define GPIO_AF6_TIM11_GATE											((uint8_t)0x06)  /* TIM11 Alternate Function mapping 		*/
#define GPIO_AF6_TIM11_EXT											((uint8_t)0x06)  /* TIM11 Alternate Function mapping 		*/
#define GPIO_AF6_LIRC_OUT												((uint8_t)0x06)  /* LIRC Alternate Function mapping 		*/
#define GPIO_AF6_HIRC_OUT												((uint8_t)0x06)  /* HIRC Alternate Function mapping 		*/
#define GPIO_AF6_LPTIM_TOG											((uint8_t)0x06)  /* LPTIM Alternate Function mapping 		*/
#define GPIO_AF6_LPTIM_TOGN											((uint8_t)0x06)  /* LPTIM Alternate Function mapping 		*/

/** 
  * @brief   AF 7 selection  
  */ 
#define GPIO_AF7_BEEP          									((uint8_t)0x07)  /* BEEP Alternate Function mapping  */
#define GPIO_AF7_UART0_TXD        							((uint8_t)0x07)  /* UART0 Alternate Function mapping */
#define GPIO_AF7_UART0_RXD        							((uint8_t)0x07)  /* UART0 Alternate Function mapping */
#define GPIO_AF7_UART1_TXD        							((uint8_t)0x07)  /* UART1 Alternate Function mapping */
#define GPIO_AF7_UART1_RXD       								((uint8_t)0x07)  /* UART1 Alternate Function mapping */
#define GPIO_AF7_VC0_OUT        								((uint8_t)0x07)  /* VC0 Alternate Function mapping   */
#define GPIO_AF7_LVD_OUT        								((uint8_t)0x07)  /* LVD Alternate Function mapping   */
#define GPIO_AF7_1WIRE        									((uint8_t)0x07)  /* 1WIRE Alternate Function mapping */
#define GPIO_AF7_CLK_MCO       									((uint8_t)0x07)  /* MCO Alternate Function mapping 	 */
#define GPIO_AF7_LXT_OUT       									((uint8_t)0x07)  /* LXT Alternate Function mapping 	 */

/** 
  * @brief   AF 8 selection  
  */ 
#define GPIO_AF8_TIM2_CH1        								((uint8_t)0x08)  /* TIM2 Alternate Function mapping */
#define GPIO_AF8_TIM2_CH2        								((uint8_t)0x08)  /* TIM2 Alternate Function mapping */
#define GPIO_AF8_TIM2_CH3        								((uint8_t)0x08)  /* TIM2 Alternate Function mapping */
#define GPIO_AF8_TIM2_CH4        								((uint8_t)0x08)  /* TIM2 Alternate Function mapping */

/** 
  * @brief   Analog selection  
  */ 
#define GPIO_ANALOG_VCIN1        								((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */	
#define GPIO_ANALOG_VCIN2        								((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */
#define GPIO_ANALOG_AIN0         								((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */
#define GPIO_ANALOG_AIN1         								((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */
#define GPIO_ANALOG_AIN2         								((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */
#define GPIO_ANALOG_AIN3_VCIN0   								((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */
#define GPIO_ANALOG_AIN4         								((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */
#define GPIO_ANALOG_AIN5         								((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */
#define GPIO_ANALOG_AIN6         								((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */
#define GPIO_ANALOG_AIN7         								((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */
#define GPIO_X32K_INOUT													((uint8_t)0x0F)
#define GPIO_OSC_INOUT													((uint8_t)0x0F)
/**
  * @}
  */

/**
  * @}
  */ /* End of group GPIO_Exported_Constants */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Macros GPIO Exported Macros
  * @{
  */

/**
  * @brief  Set GPIO_PIN_x as input
  * @param  __GPIOx__: specifies the GPIO.
						This parameter can be GPIOx where x can be(A..D)
  * @param  __GPIO_PIN__: specifies the pin.
  *          This parameter can be GPIO_PIN_x where x can be(0..7)
  * @retval None.
  */
#define __HAL_GPIO_SET_INPUT(__GPIOx__, __GPIO_PIN__) (__GPIOx__->DIRCR &= (~(__GPIO_PIN__)))

/**
  * @brief  Set GPIO_PIN_x as output
  * @param  __GPIOx__: specifies the GPIO.
						This parameter can be GPIOx where x can be(A..D)
  * @param  __GPIO_PIN__: specifies the pin.
  *          This parameter can be GPIO_PIN_x where x can be(0..7)
  * @retval None.
  */
#define __HAL_GPIO_SET_OUTPUT(__GPIOx__, __GPIO_PIN__) (__GPIOx__->DIRCR |= (__GPIO_PIN__))

/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  __GPIOx__: specifies the GPIO to check.
						This parameter can be GPIOx where x can be(A..D)
  * @param  __EXTI_LINE__: specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..7)
  * @retval The new state of __EXTI_LINE__ (SET or RESET).
  */
#define __HAL_GPIO_EXTI_GET_FLAG(__GPIOx__, __EXTI_LINE__) (__GPIOx__->MSKINTSR & (__EXTI_LINE__))

/**
  * @brief  Clears the EXTI's line pending flags.
  * @param  __GPIOx__: specifies the GPIO to check.
						This parameter can be GPIOx where x can be(A..D)
  * @param  __EXTI_LINE__: specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..7)
  * @retval None
  */
#define __HAL_GPIO_EXTI_CLEAR_FLAG(__GPIOx__, __EXTI_LINE__) (__GPIOx__->INTCLR = (__EXTI_LINE__))

/**
  * @brief  Checks whether the specified EXTI line is asserted or not.
  * @param  __GPIOx__: specifies the GPIO to check.
						This parameter can be GPIOx where x can be(A..D)
  * @param  __EXTI_LINE__: specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..7)
  * @retval The new state of __EXTI_LINE__ (SET or RESET).
  */
#define __HAL_GPIO_EXTI_GET_IT(__GPIOx__, __EXTI_LINE__) (__GPIOx__->INTEN & (__EXTI_LINE__))

/**
  * @brief  Clears the EXTI's line pending bits.
  * @param  __GPIOx__: specifies the GPIO to check.
						This parameter can be GPIOx where x can be(A..D)
  * @param  __EXTI_LINE__: specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..7)
  * @retval None
  */
#define __HAL_GPIO_EXTI_CLEAR_IT(__GPIOx__, __EXTI_LINE__) (__GPIOx__->INTEN &= (~(__EXTI_LINE__)))

/**
  * @}
  */ /* End of group GPIO_Exported_Macros */



/* Exported functions --------------------------------------------------------*/
/** @addtogroup GPIO_Exported_Functions
  * @{
  */

/** @addtogroup GPIO_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
void  HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void  HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
/**
  * @}
  */

/** @addtogroup GPIO_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *****************************************************/
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_IRQHandler(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);	
void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
  * @}
  */

/**
  * @}
  */ /* End of group GPIO_Exported_Functions */
		
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup GPIO_Private_Constants GPIO Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup GPIO_Private_Macros GPIO Private Macros
  * @{
  */
#define IS_GPIO_PIN_ACTION(ACTION) (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))
#define IS_GPIO_PIN(PIN)           ((((PIN) & GPIO_PIN_MASK ) != 0x00U) && (((PIN) & ~GPIO_PIN_MASK) == 0x00U))
#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_MODE_INPUT)              ||\
                            ((MODE) == GPIO_MODE_OUTPUT)          	 ||\
                            ((MODE) == GPIO_MODE_AF)              	 ||\
                            ((MODE) == GPIO_MODE_ANALOG)          	 ||\
                            ((MODE) == EXTI_MODE))
#define IS_GPIO_PULL(PULL) (((PULL) == GPIO_NOPULL) || ((PULL) == GPIO_PULLUP) || \
                            ((PULL) == GPIO_PULLDOWN))

/** @defgroup GPIO_Get_Port_Index GPIO Get Port Index
  * @{
  */	
#define GPIO_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U :\
                                               ((__GPIOx__) == (GPIOD))? 3U : 4U)														
/**
  * @}
  */														

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup GPIO_Private_Functions GPIO Private Functions
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */ /* End of group GPIO */

/**
  * @}
  */ /* End of group CX32L003_HAL_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_GPIO_H */

