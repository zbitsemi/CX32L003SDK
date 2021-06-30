/**
  ******************************************************************************
  * @file    cx32l003_hal_uart.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   UART HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter (UART) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
    The UART HAL driver can be used as follows:

    (#) Declare a UART_HandleTypeDef handle structure.
    (#) Initialize the UART low level resources by implementing the HAL_UART_MspInit() API:
        (##) Enable the UARTx interface clock.
        (##) UART pins configuration:
            (+++) Enable the clock for the UART GPIOs.
            (+++) Configure the UART pins.
        (##) NVIC configuration if you need to use interrupt process (HAL_UART_Transmit_IT()
             and HAL_UART_Receive_IT() APIs):
            (+++) Configure the UARTx interrupt priority.
            (+++) Enable the NVIC UART IRQ handle.

    (#) Program the Baud Rate, Word Length, Stop Bit, Parity and Mode(Receiver/Transmitter) 
				in the huart Init structure.

    (#) For the UART asynchronous mode, initialize the UART registers by calling
        the HAL_UART_Init() API.

    (#) For the UART Half duplex mode, initialize the UART registers by calling 
        the HAL_HalfDuplex_Init() API.

     [..] 
       (@) The specific UART interrupts (Transmission complete interrupt, 
            RXNE interrupt and Error Interrupts) will be managed using the macros
            __HAL_UART_ENABLE_IT() and __HAL_UART_DISABLE_IT() inside the transmit 
            and receive process.

     [..] 
       (@) These APIs (HAL_UART_Init() and HAL_HalfDuplex_Init()) configure also the 
            low level Hardware GPIO, CLOCK, CORTEX...etc) by calling the customized
            HAL_UART_MspInit() API.

     [..]
        Three operation modes are available within this driver:

     *** Polling mode IO operation ***
     =================================
     [..]
       (+) Send an amount of data in blocking mode using HAL_UART_Transmit()
       (+) Receive an amount of data in blocking mode using HAL_UART_Receive()

     *** Interrupt mode IO operation ***
     ===================================
     [..]
       (+) Send an amount of data in non blocking mode using HAL_UART_Transmit_IT() 
       (+) At transmission end of transfer HAL_UART_TxCpltCallback is executed and user can 
            add his own code by customization of function pointer HAL_UART_TxCpltCallback
       (+) Receive an amount of data in non blocking mode using HAL_UART_Receive_IT() 
       (+) At reception end of transfer HAL_UART_RxCpltCallback is executed and user can 
            add his own code by customization of function pointer HAL_UART_RxCpltCallback
       (+) In case of transfer Error, HAL_UART_ErrorCallback() function is executed and user can 
            add his own code by customization of function pointer HAL_UART_ErrorCallback

     *** UART HAL driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in UART HAL driver.
      (+) __HAL_UART_GET_FLAG : Check whether the specified UART flag is set or not
      (+) __HAL_UART_CLEAR_FLAG : Clear the specified UART pending flag
      (+) __HAL_UART_ENABLE_IT: Enable the specified UART interrupt
      (+) __HAL_UART_DISABLE_IT: Disable the specified UART interrupt
      (+) __HAL_UART_GET_IT_SOURCE: Check whether the specified UART interrupt has occurred or not

     [..]
       (@) You can refer to the UART HAL driver header file for more useful macros 
  @endverbatim
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

#ifdef HAL_UART_MODULE_ENABLED

/** @defgroup UART UART
  * @brief HAL UART module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup UART_Private_Constants
  * @{
  */
	
/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
#define UART_PARITYBIT_Pos			0x9U
#define UART_BIT0_Msk						0x1U

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
/** @addtogroup UART_Private_Functions
  * @{
  */
 HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart);
 HAL_StatusTypeDef UART_Receive_IT(UART_HandleTypeDef *huart);
static HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status, uint32_t Tickstart, uint32_t Timeout);
static void UART_SetConfig (UART_HandleTypeDef *huart);
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup UART_Exported_Functions UART Exported Functions
  * @{
  */

/** @defgroup UART_Exported_Functions_Group1 Initialization and de-initialization functions 
  *  @brief    Initialization and Configuration functions 
  *
@verbatim
  ==============================================================================
            ##### Initialization and Configuration functions #####
  ==============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the UARTx 
    in asynchronous mode.
      (+) For the asynchronous mode only these parameters can be configured: 
        (++) Baud Rate
        (++) Word Length						
        (++) Receiver/transmitter modes
    [..]
    The HAL_UART_Init() and HAL_HalfDuplex_Init() APIs follow respectively the 
		UART asynchronous, UART Half duplex, configuration procedures (details for the 
		procedures are available in reference manuals)

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the UART mode according to the specified parameters in
  *         the UART_InitTypeDef and create the associated handle.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)
{
  /* Check the UART handle allocation */
  if(huart == NULL)
  {
    return HAL_ERROR;
  }
  
  if(huart->gState == HAL_UART_STATE_RESET)
  {  
    /* Allocate lock resource and initialize it */
    huart->Lock = HAL_UNLOCKED;

    /* Init the low level hardware */
    HAL_UART_MspInit(huart);
  }

  huart->gState = HAL_UART_STATE_BUSY;
  
  /* Set the UART Communication parameters */
  UART_SetConfig(huart);

  /* Initialize the UART state */
  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->gState= HAL_UART_STATE_READY;
  huart->RxState= HAL_UART_STATE_READY;
  
  return HAL_OK;
}

/**
  * @brief  Initializes the half-duplex mode according to the specified
  *         parameters in the UART_InitTypeDef and create the associated handle.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart)
{
  /* Check the UART handle allocation */
  if(huart == NULL)
  {
    return HAL_ERROR;
  }
 
  if(huart->gState == HAL_UART_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    huart->Lock = HAL_UNLOCKED;
    /* Init the low level hardware */
    HAL_UART_MspInit(huart);
  }

  huart->gState = HAL_UART_STATE_BUSY;

  /* Set the UART Communication parameters */
  UART_SetConfig(huart);
   
  /* Enable the Half-Duplex mode by clear the SM0_1 bit in the SCON register */
	if(huart->Init.HalfDuplexMode == UART_HALFDUPLEX_ENABLE)
	{
		CLEAR_BIT(huart->Instance->SCON, UART_SCON_SM0_SM1);
	}
  
  /* Initialize the UART state*/
  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->gState= HAL_UART_STATE_READY;
  huart->RxState= HAL_UART_STATE_READY;
  
  return HAL_OK;
}


/**
  * @brief  DeInitializes the UART peripheral. 
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart)
{
  /* Check the UART handle allocation */
  if(huart == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_UART_INSTANCE(huart->Instance));

  huart->gState = HAL_UART_STATE_BUSY;

  /* DeInit the low level hardware */
  HAL_UART_MspDeInit(huart);

  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->gState = HAL_UART_STATE_RESET;
  huart->RxState = HAL_UART_STATE_RESET;

  /* Process Unlock */
  __HAL_UNLOCK(huart);

  return HAL_OK;
}

/**
  * @brief  UART MSP Init.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
__weak void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_MspInit could be implemented in the user file
   */
}

/**
  * @brief  UART MSP DeInit.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
__weak void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_MspDeInit could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup UART_Exported_Functions_Group2 IO operation functions 
  *  @brief UART Transmit and Receive functions 
  *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the UART asynchronous
    and Half duplex data transfers.

    (#) There are two modes of transfer:
       (++) Blocking mode: The communication is performed in polling mode. 
            The HAL status of all data processing is returned by the same function 
            after finishing transfer.  
       (++) Non blocking mode: The communication is performed using Interrupts, these 
						APIs return the HAL status.
            The end of the data processing will be indicated through the 
            dedicated UART IRQ when using Interrupt mode.
            The HAL_UART_TxCpltCallback(), HAL_UART_RxCpltCallback() user callbacks 
            will be executed respectively at the end of the transmit or receive process.
            The HAL_UART_ErrorCallback() user callback will be executed when 
            a communication error is detected.

    (#) Blocking mode APIs are:
        (++) HAL_UART_Transmit()
        (++) HAL_UART_Receive() 

    (#) Non Blocking mode APIs with Interrupt are:
        (++) HAL_UART_Transmit_IT()
        (++) HAL_UART_Receive_IT()
        (++) HAL_UART_IRQHandler()

    (#) A set of Transfer Complete Callbacks are provided in non blocking mode:
        (++) HAL_UART_TxCpltCallback()
        (++) HAL_UART_RxCpltCallback()
        (++) HAL_UART_ErrorCallback()

    [..]
      (@) In the Half duplex communication, it is forbidden to run the transmit 
          and receive process in parallel, the UART state HAL_UART_STATE_BUSY_TX_RX
          can't be useful.

@endverbatim
  * @{
  */



/**
  * @brief  Sends an amount of data in blocking mode.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be sent
  * @param  Timeout: Timeout duration  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  
  /* Check that a Tx process is not already ongoing */
  if(huart->gState == HAL_UART_STATE_READY)
  {
    if((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(huart);

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->gState = HAL_UART_STATE_BUSY_TX;

    /* Init tickstart for timeout management */
    tickstart = HAL_GetTick();

		/* TC interrupt must be enabled to unmask TC flag for polling */
		__HAL_UART_ENABLE_IT(huart, UART_IT_TC);			
		
    huart->TxXferSize = Size;
    huart->TxXferCount = Size;
    while(huart->TxXferCount > 0U)
    {
      huart->TxXferCount--;
      if(huart->Init.WordLength == UART_WORDLENGTH_9B)
      {			
				if(huart->Init.Parity == UART_PARITY_EVEN)
				{
					MODIFY_REG(huart->Instance->SCON, UART_SCON_TB8, ((ParityTable256[*pData] & UART_BIT0_Msk) << UART_SCON_TB8_Pos));
				}
				else if(huart->Init.Parity == UART_PARITY_ODD)
				{
					MODIFY_REG(huart->Instance->SCON, UART_SCON_TB8, (((~ParityTable256[*pData]) & UART_BIT0_Msk) << UART_SCON_TB8_Pos));
				}						
					
        huart->Instance->SBUF = (*pData++ & (uint8_t)0xFF);	
				
        if(UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TC, RESET, tickstart, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }	
				__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_TC);	
      }
      else
      {
        huart->Instance->SBUF = (*pData++ & (uint8_t)0xFF);				
				/* uart 8bit communication doesn't support parity transmit */
        if(UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TC, RESET, tickstart, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
				__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_TC);	
      }
    }

    /* At end of Tx process, restore huart->gState to Ready */
    huart->gState = HAL_UART_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(huart);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}


void Naked_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size,IRQn_Type IRQn)
{
		uint16_t Timeout;
		HAL_NVIC_DisableIRQ(IRQn);
		/* TC interrupt must be enabled to unmask TC flag for polling */
		__HAL_UART_ENABLE_IT(huart, UART_IT_TC);			
		
    huart->TxXferCount = Size;
    while(huart->TxXferCount > 0U)
    {
      huart->TxXferCount--;
      if(huart->Init.WordLength == UART_WORDLENGTH_9B)
      {			
				if(huart->Init.Parity == UART_PARITY_EVEN)
				{
					MODIFY_REG(huart->Instance->SCON, UART_SCON_TB8, ((ParityTable256[*pData] & UART_BIT0_Msk) << UART_SCON_TB8_Pos));
				}
				else if(huart->Init.Parity == UART_PARITY_ODD)
				{
					MODIFY_REG(huart->Instance->SCON, UART_SCON_TB8, (((~ParityTable256[*pData]) & UART_BIT0_Msk) << UART_SCON_TB8_Pos));
				}						
        huart->Instance->SBUF = (*pData++ & (uint8_t)0xFF);	
      }
      else
      {
        huart->Instance->SBUF = (*pData++ & (uint8_t)0xFF);				
      }
			Timeout = 0;
			while((huart->Instance->INTSR & UART_FLAG_TC) != (UART_FLAG_TC)) 
			{
				/* Check for the Timeout */
				Timeout++;
				if(Timeout >= 5000)
				{
					huart->TxXferCount = 0;
					break;
				}
			}
			__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_TC);	
    }
		/* Disable TXE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
		CLEAR_BIT(huart->Instance->SCON, (UART_SCON_TIEN));
		HAL_NVIC_EnableIRQ(IRQn); 
}
/**
  * @brief  Receive an amount of data in blocking mode. 
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be received
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint8_t tmp;
  uint32_t tickstart = 0U;
  
  /* Check that a Rx process is not already ongoing */
  if(huart->RxState == HAL_UART_STATE_READY)
  {
    if((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(huart);
    
    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->RxState = HAL_UART_STATE_BUSY_RX;

    /* Init tickstart for timeout managment */
    tickstart = HAL_GetTick();
		
		/* RXNE interrupt must be enabled to unmask RXNE flag for polling */
		__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);		
		
    huart->RxXferSize = Size;
    huart->RxXferCount = Size;

    /* Check the remain data to be received */
    while(huart->RxXferCount > 0U)
    {
      huart->RxXferCount--;
      if(huart->Init.WordLength == UART_WORDLENGTH_9B)
      {
        if(UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
				__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_RXNE);

				tmp = (uint8_t)(huart->Instance->SBUF & (uint8_t)0xFF);
				if(huart->Init.Parity == UART_PARITY_NONE)
				{
						*pData++ = tmp&((uint8_t)0xFF);					
				}
				else if(huart->Init.Parity == UART_PARITY_EVEN)
				{					
					if((ParityTable256[tmp&((uint8_t)0xFF)]) == (((huart->Instance->SCON & UART_SCON_RB8) >> UART_SCON_RB8_Pos) & UART_BIT0_Msk))	
					{
						*pData++ = tmp&((uint8_t)0xFF);
					}
					else
					{
						/* Rx error process, set huart->RxState to Error */
						huart->RxState = HAL_UART_STATE_ERROR;
						huart->ErrorCode = HAL_UART_ERROR_PARITY;						
						__HAL_UNLOCK(huart);
						return HAL_ERROR;						
					}				
				}
				else if(huart->Init.Parity == UART_PARITY_ODD)
				{
					if((ParityTable256[tmp&((uint8_t)0xFF)]) == ((~((huart->Instance->SCON & UART_SCON_RB8) >> UART_SCON_RB8_Pos)) & UART_BIT0_Msk))	
					{
						*pData++ = tmp&((uint8_t)0xFF);
					}	
					else
					{
						/* Rx error process, set huart->RxState to Error */
						huart->RxState = HAL_UART_STATE_ERROR;
						huart->ErrorCode = HAL_UART_ERROR_PARITY;								
						__HAL_UNLOCK(huart);
						return HAL_ERROR;						
					}							
				}
				else
				{
					/* Rx error process, set huart->RxState to Error */
					huart->RxState = HAL_UART_STATE_ERROR;
					__HAL_UNLOCK(huart);
					return HAL_ERROR;						
				}
      } 
      else
      {
        if(UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
				__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_RXNE);
				
				/* uart 8bit communication doesn't support parity check */
        if(huart->Init.Parity != UART_PARITY_NONE)
        {
					/* Rx error process, set huart->RxState to Error */
					huart->RxState = HAL_UART_STATE_ERROR;
					__HAL_UNLOCK(huart);
					return HAL_ERROR;		
        }
        else
        {
          *pData++ = (uint8_t)(huart->Instance->SBUF & (uint8_t)0x00FF);
        }
      }
    }

    /* At end of Rx process, restore huart->RxState to Ready */
    huart->RxState = HAL_UART_STATE_READY;
    
    /* Process Unlocked */
    __HAL_UNLOCK(huart);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  /* Check that a Tx process is not already ongoing */
  if(huart->gState == HAL_UART_STATE_READY)
  {
    if((pData == NULL) || (Size == 0U)) 
    {
      return HAL_ERROR;
    }
    /* Process Locked */
    __HAL_LOCK(huart);

    huart->pTxBuffPtr = pData;
    huart->TxXferSize = Size;
    huart->TxXferCount = Size;

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->gState = HAL_UART_STATE_BUSY_TX;

    /* Process Unlocked */
    __HAL_UNLOCK(huart);

    /* Enable the UART Transmit data complete Interrupt */
    /* This interrupt must be enabled first, otherwise TC flag will not set */		
    __HAL_UART_ENABLE_IT(huart, UART_IT_TC);		
		
		if(huart->Init.WordLength == UART_WORDLENGTH_9B)
		{
			if(huart->Init.Parity == UART_PARITY_EVEN)
			{
				MODIFY_REG(huart->Instance->SCON, UART_SCON_TB8, ((ParityTable256[*pData] & UART_BIT0_Msk) << UART_SCON_TB8_Pos));
			}
			else if(huart->Init.Parity == UART_PARITY_ODD)
			{
				MODIFY_REG(huart->Instance->SCON, UART_SCON_TB8, (((~ParityTable256[*pData]) & UART_BIT0_Msk) << UART_SCON_TB8_Pos));
			}				
			
			huart->Instance->SBUF = (*pData++ & (uint8_t)0xFF);	
			huart->pTxBuffPtr = pData;
			huart->TxXferCount--;			
		}
		else
		{
			/* uart 8bit communication doesn't support parity transmit */
			huart->Instance->SBUF = (*pData++ & (uint8_t)0xFF);
			huart->pTxBuffPtr = pData;
			huart->TxXferCount--;
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
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  /* Check that a Rx process is not already ongoing */
  if(huart->RxState == HAL_UART_STATE_READY)
  {
    if((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(huart);

    huart->pRxBuffPtr = pData;
    huart->RxXferSize = Size;
    huart->RxXferCount = Size;

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->RxState = HAL_UART_STATE_BUSY_RX;
    
    /* Process Unlocked */
    __HAL_UNLOCK(huart);

    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}


void Naked_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    huart->pRxBuffPtr = pData;
    huart->RxXferSize = Size;
    huart->RxXferCount = Size;

    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
  
}

/**
  * @brief  Abort ongoing transfers (blocking mode or interrupt mode).
  * @param  huart UART handle.
  * @note   This procedure could be used for aborting any ongoing transfer started in Interrupt. 
  *         This procedure performs following operations :
  *           - Disable all uart Interrupts
  *           - Set handle State to READY
  * @note   This procedure is executed in blocking mode : when exiting function, Abort is considered as completed.
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart)
{
  /* Disable TCIE, RXNE interrupts */
  CLEAR_BIT(huart->Instance->SCON, (UART_SCON_TIEN | UART_SCON_RIEN));

  /* Reset Tx and Rx transfer counters */
  huart->TxXferCount = 0x00U;
  huart->RxXferCount = 0x00U;

  /* Reset ErrorCode */
  huart->ErrorCode = HAL_UART_ERROR_NONE;

  /* Restore huart->RxState and huart->gState to Ready */
  huart->RxState = HAL_UART_STATE_READY;
  huart->gState = HAL_UART_STATE_READY;

  /* Call directly user Abort complete callback */
  HAL_UART_AbortCpltCallback(huart);
	
  return HAL_OK;
}
	
/**
  * @brief  Abort ongoing Transmit transfer (blocking mode or interrupt mode).
  * @param  huart UART handle.
  * @note   This procedure could be used for aborting any ongoing transfer started in Interrupt mode. 
  *         This procedure performs following operations :
  *           - Disable all uart transmit interrupts
  *           - Set handle State to READY
  * @note   This procedure is executed in blocking mode : when exiting function, Abort is considered as completed.
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_UART_AbortTransmit(UART_HandleTypeDef *huart)
{
  /* Disable TCIE interrupts */
  CLEAR_BIT(huart->Instance->SCON, UART_SCON_TIEN);

  /* Reset Tx transfer counter */
  huart->TxXferCount = 0x00U;
	
  /* Restore huart->gState to Ready */
  huart->gState = HAL_UART_STATE_READY;
	
	HAL_UART_AbortTransmitCpltCallback(huart);
	
  return HAL_OK;
}

/**
  * @brief  Abort ongoing Receive transfer (blocking mode or interrupt mode).
  * @param  huart UART handle.
  * @note   This procedure could be used for aborting any ongoing transfer started in Interrupt mode. 
  *         This procedure performs following operations :
  *           - Disable uart receive interrupts
  *           - Set handle State to READY
  * @note   This procedure is executed in blocking mode : when exiting function, Abort is considered as completed.
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_UART_AbortReceive(UART_HandleTypeDef *huart)
{
  /* Disable RXNE interrupts */
  CLEAR_BIT(huart->Instance->SCON, (UART_SCON_RIEN));

  /* Reset Rx transfer counter */
  huart->RxXferCount = 0x00U;

  /* Restore huart->RxState to Ready */
  huart->RxState = HAL_UART_STATE_READY;
	
	HAL_UART_AbortReceiveCpltCallback(huart);

  return HAL_OK;
}


/**
  * @brief  This function handles UART interrupt request.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)
{
  uint32_t isrflags   = READ_REG(huart->Instance->INTSR);
  uint32_t sconits    = READ_REG(huart->Instance->SCON);
  uint32_t errorflags = 0x00U;
	
  /* If no error occurs */
  errorflags = (isrflags & (uint32_t)UART_INTSR_FE);
  if(errorflags == RESET)
  {
    /* UART in mode Receiver -------------------------------------------------*/
    if(((isrflags & UART_INTSR_RI) != RESET) && ((sconits & UART_SCON_RIEN) != RESET))
    {
      if(UART_Receive_IT(huart) != HAL_OK)
			{
				/* Non Blocking error : transfer could go on. 
					 Error is notified to user through user error callback */
				HAL_UART_ErrorCallback(huart);
				huart->ErrorCode = HAL_UART_ERROR_NONE;				
			}
      return;
    }
  }

  /* If some errors occur */
  if(errorflags != RESET)
  {
    /* UART frame error occurred -----------------------------------*/
    if((isrflags & UART_INTSR_FE) != RESET)
    {
      huart->ErrorCode |= HAL_UART_ERROR_FE;
			__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_FE);	
    }

    /* Call UART Error Call back function if need be --------------------------*/
    if(huart->ErrorCode != HAL_UART_ERROR_NONE)
    {
			/* UART in mode Receiver -------------------------------------------------*/
			if(((isrflags & UART_INTSR_RI) != RESET) && ((sconits & UART_SCON_RIEN) != RESET))
      {
        UART_Receive_IT(huart);
      }
			/* Non Blocking error : transfer could go on. 
				 Error is notified to user through user error callback */
			HAL_UART_ErrorCallback(huart);
			huart->ErrorCode = HAL_UART_ERROR_NONE;
    }
    return;
  } /* End if error occurs */

  /* UART in mode Transmitter ------------------------------------------------*/
  if(((isrflags & UART_INTSR_TI) != RESET) && ((sconits & UART_SCON_TIEN) != RESET))
  {
    UART_Transmit_IT(huart);
    return;
  }

}

void Naked_UART_IRQHandler(UART_HandleTypeDef *huart)
{
		uint8_t tmp;
		uint32_t isrflags   = READ_REG(huart->Instance->INTSR);
		uint32_t sconits    = READ_REG(huart->Instance->SCON);
		uint32_t errorflags = 0x00U;
		
		/* If no error occurs */
		errorflags = (isrflags & (uint32_t)UART_INTSR_FE);
		if(errorflags == RESET)
		{
			/* UART in mode Receiver -------------------------------------------------*/
			if(((isrflags & UART_INTSR_RI) != RESET) && ((sconits & UART_SCON_RIEN) != RESET))
			{
					__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_RXNE);		
					if(huart->Init.WordLength == UART_WORDLENGTH_9B)
					{
						if(huart->Init.Parity == UART_PARITY_NONE)
						{
							*huart->pRxBuffPtr++ = (uint8_t)(huart->Instance->SBUF & (uint8_t)0xFF);
						}
						else if(huart->Init.Parity == UART_PARITY_EVEN)
						{
							tmp = (uint8_t)(huart->Instance->SBUF & (uint8_t)0x0FF);	
							if((ParityTable256[tmp&((uint8_t)0xFF)]) == (((huart->Instance->SCON & UART_SCON_RB8) >> UART_SCON_RB8_Pos) & UART_BIT0_Msk))	
							{
								*huart->pRxBuffPtr++ = tmp&((uint8_t)0xFF);
							}			
						}
						else if(huart->Init.Parity == UART_PARITY_ODD)
						{
							tmp = (uint8_t)(huart->Instance->SBUF & (uint8_t)0xFF);	
							if((ParityTable256[tmp&((uint8_t)0xFF)]) == ((~((huart->Instance->SCON & UART_SCON_RB8) >> UART_SCON_RB8_Pos)) & UART_BIT0_Msk))
							{
								*huart->pRxBuffPtr++ = tmp&((uint8_t)0xFF);
							}				
						}			
					}
					else
					{
						*huart->pRxBuffPtr++ = (uint8_t)(huart->Instance->SBUF & (uint8_t)0xFF);
					}
					if(--huart->RxXferCount == 0U)
					{
						/* Disable the Receive Data Interrupt */
//						__HAL_UART_DISABLE_IT(huart, UART_IT_RXNE);
						HAL_UART_RxCpltCallback(huart);		
					}
					
				return;
			}
		}

		/* If some errors occur */
		if(errorflags != RESET)
		{
			/* UART frame error occurred -----------------------------------*/
			if((isrflags & UART_INTSR_FE) != RESET)
			{
	//      sUartxHandle.ErrorCode |= HAL_UART_ERROR_FE;
				__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_FE);	
			}
			return;
		} /* End if error occurs */

		/* UART in mode Transmitter ------------------------------------------------*/
	//  if(((isrflags & UART_INTSR_TI) != RESET) && ((sconits & UART_SCON_TIEN) != RESET))
	//  {
	//    UART_Transmit_IT(huart);
	//    return;
	//  }

}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
 __weak void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
   */ 
}


/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
__weak void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
   */
}


/**
  * @brief  UART error callbacks.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
 __weak void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart); 
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_ErrorCallback could be implemented in the user file
   */ 
}

/**
  * @brief  UART Abort Complete callback.
  * @param  huart UART handle.
  * @retval None
  */
__weak void HAL_UART_AbortCpltCallback (UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_AbortCpltCallback can be implemented in the user file.
   */
}
/**
  * @brief  UART Abort Complete callback.
  * @param  huart UART handle.
  * @retval None
  */
__weak void HAL_UART_AbortTransmitCpltCallback (UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_AbortTransmitCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  UART Abort Receive Complete callback.
  * @param  huart UART handle.
  * @retval None
  */
__weak void HAL_UART_AbortReceiveCpltCallback (UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_AbortReceiveCpltCallback can be implemented in the user file.
   */
}

/**
  * @}
  */


/** @defgroup UART_Exported_Functions_Group3 Peripheral State and Errors functions 
  *  @brief   UART State and Errors functions 
  *
@verbatim   
  ==============================================================================
                 ##### Peripheral State and Errors functions #####
  ==============================================================================  
 [..]
   This subsection provides a set of functions allowing to return the State of 
   UART communication process, return Peripheral Errors occurred during communication 
   process
   (+) HAL_UART_GetState() API can be helpful to check in run-time the state of the UART peripheral.
   (+) HAL_UART_GetError() check in run-time errors that could be occurred during communication. 

@endverbatim
  * @{
  */
  
/**
  * @brief  Returns the UART state.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL state
  */
HAL_UART_StateTypeDef HAL_UART_GetState(UART_HandleTypeDef *huart)
{
  uint32_t temp1= 0x00U, temp2 = 0x00U;
  temp1 = huart->gState;
  temp2 = huart->RxState;
  
  return (HAL_UART_StateTypeDef)(temp1 | temp2);
}

/**
  * @brief  Return the UART error code
  * @param  huart : pointer to a UART_HandleTypeDef structure that contains
  *              the configuration information for the specified UART.
  * @retval UART Error Code
  */
uint32_t HAL_UART_GetError(UART_HandleTypeDef *huart)
{
  return huart->ErrorCode;
}

/**
  * @}
  */


/**
  * @}
  */

/* Private functions --------------------------------------------------------*/
/** @defgroup UART_Private_Functions UART Interrupt handle functions 
  *  @brief   UART Interrupt handle functions 
  *
@verbatim   
  ==============================================================================
                 ##### UART Interrupt handle functions  #####
  ==============================================================================  
 [..]
   This subsection provides a set of functions allowing to clear interrupt flags, and  
   transmit/receive data in UART communication process, return Peripheral Errors occurred 
	 during communication process
   (+) UART_WaitOnFlagUntilTimeout() wait interrupt state of the UART peripheral.
   (+) UART_Transmit_IT() transmit data and clear interupt flags during communication. 
   (+) UART_Receive_IT() receive data and clear interupt flags during communication.
   (+) UART_SetConfig() uart basic configuration including word length, parity, baudrate etc. 	 
@endverbatim
  * @{
  */


/**
  * @brief  This function handles UART Communication Timeout.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @param  Flag: specifies the UART flag to check.
  * @param  Status: The new Flag status (SET or RESET).
  * @param  Tickstart Tick start value
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status, uint32_t Tickstart, uint32_t Timeout)
{
  /* Wait until flag is set */
  while((__HAL_UART_GET_FLAG(huart, Flag) ? SET : RESET) == Status) 
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0U)||((HAL_GetTick() - Tickstart ) > Timeout))
      {
        /* Disable TXE, RXNE interrupts for the interrupt process */
        CLEAR_BIT(huart->Instance->SCON, (UART_SCON_RIEN | UART_SCON_TIEN));
        
        huart->gState  = HAL_UART_STATE_READY;
        huart->RxState = HAL_UART_STATE_READY;
        
        /* Process Unlocked */
        __HAL_UNLOCK(huart);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  return HAL_OK;
}


/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  huart: Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
 HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart)
{
  /* Check that a Tx process is ongoing */
  if(huart->gState == HAL_UART_STATE_BUSY_TX)
  {
      /* Clear the UART Transmit Complete Interrupt Flag*/				
		__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_TC);

		if(huart->TxXferCount-- == 0U)
    {
      /* Disable the UART Transmit Complete Interrupt */
      __HAL_UART_DISABLE_IT(huart, UART_IT_TC);	
			HAL_UART_TxCpltCallback(huart);			
      /* Tx process is completed, restore huart->gState to Ready */			
			huart->gState = HAL_UART_STATE_READY;
			return HAL_OK;
    }				
		
    if(huart->Init.WordLength == UART_WORDLENGTH_9B)
    {						
			if(huart->Init.Parity == UART_PARITY_EVEN)
			{
				MODIFY_REG(huart->Instance->SCON, UART_SCON_TB8, ((ParityTable256[*huart->pTxBuffPtr] & UART_BIT0_Msk) << UART_SCON_TB8_Pos));
			}
			else if(huart->Init.Parity == UART_PARITY_ODD)
			{
				MODIFY_REG(huart->Instance->SCON, UART_SCON_TB8, (((~ParityTable256[*huart->pTxBuffPtr]) & UART_BIT0_Msk) << UART_SCON_TB8_Pos));
			}				
			
      huart->Instance->SBUF = (uint8_t)((*huart->pTxBuffPtr++) & (uint8_t)0xFF);
    } 
    else
    {
      huart->Instance->SBUF = (uint8_t)((*huart->pTxBuffPtr++) & (uint8_t)0xFF);
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
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef UART_Receive_IT(UART_HandleTypeDef *huart)
{
  uint8_t tmp;
  
	/* Check that a Rx process is ongoing */
  if(huart->RxState == HAL_UART_STATE_BUSY_RX) 
  {
		__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_RXNE);		
    if(huart->Init.WordLength == UART_WORDLENGTH_9B)
    {
      if(huart->Init.Parity == UART_PARITY_NONE)
      {
        *huart->pRxBuffPtr++ = (uint8_t)(huart->Instance->SBUF & (uint8_t)0xFF);
      }
      else if(huart->Init.Parity == UART_PARITY_EVEN)
      {
				tmp = (uint8_t)(huart->Instance->SBUF & (uint8_t)0x0FF);	
				if((ParityTable256[tmp&((uint8_t)0xFF)]) == (((huart->Instance->SCON & UART_SCON_RB8) >> UART_SCON_RB8_Pos) & UART_BIT0_Msk))	
				{
					*huart->pRxBuffPtr++ = tmp&((uint8_t)0xFF);
				}
				else
				{
					/* Rx error process, set huart->RxState to Error */
					huart->RxState = HAL_UART_STATE_ERROR;		
					huart->ErrorCode = HAL_UART_ERROR_PARITY;
					return HAL_ERROR;	
				}					
      }
      else if(huart->Init.Parity == UART_PARITY_ODD)
      {
				tmp = (uint8_t)(huart->Instance->SBUF & (uint8_t)0xFF);	
				if((ParityTable256[tmp&((uint8_t)0xFF)]) == ((~((huart->Instance->SCON & UART_SCON_RB8) >> UART_SCON_RB8_Pos)) & UART_BIT0_Msk))
				{
					*huart->pRxBuffPtr++ = tmp&((uint8_t)0xFF);
				}
				else
				{
					/* Rx error process, set huart->RxState to Error */
					huart->RxState = HAL_UART_STATE_ERROR;		
					huart->ErrorCode = HAL_UART_ERROR_PARITY;					
					return HAL_ERROR;	
				}					
      }			
    }
    else
    {
      if(huart->Init.Parity != UART_PARITY_NONE)
      {
				/* Rx error process, set huart->RxState to Error */
				huart->RxState = HAL_UART_STATE_ERROR;	
				huart->ErrorCode = HAL_UART_ERROR_CONFIG;						
				return HAL_ERROR;				
      }
      else
      {
        *huart->pRxBuffPtr++ = (uint8_t)(huart->Instance->SBUF & (uint8_t)0xFF);
      }
    }

    if(--huart->RxXferCount == 0U)
    {
      /* Disable the Receive Data Interrupt */
      __HAL_UART_DISABLE_IT(huart, UART_IT_RXNE);
			/* Rx process is completed, restore huart->RxState to Ready */
			huart->RxState = HAL_UART_STATE_READY;
			
      HAL_UART_RxCpltCallback(huart);		
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
  * @brief  Receives an amount of data in non blocking mode 
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef UART_Single_Receive_IT(UART_HandleTypeDef *huart)
{
  uint8_t tmp;
	/* Check that a Rx process is ongoing */
	if(huart->Init.WordLength == UART_WORDLENGTH_9B)
	{
		if(huart->Init.Parity == UART_PARITY_NONE)
		{
			*huart->pRxBuffPtr = (uint8_t)(huart->Instance->SBUF & (uint8_t)0xFF);
		}
		else if(huart->Init.Parity == UART_PARITY_EVEN)
		{
			tmp = (uint8_t)(huart->Instance->SBUF & (uint8_t)0x0FF);	
			if((ParityTable256[tmp&((uint8_t)0xFF)]) == (((huart->Instance->SCON & UART_SCON_RB8) >> UART_SCON_RB8_Pos) & UART_BIT0_Msk))	
			{
				*huart->pRxBuffPtr = tmp&((uint8_t)0xFF);
			}
		}
		else if(huart->Init.Parity == UART_PARITY_ODD)
		{
			tmp = (uint8_t)(huart->Instance->SBUF & (uint8_t)0xFF);	
			if((ParityTable256[tmp&((uint8_t)0xFF)]) == ((~((huart->Instance->SCON & UART_SCON_RB8) >> UART_SCON_RB8_Pos)) & UART_BIT0_Msk))
			{
				*huart->pRxBuffPtr = tmp&((uint8_t)0xFF);
			}			
		}			
	}
	else
	{
		 *huart->pRxBuffPtr = (uint8_t)(huart->Instance->SBUF & (uint8_t)0xFF);
	}

	return HAL_OK;
}

/**
  * @brief  Configures the UART peripheral. 
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
static void UART_SetConfig(UART_HandleTypeDef *huart)
{
  /* Check the parameters */
  assert_param(IS_UART_BAUDRATE(huart->Init.BaudRate));

  /*------- UART-associated registers setting : SCON Configuration ------*/
  /* Configure the UART Word Length and mode: 
		 Set the DBAUD bits according to huart->Init.BaudDouble value 
     Set the SM bits according to huart->Init.WordLength value 
     Set REN bits according to huart->Init.Mode value */
  MODIFY_REG(huart->Instance->SCON, (UART_SCON_DBAUD | UART_SCON_SM0_SM1 | UART_SCON_REN), huart->Init.BaudDouble | huart->Init.WordLength | huart->Init.Mode);
	
  /*-------------------------- UART BAUDCR Configuration ---------------------*/
  huart->Instance->BAUDCR = (((((huart->Init.BaudDouble >> UART_SCON_DBAUD_Pos)+1)*HAL_RCC_GetPCLKFreq())/(32*(huart->Init.BaudRate))-1) & UART_BAUDCR_BRG) | UART_BAUDCR_SELF_BRG;

}


/*****************  ����һ���ֽ� **********************/
void Uart_SendByte( UART_TypeDef * pUSARTx, uint8_t Data)
{
	uint16_t Timeout = 0;

	pUSARTx->SBUF = (uint32_t)Data;
	while((pUSARTx->INTSR&UART_FLAG_TC) != UART_FLAG_TC)
	{
		Timeout++;
		if(Timeout > 5000)
		{
			break;
		}	
	}
	pUSARTx->INTCLR |= UART_FLAG_TC;
}

/**
  * @}
  */

/**
  * @}
  */ /* End of group UART */

#endif /* HAL_UART_MODULE_ENABLED */

/**
  * @}
  */

