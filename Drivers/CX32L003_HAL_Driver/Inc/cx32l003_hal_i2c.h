/**
  ******************************************************************************
  * @file    cx32l003_hal_i2c.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of I2C HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/	
#ifndef __CX32L003_HAL_I2C_H	
#define __CX32L003_HAL_I2C_H	
	
/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/******************************************************************************/
/* Exported types ------------------------------------------------------------*/
/******************************************************************************/

/** @defgroup I2C_Exported_Types I2C Exported Types
  * @{
  */


/**
  * @brief  HAL State structure definition
  *
  */
typedef enum
{
  HAL_I2C_STATE_RESET             = 0x00U,   /*!< Peripheral is not yet Initialized         */	
	HAL_I2C_STATE_NONE ,                       /*!< I2C not do anything        								*/	
   HAL_I2C_STATE_READY,                      /*!< Peripheral Initialized and ready for use  */
  HAL_I2C_STATE_BUSY,                       /*!< An internal process is ongoing            */
  HAL_I2C_STATE_BUSY_TX,                     /*!< Data Transmission process is ongoing      */
  HAL_I2C_STATE_BUSY_RX,                    /*!< Data Reception process is ongoing         */
  HAL_I2C_STATE_ABORT,                     /*!< Abort user request ongoing                */
  HAL_I2C_STATE_TIMEOUT,                   /*!< Timeout state                             */
  HAL_I2C_STATE_ERROR                     /*!< Error                                     */

}HAL_I2C_StateTypeDef;


/** 
  * @brief  I2C Initial Configuration Structure definition  
  */
typedef struct 
{
	uint32_t master;						/*!< master mode enable/disable.
															This parameter can be a value of @ref I2C_Master_Mode */
	
	uint32_t slave; 						/*!< slave mode enable/disable.
															This parameter can be a value of @ref I2C_Slave_Mode */
	
	uint32_t slaveAddr;						/*!< slave address */
	
  uint32_t speedclock;				    /*!< i2c speed clock set, speed=Pclk/(8*(baudcr+1)),uint khz*/
	
	uint32_t broadack;						/*!<ack enable or disable when as slave.
															This parameter can be a value of @ref I2C BROAD */
	
}I2C_InitTypeDef; 


/**
  * @brief  HAL Mode structure definition
 */
typedef enum
{
  HAL_I2C_MODE_NONE               = 0x00U,   /*!< No I2C communication on going             */
  HAL_I2C_MODE_MASTER             = 0x10U,   /*!< I2C communication is in Master Mode       */
  HAL_I2C_MODE_SLAVE              = 0x20U,   /*!< I2C communication is in Slave Mode        */
}HAL_I2C_ModeTypeDef;

/**
  * @brief  I2CStatus enum definition
 */

typedef enum 
{
  I2C_ERROR = 0,                        /*!<No i2c status flag      */
  I2C_SUCCESS = 1,                      /*!<Waited i2c status flag  */
  I2C_WAITING = 2                       /*!<Waiting i2c status flag  */
} I2CStatus;


/** 
  * @brief  I2C handle Structure definition  
  */ 
typedef struct 
{
	I2C_TypeDef *Instance;
	
	I2C_InitTypeDef Init;
                                            
  __IO uint32_t              PreviousState;  /*!< I2C communication Previous state and mode
                                                  context for internal usage               */

  HAL_LockTypeDef            Lock;           /*!< I2C locking object                       */

  __IO HAL_I2C_StateTypeDef  State;          /*!< I2C communication state                  */
                                             
  __IO HAL_I2C_ModeTypeDef   Mode;           /*!< I2C communication mode                   */
                                             
  __IO uint32_t              ErrorCode;      /*!< I2C Error code                           */

 }I2C_HandleTypeDef;


/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup I2C_Exported_Constants I2C Exported Constants
  * @{
  */


/** @defgroup I2C_Error_Code I2C Error Code
  * @brief    I2C Error Code 
  * @{
  */ 
#define HAL_I2C_ERROR_NONE       0x00000000U    /*!< No error           */
#define HAL_I2C_ERROR_TIMEOUT    0x00000020U    /*!< Timeout Error      */
/**
  * @}
  */


/** @defgroup I2C_Master_Mode I2C master mode enable/disable
  * @{
  */
#define I2C_MASTER_MODE_DISABLE        		((uint32_t)0x00000000U)
#define I2C_MASTER_MODE_ENABLE         		((uint32_t)0x00000001U)

/**
  * @}
  */


/** @defgroup I2C_Slave_Mode I2C slave mode enable/disable
  * @{
  */
#define I2C_SLAVE_MODE_ENABLE         		((uint32_t)0x00000000U)
#define I2C_SLAVE_MODE_DISABLE        		((uint32_t)0x00000001U)

/**
  * @}
  */
  
/** @defgroup I2C_BROAD  I2C broad ack enable/disable
  * @{
  */
#define I2C_BROAD_ACK_ENABLE         		((uint32_t)0x00000000U)
#define I2C_BROAD_ACK_DISABLE        		((uint32_t)0x00000001U)
/**
  * @}
  */
  
/** @defgroup I2C_HIGH_RATE  I2C high rate enable/disable
  * @{
  */
#define I2C_HIGH_RATE_ENABLE         		((uint32_t)0x00000000U)
#define I2C_HIGH_RATE_DISABLE        		I2C_CR_H1M

/**
  * @}
  */

/** @defgroup I2C_Flag_definition I2C Flag definition
  * @{
  */
#define I2C_FLAG_ERROR_UNDER                 ((uint32_t)0x00000000U)
#define I2C_FLAG_USELESS                     ((uint32_t)0x000000F8U)

#define I2C_FLAG_MASTER_TX_START             ((uint32_t)0x00000008U)
#define I2C_FLAG_MASTER_TX_RESTART           ((uint32_t)0x00000010U)
#define I2C_FLAG_MASTER_TX_SLAW_ACK          ((uint32_t)0x00000018U)
#define I2C_FLAG_MASTER_TX_SLAW_NOACK        ((uint32_t)0x00000020U)
#define I2C_FLAG_MASTER_TX_DATA_ACK          ((uint32_t)0x00000028U)
#define I2C_FLAG_MASTER_TX_DATA_NOACK        ((uint32_t)0x00000030U)
#define I2C_FLAG_MASTER_TX_LOST_SCL          ((uint32_t)0x00000038U)


#define I2C_FLAG_MASTER_RX_START             ((uint32_t)0x00000008U)
#define I2C_FLAG_MASTER_RX_RESTART           ((uint32_t)0x00000010U)
#define I2C_FLAG_MASTER_RX_SLAW_ACK          ((uint32_t)0x00000040U)
#define I2C_FLAG_MASTER_RX_SLAW_NOACK        ((uint32_t)0x00000048U)
#define I2C_FLAG_MASTER_RX_DATA_ACK          ((uint32_t)0x00000050U)
#define I2C_FLAG_MASTER_RX_DATA_NOACK        ((uint32_t)0x00000058U)
#define I2C_FLAG_MASTER_RX_LOST_SCL          ((uint32_t)0x00000038U)


#define I2C_FLAG_SLAVE_TX_SLAW_ACK          ((uint32_t)0x000000A8U)
#define I2C_FLAG_SLAVE_TX_DATA_ACK          ((uint32_t)0x000000B8U)
#define I2C_FLAG_SLAVE_TX_DATA_NOACK        ((uint32_t)0x000000C0U)
#define I2C_FLAG_SLAVE_TX_DATA_LAST            ((uint32_t)0x000000C8U)
#define I2C_FLAG_SLAVE_TX_LOST_SCL          ((uint32_t)0x000000B0U)

#define I2C_FLAG_SLAVE_RX_SLAW_ACK          ((uint32_t)0x00000060U)
#define I2C_FLAG_SLAVE_RX_BROAD_ACK         ((uint32_t)0x00000070U)
#define I2C_FLAG_SLAVE_RX_SDATA_ACK         ((uint32_t)0x00000080U)
#define I2C_FLAG_SLAVE_RX_SDATA_NOACK       ((uint32_t)0x00000088U)
#define I2C_FLAG_SLAVE_RX_BDATA_ACK         ((uint32_t)0x00000090U)
#define I2C_FLAG_SLAVE_RX_BDATA_NOACK       ((uint32_t)0x00000098U)
#define I2C_FLAG_SLAVE_RX_SA_LOST_SCL       ((uint32_t)0x00000068U)
#define I2C_FLAG_SLAVE_RX_BA_LOST_SCL       ((uint32_t)0x00000078U)
#define I2C_FLAG_SLAVE_STOP_RESTART         ((uint32_t)0x000000A0U)



/**
  * @}
  */

/**
  * @}
  */
  
 /** @defgroup I2C_transfer_direction I2C transfer direction selection
  * @{
  */

#define  I2C_Direction_Transmitter      ((uint8_t)0x00)
#define  I2C_Direction_Receiver         ((uint8_t)0x01)
#define IS_I2C_DIRECTION(DIRECTION) (((DIRECTION) == I2C_Direction_Transmitter) || \
                                     ((DIRECTION) == I2C_Direction_Receiver))
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/** @defgroup I2C_Exported_Macros I2C Exported Macros
  * @{
  */
	
/**
  * @brief  Enable/Disable the I2C peripheral.
  * @param  __HANDLE__: I2C handle
  * @retval None
  */
#define __HAL_I2C_ENABLE(__HANDLE__)   		(SET_BIT((__HANDLE__)->Instance->CR, I2C_CR_ENS))
#define __HAL_I2C_DISABLE(__HANDLE__)  		(CLEAR_BIT((__HANDLE__)->Instance->CR, I2C_CR_ENS))


/** @brief  Check whether the I2C interrupt SI is enabled or not.
  * @param  __HANDLE__ specifies the I2C Handle.
  * @retval The new state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_I2C_GET_INT_SI_FLAG(__HANDLE__)      	((((__HANDLE__)->Instance->CR & (I2C_CR_SI)) == (I2C_CR_SI)) ? SET : RESET)

/** @brief  Clear the I2C interrupt set flags which are cleared by write 0 to specific bit.
  * @param  __HANDLE__ specifies the I2C Handle.
  * @retval None
  */
#define __HAL_I2C_CLEAR_INT_SI_FLAG(__HANDLE__) 			CLEAR_BIT((__HANDLE__)->Instance->CR,I2C_CR_SI)

 
/** @brief  CHECK the parameter used init
  * @param  
  * @retval None
  */

#define IS_I2C_ALL_INSTANCE(INSTANCE)   ((INSTANCE) == I2C)
#define IS_I2C_SLAVE_MODE(MODE)        (((MODE) == I2C_SLAVE_MODE_ENABLE) || ((MODE) == I2C_SLAVE_MODE_DISABLE)) 
#define IS_I2C_MASTER_MODE(MODE)       (((MODE) == I2C_MASTER_MODE_ENABLE) || ((MODE) == I2C_MASTER_MODE_DISABLE)) 
#define IS_I2C_BROAD_ACK(ACK)          (((ACK) == I2C_BROAD_ACK_ENABLE) || ((ACK) == I2C_BROAD_ACK_DISABLE))
#define IS_I2C_SPEED_CLOCK(CLOCK)          ((CLOCK) < 1000 ) 
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/**
  * @{
  */

/* Initialization/de-initialization functions  ********************************/
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c);


/* MSP functions  *************************************************************/
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);

void HAL_I2C_Start_Config(I2C_HandleTypeDef *hi2c,FunctionalState NewState);
void HAL_I2C_Stop_Config(I2C_HandleTypeDef *hi2c,FunctionalState NewState);
void HAL_I2C_ACK_Config(I2C_HandleTypeDef *hi2c,FunctionalState NewState);
FlagStatus HAL_I2C_Get_Interrupt_Flag(I2C_HandleTypeDef *hi2c);
void HAL_I2C_Clear_Interrupt_Flag(I2C_HandleTypeDef *hi2c);
void HAL_I2C_Send_Byte(I2C_HandleTypeDef *hi2c, uint8_t Data);
void HAL_I2C_Receive_Byte(I2C_HandleTypeDef *hi2c, uint8_t *pData);
void HAL_I2C_Send_Address(I2C_HandleTypeDef *hi2c, uint8_t Address, uint8_t I2C_Direction);
I2CStatus HAL_I2C_Check_Flag(I2C_HandleTypeDef *hi2c, uint32_t *I2C_flag);
ErrorStatus HAL_I2C_Wait_Flag(I2C_HandleTypeDef *hi2c, uint32_t *I2C_flag);
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Transmit_NOStop(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint8_t *tData, uint8_t tSize, uint8_t *rData, uint8_t rSize);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t *Size);

void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c);
__weak void HAL_I2C_MasterCallback(I2C_HandleTypeDef *hi2c);
__weak void HAL_I2C_SlaveCallback(I2C_HandleTypeDef *hi2c);

/**
  * @}
  */

#endif
