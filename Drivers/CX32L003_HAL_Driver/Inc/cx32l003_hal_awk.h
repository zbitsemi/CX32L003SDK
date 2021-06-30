/**
  ******************************************************************************
  * @file    cx32l003_hal_awk.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of AWK HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_AWK_H
#define __CX32L003_HAL_AWK_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup AWK
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup AWK_Exported_Types AWK Exported Types
  * @{
  */
	
/**
  * @brief  AWK Configuration Structure definition
	* @note   This structure is for AWK 	
  */
typedef struct
{	
  uint32_t ClkSel;     				/*!< Specifies low power timer clock.
                                   This parameter can be a value of @ref AWK_ClkSel */		
	
  uint32_t ClkDiv;     				/*!< Specifies tog function enable or disable.
                                   This parameter can be a value of @ref AWK_ClkDiv */	
	
  uint32_t HxtDiv;     				/*!< Specifies hxt divider value. 
																	 Frequency = Fhxt/(HxtDiv+1)
                                   This parameter can be a number between Min_Data = 0x00 and Max_Data = 0xFF.  */

  uint32_t Period;            /*!< Specifies the period value to be loaded into the active CNT value immediately through RLOAD register.
																	 Period caculation = (MaxCntLevel - Period)/(AWK clock)
                                   This parameter can be a number between Min_Data = 0x00 and Max_Data = 0xFF.  */	
	
}AWK_InitTypeDef;


/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_AWK_STATE_RESET             = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
  HAL_AWK_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_AWK_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  HAL_AWK_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  HAL_AWK_STATE_ERROR             = 0x04U     /*!< Reception process is ongoing                */
}HAL_AWK_StateTypeDef;


/**
  * @brief  AWK Handle Structure definition
  */
typedef struct
{
  AWK_TypeDef             		*Instance;     /*!< Register base address             	*/
  AWK_InitTypeDef    					Init;          /*!< AWK required parameters 						*/
  HAL_LockTypeDef             Lock;          /*!< Locking object                    	*/
  __IO HAL_AWK_StateTypeDef   State;         /*!< AWK operation state               	*/
}AWK_HandleTypeDef;


/**
  * @}
  */ /* End of group AWK_Exported_Types */


/* Exported constants --------------------------------------------------------*/
/** @defgroup AWK_Exported_Constants AWK Exported Constants
  * @{
  */

/** @defgroup AWK_ClkSel AWK function clock source select
  * @{
  */
#define AWK_CLOCK_STOP              		(0x00000000U)              						/*!< Clock source stop */
#define AWK_CLOCK_LIRC           			  (AWK_CR_TCLKSEL_0)                    /*!< Gate function disable */
#define AWK_CLOCK_HXT										(AWK_CR_TCLKSEL_1)
#define AWK_CLOCK_LXT										(AWK_CR_TCLKSEL_1 | AWK_CR_TCLKSEL_0)
/**
  * @}
  */

/** @defgroup AWK_ClkDiv AWK function clock divider
  * @{
  */
#define AWK_CLOCK_DIV_2              		(0x00000000U)              																									/*!< Clock divider 2 */
#define AWK_CLOCK_DIV_4              		(AWK_CR_DIVSEL_0)              																							/*!< Clock divider 4 */
#define AWK_CLOCK_DIV_8           			(AWK_CR_DIVSEL_1)   																												/*!< Clock divider 8 */
#define AWK_CLOCK_DIV_16           			(AWK_CR_DIVSEL_1 | AWK_CR_DIVSEL_0) 																				/*!< Clock divider 16 */
#define AWK_CLOCK_DIV_32								(AWK_CR_DIVSEL_2) 																													/*!< Clock divider 32 */
#define AWK_CLOCK_DIV_64								(AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_0)																					/*!< Clock divider 64 */
#define AWK_CLOCK_DIV_128								(AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_1)																					/*!< Clock divider 128 */
#define AWK_CLOCK_DIV_256								(AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_1 | AWK_CR_DIVSEL_0)												/*!< Clock divider 256 */
#define AWK_CLOCK_DIV_512								(AWK_CR_DIVSEL_3)																														/*!< Clock divider 512 */
#define AWK_CLOCK_DIV_1024							(AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_0)																					/*!< Clock divider 1024 */
#define AWK_CLOCK_DIV_2048							(AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_1)																					/*!< Clock divider 2048 */
#define AWK_CLOCK_DIV_4096							(AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_1 | AWK_CR_DIVSEL_0)												/*!< Clock divider 4096 */
#define AWK_CLOCK_DIV_8192							(AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_2)																					/*!< Clock divider 8192 */
#define AWK_CLOCK_DIV_16384							(AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_0)												/*!< Clock divider 16384 */
#define AWK_CLOCK_DIV_32768							(AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_1)												/*!< Clock divider 32768 */
#define AWK_CLOCK_DIV_65536							(AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_1 | AWK_CR_DIVSEL_0)			/*!< Clock divider 65536 */

/**
  * @}
  */


/**
  * @}
  */ /* End of group AWK_Exported_Constants */



/* Exported functions --------------------------------------------------------*/
/** @addtogroup AWK_Exported_Functions
  * @{
  */

/** @addtogroup AWK_Exported_Functions_Group
 * @{
 */
/* AWK Base functions ********************************************************/
HAL_StatusTypeDef HAL_AWK_Init(AWK_HandleTypeDef *hawk);
HAL_StatusTypeDef HAL_AWK_DeInit(AWK_HandleTypeDef *hawk);
void HAL_AWK_MspInit(AWK_HandleTypeDef *hawk);
void HAL_AWK_MspDeInit(AWK_HandleTypeDef *hawk);
HAL_StatusTypeDef HAL_AWK_Start(AWK_HandleTypeDef *hawk);
HAL_StatusTypeDef HAL_AWK_Stop(AWK_HandleTypeDef *hawk);
void HAL_AWK_IRQHandler(AWK_HandleTypeDef *hawk);
void HAL_AWK_WakeUpCallback(AWK_HandleTypeDef *hawk);

/**
  * @}
  */ /* End of group AWK_Exported_Functions_Group */

/**
  * @}
  */ /* End of group AWK_Exported_Functions */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup AWK_Exported_Macros AWK Exported Macros
  * @{
  */

/** @brief  Reset AWK handle state
  * @param  __HANDLE__: AWK handle.
  * @retval None
  */
#define __HAL_AWK_RESET_HANDLE_STATE(__HANDLE__) 						((__HANDLE__)->State = HAL_AWK_STATE_RESET)


/**
  * @brief  Enable the AWK.
  * @param  __HANDLE__: AWK handle
  * @retval None
 */
#define __HAL_AWK_ENABLE(__HANDLE__)                 				((__HANDLE__)->Instance->CR |= (AWK_CR_AWKEN))


/**
  * @brief  Disable the AWK.
  * @param  __HANDLE__: AWK handle
  * @retval None
 */
#define __HAL_AWK_DISABLE(__HANDLE__)                 			((__HANDLE__)->Instance->CR &= ~(AWK_CR_AWKEN))


/**
  * @brief  Checks whether the specified AWK interrupt flag is set or not.
  * @param  __HANDLE__: specifies the AWK Handle.
  * @retval TRUE or FALSE.
  */
#define __HAL_AWK_GET_FLAG(__HANDLE__)          						(((__HANDLE__)->Instance->SR & (AWK_SR_AWUF)) == (AWK_SR_AWUF))


/**
  * @brief Clear the AWK interrupt pending bits
  * @param  __HANDLE__: AWK handle
  * @retval None
  */
#define __HAL_AWK_CLEAR_IT(__HANDLE__)        							((__HANDLE__)->Instance->INTCLR |= (AWK_INTCLR_INTCLR))


/**
  * @brief  Set the AWK Reload Register value on runtime.
  * @param  __HANDLE__: AWK handle.
  * @retval 8-bit value of the reload register (AWK_RELOAD)
  */
#define __HAL_AWK_SET_RELOAD(__HANDLE__, __VALUE__) 				((__HANDLE__)->Instance->RLOAD = (__VALUE__))


/**
  * @}
  */ /* End of group AWK_Exported_Macros */


/* Private Macros -----------------------------------------------------------*/
/** @defgroup AWK_Private_Macros AWK Private Macros
 * @{
 */ 
#define IS_AWK_INSTANCE(INSTANCE)			((INSTANCE) == AWK)   

/**
  * @}
  */ /* End of group AWK_Private_Macros */


/* Private Functions --------------------------------------------------------*/
/** @addtogroup AWK_Private_Functions
 * @{
 */


/**
  * @}
  */ /* End of group AWK_Private_Functions */


/**
  * @}
  */ /* End of group AWK */


#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_AWK_H */
