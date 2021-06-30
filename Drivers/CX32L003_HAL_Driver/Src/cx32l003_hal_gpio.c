/**
  ******************************************************************************
  * @file    cx32l003_hal_gpio.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   GPIO HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the General Purpose Input/Output (GPIO) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + GPIO_MODE_GPIO macro	
  *
  @verbatim
  ==============================================================================
                    ##### GPIO Peripheral features #####
  ==============================================================================
  [..]
  Subject to the specific hardware characteristics of each I/O port listed in the datasheet, each
  port bit of the General Purpose IO (GPIO) Ports, can be individually configured by software
  in several modes:
  (+) Input mode
  (+) Analog mode
  (+) Output mode
  (+) Alternate function mode
  (+) External interrupt lines

  [..]
  During and just after reset, the alternate functions and external interrupt
  lines are not active and the I/O ports are configured in input floating mode.

  [..]
  All GPIO pins have weak internal pull-up and pull-down resistors, which can be
  activated or not.

  [..]
  In Output or Alternate mode, each IO can be configured on open-drain or push-pull
  type and the IO slew rate can be selected.

  [..]
  All ports have external interrupt capability. To use external interrupt
  lines, the port must be configured in input mode.

  [..]
  The external interrupt controller consists of up to 16 edge detectors in devices for 
	generating interrupt requests. Each input line can be independently configured to 
	select the corresponding trigger event (rising or falling or both). Each line can also masked
  independently. A pending register maintains the status line of the interrupt requests

                     ##### How to use this driver #####
  ==============================================================================
 [..]
   (#) Enable the GPIO AHB clock using the following function : 
			 __HAL_RCC_GPIOA_CLK_ENABLE().
			 __HAL_RCC_GPIOB_CLK_ENABLE().
			 __HAL_RCC_GPIOC_CLK_ENABLE().
			 __HAL_RCC_GPIOD_CLK_ENABLE().			 
   (#) Configure the GPIO pin(s) using HAL_GPIO_Init().
       (++) Configure the IO mode using "Mode" member from GPIO_InitTypeDef structure
       (++) Activate Pull-up, Pull-down resistor using "Pull" member from GPIO_InitTypeDef
            structure.
       (++) Activate Pushpull, Opendrain using "OpenDrain" member from GPIO_InitTypeDef
            structure.						
       (++) In case of Output or alternate function mode selection: the SlewRate is
            configured through "SlewRate" member from GPIO_InitTypeDef structure
       (++) Analog mode is required when a pin is to be used as ADC channel.
       (++) In case of external interrupt selection the "Mode" member from
            GPIO_InitTypeDef structure select the corresponding trigger event 
						(rising or falling or both) through "Exti" member from GPIO_InitTypeDef structure.

   (#) In case of external interrupt mode selection, configure NVIC IRQ priority
       mapped to the EXTI line using HAL_NVIC_SetPriority() and enable it using
       HAL_NVIC_EnableIRQ().

   (#) To get the level of a pin configured in input mode use HAL_GPIO_ReadPin().

   (#) To set/reset the level of a pin configured in output mode use
       HAL_GPIO_WritePin()/HAL_GPIO_TogglePin().

   (#) During and just after reset, the alternate functions are not
       active and the GPIO pins are configured in input floating mode (except SWD
       pins).

   (#) The LXT oscillator pins X32_IN and X32_OUT can be used as general purpose
       (PB5 and PB4, respectively) when the LXT oscillator is off. The LXT has
       priority over the GPIO function.

   (#) The HXT oscillator pins OSC_IN and OSC_OUT can be used as general purpose
       (PA1 and PA2, respectively) when the HXT oscillator is off. The HXT has
       priority over the GPIO function.

  @endverbatim
  ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"


/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @defgroup GPIO GPIO
  * @brief GPIO HAL module driver
  * @{
  */

#ifdef HAL_GPIO_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup GPIO_Private_Constants GPIO Private Constants
  * @{
  */

#define GPIO_NUMBER           8U


/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup GPIO_Exported_Functions GPIO Exported Functions
  * @{
  */

/** @defgroup GPIO_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
  [..]
    This section provides functions allowing to initialize and de-initialize the GPIOs
    to be ready for use.

@endverbatim
  * @{
  */


/**
  * @brief  Initializes the GPIOx peripheral according to the specified parameters in the GPIO_Init.
  * @param  GPIOx where x can be (A..D) to select the GPIO peripheral for CX32L003 device
  * @param  GPIO_Init pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
  uint32_t position ;
  uint32_t ioposition = 0x00U;
  uint32_t iocurrent = 0x00U;
  uint32_t temp = 0x00U;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Init->Pin));
  assert_param(IS_GPIO_MODE(GPIO_Init->Mode));
  assert_param(IS_GPIO_PULL(GPIO_Init->Pull));
	
  /* Configure the port pins */
  for(position = 0U; position < GPIO_NUMBER; position++)
  {
    /* Get the IO position */
    ioposition = 0x01U << position;
    /* Get the current IO position */
    iocurrent = (uint32_t)(GPIO_Init->Pin) & ioposition;
		
    if(iocurrent == ioposition)
    {
      /*------------------------- EXTI Mode Configuration --------------------*/
      GPIOx->INTEN &= ~(GPIO_INTEN_PxIEN0 << (position * 1U));

      GPIOx->INTTYPCR &= ~(GPIO_INTTYPCR_PxITYPE0 << (position * 1U));

      GPIOx->INTPOLCR &= ~(GPIO_INTPOLCR_PxIVAL0 << (position * 1U));

      GPIOx->INTANY &= ~(GPIO_INTANY_PxIANY0 << (position * 1U));
			
      /*------------------------- GPIO Mode Configuration --------------------*/
      /* Configure the default Alternate Function in current IO */
      GPIOx->AFR &= ~(GPIO_AFR_PxAFR0 << (position * 4U));

      /* Configure the default value for inout mode */
      GPIOx->DIRCR &= ~(GPIO_DIRCR_PxDIR0 << (position * 1U));			
	
      /* Configure the default value for debounce */
      GPIOx->INDBEN &= ~(GPIO_INDBEN_PxDIDB << (position * 1U));		
			
      /* Configure the default value for slew rate */
      GPIOx->SLEWCR |= GPIO_SLEWCR_PASR0 << (position * 1U);

      /* Deactivate the Pull-up and Pull-down resistor for the current IO */
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PxPUPD0 << (position * 2U));
			
      if(GPIO_Init->Mode == GPIO_MODE_AF)
      {
        /* Check the Alternate function parameter */
        assert_param(IS_GPIO_AF(GPIO_Init->Alternate));
        /* Configure Alternate function mapped with the current IO */				
        temp = GPIOx->AFR;
        temp &= ~(0xFU << ((uint32_t)(position & 0x07U) * 4U)) ;
        temp |= ((uint32_t)(GPIO_Init->Alternate) << (((uint32_t)position & 0x07U) * 4U));
        GPIOx->AFR = temp;
      }
			
      /* In case of Gpio function mode selection */
      if(GPIO_Init->Mode == GPIO_MODE_GPIO)
      {
        /* Configure Alternate function mapped with the current IO */				
        temp = GPIOx->AFR;
        temp &= ~(0xFU << ((uint32_t)(position & 0x07U) * 4U)) ;
        GPIOx->AFR = temp;
      }			
			
      /* In case of Analog function mode selection */
      if(GPIO_Init->Mode == GPIO_MODE_ANALOG)
      {
        /* Configure Analog function mapped with the current IO */			
        temp = GPIOx->AFR;
        temp &= ~(0xFU << ((uint32_t)(position & 0x07U) * 4U));
        temp |= ((uint32_t)(0x0FU) << (((uint32_t)position & 0x07U) * 4U));
        GPIOx->AFR = temp; 
      }

      /* In case of Input function mode selection */
      if(GPIO_Init->Mode == GPIO_MODE_INPUT)
      {
        /* Configure Input function IO */				
        temp = GPIOx->DIRCR;
        temp &= ~(0x01U << ((uint32_t)(position & 0x07U) * 1U)) ;
        GPIOx->DIRCR = temp; 
      }			
			
      /* In case of Output or Alternate function mode selection */
      if(GPIO_Init->Mode == GPIO_MODE_OUTPUT)
      {
        /* Configure Output function IO */				
        temp = GPIOx->DIRCR;
        temp &= ~(0x01U << ((uint32_t)(position & 0x07U) * 1U)) ;
        temp |= ((uint32_t)(0x01U) << (((uint32_t)position & 0x07U) * 1U));        
								GPIOx->DIRCR = temp; 
      }			
			
			/* Configure debounce function for Input function IO */
			if(GPIO_Init->Debounce.Enable == GPIO_DEBOUNCE_ENABLE)
			{
				/* Configure debounce clock divider for Input function IO */					
				GPIOx->DBCLKCR |= GPIO_Init->Debounce.DebounceClk << GPIO_DBCLKCR_DBCLK_DIV_Pos;
				
				/* Enable debounce function for Input function IO */						
				temp = GPIOx->INDBEN;
				temp &= ~(0x01U << ((uint32_t)(position & 0x07U) * 1U)) ;
				temp |= GPIO_Init->Debounce.Enable << ((uint32_t)(position & 0x07U) * 1U);	
				GPIOx->INDBEN = temp;	
			}
			else if(GPIO_Init->Debounce.TwoLevelSync == GPIO_SYNC_ENABLE)
			{
				/* Disable debounce function for Input function IO */					
				temp = GPIOx->INDBEN;
				temp &= ~(0x01U << ((uint32_t)(position & 0x07U) * 1U)) ;
				GPIOx->INDBEN = temp;						

				/* Disable debounce clock for Input function IO */		
				temp = GPIOx->DBCLKCR;
				temp &= ~(0x01U << GPIO_DBCLKCR_DBCLKEN_Pos);
				GPIOx->DBCLKCR = temp;				
							
				/* Configure two level sync function for Input function IO */					
				temp = GPIOx->INDBEN;
				temp &= ~(0x01U << GPIO_INDBEN_SYNC_EN_Pos);
				temp |= GPIO_Init->Debounce.TwoLevelSync;	
				GPIOx->INDBEN = temp;		 					
			}
			else
			{
				/* Disable debounce function for Input function IO */					
				temp = GPIOx->INDBEN;
				temp &= ~(0x01U << ((uint32_t)(position & 0x07U) * 1U));
				GPIOx->INDBEN = temp;								
			}
			/* Enable debounce function clock */			
			if((GPIOx->INDBEN & GPIO_INDBEN_PxDIDB) != 0x0U)
			{
				/* Enable debounce clock for Input function IO */						
				GPIOx->DBCLKCR |= GPIO_Init->Debounce.Enable << GPIO_DBCLKCR_DBCLKEN_Pos;		
			}
			else
			{
				/* Disable debounce clock for Input function IO */		
				GPIOx->DBCLKCR &= ~(0x01U << GPIO_DBCLKCR_DBCLKEN_Pos);	
			}		
			/*------------------------- GPIO Mode Configuration --------------------*/
      /* Activate the Pull-up or Pull down resistor for the current IO */
      temp = GPIOx->PUPDR;
      temp &= ~(GPIO_PUPDR_PxPUPD0 << (position * 2U));
      temp |= ((GPIO_Init->Pull) << (position * 2U));
      GPIOx->PUPDR = temp; 

      /* Activate the pushpull or opendrain for the current IO */
      temp = GPIOx->OTYPER;
      temp &= ~(GPIO_OTYPER_PxOTYP0_Msk << (position * 1U));
      temp |= ((GPIO_Init->OpenDrain) << (position * 1U));
      GPIOx->OTYPER = temp;	
			
      /* Set the slew rate for the current IO */
      temp = GPIOx->SLEWCR;
      temp &= ~(GPIO_SLEWCR_PASR0 << (position * 1U));
      temp |= ((GPIO_Init->SlewRate) << (position * 1U));
      GPIOx->SLEWCR = temp;	
			
      /* Set the driver strength for the current IO */
      temp = GPIOx->DRVCR;
      temp &= ~(GPIO_DRVCR_PxDRV0 << (position * 1U));
      temp |= ((GPIO_Init->DrvStrength) << (position * 1U));
      GPIOx->DRVCR = temp;			
			
      /*--------------------- EXTI Mode Configuration ------------------------*/
      /* Configure the External Interrupt or event for the current IO */
      if((GPIO_Init->Mode & EXTI_MODE) == EXTI_MODE)
      {
        /* Set the exti for the current IO */
        temp = GPIOx->INTEN;
        temp &= ~(GPIO_INTEN_PxIEN0 << (position * 1U));
        temp |= ((GPIO_Init->Exti.Enable) << (position * 1U));
        GPIOx->INTEN = temp;		
        
        temp = GPIOx->INTTYPCR;
        temp &= ~(GPIO_INTTYPCR_PxITYPE0 << (position * 1U));
        temp |= ((GPIO_Init->Exti.EdgeLevelSel) << (position * 1U));
        GPIOx->INTTYPCR = temp;			
        
        if((GPIO_Init->Exti.RiseFallSel == GPIO_EXTI_INT_LOWFALL) || (GPIO_Init->Exti.RiseFallSel == GPIO_EXTI_INT_HIGHRISE))
        {
          temp = GPIOx->INTANY;
          temp &= ~(GPIO_INTANY_PxIANY0 << (position * 1U));					
          GPIOx->INTANY = temp;	
          
          temp = GPIOx->INTPOLCR;
          temp &= ~(GPIO_INTPOLCR_PxIVAL0 << (position * 1U));
          temp |= ((GPIO_Init->Exti.RiseFallSel) << (position * 1U));
          GPIOx->INTPOLCR = temp;		
        }
        else
        {
          temp = GPIOx->INTANY;
          temp &= ~(GPIO_INTANY_PxIANY0 << (position * 1U));	
          temp |= 0x01U << (position * 1U);					
          GPIOx->INTANY = temp;		
        }
      }
    }
  }
}

/**
  * @brief  De-initializes the GPIOx peripheral registers to their default reset values.
  * @param  GPIOx where x can be (A..D) to select the GPIO peripheral for CX32L003 device
  * @param  GPIO_Pin specifies the port bit to be written.
  *          This parameter can be one of GPIO_PIN_x where x can be (0..7).
  * @retval None
  */
void HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
  uint32_t position;
  uint32_t ioposition = 0x00U;
  uint32_t iocurrent = 0x00U;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  
  /* Configure the port pins */
  for(position = 0U; position < GPIO_NUMBER; position++)
  {
    /* Get the IO position */
    ioposition = 0x01U << position;
    /* Get the current IO position */
    iocurrent = (GPIO_Pin) & ioposition;

    if(iocurrent == ioposition)
    {
      /*------------------------- EXTI Mode Configuration --------------------*/
			GPIOx->INTEN &= ~(GPIO_INTEN_PxIEN0 << (position * 1U));

			GPIOx->INTTYPCR &= ~(GPIO_INTTYPCR_PxITYPE0 << (position * 1U));

			GPIOx->INTPOLCR &= ~(GPIO_INTPOLCR_PxIVAL0 << (position * 1U));
		
			GPIOx->INTANY &= ~(GPIO_INTANY_PxIANY0 << (position * 1U));
			
      /*------------------------- GPIO Mode Configuration --------------------*/
      /* Configure the default Alternate Function in current IO */
      GPIOx->AFR &= ~(GPIO_AFR_PxAFR0 << (position * 4U));

      /* Configure the default value for inout mode */
      GPIOx->DIRCR &= ~(GPIO_DIRCR_PxDIR0 << (position * 1U));			
	
      /* Configure the default value for debounce */
      GPIOx->INDBEN &= ~(GPIO_INDBEN_PxDIDB << (position * 1U));		
			
      /* Configure the default value for slew rate */
      GPIOx->SLEWCR |= GPIO_SLEWCR_PASR0 << (position * 1U);

      /* Deactivate the Pull-up and Pull-down resistor for the current IO */
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PxPUPD0 << (position * 2U));
    }
  }
}

/**
  * @}
  */ /* End of group GPIO_Exported_Functions_Group1 */

/** @defgroup GPIO_Exported_Functions_Group2 IO operation functions
 *  @brief   GPIO Read and Write
 *
@verbatim
 ===============================================================================
                       ##### IO operation functions #####
 ===============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the GPIOs.

@endverbatim
  * @{
  */

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: specifies the port bit to read.
  *         This parameter can be GPIO_PIN_x where x can be (0..7).
  * @retval The input port pin value.
  */
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  GPIO_PinState bitstatus;

  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Sets or clears the selected data port bit.
  *
  * @note   This function uses GPIOx_ODSET register to allow atomic read/modify
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  *
  * @param  GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: specifies the port bit to be written.
  *          This parameter can be one of GPIO_PIN_x where x can be (0..7).
  * @param  PinState: specifies the value to be written to the selected bit.
  *          This parameter can be one of the GPIO_PinState enum values:
  *            @arg GPIO_PIN_RESET: to clear the port pin
  *            @arg GPIO_PIN_SET: to set the port pin
  * @retval None
  */
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_PIN_ACTION(PinState));

  if (PinState != GPIO_PIN_RESET)
  {
    GPIOx->ODSET = GPIO_Pin;
  }
  else
  {
    GPIOx->ODCLR = GPIO_Pin;
  }
}

/**
  * @brief  Toggles the specified GPIO pin
  * @param  GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  * @retval None
  */
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR ^= GPIO_Pin; 
}


/**
  * @brief  This function handles EXTI interrupt request.
  * @param  GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */	
void HAL_GPIO_EXTI_IRQHandler(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{	
  /* EXTI line interrupt detected */	
  if (__HAL_GPIO_EXTI_GET_FLAG(GPIOx, GPIO_Pin) != RESET)
  {
				__HAL_GPIO_EXTI_CLEAR_FLAG(GPIOx, GPIO_Pin);
		
		/*uncomment the code below to let interrupt entered only once*/
		
    HAL_GPIO_EXTI_Callback(GPIOx, GPIO_Pin);
  }	
}


/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
__weak void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
	 UNUSED(GPIOx);
  UNUSED(GPIO_Pin);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}

/**
  * @}
  */ /* End of group GPIO_Exported_Functions_Group2 */

/**
  * @}
  */ /* End of group GPIO_Exported_Functions */

#endif /* HAL_GPIO_MODULE_ENABLED */

/**
  * @}
  */ /* End of group GPIO GPIO */


/**
  * @}
  */ /* group CX32L003_HAL_Driver */

