/**
  ******************************************************************************
  * @file    cx32l003_hal_lvd.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of LVD HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_LVD_H
#define __CX32L003_HAL_LVD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup LVD
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup LVD_Exported_Types LVD Exported Types
  * @{
  */
	
/**
  * @brief  LVD Configuration Structure definition
	* @note   This structure is for LVD 	
  */
typedef struct
{	
  uint32_t FltClkSel;     				/*!< Specifies filter clock.
																			 This parameter can be a value of @ref LVD_FltClkSel */		
	
  uint32_t VoltageLevel;     			/*!< Specifies voltage level for LVD.
																			 This parameter can be a value of @ref LVD_VoltageLevel */	
	
  uint32_t TriggerSel;						/*!< Specifies trigger selection for LVD.
																			 This parameter can be a value of @ref LVD_TriggerSel */	
	
  uint32_t Action;     						/*!< Specifies low voltage detection action.
																			 This parameter can be a value of @ref LVD_Action */		
	
  uint32_t FltNum;     						/*!< Specifies the filter number for digital filter.
																			 This parameter can be a value between 0x0000 to 0xFFFF */	

}LVD_InitTypeDef;


/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_LVD_STATE_RESET             = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
  HAL_LVD_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_LVD_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  HAL_LVD_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  HAL_LVD_STATE_ERROR             = 0x04U     /*!< Reception process is ongoing                */
}HAL_LVD_StateTypeDef;


/**
  * @brief  LVD Handle Structure definition
  */
typedef struct
{
  LVD_TypeDef             		*Instance;     /*!< Register base address             	*/
  LVD_InitTypeDef    					Init;          /*!< LVD required parameters 						*/
  HAL_LockTypeDef             Lock;          /*!< Locking object                    	*/
  __IO HAL_LVD_StateTypeDef   State;         /*!< LVD operation state               	*/
}LVD_HandleTypeDef;


/**
  * @}
  */ /* End of group LVD_Exported_Types */


/* Exported constants --------------------------------------------------------*/
/** @defgroup LVD_Exported_Constants LVD Exported Constants
  * @{
  */

/** @defgroup LVD_FltClkSel LVD filter clock select
  * @{
  */
#define LVD_FLTCLK_DISABLE              (0x00000000U)              						/*!< Digital filter clock select */
#define LVD_FLTCLK_PCLK           			(LVD_CR_FLTCLK_SEL_0)                    /*!< Digital filter clock select PCLK */
#define LVD_FLTCLK_LIRC									(LVD_CR_FLTCLK_SEL_1)										/*!< Digital filter clock select LIRC */

/**
  * @}
  */

/** @defgroup LVD_TriggerSel LVD trigger selection
  * @{
  */
#define LVD_TRIGGER_HIGHLEVEL             (VC_CR1_HIGHINTEN)              													/*!< Trigger select highlevel */
#define LVD_TRIGGER_RISING           			(VC_CR1_RISEINTEN)                    										/*!< Trigger select rising edge */
#define LVD_TRIGGER_FALLING								(VC_CR1_FALLINTEN)																				/*!< Trigger select falling edge */
#define LVD_TRIGGER_BOTHEDGE							(VC_CR1_RISEINTEN | VC_CR1_FALLINTEN)											/*!< Trigger select both edge */
#define LVD_TRIGGER_ALL										(VC_CR1_HIGHINTEN | VC_CR1_RISEINTEN | VC_CR1_FALLINTEN)	/*!< Trigger select both edge and highlevel */

/**
  * @}
  */




/** @defgroup LVD_VoltageLevel LVD voltage level
  * @{
  */
#define LVD_VOLLEVEL_4_4V              	(0x00000000U)              																/*!< LVD voltage select 4.4V*/
#define LVD_VOLLEVEL_4_0V           		(LVD_CR_DIV_SEL_0)                    										/*!< LVD voltage select 4.0V*/
#define LVD_VOLLEVEL_3_6V								(LVD_CR_DIV_SEL_1)																				/*!< LVD voltage select 3.6V*/
#define LVD_VOLLEVEL_3_3V								(LVD_CR_DIV_SEL_1 | LVD_CR_DIV_SEL_0)											/*!< LVD voltage select 3.3V*/
#define LVD_VOLLEVEL_3_1V								(LVD_CR_DIV_SEL_2)																				/*!< LVD voltage select 3.1V*/
#define LVD_VOLLEVEL_2_9V								(LVD_CR_DIV_SEL_2 | LVD_CR_DIV_SEL_0)											/*!< LVD voltage select 2.9V*/
#define LVD_VOLLEVEL_2_7V								(LVD_CR_DIV_SEL_2 | LVD_CR_DIV_SEL_1)											/*!< LVD voltage select 2.7V*/
#define LVD_VOLLEVEL_2_5V								(LVD_CR_DIV_SEL_2 | LVD_CR_DIV_SEL_1 | LVD_CR_DIV_SEL_0)	/*!< LVD voltage select 2.5V*/

/**
  * @}
  */


/** @defgroup LVD_Action LVD action after detection
  * @{
  */
#define LVD_ACTION_INTERRUPT					(0x00000000U)   											/*!< LVD module generate interrupt after detection */
#define LVD_ACTION_RESET              (LVD_CR_ACT)              						/*!< LVD module generate reset after detection */

/**
  * @}
  */


/**
  * @}
  */ /* End of group LVD_Exported_Constants */



/* Exported functions --------------------------------------------------------*/
/** @addtogroup LVD_Exported_Functions
  * @{
  */

/** @addtogroup LVD_Exported_Functions_Group
 * @{
 */
/* LVD Base functions ********************************************************/
HAL_StatusTypeDef HAL_LVD_Init(LVD_HandleTypeDef *hlvd);
HAL_StatusTypeDef HAL_LVD_DeInit(LVD_HandleTypeDef *hlvd);
void HAL_LVD_MspInit(LVD_HandleTypeDef *hlvd);
void HAL_LVD_MspDeInit(LVD_HandleTypeDef *hlvd);
HAL_StatusTypeDef HAL_LVD_Enable(LVD_HandleTypeDef *hlvd);
HAL_StatusTypeDef HAL_LVD_Enable_IT(LVD_HandleTypeDef *hlvd);
HAL_StatusTypeDef HAL_LVD_Disable(LVD_HandleTypeDef *hlvd);
void HAL_LVD_InterruptCallback(LVD_HandleTypeDef *hlvd);
void HAL_LVD_IRQHandler(LVD_HandleTypeDef *hlvd);

/**
  * @}
  */ /* End of group LVD_Exported_Functions_Group */

/**
  * @}
  */ /* End of group LVD_Exported_Functions */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup LVD_Exported_Macros LVD Exported Macros
  * @{
  */

/** @brief  Reset LVD handle state
  * @param  __HANDLE__: LVD handle.
  * @retval None
  */
#define __HAL_LVD_RESET_HANDLE_STATE(__HANDLE__) 						((__HANDLE__)->State = HAL_LVD_STATE_RESET)


/**
  * @brief  Enable the LVD.
  * @param  __HANDLE__: LVD handle
  * @retval None
 */
#define __HAL_LVD_ENABLE(__HANDLE__)                 				((__HANDLE__)->Instance->CR |= (LVD_CR_LVDEN))


/**
  * @brief  Disable the LVD.
  * @param  __HANDLE__: LVD handle
  * @retval None
 */
#define __HAL_LVD_DISABLE(__HANDLE__)                 			((__HANDLE__)->Instance->CR &= ~(LVD_CR_LVDEN))


/**
  * @brief  Enables the specified LVD interrupt.
  * @param  __HANDLE__: specifies the LVD Handle.
  * @retval None
  */
#define __HAL_LVD_ENABLE_IT(__HANDLE__)    									((__HANDLE__)->Instance->CR |= (LVD_CR_INT_EN))


/**
  * @brief  Disables the specified LVD interrupt.
  * @param  __HANDLE__: specifies the LVD Handle.
  * @retval None
  */
#define __HAL_LVD_DISABLE_IT(__HANDLE__)    								((__HANDLE__)->Instance->CR &= ~(LVD_CR_INT_EN))


/**
  * @brief  Enables the LVD digital filter.
  * @param  __HANDLE__: specifies the LVD Handle.
  * @retval None
  */
#define __HAL_LVD_ENABLE_DIGFLT(__HANDLE__)    							((__HANDLE__)->Instance->CR |= (LVD_CR_FLTEN))


/**
  * @brief  Disables the LVD digital filter.
  * @param  __HANDLE__: specifies the LVD Handle.
  * @retval None
  */
#define __HAL_LVD_DISABLE_DIGFLT(__HANDLE__)    						((__HANDLE__)->Instance->CR &= ~(LVD_CR_FLTEN))


/**
  * @brief  Checks whether the specified LVD interrupt flag is set or not.
  * @param  __HANDLE__: specifies the LVD Handle.
  * @retval TRUE or FALSE.
  */
#define __HAL_LVD_GET_FLAG(__HANDLE__)          						(((__HANDLE__)->Instance->SR & (LVD_SR_INTF)) == (LVD_SR_INTF))


/**
  * @brief  Checks whether the specified LVD interrupt source is enable or disable.
  * @param  __HANDLE__: specifies the LVD Handle.
  * @retval TRUE or FALSE.
  */
#define __HAL_LVD_GET_IT_SOURCE(__HANDLE__)          				(((__HANDLE__)->Instance->CR & (LVD_CR_INT_EN)) == (LVD_CR_INT_EN))


/**
  * @brief Clear the LVD interrupt pending bits
  * @param  __HANDLE__: LVD handle
  * @retval None
  */
#define __HAL_LVD_CLEAR_IT(__HANDLE__)        							((__HANDLE__)->Instance->SR = 0x0)



/**
  * @}
  */ /* End of group LVD_Exported_Macros */


/* Private Macros -----------------------------------------------------------*/
/** @defgroup LVD_Private_Macros LVD Private Macros
 * @{
 */ 
#define IS_LVD_INSTANCE(INSTANCE)			((INSTANCE) == LVD)   

/**
  * @}
  */ /* End of group LVD_Private_Macros */


/* Private Functions --------------------------------------------------------*/
/** @addtogroup LVD_Private_Functions
 * @{
 */


/**
  * @}
  */ /* End of group LVD_Private_Functions */


/**
  * @}
  */ /* End of group LVD */


#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_LVD_H */
