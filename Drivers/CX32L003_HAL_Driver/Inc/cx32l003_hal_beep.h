/**
  ******************************************************************************
  * @file    cx32l003_hal_beep.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of BEEP HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_BEEP_H
#define __CX32L003_HAL_BEEP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup BEEP
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup BEEP_Exported_Types BEEP Exported Types
  * @{
  */
/**
  * @brief  BEEP base Configuration Structure definition
	* @note   This structure is for BEEP 	
  */
typedef struct
{	
  uint32_t ClkSel;     						/*!< Specifies beep clock.
																			 This parameter can be a value of @ref BEEP_ClkSel */		
  
	uint32_t OutFreqDiv;	  				/*!< Specifies beep clock output divider.
																			 This parameter can be a value between 0 to 0xFFF */	
	
  uint32_t OutFreqSel;     				/*!< Specifies beep clock frequency select.
																			 This parameter can be a value of @ref BEEP_OutFreqSel */		
	
} BEEP_InitTypeDef;


/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_BEEP_STATE_RESET             = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
  HAL_BEEP_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_BEEP_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  HAL_BEEP_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  HAL_BEEP_STATE_ERROR             = 0x04U     /*!< Reception process is ongoing                */
}HAL_BEEP_StateTypeDef;


/**
  * @brief  BEEP Base Time Base Handle Structure definition
  */
typedef struct
{
  BEEP_TypeDef             			*Instance;     /*!< Register base address             	*/
  BEEP_InitTypeDef    					Init;          /*!< BEEP Time Base required parameters */
  HAL_LockTypeDef             	Lock;          /*!< Locking object                    	*/
  __IO HAL_BEEP_StateTypeDef   	State;         /*!< BEEP operation state               */
}BEEP_HandleTypeDef;


/**
  * @}
  */ /* End of group BEEP_Exported_Types */


/* Exported constants --------------------------------------------------------*/
/** @defgroup BEEP_Exported_Constants BEEP Exported Constants
  * @{
  */

/** @defgroup BEEP_ClkSel BEEP clock select
  * @{
  */
#define BEEP_CLOCK_STOP									0x00000000U															/*!< Clock stop */
#define BEEP_CLOCK_LIRC              		BEEP_CSR_CLKSEL_0              					/*!< LIRC select */
#define BEEP_CLOCK_HXT           				BEEP_CSR_CLKSEL_1               				/*!< HXT select */
#define BEEP_CLOCK_PCLK									BEEP_CSR_CLKSEL_1 | BEEP_CSR_CLKSEL_0		/*!< PCLK select */

/**
  * @}
  */

/** @defgroup BEEP_OutFreqSel BEEP output clock frequency select
  * @{
  */
#define BEEP_OUTFREQSEL_DIV8           	(0x00000000U)               						/*!< Frequency output select div8 */
#define BEEP_OUTFREQSEL_DIV4            BEEP_CSR_BEEPSEL_0              				/*!< Frequency output select div4 */
#define BEEP_OUTFREQSEL_DIV2						BEEP_CSR_BEEPSEL_1											/*!< Frequency output select div2 */

/**
  * @}
  */	
	

/**
  * @}
  */ /* End of group BEEP_Exported_Constants */



/* Exported functions --------------------------------------------------------*/
/** @addtogroup BEEP_Exported_Functions
  * @{
  */

/** @addtogroup BEEP_Exported_Functions_Group
 * @{
 */
/* Time Base functions ********************************************************/
HAL_StatusTypeDef HAL_BEEP_Init(BEEP_HandleTypeDef *hbeep);
HAL_StatusTypeDef HAL_BEEP_DeInit(BEEP_HandleTypeDef *hbeep);
void HAL_BEEP_MspInit(BEEP_HandleTypeDef *hbeep);
void HAL_BEEP_MspDeInit(BEEP_HandleTypeDef *hbeep);
HAL_StatusTypeDef HAL_BEEP_Start(BEEP_HandleTypeDef *hbeep);
HAL_StatusTypeDef HAL_BEEP_Stop(BEEP_HandleTypeDef *hbeep);


/**
  * @}
  */ /* End of group BEEP_Exported_Functions_Group */

/**
  * @}
  */ /* End of group BEEP_Exported_Functions */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup BEEP_Exported_Macros BEEP Exported Macros
  * @{
  */

/** @brief  Reset BEEP handle state
  * @param  __HANDLE__: BEEP handle.
  * @retval None
  */
#define __HAL_BEEP_RESET_HANDLE_STATE(__HANDLE__) 			((__HANDLE__)->State = HAL_BEEP_STATE_RESET)


/** @brief  Enable BEEP function
  * @param  __HANDLE__: BEEP handle.
  * @retval None
  */
#define __HAL_BEEP_ENABLE(__HANDLE__) 									((__HANDLE__)->Instance->CSR |= BEEP_CSR_BEEPEN)


/** @brief  Disable BEEP function
  * @param  __HANDLE__: BEEP handle.
  * @retval None
  */
#define __HAL_BEEP_DISABLE(__HANDLE__) 									((__HANDLE__)->Instance->CSR &= ~BEEP_CSR_BEEPEN)


/** @brief  BEEP clock selection
  * @param  __HANDLE__: BEEP handle.
  * @param  __CLKSRC__: clock source, @ref BEEP_ClkSel
  * @retval None
  */
#define __HAL_BEEP_CLKSEL(__HANDLE__, __CLKSRC__) 			(MODIFY_REG(hbeep->Instance->CSR, BEEP_CSR_CLKSEL, __CLKSRC__))


/** @brief  BEEP clock divider
  * @param  __HANDLE__: BEEP handle.
  * @param  __CLKDIV__: clock source, This parameter can be a value between 0 to 0xFFF
  * @retval None
  */
#define __HAL_BEEP_SETDIV(__HANDLE__, __CLKDIV__) 			(MODIFY_REG(hbeep->Instance->CSR, BEEP_CSR_BEEPDIV, __DIV__))


/** @brief  BEEP output frequency select
  * @param  __HANDLE__: BEEP handle.
  * @param  __OUTDIV__: output freqency clock select, @ref BEEP_OutFreqSel
  * @retval None
  */
#define __HAL_BEEP_OUTDIV(__HANDLE__, __OUTDIV__) 			(MODIFY_REG(hbeep->Instance->CSR, BEEP_CSR_BEEPSEL, __OUTDIV__))


/**
  * @}
  */ /* End of group BEEP_Exported_Macros */


/* Private Macros -----------------------------------------------------------*/
/** @defgroup BEEP_Private_Macros BEEP Private Macros
 * @{
 */ 
#define IS_BEEP_INSTANCE(INSTANCE)			((INSTANCE) == BEEP)   

/**
  * @}
  */ /* End of group BEEP_Private_Macros */


/* Private Functions --------------------------------------------------------*/
/** @addtogroup BEEP_Private_Functions
 * @{
 */


/**
  * @}
  */ /* End of group BEEP_Private_Functions */




/**
  * @}
  */ /* End of group BEEP */


#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_BEEP_H */
