/**
  ******************************************************************************
  * @file    cx32l003_hal_basetim.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of BASETIM HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_BASETIM_H
#define __CX32L003_HAL_BASETIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup BASETIM
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup BASETIM_Exported_Types BASETIM Exported Types
  * @{
  */
/**
  * @brief  BASETIM Time base Configuration Structure definition
	* @note   This structure is for TIM10/11 	
  */
typedef struct
{
	
  uint32_t GateEnable;     		/*!< Specifies gate function enable or disable.
                                   This parameter can be a value of @ref BASETIM_GateEnable */		
	
  uint32_t GateLevel;     		/*!< Specifies gate level high or low.
                                   This parameter can be a value of @ref BASETIM_GateLevel */	
	
  uint32_t TogEnable;     		/*!< Specifies tog function enable or disable.
                                   This parameter can be a value of @ref BASETIM_TogEnable */	
	
  uint32_t CntTimSel;     		/*!< Specifies Counter/Timer function selection.
                                   This parameter can be a value of @ref BASETIM_CntTimSel */		
	
  uint32_t AutoReload;     		/*!< Specifies Timer auto reload enable or disable.
                                   This parameter can be a value of @ref BASETIM_AutoReload */		
	
  uint32_t MaxCntLevel;     	/*!< Specifies Timer maxim counter value is 0xFFFF or 0xFFFFFFFF.
                                   This parameter can be a value of @ref BASETIM_MaxCntLevel */		
	
  uint32_t OneShot; 					/*!< Specifies Timer oneshot or repeat mode.
                                   This parameter can be a value of @ref BASETIM_OneShot */
	
  uint32_t Prescaler;         /*!< Specifies the prescaler value used to divide the BASETIM clock.
                                   This parameter can be a value of @ref BASETIM_Prescaler */

  uint32_t Period;            /*!< Specifies the period value to be loaded into the active
                                   CNT value immediately through LOAD register or periodly through BGLOAD register
																	 refer to mode specified by BASETIM_AutoReload.
																	 Period caculation = (MaxCntLevel - Period)/((BASETIM clock)/Prescaler)
                                   This parameter can be a number between Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF.  */

} BASETIM_Base_InitTypeDef;


/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_BASETIM_STATE_RESET             = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
  HAL_BASETIM_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_BASETIM_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  HAL_BASETIM_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  HAL_BASETIM_STATE_ERROR             = 0x04U     /*!< Reception process is ongoing                */
}HAL_BASETIM_StateTypeDef;


/**
  * @brief  BASETIM Base Time Base Handle Structure definition
  */
typedef struct
{
  BASETIM_TypeDef             		*Instance;     /*!< Register base address             		*/
  BASETIM_Base_InitTypeDef    		Init;          /*!< BASETIM Time Base required parameters */
  HAL_LockTypeDef             		Lock;          /*!< Locking object                    */
  __IO HAL_BASETIM_StateTypeDef   State;         /*!< TIM operation state               */
}BASETIM_HandleTypeDef;


/**
  * @}
  */ /* End of group BASETIM_Exported_Types */


/* Exported constants --------------------------------------------------------*/
/** @defgroup BASETIM_Exported_Constants BASETIM Exported Constants
  * @{
  */

/** @defgroup BASETIM_GateEnable BASETIM gate function enable/disable
  * @{
  */
#define BASETIM_GATE_ENABLE              		(BASETIM_CR_GATE_EN)              /*!< Gate function enable */
#define BASETIM_GATE_DISABLE           			0x00000000U                       /*!< Gate function disable */
/**
  * @}
  */


/** @defgroup BASETIM_GateLevel BASETIM gate level select
  * @{
  */
#define BASETIM_GATELEVEL_LOW               (BASETIM_CR_GATE_P)               /*!< Specify gatelevel low for gate input */
#define BASETIM_GATELEVEL_HIGH           		0x00000000U                       /*!< Specify gatelevel high for gate input */
/**
  * @}
  */


/** @defgroup BASETIM_TogEnable BASETIM tog function enable/disable
  * @{
  */
#define BASETIM_TOG_ENABLE              		(BASETIM_CR_TOG_EN)              /*!< Tog function enable */
#define BASETIM_TOG_DISABLE           			0x00000000U                      /*!< Tog function disable */
/**
  * @}
  */


/** @defgroup BASETIM_CntTimSel BASETIM select counter or timer function
  * @{
  */
#define BASETIM_COUNTER_SELECT              (BASETIM_CR_CT_SEL)              /*!< Counter function select */
#define BASETIM_TIMER_SELECT           			0x00000000U                      /*!< Timer function select */
/**
  * @}
  */


/** @defgroup BASETIM_AutoReload BASETIM auto reload enable/disable
  * @{
  */
#define BASETIM_AUTORELOAD_ENABLE           (BASETIM_CR_MODE)              		/*!< auto reload mode enable */
#define BASETIM_AUTORELOAD_DISABLE          0x00000000U                   		/*!< auto reload mode disable */
/**
  * @}
  */

/** @defgroup BASETIM_MaxCntLevel BASETIM maxim counter value set
  * @{
  */
#define BASETIM_MAXCNTLEVEL_32BIT           (BASETIM_CR_TMR_SIZE)             /*!< configure base timer maxim counter value is 0xFFFFFFFF */
#define BASETIM_MAXCNTLEVEL_16BIT           0x00000000U                   		/*!< configure base timer maxim counter value is 0xFFFF */
/**
  * @}
  */


/** @defgroup BASETIM_MaxCntNum BASETIM maxim counter value number
  * @{
  */
#define BASETIM_MAXCNTVALUE_32BIT           (0xFFFFFFFFU)             				/*!< base timer maxim counter value 0xFFFFFFFF */
#define BASETIM_MAXCNTVALUE_16BIT           (0x0000FFFFU)                   	/*!< base timer maxim counter value 0xFFFF */
/**
  * @}
  */


/** @defgroup BASETIM_OneShot BASETIM one shot mode or repeat mode
  * @{
  */
#define BASETIM_ONESHOT_MODE           			(BASETIM_CR_ONESHOT)             /*!< base timer oneshot mode */
#define BASETIM_REPEAT_MODE           			0x00000000U                   	 /*!< base timer repeat mode */
/**
  * @}
  */


/** @defgroup BASETIM_Prescaler BASETIM prescaler setting
  * @{
  */
#define BASETIM_PRESCALER_DIV1              (0x00000000)
#define BASETIM_PRESCALER_DIV2              (BASETIM_CR_TMR_PRSC_0)
#define BASETIM_PRESCALER_DIV4              (BASETIM_CR_TMR_PRSC_1)
#define BASETIM_PRESCALER_DIV8              (BASETIM_CR_TMR_PRSC_0 | BASETIM_CR_TMR_PRSC_1)
#define BASETIM_PRESCALER_DIV16             (BASETIM_CR_TMR_PRSC_2)
#define BASETIM_PRESCALER_DIV32             (BASETIM_CR_TMR_PRSC_2 | BASETIM_CR_TMR_PRSC_0)
#define BASETIM_PRESCALER_DIV64             (BASETIM_CR_TMR_PRSC_2 | BASETIM_CR_TMR_PRSC_1)
#define BASETIM_PRESCALER_DIV128            (BASETIM_CR_TMR_PRSC_2 | BASETIM_CR_TMR_PRSC_1 | BASETIM_CR_TMR_PRSC_0)

/**
  * @}
  */


/**
  * @}
  */ /* End of group BASETIM_Exported_Constants */



/* Exported functions --------------------------------------------------------*/
/** @addtogroup BASETIM_Exported_Functions
  * @{
  */

/** @addtogroup BASETIM_Exported_Functions_Group
 * @{
 */
/* Base Time Base functions ***************************************************/
HAL_StatusTypeDef HAL_BASETIM_Base_Init(BASETIM_HandleTypeDef *hbasetim);
HAL_StatusTypeDef HAL_BASETIM_Base_DeInit(BASETIM_HandleTypeDef *hbasetim);
void HAL_BASETIM_Base_MspInit(BASETIM_HandleTypeDef *hbasetim);
void HAL_BASETIM_Base_MspDeInit(BASETIM_HandleTypeDef *hbasetim);
HAL_StatusTypeDef HAL_BASETIM_Base_Start(BASETIM_HandleTypeDef *hbasetim);
HAL_StatusTypeDef HAL_BASETIM_Base_Start_IT(BASETIM_HandleTypeDef *hbasetim);
HAL_StatusTypeDef HAL_BASETIM_Base_Stop(BASETIM_HandleTypeDef *hbasetim);
HAL_StatusTypeDef HAL_BASETIM_Base_Stop_IT(BASETIM_HandleTypeDef *hbasetim);
void HAL_BASETIM_PeriodElapsedCallback(BASETIM_HandleTypeDef *htim);
void HAL_BASETIM_IRQHandler(BASETIM_HandleTypeDef *hbasetim);
/**
  * @}
  */ /* End of group BASETIM_Exported_Functions_Group */

/**
  * @}
  */ /* End of group BASETIM_Exported_Functions */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup BASETIM_Exported_Macros BASETIM Exported Macros
  * @{
  */

/** @brief  Reset BASETIM handle state
  * @param  __HANDLE__: BASETIM handle.
  * @retval None
  */
#define __HAL_BASETIM_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_BASETIM_STATE_RESET)

/**
  * @brief  Enable the BASETIM.
  * @param  __HANDLE__: BASETIM handle
  * @retval None
 */
#define __HAL_BASETIM_ENABLE(__HANDLE__)                 ((__HANDLE__)->Instance->CR |= (BASETIM_CR_TR))


/**
  * @brief  Disable the BASETIM.
  * @param  __HANDLE__: BASETIM handle
  * @retval None
 */
#define __HAL_BASETIM_DISABLE(__HANDLE__)                 ((__HANDLE__)->Instance->CR &= ~(BASETIM_CR_TR))


/**
  * @brief  Enables the specified BASETIM interrupt.
  * @param  __HANDLE__: specifies the BASETIM Handle.
  * @retval None
  */
#define __HAL_BASETIM_ENABLE_IT(__HANDLE__)    								((__HANDLE__)->Instance->CR |= (BASETIM_CR_INTEN))


/**
  * @brief  Disables the specified BASETIM interrupt.
  * @param  __HANDLE__: specifies the BASETIM Handle.
  * @retval None
  */
#define __HAL_BASETIM_DISABLE_IT(__HANDLE__)    							((__HANDLE__)->Instance->CR &= ~(BASETIM_CR_INTEN))


/**
  * @brief  Checks whether the specified BASETIM interrupt flag is set or not.
  * @param  __HANDLE__: specifies the BASETIM Handle.
  * @retval TRUE or FALSE.
  */
#define __HAL_BASETIM_GET_FLAG(__HANDLE__)          							(((__HANDLE__)->Instance->MSKINTSR & (BASETIM_MSKINTSR_TF)) == (BASETIM_MSKINTSR_TF))


/**
  * @brief  Checks whether the specified BASETIM interrupt flag is set or not.
  * @param  __HANDLE__: specifies the BASETIM Handle.
  * @retval TRUE or FALSE.
  */
#define __HAL_BASETIM_GET_RAWFLAG(__HANDLE__)          						(((__HANDLE__)->Instance->RAWINTSR & (BASETIM_RAWINTSR_RIS)) == (BASETIM_RAWINTSR_RIS))


/**
  * @brief Clear the BASETIM interrupt pending bits
  * @param  __HANDLE__: BASETIM handle
  * @retval None
  */
#define __HAL_BASETIM_CLEAR_IT(__HANDLE__)        								((__HANDLE__)->Instance->INTCLR |= (BASETIM_INTCLR_INTCLR))


/**
  * @brief  Checks whether the specified BASETIM interrupt source is enable or disable.
  * @param  __HANDLE__: specifies the BASETIM Handle.
  * @retval TRUE or FALSE.
  */
#define __HAL_BASETIM_GET_IT_SOURCE(__HANDLE__)          							(((__HANDLE__)->Instance->CR & (BASETIM_CR_INTEN)) == (BASETIM_CR_INTEN))



/**
  * @brief  Sets the BASETIM active prescaler register value.
  * @param  __HANDLE__: BASETIM handle.
  * @param  __PRESC__:  This parameter can be a value of @ref BASETIM_Prescaler.
  * @retval None
  */
#define __HAL_BASETIM_SET_PRESCALER(__HANDLE__, __PRESC__)      	(MODIFY_REG((__HANDLE__)->Instance->CR, BASETIM_CR_TMR_PRSC, (__PRESC__))) 



/**
  * @brief  Gets the BASETIM Counter Register value on runtime.
  * @param  __HANDLE__: BASETIM handle.
  * @retval 32-bit value of the timer counter register (TIMx_CNT)
  */
#define __HAL_BASETIM_GET_COUNTER(__HANDLE__) 										((__HANDLE__)->Instance->CNT)



/**
  * @brief  Enable oneshot function.
  * @param  __HANDLE__: BASETIM handle.
  * @retval None
  */
#define __HAL_BASETIM_ENABLE_ONESHOT(__HANDLE__) 									(SET_BIT((__HANDLE__), BASETIM_CR_ONESHOT))


/**
  * @brief  Enable repeat function.
  * @param  __HANDLE__: BASETIM handle.
  * @retval None
  */
#define __HAL_BASETIM_ENABLE_REPEAT(__HANDLE__) 									(CLEAR_BIT((__HANDLE__), BASETIM_CR_ONESHOT))


/**
  * @brief  Enable gate function.
  * @param  __HANDLE__: BASETIM handle.
  * @retval None
  */
#define __HAL_BASETIM_ENABLE_GATE(__HANDLE__) 										(SET_BIT((__HANDLE__), BASETIM_CR_GATE_EN))


/**
  * @brief  Disable gate function.
  * @param  __HANDLE__: BASETIM handle.
  * @retval None
  */
#define __HAL_BASETIM_DISABLE_GATE(__HANDLE__) 										(CLEAR_BIT((__HANDLE__), BASETIM_CR_GATE_EN))


/**
  * @brief  Enable tog function.
  * @param  __HANDLE__: BASETIM handle.
  * @retval None
  */
#define __HAL_BASETIM_ENABLE_TOG(__HANDLE__) 											(SET_BIT((__HANDLE__), BASETIM_CR_TOG_EN))


/**
  * @brief  Disable tog function.
  * @param  __HANDLE__: BASETIM handle.
  * @retval None
  */
#define __HAL_BASETIM_DISABLE_TOG(__HANDLE__) 										(CLEAR_BIT((__HANDLE__), BASETIM_CR_TOG_EN))


/**
  * @brief  Set gate level high.
  * @param  __HANDLE__: BASETIM handle.
  * @retval None
  */
#define __HAL_BASETIM_GATELEVEL_HIGH(__HANDLE__) 									(CLEAR_BIT((__HANDLE__), BASETIM_CR_GATE_P))


/**
  * @brief  Set gate level low.
  * @param  __HANDLE__: BASETIM handle.
  * @retval None
  */
#define __HAL_BASETIM_GATELEVEL_LOW(__HANDLE__) 									(SET_BIT((__HANDLE__), BASETIM_CR_GATE_P))


/**
  * @}
  */ /* End of group BASETIM_Exported_Macros */




/* Private Macros -----------------------------------------------------------*/
/** @defgroup BASETIM_Private_Macros BASETIM Private Macros
 * @{
 */
 
#define IS_BASETIM_INSTANCE(INSTANCE)\
  (((INSTANCE) == TIM10)    || \
   ((INSTANCE) == TIM11))    


/**
  * @}
  */ /* End of group BASETIM_Private_Macros */


/* Private Functions --------------------------------------------------------*/
/** @addtogroup BASETIM_Private_Functions
 * @{
 */


/**
  * @}
  */ /* End of group BASETIM_Private_Functions */




/**
  * @}
  */ /* End of group BASETIM */


#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_BASETIM_H */
