/**
  ******************************************************************************
  * @file    cx32l003_hal_spi.c
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   SPI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Serial Peripheral Interface (SPI) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
      The SPI HAL driver can be used as follows:

      (#) Declare a SPI_HandleTypeDef handle structure, for example:
          SPI_HandleTypeDef  hspi;

      (#)Initialize the SPI low level resources by implementing the HAL_SPI_MspInit() API:
          (##) Enable the SPIx interface clock
          (##) SPI pins configuration
              (+++) Enable the clock for the SPI GPIOs
              (+++) Configure these SPI pins as alternate function push-pull
          (##) NVIC configuration if you need to use interrupt process
              (+++) Configure the SPIx interrupt priority
              (+++) Enable the NVIC SPI IRQ handle
          
      (#) Program the Mode, Baudrate Prescaler, NSS  management, Clock polarity and phase configuration in the hspi Init structure.

      (#) Initialize the SPI registers by calling the HAL_SPI_Init() API:
          (++) This API configures also the low level Hardware GPIO, CLOCK, CORTEX...etc)
              by calling the customized HAL_SPI_MspInit() API.
     [..]
       Master Receive mode restriction:
      (#) In Master unidirectional bidirectional receive mode (MSTR=1), to ensure that the SPI
          does not initiate a new transfer the following procedure has to be respected:
          (##) HAL_SPI_DeInit()
          (##) HAL_SPI_Init()
      [..]
        Send data
      (#)  When sending data continuously, starting from the second byte of data, 
           the received data must be read before each byte of data is send

  @endverbatim

    Using the HAL it is not possible to reach all supported SPI frequency with the differents SPI Modes,
    the following tables resume the max SPI frequency reached  according to frequency used on APBx Peripheral 
    Clock (fPCLK) used by the SPI instance :
    
  
   +--------------------------------------------------+
   |         |                | 2Lines Fullduplex     | 
   | Process | Tranfert mode  |-----------------------|
   |         |                |  Master   |  Slave    |
   |=========|================|===========|===========|
   |         |     Polling    |  fPCLK/2  | fPCLK/4   | 
   |         |----------------|-----------|-----------|
   |    R    |     Interrupt  |  fPCLK/2  | fPCLK/4  |
   |    X    |----------------|-----------|-----------|
   |=========|================|===========|===========|
   |         |     Polling    |  fPCLK/2  |  fPCLK/4  |   
   |         |----------------|-----------|-----------|
   |    T    |     Interrupt  |  fPCLK/2  | fPCLK/4 |  
   |    X    |----------------|-----------|-----------|
   +---------------------------------------------------+

   
     [..]
       (+@) RX processes are HAL_SPI_Receive_Data()
       (+@) TX processes are HAL_SPI_Send_Data()
  ******************************************************************************
 **/ 

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */


/** @defgroup SPI SPI
  * @brief SPI HAL module driver
  * @{
  */
	
#ifdef HAL_SPI_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define SPI_WAIT_TIMEOUT       1024    /*1s*/  
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup SPI_Exported_Functions SPI Exported Functions
  * @{
  */

/** @defgroup SPI_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          de-initialize the SPIx peripheral:

      (+) User must implement HAL_SPI_MspInit() function in which he configures
          all related peripherals resources (CLOCK, GPIO, IT and NVIC ).

      (+) Call the function HAL_SPI_Init() to configure the selected device with
          the selected configuration:
        (++) Mode
        (++) Clock Polarity and Phase
        (++) NSS Management
        (++) BaudRate Prescaler
      (+) Call the function HAL_SPI_DeInit() to restore the default configuration
          of the selected SPIx peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the SPI according to the specified parameters
  *         in the SPI_InitTypeDef and initialize the associated handle.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
{
  /* Check the SPI handle allocation */
  if(hspi == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_SPI_INSTANCE(hspi->Instance));
  assert_param(IS_SPI_MODE(hspi->Init.Mode));
  assert_param(IS_SPI_CPOL(hspi->Init.CLKPolarity));
  assert_param(IS_SPI_CPHA(hspi->Init.CLKPhase));
  assert_param(IS_SPI_NSS(hspi->Init.NSS));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(hspi->Init.BaudRatePrescaler));

  if(hspi->State == HAL_SPI_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hspi->Lock = HAL_UNLOCKED;
    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    HAL_SPI_MspInit(hspi);
  }

  hspi->State = HAL_SPI_STATE_BUSY;
  /* Disable the selected SPI peripheral */
  __HAL_SPI_DISABLE(hspi);
  /*----------------------- SPIx CR & SSN Configuration ---------------------*/
  /* Configure : SPI Mode, Clock polarity and phase, NSS management,Communication speed */
  WRITE_REG(hspi->Instance->CR, (hspi->Init.Mode | hspi->Init.CLKPolarity | hspi->Init.CLKPhase | hspi->Init.BaudRatePrescaler ) );
  /* Configure : NSS management */
  WRITE_REG(hspi->Instance->SSN, (hspi->Init.NSS));
 /* Enable the selected SPI peripheral */
  __HAL_SPI_ENABLE(hspi);

  hspi->State = HAL_SPI_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  De Initialize the SPI peripheral.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi)
{
  /* Check the SPI handle allocation */
  if(hspi == NULL)
  {
    return HAL_ERROR;
  }
  /* Check SPI Instance parameter */
  assert_param(IS_SPI_INSTANCE(hspi->Instance));

  hspi->State = HAL_SPI_STATE_BUSY;
  /* Disable the SPI Peripheral Clock */
  __HAL_SPI_DISABLE(hspi);
  /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
  HAL_SPI_MspDeInit(hspi);

  hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  hspi->State = HAL_SPI_STATE_RESET;
  /* Release Lock */
  __HAL_UNLOCK(hspi);

  return HAL_OK;
}

/**
  * @brief  Initialize the SPI MSP.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_MspInit should be implemented in the user file
  */
}

/**
  * @brief  De-Initialize the SPI MSP.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_MspDeInit should be implemented in the user file
  */
}

/**
  * @}
  */

/** @defgroup SPI_Exported_Functions_Group2 IO operation functions
 *  @brief   Data transfers functions
 *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
 ===============================================================================
 [..]
    This subsection provides a set of functions allowing to manage the SPI
    data transfers.

    [..] The SPI supports master and slave mode :

    (#) APIs provided for these 2 transfer modes (send data or receive data )
         2Lines (full duplex) modes.

@endverbatim
  * @{
  */


/**
  * @brief  Master Receive one data .Receive one data must send one data
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pRxData: pointer to data buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Master_Receive_Data(SPI_HandleTypeDef *hspi, uint8_t *pRxData)
{
    if(pRxData == NULL )
    {
      return HAL_ERROR;
    }
     /* Process Locked */
    __HAL_LOCK(hspi);
  
    if ((hspi->State) == HAL_SPI_STATE_READY)
    {
      hspi->State = HAL_SPI_STATE_BUSY_RX;
    }
    else
    {
      hspi->State = HAL_SPI_STATE_READY;
      __HAL_UNLOCK(hspi);
      return HAL_BUSY;
    }
    
    if(HAL_SPI_Get_SPIIF(hspi) != RESET)
        *pRxData = hspi->Instance->DATA;
    else
    {
  hspi->State = HAL_SPI_STATE_READY;
  __HAL_UNLOCK(hspi);
      return HAL_ERROR;
    }
    
    hspi->State = HAL_SPI_STATE_READY;
    __HAL_UNLOCK(hspi);
		
		return HAL_OK;
}

/**
  * @brief  Master Send one data .
  * @note        When sending data continuously, starting from the second byte of data, 
  *          the received data must be read before each byte of data is send
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData: pointer to transmission data buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Master_Send_Data(SPI_HandleTypeDef *hspi, uint8_t TxData)
{
    /* Variable used to alternate  Tx during transfer */
    uint32_t time_start = 0;
  
    /* Process Locked */
    __HAL_LOCK(hspi);
    /* Don't overwrite in case of HAL_SPI_STATE_BUSY_TX */
    if ((hspi->State) == HAL_SPI_STATE_READY)
    {
      hspi->State = HAL_SPI_STATE_BUSY_TX;
    }
    else
    {
      hspi->State = HAL_SPI_STATE_READY;
      __HAL_UNLOCK(hspi);
      return HAL_BUSY;
		}
		hspi->Instance->DATA = TxData;

    time_start = HAL_GetTick();
		while(HAL_SPI_Get_SPIIF(hspi) != SET)
    {  
      if ((HAL_GetTick()-time_start) > SPI_WAIT_TIMEOUT)
      {
       hspi->State = HAL_SPI_STATE_READY;
       __HAL_UNLOCK(hspi);
        return HAL_TIMEOUT;
      }
    }

		hspi->State = HAL_SPI_STATE_READY;
    __HAL_UNLOCK(hspi);
		
		return HAL_OK;
}
/**
  * @brief  Transmit and Receive an amount of data in blocking mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData pointer to transmission data buffer
  * @param  pRxData pointer to reception data buffer
  * @param  TxSize amount of data to be sent
  * @param  RxSize amount of data to be received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Master_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t TxSize,uint8_t *pRxData, uint16_t RxSize)
{
	uint16_t count = 0;
	uint8_t data = 0;
	HAL_SPI_Set_NSS(hspi,SPI_NSS_MODE_LOW);
	
	for(count = 0;count < TxSize; count++)
	{
		HAL_SPI_Master_Send_Data(hspi, pTxData[count]);
		HAL_SPI_Master_Receive_Data(hspi, &data);
	}

	data = 0;
	for(count = 0;count < RxSize; count++)
	{
		HAL_SPI_Master_Send_Data(hspi, data);
		HAL_SPI_Master_Receive_Data(hspi, &pRxData[count]);
	}
	
	HAL_SPI_Set_NSS(hspi,SPI_NSS_MODE_HIGH);
	
	return HAL_OK;
}


/**
  * @brief  Transmit and Receive an amount of data in blocking mode in low level.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData pointer to transmission data buffer
  * @param  pRxData pointer to reception data buffer
  * @param  TxSize amount of data to be sent
  * @param  RxSize amount of data to be received
  * @retval HAL status
  */
void LL_SPI_Master_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t TxSize,uint8_t *pRxData, uint16_t RxSize)
{
	uint16_t count = 0;
	uint8_t data = 0;
	
	hspi->Instance->SSN = SPI_NSS_MODE_LOW;
	
	for(count = 0;count < TxSize; count++)
	{
		hspi->Instance->DATA = pTxData[count];
		while((hspi->Instance->SR&SPI_FLAG_SPIF)!=SPI_FLAG_SPIF)
			;
		data = hspi->Instance->DATA;		
	}
	
	 data = 0;
	for(count = 0;count < RxSize; count++)
	{
		hspi->Instance->DATA = data;
		while((hspi->Instance->SR&SPI_FLAG_SPIF)!=SPI_FLAG_SPIF)
			;
		pRxData[count] = hspi->Instance->DATA;
	}
	hspi->Instance->SSN = SPI_NSS_MODE_HIGH;
	
}
/**
  * @brief  Slave Receive one data .
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pRxData: pointer to data buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Slave_Receive_Data(SPI_HandleTypeDef *hspi, uint8_t *pRxData)
{
  uint32_t time_start = 0;

  if(pRxData == NULL )
  {
    return HAL_ERROR;
  }
      
   /* Process Locked */
   __HAL_LOCK(hspi);
    
  if ((hspi->State) == HAL_SPI_STATE_READY)
  {
    hspi->State = HAL_SPI_STATE_BUSY_RX;
  }
  else
  {
		hspi->State = HAL_SPI_STATE_READY;
    __HAL_UNLOCK(hspi);
    return HAL_BUSY;
  }
  time_start = HAL_GetTick();  
  while(HAL_SPI_Get_SPIIF(hspi) != SET)  
  {  
    if ((HAL_GetTick()-time_start) > SPI_WAIT_TIMEOUT)
    {
      hspi->State = HAL_SPI_STATE_READY;
      __HAL_UNLOCK(hspi);
      return HAL_TIMEOUT;
     }
    }
    
  *pRxData = hspi->Instance->DATA;
    
  hspi->State = HAL_SPI_STATE_READY;
  __HAL_UNLOCK(hspi);
  
  return HAL_OK;
}

/**
  * @brief  Slave Send one data .
  * @note    before sending data, the last received data must be read 
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData: pointer to transmission data buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Slave_Send_Data(SPI_HandleTypeDef *hspi, uint8_t TxData)
{
    /* Process Locked */
    __HAL_LOCK(hspi);
    /* Don't overwrite in case of HAL_SPI_STATE_BUSY_TX */
    if ((hspi->State) == HAL_SPI_STATE_READY)
    {
      hspi->State = HAL_SPI_STATE_BUSY_TX;
    }
    else
    {
			hspi->State = HAL_SPI_STATE_READY;
			__HAL_UNLOCK(hspi);
			return HAL_BUSY;
    }
    if(HAL_SPI_Get_SPIIF(hspi) != SET)
        hspi->Instance->DATA = TxData;
		else
    {
			hspi->State = HAL_SPI_STATE_READY;
			__HAL_UNLOCK(hspi);
			return HAL_ERROR;
    }
  
  hspi->State = HAL_SPI_STATE_READY;
  __HAL_UNLOCK(hspi);
		return HAL_OK;
  
}

/**
  * @brief  Set NSS HIGH OR LOW.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval HAL status
*/
HAL_StatusTypeDef HAL_SPI_Set_NSS(SPI_HandleTypeDef *hspi, uint32_t NSS_Status)
{
    assert_param(IS_SPI_NSS(NSS_Status));
    hspi->Instance->SSN =  NSS_Status;
	hspi->Init.NSS = NSS_Status; 
    
    return HAL_OK;
}

/**
  * @brief  Checks the SPIF FlagStatus
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval FlagStatus (SET or RESET).  
*/
FlagStatus HAL_SPI_Get_SPIIF(SPI_HandleTypeDef *hspi)
{
    if(__HAL_SPI_GET_FLAG(hspi,SPI_FLAG_SPIF))
        return SET;
    else
        return RESET;
        
}
/**
  * @brief  Checks the all flags in SPI_SR.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval the register value
*/
uint32_t  HAL_SPI_Get_ErrorFlags(SPI_HandleTypeDef *hspi)
{
    return (hspi->Instance->SR);
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_SPI_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */


