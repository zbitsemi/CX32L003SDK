/**
  ******************************************************************************
  * @file    cx32l003_starterkit.c
	* @author  MCU Software Team
	* @Version V1.0.0
  * @Date    21-Oct-2019
  * @brief  This file contains definitions for:
  *          - LED, push-button, EEPROM and External SPI flash available on CX32L003-StarterKit 
  *            from XMC
  *
  @verbatim
 **/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_STARTERKIT_H
#define __CX32L003_STARTERKIT_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup CX32L003_STARTERKIT
  * @{
  */ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"
   
   
/** @defgroup CX32L003_STARTERKIT_Exported_Types CX32L003 STARTERKIT Exported Types
  * @{
  */
typedef enum 
{
  LED1 = 0
} Led_TypeDef;

typedef enum 
{  
  BUTTON_USER = 0
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef; 


/**
  * @}
  */ 

/** @defgroup CX32L003_STARTERKIT_Exported_Constants CX32L003 STARTERKIT Exported Constants
  * @{
  */ 

/** 
  * @brief  Define for CX32L003_STARTERKIT board  
  */ 
#if !defined (USE_CX32L003_STARTERKIT)
 #define USE_CX32L003_STARTERKIT
#endif
  
/** @defgroup CX32L003_STARTERKIT_LED CX32L003 STARTERKIT LED
  * @{
  */
#define LEDn                             	1

#define LED1_PIN                         	GPIO_PIN_4
#define LED1_GPIO_PORT                   	GPIOD
#define LED1_GPIO_CLK_ENABLE()           	__HAL_RCC_GPIOD_CLK_ENABLE()  
#define LED1_GPIO_CLK_DISABLE()          	__HAL_RCC_GPIOD_CLK_DISABLE()  

#define LEDx_GPIO_CLK_ENABLE(__INDEX__)   do{														\
																							if((__INDEX__) == 0)			\
																								LED1_GPIO_CLK_ENABLE();	\
																						}while(0U)

#define LEDx_GPIO_CLK_DISABLE(__INDEX__)  (((__INDEX__) == 0) ? LED1_GPIO_CLK_DISABLE() : 0)

/**
  * @}
  */ 

/** @defgroup CX32L003_STARTERKIT_BUTTON CX32L003 STARTERKIT BUTTON
  * @{
  */  
#define BUTTONn                          1  

/**
  * @brief User push-button
 */
#define USER_BUTTON_PIN                  			GPIO_PIN_6
#define USER_BUTTON_GPIO_PORT            			GPIOC
#define USER_BUTTON_GPIO_CLK_ENABLE()    			__HAL_RCC_GPIOC_CLK_ENABLE()
#define USER_BUTTON_GPIO_CLK_DISABLE()   			__HAL_RCC_GPIOC_CLK_DISABLE()
#define USER_BUTTON_EXTI_IRQn            			GPIOC_IRQn

#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)   	do{																\
																								if((__INDEX__) == 0)						\
																									USER_BUTTON_GPIO_CLK_ENABLE();\
																								}while(0U)

#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)   (((__INDEX__) == 0) ? USER_BUTTON_GPIO_CLK_DISABLE() : 0)
/**
  * @}
  */
    
/** @addtogroup CX32L003_STARTERKIT_BUS CX32L003 STARTERKIT BUS
  * @{
  */
/*############################### SPI ###################################*/
/**
  * @brief  SPI Interface pins
  *         used to control external spi flash
  */
#define STARTERKIT_SPIx                                 SPI
#define STARTERKIT_SPIx_CLK_ENABLE()                    __HAL_RCC_SPI_CLK_ENABLE()

#define STARTERKIT_SPIx_NSS_GPIO_PORT                   GPIOA
#define STARTERKIT_SPIx_NSS_PIN                         GPIO_PIN_3
#define STARTERKIT_SPIx_NSS_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define STARTERKIT_SPIx_NSS_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()

#define STARTERKIT_SPIx_SCK_GPIO_PORT                   GPIOC
#define STARTERKIT_SPIx_SCK_PIN                         GPIO_PIN_5
#define STARTERKIT_SPIx_SCK_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define STARTERKIT_SPIx_SCK_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()

#define STARTERKIT_SPIx_MISO_MOSI_GPIO_PORT             GPIOD
#define STARTERKIT_SPIx_MISO_MOSI_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOD_CLK_ENABLE()
#define STARTERKIT_SPIx_MISO_MOSI_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOD_CLK_DISABLE()
#define STARTERKIT_SPIx_MISO_PIN                        GPIO_PIN_2
#define STARTERKIT_SPIx_MOSI_PIN                        GPIO_PIN_3
/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define STARTERKIT_SPIx_TIMEOUT_MAX                   1000


/*############################### I2C ###################################*/
/*#####  !!!!!Warning:I2C using same port as ADC's AIN1, AIN2!!!!!  #####*/
#if !defined (USE_CX32L003_STARTERKIT_ADC)
/**
  * @brief  I2C Interface pins
  *         used to control external eeprom
  */
#define STARTERKIT_I2Cx                                 SPI
#define STARTERKIT_I2Cx_CLK_ENABLE()                    __HAL_RCC_SPI_CLK_ENABLE()

#define STARTERKIT_I2Cx_SCL_GPIO_PORT                   GPIOC
#define STARTERKIT_I2Cx_SCL_PIN                         GPIO_PIN_3
#define STARTERKIT_I2Cx_SDA_PIN                         GPIO_PIN_4
#define STARTERKIT_I2Cx_SCL_SDA_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOC_CLK_ENABLE()
#define STARTERKIT_I2Cx_SCL_SDA_GPIO_CLK_DISABLE()      __HAL_RCC_GPIOC_CLK_DISABLE()

/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define STARTERKIT_I2Cx_TIMEOUT_MAX                   1000
#endif 

/*############################ADC##############################*/
/*### !!!Warning:ADC's AIN1, AIN2 using same port as I2C!!! ###*/
#if defined (USE_CX32L003_STARTERKIT_ADC)
/**
  * @brief  ADC Interface pins
  *         used to measure adc input voltage
  */
#define STARTERKIT_ADCx                                 ADC
#define STARTERKIT_ADCx_CLK_ENABLE()                    __HAL_RCC_ADC_CLK_ENABLE()
#define STARTERKIT_ADCx_CLK_DISABLE()                 __HAL_RCC_ADC_CLK_DISABLE()
    
#define STARTERKIT_ADCx_GPIO_PORT                       GPIOC
#define STARTERKIT_ADCx_GPIO_PIN                        GPIO_PIN_3
#define STARTERKIT_ADCx_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOC_CLK_ENABLE()
#define STARTERKIT_ADCx_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOC_CLK_DISABLE()
#endif 

/**
  * @}
  */
    

/**
  * @}
  */
    
/** @addtogroup CX32L003_STARTERKIT_Exported_Functions
  * @{
  */
uint32_t        BSP_GetVersion(void);

/** @addtogroup CX32L003_STARTERKIT_LED_Functions CX32L003 STARTERKIT LED Functions
  * @{
  */ 

void            BSP_LED_Init(Led_TypeDef Led);
void            BSP_LED_DeInit(Led_TypeDef Led);
void            BSP_LED_On(Led_TypeDef Led);
void            BSP_LED_Off(Led_TypeDef Led);
void            BSP_LED_Toggle(Led_TypeDef Led);

/**
  * @}
  */

/** @addtogroup CX32L003_STARTERKIT_BUTTON_Functions CX32L003 STARTERKIT BUTTON Functions
  * @{
  */
void             BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
void             BSP_PB_DeInit(Button_TypeDef Button);
uint32_t         BSP_PB_GetState(Button_TypeDef Button);

/**
  * @}
  */

/**
  * @}
  */ /* End of group CX32L003_STARTERKIT_Exported_Functions */

/**
  * @}
  */ /* End of group CX32L003_STARTERKIT */

/**
  * @}
  */ /* End of group BSP */

#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_STARTERKIT_H */


