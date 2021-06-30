/**
  ******************************************************************************
  * @file    cx32l003_hal_rtc.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of RTC HAL module.
  ****************************************************************************** 
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_RTC_H
#define __CX32L003_HAL_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */ 


/* Exported types ------------------------------------------------------------*/ 
/** @defgroup RTC_Exported_Types RTC Exported Types
  * @{
  */
/** 
  * @brief  RTC Time structure definition  
  */
typedef struct
{
  uint8_t Hours;            /*!< Specifies the RTC Time Hour.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 23 */

  uint8_t Minutes;          /*!< Specifies the RTC Time Minutes.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 59 */
  
  uint8_t Seconds;          /*!< Specifies the RTC Time Seconds.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 59 */
  
}RTC_TimeTypeDef; 

/** 
  * @brief  RTC Date structure definition  
  */
typedef struct
{
  uint8_t WeekDay;  /*!< Specifies the RTC Date WeekDay (not necessary for HAL_RTC_SetDate).
                         This parameter can be a value of @ref RTC_WeekDay_Definitions */
  
  uint8_t Month;    /*!< Specifies the RTC Date Month (in BCD format).
                         This parameter can be a value of @ref RTC_Month_Date_Definitions */

  uint8_t Date;     /*!< Specifies the RTC Date.
                         This parameter must be a number between Min_Data = 1 and Max_Data = 31 */
  
  uint32_t Year;     /*!< Specifies the RTC Date Year.
                         This parameter must be a number between Min_Data = 1900 and Max_Data = 2099 */
                   
}RTC_DateTypeDef;
/** 
  * @brief  RTC ALARM Enable structure definition  
  */
typedef struct
{
	uint32_t Year_Enable;            /*!< Set year or not .
                                      This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
	uint32_t Month_Enable;           /*!< Set month or not .
                                      This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
	uint32_t Date_Enable;            /*!< Set date or not .
                                      This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
	uint32_t WeekDay_Enable;         /*!< Set week or not .
                                      This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
	uint32_t Hours_Enable;         /*!< Set hour or not .
                                      This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
	uint32_t Minutes_Enable;       /*!< Set minute or not .
                                      This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
	uint32_t Seconds_Enable;      /*!< Set second or not .
                                      This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
    
}RTC_AlarmEnableTypeDef;
/** 
  * @brief  RTC Alarm structure definition  
  */
typedef struct
{
	RTC_AlarmEnableTypeDef Alarm_Enable;
	RTC_DateTypeDef Alarm_Date; 
  RTC_TimeTypeDef Alarm_Time;     /*!< Specifies the RTC Alarm Time members */
  uint32_t Alarm;                /*!< Specifies the alarm ID .
                                      This parameter can be a value of @ref RTC_Alarms_Definitions */
}RTC_AlarmTypeDef;
  
/** 
  * @brief  HAL RTC State structures definition  
  */ 
typedef enum
{
  HAL_RTC_STATE_RESET             = 0x00U,  /*!< RTC not yet initialized or disabled */
  HAL_RTC_STATE_READY             = 0x01U,  /*!< RTC initialized and ready for use   */
  HAL_RTC_STATE_BUSY              = 0x02U,  /*!< RTC process is ongoing              */     
  HAL_RTC_STATE_TIMEOUT           = 0x03U,  /*!< RTC timeout state                   */  
  HAL_RTC_STATE_ERROR             = 0x04U   /*!< RTC error state                     */      
                                                                        
}HAL_RTCStateTypeDef;

/** 
  * @brief  HAL RTC alarm2 structures definition  
  */ 
typedef enum
{
  HAL_RTC_ALARM2_CLOSE             = 0x00U,  /*!< RTC ALARM2 disabled */
  HAL_RTC_ALARM2_1S,                  			 /*!< RTC ALARM2 cycle time set 1s   */
  HAL_RTC_ALARM2_1P2S,               				 /*!< RTC ALARM2 cycle time set 1/2s   */     
  HAL_RTC_ALARM2_1P4S,                       /*!< RTC ALARM2 cycle time set 1/4s   */  
  HAL_RTC_ALARM2_1P8S,                       /*!< RTC ALARM2 cycle time set 1/8s   */      
  HAL_RTC_ALARM2_1P16S,                      /*!< RTC ALARM2 cycle time set 1/16s   */      
  HAL_RTC_ALARM2_1P32S,                      /*!< RTC ALARM2 cycle time set 1/32s   */      
  HAL_RTC_ALARM2_1P64S,                      /*!< RTC ALARM2 cycle time set 1/64s   */      
  HAL_RTC_ALARM2_1P128S,                     /*!< RTC ALARM2 cycle time set 1/128s   */      
  HAL_RTC_ALARM2_10S,                        /*!< RTC ALARM2 cycle time set 108s   */      
  HAL_RTC_ALARM2_30S,                        /*!< RTC ALARM2 cycle time set 30s   */
	HAL_RTC_ALARM2_1M,                         /*!< RTC ALARM2 cycle time set 1 MINUTS   */  
  HAL_RTC_ALARM2_30M,                        /*!< RTC ALARM2 cycle time set 30 MINUTS   */    
  HAL_RTC_ALARM2_60M,                        /*!< RTC ALARM2 cycle time set 60 MINUTS   */    
  HAL_RTC_ALARM2_12H,                        /*!< RTC ALARM2 cycle time set 12 HOURS   */ 
  HAL_RTC_ALARM2_24H                         /*!< RTC ALARM2 cycle time set 24 HOURS   */    
               
}HAL_RTCAlarm2TypeDef;

/** 
  * @brief  RTC Init Configuration Structure definition  
  */
typedef struct
{
  uint32_t ClockSource;       /*!< Specifies the RTC clock source
                                 This parameter can be a value of @ref RTC_CLOCK_SOURCE_Definitions*/
  
  uint32_t HourFormat;/*!< Specifies the RTC Hour Formate
                                 This parameter can be a value of @ref RTC_Hour_Formats_Definition*/

  uint32_t TimeAdjustMode;/*!< Specifies the RTC clock source
                                 This parameter can be a value of @ref RTC_TIME_ADJUST_MODE_Definitions*/
  int8_t TimeTrim;/*!< Specifies the RTC clock source
                                 This parameter must be a number between Min_Data = -128 and Max_Data = 127 */

}RTC_InitTypeDef;
  



/** 
  * @brief  Time Handle Structure definition  
  */ 
typedef struct
{
  RTC_TypeDef                 *Instance;  /*!< Register base address    */

  RTC_InitTypeDef             Init;       /*!< RTC required parameters  */ 

  RTC_DateTypeDef             DateToUpdate;       /*!< Current date set by user and updated automatically  */ 

  HAL_LockTypeDef             Lock;       /*!< RTC locking object       */

  __IO HAL_RTCStateTypeDef    State;      /*!< Time communication state */

}RTC_HandleTypeDef;

/**
  * @}
  */ 

/* Exported constants --------------------------------------------------------*/
/** @defgroup RTC_Exported_Constants RTC Exported Constants
  * @{
  */ 
/** @defgroup RTC_WRITE_PROTECT_KEY  write KEY before write to register
  * @{
  */ 
#define RTC_WRITE_PROTECT_KEY1                      0xCAU
#define RTC_WRITE_PROTECT_KEY2                      0x53U

/**
  * @}
  */ 
/** @defgroup RTC_Hour_Formats_Definitions RTC Hour Formats
  * @{
  */
#define RTC_HOURFORMAT_24                   RTC_CR_FMT
#define RTC_HOURFORMAT_12                   0x00000000U
/**
  * @}
  */
/** @defgroup RTC_AM_PM_Definitions RTC AM PM Definitions
  * @{
  */
#define RTC_HOURFORMAT12_AM                 ((uint8_t)0x00U)
#define RTC_HOURFORMAT12_PM                 ((uint8_t)0x40U)
/**
  * @}
  */
	/** @defgroup RTC_TIME_ADJUST_MODE_Definitions RTC time adjust mode Definitions
  * @{
  */
#define RTC_TIME_ADJUST_SEC60                 (0x0000U)
#define RTC_TIME_ADJUST_SEC30                 (0x0100U)
#define RTC_TIME_ADJUST_SEC15                 (0x0200U)
#define RTC_TIME_ADJUST_SEC06                 (0x0300U)
/**
  * @}
  */
	/** @defgroup RTC_CLOCK_SOURCE_Definitions RTC CLOCK Source Definitions
  * @{
  */
#define RTC_CLOCK_LXT                 			(0x00UL<<RTC_CLKCR_RTCCKSEL_Pos)
#define RTC_CLOCK_LIRC                 			(0x01UL<<RTC_CLKCR_RTCCKSEL_Pos)
#define RTC_CLOCK_HXT                 			(0x02UL<<RTC_CLKCR_RTCCKSEL_Pos)

/**
  * @}
  */
#define RTC_BYPASS_HAD_MAX                      (0x08U)
/** @defgroup RTC_Automatic_Prediv_1_Second Automatic calculation of prediv for 1sec timebase
  * @{
  */ 
#define RTC_AUTO_1_SECOND                      0xFFFFFFFFU

/**
  * @}
  */
#define RTC_BCD_TO_BYTE_MASK                            0XFFU

/** @defgroup RTC_Month_Date_Definitions Month Definitions
  * @{
  */ 

/* Coded in BCD format */
#define RTC_MONTH_JANUARY              ((uint8_t)0x01)
#define RTC_MONTH_FEBRUARY             ((uint8_t)0x02)
#define RTC_MONTH_MARCH                ((uint8_t)0x03)
#define RTC_MONTH_APRIL                ((uint8_t)0x04)
#define RTC_MONTH_MAY                  ((uint8_t)0x05)
#define RTC_MONTH_JUNE                 ((uint8_t)0x06)
#define RTC_MONTH_JULY                 ((uint8_t)0x07)
#define RTC_MONTH_AUGUST               ((uint8_t)0x08)
#define RTC_MONTH_SEPTEMBER            ((uint8_t)0x09)
#define RTC_MONTH_OCTOBER              ((uint8_t)0x10)
#define RTC_MONTH_NOVEMBER             ((uint8_t)0x11)
#define RTC_MONTH_DECEMBER             ((uint8_t)0x12)

/**
  * @}
  */ 

/** @defgroup RTC_WeekDay_Definitions WeekDay Definitions 
  * @{
  */ 
#define RTC_WEEKDAY_MONDAY             ((uint8_t)0x01)
#define RTC_WEEKDAY_TUESDAY            ((uint8_t)0x02)
#define RTC_WEEKDAY_WEDNESDAY          ((uint8_t)0x03)
#define RTC_WEEKDAY_THURSDAY           ((uint8_t)0x04)
#define RTC_WEEKDAY_FRIDAY             ((uint8_t)0x05)
#define RTC_WEEKDAY_SATURDAY           ((uint8_t)0x06)
#define RTC_WEEKDAY_SUNDAY             ((uint8_t)0x00)

/**
  * @}
  */ 
/** @defgroup RTC_AlarmEnable_Definitions  alarm enable Definitions 
  * @{
  */ 
#define RTC_ALARM_DISABLE             		((uint8_t)0x00)
#define RTC_ALARM_YEAR_ENABLE          		RTC_ALM1DATE_ALMYEAREN
#define RTC_ALARM_MONTH_ENABLE          	RTC_ALM1DATE_ALMMONEN
#define RTC_ALARM_DATE_ENABLE           	RTC_ALM1DATE_ALMDAYEN
#define RTC_ALARM_WEEK_ENABLE             	RTC_ALM1DATE_ALMWEEKEN
#define RTC_ALARM_HOURS_ENABLE           	RTC_ALM1DATE_ALMHOUREN
#define RTC_ALARM_MINUTES_ENABLE          RTC_ALM1DATE_ALMMINEN
#define RTC_ALARM_SECONDS_ENABLE          RTC_ALM1DATE_ALMSECEN
#define RTC_ALARM_ENABLE            			RTC_CR_ALM1EN


/**
  * @}
  */ 
/** @defgroup RTC_Alarms_Definitions Alarms Definitions 
  * @{
  */ 
#define RTC_ALARM_1                        0x00U                               
#define RTC_ALARM_2                        0x01U                                 


/**
  * @}
  */ 


/** @defgroup RTC_output_source_to_output_on_the_Tamper_pin Output source to output on the Tamper pin
  * @{
  */

#define RTC_OUTPUTSOURCE_NONE               0x00000000U                       /*!< No output on the TAMPER pin  */
#define RTC_OUTPUTSOURCE_CALIBCLOCK         BKP_RTCCR_CCO                     /*!< RTC clock with a frequency divided by 64 on the TAMPER pin  */
#define RTC_OUTPUTSOURCE_ALARM              BKP_RTCCR_ASOE                    /*!< Alarm pulse signal on the TAMPER pin  */
#define RTC_OUTPUTSOURCE_SECOND             (BKP_RTCCR_ASOS | BKP_RTCCR_ASOE) /*!< Second pulse signal on the TAMPER pin  */

/**
  * @}
  */

/** @defgroup RTC_Interrupts_Definitions Interrupts Definitions 
  * @{
  */ 
#define RTC_IT_OW            RTC_CRH_OWIE       /*!< Overflow interrupt */
#define RTC_IT_ALRA          RTC_CRH_ALRIE      /*!< Alarm interrupt */
#define RTC_IT_SEC           RTC_CRH_SECIE      /*!< Second interrupt */
#define RTC_IT_TAMP1         BKP_CSR_TPIE       /*!< TAMPER Pin interrupt enable */  
/**
  * @}
  */

/** @defgroup RTC_Flags_Definitions Flags Definitions 
  * @{
  */ 
#define RTC_FLAG_RTOFF       RTC_CRL_RTOFF      /*!< RTC Operation OFF flag */
#define RTC_FLAG_RSF         RTC_CRL_RSF        /*!< Registers Synchronized flag */
#define RTC_FLAG_OW          RTC_CRL_OWF        /*!< Overflow flag */
#define RTC_FLAG_ALRAF       RTC_CRL_ALRF       /*!< Alarm flag */
#define RTC_FLAG_SEC         RTC_CRL_SECF       /*!< Second flag */
#define RTC_FLAG_TAMP1F      BKP_CSR_TEF        /*!< Tamper Interrupt Flag */

/**
  * @}
  */

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RTC_Exported_macros RTC Exported Macros
  * @{
  */
/**
  * @brief Enter RTC  read/write mode .
  * @retval None.
  */									   
	                                            
#define __HAL_RTC_ENTER_RW(__HANDLE__)									\
do{																											\
		RTC_Disable_Write_Protected(__HANDLE__);						\
		SET_BIT((__HANDLE__)->Instance->ISR, RTC_ISR_WAIT);	\
		} while(0U)
 
 
/**
  * @brief Exit RTC  read/write mode.
  * @retval None.
  */

#define __HAL_RTC_EXIT_RW(__HANDLE__)    										\
do{  																												\
		RTC_Disable_Write_Protected(__HANDLE__); 							\
		CLEAR_BIT((__HANDLE__)->Instance->ISR, RTC_ISR_WAIT); \
	} while(0U)


/**
  * @brief Get WAITF Status .
  * @retval None.
  */
#define __HAL_RTC_GET_WAITF_STATUS(__HANDLE__)    ((READ_BIT((__HANDLE__)->Instance->ISR, RTC_ISR_WAITF) == RTC_ISR_WAITF)? SET : RESET)
											   

/**
  * @brief Enable RTC .
  * @retval None.
  */

#define __HAL_RTC_ENABLE(__HANDLE__)    						\
do{  																								\
		RTC_Disable_Write_Protected(__HANDLE__); 					\
		SET_BIT((__HANDLE__)->Instance->CR, RTC_CR_START); \
	} while(0U)

/**
  * @brief Disable RTC .
  * @retval None.
  */

#define __HAL_RTC_DISABLE(__HANDLE__)						\
do{																							\
		RTC_Disable_Write_Protected(__HANDLE__);		\
		CLEAR_BIT((__HANDLE__)->Instance->CR, RTC_CR_START);	\
	}	while(0U)

/**
  * @brief Enable RTC Alm1.
  * @retval None.
  */

#define __HAL_RTC_ENABLE_ALM1(__HANDLE__)											\
do{																															\
		RTC_Disable_Write_Protected(__HANDLE__); 										\
		SET_BIT((__HANDLE__)->Instance->CR, RTC_CR_ALM1EN); 	\
	}	while(0U)

/**
  * @brief Disable RTC ALM1.
  * @retval None.
  */
																					
#define __HAL_RTC_DISABLE_ALM1(__HANDLE__)										\
do{  \
		RTC_Disable_Write_Protected(__HANDLE__); \
		CLEAR_BIT((__HANDLE__)->Instance->CR, RTC_CR_ALM1EN); \
	} while(0U)

/**
  * @brief Enable RTC Clock.
  * @retval None.
  */
#define __HAL_RTC_ENABLE_CLOCK(__HANDLE__)										\
do{																														\
		RTC_Disable_Write_Protected(__HANDLE__);									\
		SET_BIT((__HANDLE__)->Instance->CLKCR, RTC_CLKCR_RTCCKEN); \
	}	while(0U)


/**
  * @brief Disable RTC Clock.
  * @retval None.
  */
#define __HAL_RTC_DISABLE_CLOCK(__HANDLE__)											\
do{																															\
		RTC_Disable_Write_Protected(__HANDLE__);										\
		CLEAR_BIT((__HANDLE__)->Instance->CLKCR, RTC_CLKCR_RTCCKEN); \
	}	while(0U)

	
/**
  * @}
  */
	
	
/** @addtogroup RTC_Private_Macros
  * @{
  */

#define IS_RTC_ASYNCH_PREDIV(PREDIV)  (((PREDIV) <= 0xFFFFFU) || ((PREDIV) == RTC_AUTO_1_SECOND))
#define IS_RTC_HOUR24(HOUR)           ((HOUR) <= 23U)
#define IS_RTC_MINUTES(MINUTES)       ((MINUTES) <= 59U)
#define IS_RTC_SECONDS(SECONDS)       ((SECONDS) <= 59U)
#define IS_RTC_FORMAT(FORMAT)         (((FORMAT) == RTC_FORMAT_BIN) || ((FORMAT) == RTC_FORMAT_BCD))
#define IS_RTC_YEAR(YEAR)             ((YEAR) >= 1900U) &&(YEAR) <= 2099U)
#define IS_RTC_MONTH(MONTH)           (((MONTH) >= 1U) && ((MONTH) <= 12U))
#define IS_RTC_DATE(DATE)             (((DATE) >= 1U) && ((DATE) <= 31U))
#define IS_RTC_WEEKDAY(WEEKDAY)       (((WEEKDAY) >= RTC_WEEKDAY_SUNDAY) && ((WEEKDAY) <= RTC_WEEKDAY_SATURDAY))
#define IS_RTC_ALARM(ALARM)           ((ALARM) == RTC_ALARM_1) || (ALARM) == RTC_ALARM_2))
#define IS_RTC_CALIB_OUTPUT(__OUTPUT__) (((__OUTPUT__) == RTC_OUTPUTSOURCE_NONE) || \
                                         ((__OUTPUT__) == RTC_OUTPUTSOURCE_CALIBCLOCK) || \
                                      ((__OUTPUT__) == RTC_OUTPUTSOURCE_ALARM) || \
                                         ((__OUTPUT__) == RTC_OUTPUTSOURCE_SECOND)) 

#define IS_RTC_ALL_INSTANCE(INSTANCE)			(INSTANCE == RTC)
#define IS_RTC_CLOCK_SOURCE(SOURCE)				((SOURCE == RTC_CLOCK_LXT)	\
																						|| (SOURCE == RTC_CLOCK_LIRC) || (SOURCE == RTC_CLOCK_HXT))
#define IS_RTC_HOUR_FORMAT(FORMAT)				((FORMAT == RTC_HOURFORMAT_12) || (FORMAT == RTC_HOURFORMAT_24))
#define IS_RTC_TIME_ADJUST_MODE(MODE)				((MODE == RTC_TIME_ADJUST_SEC60) || (MODE == RTC_TIME_ADJUST_SEC30)	\
																							(MODE == RTC_TIME_ADJUST_SEC15) || (MODE == RTC_TIME_ADJUST_SEC06))
#define IS_RTC_TIME_TRIM(TRIM)				((TRIM > (int8_t)(-128)) && (TRIM < (int8_t)(127)))
/**
  * @}
  */	
/* Exported functions --------------------------------------------------------*/
/** @addtogroup RTC_Exported_Functions
  * @{
  */


/* Initialization and de-initialization functions  ****************************/
/** @addtogroup RTC_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_RTC_Init(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTC_DeInit(RTC_HandleTypeDef *hrtc);
void              HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc);
void              HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */
  
/* RTC Time and Date functions ************************************************/
/** @addtogroup RTC_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_RTC_SetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_SetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate);
HAL_StatusTypeDef HAL_RTC_SetTime_SetDate(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Hour_Format, RTC_DateTypeDef *sDate);
HAL_StatusTypeDef HAL_RTC_GetTime_Date(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate);

FlagStatus RTC_Get_RSF_Flag(void);
void RTC_Clear_RSF_Flag(void);

//HAL_StatusTypeDef HAL_RTC_GetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate);

/**
  * @}
  */

/* RTC Alarm functions ********************************************************/
/** @addtogroup RTC_Exported_Functions_Group3
  * @{
  */
 HAL_StatusTypeDef HAL_RTC_Alarm1_SetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime);
 HAL_StatusTypeDef HAL_RTC_Alarm1_SetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate);
 HAL_StatusTypeDef HAL_RTC_Alarm1_GetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime);
 HAL_StatusTypeDef HAL_RTC_Alarm1_GetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate);

HAL_StatusTypeDef HAL_RTC_Alarm1_Set_INT_Source(RTC_HandleTypeDef* hrtc, RTC_AlarmEnableTypeDef *AlarmEn);
HAL_StatusTypeDef HAL_RTC_Alarm_INT_Config(RTC_HandleTypeDef *hrtc, uint32_t Alarm, FunctionalState NewState);
HAL_StatusTypeDef HAL_RTC_Alarm1_Config(RTC_HandleTypeDef *hrtc,FunctionalState NewState);
HAL_StatusTypeDef HAL_RTC_Alarm2_Config(RTC_HandleTypeDef *hrtc,FunctionalState NewState, HAL_RTCAlarm2TypeDef CycleTime);

FlagStatus HAL_RTC_Alarm_Get_Flag(uint32_t Alarm);
void HAL_RTC_Alarm_Clear_Flag(uint32_t Alarm);

/**
  * @}
  */

/* Peripheral State functions *************************************************/
/** @addtogroup RTC_Exported_Functions_Group4
  * @{
  */
 HAL_StatusTypeDef HAL_RTC_1HZ_Config(RTC_HandleTypeDef *hrtc,FunctionalState NewState);
HAL_RTCStateTypeDef HAL_RTC_GetState(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */


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

#endif /* __CX32L003_HAL_RTC_H */
