/**
  ******************************************************************************
  * @file    system_cx32l003.c
	* @author  MCU Software Team
	* @Version V1.1.0
  * @Date    20-Nov-2019
  * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer System Source File.
  * 
  * 1.  This file provides two functions and one global variable to be called from 
  *     user application:
  *      - SystemInit(): Setups the system clock (System clock source, AHB/APB 
	*											 prescalers). This function is called at startup just 
	*											 after reset and before branch to main program. This call 
	*											 is made inside the "startup_cx32l003_xx.s" file.
  *                      
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick 
  *                                  timer or configure other parameters.
  *                                     
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  * 2. After each device reset the HIRC (4 MHz) is used as system clock source.
  *    Then SystemInit() function is called, in "startup_cx32l003_xx.s" file, to
  *    configure the system clock before to branch to main program.
  *
  * 4. The default value of HXT crystal is set to 8 MHz (or other values, depending on
  *    the crystal used), refer to "HXT_VALUE". 
  *    When HXT is used as system clock source directly and you are using different 
	*		 crystal you have to adapt the HSE value to your own configuration.
  *        
  ******************************************************************************
**/

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup cx32l003_system
  * @{
  */  
  
/** @addtogroup CX32L003_System_Private_Includes
  * @{
  */
#include "cx32l003.h"
#include "cx32l003_hal_rcc.h" 
/**
  * @}
  */


/** @addtogroup CX32L003_System_Private_Defines
  * @{
  */


/**
  * @}
  */

/**
  * @brief Adjust the value of External High Speed oscillator (HXT) used in your application.
  *        This value is used by the RCC HAL module to compute the system frequency
  */
#if !defined  (HXT_VALUE) 
  #define HXT_VALUE    ((uint32_t)8000000) /*!< Value of the External oscillator in Hz */
#endif /* HXT_VALUE */

/**
  * @brief Internal Low Speed Internal oscillator (LIRC) value.
  */
#if !defined  (LIRC_VALUE) 
 #define LIRC_VALUE               38400U    /*!< LIRC Typical Value in Hz */
#endif /* LIRC_VALUE */                     /*!< Value of the Internal Low Speed oscillator in Hz
                                                The real value may vary depending on the variations
                                                in voltage and temperature. */

/**
  * @brief Adjust the value of External Low Speed oscillator (LXT) used in your application.
  *        This value is used by the RCC HAL module to compute the system frequency  
  */
#if !defined  (LXT_VALUE)
  #define LXT_VALUE    ((uint32_t)32768) /*!< Value of the External oscillator in Hz*/
#endif /* LXT_VALUE */

/**
  * @brief External Low Speed oscillator (LSE) value.
  *        This value is used by the UART, RTC HAL module to compute the system frequency
  */
#if !defined  (LSE_VALUE)
  #define LSE_VALUE    ((uint32_t)32768) /*!< Value of the External oscillator in Hz*/
#endif /* LSE_VALUE */


/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */ 
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x00000000U /*!< Vector Table base offset field. */ 
// IAP功能，把此处地址修改，当切换正常程序时，影响到内部的HAL_Delay() 
//#define VECT_TAB_OFFSET  0x00002000U /*!< Vector Table base offset field. */ 

/**
  * @}
  */

/** @addtogroup CX32L003_System_Private_Variables
  * @{
  */

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/

uint32_t SystemCoreClock         = 4000000;        				/*!< System Clock Frequency Default(Core Clock) */

/**
  * @}
  */


/** @addtogroup CX32L003_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
	/* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HIRCEN bit, Reset HXTEN, HXTBYP, LIRCEN*/
	RCC->UNLOCK = RCC_UNLOCK_UNLOCK | (0x2AD5334C << RCC_UNLOCK_KEY_Pos);
	RCC->SYSCLKCR = RCC_SYSCLKCR_HIRCEN | (0x5A69 << RCC_SYSCLKCR_KEY_Pos);
	RCC->UNLOCK = (0x2AD5334C << RCC_UNLOCK_KEY_Pos) & RCC_UNLOCK_KEY;	
	
  /* Reset HCLK and PCLK div bits */	
	RCC->HCLKDIV = 0x00000000;
	RCC->PCLKDIV = 0x0000000;
	
  /* Reset AHB and APB module */	
	RCC->HCLKEN = 0x00000100;
	RCC->PCLKEN = 0x00000000;	

  /* Reset MCO bits */	
	RCC->MCOCR = 0x00000000;
	
#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_MEMORY_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
  SCB->VTOR = FLASH_MEMORY_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif 
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *           
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.         
  *     
  * @note   - The system frequency computed by this function is not the real 
  *           frequency in the chip. It is calculated based on the predefined 
  *           constant and the selected clock source:
  *             
  *           - If SYSCLK source is HIRC, SystemCoreClock will contain the HIRC_VALUE_xxM(*)
  *                                              
  *           - If SYSCLK source is HXT, SystemCoreClock will contain the HXT_VALUE(**)
  *         
  *         (*) HIRC_VALUE_xxM is a constant defined in cx32l003_hal_conf.h file (default value
  *             4 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.   
  *    
  *         (**) HXT_VALUE is a constant defined in cx32l003_hal_conf.h file (default value
  *              8 MHz, depending on the product used), user has to ensure
  *              that HXT_VALUE is same as the real frequency of the crystal used.
  *              Otherwise, this function may have wrong result.
  *                
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
  uint32_t tmp = 0U;
    
  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->SYSCLKSEL & RCC_SYSCLKSEL_CLKSW;
  
  switch (tmp)
  {
    case 0x01U:  /* HIRC used as system clock */
			if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_24M)
			{
				SystemCoreClock = HIRC_VALUE_24M;				
			}	
			else if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_22M)
			{
				SystemCoreClock = HIRC_VALUE_22M;					
			}			
			else if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_16M)
			{
				SystemCoreClock = HIRC_VALUE_16M;					
			}
			else if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_8M)
			{
				SystemCoreClock = HIRC_VALUE_8M;					
			}
			else if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_4M)
			{
				SystemCoreClock = HIRC_VALUE_4M;					
			}			
			else
			{
				SystemCoreClock = HIRC_VALUE_4M;						
			}
      break;	
    case 0x02U:  /* HXT used as system clock */
      SystemCoreClock = HXT_VALUE;
      break;
    case 0x04U:  /* LIRC used as system clock */
      SystemCoreClock = LIRC_VALUE;
      break;		
    case 0x08U:  /* LXT used as system clock */
      SystemCoreClock = LXT_VALUE;
      break;		
    default:
      SystemCoreClock = HIRC_VALUE_4M;
      break;
  }
  
  /* Compute HCLK clock frequency ----------------*/
	/* Get HCLK prescaler and caculate HCLK clock frequency*/  
  if((RCC->HCLKDIV & RCC_HCLKDIV_AHBCKDIV) != 0)
		SystemCoreClock = (SystemCoreClock>>1) / (RCC->HCLKDIV & RCC_HCLKDIV_AHBCKDIV);
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
