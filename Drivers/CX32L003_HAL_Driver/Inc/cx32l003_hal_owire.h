/**
  ******************************************************************************
  * @file    cx32l003_hal_owire.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of OWIRE HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_OWIRE_H
#define __CX32L003_HAL_OWIRE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @addtogroup OWIRE
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup OWIRE_Exported_Types OWIRE Exported Types
  * @{
  */

/**
  * @brief OWIRE Init Structure definition
  */
typedef struct
{
  uint32_t ClockDiv;							/*!< Specifies the prescaler value which will be
                                    used to configure the counter clock.
                                    This parameter can be a value of @ref OWIRE_Clock_Divider */

  uint32_t FirstBit;							/*!< Specifies whether data transfers start from MSB or LSB bit.
                                    This parameter can be a value of @ref OWIRE_MSB_LSB_Transmission */

  uint32_t DataSize;           		/*!< Specifies the OWIRE data size.
                                    This parameter can be a value of @ref OWIRE_Data_Size */	
	
  uint32_t ReadMode;           		/*!< Specifies if the time of reading 0 is the same as writing 0.
                                    This parameter can be a value of @ref OWIRE_Read_Mode */	
	
  uint32_t NoiseFilterEn;			  	/*!< Specifies whether the filter is enabled.
                                    This parameter can be a value of @ref OWIRE_Noise_Filter_Enable */	
	
  uint32_t NoiseFilterClk;		  	/*!< Specifies the clock source of the noise filter.
                                    This parameter can be a value of @ref OWIRE_Noise_Filter_Clock */	

  uint32_t ResetCounter;  				/*!< Specifies the Reset Counter(us) which will be
                                    used to configure the time slot of reset. */
	
  uint32_t PresencePulseCounter;	/*!< Specifies the Presence Pulse Counter(us) which will be
                                    used to configure the time slot of presense pulse. */

  uint32_t BitRateCounter;  			/*!< Specifies the Bit Rate Counter(us) which will be
                                    used to configure the bit rate. */

  uint32_t DriveCounter;	  			/*!< Specifies the Drive Counter(us) which will be
                                    used to configure the time slot of driving. */

  uint32_t ReadSamplingCounter;		/*!< Specifies the Read Sampling Counter(us) which will be
                                    used to configure the time slot of read sampling. */

  uint32_t RecoverCounter;	 			/*!< Specifies the Recover Counter(us) which will be
                                    used to configure the time slot of recovering. */

}OWIRE_InitTypeDef;

/** 
  * @brief HAL OWIRE State structures definition
  */
typedef enum
{
  HAL_OWIRE_STATE_RESET             = 0x00U,    /*!< Peripheral is not yet Initialized 
                                                   Value is allowed for gState */
  HAL_OWIRE_STATE_READY             = 0x20U,    /*!< Peripheral Initialized and ready for use */
		
  HAL_OWIRE_STATE_BUSY_INIT         = 0x21U,    /*!< Initialization process is ongoing */
	
	HAL_OWIRE_STATE_BUSY_TX           = 0x22U,    /*!< Data Transmission process is ongoing */
	
  HAL_OWIRE_STATE_BUSY_RX           = 0x24U,    /*!< Data Reception process is ongoing */

  HAL_OWIRE_STATE_BUSY_TX_RX        = 0x28U,    /*!< Data Transmission & Reception process is ongoing */

  HAL_OWIRE_STATE_BUSY              = 0x2AU,    /*!< an internal process is ongoing */
	
  HAL_OWIRE_STATE_TIMEOUT           = 0xA0U,    /*!< Timeout state */
	
  HAL_OWIRE_STATE_ERROR             = 0xE0U     /*!< Error */	
}HAL_OWIRE_StateTypeDef;

/** 
  * @brief  OWIRE handle Structure definition
  */
typedef struct
{
  OWIRE_TypeDef                 *Instance;         	/*!< OWIRE registers base address        */

  OWIRE_InitTypeDef              Init;             	/*!< OWIRE communication parameters      */

  uint8_t                       *pTxBuffPtr;      	/*!< Pointer to OWIRE Tx transfer Buffer */

  uint16_t                      TxXferSize;       	/*!< OWIRE Tx Transfer size              */

  __IO uint16_t                 TxXferCount;      	/*!< OWIRE Tx Transfer Counter           */

  uint8_t                       *pRxBuffPtr;      	/*!< Pointer to OWIRE Rx transfer Buffer */

  uint16_t                      RxXferSize;       	/*!< OWIRE Rx Transfer size              */

  __IO uint16_t                 RxXferCount;      	/*!< OWIRE Rx Transfer Counter           */

  HAL_LockTypeDef               Lock;             	/*!< Locking object                      */

  __IO HAL_OWIRE_StateTypeDef    gState;          	/*!< OWIRE state information related to global Handle management 
                                                       and also related to Tx operations.
                                                       This parameter can be a value of @ref HAL_OWIRE_StateTypeDef */

  __IO uint32_t                 ErrorCode;     			/*!< OWIRE Error code                    */
}OWIRE_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup OWIRE_Exported_Constants One-Wire Exported constants
  * @{
  */

/** @defgroup OWIRE_Data_Size One-Wire Data Size
  * @{
  */
#define OWIRE_DATASIZE_1BIT               0x00000000U
#define OWIRE_DATASIZE_8BIT               OWIRE_CR_SIZE_Msk
/**
  * @}
  */

/** @defgroup OWIRE_MSB_LSB_Transmission One-Wire MSB LSB Transmission
  * @{
  */
#define OWIRE_FIRSTBIT_LSB                0x00000000U
#define OWIRE_FIRSTBIT_MSB                OWIRE_CR_MSBFIRST_Msk
/**
  * @}
  */

/** @defgroup OWIRE_Clock_Divider One-Wire Clock Divider
  * @{
  */
#define OWIRE_CLOCK_DIVIDER_1         		0x00000000U
#define OWIRE_CLOCK_DIVIDER_2         		(0x1U << OWIRE_CR_CLKDIV_Pos)
#define OWIRE_CLOCK_DIVIDER_4         		(0x2U << OWIRE_CR_CLKDIV_Pos)
#define OWIRE_CLOCK_DIVIDER_16        		(0x3U << OWIRE_CR_CLKDIV_Pos)
/**
  * @}
  */

/** @defgroup OWIRE_READ_MODE One-Wire Read Mode
  * @{
  */
#define OWIRE_RDMODE_0                		0x00000000U
#define OWIRE_RDMODE_1                		OWIRE_CR_RDMODE_Msk
/**
  * @}
  */
	
/** @defgroup OWIRE_NOISE_FILTER_CLOCK One-Wire Noise Filter Clock Divider
  * @{
  */
#define OWIRE_NOISE_FILTER_CLK_DIV_1			0x00000000U
#define OWIRE_NOISE_FILTER_CLK_DIV_2			(0x1U << OWIRE_NFCR_NFDIV_Pos)
#define OWIRE_NOISE_FILTER_CLK_DIV_4			(0x2U << OWIRE_NFCR_NFDIV_Pos)
#define OWIRE_NOISE_FILTER_CLK_DIV_8			(0x3U << OWIRE_NFCR_NFDIV_Pos)
/**
  * @}
  */

/** @defgroup OWIRE_NOISE_FILTER_ENABLE One-Wire Noise Filter Enable
  * @{
  */
#define OWIRE_NOISE_FILTER_ENABLE					(0x1U << OWIRE_NFCR_NFEN_Pos)
#define OWIRE_NOISE_FILTER_DISABLE				0x00000000U
/**
  * @}
  */

/** @defgroup OWIRE_COMMAND One-Wire Command
  * @{
  */
#define OWIRE_COMMAND_INIT								(0x1U << OWIRE_CMD_CMD_Pos)
#define OWIRE_COMMAND_TX									(0x2U << OWIRE_CMD_CMD_Pos)
#define OWIRE_COMMAND_RX									(0x3U << OWIRE_CMD_CMD_Pos)
/**
  * @}
  */	
	
/** @defgroup OWIRE_Error_Code One-Wire Error Code
  * @{
  */
#define HAL_OWIRE_ERROR_NONE         				0x00000000U   /*!< No error            */
#define HAL_OWIRE_ERROR_NOACK 							0x00000001U   /*!< No ACK error     */
#define HAL_OWIRE_ERROR_INIT         				0x00000002U   /*!< Init error         */
#define HAL_OWIRE_ERROR_TX          				0x00000004U   /*!< Transmit error         */
#define HAL_OWIRE_ERROR_RX          				0x00000008U   /*!< Receive error         */
/**
  * @}
  */

/** @defgroup OWIRE_Flags OWIRE Flags
  * @{
  */
#define OWIRE_FLAG_ACKERROR                 ((uint32_t)OWIRE_SR_ACKERR_Msk)
#define OWIRE_FLAG_INITDONE                 ((uint32_t)OWIRE_SR_INITDONE_Msk)
#define OWIRE_FLAG_TXDONE                 	((uint32_t)OWIRE_SR_TXDONE_Msk)
#define OWIRE_FLAG_RXDONE                  	((uint32_t)OWIRE_SR_RXDONE_Msk)
/**
  * @}
  */

/** @defgroup OWIRE_Interrupt_definition One-Wire Interrupts Definition
  * @{
  */
#define OWIRE_IT_ACKERROR               		((uint32_t)OWIRE_INTEN_ACKERREN_Msk)
#define OWIRE_IT_INIT                   		((uint32_t)OWIRE_INTEN_INITEN_Msk)
#define OWIRE_IT_TXDONE                 		((uint32_t)OWIRE_INTEN_TXDONEEN_Msk)
#define OWIRE_IT_RXDONE                 		((uint32_t)OWIRE_INTEN_RXDONEEN_Msk)
/**
  * @}
  */
	
/**
  * @}
  */	
	
/* Exported macro ------------------------------------------------------------*/
/** @defgroup OWIRE_Exported_Macros One-Wire Exported Macros
  * @{
  */
/** @brief  Checks whether the specified OWIRE flag is set or not.
  * @param  __HANDLE__: specifies the OWIRE Handle.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg OWIRE_FLAG_ACKERROR: ACK Error flag
  *            @arg OWIRE_FLAG_INITDONE: Idle Line detection flag
  *            @arg OWIRE_FLAG_TXDONE:   Transmit data register empty flag
  *            @arg OWIRE_FLAG_RXDONE:   Receive data register not empty flag	
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_OWIRE_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->SR & (__FLAG__)) == (__FLAG__))

/** @brief  Clears the specified OWIRE pending flags.
  * @param  __HANDLE__: specifies the OWIRE Handle.
  * @param  __FLAG__: specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg OWIRE_FLAG_ACKERROR: ACK Error flag
  *            @arg OWIRE_FLAG_INITDONE: Idle Line detection flag
  *            @arg OWIRE_FLAG_TXDONE:   Transmit data register empty flag
  *            @arg OWIRE_FLAG_RXDONE:   Receive data register not empty flag	
  */
#define __HAL_OWIRE_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->INTCLR = (__FLAG__))

/** @brief  Enable the specified OWIRE interrupts.
  * @param  __HANDLE__: specifies the OWIRE Handle.
  *         OWIRE Handle selects the OWIRE peripheral
  * @param  __INTERRUPT__: specifies the OWIRE interrupt source to enable.
  */
#define __HAL_OWIRE_ENABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->INTEN = (__INTERRUPT__))


/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/** @addtogroup OWIRE_Exported_Functions
  * @{
  */

/** @addtogroup OWIRE_Exported_Functions_Group1
  * @{
  */
/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_OWIRE_Init(OWIRE_HandleTypeDef *howire);
HAL_StatusTypeDef HAL_OWIRE_DeInit (OWIRE_HandleTypeDef *howire);
void HAL_OWIRE_MspInit(OWIRE_HandleTypeDef *howire);
void HAL_OWIRE_MspDeInit(OWIRE_HandleTypeDef *howire);

/**
  * @}
  */

HAL_StatusTypeDef HAL_OWIRE_Transmit(OWIRE_HandleTypeDef *howire, uint8_t *pTxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_OWIRE_Receive(OWIRE_HandleTypeDef *howire, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_OWIRE_TransmitReceive(OWIRE_HandleTypeDef *howire, uint8_t *pTxData, uint16_t TxSize, uint8_t *pRxData, uint16_t RxSize, uint32_t Timeout);

HAL_StatusTypeDef HAL_OWIRE_Transmit_IT(OWIRE_HandleTypeDef *howire, uint8_t *pTxData, uint16_t Size);
HAL_StatusTypeDef HAL_OWIRE_Receive_IT(OWIRE_HandleTypeDef *howire, uint8_t *pRxData, uint16_t Size);
HAL_StatusTypeDef HAL_OWIRE_TransmitReceive_IT(OWIRE_HandleTypeDef *howire, uint8_t *pTxData, uint16_t TxSize, uint8_t *pRxData, uint16_t RxSize);

HAL_StatusTypeDef HAL_OWIRE_Command_Init(OWIRE_HandleTypeDef *howire, uint32_t Timeout);
HAL_StatusTypeDef HAL_OWIRE_Command_Tx(OWIRE_HandleTypeDef *howire, uint8_t *pTxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_OWIRE_Command_Rx(OWIRE_HandleTypeDef *howire, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_OWIRE_Command_Init_IT_Start(OWIRE_HandleTypeDef *howire);
HAL_StatusTypeDef HAL_OWIRE_Command_Tx_IT_Start(OWIRE_HandleTypeDef *howire);
HAL_StatusTypeDef HAL_OWIRE_Command_Rx_IT_Start(OWIRE_HandleTypeDef *howire);

void HAL_OWIRE_IRQHandler(OWIRE_HandleTypeDef *howire);
void HAL_OWIRE_InitDoneCallback(OWIRE_HandleTypeDef *howire);
void HAL_OWIRE_TxCpltCallback(OWIRE_HandleTypeDef *howire);
void HAL_OWIRE_RxCpltCallback(OWIRE_HandleTypeDef *howire);
void HAL_OWIRE_TxRxCpltCallback(OWIRE_HandleTypeDef *howire);
void HAL_OWIRE_ErrorCallback(OWIRE_HandleTypeDef *howire);

/**
  * @}
  */
	
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/**
  * @}
  */ /* End of group OWIRE */

/**
  * @}
  */ /* End of group CX32L003_HAL_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_OWIRE_H */


