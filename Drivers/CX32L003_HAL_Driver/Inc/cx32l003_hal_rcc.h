/**
  ******************************************************************************
  * @file    cx32l003_hal_rcc.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of RCC HAL module.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_RCC_H
#define __CX32L003_HAL_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"



/** @addtogroup RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition  
  */
typedef struct
{
  uint32_t ClockType;             /*!< The clock to be configured.
                                       This parameter can be a value of @ref RCC_System_Clock_Type */

  uint32_t SYSCLKSource;          /*!< The clock source (SYSCLKS) used as system clock.
                                       This parameter can be a value of @ref RCC_System_Clock_Source */

  uint32_t AHBCLKDivider;         /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of 0-255, default is RCC_HCLK_DIV1 */

  uint32_t APBCLKDivider;         /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of 0-255, default is RCC_PCLK_DIV1 */

} RCC_ClkInitTypeDef;


/** 
  * @brief  RCC Internal/External Oscillator (HIRC, HXT, LIRC and LXT) configuration structure definition  
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                       This parameter can be a value of @ref RCC_Oscillator_Type */

  uint32_t HIRCState;              /*!< The new state of the HIRC.
                                       This parameter can be a value of @ref RCC_HIRC_Config */	
	
  uint32_t HIRCCalibrationValue;   /*!< The HIRC calibration trimming value.
                                       This parameter can be a value of @ref RCC_HIRC_Calibration_Config */	
	
  uint32_t HXTState;              /*!< The new state of the HXT.
                                       This parameter can be a value of @ref RCC_HXT_Config */	
	
  uint32_t LIRCState;              /*!<  The new state of the LIRC.
                                        This parameter can be a value of @ref RCC_LIRC_Config */ 	

  uint32_t LIRCStartupValue;       /*!<  The startup time of the LIRC.
                                         This parameter can be a value of @ref RCC_LIRC_Startup_Value */ 	
	
  uint32_t LIRCCalibrationValue;   /*!< The LIRC calibration trimming value.
                                       This parameter can be a value of @ref RCC_LIRC_Calibration_Config */		
	
  uint32_t LXTState;               /*!<  The new state of the LXT.
                                        This parameter can be a value of @ref RCC_LXT_Config */
                                 
} RCC_OscInitTypeDef;

/**
  * @}
  */ /* End of group RCC_Exported_Types */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE            0x00000000U
#define RCC_OSCILLATORTYPE_HIRC            0x00000001U
#define RCC_OSCILLATORTYPE_HXT             0x00000002U
#define RCC_OSCILLATORTYPE_LXT             0x00000004U
#define RCC_OSCILLATORTYPE_LIRC            0x00000008U
/**
  * @}
  */

/** @defgroup RCC_HXT_Config HXT Config
  * @{
  */
#define RCC_HXT_OFF                      0x00000000U                                /*!< HXT clock deactivation */
#define RCC_HXT_ON                       RCC_SYSCLKCR_HXTEN                         /*!< HXT clock activation */
#define RCC_HXT_BYPASS									 RCC_SYSCLKCR_HXTBYP												/*!< HXT clock bypass */
#define RCC_HXT_DEFAULT									 0xFFFFFFFFU

/**
  * @}
  */


/** @defgroup RCC_HIRC_Config HIRC Config
  * @{
  */
#define RCC_HIRC_OFF                      0x00000000U                                /*!< HIRC clock deactivation */
#define RCC_HIRC_ON                       RCC_SYSCLKCR_HIRCEN                        /*!< HIRC clock activation */

//PACKAGE is defined by default. for KDG customer, PACKAGE should be undefined.
#define PACKAGE

/** @defgroup RCC_HIRC_Calibration_Config HIRC Calibration Config
  * @{
  */	
#ifdef PACKAGE	
#define HIRC24M_FLASHADDR									0x180000A0
#define HIRC22M_FLASHADDR									0x180000A2
#define HIRC16M_FLASHADDR									0x180000A4
#define HIRC8M_FLASHADDR									0x180000A6
#define HIRC4M_FLASHADDR									0x180000A8
#else
#define HIRC24M_FLASHADDR									0x180000C0
#define HIRC22M_FLASHADDR									0x180000C2
#define HIRC16M_FLASHADDR									0x180000C4
#define HIRC8M_FLASHADDR									0x180000C6
#define HIRC4M_FLASHADDR									0x180000C8
#endif


#define RCC_HIRCCALIBRATION_24M       		(*(uint16_t*)(HIRC24M_FLASHADDR))        
#define RCC_HIRCCALIBRATION_22M						(*(uint16_t*)(HIRC22M_FLASHADDR))  
#define RCC_HIRCCALIBRATION_16M						(*(uint16_t*)(HIRC16M_FLASHADDR))  
#define RCC_HIRCCALIBRATION_8M						(*(uint16_t*)(HIRC8M_FLASHADDR))  
#define RCC_HIRCCALIBRATION_4M						(*(uint16_t*)(HIRC4M_FLASHADDR))

#define RCC_HIRCCALIBRATION_DEFAULT				0x00000312

#define RCC_HIRCCR_TRIMLEVEL_4M						RCC_HIRCCR_HIRCTRIM_9
#define RCC_HIRCCR_TRIMLEVEL_8M						RCC_HIRCCR_HIRCTRIM_10
#define RCC_HIRCCR_TRIMLEVEL_12M					RCC_HIRCCR_HIRCTRIM_9 | RCC_HIRCCR_HIRCTRIM_10
#define RCC_HIRCCR_TRIMLEVEL_16M					RCC_HIRCCR_HIRCTRIM_11
#define RCC_HIRCCR_TRIMLEVEL_20M					RCC_HIRCCR_HIRCTRIM_11 | RCC_HIRCCR_HIRCTRIM_9
#define RCC_HIRCCR_TRIMLEVEL_24M					RCC_HIRCCR_HIRCTRIM_11 | RCC_HIRCCR_HIRCTRIM_10

/**
  * @}
  */
	
/**
  * @}
  */

/** @defgroup RCC_LXT_Config LXT Config
  * @{
  */
#define RCC_LXT_OFF                      0x00000000U                                 /*!< LXT clock deactivation */
#define RCC_LXT_ON                       RCC_LXTCR_LXTEN                             /*!< LXT clock activation */
#define RCC_LXT_BYPASS                   RCC_LXTCR_LXTBYP 													 /*!< External clock source for LXT clock */

/**
  * @}
  */


/** @defgroup RCC_LIRC_Config LIRC Config
  * @{
  */
#define RCC_LIRC_OFF                      0x00000000U              /*!< LIRC clock deactivation */
#define RCC_LIRC_ON                       RCC_SYSCLKCR_LIRCEN      /*!< LIRC clock activation */

/**
  * @}
  */


/** @defgroup RCC_LIRC_Startup_Value LIRC Startup time duration Config
  * @{
  */
#define RCC_LIRC_STARTUP_4CYCLE         	0x00000000U              															/*!< Startup time 4 cycles */
#define RCC_LIRC_STARTUP_16CYCLE        	(RCC_LIRCCR_LIRCSTARTUP_0)       											/*!< Startup time 16 cycles */
#define RCC_LIRC_STARTUP_64CYCLE 					(RCC_LIRCCR_LIRCSTARTUP_1)														/*!< Startup time 64 cycles */
#define RCC_LIRC_STARTUP_256CYCLE 				(RCC_LIRCCR_LIRCSTARTUP_1 | RCC_LIRCCR_LIRCSTARTUP_0)	/*!< Startup time 256 cycles */

/**
  * @}
  */


/** @defgroup RCC_LIRC_Calibration_Config LIRC Calibration Config
  * @{
  */	
#ifdef PACKAGE		
#define LIRC32K_FLASHADDR									0x180000B0
#define LIRC38K_FLASHADDR									0x180000B4
#else
#define LIRC32K_FLASHADDR									0x180000D0
#define LIRC38K_FLASHADDR									0x180000D4
#endif

#define RCC_LIRCCALIBRATION_32K       		(*(uint16_t*)(LIRC32K_FLASHADDR))        
#define RCC_LIRCCALIBRATION_38K						(*(uint16_t*)(LIRC38K_FLASHADDR))  
#define RCC_LIRCCALIBRATION_DEFAULT				0x0000007F

/**
  * @}
  */




/** @defgroup RCC_System_Clock_Type System Clock Type
  * @{
  */
#define RCC_CLOCKTYPE_SYSCLK             0x00000001U /*!< SYSCLK to configure */
#define RCC_CLOCKTYPE_HCLK               0x00000002U /*!< HCLK to configure */
#define RCC_CLOCKTYPE_PCLK               0x00000004U /*!< PCLK to configure */

/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_HIRC          RCC_SYSCLKSEL_CLKSW_0  /*!< HIRC selected as system clock */
#define RCC_SYSCLKSOURCE_HXT           RCC_SYSCLKSEL_CLKSW_1  /*!< HXT selected as system clock */
#define RCC_SYSCLKSOURCE_LIRC          RCC_SYSCLKSEL_CLKSW_2  /*!< LIRC selected as system clock */
#define RCC_SYSCLKSOURCE_LXT					 RCC_SYSCLKSEL_CLKSW_3	/*!< LXT selected as system clock */

/**
  * @}
  */

/** @defgroup RCC_System_Clock_Source_Status System Clock Source Status
  * @{
  */
#define RCC_SYSCLKSOURCE_STATUS_HIRC      RCC_SYSCLKSEL_CLKSW_0            /*!< HIRC used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HXT      	RCC_SYSCLKSEL_CLKSW_1            /*!< HXT used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_LIRC   		RCC_SYSCLKSEL_CLKSW_2            /*!< LIRC used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_LXT				RCC_SYSCLKSEL_CLKSW_3						 /*!< LXT used as system clock */
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source AHB Clock Source
  * @{
  */
#define RCC_SYSCLK_DIV1                  RCC_CFGR_HPRE_DIV1   /*!< SYSCLK not divided */
#define RCC_SYSCLK_DIV2                  RCC_CFGR_HPRE_DIV2   /*!< SYSCLK divided by 2 */
#define RCC_SYSCLK_DIV4                  RCC_CFGR_HPRE_DIV4   /*!< SYSCLK divided by 4 */
#define RCC_SYSCLK_DIV8                  RCC_CFGR_HPRE_DIV8   /*!< SYSCLK divided by 8 */
#define RCC_SYSCLK_DIV16                 RCC_CFGR_HPRE_DIV16  /*!< SYSCLK divided by 16 */
#define RCC_SYSCLK_DIV64                 RCC_CFGR_HPRE_DIV64  /*!< SYSCLK divided by 64 */
#define RCC_SYSCLK_DIV128                RCC_CFGR_HPRE_DIV128 /*!< SYSCLK divided by 128 */
#define RCC_SYSCLK_DIV256                RCC_CFGR_HPRE_DIV256 /*!< SYSCLK divided by 256 */
#define RCC_SYSCLK_DIV512                RCC_CFGR_HPRE_DIV512 /*!< SYSCLK divided by 512 */

/**
  * @}
  */
  
/** @defgroup RCC_HCLK_DIV HCLK divider
  * @{
  */
#define RCC_HCLK_DIV1                   RCC_HCLKDIV_AHBCKDIV_1  /*!< HCLK not divided */

/**
  * @}
  */
	
/** @defgroup RCC_PCLK_DIV PCLK divider
  * @{
  */	
#define RCC_PCLK_DIV1                    RCC_PCLKDIV_APBCKDIV_1  /*!< PCLK not divided */

/**
  * @}
  */

/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */
#define RCC_MCO                          0x00000000U

/**
  * @}
  */


/** @defgroup RCC_MCO_Index MCO Index
  * @{
  */
#define  RCC_MCOSOURCE_HIRC     				0x00000000U
#define  RCC_MCOSOURCE_HXT      				RCC_MCOCR_MCOSEL_0
#define  RCC_MCOSOURCE_LIRC     				RCC_MCOCR_MCOSEL_1
#define  RCC_MCOSOURCE_LXT      				RCC_MCOCR_MCOSEL_1 | RCC_MCOCR_MCOSEL_0
#define  RCC_MCOSOURCE_SYSCLK   				RCC_MCOCR_MCOSEL_2
#define  RCC_MCOSOURCE_HCLK     				RCC_MCOCR_MCOSEL_2 | RCC_MCOCR_MCOSEL_0

/**
  * @}
  */


/** @defgroup RCC_MCOx_Clock_Prescaler MCO Clock Prescaler
  * @{
  */
#define RCC_MCODIV_1                    0x00000000U

/**
  * @}
  */

  
/** @defgroup RCC_Flag Flags
  *        Elements values convention: XXXX_YYYY_YYYY_YYYY_YYYYb
  *           - YYYY_YYYY_YYYY_YYYY  : Flag position in the register
  *           - XXXX  : Register index
  *                 - 0001: HIRCCR register
  *                 - 0010: HXTCR register
  *                 - 0011: LIRCCR register
  *                 - 0100: LXTCR register
  *                 - 0101: RSTSR register	
  * @{
  */
/* Flags for different clock */
#define RCC_FLAG_HIRCRDY                  ((uint32_t)((HIRCCR_REG_INDEX << 16U) | RCC_HIRCCR_HIRCRDY)) 	/*!< Internal High Speed clock ready flag */
#define RCC_FLAG_HXTRDY                  	((uint32_t)((HXTCR_REG_INDEX << 16U) | RCC_HXTCR_HXTRDY)) 		/*!< External High Speed clock ready flag */
#define RCC_FLAG_LIRCRDY                  ((uint32_t)((LIRCCR_REG_INDEX << 16U) | RCC_LIRCCR_LIRCRDY)) 	/*!< Internal Low Speed clock ready flag */
#define RCC_FLAG_LXTRDY										((uint32_t)((LXTCR_REG_INDEX << 16U) | RCC_LXTCR_LXTRDY)) 		/*!< External Low Speed clock ready flag */
	
/* Flags for different reset */	
#define RCC_FLAG_SFTRST                   ((uint32_t)((RSTSR_REG_INDEX << 16U) | RCC_RSTSR_SFTRST))  		/*!< Software Reset flag */
#define RCC_FLAG_PADRST                   ((uint32_t)((RSTSR_REG_INDEX << 16U) | RCC_RSTSR_PADRST))  		/*!< Pad Reset flag */	
#define RCC_FLAG_LOCKUPRST                ((uint32_t)((RSTSR_REG_INDEX << 16U) | RCC_RSTSR_LOCKUPRST))  /*!< CPU Lockup Reset flag */
#define RCC_FLAG_PORRST                   ((uint32_t)((RSTSR_REG_INDEX << 16U) | RCC_RSTSR_PORRST))  		/*!< Por Reset flag */		
#define RCC_FLAG_LVDRST                		((uint32_t)((RSTSR_REG_INDEX << 16U) | RCC_RSTSR_LVDRST))  		/*!< Lvd Reset flag */
#define RCC_FLAG_IWDGRST                  ((uint32_t)((RSTSR_REG_INDEX << 16U) | RCC_RSTSR_IWDGRST))  	/*!< IWDG Reset flag */		
#define RCC_FLAG_WWDGRST                  ((uint32_t)((RSTSR_REG_INDEX << 16U) | RCC_RSTSR_WWDGRST))  	/*!< WWDG Reset flag */		
#define RCC_FLAG_CPURST                   ((uint32_t)((RSTSR_REG_INDEX << 16U) | RCC_RSTSR_CPURST))  		/*!< CPU Reset flag */
#define RCC_FLAG_MCURST                   ((uint32_t)((RSTSR_REG_INDEX << 16U) | RCC_RSTSR_MCURST))  		/*!< MCU Reset flag */

/**
  * @}
  */

/**
  * @}
  */ /* End of group RCC_Exported_Constants */


/* Exported macro ------------------------------------------------------------*/

/** @defgroup RCC_Exported_Macros RCC Exported Macros
  * @{
  */

/** @defgroup RCC_Peripheral_Clock_Enable_Disable Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.   
  * @{
  */
#define __HAL_RCC_FLASH_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->HCLKEN, RCC_HCLKEN_FLASHCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->HCLKEN, RCC_HCLKEN_FLASHCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)

#define __HAL_RCC_CRC_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->HCLKEN, RCC_HCLKEN_CRCCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->HCLKEN, RCC_HCLKEN_CRCCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																			
																			
#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->HCLKEN, RCC_HCLKEN_GPIODCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->HCLKEN, RCC_HCLKEN_GPIODCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)		
																			
#define __HAL_RCC_GPIOC_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->HCLKEN, RCC_HCLKEN_GPIOCCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->HCLKEN, RCC_HCLKEN_GPIOCCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																					

#define __HAL_RCC_GPIOB_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->HCLKEN, RCC_HCLKEN_GPIOBCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->HCLKEN, RCC_HCLKEN_GPIOBCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																					
	
#define __HAL_RCC_GPIOA_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->HCLKEN, RCC_HCLKEN_GPIOACKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->HCLKEN, RCC_HCLKEN_GPIOACKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																				

#define __HAL_RCC_FLASH_CLK_DISABLE()     (RCC->HCLKEN &= ~(RCC_HCLKEN_FLASHCKEN))
#define __HAL_RCC_CRC_CLK_DISABLE()       (RCC->HCLKEN &= ~(RCC_HCLKEN_CRCCKEN))
#define __HAL_RCC_GPIOD_CLK_DISABLE()     (RCC->HCLKEN &= ~(RCC_HCLKEN_GPIODCKEN))
#define __HAL_RCC_GPIOC_CLK_DISABLE()     (RCC->HCLKEN &= ~(RCC_HCLKEN_GPIOCCKEN))																		
#define __HAL_RCC_GPIOB_CLK_DISABLE()     (RCC->HCLKEN &= ~(RCC_HCLKEN_GPIOBCKEN))																			
#define __HAL_RCC_GPIOA_CLK_DISABLE()     (RCC->HCLKEN &= ~(RCC_HCLKEN_GPIOACKEN))																				
																			
/**
  * @}
  */

/** @defgroup RCC_AHB_Peripheral_Clock_Enable_Disable_Status AHB Peripheral Clock Enable Disable Status
  * @brief  Get the enable or disable status of the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#define __HAL_RCC_FLASH_IS_CLK_ENABLED()       ((RCC->HCLKEN & (RCC_HCLKEN_FLASHCKEN)) != RESET)
#define __HAL_RCC_FLASH_IS_CLK_DISABLED()      ((RCC->HCLKEN & (RCC_HCLKEN_FLASHCKEN)) == RESET)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()       	 ((RCC->HCLKEN & (RCC_HCLKEN_CRCCKEN)) != RESET)
#define __HAL_RCC_CRC_IS_CLK_DISABLED()      	 ((RCC->HCLKEN & (RCC_HCLKEN_CRCCKEN)) == RESET)
#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()       ((RCC->HCLKEN & (RCC_HCLKEN_GPIODCKEN)) != RESET)
#define __HAL_RCC_GPIOD_IS_CLK_DISABLED()      ((RCC->HCLKEN & (RCC_HCLKEN_GPIODCKEN)) == RESET)
#define __HAL_RCC_GPIOC_IS_CLK_ENABLED()       ((RCC->HCLKEN & (RCC_HCLKEN_GPIOCCKEN)) != RESET)
#define __HAL_RCC_GPIOC_IS_CLK_DISABLED()      ((RCC->HCLKEN & (RCC_HCLKEN_GPIOCCKEN)) == RESET)
#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()       ((RCC->HCLKEN & (RCC_HCLKEN_GPIOBCKEN)) != RESET)
#define __HAL_RCC_GPIOB_IS_CLK_DISABLED()      ((RCC->HCLKEN & (RCC_HCLKEN_GPIOBCKEN)) == RESET)
#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()       ((RCC->HCLKEN & (RCC_HCLKEN_GPIOACKEN)) != RESET)
#define __HAL_RCC_GPIOA_IS_CLK_DISABLED()      ((RCC->HCLKEN & (RCC_HCLKEN_GPIOACKEN)) == RESET)

/**
  * @}
  */

/** @defgroup RCC_APB_Clock_Enable_Disable APB Clock Enable Disable
  * @brief  Enable or disable the Low Speed APB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it. 
  * @{   
  */
#define __HAL_RCC_DBG_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_DBGCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_DBGCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)

#define __HAL_RCC_BEEP_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_BEEPCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_BEEPCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)
																			
#define __HAL_RCC_LVDVC_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_LVDVCCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_LVDVCCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																			
																			
#define __HAL_RCC_IWDG_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_IWDGCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_IWDGCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																							
																			
#define __HAL_RCC_CLKTRIM_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_CLKCTRIMCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_CLKCTRIMCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																					

#define __HAL_RCC_RTC_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_RTCCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_RTCCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)			

#define __HAL_RCC_AWK_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_AWKCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_AWKCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)		

#define __HAL_RCC_ADC_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_ADCCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_ADCCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)		

#define __HAL_RCC_WWDG_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_WWDGCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_WWDGCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)		
																			
#define __HAL_RCC_TIM2_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_TIM2CKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_TIM2CKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)		

#define __HAL_RCC_TIM1_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_TIM1CKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_TIM1CKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)		

#define __HAL_RCC_OWIRE_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_OWIRECKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_OWIRECKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)	
																			
#define __HAL_RCC_PCA_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_PCACKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_PCACKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																				
																			
#define __HAL_RCC_SYSCON_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_SYSCONCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_SYSCONCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																					
																			
#define __HAL_RCC_BASETIM_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_BASETIMCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_BASETIMCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																					
																			
#define __HAL_RCC_LPTIM_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_LPTIMCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_LPTIMCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																					

#define __HAL_RCC_SPI_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_SPICKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_SPICKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)				

#define __HAL_RCC_LPUART_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_LPUARTCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_LPUARTCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																					
																			
#define __HAL_RCC_I2C_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_I2CCKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_I2CCKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)		

#define __HAL_RCC_UART1_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_UART1CKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_UART1CKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																					
																			
#define __HAL_RCC_UART0_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->PCLKEN, RCC_PCLKEN_UART0CKEN);\
                                        /* Delay after an RCC peripheral clock enabling */\
                                        tmpreg = READ_BIT(RCC->PCLKEN, RCC_PCLKEN_UART0CKEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)																					
																			
																			
#define __HAL_RCC_DBG_CLK_DISABLE()      			(RCC->PCLKEN &= ~(RCC_PCLKEN_DBGCKEN))
#define __HAL_RCC_BEEP_CLK_DISABLE()      		(RCC->PCLKEN &= ~(RCC_PCLKEN_BEEPCKEN))
#define __HAL_RCC_LVDVC_CLK_DISABLE()      		(RCC->PCLKEN &= ~(RCC_PCLKEN_LVDVCCKEN))
#define __HAL_RCC_IWDG_CLK_DISABLE()       		(RCC->PCLKEN &= ~(RCC_PCLKEN_IWDGCKEN))
#define __HAL_RCC_CLKTRIM_CLK_DISABLE()       (RCC->PCLKEN &= ~(RCC_PCLKEN_CLKCTRIMCKEN))
#define __HAL_RCC_RTC_CLK_DISABLE()      			(RCC->PCLKEN &= ~(RCC_PCLKEN_RTCCKEN))
#define __HAL_RCC_AWK_CLK_DISABLE()      			(RCC->PCLKEN &= ~(RCC_PCLKEN_AWKCKEN))
#define __HAL_RCC_ADC_CLK_DISABLE()      			(RCC->PCLKEN &= ~(RCC_PCLKEN_ADCCKEN))
#define __HAL_RCC_WWDG_CLK_DISABLE()       		(RCC->PCLKEN &= ~(RCC_PCLKEN_WWDGCKEN))
#define __HAL_RCC_TIM2_CLK_DISABLE()       		(RCC->PCLKEN &= ~(RCC_PCLKEN_TIM2CKEN))																			
#define __HAL_RCC_TIM1_CLK_DISABLE()       		(RCC->PCLKEN &= ~(RCC_PCLKEN_TIM1CKEN))
#define __HAL_RCC_OWIRE_CLK_DISABLE()       	(RCC->PCLKEN &= ~(RCC_PCLKEN_OWIRECKEN))	
#define __HAL_RCC_PCA_CLK_DISABLE()       		(RCC->PCLKEN &= ~(RCC_PCLKEN_PCACKEN))
#define __HAL_RCC_SYSCON_CLK_DISABLE()       	(RCC->PCLKEN &= ~(RCC_PCLKEN_SYSCONCKEN))	
#define __HAL_RCC_BASETIM_CLK_DISABLE()       (RCC->PCLKEN &= ~(RCC_PCLKEN_BASETIMCKEN))
#define __HAL_RCC_LPTIM_CLK_DISABLE()       	(RCC->PCLKEN &= ~(RCC_PCLKEN_LPTIMCKEN))																													
#define __HAL_RCC_SPI_CLK_DISABLE()       		(RCC->PCLKEN &= ~(RCC_PCLKEN_SPICKEN))
#define __HAL_RCC_LPUART_CLK_DISABLE()       	(RCC->PCLKEN &= ~(RCC_PCLKEN_LPUARTCKEN))	
#define __HAL_RCC_I2C_CLK_DISABLE()       		(RCC->PCLKEN &= ~(RCC_PCLKEN_I2CCKEN))
#define __HAL_RCC_UART1_CLK_DISABLE()       	(RCC->PCLKEN &= ~(RCC_PCLKEN_UART1CKEN))	
#define __HAL_RCC_UART0_CLK_DISABLE()       	(RCC->PCLKEN &= ~(RCC_PCLKEN_UART0CKEN))	

/**
  * @}
  */

/** @defgroup RCC_APB_Peripheral_Clock_Enable_Disable_Status APB Peripheral Clock Enable Disable Status
  * @brief  Get the enable or disable status of the APB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

#define __HAL_RCC_DBG_IS_CLK_ENABLED()        ((RCC->PCLKEN & (RCC_PCLKEN_DBGCKEN)) != RESET)
#define __HAL_RCC_BEEP_IS_CLK_DISABLED()      ((RCC->PCLKEN & (RCC_PCLKEN_BEEPCKEN)) == RESET)
#define __HAL_RCC_LVDVC_IS_CLK_ENABLED()      ((RCC->PCLKEN & (RCC_PCLKEN_LVDVCCKEN)) != RESET)
#define __HAL_RCC_IWDG_IS_CLK_DISABLED()      ((RCC->PCLKEN & (RCC_PCLKEN_IWDGCKEN)) == RESET)
#define __HAL_RCC_CLKTRIM_IS_CLK_ENABLED()    ((RCC->PCLKEN & (RCC_PCLKEN_CLKCTRIMCKEN)) != RESET)
#define __HAL_RCC_RTC_IS_CLK_DISABLED()       ((RCC->PCLKEN & (RCC_PCLKEN_RTCCKEN)) == RESET)
#define __HAL_RCC_AWK_IS_CLK_ENABLED()        ((RCC->PCLKEN & (RCC_PCLKEN_AWKCKEN)) != RESET)
#define __HAL_RCC_ADC_IS_CLK_DISABLED()       ((RCC->PCLKEN & (RCC_PCLKEN_ADCCKEN)) == RESET)
#define __HAL_RCC_WWDG_IS_CLK_DISABLED()      ((RCC->PCLKEN & (RCC_PCLKEN_WWDGCKEN)) == RESET)
#define __HAL_RCC_TIM2_IS_CLK_ENABLED()       ((RCC->PCLKEN & (RCC_PCLKEN_TIM2CKEN)) != RESET)
#define __HAL_RCC_TIM1_IS_CLK_DISABLED()      ((RCC->PCLKEN & (RCC_PCLKEN_TIM1CKEN)) == RESET)
#define __HAL_RCC_OWIRE_IS_CLK_DISABLED()     ((RCC->PCLKEN & (RCC_PCLKEN_OWIRECKEN)) == RESET)
#define __HAL_RCC_PCA_IS_CLK_ENABLED()        ((RCC->PCLKEN & (RCC_PCLKEN_PCACKEN)) != RESET)
#define __HAL_RCC_SYSCON_IS_CLK_DISABLED()    ((RCC->PCLKEN & (RCC_PCLKEN_SYSCONCKEN)) == RESET)
#define __HAL_RCC_BASETIM_IS_CLK_DISABLED()   ((RCC->PCLKEN & (RCC_PCLKEN_BASETIMCKEN)) == RESET)
#define __HAL_RCC_LPTIM_IS_CLK_ENABLED()      ((RCC->PCLKEN & (RCC_PCLKEN_LPTIMCKEN)) != RESET)
#define __HAL_RCC_SPI_IS_CLK_DISABLED()       ((RCC->PCLKEN & (RCC_PCLKEN_SPICKEN)) == RESET)
#define __HAL_RCC_LPUART_IS_CLK_ENABLED()     ((RCC->PCLKEN & (RCC_PCLKEN_LPUARTCKEN)) != RESET)
#define __HAL_RCC_I2C_IS_CLK_DISABLED()       ((RCC->PCLKEN & (RCC_PCLKEN_I2CCKEN)) == RESET)
#define __HAL_RCC_UART1_IS_CLK_ENABLED()      ((RCC->PCLKEN & (RCC_PCLKEN_UART1CKEN)) != RESET)
#define __HAL_RCC_UART0_IS_CLK_DISABLED()     ((RCC->PCLKEN & (RCC_PCLKEN_UART0CKEN)) == RESET)

/**
  * @}
  */


/** @defgroup RCC_AHB_APB_Force_Release_Reset AHB and APB Force Release Reset
  * @brief  Force or release AHB, APB peripheral reset.
  * @{   
  */
#define __HAL_RCC_CRC_FORCE_RESET()       		(RCC->PERIRST |= (RCC_PERIRST_CRCRST))
#define __HAL_RCC_GPIOD_FORCE_RESET()       	(RCC->PERIRST |= (RCC_PERIRST_GPIODRST))
#define __HAL_RCC_GPIOC_FORCE_RESET()       	(RCC->PERIRST |= (RCC_PERIRST_GPIOCRST))
#define __HAL_RCC_GPIOB_FORCE_RESET()     		(RCC->PERIRST |= (RCC_PERIRST_GPIOBRST))
#define __HAL_RCC_GPIOA_FORCE_RESET()       	(RCC->PERIRST |= (RCC_PERIRST_GPIOARST))
#define __HAL_RCC_DBG_FORCE_RESET()        		(RCC->PERIRST |= (RCC_PERIRST_DBGRST))
#define __HAL_RCC_BEEP_FORCE_RESET()        	(RCC->PERIRST |= (RCC_PERIRST_BEEPRST))
#define __HAL_RCC_LVDVC_FORCE_RESET()       	(RCC->PERIRST |= (RCC_PERIRST_LVDVCRST))
#define __HAL_RCC_CLKTRIM_FORCE_RESET()       (RCC->PERIRST |= (RCC_PERIRST_CLKTRIMRST))
#define __HAL_RCC_AWK_FORCE_RESET()       		(RCC->PERIRST |= (RCC_PERIRST_AWKRST))
#define __HAL_RCC_ADC_FORCE_RESET()     			(RCC->PERIRST |= (RCC_PERIRST_ADCRST))
#define __HAL_RCC_WWDG_FORCE_RESET()       		(RCC->PERIRST |= (RCC_PERIRST_WWDGRST))
#define __HAL_RCC_TIM2_FORCE_RESET()        	(RCC->PERIRST |= (RCC_PERIRST_TIM2RST))
#define __HAL_RCC_TIM1_FORCE_RESET()        	(RCC->PERIRST |= (RCC_PERIRST_TIM1RST))
#define __HAL_RCC_OWRIE_FORCE_RESET()     		(RCC->PERIRST |= (RCC_PERIRST_OWIRERST))
#define __HAL_RCC_PCA_FORCE_RESET()       		(RCC->PERIRST |= (RCC_PERIRST_PCARST))
#define __HAL_RCC_SYSCON_FORCE_RESET()        (RCC->PERIRST |= (RCC_PERIRST_SYSCONRST))
#define __HAL_RCC_BASETIM_FORCE_RESET()       (RCC->PERIRST |= (RCC_PERIRST_BASETIMRST))
#define __HAL_RCC_LPTIM_FORCE_RESET()     		(RCC->PERIRST |= (RCC_PERIRST_LPTIMRST))
#define __HAL_RCC_SPI_FORCE_RESET()       		(RCC->PERIRST |= (RCC_PERIRST_SPIRST))
#define __HAL_RCC_LPUART_FORCE_RESET()        (RCC->PERIRST |= (RCC_PERIRST_LPUARTRST))
#define __HAL_RCC_I2C_FORCE_RESET()        		(RCC->PERIRST |= (RCC_PERIRST_I2CRST))
#define __HAL_RCC_UART1_FORCE_RESET()        	(RCC->PERIRST |= (RCC_PERIRST_UART1RST))
#define __HAL_RCC_UART0_FORCE_RESET()        	(RCC->PERIRST |= (RCC_PERIRST_UART0RST))

#define __HAL_RCC_CRC_RELEASE_RESET()      		(RCC->PERIRST &= ~(RCC_PERIRST_CRCRST)) 
#define __HAL_RCC_GPIOD_RELEASE_RESET()       (RCC->PERIRST &= ~(RCC_PERIRST_GPIODRST))
#define __HAL_RCC_GPIOC_RELEASE_RESET()       (RCC->PERIRST &= ~(RCC_PERIRST_GPIOCRST))
#define __HAL_RCC_GPIOB_RELEASE_RESET()       (RCC->PERIRST &= ~(RCC_PERIRST_GPIOBRST))
#define __HAL_RCC_GPIOA_RELEASE_RESET()     	(RCC->PERIRST &= ~(RCC_PERIRST_GPIOARST))
#define __HAL_RCC_DBG_RELEASE_RESET()       	(RCC->PERIRST &= ~(RCC_PERIRST_DBGRST))
#define __HAL_RCC_BEEP_RELEASE_RESET()     		(RCC->PERIRST &= ~(RCC_PERIRST_BEEPRST))
#define __HAL_RCC_LVDVC_RELEASE_RESET()      	(RCC->PERIRST &= ~(RCC_PERIRST_LVDVCRST))
#define __HAL_RCC_CLKTRIM_RELEASE_RESET()     (RCC->PERIRST &= ~(RCC_PERIRST_CLKTRIMRST))
#define __HAL_RCC_AWK_RELEASE_RESET()       	(RCC->PERIRST &= ~(RCC_PERIRST_AWKRST))
#define __HAL_RCC_ADC_RELEASE_RESET()       	(RCC->PERIRST &= ~(RCC_PERIRST_ADCRST))
#define __HAL_RCC_WWDG_RELEASE_RESET()     		(RCC->PERIRST &= ~(RCC_PERIRST_WWDGRST))
#define __HAL_RCC_TIM2_RELEASE_RESET()       	(RCC->PERIRST &= ~(RCC_PERIRST_TIM2RST))
#define __HAL_RCC_TIM1_RELEASE_RESET()        (RCC->PERIRST &= ~(RCC_PERIRST_TIM1RST))
#define __HAL_RCC_OWRIE_RELEASE_RESET()       (RCC->PERIRST &= ~(RCC_PERIRST_OWIRERST))
#define __HAL_RCC_PCA_RELEASE_RESET()        	(RCC->PERIRST &= ~(RCC_PERIRST_PCARST))
#define __HAL_RCC_SYSCON_RELEASE_RESET()      (RCC->PERIRST &= ~(RCC_PERIRST_SYSCONRST))
#define __HAL_RCC_BASETIM_RELEASE_RESET()     (RCC->PERIRST &= ~(RCC_PERIRST_BASETIMRST))
#define __HAL_RCC_LPTIM_RELEASE_RESET()       (RCC->PERIRST &= ~(RCC_PERIRST_LPTIMRST))
#define __HAL_RCC_SPI_RELEASE_RESET()        	(RCC->PERIRST &= ~(RCC_PERIRST_SPIRST))
#define __HAL_RCC_LPUART_RELEASE_RESET()      (RCC->PERIRST &= ~(RCC_PERIRST_LPUARTRST))
#define __HAL_RCC_I2C_RELEASE_RESET()        	(RCC->PERIRST &= ~(RCC_PERIRST_I2CRST))
#define __HAL_RCC_UART1_RELEASE_RESET()       (RCC->PERIRST &= ~(RCC_PERIRST_UART1RST))
#define __HAL_RCC_UART0_RELEASE_RESET()       (RCC->PERIRST &= ~(RCC_PERIRST_UART0RST))

/**
  * @}
  */


/** @defgroup RCC_RegisterWrite_Unlock Unlock RCC write-protected registers
  * @brief  unlock RCC write-protected registers.
  * @{   
  */
#define __HAL_RCC_REGWR_LOCK()							(RCC->UNLOCK = (0x2AD5334C << RCC_UNLOCK_KEY_Pos) & RCC_UNLOCK_KEY)
#define __HAL_RCC_REGWR_UNLOCK()						(RCC->UNLOCK = RCC_UNLOCK_UNLOCK | (0x2AD5334C << RCC_UNLOCK_KEY_Pos))

/**
  * @}
  */

/** @defgroup RCC_HIRC_Configuration HSI Configuration
  * @{   
  */

/** @brief  Macros to enable or disable the Internal High Speed oscillator (HIRC).
  * @note   HIRC can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the HIRC.  
  * @note   After enabling the HIRC, the application software should wait on HIRCRDY
  *         flag to be set indicating that HIRC clock is stable and can be used as
  *         system clock source.  
  */
#define __HAL_RCC_HIRC_ENABLE() 			  \
						do{												  \
							__HAL_RCC_REGWR_UNLOCK(); \
							SET_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HIRCEN | (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos));\
							__HAL_RCC_REGWR_LOCK();	  \
						}while(0U)

#define __HAL_RCC_HIRC_DISABLE() 			  \
						do{												  \
							__HAL_RCC_REGWR_UNLOCK(); \
							CLEAR_WPBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HIRCEN, (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos)); \
							__HAL_RCC_REGWR_LOCK();	  \
						}while(0U)

/** @brief  Macro to adjust the Internal High Speed oscillator (HIRC) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HIRC.
  * @param  _HIRCCALIBRATIONVALUE_ specifies the calibration trimming value @ref RCC_HIRC_Calibration_Config
  *            - RCC_HIRCCALIBRATION_24M: HIRC select 24M
  *            - RCC_HIRCCALIBRATION_22M: HIRC select 22M
  *            - RCC_HIRCCALIBRATION_16M: HIRC select 16M
  *            - RCC_HIRCCALIBRATION_8M: HIRC select 8M	
  *            - RCC_HIRCCALIBRATION_4M: HIRC select 4M				
  */  
#define	RCC_KEY_UNLOCK			0x5A69
#define	RCC_HIRCCR_TRIMLEVEL_MSK	(RCC_HIRCCR_HIRCTRIM_9 | RCC_HIRCCR_HIRCTRIM_10 | RCC_HIRCCR_HIRCTRIM_11)
#define __HAL_RCC_HIRC_CALIBRATIONVALUE_ADJUST(_HIRCCALIBRATIONVALUE_) 																		 \
							do{                                                     																		 \
								__HAL_RCC_REGWR_UNLOCK();																																	 \
								if (((_HIRCCALIBRATIONVALUE_&RCC_HIRCCR_TRIMLEVEL_MSK) != RCC_HIRCCR_TRIMLEVEL_MSK) 			 \
									&&((_HIRCCALIBRATIONVALUE_&RCC_HIRCCR_TRIMLEVEL_MSK) != 0x00))													 \
									{                                                     \
										WRITE_REG(RCC->HIRCCR, ((uint32_t)(_HIRCCALIBRATIONVALUE_ & RCC_HIRCCR_HIRCTRIM_Msk) | \
																						(RCC_KEY_UNLOCK << RCC_HIRCCR_KEY_Pos)));							 \
									}                                                     																	 \
								__HAL_RCC_REGWR_LOCK();																																		 \
							}while(0U)



/**
  * @}
  */

/** @defgroup RCC_LSI_Configuration  LIRC Configuration
  * @{   
  */

/** @brief Macro to enable the Internal Low Speed oscillator (LIRC).
  * @note   After enabling the LIRC, the application software should wait on 
  *         LIRCRDY flag to be set indicating that LIRC clock is stable
  */
#define __HAL_RCC_LIRC_ENABLE() 			  \
						do{												  \
							__HAL_RCC_REGWR_UNLOCK(); \
							SET_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_LIRCEN | (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos));\
							__HAL_RCC_REGWR_LOCK();	  \
						}while(0U)							
							
						
/** @brief Macro to disable the Internal Low Speed oscillator (LIRC).
  * @note   When the LIRC is stopped, LIRCRDY flag goes low.
  */
					
#define __HAL_RCC_LIRC_DISABLE() 			  \
						do{												  \
							__HAL_RCC_REGWR_UNLOCK(); \
							CLEAR_WPBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_LIRCEN, (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos)); \
							__HAL_RCC_REGWR_LOCK();	  \
						}while(0U)		
							
						
/** @brief  Macro to adjust the Internal Low Speed oscillator (LIRC) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal LIRC.
  * @param  _LIRCCALIBRATIONVALUE_ specifies the calibration trimming value	@ref RCC_LIRC_Calibration_Config
  *            - RCC_LIRCCALIBRATION_32K: LIRC select 32K
  *            - RCC_LIRCCALIBRATION_38K: LIRC select 38K						
  */  
#define __HAL_RCC_LIRC_CALIBRATIONVALUE_ADJUST(_LIRCCALIBRATIONVALUE_) 																		\
							do{                                                     																		\
								__HAL_RCC_REGWR_UNLOCK();																																	\
								uint32_t tmpLIRCCR = 0;																																		\
								tmpLIRCCR = RCC->LIRCCR & RCC_LIRCCR_LIRCSTARTUP;																					\
								tmpLIRCCR |= (_LIRCCALIBRATIONVALUE_) & RCC_LIRCCR_LIRCTRIM_Msk;													\
								WRITE_REG(RCC->LIRCCR, ((uint32_t)(tmpLIRCCR) | (RCC_KEY_UNLOCK << RCC_LIRCCR_KEY_Pos)));	\
								__HAL_RCC_REGWR_LOCK();																																		\
							}while(0U)						


/** @brief  Macro to adjust the Internal Low Speed oscillator (LIRC) startup time value.
  * @param  _STARTUPTIME_ specifies the startup time value.
  */  
#define __HAL_RCC_LIRC_STARTUP_CONFIG(_STARTUPTIME_) 																		\
							do{                                                     																		\
								__HAL_RCC_REGWR_UNLOCK();																																	\
								uint32_t tmpLIRCCR = 0;																																		\
								tmpLIRCCR = RCC->LIRCCR & RCC_LIRCCR_LIRCTRIM;																						\
								tmpLIRCCR |= (_STARTUPTIME_);																															\
								WRITE_REG(RCC->LIRCCR, ((uint32_t)(tmpLIRCCR) | (RCC_KEY_UNLOCK << RCC_LIRCCR_KEY_Pos)));	\
								__HAL_RCC_REGWR_LOCK();																																		\
							}while(0U)		
							
						
/**
  * @}
  */

/** @defgroup RCC_HSE_Configuration HSE Configuration
  * @{   
  */

/**
  * @brief  Macro to configure the External High Speed oscillator (HXT).
  * @note   Transition HXT Bypass to HXT On and HXT On to HXT Bypass are not
  *         supported by this macro. User should request a transition to HXT Off
  *         first and then HXT On or HXT Bypass.
  * @param  __STATE__ specifies the new state of the HXT.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_HXT_ON turn ON the HXT oscillator
  *            @arg @ref RCC_HXT_BYPASS HXT oscillator bypassed with external clock
  */
#define __HAL_RCC_HXT_CONFIG(__STATE__)                                     \
                    do{                                                     \
											__HAL_RCC_REGWR_UNLOCK(); 														\
                      if ((__STATE__) == RCC_HXT_ON)                        \
                      {                                                     \
                        SET_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HXTEN | (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos)); \
                      }                                                     \
                      else if ((__STATE__) == RCC_HXT_OFF)                  \
                      {                                                     \
												CLEAR_WPBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HXTEN, (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos)); \
                      }                                                     \
                      else if ((__STATE__) == RCC_HXT_BYPASS)               \
                      {                                                     \
                        SET_BIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HXTBYP | (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos)); \
                      }                                                     \
                      else                                                  \
                      {                                                     \
												CLEAR_WPBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HXTEN, (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos)); \
												CLEAR_WPBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HXTBYP, (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos)); \
                      }                                                     \
        							__HAL_RCC_REGWR_LOCK();	  													  \
										}while(0U)

/**
  * @}
  */

/** @defgroup RCC_LXT_Configuration LXT Configuration
  * @{   
  */

/**
  * @brief  Macro to configure the External Low Speed oscillator (LXT).
  * @note Transitions LXT Bypass to LXT On and LXT On to LXT Bypass are not supported by this macro. 
  * @note   After enabling the LXT (RCC_LXT_ON or RCC_LXT_BYPASS), the application
  *         software should wait on LXTRDY flag to be set indicating that LXT clock
  *         is stable and can be used to clock the RTC.
  * @param  __STATE__ specifies the new state of the LXT.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_LXT_OFF turn OFF the LXT oscillator, LXTRDY flag goes low after
  *                              6 LXT oscillator clock cycles.
  *            @arg @ref RCC_LXT_ON turn ON the LXT oscillator.
  *            @arg @ref RCC_LXT_BYPASS LXT oscillator bypassed with external clock.
  */
#define __HAL_RCC_LXT_CONFIG(__STATE__)                                     \
                    do{                                                     \
											__HAL_RCC_REGWR_UNLOCK(); 														\
                      if ((__STATE__) == RCC_LXT_ON)                        \
                      {                                                     \
                        SET_BIT(RCC->LXTCR, RCC_LXTCR_LXTEN |RCC_LXTCR_LXTSTARTUP | RCC_LXTCR_LXTPORT_Msk | (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos));    \
                      }                                                     \
                      else if ((__STATE__) == RCC_LXT_OFF)                  \
                      {                                                     \
												CLEAR_WPBIT(RCC->LXTCR, RCC_LXTCR_LXTAON, (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos)); \
												CLEAR_WPBIT(RCC->LXTCR, RCC_LXTCR_LXTEN, (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos));  \
												SET_BIT(RCC->LXTCR, RCC_LXTCR_LXTAON | (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos)); 	 \
											}                                                     \
                      else if ((__STATE__) == RCC_LXT_BYPASS)               \
                      {                                                     \
												CLEAR_WPBIT(RCC->LXTCR, RCC_LXTCR_LXTEN, (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos)); \
                        SET_BIT(RCC->LXTCR, RCC_LXTCR_LXTBYP | (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos));   \
                      }                                                     \
                      else                                                  \
                      {                                                     \
                        CLEAR_WPBIT(RCC->LXTCR, RCC_LXTCR_LXTEN, (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos));  \
												CLEAR_WPBIT(RCC->LXTCR, RCC_LXTCR_LXTBYP, (RCC_KEY_UNLOCK << RCC_SYSCLKCR_KEY_Pos)); \
                      }                                                     \
                      __HAL_RCC_REGWR_LOCK();	  													  \
										}while(0U)

/**
  * @}
  */


/** @defgroup RCC_Get_Clock_source Get Clock source
  * @{   
  */

/**
  * @brief  Macro to configure the system clock source.
  * @param  __SYSCLKSOURCE__ specifies the system clock source.
  *          This parameter can be one of the following values:
  *              @arg @ref RCC_SYSCLKSOURCE_HIRC HIRC is used as system clock source.										
  *              @arg @ref RCC_SYSCLKSOURCE_HXT HXT oscillator is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_LIRC LIRC is used as system clock source.
  *              @arg @ref RCC_SYSCLKSOURCE_LXT LXT oscillator is used as system clock source.
  */
#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__) \
									do{															\
										__HAL_RCC_REGWR_UNLOCK();			\
										WRITE_REG(RCC->SYSCLKSEL, ((__SYSCLKSOURCE__) | (RCC_KEY_UNLOCK << RCC_SYSCLKSEL_KEY_Pos)));\
										__HAL_RCC_REGWR_LOCK();				\
									}while(0)

/** @brief  Macro to get the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following:
  *             @arg @ref RCC_SYSCLKSOURCE_STATUS_HIRC HIRC used as system clock
  *             @arg @ref RCC_SYSCLKSOURCE_STATUS_HXT HXT used as system clock
  *             @arg @ref RCC_SYSCLKSOURCE_STATUS_LIRC LIRC used as system clock
  *             @arg @ref RCC_SYSCLKSOURCE_STATUS_LXT LXT used as system clock	
  */
#define __HAL_RCC_GET_SYSCLK_SOURCE() ((uint32_t)(READ_BIT(RCC->SYSCLKSEL,RCC_SYSCLKSEL_CLKSW)))

/**
  * @}
  */

/** @defgroup RCCEx_MCOx_Clock_Config RCC Extended MCOx Clock Config
  * @{   
  */ 

/** @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_MCOSOURCE_HIRC     HIRC selected as MCO clock
  *            @arg @ref RCC_MCOSOURCE_HXT      HXT selected as MCO clock
  *            @arg @ref RCC_MCOSOURCE_LIRC     LIRC selected as MCO clock
  *            @arg @ref RCC_MCOSOURCE_LXT      LXT selected as MCO clock
  *            @arg @ref RCC_MCOSOURCE_SYSCLK   SYSCLK selected as MCO clock
  *            @arg @ref RCC_MCOSOURCE_HCLK     HCLK selected as MCO clock
  * @param  __MCODIV__ specifies the MCO clock prescaler, only valid when RCC_MCOSOURCE_HCLK 
	*					is selected as __MCOCLKSOURCE__.
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1 No division applied on MCO clock source
  *            @arg @ref value between 1 and 255 represents divide by (2 * __MCODIV__)	
  */
#define __HAL_RCC_MCO_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
                 do{	\
									MODIFY_REG(RCC->MCOCR, (RCC_MCOCR_MCOSEL | RCC_MCOCR_MCODIV), ((__MCOCLKSOURCE__) | (__MCODIV__))); \
								  MODIFY_REG(RCC->MCOCR, RCC_MCOCR_MCOEN, RCC_MCOCR_MCOEN); \
								 }while(0)

/**
  * @}
  */



/** @defgroup RCC_Flags_Management Flags Management
  * @brief macros to manage the specified RCC Flags.
  * @{
  */

/** @brief  Clear the reset flags in RSTSR.
  *            @arg @ref RCC_FLAG_SFTRST    Software reset.
  *            @arg @ref RCC_FLAG_PADRST    Pad reset.
  *            @arg @ref RCC_FLAG_LOCKUPRST CPU Lockup reset.
  *            @arg @ref RCC_FLAG_PORRST    PowerON reset.
  *            @arg @ref RCC_FLAG_LVDRST   	Low Voltage Detect reset.
  *            @arg @ref RCC_FLAG_IWDGRST  	Independent Watchdog reset.
  *            @arg @ref RCC_FLAG_WWDGRST  	Window Watchdog reset.
  *            @arg @ref RCC_FLAG_CPURST   	CPU reset-no option byte reload
  *            @arg @ref RCC_FLAG_MCURST   	MCU reset-option byte reload
  */
#define __HAL_RCC_CLEAR_RESET_FLAGS(__FLAG__) (RCC->RSTSR &= (~((__FLAG__) & RCC_RSTFLAG_MASK)))

/** @brief  Check RCC flag is set or not.
  * @param  __FLAG__ specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_FLAG_HIRCRDY HIRC clock ready.
  *            @arg @ref RCC_FLAG_HXTRDY HXT oscillator clock ready.
  *            @arg @ref RCC_FLAG_LIRCRDY LIRC clock ready.
  *            @arg @ref RCC_FLAG_LXTRDY LXT oscillator clock ready.					 
	***********************************************************************
  *            @arg @ref RCC_FLAG_SFTRST    Software reset.
  *            @arg @ref RCC_FLAG_PADRST    Pad reset.
  *            @arg @ref RCC_FLAG_LOCKUPRST CPU Lockup reset.
  *            @arg @ref RCC_FLAG_PORRST    PowerON reset.
  *            @arg @ref RCC_FLAG_LVDRST   	Low Voltage Detect reset.
  *            @arg @ref RCC_FLAG_IWDGRST  	Independent Watchdog reset.
  *            @arg @ref RCC_FLAG_WWDGRST  	Window Watchdog reset.
  *            @arg @ref RCC_FLAG_CPURST   	CPU reset-no option byte reload
  *            @arg @ref RCC_FLAG_MCURST   	MCU reset-option byte reload
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_RCC_GET_FLAG(__FLAG__)  ((((__FLAG__) >> 16U) == HIRCCR_REG_INDEX)? ((RCC->HIRCCR & RCC_HIRCCR_HIRCRDY) == RCC_HIRCCR_HIRCRDY): \
																			 (((__FLAG__) >> 16U) == HXTCR_REG_INDEX)? ((RCC->HXTCR & RCC_HXTCR_HXTRDY) == RCC_HXTCR_HXTRDY) : \
																			 (((__FLAG__) >> 16U) == LIRCCR_REG_INDEX)? ((RCC->LIRCCR & RCC_LIRCCR_LIRCRDY) == RCC_LIRCCR_LIRCRDY) : \
																			 (((__FLAG__) >> 16U) == LXTCR_REG_INDEX)? ((RCC->LXTCR & RCC_LXTCR_LXTRDY) == RCC_LXTCR_LXTRDY) : \
																			 ((RCC->RSTSR & ((__FLAG__) & RCC_RSTFLAG_MASK)) == ((__FLAG__) & RCC_RSTFLAG_MASK)))
/**
  * @}
  */

/**
  * @}
  */ /* End of group RCC_Exported_Macros */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_Exported_Functions
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct);

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
uint32_t          HAL_RCC_GetSysClockFreq(void);
uint32_t          HAL_RCC_GetHCLKFreq(void);
uint32_t          HAL_RCC_GetPCLKFreq(void);
void              HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct);
void              HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct);

/**
  * @}
  */

/**
  * @} 
  */ /*End of group RCC_Exported_Functions */

/** @addtogroup RCC_Private_Constants
  * @{
  */

/** @defgroup RCC_Timeout RCC Timeout
  * @{
  */ 

/* LXT state change timeout */
#define RCC_LXT_TIMEOUT_VALUE          LXT_STARTUP_TIMEOUT

#define CLOCKSWITCH_TIMEOUT_VALUE      5000    /* 5 s    */
#define HXT_TIMEOUT_VALUE              HXT_STARTUP_TIMEOUT
#define HIRC_TIMEOUT_VALUE              2U      /* 2 ms (minimum Tick + 1) */
#define LIRC_TIMEOUT_VALUE              2U      /* 2 ms (minimum Tick + 1) */

/**
  * @}
  */
  
/* Defines used for Flags */
#define HIRCCR_REG_INDEX                 ((uint32_t)1)
#define HXTCR_REG_INDEX                  ((uint32_t)2)
#define LIRCCR_REG_INDEX                 ((uint32_t)3)
#define LXTCR_REG_INDEX                  ((uint32_t)4)
#define RSTSR_REG_INDEX                  ((uint32_t)5)

#define RCC_RSTFLAG_MASK                 ((uint32_t)0x1FF)

/**
  * @}
  */

/** @addtogroup RCC_Private_Macros
  * @{
  */
#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                           || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HXT) == RCC_OSCILLATORTYPE_HXT) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HIRC) == RCC_OSCILLATORTYPE_HIRC) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LIRC) == RCC_OSCILLATORTYPE_LIRC) || \
                                               (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LXT) == RCC_OSCILLATORTYPE_LXT))
#define IS_RCC_HIRC(__HXT__) 			(((__HXT__) == RCC_HXT_OFF) || ((__HXT__) == RCC_HXT_ON) || \
																	((__HXT__) == RCC_HXT_BYPASS))
#define IS_RCC_LXT(__LSE__) 			(((__LXT__) == RCC_LXT_OFF) || ((__LXT__) == RCC_LXT_ON) || \
																	((__LXT__) == RCC_LXT_BYPASS))
#define IS_RCC_HXT(__HIRC__) 			(((__HIRC__) == RCC_HIRC_OFF) || ((__HXT__) == RCC_HIRC_ON))
#define IS_RCC_CALIBRATION_VALUE	(__VALUE__) ((__VALUE__) <= 0x1FFU)
#define IS_RCC_LIRC(__LIRC__) 		(((__LIRC__) == RCC_LIRC_OFF) || ((__LIRC__) == RCC_LIRC_ON))

#define IS_RCC_CLOCKTYPE(CLK) ((((CLK) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK) || \
                               (((CLK) & RCC_CLOCKTYPE_HCLK)   == RCC_CLOCKTYPE_HCLK)   || \
                               (((CLK) & RCC_CLOCKTYPE_PCLK)  == RCC_CLOCKTYPE_PCLK))
#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_HIRC) || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_HXT)  || \
                                         ((__SOURCE__) == RCC_SYSCLKSOURCE_LIRC) || \
																				 ((__SOURCE__) == RCC_SYSCLKSOURCE_LXT))
#define IS_RCC_HCLK(__HCLK__) 	((__HCLK__) <= 0xFFU)
#define IS_RCC_PCLK(__PCLK__) 	((__PCLK__) <= 0xFFU)
#define IS_RCC_MCO(__MCO__)  		((__MCO__) == RCC_MCO)
#define IS_RCC_MCODIV(__DIV__) 	((__DIV__) <= 0xFFU)

/**
  * @}
  */ /* End of group RCC_Private_Macros*/
 
/**
  * @}
  */ /* End of group RCC */ 

#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_RCC_H */


