/**
  ******************************************************************************
  * @file    cx32l003_hal_rtc.c
  * @author  MCU Software Team
  * @Version V1.2.0
  * @Date    2021-01-11
  * @brief   RTC HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Real Time Clock (RTC) peripheral:
  *           + Initialization and de-initialization functions
  *           + RTC Time and Date functions
  *           + RTC Alarm functions
  *           + Peripheral Control functions   
  *           + Peripheral State functions
  *         
  @verbatim
  ==============================================================================
                  ##### How to use this driver #####
  ==================================================================
  [..] 
    (+) Enable the RTC domain access (see description in the section above).
    (+) Configure the RTC Prescaler (Asynchronous prescaler to generate RTC 1Hz time base) 
        using the HAL_RTC_Init() function.
  
  *** Time and Date configuration ***
  ===================================
  [..] 
    (+) To configure the RTC Calendar (Time and Date) use the HAL_RTC_SetTime() 
        and HAL_RTC_SetDate() functions.
    (+) To read the RTC Calendar, use the HAL_RTC_GetTime_Date() functions.
  
  *** Alarm configuration ***
  ===========================
  [..]
    (+) To configure the RTC Alarm use the HAL_RTC_Alarm1_SetTime() and  HAL_RTC_Alarm1_SetDate()function. 
    (+) To read the RTC Alarm, use the HAL_RTC_Alarm1_GetTime() and HAL_RTC_Alarm1_GetDate() function.
    
  
                      ##### Backup Domain Operating Condition #####
  ==============================================================================
  [..] The real-time clock (RTC) and the RTC backup registers can be powered
       from the VBAT voltage when the main VDD supply is powered off.
       To retain the content of the RTC backup registers and supply the RTC 
       when VDD is turned off, VBAT pin can be connected to an optional 
       standby voltage supplied by a battery or by another source.

  [..] To allow the RTC operating even when the main digital supply (VDD) is turned
       off, the VBAT pin powers the following blocks:
    (+) The RTC
    (+) The LSE oscillator

    
                  ##### RTC and low power modes #####
  ==================================================================
  [..] The MCU can be woken up from a low power mode by an RTC alternate 
       function.
  [..] The RTC alternate functions are the RTC alarms (Alarm 1), 
       and RTC tamper event detection.
       These RTC alternate functions can wake up the system from the Stop and 
       Standby low power modes.
  [..] The system can also wake up from low power modes without depending 
       on an external interrupt (Auto-wakeup mode), by using the RTC alarm.
     
   @endverbatim
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */


/** @defgroup RTC RTC
  * @brief RTC HAL module driver
  * @{
  */

#ifdef HAL_RTC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup RTC_Private_Constants RTC Private Constants
  * @{
  */
#define RTC_READ_TIMEOUT					0x08U
#define RTC_TIMEOUT_VALUE					0X10000U
/**
  * @}
  */


/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RTC_Private_Functions RTC Private Functions
  * @{
  */
static void RTC_Disable_Write_Protected(RTC_HandleTypeDef *hrtc);
static HAL_StatusTypeDef  RTC_Enter_Init_Mode(RTC_HandleTypeDef* hrtc);
static HAL_StatusTypeDef  RTC_Exit_Init_Mode(RTC_HandleTypeDef* hrtc);
static uint8_t            RTC_ByteToBcd2(uint8_t Value);
static uint8_t            RTC_Bcd2ToByte(uint8_t Value);

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup RTC_Exported_Functions RTC Exported Functions
  * @{
  */
  
/** @defgroup RTC_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
 @endverbatim
  * @{
  */

/**
  * @brief  Initializes the RTC peripheral 
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_Init(RTC_HandleTypeDef *hrtc)
{
	uint32_t hxt_div = 0X00U;
  /* Check input parameters */
	if(hrtc == NULL)
	{
		return HAL_ERROR;
	}
   /* Check the parameters */
	assert_param(IS_RTC_ALL_INSTANCE(hrtc->Instance));
	assert_param(IS_RTC_CLOCK_SOURCE(hrtc->Init.ClockSource));
	assert_param(IS_RTC_HOUR_FORMAT(hrtc->Init.HourFormat));
	assert_param(IS_RTC_TIME_ADJUST_MODE(hrtc->Init.TimeAdjustMode));
	assert_param(IS_RTC_TIME_TRIM(hrtc->Init.TimeTrim));
    
    if(hrtc->State == HAL_RTC_STATE_RESET)
	{
		/* Allocate lock resource and initialize it */
		hrtc->Lock = HAL_UNLOCKED;
		/* Initialize RTC MSP */
		HAL_RTC_MspInit(hrtc);
	}
  
	/* Set RTC state */  
	hrtc->State = HAL_RTC_STATE_BUSY;  
	/* Clear Flags Bits */
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->INTCLR);
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->ISR);
  
	if(hrtc->Init.ClockSource == RTC_CLOCK_HXT)
	{
      /* RTC Prescaler will be automatically calculated to get 1 second timebase */
      /* Get the RTCCLK frequency */
		hxt_div = HXT_VALUE/1000;
     /* Check that RTC clock is enabled*/
		if (hxt_div == 0U)
		{
        /* Should not happen. Frequency is not available*/
			hrtc->State = HAL_RTC_STATE_ERROR;
			return HAL_ERROR;
		}
		else
		{
        /* RTC clk F=Fhxt/(HXTDIV[9:0]),set HXTDIV */
			RTC_Disable_Write_Protected(hrtc);
			SET_BIT(hrtc->Instance->CLKCR,(hxt_div&RTC_CLKCR_HXTDIV));
			if(hxt_div >= RTC_BYPASS_HAD_MAX)
			{
				RTC_Disable_Write_Protected(hrtc);
				CLEAR_BIT(hrtc->Instance->CR,RTC_CR_BYPSHAD);
			}
			else
			{
				RTC_Disable_Write_Protected(hrtc);
				SET_BIT(hrtc->Instance->CR,RTC_CR_BYPSHAD);
			}
		}
	}
	else
	{ 
		RTC_Disable_Write_Protected(hrtc);
		CLEAR_BIT(hrtc->Instance->CLKCR,RTC_CLKCR_HXTDIV);
	}
  
	RTC_Disable_Write_Protected(hrtc);
	SET_BIT(hrtc->Instance->CLKCR,hrtc->Init.ClockSource);
	RTC_Disable_Write_Protected(hrtc);
	SET_BIT(hrtc->Instance->CLKCR,RTC_CLKCR_RTCCKEN);
	  /* set hour format Bits */
	RTC_Disable_Write_Protected(hrtc);
	if(hrtc->Init.HourFormat != RTC_HOURFORMAT_12)
	    SET_BIT(hrtc->Instance->CR, RTC_HOURFORMAT_24);
	else
	   CLEAR_BIT(hrtc->Instance->CR, RTC_HOURFORMAT_24);
    /* Initialize date to 1st of January 2000 */
    hrtc->DateToUpdate.Year = 0x2000U;
    hrtc->DateToUpdate.Month = RTC_MONTH_JANUARY;
    hrtc->DateToUpdate.Date = 0x01U;
	hrtc->DateToUpdate.WeekDay= RTC_WEEKDAY_SATURDAY;

	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->RCLKTRIM);
	RTC_Disable_Write_Protected(hrtc);
	SET_BIT(hrtc->Instance->RCLKTRIM,hrtc->Init.TimeAdjustMode | hrtc->Init.TimeTrim);
		
	__HAL_RTC_ENABLE(hrtc);
    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_READY;
    
    return HAL_OK;
}

/**
  * @brief  DeInitializes the RTC peripheral 
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @note   This function does not reset the RTC Backup Data registers.   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_DeInit(RTC_HandleTypeDef *hrtc)
{
  /* Check input parameters */
	if(hrtc == NULL)
	{
		return HAL_ERROR;
	}
  
	/* Check the parameters */
	assert_param(IS_RTC_ALL_INSTANCE(hrtc->Instance));
	/* Set RTC state */
	hrtc->State = HAL_RTC_STATE_BUSY; 
  
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->CR);
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->CLKCR);
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->TIME);
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->DATE);
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->ALM1TIME);
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->ALM1DATE);
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->ALM2PRD);
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->RCLKTRIM);
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_REG(hrtc->Instance->INTCLR);
	RTC_Disable_Write_Protected(hrtc);
	CLEAR_BIT(hrtc->Instance->ISR,(RTC_ISR_RSF | RTC_ISR_ALM1_F)|RTC_ISR_ALM2_F );
       
	/* De-Initialize RTC MSP */
	HAL_RTC_MspDeInit(hrtc);

	hrtc->State = HAL_RTC_STATE_RESET; 
	/* Release Lock */
	__HAL_UNLOCK(hrtc);

	return HAL_OK;
}

/**
  * @brief  Initializes the RTC MSP.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.  
  * @retval None
  */
__weak void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
  /* Prevent unused argument(s) compilation warning */
	UNUSED(hrtc);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTC_MspInit could be implemented in the user file
   */ 
}

/**
  * @brief  DeInitializes the RTC MSP.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC. 
  * @retval None
  */
__weak void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{
  /* Prevent unused argument(s) compilation warning */
	UNUSED(hrtc);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTC_MspDeInit could be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup RTC_Exported_Functions_Group2 Time and Date functions
 *  @brief   RTC Time and Date functions
 *
@verbatim   
 ===============================================================================
                 ##### RTC Time and Date functions #####
 ===============================================================================  
 
 [..] This section provides functions allowing to configure Time and Date features

@endverbatim
  * @{
  */

/**
  * @brief  Sets RTC current time.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTime: Pointer to Time structure
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_HOURFORMAT_12: 12 hour system
  *            @arg RTC_HOURFORMAT_24: 24 hour system
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Hour_Format)
{
	uint32_t time_reg = 0;
	/* Check input parameters */
	if((hrtc == NULL) || (sTime == NULL))
	{
		return HAL_ERROR;
	}
	/* Check the parameters */
	assert_param(IS_RTC_HOUR_FORMAT(Hour_Format));
   /* Process Locked */ 
	__HAL_LOCK(hrtc);
  
	hrtc->State = HAL_RTC_STATE_BUSY;
	/* Check the parameters */
	assert_param(IS_RTC_HOUR24(sTime->Hours));
	assert_param(IS_RTC_MINUTES(sTime->Minutes));
	assert_param(IS_RTC_SECONDS(sTime->Seconds));

	if(Hour_Format != hrtc->Init.HourFormat)
	{
		hrtc->Init.HourFormat = Hour_Format;
		RTC_Disable_Write_Protected(hrtc);
		if(hrtc->Init.HourFormat != RTC_HOURFORMAT_12)
			SET_BIT(hrtc->Instance->INTCLR, RTC_HOURFORMAT_24);
		else
			CLEAR_BIT(hrtc->Instance->INTCLR, RTC_HOURFORMAT_24);
	}
  
	if(Hour_Format == RTC_HOURFORMAT_12)
	{
		if(sTime->Hours > 12)
		{
			time_reg = RTC_TIME_H20_PA;
			time_reg |= (RTC_ByteToBcd2(sTime->Hours-12)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
		else
		{
			time_reg |= (RTC_ByteToBcd2(sTime->Hours)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
			
	}
	else
	{
		if(sTime->Hours > 19)
		{
			time_reg = RTC_TIME_H20_PA;
			time_reg |= (RTC_ByteToBcd2(sTime->Hours-20)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
		else
		{
			time_reg |= (RTC_ByteToBcd2(sTime->Hours)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
		
	}
	time_reg |= (RTC_ByteToBcd2(sTime->Minutes)<<RTC_TIME_MIN_Pos)&RTC_TIME_MIN;
	time_reg |= RTC_ByteToBcd2(sTime->Seconds)&RTC_BCD_TO_BYTE_MASK;
	time_reg |= (hrtc->Instance->TIME&RTC_TIME_WEEK);
	/* Set Initialization mode */
	if(RTC_Enter_Init_Mode(hrtc) != HAL_OK)
	{
		/* Set RTC state */
		hrtc->State = HAL_RTC_STATE_ERROR;
		/* Release Lock */
		__HAL_UNLOCK(hrtc);

		return HAL_ERROR;
	}  
	
	RTC_Disable_Write_Protected(hrtc);
	WRITE_REG(hrtc->Instance->TIME,time_reg);
    /* Exit read/writ mode in RTC registers */
	if(RTC_Exit_Init_Mode(hrtc) != HAL_OK)
	{       
		hrtc->State = HAL_RTC_STATE_ERROR;
		/* Process Unlocked */ 
		__HAL_UNLOCK(hrtc);
      
		return HAL_ERROR;
	}
    
	hrtc->State = HAL_RTC_STATE_READY;
  
	__HAL_UNLOCK(hrtc); 
     
	return HAL_OK;
     
}


/**
  * @brief  Sets RTC current time��date.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTime: Pointer to Time structure
	* @param  sDate: Pointer to date structure
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_HOURFORMAT_12: 12 hour system
  *            @arg RTC_HOURFORMAT_24: 24 hour system
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetTime_SetDate(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Hour_Format, RTC_DateTypeDef *sDate)
{
	uint32_t time_reg = 0;
	uint32_t years = 0U;
	uint32_t data_reg = 0;
	/* Check input parameters */
	if((hrtc == NULL) || (sTime == NULL)|| (sDate == NULL))
	{
		return HAL_ERROR;
	}
	/* Check the parameters */
	assert_param(IS_RTC_HOUR_FORMAT(Hour_Format));
	
	assert_param(IS_RTC_HOUR24(sTime->Hours));
	assert_param(IS_RTC_MINUTES(sTime->Minutes));
	assert_param(IS_RTC_SECONDS(sTime->Seconds));

	assert_param(IS_RTC_YEAR(sDate->Year));
	assert_param(IS_RTC_MONTH(sDate->Month));
	assert_param(IS_RTC_DATE(sDate->Date));
	assert_param(IS_RTC_WEEKDAY(sDate->WeekDay));
   /* Process Locked */ 
	__HAL_LOCK(hrtc);

	hrtc->State = HAL_RTC_STATE_BUSY;

	
	if(Hour_Format != hrtc->Init.HourFormat)
	{
		hrtc->Init.HourFormat = Hour_Format;
		RTC_Disable_Write_Protected(hrtc);
		if(hrtc->Init.HourFormat != RTC_HOURFORMAT_12)
			SET_BIT(hrtc->Instance->INTCLR, RTC_HOURFORMAT_24);
		else
			CLEAR_BIT(hrtc->Instance->INTCLR, RTC_HOURFORMAT_24);
	}
	
	if(Hour_Format == RTC_HOURFORMAT_12)
	{
		if(sTime->Hours >= 12)
		{
			time_reg = RTC_TIME_H20_PA;
			time_reg |= (RTC_ByteToBcd2(sTime->Hours-12)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
		else
		{
			time_reg = (RTC_ByteToBcd2(sTime->Hours)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
		
	}
	else
	{
		if(sTime->Hours > 19)
		{
			time_reg = RTC_TIME_H20_PA;
			time_reg |= (RTC_ByteToBcd2(sTime->Hours-20)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
		else
		{
			time_reg |= (RTC_ByteToBcd2(sTime->Hours)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
		
	}
	
	time_reg |= (RTC_ByteToBcd2(sTime->Minutes)<<RTC_TIME_MIN_Pos)&RTC_TIME_MIN;
	time_reg |= RTC_ByteToBcd2(sTime->Seconds)&RTC_BCD_TO_BYTE_MASK;
	time_reg |= (sDate->WeekDay << RTC_TIME_WEEK_Pos);
	
	/* Change the current date */
	hrtc->DateToUpdate.Year  = sDate->Year;
	hrtc->DateToUpdate.Month = sDate->Month;
	hrtc->DateToUpdate.Date  = sDate->Date;
	hrtc->DateToUpdate.WeekDay= sDate->WeekDay;
	
	/* Read the time counter*/
	if (sDate->Year >= 2000)
	{
		years = sDate->Year-2000;
		data_reg |= RTC_DATE_CEN;
	}
	else
	{
		years = sDate->Year-1900;
	}
	
	
	data_reg |= ((RTC_ByteToBcd2((uint8_t)years))<<RTC_DATE_YEAR_Pos)&RTC_DATE_YEAR;
	data_reg |= (((uint32_t)(RTC_ByteToBcd2(sDate->Month))<<RTC_DATE_MONTH_Pos)&RTC_DATE_MONTH);
	data_reg |= RTC_ByteToBcd2(sDate->Date)&RTC_DATE_DAY;
	
	/* Set Initialization mode */
	if(RTC_Enter_Init_Mode(hrtc) != HAL_OK)
	{
		/* Set RTC state */
		hrtc->State = HAL_RTC_STATE_ERROR;
		/* Release Lock */
		__HAL_UNLOCK(hrtc);

		return HAL_ERROR;
	}  
	
	RTC_Disable_Write_Protected(hrtc);
	WRITE_REG(hrtc->Instance->TIME,time_reg);	
	RTC_Disable_Write_Protected(hrtc);
	WRITE_REG(hrtc->Instance->DATE,data_reg);

    /* Exit read/writ mode in RTC registers */
	if(RTC_Exit_Init_Mode(hrtc) != HAL_OK)
	{       
		hrtc->State = HAL_RTC_STATE_ERROR;
		/* Process Unlocked */ 
		__HAL_UNLOCK(hrtc);
      
		return HAL_ERROR;
	}
    
	hrtc->State = HAL_RTC_STATE_READY;
	__HAL_UNLOCK(hrtc); 
 
	return HAL_OK;
}
/**
  * @brief  Gets RTC current time and date.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTime: Pointer to Time structure
  * @param  sDate: Pointer to Date structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_GetTime_Date(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime,RTC_DateTypeDef *sDate)
{
	uint32_t counter_times = 0U, time1_reg = 0U, date1_reg = 0U,time2_reg = 0U, date2_reg = 0U;
	HAL_StatusTypeDef read_ok = HAL_ERROR;
	/* Check input parameters */
	if((hrtc == NULL) || (sTime == NULL))
	{
		return HAL_ERROR;
	}
    /* Check if Bypass Shadow register */
	if (READ_BIT(hrtc->Instance->CR,RTC_CR_BYPSHAD) != RESET)
	{
		counter_times = RTC_READ_TIMEOUT;
		do
		{
			time1_reg = hrtc->Instance->TIME;
			date1_reg = hrtc->Instance->DATE;
			time2_reg = hrtc->Instance->TIME;
			date2_reg = hrtc->Instance->DATE;
			
			if((time1_reg == time2_reg) && (date1_reg == date2_reg))
				read_ok = HAL_OK;
		}while((read_ok != HAL_OK) && (counter_times-- > 0));

		if(read_ok != HAL_OK)
		{
			/* Set RTC state */
			hrtc->State = HAL_RTC_STATE_ERROR;
		    
			/* Release Lock */
			__HAL_UNLOCK(hrtc);

			return HAL_ERROR;
		}
	}
	else
	{
		while(RTC_Get_RSF_Flag() == RESET);
		time1_reg = hrtc->Instance->TIME;
		date1_reg = hrtc->Instance->DATE;
	
		RTC_Clear_RSF_Flag();
	}
  /* Fill the structure fields with the read parameters */
   if((time1_reg & RTC_TIME_H20_PA) == RESET)
   {
		if (hrtc->Init.HourFormat == RTC_HOURFORMAT_12)
	  { 
	    sTime->Hours =  RTC_Bcd2ToByte((uint8_t)((time1_reg & RTC_TIME_HOUR19_Msk)>>RTC_TIME_HOUR19_Pos));
        if(sTime->Hours >= 12)
           sTime->Hours -= 12;
	  }
	  else
		sTime->Hours = RTC_Bcd2ToByte((uint8_t)((time1_reg & RTC_TIME_HOUR19_Msk)>>RTC_TIME_HOUR19_Pos));
	}
	else
	{
		if (hrtc->Init.HourFormat == RTC_HOURFORMAT_12)
		{ 
			sTime->Hours = 12 + RTC_Bcd2ToByte((uint8_t)((time1_reg & RTC_TIME_HOUR19_Msk)>>RTC_TIME_HOUR19_Pos));
			if(sTime->Hours >= 24)
               sTime->Hours -= 12;
		}
		else
			sTime->Hours = 20+ RTC_Bcd2ToByte((uint8_t)((time1_reg & RTC_TIME_HOUR19_Msk)>>RTC_TIME_HOUR19_Pos));
	}
	sTime->Minutes = RTC_Bcd2ToByte((uint8_t)((time1_reg & RTC_TIME_MIN)>>RTC_TIME_MIN_Pos));
	sTime->Seconds = RTC_Bcd2ToByte((uint8_t)(time1_reg & RTC_BCD_TO_BYTE_MASK));

	
	if ((date1_reg & RTC_DATE_CEN) != RESET)
		sDate->Year= 2000 + RTC_Bcd2ToByte((uint8_t)((date1_reg & RTC_DATE_YEAR)>>RTC_TIME_HOUR19_Pos));
	else
		sDate->Year= 1900 + RTC_Bcd2ToByte((uint8_t)((date1_reg & RTC_DATE_YEAR)>>RTC_TIME_HOUR19_Pos));
	
	sDate->Month= RTC_Bcd2ToByte((uint8_t)((date1_reg & RTC_DATE_MONTH)>>RTC_DATE_MONTH_Pos));
	sDate->Date = RTC_Bcd2ToByte((uint8_t)(date1_reg & RTC_DATE_DAY));
	sDate->WeekDay = (uint8_t)((time1_reg & RTC_TIME_WEEK)>>RTC_TIME_WEEK_Pos);
    /* Update date */
    hrtc->DateToUpdate.Date = sDate->Date;
	hrtc->DateToUpdate.Month = sDate->Month;
	hrtc->DateToUpdate.Year = sDate->Year;
	hrtc->DateToUpdate.WeekDay = sDate->WeekDay;
  
    return HAL_OK;
}


/**
  * @brief  Sets RTC current date.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sDate: Pointer to date structure
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_RTC_SetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate)
{
	uint32_t years = 0U, data_reg = 0;
	/* Check input parameters */
	if((hrtc == NULL) || (sDate == NULL))
	{
		return HAL_ERROR;
	}
  
	/* Process Locked */ 
	__HAL_LOCK(hrtc);
  
	hrtc->State = HAL_RTC_STATE_BUSY; 
		/* Check the parameters */		
	assert_param(IS_RTC_YEAR(sDate->Year));
	assert_param(IS_RTC_MONTH(sDate->Month));
	assert_param(IS_RTC_DATE(sDate->Date));
	assert_param(IS_RTC_WEEKDAY(sDate->WeekDay));
    /* Change the current date */
	hrtc->DateToUpdate.Year  = sDate->Year;
	hrtc->DateToUpdate.Month = sDate->Month;
	hrtc->DateToUpdate.Date  = sDate->Date;
	hrtc->DateToUpdate.WeekDay= sDate->WeekDay;
	/* Read the time counter*/
	if (sDate->Year >= 2000)
	{
		years = sDate->Year-2000;
		data_reg |= RTC_DATE_CEN;
	}
	else
		years = sDate->Year-1900;
		
	data_reg |= ((RTC_ByteToBcd2((uint8_t)years))<<RTC_DATE_YEAR_Pos)&RTC_DATE_YEAR;
	data_reg |= (((uint32_t)(RTC_ByteToBcd2(sDate->Month))<<RTC_DATE_MONTH_Pos)&RTC_DATE_MONTH);
	data_reg |= RTC_ByteToBcd2(sDate->Date)&RTC_DATE_DAY;
	/* Set Initialization mode */
	if(RTC_Enter_Init_Mode(hrtc) != HAL_OK)
	{
		/* Set RTC state */
		hrtc->State = HAL_RTC_STATE_ERROR;
		/* Release Lock */
		__HAL_UNLOCK(hrtc);

		return HAL_ERROR;
	}  
	RTC_Disable_Write_Protected(hrtc);
	WRITE_REG(hrtc->Instance->DATE,data_reg);
  
	RTC_Disable_Write_Protected(hrtc);
	SET_BIT(hrtc->Instance->TIME,sDate->WeekDay);
	if(RTC_Exit_Init_Mode(hrtc) != HAL_OK)
	{       
		hrtc->State = HAL_RTC_STATE_ERROR;
		/* Process Unlocked */ 
		__HAL_UNLOCK(hrtc);
      
		return HAL_ERROR;
	}

	hrtc->State = HAL_RTC_STATE_READY ;
	/* Process Unlocked */ 
	__HAL_UNLOCK(hrtc);
  
	return HAL_OK;    
}


/**
  * @brief  Sets RTC Alarm1 time.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTime: Pointer to Time structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_Alarm1_SetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime)
{
	uint32_t time_reg = 0;
	/* Check input parameters */
	if((hrtc == NULL) || (sTime == NULL))
	{
		return HAL_ERROR;
	}
	/* Process Locked */ 
	__HAL_LOCK(hrtc);
		
	hrtc->State = HAL_RTC_STATE_BUSY;
	/* Check the parameters */
	assert_param(IS_RTC_HOUR24(sTime->Hours));
	assert_param(IS_RTC_MINUTES(sTime->Minutes));
	assert_param(IS_RTC_SECONDS(sTime->Seconds));
  
	if(hrtc->Init.HourFormat == RTC_HOURFORMAT_12)
	{
		if(sTime->Hours > 12)
		{
			time_reg = RTC_TIME_H20_PA;
			time_reg |= (RTC_ByteToBcd2(sTime->Hours-12)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
		else
		{
			time_reg |= (RTC_ByteToBcd2(sTime->Hours)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
			
	}
	else
	{
		if(sTime->Hours > 19)
		{
			time_reg = RTC_TIME_H20_PA;
			time_reg |= (RTC_ByteToBcd2(sTime->Hours-20)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
		else
		{
			time_reg |= (RTC_ByteToBcd2(sTime->Hours)<<RTC_TIME_HOUR19_Pos)&RTC_TIME_HOUR19;
		}
		
	}
	time_reg |= (RTC_ByteToBcd2(sTime->Minutes)<<RTC_TIME_MIN_Pos)&RTC_TIME_MIN;
	time_reg |= RTC_ByteToBcd2(sTime->Seconds)&RTC_BCD_TO_BYTE_MASK;
	time_reg |= (hrtc->Instance->ALM1TIME&RTC_TIME_WEEK);
	/* Set Initialization mode */
	if(RTC_Enter_Init_Mode(hrtc) != HAL_OK)
	{
		/* Set RTC state */
		hrtc->State = HAL_RTC_STATE_ERROR;
		/* Release Lock */
		__HAL_UNLOCK(hrtc);

		return HAL_ERROR;
	}  
	
	RTC_Disable_Write_Protected(hrtc);
	WRITE_REG(hrtc->Instance->ALM1TIME,time_reg);
    /* Exit read/writ mode in RTC registers */
	if(RTC_Exit_Init_Mode(hrtc) != HAL_OK)
	{       
		hrtc->State = HAL_RTC_STATE_ERROR;
		/* Process Unlocked */ 
		__HAL_UNLOCK(hrtc);
      
		return HAL_ERROR;
	}
    
	hrtc->State = HAL_RTC_STATE_READY;
  
	__HAL_UNLOCK(hrtc); 
     
	return HAL_OK;
     
}


/**
  * @brief  Sets RTC Alarm1 date.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sDate: Pointer to date structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_Alarm1_SetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate)
{
	uint32_t years = 0U, data_reg = 0;
	/* Check input parameters */
	if((hrtc == NULL) || (sDate == NULL))
	{
		return HAL_ERROR;
	}
	/* Process Locked */ 
	__HAL_LOCK(hrtc);
  
	hrtc->State = HAL_RTC_STATE_BUSY; 
	/* Check the parameters */		
	assert_param(IS_RTC_YEAR(sDate->Year));
	assert_param(IS_RTC_MONTH(sDate->Month));
	assert_param(IS_RTC_DATE(sDate->Date));
	assert_param(IS_RTC_WEEKDAY(sDate->WeekDay));
	/* Read the time counter*/
	if (sDate->Year >= 2000)
	{
		years = sDate->Year-2000;
  	data_reg |= RTC_DATE_CEN;
	}
	else
		years = sDate->Year-1900;
		
	data_reg |= ((RTC_ByteToBcd2((uint8_t)years))<<RTC_DATE_YEAR_Pos)&RTC_DATE_YEAR;
	data_reg |= (((uint32_t)(RTC_ByteToBcd2(sDate->Month))<<RTC_DATE_MONTH_Pos)&RTC_DATE_MONTH);
	data_reg |= RTC_ByteToBcd2(sDate->Date)&RTC_DATE_DAY;
	/* Set Initialization mode */
	if(RTC_Enter_Init_Mode(hrtc) != HAL_OK)
	{
		/* Set RTC state */
		hrtc->State = HAL_RTC_STATE_ERROR;
		/* Release Lock */
		__HAL_UNLOCK(hrtc);
		
		return HAL_ERROR;
	}  
	RTC_Disable_Write_Protected(hrtc);
	WRITE_REG(hrtc->Instance->ALM1DATE,data_reg);
  
	RTC_Disable_Write_Protected(hrtc);
	SET_BIT(hrtc->Instance->ALM1TIME,sDate->WeekDay);
	if(RTC_Exit_Init_Mode(hrtc) != HAL_OK)
	{       
		hrtc->State = HAL_RTC_STATE_ERROR;
    /* Process Unlocked */ 
		__HAL_UNLOCK(hrtc);
		
		return HAL_ERROR;
	}
	hrtc->State = HAL_RTC_STATE_READY ;
	/* Process Unlocked */ 
	__HAL_UNLOCK(hrtc);
  
	return HAL_OK;    
}

/**
  * @brief  Gets RTC Alarm1 time 
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTime: Pointer to Time structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_Alarm1_GetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime)
{
	uint32_t time_reg = 0U;

	/* Check input parameters */
	if((hrtc == NULL) || (sTime == NULL))
	{
		return HAL_ERROR;
	}
	time_reg = hrtc->Instance->TIME; 
	/* Fill the structure fields with the read parameters */
	if((time_reg & RTC_TIME_H20_PA) == RESET)
	{
		if (hrtc->Init.HourFormat == RTC_HOURFORMAT_12)
			sTime->Hours =  RTC_Bcd2ToByte((uint8_t)((time_reg & RTC_TIME_HOUR19_Msk)>>RTC_TIME_HOUR19_Pos));
		else
			sTime->Hours = RTC_Bcd2ToByte((uint8_t)((time_reg & RTC_TIME_HOUR19_Msk)>>RTC_TIME_HOUR19_Pos));
	}
	else
	{
		if (hrtc->Init.HourFormat == RTC_HOURFORMAT_12)
			sTime->Hours = 12 + RTC_Bcd2ToByte((uint8_t)((time_reg & RTC_TIME_HOUR19_Msk)>>RTC_TIME_HOUR19_Pos));
		else
			sTime->Hours = 20+ RTC_Bcd2ToByte((uint8_t)((time_reg & RTC_TIME_HOUR19_Msk)>>RTC_TIME_HOUR19_Pos));
	}
	sTime->Minutes = RTC_Bcd2ToByte((uint8_t)((time_reg & RTC_TIME_MIN)>>RTC_TIME_MIN_Pos));
	sTime->Seconds = RTC_Bcd2ToByte((uint8_t)(time_reg & RTC_BCD_TO_BYTE_MASK));
  
	return HAL_OK;
}

/**
  * @brief  Gets RTC Alarm1 date 
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sDate: Pointer to Date structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_Alarm1_GetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate)
{
	uint32_t date_reg = 0U, time_reg = 0;
	/* Check input parameters */
	if((hrtc == NULL) || (sDate == NULL))
	{
		return HAL_ERROR;
	}
 
	date_reg = hrtc->Instance->ALM1DATE;
	time_reg = hrtc->Instance->ALM1TIME;
  /* Fill the structure fields with the read parameters */
	if ((date_reg & RTC_DATE_CEN) != RESET)
		sDate->Year= 2000 + RTC_Bcd2ToByte((uint8_t)((date_reg & RTC_DATE_YEAR)>>RTC_TIME_HOUR19_Pos));
	else
		sDate->Year= 1900 + RTC_Bcd2ToByte((uint8_t)((date_reg & RTC_DATE_YEAR)>>RTC_TIME_HOUR19_Pos));
	
	sDate->Month= RTC_Bcd2ToByte((uint8_t)((date_reg & RTC_DATE_MONTH)>>RTC_DATE_MONTH_Pos));
	sDate->Date = RTC_Bcd2ToByte((uint8_t)(date_reg & RTC_DATE_DAY));
	sDate->WeekDay = (uint8_t)((time_reg & RTC_TIME_WEEK)>>RTC_TIME_WEEK_Pos);
  
	return HAL_OK;
}
/**
  * @brief  Active or Deactive the specified RTC Alarm interrupt 
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Alarm: Specifies the Alarm.
  *          This parameter can be one of the following values:
  *            @arg RTC_ALARM_1:  Alarm1
  *           @arg RTC_ALARM_2:  Alarm2
  * @param  NewState: the Alarm enable  or disable.
  *          This parameter can be one of the following values:
  *            @arg DISABLE
  *            @arg ENABLE
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_RTC_Alarm_INT_Config(RTC_HandleTypeDef *hrtc, uint32_t Alarm, FunctionalState NewState)
{
	UNUSED(Alarm);

	/* Check the parameters */
	assert_param(IS_RTC_ALARM(Alarm));
  
	RTC_Disable_Write_Protected(hrtc);
	if(Alarm != RTC_ALARM_2)
	{
		if (NewState != DISABLE)
		{
			SET_BIT(hrtc->Instance->CR, RTC_CR_ALM1_INTEN);
		}
		else
		{
			CLEAR_BIT(hrtc->Instance->CR,RTC_CR_ALM1_INTEN);
		}
	}
	else
	{
		if (NewState != DISABLE)
		{
			SET_BIT(hrtc->Instance->CR, RTC_CR_ALM2_INTEN);
		}
		else
		{
			CLEAR_BIT(hrtc->Instance->CR,RTC_CR_ALM2_INTEN);
		}
	}
	return HAL_OK;
}


/**
  * @brief  Active or Deactive the specified RTC Alarm1 
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  NewState: the Alarm enable  or disable.
  *          This parameter can be one of the following values:
  *            @arg DISABLE
  *            @arg ENABLE
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_Alarm1_Config(RTC_HandleTypeDef *hrtc,FunctionalState NewState)
{
  /* Check input parameters */
	if(hrtc == NULL)
	{
		return HAL_ERROR;
	}
   /* Process Locked */ 
	__HAL_LOCK(hrtc);
  
	hrtc->State = HAL_RTC_STATE_BUSY;
	RTC_Disable_Write_Protected(hrtc);
		/* In case of interrupt mode is used, the interrupt source must disabled */ 
	if (NewState != DISABLE)
	{
		SET_BIT(hrtc->Instance->CR, RTC_CR_ALM1EN);
	}
	else
	{
		CLEAR_BIT(hrtc->Instance->CR,RTC_CR_ALM1EN);
	}
  
	hrtc->State = HAL_RTC_STATE_READY; 
	/* Process Unlocked */ 
	__HAL_UNLOCK(hrtc);
  
	return HAL_OK;  
  
}

/**
  * @brief  Set the RTC Alarm1 interrupt source.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  AlarmEn  Alarm1 interrupt source
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_Alarm1_Set_INT_Source(RTC_HandleTypeDef* hrtc, RTC_AlarmEnableTypeDef *AlarmEn)
{
	uint32_t alarmen_reg = 0;
  
	alarmen_reg = (hrtc->Instance->ALM1DATE)&0XFFFFFF;
	alarmen_reg |= (AlarmEn->Year_Enable | AlarmEn->Month_Enable | AlarmEn->Date_Enable	\
									| AlarmEn->WeekDay_Enable | AlarmEn->Hours_Enable | AlarmEn->Minutes_Enable \
									| AlarmEn->Seconds_Enable);
  
	RTC_Disable_Write_Protected(hrtc);
	hrtc->Instance->ALM1DATE = alarmen_reg;
	return HAL_OK;  
}


/**
  * @brief  Active or Deactive the specified RTC Alarm2 
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  NewState: the Alarm2 enable  or disable.
  *          This parameter can be one of the following values:
  *            @arg DISABLE
  *            @arg ENABLE
  * @param  CycleTime: the Alarm2 cycle time set.
  *          This parameter can be a value of @ref HAL_RTCAlarm2TypeDef
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_Alarm2_Config(RTC_HandleTypeDef *hrtc,FunctionalState NewState, HAL_RTCAlarm2TypeDef CycleTime)
{
  /* Check input parameters */
	if(hrtc == NULL)
	{
		return HAL_ERROR;
	}
	UNUSED(CycleTime);
  
	/* Process Locked */ 
	__HAL_LOCK(hrtc);
  
	hrtc->State = HAL_RTC_STATE_BUSY;
	RTC_Disable_Write_Protected(hrtc);
	/* In case of interrupt mode is used, the interrupt source must disabled */ 
	if (NewState != DISABLE)
	{
		WRITE_REG(hrtc->Instance->ALM2PRD, CycleTime);
	}
	else
	{
		WRITE_REG(hrtc->Instance->ALM2PRD, DISABLE);
	}
	hrtc->State = HAL_RTC_STATE_READY; 
	/* Process Unlocked */ 
	__HAL_UNLOCK(hrtc);
  
	return HAL_OK;  
  
}

/**
  * @}
  */

/** @defgroup RTC_Exported_Functions_Group4 Peripheral State functions 
 *  @brief   Peripheral State functions 
 *
@verbatim   
 ===============================================================================
                     ##### Peripheral State functions #####
 ===============================================================================  
    [..]
    This subsection provides functions allowing to
      (+) Get RTC state

@endverbatim
  * @{
  */
/**
  * @brief  Returns the RTC state.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL state
  */
HAL_RTCStateTypeDef HAL_RTC_GetState(RTC_HandleTypeDef* hrtc)
{
	return hrtc->State;
}

/**
  * @}
  */

/** @defgroup RTC_Exported_Functions_Group5 Peripheral Control functions 
 *  @brief   Peripheral Control functions 
 *
@verbatim   
 ===============================================================================
                     ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides functions allowing to
      (+) Wait for RTC Time and Date Synchronization

@endverbatim
  * @{
  */

/**
  * @brief  Enters the RTC Initialization mode.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
static HAL_StatusTypeDef RTC_Enter_Init_Mode(RTC_HandleTypeDef* hrtc)
{
	uint32_t tickstart = 0U;
  
	tickstart = HAL_GetTick();
  
	__HAL_RTC_ENTER_RW(hrtc);
  /* Wait till RTC is in WAITF state and if Time out is reached exit */
	while((__HAL_RTC_GET_WAITF_STATUS(hrtc)) == RESET)
	{
		if((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
		{       
			return HAL_TIMEOUT;
		} 
	}

	return HAL_OK;  
}

/**
  * @brief  Exit the RTC Initialization mode.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
static HAL_StatusTypeDef RTC_Exit_Init_Mode(RTC_HandleTypeDef* hrtc)
{
	uint32_t tickstart = 0U;
  
	tickstart = HAL_GetTick();
	
	__HAL_RTC_EXIT_RW(hrtc);
  /* Wait till RTC is in INIT state and if Time out is reached exit */
	while((__HAL_RTC_GET_WAITF_STATUS(hrtc)) != RESET)
	{
		if((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
		{       
			return HAL_TIMEOUT;
		} 
	}
  
	return HAL_OK;  
}

/**
  * @brief  Converts a 2 digit decimal to BCD format.
  * @param  Value: Byte to be converted
  * @retval Converted byte
  */
static uint8_t RTC_ByteToBcd2(uint8_t Value)
{
  uint32_t bcdhigh = 0U;
  
  while(Value >= 10U)
  {
	  bcdhigh++;
	  Value -= 10U;
  }
  
  return  ((uint8_t)(bcdhigh << 4U) | Value);
}

/**
  * @brief  Converts from 2 digit BCD to Binary.
  * @param  Value: BCD value to be converted
  * @retval Converted word
  */
static uint8_t RTC_Bcd2ToByte(uint8_t Value)
{
	uint32_t tmp = 0U;
	tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10U;
	return (tmp + (Value & (uint8_t)0x0F));
}
/**
  * @brief  Get RSF flag .
  * @param  None
  * @retval FlagStatus 
  */

FlagStatus RTC_Get_RSF_Flag(void)
{
	if (READ_BIT(RTC->ISR,RTC_ISR_RSF) != 0x00)
		return SET;
	else
		return RESET;
}
/**
  * @brief  Clear RSF flag .
  * @param  None
  * @retval None 
  */

void RTC_Clear_RSF_Flag(void)
{
	RTC->WPR = RTC_WRITE_PROTECT_KEY1;
	RTC->WPR = RTC_WRITE_PROTECT_KEY2;
	CLEAR_BIT(RTC->ISR,RTC_ISR_RSF);
}
/**
  * @brief  Get Alarm  flag .
  * @param  Alarm: Specifies the Alarm.
  *          This parameter can be one of the following values:
  *            @arg RTC_ALARM_1:  Alarm1
  *           @arg RTC_ALARM_2:  Alarm2
  * @retval FlagStatus 
  */

FlagStatus HAL_RTC_Alarm_Get_Flag(uint32_t Alarm)
{
	/* Check the parameters */
	assert_param(IS_RTC_ALARM(Alarm));
  
	if(Alarm != RTC_ALARM_2)
	{
		if (READ_BIT(RTC->ISR,RTC_ISR_ALM1_F) != RESET)
			return SET;
		else
			return RESET;
	}
	else
	{
		if (READ_BIT(RTC->ISR,RTC_ISR_ALM2_F) != RESET)
			return SET;
		else
			return RESET;
	}
		
}
/**
  * @brief  Clear Alarm flag .
  * @param  Alarm: Specifies the Alarm.
  *          This parameter can be one of the following values:
  *            @arg RTC_ALARM_1:  Alarm1
  *           @arg RTC_ALARM_2:  Alarm2
  * @retval FlagStatus 
  */

void HAL_RTC_Alarm_Clear_Flag(uint32_t Alarm)
{
	/* Check the parameters */
	assert_param(IS_RTC_ALARM(Alarm));
  
	RTC->WPR = RTC_WRITE_PROTECT_KEY1;
	RTC->WPR = RTC_WRITE_PROTECT_KEY2;
	if(Alarm != RTC_ALARM_2)
		SET_BIT(RTC->INTCLR, RTC_INTCLR_ALM1_CLR);
	else
		SET_BIT(RTC->INTCLR, RTC_INTCLR_ALM2_CLR);
	
}
/**
  * @brief  Deactive the specified 1HZ out
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  NewState: the 1HZ out enable  or disable.
  *          This parameter can be one of the following values:
  *            @arg DISABLE
  *            @arg ENABLE
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_1HZ_Config(RTC_HandleTypeDef *hrtc,FunctionalState NewState)
{
  /* Check input parameters */
	if(hrtc == NULL)
	{
		return HAL_ERROR;
	}
   /* Process Locked */ 
	__HAL_LOCK(hrtc);
  
    hrtc->State = HAL_RTC_STATE_BUSY;
  
	RTC_Disable_Write_Protected(hrtc);
  /* In case of interrupt mode is used, the interrupt source must disabled */ 
	if (NewState != DISABLE)
	{
		SET_BIT(hrtc->Instance->CR, RTC_CR_RTC1HZOE);
	}
	else
	{
		CLEAR_BIT(hrtc->Instance->CR,RTC_CR_RTC1HZOE);
	}
	hrtc->State = HAL_RTC_STATE_READY; 
  /* Process Unlocked */ 
	__HAL_UNLOCK(hrtc);
  
	return HAL_OK;  
  
}
/**
  * @brief  Disable Write Protected
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */

static void RTC_Disable_Write_Protected(RTC_HandleTypeDef *hrtc)
{
	hrtc->Instance->WPR = RTC_WRITE_PROTECT_KEY1;
    hrtc->Instance->WPR = RTC_WRITE_PROTECT_KEY2;
}
/**
  * @}
  */
/**
  * @}
  */

#endif /* HAL_RTC_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

