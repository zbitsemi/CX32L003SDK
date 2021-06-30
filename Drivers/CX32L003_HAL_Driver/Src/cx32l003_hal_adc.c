/**
  ******************************************************************************
  * @file    cx32l003_hal_adc.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Initialization and de-initialization functions
  *             ++ Initialization and Configuration of ADC
  *           + Operation functions
  *             ++ Start, stop, get result of conversions adc, using 3 possible modes: polling, interruption.
  *           + Control functions
  *             ++ Threshold configuration
  *           + State functions
  *             ++ ADC state machine management
  *             ++ Interrupts and flags management
  *
  @verbatim
  ==============================================================================
                     ##### ADC peripheral features #####
  ==============================================================================
  [..]
  (+) 12-bit resolution

  (+) Interrupt generation at the end of regular conversion, and in case of over/below 
			threshold.
  
  (+) Single and continuous conversion modes.
  
  (+) Conversion of several channels sequentially.
  
  (+) Programmable sampling time. 

  (+) External trigger (timer or EXTI ....) 
  
  (+) ADC input range: from 0V to Vcc.

                     ##### How to use this driver #####
  ==============================================================================
    [..]

     *** Configuration of top level parameters related to ADC ***
     ============================================================
     [..]

    (#) Enable the ADC interface
      (++) As prerequisite, ADC clock must be configured at RCC top level.
        (++) clock setting is mandatory:
             ADC clock (core clock, also possibly conversion clock).
             (+++) Example:
                   Into HAL_ADC_MspInit() (recommended code location) or with
                   other device clock parameters configuration:
               (+++) __HAL_RCC_ADC_CLK_ENABLE()

    (#) ADC pins configuration
         (++) Enable the clock for the ADC GPIOs
              using macro __HAL_RCC_GPIOx_CLK_ENABLE()
         (++) Configure these ADC pins in analog mode
              using function HAL_GPIO_Init()

    (#) Optionally, in case of usage of ADC with interruptions:
         (++) Configure the NVIC for ADC
              using function HAL_NVIC_EnableIRQ(ADC_IRQn)
         (++) Insert the ADC interruption handler function HAL_ADC_IRQHandler() 
              into the function of corresponding ADC interruption vector 
              ADC_IRQHandler().


     *** Configuration of ADC, channels parameters ***
     ==========================================================================
     [..]

    (#) Configure the ADC parameters and thresholds using function HAL_ADC_Init().


     *** Execution of ADC conversions ***
     ====================================
     [..]

    (#) ADC driver can be used among two modes: polling, interruption.

        (++) ADC conversion by polling:
          (+++) Activate the ADC peripheral and start conversions
                using function HAL_ADC_Enable(), then HAL_ADC_Start()
          (+++) Wait for ADC conversion completion 
                using function HAL_ADC_PollForConversion()
          (+++) Retrieve conversion results 
                using function HAL_ADC_GetValue()
          (+++) Stop conversion and disable the ADC peripheral 
                using function HAL_ADC_Stop()

        (++) ADC conversion by interruption: 
          (+++) Activate the ADC peripheral and start conversions
                using function HAL_ADC_Start_IT()
          (+++) Wait for ADC conversion completion by call of function
                HAL_ADC_ConvCpltCallback()
                (this function must be implemented in user program)
          (+++) Retrieve conversion results 
                using function HAL_ADC_GetValue()
          (+++) Stop conversion and disable the ADC peripheral 
                using function HAL_ADC_Stop_IT()

     [..]

    (@) Callback functions must be implemented in user program:
      (+@) HAL_ADC_ErrorCallback()
      (+@) HAL_ADC_LevelOutOfRangeCallback()
      (+@) HAL_ADC_ConvCpltCallback()

     *** Deinitialization of ADC ***
     ============================================================
     [..]

    (#) Disable the ADC interface
      (++) ADC clock can be hard reset and disabled at RCC top level.
        (++) Hard reset of ADC peripherals
             using macro __HAL_RCC_ADC_FORCE_RESET(), __HAL_RCC_ADC_RELEASE_RESET().
        (++) ADC clock disable
             using the equivalent macro/functions as configuration step.

    (#) ADC pins configuration
         (++) Disable the clock for the ADC GPIOs
              using macro __HAL_RCC_GPIOx_CLK_DISABLE()

    (#) Optionally, in case of usage of ADC with interruptions:
         (++) Disable the NVIC for ADC
              using function HAL_NVIC_EnableIRQ(ADCx_IRQn)

    [..]
  
    @endverbatim
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"



/** @defgroup ADC ADC
  * @brief ADC HAL module driver
  * @{
  */

#ifdef HAL_ADC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup ADC_Private_Constants ADC Private Constants
  * @{
  */

  /* Timeout values for ADC enable and disable settling time.                 */
  /* Values defined to be higher than worst cases: low clocks freq,           */
  /* maximum prescaler.                                                       */
  /* Ex of profile low frequency : Clock source at 0.1 MHz, ADC clock         */
  /* prescaler 4, sampling time 12.5 ADC clock cycles, resolution 12 bits.    */
  /* Unit: ms                                                                 */
  #define ADC_ENABLE_TIMEOUT              2U
  #define ADC_DISABLE_TIMEOUT             2U

  /* Delay for ADC stabilization time.                                        */
  /* Maximum delay is 1us (refer to device datasheet, parameter tSTAB).       */
  /* Unit: us                                                                 */
  #define ADC_STAB_DELAY_US               1U

  /* Delay for temperature sensor stabilization time.                         */
  /* Maximum delay is 10us (refer to device datasheet, parameter tSTART).     */
  /* Unit: us                                                                 */
  #define ADC_TEMPSENSOR_DELAY_US         10U

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup ADC_Exported_Functions ADC Exported Functions
  * @{
  */

/** @defgroup ADC_Exported_Functions_Group1 Initialization/de-initialization functions 
  * @brief    Initialization and Configuration functions
  *
@verbatim    
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the ADC. 
      (+) De-initialize the ADC.

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the ADC peripheral and regular group according to  
  *         parameters specified in structure "ADC_InitTypeDef".
  * @note   As prerequisite, ADC clock must be configured at RCC top level
  *         (clock source APB).
  *         See commented example code below that can be copied and uncommented 
  *         into HAL_ADC_MspInit().
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the ADC MSP (HAL_ADC_MspInit()) only when
  *         coming from ADC state reset. Following calls to this function can
  *         be used to reconfigure some parameters of ADC_InitTypeDef  
  *         structure on the fly, without modifying MSP configuration. If ADC  
  *         MSP has to be modified again, HAL_ADC_DeInit() must be called
  *         before HAL_ADC_Init().
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_InitTypeDef".
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  uint32_t tmp_cr0 = 0U;
  uint32_t tmp_cr1 = 0U;
  uint32_t tmp_cr2 = 0U;
  
  /* Check ADC handle */
  if(hadc == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.SingleContinueMode));
  
  /* As prerequisite, into HAL_ADC_MspInit(), ADC clock must be configured    */
  /* at RCC top level.                                                        */
  /* Refer to header of this file for more details on clock enabling          */
  /* procedure.                                                               */

  /* Actions performed only if ADC is coming from state reset:                */
  /* - Initialization of ADC MSP                                              */
  if (hadc->State == HAL_ADC_STATE_RESET)
  {
    
    /* Allocate lock resource and initialize it */
    hadc->Lock = HAL_UNLOCKED;
    
    /* Init the low level hardware */
    HAL_ADC_MspInit(hadc);
  }
  
  /* Disable ADC peripheral */
  /* Note: Reset ADC continuous conversion status        */
  tmp_hal_status = ADC_ConversionStatus_Reset(hadc);
  
  /* Configuration of ADC parameters if previous preliminary actions are      */ 
  /* correctly completed.                                                     */
  if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL) &&
      (tmp_hal_status == HAL_OK)                                  )
  {
    /* Set ADC state */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_BUSY,
											HAL_ADC_STATE_BUSY_INTERNAL);
    
    /* Set ADC parameters */
    /* Configuration of ADC:                                                  */
    /*  - external trigger or software to start conversion                    */
    /*  - continuous conversion mode                                          */
    tmp_cr0 |= (hadc->Init.SamplingTime | hadc->Init.ClkSel);

		/* Continuous conversion or Single conversion selection */		
		tmp_cr1 |= hadc->Init.SingleContinueMode;		
		
		if(hadc->Init.CircleMode == ADC_MULTICHANNEL_NONCIRCLE)
		{
			if (hadc->Init.SingleContinueMode == ADC_MODE_SINGLE)		
			{
				tmp_cr0 |= (hadc->Init.SingleChannelSel);
			}	
			else if(hadc->Init.SingleContinueMode == ADC_MODE_CONTINUE)			
			{
				tmp_cr2 |= ((hadc->Init.NbrOfConversion-1) << 8) | hadc->Init.ContinueChannelSel;	
			}
		}
		else
		{
				tmp_cr2 |= hadc->Init.CircleMode | hadc->Init.ContinueChannelSel;				
		}
		
		/* Auto accumulation enable or disable*/		
		tmp_cr1 |= hadc->Init.AutoAccumulation;
		
		/* Software trigger conversion or external interrupt trigger*/
		tmp_cr1 |= hadc->Init.ExternalTrigConv1 | hadc->Init.ExternalTrigConv2;	
			
    /* Update ADC configuration register CR1 with previous settings */
		MODIFY_REG(hadc->Instance->CR0,
							 ADC_CR0_SAM    |
							 ADC_CR0_SEL  	|
							 ADC_CR0_CLKSEL     ,
							 tmp_cr0             );

    /* Update ADC configuration register CR1 with previous settings */
		MODIFY_REG(hadc->Instance->CR1,
							 ADC_CR1_RACC_EN   |
							 ADC_CR1_TRIGS0  	 |
							 ADC_CR1_TRIGS1			,
							 tmp_cr1             );

    /* Update ADC configuration register CR2 with previous settings */
		MODIFY_REG(hadc->Instance->CR2,
							 ADC_CR2_CIRCLE_MODE  |
							 ADC_CR2_ADCCNT  	 		|
							 ADC_CR2_CHEN				,
							 tmp_cr2             );

    /* Check back that ADC registers have effectively been configured to      */
    /* ensure of no potential problem of ADC core IP clocking.                */
    /* Check through register CR0 (excluding bits set in other functions)     */
    if (READ_BIT(hadc->Instance->CR0, ~(ADC_CR0_ADCEN | ADC_CR0_START | ADC_CR0_STATERST))
         == tmp_cr0)
    {
      /* Set ADC error code to none */
      ADC_CLEAR_ERRORCODE(hadc);	
      
      /* Set the ADC state */
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_BUSY_INTERNAL,
                        HAL_ADC_STATE_READY);
    }
    else
    {
      /* Update ADC state machine to error */
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_BUSY_INTERNAL,
                        HAL_ADC_STATE_ERROR_INTERNAL);
      
      /* Set ADC error code to ADC IP internal error */
      SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);
      
      tmp_hal_status = HAL_ERROR;
    }
  }
  else
  {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);
        
    tmp_hal_status = HAL_ERROR;
  }
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Deinitialize the ADC peripheral registers to their default reset
  *         values, with deinitialization of the ADC MSP.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check ADC handle */
  if(hadc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Set ADC state */
  SET_BIT(hadc->State, HAL_ADC_STATE_BUSY_INTERNAL);
  
  /* Stop potential conversion on going*/
  /* Disable ADC peripheral */
  tmp_hal_status = ADC_ConversionStatus_Reset(hadc);
  
  /* Configuration of ADC parameters if previous preliminary actions are      */ 
  /* correctly completed.                                                     */
  if (tmp_hal_status == HAL_OK)
  {    
    /* ========== Hard reset ADC peripheral ========== */
    /* Performs a global reset of the entire ADC peripheral: ADC state is     */
    /* forced to a similar state after device power-on.                       */

    __HAL_RCC_ADC_FORCE_RESET();                                         
    __HAL_RCC_ADC_RELEASE_RESET();                                        
    
    /* DeInit the low level hardware: GPIO, NVIC */
    HAL_ADC_MspDeInit(hadc);
    
    /* Set ADC error code to none */
    ADC_CLEAR_ERRORCODE(hadc);
    
    /* Set ADC state */
    hadc->State = HAL_ADC_STATE_RESET; 
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Initializes the ADC MSP.
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MspInit must be implemented in the user file.
   */ 
}

/**
  * @brief  DeInitializes the ADC MSP.
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MspDeInit must be implemented in the user file.
   */ 
}

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group2 IO operation functions
 *  @brief    Input and Output operation functions
 *
@verbatim   
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Start conversion.
      (+) Stop conversion.
      (+) Poll for conversion complete.
      (+) Get result of conversion.
      (+) Start conversion and enable interruptions.
      (+) Stop conversion and disable interruptions.
      (+) Handle ADC interrupt request
@endverbatim
  * @{
  */

/**
  * @brief  Enables ADC, starts conversion.
  *         Interruptions enabled in this function: None.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
   
  /* Enable the ADC peripheral */
  tmp_hal_status = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmp_hal_status == HAL_OK)
  {
    /* Set ADC state                                                          */
    /* - Clear state bitfield related to conversion results     							*/
    /* - Set state bitfield related to conversion                      				*/
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_READY | HAL_ADC_STATE_EOC,
                      HAL_ADC_STATE_BUSY);
    
    /* Reset ADC all error code fields */
    ADC_CLEAR_ERRORCODE(hadc);    
		
    /* Process unlocked */
    /* Unlock before starting ADC conversions: in case of potential           */
    /* interruption, to let the process to ADC IRQ Handler.                   */
    __HAL_UNLOCK(hadc);
  
    /* Clear continue conversion flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CONTINUE);
    
    /* Enable conversion.                                    									*/
    /* If software start has been selected, conversion starts immediately.    */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    if (ADC_IS_SOFTWARE_START(hadc))	
    {
      /* Start ADC conversion with SW start */
      SET_BIT(hadc->Instance->CR0, (ADC_CR0_START));
    }
    else
    {
      /* Start ADC conversion with external trigger */
      /* User should configure corresponding interrupt to start ADC */			
    }
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
    
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Stop ADC conversion, disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing stop of potential 
  *         conversion.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
     
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Disable ADC peripheral */
  tmp_hal_status = ADC_ConversionStatus_Reset(hadc);
  __HAL_ADC_DISABLE(hadc);
	
  /* Check if ADC is effectively disabled */
  if (tmp_hal_status == HAL_OK)
  {
    /* Set ADC state */
    ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_BUSY, HAL_ADC_STATE_READY);
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Wait for conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
 
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Get tick count */
  tickstart = HAL_GetTick();
  
  /* 	Polling for end of conversion(no circle mode): difference in  					*/
	/* 	single/continuous conversion.        																			*/
  /*  - If single conversion, START bit is used to determine the           		*/
  /*    conversion completion.                                                */
  /*  - If continuous conversion, CONT_MIF bit is used to determine the    		*/
  /*    conversion completion.                                                */	
  /*    To poll for each conversion, the maximum conversion time is computed  */
  /*    from ADC conversion time and APB/ADC clock prescalers.  							*/
  /*    START bit is cleared after each single conversion, no timeout status  */
  /*    can be set.                                                           */
	if(HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_CIRCLE_MODE)) 
	{
		if (HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_CT))
		{
			/* Wait until End of Single Conversion START flag is cleared */
			while(HAL_IS_BIT_SET(hadc->Instance->CR0, ADC_CR0_START)) 
			{
				/* Check if timeout is disabled (set to infinite wait)  */
				if(Timeout != HAL_MAX_DELAY)
				{
					if((Timeout == 0U) || ((HAL_GetTick() - tickstart ) > Timeout))
					{
						/* Update ADC state machine to timeout */
						SET_BIT(hadc->State, HAL_ADC_STATE_TIMEOUT);
						
						/* Process unlocked */
						__HAL_UNLOCK(hadc);
						
						return HAL_TIMEOUT;
					}
				}
			}
		}
		else
		{
			/* Wait until End of continuous Conversion flag is raised */
			while(__HAL_ADC_GET_RAWFLAG(hadc, ADC_RAWINTFLAG_CONTINUE) == RESET) 
			{
				/* Check if timeout is disabled (set to infinite wait) */
				if(Timeout != HAL_MAX_DELAY)
				{
					if((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout))
					{
						/* Update ADC state machine to timeout */
						SET_BIT(hadc->State, HAL_ADC_STATE_TIMEOUT);
						
						/* Process unlocked */
						__HAL_UNLOCK(hadc);
						
						return HAL_TIMEOUT;
					}
				}	
			}	
		}		
	}

  /* Clear continuous conversion flag */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CONTINUE);
  
  /* Update ADC state machine */
  SET_BIT(hadc->State, HAL_ADC_STATE_EOC);
  
  /* Return ADC state */
  return HAL_OK;
}

/**
  * @brief  Poll for conversion event.
  * @param  hadc: ADC handle
  * @param  EventType: the ADC event type.
  *          This parameter can be one of the following values:
  *            @arg ADC_INTFLAG_RANGE_THRESHOLD	  ADC conversion data in defined range interrupt flag 
  *            @arg ADC_INTFLAG_HIGH_THRESHOLD 	  ADC conversion data above threshold interrupt flag 
  *            @arg ADC_INTFLAG_LOW_THERSHOLD		  ADC conversion data below threshold interrupt flag 
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout)
{
  uint32_t tickstart = 0U; 

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Get tick count */
  tickstart = HAL_GetTick();
  
  /* Check selected event flag */
  while(__HAL_ADC_GET_FLAG(hadc, EventType) == RESET)
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0U) || ((HAL_GetTick() - tickstart ) > Timeout))
      {
        /* Update ADC state machine to timeout */
        SET_BIT(hadc->State, HAL_ADC_STATE_TIMEOUT);
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  /* Threshold (level out of window) event */
  /* Set ADC state */
  SET_BIT(hadc->State, HAL_ADC_STATE_OUTRANGE);
   
  /* Clear ADC interrupt flag */
  __HAL_ADC_CLEAR_FLAG(hadc, EventType);
  
  /* Return ADC state */
  return HAL_OK;
}

/**
  * @brief  Enables ADC, starts conversion with interruption.
  *         Interruptions enabled in this function:
  *         Each of these interruptions has its dedicated callback function.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmp_hal_status = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmp_hal_status == HAL_OK)
  {
    /* Set ADC state                                                          */
    /* - Clear state bitfield related to regular group conversion results     */
    /* - Set state bitfield related to regular operation                      */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_READY | HAL_ADC_STATE_EOC,
                      HAL_ADC_STATE_BUSY);
    
    /* Reset ADC all error code fields */
    ADC_CLEAR_ERRORCODE(hadc);

    /* Process unlocked */
    /* Unlock before starting ADC conversions: in case of potential           */
    /* interruption, to let the process to ADC IRQ Handler.                   */
    __HAL_UNLOCK(hadc);
    
		
		if(hadc->Init.SingleContinueMode == ADC_MODE_SINGLE)
		{
			switch(hadc->Init.SingleChannelSel)
			{
				case ADC_SINGLE_CHANNEL_0:
					/* Clear conversion end flag */
					/* (To ensure of no unknown state from potential previous ADC operations) */
					__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL0);
					/* Enable end of conversion interrupt */
					__HAL_ADC_ENABLE_IT(hadc, ADC_IT_CHANNEL0);
					break;
				case ADC_SINGLE_CHANNEL_1:
					__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL1);
					__HAL_ADC_ENABLE_IT(hadc, ADC_IT_CHANNEL1);
					break;			
				case ADC_SINGLE_CHANNEL_2:
					__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL2);
					__HAL_ADC_ENABLE_IT(hadc, ADC_IT_CHANNEL2);
					break;		
				case ADC_SINGLE_CHANNEL_3:
					__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL3);
					__HAL_ADC_ENABLE_IT(hadc, ADC_IT_CHANNEL3);
					break;					
				case ADC_SINGLE_CHANNEL_4:
					__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL4);
					__HAL_ADC_ENABLE_IT(hadc, ADC_IT_CHANNEL4);
					break;					
				case ADC_SINGLE_CHANNEL_5:
					__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL5);
					__HAL_ADC_ENABLE_IT(hadc, ADC_IT_CHANNEL5);
					break;		
				case ADC_SINGLE_CHANNEL_6:
					__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL6);
					__HAL_ADC_ENABLE_IT(hadc, ADC_IT_CHANNEL6);
					break;		
				case ADC_SINGLE_CHANNEL_7:
					__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL7);
					__HAL_ADC_ENABLE_IT(hadc, ADC_IT_CHANNEL7);
					break;		
				default:
					__HAL_ADC_DISABLE_IT(hadc,ADC_INTEN_CONT_ALL);
					break;
			}			
		}
		else
		{	
			__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL_ALL);		
			__HAL_ADC_ENABLE_IT(hadc, ADC_IT_CONTINUE | (hadc->Init.ContinueChannelSel));
		}
		
    /* Enable conversion.                                    									*/
    /* If software start has been selected, conversion starts immediately.    */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    if (ADC_IS_SOFTWARE_START(hadc))
    {
      /* Start ADC conversion with SW start */
      SET_BIT(hadc->Instance->CR0, (ADC_CR0_START));
    }
    else
    {
      /* Start ADC conversion with external trigger */
      /* User should configure corresponding interrupt to start ADC */	
    }
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Stop ADC conversion, disable interrution of 
  *         end-of-conversion, disable ADC peripheral.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
     
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Stop potential conversion on going */
  /* Disable ADC peripheral */
  tmp_hal_status = ADC_ConversionStatus_Reset(hadc);
  
  /* Check if ADC is effectively disabled */
  if (tmp_hal_status == HAL_OK)
  {
    /* Disable ADC end of conversion interrupt */
    __HAL_ADC_DISABLE_IT(hadc, ADC_INTEN_CONT_ALL);
		
		/* Disable ADC */
    __HAL_ADC_DISABLE(hadc);
    
		/* Set ADC state */
    ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_BUSY, HAL_ADC_STATE_READY);
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}




/**
  * @brief  Get ADC conversion result.
  * @param  hadc: ADC handle
	* @param  channel: ADC channel number used for continuous mode @ref ADC_ContinueChannelSel
	* 								= ADC_CONTINUE_CHANNEL_0
	* 								= ADC_CONTINUE_CHANNEL_1
	* 								= ADC_CONTINUE_CHANNEL_2
	* 								= ADC_CONTINUE_CHANNEL_3
	* 								= ADC_CONTINUE_CHANNEL_4
	* 								= ADC_CONTINUE_CHANNEL_5
	* 								= ADC_CONTINUE_CHANNEL_6
	* 								= ADC_CONTINUE_CHANNEL_7
	* @note		For single channel mode, param channel will have no effect. 
  * @retval ADC conversion data
  */
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc, uint32_t channel)
{
	uint32_t tmpADCvalue;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

	if(hadc->Init.SingleContinueMode == ADC_MODE_SINGLE)
	{
		tmpADCvalue = hadc->Instance->RESULT;
	}
	else
	{
		switch(channel)
		{
			case ADC_CONTINUE_CHANNEL_0:
					/* Return ADC converted value */ 
					tmpADCvalue = hadc->Instance->RESULT0;
				break;
			case ADC_CONTINUE_CHANNEL_1:
					tmpADCvalue = hadc->Instance->RESULT1;
				break;			
			case ADC_CONTINUE_CHANNEL_2:
					tmpADCvalue = hadc->Instance->RESULT2;
				break;		
			case ADC_CONTINUE_CHANNEL_3:
					tmpADCvalue = hadc->Instance->RESULT3;
				break;					
			case ADC_CONTINUE_CHANNEL_4:
					tmpADCvalue = hadc->Instance->RESULT4;
				break;					
			case ADC_CONTINUE_CHANNEL_5:
					tmpADCvalue = hadc->Instance->RESULT5;
				break;		
			case ADC_CONTINUE_CHANNEL_6:
					tmpADCvalue = hadc->Instance->RESULT6;
				break;		
			case ADC_CONTINUE_CHANNEL_7:
					tmpADCvalue = hadc->Instance->RESULT7;
				break;		
			default:
					tmpADCvalue = 0;
				break;
		}		
	}
	return tmpADCvalue;
}


/**
  * @brief  Get ADC conversion result.
  * @param  hadc: ADC handle
	* @note		This function is only valid when RACC_EN is set. 
  * @retval ADC conversion data
  */
uint32_t HAL_ADC_GetAccValue(ADC_HandleTypeDef* hadc)
{
	uint32_t tmpADCvalue;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

	tmpADCvalue = hadc->Instance->RESULT_ACC;
	
	SET_BIT(hadc->Instance->CR1, ADC_CR1_RACC_CLR); 
	
	return tmpADCvalue;
}



/**
  * @brief  Handles ADC interrupt request  
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* ========== Check End of Conversion flag ========== */
	/* Update state machine on conversion status if not in error state */
	if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL))
	{
		/* Set ADC state */
		SET_BIT(hadc->State, HAL_ADC_STATE_EOC); 
	}				
	/* Set ADC state */
	CLEAR_BIT(hadc->State, HAL_ADC_STATE_BUSY);   
	SET_BIT(hadc->State, HAL_ADC_STATE_READY);	

	if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_CHANNEL0))
	{
		if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_CHANNEL0))
		{
			/* Clear single channel conversion flag */
			__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL0);					
			if(hadc->Init.SingleContinueMode == ADC_MODE_SINGLE)
			{
				/* Disable ADC end of conversion interrupt */
				__HAL_ADC_DISABLE_IT(hadc, ADC_IT_CHANNEL0);				
				/* Conversion complete callback */
				HAL_ADC_SingleChannel_ConvCpltCallback(hadc);
			}
			else
			{			
				/* Channel0 Conversion complete callback in continuous mode */
				HAL_ADC_MultiChannel0_ConvCpltCallback(hadc);									
			}
		}
	}
	if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_CHANNEL1))
	{
		if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_CHANNEL1))
		{
			/* Clear single channel conversion flag */
			__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL1);					
			if(hadc->Init.SingleContinueMode == ADC_MODE_SINGLE)
			{
				/* Disable ADC end of conversion interrupt */
				__HAL_ADC_DISABLE_IT(hadc, ADC_IT_CHANNEL1);				
				/* Conversion complete callback */
				HAL_ADC_SingleChannel_ConvCpltCallback(hadc);
			}
			else
			{			
				/* Channel1 Conversion complete callback in continuous mode */
				HAL_ADC_MultiChannel1_ConvCpltCallback(hadc);									
			}
		}
	}		
	if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_CHANNEL2))
	{
		if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_CHANNEL2))
		{
			/* Clear single channel conversion flag */
			__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL2);					
			if(hadc->Init.SingleContinueMode == ADC_MODE_SINGLE)
			{
				/* Disable ADC end of conversion interrupt */
				__HAL_ADC_DISABLE_IT(hadc, ADC_IT_CHANNEL2);				
				/* Conversion complete callback */
				HAL_ADC_SingleChannel_ConvCpltCallback(hadc);
			}
			else
			{			
				/* Channel2 Conversion complete callback in continuous mode */
				HAL_ADC_MultiChannel2_ConvCpltCallback(hadc);									
			}	
		}
	}				
	if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_CHANNEL3))
	{
		if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_CHANNEL3))
		{
			/* Clear single channel conversion flag */
			__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL3);					
			if(hadc->Init.SingleContinueMode == ADC_MODE_SINGLE)
			{
				/* Disable ADC end of conversion interrupt */
				__HAL_ADC_DISABLE_IT(hadc, ADC_IT_CHANNEL3);				
				/* Conversion complete callback */
				HAL_ADC_SingleChannel_ConvCpltCallback(hadc);
			}
			else
			{			
				/* Channel3 Conversion complete callback in continuous mode */
				HAL_ADC_MultiChannel3_ConvCpltCallback(hadc);									
			}	
		}
	}				
	if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_CHANNEL4))
	{
		if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_CHANNEL4))
		{
			/* Clear single channel conversion flag */
			__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL4);					
			if(hadc->Init.SingleContinueMode == ADC_MODE_SINGLE)
			{
				/* Disable ADC end of conversion interrupt */
				__HAL_ADC_DISABLE_IT(hadc, ADC_IT_CHANNEL4);				
				/* Conversion complete callback */
				HAL_ADC_SingleChannel_ConvCpltCallback(hadc);
			}
			else
			{			
				/* Channel4 Conversion complete callback in continuous mode */
				HAL_ADC_MultiChannel4_ConvCpltCallback(hadc);									
			}		
		}
	}				
	if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_CHANNEL5))
	{
		if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_CHANNEL5))
		{
			/* Clear single channel conversion flag */
			__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL5);					
			if(hadc->Init.SingleContinueMode == ADC_MODE_SINGLE)
			{
				/* Disable ADC end of conversion interrupt */
				__HAL_ADC_DISABLE_IT(hadc, ADC_IT_CHANNEL5);				
				/* Conversion complete callback */
				HAL_ADC_SingleChannel_ConvCpltCallback(hadc);
			}
			else
			{			
				/* Channel5 Conversion complete callback in continuous mode */
				HAL_ADC_MultiChannel5_ConvCpltCallback(hadc);									
			}			
		}
	}				
	if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_CHANNEL6))
	{
		if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_CHANNEL6))
		{
			/* Clear single channel conversion flag */
			__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL6);					
			if(hadc->Init.SingleContinueMode == ADC_MODE_SINGLE)
			{
				/* Disable ADC end of conversion interrupt */
				__HAL_ADC_DISABLE_IT(hadc, ADC_IT_CHANNEL6);				
				/* Conversion complete callback */
				HAL_ADC_SingleChannel_ConvCpltCallback(hadc);
			}
			else
			{			
				/* Channel6 Conversion complete callback in continuous mode */
				HAL_ADC_MultiChannel6_ConvCpltCallback(hadc);									
			}	
		}
	}				
	if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_CHANNEL7))
	{
		if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_CHANNEL7))
		{
			/* Clear single channel conversion flag */
			__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CHANNEL7);					
			if(hadc->Init.SingleContinueMode == ADC_MODE_SINGLE)
			{
				/* Disable ADC end of conversion interrupt */
				__HAL_ADC_DISABLE_IT(hadc, ADC_IT_CHANNEL7);				
				/* Conversion complete callback */
				HAL_ADC_SingleChannel_ConvCpltCallback(hadc);
			}
			else
			{			
				/* Channel7 Conversion complete callback in continuous mode */
				HAL_ADC_MultiChannel7_ConvCpltCallback(hadc);									
			}			
		}
	}				

	if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_CONTINUE))
	{
		if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_CONTINUE))
		{
			/* Update state machine on conversion status if not in error state */
			if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL))
			{
				/* Set ADC state */
				SET_BIT(hadc->State, HAL_ADC_STATE_EOC); 
			}
			/* Clear continuos conversion flag */				
			__HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_CONTINUE);						
			/* Disable ADC end of conversion interrupt */
			__HAL_ADC_DISABLE_IT(hadc, ADC_IT_CONTINUE);
			
			/* Set ADC state */
			CLEAR_BIT(hadc->State, HAL_ADC_STATE_BUSY);   
			SET_BIT(hadc->State, HAL_ADC_STATE_READY);
			
			/* Conversion complete callback */
			HAL_ADC_ConvCpltCallback(hadc);
		}
	}

   
  /* ========== Check out of threshold flags ========== */
  if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_RANGE_THRESHOLD))
  {
    if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_RANGE_THRESHOLD))
    {
      /* Set ADC state */
      SET_BIT(hadc->State, HAL_ADC_STATE_OUTRANGE);
      
      /* Level out of window callback */ 
      HAL_ADC_LevelOutOfRangeCallback(hadc);
      
      /* Clear the ADC out of threshold flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_RANGE_THRESHOLD);
    }
  }

  if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_HIGH_THRESHOLD))
  {
    if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_HIGH_THRESHOLD))
    {
      /* Set ADC state */
      SET_BIT(hadc->State, HAL_ADC_STATE_OUTRANGE);
      
      /* Level out of window callback */ 
      HAL_ADC_LevelOutOfRangeCallback(hadc);
      
      /* Clear the ADC out of threshold flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_HIGH_THRESHOLD);
    }
  }	
	
  if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_LOW_THRESHOLD))
  {
    if(__HAL_ADC_GET_FLAG(hadc, ADC_INTFLAG_LOW_THERSHOLD))
    {
      /* Set ADC state */
      SET_BIT(hadc->State, HAL_ADC_STATE_OUTRANGE);
      
      /* Level out of window callback */ 
      HAL_ADC_LevelOutOfRangeCallback(hadc);
      
      /* Clear the ADC out of threshold flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_INTFLAG_LOW_THERSHOLD);
    }
  }
}


/**
  * @brief  Continuous mode channel0 conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MultiChannel0_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MultiChannel0_ConvCpltCallback must be implemented in the user file.
   */
}


/**
  * @brief  Continuous mode channel1 conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MultiChannel1_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MultiChannel1_ConvCpltCallback must be implemented in the user file.
   */
}


/**
  * @brief  Continuous mode channel2 conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MultiChannel2_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MultiChannel2_ConvCpltCallback must be implemented in the user file.
   */
}


/**
  * @brief  Continuous mode channel3 conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MultiChannel3_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MultiChannel3_ConvCpltCallback must be implemented in the user file.
   */
}


/**
  * @brief  Continuous mode channel4 conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MultiChannel4_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MultiChannel4_ConvCpltCallback must be implemented in the user file.
   */
}


/**
  * @brief  Continuous mode channel5 conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MultiChannel5_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MultiChannel5_ConvCpltCallback must be implemented in the user file.
   */
}



/**
  * @brief  Continuous mode channel6 conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MultiChannel6_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MultiChannel6_ConvCpltCallback must be implemented in the user file.
   */
}


/**
  * @brief  Continuous mode channel7 conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MultiChannel7_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MultiChannel7_ConvCpltCallback must be implemented in the user file.
   */
}



/**
  * @brief  Single channel conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_SingleChannel_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_SingleChannel_ConvCpltCallback must be implemented in the user file.
   */
}


/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvCpltCallback must be implemented in the user file.
   */
}


/**
  * @brief  Out of threshold callback in non blocking mode. 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_LevelOutOfRangeCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_LevelOutOfRangeCallback must be implemented in the user file.
  */
}

/**
  * @brief  ADC error callback in non blocking mode
  *        (ADC conversion with interruption or transfer by DMA)
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ErrorCallback must be implemented in the user file.
  */
}


/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group3 Peripheral Control functions
 *  @brief    Peripheral Control functions
 *
@verbatim   
 ===============================================================================
             ##### Peripheral Control functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure channels to convert
      (+) Configure the threshold level
      
@endverbatim
  * @{
  */

/**
  * @brief  Configures the the selected channel.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes channel to be converted, following  
  *         calls to this function can be used to reconfigure some parameters 
  *         of structure "ADC_ChannelConfTypeDef" on the fly, without reseting 
  *         the ADC.
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_ChannelConfTypeDef".
  * @param  hadc: ADC handle
  * @param  sConfig: Structure of ADC channel.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig)
{ 
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  __IO uint32_t wait_loop_index = 0U;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_CHANNEL(sConfig->Channel));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Channel for conversion configuration */
  MODIFY_REG(hadc->Instance->CR0, ADC_CR0_SEL, sConfig->SingleChannelSel);	
	
  /* Channel sampling time configuration */
  MODIFY_REG(hadc->Instance->CR0, ADC_CR0_SAM, sConfig->SamplingTime);

  /* ADC clock divider configuration */
  MODIFY_REG(hadc->Instance->CR0, ADC_CR0_CLKSEL, sConfig->ClkSel);  

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Configures the threshold.
  * @note   Thresholds can be modified while ADC conversion
  *         is on going.
  *         In this case, some constraints must be taken into account:
  *         the programmed threshold values are effective from the next
  *         ADC EOC (end of unitary conversion).
  *         Considering that registers write delay may happen due to
  *         bus activity, this might cause an uncertainty on the
  *         effective timing of the new programmed threshold values.
  * @param  hadc: ADC handle
  * @param  sConfig: Structure of ADC compare threshold configuration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_ThresholdConfig(ADC_HandleTypeDef* hadc, ADC_ThresholdConfTypeDef* sConfig)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
	
  /* Configure ADC out of threshold interrupt */
  if(sConfig->ITMode == ENABLE)
  {
		/* Enable the ADC out of threshold interrupt */
		if(sConfig->CompareMode == ADC_COMP_THRESHOLD_RANGE)
			__HAL_ADC_ENABLE_IT(hadc, ADC_IT_RANGE_THRESHOLD); 
		if(sConfig->CompareMode == ADC_COMP_THRESHOLD_HIGH)
			__HAL_ADC_ENABLE_IT(hadc, ADC_IT_HIGH_THRESHOLD);
		if(sConfig->CompareMode == ADC_COMP_THRESHOLD_LOW)
			__HAL_ADC_ENABLE_IT(hadc, ADC_IT_LOW_THRESHOLD);		
  }
  else
  {
    /* Disable the ADC out of threshold interrupt */
		if(sConfig->CompareMode == ADC_COMP_THRESHOLD_HIGH)
			__HAL_ADC_DISABLE_IT(hadc, ADC_IT_RANGE_THRESHOLD);
		if(sConfig->CompareMode == ADC_COMP_THRESHOLD_LOW)
			__HAL_ADC_DISABLE_IT(hadc, ADC_IT_HIGH_THRESHOLD);
		if(sConfig->CompareMode == ADC_COMP_THRESHOLD_LOW)
			__HAL_ADC_DISABLE_IT(hadc, ADC_IT_LOW_THRESHOLD);			
  }

  /* Set the high threshold */
  WRITE_REG(hadc->Instance->HT, sConfig->HighThreshold);
  
  /* Set the low threshold */
  WRITE_REG(hadc->Instance->LT, sConfig->LowThreshold);

  /* Compare mode enable */
  MODIFY_REG(hadc->Instance->CR1, ADC_CR1_LTCMP | ADC_CR1_HTCMP | ADC_CR1_REGCMP, sConfig->CompareMode);		
	
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return HAL_OK;
}


/**
  * @}
  */


/** @defgroup ADC_Exported_Functions_Group4 Peripheral State functions
 *  @brief    Peripheral State functions
 *
@verbatim
 ===============================================================================
            ##### Peripheral State and Errors functions #####
 ===============================================================================  
    [..]
    This subsection provides functions to get in run-time the status of the  
    peripheral.
      (+) Check the ADC state
      (+) Check the ADC error code

@endverbatim
  * @{
  */

/**
  * @brief  return the ADC state
  * @param  hadc: ADC handle
  * @retval HAL state
  */
uint32_t HAL_ADC_GetState(ADC_HandleTypeDef* hadc)
{
  /* Return ADC state */
  return hadc->State;
}

/**
  * @brief  Return the ADC error code
  * @param  hadc: ADC handle
  * @retval ADC Error Code
  */
uint32_t HAL_ADC_GetError(ADC_HandleTypeDef *hadc)
{
  return hadc->ErrorCode;
}


/**
  * @brief  Get the ADC divider value
  * @param  hadc: ADC handle
  * @retval ADC divider value 
  */
uint32_t HAL_ADC_GetDiv(ADC_HandleTypeDef *hadc)	
{
	switch(hadc->Init.ClkSel)
	{
		case ADC_CLOCK_PCLK_DIV1:
			return 1;
		case ADC_CLOCK_PCLK_DIV2:
			return 2;
		case ADC_CLOCK_PCLK_DIV4:
			return 4;
		case ADC_CLOCK_PCLK_DIV8:
			return 8;		
		case ADC_CLOCK_PCLK_DIV16:
			return 16;		
		case ADC_CLOCK_PCLK_DIV32:
			return 32;		
		case ADC_CLOCK_PCLK_DIV64:
			return 64;		
		case ADC_CLOCK_PCLK_DIV128:
			return 128;		
		default:
			return 128;
	}
}


/**
  * @}
  */

/**
  * @}
  */

/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */

/**
  * @brief  Enable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC must be disabled
  *         and clock must be enabled (done into HAL_ADC_Init()).
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0U;
  __IO uint32_t wait_loop_index = 0U;
  
  /* ADC enable and wait for ADC ready         																*/
  /* Timeout implemented to not be stuck if ADC cannot be enabled (possible   */
  /* causes: ADC clock not running, ...).                                     */
  if (ADC_IS_ENABLE(hadc) == RESET)
  {
    /* Enable the Peripheral */
    __HAL_ADC_ENABLE(hadc);
    
    /* Delay for ADC stabilization time */
    /* Compute number of CPU cycles to wait for */
    wait_loop_index = (ADC_STAB_DELAY_US * (SystemCoreClock / 1000000U));
    while(wait_loop_index != 0U)
    {
      wait_loop_index--;
    }
    
    /* Get tick count */
    tickstart = HAL_GetTick();

    /* Wait for ADC effectively enabled */
    while(ADC_IS_ENABLE(hadc) == RESET)
    {
      if((HAL_GetTick() - tickstart) > ADC_ENABLE_TIMEOUT)
      {
        /* Update ADC state machine to error */
        SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
      
        return HAL_ERROR;
      }
    }
  }
   
  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  Reset ADC conversion status and disable the selected ADC
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_ConversionStatus_Reset(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0U;
  
  /* Verification if ADC is not already disabled */
  if (ADC_IS_ENABLE(hadc) != RESET)
  {
    /* Disable the ADC peripheral */
    __HAL_ADC_DISABLE(hadc);
     
    /* Get tick count */
    tickstart = HAL_GetTick();
    
    /* Wait for ADC effectively disabled */
    while(ADC_IS_ENABLE(hadc) != RESET)
    {
      if((HAL_GetTick() - tickstart) > ADC_DISABLE_TIMEOUT)
      {
        /* Update ADC state machine to error */
        SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);
        
        return HAL_ERROR;
      }
    }
  }
  
  /* Return HAL status */
  return HAL_OK;
}

/**
  * @}
  */

#endif /* HAL_ADC_MODULE_ENABLED */
/**
  * @}
  */ /* End of group ADC ADC */




