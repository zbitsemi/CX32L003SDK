/**
  ******************************************************************************
  * @file    cx32l003_hal.h 
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_H
#define __CX32L003_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

	
/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_conf.h"

/** @addtogroup HAL
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup HAL_Exported_Constants HAL Exported Constants
  * @{
  */
	
/**	
  * @brief DBG_KEY Debug module unlock key
  * @{
  */	
#define DBG_KEY_UNLOCK		 (0x5A69)
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup HAL_TICK_FREQ Tick Frequency
  * @{
  */
	
/**
  * @brief   SystemTick frequency setting
  * @{	
  */	
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;

/**
  * @}
  */

extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup HAL_Exported_Macros HAL Exported Macros
  * @{
  */

/** @defgroup DBGMCU_Freeze_Unfreeze Freeze Unfreeze Peripherals in Debug mode
  * @brief   Freeze/Unfreeze Peripherals in Debug mode
  * @{
  */

/* Peripherals on APB */
/**
  * @brief  TIM2 Peripherals Debug mode freeze enable
  * @{	
  */
#define __HAL_DBGMCU_FREEZE_TIM2()            SET_BIT(DBG->APBFZ, (DBGMCU_CR_DBG_TIM2_STOP | (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos)))
/**
  * @}
  */
	
/**
  * @brief  TIM2 Peripherals Debug mode freeze disable
  * @{	
  */
#define __HAL_DBGMCU_UNFREEZE_TIM2()          CLEAR_WPBIT(DBG->APBFZ, DBGMCU_CR_DBG_TIM2_STOP, (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos))
/**
  * @}
  */


/**
  * @brief  WWDG Peripherals Debug mode freeze enable
  * @{	
  */
#define __HAL_DBGMCU_FREEZE_WWDG()            SET_BIT(DBG->APBFZ, (DBGMCU_CR_DBG_WWDG_STOP | (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos)))

/**
  * @}
  */
	
/**
  * @brief  WWDG Peripherals Debug mode freeze disable
  * @{	
  */	
#define __HAL_DBGMCU_UNFREEZE_WWDG()          CLEAR_WPBIT(DBG->APBFZ, DBGMCU_CR_DBG_WWDG_STOP, (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos))	
	
/**
  * @}
  */
		

/**
  * @brief  IWDG Peripherals Debug mode freeze enable
  * @{		
  */
#define __HAL_DBGMCU_FREEZE_IWDG()            SET_BIT(DBG->APBFZ, (DBGMCU_CR_DBG_IWDG_STOP | (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos)))

/**
  * @}
  */

/**
  * @brief  IWDG Peripherals Debug mode freeze disable
  * @{		
  */
#define __HAL_DBGMCU_UNFREEZE_IWDG()          CLEAR_WPBIT(DBG->APBFZ, (DBGMCU_CR_DBG_IWDG_STOP, (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos))

/**
  * @}
  */

/**
  * @brief  BEEP Peripherals Debug mode freeze enable
  * @{		
  */
#define __HAL_DBGMCU_FREEZE_BEEP()            SET_BIT(DBG->APBFZ, (DBGMCU_CR_DBG_BEEP_STOP | (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos)))

/**
  * @}
  */

/**
  * @brief  BEEP Peripherals Debug mode freeze disable
  * @{		
  */
#define __HAL_DBGMCU_UNFREEZE_BEEP()          CLEAR_WPBIT(DBG->APBFZ, (DBGMCU_CR_DBG_BEEP_STOP, (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos))

/**
  * @}
  */

/**
  * @brief  RTC Peripherals Debug mode freeze enable
  * @{		
  */
#define __HAL_DBGMCU_FREEZE_RTC()            SET_BIT(DBG->APBFZ, (DBGMCU_CR_DBG_RTC_STOP | (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos)))

/**
  * @}
  */
	
/**
  * @brief  RTC Peripherals Debug mode freeze disable
  * @{		
  */	
#define __HAL_DBGMCU_UNFREEZE_RTC()          CLEAR_WPBIT(DBG->APBFZ, (DBGMCU_CR_DBG_RTC_STOP, (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos))	

/**
  * @}
  */
	
/**
  * @brief  TIM1 Peripherals Debug mode freeze enable
  * @{		
  */
#define __HAL_DBGMCU_FREEZE_TIM1()            SET_BIT(DBG->APBFZ, (DBGMCU_CR_DBG_TIM1_STOP | (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos)))

/**
  * @}
  */
	
/**
  * @brief  TIM1 Peripherals Debug mode freeze disable
  * @{		
  */	
#define __HAL_DBGMCU_UNFREEZE_TIM1()          CLEAR_WPBIT(DBG->APBFZ, (DBGMCU_CR_DBG_TIM1_STOP, (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos))
/**
  * @}
  */

/**
  * @brief  PCA Peripherals Debug mode freeze enable
  * @{		
  */
#define __HAL_DBGMCU_FREEZE_PCA()            SET_BIT(DBG->APBFZ, (DBGMCU_CR_DBG_PCA_STOP | (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos)))

/**
  * @}
  */

/**
  * @brief  PCA Peripherals Debug mode freeze disable
  * @{		
  */
#define __HAL_DBGMCU_UNFREEZE_PCA()          CLEAR_WPBIT(DBG->APBFZ, (DBGMCU_CR_DBG_PCA_STOP, (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos))
/**
  * @}
  */

/**
  * @brief  LPTIM Peripherals Debug mode freeze enable
  * @{		
  */
#define __HAL_DBGMCU_FREEZE_LPTIM()          SET_BIT(DBG->APBFZ, (DBGMCU_CR_DBG_LPTIM_STOP | (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos)))

/**
  * @}
  */
	
/**
  * @brief  LPTIM Peripherals Debug mode freeze disable
  * @{		
  */
#define __HAL_DBGMCU_UNFREEZE_LPTIM()        CLEAR_WPBIT(DBG->APBFZ, (DBGMCU_CR_DBG_LPTIM_STOP, (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos))
/**
  * @}
  */

/**
  * @brief  TIM11 Peripherals Debug mode freeze enable
  * @{		
  */
#define __HAL_DBGMCU_FREEZE_TIM11()          SET_BIT(DBG->APBFZ, (DBGMCU_CR_DBG_TIM11_STOP | (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos)))

/**
  * @}
  */
	
/**
  * @brief  TIM11 Peripherals Debug mode freeze disable
  * @{		
  */	
#define __HAL_DBGMCU_UNFREEZE_TIM11()        CLEAR_WPBIT(DBG->APBFZ, (DBGMCU_CR_DBG_TIM11_STOP, (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos))	
/**
  * @}
  */	
	
/**
  * @brief  TIM10 Peripherals Debug mode freeze enable
  * @{		
  */
#define __HAL_DBGMCU_FREEZE_TIM10()          SET_BIT(DBG->APBFZ, (DBGMCU_CR_DBG_TIM10_STOP | (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos)))

/**
  * @}
  */
	
/**
  * @brief  TIM10 Peripherals Debug mode freeze disable
  * @{		
  */	
#define __HAL_DBGMCU_UNFREEZE_TIM10()        CLEAR_WPBIT(DBG->APBFZ, (DBGMCU_CR_DBG_TIM10_STOP, (DBG_KEY_UNLOCK << DBG_APBFZ_KEY_Pos))
/**
  * @}
  */

/**
  * @}
  */


/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */
	
/**
  * @brief  Check systemtick frequency setting
  * @{		
  */		
#define IS_TICKFREQ(FREQ) (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                           ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                           ((FREQ) == HAL_TICK_FREQ_1KHZ))
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ /* End of group HAL_Exported_Macros */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HAL_Exported_Functions
  * @{
  */
/** @addtogroup HAL_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);
/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions  ************************************************/
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
void HAL_DBGMCU_EnableDBGSleepMode(void);
void HAL_DBGMCU_DisableDBGSleepMode(void);
void HAL_GetUID(uint32_t *UID);
/**
  * @}
  */

/**
  * @}
  */ /* End of group HAL_Exported_Functions */
	
	
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup HAL_Private_Variables HAL Private Variables
  * @{
  */
/**
  * @}
  */
/* Private constants ---------------------------------------------------------*/
/** @defgroup HAL_Private_Constants HAL Private Constants
  * @{
  */
/**
  * @}
  */
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @}
  */ /* End of group HAL */


#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_H */


