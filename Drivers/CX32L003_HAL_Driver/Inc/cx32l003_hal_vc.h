/**
  ******************************************************************************
  * @file    cx32l003_hal_vc.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of VC HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_VC_H
#define __CX32L003_HAL_VC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @addtogroup VC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup VC_Exported_Types VC Exported Types
  * @{
  */


/**
  * @brief  VC divided structure definition
  */

typedef enum
{
    HAL_VC_1P4_V25DIV = 0X00U,          /*!< Specifies the VC 1/4V25D */
    HAL_VC_2P4_V25DIV,									/*!< Specifies the VC 2/4 V25D  */
    HAL_VC_3P4_V25DIV,									/*!< Specifies the VC 3/4V25D  */
    HAL_VC_4P4_V25DIV										/*!< Specifies the VC V25D not divided */
}VC_V25DIVTypeDef;

/**
  * @brief  VC input select structure definition
  */

typedef enum
{
    HAL_VC_INPUT_0 = 0X00U,
    HAL_VC_INPUT_1,
    HAL_VC_INPUT_2,
    HAL_VC_INPUT_V25DIV,
}VC_InPutTypeDef;

/**
  * @brief  VC Init structure definition
  */

typedef struct
{
    VC_V25DIVTypeDef V25div;     /*!< Specifies the VC V25DIV divider,@ref VC_V25DIVTypeDef */
    VC_InPutTypeDef NinSel;      /*!< Negative input select,@ref VC_InPutTypeDef*/
    VC_InPutTypeDef PinSel;      /*!< Positive input select,@ref VC_InPutTypeDef */
    uint32_t INT_Enable;         /*!< Interrupt Enable or Disable,@ref VC_ENABLE_Definitions*/
    uint32_t INT_Mode;           /*!< Interrupt triger mode,@ref VC_ENABLE_Definitions*/
    uint32_t Filter_Enable;      /*!< Filter counter Enable or Disable,@ref VC_ENABLE_Definitions*/
    uint32_t Filter_Clk;         /*!< Filter clk select @ref VC_FILTER_CLK_SELECT*/
    uint32_t Fliter_Num;         /*!< Filter counter number.Min_Data >= 0x00 and Max_Data = 0xFFFF*/
}VC_InitTypeDef;

/** 
  * @brief  VC Handle Structure definition  
  */
typedef struct
{
  VC_TypeDef                 *Instance;  /*!< Register base address    */

  VC_InitTypeDef             Init;       /*!< VC required parameters */

}VC_HandleTypeDef;
/**
  * @}
  */
   
/* Exported constants --------------------------------------------------------*/
/** @defgroup VC_Exported_Constants VC Exported Constants
  * @{
  */

/**
  * @brief  VC_ENABLE_Definitions  enable and disable 
  */

#define HAL_VC_VC25DIV_ENABLE             VC_CR0_V25DIV_EN      /*VC VC25 DIVIDED ENABLE   */
#define HAL_VC_VC25DIV_DISABLE            (0X0U)             /*VC VC25 DIVIDED DISABLE   */

#define HAL_VC_INT_ENABLE                 VC_CR1_INT_EN      /*VC INTERRUPT ENABLE   */
#define HAL_VC_INT_DISABLE                (0X0U)             /*VC INTERRUPT DISABLE   */

#define HAL_VC_HIGH_INT_ENABLE            VC_CR1_HIGHINTEN   /*VC INTERRUPT HIGHT LEVEL TRIGER ENABLE   */
#define HAL_VC_HIGH_INT_DISABLE           (0X0U)             /*VC INTERRUPT HIGHT LEVEL TRIGER DISABLE   */
#define HAL_VC_RISE_INT_ENABLE            VC_CR1_RISEINTEN   /*VC INTERRUPT RISE TRIGER ENABLE  */
#define HAL_VC_RISE_INT_DISABLE           (0X0U)             /*VC INTERRUPT RISE TRIGER DISABLE  */
#define HAL_VC_FALL_INT_ENABLE            VC_CR1_FALLINTEN   /*VC INTERRUPT FALL TRIGER ENABLE */
#define HAL_VC_FALL_INT_DISABLE           (0X0U)            /*VC INTERRUPT FALL TRIGER DISABLE */

#define HAL_VC_FILTER_ENABLE              VC_CR1_FLTEN       /*VC FILTER ENABLE */
#define HAL_VC_FILTER_DISABLE             (0X0U)            /*VC FILTER DISABLE */

#define HAL_VC_ENABLE                     VC_CR1_VCEN       /*VC ENABLE */
#define HAL_VC_DISABLE                    (0X0U)            /*VC DISABLE */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup VC_FILTER_CLK_SELECT  VC Filter clock select
  * @{
  */
#define HAL_VC_FILTER_CLK_NONE                    (0X00U)                              /*!< VC Filter clock select NONE */
#define HAL_VC_FILTER_CLK_PCLK                    (0X01U<<VC_CR1_VC_FLTCLK_SEL_Pos)    /*!< VC Filter clock select PCLK */
#define HAL_VC_FILTER_CLK_LIRC                    (0X02U<<VC_CR1_VC_FLTCLK_SEL_Pos)    /*!< VC Filter clock select LIRC */

#define HAL_VC_OUTCFG_Msk                         (0X7FFFFU)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup VC_Exported_Functions  VC Exported Functions
  * @{
  */

/** @defgroup VC_Exported_Functions_Group1 Initialization and DeInitialization functions
  * @{
  */
/* Initialization/Start functions  ********************************************/
HAL_StatusTypeDef HAL_VC_Init(VC_HandleTypeDef *hvc);

/* DeInitialization functions  ********************************************/
HAL_StatusTypeDef HAL_VC_DeInit(VC_HandleTypeDef *hvc);
/**
  * @}
  */

/** @defgroup VC_Exported_Functions_Group2 IO operation functions
  * @{
  */
/* I/O operation functions ****************************************************/
HAL_StatusTypeDef HAL_VC_OutPut_Config_Enable(VC_HandleTypeDef *hvc, uint32_t config);
HAL_StatusTypeDef HAL_VC_OutPut_Config_Disable(VC_HandleTypeDef *hvc, uint32_t config);
FlagStatus HAL_VC_Get_INT_Flag(VC_HandleTypeDef *hvc);
FlagStatus HAL_VC_Get_OutPut_State(VC_HandleTypeDef *hvc);
void HAL_VC_Clear_INT_Flag(VC_HandleTypeDef *hvc);
void HAL_VC_Enable(VC_HandleTypeDef  *hvc);
void HAL_VC_Disable(VC_HandleTypeDef *hvc);

/**
  * @}
  */

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup VC_Private_Macros VC Private Macros
  * @{
  */

/**
  * @brief  Enable interrupt to set INT_EN and INT_MODE.
  * @param  __HANDLE__  pointer to a VC_HandleTypeDef structure that contains
  *                the configuration information for the specified VC module.
  * @retval None
  */
#define VC_ENABLE_INT_SET(__HANDLE__)          SET_BIT((__HANDLE__)->Instance->CR1,(HAL_VC_INT_ENABLE | (__HANDLE__)->Init.INT_Mode))

/**
  * @brief  Disable interrupt to clear INT_EN ,HIGHINTEN,RISEINTEN and FALLINTEN.
  * @param  __HANDLE__  pointer to a VC_HandleTypeDef structure that contains
  *                the configuration information for the specified VC module.
  * @retval None
  */
#define VC_DISABLE_INT_CLEAR(__HANDLE__)          CLEAR_BIT((__HANDLE__)->Instance->CR1,(HAL_VC_INT_ENABLE | HAL_VC_HIGH_INT_ENABLE | \
                                                              HAL_VC_RISE_INT_ENABLE | HAL_VC_FALL_INT_ENABLE))

/**
  * @brief  Check VC VC25 DIVIDER.
  * @param  VC25DIV  VC VC25 divider
  * @retval None
  */
#define IS_VC_VC25DIV(VC25DIV)          (((VC25DIV) == HAL_VC_1P4_V25DIV) || ((VC25DIV) == HAL_VC_2P4_V25DIV) || \
                                          ((VC25DIV) == HAL_VC_3P4_V25DIV) || ((VC25DIV) == HAL_VC_4P4_V25DIV) ) 

/**
  * @brief  Check VC INPUT SELECT.
  * @param  INPUTE  VC Input Source
  * @retval None
  */
#define IS_VC_INPUT(INPUTE)         (((INPUT) == HAL_VC_INPUT_0) || ((INPUT) == HAL_VC_INPUT_1) || \
                                      ((INPUT) == HAL_VC_INPUT_2) || ((INPUT) == HAL_VC_INPUT_V25DIV))
    /**
  * @brief  Check VC INTERRUPT ENABLE OR DISABLE.
  * @param  STATE  VC interrupt enable or disable
  * @retval None
  */
#define IS_VC_INT_STATE(STATE)       ((STATE == HAL_VC_INT_ENABLE) || (STATE == HAL_VC_INT_DISABLE))
    /**
  * @brief  Check VC INTERRUPT TRIGER MODE.
  * @param  MODE  VC interrupt triger mode
  * @retval None
  */
#define IS_VC_INT_MODE(MODE)         ((MODE) == HAL_VC_HIGH_INT_ENABLE) || (MODE) == HAL_VC_RASI_INT_ENABLE) || \
                                    (MODE) == HAL_VC_FALL_INT_ENABLE))
    /**
  * @brief  Check VC FILTER ENABLE OR DISABLE.
  * @param  STATE  VC Filter enable or disable
  * @retval None
  */
#define IS_VC_FILTER_STATE(STATE)       ((STATE == HAL_VC_FILTER_ENABLE) || (STATE == HAL_VC_FILTER_DISABLE))
/**
  * @brief  Check VC FILTER NUMBER.
  * @param  FILTER_NUM  VC Filter number
  * @retval None
  */
#define IS_VC_FILTER_NUM(FILTER_NUM)        ((FILTER_NUM >= 0U) && (FILTER_NUM <= 0XFFFFU)) 
/**
  * @brief  Check VC FILTER CLK SOURCE.
  * @param  FILTER_CLK  VC Filter clock source
  * @retval None
  */
#define IS_VC_FILTER_CLK(FILTER_CLK)        ((FILTER_CLK == HAL_VC_FILTER_CLK_NONE) || (FILTER_CLK == HAL_VC_FILTER_CLK_PLK) || \
                                               (FILTER_CLK == HAL_VC_FILTER_CLK_LIRC)) 
/**
  * @brief  Check VC OUTPUT CONFIG.
  * @param  OUTPUT_CONFIG  VC output config
  * @retval None
  */
#define IS_VC_OUTPUT_CONFIG(OUTPUT_CONFIG)   (((OUTPUT_CONFIG&HAL_VC_OUTCFG_Msk) != 0X00U) && \
                                              ((OUTPUT_CONFIG&~HAL_VC_OUTCFG_Msk) == 0X00U))  
/**
  * @brief  Check VC INSTANCE INhandle .
  * @param  INSTANCE  VC Instance
  * @retval None
  */
#define IS_VC_INSTANCE(INSTANCE)       ((INSTANCE) == VC)

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

#endif /* __CX32L003_HAL_VC_H */


