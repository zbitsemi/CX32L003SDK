/**
  ******************************************************************************
  * @file    cx32l003_hal_clktrim.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of CLKTRIM HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_CLKTRIM_H
#define __CX32L003_HAL_CLKTRIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup CLKTRIM
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup CLKTRIM_Exported_Types CLKTRIM Exported Types
  * @{
  */
	
/**
  * @brief  CLKTRIM Configuration Structure definition
	* @note   This structure is for CLKTRIM 	
  */
typedef struct
{	
  uint32_t ReferClockSel;     				/*!< Specifies reference clock.
																					 This parameter can be a value of @ref CLKTRIM_ReferClockSel */		
	
  uint32_t MonitorCalClockSel;     		/*!< Specifies monitor clock.
																					 This parameter can be a value of @ref CLKTRIM_MonitorCalClockSel */	
	
  uint32_t MonitorInterval;						/*!< Specifies monitor interval time.
																					 This parameter can be a value between 0x00000000 an 0xFFFFFFFF */	
	
  uint32_t MonitorOverflowTime;     	/*!< Specifies monitor overflow time.
																					 This parameter can be a value between 0x0000 an 0xFFFF */	
	
}CLKTRIM_InitTypeDef;


/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_CLKTRIM_STATE_RESET             = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
  HAL_CLKTRIM_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_CLKTRIM_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  HAL_CLKTRIM_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  HAL_CLKTRIM_STATE_ERROR             = 0x04U     /*!< An error is generated                 			 */
}HAL_CLKTRIM_StateTypeDef;


/**
  * @brief  CLKTRIM Handle Structure definition
  */
typedef struct
{
  CLKTRIM_TypeDef             		*Instance;     /*!< Register base address             	*/
  CLKTRIM_InitTypeDef    					Init;          /*!< CLKTRIM required parameters 						*/
  HAL_LockTypeDef             		Lock;          /*!< Locking object                    	*/
  __IO HAL_CLKTRIM_StateTypeDef   State;         /*!< CLKTRIM operation state               	*/
}CLKTRIM_HandleTypeDef;


/**
  * @}
  */ /* End of group CLKTRIM_Exported_Types */


/* Exported constants --------------------------------------------------------*/
/** @defgroup CLKTRIM_Exported_Constants CLKTRIM Exported Constants
  * @{
  */

/** @defgroup CLKTRIM_ReferClockSel Select reference clock
  * @{
  */
#define CLKTRIM_REFCLK_HIRC              	(0x00000000U)              																/*!< Reference clock select HIRC */
#define CLKTRIM_REFCLK_HXT           			(CLKTRIM_CR_REFCLK_SEL_0)                    							/*!< Reference clock select HXT */
#define CLKTRIM_REFCLK_LIRC								(CLKTRIM_CR_REFCLK_SEL_1)																	/*!< Reference clock select LIRC */
#define CLKTRIM_REFCLK_LXT								(CLKTRIM_CR_REFCLK_SEL_1 | CLKTRIM_CR_REFCLK_SEL_0)				/*!< Reference clock select LXT */
#define CLKTRIM_REFCLK_HXTBYPASS					(CLKTRIM_CR_REFCLK_SEL_2 | CLKTRIM_CR_REFCLK_SEL_0)				/*!< Reference clock select HXTBYPASS */

/**
  * @}
  */


/** @defgroup CLKTRIM_MonitorCalClockSel Select monitor/calibration clock
  * @{
  */
#define CLKTRIM_MONCALCLK_HIRC            (0x00000000U)              																/*!< Monitor or calibration clock select HIRC */
#define CLKTRIM_MONCALCLK_HXT           	(CLKTRIM_CR_CALCLK_SEL_0)                    							/*!< Monitor or calibration clock select HXT */
#define CLKTRIM_MONCALCLK_LIRC						(CLKTRIM_CR_CALCLK_SEL_1)																	/*!< Monitor or calibration clock select LIRC */
#define CLKTRIM_MONCALCLK_LXT							(CLKTRIM_CR_CALCLK_SEL_1 | CLKTRIM_CR_CALCLK_SEL_0)				/*!< Monitor or calibration clock select LXT */

/**
  * @}
  */

/** @defgroup CLKTRIM_Interrupt_Flags CLKTRIM interrupt flags
  * @{
  */
#define CLKTRIM_FLAG_HXTFAULT            	(CLKTRIM_IFR_HXT_FAULT)              											
#define CLKTRIM_FLAG_LXTFAULT           	(CLKTRIM_IFR_LXT_FAULT)                    							
#define CLKTRIM_FLAG_CALCNTOVF						(CLKTRIM_IFR_CALCNT_OVF)
#define CLKTRIM_FLAG_STOP									(CLKTRIM_IFR_STOP)

/**
  * @}
  */


/**
  * @}
  */ /* End of group CLKTRIM_Exported_Constants */



/* Exported functions --------------------------------------------------------*/
/** @addtogroup CLKTRIM_Exported_Functions
  * @{
  */

/** @addtogroup CLKTRIM_Exported_Functions_Group
 * @{
 */
/* CLKTRIM Base functions ********************************************************/
HAL_StatusTypeDef HAL_CLKTRIM_Init(CLKTRIM_HandleTypeDef *hclktrim);
HAL_StatusTypeDef HAL_CLKTRIM_DeInit(CLKTRIM_HandleTypeDef *hclktrim);
void HAL_CLKTRIM_MspInit(CLKTRIM_HandleTypeDef *hclktrim);
void HAL_CLKTRIM_MspDeInit(CLKTRIM_HandleTypeDef *hclktrim);
HAL_StatusTypeDef HAL_CLKTRIM_Enable(CLKTRIM_HandleTypeDef *hclktrim);
HAL_StatusTypeDef HAL_CLKTRIM_Enable_IT(CLKTRIM_HandleTypeDef *hclktrim);
HAL_StatusTypeDef HAL_CLKTRIM_Disable(CLKTRIM_HandleTypeDef *hclktrim);


/**
  * @}
  */ /* End of group CLKTRIM_Exported_Functions_Group */

/**
  * @}
  */ /* End of group CLKTRIM_Exported_Functions */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup CLKTRIM_Exported_Macros CLKTRIM Exported Macros
  * @{
  */

/** @brief  Reset CLKTRIM handle state
  * @param  __HANDLE__: CLKTRIM handle.
  * @retval None
  */
#define __HAL_CLKTRIM_RESET_HANDLE_STATE(__HANDLE__) 									((__HANDLE__)->State = HAL_CLKTRIM_STATE_RESET)


/** @brief  Enable CLKTRIM reference and monitor clock
  * @param  __HANDLE__: specifies the CLKTRIM Handle.
  *         CLKTRIM Handle selects the CLKTRIM peripheral.
  */
#define __HAL_CLKTRIM_CLOCK_ENABLE(__HANDLE__)               					SET_BIT((__HANDLE__)->Instance->CR, CLKTRIM_CR_CLKEN) 


/** @brief  Disable CLKTRIM reference and monitor clock
  * @param  __HANDLE__: specifies the CLKTRIM Handle.
  *         CLKTRIM Handle selects the CLKTRIM peripheral.
  */
#define __HAL_CLKTRIM_CLOCK_DISABLE(__HANDLE__)               				CLEAR_BIT((__HANDLE__)->Instance->CR, CLKTRIM_CR_CLKEN) 


/** @brief  Enable CLKTRIM monitor function
  * @param  __HANDLE__: specifies the CLKTRIM Handle.
  *         CLKTRIM Handle selects the CLKTRIM peripheral.
  */
#define __HAL_CLKTRIM_MONITOR_ENABLE(__HANDLE__)               				SET_BIT((__HANDLE__)->Instance->CR, CLKTRIM_CR_MON_EN) 


/** @brief  Disable CLKTRIM monitor function
  * @param  __HANDLE__: specifies the CLKTRIM Handle.
  *         CLKTRIM Handle selects the CLKTRIM peripheral.
  */
#define __HAL_CLKTRIM_MONITOR_DISABLE(__HANDLE__)               			CLEAR_BIT((__HANDLE__)->Instance->CR, CLKTRIM_CR_MON_EN) 


/** @brief  CLKTRIM monitor/calibration start
  * @param  __HANDLE__: specifies the CLKTRIM Handle.
  *         CLKTRIM Handle selects the CLKTRIM peripheral.
  */
#define __HAL_CLKTRIM_START(__HANDLE__)               								SET_BIT((__HANDLE__)->Instance->CR, CLKTRIM_CR_TRIM_START) 


/** @brief  CLKTRIM monitor/calibration stop
  * @param  __HANDLE__: specifies the CLKTRIM Handle.
  *         CLKTRIM Handle selects the CLKTRIM peripheral.
  */
#define __HAL_CLKTRIM_STOP(__HANDLE__)               									CLEAR_BIT((__HANDLE__)->Instance->CR, CLKTRIM_CR_TRIM_START) 


/**
  * @brief  Enables the specified CLKTRIM interrupt.
  * @param  __HANDLE__: specifies the CLKTRIM Handle.
  * @retval None
  */
#define __HAL_CLKTRIM_ENABLE_IT(__HANDLE__)    												((__HANDLE__)->Instance->CR |= (CLKTRIM_CR_IE))


/**
  * @brief  Disables the specified CLKTRIM interrupt.
  * @param  __HANDLE__: specifies the CLKTRIM Handle.
  * @retval None
  */
#define __HAL_CLKTRIM_DISABLE_IT(__HANDLE__)    											((__HANDLE__)->Instance->CR &= ~(CLKTRIM_CR_IE))



/**
  * @brief  Checks whether the specified CLKTRIM interrupt flag is set or not.
  * @param  __HANDLE__: specifies the CLKTRIM Handle.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg CLKTRIM_FLAG_HXTFAULT: high speed extern clock fault
  *            @arg CLKTRIM_FLAG_LXTFAULT: low speed extern clock fault
  *            @arg CLKTRIM_FLAG_CALCNTOVF: calibration counter overflow	
  *            @arg CLKTRIM_FLAG_STOP: reference clock stop	
	*
  * @retval TRUE or FALSE.
  */
#define __HAL_CLKTRIM_GET_FLAG(__HANDLE__, __FLAG__)          	(((__HANDLE__)->Instance->IFR & (__FLAG__)) == (__FLAG__))


/** @brief  Clears the specified CLKTRIM pending flag.
  * @param  __HANDLE__: specifies the CLKTRIM Handle.
  *         This parameter should be CLKTRIM to select the peripheral.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg CLKTRIM_FLAG_HXTFAULT: high speed extern clock fault
  *            @arg CLKTRIM_FLAG_LXTFAULT: low speed extern clock fault
  *            @arg CLKTRIM_FLAG_CALCNTOVF: calibration counter overflow	
  *            @arg CLKTRIM_FLAG_STOP: reference clock stop	
  *   
  */
	#define __HAL_CLKTRIM_CLEAR_FLAG(__HANDLE__, __FLAG__) 					(((__FLAG__)&CLKTRIM_FLAG_HXTFAULT)==CLKTRIM_FLAG_HXTFAULT ? (__HANDLE__)->Instance->ICLR |= (__FLAG__):\
																																	 ((__FLAG__)&CLKTRIM_FLAG_LXTFAULT)==CLKTRIM_FLAG_LXTFAULT ? (__HANDLE__)->Instance->ICLR |= (__FLAG__):\
																																	 (__HANDLE__)->Instance->CR &= (~CLKTRIM_CR_TRIM_START))


/**
  * @}
  */ /* End of group CLKTRIM_Exported_Macros */


/* Private Macros -----------------------------------------------------------*/
/** @defgroup CLKTRIM_Private_Macros CLKTRIM Private Macros
 * @{
 */ 
#define IS_CLKTRIM_INSTANCE(INSTANCE)			((INSTANCE) == CLKTRIM)   

/**
  * @}
  */ /* End of group CLKTRIM_Private_Macros */


/* Private Functions --------------------------------------------------------*/
/** @addtogroup CLKTRIM_Private_Functions
 * @{
 */


/**
  * @}
  */ /* End of group CLKTRIM_Private_Functions */


/**
  * @}
  */ /* End of group CLKTRIM */


#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_CLKTRIM_H */
