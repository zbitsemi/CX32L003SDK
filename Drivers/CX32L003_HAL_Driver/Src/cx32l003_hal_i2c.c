/**
  ******************************************************************************
  * @file    cx32l003_hal_i2c.c
  * @author  MCU Software Team
  * @Version V1.2.0
  * @Date    2021-01-11
  * @Date    03-Dec-2019
  * @brief   
   @endverbatim
  ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal.h"

#ifdef HAL_I2C_MODULE_ENABLED

/** @addtogroup I2C
  * @brief I2C HAL module driver.
  * @{
  */

/* Private define ------------------------------------------------------------*/
/** @addtogroup I2C_Private_Define
  * @{
  */    
#define I2C_TIMEOUT_FLAG          10U         /*!< Timeout 10 ms             */
#define I2C_TIMEOUT_BUSY_FLAG     20U             /*!< Timeout 20 ms             */

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/
	
	/** @addtogroup I2C_Exported_Functions
  * @{
  */

/**
  * @brief  Initializes the I2C according to the specified parameters in the
  *         I2C_InitTypeDef and creates the associated handle.
  * @param  hi2c : I2C handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c)
{
    uint32_t tmpcon = 0;
	
	if(hi2c == NULL)
		return HAL_ERROR; 
    
    assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));
    assert_param(IS_I2C_SLAVE_MODE(hi2c->Init.slave));
    assert_param(IS_I2C_MASTER_MODE(hi2c->Init.master));
    assert_param(IS_I2C_SPEED_CLOCK(hi2c->Init.speedclock));
    
    if(hi2c->State == HAL_I2C_STATE_RESET)
    {
      /* Allocate lock resource and initialize it */
      hi2c->Lock = HAL_UNLOCKED;
      /* Init the low level hardware : GPIO, CLOCK, NVIC */
      HAL_I2C_MspInit(hi2c);
	  }
	
	 __HAL_I2C_DISABLE(hi2c); 
		
	 tmpcon = HAL_RCC_GetPCLKFreq()/1000;
	 tmpcon = (uint32_t)((tmpcon-((hi2c->Init.speedclock)<<3))/((hi2c->Init.speedclock)<<3));

	if(hi2c->Init.slave != I2C_SLAVE_MODE_DISABLE)
	{
		assert_param(IS_I2C_BROAD_ACK(hi2c->Init.broadack));
      
		SET_BIT(hi2c->Instance->CR,I2C_CR_AA);
		hi2c->Instance->ADDR |= (hi2c->Init.slaveAddr<<I2C_ADDR_I2CADR_Pos);

		if(hi2c->Init.broadack != I2C_BROAD_ACK_DISABLE)
			SET_BIT(hi2c->Instance->ADDR,I2C_ADDR_GC);
		else
			CLEAR_BIT(hi2c->Instance->ADDR,I2C_ADDR_GC);
	}
	else
	{
		CLEAR_BIT(hi2c->Instance->CR,I2C_CR_AA);
	}
  
	if(hi2c->Init.master != I2C_MASTER_MODE_DISABLE)
	{
		hi2c->Instance->BAUDCR = tmpcon&I2C_BAUDCR_TM;
		SET_BIT(hi2c->Instance->TIMRUN,I2C_TIMRUN_TME);
	}
 
	if(hi2c->Init.speedclock < 400)
		CLEAR_BIT(hi2c->Instance->CR,I2C_CR_H1M);
	else
		SET_BIT(hi2c->Instance->CR,I2C_CR_H1M);
  
	__HAL_I2C_ENABLE(hi2c); 
	HAL_I2C_Clear_Interrupt_Flag(hi2c);
    
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->State = HAL_I2C_STATE_READY;  
	hi2c->PreviousState = HAL_I2C_STATE_NONE;
 
	return HAL_OK; 
}



	
/**
  * @brief  Initializes the I2C MSP.
  * @param  hi2c : I2C handle
  * @retval None
  */
__weak void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
  /* Prevent unused argument(s) compilation warning */
	UNUSED(hi2c);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2C_MspInit could be implemented in the user file
   */
}



/**
  * @brief  DeInitializes the I2C peripheral. 
  * @param  hi2c : I2C handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c)
{
  /* Check the I2C handle allocation */
	if(hi2c == NULL)
	{
		return HAL_ERROR;
	}

	hi2c->State = HAL_I2C_STATE_BUSY;	
  
	hi2c->Instance->CR = 0x00;
	/* Disable the I2C */
	__HAL_I2C_DISABLE(hi2c);
		
	/* DeInit the low level hardware: CLOCK, NVIC.*/
	HAL_I2C_MspDeInit(hi2c);
  
	hi2c->ErrorCode     = HAL_I2C_ERROR_NONE;
	hi2c->State         = HAL_I2C_STATE_RESET;
	//  hi2c->PreviousState = I2C_STATE_NONE;
	hi2c->Mode          = HAL_I2C_MODE_NONE;	
	
	/* Release Lock */
	__HAL_UNLOCK(hi2c);
	
	/* Return function status */
	return HAL_OK;	
}
	

/**
  * @brief  DeInitializes the I2C MSP.
  * @param  hi2c : I2C handle
  * @retval None
  */
__weak void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
  /* Prevent unused argument(s) compilation warning */
	UNUSED(hi2c);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2C_MspInit could be implemented in the user file
   */
}

/**
  * @brief  Set i2c start status.
  * @param  hi2c : I2C handle
  * @param  NewState : ENABLE or DISABLE
  * @retval None
  */
void HAL_I2C_Start_Config(I2C_HandleTypeDef *hi2c,FunctionalState NewState)
{
	if (NewState != DISABLE)
		SET_BIT(hi2c->Instance->CR, I2C_CR_STA);
	else
		CLEAR_BIT(hi2c->Instance->CR,I2C_CR_STA); 
}

/**
  * @brief  Set i2c stop status.
  * @param  hi2c : I2C handle
  * @param  NewState : ENABLE or DISABLE
  * @retval None
  */
void HAL_I2C_Stop_Config(I2C_HandleTypeDef *hi2c,FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		SET_BIT(hi2c->Instance->CR, I2C_CR_STO);
		HAL_I2C_Clear_Interrupt_Flag(hi2c);
	}
	else
		CLEAR_BIT(hi2c->Instance->CR,I2C_CR_STO); 
}

/**
  * @brief  Set i2c ACK status.
  * @param  hi2c : I2C handle
  * @param  NewState : ENABLE or DISABLE
  * @retval None
  */
void HAL_I2C_ACK_Config(I2C_HandleTypeDef *hi2c,FunctionalState NewState)
{
	if (NewState != DISABLE)
		SET_BIT(hi2c->Instance->CR, I2C_CR_AA);
	else
		CLEAR_BIT(hi2c->Instance->CR,I2C_CR_AA); 
}

/**
  * @brief  Get i2c Interrupt SI Flag.
  * @param  hi2c : I2C handle
  * @retval FlagStatus (SET or RESET)
  */
FlagStatus HAL_I2C_Get_Interrupt_Flag(I2C_HandleTypeDef *hi2c)
{
	return (__HAL_I2C_GET_INT_SI_FLAG(hi2c)); 
}
/**
  * @brief  Clear i2c Interrupt SI Flag.
  * @param  hi2c : I2C handle
  * @retval None
  */
void HAL_I2C_Clear_Interrupt_Flag(I2C_HandleTypeDef *hi2c)
{
	__HAL_I2C_CLEAR_INT_SI_FLAG(hi2c); 
}
/**
  * @brief  Send Byte Data.
  * @param  hi2c : I2C handle
  * @param  Data : send date  
  * @retval None
  */
void HAL_I2C_Send_Byte(I2C_HandleTypeDef *hi2c, uint8_t Data)
{
	hi2c->Instance->DATA = Data; 
	HAL_I2C_Clear_Interrupt_Flag(hi2c);
}
/**
  * @brief  Receive Byte Data.
  * @param  hi2c : I2C handle
  * @param  pData : reveive date handle
  * @retval None
  */
void HAL_I2C_Receive_Byte(I2C_HandleTypeDef *hi2c, uint8_t *pData)
{
	*pData = hi2c->Instance->DATA; 
}

/**
  * @brief  Transmits the address byte to select the slave device.
  * @param  hi2c: I2C handle
  * @param  Address: specifies the slave address which will be transmitted
  * @param  I2C_Direction: specifies whether the I2C device will be a Transmitter
  *         or a Receiver. 
  *          This parameter can be one of the following values
  *            @arg I2C_Direction_Transmitter: Transmitter mode
  *            @arg I2C_Direction_Receiver: Receiver mode
  * @retval None.
  */
void HAL_I2C_Send_Address(I2C_HandleTypeDef *hi2c, uint8_t Address, uint8_t I2C_Direction)
{
	/* Check the parameters */
	assert_param(IS_I2C_DIRECTION(I2C_Direction));

   /* Test on the direction to set/reset the read/write bit */
	if (I2C_Direction != I2C_Direction_Transmitter)
	{
		/* Set the address bit0 for read */
		Address |= I2C_Direction_Receiver;
	}
	else
	{
		/* Reset the address bit0 for write */
		Address &= (uint8_t)~((uint8_t)I2C_Direction_Receiver);
	}
	/* Send the address */
	hi2c->Instance->DATA = Address;

	HAL_I2C_Start_Config(hi2c,DISABLE);
	HAL_I2C_Clear_Interrupt_Flag(hi2c);
}
/*
 ===============================================================================
                          1. Basic state monitoring                    
 ===============================================================================  
 */

/**
  * @brief  Get the last I2C module  status falg
  * @note   For detailed description of status flag , please refer to section I2C Flag
  *         in cx32l003_hal_i2c.h file.
  *    
  * @retval An I2C Status enumeration value:
  *           - I2C_SUCCESS: Get the i2c module status
  *           - I2C_WAITING: Can't get the i2c module status 
  */
I2CStatus HAL_I2C_Check_Flag(I2C_HandleTypeDef *hi2c, uint32_t *i2c_flag)
{
   I2CStatus status = I2C_WAITING;

	/* Check the parameters */
	assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));
 
	if(HAL_I2C_Get_Interrupt_Flag(hi2c) != RESET)
	{
		/* Read the I2Cx status register */
		*i2c_flag = hi2c->Instance->SR;
		/* I2C_SUCCESS: Get the i2c module status */
		status = I2C_SUCCESS;
		
	}
	/* Return status */
	return status;
}

/**
  * @brief  Checks whether the last I2C module  status flag is get or not in timeout
   
  * @note   For detailed description of Status flag, please refer to section I2C Flag
  *         in cx32l003_hal_i2c.h file.
  *    
  * @retval An ErrorStatus enumeration value:
  *           - SUCCESS: Get the status falg
  *           - ERROR: Can't get the status flag
  */
ErrorStatus HAL_I2C_Wait_Flag(I2C_HandleTypeDef *hi2c, uint32_t *I2C_flag)
{
    uint32_t time_cnt = 0;
    uint32_t tickstart = 0;
    I2CStatus ret = I2C_WAITING;
	
    time_cnt = I2C_TIMEOUT_FLAG;
    
     /* Init tickstart for timeout management ,SysTick time must enable*/
    tickstart = HAL_GetTick();
	
    do
    {
        ret = HAL_I2C_Check_Flag(hi2c, I2C_flag);
      
    }while((time_cnt > (HAL_GetTick()-tickstart)) && (ret == I2C_WAITING));
    
    if(ret == I2C_SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/**
  * @brief  Transmits in master mode an amount of data in blocking mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shift at right before call interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	uint32_t transmit_size = 0;
	uint32_t i2c_flag = 0XFF;
	
	if(hi2c->State == HAL_I2C_STATE_READY)
	{
		hi2c->State     = HAL_I2C_STATE_BUSY_TX;
		hi2c->Mode      = HAL_I2C_MODE_MASTER;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
	    
		HAL_I2C_Start_Config(hi2c, ENABLE);
		HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
		if(i2c_flag != I2C_FLAG_MASTER_TX_START) // 0x00000008U
		{ 
			hi2c->State     = HAL_I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return HAL_ERROR;
		}
		i2c_flag = 0XFF;
		
		HAL_I2C_Send_Address(hi2c,DevAddress,I2C_Direction_Transmitter);
		HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
		if(i2c_flag != I2C_FLAG_MASTER_TX_SLAW_ACK)	// 0x00000018U
		{ 
			hi2c->State     = HAL_I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return HAL_ERROR;
		}
             
		while(transmit_size < Size)
		{
			i2c_flag = 0XFF;
			HAL_I2C_Send_Byte(hi2c,pData[transmit_size]);
			HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
			if(i2c_flag != I2C_FLAG_MASTER_TX_DATA_ACK)	// 0x00000028U
			{ 
				hi2c->State     = HAL_I2C_STATE_ERROR;
				hi2c->ErrorCode = hi2c->PreviousState;
				return HAL_ERROR;
			}
			transmit_size++;
		} 
		HAL_I2C_Stop_Config(hi2c,ENABLE);	// ����
		hi2c->State = HAL_I2C_STATE_READY;
		return HAL_OK;
	}
	else
		return HAL_BUSY;
}

/**
  * @brief  Transmits in master mode an amount of data in blocking mode for restart read(not stop).
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shift at right before call interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_NOStop(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	uint32_t transmit_size = 0;
	uint32_t i2c_flag = 0XFF;
	
	if(hi2c->State == HAL_I2C_STATE_READY)
	{
		hi2c->State     = HAL_I2C_STATE_BUSY_TX;
		hi2c->Mode      = HAL_I2C_MODE_MASTER;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
	    
		HAL_I2C_Start_Config(hi2c, ENABLE);
		HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
		if(i2c_flag != I2C_FLAG_MASTER_TX_START)
		{ 
			hi2c->State     = HAL_I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return HAL_ERROR;
		}
		i2c_flag = 0XFF;
		
		HAL_I2C_Send_Address(hi2c,DevAddress,I2C_Direction_Transmitter);
		HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
		if(i2c_flag != I2C_FLAG_MASTER_TX_SLAW_ACK)
		{ 
			hi2c->State     = HAL_I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return HAL_ERROR;
		}
             
		while(transmit_size < Size)
		{
			i2c_flag = 0XFF;
			HAL_I2C_Send_Byte(hi2c,pData[transmit_size]);
			HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
			if(i2c_flag != I2C_FLAG_MASTER_TX_DATA_ACK)
			{ 
				hi2c->State     = HAL_I2C_STATE_ERROR;
				hi2c->ErrorCode = hi2c->PreviousState;
				return HAL_ERROR;
			}
			transmit_size++;
		} 
		HAL_I2C_Clear_Interrupt_Flag(hi2c);
		hi2c->State = HAL_I2C_STATE_READY;
   	
		return HAL_OK;
	}
	else
		return HAL_BUSY;
}


/**
  * @brief  Receives in master mode an amount of data in blocking mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shift at right before call interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint8_t *tData, uint8_t tSize, uint8_t *rData, uint8_t rSize)
{
	uint32_t receive_size = 0;
	uint32_t transmit_size = 0;
	uint32_t i2c_flag = 0XFF;
    
	if(hi2c->State == HAL_I2C_STATE_READY)
	{
		hi2c->State     = HAL_I2C_STATE_BUSY_RX;
		hi2c->Mode      = HAL_I2C_MODE_MASTER;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
	   
		HAL_I2C_Start_Config(hi2c, ENABLE);
		HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
		if(i2c_flag != I2C_FLAG_MASTER_TX_START) // 0x00000008U
		{ 
			hi2c->State     = HAL_I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return HAL_ERROR;
		}
		i2c_flag = 0XFF;
		
		HAL_I2C_Send_Address(hi2c,DevAddress,I2C_Direction_Transmitter);
		HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
		if(i2c_flag != I2C_FLAG_MASTER_TX_SLAW_ACK)	// 0x00000018U
		{ 
			hi2c->State     = HAL_I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return HAL_ERROR;
		}
             
		while(transmit_size < tSize)
		{
			i2c_flag = 0XFF;
			HAL_I2C_Send_Byte(hi2c,tData[transmit_size]);
			HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
			if(i2c_flag != I2C_FLAG_MASTER_TX_DATA_ACK)	// 0x00000028U
			{ 
				hi2c->State     = HAL_I2C_STATE_ERROR;
				hi2c->ErrorCode = hi2c->PreviousState;
				return HAL_ERROR;
			}
			transmit_size++;
		} 
		
		HAL_I2C_Start_Config(hi2c, ENABLE);
		HAL_I2C_Clear_Interrupt_Flag(hi2c);
		
		HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
    
		if ((i2c_flag != I2C_FLAG_MASTER_RX_START) && (i2c_flag != I2C_FLAG_MASTER_RX_RESTART)) // 0x00000008U&0x00000010U
		{ 
			hi2c->State = HAL_I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return HAL_ERROR;
		}
		i2c_flag = 0XFF;    
		HAL_I2C_Send_Address(hi2c,DevAddress,I2C_Direction_Receiver);
		HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
		if(i2c_flag != I2C_FLAG_MASTER_RX_SLAW_ACK) // 0x00000040U
		{ 
			hi2c->State     = HAL_I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return HAL_ERROR;
		}
        
		while(receive_size < (rSize-1))
		{
			HAL_I2C_ACK_Config(hi2c,ENABLE);
			i2c_flag = 0XFF;
			HAL_I2C_Clear_Interrupt_Flag(hi2c);
			HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
			if(i2c_flag != I2C_FLAG_MASTER_RX_DATA_ACK) // 0x00000050U
			{ 
				hi2c->State     = HAL_I2C_STATE_ERROR;
				hi2c->ErrorCode = hi2c->PreviousState;
				return HAL_ERROR;
			}
			HAL_I2C_Receive_Byte(hi2c,&rData[receive_size]);
			receive_size++;
		}
		if(receive_size == (rSize-1))
		{
			HAL_I2C_ACK_Config(hi2c,DISABLE);
			i2c_flag = 0XFF;
			HAL_I2C_Clear_Interrupt_Flag(hi2c);
			HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
			if(i2c_flag != I2C_FLAG_MASTER_RX_DATA_NOACK) // 0x00000058U 
			{ 
				hi2c->State     = HAL_I2C_STATE_ERROR;
				hi2c->ErrorCode = hi2c->PreviousState;
				return HAL_ERROR;
			}
			HAL_I2C_Receive_Byte(hi2c,&rData[receive_size]);
			receive_size++;
		}			
		HAL_I2C_Stop_Config(hi2c,ENABLE);
		if(hi2c->Init.slave == I2C_SLAVE_MODE_ENABLE)
			HAL_I2C_ACK_Config(hi2c,ENABLE);
        
		hi2c->State = HAL_I2C_STATE_READY;
		
		return HAL_OK;
	}
	else
		return HAL_BUSY;
}



/**
  * @brief  Transmits in slave mode an amount of data in blocking mode. 
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{
	uint32_t transmit_size = 0;
	uint32_t i2c_flag = 0XFF;
  
	if(hi2c->State == HAL_I2C_STATE_READY)
	{
		hi2c->State     = HAL_I2C_STATE_BUSY_TX;
		hi2c->Mode      = HAL_I2C_MODE_SLAVE;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
	    
		while(transmit_size < Size)
		{
			i2c_flag = 0XFF;
			HAL_I2C_ACK_Config(hi2c, ENABLE);
			HAL_I2C_Send_Byte(hi2c,pData[transmit_size]);
			HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
			if (i2c_flag == I2C_FLAG_SLAVE_TX_DATA_ACK) 
			{
				transmit_size++;
			}
			else if((i2c_flag == I2C_FLAG_SLAVE_TX_DATA_NOACK) ||(i2c_flag == I2C_FLAG_SLAVE_TX_DATA_LAST))
			{
				i2c_flag = 0XFF;
				HAL_I2C_ACK_Config(hi2c, DISABLE);
				HAL_I2C_Clear_Interrupt_Flag(hi2c);
				transmit_size++;
				break;
			}
			else
			{ 
				hi2c->State = HAL_I2C_STATE_ERROR;
				hi2c->ErrorCode = hi2c->PreviousState;
				return HAL_ERROR;
			}
		} 
		HAL_I2C_ACK_Config(hi2c, ENABLE);
		hi2c->State = HAL_I2C_STATE_READY;
   
		return HAL_OK;
	}
	else
		return HAL_BUSY;
}


/**
  * @brief  Receive in slave mode an amount of data in blocking mode
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be reveive
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t *Size)
{
	uint32_t i2c_flag = 0XFF;
	uint32_t receive_size = 0;

	if(hi2c->State == HAL_I2C_STATE_READY)
	{	
		hi2c->State     = HAL_I2C_STATE_BUSY_RX;
		hi2c->Mode      = HAL_I2C_MODE_SLAVE;
		hi2c->ErrorCode = HAL_I2C_ERROR_NONE;	
		HAL_I2C_ACK_Config(hi2c, ENABLE);
		HAL_I2C_Clear_Interrupt_Flag(hi2c);
		HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
		while(i2c_flag == I2C_FLAG_SLAVE_RX_SDATA_ACK) 
		{
			pData[receive_size] = hi2c->Instance->DATA;
			i2c_flag = 0XFF;
			HAL_I2C_ACK_Config(hi2c, ENABLE);
			HAL_I2C_Clear_Interrupt_Flag(hi2c);
			HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
			receive_size++;
      
		}
		if(i2c_flag == I2C_FLAG_SLAVE_STOP_RESTART) 
		{
			i2c_flag = 0XFF;
			HAL_I2C_ACK_Config(hi2c, ENABLE);
			HAL_I2C_Clear_Interrupt_Flag(hi2c);
		}
		else
		{ 
			hi2c->State     = HAL_I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return HAL_ERROR;
		}

      /* Last Byte is received */
		hi2c->State = HAL_I2C_STATE_READY;	
	
		/* Process Unlocked */
		__HAL_UNLOCK(hi2c);	
		*Size = receive_size;
	}
	else
	{	
		return HAL_BUSY;
	}
	return HAL_OK;	
}


/**
  * @brief  This function handles I2C  interrupt request.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c)
{
	uint32_t CurrentMode  = hi2c->Mode;
	
	/* Master mode selected */	
	if(CurrentMode == HAL_I2C_MODE_MASTER)	
	{
		HAL_I2C_MasterCallback(hi2c);
	}
	/* Slave mode selected */
	else
	{
		HAL_I2C_SlaveCallback(hi2c);
	}
}
__weak void HAL_I2C_MasterCallback(I2C_HandleTypeDef *hi2c)
{
  /* Prevent unused argument(s) compilation warning */
    UNUSED(hi2c);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2C_MasterCallback could be implemented in the user file
   */

}
__weak void HAL_I2C_SlaveCallback(I2C_HandleTypeDef *hi2c)
{
  /* Prevent unused argument(s) compilation warning */
    UNUSED(hi2c);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2C_SlaveCallback could be implemented in the user file
   */
/*example
   HAL_I2C_Wait_Flag(hi2c, &i2c_flag);
    if(i2c_flag == I2C_FLAG_SLAVE_RX_SLAW_ACK) 
    {
    1.close  i2c interrupt
    2.HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t *Size);
        3. open i2c interrupt
     }
    else  if(i2c_flag == I2C_FLAG_SLAVE_RX_SLAW_ACK) 
    {
    1.close  i2c interrupt
    2.HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
        3. open i2c interrupt
     }
     
  */
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



#endif	/* HAL_I2C_MODULE_ENABLED */


