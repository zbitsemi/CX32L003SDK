/**
  ******************************************************************************
  * @file    cx32l003_hal_uart.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of UART HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_UART_H
#define __CX32L003_HAL_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @addtogroup UART
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup UART_Exported_Types UART Exported Types
  * @{
  */

/**
  * @brief UART Init Structure definition
  */
typedef struct
{
  uint32_t BaudRate;                  /*!< This member configures the UART communication baud rate.
                                           The baud rate is computed using the following formula:
                                           - IntegerDivider = ((PCLKx) / (16 * (huart->Init.BaudRate)))
                                           - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 16) + 0.5 */

	uint32_t BaudDouble;                /*!< Specifies whether baudrate is doubled.
                                           This parameter can be a value of @ref UART_BaudDouble */	
	
	uint32_t HalfDuplexMode;						/*!< Specifies whether halfduplex mode is enabled.
                                           This parameter can be a value of @ref UART_HalfDuplex */	
	
  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UART_Word_Length */	
	
  uint32_t Parity;                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_Parity
                                           @note When parity is enabled, the computed parity is set
                                                 at the MSB position of the transmitted data (9th bit only when
                                                 the word length is set to 9 data bits;*/	
	
  uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref UART_Mode */

}UART_InitTypeDef;

/** 
  * @brief HAL UART State structures definition
  * @note  HAL UART State value is a combination of 2 different substates: gState and RxState.
  *        - gState contains UART state information related to global Handle management 
  *          and also information related to Tx operations.
  *          gState value coding follow below described bitmap :
  *          b7-b6  Error information 
  *             00 : No Error
  *             01 : (Not Used)
  *             10 : Timeout
  *             11 : Error
  *          b5     IP initilisation status
  *             0  : Reset (IP not initialized)
  *             1  : Init done (IP not initialized. HAL UART Init function already called)
  *          b4-b3  (not used)
  *             xx : Should be set to 00
  *          b2     Intrinsic process state
  *             0  : Ready
  *             1  : Busy (IP busy with some configuration or internal operations)
  *          b1     (not used)
  *             x  : Should be set to 0
  *          b0     Tx state
  *             0  : Ready (no Tx operation ongoing)
  *             1  : Busy (Tx operation ongoing)
  *        - RxState contains information related to Rx operations.
  *          RxState value coding follow below described bitmap :
  *          b7-b6  (not used)
  *             xx : Should be set to 00
  *          b5     IP initilisation status
  *             0  : Reset (IP not initialized)
  *             1  : Init done (IP not initialized)
  *          b4-b2  (not used)
  *            xxx : Should be set to 000
  *          b1     Rx state
  *             0  : Ready (no Rx operation ongoing)
  *             1  : Busy (Rx operation ongoing)
  *          b0     (not used)
  *             x  : Should be set to 0.
  */
typedef enum
{
  HAL_UART_STATE_RESET             = 0x00U,    /*!< Peripheral is not yet Initialized 
                                                   Value is allowed for gState and RxState */
  HAL_UART_STATE_READY             = 0x20U,    /*!< Peripheral Initialized and ready for use
                                                   Value is allowed for gState and RxState */
  HAL_UART_STATE_BUSY              = 0x24U,    /*!< an internal process is ongoing
                                                   Value is allowed for gState only */
  HAL_UART_STATE_BUSY_TX           = 0x21U,    /*!< Data Transmission process is ongoing 
                                                   Value is allowed for gState only */
  HAL_UART_STATE_BUSY_RX           = 0x22U,    /*!< Data Reception process is ongoing
                                                   Value is allowed for RxState only */
  HAL_UART_STATE_BUSY_TX_RX        = 0x23U,    /*!< Data Transmission and Reception process is ongoing 
                                                   Not to be used for neither gState nor RxState.
                                                   Value is result of combination (Or) between gState and RxState values */
  HAL_UART_STATE_TIMEOUT           = 0xA0U,    /*!< Timeout state    
                                                   Value is allowed for gState only */
  HAL_UART_STATE_ERROR             = 0xE0U     /*!< Error   
                                                   Value is allowed for gState only */
}HAL_UART_StateTypeDef;

/** 
  * @brief  UART handle Structure definition
  */
typedef struct
{
  UART_TypeDef                 *Instance;         /*!< UART registers base address        */

  UART_InitTypeDef              Init;             /*!< UART communication parameters      */

  uint8_t                       *pTxBuffPtr;      /*!< Pointer to UART Tx transfer Buffer */

  uint16_t                      TxXferSize;       /*!< UART Tx Transfer size              */

  __IO uint16_t                 TxXferCount;      /*!< UART Tx Transfer Counter           */

  uint8_t                       *pRxBuffPtr;      /*!< Pointer to UART Rx transfer Buffer */

  uint16_t                      RxXferSize;       /*!< UART Rx Transfer size              */

  __IO uint16_t                 RxXferCount;      /*!< UART Rx Transfer Counter           */

  HAL_LockTypeDef               Lock;             /*!< Locking object                     */

  __IO HAL_UART_StateTypeDef    gState;           /*!< UART state information related to global Handle management 
                                                       and also related to Tx operations.
                                                       This parameter can be a value of @ref HAL_UART_StateTypeDef */
  
  __IO HAL_UART_StateTypeDef    RxState;          /*!< UART state information related to Rx operations.
                                                       This parameter can be a value of @ref HAL_UART_StateTypeDef */

  __IO uint32_t                 ErrorCode;        /*!< UART Error code                    */
}UART_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup UART_Exported_Constants UART Exported constants
  * @{
  */

/** @defgroup UART_Error_Code UART Error Code
  * @{
  */
#define HAL_UART_ERROR_NONE         				0x00000000U   /*!< No error            */
#define HAL_UART_ERROR_CONFIG								0x00000001U   /*!< Configure error     */
#define HAL_UART_ERROR_PARITY        				0x00000002U   /*!< Parity error        */
#define HAL_UART_ERROR_FE           				0x00000004U   /*!< Frame error         */

/**
  * @}
  */

/** @defgroup UART_BaudDouble UART Baudrate doubled
  * @{
  */
#define UART_BAUDDOUBLE_ENABLE              ((uint32_t)UART_SCON_DBAUD)
#define UART_BAUDDOUBLE_DISABLE             (0x00000000U)
/**
  * @}
  */


/** @defgroup UART_HalfDuplex UART Halfduplex mode enable or disable
  * @{
  */
#define UART_HALFDUPLEX_ENABLE							(0x00000001U)
#define UART_HALFDUPLEX_DISABLE							(0x00000000U)
	
/**
  * @}
  */	
	

/** @defgroup UART_Word_Length UART Word Length
  * @{
  */
#define UART_WORDLENGTH_8B                  ((uint32_t)UART_SCON_SM0_SM1_1)
#define UART_WORDLENGTH_9B                  ((uint32_t)(UART_SCON_SM0_SM1_0 | UART_SCON_SM0_SM1_1))
/**
  * @}
  */


/** @defgroup UART_Parity  UART Parity
  * @{
  */
#define UART_PARITY_NONE                    (0x00000000U)
#define UART_PARITY_EVEN                    (0x00000001U)
#define UART_PARITY_ODD                     (0x00000002U) 
/**
  * @}
  */


/** @defgroup UART_Mode UART Transfer Mode
  * @{
  */ 
#define UART_MODE_TX                        (0x00000000U)
#define UART_MODE_TX_RX                     ((uint32_t)UART_SCON_REN)
/**
  * @}
  */


/** @defgroup UART_Flags   UART FLags
  * @{
  */
#define UART_FLAG_TC                        ((uint32_t)UART_INTSR_TI)
#define UART_FLAG_RXNE                      ((uint32_t)UART_INTSR_RI)
#define	UART_FLAG_FE												((uint32_t)UART_INTSR_FE)

/**
  * @}
  */

/** @defgroup UART_Interrupt_definition  UART Interrupt Definitions
  * @{
  */
#define UART_IT_TC                       ((uint32_t)(UART_SCON_TIEN))
#define UART_IT_RXNE                     ((uint32_t)(UART_SCON_RIEN))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup UART_Exported_Macros UART Exported Macros
  * @{
  */

/** @brief  Checks whether the specified UART flag is set or not.
  * @param  __HANDLE__: specifies the UART Handle.
  *         This parameter can be UARTx where x: 0, 1 to select the peripheral.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg UART_FLAG_TC:   Transmission Complete flag
  *            @arg UART_FLAG_RXNE: Receive data register not empty flag
  *            @arg UART_FLAG_FE:   Framing Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_UART_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->INTSR & (__FLAG__)) == (__FLAG__))   

/** @brief  Clears the specified UART pending flag.
  * @param  __HANDLE__: specifies the UART Handle.
  *         This parameter can be UARTx where x: 0, 1 to select the peripheral.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg UART_FLAG_TC:   Transmission Complete flag
  *            @arg UART_FLAG_RXNE: Receive data register not empty flag
  *            @arg UART_FLAG_FE:   Framing Error flag	
  *   
  * @note   TC, FE, RXNE flag should be cleared by software.
  *   
  */
#define __HAL_UART_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->INTCLR |= (__FLAG__))


/** @brief  Enable the specified UART interrupt.
  * @param  __HANDLE__: specifies the UART Handle.
  *         UART Handle selects the UARTx peripheral 
  * @param  __INTERRUPT__: specifies the UART interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg UART_IT_TC:   Transmission complete interrupt
  *            @arg UART_IT_RXNE: Receive Data register not empty interrupt
  */
#define __HAL_UART_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->SCON |= ((__INTERRUPT__) & UART_IT_MASK))

/** @brief  Disable the specified UART interrupt.
  * @param  __HANDLE__: specifies the UART Handle.
  *         UART Handle selects the UARTx peripheral 
  * @param  __INTERRUPT__: specifies the UART interrupt source to disable.
  *          This parameter can be one of the following values:
  *            @arg UART_IT_TC:   Transmission complete interrupt
  *            @arg UART_IT_RXNE: Receive Data register not empty interrupt
  */
#define __HAL_UART_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->SCON &= ~ ((__INTERRUPT__) & UART_IT_MASK))

/** @brief  Checks whether the specified UART interrupt has occurred or not.
  * @param  __HANDLE__: specifies the UART Handle.
  *         UART Handle selects the UARTx peripheral 
  * @param  __IT__: specifies the UART interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg UART_IT_TC:  Transmission complete interrupt
  *            @arg UART_IT_RXNE: Receive Data register not empty interrupt
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_UART_GET_IT_SOURCE(__HANDLE__, __IT__) ((__HANDLE__)->Instance->SCON) & (((uint32_t)(__IT__)) & UART_IT_MASK))


/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/** @addtogroup UART_Exported_Functions
  * @{
  */

/** @addtogroup UART_Exported_Functions_Group1
  * @{
  */
/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DeInit (UART_HandleTypeDef *huart);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);
/**
  * @}
  */

/** @addtogroup UART_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *******************************************************/
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
/* Transfer Abort functions */
HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive(UART_HandleTypeDef *huart);

void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortCpltCallback (UART_HandleTypeDef *huart);
void HAL_UART_AbortTransmitCpltCallback (UART_HandleTypeDef *huart);
void HAL_UART_AbortReceiveCpltCallback (UART_HandleTypeDef *huart);


extern HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart);
extern HAL_StatusTypeDef UART_Single_Receive_IT(UART_HandleTypeDef *huart);

void Naked_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size,IRQn_Type IRQn);
void Naked_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
void Naked_UART_IRQHandler(UART_HandleTypeDef *huart);
/**
  * @}
  */


/** @addtogroup UART_Exported_Functions_Group3
  * @{
  */
/* Peripheral State functions  **************************************************/
HAL_UART_StateTypeDef HAL_UART_GetState(UART_HandleTypeDef *huart);
uint32_t HAL_UART_GetError(UART_HandleTypeDef *huart);
/**
  * @}
  */

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup UART_Private_Constants UART Private Constants
  * @{
  */
/** @brief UART interruptions flag mask
  * 
  */
#define UART_IT_MASK                     0x00000003U

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup UART_Private_Macros UART Private Macros
  * @{
  */
#define IS_UART_BAUDRATE(BAUDRATE) ((BAUDRATE) < 230400U)

/**
  * @}
  */



/**
  * @}
  */ /* End of group UART */

/**
  * @}
  */ /* End of group CX32L003_HAL_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_UART_H */


