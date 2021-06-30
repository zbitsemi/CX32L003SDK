/**
  ******************************************************************************
  * @file    cx32l003_hal_pca.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of PCA HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_PCA_H
#define __CX32L003_HAL_PCA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup PCA
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PCA_Exported_Types PCA Exported Types
  * @{
  */
/**
  * @brief  PCA Configuration Structure definition
	* @note   This structure is for PCA 	
  */
typedef struct
{
  uint32_t ClkSrcSel;     				/*!< Specifies input capture clock source.
																			 This parameter can be a value of @ref PCA_ClkSrcSel */		
	
  uint32_t RunInIdleMode;     		/*!< PCA is enabled or disabled in IDLE mode.
																			 This parameter can be a value of @ref PCA_RunInIdleMode */	
} PCA_Base_InitTypeDef;



/**
  * @brief  PCA Input Capture Configuration Structure definition
  */
typedef struct
{
  uint32_t  ICPolarity;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref PCA_Input_Capture_Polarity */

} PCA_IC_InitTypeDef;


/**
  * @brief  PCA Output Compare Configuration Structure definition
  */
typedef struct
{
  uint32_t  CompareEnable;   /*!< Specifies the output compare function enable or disable.
																	This parameter can be a value of @ref PCA_Output_Compare_Enable */

  uint32_t 	TogEnable;     	 /*!< Specifies tog function enable or disable.
																	TogEnable & PwmEnable must not be enabled at the same time.
                                  This parameter can be a value of @ref PCA_TogEnable */		
	
  uint32_t 	PwmEnable;     	 /*!< Specifies tog function enable or disable.
																	TogEnable & PwmEnable must not be enabled at the same time.	
                                  This parameter can be a value of @ref PCA_PwmEnable */			
	
  uint32_t 	Period;          /*!< Specifies the period value compared with CNT register.
																	Period caculation = Period/(PCA clock)
                                  This parameter can be a number between Min_Data = 0x00 and Max_Data = 0xFF. */	
	
} PCA_OC_InitTypeDef;



/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_PCA_STATE_RESET             = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
  HAL_PCA_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_PCA_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  HAL_PCA_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  HAL_PCA_STATE_ERROR             = 0x04U     /*!< Reception process is ongoing                */
}HAL_PCA_StateTypeDef;


/**
  * @brief  PCA Handle Structure definition
  */
typedef struct
{
  PCA_TypeDef             		*Instance;     /*!< Register base address             	*/
  PCA_Base_InitTypeDef    		Init;          /*!< PCA required basic parameters 			*/
  HAL_LockTypeDef             Lock;          /*!< Locking object                    	*/
  __IO HAL_PCA_StateTypeDef   State;         /*!< PCA operation state               	*/
}PCA_HandleTypeDef;


/**
  * @}
  */ /* End of group PCA_Exported_Types */


/* Exported constants --------------------------------------------------------*/
/** @defgroup PCA_Exported_Constants PCA Exported Constants
  * @{
  */

/** @defgroup PCA_ClkSrcSel PCA input capture clock source select
  * @{
  */
#define PCA_CLOCK_SOURCE_PCLKDIV32           		0x00000000U   	            											/*!< Specify PCLK divider 32 as pca input clock source */
#define PCA_CLOCK_SOURCE_PCLKDIV16           		(PCA_MOD_CPS_0)                    								/*!< Specify PCLK divider 16 as pca input clock source */
#define PCA_CLOCK_SOURCE_PCLKDIV8								(PCA_MOD_CPS_1)																		/*!< Specify PCLK divider 8 as pca input clock source */
#define PCA_CLOCK_SOURCE_PCLKDIV4								(PCA_MOD_CPS_1 | PCA_MOD_CPS_0)										/*!< Specify PCLK divider 4 as pca input clock source */
#define PCA_CLOCK_SOURCE_PCLKDIV2								(PCA_MOD_CPS_2)																		/*!< Specify PCLK divider 2 as pca input clock source */
#define PCA_CLOCK_SOURCE_TIM0_OVERFLOW					(PCA_MOD_CPS_2 | PCA_MOD_CPS_0)										/*!< Specify TIM0 overflow as pca input clock source */
#define PCA_CLOCK_SOURCE_TIM1_OVERFLOW					(PCA_MOD_CPS_2 | PCA_MOD_CPS_1)										/*!< Specify TIM1 overflow as pca input clock source */
#define PCA_CLOCK_SOURCE_ECI										(PCA_MOD_CPS_2 | PCA_MOD_CPS_1 | PCA_MOD_CPS_0)		/*!< Specify ECI as pca input clock source */

/**
  * @}
  */

/** @defgroup PCA_RunInIdleMode PCA is enabled or disabled in IDLE mode.
  * @{
  */
#define PCA_IDLEMODE_DISABLE										(0x00000000)	
#define PCA_IDLEMODE_ENABLE											(0x00000001)	

/**
  * @}
  */


/** @defgroup PCA_Input_Capture_Polarity PCA input capture polarity selection
	* @note	CCAPMx(1,2,3,4)'s position is same as CCAPM0
  * @{
  */
#define PCA_INPUT_POLARITY_NONE											(0x00000000)	
#define PCA_INPUT_POLARITY_FALLING									(PCA_CCAPM0_CAPN)
#define PCA_INPUT_POLARITY_RISING										(PCA_CCAPM0_CAPP)
#define PCA_INPUT_POLARITY_BOTH											(PCA_CCAPM0_CAPN | PCA_CCAPM0_CAPP)

/**
  * @}
  */


/** @defgroup PCA_Interrupt_Flags PCA interrupt flags
  * @{
  */
#define PCA_FLAG_CC0              	(PCA_CR_CCF0)              			
#define PCA_FLAG_CC1           			(PCA_CR_CCF1)        	              
#define PCA_FLAG_CC2								(PCA_CR_CCF2)  
#define PCA_FLAG_CC3								(PCA_CR_CCF3)  
#define PCA_FLAG_CC4								(PCA_CR_CCF4)  
#define	PCA_FLAG_OVERFLOW						(PCA_CR_CF)

/**
  * @}
  */


/** @defgroup PCA_Interrupt_Enable PCA interrupt enable
  * @{
  */
#define PCA_IT_CC0 									(0x01)
#define PCA_IT_CC1 									(0x02)
#define PCA_IT_CC2 									(0x04)
#define PCA_IT_CC3									(0x08)
#define PCA_IT_CC4 									(0x10)
#define PCA_IT_OVERFLOW							(0x20)

/**
  * @}
  */


/** @defgroup PCA_Channel_Num PCA input capture channel number
  * @{
  */
#define PCA_CHANNEL_0 							(0x01)
#define PCA_CHANNEL_1 							(0x02)
#define PCA_CHANNEL_2 							(0x04)
#define PCA_CHANNEL_3								(0x08)
#define PCA_CHANNEL_4 							(0x10)

/**
  * @}
  */


/** @defgroup PCA_Output_Compare_Enable PCA output compare function enable/disable
  * @{
  */
#define PCA_OC_ENABLE              	(PCA_CCAPM0_ECOM)      								/*!< output compare function enable */
#define PCA_OC_DISABLE           		0x00000000U                      			/*!< output compare function disable */

/**
  * @}
  */


/** @defgroup PCA_TogEnable PCA tog function enable/disable
  * @{
  */
#define PCA_TOG_ENABLE              	(PCA_CCAPM0_MAT | PCA_CCAPM0_TOG)   /*!< Tog function enable */
#define PCA_TOG_DISABLE           		0x00000000U                      		/*!< Tog function disable */
/**
  * @}
  */


/** @defgroup PCA_PwmEnable PCA pwm function enable/disable
  * @{
  */
#define PCA_PWM_ENABLE              	(PCA_CCAPM0_PWM)              			/*!< Pwm function enable */
#define PCA_PWM_DISABLE           		0x00000000U                      		/*!< Pwm function disable */
/**
  * @}
  */


/**
  * @}
  */ /* End of group PCA_Exported_Constants */



/* Exported functions --------------------------------------------------------*/
/** @addtogroup PCA_Exported_Functions
  * @{
  */

/** @addtogroup PCA_Exported_Functions_Group
 * @{
 */
/* PCA functions ********************************************************/
HAL_StatusTypeDef HAL_PCA_Base_Init(PCA_HandleTypeDef *hpca);
HAL_StatusTypeDef HAL_PCA_Base_DeInit(PCA_HandleTypeDef *hpca);
void HAL_PCA_Base_MspInit(PCA_HandleTypeDef *hpca);
void HAL_PCA_Base_MspDeInit(PCA_HandleTypeDef *hpca);
HAL_StatusTypeDef HAL_PCA_Start(PCA_HandleTypeDef *hpca);
HAL_StatusTypeDef HAL_PCA_Start_IT(PCA_HandleTypeDef *hpca, uint32_t intid);	
HAL_StatusTypeDef HAL_PCA_Stop(PCA_HandleTypeDef *hpca);
HAL_StatusTypeDef HAL_PCA_Stop_IT(PCA_HandleTypeDef *hpca, uint32_t intid);
void HAL_PCA_IRQHandler(PCA_HandleTypeDef *hpca);
void HAL_PCA_InputCaptureCallback(PCA_HandleTypeDef *hpca);
void HAL_PCA_OverflowCallback(PCA_HandleTypeDef *hpca);
HAL_StatusTypeDef HAL_PCA_IC_ConfigChannel(PCA_HandleTypeDef *hpca, PCA_IC_InitTypeDef* sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_PCA_IC_Init(PCA_HandleTypeDef *hpca);
HAL_StatusTypeDef HAL_PCA_IC_DeInit(PCA_HandleTypeDef *hpca);
void HAL_PCA_IC_MspInit(PCA_HandleTypeDef *hpca);
void HAL_PCA_IC_MspDeInit(PCA_HandleTypeDef *hpca);
HAL_StatusTypeDef HAL_PCA_OC_ConfigChannel(PCA_HandleTypeDef *hpca, PCA_OC_InitTypeDef* sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_PCA_OC_Init(PCA_HandleTypeDef *hpca);
HAL_StatusTypeDef HAL_PCA_OC_DeInit(PCA_HandleTypeDef *hpca);
void HAL_PCA_OC_MspInit(PCA_HandleTypeDef *hpca);
void HAL_PCA_OC_MspDeInit(PCA_HandleTypeDef *hpca);

/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_PCA_OC_Start(PCA_HandleTypeDef *hpca, uint32_t Channel);
HAL_StatusTypeDef HAL_PCA_OC_Stop(PCA_HandleTypeDef *hpca, uint32_t Channel);

/* interrupt */
HAL_StatusTypeDef HAL_PCA_OC_Start_IT(PCA_HandleTypeDef *hpca, uint32_t Channel);
HAL_StatusTypeDef HAL_PCA_OC_Stop_IT(PCA_HandleTypeDef *hpca, uint32_t Channel);
void HAL_PCA_OutputCompareCallback(PCA_HandleTypeDef *hpca);

/**
  * @}
  */ /* End of group PCA_Exported_Functions_Group */

/**
  * @}
  */ /* End of group PCA_Exported_Functions */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup PCA_Exported_Macros PCA Exported Macros
  * @{
  */

/** @brief  Reset PCA handle state
  * @param  __HANDLE__: PCA handle.
  * @retval None
  */
#define __HAL_PCA_RESET_HANDLE_STATE(__HANDLE__) 			((__HANDLE__)->State = HAL_PCA_STATE_RESET)


/**
  * @brief  Enable the PCA.
  * @param  __HANDLE__: PCA handle
  * @retval None
 */
#define __HAL_PCA_ENABLE(__HANDLE__)           ((__HANDLE__)->Instance->CR |= (PCA_CR_CR))


/**
  * @brief  Disable the PCA.
  * @param  __HANDLE__: PCA handle
  * @retval None
 */
#define __HAL_PCA_DISABLE(__HANDLE__)           ((__HANDLE__)->Instance->CR &= ~(PCA_CR_CR))


/**
  * @brief  Enables the specified PCA interrupt.
  * @param  __HANDLE__: specifies the PCA Handle.
  * @param  __INTERRUPT__: specifies the PCA interrupt source to enable @ref PCA_Interrupt_Enable.
  *          This parameter can be one of the following values:
  *            @arg PCA_IT_CC0: Capture/Compare 0 interrupt	
  *            @arg PCA_IT_CC1: Capture/Compare 1 interrupt
  *            @arg PCA_IT_CC2: Capture/Compare 2 interrupt
  *            @arg PCA_IT_CC3: Capture/Compare 3 interrupt
  *            @arg PCA_IT_CC4: Capture/Compare 4 interrupt	
  *            @arg PCA_IT_OVERFLOW: Overflow interrupt
  * @retval None
  */
#define __HAL_PCA_ENABLE_IT(__HANDLE__,  __INTERRUPT__)    					\
                        do { \
                          if (((__INTERRUPT__) & PCA_IT_CC0) == PCA_IT_CC0) \
                          { \
															(__HANDLE__)->Instance->CCAPM0 |= (PCA_CCAPM0_CCIE);\
                          } \
                          if (((__INTERRUPT__) & PCA_IT_CC1) == PCA_IT_CC1) \
                          { \
															(__HANDLE__)->Instance->CCAPM1 |= (PCA_CCAPM1_CCIE);\
                          } \
                          if (((__INTERRUPT__) & PCA_IT_CC2) == PCA_IT_CC2) \
                          { \
															(__HANDLE__)->Instance->CCAPM2 |= (PCA_CCAPM2_CCIE);\
                          } \
                          if (((__INTERRUPT__) & PCA_IT_CC3) == PCA_IT_CC3) \
                          { \
															(__HANDLE__)->Instance->CCAPM3 |= (PCA_CCAPM3_CCIE);\
                          } \
                          if (((__INTERRUPT__) & PCA_IT_CC4) == PCA_IT_CC4) \
                          { \
															(__HANDLE__)->Instance->CCAPM4 |= (PCA_CCAPM4_CCIE);\
                          } \
                          if (((__INTERRUPT__) & PCA_IT_OVERFLOW) == PCA_IT_OVERFLOW) \
                          { \
															(__HANDLE__)->Instance->MOD |= (PCA_MOD_CFIE);\
                          } \
                        } while(0U)



/**
  * @brief  Disable the specified PCA interrupt.
  * @param  __HANDLE__: specifies the PCA Handle.
  * @param  __INTERRUPT__: specifies the PCA interrupt source to disable @ref PCA_Interrupt_Enable.
  *          This parameter can be one of the following values:
  *            @arg PCA_IT_CC0: Capture/Compare 0 interrupt	
  *            @arg PCA_IT_CC1: Capture/Compare 1 interrupt
  *            @arg PCA_IT_CC2: Capture/Compare 2 interrupt
  *            @arg PCA_IT_CC3: Capture/Compare 3 interrupt
  *            @arg PCA_IT_CC4: Capture/Compare 4 interrupt	
  *            @arg PCA_IT_OVERFLOW: Overflow interrupt
  * @retval None
  */
#define __HAL_PCA_DISABLE_IT(__HANDLE__,  __INTERRUPT__)    					\
                        do { \
                          if (((__INTERRUPT__) & PCA_IT_CC0) == PCA_IT_CC0) \
                          { \
															(__HANDLE__)->Instance->CCAPM0 &= (~PCA_CCAPM0_CCIE);\
                          } \
                          if (((__INTERRUPT__) & PCA_IT_CC1) == PCA_IT_CC1) \
                          { \
															(__HANDLE__)->Instance->CCAPM1 &= (~PCA_CCAPM1_CCIE);\
                          } \
                          if (((__INTERRUPT__) & PCA_IT_CC2) == PCA_IT_CC2) \
                          { \
															(__HANDLE__)->Instance->CCAPM2 &= (~PCA_CCAPM2_CCIE);\
                          } \
                          if (((__INTERRUPT__) & PCA_IT_CC3) == PCA_IT_CC3) \
                          { \
															(__HANDLE__)->Instance->CCAPM3 &= (~PCA_CCAPM3_CCIE);\
                          } \
                          if (((__INTERRUPT__) & PCA_IT_CC4) == PCA_IT_CC4) \
                          { \
															(__HANDLE__)->Instance->CCAPM4 &= (~PCA_CCAPM4_CCIE);\
                          } \
                          if (((__INTERRUPT__) & PCA_IT_OVERFLOW) == PCA_IT_OVERFLOW) \
                          { \
															(__HANDLE__)->Instance->MOD &= (~PCA_MOD_CFIE);\
                          } \
                        } while(0U)


/**
  * @brief  Checks whether the specified PCA interrupt is enabled or not.
  * @param  __HANDLE__: PCA handle
  * @param  __INTERRUPT__: specifies the PCA interrupt source to check @ref PCA_Interrupt_Enable.
  *          This parameter can be one of the following values:
  *            @arg PCA_IT_CC0: Capture/Compare 0 interrupt	
  *            @arg PCA_IT_CC1: Capture/Compare 1 interrupt
  *            @arg PCA_IT_CC2: Capture/Compare 2 interrupt
  *            @arg PCA_IT_CC3: Capture/Compare 3 interrupt
  *            @arg PCA_IT_CC4: Capture/Compare 4 interrupt	
  *            @arg PCA_IT_OVERFLOW: Overflow interrupt
  * @retval The state of PCA_IT (SET or RESET).
  */
#define __HAL_PCA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)          \
																								(((__INTERRUPT__) == PCA_IT_CC0) ? (((__HANDLE__)->Instance->CCAPM0 & PCA_CCAPM0_CCIE) == PCA_CCAPM0_CCIE) :\
																									((__INTERRUPT__) == PCA_IT_CC1) ? (((__HANDLE__)->Instance->CCAPM1 & PCA_CCAPM1_CCIE) == PCA_CCAPM1_CCIE) :\
																									((__INTERRUPT__) == PCA_IT_CC2) ? (((__HANDLE__)->Instance->CCAPM2 & PCA_CCAPM2_CCIE) == PCA_CCAPM2_CCIE) :\
																									((__INTERRUPT__) == PCA_IT_CC3) ? (((__HANDLE__)->Instance->CCAPM3 & PCA_CCAPM3_CCIE) == PCA_CCAPM3_CCIE):\
																									((__INTERRUPT__) == PCA_IT_CC4) ? (((__HANDLE__)->Instance->CCAPM4 & PCA_CCAPM4_CCIE) == PCA_CCAPM4_CCIE):\
																									(((__HANDLE__)->Instance->MOD & PCA_MOD_CFIE) == PCA_MOD_CFIE))


/**
  * @brief  Checks whether the specified PCA interrupt flag is set or not.
  * @param  __HANDLE__: specifies the PCA Handle.
  * @param  __FLAG__: specifies the PCA interrupt flag to check @ref PCA_Interrupt_Flags.
  *        This parameter can be one of the following values:
  *            @arg PCA_FLAG_CC0: Capture/Compare 0 interrupt flag	
  *            @arg PCA_FLAG_CC1: Capture/Compare 1 interrupt flag
  *            @arg PCA_FLAG_CC2: Capture/Compare 2 interrupt flag
  *            @arg PCA_FLAG_CC3: Capture/Compare 3 interrupt flag
  *            @arg PCA_FLAG_CC4: Capture/Compare 4 interrupt flag	
  *            @arg PCA_FLAG_OVERFLOW: Update interrupt flag	
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_PCA_GET_FLAG(__HANDLE__, __FLAG__)          			(((__HANDLE__)->Instance->CR & (__FLAG__)) == (__FLAG__))


/**
  * @brief Clear the PCA interrupt pending bits
  * @param  __HANDLE__: PCA handle
  * @param  __FLAG__: specifies the PCA interrupt flag @ref PCA_Interrupt_Flags.	
  *            @arg PCA_FLAG_CC0: Capture/Compare 0 interrupt flag	
  *            @arg PCA_FLAG_CC1: Capture/Compare 1 interrupt flag
  *            @arg PCA_FLAG_CC2: Capture/Compare 2 interrupt flag
  *            @arg PCA_FLAG_CC3: Capture/Compare 3 interrupt flag
  *            @arg PCA_FLAG_CC4: Capture/Compare 4 interrupt flag	
  *            @arg PCA_FLAG_OVERFLOW: Update interrupt flag		
  * @retval None
  */
#define __HAL_PCA_CLEAR_IT(__HANDLE__, __FLAG__)        				((__HANDLE__)->Instance->INTCLR |= (__FLAG__))



/**
  * @brief  Gets the PCA Capture Compare Register value on runtime
  * @param  __HANDLE__: PCA handle.
  * @param  __CHANNEL__ : PCA Channel associated with the capture compare register
  *          This parameter can be one of the following values:
  *            @arg PCA_CHANNEL_0: Capture/Compare channel0	
  *            @arg PCA_CHANNEL_1: Capture/Compare channel1
  *            @arg PCA_CHANNEL_2: Capture/Compare channel2
  *            @arg PCA_CHANNEL_3: Capture/Compare channel3
  *            @arg PCA_CHANNEL_4: Capture/Compare channel4
  * @retval 16-bit value of the capture/compare register (PCA_CCAPx)
  */
#define __HAL_PCA_GET_COMPARE(__HANDLE__, __CHANNEL__) \
																							 (((__CHANNEL__) == PCA_CHANNEL_0) ? ((__HANDLE__)->Instance->CCAP0) :\
																								((__CHANNEL__) == PCA_CHANNEL_1) ? ((__HANDLE__)->Instance->CCAP1) :\
																								((__CHANNEL__) == PCA_CHANNEL_2) ? ((__HANDLE__)->Instance->CCAP2) :\
																								((__CHANNEL__) == PCA_CHANNEL_3) ? ((__HANDLE__)->Instance->CCAP3) :\
																								((__CHANNEL__) == PCA_CHANNEL_4) ? ((__HANDLE__)->Instance->CCAP4) :\
																								(0xFFFF))





/**
  * @brief  Gets the PCA Counter Register value on runtime.
  * @param  __HANDLE__: PCA handle.
  * @retval 16-bit value of the timer counter register (PCA_CNT)
  */
#define __HAL_PCA_GET_COUNTER(__HANDLE__) 											((__HANDLE__)->Instance->CNT)


/**
  * @brief  Enables the specified PCA channel toggle output.
  * @param  __HANDLE__: specifies the PCA Handle.
  * @param  __CHANNEL__: specifies the PCA toggle output channel @ref PCA_Channel_Num.
  *          This parameter can be one of the following values:
  *            @arg PCA_CHANNEL_0: Capture/Compare channel0	
  *            @arg PCA_CHANNEL_1: Capture/Compare channel1
  *            @arg PCA_CHANNEL_2: Capture/Compare channel2
  *            @arg PCA_CHANNEL_3: Capture/Compare channel3
  *            @arg PCA_CHANNEL_4: Capture/Compare channel4
  * @retval None
  */
	#define __HAL_PCA_ENABLE_TOG(__HANDLE__,  __CHANNEL__)    					\
																								(((__CHANNEL__) == PCA_CHANNEL_0) ? ((__HANDLE__)->Instance->CCAPM0 |= (PCA_CCAPM0_TOG)) :\
																								((__CHANNEL__) == PCA_CHANNEL_1) ? ((__HANDLE__)->Instance->CCAPM1 |= (PCA_CCAPM1_TOG)) :\
																								((__CHANNEL__) == PCA_CHANNEL_2) ? ((__HANDLE__)->Instance->CCAPM2 |= (PCA_CCAPM2_TOG)) :\
																								((__CHANNEL__) == PCA_CHANNEL_3) ? ((__HANDLE__)->Instance->CCAPM3 |= (PCA_CCAPM3_TOG)) :\
																								((__CHANNEL__) == PCA_CHANNEL_4) ? ((__HANDLE__)->Instance->CCAPM4 |= (PCA_CCAPM4_TOG)) :\
																								((__HANDLE__)->Instance->CCAPM4 = ((__HANDLE__)->Instance->CCAPM4)))


/**
  * @brief  Disable the specified PCA channel toggle output.
  * @param  __HANDLE__: specifies the PCA Handle.
  * @param  __CHANNEL__: specifies the PCA toggle output channel.
  *          This parameter can be one of the following values:
  *            @arg PCA_CHANNEL_0: Capture/Compare channel0	
  *            @arg PCA_CHANNEL_1: Capture/Compare channel1
  *            @arg PCA_CHANNEL_2: Capture/Compare channel2
  *            @arg PCA_CHANNEL_3: Capture/Compare channel3
  *            @arg PCA_CHANNEL_4: Capture/Compare channel4
  * @retval None
  */
	#define __HAL_PCA_DISABLE_TOG(__HANDLE__,  __CHANNEL__)    					\
																								(((__CHANNEL__) == PCA_CHANNEL_0) ? ((__HANDLE__)->Instance->CCAPM0 &= (~PCA_CCAPM0_TOG)) :\
																								((__CHANNEL__) == PCA_CHANNEL_1) ? ((__HANDLE__)->Instance->CCAPM1 &= (~PCA_CCAPM1_TOG)) :\
																								((__CHANNEL__) == PCA_CHANNEL_2) ? ((__HANDLE__)->Instance->CCAPM2 &= (~PCA_CCAPM2_TOG)) :\
																								((__CHANNEL__) == PCA_CHANNEL_3) ? ((__HANDLE__)->Instance->CCAPM3 &= (~PCA_CCAPM3_TOG)) :\
																								((__CHANNEL__) == PCA_CHANNEL_4) ? ((__HANDLE__)->Instance->CCAPM4 &= (~PCA_CCAPM4_TOG)) :\
																								((__HANDLE__)->Instance->CCAPM4 = ((__HANDLE__)->Instance->CCAPM4)))

/**
  * @}
  */ /* End of group PCA_Exported_Macros */


/* Private Macros -----------------------------------------------------------*/
/** @defgroup PCA_Private_Macros PCA Private Macros
 * @{
 */ 
#define IS_PCA_INSTANCE(INSTANCE)			((INSTANCE) == PCA)   

/**
  * @}
  */ /* End of group PCA_Private_Macros */


/* Private Functions --------------------------------------------------------*/
/** @addtogroup PCA_Private_Functions
 * @{
 */


/**
  * @}
  */ /* End of group PCA_Private_Functions */




/**
  * @}
  */ /* End of group PCA */


#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_PCA_H */
