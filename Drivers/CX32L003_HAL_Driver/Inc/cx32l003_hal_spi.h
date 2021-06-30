/**
  ******************************************************************************
  * @file    cx32l003_hal_spi.h
	* @author  MCU Software Team
	* @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of SPI HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_SPI_H
#define __CX32L003_HAL_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"  

/** @addtogroup CX32L003_HAL_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SPI_Exported_Types SPI Exported Types
  * @{
  */

/**
  * @brief  SPI Configuration Structure definition
  */
typedef struct
{
  uint32_t Mode;               /*!< Specifies the SPI operating mode.
                                    This parameter can be a value of @ref SPI_Mode */

 uint32_t CLKPolarity;        /*!< Specifies the serial clock steady state.
                                    This parameter can be a value of @ref SPI_Clock_Polarity */

  uint32_t CLKPhase;           /*!< Specifies the clock active edge for the bit capture.
                                    This parameter can be a value of @ref SPI_Clock_Phase */

  uint32_t NSS;                /*!< Specifies the NSS signal is Hight or low after Inint @ref SPI_Init_Mode */

  uint32_t BaudRatePrescaler;  /*!< Specifies the Baud Rate prescaler value which will be
                                    used to configure the transmit and receive SCK clock.
                                    This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                    @note The communication clock is derived from the master
                                     clock. The slave clock does not need to be set. */
}SPI_InitTypeDef;

/**
  * @brief  HAL SPI State structure definition
  */
typedef enum
{
  HAL_SPI_STATE_RESET      = 0x00U,    /*!< Peripheral not Initialized                         */
  HAL_SPI_STATE_READY      = 0x01U,    /*!< Peripheral Initialized and ready for use           */
  HAL_SPI_STATE_BUSY       = 0x02U,    /*!< an internal process is ongoing                     */
  HAL_SPI_STATE_BUSY_TX    = 0x03U,    /*!< Data Transmission process is ongoing               */
  HAL_SPI_STATE_BUSY_RX    = 0x04U,    /*!< Data Reception process is ongoing                  */
  HAL_SPI_STATE_BUSY_TX_RX = 0x05U,    /*!< Data Transmission and Reception process is ongoing */
  HAL_SPI_STATE_ERROR      = 0x06U     /*!< SPI error state                                    */
}HAL_SPI_StateTypeDef;

/**
  * @brief  SPI handle Structure definition
  */
typedef struct __SPI_HandleTypeDef
{
  SPI_TypeDef                *Instance;    /*!< SPI registers base address */

  SPI_InitTypeDef            Init;         /*!< SPI communication parameters */

  HAL_LockTypeDef            Lock;         /*!< Locking object                 */

  __IO HAL_SPI_StateTypeDef  State;        /*!< SPI communication state */
 
  __IO uint32_t              ErrorCode;      /*!< SPI Error code                           */
}SPI_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup SPI_Exported_Constants SPI Exported Constants
  * @{
  */

/** @defgroup SPI_Error_Code SPI Error Code
  * @{
  */
#define HAL_SPI_ERROR_NONE              0x00000000U   /*!< No error             */
#define HAL_SPI_ERROR_MODF              0x00000001U   /*!< MODF error           */
#define HAL_SPI_ERROR_OVR               0x00000002U   /*!< OVR error            */
#define HAL_SPI_ERROR_FRE               0x00000004U   /*!< FRE error            */
#define HAL_SPI_ERROR_FLAG              0x00000008U   /*!< Flag:                */
/**
  * @}
  */

/** @defgroup SPI_Mode SPI Mode
  * @{
  */
#define SPI_MODE_SLAVE                  0x00000000U
#define SPI_MODE_MASTER                 SPI_CR_MSTR
/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity SPI Clock Polarity
  * @{
  */
#define SPI_POLARITY_LOW                0x00000000U
#define SPI_POLARITY_HIGH               SPI_CR_CPOL
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase SPI Clock Phase
  * @{
  */
#define SPI_PHASE_1EDGE                 0x00000000U
#define SPI_PHASE_2EDGE                 SPI_CR_CPHA
/**
  * @}
  */

/** @defgroup SPI_NSS_management SPI NSS set
  * @{
  */
#define SPI_NSS_MODE_HIGH                   SPI_SSN_SSN
#define SPI_NSS_MODE_LOW                    0x00000000U

/**
  * @}
  */

/** @defgroup SPI_BaudRate_Prescaler SPI BaudRate Prescaler
  * @{
  */
#define SPI_BAUDRATEPRESCALER_2         0x00000000U
#define SPI_BAUDRATEPRESCALER_4         SPI_CR_SPR0
#define SPI_BAUDRATEPRESCALER_8         SPI_CR_SPR1
#define SPI_BAUDRATEPRESCALER_16        (uint32_t)(SPI_CR_SPR0 | SPI_CR_SPR1)
#define SPI_BAUDRATEPRESCALER_32        SPI_CR_SPR2
#define SPI_BAUDRATEPRESCALER_64        (uint32_t)(SPI_CR_SPR2 | SPI_CR_SPR0)
#define SPI_BAUDRATEPRESCALER_128       (uint32_t)(SPI_CR_SPR2 | SPI_CR_SPR1)


/**
  * @}
  */

/** @defgroup SPI_Flags_definition SPI Flags Definition
  * @{
  */
#define SPI_FLAG_SPIF                  SPI_SR_SPIF    /* SPI status flag: Tx ok flag */
#define SPI_FLAG_WCOL                  SPI_SR_WCOL    /* SPI status flag: write conflict  flag */
#define SPI_FLAG_SSERR                 SPI_SR_SSERR /* SPI Error flag: Slave SSN flag */
#define SPI_FLAG_MDF                   SPI_SR_MDF   /* SPI Error flag: Master Mode error flag */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup SPI_Exported_Macros SPI Exported Macros
  * @{
  */



/** @brief  Check whether the specified SPI flag is set or not.
  * @param  __HANDLE__ specifies the SPI Handle.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg SPI_FLAG_SPIF  : SPI status flag: Tx ok flag 
  *            @arg SPI_FLAG_WCOL  : SPI status flag: write conflict  flag 
  *            @arg SPI_FLAG_SSERR : SPI Error flag: Slave SSN flag 
  *            @arg SPI_FLAG_MDF   : SPI Error flag: Master Mode error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_SPI_GET_FLAG(__HANDLE__,__FLAG__) ((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__))


/** @brief  Enable the SPI peripheral.
  * @param  __HANDLE__ specifies the SPI Handle.
  * @retval None
  */
#define __HAL_SPI_ENABLE(__HANDLE__) SET_BIT((__HANDLE__)->Instance->CR, SPI_CR_SPEN)

/** @brief  Disable the SPI peripheral.
  * @param  __HANDLE__ specifies the SPI Handle.
  * @retval None
  */
#define __HAL_SPI_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR &= (~SPI_CR_SPEN))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SPI_Exported_Functions
  * @{
  */

/** @addtogroup SPI_Exported_Functions_Group1
  * @{
  */
/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DeInit (SPI_HandleTypeDef *hspi);
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi);
/**
  * @}
  */

/** @addtogroup SPI_Exported_Functions_Group2
  * @{
  */
/* I/O operation functions  *****************************************************/
HAL_StatusTypeDef HAL_SPI_Master_Send_Data(SPI_HandleTypeDef *hspi, uint8_t RxData);
HAL_StatusTypeDef HAL_SPI_Master_Receive_Data(SPI_HandleTypeDef *hspi, uint8_t *pRxData);
HAL_StatusTypeDef HAL_SPI_Master_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t TxSize,uint8_t *pRxData, uint16_t RxSize);
HAL_StatusTypeDef HAL_SPI_Slave_Send_Data(SPI_HandleTypeDef *hspi, uint8_t RxData);
HAL_StatusTypeDef HAL_SPI_Slave_Receive_Data(SPI_HandleTypeDef *hspi, uint8_t *pRxData);
HAL_StatusTypeDef HAL_SPI_Set_NSS(SPI_HandleTypeDef *hspi, uint32_t NSS_Status);
void LL_SPI_Master_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t TxSize,uint8_t *pRxData, uint16_t RxSize);
/**
  * @}
  */

/** @addtogroup SPI_Exported_Functions_Group3
  * @{
  */
/* Peripheral State and Error functions ***************************************/
FlagStatus    HAL_SPI_Get_SPIIF(SPI_HandleTypeDef *hspi);
uint32_t      HAL_SPI_Get_ErrorFlags(SPI_HandleTypeDef *hspi);
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
/** @defgroup SPI_Private_Macros SPI Private Macros
  * @{
  */


#define IS_SPI_MODE(MODE) (((MODE) == SPI_MODE_SLAVE) || \
                           ((MODE) == SPI_MODE_MASTER))

#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_POLARITY_LOW) || \
                           ((CPOL) == SPI_POLARITY_HIGH))

#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_PHASE_1EDGE) || \
                           ((CPHA) == SPI_PHASE_2EDGE))

#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_MODE_HIGH)       || \
                         ((NSS) == SPI_NSS_MODE_LOW))

#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BAUDRATEPRESCALER_2)   || \
                                              ((PRESCALER) == SPI_BAUDRATEPRESCALER_4)   || \
                                              ((PRESCALER) == SPI_BAUDRATEPRESCALER_8)   || \
                                              ((PRESCALER) == SPI_BAUDRATEPRESCALER_16)  || \
                                              ((PRESCALER) == SPI_BAUDRATEPRESCALER_32)  || \
                                              ((PRESCALER) == SPI_BAUDRATEPRESCALER_64)  || \
                                              ((PRESCALER) == SPI_BAUDRATEPRESCALER_128))
                                              
#define IS_SPI_INSTANCE(INSTANCE)       ((INSTANCE) == SPI)
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_SPI_H */

