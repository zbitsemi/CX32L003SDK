/**
  ******************************************************************************
  * @file    cx32l003_hal_iwdg.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of IWDG HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_IWDG_H
#define __CX32L003_HAL_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @addtogroup IWDG
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup IWDG_Exported_Types IWDG Exported Types
  * @{
  */

/**
  * @brief  IWDG Init structure definition
  */
typedef enum
{
	IWDG_UNMASK_INT = 0X00U,
  IWDG_MASK_INT =   0X01U,
}IWDG_MaskINTTypeDef;

typedef enum
{
  IWDG_MODE_RESET = 0X00U,
  IWDG_MODE_INT =   0X01U,
}IWDG_ModeTypeDef;


/** 
  * @brief  IWDG Initial Configuration Structure definition  
  */
typedef struct
{
  uint32_t Reload;         					/*!< Specifies the IWDG down-counter reload value.
																					This parameter must be a number between Min_Data = 0 and Max_Data = 0xFFFFF */
  IWDG_MaskINTTypeDef MaskINT;    	/*!< Mask interrupt request or not */ 
																		       
  IWDG_ModeTypeDef Mode;       			/*!< reset or interrupt when IWDG counter to 0x00*/

}IWDG_InitTypeDef;

/** 
  * @brief  IWDG Handle Structure definition  
  */
typedef struct
{
  IWDG_TypeDef                 *Instance;  /*!< Register base address    */

  IWDG_InitTypeDef             Init;       /*!< IWDG required parameters */

}IWDG_HandleTypeDef;
/**
  * @}
  */
   
/* Exported constants --------------------------------------------------------*/
/** @defgroup IWDG_Exported_Constants IWDG Exported Constants
  * @{
  */

/**
  * @brief  IWDG Key Register value
  */
#define IWDG_UNLOCK_KEY                 ((uint32_t)0X55AA6699)   /*IWDG REG Write Access UNLOCK   */
#define IWDG_LOCK_KEY                   ((uint32_t)0X55AA6698)   /*IWDG REG Write Access LOCK   */
#define IWDG_START_ENABLE               ((uint32_t)0x00000055)  /*IWDG Enable   */
#define IWDG_RELOAD_REFRESH             ((uint32_t)0x000000AA)  /*IWDG Peripheral Enable       */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup IWDG_Exported_Macros IWDG Exported Macros
  * @{
  */
#define IWDG_RLR_MAX                    IWDG_RLOAD_IWDGRLOAD    /*!< Watchdog counter reload max value */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup IWDG_Exported_Functions  IWDG Exported Functions
  * @{
  */

/** @defgroup IWDG_Exported_Functions_Group1 Initialization and Start functions
  * @{
  */
/* Initialization/Start functions  ********************************************/
HAL_StatusTypeDef HAL_IWDG_Init(IWDG_HandleTypeDef *hiwdg);
HAL_StatusTypeDef HAL_IWDG_STOP(IWDG_HandleTypeDef *hiwdg);
HAL_StatusTypeDef HAL_IWDG_RUN(IWDG_HandleTypeDef *hiwdg);
/**
  * @}
  */

/** @defgroup IWDG_Exported_Functions_Group2 IO operation functions
  * @{
  */
/* I/O operation functions ****************************************************/
HAL_StatusTypeDef HAL_IWDG_Refresh(IWDG_HandleTypeDef *hiwdg);
HAL_StatusTypeDef HAL_IWDG_Get_Counter(IWDG_HandleTypeDef *hiwdg, uint32_t *counter);
FlagStatus HAL_IWDG_Get_INT_Flag(void);
void HAL_IWDG_Clear_INT_Flag(void);
/**
  * @}
  */

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup IWDG_Private_Macros IWDG Private Macros
  * @{
  */

/**
  * @brief  Enable write access to IWDG_CFCG, IWDG_RLOAD and IWDG_INTCLR registers.
  * @param  None
  * @retval None
  */
#define IWDG_ENABLE_WRITE_ACCESS()          WRITE_REG(IWDG->UNLOCK, IWDG_UNLOCK_KEY)

/**
  * @brief  Disable write access to IWDG_CFCG, IWDG_RLOAD and IWDG_INTCLR registers.
  * @param  None
  * @retval None
  */
#define IWDG_DISABLE_WRITE_ACCESS()          WRITE_REG(IWDG->UNLOCK, IWDG_LOCK_KEY)

/**
  * @brief  Check IWDG reload value.
  * @param  __RELOAD__  IWDG reload value
  * @retval None
  */
#define IS_IWDG_RELOAD(__RELOAD__)            ((__RELOAD__) <= IWDG_RLR_MAX)
/**
  * @brief  Check IWDG INT Mask.
  * @param  __MASKINT__  IWDG INT Mask or not
  * @retval None
  */
#define IS_IWDG_MASKINT(__MASKINT__)          ((__MASKINT__== IWDG_UNMASK_INT) ||(__MASKINT__== IWDG_MASK_INT))                             
/**
  * @brief  Check IWDG Overflow MODE.
  * @param  __MODE__  IWDG Overflow Mode
  * @retval None
  */
#define IS_IWDG_MODE(__MODE__)                ((__MODE__ == IWDG_MODE_RESET) || (__MODE__ == IWDG_MODE_INT))
/**
  * @}
  */
/* Private functions ------------------------------------------------------------*/
/** @defgroup IWDG_Private_Functions IWDG Private Function
  * @{
  */
/**
  * @brief  Enables IWDG (write access to IWDG_CMDCR registers).
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval None
  */
__STATIC_INLINE void HAL_IWDG_Enable(IWDG_HandleTypeDef  *hiwdg)
{
  WRITE_REG(hiwdg->Instance->CMDCR, IWDG_START_ENABLE);
}

/**
  * @brief  Sets IWDG Reload value.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval None
  */
__STATIC_INLINE void HAL_IWDG_SetReload(IWDG_HandleTypeDef  *hiwdg)
{
  /* Check the parameters */
    IWDG_ENABLE_WRITE_ACCESS(); 
    hiwdg->Instance->RLOAD = hiwdg->Init.Reload;
    IWDG_DISABLE_WRITE_ACCESS(); 
}

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

#endif /* __CX32L003_HAL_IWDG_H */


