/**
  ******************************************************************************
  * @file    cx32l003_hal_crc.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of CRC HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_CRC_H
#define __CX32L003_HAL_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup CRC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** @defgroup CRC_Exported_Types CRC Exported Types
  * @{
  */

/** 
  * @brief  CRC HAL State Structure definition  
  */ 
typedef enum
{
  HAL_CRC_STATE_RESET     = 0x00U,  /*!< CRC not yet initialized or disabled */
  HAL_CRC_STATE_READY     = 0x01U,  /*!< CRC initialized and ready for use   */
  HAL_CRC_STATE_BUSY      = 0x02U,  /*!< CRC internal process is ongoing     */
  HAL_CRC_STATE_TIMEOUT   = 0x03U,  /*!< CRC timeout state                   */
  HAL_CRC_STATE_ERROR     = 0x04U   /*!< CRC error state                     */

}HAL_CRC_StateTypeDef;

/** 
  * @brief  CRC handle Structure definition
  */ 
typedef struct
{
  CRC_TypeDef                 *Instance;  /*!< Register base address   */
																					
  void*												pvCrcData;	/*!< pvCrcData initialization refer to CRC_DATA_ADDRESS */
	
	HAL_LockTypeDef             Lock;       /*!< CRC locking object      */

  __IO HAL_CRC_StateTypeDef   State;      /*!< CRC communication state */

}CRC_HandleTypeDef;

/**
  * @}
  */ 

/* Exported constants --------------------------------------------------------*/
#define CRC_DATA_ADDRESS	(CRC_BASE+0x80)

/* Exported macro ------------------------------------------------------------*/

/** @defgroup CRC_Exported_Macros CRC Exported Macros
  * @{
  */

/** @brief Reset CRC handle state
  * @param  __HANDLE__: CRC handle
  * @retval None
  */
#define __HAL_CRC_RESET_HANDLE_STATE(__HANDLE__)  ((__HANDLE__)->State = HAL_CRC_STATE_RESET)

/**
  * @brief  Initialize CRC caculation.
  * @param  __HANDLE__: CRC handle
  * @retval None
  */
#define __HAL_CRC_INITIAL(__HANDLE__)             (WRITE_REG((__HANDLE__)->Instance->RESULT, CRC_RESULT_RESULT))

/**
  * @brief Stores a 8-bit data in the Independent Data register.
  * @param __HANDLE__: CRC handle
  * @param __VALUE__: 8-bit value to be stored in the Data register
  * @retval None
  */
#define __HAL_CRC_SET_DATA(__HANDLE__, __VALUE__) 	(WRITE_REG(*(uint8_t*)((__HANDLE__)->Instance->DATA), (__VALUE__)))

/**
  * @brief Returns the 8-bit data stored in the Independent Data register.
  * @param __HANDLE__: CRC handle
  * @retval 8-bit value of the DATA register 
  */
#define __HAL_CRC_GET_DATA(__HANDLE__) ((*(uint8_t*)((__HANDLE__)->Instance->DATA)) & 0xFF)

/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/

/** @addtogroup CRC_Exported_Functions
  * @{
  */ 

/** @addtogroup CRC_Exported_Functions_Group1
  * @{
  */ 

/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef     HAL_CRC_Init(CRC_HandleTypeDef *hcrc);
HAL_StatusTypeDef     HAL_CRC_DeInit (CRC_HandleTypeDef *hcrc);
void                  HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc);
void                  HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc);

/**
  * @}
  */ 

/** @addtogroup CRC_Exported_Functions_Group2
  * @{
  */ 

/* Peripheral Control functions  ************************************************/
uint32_t              HAL_CRC_Accumulate(CRC_HandleTypeDef *hcrc, uint8_t pBuffer[], uint32_t BufferLength);
uint32_t              HAL_CRC_Calculate(CRC_HandleTypeDef *hcrc, uint8_t pBuffer[], uint32_t BufferLength);
ErrorStatus 					HAL_Get_CRC_RESULT_FLAG(CRC_HandleTypeDef *hcrc);
  
/**
  * @}
  */ 

/** @addtogroup CRC_Exported_Functions_Group3
  ** @{
  */ 

/* Peripheral State functions  **************************************************/
HAL_CRC_StateTypeDef  HAL_CRC_GetState(CRC_HandleTypeDef *hcrc);

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_CRC_H */

