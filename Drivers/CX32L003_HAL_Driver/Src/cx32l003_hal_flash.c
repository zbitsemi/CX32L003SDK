/**
  ******************************************************************************
  * @file    cx32l003_hal_flash.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   FLASH HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the internal FLASH memory:
  *           + Program operations functions
  *           + Memory Control functions 
  *           + Peripheral State functions
  *         
  @verbatim
  ==============================================================================
                        ##### FLASH peripheral features #####
  ==============================================================================
  [..] The Flash memory interface manages CPU AHB accesses to the Flash memory. 
			 It implements the erase and program Flash memory operations and the read 
			 and write protection mechanisms.

  [..] The FLASH main features are:
      (+) Flash memory read operations
      (+) Flash memory program/erase operations
      (+) Read / write protections


                     ##### How to use this driver #####
  ==============================================================================
  [..]                             
      This driver provides functions and macros to configure and program the FLASH 
      memory of all CX32L003 devices.
    
      (#) FLASH Memory I/O Programming functions: this group includes all needed
          functions to erase and program the main memory:
        (++) Lock and Unlock the FLASH interface
        (++) Erase function: Erase page, erase all pages
        (++) Program functions: half word, word and doubleword
				
      (#) Interrupts and flags management functions : this group 
          includes all needed functions to:
        (++) Handle FLASH interrupts
        (++) Get error flag status

  [..] In addition to these function, this driver includes a set of macros allowing
       to handle the following operations:
      (+) Enable/Disable the FLASH interrupts
      (+) Monitor the FLASH flags status
          
  @endverbatim
  ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/** @defgroup FLASH FLASH
  * @brief FLASH HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */
#define FLASH_OP_READ								(0x00000000)
#define FLASH_OP_PROGRAM						(FLASH_CR_OP_0)
#define FLASH_OP_SECTORERASE				(FLASH_CR_OP_1)
#define FLASH_OP_CHIPERASE					(FLASH_CR_OP_0 | FLASH_CR_OP_1)
	
#define DUMMY_ADDERSS								(0x00002000)
#define DUMMY_DATA									(0x5555AAAA)
	
	
/**
  * @}
  */

/* Private macro ---------------------------- ---------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
  * @{
  */
 
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup FLASH_Private_Variables FLASH Private Variables
  * @{
  */
/* Variables used for Erase pages under interruption*/
FLASH_ProcessTypeDef pFlash;
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */
/* Reserved for future start */
#ifdef PROGRAMADV
static  void FLASH_Program_HalfWord(uint32_t Address, uint16_t Data);
static void FLASH_Program_Word(uint32_t Address, uint32_t Data);
#endif
/* Reserved for future end */

static	void 	FLASH_Program_Byte(uint32_t Address, uint8_t Data);	
static 	void 	FLASH_PageErase(uint32_t PageAddress);
static 	void 	FLASH_MassErase(void);
static 	void 	FLASH_SetErrorCode(void);
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup FLASH_Exported_Functions FLASH Exported Functions
  * @{
  */
  
/** @defgroup FLASH_Exported_Functions_Group1 Programming operation functions 
  *  @brief   Programming operation functions 
  *
@verbatim   
@endverbatim
  * @{
  */

uint8_t FLASH_Byte_Read(uint32_t Address)
{
  return (*((uint8_t *)Address));
}

uint16_t FLASH_HalfWord_Read(uint32_t Address)
{
  return (*((uint16_t *)Address));
}

uint32_t FLASH_Word_Read(uint32_t Address)
{
  return (uint32_t)(READ_REG(*((uint32_t *)Address)));
}


/**
  * @brief  Program halfword, word or double word at a specified address
  * @note   FLASH should be previously erased before new programmation (only exception to this 
  *         is when 0x0000 is programmed)
  *
  * @param  TypeProgram:  Indicate the way to program at a specified address.
  *                       This parameter can be a value of @ref FLASH_Type_Program
  * @param  Address:      Specifies the address to be programmed.
  * @param  Data:         Specifies the data to be programmed
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint8_t index = 0;
  uint8_t nbiterations = 0;
  
  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));

	/* Wait for last operation to be completed */
	status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {
    if(TypeProgram == FLASH_TYPEPROGRAM_BYTE)
    {
      /* Program byte (8-bit) at a specified address. */
      nbiterations = 1U;
    }		
    else if(TypeProgram == FLASH_TYPEPROGRAM_HALFWORD)
    {
      /* Program halfword (16-bit) at a specified address. */
      nbiterations = 2U;
    }
    else if(TypeProgram == FLASH_TYPEPROGRAM_WORD)
    {
      /* Program word (32-bit = 2*16-bit) at a specified address. */
      nbiterations = 4U;
    }
    else
    {
      /* Program double word (64-bit = 4*16-bit) at a specified address. */
      nbiterations = 8U;
    }
		
		HAL_FLASH_OPERATION_Unlock(Address);	
    for (index = 0U; index < nbiterations; index++)
    {
	
      FLASH_Program_Byte((Address + (1U*index)), (uint8_t)(Data >> (8U*index)));

			/* Wait for last operation to be completed */
			status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
	
			/* If the program operation is completed, change operation to Read */
			__disable_irq();	
			__HAL_FLASH_REGISTER_UNLOCK;
			CLEAR_BIT(FLASH->CR, FLASH_CR_OP);
			__HAL_FLASH_REGISTER_LOCK;
			__enable_irq();			
			
      /* In case of error, stop programation procedure */
      if (status != HAL_OK)
      {
        break;
      }
    }
		HAL_FLASH_OPERATION_Lock(Address);			
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Perform a mass erase or erase the specified FLASH memory pages
  * @note   Default the FLASH memory is written protected against possible unwanted operation.
  * @param[in]  pEraseInit pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  *
  * @param[out]  PageError pointer to variable  that
  *         contains the configuration information on faulty page in case of error
  *         (0xFFFFFFFF means that all the pages have been correctly erased)
  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint32_t address = 0U;

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASS)
  {
    {
      /* Mass Erase requested for Bank1 */
      /* Wait for last operation to be completed */
      if (FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE) == HAL_OK)
      {				
				HAL_FLASH_OPERATION_Unlock(FLASH_ALLPAGE_SELECTED);
				
        /*Mass erase to be done*/
        FLASH_MassErase();
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
				HAL_FLASH_OPERATION_Lock(FLASH_ALLPAGE_SELECTED);
				
				/* If the mass erase operation is completed, change operation to Read */
				__disable_irq();				
				__HAL_FLASH_REGISTER_UNLOCK;;
				CLEAR_BIT(FLASH->CR, FLASH_CR_OP);
				__HAL_FLASH_REGISTER_LOCK;
				__enable_irq();					
      }
    }
  }
  else
  {
    /* Page Erase is requested */    
		/* Wait for last operation to be completed */
		if (FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE) == HAL_OK)
		{
			/*Initialization of PageError variable*/
			*PageError = 0xFFFFFFFFU;
			
			/* Erase page by page to be done*/
			for(address = pEraseInit->PageAddress;
					address < ((pEraseInit->NbPages * FLASH_PAGE_SIZE) + pEraseInit->PageAddress);
					address += FLASH_PAGE_SIZE)
			{
				HAL_FLASH_OPERATION_Unlock(address);				
				FLASH_PageErase(address);
				
				/* Wait for last operation to be completed */
				status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
				
				HAL_FLASH_OPERATION_Lock(address);		
				
				/* If the page erase operation is completed, change operation to Read */
				__disable_irq();	
				__HAL_FLASH_REGISTER_UNLOCK;
				CLEAR_BIT(FLASH->CR, FLASH_CR_OP);
				__HAL_FLASH_REGISTER_LOCK;
				__enable_irq();	
				
				if (status != HAL_OK)
				{
					/* In case of error, stop erase procedure and return the faulty address */
					*PageError = address;
					break;
				}
			}
		}
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}



/**
  * @brief This function handles FLASH interrupt request.
  * @retval None
  */
void HAL_FLASH_IRQHandler(void)
{
  uint32_t addresstmp = 0U;

  /* Check FLASH operation alarm(error) flags */
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_ALARM_ERASE_PROTADDR) ||__HAL_FLASH_GET_FLAG(FLASH_FLAG_ALARM_ERASE_PCADDR))
  {
    /* Return the faulty address */
    addresstmp = pFlash.Address;
		
    /* Save the Error code */
    FLASH_SetErrorCode();
    
    /* FLASH alarm(error) interrupt user callback */
    HAL_FLASH_OperationErrorCallback(addresstmp);

    /* Stop the procedure ongoing */
    pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
  }
}


/**
  * @brief  FLASH operation error interrupt callback
  * @param  ReturnValue: The value saved in this parameter depends on the ongoing procedure
  *                 - Mass Erase: No return value expected
  *                 - Pages Erase: Address of the page which returned an error
  * @retval none
  */
__weak void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(ReturnValue);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FLASH_OperationErrorCallback could be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions_Group2 Peripheral Control functions 
 *  @brief   management functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the FLASH 
    memory operations.

@endverbatim
  * @{
  */

/**
  * @brief  Unlock the FLASH Page Erase/write access.
  * @param  PageAddress:  Set the page address to lock erase/write protect. 
  *                       This parameter can be set 0xFFFFFFFF which means lock all pages.	
  * @retval HAL Status 
  */
HAL_StatusTypeDef HAL_FLASH_OPERATION_Unlock(uint32_t PageAddress)
{
		__disable_irq();
  /* One bit of SLOCKx controls 2 pages, page size is 1K bytes */
	if(PageAddress < FLASH_SIZE_32K)
	{
		__HAL_FLASH_REGISTER_UNLOCK;  
		SET_BIT(FLASH->SLOCK0, 1 << (PageAddress>>10));
		__HAL_FLASH_REGISTER_LOCK;	
	}
	else if(PageAddress < FLASH_SIZE_64K)
	{
		__HAL_FLASH_REGISTER_UNLOCK;  
		SET_BIT(FLASH->SLOCK1, 1 << ((PageAddress-32*1024)>>10));
		__HAL_FLASH_REGISTER_LOCK;			
	}
	else if(PageAddress == FLASH_ALLPAGE_SELECTED)
	{
		__HAL_FLASH_REGISTER_UNLOCK;  
		SET_BIT(FLASH->SLOCK0, 0xFFFFFFFF);
		__HAL_FLASH_REGISTER_LOCK;
		
		__HAL_FLASH_REGISTER_UNLOCK;  
		SET_BIT(FLASH->SLOCK1, 0xFFFFFFFF);
		__HAL_FLASH_REGISTER_LOCK;			
	}
	else
		return HAL_ERROR;
	
	__enable_irq();	
  return HAL_OK;  
}


/**
  * @brief  Lock the FLASH Page Erase/Write access.
  * @param  PageAddress:  Set the page address to lock erase/write protect. 
  *                       This parameter can be set 0xFFFFFFFF which means lock all pages.
  * @retval HAL Status 
  */
HAL_StatusTypeDef HAL_FLASH_OPERATION_Lock(uint32_t PageAddress)
{
		__disable_irq();	
  /* One bit of SLOCKx controls 2 pages, page size is 1K bytes */
	if(PageAddress < FLASH_SIZE_32K)
	{
		__HAL_FLASH_REGISTER_UNLOCK;  
		CLEAR_BIT(FLASH->SLOCK0, 1 << (PageAddress>>10));
		__HAL_FLASH_REGISTER_LOCK;	
	}
	else if(PageAddress < FLASH_SIZE_64K)
	{
		__HAL_FLASH_REGISTER_UNLOCK;  
		CLEAR_BIT(FLASH->SLOCK1, 1 << ((PageAddress-32*1024)>>10));
		__HAL_FLASH_REGISTER_LOCK;			
	}
	else if(PageAddress == FLASH_ALLPAGE_SELECTED)
	{
		__HAL_FLASH_REGISTER_UNLOCK;  
		CLEAR_BIT(FLASH->SLOCK0, 0xFFFFFFFF);
		__HAL_FLASH_REGISTER_LOCK;
		
		__HAL_FLASH_REGISTER_UNLOCK;  
		CLEAR_BIT(FLASH->SLOCK1, 0xFFFFFFFF);
		__HAL_FLASH_REGISTER_LOCK;			
	}
	else
		return HAL_ERROR;
	
	__enable_irq();	
  return HAL_OK;   
}



/**
  * @}
  */  

/** @defgroup FLASH_Exported_Functions_Group3 Peripheral errors functions 
 *  @brief    Peripheral errors functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral Errors functions #####
 ===============================================================================  
    [..]
    This subsection permit to get in run-time errors of  the FLASH peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Get the specific FLASH error flag.
  * @retval FLASH_ErrorCode The returned value can be:
  *            @ref FLASH_Error_Codes
  */
uint32_t HAL_FLASH_GetError(void)
{
   return pFlash.ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup FLASH_Private_Functions
 * @{
 */


/**
  * @brief  Program a byte (8-bit) at a specified address.
  * @param  Address specify the address to be programmed.
  * @param  Data    specify the data to be programmed.
  * @retval None
  */
static void FLASH_Program_Byte(uint32_t Address, uint8_t Data)
{
  /* Clean the error context */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
	
	__disable_irq();
	/* Proceed to program the new data */
	__HAL_FLASH_REGISTER_UNLOCK;
	MODIFY_REG(FLASH->CR, FLASH_CR_OP, FLASH_OP_PROGRAM);

  /* Write data in the address */
  *(__IO uint8_t*)Address = Data;
	
	__HAL_FLASH_REGISTER_LOCK;
	
	__enable_irq();	
}

#ifdef PROGRAMADV
/**
  * @brief  Program a half-word (16-bit) at a specified address.
  * @param  Address specify the address to be programmed.
  * @param  Data    specify the data to be programmed.
  * @retval None
  */
static void FLASH_Program_HalfWord(uint32_t Address, uint16_t Data)
{
  /* Clean the error context */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
	__disable_irq();
	
/* Proceed to program the new data */
	__HAL_FLASH_REGISTER_UNLOCK;
	MODIFY_REG(FLASH->CR, FLASH_CR_OP, FLASH_OP_PROGRAM);

  /* Write data in the address */
  *(__IO uint16_t*)Address = Data;
	
	__HAL_FLASH_REGISTER_LOCK;	
	__enable_irq();		
}


/**
  * @brief  Program a word (32-bit) at a specified address.
  * @param  Address specify the address to be programmed.
  * @param  Data    specify the data to be programmed.
  * @retval None
  */
static void FLASH_Program_Word(uint32_t Address, uint32_t Data)
{
  /* Clean the error context */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
	__disable_irq();	
	/* Proceed to program the new data */
	__HAL_FLASH_REGISTER_UNLOCK;
	MODIFY_REG(FLASH->CR, FLASH_CR_OP, FLASH_OP_PROGRAM);
	
  /* Write data in the address */
  *(__IO uint32_t*)Address = Data;
	
	__HAL_FLASH_REGISTER_LOCK;	
	__enable_irq();		
}
#endif


/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  Timeout  maximum flash operation timeout
  * @retval HAL Status
  */
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout)
{
  /* Wait for the FLASH operation to complete by polling on BUSY flag to be reset. */
     
  uint32_t tickstart = HAL_GetTick();
  
  while(__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) == FLASH_FLAG_BSY) 
  { 
    if (Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0U) || ((HAL_GetTick()-tickstart) > Timeout))
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* There is no error flag set */
  return HAL_OK;
}



/**
  * @brief  Full erase of FLASH memory Bank 
  * @param  None
  * @retval None
  */
static void FLASH_MassErase(void)
{
  /* Clean the error context */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
	
	__disable_irq();
  /* Whole chip will be erased*/
	__HAL_FLASH_REGISTER_UNLOCK;
	MODIFY_REG(FLASH->CR, FLASH_CR_OP, FLASH_OP_CHIPERASE);
  /* Write data in the address */
  *(__IO uint32_t*)DUMMY_ADDERSS = DUMMY_DATA;
	__HAL_FLASH_REGISTER_LOCK;
	
	__enable_irq();	
}


/**
  * @brief  Erase the specified FLASH memory page
  * @param  PageAddress FLASH page to erase
  *         The value of this parameter depend on device used within the same series      
  * 
  * @retval None
  */
static void FLASH_PageErase(uint32_t PageAddress)
{
  /* Clean the error context */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
	
	__disable_irq();	
  /* one page will be erased*/
	__HAL_FLASH_REGISTER_UNLOCK;
	MODIFY_REG(FLASH->CR, FLASH_CR_OP, FLASH_OP_SECTORERASE);
	/* Proceed to erase the page */
  *(__IO uint32_t*)PageAddress = DUMMY_DATA;	
	
	__HAL_FLASH_REGISTER_LOCK;
	__enable_irq();	
}


/**
  * @brief  Set the specific FLASH error flag.
  * @retval None
  */
static void FLASH_SetErrorCode(void)
{
  uint32_t flags = 0U;
  
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_ALARM_ERASE_PROTADDR))
  {
    pFlash.ErrorCode |= HAL_FLASH_ERROR_ERASEWP;
    flags |= FLASH_FLAG_ALARM_ERASE_PROTADDR;
  }
	
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_ALARM_ERASE_PCADDR))
  {
    pFlash.ErrorCode |= HAL_FLASH_ERROR_ERASEPC;
    flags |= FLASH_FLAG_ALARM_ERASE_PCADDR;
  }

  /* Clear FLASH error pending bits */
  __HAL_FLASH_CLEAR_FLAG(flags);
}  



/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_FLASH_MODULE_ENABLED */

/**
  * @}
  */ /* group CX32L003_HAL_Driver */


