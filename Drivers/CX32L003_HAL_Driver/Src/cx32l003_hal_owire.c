/**
  ******************************************************************************
  * @file    cx32l003_hal_owire.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   OWIRE HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the One-Wire peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

#ifdef HAL_OWIRE_MODULE_ENABLED

/** @defgroup OWIRE One-Wire
  * @brief HAL OWIRE module driver
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/** @defgroup OWIRE_Private_Functions
	* @brief   Private functions
  * @{
  */

static void OWIRE_InitDoneISR(OWIRE_HandleTypeDef *howire);
static void OWIRE_TxDoneISR(OWIRE_HandleTypeDef *howire);
static void OWIRE_RxDoneISR(OWIRE_HandleTypeDef *howire);
static HAL_StatusTypeDef OWIRE_WaitOnFlagUntilTimeout(OWIRE_HandleTypeDef *howire, uint32_t Flag, FlagStatus Status, uint32_t Tickstart, uint32_t Timeout);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup OWIRE_Exported_Functions One-Wire Exported Functions
  * @{
  */

/**
  * @brief  Initializes the OWIRE mode according to the specified parameters in
  *         the OWIRE_InitTypeDef and create the associated handler.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                the configuration information for the specified OWIRE module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_Init(OWIRE_HandleTypeDef *howire)
{
  /* Check the OWIRE handle allocation */
  if(howire == NULL)
  {
    return HAL_ERROR;
  }
  
  if(howire->gState == HAL_OWIRE_STATE_RESET)
  {  
    /* Allocate lock resource and initialize it */
    howire->Lock = HAL_UNLOCKED;

    /* Init the low level hardware */
    HAL_OWIRE_MspInit(howire);
  }

  howire->gState = HAL_OWIRE_STATE_BUSY;
  
  /* Set the OWIRE Communication parameters */
	
	howire->Instance->CR = (howire->Init.ClockDiv | howire->Init.DataSize | howire->Init.FirstBit | howire->Init.ReadMode);
	howire->Instance->NFCR = (howire->Init.NoiseFilterClk | howire->Init.NoiseFilterEn);

  uint32_t cnt = HAL_RCC_GetPCLKFreq()/1000000;
	if(cnt<1)
		cnt = 1;

	howire->Instance->RSTCNT = howire->Init.ResetCounter*cnt; 
	howire->Instance->PRESCNT = howire->Init.PresencePulseCounter*cnt;
	howire->Instance->BITRATECNT = howire->Init.BitRateCounter*cnt;
	howire->Instance->DRVCNT = howire->Init.DriveCounter*cnt; 
	howire->Instance->RDSMPCNT = howire->Init.ReadSamplingCounter*cnt; 
	howire->Instance->RECCNT = howire->Init.RecoverCounter*cnt; 

	/* Enable the OWIRE peripheral */
	howire->Instance->CR |= OWIRE_CR_EN_Msk;	

  /* Initialize the OWIRE state */
  howire->ErrorCode = HAL_OWIRE_ERROR_NONE;
  howire->gState= HAL_OWIRE_STATE_READY;
  
  return HAL_OK;
}

/**
  * @brief  DeInitializes the OWIRE peripheral. 
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                the configuration information for the specified OWIRE module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_DeInit(OWIRE_HandleTypeDef *howire)
{
  /* Check the OWIRE handle allocation */
  if(howire == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_OWIRE_INSTANCE(howire->Instance));

  howire->gState = HAL_OWIRE_STATE_BUSY;

  /* DeInit the low level hardware */
  HAL_OWIRE_MspDeInit(howire);

  howire->ErrorCode = HAL_OWIRE_ERROR_NONE;
  howire->gState = HAL_OWIRE_STATE_RESET;

  /* Process Unlock */
  __HAL_UNLOCK(howire);

  return HAL_OK;
}

/**
  * @brief  OWIRE MSP Init.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                the configuration information for the specified OWIRE module.
  * @retval None
  */
__weak void HAL_OWIRE_MspInit(OWIRE_HandleTypeDef *howire)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(howire);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_OWIRE_MspInit could be implemented in the user file
   */
}

/**
  * @brief  OWIRE MSP DeInit.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                the configuration information for the specified OWIRE module.
  * @retval None
  */
__weak void HAL_OWIRE_MspDeInit(OWIRE_HandleTypeDef *howire)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(howire);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_OWIRE_MspDeInit could be implemented in the user file
   */
}

/**
  * @brief  Send an amount of data in blocking mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @param  pTxData: Pointer to data buffer
  * @param  Size: Amount of data to be sent
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_Transmit(OWIRE_HandleTypeDef *howire, uint8_t *pTxData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;

  if(howire->gState == HAL_OWIRE_STATE_READY)
  {
    if((pTxData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(howire);

    howire->ErrorCode = HAL_OWIRE_ERROR_NONE;
    howire->gState = HAL_OWIRE_STATE_BUSY_TX;

    /* Init tickstart for timeout managment */
    tickstart = HAL_GetTick();

		/* Set Initialization */
		howire->Instance->CMD = OWIRE_COMMAND_INIT;
		
		/* Wait for the initialization done */
		if(OWIRE_WaitOnFlagUntilTimeout(howire, OWIRE_FLAG_INITDONE, SET, tickstart, Timeout) != HAL_OK)
		{
			howire->ErrorCode = HAL_OWIRE_ERROR_INIT;
			return HAL_TIMEOUT;
		}
		__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_INITDONE);
		
		if(__HAL_OWIRE_GET_FLAG(howire, OWIRE_FLAG_ACKERROR))
		{
			__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_ACKERROR);
//			howire->ErrorCode = HAL_OWIRE_ERROR_NOACK;
//			return HAL_ERROR;
		}

		/* For both OWIRE_DATASIZE_8BIT mode and OWIRE_DATASIZE_1BIT. But in OWIRE_DATASIZE_1BIT mode, only bit 0 of every byte in pTxData will be sent */
    howire->TxXferSize = Size;
    howire->TxXferCount = Size;
    while(howire->TxXferCount > 0U)
    {
      howire->TxXferCount--;
			howire->Instance->DATA = (uint8_t)(*pTxData);
			pTxData += 1U;
			
			/* Set TX */
			howire->Instance->CMD = OWIRE_COMMAND_TX;

			/* Wait for TXDONE flag*/
			if(OWIRE_WaitOnFlagUntilTimeout(howire, OWIRE_FLAG_TXDONE, SET, tickstart, Timeout) != HAL_OK)
			{
				howire->ErrorCode = HAL_OWIRE_ERROR_TX;
				return HAL_TIMEOUT;
			}
			__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_TXDONE);
    }

    howire->gState = HAL_OWIRE_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(howire);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @param  pRxData: Pointer to data buffer
  * @param  Size: Amount of data to be received
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_Receive(OWIRE_HandleTypeDef *howire, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;

  if(howire->gState == HAL_OWIRE_STATE_READY)
  {
    if((pRxData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(howire);

    howire->ErrorCode = HAL_OWIRE_ERROR_NONE;
    howire->gState = HAL_OWIRE_STATE_BUSY_RX;

    /* Init tickstart for timeout managment */
    tickstart = HAL_GetTick();
		
		/* Set Initialization */
		howire->Instance->CMD = OWIRE_COMMAND_INIT;
		
		/* Wait for the initialization done */
		if(OWIRE_WaitOnFlagUntilTimeout(howire, OWIRE_FLAG_INITDONE, SET, tickstart, Timeout) != HAL_OK)
		{
			howire->ErrorCode = HAL_OWIRE_ERROR_INIT;
			return HAL_TIMEOUT;
		}
		__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_INITDONE);
		
		if(__HAL_OWIRE_GET_FLAG(howire, OWIRE_FLAG_ACKERROR))
		{
			__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_ACKERROR);
			howire->ErrorCode = HAL_OWIRE_ERROR_NOACK;
			return HAL_ERROR;
		}
		
    howire->RxXferSize = Size;
    howire->RxXferCount = Size;
    while(howire->RxXferCount > 0U)
    {
			/* Set RX */
			howire->Instance->CMD = OWIRE_COMMAND_RX;
			
			/* Wait for RXDONE flag*/
			if(OWIRE_WaitOnFlagUntilTimeout(howire, OWIRE_FLAG_RXDONE, SET, tickstart, Timeout) != HAL_OK)
			{
				howire->ErrorCode = HAL_OWIRE_ERROR_RX;
				return HAL_TIMEOUT;
			}
			__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_RXDONE);
			
			*pRxData = (uint8_t)howire->Instance->DATA;
			pRxData += 1U;
			howire->RxXferCount--;			
    }

    howire->gState = HAL_OWIRE_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(howire);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Send then receive an amount of data in blocking mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @param  pTxData: Pointer to sent data buffer
  * @param  TxSize: Amount of data to be sent
	* @param  pRxData: Pointer to received data buffer
  * @param  RxSize: Amount of data to be received
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_TransmitReceive(OWIRE_HandleTypeDef *howire, uint8_t *pTxData, uint16_t TxSize, uint8_t *pRxData, uint16_t RxSize, uint32_t Timeout)
{
  uint32_t tickstart = 0U;

  if(howire->gState == HAL_OWIRE_STATE_READY)
  {
    if((pTxData == NULL) || (TxSize == 0U) || (pRxData == NULL) || (RxSize == 0U))
    {
      return  HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(howire);

    howire->ErrorCode = HAL_OWIRE_ERROR_NONE;
    howire->gState = HAL_OWIRE_STATE_BUSY_TX_RX;

    /* Init tickstart for timeout managment */
    tickstart = HAL_GetTick();

		/* Set Initialization */
		howire->Instance->CMD = OWIRE_COMMAND_INIT;
		
		/* Wait for the initialization done */
		if(OWIRE_WaitOnFlagUntilTimeout(howire, OWIRE_FLAG_INITDONE, SET, tickstart, Timeout) != HAL_OK)
		{
			howire->ErrorCode = HAL_OWIRE_ERROR_INIT;
			return HAL_TIMEOUT;
		}
		__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_INITDONE);
		
		if(__HAL_OWIRE_GET_FLAG(howire, OWIRE_FLAG_ACKERROR))
		{
			__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_ACKERROR);
//			howire->ErrorCode = HAL_OWIRE_ERROR_NOACK;
//			return HAL_ERROR;
		}

		/* For both OWIRE_DATASIZE_8BIT mode and OWIRE_DATASIZE_1BIT. But in OWIRE_DATASIZE_1BIT mode, only bit 0 of every byte in pTxData will be sent */
    howire->TxXferSize = TxSize;
    howire->TxXferCount = TxSize;
    while(howire->TxXferCount > 0U)
    {
      howire->TxXferCount--;
			howire->Instance->DATA = (uint8_t)(*pTxData);
			pTxData += 1U;
			
			/* Set TX */
			howire->Instance->CMD = OWIRE_COMMAND_TX;

			/* Wait for TXDONE flag*/
			if(OWIRE_WaitOnFlagUntilTimeout(howire, OWIRE_FLAG_TXDONE, SET, tickstart, Timeout) != HAL_OK)
			{
				howire->ErrorCode = HAL_OWIRE_ERROR_TX;
				return HAL_TIMEOUT;
			}
			__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_TXDONE);
    }

    howire->RxXferSize = RxSize;
    howire->RxXferCount = RxSize;
    while(howire->RxXferCount > 0U)
    {
			/* Set RX */
			howire->Instance->CMD = OWIRE_COMMAND_RX;
			
			/* Wait for RXDONE flag*/
			if(OWIRE_WaitOnFlagUntilTimeout(howire, OWIRE_FLAG_RXDONE, SET, tickstart, Timeout) != HAL_OK)
			{
				howire->ErrorCode = HAL_OWIRE_ERROR_RX;
				return HAL_TIMEOUT;
			}
			__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_RXDONE);
			
			*pRxData = (uint8_t)howire->Instance->DATA;
			pRxData += 1U;
			howire->RxXferCount--;			
    }
		
    howire->gState = HAL_OWIRE_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(howire);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }	
}

/**
  * @brief  Send an amount of data in non-blocking mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @param  pTxData: Pointer to data buffer
  * @param  Size: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_Transmit_IT(OWIRE_HandleTypeDef *howire, uint8_t *pTxData, uint16_t Size)
{
  /* Check that a Tx/Rx process is not already ongoing */
  if(howire->gState == HAL_OWIRE_STATE_READY)
  {
    if((pTxData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }
    /* Process Locked */
    __HAL_LOCK(howire);

    howire->pTxBuffPtr = pTxData;
    howire->TxXferSize = Size;
    howire->TxXferCount = Size;

    howire->ErrorCode = HAL_OWIRE_ERROR_NONE;
    howire->gState = HAL_OWIRE_STATE_BUSY_TX;

    /* Process Unlocked */
    __HAL_UNLOCK(howire);

		/* Enable the OWIRE related interrupts */
	
    __HAL_OWIRE_ENABLE_IT(howire, OWIRE_IT_ACKERROR | OWIRE_IT_INIT | OWIRE_IT_TXDONE);
		
    /* Enable the OWIRE Initialization to start the transmitting process */
		howire->Instance->CMD = OWIRE_COMMAND_INIT;

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Receive an amount of data in non-blocking mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @param  pTxData: Pointer to data buffer
  * @param  Size: Amount of data to be received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_Receive_IT(OWIRE_HandleTypeDef *howire, uint8_t *pRxData, uint16_t Size)
{
  /* Check that a Tx/Rx process is not already ongoing */
  if(howire->gState == HAL_OWIRE_STATE_READY)
  {
    if((pRxData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }
    /* Process Locked */
    __HAL_LOCK(howire);

    howire->pRxBuffPtr = pRxData;
    howire->RxXferSize = Size;
    howire->RxXferCount = Size;

    howire->ErrorCode = HAL_OWIRE_ERROR_NONE;
    howire->gState = HAL_OWIRE_STATE_BUSY_RX;

    /* Process Unlocked */
    __HAL_UNLOCK(howire);

		/* Enable the OWIRE related interrupts */
    __HAL_OWIRE_ENABLE_IT(howire, OWIRE_IT_ACKERROR | OWIRE_IT_INIT | OWIRE_IT_RXDONE); 

    /* Enable the OWIRE Initialization to start the reception process */
		howire->Instance->CMD = OWIRE_COMMAND_INIT; 

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Send then receive an amount of data in non-blocking mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @param  pTxData: Pointer to sent data buffer 
  * @param  TxSize: Amount of data to be sent
  * @param  pRxData: Pointer to received data buffer
  * @param  RxSize: Amount of data to be received
	* @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_TransmitReceive_IT(OWIRE_HandleTypeDef *howire, uint8_t *pTxData, uint16_t TxSize, uint8_t *pRxData, uint16_t RxSize)
{
  /* Check that a Tx/Rx process is not already ongoing */
  if(howire->gState == HAL_OWIRE_STATE_READY)
  {
    if((pTxData == NULL) || (TxSize == 0U) || (pRxData == NULL) || (RxSize == 0U))
    {
      return HAL_ERROR;
    }
    /* Process Locked */
    __HAL_LOCK(howire);

    howire->pTxBuffPtr = pTxData;
    howire->TxXferSize = TxSize;
    howire->TxXferCount = TxSize;

    howire->pRxBuffPtr = pRxData;
    howire->RxXferSize = RxSize;
    howire->RxXferCount = RxSize;
		
    howire->ErrorCode = HAL_OWIRE_ERROR_NONE;
    howire->gState = HAL_OWIRE_STATE_BUSY_TX_RX;

    /* Process Unlocked */
    __HAL_UNLOCK(howire);

		/* Enable the OWIRE related interrupts */
    __HAL_OWIRE_ENABLE_IT(howire, OWIRE_IT_ACKERROR | OWIRE_IT_INIT | OWIRE_IT_TXDONE | OWIRE_IT_RXDONE);
		
    /* Enable the OWIRE Initialization to start the transmitting process */
		howire->Instance->CMD = OWIRE_COMMAND_INIT;

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }	
	
}

/**
  * @brief  This function handles OWIRE interrupt request.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                the configuration information for the specified OWIRE module.
  * @retval None
  */
void HAL_OWIRE_IRQHandler(OWIRE_HandleTypeDef *howire)
{
  uint32_t srflags = READ_REG(howire->Instance->SR);

  /* If error occurs */
	if((srflags & OWIRE_SR_ACKERR_Msk) != RESET)
  {
		__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_SR_ACKERR_Msk);
//		howire->ErrorCode |= HAL_OWIRE_ERROR_NOACK;
//		howire->gState = HAL_OWIRE_STATE_READY;
//		HAL_OWIRE_ErrorCallback(howire);
	}
  /* Initialization done */
  if((srflags & OWIRE_SR_INITDONE_Msk) != RESET)
  {
		__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_INITDONE);
		OWIRE_InitDoneISR(howire);
  }
  /* Tx done */
  if((srflags & OWIRE_SR_TXDONE_Msk) != RESET)
  {
		__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_TXDONE);		
    OWIRE_TxDoneISR(howire);
  }
  /* Rx done */
  if((srflags & OWIRE_SR_RXDONE_Msk) != RESET)
  {
		__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_RXDONE);	
    OWIRE_RxDoneISR(howire);
  }
	
	return;
}

/**
  * @brief  Send Initialization command.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_Command_Init(OWIRE_HandleTypeDef *howire, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
	
	/* Init tickstart for timeout managment */
	tickstart = HAL_GetTick();
	
	/* Set Initialization */
	howire->Instance->CMD = OWIRE_COMMAND_INIT;
	
	/* Wait for the initialization done */
	if(OWIRE_WaitOnFlagUntilTimeout(howire, OWIRE_FLAG_INITDONE, SET, tickstart, Timeout) != HAL_OK)
	{
		return HAL_ERROR;
	}
	__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_INITDONE);

	return HAL_OK;
}

/**
  * @brief  Command to send an amount of data in blocking mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @param  pTxData: Pointer to data buffer
  * @param  Size: Amount of data to be sent
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_Command_Tx(OWIRE_HandleTypeDef *howire, uint8_t *pTxData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
	
	/* Init tickstart for timeout managment */
	tickstart = HAL_GetTick();

	/* For both OWIRE_DATASIZE_8BIT mode and OWIRE_DATASIZE_1BIT. But in OWIRE_DATASIZE_1BIT mode, only bit 0 of every byte in pTxData will be sent */
	while(Size-- > 0U)
	{
		howire->Instance->DATA = (uint8_t)(*pTxData);
		pTxData += 1U;
		
		/* Set TX */
		howire->Instance->CMD = OWIRE_COMMAND_TX;

		/* Wait for TXDONE flag*/
		if(OWIRE_WaitOnFlagUntilTimeout(howire, OWIRE_FLAG_TXDONE, SET, tickstart, Timeout) != HAL_OK)
		{
			return HAL_ERROR;
		}
		__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_TXDONE);
	}

	return HAL_OK;
}

/**
  * @brief  Command to receive an amount of data in blocking mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @param  pRxData: Pointer to data buffer
  * @param  Size: Amount of data to be received
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_Command_Rx(OWIRE_HandleTypeDef *howire, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
	
	/* Init tickstart for timeout managment */
	tickstart = HAL_GetTick();
	
	while(Size-- > 0U)
	{
		/* Set RX */
		howire->Instance->CMD = OWIRE_COMMAND_RX;
		
		/* Wait for RXDONE flag*/
		if(OWIRE_WaitOnFlagUntilTimeout(howire, OWIRE_FLAG_RXDONE, SET, tickstart, Timeout) != HAL_OK)
		{
			return HAL_ERROR;
		}
		__HAL_OWIRE_CLEAR_FLAG(howire, OWIRE_FLAG_RXDONE);
		
		*pRxData = (uint8_t)howire->Instance->DATA;
		pRxData += 1U;	
	}

	return HAL_OK;
}

/**
  * @brief  Start Initialization command in non-blocking mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_Command_Init_IT_Start(OWIRE_HandleTypeDef *howire)
{
	/* Set Initialization */
	howire->Instance->CMD = OWIRE_COMMAND_INIT;
	
	return HAL_OK;
}

/**
  * @brief  Command to start sending an amount of data in blocking mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_Command_Tx_IT_Start(OWIRE_HandleTypeDef *howire)
{	
  if(howire->gState == HAL_OWIRE_STATE_BUSY_TX || howire->gState == HAL_OWIRE_STATE_BUSY_TX_RX)
  {
		if(howire->pTxBuffPtr != NULL && howire->TxXferCount > 0)
		{
			howire->Instance->DATA = (uint8_t)(*howire->pTxBuffPtr);
			howire->pTxBuffPtr++;
			howire->TxXferCount--;
		}
		/* Set Tx */
		howire->Instance->CMD = OWIRE_COMMAND_TX;
    return HAL_OK;		
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Command to start receiving an amount of data in blocking mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OWIRE_Command_Rx_IT_Start(OWIRE_HandleTypeDef *howire)
{
  if(howire->gState == HAL_OWIRE_STATE_BUSY_RX || howire->gState == HAL_OWIRE_STATE_BUSY_TX_RX)
  {
		/* Set Rx */
		howire->Instance->CMD = OWIRE_COMMAND_RX;
    return HAL_OK;		
  }
  else
  {
    return HAL_BUSY;
  }
}


/**
  * @brief  Initialization done callbacks.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                the configuration information for the specified OWIRE module.
  * @retval None
  */
 __weak void HAL_OWIRE_InitDoneCallback(OWIRE_HandleTypeDef *howire)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(howire);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_OWIRE_InitDoneCallback could be implemented in the user file
   */ 
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                the configuration information for the specified OWIRE module.
  * @retval None
  */
 __weak void HAL_OWIRE_TxCpltCallback(OWIRE_HandleTypeDef *howire)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(howire);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_OWIRE_TxCpltCallback could be implemented in the user file
   */ 
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                the configuration information for the specified OWIRE module.
  * @retval None
  */
 __weak void HAL_OWIRE_RxCpltCallback(OWIRE_HandleTypeDef *howire)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(howire);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_OWIRE_RxCpltCallback could be implemented in the user file
   */ 
}

/**
  * @brief  Tx & Rx Transfer completed callbacks.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                the configuration information for the specified OWIRE module.
  * @retval None
  */
 __weak void HAL_OWIRE_TxRxCpltCallback(OWIRE_HandleTypeDef *howire)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(howire);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_OWIRE_TxRxCpltCallback could be implemented in the user file
   */ 
}
/**
  * @brief  Transfer Error callback.
  * @param  howire : OWIRE handle
  * @retval None
  */
__weak void HAL_OWIRE_ErrorCallback(OWIRE_HandleTypeDef *howire)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(howire);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_OWIRE_ErrorCallback could be implemented in the user file
   */
}
/**
  * @}
  */

/** @addtogroup OWIRE_Private_Functions
  * @brief   Private functions
  * @{
  */

/**
  * @brief  INITDONE handler for INITDONE event in Interrupt mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *               the configuration information for OWIRE module.
  * @retval None
  */
static void OWIRE_InitDoneISR(OWIRE_HandleTypeDef *howire)
{
	/* Trigger the transmission or reception */
	if(howire->gState == HAL_OWIRE_STATE_BUSY_TX || howire->gState == HAL_OWIRE_STATE_BUSY_TX_RX)
	{
		HAL_OWIRE_Command_Tx_IT_Start(howire);
	}
	else if(howire->gState == HAL_OWIRE_STATE_BUSY_RX)
	{
		HAL_OWIRE_Command_Rx_IT_Start(howire);
	}
	else
	{
		howire->gState = HAL_OWIRE_STATE_READY;	
		HAL_OWIRE_InitDoneCallback(howire);
	}
	return;
}

/**
  * @brief  TXDONE handler for TXDONE event in Interrupt mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *               the configuration information for OWIRE module.
  * @retval None
  */
static void OWIRE_TxDoneISR(OWIRE_HandleTypeDef *howire)
{
  if(howire->gState == HAL_OWIRE_STATE_BUSY_TX || howire->gState == HAL_OWIRE_STATE_BUSY_TX_RX)
  {
    if(howire->TxXferCount == 0U)
    {
			if(howire->gState == HAL_OWIRE_STATE_BUSY_TX)
			{
				howire->gState = HAL_OWIRE_STATE_READY;	
				HAL_OWIRE_TxCpltCallback(howire);
			}
			else
			{
				HAL_OWIRE_Command_Rx_IT_Start(howire);
			}
    }
		else
		{
			howire->Instance->DATA = (uint8_t)(*howire->pTxBuffPtr);
			howire->pTxBuffPtr++;	
			howire->TxXferCount--;			
			/* Set Tx */
			howire->Instance->CMD = OWIRE_COMMAND_TX;
		}		
  }
	else
	{
		howire->ErrorCode |= HAL_OWIRE_ERROR_TX;
		HAL_OWIRE_ErrorCallback(howire);
	}
	return;
}

/**
  * @brief  RXDONE handler for RXDONE event in Interrupt mode.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *               the configuration information for OWIRE module.
  * @retval None
  */
static void OWIRE_RxDoneISR(OWIRE_HandleTypeDef *howire)
{
  if(howire->gState == HAL_OWIRE_STATE_BUSY_RX || howire->gState == HAL_OWIRE_STATE_BUSY_TX_RX)
  {
    if(howire->RxXferCount == 0U)
    {
			if(howire->gState == HAL_OWIRE_STATE_BUSY_RX)
			{
				howire->gState = HAL_OWIRE_STATE_READY;
				HAL_OWIRE_RxCpltCallback(howire);
			}
			else
			{
				howire->gState = HAL_OWIRE_STATE_READY;
				HAL_OWIRE_TxRxCpltCallback(howire);
			}
    }
		else
		{
			*howire->pRxBuffPtr = howire->Instance->DATA;
			howire->pRxBuffPtr++;	
			howire->RxXferCount--;	
			/* Set Rx */
			howire->Instance->CMD = OWIRE_COMMAND_RX;
		}		
  }
	else
	{
		howire->ErrorCode |= HAL_OWIRE_ERROR_RX;
		HAL_OWIRE_ErrorCallback(howire);
	}
	return;
}

/**
  * @brief  This function handles OWIRE Communication Timeout.
  * @param  howire: pointer to a OWIRE_HandleTypeDef structure that contains
  *                 the configuration information for the specified OWIRE module.
  * @param  Flag: specifies the OWIRE flag to check.
  * @param  Status: The new Flag status (SET or RESET).
  * @param  Tickstart: Tick start value.
  * @param  Timeout: Timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef OWIRE_WaitOnFlagUntilTimeout(OWIRE_HandleTypeDef *howire, uint32_t Flag, FlagStatus Status, uint32_t Tickstart, uint32_t Timeout)
{
  /* Wait until flag is set */	
  while((__HAL_OWIRE_GET_FLAG(howire, Flag) ? SET : RESET) != Status)
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0U)||((HAL_GetTick() - Tickstart ) > Timeout))
      {
        howire->gState = HAL_OWIRE_STATE_READY;

        /* Process Unlocked */
        __HAL_UNLOCK(howire);

        return HAL_TIMEOUT;
      }
    }
  }
  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */ /* End of group OWIRE */


#endif /* HAL_OWIRE_MODULE_ENABLED */

/**
  * @}
  */ /* group CX32L003_HAL_Driver */

