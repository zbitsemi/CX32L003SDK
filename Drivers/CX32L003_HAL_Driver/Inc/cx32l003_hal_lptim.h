/**
  ******************************************************************************
  * @file    cx32l003_hal_lptim.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of LPTIM HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_LPTIM_H
#define __CX32L003_HAL_LPTIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup LPTIM
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Types LPTIM Exported Types
  * @{
  */
/**
  * @brief  LPTIM Time base Configuration Structure definition
	* @note   This structure is for LPTIM 	
  */
typedef struct
{
	
  uint32_t GateEnable;     		/*!< Specifies gate function enable or disable.
                                   This parameter can be a value of @ref LPTIM_GateEnable */		
	
  uint32_t GateLevel;     		/*!< Specifies gate level high or low.
                                   This parameter can be a value of @ref LPTIM_GateLevel */	
	
  uint32_t ClkSel;     				/*!< Specifies low power timer clock.
                                   This parameter can be a value of @ref LPTIM_ClkSel */		
	
  uint32_t TogEnable;     		/*!< Specifies tog function enable or disable.
                                   This parameter can be a value of @ref LPTIM_TogEnable */	
	
  uint32_t CntTimSel;     		/*!< Specifies Counter/Timer function selection.
                                   This parameter can be a value of @ref LPTIM_CntTimSel */		
	
  uint32_t AutoReload;     		/*!< Specifies Timer auto reload enable or disable.
                                   This parameter can be a value of @ref LPTIM_AutoReload */		

  uint32_t Period;            /*!< Specifies the period value to be loaded into the active
                                   CNT value immediately through LOAD register or periodly through BGLOAD register
																	 refer to mode specified by LPTIM_AutoReload.
																	 Period caculation = (MaxCntLevel - Period)/(LPTIM clock)
                                   This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.  */

} LPTIM_Base_InitTypeDef;


/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_LPTIM_STATE_RESET             = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
  HAL_LPTIM_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_LPTIM_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  HAL_LPTIM_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  HAL_LPTIM_STATE_ERROR             = 0x04U     /*!< Reception process is ongoing                */
}HAL_LPTIM_StateTypeDef;


/**
  * @brief  LPTIM Base Time Base Handle Structure definition
  */
typedef struct
{
  LPTIM_TypeDef             		*Instance;     /*!< Register base address             	*/
  LPTIM_Base_InitTypeDef    		Init;          /*!< LPTIM Time Base required parameters */
  HAL_LockTypeDef             	Lock;          /*!< Locking object                    	*/
  __IO HAL_LPTIM_StateTypeDef   State;         /*!< LPTIM operation state               */
}LPTIM_HandleTypeDef;


/**
  * @}
  */ /* End of group LPTIM_Exported_Types */


/* Exported constants --------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Constants LPTIM Exported Constants
  * @{
  */

/** @defgroup LPTIM_GateEnable LPTIM gate function enable/disable
  * @{
  */
#define LPTIM_GATE_ENABLE              		(LPTIM_CR_GATE_EN)              	/*!< Gate function enable */
#define LPTIM_GATE_DISABLE           			0x00000000U                       /*!< Gate function disable */
/**
  * @}
  */


/** @defgroup LPTIM_GateLevel LPTIM gate level select
  * @{
  */
#define LPTIM_GATELEVEL_LOW               (LPTIM_CR_GATE_P)               	/*!< Specify gatelevel low for gate input */
#define LPTIM_GATELEVEL_HIGH           		0x00000000U                       /*!< Specify gatelevel high for gate input */
/**
  * @}
  */


/** @defgroup LPTIM_ClkSel LPTIM clock source select
  * @{
  */
#define LPTIM_CLOCK_SOURCE_PCLK           0x00000000U   	            								/*!< Specify PCLK as lptim clock source */
#define LPTIM_CLOCK_SOURCE_LXT           	(LPTIM_CR_TCK_SEL_1)                    		/*!< Specify LXT as lptim clock source */
#define LPTIM_CLOCK_SOURCE_LIRC						(LPTIM_CR_TCK_SEL_1 | LPTIM_CR_TCK_SEL_0)		/*!< Specify LIRC as lptim clock source */
/**
  * @}
  */


/** @defgroup LPTIM_TogEnable LPTIM tog function enable/disable
  * @{
  */
#define LPTIM_TOG_ENABLE              		(LPTIM_CR_TOG_EN)              		/*!< Tog function enable */
#define LPTIM_TOG_DISABLE           			0x00000000U                      	/*!< Tog function disable */
/**
  * @}
  */


/** @defgroup LPTIM_CntTimSel LPTIM select counter or timer function
  * @{
  */
#define LPTIM_COUNTER_SELECT              (LPTIM_CR_CT_SEL)              		/*!< Counter function select */
#define LPTIM_TIMER_SELECT           			0x00000000U                     	/*!< Timer function select */
/**
  * @}
  */


/** @defgroup LPTIM_AutoReload LPTIM auto reload enable/disable
  * @{
  */
#define LPTIM_AUTORELOAD_ENABLE           (LPTIM_CR_MODE)              			/*!< auto reload mode enable */
#define LPTIM_AUTORELOAD_DISABLE          0x00000000U                   		/*!< auto reload mode disable */
/**
  * @}
  */

/**
  * @}
  */ /* End of group LPTIM_Exported_Constants */



/* Exported functions --------------------------------------------------------*/
/** @addtogroup LPTIM_Exported_Functions
  * @{
  */

/** @addtogroup LPTIM_Exported_Functions_Group
 * @{
 */
/* Time Base functions ********************************************************/
HAL_StatusTypeDef HAL_LPTIM_Base_Init(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Base_DeInit(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_Base_MspInit(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_Base_MspDeInit(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Base_Start(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Base_Start_IT(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Base_Stop(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Base_Stop_IT(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_IRQHandler(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_PeriodElapsedCallback(LPTIM_HandleTypeDef *hlptim);

/**
  * @}
  */ /* End of group LPTIM_Exported_Functions_Group */

/**
  * @}
  */ /* End of group LPTIM_Exported_Functions */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Macros LPTIM Exported Macros
  * @{
  */

/** @brief  Reset LPTIM handle state
  * @param  __HANDLE__: LPTIM handle.
  * @retval None
  */
#define __HAL_LPTIM_RESET_HANDLE_STATE(__HANDLE__) 			((__HANDLE__)->State = HAL_LPTIM_STATE_RESET)


/**
  * @brief  Enable the LPTIM Clock.
  * @param  __HANDLE__: LPTIM handle
  * @retval None
 */
#define __HAL_LPTIM_CLOCK_ENABLE(__HANDLE__)           ((__HANDLE__)->Instance->CR |= (LPTIM_CR_TCK_EN))


/**
  * @brief  Disable the LPTIM Clock.
  * @param  __HANDLE__: LPTIM handle
  * @retval None
 */
#define __HAL_LPTIM_CLOCK_DISABLE(__HANDLE__)           ((__HANDLE__)->Instance->CR &= ~(LPTIM_CR_TCK_EN))


/**
  * @brief  Enable the LPTIM.
  * @param  __HANDLE__: LPTIM handle
  * @retval None
 */
#define __HAL_LPTIM_ENABLE(__HANDLE__)                 	((__HANDLE__)->Instance->CR |= (LPTIM_CR_TIM_RUN))


/**
  * @brief  Disable the LPTIM.
  * @param  __HANDLE__: LPTIM handle
  * @retval None
 */
#define __HAL_LPTIM_DISABLE(__HANDLE__)                 ((__HANDLE__)->Instance->CR &= ~(LPTIM_CR_TIM_RUN))


/**
  * @brief  Enables the specified LPTIM interrupt.
  * @param  __HANDLE__: specifies the LPTIM Handle.
  * @retval None
  */
#define __HAL_LPTIM_ENABLE_IT(__HANDLE__)    						((__HANDLE__)->Instance->CR |= (LPTIM_CR_INT_EN))


/**
  * @brief  Disables the specified LPTIM interrupt.
  * @param  __HANDLE__: specifies the LPTIM Handle.
  * @retval None
  */
#define __HAL_LPTIM_DISABLE_IT(__HANDLE__)    					((__HANDLE__)->Instance->CR &= ~(LPTIM_CR_INT_EN))


/**
  * @brief  Checks whether the specified LPTIM interrupt flag is set or not.
  * @param  __HANDLE__: specifies the LPTIM Handle.
  * @retval TRUE or FALSE.
  */
#define __HAL_LPTIM_GET_FLAG(__HANDLE__)          			(((__HANDLE__)->Instance->INTSR & (LPTIM_INTSR_INTF)) == (LPTIM_INTSR_INTF))


/**
  * @brief  Checks whether the specified LPTIM interrupt source is enable or disable.
  * @param  __HANDLE__: specifies the LPTIM Handle.
  * @retval TRUE or FALSE.
  */
#define __HAL_LPTIM_GET_IT_SOURCE(__HANDLE__)          	(((__HANDLE__)->Instance->CR & (LPTIM_CR_INT_EN)) == (LPTIM_CR_INT_EN))

/**
  * @brief Clear the LPTIM interrupt pending bits
  * @param  __HANDLE__: LPTIM handle
  * @retval None
  */
#define __HAL_LPTIM_CLEAR_IT(__HANDLE__)        				((__HANDLE__)->Instance->INTCLR |= (LPTIM_INTCLR_ICLR))


/**
  * @brief  Gets the LPTIM Counter Register value on runtime.
  * @param  __HANDLE__: LPTIM handle.
  * @retval 16-bit value of the timer counter register (LPTIM_CNTVAL)
  */
#define __HAL_LPTIM_GET_COUNTER(__HANDLE__) 						((__HANDLE__)->Instance->CNTVAL)


/**
  * @brief  Sets the LPTIM Counter Register value on runtime.
  * @param  __HANDLE__: LPTIM handle.
  * @param  __COUNTER__: Counter value.	
  * @retval None
  */
#define __HAL_LPTIM_SET_COUNTER(__HANDLE__, __COUNTER__) \
                        do { \
                          while (((__HANDLE__)->Instance->CR & LPTIM_CR_WT_FLAG) == LPTIM_CR_WT_FLAG); \
													WRITE_REG((__HANDLE__)->Instance->LOAD, (__COUNTER__));	\
                          while (((__HANDLE__)->Instance->CR & LPTIM_CR_WT_FLAG) == LPTIM_CR_WT_FLAG); \
													WRITE_REG((__HANDLE__)->Instance->BGLOAD, (__COUNTER__));	\
                        } while(0U)

/**
  * @brief  Enable gate function.
  * @param  __HANDLE__: LPTIM handle.
  * @retval None
  */
#define __HAL_LPTIM_ENABLE_GATE(__HANDLE__) 						(SET_BIT((__HANDLE__), LPTIM_CR_GATE_EN))


/**
  * @brief  Disable gate function.
  * @param  __HANDLE__: LPTIM handle.
  * @retval None
  */
#define __HAL_LPTIM_DISABLE_GATE(__HANDLE__) 						(CLEAR_BIT((__HANDLE__), LPTIM_CR_GATE_EN))


/**
  * @brief  Enable tog function.
  * @param  __HANDLE__: LPTIM handle.
  * @retval None
  */
#define __HAL_LPTIM_ENABLE_TOG(__HANDLE__) 							(SET_BIT((__HANDLE__), LPTIM_CR_TOG_EN))


/**
  * @brief  Disable tog function.
  * @param  __HANDLE__: LPTIM handle.
  * @retval None
  */
#define __HAL_LPTIM_DISABLE_TOG(__HANDLE__) 						(CLEAR_BIT((__HANDLE__), LPTIM_CR_TOG_EN))


/**
  * @brief  Set gate level high.
  * @param  __HANDLE__: LPTIM handle.
  * @retval None
  */
#define __HAL_LPTIM_GATELEVEL_HIGH(__HANDLE__) 					(CLEAR_BIT((__HANDLE__), LPTIM_CR_GATE_P))


/**
  * @brief  Set gate level low.
  * @param  __HANDLE__: LPTIM handle.
  * @retval None
  */
#define __HAL_LPTIM_GATELEVEL_LOW(__HANDLE__) 					(SET_BIT((__HANDLE__), LPTIM_CR_GATE_P))


/**
  * @brief  Wait for LPTIM WT sync finish.
  * @param  __MODULE__: specifies the LPTIM.
  * @retval TRUE or FALSE.
  */
#define __HAL_LPTIM_SYNC_FLAG(__MODULE__)          			(((__MODULE__)->CR & (LPTIM_CR_WT_FLAG)) == (LPTIM_CR_WT_FLAG))


/**
  * @}
  */ /* End of group LPTIM_Exported_Macros */


/* Private Macros -----------------------------------------------------------*/
/** @defgroup LPTIM_Private_Macros LPTIM Private Macros
 * @{
 */ 
#define IS_LPTIM_INSTANCE(INSTANCE)			((INSTANCE) == LPTIM)   

/**
  * @}
  */ /* End of group LPTIM_Private_Macros */


/* Private Functions --------------------------------------------------------*/
/** @addtogroup LPTIM_Private_Functions
 * @{
 */


/**
  * @}
  */ /* End of group LPTIM_Private_Functions */




/**
  * @}
  */ /* End of group LPTIM */


#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_LPTIM_H */
