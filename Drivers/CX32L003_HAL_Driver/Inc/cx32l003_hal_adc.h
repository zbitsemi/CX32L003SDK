
/**
  ******************************************************************************
  * @file    cx32l003_hal_adc.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of ADC HAL module.
  ******************************************************************************
 **/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_ADC_H
#define __CX32L003_HAL_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"  
/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup ADC_Exported_Types ADC Exported Types
  * @{
  */

/** 
  * @brief  Structure definition of ADC initialization 
  * @note   The setting of these parameters with function HAL_ADC_Init() is conditioned to ADC state.
  *         ADC can be either disabled or enabled without conversion on going on regular group.
  */
typedef struct
{
	uint32_t SamplingTime;							/*!< Specifies ADC sample time.
																					 This parameter can be a value of @ref ADC_SampleDuty */		
	
  uint32_t SingleChannelSel;          /*!< Specifies ADC channel select in single conversion mode.
																					 This parameter can be a value of @ref ADC_SingleChannelSel */
	
	uint32_t ClkSel;										/*!< Specifies ADC clock select.
																					 This parameter can be a value of @ref ADC_ClkSel */
	
  uint32_t SingleContinueMode;				/*!< Specifies ADC single/continue converstion mode select.
																					 This parameter can be a value of @ref ADC_SingleContinueMode */		
		
  uint32_t AutoAccumulation;					/*!< Specifies ADC conversion result auto accumulation.
																					 This parameter can be a value of @ref ADC_AutoAccumulation */		
				
  uint32_t CircleMode;								/*!< Specifies whether the conversion is performed in circle mode or normal mode for multichannel
																					 This parameter can be a value of @ref ADC_CircleMode */		
		
  uint32_t NbrOfConversion;       		/*!< Specifies the number of conversions in continue mode.	
																					 This parameter can be a value between 0x00 to 0xff */	
		
  uint32_t ContinueChannelSel;     		/*!< Specifies channels to be converted in multchannel conversion mode.
																					 This parameter can be a value of @ref ADC_ContinueChannelSel */		
		
  uint32_t ExternalTrigConv1;      		/*!< Selects the external interrupt 1 used to trigger the conversion.
																					 If set to ADC_SOFTWARE_START, external triggers are disabled.
																					 If set to external trigger source, triggering is on interrupt flag rising edge.
																					 This parameter can be a value of @ref ADC_External_trigger_source1 */
																					 
  uint32_t ExternalTrigConv2;      		/*!< Selects the external interrupt 2 used to trigger the conversion.
																					 If set to ADC_SOFTWARE_START, external triggers are disabled.
																					 If set to external trigger source, triggering is on interrupt flag rising edge.
																					 This parameter can be a value of @ref ADC_External_trigger_source2 */																					 
																					 
}ADC_InitTypeDef;

/** 
  * @brief  Structure definition of ADC channel for regular group   
  * @note   The setting of these parameters with function HAL_ADC_ConfigChannel() is conditioned to ADC state.
  *         ADC can be either disabled or enabled without conversion on going on regular group.
  */ 
typedef struct 
{
  uint32_t SingleChannelSel;          /*!< Specifies ADC channel select in single conversion mode.
																					 This parameter can be a value of @ref ADC_SingleChannelSel */
	
	uint32_t SamplingTime;							/*!< Specifies ADC sample time.
																					 This parameter can be a value of @ref ADC_SampleDuty */		
	
	uint32_t ClkSel;										/*!< Specifies ADC clock select.
																					 This parameter can be a value of @ref ADC_ClkSel */
}ADC_ChannelConfTypeDef;

/**
  * @brief  ADC Configuration threshold definition
  * @note   The setting of these parameters with function is conditioned to ADC state.
  */
typedef struct
{
  uint32_t CompareMode;								/*!< Specifies ADC threshold compare mode.
																					 This parameter can be a value of @ref ADC_CompareMode */		
  
	uint32_t ITMode;            				/*!< Specifies whether out of threshold is configured in interrupt or polling mode.
																						This parameter can be set to ENABLE or DISABLE */
  
	uint32_t HighThreshold;							/*!< Specifies ADC high level threshold.
																					  This parameter can be a value between 0x0000 to 0x0fff */
	
  uint32_t LowThreshold;							/*!< Specifies ADC low level threshold.
																					  This parameter can be a value between 0x0000 to 0x0fff */	
}ADC_ThresholdConfTypeDef;

/** 
  * @brief  HAL ADC state machine: ADC states definition (bitfields)
  */ 
/* States of ADC global scope */
#define HAL_ADC_STATE_RESET             0x00000000U    /*!< ADC not yet initialized or disabled */
#define HAL_ADC_STATE_READY             0x00000001U    /*!< ADC peripheral ready for use */
#define HAL_ADC_STATE_BUSY_INTERNAL     0x00000002U    /*!< ADC is busy to internal process (initialization, calibration) */
#define HAL_ADC_STATE_TIMEOUT           0x00000004U    /*!< TimeOut occurrence */

/* States of ADC errors */
#define HAL_ADC_STATE_ERROR_INTERNAL    0x00000010U    /*!< Internal error occurrence */
#define HAL_ADC_STATE_ERROR_CONFIG      0x00000020U    /*!< Configuration error occurrence */

/* States of ADC conversion */
#define HAL_ADC_STATE_BUSY          		0x00000100U    /*!< A conversion is ongoing (either by continuous mode, external trigger) */
#define HAL_ADC_STATE_EOC           		0x00000200U    /*!< Conversion data available */

/* States of ADC value out of range */
#define HAL_ADC_STATE_OUTRANGE          0x00010000U    /*!< Out-of-range occurrence defined by user */


/** 
  * @brief  ADC handle Structure definition  
  */ 
typedef struct
{
  ADC_TypeDef                   *Instance;              /*!< Register base address */

  ADC_InitTypeDef               Init;                   /*!< ADC required parameters */

  HAL_LockTypeDef               Lock;                   /*!< ADC locking object */
  
  __IO uint32_t                 State;                  /*!< ADC communication state (bitmap of ADC states) */

  __IO uint32_t                 ErrorCode;              /*!< ADC Error code */
}ADC_HandleTypeDef;
/**
  * @}
  */



/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants ADC Exported Constants
  * @{
  */


/** @defgroup ADC_Error_Code ADC Error Code
  * @{
  */
#define HAL_ADC_ERROR_NONE                0x00U   /*!< No error                                              */
#define HAL_ADC_ERROR_INTERNAL            0x01U   /*!< ADC IP internal error: if problem of clocking, 
                                                       enable/disable, erroneous state                       */

/**
  * @}
  */


/** @defgroup ADC_SampleDuty ADC Sample duty cycle
  * @{
  */
#define ADC_SAMPLE_4CYCLE            0x00U   				/*!< ADC Sample 4 cycles           */
#define ADC_SAMPLE_8CYCLE            ADC_CR0_SAM   	/*!< ADC Sample 8 cycles  					*/

/**
  * @}
  */


/** @defgroup ADC_SingleChannelSel ADC channel select
  * @{
  */
#define ADC_SINGLE_CHANNEL_0            	(0x00000000U)   																		/*!< Select ADC channel 0 in single mode           */
#define ADC_SINGLE_CHANNEL_1            	(ADC_CR0_SEL_0)   																	/*!< Select ADC channel 1 in single mode  				 */
#define ADC_SINGLE_CHANNEL_2            	(ADC_CR0_SEL_1)   																	/*!< Select ADC channel 2 in single mode           */
#define ADC_SINGLE_CHANNEL_3            	(ADC_CR0_SEL_1 | ADC_CR0_SEL_0)   									/*!< Select ADC channel 3 in single mode  				 */
#define ADC_SINGLE_CHANNEL_4            	(ADC_CR0_SEL_2)   																	/*!< Select ADC channel 4 in single mode           */
#define ADC_SINGLE_CHANNEL_5            	(ADC_CR0_SEL_2 | ADC_CR0_SEL_0)   									/*!< Select ADC channel 5 in single mode  				 */
#define ADC_SINGLE_CHANNEL_6            	(ADC_CR0_SEL_2 | ADC_CR0_SEL_1)   									/*!< Select ADC channel 6 in single mode           */
#define ADC_SINGLE_CHANNEL_7            	(ADC_CR0_SEL_2 | ADC_CR0_SEL_1 | ADC_CR0_SEL_0)   	/*!< Select ADC channel 7(VCAP)	in single mode 	 	 */

/**
  * @}
  */


/** @defgroup ADC_ClkSel ADC clock selection
  * @{
  */
#define ADC_CLOCK_PCLK_DIV1         			(0x00000000U)   																					/*!< Select ADC clock PCLK          */
#define ADC_CLOCK_PCLK_DIV2         			(ADC_CR0_CLKSEL_0)   																			/*!< Select ADC clock PCLK/2  			*/
#define ADC_CLOCK_PCLK_DIV4           		(ADC_CR0_CLKSEL_1)   																			/*!< Select ADC clock PCLK/4        */
#define ADC_CLOCK_PCLK_DIV8           		(ADC_CR0_CLKSEL_1 | ADC_CR0_CLKSEL_0)   									/*!< Select ADC clock PCLK/8  			*/
#define ADC_CLOCK_PCLK_DIV16          		(ADC_CR0_CLKSEL_2)   																			/*!< Select ADC clock PCLK/16       */
#define ADC_CLOCK_PCLK_DIV32          		(ADC_CR0_CLKSEL_2 | ADC_CR0_CLKSEL_0)   									/*!< Select ADC clock PCLK/32  			*/
#define ADC_CLOCK_PCLK_DIV64          		(ADC_CR0_CLKSEL_2 | ADC_CR0_CLKSEL_1)   									/*!< Select ADC clock PCLK/64       */
#define ADC_CLOCK_PCLK_DIV128         		(ADC_CR0_CLKSEL_2 | ADC_CR0_CLKSEL_1 | ADC_CR0_CLKSEL_0)  /*!< Select ADC clock PCLK/128		 	*/

/**
  * @}
  */


/** @defgroup ADC_SingleContinueMode ADC single/continue mode selection
  * @{
  */
#define ADC_MODE_SINGLE         					(0x00000000U)   																					/*!< Select ADC single mode          */
#define ADC_MODE_CONTINUE         				(ADC_CR1_CT)   																						/*!< Select ADC continue mode  			 */

/**
  * @}
  */


/** @defgroup ADC_CompareMode ADC conversion value compared with threshold value ADC_HT/ADC_LT
  * @{
  */
#define ADC_COMP_THRESHOLD_NONE						(0x00000000)																					/*!< Disable Comparation with threshold */	
#define ADC_COMP_THRESHOLD_HIGH         	(ADC_CR1_HTCMP)   																		/*!< Compare with high threshold       */
#define ADC_COMP_THRESHOLD_LOW         		(ADC_CR1_LTCMP)   																		/*!< Compare with low threshold  			 */
#define ADC_COMP_THRESHOLD_RANGE					(ADC_CR1_REGCMP)																			/*!< Compare with range threshold  		 */

/**
  * @}
  */


/** @defgroup ADC_AutoAccumulation ADC conversion results are auto accmulated in ADC_RESULT_ACC register
  * @{
  */
#define ADC_AUTOACC_DISABLE 							(0x00000000U) 
#define ADC_AUTOACC_ENABLE         				(ADC_CR1_RACC_EN)   																		/*!< Auto accumulation enable       */

/**
  * @}
  */


/** @defgroup ADC_CircleMode ADC multichannel conversion mode selection: circle/non-circle
  * @{
  */
#define ADC_MULTICHANNEL_NONCIRCLE 				(0x00000000U) 
#define ADC_MULTICHANNEL_CIRCLE         	(ADC_CR2_CIRCLE_MODE)   																/*!< ADC multichannel conversion circle mode   */

/**
  * @}
  */


/** @defgroup ADC_ContinueChannelSel ADC multichannel conversion channels selection
  * @{
  */
#define ADC_CONTINUE_CHANNEL_0            					(ADC_CR2_CHEN_0)   														/*!< Select ADC channel 0 in continue mode          */
#define ADC_CONTINUE_CHANNEL_1            					(ADC_CR2_CHEN_1)   														/*!< Select ADC channel 1 in continue mode 				 	*/
#define ADC_CONTINUE_CHANNEL_2            					(ADC_CR2_CHEN_2)   														/*!< Select ADC channel 2 in continue mode          */
#define ADC_CONTINUE_CHANNEL_3            					(ADC_CR2_CHEN_3)   														/*!< Select ADC channel 3 in continue mode 				 	*/
#define ADC_CONTINUE_CHANNEL_4            					(ADC_CR2_CHEN_4)   														/*!< Select ADC channel 4 in continue mode          */
#define ADC_CONTINUE_CHANNEL_5            					(ADC_CR2_CHEN_5)   														/*!< Select ADC channel 5 in continue mode 				 	*/
#define ADC_CONTINUE_CHANNEL_6            					(ADC_CR2_CHEN_6)   														/*!< Select ADC channel 6 in continue mode          */
#define ADC_CONTINUE_CHANNEL_7            					(ADC_CR2_CHEN_7)   														/*!< Select ADC channel 7(VCAP) in continue mode		*/

/**
  * @}
  */


/** @defgroup ADC_interrupts_definition ADC interrupts definition
  * @{
  */
#define ADC_IT_CONTINUE           									ADC_INTEN_CONT_IEN        /*!< ADC End of Continue Conversion interrupt source */
#define ADC_IT_RANGE_THRESHOLD          						ADC_INTEN_REG_IEN       	/*!< ADC conversion data in defined range interrupt source */
#define ADC_IT_HIGH_THRESHOLD     									ADC_INTEN_HHT_IEN        	/*!< ADC conversion data above threshold interrupt source */
#define ADC_IT_LOW_THRESHOLD												ADC_INTEN_LLT_IEN					/*!< ADC conversion data below threshold interrupt source */
#define ADC_IT_CHANNEL7															ADC_INTEN_ADCXIEN_7				/*!< ADC End of channel7 conversion interrupt source */
#define ADC_IT_CHANNEL6															ADC_INTEN_ADCXIEN_6				/*!< ADC End of channel6 conversion interrupt source */
#define ADC_IT_CHANNEL5															ADC_INTEN_ADCXIEN_5				/*!< ADC End of channel5 conversion interrupt source */
#define ADC_IT_CHANNEL4															ADC_INTEN_ADCXIEN_4				/*!< ADC End of channel4 conversion interrupt source */
#define ADC_IT_CHANNEL3															ADC_INTEN_ADCXIEN_3				/*!< ADC End of channel3 conversion interrupt source */
#define ADC_IT_CHANNEL2															ADC_INTEN_ADCXIEN_2				/*!< ADC End of channel2 conversion interrupt source */
#define ADC_IT_CHANNEL1															ADC_INTEN_ADCXIEN_1				/*!< ADC End of channel1 conversion interrupt source */
#define ADC_IT_CHANNEL0															ADC_INTEN_ADCXIEN_0				/*!< ADC End of channel0 conversion interrupt source */

/**
  * @}
  */


/** @defgroup ADC_raw_intflags_definition ADC raw interrupt flags definition
  * @{
  */	
#define ADC_RAWINTFLAG_CONTINUE       							ADC_RAWINTSR_CONT_INTF		/*!< ADC End of Continue Conversion raw interrupt flag */
#define ADC_RAWINTFLAG_RANGE_THRESHOLD							ADC_RAWINTSR_REG_INTF			/*!< ADC conversion data in defined range raw interrupt flag */
#define ADC_RAWINTFLAG_HIGH_THRESHOLD 							ADC_RAWINTSR_HHT_INTF			/*!< ADC conversion data above threshold raw interrupt flag */
#define ADC_RAWINTFLAG_LOW_THERSHOLD								ADC_RAWINTSR_LLT_INTF			/*!< ADC conversion data below threshold raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL7											ADC_RAWINTSR_ADCRIS_7			/*!< ADC End of channel7 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL6											ADC_RAWINTSR_ADCRIS_6			/*!< ADC End of channel6 conversion raw interrupt flag */		
#define ADC_RAWINTFLAG_CHANNEL5											ADC_RAWINTSR_ADCRIS_5			/*!< ADC End of channel5 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL4											ADC_RAWINTSR_ADCRIS_4			/*!< ADC End of channel4 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL3											ADC_RAWINTSR_ADCRIS_3			/*!< ADC End of channel3 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL2											ADC_RAWINTSR_ADCRIS_2			/*!< ADC End of channel2 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL1											ADC_RAWINTSR_ADCRIS_1			/*!< ADC End of channel1 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL0											ADC_RAWINTSR_ADCRIS_0			/*!< ADC End of channel0 conversion raw interrupt flag */
	
/**
  * @}
  */


/** @defgroup ADC_intflags_definition ADC interrupt flags definition
  * @{
  */	
#define ADC_INTFLAG_CONTINUE       									ADC_MSKINTSR_CONT_MIF			/*!< ADC End of Continue Conversion interrupt flag */
#define ADC_INTFLAG_RANGE_THRESHOLD									ADC_MSKINTSR_REG_MIF			/*!< ADC conversion data in defined range interrupt flag */
#define ADC_INTFLAG_HIGH_THRESHOLD 									ADC_MSKINTSR_HHT_MIF			/*!< ADC conversion data above threshold interrupt flag */
#define ADC_INTFLAG_LOW_THERSHOLD										ADC_MSKINTSR_LLT_MIF			/*!< ADC conversion data below threshold interrupt flag */
#define ADC_INTFLAG_CHANNEL7												ADC_MSKINTSR_ADCMIS_7			/*!< ADC End of channel7 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL6												ADC_MSKINTSR_ADCMIS_6			/*!< ADC End of channel6 conversion interrupt flag */		
#define ADC_INTFLAG_CHANNEL5												ADC_MSKINTSR_ADCMIS_5			/*!< ADC End of channel5 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL4												ADC_MSKINTSR_ADCMIS_4			/*!< ADC End of channel4 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL3												ADC_MSKINTSR_ADCMIS_3			/*!< ADC End of channel3 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL2												ADC_MSKINTSR_ADCMIS_2			/*!< ADC End of channel2 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL1												ADC_MSKINTSR_ADCMIS_1			/*!< ADC End of channel1 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL0												ADC_MSKINTSR_ADCMIS_0			/*!< ADC End of channel0 conversion interrupt flag */

#define ADC_INTFLAG_CHANNEL_ALL											(ADC_INTFLAG_CHANNEL0 | ADC_INTFLAG_CHANNEL1 | ADC_INTFLAG_CHANNEL2 | ADC_INTFLAG_CHANNEL3 | \
																										ADC_INTFLAG_CHANNEL4 | ADC_INTFLAG_CHANNEL5 | ADC_INTFLAG_CHANNEL6 | ADC_INTFLAG_CHANNEL7)
/**
  * @}
  */



/** @defgroup ADC_External_trigger_source1 ADC external trigger source 1 select
  * @{
  */	
#define ADC_SOFTWARE_START       										(0x00000000U) 							
#define ADC_EXTTRIG1_TIM10													(																																			 					ADC_CR1_TRIGS0_0)							
#define ADC_EXTTRIG1_TIM11 													(																														ADC_CR1_TRIGS0_1 								 		)			
#define ADC_EXTTRIG1_TIM1														(																														ADC_CR1_TRIGS0_1 |	ADC_CR1_TRIGS0_0)		
#define ADC_EXTTRIG1_LPTIM													(																				ADC_CR1_TRIGS0_2																	 			)
#define ADC_EXTTRIG1_TIM1_TRGO											(																				ADC_CR1_TRIGS0_2	|								 			ADC_CR1_TRIGS0_0)	
#define ADC_EXTTRIG1_TIM2_TRGO											(																				ADC_CR1_TRIGS0_2	|	ADC_CR1_TRIGS0_1 								 		)	
#define ADC_EXTTRIG1_TIM2_INT												(																				ADC_CR1_TRIGS0_2	|	ADC_CR1_TRIGS0_1	| ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_UART0_INT											(										ADC_CR1_TRIGS0_3																										 				)
#define ADC_EXTTRIG1_UART1_INT											(										ADC_CR1_TRIGS0_3	|																		 			ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_LPUART_INT											(										ADC_CR1_TRIGS0_3	|										ADC_CR1_TRIGS0_1								 			)
#define ADC_EXTTRIG1_VC0_INT												(										ADC_CR1_TRIGS0_3	|										ADC_CR1_TRIGS0_1	|		ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_NC															(										ADC_CR1_TRIGS0_3	|	ADC_CR1_TRIGS0_2																			)
#define ADC_EXTTRIG1_RTC_INT												(										ADC_CR1_TRIGS0_3	|	ADC_CR1_TRIGS0_2	|											ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PCA_INT												(										ADC_CR1_TRIGS0_3	|	ADC_CR1_TRIGS0_2	|	ADC_CR1_TRIGS0_1										)
#define ADC_EXTTRIG1_SPI_INT												(										ADC_CR1_TRIGS0_3	|	ADC_CR1_TRIGS0_2	|	ADC_CR1_TRIGS0_1	|	ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PA1_INT												(ADC_CR1_TRIGS0_4																																								)
#define ADC_EXTTRIG1_PA2_INT												(ADC_CR1_TRIGS0_4	|																															ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PA3_INT												(ADC_CR1_TRIGS0_4	|																					ADC_CR1_TRIGS0_1										)
#define ADC_EXTTRIG1_PB4_INT												(ADC_CR1_TRIGS0_4	|																					ADC_CR1_TRIGS0_1	|	ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PB5_INT												(ADC_CR1_TRIGS0_4	|											ADC_CR1_TRIGS0_2																				)
#define ADC_EXTTRIG1_PC3_INT												(ADC_CR1_TRIGS0_4	|											ADC_CR1_TRIGS0_2	|											ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PC4_INT												(ADC_CR1_TRIGS0_4	|											ADC_CR1_TRIGS0_2	|											ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PC5_INT												(ADC_CR1_TRIGS0_4	|											ADC_CR1_TRIGS0_2	|	ADC_CR1_TRIGS0_1										)
#define ADC_EXTTRIG1_PC6_INT												(ADC_CR1_TRIGS0_4	|	ADC_CR1_TRIGS0_3																														)
#define ADC_EXTTRIG1_PC7_INT												(ADC_CR1_TRIGS0_4	|	ADC_CR1_TRIGS0_3	|																					ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PD1_INT												(ADC_CR1_TRIGS0_4	|	ADC_CR1_TRIGS0_3	|											ADC_CR1_TRIGS0_1										)
#define ADC_EXTTRIG1_PD2_INT												(ADC_CR1_TRIGS0_4	|	ADC_CR1_TRIGS0_3	|											ADC_CR1_TRIGS0_1	|	ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PD3_INT												(ADC_CR1_TRIGS0_4	|	ADC_CR1_TRIGS0_3	|	ADC_CR1_TRIGS0_2																				)
#define ADC_EXTTRIG1_PD4_INT												(ADC_CR1_TRIGS0_4	|	ADC_CR1_TRIGS0_3	|	ADC_CR1_TRIGS0_2	|											ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PD5_INT												(ADC_CR1_TRIGS0_4	|	ADC_CR1_TRIGS0_3	|	ADC_CR1_TRIGS0_2	|	ADC_CR1_TRIGS0_1										)
#define ADC_EXTTRIG1_PD6_INT												(ADC_CR1_TRIGS0_4	|	ADC_CR1_TRIGS0_3	|	ADC_CR1_TRIGS0_2	|	ADC_CR1_TRIGS0_1	|	ADC_CR1_TRIGS0_0)
	

/**
  * @}
  */


/** @defgroup ADC_External_trigger_source2 ADC external trigger source 2 select
  * @{
  */	     	
#define ADC_EXTTRIG2_TIM10													(																																			 					ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_TIM11 					                (																														ADC_CR1_TRIGS1_1 								 		)
#define ADC_EXTTRIG2_TIM1					                  (																														ADC_CR1_TRIGS1_1	| ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_LPTIM				                  (																				ADC_CR1_TRIGS1_2	|																	 		)
#define ADC_EXTTRIG2_TIM1_TRGO		                  (																				ADC_CR1_TRIGS1_2	|									 		ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_TIM2_TRGO		                  (																				ADC_CR1_TRIGS1_2	|	ADC_CR1_TRIGS1_1 								 		)
#define ADC_EXTTRIG2_TIM2_INT			                  (																				ADC_CR1_TRIGS1_2	|	ADC_CR1_TRIGS1_1	| ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_UART0_INT		                  (										ADC_CR1_TRIGS1_3																										 				)
#define ADC_EXTTRIG2_UART1_INT		                  (										ADC_CR1_TRIGS1_3	|																		 			ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_LPUART_INT		                  (										ADC_CR1_TRIGS1_3	|											ADC_CR1_TRIGS1_1								 		)
#define ADC_EXTTRIG2_VC0_INT			                  (										ADC_CR1_TRIGS1_3	|											ADC_CR1_TRIGS1_1	|	ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_NC						                  (										ADC_CR1_TRIGS1_3	|	ADC_CR1_TRIGS1_2																				)
#define ADC_EXTTRIG2_RTC_INT			                  (										ADC_CR1_TRIGS1_3	|	ADC_CR1_TRIGS1_2	|											ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PCA_INT			                  (										ADC_CR1_TRIGS1_3	|	ADC_CR1_TRIGS1_2	|	ADC_CR1_TRIGS1_1										)
#define ADC_EXTTRIG2_SPI_INT			                  (										ADC_CR1_TRIGS1_3	|	ADC_CR1_TRIGS1_2	|	ADC_CR1_TRIGS1_1	|	ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PA1_INT			                  (ADC_CR1_TRIGS1_4																																								)
#define ADC_EXTTRIG2_PA2_INT			                  (ADC_CR1_TRIGS1_4	|																															ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PA3_INT			                  (ADC_CR1_TRIGS1_4	|																					ADC_CR1_TRIGS1_1										)
#define ADC_EXTTRIG2_PB4_INT			                  (ADC_CR1_TRIGS1_4	|																					ADC_CR1_TRIGS1_1	|	ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PB5_INT			                  (ADC_CR1_TRIGS1_4	|											ADC_CR1_TRIGS1_2																				)
#define ADC_EXTTRIG2_PC3_INT			                  (ADC_CR1_TRIGS1_4	|											ADC_CR1_TRIGS1_2	|											ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PC4_INT			                  (ADC_CR1_TRIGS1_4	|											ADC_CR1_TRIGS1_2	|											ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PC5_INT			                  (ADC_CR1_TRIGS1_4	|											ADC_CR1_TRIGS1_2	|	ADC_CR1_TRIGS1_1										)
#define ADC_EXTTRIG2_PC6_INT			                  (ADC_CR1_TRIGS1_4	|	ADC_CR1_TRIGS1_3																														)
#define ADC_EXTTRIG2_PC7_INT			                  (ADC_CR1_TRIGS1_4	|	ADC_CR1_TRIGS1_3	|																					ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PD1_INT			                  (ADC_CR1_TRIGS1_4	|	ADC_CR1_TRIGS1_3	|											ADC_CR1_TRIGS1_1										)
#define ADC_EXTTRIG2_PD2_INT			                  (ADC_CR1_TRIGS1_4	|	ADC_CR1_TRIGS1_3	|											ADC_CR1_TRIGS1_1	|	ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PD3_INT			                  (ADC_CR1_TRIGS1_4	|	ADC_CR1_TRIGS1_3	|	ADC_CR1_TRIGS1_2																				)
#define ADC_EXTTRIG2_PD4_INT			                  (ADC_CR1_TRIGS1_4	|	ADC_CR1_TRIGS1_3	|	ADC_CR1_TRIGS1_2	|											ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PD5_INT			                  (ADC_CR1_TRIGS1_4	|	ADC_CR1_TRIGS1_3	|	ADC_CR1_TRIGS1_2	|	ADC_CR1_TRIGS1_1										)
#define ADC_EXTTRIG2_PD6_INT			                  (ADC_CR1_TRIGS1_4	|	ADC_CR1_TRIGS1_3	|	ADC_CR1_TRIGS1_2	|	ADC_CR1_TRIGS1_1	|	ADC_CR1_TRIGS1_0)

/**
  * @}
  */




/**
  * @}
  */ 

/* Private constants ---------------------------------------------------------*/

/** @addtogroup ADC_Private_Constants ADC Private Constants
  * @{
  */


/** @defgroup ADC_conversion_cycles ADC conversion cycles
  * @{
  */
/* ADC conversion cycles (unit: ADC clock cycles)                           				*/
/* (selected sampling time(4 or 8) + conversion time of 12 ADC clock cycles, with 	*/
/* resolution 12 bits)                                                      				*/
#define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_4CYCLE                  16U
#define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_8CYCLE                  20U
/**
  * @}
  */


/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/** @defgroup ADC_Exported_Macros ADC Exported Macros
  * @{
  */
/* Macro for internal HAL driver usage, and possibly can be used into code of */
/* final user.                                                                */    


/** @brief  Reset ADC handle state
  * @param  __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)                               \
  ((__HANDLE__)->State = HAL_ADC_STATE_RESET)


/**
  * @brief Enable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_ENABLE(__HANDLE__)                                           \
  (SET_BIT((__HANDLE__)->Instance->CR0, (ADC_CR0_ADCEN)))
  
/**
  * @brief Disable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_DISABLE(__HANDLE__)                                          \
  (CLEAR_BIT((__HANDLE__)->Instance->CR0, (ADC_CR0_ADCEN)))
    
/**
  * @brief Start the ADC conversion
  * @note  ADC module start by software, stop by hardware after conversion. 	
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_START(__HANDLE__)                                           \
  (SET_BIT((__HANDLE__)->Instance->CR0, (ADC_CR0_START)))
    
				
/** @brief Enable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt
  *          This parameter can be any combination of the following values:
	*						@arg	ADC_IT_CONTINUE: 						ADC End of Continue Conversion interrupt source 
	*						@arg	ADC_IT_RANGE_THRESHOLD			ADC conversion data in defined range interrupt source
	*						@arg	ADC_IT_HIGH_THRESHOLD 			ADC conversion data above threshold interrupt source  
	*						@arg 	ADC_IT_LOW_THRESHOLD				ADC conversion data below threshold interrupt source 
	*						@arg	ADC_IT_CHANNEL7							ADC End of channel7 conversion interrupt source 
	*						@arg	ADC_IT_CHANNEL6							ADC End of channel6 conversion interrupt source 
	*						@arg	ADC_IT_CHANNEL5							ADC End of channel5 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL4							ADC End of channel4 conversion interrupt source 	
	*						@arg	ADC_IT_CHANNEL3							ADC End of channel3 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL2							ADC End of channel2 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL1							ADC End of channel1 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL0							ADC End of channel0 conversion interrupt source 
	* @retval None
  */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__)                         \
  (SET_BIT((__HANDLE__)->Instance->INTEN, (__INTERRUPT__)))
    
/** @brief Disable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt
  *          This parameter can be any combination of the following values:
	*						@arg	ADC_IT_CONTINUE: 						ADC End of Continue Conversion interrupt source 
	*						@arg	ADC_IT_RANGE_THRESHOLD			ADC conversion data in defined range interrupt source
	*						@arg	ADC_IT_HIGH_THRESHOLD 			ADC conversion data above threshold interrupt source  
	*						@arg 	ADC_IT_LOW_THRESHOLD				ADC conversion data below threshold interrupt source 
	*						@arg	ADC_IT_CHANNEL7							ADC End of channel7 conversion interrupt source 
	*						@arg	ADC_IT_CHANNEL6							ADC End of channel6 conversion interrupt source 
	*						@arg	ADC_IT_CHANNEL5							ADC End of channel5 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL4							ADC End of channel4 conversion interrupt source 	
	*						@arg	ADC_IT_CHANNEL3							ADC End of channel3 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL2							ADC End of channel2 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL1							ADC End of channel1 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL0							ADC End of channel0 conversion interrupt source 
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__)                        \
  (CLEAR_BIT((__HANDLE__)->Instance->INTEN, (__INTERRUPT__)))

/** @brief  Checks if the specified ADC interrupt source is enabled or disabled.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC interrupt source to check
  *          This parameter can be any combination of the following values:
	*						@arg	ADC_IT_CONTINUE: 						ADC End of Continue Conversion interrupt source 
	*						@arg	ADC_IT_RANGE_THRESHOLD			ADC conversion data in defined range interrupt source
	*						@arg	ADC_IT_HIGH_THRESHOLD 			ADC conversion data above threshold interrupt source  
	*						@arg 	ADC_IT_LOW_THRESHOLD				ADC conversion data below threshold interrupt source 
	*						@arg	ADC_IT_CHANNEL7							ADC End of channel7 conversion interrupt source 
	*						@arg	ADC_IT_CHANNEL6							ADC End of channel6 conversion interrupt source 
	*						@arg	ADC_IT_CHANNEL5							ADC End of channel5 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL4							ADC End of channel4 conversion interrupt source 	
	*						@arg	ADC_IT_CHANNEL3							ADC End of channel3 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL2							ADC End of channel2 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL1							ADC End of channel1 conversion interrupt source 		
	*						@arg	ADC_IT_CHANNEL0							ADC End of channel0 conversion interrupt source 
  * @retval None
  */
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)                     \
  (((__HANDLE__)->Instance->INTEN & (__INTERRUPT__)) == (__INTERRUPT__))

/** @brief Get the selected ADC's flag status.
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag
  *          This parameter can be any combination of the following values:
  *            @arg ADC_INTFLAG_CONTINUE       		ADC End of Continue Conversion interrupt flag 
  *            @arg ADC_INTFLAG_RANGE_THRESHOLD	  ADC conversion data in defined range interrupt flag 
  *            @arg ADC_INTFLAG_HIGH_THRESHOLD 	  ADC conversion data above threshold interrupt flag 
  *            @arg ADC_INTFLAG_LOW_THERSHOLD		  ADC conversion data below threshold interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL7				  ADC End of channel7 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL6				  ADC End of channel6 conversion interrupt flag 		
  *            @arg ADC_INTFLAG_CHANNEL5				  ADC End of channel5 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL4					ADC End of channel4 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL3					ADC End of channel3 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL2					ADC End of channel2 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL1					ADC End of channel1 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL0					ADC End of channel0 conversion interrupt flag 
  * @retval None
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__)                               \
  ((((__HANDLE__)->Instance->MSKINTSR) & (__FLAG__)) == (__FLAG__))
    
/** @brief Clear the ADC's pending flags
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag
  *          This parameter can be any combination of the following values:
  *            @arg ADC_INTFLAG_CONTINUE       		ADC End of Continue Conversion interrupt flag 
  *            @arg ADC_INTFLAG_RANGE_THRESHOLD	  ADC conversion data in defined range interrupt flag 
  *            @arg ADC_INTFLAG_HIGH_THRESHOLD 	  ADC conversion data above threshold interrupt flag 
  *            @arg ADC_INTFLAG_LOW_THERSHOLD		  ADC conversion data below threshold interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL7				  ADC End of channel7 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL6				  ADC End of channel6 conversion interrupt flag 		
  *            @arg ADC_INTFLAG_CHANNEL5				  ADC End of channel5 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL4					ADC End of channel4 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL3					ADC End of channel3 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL2					ADC End of channel2 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL1					ADC End of channel1 conversion interrupt flag 
  *            @arg ADC_INTFLAG_CHANNEL0					ADC End of channel0 conversion interrupt flag 
  * @retval None
  */
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__)                             \
  (SET_BIT((__HANDLE__)->Instance->INTCLR, (__FLAG__)))


/** @brief Get the selected ADC's rawflag status.
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC rawflag
  *          This parameter can be any combination of the following values:
  *            @arg ADC_RAWINTFLAG_CONTINUE       		ADC End of Continue Conversion interrupt raw flag 
  *            @arg ADC_RAWINTFLAG_RANGE_THRESHOLD	  ADC conversion data in defined range interrupt raw flag 
  *            @arg ADC_RAWINTFLAG_HIGH_THRESHOLD 	  ADC conversion data above threshold interrupt raw flag 
  *            @arg ADC_RAWINTFLAG_LOW_THERSHOLD		  ADC conversion data below threshold interrupt raw flag 
  *            @arg ADC_RAWINTFLAG_CHANNEL7				 	 	ADC End of channel7 conversion interrupt raw flag 
  *            @arg ADC_RAWINTFLAG_CHANNEL6				  	ADC End of channel6 conversion interrupt raw flag 		
  *            @arg ADC_RAWINTFLAG_CHANNEL5				  	ADC End of channel5 conversion interrupt raw flag 
  *            @arg ADC_RAWINTFLAG_CHANNEL4						ADC End of channel4 conversion interrupt raw flag 
  *            @arg ADC_RAWINTFLAG_CHANNEL3						ADC End of channel3 conversion interrupt raw flag 
  *            @arg ADC_RAWINTFLAG_CHANNEL2						ADC End of channel2 conversion interrupt raw flag 
  *            @arg ADC_RAWINTFLAG_CHANNEL1						ADC End of channel1 conversion interrupt raw flag 
  *            @arg ADC_RAWINTFLAG_CHANNEL0						ADC End of channel0 conversion interrupt raw flag 
  * @retval None
  */
#define __HAL_ADC_GET_RAWFLAG(__HANDLE__, __FLAG__)                               \
  ((((__HANDLE__)->Instance->RAWINTSR) & (__FLAG__)) == (__FLAG__))

/**
  * @}
  */

/* Private macro ------------------------------------------------------------*/

/** @defgroup ADC_Private_Macros ADC Private Macros
  * @{
  */
/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

/**
  * @brief Verification of ADC state: enabled or disabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC enabled) or RESET (ADC disabled)
  */
#define ADC_IS_ENABLE(__HANDLE__)                                              \
  ((( ((__HANDLE__)->Instance->CR0 & ADC_CR0_ADCEN) == ADC_CR0_ADCEN )           \
   ) ? SET : RESET)

/**
  * @brief Test if conversion trigger is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define ADC_IS_SOFTWARE_START(__HANDLE__)                              \
  (READ_BIT((__HANDLE__)->Instance->CR1, ADC_CR1_TRIGS0) == ADC_SOFTWARE_START) && \
	(READ_BIT((__HANDLE__)->Instance->CR1, ADC_CR1_TRIGS1) == ADC_SOFTWARE_START)


/**
  * @brief Simultaneously clears and sets specific bits of the handle State
  * @note: ADC_STATE_CLR_SET() macro is merely aliased to generic macro MODIFY_REG(),
  *        the first parameter is the ADC handle State, the second parameter is the
  *        bit field to clear, the third and last parameter is the bit field to set.
  * @retval None
  */
#define ADC_STATE_CLR_SET MODIFY_REG


/**
  * @brief Clear ADC error code (set it to error code: "no error")
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define ADC_CLEAR_ERRORCODE(__HANDLE__)                                        \
  ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE)



/**
  * @brief Get the maximum ADC conversion cycles on all channels.
  * Returns the selected sampling time + conversion time (12 ADC clock cycles)
  * Approximation of sampling time within 4 ranges, returns the highest value:
	*   4 sampling time: 4 + 12 = 16 cycles
	*   8 sampling time: 8 + 12 = 20 cycles	
  * Unit: ADC clock cycles
  * @param __HANDLE__: ADC handle
  * @retval ADC conversion cycles on all channels
  */   
#define ADC_CONVCYCLES_MAX_RANGE(__HANDLE__)                                  \
    (((((__HANDLE__)->Instance->CR0 & ADC_SAMPLE_8CYCLE) == ADC_SAMPLE_8CYCLE)? \
               ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_8CYCLE : ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_4CYCLE))



#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_CHANNEL_0)           || \
                                 ((CHANNEL) == ADC_CHANNEL_1)           || \
                                 ((CHANNEL) == ADC_CHANNEL_2)           || \
                                 ((CHANNEL) == ADC_CHANNEL_3)           || \
                                 ((CHANNEL) == ADC_CHANNEL_4)           || \
                                 ((CHANNEL) == ADC_CHANNEL_5)           || \
                                 ((CHANNEL) == ADC_CHANNEL_6)           || \
                                 ((CHANNEL) == ADC_CHANNEL_7)            )
      
#define IS_ADC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == ADC)			
			
/**
  * @}
  */
    

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_Exported_Functions
  * @{
  */

/** @addtogroup ADC_Exported_Functions_Group1
  * @{
  */


/* Initialization and de-initialization functions  **********************************/
HAL_StatusTypeDef       HAL_ADC_Init(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc);
/**
  * @}
  */

/* IO operation functions  *****************************************************/

/** @addtogroup ADC_Exported_Functions_Group2
  * @{
  */

/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);
HAL_StatusTypeDef       HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout);


/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);


/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc, uint32_t channel);
uint32_t HAL_ADC_GetAccValue(ADC_HandleTypeDef* hadc);

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption) */
void                    HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc);

/* ADC single channel conversion complete interrupt */
void 										HAL_ADC_SingleChannel_ConvCpltCallback(ADC_HandleTypeDef* hadc);

/* ADC continuous mode, multi channel, each channel coversion complete interrupt */
void 										HAL_ADC_MultiChannel0_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void 										HAL_ADC_MultiChannel1_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void 										HAL_ADC_MultiChannel2_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void 										HAL_ADC_MultiChannel3_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void 										HAL_ADC_MultiChannel4_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void 										HAL_ADC_MultiChannel5_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void 										HAL_ADC_MultiChannel6_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void 										HAL_ADC_MultiChannel7_ConvCpltCallback(ADC_HandleTypeDef* hadc);

/* ADC continuous mode, multi channel, all channels coversion complete interrupt */
void                    HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

void                    HAL_ADC_LevelOutOfRangeCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);
/**
  * @}
  */


/* Peripheral Control functions ***********************************************/
/** @addtogroup ADC_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig);
HAL_StatusTypeDef HAL_ADC_ThresholdConfig(ADC_HandleTypeDef* hadc, ADC_ThresholdConfTypeDef* sConfig);
/**
  * @}
  */


/* Peripheral State functions *************************************************/
/** @addtogroup ADC_Exported_Functions_Group4
  * @{
  */
uint32_t                HAL_ADC_GetState(ADC_HandleTypeDef* hadc);
uint32_t                HAL_ADC_GetError(ADC_HandleTypeDef *hadc);
uint32_t 								HAL_ADC_GetDiv(ADC_HandleTypeDef *hadc);

/**
  * @}
  */


/**
  * @}
  */


/* Internal HAL driver functions **********************************************/
/** @addtogroup ADC_Private_Functions
  * @{
  */
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef ADC_ConversionStatus_Reset(ADC_HandleTypeDef* hadc);
void              ADC_StabilizationTime(uint32_t DelayUs);
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


#endif /* __CX32L003_HAL_ADC_H */


