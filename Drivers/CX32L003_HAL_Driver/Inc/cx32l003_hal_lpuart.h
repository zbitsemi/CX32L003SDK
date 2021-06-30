/**
  ******************************************************************************
  * @file    cx32l003_hal_lpuart.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of LPUART HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_LPUART_H
#define __CX32L003_HAL_LPUART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @addtogroup LPUART
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup LPUART_Exported_Types LPUART Exported Types
  * @{
  */

/**
  * @brief LPUART Init Structure definition
  */
typedef struct
{
	uint32_t ClkSel;										/*!< Specifies SCLK for LPUART.
                                           This parameter can be a value of @ref LPUART_ClkSel */	
	
	uint32_t ClkDiv;										/*!< Specifies SCLK divider for LPUART.
                                           This parameter can be a value of @ref LPUART_ClkDiv */	

	uint32_t LowPowerMode;							/*!< Specifies low power mode for LPUART.
																					 LPUART can run in normal mode or low power mode by configuration.
                                           This parameter can be a value of @ref LPUART_LowPowerMode */	
	
  uint32_t BaudRate;                  /*!< This member configures the LPUART communication baud rate.
                                           The baud rate is computed using the following formula:
                                           - IntegerDivider = ((PCLKx) / (16 * (hlpuart->Init.BaudRate)))
                                           - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 16) + 0.5 */

	uint32_t BaudDouble;                /*!< Specifies whether baudrate is doubled.
                                           This parameter can be a value of @ref LPUART_BaudDouble */	
	
	uint32_t HalfDuplexMode;						/*!< Specifies whether halfduplex mode is enabled.
                                           This parameter can be a value of @ref LPUART_HalfDuplex */	
	
  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref LPUART_Word_Length */	
	
  uint32_t Parity;                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref LPUART_Parity
                                           @note When parity is enabled, the computed parity is set
                                                 at the MSB position of the transmitted data (9th bit only when
                                                 the word length is set to 9 data bits;*/	
	
  uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref LPUART_Mode */

}LPUART_InitTypeDef;

/** 
  * @brief HAL LPUART State structures definition
  * @note  HAL LPUART State value is a combination of 2 different substates: gState and RxState.
  *        - gState contains LPUART state information related to global Handle management 
  *          and also information related to Tx operations.
  *          gState value coding follow below described bitmap :
  *          b7-b6  Error information 
  *             00 : No Error
  *             01 : (Not Used)
  *             10 : Timeout
  *             11 : Error
  *          b5     IP initilisation status
  *             0  : Reset (IP not initialized)
  *             1  : Init done (IP not initialized. HAL LPUART Init function already called)
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
  HAL_LPUART_STATE_RESET             = 0x00U,    /*!< Peripheral is not yet Initialized 
                                                   Value is allowed for gState and RxState */
  HAL_LPUART_STATE_READY             = 0x20U,    /*!< Peripheral Initialized and ready for use
                                                   Value is allowed for gState and RxState */
  HAL_LPUART_STATE_BUSY              = 0x24U,    /*!< an internal process is ongoing
                                                   Value is allowed for gState only */
  HAL_LPUART_STATE_BUSY_TX           = 0x21U,    /*!< Data Transmission process is ongoing 
                                                   Value is allowed for gState only */
  HAL_LPUART_STATE_BUSY_RX           = 0x22U,    /*!< Data Reception process is ongoing
                                                   Value is allowed for RxState only */
  HAL_LPUART_STATE_BUSY_TX_RX        = 0x23U,    /*!< Data Transmission and Reception process is ongoing 
                                                   Not to be used for neither gState nor RxState.
                                                   Value is result of combination (Or) between gState and RxState values */
  HAL_LPUART_STATE_TIMEOUT           = 0xA0U,    /*!< Timeout state    
                                                   Value is allowed for gState only */
  HAL_LPUART_STATE_ERROR             = 0xE0U     /*!< Error   
                                                   Value is allowed for gState only */
}HAL_LPUART_StateTypeDef;

/** 
  * @brief  LPUART handle Structure definition
  */
typedef struct
{
  LPUART_TypeDef                 *Instance;         /*!< LPUART registers base address        */

  LPUART_InitTypeDef              Init;             /*!< LPUART communication parameters      */

  uint8_t                       *pTxBuffPtr;      /*!< Pointer to LPUART Tx transfer Buffer */

  uint16_t                      TxXferSize;       /*!< LPUART Tx Transfer size              */

  __IO uint16_t                 TxXferCount;      /*!< LPUART Tx Transfer Counter           */

  uint8_t                       *pRxBuffPtr;      /*!< Pointer to LPUART Rx transfer Buffer */

  uint16_t                      RxXferSize;       /*!< LPUART Rx Transfer size              */

  __IO uint16_t                 RxXferCount;      /*!< LPUART Rx Transfer Counter           */

  HAL_LockTypeDef               Lock;             /*!< Locking object                     */

  __IO HAL_LPUART_StateTypeDef    gState;           /*!< LPUART state information related to global Handle management 
                                                       and also related to Tx operations.
                                                       This parameter can be a value of @ref HAL_LPUART_StateTypeDef */
  
  __IO HAL_LPUART_StateTypeDef    RxState;          /*!< LPUART state information related to Rx operations.
                                                       This parameter can be a value of @ref HAL_LPUART_StateTypeDef */

  __IO uint32_t                 ErrorCode;        /*!< LPUART Error code                    */
}LPUART_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup LPUART_Exported_Constants LPUART Exported constants
  * @{
  */

/** @defgroup LPUART_Error_Code LPUART Error Code
  * @{
  */
#define HAL_LPUART_ERROR_NONE         				0x00000000U   /*!< No error            */
#define HAL_LPUART_ERROR_CONFIG								0x00000001U   /*!< Configure error     */
#define HAL_LPUART_ERROR_PARITY        				0x00000002U   /*!< Parity error        */
#define HAL_LPUART_ERROR_FE           				0x00000004U   /*!< Frame error         */

/**
  * @}
  */


/** @defgroup LPUART_ClkSel LPUART Clock selection
  * @{
  */
#define LPUART_CLOCK_PCLK             				(0x00000000U)
#define LPUART_CLOCK_LXT             					(LPUART_SCON_SCLKSEL_1)
#define LPUART_CLOCK_LIRC             				(LPUART_SCON_SCLKSEL_1 | LPUART_SCON_SCLKSEL_0)

/**
  * @}
  */


/** @defgroup LPUART_ClkDiv LPUART Clock divider
  * @{
  */
#define LPUART_CLOCK_DIV128             			(0x00000000U)
#define LPUART_CLOCK_DIV64             				(LPUART_SCON_PRSC_0)
#define LPUART_CLOCK_DIV32             				(LPUART_SCON_PRSC_1)
#define LPUART_CLOCK_DIV16 										(LPUART_SCON_PRSC_1 | LPUART_SCON_PRSC_0)
#define LPUART_CLOCK_DIV8											(LPUART_SCON_PRSC_2)
#define LPUART_CLOCK_DIV4											(LPUART_SCON_PRSC_2 | LPUART_SCON_PRSC_0)
#define LPUART_CLOCK_DIV2											(LPUART_SCON_PRSC_2 | LPUART_SCON_PRSC_1)
#define LPUART_CLOCK_DIV1											(LPUART_SCON_PRSC_2 | LPUART_SCON_PRSC_1 | LPUART_SCON_PRSC_0)

/**
  * @}
  */

/** @defgroup LPUART_LowPowerMode LPUART low power mode enable/disable
  * @{
  */
#define LPUART_MODE_NORMAL             				(0x00000000U)	
#define LPUART_MODE_LOWPOWER              		((uint32_t)LPUART_SCON_LPMODE)

/**
  * @}
  */


/** @defgroup LPUART_BaudDouble LPUART Baudrate doubled
  * @{
  */
#define LPUART_BAUDDOUBLE_ENABLE              ((uint32_t)LPUART_SCON_DBAUND)
#define LPUART_BAUDDOUBLE_DISABLE             (0x00000000U)
/**
  * @}
  */


/** @defgroup LPUART_HalfDuplex LPUART Halfduplex mode enable or disable
  * @{
  */
#define LPUART_HALFDUPLEX_ENABLE							(0x00000001U)
#define LPUART_HALFDUPLEX_DISABLE							(0x00000000U)
	
/**
  * @}
  */	
	

/** @defgroup LPUART_Word_Length LPUART Word Length
  * @{
  */
#define LPUART_WORDLENGTH_8B                  ((uint32_t)LPUART_SCON_SM0_SM1_1)  // ģʽ1
#define LPUART_WORDLENGTH_9B                  ((uint32_t)(LPUART_SCON_SM0_SM1_0 | LPUART_SCON_SM0_SM1_1)) // ģʽ3
/**
  * @}
  */


/** @defgroup LPUART_Parity  LPUART Parity
  * @{
  */
#define LPUART_PARITY_NONE                    (0x00000000U)
#define LPUART_PARITY_EVEN                    (0x00000001U)
#define LPUART_PARITY_ODD                     (0x00000002U) 
/**
  * @}
  */


/** @defgroup LPUART_Mode LPUART Transfer Mode
  * @{
  */ 
#define LPUART_MODE_TX                        (0x00000000U)
#define LPUART_MODE_TX_RX                     ((uint32_t)LPUART_SCON_REN)
/**
  * @}
  */


/** @defgroup LPUART_Flags   LPUART FLags
  * @{
  */
#define LPUART_FLAG_TC                        ((uint32_t)LPUART_INTSR_TI)
#define LPUART_FLAG_RXNE                      ((uint32_t)LPUART_INTSR_RI)
#define	LPUART_FLAG_FE												((uint32_t)LPUART_INTSR_FE)

/**
  * @}
  */

/** @defgroup LPUART_Interrupt_definition  LPUART Interrupt Definitions
  * @{
  */
#define LPUART_IT_TE                       ((uint32_t)(LPUART_SCON_TEEN))	
#define LPUART_IT_TC                       ((uint32_t)(LPUART_SCON_TIEN))
#define LPUART_IT_RXNE                     ((uint32_t)(LPUART_SCON_RIEN))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup LPUART_Exported_Macros LPUART Exported Macros
  * @{
  */

/** @brief  Checks whether the specified LPUART flag is set or not.
  * @param  __HANDLE__: specifies the LPUART Handle.
  *         This parameter can be LPUARTx where x: 0, 1 to select the peripheral.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg LPUART_FLAG_TC:   Transmission Complete flag
  *            @arg LPUART_FLAG_RXNE: Receive data register not empty flag
  *            @arg LPUART_FLAG_FE:   Framing Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_LPUART_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->INTSR & (__FLAG__)) == (__FLAG__))   

/** @brief  Clears the specified LPUART pending flag.
  * @param  __HANDLE__: specifies the LPUART Handle.
  *         This parameter can be LPUARTx where x: 0, 1 to select the peripheral.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg LPUART_FLAG_TC:   Transmission Complete flag
  *            @arg LPUART_FLAG_RXNE: Receive data register not empty flag
  *            @arg LPUART_FLAG_FE:   Framing Error flag	
  *   
  * @note   TC, FE, RXNE flag should be cleared by software.
  *   
  */
#define __HAL_LPUART_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->INTCLR = (__FLAG__))


/** @brief  Enable the specified LPUART interrupt.
  * @param  __HANDLE__: specifies the LPUART Handle.
  *         LPUART Handle selects the LPUARTx peripheral 
  * @param  __INTERRUPT__: specifies the LPUART interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg LPUART_IT_TE:   Transmission buffer empty interrupt	
  *            @arg LPUART_IT_TC:   Transmission complete interrupt
  *            @arg LPUART_IT_RXNE: Receive Data register not empty interrupt
  */
#define __HAL_LPUART_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->SCON |= ((__INTERRUPT__) & LPUART_IT_MASK))

/** @brief  Disable the specified LPUART interrupt.
  * @param  __HANDLE__: specifies the LPUART Handle.
  *         LPUART Handle selects the LPUARTx peripheral 
  * @param  __INTERRUPT__: specifies the LPUART interrupt source to disable.
  *          This parameter can be one of the following values:
  *            @arg LPUART_IT_TE:   Transmission buffer empty interrupt		
  *            @arg LPUART_IT_TC:   Transmission complete interrupt
  *            @arg LPUART_IT_RXNE: Receive Data register not empty interrupt
  */
#define __HAL_LPUART_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->SCON &= ~ ((__INTERRUPT__) & LPUART_IT_MASK))

/** @brief  Checks whether the specified LPUART interrupt has occurred or not.
  * @param  __HANDLE__: specifies the LPUART Handle.
  *         LPUART Handle selects the LPUARTx peripheral 
  * @param  __IT__: specifies the LPUART interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg LPUART_IT_TC:  Transmission complete interrupt
  *            @arg LPUART_IT_RXNE: Receive Data register not empty interrupt
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_LPUART_GET_IT_SOURCE(__HANDLE__, __IT__) ((__HANDLE__)->Instance->SCON) & (((uint32_t)(__IT__)) & LPUART_IT_MASK))

/** @brief  Enable LPUART
  * @param  __HANDLE__: specifies the LPUART Handle.
  *         LPUART Handle selects the LPUART peripheral.
  */
#define __HAL_LPUART_ENABLE(__HANDLE__)               SET_BIT((__HANDLE__)->Instance->SCON,(LPUART_SCON_EN)) 

/** @brief  Disable LPUART
  * @param  __HANDLE__: specifies the LPUART Handle.
  *         LPUART Handle selects the LPUART peripheral.
  */
#define __HAL_LPUART_DISABLE(__HANDLE__)              CLEAR_BIT((__HANDLE__)->Instance->SCON,(LPUART_SCON_EN)) 



/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/** @addtogroup LPUART_Exported_Functions
  * @{
  */

/** @addtogroup LPUART_Exported_Functions_Group1
  * @{
  */
/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_LPUART_Init(LPUART_HandleTypeDef *hlpuart);
HAL_StatusTypeDef HAL_LPUART_DeInit (LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_MspInit(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_MspDeInit(LPUART_HandleTypeDef *hlpuart);
/**
  * @}
  */

/** @addtogroup LPUART_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *******************************************************/
HAL_StatusTypeDef HAL_LPUART_Transmit(LPUART_HandleTypeDef *hlpuart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_LPUART_Receive(LPUART_HandleTypeDef *hlpuart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_LPUART_Transmit_IT(LPUART_HandleTypeDef *hlpuart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_LPUART_Receive_IT(LPUART_HandleTypeDef *hlpuart, uint8_t *pData, uint16_t Size);
/* Transfer Abort functions */
HAL_StatusTypeDef HAL_LPUART_Abort(LPUART_HandleTypeDef *hlpuart);
HAL_StatusTypeDef HAL_LPUART_AbortTransmit(LPUART_HandleTypeDef *hlpuart);
HAL_StatusTypeDef HAL_LPUART_AbortReceive(LPUART_HandleTypeDef *hlpuart);

void HAL_LPUART_IRQHandler(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_TxCpltCallback(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_RxCpltCallback(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_ErrorCallback(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_AbortCpltCallback (LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_AbortTransmitCpltCallback (LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_AbortReceiveCpltCallback (LPUART_HandleTypeDef *hlpuart);
/**
  * @}
  */


/** @addtogroup LPUART_Exported_Functions_Group3
  * @{
  */
/* Peripheral State functions  **************************************************/
HAL_LPUART_StateTypeDef HAL_LPUART_GetState(LPUART_HandleTypeDef *hlpuart);
uint32_t HAL_LPUART_GetError(LPUART_HandleTypeDef *hlpuart);
/**
  * @}
  */

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup LPUART_Private_Constants LPUART Private Constants
  * @{
  */
/** @brief LPUART interruptions flag mask
  * 
  */
#define LPUART_IT_MASK                     0x00000103U

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup LPUART_Private_Macros LPUART Private Macros
  * @{
  */
#define IS_LPUART_BAUDRATE(BAUDRATE) ((BAUDRATE) < 230400U)

/**
  * @}
  */



/**
  * @}
  */ /* End of group LPUART */

/**
  * @}
  */ /* End of group CX32L003_HAL_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_LPUART_H */


