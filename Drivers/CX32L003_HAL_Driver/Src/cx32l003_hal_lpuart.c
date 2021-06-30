/**
  ******************************************************************************
  * @file    cx32l003_hal_lpuart.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   LPUART HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Low Power Universal Asynchronous Receiver Transmitter (LPUART) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
    The LPUART HAL driver can be used as follows:

    (#) Declare a LPUART_HandleTypeDef handle structure.
    (#) Initialize the LPUART low level resources by implementing the HAL_LPUART_MspInit() API:
        (##) Enable the LPUART interface clock.
        (##) LPUART pins configuration:
            (+++) Enable the clock for the LPUART GPIOs.
            (+++) Configure the LPUART pins.
        (##) NVIC configuration if you need to use interrupt process (HAL_LPUART_Transmit_IT()
             and HAL_LPUART_Receive_IT() APIs):
            (+++) Configure the LPUART interrupt priority.
            (+++) Enable the NVIC LPUART IRQ handle.

    (#) Program the Baud Rate, Word Length, Stop Bit, Parity and Mode(Receiver/Transmitter) 
				in the huart Init structure.

    (#) For the LPUART asynchronous mode, initialize the LPUART registers by calling
        the HAL_LPUART_Init() API.

     [..] 
       (@) The specific LPUART interrupts (Transmission complete interrupt, 
           RXNE interrupt and Error Interrupts) will be managed using the macros
           __HAL_LPUART_ENABLE_IT() and __HAL_LPUART_DISABLE_IT() inside the transmit 
           and receive process.

     [..] 
       (@) This API HAL_LPUART_Init() configure also the low level Hardware GPIO, CLOCK, CORTEX...etc 
					 by calling the customized HAL_LPUART_MspInit() API.

     [..]
        Three operation modes are available within this driver:

     *** Polling mode IO operation ***
     =================================
     [..]
       (+) Send an amount of data in blocking mode using HAL_LPUART_Transmit()
       (+) Receive an amount of data in blocking mode using HAL_LPUART_Receive()

     *** Interrupt mode IO operation ***
     ===================================
     [..]
       (+) Send an amount of data in non blocking mode using HAL_LPUART_Transmit_IT() 
       (+) At transmission end of transfer HAL_LPUART_TxCpltCallback is executed and user can 
            add his own code by customization of function pointer HAL_LPUART_TxCpltCallback
       (+) Receive an amount of data in non blocking mode using HAL_LPUART_Receive_IT() 
       (+) At reception end of transfer HAL_LPUART_RxCpltCallback is executed and user can 
            add his own code by customization of function pointer HAL_LPUART_RxCpltCallback
       (+) In case of transfer Error, HAL_LPUART_ErrorCallback() function is executed and user can 
            add his own code by customization of function pointer HAL_LPUART_ErrorCallback

     *** LPUART HAL driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in LPUART HAL driver.
      (+) __HAL_LPUART_GET_FLAG : Check whether the specified LPUART flag is set or not
      (+) __HAL_LPUART_CLEAR_FLAG : Clear the specified LPUART pending flag
      (+) __HAL_LPUART_ENABLE_IT: Enable the specified LPUART interrupt
      (+) __HAL_LPUART_DISABLE_IT: Disable the specified LPUART interrupt
      (+) __HAL_LPUART_GET_IT_SOURCE: Check whether the specified LPUART interrupt has occurred or not

     [..]
       (@) You can refer to the LPUART HAL driver header file for more useful macros 
  @endverbatim
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"


/** @addtogroup CX32L003_HAL_Driver
  * @{
  */


#ifdef HAL_LPUART_MODULE_ENABLED

/** @defgroup LPUART LPUART
  * @brief HAL LPUART module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup LPUART_Private_Constants
  * @{
  */
	
/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
#define LPUART_PARITYBIT_Pos			0x9U
#define LPUART_BIT0_Msk						0x1U

/* Private constants ---------------------------------------------------------*/
static const uint8_t ParityTable256[256] = 
{
0, 1,	1, 0,	1, 0,	0, 1,	1, 0,	0, 1,	0, 1,	1, 0, 
1, 0,	0, 1,	0, 1,	1, 0,	0, 1,	1, 0,	1, 0,	0, 1, 	
1, 0,	0, 1,	0, 1,	1, 0,	0, 1,	1, 0,	1, 0,	0, 1,	
0, 1,	1, 0,	1, 0,	0, 1,	1, 0,	0, 1,	0, 1,	1, 0, 	
1, 0,	0, 1,	0, 1,	1, 0,	0, 1,	1, 0,	1, 0,	0, 1,		
0, 1,	1, 0,	1, 0,	0, 1,	1, 0,	0, 1,	0, 1,	1, 0, 	
0, 1,	1, 0,	1, 0,	0, 1,	1, 0,	0, 1,	0, 1,	1, 0, 
1, 0,	0, 1,	0, 1,	1, 0,	0, 1,	1, 0,	1, 0,	0, 1,	
1, 0,	0, 1,	0, 1,	1, 0,	0, 1,	1, 0,	1, 0,	0, 1,	
0, 1,	1, 0,	1, 0,	0, 1,	1, 0,	0, 1,	0, 1,	1, 0, 
0, 1,	1, 0,	1, 0,	0, 1,	1, 0,	0, 1,	0, 1,	1, 0, 
1, 0,	0, 1,	0, 1,	1, 0,	0, 1,	1, 0,	1, 0,	0, 1,
0, 1,	1, 0,	1, 0,	0, 1,	1, 0,	0, 1,	0, 1,	1, 0, 
1, 0,	0, 1,	0, 1,	1, 0,	0, 1,	1, 0,	1, 0,	0, 1,
1, 0,	0, 1,	0, 1,	1, 0,	0, 1,	1, 0,	1, 0,	0, 1,
0, 1,	1, 0,	1, 0,	0, 1,	1, 0,	0, 1,	0, 1,	1, 0	
};



/* Private function prototypes -----------------------------------------------*/
/** @addtogroup LPUART_Private_Functions
  * @{
  */
static HAL_StatusTypeDef LPUART_Transmit_IT(LPUART_HandleTypeDef *hlpuart);
static HAL_StatusTypeDef LPUART_Receive_IT(LPUART_HandleTypeDef *hlpuart);
static HAL_StatusTypeDef LPUART_WaitOnFlagUntilTimeout(LPUART_HandleTypeDef *hlpuart, uint32_t Flag, FlagStatus Status, uint32_t Tickstart, uint32_t Timeout);
static void LPUART_SetConfig (LPUART_HandleTypeDef *hlpuart);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup LPUART_Exported_Functions LPUART Exported Functions
  * @{
  */

/** @defgroup LPUART_Exported_Functions_Group1 Initialization and de-initialization functions 
  *  @brief    Initialization and Configuration functions 
  *
@verbatim
  ==============================================================================
            ##### Initialization and Configuration functions #####
  ==============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the LPUART 
    in asynchronous mode.
      (+) For the asynchronous mode only these parameters can be configured: 
        (++) Baud Rate
        (++) Word Length				
        (++) Receiver/transmitter modes
    [..]
    The HAL_LPUART_Init() API follow respectively the LPUART asynchronous, configuration 
		procedures (details for the procedures are available in reference manuals)

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the LPUART mode according to the specified parameters in
  *         the LPUART_InitTypeDef and create the associated handle.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPUART_Init(LPUART_HandleTypeDef *hlpuart)
{
  /* Check the LPUART handle allocation */
  if(hlpuart == NULL)
  {
    return HAL_ERROR;
  }
  
  if(hlpuart->gState == HAL_LPUART_STATE_RESET)
  {  
    /* Allocate lock resource and initialize it */
    hlpuart->Lock = HAL_UNLOCKED;

    /* Init the low level hardware */
    HAL_LPUART_MspInit(hlpuart);
  }

  hlpuart->gState = HAL_LPUART_STATE_BUSY;
  
  /* Set the LPUART Communication parameters */
  LPUART_SetConfig(hlpuart);

  /* Enable the Peripheral */	
	__HAL_LPUART_ENABLE(hlpuart);
	
  /* Initialize the LPUART state */
  hlpuart->ErrorCode = HAL_LPUART_ERROR_NONE;
  hlpuart->gState= HAL_LPUART_STATE_READY;
  hlpuart->RxState= HAL_LPUART_STATE_READY;
  
  return HAL_OK;
}


/**
  * @brief  DeInitializes the LPUART peripheral. 
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPUART_DeInit(LPUART_HandleTypeDef *hlpuart)
{
  /* Check the LPUART handle allocation */
  if(hlpuart == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));

  hlpuart->gState = HAL_LPUART_STATE_BUSY;

  /* Disable the Peripheral */	
	__HAL_LPUART_DISABLE(hlpuart);
	
  /* DeInit the low level hardware */
  HAL_LPUART_MspDeInit(hlpuart);

  hlpuart->ErrorCode = HAL_LPUART_ERROR_NONE;
  hlpuart->gState = HAL_LPUART_STATE_RESET;
  hlpuart->RxState = HAL_LPUART_STATE_RESET;

  /* Process Unlock */
  __HAL_UNLOCK(hlpuart);

  return HAL_OK;
}

/**
  * @brief  LPUART MSP Init.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval None
  */
__weak void HAL_LPUART_MspInit(LPUART_HandleTypeDef *hlpuart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlpuart);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_LPUART_MspInit could be implemented in the user file
   */
}

/**
  * @brief  LPUART MSP DeInit.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval None
  */
__weak void HAL_LPUART_MspDeInit(LPUART_HandleTypeDef *hlpuart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlpuart);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_LPUART_MspDeInit could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup LPUART_Exported_Functions_Group2 IO operation functions 
  *  @brief LPUART Transmit and Receive functions 
  *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the LPUART asynchronous
    and Half duplex data transfers.

    (#) There are two modes of transfer:
       (++) Blocking mode: The communication is performed in polling mode. 
            The HAL status of all data processing is returned by the same function 
            after finishing transfer.  
       (++) Non blocking mode: The communication is performed using Interrupts, these 
						APIs return the HAL status.
            The end of the data processing will be indicated through the 
            dedicated LPUART IRQ when using Interrupt mode.
            The HAL_LPUART_TxCpltCallback(), HAL_LPUART_RxCpltCallback() user callbacks 
            will be executed respectively at the end of the transmit or receive process.
            The HAL_LPUART_ErrorCallback() user callback will be executed when 
            a communication error is detected.

    (#) Blocking mode APIs are:
        (++) HAL_LPUART_Transmit()
        (++) HAL_LPUART_Receive()

    (#) Non Blocking mode APIs with Interrupt are:
        (++) HAL_LPUART_Transmit_IT()
        (++) HAL_LPUART_Receive_IT()
        (++) HAL_LPUART_IRQHandler()

    (#) A set of Transfer Complete Callbacks are provided in non blocking mode:
        (++) HAL_LPUART_TxCpltCallback()
        (++) HAL_LPUART_RxCpltCallback()
        (++) HAL_LPUART_ErrorCallback()

@endverbatim
  * @{
  */


/**
  * @brief  Sends an amount of data in blocking mode.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be sent
  * @param  Timeout: Timeout duration  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPUART_Transmit(LPUART_HandleTypeDef *hlpuart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  
  /* Check that a Tx process is not already ongoing */
  if(hlpuart->gState == HAL_LPUART_STATE_READY)
  {
    if((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(hlpuart);

    hlpuart->ErrorCode = HAL_LPUART_ERROR_NONE;
    hlpuart->gState = HAL_LPUART_STATE_BUSY_TX;

    /* Init tickstart for timeout management */
    tickstart = HAL_GetTick();

		/* TC interrupt must be enabled to unmask TC flag for polling */
		__HAL_UART_ENABLE_IT(hlpuart, LPUART_IT_TC);
		
    hlpuart->TxXferSize = Size;
    hlpuart->TxXferCount = Size;
    while(hlpuart->TxXferCount > 0U)
    {
      hlpuart->TxXferCount--;
      if(hlpuart->Init.WordLength == LPUART_WORDLENGTH_9B)
      {
        if(hlpuart->Init.Parity == LPUART_PARITY_EVEN)
        {
          MODIFY_REG(hlpuart->Instance->SCON, LPUART_SCON_TB8, ((ParityTable256[*pData] & LPUART_BIT0_Msk) << LPUART_SCON_TB8_Pos));
        }
        else if(hlpuart->Init.Parity == LPUART_PARITY_ODD)
        {
          MODIFY_REG(hlpuart->Instance->SCON, LPUART_SCON_TB8, (((~ParityTable256[*pData]) & LPUART_BIT0_Msk) << LPUART_SCON_TB8_Pos));
        }				
				
        hlpuart->Instance->SBUF = (*pData++ & (uint8_t)0xFF);	
				
        if(LPUART_WaitOnFlagUntilTimeout(hlpuart, LPUART_FLAG_TC, RESET, tickstart, Timeout) != HAL_OK) 
        {
          return HAL_TIMEOUT;
        }		
				__HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_TC);		
      }
      else
      {
				/* uart 8bit communication doesn't support parity transmit */
        hlpuart->Instance->SBUF = (*pData++ & (uint8_t)0xFF);
				
        if(LPUART_WaitOnFlagUntilTimeout(hlpuart, LPUART_FLAG_TC, RESET, tickstart, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }				
				__HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_TC);				
      }
    }
		
    /* At end of Tx process, restore hlpuart->gState to Ready */
    hlpuart->gState = HAL_LPUART_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hlpuart);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}


/**
  * @brief  Receive an amount of data in blocking mode. 
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be received
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPUART_Receive(LPUART_HandleTypeDef *hlpuart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint8_t tmp;
  uint32_t tickstart = 0U;
  
  /* Check that a Rx process is not already ongoing */
  if(hlpuart->RxState == HAL_LPUART_STATE_READY)
  {
    if((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(hlpuart);
    
    hlpuart->ErrorCode = HAL_LPUART_ERROR_NONE;
    hlpuart->RxState = HAL_LPUART_STATE_BUSY_RX;

    /* Init tickstart for timeout managment */
    tickstart = HAL_GetTick();

		/* RXNE interrupt must be enabled to unmask RXNE flag for polling */
		__HAL_LPUART_ENABLE_IT(hlpuart, LPUART_IT_RXNE);
		
    hlpuart->RxXferSize = Size;
    hlpuart->RxXferCount = Size;

    /* Check the remain data to be received */
    while(hlpuart->RxXferCount > 0U)
    {
      hlpuart->RxXferCount--;
      if(hlpuart->Init.WordLength == LPUART_WORDLENGTH_9B)
      {
        if(LPUART_WaitOnFlagUntilTimeout(hlpuart, LPUART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK) 
        {
          return HAL_TIMEOUT;
        }
				__HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_RXNE); 

				tmp = (uint8_t)(hlpuart->Instance->SBUF & (uint8_t)0xFF); 
				if(hlpuart->Init.Parity == LPUART_PARITY_NONE)
				{
						*pData++ = tmp&((uint8_t)0xFF);	
				}
				else if(hlpuart->Init.Parity == LPUART_PARITY_EVEN)
				{
					if((ParityTable256[tmp&((uint8_t)0xFF)]) == (((hlpuart->Instance->SCON & LPUART_SCON_RB8) >> LPUART_SCON_RB8_Pos) & LPUART_BIT0_Msk))	
					{
						*pData++ = tmp&((uint8_t)0xFF);
					}
					else
					{
						/* Rx error process, set hlpuart->RxState to Error */
						hlpuart->RxState = HAL_LPUART_STATE_ERROR;
						__HAL_UNLOCK(hlpuart);
						return HAL_ERROR;						
					}				
				}
				else if(hlpuart->Init.Parity == LPUART_PARITY_ODD)
				{
					if((ParityTable256[tmp&((uint8_t)0xFF)]) == ((~((hlpuart->Instance->SCON & LPUART_SCON_RB8) >> LPUART_SCON_RB8_Pos)) & LPUART_BIT0_Msk))	
					{
						*pData++ = tmp&((uint8_t)0xFF);
					}	
					else
					{
						/* Rx error process, set hlpuart->RxState to Error */
						hlpuart->RxState = HAL_LPUART_STATE_ERROR;
						__HAL_UNLOCK(hlpuart);
						return HAL_ERROR;						
					}							
				}
				else
				{
					/* Rx error process, set hlpuart->RxState to Error */
					hlpuart->RxState = HAL_LPUART_STATE_ERROR;
					__HAL_UNLOCK(hlpuart);
					return HAL_ERROR;						
				}
      } 
      else
      {
        if(LPUART_WaitOnFlagUntilTimeout(hlpuart, LPUART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
				__HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_RXNE);
				
				/* uart 8bit communication doesn't support parity check */
        if(hlpuart->Init.Parity != LPUART_PARITY_NONE)
        {
					/* Rx error process, set hlpuart->RxState to Error */
					hlpuart->RxState = HAL_LPUART_STATE_ERROR;
					__HAL_UNLOCK(hlpuart);
					return HAL_ERROR;		
        }
        else
        {
          *pData++ = (uint8_t)(hlpuart->Instance->SBUF & (uint8_t)0xFF);
        }

      }
    }

    /* At end of Rx process, restore hlpuart->RxState to Ready */
    hlpuart->RxState = HAL_LPUART_STATE_READY;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hlpuart);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPUART_Transmit_IT(LPUART_HandleTypeDef *hlpuart, uint8_t *pData, uint16_t Size)
{
  /* Check that a Tx process is not already ongoing */
  if(hlpuart->gState == HAL_LPUART_STATE_READY)
  {
    if((pData == NULL) || (Size == 0U)) 
    {
      return HAL_ERROR;
    }
    /* Process Locked */
    __HAL_LOCK(hlpuart);

    hlpuart->pTxBuffPtr = pData;
    hlpuart->TxXferSize = Size;
    hlpuart->TxXferCount = Size;

    hlpuart->ErrorCode = HAL_LPUART_ERROR_NONE;
    hlpuart->gState = HAL_LPUART_STATE_BUSY_TX;

    /* Process Unlocked */
    __HAL_UNLOCK(hlpuart);

    /* Enable the LPUART Transmit data Complete Interrupt */
    __HAL_LPUART_ENABLE_IT(hlpuart, LPUART_IT_TC);
	
		if(hlpuart->Init.WordLength == LPUART_WORDLENGTH_9B)
		{
			if(hlpuart->Init.Parity == LPUART_PARITY_EVEN)
			{
				MODIFY_REG(hlpuart->Instance->SCON, LPUART_SCON_TB8, ((ParityTable256[*pData] & LPUART_BIT0_Msk) << LPUART_SCON_TB8_Pos));
			}
			else if(hlpuart->Init.Parity == LPUART_PARITY_ODD)
			{
				MODIFY_REG(hlpuart->Instance->SCON, LPUART_SCON_TB8, (((~ParityTable256[*pData]) & LPUART_BIT0_Msk) << LPUART_SCON_TB8_Pos));
			}				
			
			hlpuart->Instance->SBUF = (*pData++ & (uint8_t)0xFF);	
			hlpuart->pTxBuffPtr = pData;
			hlpuart->TxXferCount--;			
		}
		else
		{
			/* uart 8bit communication doesn't support parity transmit */
			hlpuart->Instance->SBUF = (*pData++ & (uint8_t)0xFF);
			hlpuart->pTxBuffPtr = pData;
			hlpuart->TxXferCount--;
		}				
		
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Receives an amount of data in non blocking mode. 
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPUART_Receive_IT(LPUART_HandleTypeDef *hlpuart, uint8_t *pData, uint16_t Size)
{
  /* Check that a Rx process is not already ongoing */
  if(hlpuart->RxState == HAL_LPUART_STATE_READY)
  {
    if((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(hlpuart);

    hlpuart->pRxBuffPtr = pData;
    hlpuart->RxXferSize = Size;
    hlpuart->RxXferCount = Size;

    hlpuart->ErrorCode = HAL_LPUART_ERROR_NONE;
    hlpuart->RxState = HAL_LPUART_STATE_BUSY_RX;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hlpuart);

    /* Enable the LPUART Data Register not empty Interrupt */
    __HAL_LPUART_ENABLE_IT(hlpuart, LPUART_IT_RXNE);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}


/**
  * @brief  Abort ongoing transfers (blocking mode or interrupt mode).
  * @param  hlpuart LPUART handle.
  * @note   This procedure could be used for aborting any ongoing transfer started in Interrupt. 
  *         This procedure performs following operations :
  *           - Disable all uart Interrupts
  *           - Set handle State to READY
  * @note   This procedure is executed in blocking mode : when exiting function, Abort is considered as completed.
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_LPUART_Abort(LPUART_HandleTypeDef *hlpuart)
{
  /* Disable TCIE, RXNE interrupts */
  CLEAR_BIT(hlpuart->Instance->SCON, (LPUART_SCON_TIEN | LPUART_SCON_RIEN | LPUART_SCON_TEEN));

  /* Reset Tx and Rx transfer counters */
  hlpuart->TxXferCount = 0x00U;
  hlpuart->RxXferCount = 0x00U;

  /* Reset ErrorCode */
  hlpuart->ErrorCode = HAL_LPUART_ERROR_NONE;

  /* Restore hlpuart->RxState and hlpuart->gState to Ready */
  hlpuart->RxState = HAL_LPUART_STATE_READY;
  hlpuart->gState = HAL_LPUART_STATE_READY;

  /* Call directly user Abort complete callback */
  HAL_LPUART_AbortCpltCallback(hlpuart);
	
  return HAL_OK;
}
	
/**
  * @brief  Abort ongoing Transmit transfer (blocking mode or interrupt mode).
  * @param  hlpuart LPUART handle.
  * @note   This procedure could be used for aborting any ongoing transfer started in Interrupt mode. 
  *         This procedure performs following operations :
  *           - Disable all uart transmit interrupts
  *           - Set handle State to READY
  * @note   This procedure is executed in blocking mode : when exiting function, Abort is considered as completed.
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_LPUART_AbortTransmit(LPUART_HandleTypeDef *hlpuart)
{
  /* Disable TCIE interrupts */
  CLEAR_BIT(hlpuart->Instance->SCON, (LPUART_SCON_TIEN | LPUART_SCON_TEEN));

  /* Reset Tx transfer counter */
  hlpuart->TxXferCount = 0x00U;
	
  /* Restore hlpuart->gState to Ready */
  hlpuart->gState = HAL_LPUART_STATE_READY;
	
	HAL_LPUART_AbortTransmitCpltCallback(hlpuart);
	
  return HAL_OK;
}

/**
  * @brief  Abort ongoing Receive transfer (blocking mode or interrupt mode).
  * @param  hlpuart LPUART handle.
  * @note   This procedure could be used for aborting any ongoing transfer started in Interrupt mode. 
  *         This procedure performs following operations :
  *           - Disable uart receive interrupts
  *           - Set handle State to READY
  * @note   This procedure is executed in blocking mode : when exiting function, Abort is considered as completed.
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_LPUART_AbortReceive(LPUART_HandleTypeDef *hlpuart)
{
  /* Disable RXNE interrupts */
  CLEAR_BIT(hlpuart->Instance->SCON, (LPUART_SCON_RIEN));

  /* Reset Rx transfer counter */
  hlpuart->RxXferCount = 0x00U;

  /* Restore hlpuart->RxState to Ready */
  hlpuart->RxState = HAL_LPUART_STATE_READY;
	
	HAL_LPUART_AbortReceiveCpltCallback(hlpuart);

  return HAL_OK;
}


/**
  * @brief  This function handles LPUART interrupt request.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval None
  */
void HAL_LPUART_IRQHandler(LPUART_HandleTypeDef *hlpuart)
{
  uint32_t isrflags   = READ_REG(hlpuart->Instance->INTSR);
  uint32_t sconits    = READ_REG(hlpuart->Instance->SCON);
  uint32_t errorflags = 0x00U;
	
  /* If no error occurs */
  errorflags = (isrflags & (uint32_t)LPUART_INTSR_FE);
  if(errorflags == RESET)
  {
    /* LPUART in mode Receiver -------------------------------------------------*/
    if(((isrflags & LPUART_INTSR_RI) != RESET) && ((sconits & LPUART_SCON_RIEN) != RESET))
    {
      if(LPUART_Receive_IT(hlpuart) != HAL_OK)
			{
				/* Non Blocking error : transfer could go on. 
					 Error is notified to user through user error callback */
				HAL_LPUART_ErrorCallback(hlpuart);
				hlpuart->ErrorCode = HAL_LPUART_ERROR_NONE;		
				__HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_FE);				
			}			
      return;
    }
  }

  /* If some errors occur */
  if(errorflags != RESET)
  {
    /* LPUART frame error occurred -----------------------------------*/
    if((isrflags & LPUART_INTSR_FE) != RESET)
    {
      hlpuart->ErrorCode |= HAL_LPUART_ERROR_FE;
    }

    /* Call LPUART Error Call back function if need be --------------------------*/
    if(hlpuart->ErrorCode != HAL_LPUART_ERROR_NONE)
    {
			/* LPUART in mode Receiver -------------------------------------------------*/
			if(((isrflags & LPUART_INTSR_RI) != RESET) && ((sconits & LPUART_SCON_RIEN) != RESET))
      {
        LPUART_Receive_IT(hlpuart);
      }
			/* Non Blocking error : transfer could go on. 
				 Error is notified to user through user error callback */
			HAL_LPUART_ErrorCallback(hlpuart);
			hlpuart->ErrorCode = HAL_LPUART_ERROR_NONE;
			__HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_FE);		
    }
    return;
  } /* End if error occurs */

  /* LPUART in mode Transmitter ------------------------------------------------*/
  if(((isrflags & LPUART_INTSR_TI) != RESET) && ((sconits & LPUART_SCON_TIEN) != RESET))
  {
    LPUART_Transmit_IT(hlpuart);
    return;
  }

}




/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval None
  */
 __weak void HAL_LPUART_TxCpltCallback(LPUART_HandleTypeDef *hlpuart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlpuart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_LPUART_TxCpltCallback could be implemented in the user file
   */ 
}


/**
  * @brief  Rx Transfer completed callbacks.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval None
  */
__weak void HAL_LPUART_RxCpltCallback(LPUART_HandleTypeDef *hlpuart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlpuart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_LPUART_RxCpltCallback could be implemented in the user file
   */
}


/**
  * @brief  LPUART error callbacks.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval None
  */
 __weak void HAL_LPUART_ErrorCallback(LPUART_HandleTypeDef *hlpuart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlpuart); 
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_LPUART_ErrorCallback could be implemented in the user file
   */ 
}

/**
  * @brief  LPUART Abort Complete callback.
  * @param  hlpuart LPUART handle.
  * @retval None
  */
__weak void HAL_LPUART_AbortCpltCallback (LPUART_HandleTypeDef *hlpuart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlpuart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_LPUART_AbortCpltCallback can be implemented in the user file.
   */
}
/**
  * @brief  LPUART Abort Complete callback.
  * @param  hlpuart LPUART handle.
  * @retval None
  */
__weak void HAL_LPUART_AbortTransmitCpltCallback (LPUART_HandleTypeDef *hlpuart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlpuart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_LPUART_AbortTransmitCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  LPUART Abort Receive Complete callback.
  * @param  hlpuart LPUART handle.
  * @retval None
  */
__weak void HAL_LPUART_AbortReceiveCpltCallback (LPUART_HandleTypeDef *hlpuart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hlpuart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_LPUART_AbortReceiveCpltCallback can be implemented in the user file.
   */
}

/**
  * @}
  */


/** @defgroup LPUART_Exported_Functions_Group3 Peripheral State and Errors functions 
  *  @brief   LPUART State and Errors functions 
  *
@verbatim   
  ==============================================================================
                 ##### Peripheral State and Errors functions #####
  ==============================================================================  
 [..]
   This subsection provides a set of functions allowing to return the State of 
   LPUART communication process, return Peripheral Errors occurred during communication 
   process
   (+) HAL_LPUART_GetState() API can be helpful to check in run-time the state of the LPUART peripheral.
   (+) HAL_LPUART_GetError() check in run-time errors that could be occurred during communication. 

@endverbatim
  * @{
  */
  
/**
  * @brief  Returns the LPUART state.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval HAL state
  */
HAL_LPUART_StateTypeDef HAL_LPUART_GetState(LPUART_HandleTypeDef *hlpuart)
{
  uint32_t temp1= 0x00U, temp2 = 0x00U;
  temp1 = hlpuart->gState;
  temp2 = hlpuart->RxState;
  
  return (HAL_LPUART_StateTypeDef)(temp1 | temp2);
}

/**
  * @brief  Return the LPUART error code
  * @param  hlpuart : pointer to a LPUART_HandleTypeDef structure that contains
  *              the configuration information for the specified LPUART.
  * @retval LPUART Error Code
  */
uint32_t HAL_LPUART_GetError(LPUART_HandleTypeDef *hlpuart)
{
  return hlpuart->ErrorCode;
}

/**
  * @}
  */


/**
  * @}
  */

/* Private functions --------------------------------------------------------*/
/** @defgroup LPUART_Private_Functions LPUART Interrupt handle functions 
  *  @brief   LPUART Interrupt handle functions 
  *
@verbatim   
  ==============================================================================
                 ##### LPUART Interrupt handle functions  #####
  ==============================================================================  
 [..]
   This subsection provides a set of functions allowing to clear interrupt flags, and  
   transmit/receive data in LPUART communication process, return Peripheral Errors occurred 
	 during communication process
   (+) LPUART_WaitOnFlagUntilTimeout() wait interrupt state of the LPUART peripheral.
   (+) LPUART_Transmit_IT() transmit data and clear interupt flags during communication. 
   (+) LPUART_Receive_IT() receive data and clear interupt flags during communication.
   (+) LPUART_SetConfig() uart basic configuration including word length, parity, baudrate etc. 	 
@endverbatim
  * @{
  */


/**
  * @brief  This function handles LPUART Communication Timeout.
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @param  Flag: specifies the LPUART flag to check.
  * @param  Status: The new Flag status (SET or RESET).
  * @param  Tickstart Tick start value
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef LPUART_WaitOnFlagUntilTimeout(LPUART_HandleTypeDef *hlpuart, uint32_t Flag, FlagStatus Status, uint32_t Tickstart, uint32_t Timeout)
{
  /* Wait until flag is set */
  while((__HAL_LPUART_GET_FLAG(hlpuart, Flag) ? SET : RESET) == Status) 
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0U)||((HAL_GetTick() - Tickstart ) > Timeout))
      {
        /* Disable TXE, RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
        CLEAR_BIT(hlpuart->Instance->SCON, (LPUART_SCON_RIEN | LPUART_SCON_TIEN));
        
        hlpuart->gState  = HAL_LPUART_STATE_READY;
        hlpuart->RxState = HAL_LPUART_STATE_READY;
        
        /* Process Unlocked */
        __HAL_UNLOCK(hlpuart);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  return HAL_OK;
}


/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hlpuart: Pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval HAL status
  */
static HAL_StatusTypeDef LPUART_Transmit_IT(LPUART_HandleTypeDef *hlpuart)
{
  /* Check that a Tx process is ongoing */
  if(hlpuart->gState == HAL_LPUART_STATE_BUSY_TX)
  {
      /* Clear the LPUART Transmit Complete Interrupt Flag*/		
		__HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_TC);	
		
    if(hlpuart->TxXferCount-- == 0U)
    {
      /* Disable the LPUART Transmit Complete Interrupt */
      __HAL_LPUART_DISABLE_IT(hlpuart, LPUART_IT_TC);
			
			HAL_LPUART_TxCpltCallback(hlpuart);
      /* Tx process is completed, restore hlpuart->gState to Ready */			
			hlpuart->gState = HAL_LPUART_STATE_READY;	
			return HAL_OK;			
    }		
		
    if(hlpuart->Init.WordLength == LPUART_WORDLENGTH_9B)
    {			
			if(hlpuart->Init.Parity == LPUART_PARITY_EVEN)
			{
				MODIFY_REG(hlpuart->Instance->SCON, LPUART_SCON_TB8, ((ParityTable256[*hlpuart->pTxBuffPtr] & LPUART_BIT0_Msk) << LPUART_SCON_TB8_Pos));
			}
			else if(hlpuart->Init.Parity == LPUART_PARITY_ODD)
			{
				MODIFY_REG(hlpuart->Instance->SCON, LPUART_SCON_TB8, (((~ParityTable256[*hlpuart->pTxBuffPtr]) & LPUART_BIT0_Msk) << LPUART_SCON_TB8_Pos));
			}				
			
			hlpuart->Instance->SBUF = (*hlpuart->pTxBuffPtr++ & (uint8_t)0xFF);	
    } 
    else
    {
      hlpuart->Instance->SBUF = (uint8_t)(*hlpuart->pTxBuffPtr++ & (uint8_t)0xFF);
    }
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}



/**
  * @brief  Receives an amount of data in non blocking mode 
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval HAL status
  */
static HAL_StatusTypeDef LPUART_Receive_IT(LPUART_HandleTypeDef *hlpuart)
{
  uint8_t tmp;
  
	/* Check that a Rx process is ongoing */
  if(hlpuart->RxState == HAL_LPUART_STATE_BUSY_RX) 
  {
		__HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_RXNE);		
    if(hlpuart->Init.WordLength == LPUART_WORDLENGTH_9B)
    {
      if(hlpuart->Init.Parity == LPUART_PARITY_NONE)
      {
        *hlpuart->pRxBuffPtr++ = (uint8_t)(hlpuart->Instance->SBUF & (uint8_t)0xFF);
      }
      else if(hlpuart->Init.Parity == LPUART_PARITY_EVEN)
      {
				tmp = (uint8_t)(hlpuart->Instance->SBUF & (uint8_t)0xFF);	
				if((ParityTable256[tmp&((uint8_t)0xFF)]) == (((hlpuart->Instance->SCON & LPUART_SCON_RB8) >> LPUART_SCON_RB8_Pos) & LPUART_BIT0_Msk))	
				{
					*hlpuart->pRxBuffPtr++ = tmp&((uint8_t)0xFF);
				}
				else
				{
					/* Rx error process, set hlpuart->RxState to Error */
					hlpuart->RxState = HAL_LPUART_STATE_ERROR;		
					hlpuart->ErrorCode = HAL_LPUART_ERROR_PARITY;					
					return HAL_ERROR;	
				}					
      }
      else if(hlpuart->Init.Parity == LPUART_PARITY_ODD)
      {
				tmp = (uint8_t)(hlpuart->Instance->SBUF & (uint8_t)0xFF);	
				if((ParityTable256[tmp&((uint8_t)0xFF)]) == ((~((hlpuart->Instance->SCON & LPUART_SCON_RB8) >> LPUART_SCON_RB8_Pos)) & LPUART_BIT0_Msk))	
				{
					*hlpuart->pRxBuffPtr++ = tmp&((uint8_t)0xFF);
				}
				else
				{
					/* Rx error process, set hlpuart->RxState to Error */
					hlpuart->RxState = HAL_LPUART_STATE_ERROR;	
					hlpuart->ErrorCode = HAL_LPUART_ERROR_PARITY;							
					return HAL_ERROR;	
				}					
      }			
    }
    else
    {
      if(hlpuart->Init.Parity != LPUART_PARITY_NONE)
      {
				/* Rx error process, set hlpuart->RxState to Error */
				hlpuart->RxState = HAL_LPUART_STATE_ERROR;
				hlpuart->ErrorCode = HAL_LPUART_ERROR_CONFIG;						
				return HAL_ERROR;				
      }
      else
      {
        *hlpuart->pRxBuffPtr++ = (uint8_t)(hlpuart->Instance->SBUF & (uint8_t)0xFF);
      }
    }

    if(--hlpuart->RxXferCount == 0U)
    {
      /* Disable the Receive Data Interrupt */
      __HAL_LPUART_DISABLE_IT(hlpuart, LPUART_IT_RXNE);

      HAL_LPUART_RxCpltCallback(hlpuart);

      /* Rx process is completed, restore hlpuart->RxState to Ready */
      hlpuart->RxState = HAL_LPUART_STATE_READY;
			
      return HAL_OK;
    }
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Configures the LPUART peripheral. 
  * @param  hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
  *                the configuration information for the specified LPUART module.
  * @retval None
  */
static void LPUART_SetConfig(LPUART_HandleTypeDef *hlpuart)
{
  /* Check the parameters */
  assert_param(IS_LPUART_BAUDRATE(hlpuart->Init.BaudRate));

  /*------- LPUART-associated registers setting : SCON Configuration ------*/
  /* Configure the LPUART Clock, Divider, Word Length and mode: 
		 Set the SCLKSEL bits according to hlpuart->Init.ClkSel value 		
		 Set the DBAUD bits according to hlpuart->Init.BaudDouble value 
     Set the SM bits according to hlpuart->Init.WordLength value 
     Set REN bits according to hlpuart->Init.Mode value */
  MODIFY_REG(hlpuart->Instance->SCON, (LPUART_SCON_SCLKSEL | LPUART_SCON_DBAUD | LPUART_SCON_SM0_SM1 | LPUART_SCON_REN), \
																			 hlpuart->Init.ClkSel | hlpuart->Init.BaudDouble | hlpuart->Init.WordLength | hlpuart->Init.Mode);
	
	if(hlpuart->Init.LowPowerMode == LPUART_MODE_NORMAL)
	{
		CLEAR_BIT(hlpuart->Instance->SCON, LPUART_SCON_LPMODE);
	}
	else
	{
		/* PRSC clock divider setting is only valid in low power mode*/
		SET_BIT(hlpuart->Instance->SCON, LPUART_SCON_LPMODE);
		MODIFY_REG(hlpuart->Instance->SCON, LPUART_SCON_PRSC, hlpuart->Init.ClkDiv);
	}
	
  /*-------------------------- LPUART BAUDCR Configuration ---------------------*/
	if(hlpuart->Init.LowPowerMode == LPUART_MODE_NORMAL)
	{	
		if(hlpuart->Init.ClkSel == LPUART_CLOCK_PCLK)
		{
			hlpuart->Instance->BAUDCR = (((((hlpuart->Init.BaudDouble >> LPUART_SCON_DBAUD_Pos)+1)*HAL_RCC_GetPCLKFreq())/(32*(hlpuart->Init.BaudRate))-1) & LPUART_BAUDCR_BRG) | LPUART_BAUDCR_SELF_BRG;
		}
		else if(hlpuart->Init.ClkSel == LPUART_CLOCK_LXT)
		{
			hlpuart->Instance->BAUDCR = (((((hlpuart->Init.BaudDouble >> LPUART_SCON_DBAUD_Pos)+1)*LXT_VALUE)/(32*(hlpuart->Init.BaudRate))-1) & LPUART_BAUDCR_BRG) | LPUART_BAUDCR_SELF_BRG;
		}
		else if(hlpuart->Init.ClkSel == LPUART_CLOCK_LIRC)
		{
			hlpuart->Instance->BAUDCR = (((((hlpuart->Init.BaudDouble >> LPUART_SCON_DBAUD_Pos)+1)*LIRC_VALUE)/(32*(hlpuart->Init.BaudRate))-1) & LPUART_BAUDCR_BRG) | LPUART_BAUDCR_SELF_BRG;
		}
	}
	else
	{
		//In Lower Power mode, baudrate is fixed at Fsclk/(4*LPUART_SCON.PRSC), LPUART_BAUDCR is meaningless.	
	}
}

/**
  * @}
  */

/**
  * @}
  */ /* End of group LPUART */


#endif /* HAL_LPUART_MODULE_ENABLED */

/**
  * @}
  */ /* group CX32L003_HAL_Driver */

