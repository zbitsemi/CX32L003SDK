/**
  ******************************************************************************
  * @file    cx32l003_hal_pwr.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of PWR HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_PWR_H
#define __CX32L003_HAL_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */

/* Exported types ------------------------------------------------------------*/



/* Internal constants --------------------------------------------------------*/


 
/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */ 
/** @defgroup PWR_SLEEP_mode_entry PWR SLEEP mode entry
  * @{
  */
#define PWR_SLEEPENTRY_WFI              ((uint8_t)0x01)
#define PWR_SLEEPENTRY_WFE              ((uint8_t)0x02)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/** @defgroup PWR_Private_Macros PWR Private Macros
  * @{
  */
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPENTRY_WFI) || ((ENTRY) == PWR_SLEEPENTRY_WFE))

/**
  * @}
  */



/* Exported functions --------------------------------------------------------*/

/** @addtogroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @addtogroup PWR_Exported_Functions_Group1 Peripheral Control functions 
  * @{
  */

/* Low Power modes configuration functions ************************************/
void HAL_PWR_EnterSLEEPMode(uint8_t SLEEPEntry);
void HAL_PWR_EnterDEEPSLEEPMode(void);

void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ /* End of group PWR */

/**
  * @}
  */ /* End of group CX32L003_HAL_Driver */

#ifdef __cplusplus
}
#endif


#endif /* __CX32L003_HAL_PWR_H */

