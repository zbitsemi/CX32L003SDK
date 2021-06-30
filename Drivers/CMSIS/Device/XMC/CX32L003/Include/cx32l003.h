/**
  ******************************************************************************
  * @file    cx32l003.h
  * @author  Software Team
  * @version V1.0.0
  * @date    21-Oct-2019
  * @brief   CMSIS Cortex-M+ Device Peripheral Access Layer Header File. 
  *          This file contains all the peripheral register's definitions, bits 
  *          definitions and memory mapping for CX32L0xx devices.            
  *            
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *  
  ******************************************************************************
  */


/** @addtogroup CX32L003
  * @{
  */

#ifndef CX32L003_H
#define CX32L003_H

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup Configuration_of_CMSIS
  * @{
  */

/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum {
/* =======================================  ARM Cortex-M0+ Specific Interrupt Numbers  ======================================= */
  Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
  NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
  HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
  SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
  PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
  SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */
/* ==========================================  CX32L003 Specific Interrupt Numbers  ========================================== */
  GPIOA_IRQn                =   0,              /*!< 0  GPIOA                                                                  */
  GPIOB_IRQn                =   1,              /*!< 1  GPIOB global interrupt                                                 */
  GPIOC_IRQn                =   2,              /*!< 2  GPIOC global interrupt                                                 */
  GPIOD_IRQn                =   3,              /*!< 3  GPIOD global interrupt                                                 */
  FLASH_IRQn                =   4,              /*!< 4  FLASH                                                                  */
  UART0_IRQn                =   6,              /*!< 6  UART0                                                                  */
  UART1_IRQn                =   7,              /*!< 7  UART1 global interrupt                                                 */
  LPUART_IRQn               =   8,              /*!< 8  LPUART                                                                 */
  SPI_IRQn                  =  10,              /*!< 10 SPI                                                                    */
  I2C_IRQn                  =  12,              /*!< 12 I2C                                                                    */
  TIM10_IRQn                =  14,              /*!< 14 TIM10                                                                  */
  TIM11_IRQn                =  15,              /*!< 15 TIM11 global interrupt                                                 */
  LPTIM_IRQn                =  16,              /*!< 16 LPTIM                                                                  */
  TIM1_IRQn                 =  18,              /*!< 18 TIM1                                                                   */
  TIM2_IRQn                 =  19,              /*!< 19 TIM2 global interrupt                                                  */
  PCA_IRQn                  =  21,              /*!< 21 PCA                                                                    */
  WWDG_IRQn                 =  22,              /*!< 22 WWDG                                                                   */
  IWDG_IRQn                 =  23,              /*!< 23 IWDG                                                                   */
  ADC_IRQn                  =  24,              /*!< 24 ADC                                                                    */
  LVD_IRQn                  =  25,              /*!< 25 LVD                                                                    */
  VC_IRQn                   =  26,              /*!< 26 VC                                                                     */
  AWK_IRQn                  =  28,              /*!< 28 AWK                                                                    */
  OWIRE_IRQn                =  29,              /*!< 29 OWIRE                                                                  */
  RTC_IRQn                  =  30,              /*!< 30 RTC                                                                    */
  CLKTRIM_IRQn              =  31               /*!< 31 CLKTRIM                                                                */
} IRQn_Type;



/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ==========================  Configuration of the ARM Cortex-M0+ Processor and Core Peripherals  =========================== */
#define __CM0PLUS_REV                  0x0201U  /*!< CM0PLUS Core Revision                                                     */
#define __NVIC_PRIO_BITS               2        /*!< Number of Bits used for Priority Levels                                   */
#define __Vendor_SysTickConfig         0        /*!< Set to 1 if different SysTick Config is used                              */
#define __VTOR_PRESENT                 1        /*!< Set to 1 if CPU supports Vector Table Offset Register                     */
#define __MPU_PRESENT                  0        /*!< MPU present or not                                                        */
#define __FPU_PRESENT                  0        /*!< FPU present or not                                                        */


/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm0plus.h"                       /*!< ARM Cortex-M0+ processor and core peripherals                             */
#include "system_cx32l003.h"                    /*!< CX32L003 System                                                           */

/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */


/* =========================================================================================================================== */
/* ================                                            VC                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief VC (VC)
  */

typedef struct {                                /*!< (@ 0x40004080) VC Structure                                               */
  __IO uint32_t  CR0;                          /*!< (@ 0x00000000) VC Control 0                                               */
  __IO uint32_t  CR1;                          /*!< (@ 0x00000004) VC Control 1                                               */
  __IO uint32_t  OUTCFG;                       /*!< (@ 0x00000008) VC Output Config                                           */
  __IO uint32_t  SR;                           /*!< (@ 0x0000000C) VC Status Register                                         */
} VC_TypeDef;                                      /*!< Size = 16 (0x10)                                                          */



/* =========================================================================================================================== */
/* ================                                            LVD                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief LVD (LVD)
  */

typedef struct {                                /*!< (@ 0x40004000) LVD Structure                                              */
  __IO uint32_t  CR;                           /*!< (@ 0x00000000) Control Register                                           */
  __IO uint32_t  SR;                           /*!< (@ 0x00000004) LVD Status                                                 */
} LVD_TypeDef;                                     /*!< Size = 8 (0x8)                                                            */



/* =========================================================================================================================== */
/* ================                                            ADC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief ADC Register (ADC)
  */

typedef struct {                                /*!< (@ 0x40002C00) ADC Structure                                              */
  __IO uint32_t  CR0;                          /*!< (@ 0x00000000) ADC Config Register 0                                      */
  __IO uint32_t  CR1;                          /*!< (@ 0x00000004) ADC Config Register 1                                      */
  __IO uint32_t  CR2;                          /*!< (@ 0x00000008) ADC Config Register2                                       */
  __IO uint32_t  RESULT0;                      /*!< (@ 0x0000000C) Channel 0 Result Register                                  */
  __IO uint32_t  RESULT1;                      /*!< (@ 0x00000010) Channel 1 Result Register                                  */
  __IO uint32_t  RESULT2;                      /*!< (@ 0x00000014) Channel 2 Result Register                                  */
  __IO uint32_t  RESULT3;                      /*!< (@ 0x00000018) Channel 3 Result Register                                  */
  __IO uint32_t  RESULT4;                      /*!< (@ 0x0000001C) Channel 4 Result Register                                  */
  __IO uint32_t  RESULT5;                      /*!< (@ 0x00000020) Channel 5 Result Register                                  */
  __IO uint32_t  RESULT6;                      /*!< (@ 0x00000024) Channel 6 Result Register                                  */
  __IO uint32_t  RESULT7;                      /*!< (@ 0x00000028) Channel 7 Result Register                                  */
  __IO uint32_t  RESULT;                       /*!< (@ 0x0000002C) Channel Result Register                                    */
  __IO uint32_t  RESULT_ACC;                   /*!< (@ 0x00000030) Channel Result accumulate                                  */
  __IO uint32_t  HT;                           /*!< (@ 0x00000034) Compare High Threshold                                     */
  __IO uint32_t  LT;                           /*!< (@ 0x00000038) Compare Low Threshold                                      */
  __I  uint32_t  RESERVED[2];
  __IO uint32_t  INTEN;                        /*!< (@ 0x00000044) Interrupt Enable Register                                  */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x00000048) Interrupt Clear Register                                   */
  __IO uint32_t  RAWINTSR;                     /*!< (@ 0x0000004C) Interrupt Status Register before mask                      */
  __IO uint32_t  MSKINTSR;                     /*!< (@ 0x00000050) Interrupt Status Register Behind mask                      */
} ADC_TypeDef;                                     /*!< Size = 84 (0x54)                                                          */



/* =========================================================================================================================== */
/* ================                                            RTC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief RTC (RTC)
  */

typedef struct {                                /*!< (@ 0x40003000) RTC Structure                                              */
  __IO uint32_t  CR;                           /*!< (@ 0x00000000) CR                                                         */
  __IO uint32_t  CLKCR;                        /*!< (@ 0x00000004) CLKCR                                                      */
  __IO uint32_t  TIME;                         /*!< (@ 0x00000008) TIME                                                       */
  __IO uint32_t  DATE;                         /*!< (@ 0x0000000C) DATE                                                       */
  __IO uint32_t  ALM1TIME;                     /*!< (@ 0x00000010) ALM                                                        */
  __IO uint32_t  ALM1DATE;                     /*!< (@ 0x00000014) ALM                                                        */
  __IO uint32_t  ALM2PRD;                      /*!< (@ 0x00000018) ALM PR                                                     */
  __IO uint32_t  RCLKTRIM;                      /*!< (@ 0x0000001C) CAL                                                        */
  __IO uint32_t  ISR;                          /*!< (@ 0x00000020) Init                                                       */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x00000024) Status Clean                                               */
  __IO uint32_t  WPR;                          /*!< (@ 0x00000028) RTC                                                        */
} RTC_TypeDef;                                     /*!< Size = 44 (0x2c)                                                          */



/* =========================================================================================================================== */
/* ================                                          CLKTRIM                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief CLK_TRIM (CLKTRIM)
  */

typedef struct {                                /*!< (@ 0x40003400) CLKTRIM Structure                                          */
  __IO uint32_t  CR;                           /*!< (@ 0x00000000) Config Register                                            */
  __IO uint32_t  REFCON;                       /*!< (@ 0x00000004) Reference Count Orignal Config Register                    */
  __IO uint32_t  REFCNT;                       /*!< (@ 0x00000008) Reference Count Register                                   */
  __IO uint32_t  CALCNT;                       /*!< (@ 0x0000000C) CAL                                                        */
  __IO uint32_t  IFR;                          /*!< (@ 0x00000010) Interrupt Flag Register                                    */
  __IO uint32_t  ICLR;                         /*!< (@ 0x00000014) Interrupt Flag Clear Register                              */
  __IO uint32_t  CALCON;                       /*!< (@ 0x00000018) Count Overtime Config Register                             */
} CLKTRIM_TypeDef;                                 /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                          OWIRE                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief One Wire (OWIRE)
  */

typedef struct {                                /*!< (@ 0x40003800) OWIRE Structure                                            */
  __IO uint32_t  CR;                           /*!< (@ 0x00000000) 1-Wire Model Control Register                              */
  __IO uint32_t  NFCR;                         /*!< (@ 0x00000004) 1-Wire Input EndPoint Control                              */
  __IO uint32_t  RSTCNT;                       /*!< (@ 0x00000008) 1-Wire Master Reset Pulse Count register                   */
  __IO uint32_t  PRESCNT;                      /*!< (@ 0x0000000C) 1-Wire Device Presence Pulse Count Register                */
  __IO uint32_t  BITRATECNT;                   /*!< (@ 0x00000010) 1-Wire Bit Rate Design Count                               */
  __IO uint32_t  DRVCNT;                       /*!< (@ 0x00000014) 1-Wire Main Read/Write Pull0                               */
  __IO uint32_t  RDSMPCNT;                     /*!< (@ 0x00000018) 1-Wire Main Read Sample Time Setting                       */
  __IO uint32_t  RECCNT;                       /*!< (@ 0x0000001C) 1-Wire Recover Time Count                                  */
  __IO uint32_t  DATA;                         /*!< (@ 0x00000020) 1_Wire Data Register                                       */
  __IO uint32_t  CMD;                          /*!< (@ 0x00000024) 1_Wire Bus Operate Command Register                        */
  __IO uint32_t  INTEN;                        /*!< (@ 0x00000028) 1-Wire Interrupt Enable Register                           */
  __IO uint32_t  SR;                           /*!< (@ 0x0000002C) 1-Wire Status Register                                     */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x00000030) 1-Wire Interrupt Status Clean Register                     */
} OWIRE_TypeDef;                                 /*!< Size = 52 (0x34)                                                          */



/* =========================================================================================================================== */
/* ================                                            SPI                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief SPI Register (SPI)
  */

typedef struct {                                /*!< (@ 0x40000800) SPI Structure                                              */
  __IO uint32_t  CR;                           /*!< (@ 0x00000000) SPI Config Register                                        */
  __IO uint32_t  SSN;                          /*!< (@ 0x00000004) SPI CHIP SELECT CONFIG                                     */
  __IO uint32_t  SR;                           /*!< (@ 0x00000008) SPI Status Register                                        */
  __IO uint32_t  DATA;                         /*!< (@ 0x0000000C) I2C Data register                                          */
} SPI_TypeDef;                                     /*!< Size = 16 (0x10)                                                          */



/* =========================================================================================================================== */
/* ================                                            I2C                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief I2C Register (I2C)
  */

typedef struct {                                /*!< (@ 0x40000C00) I2C Structure                                              */
  __IO uint32_t  CR;                           /*!< (@ 0x00000000) I2C Config Register                                        */
  __IO uint32_t  DATA;                         /*!< (@ 0x00000004) Data                                                       */
  __IO uint32_t  ADDR;                         /*!< (@ 0x00000008) I2C Address Register                                       */
  __IO uint32_t  SR;                           /*!< (@ 0x0000000C) I2C Status register                                        */
  __IO uint32_t  TIMRUN;                       /*!< (@ 0x00000010) I2C Baund Count Enable                                     */
  __IO uint32_t  BAUDCR;                       /*!< (@ 0x00000014) Baud Control Register                                      */
} I2C_TypeDef;                                     /*!< Size = 20 (0x14)                                                          */




/* =========================================================================================================================== */
/* ================                                          LPUART                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief Low Power UART Register (LPUART)
  */

typedef struct {                                /*!< (@ 0x40005000) LPUART Structure                                           */
  __IO uint32_t  SBUF;                         /*!< (@ 0x00000000) Data BUFF                                                  */
  __IO uint32_t  SCON;                         /*!< (@ 0x00000004) Low Power UART Control Register                            */
  __IO uint32_t  SADDR;                        /*!< (@ 0x00000008) UART0_Address Register                                     */
  __IO uint32_t  SADEN;                        /*!< (@ 0x0000000C) UART0_Address Mask Register                                */
  __IO uint32_t  INTSR;                        /*!< (@ 0x00000010) UART0_Interrupt flag Status Register                       */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x00000014) UART0 Interruput flag Clear Register                       */
  __IO uint32_t  BAUDCR;                       /*!< (@ 0x00000018) UART0_ Baud Control Register                               */
} LPUART_TypeDef;                                  /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                           UART                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief UART Register
  */

typedef struct {                                /*!< (@ 0x40000000) UART Structure                                            */
  __IO uint32_t  SCON;                         /*!< (@ 0x00000000) UART Control Register                                     */
  __IO uint32_t  SBUF;                         /*!< (@ 0x00000004) Data BUFF                                                  */
  __IO uint32_t  SADDR;                        /*!< (@ 0x00000008) Address Register                                           */
  __IO uint32_t  SADEN;                        /*!< (@ 0x0000000C) Address Mask Register                                      */
  __IO uint32_t  INTSR;                        /*!< (@ 0x00000010) Interrupt flag Status Register                             */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x00000014) UART Interruput flag Clear Register                       */
  __IO uint32_t  BAUDCR;                       /*!< (@ 0x00000018) Baud Control Register                                      */
  __IO uint32_t  IRDACR;                       /*!< (@ 0x0000001C) UART IrDA Control Register                                */
} UART_TypeDef;                                   /*!< Size = 32 (0x20)                                                          */



/* =========================================================================================================================== */
/* ================                                           WWDG                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Independ Watch Dog (WWDG)
  */

typedef struct {                                /*!< (@ 0x40002000) WWDG Structure                                             */
  __IO uint32_t  RLOAD;                        /*!< (@ 0x00000000) Count ReLoad Register                                      */
  __IO uint32_t  CR;                           /*!< (@ 0x00000004) IWDG Config Register                                       */
  __IO uint32_t  INTEN;                        /*!< (@ 0x00000008) Count ReLoad Register                                      */
  __IO uint32_t  SR;                           /*!< (@ 0x0000000C) WWDG Interrupt Status Register                             */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x00000010) WWDG Interrupt Status Register                             */
  __IO uint32_t  CNTVAL;                       /*!< (@ 0x00000014) Count Value                                                */
} WWDG_TypeDef;                                    /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                           IWDG                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Independ Watch Dog (IWDG)
  */

typedef struct {                                /*!< (@ 0x40002400) IWDG Structure                                             */
  __IO uint32_t  CMDCR;                        /*!< (@ 0x00000000) IWDG Control Command Register                              */
  __IO uint32_t  CFGR;                         /*!< (@ 0x00000004) IWDG Config Register                                       */
  __IO uint32_t  RLOAD;                        /*!< (@ 0x00000008) Count ReLoad Register                                      */
  __IO uint32_t  CNTVAL;                       /*!< (@ 0x0000000C) Count Value                                                */
  __IO uint32_t  SR;                           /*!< (@ 0x00000010) IWDG Interrupt Status Register                             */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x00000014) IWDG Interrupt Status Register                             */
  __IO uint32_t  UNLOCK;                       /*!< (@ 0x00000018) IWDG register Writer Protect                               */
} IWDG_TypeDef;                                    /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                           BEEP                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief BEEP (BEEP)
  */

typedef struct {                                /*!< (@ 0x40004800) BEEP Structure                                             */
  __IO uint32_t  CSR;                          /*!< (@ 0x00000000) BEEP Control Status Register                               */
} BEEP_TypeDef;                                    /*!< Size = 4 (0x4)                                                            */



/* =========================================================================================================================== */
/* ================                                            AWK                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Auto wake (AWK)
  */

typedef struct {                                /*!< (@ 0x40002800) AWK Structure                                              */
  __IO uint32_t  CR;                           /*!< (@ 0x00000000) Auto Wake Timer Control Register                           */
  __IO uint32_t  RLOAD;                        /*!< (@ 0x00000004) Auto Wake Timer ReLoad Data Register                       */
  __IO uint32_t  SR;                           /*!< (@ 0x00000008) Auto Wake Timer Status Register                            */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x0000000C) Auto Wake Interrupt Clear Register                         */
} AWK_TypeDef;                                     /*!< Size = 16 (0x10)                                                          */



/* =========================================================================================================================== */
/* ================                                           LPTIM                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief Low Power Timer (LPTIM)
  */

typedef struct {                                /*!< (@ 0x40004400) LPTIM Structure                                            */
  __IO uint32_t  CNTVAL;                       /*!< (@ 0x00000000) Low Power Count Read_Only Register                         */
  __IO uint32_t  CR;                           /*!< (@ 0x00000004) LPTIM Control Register                                     */
  __IO uint32_t  LOAD;                         /*!< (@ 0x00000008) LPTIM Reload Register                                      */
  __IO uint32_t  INTSR;                        /*!< (@ 0x0000000C) LPTIM Interrupt Status                                     */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x00000010) LPTIM Interrupt Clear Register                             */
  __IO uint32_t  BGLOAD;                       /*!< (@ 0x00000014) LPTIM Circle reload Register                               */
} LPTIM_TypeDef;                                   /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                           BASETIM                                        ================ */
/* =========================================================================================================================== */


/**
  * @brief BASE_TIMER 
  */

typedef struct {                               /*!< (@ 0x40001800) BASETIM Structure                                          */
  __IO uint32_t  CR;                           /*!< (@ 0x00000000) BASETIM Control Register                                   */
  __IO uint32_t  LOAD;                         /*!< (@ 0x00000004) 32bits Auto Load Register                                  */
  __IO uint32_t  CNT;                          /*!< (@ 0x00000008) Read Count Register，Only Read                             */
  __IO uint32_t  RAWINTSR;                     /*!< (@ 0x0000000C) READ Orignal Interrupt Register                            */
  __IO uint32_t  MSKINTSR;                     /*!< (@ 0x00000010) Read Interrupt Register                                    */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x00000014) Interrupt Clear Register                                   */
  __IO uint32_t  BGLOAD;                       /*!< (@ 0x00000018) 32Bits Circles Reload Register                             */
} BASETIM_TypeDef;                             /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                            PCA                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief PCA (PCA)
  */

typedef struct {                                /*!< (@ 0x40001400) PCA Structure                                              */
  __IO uint32_t  CR;                           /*!< (@ 0x00000000) Control Register                                           */
  __IO uint32_t  MOD;                          /*!< (@ 0x00000004) Mode Register                                              */
  __IO uint32_t  CNT;                          /*!< (@ 0x00000008) PCA Count Register                                         */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x0000000C) PCA Interrupt Clear Register                               */
  __IO uint32_t  CCAPM0;                       /*!< (@ 0x00000010) PCA Captuer/Compare Model 0 Mode Register                  */
  __IO uint32_t  CCAPM1;                       /*!< (@ 0x00000014) PCA Captuer/Compare Model 0 Mode Register                  */
  __IO uint32_t  CCAPM2;                       /*!< (@ 0x00000018) PCA Captuer/Compare Model 0 Mode Register                  */
  __IO uint32_t  CCAPM3;                       /*!< (@ 0x0000001C) PCA Captuer/Compare Model 0 Mode Register                  */
  __IO uint32_t  CCAPM4;                       /*!< (@ 0x00000020) PCA Captuer/Compare Model 0 Mode Register                  */
  __I  uint32_t  RESERVED[3];
  __IO uint32_t  CCAP0L;                       /*!< (@ 0x00000030) PCA Capture/Compare Model0 Low 8 bits Register             */
  __IO uint32_t  CCAP0H;                       /*!< (@ 0x00000034) PCA Capture/Compare Model0 High 8 bits Register            */
  __IO uint32_t  CCAP1L;                       /*!< (@ 0x00000038) PCA Capture/Compare Model 1 Low 8 bits Register            */
  __IO uint32_t  CCAP1H;                       /*!< (@ 0x0000003C) PCA Capture/Compare Model 1 High 8 bits Register           */
  __IO uint32_t  CCAP2L;                       /*!< (@ 0x00000040) PCA Capture/Compare Model 2 Low 8 bits Register            */
  __IO uint32_t  CCAP2H;                       /*!< (@ 0x00000044) PCA Capture/Compare Model 2 High 8 bits Register           */
  __IO uint32_t  CCAP3L;                       /*!< (@ 0x00000048) PCA Capture/Compare Model 3 Low 8 bits Register            */
  __IO uint32_t  CCAP3H;                       /*!< (@ 0x0000004C) PCA Capture/Compare Model 3 High 8 bits Register           */
  __IO uint32_t  CCAP4L;                       /*!< (@ 0x00000050) PCA Capture/Compare Model 4 Low 8 bits Register            */
  __IO uint32_t  CCAP4H;                       /*!< (@ 0x00000054) PCA Capture/Compare Model 4 High 8 bits Register           */
  __IO uint32_t  CCAPO;                        /*!< (@ 0x00000058) PCA EndPoint Output Control Register                       */
  __IO uint32_t  POCR;                         /*!< (@ 0x0000005C) PCA EndPoint Output Control Register                       */
  __IO uint32_t  CCAP0;                        /*!< (@ 0x00000060) PCA Capture/Compare Model0 16 bits Register                */
  __IO uint32_t  CCAP1;                        /*!< (@ 0x00000064) PCA Capture/Compare Model 1 16 bits Register               */
  __IO uint32_t  CCAP2;                        /*!< (@ 0x00000068) PCA Capture/Compare Model 2 16 bits Register               */
  __IO uint32_t  CCAP3;                        /*!< (@ 0x0000006C) PCA Capture/Compare Model 3 16 bits Register               */
  __IO uint32_t  CCAP4;                        /*!< (@ 0x00000070) PCA Capture/Compare Model 4 16 bits Register               */
} PCA_TypeDef;                                     /*!< Size = 116 (0x74)                                                         */



/* =========================================================================================================================== */
/* ================                                 Advance Timer                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief Advance Timer 
  */

typedef struct {                                /*!< (@ 0x40001000) TIM Structure                                             */
  __IO uint32_t  CR1;                          /*!< (@ 0x00000000) TIM Control Register1                                     */
  __IO uint32_t  CR2;                          /*!< (@ 0x00000004) TIM Control Register 2                                    */
  __IO uint32_t  SMCR;                         /*!< (@ 0x00000008) TIM Slave mode Control Register                           */
  __IO uint32_t  DIER;                         /*!< (@ 0x0000000C) TIM Interrupt Enable Register                             */
  __IO uint32_t  SR;                           /*!< (@ 0x00000010) TIM Status Register                                       */
  __IO uint32_t  EGR;                          /*!< (@ 0x00000014) TIM Event Trig Register                                   */
  __IO uint32_t  CCMR1;                        /*!< (@ 0x00000018) TIM Capture/Compare Mode Register 1                       */
  __IO uint32_t  CCMR2;                        /*!< (@ 0x0000001C) TIM Capture/Compare Mode Register 2                       */
  __IO uint32_t  CCER;                         /*!< (@ 0x00000020) TIM Captuer/Compare Enable Register                       */
  __IO uint32_t  CNT;                          /*!< (@ 0x00000024) TIM Count                                                 */
  __IO uint32_t  PSC;                          /*!< (@ 0x00000028) TIM Prescale Register                                     */
  __IO uint32_t  ARR;                          /*!< (@ 0x0000002C) TIM Auto Load Register                                    */
  __IO uint32_t  RCR;                          /*!< (@ 0x00000030) TIM Repeate Count Register                                */
  __IO uint32_t  CCR1;                         /*!< (@ 0x00000034) Captuer/Compare Register1                                  */
  __IO uint32_t  CCR2;                         /*!< (@ 0x00000038) Capture/Compare Register2                                  */
  __IO uint32_t  CCR3;                         /*!< (@ 0x0000003C) Capture/Compare Register3                                  */
  __IO uint32_t  CCR4;                         /*!< (@ 0x00000040) TIM Capture/Compare Register4                             */
  __IO uint32_t  BDTR;                         /*!< (@ 0x00000044) TIM Brush and DEAD Register                               */
} TIM_TypeDef;                                    /*!< Size = 72 (0x48)                                                          */



/* =========================================================================================================================== */
/* ================                                            CRC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief CRC_Register (CRC)
  */

typedef struct {                               /*!< (@ 0x40020800) CRC Structure                                              */
  __I  uint32_t  RESERVED;
  __IO uint32_t  RESULT;                       /*!< (@ 0x00000004) RESULT_Register                                            */
} CRC_TypeDef;                                 /*!< Size = 8 (0x8)                                                            */



/* =========================================================================================================================== */
/* ================                                           FLASH                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief Flash Controller (FLASH)
  */

typedef struct {                                /*!< (@ 0x40020400) FLASH Structure                                            */
  __IO uint32_t  CR;                           /*!< (@ 0x00000000) Control Register                                           */
  __IO uint32_t  IFR;                          /*!< (@ 0x00000004) Interrupt flag Register                                    */
  __IO uint32_t  ICLR;                         /*!< (@ 0x00000008) Interrupt Flag Clear Register                              */
  __IO uint32_t  BYPASS;                       /*!< (@ 0x0000000C) 0X5A5A-0XA5A5 sequence Register                            */
  __IO uint32_t  SLOCK0;                       /*!< (@ 0x00000010) Sector Write Protect Register0                             */
  __IO uint32_t  SLOCK1;                       /*!< (@ 0x00000014) Sector Write Protect Register1                             */
  __IO uint32_t  ISPCON;                       /*!< (@ 0x00000018) Flash ISP Control register                                 */
} FLASH_TypeDef;                                   /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                           GPIO                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief GPIO register list 
  */

typedef struct {                                /*!< (@ 0x40021000) GPIO Structure                                             */
  __IO uint32_t  DIRCR;                        /*!< (@ 0x00000000) Input Output model Register                                */
  __IO uint32_t  OTYPER;                       /*!< (@ 0x00000004) Output Type register                                       */
  __IO uint32_t  ODR;                          /*!< (@ 0x00000008) Output Data Register                                       */
  __IO uint32_t  IDR;                          /*!< (@ 0x0000000C) Input Data Register                                        */
  __IO uint32_t  INTEN;                        /*!< (@ 0x00000010) Inerrupt Enable Register                                   */
  __IO uint32_t  RAWINTST;                     /*!< (@ 0x00000014) Interrupt Raw Status register                              */
  __IO uint32_t  MSKINTSR;                     /*!< (@ 0x00000018) Interrupt Status Register                                  */
  __IO uint32_t  INTCLR;                       /*!< (@ 0x0000001C) Interrupt Clear Register                                   */
  __IO uint32_t  INTTYPCR;                     /*!< (@ 0x00000020) Interrupt Style Register                                   */
  __IO uint32_t  INTPOLCR;                     /*!< (@ 0x00000024) Interrupt Sytle Value Register                             */
  __IO uint32_t  INTANY;                       /*!< (@ 0x00000028) Edge Trigger Interrupt Register                            */
  __IO uint32_t  ODSET;                        /*!< (@ 0x0000002C) Output Setting Register                                    */
  __IO uint32_t  ODCLR;                        /*!< (@ 0x00000030) Output Clear Register                                      */
  __IO uint32_t  INDBEN;                       /*!< (@ 0x00000034) Input Debounce and synchronous Enable Register             */
  __IO uint32_t  DBCLKCR;                      /*!< (@ 0x00000038) Input Debounce clock Config register                       */
  __IO uint32_t  PUPDR;                        /*!< (@ 0x0000003C) PullUp and PullDown Register                               */
  __IO uint32_t  SLEWCR;                       /*!< (@ 0x00000040) Voltage Convertion Speed Control                           */
  __IO uint32_t  DRVCR;                        /*!< (@ 0x00000044) Driver Strength Config                                     */
  __IO uint32_t  AFR;                          /*!< (@ 0x00000048) Multiplex Function Register                                */
} GPIO_TypeDef;                                   /*!< Size = 76 (0x4c)                                                          */



/* =========================================================================================================================== */
/* ================                                          SYSCON                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief system control config (SYSCON)
  */

typedef struct {                                /*!< (@ 0x40001C00) SYSCON Structure                                           */
  __IO uint32_t  CFGR0;                        /*!< (@ 0x00000000) System Control setting regist 0                            */
  __IO uint32_t  PORTINTCR;                    /*!< (@ 0x00000004) PORT INTERRUPT MODE SETTING                                */
  __IO uint32_t  PORTCR;                       /*!< (@ 0x00000008) PORT control register                                      */
  __IO uint32_t  PCACR;                        /*!< (@ 0x0000000C) PCA Capture channel source select                          */
  __IO uint32_t  TIM1CR;                       /*!< (@ 0x00000010) TIM1 Channel Source Select                                 */
  __IO uint32_t  TIM2CR;                       /*!< (@ 0x00000014) TIM2 Channel Source Select                                 */
  __I  uint32_t  RESERVED[14];
  __IO uint32_t  UNLOCK;                       /*!< (@ 0x00000050) Syscon Register Write Enable                               */
} SYSCON_TypeDef;                              /*!< Size = 84 (0x54)                                                          */



/* =========================================================================================================================== */
/* ================                                            RCC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief System RCC (RCC)
  */

typedef struct {                                /*!< (@ 0x40020000) RCC Structure                                              */
  __IO uint32_t  HCLKDIV;                      /*!< (@ 0x00000000) AHB CLK Prescale                                           */
  __IO uint32_t  PCLKDIV;                      /*!< (@ 0x00000004) APB CLK Prescale                                           */
  __IO uint32_t  HCLKEN;                       /*!< (@ 0x00000008) AHB Peripheral Model Clk Enable                            */
  __IO uint32_t  PCLKEN;                       /*!< (@ 0x0000000C) APB Peripheral Model CLK Enable                            */
  __IO uint32_t  MCOCR;                        /*!< (@ 0x00000010) Clock Output Control Register                              */
  __I  uint32_t  RESERVED;
  __IO uint32_t  RSTCR;                        /*!< (@ 0x00000018) System Reset Control                                       */
  __IO uint32_t  RSTSR;                        /*!< (@ 0x0000001C) Reset Status                                               */
  __IO uint32_t  SYSCLKCR;                     /*!< (@ 0x00000020) CLK Setting                                                */
  __IO uint32_t  SYSCLKSEL;                    /*!< (@ 0x00000024) System Clock Select                                        */
  __IO uint32_t  HIRCCR;                       /*!< (@ 0x00000028) HIRC Control                                               */
  __IO uint32_t  HXTCR;                        /*!< (@ 0x0000002C) HXT Control                                                */
  __IO uint32_t  LIRCCR;                       /*!< (@ 0x00000030) LIRC Control                                               */
  __IO uint32_t  LXTCR;                        /*!< (@ 0x00000034) LXT Control                                                */
  __IO uint32_t  IRQLATENCY;                   /*!< (@ 0x00000038) M0 IRQ Delay                                               */
  __IO uint32_t  STICKCR;                      /*!< (@ 0x0000003C) SysTick Timer Circle Adjust                                */
  __IO uint32_t  SWDIOCR;                      /*!< (@ 0x00000040) Endpoint Function Select                                   */
  __IO uint32_t  PERIRST;                      /*!< (@ 0x00000044) Peripheral Model Control                                   */
  __IO uint32_t  RTCRST;                       /*!< (@ 0x00000048) RTC Control                                                */
  __I  uint32_t  RESERVED1[5];
  __IO uint32_t  UNLOCK;                       /*!< (@ 0x00000060) Register Protect                                           */
} RCC_TypeDef;                                     /*!< Size = 100 (0x64)                                                         */


/* =========================================================================================================================== */
/* ================                                          DBG                                              ================ */
/* =========================================================================================================================== */


/**
  * @brief Debug MCU Module
  */

typedef struct {															/*!< (@ 0x40004C00U) DBG Structure                                               */
  __IO uint32_t APBFZ;												/*!< (@ 0x00000000) APB Module Freeze                                            */
}DBG_TypeDef;																	/*!< Size = 4 (0x4)                                                              */


/** @} */ /* End of group Device_Peripheral_peripherals */


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

#define VC_BASE                     0x40004080UL
#define LVD_BASE                    0x40004000UL
#define ADC_BASE                    0x40002C00UL
#define RTC_BASE                    0x40003000UL
#define CLKTRIM_BASE                0x40003400UL
#define OWIRE_BASE                  0x40003800UL
#define SPI_BASE                    0x40000800UL
#define I2C_BASE                    0x40000C00UL
#define LPUART_BASE                 0x40005000UL
#define UART0_BASE                  0x40000000UL
#define UART1_BASE                  0x40000400UL
#define WWDG_BASE                   0x40002000UL
#define IWDG_BASE                   0x40002400UL
#define BEEP_BASE                   0x40004800UL
#define AWK_BASE                    0x40002800UL
#define LPTIM_BASE                  0x40004400UL
#define TIM10_BASE                  0x40001800UL
#define TIM11_BASE                  0x40001900UL
#define PCA_BASE                    0x40001400UL
#define TIM1_BASE                   0x40001000UL
#define TIM2_BASE                   0x40003C00UL
#define CRC_BASE                    0x40020800UL
#define FLASH_BASE                  0x40020400UL
#define GPIOA_BASE                  0x40021000UL
#define GPIOB_BASE                  0x40021400UL
#define GPIOC_BASE                  0x40021800UL
#define GPIOD_BASE                  0x40021C00UL
#define SYSCON_BASE                 0x40001C00UL
#define RCC_BASE                    0x40020000UL
#define SCR_BASE                    0xE000ED10UL
#define DBG_BASE          				  0x40004C00UL

#define FLASH_MEMORY_BASE           0x00000000UL 		/*!< FLASH(up to 64 KB) base address in the alias region  */
#define SRAM_MEMORY_BASE            0x20000000UL 		/*!< SRAM1(4 KB) base address in the alias region         */
#define UID_BASE              			0x180000F0UL    /*!< Unique device ID register base address 							*/

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define VC                          ((VC_TypeDef*)                VC_BASE)
#define LVD                         ((LVD_TypeDef*)               LVD_BASE)
#define ADC                         ((ADC_TypeDef*)               ADC_BASE)
#define RTC                         ((RTC_TypeDef*)               RTC_BASE)
#define CLKTRIM                     ((CLKTRIM_TypeDef*)           CLKTRIM_BASE)
#define OWIRE                       ((OWIRE_TypeDef*)             OWIRE_BASE)
#define SPI                         ((SPI_TypeDef*)               SPI_BASE)
#define I2C                         ((I2C_TypeDef*)               I2C_BASE)
#define LPUART                      ((LPUART_TypeDef*)            LPUART_BASE)
#define UART0                       ((UART_TypeDef*)              UART0_BASE)
#define UART1                       ((UART_TypeDef*)              UART1_BASE)
#define WWDG                        ((WWDG_TypeDef*)              WWDG_BASE)
#define IWDG                        ((IWDG_TypeDef*)              IWDG_BASE)
#define BEEP                        ((BEEP_TypeDef*)              BEEP_BASE)
#define AWK                         ((AWK_TypeDef*)               AWK_BASE)
#define LPTIM                       ((LPTIM_TypeDef*)             LPTIM_BASE)
#define TIM10                       ((BASETIM_TypeDef*)           TIM10_BASE)
#define TIM11                       ((BASETIM_TypeDef*)           TIM11_BASE)
#define PCA                         ((PCA_TypeDef*)               PCA_BASE)
#define TIM1                        ((TIM_TypeDef*)            		TIM1_BASE)
#define TIM2                        ((TIM_TypeDef*)            		TIM2_BASE)
#define CRC                         ((CRC_TypeDef*)               CRC_BASE)
#define FLASH                       ((FLASH_TypeDef*)             FLASH_BASE)
#define GPIOA                       ((GPIO_TypeDef*)              GPIOA_BASE)
#define GPIOB                       ((GPIO_TypeDef*)              GPIOB_BASE)
#define GPIOC                       ((GPIO_TypeDef*)              GPIOC_BASE)
#define GPIOD                       ((GPIO_TypeDef*)              GPIOD_BASE)
#define SYSCON                      ((SYSCON_TypeDef*)            SYSCON_BASE)
#define RCC                         ((RCC_TypeDef*)               RCC_BASE)
#define DBG              					  ((DBG_TypeDef *)							DBG_BASE)

/** @} */ /* End of group Device_Peripheral_declaration */


/* =========================================================================================================================== */
/* ================                                Pos/Mask Peripheral Section                                ================ */
/* =========================================================================================================================== */


/** @addtogroup PosMask_peripherals
  * @{
  */

/* =========================================================================================================================== */
/* ================                                            DBG                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  APBFZ  ========================================================= */
#define DBG_APBFZ_TIM10DBGSTOP_Pos        (0UL)                     /*!< DBG APBFZ: TIM10DBGSTOP (Bit 0)                       */
#define DBG_APBFZ_TIM10DBGSTOP_Msk        (0x1UL)                   /*!< DBG APBFZ: TIM10DBGSTOP (Bitfield-Mask: 0x01)         */
#define DBG_APBFZ_TIM11DBGSTOP_Pos        (1UL)                     /*!< DBG APBFZ: TIM11DBGSTOP (Bit 1)                       */
#define DBG_APBFZ_TIM11DBGSTOP_Msk        (0x1UL)                   /*!< DBG APBFZ: TIM11DBGSTOP (Bitfield-Mask: 0x01)         */
#define DBG_APBFZ_LPTIMDBGSTOP_Pos        (2UL)                     /*!< DBG APBFZ: LPTIMDBGSTOP (Bit 2)                       */
#define DBG_APBFZ_LPTIMDBGSTOP_Msk        (0x1UL)                   /*!< DBG APBFZ: LPTIMDBGSTOP (Bitfield-Mask: 0x01)         */
#define DBG_APBFZ_PCADBGSTOP_Pos          (4UL)                     /*!< DBG APBFZ: PCADBGSTOP 	 (Bit 4)                       */
#define DBG_APBFZ_PCADBGSTOP_Msk          (0x1UL)                   /*!< DBG APBFZ: PCADBGSTOP 	 (Bitfield-Mask: 0x01)         */
#define DBG_APBFZ_TIM1DBGSTOP_Pos         (5UL)                     /*!< DBG APBFZ: TIM1DBGSTOP  (Bit 5)                       */
#define DBG_APBFZ_TIM1DBGSTOP_Msk         (0x1UL)                   /*!< DBG APBFZ: TIM1DBGSTOP  (Bitfield-Mask: 0x01)         */
#define DBG_APBFZ_RTCDBGSTOP_Pos          (6UL)                     /*!< DBG APBFZ: RTCDBGSTOP 	 (Bit 6)                       */
#define DBG_APBFZ_RTCDBGSTOP_Msk          (0x1UL)                   /*!< DBG APBFZ: RTCDBGSTOP 	 (Bitfield-Mask: 0x01)         */
#define DBG_APBFZ_BEEPDBGSTOP_Pos         (8UL)                     /*!< DBG APBFZ: BEEPDBGSTOP  (Bit 8)                       */
#define DBG_APBFZ_BEEPDBGSTOP_Msk         (0x1UL)                   /*!< DBG APBFZ: BEEPDBGSTOP  (Bitfield-Mask: 0x01)         */
#define DBG_APBFZ_IWDGDBGSTOP_Pos         (9UL)                     /*!< DBG APBFZ: IWDGDBGSTOP  (Bit 9)                       */
#define DBG_APBFZ_IWDGDBGSTOP_Msk         (0x1UL)                   /*!< DBG APBFZ: IWDGDBGSTOP  (Bitfield-Mask: 0x01)         */
#define DBG_APBFZ_WWDGDBGSTOP_Pos         (10UL)                    /*!< DBG APBFZ: WWDGDBGSTOP  (Bit 10)                      */
#define DBG_APBFZ_WWDGDBGSTOP_Msk         (0x1UL)                   /*!< DBG APBFZ: WWDGDBGSTOP  (Bitfield-Mask: 0x01)         */
#define DBG_APBFZ_TIM2DBGSTOP_Pos         (11UL)                  	/*!< DBG APBFZ: TIM2DBGSTOP  (Bit 11)                      */
#define DBG_APBFZ_TIM2DBGSTOP_Msk         (0x1UL)                 	/*!< DBG APBFZ: TIM2DBGSTOP  (Bitfield-Mask: 0x01)         */
#define DBG_APBFZ_KEY_Pos         				(16UL)                  	/*!< DBG APBFZ: KEY  				 (Bit 16)                      */
#define DBG_APBFZ_KEY_Msk         				(0xFFUL)                 	/*!< DBG APBFZ: KEY  				 (Bitfield-Mask: 0xFF)         */

/* =========================================================================================================================== */
/* ================                                            VC                                             ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR0  ========================================================== */
#define VC_CR0_PINSEL_Pos                 (0UL)                     /*!< VC CR0: PINSEL (Bit 0)                                */
#define VC_CR0_PINSEL_Msk                 (0x3UL)                   /*!< VC CR0: PINSEL (Bitfield-Mask: 0x03)                  */
#define VC_CR0_NINSEL_Pos                 (2UL)                     /*!< VC CR0: NINSEL (Bit 2)                                */
#define VC_CR0_NINSEL_Msk                 (0xcUL)                   /*!< VC CR0: NINSEL (Bitfield-Mask: 0x03)                  */
#define VC_CR0_V25DIV_Pos                 (4UL)                     /*!< VC CR0: V25DIV (Bit 4)                                */
#define VC_CR0_V25DIV_Msk                 (0x30UL)                  /*!< VC CR0: V25DIV (Bitfield-Mask: 0x03)                  */
#define VC_CR0_V25DIV_EN_Pos              (6UL)                     /*!< VC CR0: V25DIV_EN (Bit 6)                             */
#define VC_CR0_V25DIV_EN_Msk              (0x40UL)                  /*!< VC CR0: V25DIV_EN (Bitfield-Mask: 0x01)               */
#define VC_CR0_V25DIV_EN                   VC_CR0_V25DIV_EN_Msk
/* ==========================================================  CR1  ========================================================== */
#define VC_CR1_VCEN_Pos                   (0UL)                     /*!< VC CR1: VCEN (Bit 0)                                  */
#define VC_CR1_VCEN_Msk                   (0x1UL)                   /*!< VC CR1: VCEN (Bitfield-Mask: 0x01)                    */
#define VC_CR1_VCEN                         VC_CR1_VCEN_Msk 
#define VC_CR1_VC_FLTCLK_SEL_Pos          (2UL)                     /*!< VC CR1: VC_FLTCLK_SEL (Bit 2)                         */
#define VC_CR1_VC_FLTCLK_SEL_Msk          (0xcUL)                   /*!< VC CR1: VC_FLTCLK_SEL (Bitfield-Mask: 0x03)           */
#define VC_CR1_VC_FLTCLK_SEL          		VC_CR1_VC_FLTCLK_SEL_Msk 
#define VC_CR1_FLTEN_Pos                  (8UL)                     /*!< VC CR1: FLTEN (Bit 8)                                 */
#define VC_CR1_FLTEN_Msk                  (0x100UL)                 /*!< VC CR1: FLTEN (Bitfield-Mask: 0x01)                   */
#define VC_CR1_FLTEN                       VC_CR1_FLTEN_Msk  
#define VC_CR1_FALLINTEN_Pos              (12UL)                    /*!< VC CR1: FALLINTEN (Bit 12)                            */
#define VC_CR1_FALLINTEN_Msk              (0x1000UL)                /*!< VC CR1: FALLINTEN (Bitfield-Mask: 0x01)               */
#define VC_CR1_FALLINTEN                  VC_CR1_FALLINTEN_Msk 
#define VC_CR1_RISEINTEN_Pos              (13UL)                    /*!< VC CR1: RISEINTEN (Bit 13)                            */
#define VC_CR1_RISEINTEN_Msk              (0x2000UL)                /*!< VC CR1: RISEINTEN (Bitfield-Mask: 0x01)               */
#define VC_CR1_RISEINTEN                  VC_CR1_RISEINTEN_Msk 
#define VC_CR1_HIGHINTEN_Pos              (14UL)                    /*!< VC CR1: HIGHINTEN (Bit 14)                            */
#define VC_CR1_HIGHINTEN_Msk              (0x4000UL)                /*!< VC CR1: HIGHINTEN (Bitfield-Mask: 0x01)               */
#define VC_CR1_HIGHINTEN                  VC_CR1_HIGHINTEN_Msk                    
#define VC_CR1_INT_EN_Pos                 (15UL)                    /*!< VC CR1: INT_EN (Bit 15)                               */
#define VC_CR1_INT_EN_Msk                 (0x8000UL)                /*!< VC CR1: INT_EN (Bitfield-Mask: 0x01)                  */
#define VC_CR1_INT_EN                      VC_CR1_INT_EN_Msk  
#define VC_CR1_FLT_NUM_Pos                (16UL)                    /*!< VC CR1: FLT_NUM (Bit 16)                              */
#define VC_CR1_FLT_NUM_Msk                (0xffff0000UL)            /*!< VC CR1: FLT_NUM (Bitfield-Mask: 0xffff)               */
/* ========================================================  OUTCFG  ========================================================= */
#define VC_OUTCFG_INV_TIMX_Pos            (0UL)                     /*!< VC OUTCFG: INV_TIMX (Bit 0)                           */
#define VC_OUTCFG_INV_TIMX_Msk            (0x1UL)                   /*!< VC OUTCFG: INV_TIMX (Bitfield-Mask: 0x01)             */
#define VC_OUTCFG_TIM0_EN_Pos             (1UL)                     /*!< VC OUTCFG: TIM0_EN (Bit 1)                            */
#define VC_OUTCFG_TIM0_EN_Msk             (0x2UL)                   /*!< VC OUTCFG: TIM0_EN (Bitfield-Mask: 0x01)              */
#define VC_OUTCFG_TIM1_EN_Pos             (2UL)                     /*!< VC OUTCFG: TIM1_EN (Bit 2)                            */
#define VC_OUTCFG_TIM1_EN_Msk             (0x4UL)                   /*!< VC OUTCFG: TIM1_EN (Bitfield-Mask: 0x01)              */
#define VC_OUTCFG_LPTIM_EN_Pos            (4UL)                     /*!< VC OUTCFG: LPTIM_EN (Bit 4)                           */
#define VC_OUTCFG_LPTIM_EN_Msk            (0x10UL)                  /*!< VC OUTCFG: LPTIM_EN (Bitfield-Mask: 0x01)             */
#define VC_OUTCFG_LPTIMEXT_EN_Pos         (5UL)                     /*!< VC OUTCFG: LPTIMEXT_EN (Bit 5)                        */
#define VC_OUTCFG_LPTIMEXT_EN_Msk         (0x20UL)                  /*!< VC OUTCFG: LPTIMEXT_EN (Bitfield-Mask: 0x01)          */
#define VC_OUTCFG_INV_PCA_Pos             (6UL)                     /*!< VC OUTCFG: INV_PCA (Bit 6)                            */
#define VC_OUTCFG_INV_PCA_Msk             (0x40UL)                  /*!< VC OUTCFG: INV_PCA (Bitfield-Mask: 0x01)              */
#define VC_OUTCFG_PCACAP0_EN_Pos          (7UL)                     /*!< VC OUTCFG: PCACAP0_EN (Bit 7)                         */
#define VC_OUTCFG_PCACAP0_EN_Msk          (0x80UL)                  /*!< VC OUTCFG: PCACAP0_EN (Bitfield-Mask: 0x01)           */
#define VC_OUTCFG_PCAECI_EN_Pos           (8UL)                     /*!< VC OUTCFG: PCAECI_EN (Bit 8)                          */
#define VC_OUTCFG_PCAECI_EN_Msk           (0x100UL)                 /*!< VC OUTCFG: PCAECI_EN (Bitfield-Mask: 0x01)            */
#define VC_OUTCFG_INV_TM1CH1_Pos          (9UL)                     /*!< VC OUTCFG: INV_TM1CH1 (Bit 9)                         */
#define VC_OUTCFG_INV_TM1CH1_Msk          (0x200UL)                 /*!< VC OUTCFG: INV_TM1CH1 (Bitfield-Mask: 0x01)           */
#define VC_OUTCFG_TM1CH1_EN_Pos           (10UL)                    /*!< VC OUTCFG: TM1CH1_EN (Bit 10)                         */
#define VC_OUTCFG_TM1CH1_EN_Msk           (0x400UL)                 /*!< VC OUTCFG: TM1CH1_EN (Bitfield-Mask: 0x01)            */
#define VC_OUTCFG_INV_TM1CH2_Pos          (11UL)                    /*!< VC OUTCFG: INV_TM1CH2 (Bit 11)                        */
#define VC_OUTCFG_INV_TM1CH2_Msk          (0x800UL)                 /*!< VC OUTCFG: INV_TM1CH2 (Bitfield-Mask: 0x01)           */
#define VC_OUTCFG_TM1CH2_EN_Pos           (12UL)                    /*!< VC OUTCFG: TM1CH2_EN (Bit 12)                         */
#define VC_OUTCFG_TM1CH2_EN_Msk           (0x1000UL)                /*!< VC OUTCFG: TM1CH2_EN (Bitfield-Mask: 0x01)            */
#define VC_OUTCFG_INV_TM1CH3_Pos          (13UL)                    /*!< VC OUTCFG: INV_TM1CH3 (Bit 13)                        */
#define VC_OUTCFG_INV_TM1CH3_Msk          (0x2000UL)                /*!< VC OUTCFG: INV_TM1CH3 (Bitfield-Mask: 0x01)           */
#define VC_OUTCFG_TIM1CH3_EN_Pos          (14UL)                    /*!< VC OUTCFG: TIM1CH3_EN (Bit 14)                        */
#define VC_OUTCFG_TIM1CH3_EN_Msk          (0x4000UL)                /*!< VC OUTCFG: TIM1CH3_EN (Bitfield-Mask: 0x01)           */
#define VC_OUTCFG_INV_TM1CH4_Pos          (15UL)                    /*!< VC OUTCFG: INV_TM1CH4 (Bit 15)                        */
#define VC_OUTCFG_INV_TM1CH4_Msk          (0x8000UL)                /*!< VC OUTCFG: INV_TM1CH4 (Bitfield-Mask: 0x01)           */
#define VC_OUTCFG_TM1CH3_EN_Pos           (16UL)                    /*!< VC OUTCFG: TM1CH3_EN (Bit 16)                         */
#define VC_OUTCFG_TM1CH3_EN_Msk           (0x10000UL)               /*!< VC OUTCFG: TM1CH3_EN (Bitfield-Mask: 0x01)            */
#define VC_OUTCFG_TM1BKE_Pos              (17UL)                    /*!< VC OUTCFG: TM1BKE (Bit 17)                            */
#define VC_OUTCFG_TM1BKE_Msk              (0x20000UL)               /*!< VC OUTCFG: TM1BKE (Bitfield-Mask: 0x01)               */
#define VC_OUTCFG_INV_PAD_Pos             (18UL)                    /*!< VC OUTCFG: INV_PAD (Bit 18)                           */
#define VC_OUTCFG_INV_PAD_Msk             (0x40000UL)               /*!< VC OUTCFG: INV_PAD (Bitfield-Mask: 0x01)              */
/* ==========================================================  SR  =========================================================== */
#define VC_SR_INTF_Pos                    (0UL)                     /*!< VC SR: INTF (Bit 0)                                   */
#define VC_SR_INTF_Msk                    (0x1UL)                   /*!< VC SR: INTF (Bitfield-Mask: 0x01)                     */
#define VC_SR_INTF                        VC_SR_INTF_Msk
#define VC_SR_VC_FLOUT_Pos                (1UL)                     /*!< VC SR: VC_FLOUT (Bit 1)                               */
#define VC_SR_VC_FLOUT_Msk                (0x2UL)                   /*!< VC SR: VC_FLOUT (Bitfield-Mask: 0x01)                 */
#define VC_SR_VC_FLOUT                 		VC_SR_VC_FLOUT_Msk

/* =========================================================================================================================== */
/* ================                                            LVD                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define LVD_CR_DIV_SEL_Pos                (0UL)                     /*!< LVD CR: DIV_SEL (Bit 0)                               */
#define LVD_CR_DIV_SEL_Msk                (0x3UL)                   /*!< LVD CR: DIV_SEL (Bitfield-Mask: 0x03)                 */
#define LVD_CR_DIV_SEL										LVD_CR_DIV_SEL_Msk
#define LVD_CR_DIV_SEL_0									(0x1 << LVD_CR_DIV_SEL_Pos)
#define LVD_CR_DIV_SEL_1									(0x2 << LVD_CR_DIV_SEL_Pos)
#define LVD_CR_DIV_SEL_2									(0x4 << LVD_CR_DIV_SEL_Pos)
#define LVD_CR_LVDEN_Pos                  (5UL)                     /*!< LVD CR: LVDEN (Bit 5)                                 */
#define LVD_CR_LVDEN_Msk                  (0x20UL)                  /*!< LVD CR: LVDEN (Bitfield-Mask: 0x01)                   */
#define LVD_CR_LVDEN											LVD_CR_LVDEN_Msk
#define LVD_CR_ACT_Pos                    (6UL)                     /*!< LVD CR: ACT (Bit 6)                                   */
#define LVD_CR_ACT_Msk                    (0x40UL)                  /*!< LVD CR: ACT (Bitfield-Mask: 0x01)                     */
#define LVD_CR_ACT												LVD_CR_ACT_Msk
#define LVD_CR_FLTEN_Pos                  (7UL)                     /*!< LVD CR: FLTEN (Bit 7)                                 */
#define LVD_CR_FLTEN_Msk                  (0x80UL)                  /*!< LVD CR: FLTEN (Bitfield-Mask: 0x01)                   */
#define LVD_CR_FLTEN											LVD_CR_FLTEN_Msk
#define LVD_CR_FLTCLK_SEL_Pos             (8UL)                     /*!< LVD CR: FLTCLK_SEL (Bit 8)                            */
#define LVD_CR_FLTCLK_SEL_Msk             (0x300UL)                 /*!< LVD CR: FLTCLK_SEL (Bitfield-Mask: 0x03)              */
#define LVD_CR_FLTCLK_SEL									LVD_CR_FLTCLK_SEL_Msk
#define LVD_CR_FLTCLK_SEL_0								(0x1 << LVD_CR_FLTCLK_SEL_Pos)
#define LVD_CR_FLTCLK_SEL_1								(0x2 << LVD_CR_FLTCLK_SEL_Pos)
#define LVD_CR_FALLINTEN_Pos              (12UL)                    /*!< LVD CR: FALLINTEN (Bit 12)                            */
#define LVD_CR_FALLINTEN_Msk              (0x1000UL)                /*!< LVD CR: FALLINTEN (Bitfield-Mask: 0x01)               */
#define LVD_CR_FALLINTEN									LVD_CR_FALLINTEN_Msk
#define LVD_CR_RISEINTEN_Pos              (13UL)                    /*!< LVD CR: RISEINTEN (Bit 13)                            */
#define LVD_CR_RISEINTEN_Msk              (0x2000UL)                /*!< LVD CR: RISEINTEN (Bitfield-Mask: 0x01)               */
#define LVD_CR_RISEINTEN									LVD_CR_RISEINTEN_Msk
#define LVD_CR_HIGHINTEN_Pos              (14UL)                    /*!< LVD CR: HIGHINTEN (Bit 14)                            */
#define LVD_CR_HIGHINTEN_Msk              (0x4000UL)                /*!< LVD CR: HIGHINTEN (Bitfield-Mask: 0x01)               */
#define LVD_CR_HIGHINTEN									LVD_CR_HIGHINTEN_Msk
#define LVD_CR_INT_EN_Pos                 (15UL)                    /*!< LVD CR: INT_EN (Bit 15)                               */
#define LVD_CR_INT_EN_Msk                 (0x8000UL)                /*!< LVD CR: INT_EN (Bitfield-Mask: 0x01)                  */
#define LVD_CR_INT_EN											LVD_CR_INT_EN_Msk
#define LVD_CR_FLT_NUM_Pos                (16UL)                    /*!< LVD CR: FLT_NUM (Bit 16)                              */
#define LVD_CR_FLT_NUM_Msk                (0xffff0000UL)            /*!< LVD CR: FLT_NUM (Bitfield-Mask: 0xffff)               */
#define LVD_CR_FLT_NUM										LVD_CR_FLT_NUM_Msk
#define LVD_CR_ALL_Msk										(0xfffff3e7UL)

/* ==========================================================  SR  =========================================================== */
#define LVD_SR_INTF_Pos                   (0UL)                     /*!< LVD SR: INTF (Bit 0)                                  */
#define LVD_SR_INTF_Msk                   (0x1UL)                   /*!< LVD SR: INTF (Bitfield-Mask: 0x01)                    */
#define LVD_SR_INTF												LVD_SR_INTF_Msk

/* =========================================================================================================================== */
/* ================                                            ADC                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR0  ========================================================== */
#define ADC_CR0_ADCEN_Pos                 (0UL)                     /*!< ADC CR0: ADCEN (Bit 0)                                */
#define ADC_CR0_ADCEN_Msk                 (0x1UL)                   /*!< ADC CR0: ADCEN (Bitfield-Mask: 0x01)                  */
#define ADC_CR0_ADCEN											ADC_CR0_ADCEN_Msk
#define ADC_CR0_START_Pos                 (1UL)                     /*!< ADC CR0: START (Bit 1)                                */
#define ADC_CR0_START_Msk                 (0x2UL)                   /*!< ADC CR0: START (Bitfield-Mask: 0x01)                  */
#define ADC_CR0_START											ADC_CR0_START_Msk
#define ADC_CR0_CLKSEL_Pos                (4UL)                     /*!< ADC CR0: CLKSEL (Bit 4)                               */
#define ADC_CR0_CLKSEL_Msk                (0x70UL)                  /*!< ADC CR0: CLKSEL (Bitfield-Mask: 0x07)                 */
#define ADC_CR0_CLKSEL										ADC_CR0_CLKSEL_Msk
#define ADC_CR0_CLKSEL_0									(0x1 << ADC_CR0_CLKSEL_Pos)
#define ADC_CR0_CLKSEL_1									(0x2 << ADC_CR0_CLKSEL_Pos)
#define ADC_CR0_CLKSEL_2									(0x4 << ADC_CR0_CLKSEL_Pos)
#define ADC_CR0_SEL_Pos                   (8UL)                     /*!< ADC CR0: SEL (Bit 8)                                  */
#define ADC_CR0_SEL_Msk                   (0x700UL)                 /*!< ADC CR0: SEL (Bitfield-Mask: 0x07)                    */
#define ADC_CR0_SEL												ADC_CR0_SEL_Msk
#define ADC_CR0_SEL_0											(0x1 << ADC_CR0_SEL_Pos)
#define ADC_CR0_SEL_1											(0x2 << ADC_CR0_SEL_Pos)
#define ADC_CR0_SEL_2											(0x4 << ADC_CR0_SEL_Pos)
#define ADC_CR0_SAM_Pos                   (11UL)                    /*!< ADC CR0: SAM (Bit 11)                                 */
#define ADC_CR0_SAM_Msk                   (0x800UL)                 /*!< ADC CR0: SAM (Bitfield-Mask: 0x01)                    */
#define ADC_CR0_SAM												ADC_CR0_SAM_Msk
#define ADC_CR0_STATERST_Pos              (15UL)                    /*!< ADC CR0: STATERST (Bit 15)                            */
#define ADC_CR0_STATERST_Msk              (0x8000UL)                /*!< ADC CR0: STATERST (Bitfield-Mask: 0x01)               */
#define ADC_CR0_STATERST									ADC_CR0_STATERST_Msk
/* ==========================================================  CR1  ========================================================== */
#define ADC_CR1_TRIGS0_Pos                (0UL)                     /*!< ADC CR1: TRIGS0 (Bit 0)                               */
#define ADC_CR1_TRIGS0_Msk                (0x1fUL)                  /*!< ADC CR1: TRIGS0 (Bitfield-Mask: 0x1f)                 */
#define ADC_CR1_TRIGS0										ADC_CR1_TRIGS0_Msk
#define ADC_CR1_TRIGS0_0									(0x1 << ADC_CR1_TRIGS0_Pos)
#define ADC_CR1_TRIGS0_1									(0x2 << ADC_CR1_TRIGS0_Pos)
#define ADC_CR1_TRIGS0_2									(0x4 << ADC_CR1_TRIGS0_Pos)
#define ADC_CR1_TRIGS0_3									(0x8 << ADC_CR1_TRIGS0_Pos)
#define ADC_CR1_TRIGS0_4									(0x10 << ADC_CR1_TRIGS0_Pos)
#define ADC_CR1_TRIGS1_Pos                (5UL)                     /*!< ADC CR1: TRIGS1 (Bit 5)                               */
#define ADC_CR1_TRIGS1_Msk                (0x3e0UL)                 /*!< ADC CR1: TRIGS1 (Bitfield-Mask: 0x1f)                 */
#define ADC_CR1_TRIGS1										ADC_CR1_TRIGS1_Msk
#define ADC_CR1_TRIGS1_0									(0x1 << ADC_CR1_TRIGS1_Pos)
#define ADC_CR1_TRIGS1_1									(0x1 << ADC_CR1_TRIGS1_Pos)
#define ADC_CR1_TRIGS1_2									(0x1 << ADC_CR1_TRIGS1_Pos)
#define ADC_CR1_TRIGS1_3									(0x1 << ADC_CR1_TRIGS1_Pos)
#define ADC_CR1_TRIGS1_4									(0x1 << ADC_CR1_TRIGS1_Pos)
#define ADC_CR1_CT_Pos                    (10UL)                    /*!< ADC CR1: CT (Bit 10)                                  */
#define ADC_CR1_CT_Msk                    (0x400UL)                 /*!< ADC CR1: CT (Bitfield-Mask: 0x01)                     */
#define ADC_CR1_CT												ADC_CR1_CT_Msk
#define ADC_CR1_RACC_EN_Pos               (11UL)                    /*!< ADC CR1: RACC_EN (Bit 11)                             */
#define ADC_CR1_RACC_EN_Msk               (0x800UL)                 /*!< ADC CR1: RACC_EN (Bitfield-Mask: 0x01)                */
#define ADC_CR1_RACC_EN										ADC_CR1_RACC_EN_Msk
#define ADC_CR1_LTCMP_Pos                 (12UL)                    /*!< ADC CR1: LTCMP (Bit 12)                               */
#define ADC_CR1_LTCMP_Msk                 (0x1000UL)                /*!< ADC CR1: LTCMP (Bitfield-Mask: 0x01)                  */
#define ADC_CR1_LTCMP											ADC_CR1_LTCMP_Msk
#define ADC_CR1_HTCMP_Pos                 (13UL)                    /*!< ADC CR1: HTCMP (Bit 13)                               */
#define ADC_CR1_HTCMP_Msk                 (0x2000UL)                /*!< ADC CR1: HTCMP (Bitfield-Mask: 0x01)                  */
#define ADC_CR1_HTCMP											ADC_CR1_HTCMP_Msk
#define ADC_CR1_REGCMP_Pos                (14UL)                    /*!< ADC CR1: REGCMP (Bit 14)                              */
#define ADC_CR1_REGCMP_Msk                (0x4000UL)                /*!< ADC CR1: REGCMP (Bitfield-Mask: 0x01)                 */
#define ADC_CR1_REGCMP										ADC_CR1_REGCMP_Msk
#define ADC_CR1_RACC_CLR_Pos              (15UL)                    /*!< ADC CR1: RACC_CLR (Bit 15)                            */
#define ADC_CR1_RACC_CLR_Msk              (0x8000UL)                /*!< ADC CR1: RACC_CLR (Bitfield-Mask: 0x01)               */
#define ADC_CR1_RACC_CLR									ADC_CR1_RACC_CLR_Msk
/* ==========================================================  CR2  ========================================================== */
#define ADC_CR2_CHEN_Pos                  (0UL)                     /*!< ADC CR2: CHEN (Bit 0)                                 */
#define ADC_CR2_CHEN_Msk                  (0xffUL)                  /*!< ADC CR2: CHEN (Bitfield-Mask: 0xff)                   */
#define ADC_CR2_CHEN											ADC_CR2_CHEN_Msk
#define ADC_CR2_CHEN_0										(0x1 << ADC_CR2_CHEN_Pos)							
#define ADC_CR2_CHEN_1										(0x2 << ADC_CR2_CHEN_Pos)		
#define ADC_CR2_CHEN_2										(0x4 << ADC_CR2_CHEN_Pos)		
#define ADC_CR2_CHEN_3										(0x8 << ADC_CR2_CHEN_Pos)		
#define ADC_CR2_CHEN_4										(0x10 << ADC_CR2_CHEN_Pos)		
#define ADC_CR2_CHEN_5										(0x20 << ADC_CR2_CHEN_Pos)		
#define ADC_CR2_CHEN_6										(0x40 << ADC_CR2_CHEN_Pos)		
#define ADC_CR2_CHEN_7										(0x80 << ADC_CR2_CHEN_Pos)		
#define ADC_CR2_ADCCNT_Pos                (8UL)                     /*!< ADC CR2: ADCCNT (Bit 8)                                */
#define ADC_CR2_ADCCNT_Msk                (0xff00UL)                /*!< ADC CR2: ADCCNT (Bitfield-Mask: 0xff)                  */
#define ADC_CR2_ADCCNT										ADC_CR2_ADCCNT_Msk
#define ADC_CR2_CIRCLE_MODE_Pos           (16UL)                    /*!< ADC CR2: Circle_Mode (Bit 16)                         */
#define ADC_CR2_CIRCLE_MODE_Msk           (0x10000UL)               /*!< ADC CR2: Circle_Mode (Bitfield-Mask: 0x01)            */
#define ADC_CR2_CIRCLE_MODE								ADC_CR2_CIRCLE_MODE_Msk

/* ========================================================  RESULT0  ======================================================== */
#define ADC_RESULT0_Result0_Pos           (0UL)                     /*!< ADC RESULT0: Result0 (Bit 0)                          */
#define ADC_RESULT0_Result0_Msk           (0xfffUL)                 /*!< ADC RESULT0: Result0 (Bitfield-Mask: 0xfff)           */
/* ========================================================  RESULT1  ======================================================== */
#define ADC_RESULT1_Result1_Pos           (0UL)                     /*!< ADC RESULT1: Result1 (Bit 0)                          */
#define ADC_RESULT1_Result1_Msk           (0xffffffUL)              /*!< ADC RESULT1: Result1 (Bitfield-Mask: 0xffffff)        */
/* ========================================================  RESULT2  ======================================================== */
#define ADC_RESULT2_Result2_Pos           (0UL)                     /*!< ADC RESULT2: Result2 (Bit 0)                          */
#define ADC_RESULT2_Result2_Msk           (0xfffUL)                 /*!< ADC RESULT2: Result2 (Bitfield-Mask: 0xfff)           */
/* ========================================================  RESULT3  ======================================================== */
#define ADC_RESULT3_Result3_Pos           (0UL)                     /*!< ADC RESULT3: Result3 (Bit 0)                          */
#define ADC_RESULT3_Result3_Msk           (0xfffUL)                 /*!< ADC RESULT3: Result3 (Bitfield-Mask: 0xfff)           */
/* ========================================================  RESULT4  ======================================================== */
#define ADC_RESULT4_Result4_Pos           (0UL)                     /*!< ADC RESULT4: Result4 (Bit 0)                          */
#define ADC_RESULT4_Result4_Msk           (0xfffUL)                 /*!< ADC RESULT4: Result4 (Bitfield-Mask: 0xfff)           */
/* ========================================================  RESULT5  ======================================================== */
#define ADC_RESULT5_Result5_Pos           (0UL)                     /*!< ADC RESULT5: Result5 (Bit 0)                          */
#define ADC_RESULT5_Result5_Msk           (0xfffUL)                 /*!< ADC RESULT5: Result5 (Bitfield-Mask: 0xfff)           */
/* ========================================================  RESULT6  ======================================================== */
#define ADC_RESULT6_Result6_Pos           (0UL)                     /*!< ADC RESULT6: Result6 (Bit 0)                          */
#define ADC_RESULT6_Result6_Msk           (0xfffUL)                 /*!< ADC RESULT6: Result6 (Bitfield-Mask: 0xfff)           */
/* ========================================================  RESULT7  ======================================================== */
#define ADC_RESULT7_Result7_Pos           (0UL)                     /*!< ADC RESULT7: Result7 (Bit 0)                          */
#define ADC_RESULT7_Result7_Msk           (0xfffUL)                 /*!< ADC RESULT7: Result7 (Bitfield-Mask: 0xfff)           */
/* ========================================================  RESULT  ========================================================= */
#define ADC_RESULT_RESULT_Pos             (0UL)                     /*!< ADC RESULT: RESULT (Bit 0)                            */
#define ADC_RESULT_RESULT_Msk             (0xfffUL)                 /*!< ADC RESULT: RESULT (Bitfield-Mask: 0xfff)             */
/* ======================================================  RESULT_ACC  ======================================================= */
#define ADC_RESULT_ACC_HT_Pos             (0UL)                     /*!< ADC RESULT_ACC: HT (Bit 0)                            */
#define ADC_RESULT_ACC_HT_Msk             (0xfffUL)                 /*!< ADC RESULT_ACC: HT (Bitfield-Mask: 0xfff)             */
/* ==========================================================  HT  =========================================================== */
#define ADC_HT_HT_Pos                     (0UL)                     /*!< ADC HT: HT (Bit 0)                                    */
#define ADC_HT_HT_Msk                     (0xfffUL)                 /*!< ADC HT: HT (Bitfield-Mask: 0xfff)                     */
/* ==========================================================  LT  =========================================================== */
#define ADC_LT_LT_Pos                     (0UL)                     /*!< ADC LT: LT (Bit 0)                                    */
#define ADC_LT_LT_Msk                     (0xfffUL)                 /*!< ADC LT: LT (Bitfield-Mask: 0xfff)                     */
/* =========================================================  INTEN  ========================================================= */
#define ADC_INTEN_ADCXIEN_Pos             (0UL)                     /*!< ADC INTEN: ADCXIEN (Bit 0)                            */
#define ADC_INTEN_ADCXIEN_Msk             (0xffUL)                  /*!< ADC INTEN: ADCXIEN (Bitfield-Mask: 0xff)              */
#define ADC_INTEN_ADCXIEN									ADC_INTEN_ADCXIEN_Msk
#define ADC_INTEN_ADCXIEN_0								(0x1 << ADC_INTEN_ADCXIEN_Pos)
#define ADC_INTEN_ADCXIEN_1								(0x2 << ADC_INTEN_ADCXIEN_Pos)
#define ADC_INTEN_ADCXIEN_2								(0x4 << ADC_INTEN_ADCXIEN_Pos)
#define ADC_INTEN_ADCXIEN_3								(0x8 << ADC_INTEN_ADCXIEN_Pos)
#define ADC_INTEN_ADCXIEN_4								(0x10 << ADC_INTEN_ADCXIEN_Pos)
#define ADC_INTEN_ADCXIEN_5								(0x20 << ADC_INTEN_ADCXIEN_Pos)
#define ADC_INTEN_ADCXIEN_6								(0x40 << ADC_INTEN_ADCXIEN_Pos)
#define ADC_INTEN_ADCXIEN_7								(0x80 << ADC_INTEN_ADCXIEN_Pos)
#define ADC_INTEN_LLT_IEN_Pos             (8UL)                     /*!< ADC INTEN: LLT_IEN (Bit 8)                            */
#define ADC_INTEN_LLT_IEN_Msk             (0x100UL)                 /*!< ADC INTEN: LLT_IEN (Bitfield-Mask: 0x01)              */
#define ADC_INTEN_LLT_IEN									ADC_INTEN_LLT_IEN_Msk
#define ADC_INTEN_HHT_IEN_Pos             (9UL)                     /*!< ADC INTEN: HHT_IEN (Bit 9)                            */
#define ADC_INTEN_HHT_IEN_Msk             (0x200UL)                 /*!< ADC INTEN: HHT_IEN (Bitfield-Mask: 0x01)              */
#define ADC_INTEN_HHT_IEN									ADC_INTEN_HHT_IEN_Msk
#define ADC_INTEN_REG_IEN_Pos             (10UL)                    /*!< ADC INTEN: REG_IEN (Bit 10)                           */
#define ADC_INTEN_REG_IEN_Msk             (0x400UL)                 /*!< ADC INTEN: REG_IEN (Bitfield-Mask: 0x01)              */
#define ADC_INTEN_REG_IEN									ADC_INTEN_REG_IEN_Msk
#define ADC_INTEN_CONT_IEN_Pos            (11UL)                    /*!< ADC INTEN: CONT_IEN (Bit 11)                          */
#define ADC_INTEN_CONT_IEN_Msk            (0x800UL)                 /*!< ADC INTEN: CONT_IEN (Bitfield-Mask: 0x01)             */
#define ADC_INTEN_CONT_IEN								ADC_INTEN_CONT_IEN_Msk
#define ADC_INTEN_CONT_ALL								(0xfffUL)
/* ========================================================  INTCLR  ========================================================= */
#define ADC_INTCLR_ADCICLR_Pos            (0UL)                     /*!< ADC INTCLR: ADCICLR (Bit 0)                           */
#define ADC_INTCLR_ADCICLR_Msk            (0xffUL)                  /*!< ADC INTCLR: ADCICLR (Bitfield-Mask: 0xff)             */
#define ADC_INTCLR_ADCICLR								ADC_INTCLR_ADCICLR_Msk
#define ADC_INTCLR_ADCICLR_0							(0x1 << ADC_INTCLR_ADCICLR_Pos)
#define ADC_INTCLR_ADCICLR_1							(0x2 << ADC_INTCLR_ADCICLR_Pos)
#define ADC_INTCLR_ADCICLR_2							(0x4 << ADC_INTCLR_ADCICLR_Pos)
#define ADC_INTCLR_ADCICLR_3							(0x8 << ADC_INTCLR_ADCICLR_Pos)
#define ADC_INTCLR_ADCICLR_4							(0x10 << ADC_INTCLR_ADCICLR_Pos)
#define ADC_INTCLR_ADCICLR_5							(0x20 << ADC_INTCLR_ADCICLR_Pos)
#define ADC_INTCLR_ADCICLR_6							(0x40 << ADC_INTCLR_ADCICLR_Pos)
#define ADC_INTCLR_ADCICLR_7							(0x80 << ADC_INTCLR_ADCICLR_Pos)
#define ADC_INTCLR_LLT_INTC_Pos           (8UL)                     /*!< ADC INTCLR: LLT_INTC (Bit 8)                          */
#define ADC_INTCLR_LLT_INTC_Msk           (0x100UL)                 /*!< ADC INTCLR: LLT_INTC (Bitfield-Mask: 0x01)            */
#define ADC_INTCLR_LLT_INTC								ADC_INTCLR_LLT_INTC_Msk
#define ADC_INTCLR_HHT_INTC_Pos           (9UL)                     /*!< ADC INTCLR: HHT_INTC (Bit 9)                          */
#define ADC_INTCLR_HHT_INTC_Msk           (0x200UL)                 /*!< ADC INTCLR: HHT_INTC (Bitfield-Mask: 0x01)            */
#define ADC_INTCLR_HHT_INTC								ADC_INTCLR_HHT_INTC_Msk
#define ADC_INTCLR_REG_INTC_Pos           (10UL)                    /*!< ADC INTCLR: REG_INTC (Bit 10)                         */
#define ADC_INTCLR_REG_INTC_Msk           (0x400UL)                 /*!< ADC INTCLR: REG_INTC (Bitfield-Mask: 0x01)            */
#define ADC_INTCLR_REG_INTC								ADC_INTCLR_REG_INTC_Msk
#define ADC_INTCLR_CONT_INTC_Pos          (11UL)                    /*!< ADC INTCLR: CONT_INTC (Bit 11)                        */
#define ADC_INTCLR_CONT_INTC_Msk          (0x800UL)                 /*!< ADC INTCLR: CONT_INTC (Bitfield-Mask: 0x01)           */
#define ADC_INTCLR_CONT_INTC							ADC_INTCLR_CONT_INTC_Msk
/* =======================================================  RAWINTSR  ======================================================== */
#define ADC_RAWINTSR_ADCRIS_Pos           (0UL)                     /*!< ADC RAWINTSR: ADCRIS (Bit 0)                          */
#define ADC_RAWINTSR_ADCRIS_Msk           (0xffUL)                  /*!< ADC RAWINTSR: ADCRIS (Bitfield-Mask: 0xff)            */
#define ADC_RAWINTSR_ADCRIS								ADC_RAWINTSR_ADCRIS_Msk
#define ADC_RAWINTSR_ADCRIS_0							(0x1 << ADC_RAWINTSR_ADCRIS_Pos)
#define ADC_RAWINTSR_ADCRIS_1							(0x2 << ADC_RAWINTSR_ADCRIS_Pos)
#define ADC_RAWINTSR_ADCRIS_2							(0x4 << ADC_RAWINTSR_ADCRIS_Pos)
#define ADC_RAWINTSR_ADCRIS_3							(0x8 << ADC_RAWINTSR_ADCRIS_Pos)
#define ADC_RAWINTSR_ADCRIS_4							(0x10 << ADC_RAWINTSR_ADCRIS_Pos)
#define ADC_RAWINTSR_ADCRIS_5							(0x20 << ADC_RAWINTSR_ADCRIS_Pos)
#define ADC_RAWINTSR_ADCRIS_6							(0x40 << ADC_RAWINTSR_ADCRIS_Pos)
#define ADC_RAWINTSR_ADCRIS_7							(0x80 << ADC_RAWINTSR_ADCRIS_Pos)
#define ADC_RAWINTSR_LLT_INTF_Pos         (8UL)                     /*!< ADC RAWINTSR: LLT_INTF (Bit 8)                        */
#define ADC_RAWINTSR_LLT_INTF_Msk         (0x100UL)                 /*!< ADC RAWINTSR: LLT_INTF (Bitfield-Mask: 0x01)          */
#define ADC_RAWINTSR_LLT_INTF							ADC_RAWINTSR_LLT_INTF_Msk
#define ADC_RAWINTSR_HHT_INTF_Pos         (9UL)                     /*!< ADC RAWINTSR: HHT_INTF (Bit 9)                        */
#define ADC_RAWINTSR_HHT_INTF_Msk         (0x200UL)                 /*!< ADC RAWINTSR: HHT_INTF (Bitfield-Mask: 0x01)          */
#define ADC_RAWINTSR_HHT_INTF							ADC_RAWINTSR_HHT_INTF_Msk
#define ADC_RAWINTSR_REG_INTF_Pos         (10UL)                    /*!< ADC RAWINTSR: REG_INTF (Bit 10)                       */
#define ADC_RAWINTSR_REG_INTF_Msk         (0x400UL)                 /*!< ADC RAWINTSR: REG_INTF (Bitfield-Mask: 0x01)          */
#define ADC_RAWINTSR_REG_INTF							ADC_RAWINTSR_REG_INTF_Msk
#define ADC_RAWINTSR_CONT_INTF_Pos        (11UL)                    /*!< ADC RAWINTSR: CONT_INTF (Bit 11)                      */
#define ADC_RAWINTSR_CONT_INTF_Msk        (0x800UL)                 /*!< ADC RAWINTSR: CONT_INTF (Bitfield-Mask: 0x01)         */
#define ADC_RAWINTSR_CONT_INTF						ADC_RAWINTSR_CONT_INTF_Msk
/* =======================================================  MSKINTSR  ======================================================== */
#define ADC_MSKINTSR_ADCMIS_Pos           (0UL)                     /*!< ADC MSKINTSR: ADCMIS (Bit 0)                          */
#define ADC_MSKINTSR_ADCMIS_Msk           (0xffUL)                  /*!< ADC MSKINTSR: ADCMIS (Bitfield-Mask: 0xff)            */
#define ADC_MSKINTSR_ADCMIS								ADC_MSKINTSR_ADCMIS_Msk
#define ADC_MSKINTSR_ADCMIS_0							(0x1 << ADC_MSKINTSR_ADCMIS_Pos)
#define ADC_MSKINTSR_ADCMIS_1							(0x2 << ADC_MSKINTSR_ADCMIS_Pos)
#define ADC_MSKINTSR_ADCMIS_2							(0x4 << ADC_MSKINTSR_ADCMIS_Pos)
#define ADC_MSKINTSR_ADCMIS_3							(0x8 << ADC_MSKINTSR_ADCMIS_Pos)
#define ADC_MSKINTSR_ADCMIS_4							(0x10 << ADC_MSKINTSR_ADCMIS_Pos)
#define ADC_MSKINTSR_ADCMIS_5							(0x20 << ADC_MSKINTSR_ADCMIS_Pos)
#define ADC_MSKINTSR_ADCMIS_6							(0x40 << ADC_MSKINTSR_ADCMIS_Pos)
#define ADC_MSKINTSR_ADCMIS_7							(0x80 << ADC_MSKINTSR_ADCMIS_Pos)
#define ADC_MSKINTSR_LLT_MIF_Pos          (8UL)                     /*!< ADC MSKINTSR: LLT_MIF (Bit 8)                         */
#define ADC_MSKINTSR_LLT_MIF_Msk          (0x100UL)                 /*!< ADC MSKINTSR: LLT_MIF (Bitfield-Mask: 0x01)           */
#define ADC_MSKINTSR_LLT_MIF							ADC_MSKINTSR_LLT_MIF_Msk
#define ADC_MSKINTSR_HHT_MIF_Pos          (9UL)                     /*!< ADC MSKINTSR: HHT_MIF (Bit 9)                         */
#define ADC_MSKINTSR_HHT_MIF_Msk          (0x200UL)                 /*!< ADC MSKINTSR: HHT_MIF (Bitfield-Mask: 0x01)           */
#define ADC_MSKINTSR_HHT_MIF							ADC_MSKINTSR_HHT_MIF_Msk
#define ADC_MSKINTSR_REG_MIF_Pos          (10UL)                    /*!< ADC MSKINTSR: REG_MIF (Bit 10)                        */
#define ADC_MSKINTSR_REG_MIF_Msk          (0x400UL)                 /*!< ADC MSKINTSR: REG_MIF (Bitfield-Mask: 0x01)           */
#define ADC_MSKINTSR_REG_MIF							ADC_MSKINTSR_REG_MIF_Msk
#define ADC_MSKINTSR_CONT_MIF_Pos         (11UL)                    /*!< ADC MSKINTSR: CONT_MIF (Bit 11)                       */
#define ADC_MSKINTSR_CONT_MIF_Msk         (0x800UL)                 /*!< ADC MSKINTSR: CONT_MIF (Bitfield-Mask: 0x01)          */
#define ADC_MSKINTSR_CONT_MIF							ADC_MSKINTSR_CONT_MIF_Msk

/* =========================================================================================================================== */
/* ================                                            RTC                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define RTC_CR_BYPSHAD_Pos                (0UL)                     /*!< RTC CR: BYPSHAD (Bit 0)                               */
#define RTC_CR_BYPSHAD_Msk                (0x1UL)                   /*!< RTC CR: BYPSHAD (Bitfield-Mask: 0x01)                 */
#define RTC_CR_BYPSHAD										 RTC_CR_BYPSHAD_Msk
#define RTC_CR_RTC1HZOE_Pos               (1UL)                     /*!< RTC CR: RTC1HZOE (Bit 1)                              */
#define RTC_CR_RTC1HZOE_Msk               (0x2UL)                   /*!< RTC CR: RTC1HZOE (Bitfield-Mask: 0x01)                */
#define RTC_CR_RTC1HZOE										RTC_CR_RTC1HZOE_Msk
#define RTC_CR_FMT_Pos                    (2UL)                     /*!< RTC CR: FMT (Bit 2)                                   */
#define RTC_CR_FMT_Msk                    (0x4UL)                   /*!< RTC CR: FMT (Bitfield-Mask: 0x01)                     */
#define RTC_CR_FMT						  					RTC_CR_FMT_Msk
#define RTC_CR_ALM1_INTEN_Pos             (4UL)                     /*!< RTC CR: ALM1_INTEN (Bit 4)                            */
#define RTC_CR_ALM1_INTEN_Msk             (0x10UL)                  /*!< RTC CR: ALM1_INTEN (Bitfield-Mask: 0x01)              */
#define RTC_CR_ALM1_INTEN									RTC_CR_ALM1_INTEN_Msk	
#define RTC_CR_ALM2_INTEN_Pos             (5UL)                     /*!< RTC CR: ALM2_INTEN (Bit 5)                            */
#define RTC_CR_ALM2_INTEN_Msk             (0x20UL)                  /*!< RTC CR: ALM2_INTEN (Bitfield-Mask: 0x01)              */
#define RTC_CR_ALM2_INTEN									RTC_CR_ALM2_INTEN_Msk
#define RTC_CR_ALM1EN_Pos                 (6UL)                     /*!< RTC CR: ALM1EN (Bit 6)                                */
#define RTC_CR_ALM1EN_Msk                 (0x40UL)                  /*!< RTC CR: ALM1EN (Bitfield-Mask: 0x01)                  */
#define RTC_CR_ALM1EN 					 					RTC_CR_ALM1EN_Msk 
#define RTC_CR_START_Pos                  (8UL)                     /*!< RTC CR: START (Bit 8)                                 */
#define RTC_CR_START_Msk                  (0x100UL)                 /*!< RTC CR: START (Bitfield-Mask: 0x01)                   */
#define RTC_CR_START                       RTC_CR_START_Msk
/* =========================================================  CLKCR  ========================================================= */
#define RTC_CLKCR_HXTDIV_Pos              (0UL)                     /*!< RTC CLKCR: HXTDIV (Bit 0)                             */
#define RTC_CLKCR_HXTDIV_Msk              (0x3ffUL)                 /*!< RTC CLKCR: HXTDIV (Bitfield-Mask: 0x3ff)              */
#define RTC_CLKCR_HXTDIV				   				RTC_CLKCR_HXTDIV_Msk
#define RTC_CLKCR_RTCCKSEL_Pos            (16UL)                    /*!< RTC CLKCR: RTCCKSEL (Bit 16)                          */
#define RTC_CLKCR_RTCCKSEL_Msk            (0x30000UL)               /*!< RTC CLKCR: RTCCKSEL (Bitfield-Mask: 0x03)             */
#define RTC_CLKCR_RTCCKEN_Pos             (20UL)                    /*!< RTC CLKCR: RTCCKEN (Bit 20)                           */
#define RTC_CLKCR_RTCCKEN_Msk             (0x100000UL)              /*!< RTC CLKCR: RTCCKEN (Bitfield-Mask: 0x01)              */
#define RTC_CLKCR_RTCCKEN                  RTC_CLKCR_RTCCKEN_Msk 
/* =========================================================  TIME  ========================================================== */
#define RTC_TIME_SEC_Pos                  (0UL)                     /*!< RTC TIME: SEC (Bit 0)                                 */
#define RTC_TIME_SEC_Msk                  (0x3fUL)                  /*!< RTC TIME: SEC (Bitfield-Mask: 0x3f)                   */
#define RTC_TIME_SEC											RTC_TIME_SEC_Msk
#define RTC_TIME_MIN_Pos                  (8UL)                     /*!< RTC TIME: MIN (Bit 8)                                 */
#define RTC_TIME_MIN_Msk                  (0x7f00UL)                /*!< RTC TIME: MIN (Bitfield-Mask: 0x7f)                   */
#define RTC_TIME_MIN											RTC_TIME_MIN_Msk
#define RTC_TIME_HOUR19_Pos               (16UL)                    /*!< RTC TIME: HOUR19 (Bit 16)                             */
#define RTC_TIME_HOUR19_Msk               (0x1f0000UL)              /*!< RTC TIME: HOUR19 (Bitfield-Mask: 0x1f)                */
#define RTC_TIME_HOUR19						RTC_TIME_HOUR19_Msk	 
#define RTC_TIME_H20_PA_Pos               (21UL)                    /*!< RTC TIME: H20_PA (Bit 21)                             */
#define RTC_TIME_H20_PA_Msk               (0x200000UL)              /*!< RTC TIME: H20_PA (Bitfield-Mask: 0x01)                */
#define RTC_TIME_H20_PA										 RTC_TIME_H20_PA_Msk
#define RTC_TIME_WEEK_Pos                 (24UL)                    /*!< RTC TIME: WEEK (Bit 24)                               */
#define RTC_TIME_WEEK_Msk                 (0x7000000UL)             /*!< RTC TIME: WEEK (Bitfield-Mask: 0x07)                  */
#define RTC_TIME_WEEK											 RTC_TIME_WEEK_Msk
/* =========================================================  DATE  ========================================================== */
#define RTC_DATE_DAY_Pos                  (0UL)                     /*!< RTC DATE: DAY (Bit 0)                                 */
#define RTC_DATE_DAY_Msk                  (0x3fUL)                  /*!< RTC DATE: DAY (Bitfield-Mask: 0x3f)                   */
#define RTC_DATE_DAY											RTC_DATE_DAY_Msk
#define RTC_DATE_MONTH_Pos                (8UL)                     /*!< RTC DATE: MONTH (Bit 8)                               */
#define RTC_DATE_MONTH_Msk                (0x1f00UL)                /*!< RTC DATE: MONTH (Bitfield-Mask: 0x1f)                 */
#define RTC_DATE_MONTH										RTC_DATE_MONTH_Msk 
#define RTC_DATE_CEN_Pos                  (15UL)                    /*!< RTC DATE: CEN (Bit 15)                                */
#define RTC_DATE_CEN_Msk                  (0x8000UL)                /*!< RTC DATE: CEN (Bitfield-Mask: 0x01)                   */
#define RTC_DATE_CEN											 RTC_DATE_CEN_Msk 
#define RTC_DATE_YEAR_Pos                 (16UL)                    /*!< RTC DATE: YEAR (Bit 16)                               */
#define RTC_DATE_YEAR_Msk                 (0xff0000UL)              /*!< RTC DATE: YEAR (Bitfield-Mask: 0xff)                  */
#define RTC_DATE_YEAR											 RTC_DATE_YEAR_Msk
/* =======================================================  ALM1TIME  ======================================================== */
#define RTC_ALM1TIME_ALSEC_Pos            (0UL)                     /*!< RTC ALM1TIME: ALSEC (Bit 0)                           */
#define RTC_ALM1TIME_ALSEC_Msk            (0x7fUL)                  /*!< RTC ALM1TIME: ALSEC (Bitfield-Mask: 0x7f)             */
#define RTC_ALM1TIME_ALMIN_Pos            (8UL)                     /*!< RTC ALM1TIME: ALMIN (Bit 8)                           */
#define RTC_ALM1TIME_ALMIN_Msk            (0x7f00UL)                /*!< RTC ALM1TIME: ALMIN (Bitfield-Mask: 0x7f)             */
#define RTC_ALM1TIME_ALHOUR19_Pos         (16UL)                    /*!< RTC ALM1TIME: ALHOUR19 (Bit 16)                       */
#define RTC_ALM1TIME_ALHOUR19_Msk         (0x1f0000UL)              /*!< RTC ALM1TIME: ALHOUR19 (Bitfield-Mask: 0x1f)          */
#define RTC_ALM1TIME_ALH20_PA_Pos         (21UL)                    /*!< RTC ALM1TIME: ALH20_PA (Bit 21)                       */
#define RTC_ALM1TIME_ALH20_PA_Msk         (0x200000UL)              /*!< RTC ALM1TIME: ALH20_PA (Bitfield-Mask: 0x01)          */
#define RTC_ALM1TIME_ALWEEK_Pos           (24UL)                    /*!< RTC ALM1TIME: ALWEEK (Bit 24)                         */
#define RTC_ALM1TIME_ALWEEK_Msk           (0x7000000UL)             /*!< RTC ALM1TIME: ALWEEK (Bitfield-Mask: 0x07)            */
/* =======================================================  ALM1DATE  ======================================================== */
#define RTC_ALM1DATE_ALDAY_Pos            (0UL)                     /*!< RTC ALM1DATE: ALDAY (Bit 0)                           */
#define RTC_ALM1DATE_ALDAY_Msk            (0x3fUL)                  /*!< RTC ALM1DATE: ALDAY (Bitfield-Mask: 0x3f)             */
#define RTC_ALM1DATE_ALMONTH_Pos          (8UL)                     /*!< RTC ALM1DATE: ALMONTH (Bit 8)                         */
#define RTC_ALM1DATE_ALMONTH_Msk          (0x1f00UL)                /*!< RTC ALM1DATE: ALMONTH (Bitfield-Mask: 0x1f)           */
#define RTC_ALM1DATE_ALCEN_Pos            (15UL)                    /*!< RTC ALM1DATE: ALCEN (Bit 15)                          */
#define RTC_ALM1DATE_ALCEN_Msk            (0x8000UL)                /*!< RTC ALM1DATE: ALCEN (Bitfield-Mask: 0x01)             */
#define RTC_ALM1DATE_ALYEAR_Pos           (16UL)                    /*!< RTC ALM1DATE: ALYEAR (Bit 16)                         */
#define RTC_ALM1DATE_ALYEAR_Msk           (0xff0000UL)              /*!< RTC ALM1DATE: ALYEAR (Bitfield-Mask: 0xff)            */
#define RTC_ALM1DATE_ALYEAR								RTC_ALM1DATE_ALYEAR_Msk
#define RTC_ALM1DATE_ALMSECEN_Pos         (24UL)                    /*!< RTC ALM1DATE: ALMSECEN (Bit 24)                       */
#define RTC_ALM1DATE_ALMSECEN_Msk         (0x1000000UL)             /*!< RTC ALM1DATE: ALMSECEN (Bitfield-Mask: 0x01)          */
#define RTC_ALM1DATE_ALMSECEN							RTC_ALM1DATE_ALMSECEN_Msk 
#define RTC_ALM1DATE_ALMMINEN_Pos         (25UL)                    /*!< RTC ALM1DATE: ALMMINEN (Bit 25)                       */
#define RTC_ALM1DATE_ALMMINEN_Msk         (0x2000000UL)             /*!< RTC ALM1DATE: ALMMINEN (Bitfield-Mask: 0x01)          */
#define RTC_ALM1DATE_ALMMINEN							 RTC_ALM1DATE_ALMMINEN_Msk
#define RTC_ALM1DATE_ALMHOUREN_Pos        (26UL)                    /*!< RTC ALM1DATE: ALMHOUREN (Bit 26)                      */
#define RTC_ALM1DATE_ALMHOUREN_Msk        (0x4000000UL)             /*!< RTC ALM1DATE: ALMHOUREN (Bitfield-Mask: 0x01)         */
#define RTC_ALM1DATE_ALMHOUREN						 RTC_ALM1DATE_ALMHOUREN_Msk
#define RTC_ALM1DATE_ALMWEEKEN_Pos        (27UL)                    /*!< RTC ALM1DATE: ALMWEEKEN (Bit 27)                      */
#define RTC_ALM1DATE_ALMWEEKEN_Msk        (0x8000000UL)             /*!< RTC ALM1DATE: ALMWEEKEN (Bitfield-Mask: 0x01)         */
#define RTC_ALM1DATE_ALMWEEKEN						 RTC_ALM1DATE_ALMWEEKEN_Msk
#define RTC_ALM1DATE_ALMDAYEN_Pos         (28UL)                    /*!< RTC ALM1DATE: ALMDAYEN (Bit 28)                       */
#define RTC_ALM1DATE_ALMDAYEN_Msk         (0x10000000UL)            /*!< RTC ALM1DATE: ALMDAYEN (Bitfield-Mask: 0x01)          */
#define RTC_ALM1DATE_ALMDAYEN							RTC_ALM1DATE_ALMDAYEN_Msk
#define RTC_ALM1DATE_ALMMONEN_Pos         (29UL)                    /*!< RTC ALM1DATE: ALMMONEN (Bit 29)                       */
#define RTC_ALM1DATE_ALMMONEN_Msk         (0x20000000UL)            /*!< RTC ALM1DATE: ALMMONEN (Bitfield-Mask: 0x01)          */
#define RTC_ALM1DATE_ALMMONEN							 RTC_ALM1DATE_ALMMONEN_Msk 
#define RTC_ALM1DATE_ALMYEAREN_Pos        (30UL)                    /*!< RTC ALM1DATE: ALMYEAREN (Bit 30)                      */
#define RTC_ALM1DATE_ALMYEAREN_Msk        (0x40000000UL)            /*!< RTC ALM1DATE: ALMYEAREN (Bitfield-Mask: 0x01)         */
#define RTC_ALM1DATE_ALMYEAREN						RTC_ALM1DATE_ALMYEAREN_Msk
/* ========================================================  ALM2PRD  ======================================================== */
#define RTC_ALM2PRD_ALM2PR_CNT_Pos        (0UL)                     /*!< RTC ALM2PRD: ALM2PR_CNT (Bit 0)                       */
#define RTC_ALM2PRD_ALM2PR_CNT_Msk        (0xfUL)                   /*!< RTC ALM2PRD: ALM2PR_CNT (Bitfield-Mask: 0x0f)         */
/* ========================================================  CLKTRIM  ======================================================== */
#define RTC_CLKTRIM_TRIM_Pos              (0UL)                     /*!< RTC CLKTRIM: TRIM (Bit 0)                             */
#define RTC_CLKTRIM_TRIM_Msk              (0xffUL)                  /*!< RTC CLKTRIM: TRIM (Bitfield-Mask: 0xff)               */
#define RTC_CLKTRIM_MODE_1_0_Pos          (8UL)                     /*!< RTC CLKTRIM: MODE_1_0 (Bit 8)                         */
#define RTC_CLKTRIM_MODE_1_0_Msk          (0x100UL)                 /*!< RTC CLKTRIM: MODE_1_0 (Bitfield-Mask: 0x01)           */
/* ==========================================================  ISR  ========================================================== */
#define RTC_ISR_WAIT_Pos                  (0UL)                     /*!< RTC ISR: WAIT (Bit 0)                                 */
#define RTC_ISR_WAIT_Msk                  (0x1UL)                   /*!< RTC ISR: WAIT (Bitfield-Mask: 0x01)                   */
#define RTC_ISR_WAIT                 			RTC_ISR_WAIT_Msk
#define RTC_ISR_WAITF_Pos                 (1UL)                     /*!< RTC ISR: WAITF (Bit 1)                                */
#define RTC_ISR_WAITF_Msk                 (0x2UL)                   /*!< RTC ISR: WAITF (Bitfield-Mask: 0x01)                  */
#define RTC_ISR_WAITF					   					RTC_ISR_WAITF_Msk
#define RTC_ISR_RSF_Pos                   (2UL)                     /*!< RTC ISR: RSF (Bit 2)                                  */
#define RTC_ISR_RSF_Msk                   (0x4UL)                   /*!< RTC ISR: RSF (Bitfield-Mask: 0x01)                    */
#define RTC_ISR_RSF												 RTC_ISR_RSF_Msk
#define RTC_ISR_ALM1_F_Pos                (4UL)                     /*!< RTC ISR: ALM1_F (Bit 4)                               */
#define RTC_ISR_ALM1_F_Msk                (0x10UL)                  /*!< RTC ISR: ALM1_F (Bitfield-Mask: 0x01)                 */
#define RTC_ISR_ALM1_F										RTC_ISR_ALM1_F_Msk
#define RTC_ISR_ALM2_F_Pos                (5UL)                     /*!< RTC ISR: ALM2_F (Bit 5)                               */
#define RTC_ISR_ALM2_F_Msk                (0x20UL)                  /*!< RTC ISR: ALM2_F (Bitfield-Mask: 0x01)                 */
#define RTC_ISR_ALM2_F										RTC_ISR_ALM2_F_Msk 
/* ========================================================  INTCLR  ========================================================= */
#define RTC_INTCLR_ALM1_CLR_Pos           (4UL)                     /*!< RTC INTCLR: ALM1_CLR (Bit 4)                          */
#define RTC_INTCLR_ALM1_CLR_Msk           (0x10UL)                  /*!< RTC INTCLR: ALM1_CLR (Bitfield-Mask: 0x01)            */
#define RTC_INTCLR_ALM1_CLR              RTC_INTCLR_ALM1_CLR_Msk 
#define RTC_INTCLR_ALM2_CLR_Pos           (5UL)                     /*!< RTC INTCLR: ALM2_CLR (Bit 5)                          */
#define RTC_INTCLR_ALM2_CLR_Msk           (0x20UL)                  /*!< RTC INTCLR: ALM2_CLR (Bitfield-Mask: 0x01)            */
#define RTC_INTCLR_ALM2_CLR        RTC_INTCLR_ALM2_CLR_Msk
/* ==========================================================  WPR  ========================================================== */
#define RTC_WPR_WPR_Pos                   (0UL)                     /*!< RTC WPR: WPR (Bit 0)                                  */
#define RTC_WPR_WPR_Msk                   (0xffUL)                  /*!< RTC WPR: WPR (Bitfield-Mask: 0xff)                    */


/* =========================================================================================================================== */
/* ================                                          CLKTRIM                                          ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define CLKTRIM_CR_TRIM_START_Pos         (0UL)                     /*!< CLKTRIM CR: TRIM_START (Bit 0)                        */
#define CLKTRIM_CR_TRIM_START_Msk         (0x1UL)                   /*!< CLKTRIM CR: TRIM_START (Bitfield-Mask: 0x01)          */
#define CLKTRIM_CR_TRIM_START							CLKTRIM_CR_TRIM_START_Msk
#define CLKTRIM_CR_REFCLK_SEL_Pos         (1UL)                     /*!< CLKTRIM CR: REFCLK_SEL (Bit 1)                        */
#define CLKTRIM_CR_REFCLK_SEL_Msk         (0xeUL)                   /*!< CLKTRIM CR: REFCLK_SEL (Bitfield-Mask: 0x07)          */
#define CLKTRIM_CR_REFCLK_SEL							CLKTRIM_CR_REFCLK_SEL_Msk
#define CLKTRIM_CR_REFCLK_SEL_0						(0x1 << CLKTRIM_CR_REFCLK_SEL_Pos)
#define CLKTRIM_CR_REFCLK_SEL_1						(0x2 << CLKTRIM_CR_REFCLK_SEL_Pos)
#define CLKTRIM_CR_REFCLK_SEL_2						(0x4 << CLKTRIM_CR_REFCLK_SEL_Pos)
#define CLKTRIM_CR_CALCLK_SEL_Pos         (4UL)                     /*!< CLKTRIM CR: CALCLK_SEL (Bit 4)                        */
#define CLKTRIM_CR_CALCLK_SEL_Msk         (0x30UL)                  /*!< CLKTRIM CR: CALCLK_SEL (Bitfield-Mask: 0x03)          */
#define CLKTRIM_CR_CALCLK_SEL							CLKTRIM_CR_CALCLK_SEL_Msk
#define CLKTRIM_CR_CALCLK_SEL_0						(0x1 << CLKTRIM_CR_CALCLK_SEL_Pos)
#define CLKTRIM_CR_CALCLK_SEL_1						(0x2 << CLKTRIM_CR_CALCLK_SEL_Pos)
#define CLKTRIM_CR_CALCLK_SEL_2						(0x4 << CLKTRIM_CR_CALCLK_SEL_Pos)
#define CLKTRIM_CR_MON_EN_Pos             (6UL)                     /*!< CLKTRIM CR: MON_EN (Bit 6)                            */
#define CLKTRIM_CR_MON_EN_Msk             (0x40UL)                  /*!< CLKTRIM CR: MON_EN (Bitfield-Mask: 0x01)              */
#define CLKTRIM_CR_MON_EN									CLKTRIM_CR_MON_EN_Msk
#define CLKTRIM_CR_IE_Pos                 (7UL)                     /*!< CLKTRIM CR: IE (Bit 7)                                */
#define CLKTRIM_CR_IE_Msk                 (0x80UL)                  /*!< CLKTRIM CR: IE (Bitfield-Mask: 0x01)                  */
#define CLKTRIM_CR_IE											CLKTRIM_CR_IE_Msk
#define CLKTRIM_CR_CLKEN_Pos              (8UL)                     /*!< CLKTRIM CR: CLKEN (Bit 8)                             */
#define CLKTRIM_CR_CLKEN_Msk              (0x100UL)                 /*!< CLKTRIM CR: CLKEN (Bitfield-Mask: 0x01)               */
#define CLKTRIM_CR_CLKEN									CLKTRIM_CR_CLKEN_Msk
#define CLKTRIM_CR_ALL_Msk								(0x1FFUL)
/* ========================================================  REFCON  ========================================================= */
#define CLKTRIM_REFCON_RCNTVAL_Pos        (0UL)                     /*!< CLKTRIM REFCON: RCNTVAL (Bit 0)                       */
#define CLKTRIM_REFCON_RCNTVAL_Msk        (0xffffffffUL)            /*!< CLKTRIM REFCON: RCNTVAL (Bitfield-Mask: 0xffffffff)   */
#define CLKTRIM_REFCON_RCNTVAL						CLKTRIM_REFCON_RCNTVAL_Msk
/* ========================================================  REFCNT  ========================================================= */
#define CLKTRIM_REFCNT_REFCNT_Pos         (0UL)                     /*!< CLKTRIM REFCNT: REFCNT (Bit 0)                        */
#define CLKTRIM_REFCNT_REFCNT_Msk         (0xffffffffUL)            /*!< CLKTRIM REFCNT: REFCNT (Bitfield-Mask: 0xffffffff)    */
#define CLKTRIM_REFCNT_REFCNT							CLKTRIM_REFCNT_REFCNT_Msk
/* ========================================================  CALCNT  ========================================================= */
#define CLKTRIM_CALCNT_CALCNT_Pos         (0UL)                     /*!< CLKTRIM CALCNT: CALCNT (Bit 0)                        */
#define CLKTRIM_CALCNT_CALCNT_Msk         (0xffffffffUL)            /*!< CLKTRIM CALCNT: CALCNT (Bitfield-Mask: 0xffffffff)    */
#define CLKTRIM_CALCNT_CALCNT							CLKTRIM_CALCNT_CALCNT_Msk
/* ==========================================================  IFR  ========================================================== */
#define CLKTRIM_IFR_STOP_Pos              (0UL)                     /*!< CLKTRIM IFR: STOP (Bit 0)                             */
#define CLKTRIM_IFR_STOP_Msk              (0x1UL)                   /*!< CLKTRIM IFR: STOP (Bitfield-Mask: 0x01)               */
#define CLKTRIM_IFR_STOP									CLKTRIM_IFR_STOP_Msk
#define CLKTRIM_IFR_CALCNT_OVF_Pos        (1UL)                     /*!< CLKTRIM IFR: CALCNT_OVF (Bit 1)                       */
#define CLKTRIM_IFR_CALCNT_OVF_Msk        (0x2UL)                   /*!< CLKTRIM IFR: CALCNT_OVF (Bitfield-Mask: 0x01)         */
#define CLKTRIM_IFR_CALCNT_OVF						CLKTRIM_IFR_CALCNT_OVF_Msk
#define CLKTRIM_IFR_LXT_FAULT_Pos         (2UL)                     /*!< CLKTRIM IFR: LXT_FAULT (Bit 2)                        */
#define CLKTRIM_IFR_LXT_FAULT_Msk         (0x4UL)                   /*!< CLKTRIM IFR: LXT_FAULT (Bitfield-Mask: 0x01)          */
#define CLKTRIM_IFR_LXT_FAULT							CLKTRIM_IFR_LXT_FAULT_Msk
#define CLKTRIM_IFR_HXT_FAULT_Pos         (3UL)                     /*!< CLKTRIM IFR: HXT_FAULT (Bit 3)                        */
#define CLKTRIM_IFR_HXT_FAULT_Msk         (0x8UL)                   /*!< CLKTRIM IFR: HXT_FAULT (Bitfield-Mask: 0x01)          */
#define CLKTRIM_IFR_HXT_FAULT							CLKTRIM_IFR_HXT_FAULT_Msk
/* =========================================================  ICLR  ========================================================== */
#define CLKTRIM_ICLR_LXT_FAULT_CLR_Pos    (2UL)                     /*!< CLKTRIM ICLR: LXT_FAULT_CLR (Bit 2)                   */
#define CLKTRIM_ICLR_LXT_FAULT_CLR_Msk    (0x4UL)                   /*!< CLKTRIM ICLR: LXT_FAULT_CLR (Bitfield-Mask: 0x01)     */
#define CLKTRIM_ICLR_LXT_FAULT_CLR				CLKTRIM_ICLR_LXT_FAULT_CLR_Msk
#define CLKTRIM_ICLR_HXT_FAULT_CLR_Pos    (3UL)                     /*!< CLKTRIM ICLR: HXT_FAULT_CLR (Bit 3)                   */
#define CLKTRIM_ICLR_HXT_FAULT_CLR_Msk    (0x8UL)                   /*!< CLKTRIM ICLR: HXT_FAULT_CLR (Bitfield-Mask: 0x01)     */
#define CLKTRIM_ICLR_HXT_FAULT_CLR				CLKTRIM_ICLR_HXT_FAULT_CLR_Msk
/* ========================================================  CALCON  ========================================================= */
#define CLKTRIM_CALCON_CALOVCNT_Pos       (0UL)                     /*!< CLKTRIM CALCON: CALOVCNT (Bit 0)                      */
#define CLKTRIM_CALCON_CALOVCNT_Msk       (0xffffUL)                /*!< CLKTRIM CALCON: CALOVCNT (Bitfield-Mask: 0xffff)      */
#define CLKTRIM_CALCON_CALOVCNT						CLKTRIM_CALCON_CALOVCNT_Msk

/* =========================================================================================================================== */
/* ================                                          OWIRE                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define OWIRE_CR_CLKDIV_Pos               (0UL)                     /*!< OWIRE CR: CLKDIV (Bit 0)                              */
#define OWIRE_CR_CLKDIV_Msk               (0x3UL)                   /*!< OWIRE CR: CLKDIV (Bitfield-Mask: 0x03)                */
#define OWIRE_CR_SIZE_Pos                 (4UL)                     /*!< OWIRE CR: SIZE (Bit 4)                                */
#define OWIRE_CR_SIZE_Msk                 (0x10UL)                  /*!< OWIRE CR: SIZE (Bitfield-Mask: 0x01)                  */
#define OWIRE_CR_EN_Pos                   (5UL)                     /*!< OWIRE CR: EN (Bit 5)                                  */
#define OWIRE_CR_EN_Msk                   (0x20UL)                  /*!< OWIRE CR: EN (Bitfield-Mask: 0x01)                    */
#define OWIRE_CR_MSBFIRST_Pos             (6UL)                     /*!< OWIRE CR: MSBRIRST (Bit 6)                            */
#define OWIRE_CR_MSBFIRST_Msk             (0x40UL)                  /*!< OWIRE CR: MSBRIRST (Bitfield-Mask: 0x01)              */
#define OWIRE_CR_RDMODE_Pos               (7UL)                     /*!< OWIRE CR: RDMODE (Bit 7)                              */
#define OWIRE_CR_RDMODE_Msk               (0x80UL)                  /*!< OWIRE CR: RDMODE (Bitfield-Mask: 0x01)                */
/* =========================================================  NFCR  ========================================================== */
#define OWIRE_NFCR_NFDIV_Pos              (0UL)                     /*!< OWIRE NFCR: NFDIV (Bit 0)                             */
#define OWIRE_NFCR_NFDIV_Msk              (0x3UL)                   /*!< OWIRE NFCR: NFDIV (Bitfield-Mask: 0x03)               */
#define OWIRE_NFCR_NFEN_Pos               (4UL)                     /*!< OWIRE NFCR: NFEN (Bit 4)                              */
#define OWIRE_NFCR_NFEN_Msk               (0x10UL)                  /*!< OWIRE NFCR: NFEN (Bitfield-Mask: 0x01)                */
/* ========================================================  RSTCNT  ========================================================= */
#define OWIRE_RSTCNT_RSTCNT_Pos           (0UL)                     /*!< OWIRE RSTCNT: RSTCNT (Bit 0)                          */
#define OWIRE_RSTCNT_RSTCNT_Msk           (0xffffUL)                /*!< OWIRE RSTCNT: RSTCNT (Bitfield-Mask: 0xffff)          */
/* ========================================================  PRESCNT  ======================================================== */
#define OWIRE_PRESCNT_PRESCNT_Pos         (0UL)                     /*!< OWIRE PRESCNT: PRESCNT (Bit 0)                        */
#define OWIRE_PRESCNT_PRESCNT_Msk         (0x1fffUL)                /*!< OWIRE PRESCNT: PRESCNT (Bitfield-Mask: 0x1fff)        */
/* ======================================================  BITRATECNT  ======================================================= */
#define OWIRE_BITRATECNT_BITRATECNT_Pos   (0UL)                     /*!< OWIRE BITRATECNT: BITRATECNT (Bit 0)                  */
#define OWIRE_BITRATECNT_BITRATECNT_Msk   (0xfffUL)                 /*!< OWIRE BITRATECNT: BITRATECNT (Bitfield-Mask: 0xfff)   */
/* ========================================================  DRVCNT  ========================================================= */
#define OWIRE_DRVCNT_DRVCNT_Pos           (0UL)                     /*!< OWIRE DRVCNT: DRVCNT (Bit 0)                          */
#define OWIRE_DRVCNT_DRVCNT_Msk           (0x1ffUL)                 /*!< OWIRE DRVCNT: DRVCNT (Bitfield-Mask: 0x1ff)           */
/* =======================================================  RDSMPCNT  ======================================================== */
#define OWIRE_RDSMPCNT_RDSMPCNT_Pos       (0UL)                     /*!< OWIRE RDSMPCNT: RDSMPCNT (Bit 0)                      */
#define OWIRE_RDSMPCNT_RDSMPCNT_Msk       (0x1ffUL)                 /*!< OWIRE RDSMPCNT: RDSMPCNT (Bitfield-Mask: 0x1ff)       */
/* ========================================================  RECCNT  ========================================================= */
#define OWIRE_RECCNT_RECCNT_Pos           (0UL)                     /*!< OWIRE RECCNT: RECCNT (Bit 0)                          */
#define OWIRE_RECCNT_RECCNT_Msk           (0x7ffUL)                 /*!< OWIRE RECCNT: RECCNT (Bitfield-Mask: 0x7ff)           */
/* =========================================================  DATA  ========================================================== */
#define OWIRE_DATA_DRVCNT_Pos             (0UL)                     /*!< OWIRE DATA: DRVCNT (Bit 0)                            */
#define OWIRE_DATA_DRVCNT_Msk             (0xffUL)                  /*!< OWIRE DATA: DRVCNT (Bitfield-Mask: 0xff)              */
/* ==========================================================  CMD  ========================================================== */
#define OWIRE_CMD_CMD_Pos                 (0UL)                     /*!< OWIRE CMD: CMD (Bit 0)                                */
#define OWIRE_CMD_CMD_Msk                 (0x3UL)                   /*!< OWIRE CMD: CMD (Bitfield-Mask: 0x03)                  */
/* =========================================================  INTEN  ========================================================= */
#define OWIRE_INTEN_ACKERREN_Pos          (0UL)                     /*!< OWIRE INTEN: ACKERREN (Bit 0)                         */
#define OWIRE_INTEN_ACKERREN_Msk          (0x1UL)                   /*!< OWIRE INTEN: ACKERREN (Bitfield-Mask: 0x01)           */
#define OWIRE_INTEN_INITEN_Pos            (1UL)                     /*!< OWIRE INTEN: INITEN (Bit 1)                           */
#define OWIRE_INTEN_INITEN_Msk            (0x2UL)                   /*!< OWIRE INTEN: INITEN (Bitfield-Mask: 0x01)             */
#define OWIRE_INTEN_TXDONEEN_Pos          (2UL)                     /*!< OWIRE INTEN: TXDONEEN (Bit 2)                         */
#define OWIRE_INTEN_TXDONEEN_Msk          (0x4UL)                   /*!< OWIRE INTEN: TXDONEEN (Bitfield-Mask: 0x01)           */
#define OWIRE_INTEN_RXDONEEN_Pos          (3UL)                     /*!< OWIRE INTEN: RXDONEEN (Bit 3)                         */
#define OWIRE_INTEN_RXDONEEN_Msk          (0x8UL)                   /*!< OWIRE INTEN: RXDONEEN (Bitfield-Mask: 0x01)           */
/* ==========================================================  SR  =========================================================== */
#define OWIRE_SR_ACKERR_Pos               (0UL)                     /*!< OWIRE SR: ACKERR (Bit 0)                              */
#define OWIRE_SR_ACKERR_Msk               (0x1UL)                   /*!< OWIRE SR: ACKERR (Bitfield-Mask: 0x01)                */
#define OWIRE_SR_INITDONE_Pos             (1UL)                     /*!< OWIRE SR: INITDONE (Bit 1)                            */
#define OWIRE_SR_INITDONE_Msk             (0x2UL)                   /*!< OWIRE SR: INITDONE (Bitfield-Mask: 0x01)              */
#define OWIRE_SR_TXDONE_Pos               (2UL)                     /*!< OWIRE SR: TXDONE (Bit 2)                              */
#define OWIRE_SR_TXDONE_Msk               (0x4UL)                   /*!< OWIRE SR: TXDONE (Bitfield-Mask: 0x01)                */
#define OWIRE_SR_RXDONE_Pos               (3UL)                     /*!< OWIRE SR: RXDONE (Bit 3)                              */
#define OWIRE_SR_RXDONE_Msk               (0x8UL)                   /*!< OWIRE SR: RXDONE (Bitfield-Mask: 0x01)                */
/* ========================================================  INTCLR  ========================================================= */
#define OWIRE_INTCLR_ACKERRCLR_Pos        (0UL)                     /*!< OWIRE INTCLR: ACKERRCLR (Bit 0)                       */
#define OWIRE_INTCLR_ACKERRCLR_Msk        (0x1UL)                   /*!< OWIRE INTCLR: ACKERRCLR (Bitfield-Mask: 0x01)         */
#define OWIRE_INTCLR_INTDONCECLR_Pos      (1UL)                     /*!< OWIRE INTCLR: INTDONCECLR (Bit 1)                     */
#define OWIRE_INTCLR_INTDONCECLR_Msk      (0x2UL)                   /*!< OWIRE INTCLR: INTDONCECLR (Bitfield-Mask: 0x01)       */
#define OWIRE_INTCLR_TXDONECLR_Pos        (2UL)                     /*!< OWIRE INTCLR: TXDONECLR (Bit 2)                       */
#define OWIRE_INTCLR_TXDONECLR_Msk        (0x4UL)                   /*!< OWIRE INTCLR: TXDONECLR (Bitfield-Mask: 0x01)         */
#define OWIRE_INTCLR_RXDONECLR_Pos        (3UL)                     /*!< OWIRE INTCLR: RXDONECLR (Bit 3)                       */
#define OWIRE_INTCLR_RXDONECLR_Msk        (0x8UL)                   /*!< OWIRE INTCLR: RXDONECLR (Bitfield-Mask: 0x01)         */


/* =========================================================================================================================== */
/* ================                                            SPI                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define SPI_CR_SPR0_Pos                   (0UL)                     /*!< SPI CR: SPR0 (Bit 0)                                  */
#define SPI_CR_SPR0_Msk                   (0x1UL)                   /*!< SPI CR: SPR0 (Bitfield-Mask: 0x01)                    */
#define SPI_CR_SPR0                        SPI_CR_SPR0_Msk 
#define SPI_CR_SPR1_Pos                   (1UL)                     /*!< SPI CR: SPR1 (Bit 1)                                  */
#define SPI_CR_SPR1_Msk                   (0x2UL)                   /*!< SPI CR: SPR1 (Bitfield-Mask: 0x01)                    */
#define SPI_CR_SPR1                       SPI_CR_SPR1_Msk
#define SPI_CR_CPHA_Pos                   (2UL)                     /*!< SPI CR: CPHA (Bit 2)                                  */
#define SPI_CR_CPHA_Msk                   (0x4UL)                   /*!< SPI CR: CPHA (Bitfield-Mask: 0x01)                    */
#define SPI_CR_CPHA                       SPI_CR_CPHA_Msk           
#define SPI_CR_CPOL_Pos                   (3UL)                     /*!< SPI CR: CPOL (Bit 3)                                  */
#define SPI_CR_CPOL_Msk                   (0x8UL)                   /*!< SPI CR: CPOL (Bitfield-Mask: 0x01)                    */
#define SPI_CR_CPOL                       SPI_CR_CPOL_Msk
#define SPI_CR_MSTR_Pos                   (4UL)                     /*!< SPI CR: MSTR (Bit 4)                                  */
#define SPI_CR_MSTR_Msk                   (0x10UL)                  /*!< SPI CR: MSTR (Bitfield-Mask: 0x01)                    */
#define SPI_CR_MSTR                       SPI_CR_MSTR_Msk
#define SPI_CR_SPEN_Pos                   (6UL)                     /*!< SPI CR: SPEN (Bit 6)                                  */
#define SPI_CR_SPEN_Msk                   (0x40UL)                  /*!< SPI CR: SPEN (Bitfield-Mask: 0x01)                    */
#define SPI_CR_SPEN                       SPI_CR_SPEN_Msk
#define SPI_CR_SPR2_Pos                   (7UL)                     /*!< SPI CR: SPR2 (Bit 7)                                  */
#define SPI_CR_SPR2_Msk                   (0x80UL)                  /*!< SPI CR: SPR2 (Bitfield-Mask: 0x01)                    */
#define SPI_CR_SPR2                        SPI_CR_SPR2_Msk
/* ==========================================================  SSN  ========================================================== */
#define SPI_SSN_SSN_Pos                   (0UL)                     /*!< SPI SSN: SSN (Bit 0)                                  */
#define SPI_SSN_SSN_Msk                   (0x1UL)                   /*!< SPI SSN: SSN (Bitfield-Mask: 0x01)                    */
#define SPI_SSN_SSN                       SPI_SSN_SSN_Msk
/* ==========================================================  SR  =========================================================== */
#define SPI_SR_MDF_Pos                    (4UL)                     /*!< SPI SR: MDF (Bit 4)                                   */
#define SPI_SR_MDF_Msk                    (0x10UL)                  /*!< SPI SR: MDF (Bitfield-Mask: 0x01)                     */
#define SPI_SR_MDF                        SPI_SR_MDF_Msk 
#define SPI_SR_SSERR_Pos                  (5UL)                     /*!< SPI SR: SSERR (Bit 5)                                 */
#define SPI_SR_SSERR_Msk                  (0x20UL)                  /*!< SPI SR: SSERR (Bitfield-Mask: 0x01)                   */
#define SPI_SR_SSERR                      SPI_SR_SSERR_Msk 
#define SPI_SR_WCOL_Pos                   (6UL)                     /*!< SPI SR: WCOL (Bit 6)                                  */
#define SPI_SR_WCOL_Msk                   (0x40UL)                  /*!< SPI SR: WCOL (Bitfield-Mask: 0x01)                    */
#define SPI_SR_WCOL                       SPI_SR_WCOL_Msk
#define SPI_SR_SPIF_Pos                   (7UL)                     /*!< SPI SR: SPIF (Bit 7)                                  */
#define SPI_SR_SPIF_Msk                   (0x80UL)                  /*!< SPI SR: SPIF (Bitfield-Mask: 0x01)                    */
#define SPI_SR_SPIF                        SPI_SR_SPIF_Msk 
/* =========================================================  DATA  ========================================================== */
#define SPI_DATA_SPDATA_Pos               (0UL)                     /*!< SPI DATA: SPDATA (Bit 0)                              */
#define SPI_DATA_SPDATA_Msk               (0xffUL)                  /*!< SPI DATA: SPDATA (Bitfield-Mask: 0xff)                */


/* =========================================================================================================================== */
/* ================                                            I2C                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define I2C_CR_H1M_Pos                    (0UL)                     /*!< I2C CR: H1M (Bit 0)                                   */
#define I2C_CR_H1M_Msk                    (0x1UL)                   /*!< I2C CR: H1M (Bitfield-Mask: 0x01)                     */
#define I2C_CR_H1M                         I2C_CR_H1M_Msk 
#define I2C_CR_AA_Pos                     (2UL)                     /*!< I2C CR: AA (Bit 2)                                    */
#define I2C_CR_AA_Msk                     (0x4UL)                   /*!< I2C CR: AA (Bitfield-Mask: 0x01)                      */
#define I2C_CR_AA                          I2C_CR_AA_Msk   
#define I2C_CR_SI_Pos                     (3UL)                     /*!< I2C CR: SI (Bit 3)                                    */
#define I2C_CR_SI_Msk                     (0x8UL)                   /*!< I2C CR: SI (Bitfield-Mask: 0x01)                      */
#define I2C_CR_SI                          I2C_CR_SI_Msk  
#define I2C_CR_STO_Pos                    (4UL)                     /*!< I2C CR: STO (Bit 4)                                   */
#define I2C_CR_STO_Msk                    (0x10UL)                  /*!< I2C CR: STO (Bitfield-Mask: 0x01)                     */
#define I2C_CR_STO                        I2C_CR_STO_Msk
#define I2C_CR_STA_Pos                    (5UL)                     /*!< I2C CR: STA (Bit 5)                                   */
#define I2C_CR_STA_Msk                    (0x20UL)                  /*!< I2C CR: STA (Bitfield-Mask: 0x01)                     */
#define I2C_CR_STA                        I2C_CR_STA_Msk
#define I2C_CR_ENS_Pos                    (6UL)                     /*!< I2C CR: ENS (Bit 6)                                   */
#define I2C_CR_ENS_Msk                    (0x40UL)                  /*!< I2C CR: ENS (Bitfield-Mask: 0x01)                     */
#define I2C_CR_ENS                        I2C_CR_ENS_Msk 
/* =========================================================  DATA  ========================================================== */
#define I2C_DATA_DAT_Pos                  (0UL)                     /*!< I2C DATA: DAT (Bit 0)                                 */
#define I2C_DATA_DAT_Msk                  (0xffUL)                  /*!< I2C DATA: DAT (Bitfield-Mask: 0xff)                   */
/* =========================================================  ADDR  ========================================================== */
#define I2C_ADDR_GC_Pos                   (0UL)                     /*!< I2C ADDR: GC (Bit 0)                                  */
#define I2C_ADDR_GC_Msk                   (0x1UL)                   /*!< I2C ADDR: GC (Bitfield-Mask: 0x01)                    */
#define I2C_ADDR_GC                       I2C_ADDR_GC_Msk
#define I2C_ADDR_I2CADR_Pos               (1UL)                     /*!< I2C ADDR: I2CADR (Bit 1)                              */
#define I2C_ADDR_I2CADR_Msk               (0xfeUL)                  /*!< I2C ADDR: I2CADR (Bitfield-Mask: 0x7f)                */
/* ==========================================================  SR  =========================================================== */
#define I2C_SR_I2CSTA_Pos                 (0UL)                     /*!< I2C SR: I2CSTA (Bit 0)                                */
#define I2C_SR_I2CSTA_Msk                 (0xffUL)                  /*!< I2C SR: I2CSTA (Bitfield-Mask: 0xff)                  */
/* ========================================================  TIMRUN  ========================================================= */
#define I2C_TIMRUN_TME_Pos                (0UL)                     /*!< I2C TIMRUN: TME (Bit 0)                               */
#define I2C_TIMRUN_TME_Msk                (0x1UL)                   /*!< I2C TIMRUN: TME (Bitfield-Mask: 0x01)                 */
#define I2C_TIMRUN_TME                    I2C_TIMRUN_TME_Msk
/* ========================================================  BAUDCR  ========================================================= */
#define I2C_BAUDCR_TM_Pos                 (0UL)                     /*!< I2C BAUDCR: TM (Bit 0)                                */
#define I2C_BAUDCR_TM_Msk                 (0xffUL)                  /*!< I2C BAUDCR: TM (Bitfield-Mask: 0xff)                  */
#define I2C_BAUDCR_TM                 		I2C_BAUDCR_TM_Msk 


/* =========================================================================================================================== */
/* ================                                          LPUART                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  SBUF  ========================================================== */
#define LPUART_SBUF_SBUF_Pos              (0UL)                     /*!< LPUART SBUF: SBUF (Bit 0)                             */
#define LPUART_SBUF_SBUF_Msk              (0xffUL)                  /*!< LPUART SBUF: SBUF (Bitfield-Mask: 0xff)               */
#define LPUART_SBUF_SBUF									LPUART_SBUF_SBUF_Msk
/* =========================================================  SADDR  ========================================================= */
#define LPUART_SADDR_SADDR_Pos            (0UL)                     /*!< LPUART SADDR: SADDR (Bit 0)                           */
#define LPUART_SADDR_SADDR_Msk            (0xffUL)                  /*!< LPUART SADDR: SADDR (Bitfield-Mask: 0xff)             */
#define LPUART_SADDR_SADDR								LPUART_SADDR_SADDR_Msk
/* =========================================================  SADEN  ========================================================= */
#define LPUART_SADEN_SADEN_Pos            (0UL)                     /*!< LPUART SADEN: SADEN (Bit 0)                           */
#define LPUART_SADEN_SADEN_Msk            (0xffUL)                  /*!< LPUART SADEN: SADEN (Bitfield-Mask: 0xff)             */
#define LPUART_SADEN_SADEN								LPUART_SADEN_SADEN_Msk
/* =========================================================  INTSR  ========================================================= */
#define LPUART_INTSR_RI_Pos               (0UL)                     /*!< LPUART INTSR: RI (Bit 0)                              */
#define LPUART_INTSR_RI_Msk               (0x1UL)                   /*!< LPUART INTSR: RI (Bitfield-Mask: 0x01)                */
#define LPUART_INTSR_RI										LPUART_INTSR_RI_Msk
#define LPUART_INTSR_TI_Pos               (1UL)                     /*!< LPUART INTSR: TI (Bit 1)                              */
#define LPUART_INTSR_TI_Msk               (0x2UL)                   /*!< LPUART INTSR: TI (Bitfield-Mask: 0x01)                */
#define LPUART_INTSR_TI										LPUART_INTSR_TI_Msk
#define LPUART_INTSR_FE_Pos               (2UL)                     /*!< LPUART INTSR: FE (Bit 2)                              */
#define LPUART_INTSR_FE_Msk               (0x4UL)                   /*!< LPUART INTSR: FE (Bitfield-Mask: 0x01)                */
#define LPUART_INTSR_FE										LPUART_INTSR_FE_Msk
/* =========================================================  SCON  ========================================================== */
#define LPUART_SCON_RIEN_Pos              (0UL)                     /*!< LPUART SCON: RIEN (Bit 0)                             */
#define LPUART_SCON_RIEN_Msk              (0x1UL)                   /*!< LPUART SCON: RIEN (Bitfield-Mask: 0x01)               */
#define LPUART_SCON_RIEN									LPUART_SCON_RIEN_Msk
#define LPUART_SCON_TIEN_Pos              (1UL)                     /*!< LPUART SCON: TIEN (Bit 1)                             */
#define LPUART_SCON_TIEN_Msk              (0x2UL)                   /*!< LPUART SCON: TIEN (Bitfield-Mask: 0x01)               */
#define LPUART_SCON_TIEN									LPUART_SCON_TIEN_Msk
#define LPUART_SCON_RB8_Pos               (2UL)                     /*!< LPUART SCON: RB8 (Bit 2)                              */
#define LPUART_SCON_RB8_Msk               (0x4UL)                   /*!< LPUART SCON: RB8 (Bitfield-Mask: 0x01)                */
#define LPUART_SCON_RB8										LPUART_SCON_RB8_Msk
#define LPUART_SCON_TB8_Pos               (3UL)                     /*!< LPUART SCON: TB8 (Bit 3)                              */
#define LPUART_SCON_TB8_Msk               (0x8UL)                   /*!< LPUART SCON: TB8 (Bitfield-Mask: 0x01)                */
#define LPUART_SCON_TB8										LPUART_SCON_TB8_Msk
#define LPUART_SCON_REN_Pos               (4UL)                     /*!< LPUART SCON: REN (Bit 4)                              */
#define LPUART_SCON_REN_Msk               (0x10UL)                  /*!< LPUART SCON: REN (Bitfield-Mask: 0x01)                */
#define LPUART_SCON_REN										LPUART_SCON_REN_Msk
#define LPUART_SCON_SM2_Pos               (5UL)                     /*!< LPUART SCON: SM2 (Bit 5)                              */
#define LPUART_SCON_SM2_Msk               (0x20UL)                  /*!< LPUART SCON: SM2 (Bitfield-Mask: 0x01)                */
#define LPUART_SCON_SM2										LPUART_SCON_SM2_Msk
#define LPUART_SCON_SM0_SM1_Pos           (6UL)                     /*!< LPUART SCON: SM0_SM1 (Bit 6)                          */
#define LPUART_SCON_SM0_SM1_Msk           (0x40UL)                  /*!< LPUART SCON: SM0_SM1 (Bitfield-Mask: 0x01)            */
#define LPUART_SCON_SM0_SM1								LPUART_SCON_SM0_SM1_Msk
#define LPUART_SCON_SM0_SM1_1							(0x1 << LPUART_SCON_SM0_SM1_Pos)
#define LPUART_SCON_SM0_SM1_0							(0x2 << LPUART_SCON_SM0_SM1_Pos)
#define LPUART_SCON_TEEN_Pos              (8UL)                     /*!< LPUART SCON: TEEN (Bit 8)                             */
#define LPUART_SCON_TEEN_Msk              (0x100UL)                 /*!< LPUART SCON: TEEN (Bitfield-Mask: 0x01)               */
#define LPUART_SCON_TEEN									LPUART_SCON_TEEN_Msk
#define LPUART_SCON_DBAUD_Pos             (9UL)                     /*!< LPUART SCON: DBAUD (Bit 9)                            */
#define LPUART_SCON_DBAUD_Msk             (0x200UL)                 /*!< LPUART SCON: DBAUD (Bitfield-Mask: 0x01)              */
#define LPUART_SCON_DBAUD									LPUART_SCON_DBAUD_Msk
#define LPUART_SCON_LPMODE_Pos            (10UL)                    /*!< LPUART SCON: LPMODE (Bit 10)                          */
#define LPUART_SCON_LPMODE_Msk            (0x400UL)                 /*!< LPUART SCON: LPMODE (Bitfield-Mask: 0x01)             */
#define LPUART_SCON_LPMODE								LPUART_SCON_LPMODE_Msk
#define LPUART_SCON_SCLKSEL_Pos           (11UL)                    /*!< LPUART SCON: SCLKSEL (Bit 11)                         */
#define LPUART_SCON_SCLKSEL_Msk           (0x1800UL)                /*!< LPUART SCON: SCLKSEL (Bitfield-Mask: 0x03)            */
#define LPUART_SCON_SCLKSEL								LPUART_SCON_SCLKSEL_Msk
#define LPUART_SCON_SCLKSEL_0							(0x1 << LPUART_SCON_SCLKSEL_Pos)
#define LPUART_SCON_SCLKSEL_1							(0x2 << LPUART_SCON_SCLKSEL_Pos)
#define LPUART_SCON_PRSC_Pos              (13UL)                    /*!< LPUART SCON: PRSC (Bit 13)                            */
#define LPUART_SCON_PRSC_Msk              (0xe000UL)                /*!< LPUART SCON: PRSC (Bitfield-Mask: 0x07)               */
#define LPUART_SCON_PRSC									LPUART_SCON_PRSC_Msk
#define LPUART_SCON_PRSC_0								(0x1 << LPUART_SCON_PRSC_Pos)
#define LPUART_SCON_PRSC_1								(0x2 << LPUART_SCON_PRSC_Pos)
#define LPUART_SCON_PRSC_2								(0x4 << LPUART_SCON_PRSC_Pos)
#define LPUART_SCON_EN_Pos                (16UL)                    /*!< LPUART SCON: EN (Bit 16)                              */
#define LPUART_SCON_EN_Msk                (0x10000UL)               /*!< LPUART SCON: EN (Bitfield-Mask: 0x01)                 */
#define LPUART_SCON_EN										LPUART_SCON_EN_Msk
/* ========================================================  INTCLR  ========================================================= */
#define LPUART_INTCLR_RICLR_Pos           (0UL)                     /*!< LPUART INTCLR: RICLR (Bit 0)                          */
#define LPUART_INTCLR_RICLR_Msk           (0x1UL)                   /*!< LPUART INTCLR: RICLR (Bitfield-Mask: 0x01)            */
#define LPUART_INTCLR_RICLR								LPUART_INTCLR_RICLR_Msk
#define LPUART_INTCLR_TICLR_Pos           (1UL)                     /*!< LPUART INTCLR: TICLR (Bit 1)                          */
#define LPUART_INTCLR_TICLR_Msk           (0x2UL)                   /*!< LPUART INTCLR: TICLR (Bitfield-Mask: 0x01)            */
#define LPUART_INTCLR_TICLR								LPUART_INTCLR_TICLR_Msk
#define LPUART_INTCLR_FECLR_Pos           (2UL)                     /*!< LPUART INTCLR: FECLR (Bit 2)                          */
#define LPUART_INTCLR_FECLR_Msk           (0x4UL)                   /*!< LPUART INTCLR: FECLR (Bitfield-Mask: 0x01)            */
#define LPUART_INTCLR_FECLR								LPUART_INTCLR_FECLR_Msk
/* ========================================================  BAUDCR  ========================================================= */
#define LPUART_BAUDCR_BRG_Pos             (0UL)                     /*!< LPUART BAUDCR: BRG (Bit 0)                            */
#define LPUART_BAUDCR_BRG_Msk             (0xffffUL)                /*!< LPUART BAUDCR: BRG (Bitfield-Mask: 0xffff)            */
#define LPUART_BAUDCR_BRG									LPUART_BAUDCR_BRG_Msk
#define LPUART_BAUDCR_SELF_BRG_Pos        (16UL)                    /*!< LPUART BAUDCR: SELF_BRG (Bit 16)                      */
#define LPUART_BAUDCR_SELF_BRG_Msk        (0x10000UL)               /*!< LPUART BAUDCR: SELF_BRG (Bitfield-Mask: 0x01)         */
#define LPUART_BAUDCR_SELF_BRG						LPUART_BAUDCR_SELF_BRG_Msk

/* =========================================================================================================================== */
/* ================                                           UART                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  SCON  ========================================================== */
#define UART_SCON_RIEN_Pos                (0UL)                     /*!< UART SCON: RIEN (Bit 0)                               */
#define UART_SCON_RIEN_Msk                (0x1UL)                   /*!< UART SCON: RIEN (Bitfield-Mask: 0x01)                 */
#define UART_SCON_RIEN										UART_SCON_RIEN_Msk
#define UART_SCON_TIEN_Pos                (1UL)                     /*!< UART SCON: TIEN (Bit 1)                               */
#define UART_SCON_TIEN_Msk                (0x2UL)                   /*!< UART SCON: TIEN (Bitfield-Mask: 0x01)                 */
#define UART_SCON_TIEN										UART_SCON_TIEN_Msk
#define UART_SCON_RB8_Pos                 (2UL)                     /*!< UART SCON: RB8 (Bit 2)                                */
#define UART_SCON_RB8_Msk                 (0x4UL)                   /*!< UART SCON: RB8 (Bitfield-Mask: 0x01)                  */
#define UART_SCON_RB8											UART_SCON_RB8_Msk
#define UART_SCON_TB8_Pos                 (3UL)                     /*!< UART SCON: TB8 (Bit 3)                                */
#define UART_SCON_TB8_Msk                 (0x8UL)                   /*!< UART SCON: TB8 (Bitfield-Mask: 0x01)                  */
#define UART_SCON_TB8											UART_SCON_TB8_Msk
#define UART_SCON_REN_Pos                 (4UL)                     /*!< UART SCON: REN (Bit 4)                                */
#define UART_SCON_REN_Msk                 (0x10UL)                  /*!< UART SCON: REN (Bitfield-Mask: 0x01)                  */
#define UART_SCON_REN											UART_SCON_REN_Msk
#define UART_SCON_SM2_Pos                 (5UL)                     /*!< UART SCON: SM2 (Bit 5)                                */
#define UART_SCON_SM2_Msk                 (0x20UL)                  /*!< UART SCON: SM2 (Bitfield-Mask: 0x01)                  */
#define UART_SCON_SM0_SM1_Pos             (6UL)                     /*!< UART SCON: SM0_SM1 (Bit 6)                            */
#define UART_SCON_SM0_SM1_Msk             (0xc0UL)                  /*!< UART SCON: SM0_SM1 (Bitfield-Mask: 0x03)              */
#define UART_SCON_SM0_SM1									UART_SCON_SM0_SM1_Msk
#define UART_SCON_SM0_SM1_0								(0x2 << UART_SCON_SM0_SM1_Pos)
#define UART_SCON_SM0_SM1_1								(0x1 << UART_SCON_SM0_SM1_Pos)
#define UART_SCON_DBAUD_Pos               (9UL)                     /*!< UART SCON: DBAUD (Bit 9)                              */
#define UART_SCON_DBAUD_Msk               (0x200UL)                 /*!< UART SCON: DBAUD (Bitfield-Mask: 0x01)                */
#define UART_SCON_DBAUD										UART_SCON_DBAUD_Msk
/* =========================================================  SBUF  ========================================================== */
#define UART_SBUF_SBUF_Pos                (0UL)                     /*!< UART SBUF: SBUF (Bit 0)                               */
#define UART_SBUF_SBUF_Msk                (0xffUL)                  /*!< UART SBUF: SBUF (Bitfield-Mask: 0xff)                 */
#define UART_SBUF_SBUF										UART_SBUF_SBUF_Msk
/* =========================================================  SADDR  ========================================================= */
#define UART_SADDR_SADDR_Pos              (0UL)                     /*!< UART SADDR: SADDR (Bit 0)                             */
#define UART_SADDR_SADDR_Msk              (0xffUL)                  /*!< UART SADDR: SADDR (Bitfield-Mask: 0xff)               */
/* =========================================================  SADEN  ========================================================= */
#define UART_SADEN_SADEN_Pos              (0UL)                     /*!< UART SADEN: SADEN (Bit 0)                             */
#define UART_SADEN_SADEN_Msk              (0xffUL)                  /*!< UART SADEN: SADEN (Bitfield-Mask: 0xff)               */
/* =========================================================  INTSR  ========================================================= */
#define UART_INTSR_RI_Pos                 (0UL)                     /*!< UART INTSR: RI (Bit 0)                                */
#define UART_INTSR_RI_Msk                 (0x1UL)                   /*!< UART INTSR: RI (Bitfield-Mask: 0x01)                  */
#define UART_INTSR_RI											UART_INTSR_RI_Msk
#define UART_INTSR_TI_Pos                 (1UL)                     /*!< UART INTSR: TI (Bit 1)                                */
#define UART_INTSR_TI_Msk                 (0x2UL)                   /*!< UART INTSR: TI (Bitfield-Mask: 0x01)                  */
#define UART_INTSR_TI											UART_INTSR_TI_Msk
#define UART_INTSR_FE_Pos                 (2UL)                     /*!< UART INTSR: FE (Bit 2)                                */
#define UART_INTSR_FE_Msk                 (0x4UL)                   /*!< UART INTSR: FE (Bitfield-Mask: 0x01)                  */
#define UART_INTSR_FE											UART_INTSR_FE_Msk
/* ========================================================  INTCLR  ========================================================= */
#define UART_INTCLR_RICLR_Pos             (0UL)                     /*!< UART INTCLR: RICLR (Bit 0)                            */
#define UART_INTCLR_RICLR_Msk             (0x1UL)                   /*!< UART INTCLR: RICLR (Bitfield-Mask: 0x01)              */
#define UART_INTCLR_TICLR_Pos             (1UL)                     /*!< UART INTCLR: TICLR (Bit 1)                            */
#define UART_INTCLR_TICLR_Msk             (0x2UL)                   /*!< UART INTCLR: TICLR (Bitfield-Mask: 0x01)              */
#define UART_INTCLR_FECLR_Pos             (2UL)                     /*!< UART INTCLR: FECLR (Bit 2)                            */
#define UART_INTCLR_FECLR_Msk             (0x4UL)                   /*!< UART INTCLR: FECLR (Bitfield-Mask: 0x01)              */
/* ========================================================  BAUDCR  ========================================================= */
#define UART_BAUDCR_BRG_Pos               (0UL)                     /*!< UART BAUDCR: BRG (Bit 0)                              */
#define UART_BAUDCR_BRG_Msk               (0xffffUL)                /*!< UART BAUDCR: BRG (Bitfield-Mask: 0xffff)              */
#define UART_BAUDCR_BRG										UART_BAUDCR_BRG_Msk
#define UART_BAUDCR_SELF_BRG_Pos          (16UL)                    /*!< UART BAUDCR: SELF_BRG (Bit 16)                        */
#define UART_BAUDCR_SELF_BRG_Msk          (0x10000UL)               /*!< UART BAUDCR: SELF_BRG (Bitfield-Mask: 0x01)           */
#define UART_BAUDCR_SELF_BRG							UART_BAUDCR_SELF_BRG_Msk
#define UART_BAUDCR_NOREF_Pos             (31UL)                    /*!< UART BAUDCR: NOREF (Bit 31)                           */
#define UART_BAUDCR_NOREF_Msk             (0x80000000UL)            /*!< UART BAUDCR: NOREF (Bitfield-Mask: 0x01)              */
/* ========================================================  IRDACR  ========================================================= */
#define UART_IRDACR_PSC_Pos               (0UL)                     /*!< UART IRDACR: PSC (Bit 0)                              */
#define UART_IRDACR_PSC_Msk               (0xffUL)                  /*!< UART IRDACR: PSC (Bitfield-Mask: 0xff)                */
#define UART_IRDACR_IREN_Pos              (8UL)                     /*!< UART IRDACR: IREN (Bit 8)                             */
#define UART_IRDACR_IREN_Msk              (0x100UL)                 /*!< UART IRDACR: IREN (Bitfield-Mask: 0x01)               */
#define UART_IRDACR_IRTXINV_Pos           (9UL)                     /*!< UART IRDACR: IRTXINV (Bit 9)                          */
#define UART_IRDACR_IRTXINV_Msk           (0x200UL)                 /*!< UART IRDACR: IRTXINV (Bitfield-Mask: 0x01)            */
#define UART_IRDACR_IRRXINV_Pos           (10UL)                    /*!< UART IRDACR: IRRXINV (Bit 10)                         */
#define UART_IRDACR_IRRXINV_Msk           (0x400UL)                 /*!< UART IRDACR: IRRXINV (Bitfield-Mask: 0x01)            */
#define UART_IRDACR_IRLPMODE_Pos          (11UL)                    /*!< UART IRDACR: IRLPMODE (Bit 11)                        */
#define UART_IRDACR_IRLPMODE_Msk          (0x800UL)                 /*!< UART IRDACR: IRLPMODE (Bitfield-Mask: 0x01)           */


/* =========================================================================================================================== */
/* ================                                           WWDG                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  RLOAD  ========================================================= */
#define WWDG_RLOAD_RLOAD_Pos              (0UL)                     /*!< WWDG RLOAD: RLOAD (Bit 0)                             */
#define WWDG_RLOAD_RLOAD_Msk              (0xffUL)                  /*!< WWDG RLOAD: RLOAD (Bitfield-Mask: 0xff)               */
#define WWDG_RLOAD_RLOAD										WWDG_RLOAD_RLOAD_Msk              
/* ==========================================================  CR  =========================================================== */
#define WWDG_CR_WINCMP_Pos                (0UL)                     /*!< WWDG CR: WINCMP (Bit 0)                               */
#define WWDG_CR_WINCMP_Msk                (0xffUL)                  /*!< WWDG CR: WINCMP (Bitfield-Mask: 0xff)                 */
#define WWDG_CR_WINCMP										WWDG_CR_WINCMP_Msk
#define WWDG_CR_PRSC_Pos                  (8UL)                     /*!< WWDG CR: PRSC (Bit 8)                                 */
#define WWDG_CR_PRSC_Msk                  (0xfffff00UL)             /*!< WWDG CR: PRSC (Bitfield-Mask: 0xfffff)                */
#define WWDG_CR_PRSC											 WWDG_CR_PRSC_Msk
#define WWDG_CR_WWDGEN_Pos                (28UL)                    /*!< WWDG CR: WWDGEN (Bit 28)                              */
#define WWDG_CR_WWDGEN_Msk                (0x10000000UL)            /*!< WWDG CR: WWDGEN (Bitfield-Mask: 0x01)                 */
#define WWDG_CR_WWDGEN										WWDG_CR_WWDGEN_Msk
/* =========================================================  INTEN  ========================================================= */
#define WWDG_INTEN_WWDGIEN_Pos            (0UL)                     /*!< WWDG INTEN: WWDGIEN (Bit 0)                           */
#define WWDG_INTEN_WWDGIEN_Msk            (0x1UL)                   /*!< WWDG INTEN: WWDGIEN (Bitfield-Mask: 0x01)             */
#define WWDG_INTEN_WWDGIEN								WWDG_INTEN_WWDGIEN_Msk 
/* ==========================================================  SR  =========================================================== */
#define WWDG_SR_WWDGIF_Pos                (0UL)                     /*!< WWDG SR: WWDGIF (Bit 0)                               */
#define WWDG_SR_WWDGIF_Msk                (0x1UL)                   /*!< WWDG SR: WWDGIF (Bitfield-Mask: 0x01)                 */
#define WWDG_SR_WWDGIF											WWDG_SR_WWDGIF_Msk
/* ========================================================  INTCLR  ========================================================= */
#define WWDG_INTCLR_INTCLR_Pos            (0UL)                     /*!< WWDG INTCLR: INTCLR (Bit 0)                           */
#define WWDG_INTCLR_INTCLR_Msk            (0x1UL)                   /*!< WWDG INTCLR: INTCLR (Bitfield-Mask: 0x01)             */
#define WWDG_INTCLR_INTCLR								WWDG_INTCLR_INTCLR_Msk 
/* ========================================================  CNTVAL  ========================================================= */
#define WWDG_CNTVAL_WWDGCNT_Pos           (0UL)                     /*!< WWDG CNTVAL: WWDGCNT (Bit 0)                          */
#define WWDG_CNTVAL_WWDGCNT_Msk           (0xffUL)                  /*!< WWDG CNTVAL: WWDGCNT (Bitfield-Mask: 0xff)            */
#define WWDG_CNTVAL_WWDGCNT								 WWDG_CNTVAL_WWDGCNT_Msk 

/* =========================================================================================================================== */
/* ================                                           IWDG                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  CMDCR  ========================================================= */
#define IWDG_CMDCR_CMD_Pos                (0UL)                     /*!< IWDG CMDCR: CMD (Bit 0)                               */
#define IWDG_CMDCR_CMD_Msk                (0xffUL)                  /*!< IWDG CMDCR: CMD (Bitfield-Mask: 0xff)                 */
/* =========================================================  CFGR  ========================================================== */
#define IWDG_CFGR_IWDGMODE_Pos            (0UL)                     /*!< IWDG CFGR: IWDGMODE (Bit 0)                           */
#define IWDG_CFGR_IWDGMODE_Msk            (0x1UL)                   /*!< IWDG CFGR: IWDGMODE (Bitfield-Mask: 0x01)             */
#define IWDG_CFGR_IWDGMODE								IWDG_CFGR_IWDGMODE_Msk
#define IWDG_CFGR_IWDGINTMSK_Pos          (1UL)                     /*!< IWDG CFGR: IWDGINTMSK (Bit 1)                         */
#define IWDG_CFGR_IWDGINTMSK_Msk          (0x2UL)                   /*!< IWDG CFGR: IWDGINTMSK (Bitfield-Mask: 0x01)           */
#define IWDG_CFGR_IWDGINTMSK							IWDG_CFGR_IWDGINTMSK_Msk 
#define IWDG_CFGR_IWDGRUNF_Pos            (2UL)                     /*!< IWDG CFGR: IWDGRUNF (Bit 2)                           */
#define IWDG_CFGR_IWDGRUNF_Msk            (0x4UL)                   /*!< IWDG CFGR: IWDGRUNF (Bitfield-Mask: 0x01)             */
/* =========================================================  RLOAD  ========================================================= */
#define IWDG_RLOAD_IWDGRLOAD_Pos          (0UL)                     /*!< IWDG RLOAD: IWDGRLOAD (Bit 0)                         */
#define IWDG_RLOAD_IWDGRLOAD_Msk          (0xfffffUL)               /*!< IWDG RLOAD: IWDGRLOAD (Bitfield-Mask: 0xfffff)        */
#define IWDG_RLOAD_IWDGRLOAD              IWDG_RLOAD_IWDGRLOAD_Msk 
/* ========================================================  CNTVAL  ========================================================= */
#define IWDG_CNTVAL_IWDGCNT_Pos           (0UL)                     /*!< IWDG CNTVAL: IWDGCNT (Bit 0)                          */
#define IWDG_CNTVAL_IWDGCNT_Msk           (0xfffffUL)               /*!< IWDG CNTVAL: IWDGCNT (Bitfield-Mask: 0xfffff)         */
#define IWDG_CNTVAL_IWDGCNT			      IWDG_CNTVAL_IWDGCNT_Msk

/* ==========================================================  SR  =========================================================== */
#define IWDG_SR_IWDGOVF_Pos               (0UL)                     /*!< IWDG SR: IWDGOVF (Bit 0)                              */
#define IWDG_SR_IWDGOVF_Msk               (0x1UL)                   /*!< IWDG SR: IWDGOVF (Bitfield-Mask: 0x01)                */
/* ========================================================  INTCLR  ========================================================= */
#define IWDG_INTCLR_IWDGINTCLR_Pos        (0UL)                     /*!< IWDG INTCLR: IWDGINTCLR (Bit 0)                       */
#define IWDG_INTCLR_IWDGINTCLR_Msk        (0x1UL)                   /*!< IWDG INTCLR: IWDGINTCLR (Bitfield-Mask: 0x01)         */
/* ========================================================  UNLOCK  ========================================================= */
#define IWDG_UNLOCK_IWDGREN_Pos           (0UL)                     /*!< IWDG UNLOCK: IWDGREN (Bit 0)                          */
#define IWDG_UNLOCK_IWDGREN_Msk           (0x1UL)                   /*!< IWDG UNLOCK: IWDGREN (Bitfield-Mask: 0x01)            */
/* =========================================================================================================================== */
/* ================                                           BEEP                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CSR  ========================================================== */
#define BEEP_CSR_BEEPDIV_Pos              (0UL)                     /*!< BEEP CSR: BEEPDIV (Bit 0)                             */
#define BEEP_CSR_BEEPDIV_Msk              (0xfffUL)                 /*!< BEEP CSR: BEEPDIV (Bitfield-Mask: 0xfff)              */
#define BEEP_CSR_BEEPDIV									 BEEP_CSR_BEEPDIV_Msk
#define BEEP_CSR_BEEPSEL_Pos              (16UL)                    /*!< BEEP CSR: BEEPSEL (Bit 16)                            */
#define BEEP_CSR_BEEPSEL_Msk              (0x30000UL)               /*!< BEEP CSR: BEEPSEL (Bitfield-Mask: 0x03)               */
#define BEEP_CSR_BEEPSEL									 BEEP_CSR_BEEPSEL_Msk
#define BEEP_CSR_BEEPSEL_0								(0x1 << BEEP_CSR_BEEPSEL_Pos)				 
#define BEEP_CSR_BEEPSEL_1								(0x2 << BEEP_CSR_BEEPSEL_Pos)
#define BEEP_CSR_BEEPEN_Pos               (18UL)                    /*!< BEEP CSR: BEEPEN (Bit 18)                             */
#define BEEP_CSR_BEEPEN_Msk               (0x40000UL)               /*!< BEEP CSR: BEEPEN (Bitfield-Mask: 0x01)                */
#define BEEP_CSR_BEEPEN										 BEEP_CSR_BEEPEN_Msk
#define BEEP_CSR_CLKSEL_Pos               (20UL)                    /*!< BEEP CSR: CLKSEL (Bit 20)                             */
#define BEEP_CSR_CLKSEL_Msk               (0x300000UL)              /*!< BEEP CSR: CLKSEL (Bitfield-Mask: 0x03)                */
#define BEEP_CSR_CLKSEL										 BEEP_CSR_CLKSEL_Msk
#define BEEP_CSR_CLKSEL_0									(0x1 << BEEP_CSR_CLKSEL_Pos)
#define BEEP_CSR_CLKSEL_1									(0x2 << BEEP_CSR_CLKSEL_Pos)
#define BEEP_CSR_CLKSEL_2									(0x4 << BEEP_CSR_CLKSEL_Pos)
#define BEEP_CSR_ALL_Msk               		(BEEP_CSR_BEEPDIV_Msk | BEEP_CSR_BEEPSEL_Msk | BEEP_CSR_BEEPEN_Msk | BEEP_CSR_CLKSEL_Msk)  


/* =========================================================================================================================== */
/* ================                                            AWK                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define AWK_CR_DIVSEL_Pos                 (0UL)                     /*!< AWK CR: DIVSEL (Bit 0)                                */
#define AWK_CR_DIVSEL_Msk                 (0xfUL)                   /*!< AWK CR: DIVSEL (Bitfield-Mask: 0x0f)                  */
#define AWK_CR_DIVSEL											 AWK_CR_DIVSEL_Msk
#define AWK_CR_DIVSEL_0										(0x1 << AWK_CR_DIVSEL_Pos)
#define AWK_CR_DIVSEL_1										(0x2 << AWK_CR_DIVSEL_Pos)
#define AWK_CR_DIVSEL_2										(0x4 << AWK_CR_DIVSEL_Pos)
#define AWK_CR_DIVSEL_3										(0x8 << AWK_CR_DIVSEL_Pos)
#define AWK_CR_AWKEN_Pos                  (4UL)                     /*!< AWK CR: AWKEN (Bit 4)                                 */
#define AWK_CR_AWKEN_Msk                  (0x10UL)                  /*!< AWK CR: AWKEN (Bitfield-Mask: 0x01)                   */
#define AWK_CR_AWKEN											 AWK_CR_AWKEN_Msk
#define AWK_CR_TCLKSEL_Pos                (5UL)                     /*!< AWK CR: TCLKSEL (Bit 5)                               */
#define AWK_CR_TCLKSEL_Msk                (0x60UL)                  /*!< AWK CR: TCLKSEL (Bitfield-Mask: 0x03)                 */
#define AWK_CR_TCLKSEL										 AWK_CR_TCLKSEL_Msk
#define AWK_CR_TCLKSEL_0									(0x1 << AWK_CR_TCLKSEL_Pos)
#define AWK_CR_TCLKSEL_1									(0x2 << AWK_CR_TCLKSEL_Pos)
#define AWK_CR_HXPRSC_Pos                 (8UL)                     /*!< AWK CR: HXPRSC (Bit 8)                                */
#define AWK_CR_HXPRSC_Msk                 (0x7fff00UL)              /*!< AWK CR: HXPRSC (Bitfield-Mask: 0x7fff)                */
#define AWK_CR_HXPRSC											 AWK_CR_HXPRSC_Msk
/* =========================================================  RLOAD  ========================================================= */
#define AWK_RLOAD_RLDVAL_Pos              (0UL)                     /*!< AWK RLOAD: RLDVAL (Bit 0)                             */
#define AWK_RLOAD_RLDVAL_Msk              (0xffUL)                  /*!< AWK RLOAD: RLDVAL (Bitfield-Mask: 0xff)               */
#define AWK_RLOAD_RLDVAL									 AWK_RLOAD_RLDVAL_Msk
/* ==========================================================  SR  =========================================================== */
#define AWK_SR_AWUF_Pos                   (0UL)                     /*!< AWK SR: AWUF (Bit 0)                                  */
#define AWK_SR_AWUF_Msk                   (0x1UL)                   /*!< AWK SR: AWUF (Bitfield-Mask: 0x01)                    */
#define AWK_SR_AWUF												 AWK_SR_AWUF_Msk
/* ========================================================  INTCLR  ========================================================= */
#define AWK_INTCLR_INTCLR_Pos             (0UL)                     /*!< AWK INTCLR: INTCLR (Bit 0)                            */
#define AWK_INTCLR_INTCLR_Msk             (0x1UL)                   /*!< AWK INTCLR: INTCLR (Bitfield-Mask: 0x01)              */
#define AWK_INTCLR_INTCLR									 AWK_INTCLR_INTCLR_Msk

/* =========================================================================================================================== */
/* ================                                           LPTIM                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  CNTVAL  ========================================================= */
#define LPTIM_CNTVAL_LPT_CNT_Pos          (0UL)                     /*!< LPTIM CNTVAL: LPT_CNT (Bit 0)                         */
#define LPTIM_CNTVAL_LPT_CNT_Msk          (0x1UL)                   /*!< LPTIM CNTVAL: LPT_CNT (Bitfield-Mask: 0x01)           */
/* ==========================================================  CR  =========================================================== */
#define LPTIM_CR_TIM_RUN_Pos              (0UL)                     /*!< LPTIM CR: TIM_RUN (Bit 0)                             */
#define LPTIM_CR_TIM_RUN_Msk              (0x1UL)                   /*!< LPTIM CR: TIM_RUN (Bitfield-Mask: 0x01)               */
#define LPTIM_CR_TIM_RUN									 LPTIM_CR_TIM_RUN_Msk
#define LPTIM_CR_MODE_Pos                 (1UL)                     /*!< LPTIM CR: MODE (Bit 1)                                */
#define LPTIM_CR_MODE_Msk                 (0x2UL)                   /*!< LPTIM CR: MODE (Bitfield-Mask: 0x01)                  */
#define LPTIM_CR_MODE											 LPTIM_CR_MODE_Msk
#define LPTIM_CR_CT_SEL_Pos               (2UL)                     /*!< LPTIM CR: CT_SEL (Bit 2)                              */
#define LPTIM_CR_CT_SEL_Msk               (0x4UL)                   /*!< LPTIM CR: CT_SEL (Bitfield-Mask: 0x01)                */
#define LPTIM_CR_CT_SEL										 LPTIM_CR_CT_SEL_Msk
#define LPTIM_CR_TOG_EN_Pos               (3UL)                     /*!< LPTIM CR: TOG_EN (Bit 3)                              */
#define LPTIM_CR_TOG_EN_Msk               (0x8UL)                   /*!< LPTIM CR: TOG_EN (Bitfield-Mask: 0x01)                */
#define LPTIM_CR_TOG_EN										 LPTIM_CR_TOG_EN_Msk
#define LPTIM_CR_TCK_SEL_Pos              (4UL)                     /*!< LPTIM CR: TCK_SEL (Bit 4)                             */
#define LPTIM_CR_TCK_SEL_Msk              (0x30UL)                  /*!< LPTIM CR: TCK_SEL (Bitfield-Mask: 0x03)               */
#define LPTIM_CR_TCK_SEL									 LPTIM_CR_TCK_SEL_Msk
#define LPTIM_CR_TCK_SEL_0								(0x1 << LPTIM_CR_TCK_SEL_Pos)
#define LPTIM_CR_TCK_SEL_1								(0x2 << LPTIM_CR_TCK_SEL_Pos)
#define LPTIM_CR_GATE_EN_Pos              (6UL)                     /*!< LPTIM CR: GATE_EN (Bit 6)                             */
#define LPTIM_CR_GATE_EN_Msk              (0x40UL)                  /*!< LPTIM CR: GATE_EN (Bitfield-Mask: 0x01)               */
#define LPTIM_CR_GATE_EN									 LPTIM_CR_GATE_EN_Msk
#define LPTIM_CR_GATE_P_Pos               (7UL)                     /*!< LPTIM CR: GATE_P (Bit 7)                              */
#define LPTIM_CR_GATE_P_Msk               (0x80UL)                  /*!< LPTIM CR: GATE_P (Bitfield-Mask: 0x01)                */
#define LPTIM_CR_GATE_P										 LPTIM_CR_GATE_P_Msk
#define LPTIM_CR_INT_EN_Pos               (8UL)                     /*!< LPTIM CR: INT_EN (Bit 8)                              */
#define LPTIM_CR_INT_EN_Msk               (0x100UL)                 /*!< LPTIM CR: INT_EN (Bitfield-Mask: 0x01)                */
#define LPTIM_CR_INT_EN										 LPTIM_CR_INT_EN_Msk
#define LPTIM_CR_TCK_EN_Pos               (9UL)                     /*!< LPTIM CR: TCK_EN (Bit 9)                              */
#define LPTIM_CR_TCK_EN_Msk               (0x200UL)                 /*!< LPTIM CR: TCK_EN (Bitfield-Mask: 0x01)                */
#define LPTIM_CR_TCK_EN										 LPTIM_CR_TCK_EN_Msk
#define LPTIM_CR_WT_FLAG_Pos              (16UL)                    /*!< LPTIM CR: WT_FLAG (Bit 16)                            */
#define LPTIM_CR_WT_FLAG_Msk              (0x10000UL)               /*!< LPTIM CR: WT_FLAG (Bitfield-Mask: 0x01)               */
#define LPTIM_CR_WT_FLAG									 LPTIM_CR_WT_FLAG_Msk
#define LPTIM_CR_ALL_Msk									(0x3FFUL)               	/*!< LPTIM CR: ALL (Bitfield-Mask: 0x3FF)               	 */

/* =========================================================  LOAD  ========================================================== */
#define LPTIM_LOAD_LOAD_Pos               (0UL)                     /*!< LPTIM LOAD: LOAD (Bit 0)                              */
#define LPTIM_LOAD_LOAD_Msk               (0xffffUL)                /*!< LPTIM LOAD: LOAD (Bitfield-Mask: 0xffff)              */
#define LPTIM_LOAD_LOAD										 LPTIM_LOAD_LOAD_Msk
/* =========================================================  INTSR  ========================================================= */
#define LPTIM_INTSR_INTF_Pos              (0UL)                     /*!< LPTIM INTSR: INTF (Bit 0)                             */
#define LPTIM_INTSR_INTF_Msk              (0x01UL)                  /*!< LPTIM INTSR: INTF (Bitfield-Mask: 0x01)               */
#define LPTIM_INTSR_INTF									 LPTIM_INTSR_INTF_Msk
/* ========================================================  INTCLR  ========================================================= */
#define LPTIM_INTCLR_ICLR_Pos             (0UL)                     /*!< LPTIM INTCLR: ICLR (Bit 0)                            */
#define LPTIM_INTCLR_ICLR_Msk             (0x1UL)                   /*!< LPTIM INTCLR: ICLR (Bitfield-Mask: 0x01)              */
#define LPTIM_INTCLR_ICLR									 LPTIM_INTCLR_ICLR_Msk
/* ========================================================  BGLOAD  ========================================================= */
#define LPTIM_BGLOAD_BGLOAD_Pos           (0UL)                     /*!< LPTIM BGLOAD: BGLOAD (Bit 0)                          */
#define LPTIM_BGLOAD_BGLOAD_Msk           (0xffffUL)                /*!< LPTIM BGLOAD: BGLOAD (Bitfield-Mask: 0xffff)          */
#define LPTIM_BGLOAD_BGLOAD								 LPTIM_BGLOAD_BGLOAD_Msk

/* =========================================================================================================================== */
/* ================                                         BASETIM                                           ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define BASETIM_CR_TMR_PRSC_Pos               (0UL)                     /*!< BASETIM CR: TMR_PRSC (Bit 0)                              */
#define BASETIM_CR_TMR_PRSC_Msk               (0x7UL)                   /*!< BASETIM CR: TMR_PRSC (Bitfield-Mask: 0x07)                */
#define BASETIM_CR_TMR_PRSC										 BASETIM_CR_TMR_PRSC_Msk
#define BASETIM_CR_TMR_PRSC_0									(0x1 << BASETIM_CR_TMR_PRSC_Pos)
#define BASETIM_CR_TMR_PRSC_1									(0x2 << BASETIM_CR_TMR_PRSC_Pos)
#define BASETIM_CR_TMR_PRSC_2									(0x4 << BASETIM_CR_TMR_PRSC_Pos)
#define BASETIM_CR_ONESHOT_Pos                (3UL)                     /*!< BASETIM CR: ONESHOT (Bit 3)                               */
#define BASETIM_CR_ONESHOT_Msk                (0x8UL)                   /*!< BASETIM CR: ONESHOT (Bitfield-Mask: 0x01)                 */
#define BASETIM_CR_ONESHOT										 BASETIM_CR_ONESHOT_Msk
#define BASETIM_CR_TMR_SIZE_Pos               (4UL)                     /*!< BASETIM CR: TMR_SIZE (Bit 4)                              */
#define BASETIM_CR_TMR_SIZE_Msk               (0x10UL)                  /*!< BASETIM CR: TMR_SIZE (Bitfield-Mask: 0x01)                */
#define BASETIM_CR_TMR_SIZE										 BASETIM_CR_TMR_SIZE_Msk
#define BASETIM_CR_INTEN_Pos                  (5UL)                     /*!< BASETIM CR: INTEN (Bit 5)                                 */
#define BASETIM_CR_INTEN_Msk                  (0x20UL)                  /*!< BASETIM CR: INTEN (Bitfield-Mask: 0x01)                   */
#define BASETIM_CR_INTEN											 BASETIM_CR_INTEN_Msk
#define BASETIM_CR_MODE_Pos                   (6UL)                     /*!< BASETIM CR: MODE (Bit 6)                                  */
#define BASETIM_CR_MODE_Msk                   (0x40UL)                  /*!< BASETIM CR: MODE (Bitfield-Mask: 0x01)                    */
#define BASETIM_CR_MODE												 BASETIM_CR_MODE_Msk
#define BASETIM_CR_TR_Pos                     (7UL)                     /*!< BASETIM CR: TR (Bit 7)                                    */
#define BASETIM_CR_TR_Msk                     (0x80UL)                  /*!< BASETIM CR: TR (Bitfield-Mask: 0x01)                      */
#define BASETIM_CR_TR													 BASETIM_CR_TR_Msk
#define BASETIM_CR_CT_SEL_Pos                 (8UL)                     /*!< BASETIM CR: CT_SEL (Bit 8)                                */
#define BASETIM_CR_CT_SEL_Msk                 (0x100UL)                 /*!< BASETIM CR: CT_SEL (Bitfield-Mask: 0x01)                  */
#define BASETIM_CR_CT_SEL											 BASETIM_CR_CT_SEL_Msk
#define BASETIM_CR_TOG_EN_Pos                 (9UL)                     /*!< BASETIM CR: TOG_EN (Bit 9)                                */
#define BASETIM_CR_TOG_EN_Msk                 (0x200UL)                 /*!< BASETIM CR: TOG_EN (Bitfield-Mask: 0x01)                  */
#define BASETIM_CR_TOG_EN											 BASETIM_CR_TOG_EN_Msk
#define BASETIM_CR_GATE_EN_Pos                (10UL)                    /*!< BASETIM CR: GATE_EN (Bit 10)                              */
#define BASETIM_CR_GATE_EN_Msk                (0x400UL)                 /*!< BASETIM CR: GATE_EN (Bitfield-Mask: 0x01)                 */
#define BASETIM_CR_GATE_EN										 BASETIM_CR_GATE_EN_Msk
#define BASETIM_CR_GATE_P_Pos                 (11UL)                    /*!< BASETIM CR: GATE_P (Bit 11)                               */
#define BASETIM_CR_GATE_P_Msk                 (0x800UL)                 /*!< BASETIM CR: GATE_P (Bitfield-Mask: 0x01)                  */
#define BASETIM_CR_GATE_P											 BASETIM_CR_GATE_P_Msk
#define BASETIM_CR_ALL_Msk										(0xFFFUL)									/*!< BASETIM CR: All valid be mask (Bitfield-Mask: 0xFFF)      */
/* =========================================================  LOAD  ========================================================== */
#define BASETIM_LOAD_LOAD_Pos                 (0UL)                     /*!< BASETIM LOAD: LOAD (Bit 0)                                */
#define BASETIM_LOAD_LOAD_Msk                 (0xffffffffUL)            /*!< BASETIM LOAD: LOAD (Bitfield-Mask: 0xffffffff)            */
#define BASETIM_LOAD_LOAD											 BASETIM_LOAD_LOAD_Msk
/* ==========================================================  CNT  ========================================================== */
#define BASETIM_CNT_CNT_Pos                   (0UL)                     /*!< BASETIM CNT: CNT (Bit 0)                                  */
#define BASETIM_CNT_CNT_Msk                   (0xffffffffUL)            /*!< BASETIM CNT: CNT (Bitfield-Mask: 0xffffffff)              */
/* =======================================================  RAWINTSR  ======================================================== */
#define BASETIM_RAWINTSR_RIS_Pos              (0UL)                     /*!< BASETIM RAWINTSR: RIS (Bit 0)                             */
#define BASETIM_RAWINTSR_RIS_Msk              (0x1UL)                   /*!< BASETIM RAWINTSR: RIS (Bitfield-Mask: 0x01)               */
#define BASETIM_RAWINTSR_RIS									 BASETIM_RAWINTSR_RIS_Msk
/* =======================================================  MSKINTSR  ======================================================== */
#define BASETIM_MSKINTSR_TF_Pos               (0UL)                     /*!< BASETIM MSKINTSR: TF (Bit 0)                              */
#define BASETIM_MSKINTSR_TF_Msk               (0x1UL)                   /*!< BASETIM MSKINTSR: TF (Bitfield-Mask: 0x01)                */
#define BASETIM_MSKINTSR_TF										 BASETIM_MSKINTSR_TF_Msk
/* ========================================================  INTCLR  ========================================================= */
#define BASETIM_INTCLR_INTCLR_Pos             (0UL)                     /*!< BASETIM INTCLR: INTCLR (Bit 0)                            */
#define BASETIM_INTCLR_INTCLR_Msk             (0x1UL)                   /*!< BASETIM INTCLR: INTCLR (Bitfield-Mask: 0x01)              */
#define BASETIM_INTCLR_INTCLR									 BASETIM_INTCLR_INTCLR_Msk
/* ========================================================  BGLOAD  ========================================================= */
#define BASETIM_BGLOAD_BGLOAD_Pos             (0UL)                     /*!< BASETIM BGLOAD: BGLOAD (Bit 0)                            */
#define BASETIM_BGLOAD_BGLOAD_Msk             (0xffffffffUL)            /*!< BASETIM BGLOAD: BGLOAD (Bitfield-Mask: 0xffffffff)        */
#define BASETIM_BGLOAD_BGLOAD									 BASETIM_BGLOAD_BGLOAD_Msk

/* =========================================================================================================================== */
/* ================                                            PCA                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define PCA_CR_CCF0_Pos                   (0UL)                     /*!< PCA CR: CCF0 (Bit 0)                                  */
#define PCA_CR_CCF0_Msk                   (0x1UL)                   /*!< PCA CR: CCF0 (Bitfield-Mask: 0x01)                    */
#define PCA_CR_CCF0												PCA_CR_CCF0_Msk
#define PCA_CR_CCF1_Pos                   (1UL)                     /*!< PCA CR: CCF1 (Bit 1)                                  */
#define PCA_CR_CCF1_Msk                   (0x2UL)                   /*!< PCA CR: CCF1 (Bitfield-Mask: 0x01)                    */
#define PCA_CR_CCF1												PCA_CR_CCF1_Msk
#define PCA_CR_CCF2_Pos                   (2UL)                     /*!< PCA CR: CCF2 (Bit 2)                                  */
#define PCA_CR_CCF2_Msk                   (0x4UL)                   /*!< PCA CR: CCF2 (Bitfield-Mask: 0x01)                    */
#define PCA_CR_CCF2												PCA_CR_CCF2_Msk
#define PCA_CR_CCF3_Pos                   (3UL)                     /*!< PCA CR: CCF3 (Bit 3)                                  */
#define PCA_CR_CCF3_Msk                   (0x8UL)                   /*!< PCA CR: CCF3 (Bitfield-Mask: 0x01)                    */
#define PCA_CR_CCF3												PCA_CR_CCF3_Msk
#define PCA_CR_CCF4_Pos                   (4UL)                     /*!< PCA CR: CCF4 (Bit 4)                                  */
#define PCA_CR_CCF4_Msk                   (0x10UL)                  /*!< PCA CR: CCF4 (Bitfield-Mask: 0x01)                    */
#define PCA_CR_CCF4												PCA_CR_CCF4_Msk
#define PCA_CR_CR_Pos                     (6UL)                     /*!< PCA CR: CR (Bit 6)                                    */
#define PCA_CR_CR_Msk                     (0x40UL)                  /*!< PCA CR: CR (Bitfield-Mask: 0x01)                      */
#define PCA_CR_CR													PCA_CR_CR_Msk
#define PCA_CR_CF_Pos                     (7UL)                     /*!< PCA CR: CF (Bit 7)                                    */
#define PCA_CR_CF_Msk                     (0x80UL)                  /*!< PCA CR: CF (Bitfield-Mask: 0x01)                      */
#define PCA_CR_CF													PCA_CR_CF_Msk
/* ==========================================================  MOD  ========================================================== */
#define PCA_MOD_CFIE_Pos                  (0UL)                     /*!< PCA MOD: CFIE (Bit 0)                                 */
#define PCA_MOD_CFIE_Msk                  (0x1UL)                   /*!< PCA MOD: CFIE (Bitfield-Mask: 0x01)                   */
#define PCA_MOD_CFIE											PCA_MOD_CFIE_Msk
#define PCA_MOD_CPS_Pos                   (1UL)                     /*!< PCA MOD: CPS (Bit 1)                                  */
#define PCA_MOD_CPS_Msk                   (0xeUL)                   /*!< PCA MOD: CPS (Bitfield-Mask: 0x07)                    */
#define PCA_MOD_CPS												PCA_MOD_CPS_Msk
#define PCA_MOD_CPS_0											(0x01 << PCA_MOD_CPS_Pos)
#define PCA_MOD_CPS_1											(0x02 << PCA_MOD_CPS_Pos)
#define PCA_MOD_CPS_2											(0x04 << PCA_MOD_CPS_Pos)
#define PCA_MOD_CIDL_Pos                  (7UL)                     /*!< PCA MOD: CIDL (Bit 7)                                 */
#define PCA_MOD_CIDL_Msk                  (0x80UL)                  /*!< PCA MOD: CIDL (Bitfield-Mask: 0x01)                   */
#define PCA_MOD_CIDL											PCA_MOD_CIDL_Msk
/* ==========================================================  CNT  ========================================================== */
#define PCA_CNT_CNT_Pos                  	(0UL)                     /*!< PCA CNT: CNT (Bit 0)                                  */
#define PCA_CNT_CNT_Msk                  	(0xffUL)                  /*!< PCA CNT: CNT (Bitfield-Mask: 0xff)                    */
/* ========================================================  INTCLR  ========================================================= */
#define PCA_INTCLR_CCF0_Pos               (0UL)                     /*!< PCA INTCLR: CCF0 (Bit 0)                              */
#define PCA_INTCLR_CCF0_Msk               (0x1UL)                   /*!< PCA INTCLR: CCF0 (Bitfield-Mask: 0x01)                */
#define PCA_INTCLR_CCF1_Pos               (1UL)                     /*!< PCA INTCLR: CCF1 (Bit 1)                              */
#define PCA_INTCLR_CCF1_Msk               (0x2UL)                   /*!< PCA INTCLR: CCF1 (Bitfield-Mask: 0x01)                */
#define PCA_INTCLR_CCF2_Pos               (2UL)                     /*!< PCA INTCLR: CCF2 (Bit 2)                              */
#define PCA_INTCLR_CCF2_Msk               (0x4UL)                   /*!< PCA INTCLR: CCF2 (Bitfield-Mask: 0x01)                */
#define PCA_INTCLR_CCF3_Pos               (3UL)                     /*!< PCA INTCLR: CCF3 (Bit 3)                              */
#define PCA_INTCLR_CCF3_Msk               (0x8UL)                   /*!< PCA INTCLR: CCF3 (Bitfield-Mask: 0x01)                */
#define PCA_INTCLR_CCF4_Pos               (4UL)                     /*!< PCA INTCLR: CCF4 (Bit 4)                              */
#define PCA_INTCLR_CCF4_Msk               (0x10UL)                  /*!< PCA INTCLR: CCF4 (Bitfield-Mask: 0x01)                */
#define PCA_INTCLR_CF_Pos                 (7UL)                     /*!< PCA INTCLR: CF (Bit 7)                                */
#define PCA_INTCLR_CF_Msk                 (0x80UL)                  /*!< PCA INTCLR: CF (Bitfield-Mask: 0x01)                  */
/* ========================================================  CCAPM0  ========================================================= */
#define PCA_CCAPM0_ECOM_Pos               (6UL)                     /*!< PCA CCAPM0: ECOM (Bit 6)                              */
#define PCA_CCAPM0_ECOM_Msk               (0x40UL)                  /*!< PCA CCAPM0: ECOM (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM0_ECOM										PCA_CCAPM0_ECOM_Msk
#define PCA_CCAPM0_CAPP_Pos               (5UL)                     /*!< PCA CCAPM0: CAPP (Bit 5)                              */
#define PCA_CCAPM0_CAPP_Msk               (0x20UL)                  /*!< PCA CCAPM0: CAPP (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM0_CAPP										PCA_CCAPM0_CAPP_Msk
#define PCA_CCAPM0_CAPN_Pos               (4UL)                     /*!< PCA CCAPM0: CAPN (Bit 4)                              */
#define PCA_CCAPM0_CAPN_Msk               (0x10UL)                  /*!< PCA CCAPM0: CAPN (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM0_CAPN										PCA_CCAPM0_CAPN_Msk
#define PCA_CCAPM0_MAT_Pos                (3UL)                     /*!< PCA CCAPM0: MAT (Bit 3)                               */
#define PCA_CCAPM0_MAT_Msk                (0x8UL)                   /*!< PCA CCAPM0: MAT (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM0_MAT										PCA_CCAPM0_MAT_Msk
#define PCA_CCAPM0_TOG_Pos                (2UL)                     /*!< PCA CCAPM0: TOG (Bit 2)                               */
#define PCA_CCAPM0_TOG_Msk                (0x4UL)                   /*!< PCA CCAPM0: TOG (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM0_TOG										PCA_CCAPM0_TOG_Msk
#define PCA_CCAPM0_PWM_Pos                (1UL)                     /*!< PCA CCAPM0: PWM (Bit 1)                               */
#define PCA_CCAPM0_PWM_Msk                (0x2UL)                   /*!< PCA CCAPM0: PWM (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM0_PWM										PCA_CCAPM0_PWM_Msk
#define PCA_CCAPM0_CCIE_Pos               (0UL)                     /*!< PCA CCAPM0: CCIE (Bit 0)                              */
#define PCA_CCAPM0_CCIE_Msk               (0x1UL)                   /*!< PCA CCAPM0: CCIE (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM0_CCIE										PCA_CCAPM0_CCIE_Msk
/* ========================================================  CCAPM1  ========================================================= */
#define PCA_CCAPM1_ECOM_Pos               (6UL)                     /*!< PCA CCAPM1: ECOM (Bit 6)                              */
#define PCA_CCAPM1_ECOM_Msk               (0x40UL)                  /*!< PCA CCAPM1: ECOM (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM1_ECOM										PCA_CCAPM1_ECOM_Msk
#define PCA_CCAPM1_CAPP_Pos               (5UL)                     /*!< PCA CCAPM1: CAPP (Bit 5)                              */
#define PCA_CCAPM1_CAPP_Msk               (0x20UL)                  /*!< PCA CCAPM1: CAPP (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM1_CAPP										PCA_CCAPM1_CAPP_Msk
#define PCA_CCAPM1_CAPN_Pos               (4UL)                     /*!< PCA CCAPM1: CAPN (Bit 4)                              */
#define PCA_CCAPM1_CAPN_Msk               (0x10UL)                  /*!< PCA CCAPM1: CAPN (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM1_CAPN										PCA_CCAPM1_CAPN_Msk
#define PCA_CCAPM1_MAT_Pos                (3UL)                     /*!< PCA CCAPM1: MAT (Bit 3)                               */
#define PCA_CCAPM1_MAT_Msk                (0x8UL)                   /*!< PCA CCAPM1: MAT (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM1_MAT										PCA_CCAPM1_MAT_Msk
#define PCA_CCAPM1_TOG_Pos                (2UL)                     /*!< PCA CCAPM1: TOG (Bit 2)                               */
#define PCA_CCAPM1_TOG_Msk                (0x4UL)                   /*!< PCA CCAPM1: TOG (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM1_TOG										PCA_CCAPM1_TOG_Msk
#define PCA_CCAPM1_PWM_Pos                (1UL)                     /*!< PCA CCAPM1: PWM (Bit 1)                               */
#define PCA_CCAPM1_PWM_Msk                (0x2UL)                   /*!< PCA CCAPM1: PWM (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM1_PWM										PCA_CCAPM1_PWM_Msk
#define PCA_CCAPM1_CCIE_Pos               (0UL)                     /*!< PCA CCAPM1: CCIE (Bit 0)                              */
#define PCA_CCAPM1_CCIE_Msk               (0x1UL)                   /*!< PCA CCAPM1: CCIE (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM1_CCIE										PCA_CCAPM1_CCIE_Msk
/* ========================================================  CCAPM2  ========================================================= */
#define PCA_CCAPM2_ECOM_Pos               (6UL)                     /*!< PCA CCAPM2: ECOM (Bit 6)                              */
#define PCA_CCAPM2_ECOM_Msk               (0x40UL)                  /*!< PCA CCAPM2: ECOM (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM2_ECOM										PCA_CCAPM2_ECOM_Msk
#define PCA_CCAPM2_CAPP_Pos               (5UL)                     /*!< PCA CCAPM2: CAPP (Bit 5)                              */
#define PCA_CCAPM2_CAPP_Msk               (0x20UL)                  /*!< PCA CCAPM2: CAPP (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM2_CAPP										PCA_CCAPM2_CAPP_Msk
#define PCA_CCAPM2_CAPN_Pos               (4UL)                     /*!< PCA CCAPM2: CAPN (Bit 4)                              */
#define PCA_CCAPM2_CAPN_Msk               (0x10UL)                  /*!< PCA CCAPM2: CAPN (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM2_CAPN										PCA_CCAPM2_CAPN_Msk
#define PCA_CCAPM2_MAT_Pos                (3UL)                     /*!< PCA CCAPM2: MAT (Bit 3)                               */
#define PCA_CCAPM2_MAT_Msk                (0x8UL)                   /*!< PCA CCAPM2: MAT (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM2_MAT										PCA_CCAPM2_MAT_Msk
#define PCA_CCAPM2_TOG_Pos                (2UL)                     /*!< PCA CCAPM2: TOG (Bit 2)                               */
#define PCA_CCAPM2_TOG_Msk                (0x4UL)                   /*!< PCA CCAPM2: TOG (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM2_TOG										PCA_CCAPM2_TOG_Msk
#define PCA_CCAPM2_PWM_Pos                (1UL)                     /*!< PCA CCAPM2: PWM (Bit 1)                               */
#define PCA_CCAPM2_PWM_Msk                (0x2UL)                   /*!< PCA CCAPM2: PWM (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM2_PWM										PCA_CCAPM2_PWM_Msk
#define PCA_CCAPM2_CCIE_Pos               (0UL)                     /*!< PCA CCAPM2: CCIE (Bit 0)                              */
#define PCA_CCAPM2_CCIE_Msk               (0x1UL)                   /*!< PCA CCAPM2: CCIE (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM2_CCIE										PCA_CCAPM2_CCIE_Msk
/* ========================================================  CCAPM3  ========================================================= */
#define PCA_CCAPM3_ECOM_Pos               (6UL)                     /*!< PCA CCAPM3: ECOM (Bit 6)                              */
#define PCA_CCAPM3_ECOM_Msk               (0x40UL)                  /*!< PCA CCAPM3: ECOM (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM3_ECOM										PCA_CCAPM3_ECOM_Msk
#define PCA_CCAPM3_CAPP_Pos               (5UL)                     /*!< PCA CCAPM3: CAPP (Bit 5)                              */
#define PCA_CCAPM3_CAPP_Msk               (0x20UL)                  /*!< PCA CCAPM3: CAPP (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM3_CAPP										PCA_CCAPM3_CAPP_Msk
#define PCA_CCAPM3_CAPN_Pos               (4UL)                     /*!< PCA CCAPM3: CAPN (Bit 4)                              */
#define PCA_CCAPM3_CAPN_Msk               (0x10UL)                  /*!< PCA CCAPM3: CAPN (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM3_CAPN										PCA_CCAPM3_CAPN_Msk
#define PCA_CCAPM3_MAT_Pos                (3UL)                     /*!< PCA CCAPM3: MAT (Bit 3)                               */
#define PCA_CCAPM3_MAT_Msk                (0x8UL)                   /*!< PCA CCAPM3: MAT (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM3_MAT										PCA_CCAPM3_MAT_Msk
#define PCA_CCAPM3_TOG_Pos                (2UL)                     /*!< PCA CCAPM3: TOG (Bit 2)                               */
#define PCA_CCAPM3_TOG_Msk                (0x4UL)                   /*!< PCA CCAPM3: TOG (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM3_TOG										PCA_CCAPM3_TOG_Msk
#define PCA_CCAPM3_PWM_Pos                (1UL)                     /*!< PCA CCAPM3: PWM (Bit 1)                               */
#define PCA_CCAPM3_PWM_Msk                (0x2UL)                   /*!< PCA CCAPM3: PWM (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM3_PWM										PCA_CCAPM3_PWM_Msk
#define PCA_CCAPM3_CCIE_Pos               (0UL)                     /*!< PCA CCAPM3: CCIE (Bit 0)                              */
#define PCA_CCAPM3_CCIE_Msk               (0x1UL)                   /*!< PCA CCAPM3: CCIE (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM3_CCIE										PCA_CCAPM3_CCIE_Msk
/* ========================================================  CCAPM4  ========================================================= */
#define PCA_CCAPM4_ECOM_Pos               (6UL)                     /*!< PCA CCAPM4: ECOM (Bit 6)                              */
#define PCA_CCAPM4_ECOM_Msk               (0x40UL)                  /*!< PCA CCAPM4: ECOM (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM4_ECOM										PCA_CCAPM4_ECOM_Msk
#define PCA_CCAPM4_CAPP_Pos               (5UL)                     /*!< PCA CCAPM4: CAPP (Bit 5)                              */
#define PCA_CCAPM4_CAPP_Msk               (0x20UL)                  /*!< PCA CCAPM4: CAPP (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM4_CAPP										PCA_CCAPM4_CAPP_Msk
#define PCA_CCAPM4_CAPN_Pos               (4UL)                     /*!< PCA CCAPM4: CAPN (Bit 4)                              */
#define PCA_CCAPM4_CAPN_Msk               (0x10UL)                  /*!< PCA CCAPM4: CAPN (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM4_CAPN										PCA_CCAPM4_CAPN_Msk
#define PCA_CCAPM4_MAT_Pos                (3UL)                     /*!< PCA CCAPM4: MAT (Bit 3)                               */
#define PCA_CCAPM4_MAT_Msk                (0x8UL)                   /*!< PCA CCAPM4: MAT (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM4_MAT										PCA_CCAPM4_MAT_Msk
#define PCA_CCAPM4_TOG_Pos                (2UL)                     /*!< PCA CCAPM4: TOG (Bit 2)                               */
#define PCA_CCAPM4_TOG_Msk                (0x4UL)                   /*!< PCA CCAPM4: TOG (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM4_TOG										PCA_CCAPM4_TOG_Msk
#define PCA_CCAPM4_PWM_Pos                (1UL)                     /*!< PCA CCAPM4: PWM (Bit 1)                               */
#define PCA_CCAPM4_PWM_Msk                (0x2UL)                   /*!< PCA CCAPM4: PWM (Bitfield-Mask: 0x01)                 */
#define PCA_CCAPM4_PWM										PCA_CCAPM4_PWM_Msk
#define PCA_CCAPM4_CCIE_Pos               (0UL)                     /*!< PCA CCAPM4: CCIE (Bit 0)                              */
#define PCA_CCAPM4_CCIE_Msk               (0x1UL)                   /*!< PCA CCAPM4: CCIE (Bitfield-Mask: 0x01)                */
#define PCA_CCAPM4_CCIE										PCA_CCAPM4_CCIE_Msk
/* ========================================================  CCAP0L  ========================================================= */
#define PCA_CCAP0L_CCAP0_Pos              (0UL)                     /*!< PCA CCAP0L: CCAP0 (Bit 0)                             */
#define PCA_CCAP0L_CCAP0_Msk              (0xffUL)                  /*!< PCA CCAP0L: CCAP0 (Bitfield-Mask: 0xff)               */
/* ========================================================  CCAP0H  ========================================================= */
#define PCA_CCAP0H_CCAP0_Pos              (8UL)                     /*!< PCA CCAP0H: CCAP0 (Bit 8)                             */
#define PCA_CCAP0H_CCAP0_Msk              (0xff00UL)                /*!< PCA CCAP0H: CCAP0 (Bitfield-Mask: 0xff)               */
/* ========================================================  CCAP1L  ========================================================= */
#define PCA_CCAP1L_CCAP1_Pos              (0UL)                     /*!< PCA CCAP1L: CCAP1 (Bit 0)                             */
#define PCA_CCAP1L_CCAP1_Msk              (0xffUL)                  /*!< PCA CCAP1L: CCAP1 (Bitfield-Mask: 0xff)               */
/* ========================================================  CCAP1H  ========================================================= */
#define PCA_CCAP1H_CCAP1_Pos              (8UL)                     /*!< PCA CCAP1H: CCAP1 (Bit 8)                             */
#define PCA_CCAP1H_CCAP1_Msk              (0xff00UL)                /*!< PCA CCAP1H: CCAP1 (Bitfield-Mask: 0xff)               */
/* ========================================================  CCAP2L  ========================================================= */
#define PCA_CCAP2L_CCAP2_Pos              (0UL)                     /*!< PCA CCAP2L: CCAP2 (Bit 0)                             */
#define PCA_CCAP2L_CCAP2_Msk              (0xffUL)                  /*!< PCA CCAP2L: CCAP2 (Bitfield-Mask: 0xff)               */
/* ========================================================  CCAP2H  ========================================================= */
#define PCA_CCAP2H_CCAP2_Pos              (0UL)                     /*!< PCA CCAP2H: CCAP2 (Bit 0)                             */
#define PCA_CCAP2H_CCAP2_Msk              (0xffUL)                  /*!< PCA CCAP2H: CCAP2 (Bitfield-Mask: 0xff)               */
/* ========================================================  CCAP3L  ========================================================= */
#define PCA_CCAP3L_CCAP3_Pos              (0UL)                     /*!< PCA CCAP3L: CCAP3 (Bit 0)                             */
#define PCA_CCAP3L_CCAP3_Msk              (0xffUL)                  /*!< PCA CCAP3L: CCAP3 (Bitfield-Mask: 0xff)               */
/* ========================================================  CCAP3H  ========================================================= */
#define PCA_CCAP3H_CCAP3_Pos              (8UL)                     /*!< PCA CCAP3H: CCAP3 (Bit 8)                             */
#define PCA_CCAP3H_CCAP3_Msk              (0xff00UL)                /*!< PCA CCAP3H: CCAP3 (Bitfield-Mask: 0xff)               */
/* ========================================================  CCAP4L  ========================================================= */
#define PCA_CCAP4L_CCAP4_Pos              (0UL)                     /*!< PCA CCAP4L: CCAP4 (Bit 0)                             */
#define PCA_CCAP4L_CCAP4_Msk              (0xffUL)                  /*!< PCA CCAP4L: CCAP4 (Bitfield-Mask: 0xff)               */
/* ========================================================  CCAP4H  ========================================================= */
#define PCA_CCAP4H_CCAP4_Pos              (8UL)                     /*!< PCA CCAP4H: CCAP4 (Bit 8)                             */
#define PCA_CCAP4H_CCAP4_Msk              (0xff00UL)                /*!< PCA CCAP4H: CCAP4 (Bitfield-Mask: 0xff)               */
/* =========================================================  CCAPO  ========================================================= */
#define PCA_CCAPO_CCAPO4_Pos              (4UL)                     /*!< PCA CCAPO: CCAPO4 (Bit 4)                             */
#define PCA_CCAPO_CCAPO4_Msk              (0x10UL)                  /*!< PCA CCAPO: CCAPO4 (Bitfield-Mask: 0x01)               */
#define PCA_CCAPO_CCAPO3_Pos              (3UL)                     /*!< PCA CCAPO: CCAPO3 (Bit 3)                             */
#define PCA_CCAPO_CCAPO3_Msk              (0x8UL)                   /*!< PCA CCAPO: CCAPO3 (Bitfield-Mask: 0x01)               */
#define PCA_CCAPO_CCAPO2_Pos              (2UL)                     /*!< PCA CCAPO: CCAPO2 (Bit 2)                             */
#define PCA_CCAPO_CCAPO2_Msk              (0x4UL)                   /*!< PCA CCAPO: CCAPO2 (Bitfield-Mask: 0x01)               */
#define PCA_CCAPO_CCAPO1_Pos              (1UL)                     /*!< PCA CCAPO: CCAPO1 (Bit 1)                             */
#define PCA_CCAPO_CCAPO1_Msk              (0x2UL)                   /*!< PCA CCAPO: CCAPO1 (Bitfield-Mask: 0x01)               */
#define PCA_CCAPO_CCAPO0_Pos              (0UL)                     /*!< PCA CCAPO: CCAPO0 (Bit 0)                             */
#define PCA_CCAPO_CCAPO0_Msk              (0x1UL)                   /*!< PCA CCAPO: CCAPO0 (Bitfield-Mask: 0x01)               */
/* =========================================================  POCR  ========================================================== */
#define PCA_POCR_POINV4_Pos               (12UL)                    /*!< PCA POCR: POINV4 (Bit 12)                             */
#define PCA_POCR_POINV4_Msk               (0x1000UL)                /*!< PCA POCR: POINV4 (Bitfield-Mask: 0x01)                */
#define PCA_POCR_POINV3_Pos               (11UL)                    /*!< PCA POCR: POINV3 (Bit 11)                             */
#define PCA_POCR_POINV3_Msk               (0x800UL)                 /*!< PCA POCR: POINV3 (Bitfield-Mask: 0x01)                */
#define PCA_POCR_POINV2_Pos               (10UL)                    /*!< PCA POCR: POINV2 (Bit 10)                             */
#define PCA_POCR_POINV2_Msk               (0x400UL)                 /*!< PCA POCR: POINV2 (Bitfield-Mask: 0x01)                */
#define PCA_POCR_POINV1_Pos               (9UL)                     /*!< PCA POCR: POINV1 (Bit 9)                              */
#define PCA_POCR_POINV1_Msk               (0x200UL)                 /*!< PCA POCR: POINV1 (Bitfield-Mask: 0x01)                */
#define PCA_POCR_POINV0_Pos               (8UL)                     /*!< PCA POCR: POINV0 (Bit 8)                              */
#define PCA_POCR_POINV0_Msk               (0x100UL)                 /*!< PCA POCR: POINV0 (Bitfield-Mask: 0x01)                */
#define PCA_POCR_POE4_Pos                 (4UL)                     /*!< PCA POCR: POE4 (Bit 4)                                */
#define PCA_POCR_POE4_Msk                 (0x10UL)                  /*!< PCA POCR: POE4 (Bitfield-Mask: 0x01)                  */
#define PCA_POCR_POE4											PCA_POCR_POE4_Msk
#define PCA_POCR_POE3_Pos                 (3UL)                     /*!< PCA POCR: POE3 (Bit 3)                                */
#define PCA_POCR_POE3_Msk                 (0x8UL)                   /*!< PCA POCR: POE3 (Bitfield-Mask: 0x01)                  */
#define PCA_POCR_POE3											PCA_POCR_POE3_Msk
#define PCA_POCR_POE2_Pos                 (2UL)                     /*!< PCA POCR: POE2 (Bit 2)                                */
#define PCA_POCR_POE2_Msk                 (0x4UL)                   /*!< PCA POCR: POE2 (Bitfield-Mask: 0x01)                  */
#define PCA_POCR_POE2											PCA_POCR_POE2_Msk
#define PCA_POCR_POE1_Pos                 (1UL)                     /*!< PCA POCR: POE1 (Bit 1)                                */
#define PCA_POCR_POE1_Msk                 (0x2UL)                   /*!< PCA POCR: POE1 (Bitfield-Mask: 0x01)                  */
#define PCA_POCR_POE1											PCA_POCR_POE1_Msk
#define PCA_POCR_POE0_Pos                 (0UL)                     /*!< PCA POCR: POE0 (Bit 0)                                */
#define PCA_POCR_POE0_Msk                 (0x1UL)                   /*!< PCA POCR: POE0 (Bitfield-Mask: 0x01)                  */
#define PCA_POCR_POE0											PCA_POCR_POE0_Msk
/* =========================================================  CCAP0  ========================================================= */
#define PCA_CCAP0_CCAP0_Pos               (0UL)                     /*!< PCA CCAP0: CCAP0 (Bit 0)                              */
#define PCA_CCAP0_CCAP0_Msk               (0xffffUL)                /*!< PCA CCAP0: CCAP0 (Bitfield-Mask: 0xffff)              */
/* =========================================================  CCAP1  ========================================================= */
#define PCA_CCAP1_CCAP1_Pos               (0UL)                     /*!< PCA CCAP1: CCAP1 (Bit 0)                              */
#define PCA_CCAP1_CCAP1_Msk               (0xffffUL)                /*!< PCA CCAP1: CCAP1 (Bitfield-Mask: 0xffff)              */
/* =========================================================  CCAP2  ========================================================= */
#define PCA_CCAP2_CCAP2_Pos               (0UL)                     /*!< PCA CCAP2: CCAP2 (Bit 0)                              */
#define PCA_CCAP2_CCAP2_Msk               (0xffffUL)                /*!< PCA CCAP2: CCAP2 (Bitfield-Mask: 0xffff)              */
/* =========================================================  CCAP3  ========================================================= */
#define PCA_CCAP3_CCAP3_Pos               (0UL)                     /*!< PCA CCAP3: CCAP3 (Bit 0)                              */
#define PCA_CCAP3_CCAP3_Msk               (0x7fffUL)                /*!< PCA CCAP3: CCAP3 (Bitfield-Mask: 0x7fff)              */
/* =========================================================  CCAP4  ========================================================= */
#define PCA_CCAP4_CCAP4_Pos               (0UL)                     /*!< PCA CCAP4: CCAP4 (Bit 0)                              */
#define PCA_CCAP4_CCAP4_Msk               (0xffffUL)                /*!< PCA CCAP4: CCAP4 (Bitfield-Mask: 0xffff)              */


/* =========================================================================================================================== */
/* ================                                           TIM                                             ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR1  ========================================================== */
#define TIM_CR1_CEN_Pos                (0UL)                     /*!< TIM CR1: CEN (Bit 0)                               */
#define TIM_CR1_CEN_Msk                (0x1UL)                   /*!< TIM CR1: CEN (Bitfield-Mask: 0x01)                 */
#define TIM_CR1_CEN                     TIM_CR1_CEN_Msk                   
#define TIM_CR1_UDIS_Pos               (1UL)                     /*!< TIM CR1: UDIS (Bit 1)                              */
#define TIM_CR1_UDIS_Msk               (0x2UL)                   /*!< TIM CR1: UDIS (Bitfield-Mask: 0x01)                */
#define TIM_CR1_UDIS										TIM_CR1_UDIS_Msk
#define TIM_CR1_URS_Pos                (2UL)                     /*!< TIM CR1: URS (Bit 2)                               */
#define TIM_CR1_URS_Msk                (0x4UL)                   /*!< TIM CR1: URS (Bitfield-Mask: 0x01)                 */
#define TIM_CR1_URS											TIM_CR1_URS_Msk
#define TIM_CR1_OPM_Pos                (3UL)                     /*!< TIM CR1: OPM (Bit 3)                               */
#define TIM_CR1_OPM_Msk                (0x8UL)                   /*!< TIM CR1: OPM (Bitfield-Mask: 0x01)                 */
#define TIM_CR1_OPM											TIM_CR1_OPM_Msk
#define TIM_CR1_DIR_Pos                (4UL)                     /*!< TIM CR1: DIR (Bit 4)                               */
#define TIM_CR1_DIR_Msk                (0x10UL)                  /*!< TIM CR1: DIR (Bitfield-Mask: 0x01)                 */
#define TIM_CR1_DIR											TIM_CR1_DIR_Msk
#define TIM_CR1_CMS_Pos                (5UL)                     /*!< TIM CR1: CMS (Bit 5)                               */
#define TIM_CR1_CMS_Msk                (0x60UL)                  /*!< TIM CR1: CMS (Bitfield-Mask: 0x03)                 */
#define TIM_CR1_CMS											TIM_CR1_CMS_Msk
#define TIM_CR1_ARPE_Pos               (7UL)                     /*!< TIM CR1: ARPE (Bit 7)                              */
#define TIM_CR1_ARPE_Msk               (0x80UL)                  /*!< TIM CR1: ARPE (Bitfield-Mask: 0x01)                */
#define TIM_CR1_ARPE										TIM_CR1_ARPE_Msk
#define TIM_CR1_CKD_Pos                (8UL)                     /*!< TIM CR1: CKD (Bit 8)                               */
#define TIM_CR1_CKD_Msk                (0x300UL)                 /*!< TIM CR1: CKD (Bitfield-Mask: 0x03)                 */
#define TIM_CR1_CKD											TIM_CR1_CKD_Msk
/* ==========================================================  CR2  ========================================================== */
#define TIM_CR2_CCPC_Pos               (0UL)                     /*!< TIM CR2: CCPC (Bit 0)                              */
#define TIM_CR2_CCPC_Msk               (0x1UL)                   /*!< TIM CR2: CCPC (Bitfield-Mask: 0x01)                */
#define TIM_CR2_CCUS_Pos               (2UL)                     /*!< TIM CR2: CCUS (Bit 2)                              */
#define TIM_CR2_CCUS_Msk               (0x4UL)                   /*!< TIM CR2: CCUS (Bitfield-Mask: 0x01)                */
#define TIM_CR2_MMS_Pos                (4UL)                     /*!< TIM CR2: MMS (Bit 4)                               */
#define TIM_CR2_MMS_Msk                (0x70UL)                  /*!< TIM CR2: MMS (Bitfield-Mask: 0x07)                 */
#define TIM_CR2_TI1S_Pos               (7UL)                     /*!< TIM CR2: TI1S (Bit 7)                              */
#define TIM_CR2_TI1S_Msk               (0x80UL)                  /*!< TIM CR2: TI1S (Bitfield-Mask: 0x01)                */
#define TIM_CR2_TI1S										TIM_CR2_TI1S_Msk
#define TIM_CR2_OIS1_Pos               (8UL)                     /*!< TIM CR2: OIS1 (Bit 8)                              */
#define TIM_CR2_OIS1_Msk               (0x100UL)                 /*!< TIM CR2: OIS1 (Bitfield-Mask: 0x01)                */
#define TIM_CR2_OIS1										TIM_CR2_OIS1_Msk
#define TIM_CR2_OIS1N_Pos              (9UL)                     /*!< TIM CR2: OIS1N (Bit 9)                             */
#define TIM_CR2_OIS1N_Msk              (0x200UL)                 /*!< TIM CR2: OIS1N (Bitfield-Mask: 0x01)               */
#define TIM_CR2_OIS1N										TIM_CR2_OIS1N_Msk
#define TIM_CR2_OIS2_Pos               (10UL)                    /*!< TIM CR2: OIS2 (Bit 10)                             */
#define TIM_CR2_OIS2_Msk               (0x400UL)                 /*!< TIM CR2: OIS2 (Bitfield-Mask: 0x01)                */
#define TIM_CR2_OIS2										TIM_CR2_OIS2_Msk
#define TIM_CR2_OIS2N_Pos              (11UL)                    /*!< TIM CR2: OIS2N (Bit 11)                            */
#define TIM_CR2_OIS2N_Msk              (0x800UL)                 /*!< TIM CR2: OIS2N (Bitfield-Mask: 0x01)               */
#define TIM_CR2_OIS2N										TIM_CR2_OIS2N_Msk
#define TIM_CR2_OIS3_Pos               (12UL)                    /*!< TIM CR2: OIS3 (Bit 12)                             */
#define TIM_CR2_OIS3_Msk               (0x1000UL)                /*!< TIM CR2: OIS3 (Bitfield-Mask: 0x01)                */
#define TIM_CR2_OIS3										TIM_CR2_OIS3_Msk
#define TIM_CR2_OIS3N_Pos              (13UL)                    /*!< TIM CR2: OIS3N (Bit 13)                            */
#define TIM_CR2_OIS3N_Msk              (0x2000UL)                /*!< TIM CR2: OIS3N (Bitfield-Mask: 0x01)               */
#define TIM_CR2_OIS3N										TIM_CR2_OIS3N_Msk
#define TIM_CR2_OIS4_Pos               (14UL)                    /*!< TIM CR2: OIS4 (Bit 14)                             */
#define TIM_CR2_OIS4_Msk               (0x4000UL)                /*!< TIM CR2: OIS4 (Bitfield-Mask: 0x01)                */
#define TIM_CR2_OIS4										TIM_CR2_OIS4_Msk

/* =========================================================  SMCR  ========================================================== */
#define TIM_SMCR_SMS_Pos               (0UL)                     /*!< TIM SMCR: SMS (Bit 0)                              */
#define TIM_SMCR_SMS_Msk               (0x7UL)                   /*!< TIM SMCR: SMS (Bitfield-Mask: 0x07)                */
#define TIM_SMCR_SMS									  TIM_SMCR_SMS_Msk
#define TIM_SMCR_TS_Pos                (4UL)                     /*!< TIM SMCR: TS (Bit 4)                               */
#define TIM_SMCR_TS_Msk                (0x70UL)                  /*!< TIM SMCR: TS (Bitfield-Mask: 0x07)                 */
#define TIM_SMCR_TS											TIM_SMCR_TS_Msk
#define TIM_SMCR_TS_0                  (0x1U << TIM_SMCR_TS_Pos)        
#define TIM_SMCR_TS_1                  (0x2U << TIM_SMCR_TS_Pos)    
#define TIM_SMCR_TS_2                  (0x4U << TIM_SMCR_TS_Pos)     
#define TIM_SMCR_MSM_Pos               (7UL)                     /*!< TIM SMCR: MSM (Bit 7)                              */
#define TIM_SMCR_MSM_Msk               (0x80UL)                  /*!< TIM SMCR: MSM (Bitfield-Mask: 0x01)                */
#define TIM_SMCR_MSM										TIM_SMCR_MSM_Msk
#define TIM_SMCR_ETF_Pos               (8UL)                     /*!< TIM SMCR: ETF (Bit 8)                              */
#define TIM_SMCR_ETF_Msk               (0xf00UL)                 /*!< TIM SMCR: ETF (Bitfield-Mask: 0x0f)                */
#define TIM_SMCR_ETF										TIM_SMCR_ETF_Msk
#define TIM_SMCR_ETPS_Pos              (12UL)                    /*!< TIM SMCR: ETPS (Bit 12)                            */
#define TIM_SMCR_ETPS_Msk              (0x3000UL)                /*!< TIM SMCR: ETPS (Bitfield-Mask: 0x03)               */
#define TIM_SMCR_ETPS										TIM_SMCR_ETPS_Msk
#define TIM_SMCR_ETPS_0                (0x1U << TIM_SMCR_ETPS_Pos) 
#define TIM_SMCR_ETPS_1                (0x2U << TIM_SMCR_ETPS_Pos) 
#define TIM_SMCR_ECE_Pos               (14UL)                    /*!< TIM SMCR: ECE (Bit 14)                             */
#define TIM_SMCR_ECE_Msk               (0x4000UL)                /*!< TIM SMCR: ECE (Bitfield-Mask: 0x01)                */
#define TIM_SMCR_ECE										TIM_SMCR_ECE_Msk
#define TIM_SMCR_ETP_Pos               (15UL)                    /*!< TIM SMCR: ETP (Bit 15)                             */
#define TIM_SMCR_ETP_Msk               (0x8000UL)                /*!< TIM SMCR: ETP (Bitfield-Mask: 0x01)                */
#define TIM_SMCR_ETP										TIM_SMCR_ETP_Msk
/* =========================================================  DIER  ========================================================== */
#define TIM_DIER_UIE_Pos               (0UL)                     /*!< TIM DIER: UIE (Bit 0)                              */
#define TIM_DIER_UIE_Msk               (0x1UL)                   /*!< TIM DIER: UIE (Bitfield-Mask: 0x01)                */
#define TIM_DIER_UIE									  TIM_DIER_UIE_Msk
#define TIM_DIER_CC1IE_Pos             (1UL)                     /*!< TIM DIER: CC1IE (Bit 1)                            */
#define TIM_DIER_CC1IE_Msk             (0x2UL)                   /*!< TIM DIER: CC1IE (Bitfield-Mask: 0x01)              */
#define TIM_DIER_CC1IE								  TIM_DIER_CC1IE_Msk
#define TIM_DIER_CC2IE_Pos             (2UL)                     /*!< TIM DIER: CC2IE (Bit 2)                            */
#define TIM_DIER_CC2IE_Msk             (0x4UL)                   /*!< TIM DIER: CC2IE (Bitfield-Mask: 0x01)              */
#define TIM_DIER_CC2IE								  TIM_DIER_CC2IE_Msk
#define TIM_DIER_CC3IE_Pos             (3UL)                     /*!< TIM DIER: CC3IE (Bit 3)                            */
#define TIM_DIER_CC3IE_Msk             (0x8UL)                   /*!< TIM DIER: CC3IE (Bitfield-Mask: 0x01)              */
#define TIM_DIER_CC3IE								  TIM_DIER_CC3IE_Msk
#define TIM_DIER_CC4IE_Pos             (4UL)                     /*!< TIM DIER: CC4IE (Bit 4)                            */
#define TIM_DIER_CC4IE_Msk             (0x10UL)                  /*!< TIM DIER: CC4IE (Bitfield-Mask: 0x01)              */
#define TIM_DIER_CC4IE								  TIM_DIER_CC4IE_Msk
#define TIM_DIER_COMIE_Pos             (5UL)                     /*!< TIM DIER: COMIE (Bit 5)                            */
#define TIM_DIER_COMIE_Msk             (0x20UL)                  /*!< TIM DIER: COMIE (Bitfield-Mask: 0x01)              */
#define TIM_DIER_COMIE									TIM_DIER_COMIE_Msk
#define TIM_DIER_TIE_Pos               (6UL)                     /*!< TIM DIER: TIE (Bit 6)                              */
#define TIM_DIER_TIE_Msk               (0x40UL)                  /*!< TIM DIER: TIE (Bitfield-Mask: 0x01)                */
#define TIM_DIER_TIE										TIM_DIER_TIE_Msk
#define TIM_DIER_BIE_Pos               (7UL)                     /*!< TIM DIER: BIE (Bit 7)                              */
#define TIM_DIER_BIE_Msk               (0x80UL)                  /*!< TIM DIER: BIE (Bitfield-Mask: 0x01)                */
#define TIM_DIER_BIE										TIM_DIER_BIE_Msk
/* ==========================================================  SR  =========================================================== */
#define TIM_SR_CC4OF_Pos               (12UL)                    /*!< TIM SR: CC4OF (Bit 12)                             */
#define TIM_SR_CC4OF_Msk               (0x1000UL)                /*!< TIM SR: CC4OF (Bitfield-Mask: 0x01)                */
#define TIM_SR_CC4OF										TIM_SR_CC4OF_Msk
#define TIM_SR_CC3OF_Pos               (11UL)                    /*!< TIM SR: CC3OF (Bit 11)                             */
#define TIM_SR_CC3OF_Msk               (0x800UL)                 /*!< TIM SR: CC3OF (Bitfield-Mask: 0x01)                */
#define TIM_SR_CC3OF										TIM_SR_CC3OF_Msk
#define TIM_SR_CC2OF_Pos               (10UL)                    /*!< TIM SR: CC2OF (Bit 10)                             */
#define TIM_SR_CC2OF_Msk               (0x400UL)                 /*!< TIM SR: CC2OF (Bitfield-Mask: 0x01)                */
#define TIM_SR_CC2OF										TIM_SR_CC2OF_Msk
#define TIM_SR_CC1OF_Pos               (9UL)                     /*!< TIM SR: CC1OF (Bit 9)                              */
#define TIM_SR_CC1OF_Msk               (0x200UL)                 /*!< TIM SR: CC1OF (Bitfield-Mask: 0x01)                */
#define TIM_SR_CC1OF										TIM_SR_CC1OF_Msk
#define TIM_SR_BIF_Pos                 (7UL)                     /*!< TIM SR: BIF (Bit 7)                                */
#define TIM_SR_BIF_Msk                 (0x80UL)                  /*!< TIM SR: BIF (Bitfield-Mask: 0x01)                  */
#define TIM_SR_BIF											TIM_SR_BIF_Msk
#define TIM_SR_TIF_Pos                 (6UL)                     /*!< TIM SR: TIF (Bit 6)                                */
#define TIM_SR_TIF_Msk                 (0x40UL)                  /*!< TIM SR: TIF (Bitfield-Mask: 0x01)                  */
#define TIM_SR_TIF											TIM_SR_TIF_Msk
#define TIM_SR_COMIF_Pos               (5UL)                     /*!< TIM SR: COMIF (Bit 5)                              */
#define TIM_SR_COMIF_Msk               (0x20UL)                  /*!< TIM SR: COMIF (Bitfield-Mask: 0x01)                */
#define TIM_SR_COMIF										TIM_SR_COMIF_Msk
#define TIM_SR_CC4IF_Pos               (4UL)                     /*!< TIM SR: CC4IF (Bit 4)                              */
#define TIM_SR_CC4IF_Msk               (0x10UL)                  /*!< TIM SR: CC4IF (Bitfield-Mask: 0x01)                */
#define TIM_SR_CC4IF										TIM_SR_CC4IF_Msk
#define TIM_SR_CC3IF_Pos               (3UL)                     /*!< TIM SR: CC3IF (Bit 3)                              */
#define TIM_SR_CC3IF_Msk               (0x8UL)                   /*!< TIM SR: CC3IF (Bitfield-Mask: 0x01)                */
#define TIM_SR_CC3IF										TIM_SR_CC3IF_Msk
#define TIM_SR_CC2IF_Pos               (2UL)                     /*!< TIM SR: CC2IF (Bit 2)                              */
#define TIM_SR_CC2IF_Msk               (0x4UL)                   /*!< TIM SR: CC2IF (Bitfield-Mask: 0x01)                */
#define TIM_SR_CC2IF										TIM_SR_CC2IF_Msk
#define TIM_SR_CC1IF_Pos               (1UL)                     /*!< TIM SR: CC1IF (Bit 1)                              */
#define TIM_SR_CC1IF_Msk               (0x2UL)                   /*!< TIM SR: CC1IF (Bitfield-Mask: 0x01)                */
#define TIM_SR_CC1IF										TIM_SR_CC1IF_Msk
#define TIM_SR_UIF_Pos                 (0UL)                     /*!< TIM SR: UIF (Bit 0)                                */
#define TIM_SR_UIF_Msk                 (0x1UL)                   /*!< TIM SR: UIF (Bitfield-Mask: 0x01)                  */
#define TIM_SR_UIF										  TIM_SR_UIF_Msk
/* ==========================================================  EGR  ========================================================== */
#define TIM_EGR_BG_Pos                 (7UL)                     /*!< TIM EGR: BG (Bit 7)                                */
#define TIM_EGR_BG_Msk                 (0x80UL)                  /*!< TIM EGR: BG (Bitfield-Mask: 0x01)                  */
#define TIM_EGR_TG_Pos                 (6UL)                     /*!< TIM EGR: TG (Bit 6)                                */
#define TIM_EGR_TG_Msk                 (0x40UL)                  /*!< TIM EGR: TG (Bitfield-Mask: 0x01)                  */
#define TIM_EGR_COMG_Pos               (5UL)                     /*!< TIM EGR: COMG (Bit 5)                              */
#define TIM_EGR_COMG_Msk               (0x20UL)                  /*!< TIM EGR: COMG (Bitfield-Mask: 0x01)                */
#define TIM_EGR_CC4G_Pos               (4UL)                     /*!< TIM EGR: CC4G (Bit 4)                              */
#define TIM_EGR_CC4G_Msk               (0x10UL)                  /*!< TIM EGR: CC4G (Bitfield-Mask: 0x01)                */
#define TIM_EGR_CC3G_Pos               (3UL)                     /*!< TIM EGR: CC3G (Bit 3)                              */
#define TIM_EGR_CC3G_Msk               (0x8UL)                   /*!< TIM EGR: CC3G (Bitfield-Mask: 0x01)                */
#define TIM_EGR_CC2G_Pos               (2UL)                     /*!< TIM EGR: CC2G (Bit 2)                              */
#define TIM_EGR_CC2G_Msk               (0x4UL)                   /*!< TIM EGR: CC2G (Bitfield-Mask: 0x01)                */
#define TIM_EGR_CC1G_Pos               (1UL)                     /*!< TIM EGR: CC1G (Bit 1)                              */
#define TIM_EGR_CC1G_Msk               (0x2UL)                   /*!< TIM EGR: CC1G (Bitfield-Mask: 0x01)                */
#define TIM_EGR_UG_Pos                 (0UL)                     /*!< TIM EGR: UG (Bit 0)                                */
#define TIM_EGR_UG_Msk                 (0x1UL)                   /*!< TIM EGR: UG (Bitfield-Mask: 0x01)                  */
#define TIM_EGR_UG											TIM_EGR_UG_Msk		
/* =========================================================  CCMR1  ========================================================= */
#define TIM_CCMR1_OC2CE_Pos            (15UL)                    /*!< TIM CCMR1: OC2CE (Bit 15)                          */
#define TIM_CCMR1_OC2CE_Msk            (0x8000UL)                /*!< TIM CCMR1: OC2CE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR1_OC2CE									TIM_CCMR1_OC2CE_Msk
#define TIM_CCMR1_OC2M_Pos             (12UL)                    /*!< TIM CCMR1: OC2M (Bit 12)                           */
#define TIM_CCMR1_OC2M_Msk             (0x7000UL)                /*!< TIM CCMR1: OC2M (Bitfield-Mask: 0x07)              */
#define TIM_CCMR1_OC2M									TIM_CCMR1_OC2M_Msk
#define TIM_CCMR1_OC2M_0               (0x1U << TIM_CCMR1_OC2M_Pos)    
#define TIM_CCMR1_OC2M_1               (0x2U << TIM_CCMR1_OC2M_Pos)     
#define TIM_CCMR1_OC2M_2               (0x4U << TIM_CCMR1_OC2M_Pos)   
#define TIM_CCMR1_OC2PE_Pos            (11UL)                    /*!< TIM CCMR1: OC2PE (Bit 11)                          */
#define TIM_CCMR1_OC2PE_Msk            (0x800UL)                 /*!< TIM CCMR1: OC2PE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR1_OC2PE									TIM_CCMR1_OC2PE_Msk	
#define TIM_CCMR1_OC2FE_Pos            (10UL)                    /*!< TIM CCMR1: OC2FE (Bit 10)                          */
#define TIM_CCMR1_OC2FE_Msk            (0x400UL)                 /*!< TIM CCMR1: OC2FE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR1_OC2FE									TIM_CCMR1_OC2FE_Msk
#define TIM_CCMR1_CC2S_Pos             (8UL)                     /*!< TIM CCMR1: CC2S (Bit 8)                            */
#define TIM_CCMR1_CC2S_Msk             (0x300UL)                 /*!< TIM CCMR1: CC2S (Bitfield-Mask: 0x03)              */
#define TIM_CCMR1_CC2S									TIM_CCMR1_CC2S_Msk
#define TIM_CCMR1_CC2S_0               (0x1U << TIM_CCMR1_CC2S_Pos)      
#define TIM_CCMR1_CC2S_1               (0x2U << TIM_CCMR1_CC2S_Pos)   
#define TIM_CCMR1_OC1CE_Pos            (7UL)                     /*!< TIM CCMR1: OC1CE (Bit 7)                           */
#define TIM_CCMR1_OC1CE_Msk            (0x80UL)                  /*!< TIM CCMR1: OC1CE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR1_OC1CE									TIM_CCMR1_OC1CE_Msk
#define TIM_CCMR1_OC1M_Pos             (4UL)                     /*!< TIM CCMR1: OC1M (Bit 4)                            */
#define TIM_CCMR1_OC1M_Msk             (0x70UL)                  /*!< TIM CCMR1: OC1M (Bitfield-Mask: 0x07)              */
#define TIM_CCMR1_OC1M									TIM_CCMR1_OC1M_Msk
#define TIM_CCMR1_OC1M_0               (0x1U << TIM_CCMR1_OC1M_Pos)    
#define TIM_CCMR1_OC1M_1               (0x2U << TIM_CCMR1_OC1M_Pos)    
#define TIM_CCMR1_OC1M_2               (0x4U << TIM_CCMR1_OC1M_Pos)     
#define TIM_CCMR1_OC1PE_Pos            (3UL)                     /*!< TIM CCMR1: OC1PE (Bit 3)                           */
#define TIM_CCMR1_OC1PE_Msk            (0x8UL)                   /*!< TIM CCMR1: OC1PE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR1_OC1PE									TIM_CCMR1_OC1PE_Msk
#define TIM_CCMR1_OC1FE_Pos            (2UL)                     /*!< TIM CCMR1: OC1FE (Bit 2)                           */
#define TIM_CCMR1_OC1FE_Msk            (0x4UL)                   /*!< TIM CCMR1: OC1FE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR1_OC1FE									TIM_CCMR1_OC1FE_Msk
#define TIM_CCMR1_CC1S_Pos             (0UL)                     /*!< TIM CCMR1: CC1S (Bit 0)                            */
#define TIM_CCMR1_CC1S_Msk             (0x3UL)                   /*!< TIM CCMR1: CC1S (Bitfield-Mask: 0x03)              */
#define TIM_CCMR1_CC1S								 TIM_CCMR1_CC1S_Msk
#define TIM_CCMR1_CC1S_0               (0x1U << TIM_CCMR1_CC1S_Pos)   
#define TIM_CCMR1_CC1S_1               (0x2U << TIM_CCMR1_CC1S_Pos)     
#define TIM_CCMR1_IC1PSC_Pos           (2UL)                     /*!< TIM CCMR1: IC1PSC (Bit 2)                          */          
#define TIM_CCMR1_IC1PSC_Msk           (0x0000000CUL)     			 /*!< TIM CCMR1: IC1PSC (Bitfield-Mask: 0x03)            */
#define TIM_CCMR1_IC1PSC               TIM_CCMR1_IC1PSC_Msk               
#define TIM_CCMR1_IC1PSC_0             (0x00000004UL)     			 
#define TIM_CCMR1_IC1PSC_1             (0x00000008UL)     			 
#define TIM_CCMR1_IC1F_Pos             (4UL)                     /*!< TIM CCMR1: IC1F (Bit 4)                            */          
#define TIM_CCMR1_IC1F_Msk             (0x000000F0UL)       		 /*!< TIM CCMR1: IC1F (Bitfield-Mask: 0x0F)              */
#define TIM_CCMR1_IC1F                 TIM_CCMR1_IC1F_Msk                 
#define TIM_CCMR1_IC1F_0               (0x00000010UL)       
#define TIM_CCMR1_IC1F_1               (0x00000020UL)       
#define TIM_CCMR1_IC1F_2               (0x00000040UL)       
#define TIM_CCMR1_IC1F_3               (0x00000080UL)       
#define TIM_CCMR1_IC2PSC_Pos           (10UL)                 	 /*!< TIM CCMR1: IC2PSC (Bit 10)                         */              
#define TIM_CCMR1_IC2PSC_Msk           (0x00000C00UL)     			 /*!< TIM CCMR1: (Bitfield-Mask: 0x03)                   */ 
#define TIM_CCMR1_IC2PSC               TIM_CCMR1_IC2PSC_Msk              
#define TIM_CCMR1_IC2PSC_0             (0x00000400UL)     
#define TIM_CCMR1_IC2PSC_1             (0x00000800UL)    
#define TIM_CCMR1_IC2F_Pos             (12U)                     /*!< TIM CCMR1: IC2F (Bit 12)                           */           
#define TIM_CCMR1_IC2F_Msk             (0x0000F000UL)      			 /*!< TIM CCMR1: (Bitfield-Mask: 0x0F)                   */
#define TIM_CCMR1_IC2F                 TIM_CCMR1_IC2F_Msk                
#define TIM_CCMR1_IC2F_0               (0x00001000UL)       
#define TIM_CCMR1_IC2F_1               (0x00002000UL)      
#define TIM_CCMR1_IC2F_2               (0x00004000UL)       
#define TIM_CCMR1_IC2F_3               (0x00008000UL)      



/* =========================================================  CCMR2  ========================================================= */
#define TIM_CCMR2_OC4CE_Pos            (15UL)                    /*!< TIM CCMR2: OC4CE (Bit 15)                          */
#define TIM_CCMR2_OC4CE_Msk            (0x8000UL)                /*!< TIM CCMR2: OC4CE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR2_OC4CE									TIM_CCMR2_OC4CE_Msk
#define TIM_CCMR2_OC4M_Pos             (12UL)                    /*!< TIM CCMR2: OC4M (Bit 12)                           */
#define TIM_CCMR2_OC4M_Msk             (0x7000UL)                /*!< TIM CCMR2: OC4M (Bitfield-Mask: 0x07)              */
#define TIM_CCMR2_OC4M									TIM_CCMR2_OC4M_Msk
#define TIM_CCMR2_OC4PE_Pos            (11UL)                    /*!< TIM CCMR2: OC4PE (Bit 11)                          */
#define TIM_CCMR2_OC4PE_Msk            (0x800UL)                 /*!< TIM CCMR2: OC4PE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR2_OC4PE									TIM_CCMR2_OC4PE_Msk
#define TIM_CCMR2_OC4FE_Pos            (10UL)                    /*!< TIM CCMR2: OC4FE (Bit 10)                          */
#define TIM_CCMR2_OC4FE_Msk            (0x400UL)                 /*!< TIM CCMR2: OC4FE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR2_OC4FE									TIM_CCMR2_OC4FE_Msk
#define TIM_CCMR2_CC4S_Pos             (8UL)                     /*!< TIM CCMR2: CC4S (Bit 8)                            */
#define TIM_CCMR2_CC4S_Msk             (0x300UL)                 /*!< TIM CCMR2: CC4S (Bitfield-Mask: 0x03)              */
#define TIM_CCMR2_CC4S									TIM_CCMR2_CC4S_Msk
#define TIM_CCMR2_OC3CE_Pos            (7UL)                     /*!< TIM CCMR2: OC3CE (Bit 7)                           */
#define TIM_CCMR2_OC3CE_Msk            (0x80UL)                  /*!< TIM CCMR2: OC3CE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR2_OC3CE									TIM_CCMR2_OC3CE_Msk
#define TIM_CCMR2_OC3M_Pos             (4UL)                     /*!< TIM CCMR2: OC3M (Bit 4)                            */
#define TIM_CCMR2_OC3M_Msk             (0x70UL)                  /*!< TIM CCMR2: OC3M (Bitfield-Mask: 0x07)              */
#define TIM_CCMR2_OC3M									TIM_CCMR2_OC3M_Msk
#define TIM_CCMR2_OC3PE_Pos            (3UL)                     /*!< TIM CCMR2: OC3PE (Bit 3)                           */
#define TIM_CCMR2_OC3PE_Msk            (0x8UL)                   /*!< TIM CCMR2: OC3PE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR2_OC3PE									TIM_CCMR2_OC3PE_Msk
#define TIM_CCMR2_OC3FE_Pos            (2UL)                     /*!< TIM CCMR2: OC3FE (Bit 2)                           */
#define TIM_CCMR2_OC3FE_Msk            (0x4UL)                   /*!< TIM CCMR2: OC3FE (Bitfield-Mask: 0x01)             */
#define TIM_CCMR2_OC3FE									TIM_CCMR2_OC3FE_Msk
#define TIM_CCMR2_CC3S_Pos             (0UL)                     /*!< TIM CCMR2: CC3S (Bit 0)                            */
#define TIM_CCMR2_CC3S_Msk             (0x3UL)                   /*!< TIM CCMR2: CC3S (Bitfield-Mask: 0x03)              */
#define TIM_CCMR2_CC3S									TIM_CCMR2_CC3S_Msk

#define TIM_CCMR2_IC3PSC_Pos                (2UL)                               
#define TIM_CCMR2_IC3PSC_Msk                (0x0000000CUL)     
#define TIM_CCMR2_IC3PSC                    TIM_CCMR2_IC3PSC_Msk              
#define TIM_CCMR2_IC3PSC_0                  (0x00000004UL)    
#define TIM_CCMR2_IC3PSC_1                  (0x00000008UL)   
#define TIM_CCMR2_IC3F_Pos                  (4UL)                               
#define TIM_CCMR2_IC3F_Msk                  (0x000000F0UL)       
#define TIM_CCMR2_IC3F                      TIM_CCMR2_IC3F_Msk              
#define TIM_CCMR2_IC3F_0                    (0x00000010UL)     
#define TIM_CCMR2_IC3F_1                    (0x00000020UL)      
#define TIM_CCMR2_IC3F_2                    (0x00000040UL)      
#define TIM_CCMR2_IC3F_3                    (0x00000080UL)       
#define TIM_CCMR2_IC4PSC_Pos                (10UL)                              
#define TIM_CCMR2_IC4PSC_Msk                (0x00000C00UL)    
#define TIM_CCMR2_IC4PSC                    TIM_CCMR2_IC4PSC_Msk             
#define TIM_CCMR2_IC4PSC_0                  (0x00000400UL)    
#define TIM_CCMR2_IC4PSC_1                  (0x00000800UL)     
#define TIM_CCMR2_IC4F_Pos                  (12UL)                              
#define TIM_CCMR2_IC4F_Msk                  (0x0000F000UL)      
#define TIM_CCMR2_IC4F                      TIM_CCMR2_IC4F_Msk               
#define TIM_CCMR2_IC4F_0                    (0x00001000UL)      
#define TIM_CCMR2_IC4F_1                    (0x00002000UL)       
#define TIM_CCMR2_IC4F_2                    (0x00004000UL)       
#define TIM_CCMR2_IC4F_3                    (0x00008000UL)      


/* =========================================================  CCER  ========================================================== */
#define TIM_CCER_CC4P_Pos              (13UL)                    /*!< TIM CCER: CC4P (Bit 13)                            */
#define TIM_CCER_CC4P_Msk              (0x2000UL)                /*!< TIM CCER: CC4P (Bitfield-Mask: 0x01)               */
#define TIM_CCER_CC4P										TIM_CCER_CC4P_Msk
#define TIM_CCER_CC4E_Pos              (12UL)                    /*!< TIM CCER: CC4E (Bit 12)                            */
#define TIM_CCER_CC4E_Msk              (0x1000UL)                /*!< TIM CCER: CC4E (Bitfield-Mask: 0x01)               */
#define TIM_CCER_CC4E                   TIM_CCER_CC4E_Msk   
#define TIM_CCER_CC3NP_Pos             (11UL)                    /*!< TIM CCER: CC3NP (Bit 11)                           */
#define TIM_CCER_CC3NP_Msk             (0x800UL)                 /*!< TIM CCER: CC3NP (Bitfield-Mask: 0x01)              */
#define TIM_CCER_CC3NP									TIM_CCER_CC3NP_Msk
#define TIM_CCER_CC3NE_Pos             (10UL)                    /*!< TIM CCER: CC3NE (Bit 10)                           */
#define TIM_CCER_CC3NE_Msk             (0x400UL)                 /*!< TIM CCER: CC3NE (Bitfield-Mask: 0x01)              */
#define TIM_CCER_CC3NE                  TIM_CCER_CC3NE_Msk 
#define TIM_CCER_CC3P_Pos              (9UL)                     /*!< TIM CCER: CC3P (Bit 9)                             */
#define TIM_CCER_CC3P_Msk              (0x200UL)                 /*!< TIM CCER: CC3P (Bitfield-Mask: 0x01)               */
#define TIM_CCER_CC3P										TIM_CCER_CC3P_Msk
#define TIM_CCER_CC3E_Pos              (8UL)                     /*!< TIM CCER: CC3E (Bit 8)                             */
#define TIM_CCER_CC3E_Msk              (0x100UL)                 /*!< TIM CCER: CC3E (Bitfield-Mask: 0x01)               */
#define TIM_CCER_CC3E                   TIM_CCER_CC3E_Msk   
#define TIM_CCER_CC2NP_Pos             (7UL)                     /*!< TIM CCER: CC2NP (Bit 7)                            */
#define TIM_CCER_CC2NP_Msk             (0x80UL)                  /*!< TIM CCER: CC2NP (Bitfield-Mask: 0x01)              */
#define TIM_CCER_CC2NP								  TIM_CCER_CC2NP_Msk
#define TIM_CCER_CC2NE_Pos             (6UL)                     /*!< TIM CCER: CC2NE (Bit 6)                            */
#define TIM_CCER_CC2NE_Msk             (0x40UL)                  /*!< TIM CCER: CC2NE (Bitfield-Mask: 0x01)              */
#define TIM_CCER_CC2NE                  TIM_CCER_CC2NE_Msk 
#define TIM_CCER_CC2P_Pos              (5UL)                     /*!< TIM CCER: CC2P (Bit 5)                             */
#define TIM_CCER_CC2P_Msk              (0x20UL)                  /*!< TIM CCER: CC2P (Bitfield-Mask: 0x01)               */
#define TIM_CCER_CC2P										TIM_CCER_CC2P_Msk
#define TIM_CCER_CC2E_Pos              (4UL)                     /*!< TIM CCER: CC2E (Bit 4)                             */
#define TIM_CCER_CC2E_Msk              (0x10UL)                  /*!< TIM CCER: CC2E (Bitfield-Mask: 0x01)               */
#define TIM_CCER_CC2E                   TIM_CCER_CC2E_Msk   
#define TIM_CCER_CC1NP_Pos             (3UL)                     /*!< TIM CCER: CC1NP (Bit 3)                            */
#define TIM_CCER_CC1NP_Msk             (0x8UL)                   /*!< TIM CCER: CC1NP (Bitfield-Mask: 0x01)              */
#define TIM_CCER_CC1NP								  TIM_CCER_CC1NP_Msk
#define TIM_CCER_CC1NE_Pos             (2UL)                     /*!< TIM CCER: CC1NE (Bit 2)                            */
#define TIM_CCER_CC1NE_Msk             (0x4UL)                   /*!< TIM CCER: CC1NE (Bitfield-Mask: 0x01)              */
#define TIM_CCER_CC1NE                  TIM_CCER_CC1NE_Msk   
#define TIM_CCER_CC1P_Pos              (1UL)                     /*!< TIM CCER: CC1P (Bit 1)                             */
#define TIM_CCER_CC1P_Msk              (0x2UL)                   /*!< TIM CCER: CC1P (Bitfield-Mask: 0x01)               */
#define TIM_CCER_CC1P									  TIM_CCER_CC1P_Msk
#define TIM_CCER_CC1E_Pos              (0UL)                     /*!< TIM CCER: CC1E (Bit 0)                             */
#define TIM_CCER_CC1E_Msk              (0x1UL)                   /*!< TIM CCER: CC1E (Bitfield-Mask: 0x01)               */
#define TIM_CCER_CC1E                   TIM_CCER_CC1E_Msk         
/* ==========================================================  CNT  ========================================================== */
#define TIM_CNT_CNT_Pos                (0UL)                     /*!< TIM CNT: CNT (Bit 0)                               */
#define TIM_CNT_CNT_Msk                (0xffffUL)                /*!< TIM CNT: CNT (Bitfield-Mask: 0xffff)               */
/* ==========================================================  PSC  ========================================================== */
#define TIM_PSC_PSC_Pos                (0UL)                     /*!< TIM PSC: PSC (Bit 0)                               */
#define TIM_PSC_PSC_Msk                (0xffffUL)                /*!< TIM PSC: PSC (Bitfield-Mask: 0xffff)               */
/* ==========================================================  ARR  ========================================================== */
#define TIM_ARR_ARR_Pos                (0UL)                     /*!< TIM ARR: ARR (Bit 0)                               */
#define TIM_ARR_ARR_Msk                (0xffffUL)                /*!< TIM ARR: ARR (Bitfield-Mask: 0xffff)               */
/* ==========================================================  RCR  ========================================================== */
#define TIM_RCR_REP_Pos                (0UL)                     /*!< TIM RCR: REP (Bit 0)                               */
#define TIM_RCR_REP_Msk                (0xffUL)                  /*!< TIM RCR: REP (Bitfield-Mask: 0xff)                 */
/* =========================================================  CCR1  ========================================================== */
#define TIM_CCR1_CCR1_Pos              (0UL)                     /*!< TIM CCR1: CCR1 (Bit 0)                             */
#define TIM_CCR1_CCR1_Msk              (0xffffUL)                /*!< TIM CCR1: CCR1 (Bitfield-Mask: 0xffff)             */
/* =========================================================  CCR2  ========================================================== */
#define TIM_CCR2_CCR2_Pos              (0UL)                     /*!< TIM CCR2: CCR2 (Bit 0)                             */
#define TIM_CCR2_CCR2_Msk              (0xffffUL)                /*!< TIM CCR2: CCR2 (Bitfield-Mask: 0xffff)             */
/* =========================================================  CCR3  ========================================================== */
#define TIM_CCR3_CCR3_Pos              (0UL)                     /*!< TIM CCR3: CCR3 (Bit 0)                             */
#define TIM_CCR3_CCR3_Msk              (0xffffUL)                /*!< TIM CCR3: CCR3 (Bitfield-Mask: 0xffff)             */
/* =========================================================  CCR4  ========================================================== */
#define TIM_CCR4_CCR4_Pos              (0UL)                     /*!< TIM CCR4: CCR4 (Bit 0)                             */
#define TIM_CCR4_CCR4_Msk              (0xffffUL)                /*!< TIM CCR4: CCR4 (Bitfield-Mask: 0xffff)             */
/* =========================================================  BDTR  ========================================================== */
#define TIM_BDTR_DTG_Pos               (0UL)                     /*!< TIM BDTR: UTG (Bit 0)                              */
#define TIM_BDTR_DTG_Msk               (0xffUL)                  /*!< TIM BDTR: UTG (Bitfield-Mask: 0xff)                */
#define TIM_BDTR_DTG										TIM_BDTR_DTG_Msk
#define TIM_BDTR_DTG_0                 (0x01U << TIM_BDTR_DTG_Pos)        
#define TIM_BDTR_DTG_1                 (0x02U << TIM_BDTR_DTG_Pos)        
#define TIM_BDTR_DTG_2                 (0x04U << TIM_BDTR_DTG_Pos)        
#define TIM_BDTR_DTG_3                 (0x08U << TIM_BDTR_DTG_Pos)        
#define TIM_BDTR_DTG_4                 (0x10U << TIM_BDTR_DTG_Pos)        
#define TIM_BDTR_DTG_5                 (0x20U << TIM_BDTR_DTG_Pos)        
#define TIM_BDTR_DTG_6                 (0x40U << TIM_BDTR_DTG_Pos)        
#define TIM_BDTR_DTG_7                 (0x80U << TIM_BDTR_DTG_Pos)        
#define TIM_BDTR_LOCK_Pos              (8UL)                     /*!< TIM BDTR: LOCK (Bit 8)                             */
#define TIM_BDTR_LOCK_Msk              (0x300UL)                 /*!< TIM BDTR: LOCK (Bitfield-Mask: 0x03)               */
#define TIM_BDTR_LOCK										TIM_BDTR_LOCK_Msk
#define TIM_BDTR_LOCK_0                (0x1U << TIM_BDTR_LOCK_Pos)       
#define TIM_BDTR_LOCK_1                (0x2U << TIM_BDTR_LOCK_Pos)       
#define TIM_BDTR_OSSI_Pos              (10UL)                    /*!< TIM BDTR: OSSI (Bit 10)                            */
#define TIM_BDTR_OSSI_Msk              (0x400UL)                 /*!< TIM BDTR: OSSI (Bitfield-Mask: 0x01)               */
#define TIM_BDTR_OSSI										TIM_BDTR_OSSI_Msk
#define TIM_BDTR_OSSR_Pos              (11UL)                    /*!< TIM BDTR: OSSR (Bit 11)                            */
#define TIM_BDTR_OSSR_Msk              (0x800UL)                 /*!< TIM BDTR: OSSR (Bitfield-Mask: 0x01)               */
#define TIM_BDTR_OSSR										TIM_BDTR_OSSR_Msk
#define TIM_BDTR_BKE_Pos               (12UL)                    /*!< TIM BDTR: BKE (Bit 12)                             */
#define TIM_BDTR_BKE_Msk               (0x1000UL)                /*!< TIM BDTR: BKE (Bitfield-Mask: 0x01)                */
#define TIM_BDTR_BKE										TIM_BDTR_BKE_Msk
#define TIM_BDTR_BKP_Pos               (13UL)                    /*!< TIM BDTR: BKP (Bit 13)                             */
#define TIM_BDTR_BKP_Msk               (0x2000UL)                /*!< TIM BDTR: BKP (Bitfield-Mask: 0x01)                */
#define TIM_BDTR_BKP										TIM_BDTR_BKP_Msk
#define TIM_BDTR_AOE_Pos               (14UL)                    /*!< TIM BDTR: AOE (Bit 14)                             */
#define TIM_BDTR_AOE_Msk               (0x4000UL)                /*!< TIM BDTR: AOE (Bitfield-Mask: 0x01)                */
#define TIM_BDTR_AOE										TIM_BDTR_AOE_Msk
#define TIM_BDTR_MOE_Pos               (15UL)                    /*!< TIM BDTR: MOE (Bit 15)                             */
#define TIM_BDTR_MOE_Msk               (0x8000UL)                /*!< TIM BDTR: MOE (Bitfield-Mask: 0x01)                */
#define TIM_BDTR_MOE										TIM_BDTR_MOE_Msk

/* =========================================================================================================================== */
/* ================                                            CRC                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  RESULT  ========================================================= */
#define CRC_RESULT_RESULT_Pos             (0UL)                     /*!< CRC RESULT: RESULT (Bit 0)                            */
#define CRC_RESULT_RESULT_Msk             (0xffffUL)                /*!< CRC RESULT: RESULT (Bitfield-Mask: 0xffff)            */
#define CRC_RESULT_RESULT									 CRC_RESULT_RESULT_Msk
#define CRC_RESULT_FLAG_Pos               (16UL)                    /*!< CRC RESULT: FLAG (Bit 16)                             */
#define CRC_RESULT_FLAG_Msk               (0x10000UL)               /*!< CRC RESULT: FLAG (Bitfield-Mask: 0x01)                */
#define CRC_RESULT_FLAG										 CRC_RESULT_FLAG_Msk

/* =========================================================================================================================== */
/* ================                                           FLASH                                           ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define FLASH_CR_OP_Pos                   (0UL)                     /*!< FLASH CR: OP (Bit 0)                                  */
#define FLASH_CR_OP_Msk                   (0x3UL)                   /*!< FLASH CR: OP (Bitfield-Mask: 0x03)                    */
#define FLASH_CR_OP												FLASH_CR_OP_Msk
#define FLASH_CR_OP_0											(0x1 << FLASH_CR_OP_Pos)
#define FLASH_CR_OP_1											(0x2 << FLASH_CR_OP_Pos)
#define FLASH_CR_BUSY_Pos                 (2UL)                     /*!< FLASH CR: BUSY (Bit 2)                                */
#define FLASH_CR_BUSY_Msk                 (0x4UL)                   /*!< FLASH CR: BUSY (Bitfield-Mask: 0x01)                  */
#define FLASH_CR_BUSY											FLASH_CR_BUSY_Msk
#define FLASH_CR_IE_Pos                   (3UL)                     /*!< FLASH CR: IE (Bit 3)                                  */
#define FLASH_CR_IE_Msk                   (0x18UL)                  /*!< FLASH CR: IE (Bitfield-Mask: 0x03)                    */
#define FLASH_CR_IE												FLASH_CR_IE_Msk
#define FLASH_CR_IE_0											(0x1 << FLASH_CR_IE_Pos)
#define FLASH_CR_IE_1											(0x2 << FLASH_CR_IE_Pos)

/* ==========================================================  IFR  ========================================================== */
#define FLASH_IFR_IF1_Pos                 (1UL)                     /*!< FLASH IFR: IF1 (Bit 1)                                */
#define FLASH_IFR_IF1_Msk                 (0x2UL)                   /*!< FLASH IFR: IF1 (Bitfield-Mask: 0x01)                  */
#define FLASH_IFR_IF1											FLASH_IFR_IF1_Msk
#define FLASH_IFR_IF0_Pos                 (0UL)                     /*!< FLASH IFR: IF0 (Bit 0)                                */
#define FLASH_IFR_IF0_Msk                 (0x1UL)                   /*!< FLASH IFR: IF0 (Bitfield-Mask: 0x01)                  */
#define FLASH_IFR_IF0											FLASH_IFR_IF0_Msk
/* =========================================================  ICLR  ========================================================== */
#define FLASH_ICLR_ICLR1_Pos              (1UL)                     /*!< FLASH ICLR: ICLR1 (Bit 1)                             */
#define FLASH_ICLR_ICLR1_Msk              (0x2UL)                   /*!< FLASH ICLR: ICLR1 (Bitfield-Mask: 0x01)               */
#define FLASH_ICLR_ICLR1									FLASH_ICLR_ICLR1_Msk
#define FLASH_ICLR_ICLR0_Pos              (0UL)                     /*!< FLASH ICLR: ICLR0 (Bit 0)                             */
#define FLASH_ICLR_ICLR0_Msk              (0x1UL)                   /*!< FLASH ICLR: ICLR0 (Bitfield-Mask: 0x01)               */
#define FLASH_ICLR_ICLR0									FLASH_ICLR_ICLR0_Msk
/* ========================================================  BYPASS  ========================================================= */
#define FLASH_BYPASS_BYPASSSEQ_Pos        (0UL)                     /*!< FLASH BYPASS: BYPASSSEQ (Bit 0)                       */
#define FLASH_BYPASS_BYPASSSEQ_Msk        (0xffffUL)                /*!< FLASH BYPASS: BYPASSSEQ (Bitfield-Mask: 0xffff)       */
/* ========================================================  SLOCK0  ========================================================= */
#define FLASH_SLOCK0_SLOCK0_31_Pos        (31UL)                    /*!< FLASH SLOCK0: SLOCK0_31 (Bit 31)                      */
#define FLASH_SLOCK0_SLOCK0_31_Msk        (0x80000000UL)            /*!< FLASH SLOCK0: SLOCK0_31 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_30_Pos        (30UL)                    /*!< FLASH SLOCK0: SLOCK0_30 (Bit 30)                      */
#define FLASH_SLOCK0_SLOCK0_30_Msk        (0x40000000UL)            /*!< FLASH SLOCK0: SLOCK0_30 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_29_Pos        (29UL)                    /*!< FLASH SLOCK0: SLOCK0_29 (Bit 29)                      */
#define FLASH_SLOCK0_SLOCK0_29_Msk        (0x20000000UL)            /*!< FLASH SLOCK0: SLOCK0_29 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_28_Pos        (28UL)                    /*!< FLASH SLOCK0: SLOCK0_28 (Bit 28)                      */
#define FLASH_SLOCK0_SLOCK0_28_Msk        (0x10000000UL)            /*!< FLASH SLOCK0: SLOCK0_28 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_27_Pos        (27UL)                    /*!< FLASH SLOCK0: SLOCK0_27 (Bit 27)                      */
#define FLASH_SLOCK0_SLOCK0_27_Msk        (0x8000000UL)             /*!< FLASH SLOCK0: SLOCK0_27 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_26_Pos        (26UL)                    /*!< FLASH SLOCK0: SLOCK0_26 (Bit 26)                      */
#define FLASH_SLOCK0_SLOCK0_26_Msk        (0x4000000UL)             /*!< FLASH SLOCK0: SLOCK0_26 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_25_Pos        (25UL)                    /*!< FLASH SLOCK0: SLOCK0_25 (Bit 25)                      */
#define FLASH_SLOCK0_SLOCK0_25_Msk        (0x2000000UL)             /*!< FLASH SLOCK0: SLOCK0_25 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_24_Pos        (24UL)                    /*!< FLASH SLOCK0: SLOCK0_24 (Bit 24)                      */
#define FLASH_SLOCK0_SLOCK0_24_Msk        (0x1000000UL)             /*!< FLASH SLOCK0: SLOCK0_24 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_23_Pos        (23UL)                    /*!< FLASH SLOCK0: SLOCK0_23 (Bit 23)                      */
#define FLASH_SLOCK0_SLOCK0_23_Msk        (0x800000UL)              /*!< FLASH SLOCK0: SLOCK0_23 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_22_Pos        (22UL)                    /*!< FLASH SLOCK0: SLOCK0_22 (Bit 22)                      */
#define FLASH_SLOCK0_SLOCK0_22_Msk        (0x400000UL)              /*!< FLASH SLOCK0: SLOCK0_22 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_21_Pos        (21UL)                    /*!< FLASH SLOCK0: SLOCK0_21 (Bit 21)                      */
#define FLASH_SLOCK0_SLOCK0_21_Msk        (0x200000UL)              /*!< FLASH SLOCK0: SLOCK0_21 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_20_Pos        (20UL)                    /*!< FLASH SLOCK0: SLOCK0_20 (Bit 20)                      */
#define FLASH_SLOCK0_SLOCK0_20_Msk        (0x100000UL)              /*!< FLASH SLOCK0: SLOCK0_20 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_19_Pos        (19UL)                    /*!< FLASH SLOCK0: SLOCK0_19 (Bit 19)                      */
#define FLASH_SLOCK0_SLOCK0_19_Msk        (0x80000UL)               /*!< FLASH SLOCK0: SLOCK0_19 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_18_Pos        (18UL)                    /*!< FLASH SLOCK0: SLOCK0_18 (Bit 18)                      */
#define FLASH_SLOCK0_SLOCK0_18_Msk        (0x40000UL)               /*!< FLASH SLOCK0: SLOCK0_18 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_17_Pos        (17UL)                    /*!< FLASH SLOCK0: SLOCK0_17 (Bit 17)                      */
#define FLASH_SLOCK0_SLOCK0_17_Msk        (0x20000UL)               /*!< FLASH SLOCK0: SLOCK0_17 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_16_Pos        (16UL)                    /*!< FLASH SLOCK0: SLOCK0_16 (Bit 16)                      */
#define FLASH_SLOCK0_SLOCK0_16_Msk        (0x10000UL)               /*!< FLASH SLOCK0: SLOCK0_16 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_15_Pos        (15UL)                    /*!< FLASH SLOCK0: SLOCK0_15 (Bit 15)                      */
#define FLASH_SLOCK0_SLOCK0_15_Msk        (0x8000UL)                /*!< FLASH SLOCK0: SLOCK0_15 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_14_Pos        (14UL)                    /*!< FLASH SLOCK0: SLOCK0_14 (Bit 14)                      */
#define FLASH_SLOCK0_SLOCK0_14_Msk        (0x4000UL)                /*!< FLASH SLOCK0: SLOCK0_14 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_13_Pos        (13UL)                    /*!< FLASH SLOCK0: SLOCK0_13 (Bit 13)                      */
#define FLASH_SLOCK0_SLOCK0_13_Msk        (0x2000UL)                /*!< FLASH SLOCK0: SLOCK0_13 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_12_Pos        (12UL)                    /*!< FLASH SLOCK0: SLOCK0_12 (Bit 12)                      */
#define FLASH_SLOCK0_SLOCK0_12_Msk        (0x1000UL)                /*!< FLASH SLOCK0: SLOCK0_12 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_11_Pos        (11UL)                    /*!< FLASH SLOCK0: SLOCK0_11 (Bit 11)                      */
#define FLASH_SLOCK0_SLOCK0_11_Msk        (0x800UL)                 /*!< FLASH SLOCK0: SLOCK0_11 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_10_Pos        (10UL)                    /*!< FLASH SLOCK0: SLOCK0_10 (Bit 10)                      */
#define FLASH_SLOCK0_SLOCK0_10_Msk        (0x400UL)                 /*!< FLASH SLOCK0: SLOCK0_10 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK0_SLOCK0_9_Pos         (9UL)                     /*!< FLASH SLOCK0: SLOCK0_9 (Bit 9)                        */
#define FLASH_SLOCK0_SLOCK0_9_Msk         (0x200UL)                 /*!< FLASH SLOCK0: SLOCK0_9 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK0_SLOCK0_8_Pos         (8UL)                     /*!< FLASH SLOCK0: SLOCK0_8 (Bit 8)                        */
#define FLASH_SLOCK0_SLOCK0_8_Msk         (0x100UL)                 /*!< FLASH SLOCK0: SLOCK0_8 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK0_SLOCK0_7_Pos         (7UL)                     /*!< FLASH SLOCK0: SLOCK0_7 (Bit 7)                        */
#define FLASH_SLOCK0_SLOCK0_7_Msk         (0x80UL)                  /*!< FLASH SLOCK0: SLOCK0_7 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK0_SLOCK0_6_Pos         (6UL)                     /*!< FLASH SLOCK0: SLOCK0_6 (Bit 6)                        */
#define FLASH_SLOCK0_SLOCK0_6_Msk         (0x40UL)                  /*!< FLASH SLOCK0: SLOCK0_6 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK0_SLOCK0_5_Pos         (5UL)                     /*!< FLASH SLOCK0: SLOCK0_5 (Bit 5)                        */
#define FLASH_SLOCK0_SLOCK0_5_Msk         (0x20UL)                  /*!< FLASH SLOCK0: SLOCK0_5 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK0_SLOCK0_4_Pos         (4UL)                     /*!< FLASH SLOCK0: SLOCK0_4 (Bit 4)                        */
#define FLASH_SLOCK0_SLOCK0_4_Msk         (0x10UL)                  /*!< FLASH SLOCK0: SLOCK0_4 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK0_SLOCK0_3_Pos         (3UL)                     /*!< FLASH SLOCK0: SLOCK0_3 (Bit 3)                        */
#define FLASH_SLOCK0_SLOCK0_3_Msk         (0x8UL)                   /*!< FLASH SLOCK0: SLOCK0_3 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK0_SLOCK0_2_Pos         (2UL)                     /*!< FLASH SLOCK0: SLOCK0_2 (Bit 2)                        */
#define FLASH_SLOCK0_SLOCK0_2_Msk         (0x4UL)                   /*!< FLASH SLOCK0: SLOCK0_2 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK0_SLOCK0_1_Pos         (1UL)                     /*!< FLASH SLOCK0: SLOCK0_1 (Bit 1)                        */
#define FLASH_SLOCK0_SLOCK0_1_Msk         (0x2UL)                   /*!< FLASH SLOCK0: SLOCK0_1 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK0_SLOCK0_0_Pos         (0UL)                     /*!< FLASH SLOCK0: SLOCK0_0 (Bit 0)                        */
#define FLASH_SLOCK0_SLOCK0_0_Msk         (0x1UL)                   /*!< FLASH SLOCK0: SLOCK0_0 (Bitfield-Mask: 0x01)          */
/* ========================================================  SLOCK1  ========================================================= */
#define FLASH_SLOCK1_SLOCK1_31_Pos        (31UL)                    /*!< FLASH SLOCK1: SLOCK1_31 (Bit 31)                      */
#define FLASH_SLOCK1_SLOCK1_31_Msk        (0x80000000UL)            /*!< FLASH SLOCK1: SLOCK1_31 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_30_Pos        (30UL)                    /*!< FLASH SLOCK1: SLOCK1_30 (Bit 30)                      */
#define FLASH_SLOCK1_SLOCK1_30_Msk        (0x40000000UL)            /*!< FLASH SLOCK1: SLOCK1_30 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_29_Pos        (29UL)                    /*!< FLASH SLOCK1: SLOCK1_29 (Bit 29)                      */
#define FLASH_SLOCK1_SLOCK1_29_Msk        (0x20000000UL)            /*!< FLASH SLOCK1: SLOCK1_29 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_28_Pos        (28UL)                    /*!< FLASH SLOCK1: SLOCK1_28 (Bit 28)                      */
#define FLASH_SLOCK1_SLOCK1_28_Msk        (0x10000000UL)            /*!< FLASH SLOCK1: SLOCK1_28 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_27_Pos        (27UL)                    /*!< FLASH SLOCK1: SLOCK1_27 (Bit 27)                      */
#define FLASH_SLOCK1_SLOCK1_27_Msk        (0x8000000UL)             /*!< FLASH SLOCK1: SLOCK1_27 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_26_Pos        (26UL)                    /*!< FLASH SLOCK1: SLOCK1_26 (Bit 26)                      */
#define FLASH_SLOCK1_SLOCK1_26_Msk        (0x4000000UL)             /*!< FLASH SLOCK1: SLOCK1_26 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_25_Pos        (25UL)                    /*!< FLASH SLOCK1: SLOCK1_25 (Bit 25)                      */
#define FLASH_SLOCK1_SLOCK1_25_Msk        (0x2000000UL)             /*!< FLASH SLOCK1: SLOCK1_25 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_24_Pos        (24UL)                    /*!< FLASH SLOCK1: SLOCK1_24 (Bit 24)                      */
#define FLASH_SLOCK1_SLOCK1_24_Msk        (0x1000000UL)             /*!< FLASH SLOCK1: SLOCK1_24 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_23_Pos        (23UL)                    /*!< FLASH SLOCK1: SLOCK1_23 (Bit 23)                      */
#define FLASH_SLOCK1_SLOCK1_23_Msk        (0x800000UL)              /*!< FLASH SLOCK1: SLOCK1_23 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_22_Pos        (22UL)                    /*!< FLASH SLOCK1: SLOCK1_22 (Bit 22)                      */
#define FLASH_SLOCK1_SLOCK1_22_Msk        (0x400000UL)              /*!< FLASH SLOCK1: SLOCK1_22 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_21_Pos        (21UL)                    /*!< FLASH SLOCK1: SLOCK1_21 (Bit 21)                      */
#define FLASH_SLOCK1_SLOCK1_21_Msk        (0x200000UL)              /*!< FLASH SLOCK1: SLOCK1_21 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_20_Pos        (20UL)                    /*!< FLASH SLOCK1: SLOCK1_20 (Bit 20)                      */
#define FLASH_SLOCK1_SLOCK1_20_Msk        (0x100000UL)              /*!< FLASH SLOCK1: SLOCK1_20 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_19_Pos        (19UL)                    /*!< FLASH SLOCK1: SLOCK1_19 (Bit 19)                      */
#define FLASH_SLOCK1_SLOCK1_19_Msk        (0x80000UL)               /*!< FLASH SLOCK1: SLOCK1_19 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_18_Pos        (18UL)                    /*!< FLASH SLOCK1: SLOCK1_18 (Bit 18)                      */
#define FLASH_SLOCK1_SLOCK1_18_Msk        (0x40000UL)               /*!< FLASH SLOCK1: SLOCK1_18 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_17_Pos        (17UL)                    /*!< FLASH SLOCK1: SLOCK1_17 (Bit 17)                      */
#define FLASH_SLOCK1_SLOCK1_17_Msk        (0x20000UL)               /*!< FLASH SLOCK1: SLOCK1_17 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_16_Pos        (16UL)                    /*!< FLASH SLOCK1: SLOCK1_16 (Bit 16)                      */
#define FLASH_SLOCK1_SLOCK1_16_Msk        (0x10000UL)               /*!< FLASH SLOCK1: SLOCK1_16 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_15_Pos        (15UL)                    /*!< FLASH SLOCK1: SLOCK1_15 (Bit 15)                      */
#define FLASH_SLOCK1_SLOCK1_15_Msk        (0x8000UL)                /*!< FLASH SLOCK1: SLOCK1_15 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_14_Pos        (14UL)                    /*!< FLASH SLOCK1: SLOCK1_14 (Bit 14)                      */
#define FLASH_SLOCK1_SLOCK1_14_Msk        (0x4000UL)                /*!< FLASH SLOCK1: SLOCK1_14 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_13_Pos        (13UL)                    /*!< FLASH SLOCK1: SLOCK1_13 (Bit 13)                      */
#define FLASH_SLOCK1_SLOCK1_13_Msk        (0x2000UL)                /*!< FLASH SLOCK1: SLOCK1_13 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_12_Pos        (12UL)                    /*!< FLASH SLOCK1: SLOCK1_12 (Bit 12)                      */
#define FLASH_SLOCK1_SLOCK1_12_Msk        (0x1000UL)                /*!< FLASH SLOCK1: SLOCK1_12 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_11_Pos        (11UL)                    /*!< FLASH SLOCK1: SLOCK1_11 (Bit 11)                      */
#define FLASH_SLOCK1_SLOCK1_11_Msk        (0x800UL)                 /*!< FLASH SLOCK1: SLOCK1_11 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_10_Pos        (10UL)                    /*!< FLASH SLOCK1: SLOCK1_10 (Bit 10)                      */
#define FLASH_SLOCK1_SLOCK1_10_Msk        (0x400UL)                 /*!< FLASH SLOCK1: SLOCK1_10 (Bitfield-Mask: 0x01)         */
#define FLASH_SLOCK1_SLOCK1_9_Pos         (9UL)                     /*!< FLASH SLOCK1: SLOCK1_9 (Bit 9)                        */
#define FLASH_SLOCK1_SLOCK1_9_Msk         (0x200UL)                 /*!< FLASH SLOCK1: SLOCK1_9 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK1_SLOCK1_8_Pos         (8UL)                     /*!< FLASH SLOCK1: SLOCK1_8 (Bit 8)                        */
#define FLASH_SLOCK1_SLOCK1_8_Msk         (0x100UL)                 /*!< FLASH SLOCK1: SLOCK1_8 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK1_SLOCK1_7_Pos         (7UL)                     /*!< FLASH SLOCK1: SLOCK1_7 (Bit 7)                        */
#define FLASH_SLOCK1_SLOCK1_7_Msk         (0x80UL)                  /*!< FLASH SLOCK1: SLOCK1_7 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK1_SLOCK1_6_Pos         (6UL)                     /*!< FLASH SLOCK1: SLOCK1_6 (Bit 6)                        */
#define FLASH_SLOCK1_SLOCK1_6_Msk         (0x40UL)                  /*!< FLASH SLOCK1: SLOCK1_6 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK1_SLOCK1_5_Pos         (5UL)                     /*!< FLASH SLOCK1: SLOCK1_5 (Bit 5)                        */
#define FLASH_SLOCK1_SLOCK1_5_Msk         (0x20UL)                  /*!< FLASH SLOCK1: SLOCK1_5 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK1_SLOCK1_4_Pos         (4UL)                     /*!< FLASH SLOCK1: SLOCK1_4 (Bit 4)                        */
#define FLASH_SLOCK1_SLOCK1_4_Msk         (0x10UL)                  /*!< FLASH SLOCK1: SLOCK1_4 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK1_SLOCK1_3_Pos         (3UL)                     /*!< FLASH SLOCK1: SLOCK1_3 (Bit 3)                        */
#define FLASH_SLOCK1_SLOCK1_3_Msk         (0x8UL)                   /*!< FLASH SLOCK1: SLOCK1_3 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK1_SLOCK1_2_Pos         (2UL)                     /*!< FLASH SLOCK1: SLOCK1_2 (Bit 2)                        */
#define FLASH_SLOCK1_SLOCK1_2_Msk         (0x4UL)                   /*!< FLASH SLOCK1: SLOCK1_2 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK1_SLOCK1_1_Pos         (1UL)                     /*!< FLASH SLOCK1: SLOCK1_1 (Bit 1)                        */
#define FLASH_SLOCK1_SLOCK1_1_Msk         (0x2UL)                   /*!< FLASH SLOCK1: SLOCK1_1 (Bitfield-Mask: 0x01)          */
#define FLASH_SLOCK1_SLOCK1_0_Pos         (0UL)                     /*!< FLASH SLOCK1: SLOCK1_0 (Bit 0)                        */
#define FLASH_SLOCK1_SLOCK1_0_Msk         (0x1UL)                   /*!< FLASH SLOCK1: SLOCK1_0 (Bitfield-Mask: 0x01)          */
/* ========================================================  ISPCON  ========================================================= */
#define FLASH_ISPCON_ISP_CON_Pos          (0UL)                     /*!< FLASH ISPCON: ISP_CON (Bit 0)                         */
#define FLASH_ISPCON_ISP_CON_Msk          (0x1UL)                   /*!< FLASH ISPCON: ISP_CON (Bitfield-Mask: 0x01)           */


/* =========================================================================================================================== */
/* ================                                           GPIO                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  DIRCR  ========================================================= */
#define GPIO_DIRCR_PxDIR7_Pos             (7UL)                     /*!< GPIO DIRCR: PxDIR7 (Bit 7)                            */
#define GPIO_DIRCR_PxDIR7_Msk             (0x80UL)                  /*!< GPIO DIRCR: PxDIR7 (Bitfield-Mask: 0x01)              */
#define GPIO_DIRCR_PxDIR6_Pos             (6UL)                     /*!< GPIO DIRCR: PxDIR6 (Bit 6)                            */
#define GPIO_DIRCR_PxDIR6_Msk             (0x40UL)                  /*!< GPIO DIRCR: PxDIR6 (Bitfield-Mask: 0x01)              */
#define GPIO_DIRCR_PxDIR5_Pos             (5UL)                     /*!< GPIO DIRCR: PxDIR5 (Bit 5)                            */
#define GPIO_DIRCR_PxDIR5_Msk             (0x20UL)                  /*!< GPIO DIRCR: PxDIR5 (Bitfield-Mask: 0x01)              */
#define GPIO_DIRCR_PxDIR4_Pos             (4UL)                     /*!< GPIO DIRCR: PxDIR4 (Bit 4)                            */
#define GPIO_DIRCR_PxDIR4_Msk             (0x10UL)                  /*!< GPIO DIRCR: PxDIR4 (Bitfield-Mask: 0x01)              */
#define GPIO_DIRCR_PxDIR3_Pos             (3UL)                     /*!< GPIO DIRCR: PxDIR3 (Bit 3)                            */
#define GPIO_DIRCR_PxDIR3_Msk             (0x8UL)                   /*!< GPIO DIRCR: PxDIR3 (Bitfield-Mask: 0x01)              */
#define GPIO_DIRCR_PxDIR2_Pos             (2UL)                     /*!< GPIO DIRCR: PxDIR2 (Bit 2)                            */
#define GPIO_DIRCR_PxDIR2_Msk             (0x4UL)                   /*!< GPIO DIRCR: PxDIR2 (Bitfield-Mask: 0x01)              */
#define GPIO_DIRCR_PxDIR1_Pos             (1UL)                     /*!< GPIO DIRCR: PxDIR1 (Bit 1)                            */
#define GPIO_DIRCR_PxDIR1_Msk             (0x2UL)                   /*!< GPIO DIRCR: PxDIR1 (Bitfield-Mask: 0x01)              */
#define GPIO_DIRCR_PxDIR0_Pos             (0UL)                     /*!< GPIO DIRCR: PxDIR0 (Bit 0)                            */
#define GPIO_DIRCR_PxDIR0_Msk             (0x1UL)                   /*!< GPIO DIRCR: PxDIR0 (Bitfield-Mask: 0x01)              */
#define GPIO_DIRCR_PxDIR0 								 GPIO_DIRCR_PxDIR0_Msk
/* ========================================================  OTYPER  ========================================================= */
#define GPIO_OTYPER_PxOTYP7_Pos           (7UL)                     /*!< GPIO OTYPER: PxOTYP7 (Bit 7)                          */
#define GPIO_OTYPER_PxOTYP7_Msk           (0x80UL)                  /*!< GPIO OTYPER: PxOTYP7 (Bitfield-Mask: 0x01)            */
#define GPIO_OTYPER_PxOTYP6_Pos           (6UL)                     /*!< GPIO OTYPER: PxOTYP6 (Bit 6)                          */
#define GPIO_OTYPER_PxOTYP6_Msk           (0x40UL)                  /*!< GPIO OTYPER: PxOTYP6 (Bitfield-Mask: 0x01)            */
#define GPIO_OTYPER_PxOTYP5_Pos           (5UL)                     /*!< GPIO OTYPER: PxOTYP5 (Bit 5)                          */
#define GPIO_OTYPER_PxOTYP5_Msk           (0x20UL)                  /*!< GPIO OTYPER: PxOTYP5 (Bitfield-Mask: 0x01)            */
#define GPIO_OTYPER_PxOTYP4_Pos           (4UL)                     /*!< GPIO OTYPER: PxOTYP4 (Bit 4)                          */
#define GPIO_OTYPER_PxOTYP4_Msk           (0x10UL)                  /*!< GPIO OTYPER: PxOTYP4 (Bitfield-Mask: 0x01)            */
#define GPIO_OTYPER_PxOTYP3_Pos           (3UL)                     /*!< GPIO OTYPER: PxOTYP3 (Bit 3)                          */
#define GPIO_OTYPER_PxOTYP3_Msk           (0x8UL)                   /*!< GPIO OTYPER: PxOTYP3 (Bitfield-Mask: 0x01)            */
#define GPIO_OTYPER_PxOTYP2_Pos           (2UL)                     /*!< GPIO OTYPER: PxOTYP2 (Bit 2)                          */
#define GPIO_OTYPER_PxOTYP2_Msk           (0x4UL)                   /*!< GPIO OTYPER: PxOTYP2 (Bitfield-Mask: 0x01)            */
#define GPIO_OTYPER_PxOTYP1_Pos           (1UL)                     /*!< GPIO OTYPER: PxOTYP1 (Bit 1)                          */
#define GPIO_OTYPER_PxOTYP1_Msk           (0x2UL)                   /*!< GPIO OTYPER: PxOTYP1 (Bitfield-Mask: 0x01)            */
#define GPIO_OTYPER_PxOTYP0_Pos           (0UL)                     /*!< GPIO OTYPER: PxOTYP0 (Bit 0)                          */
#define GPIO_OTYPER_PxOTYP0_Msk           (0x1UL)                   /*!< GPIO OTYPER: PxOTYP0 (Bitfield-Mask: 0x01)            */
/* ==========================================================  ODR  ========================================================== */
#define GPIO_ODR_PxOD7_Pos                (7UL)                     /*!< GPIO ODR: PxOD7 (Bit 7)                               */
#define GPIO_ODR_PxOD7_Msk                (0x80UL)                  /*!< GPIO ODR: PxOD7 (Bitfield-Mask: 0x01)                 */
#define GPIO_ODR_PxOD6_Pos                (6UL)                     /*!< GPIO ODR: PxOD6 (Bit 6)                               */
#define GPIO_ODR_PxOD6_Msk                (0x40UL)                  /*!< GPIO ODR: PxOD6 (Bitfield-Mask: 0x01)                 */
#define GPIO_ODR_PxOD5_Pos                (5UL)                     /*!< GPIO ODR: PxOD5 (Bit 5)                               */
#define GPIO_ODR_PxOD5_Msk                (0x20UL)                  /*!< GPIO ODR: PxOD5 (Bitfield-Mask: 0x01)                 */
#define GPIO_ODR_PxOD4_Pos                (4UL)                     /*!< GPIO ODR: PxOD4 (Bit 4)                               */
#define GPIO_ODR_PxOD4_Msk                (0x10UL)                  /*!< GPIO ODR: PxOD4 (Bitfield-Mask: 0x01)                 */
#define GPIO_ODR_PxOD3_Pos                (3UL)                     /*!< GPIO ODR: PxOD3 (Bit 3)                               */
#define GPIO_ODR_PxOD3_Msk                (0x8UL)                   /*!< GPIO ODR: PxOD3 (Bitfield-Mask: 0x01)                 */
#define GPIO_ODR_PxOD2_Pos                (2UL)                     /*!< GPIO ODR: PxOD2 (Bit 2)                               */
#define GPIO_ODR_PxOD2_Msk                (0x4UL)                   /*!< GPIO ODR: PxOD2 (Bitfield-Mask: 0x01)                 */
#define GPIO_ODR_PxOD1_Pos                (1UL)                     /*!< GPIO ODR: PxOD1 (Bit 1)                               */
#define GPIO_ODR_PxOD1_Msk                (0x2UL)                   /*!< GPIO ODR: PxOD1 (Bitfield-Mask: 0x01)                 */
#define GPIO_ODR_PxOD0_Pos                (0UL)                     /*!< GPIO ODR: PxOD0 (Bit 0)                               */
#define GPIO_ODR_PxOD0_Msk                (0x1UL)                   /*!< GPIO ODR: PxOD0 (Bitfield-Mask: 0x01)                 */
/* ==========================================================  IDR  ========================================================== */
#define GPIO_IDR_PxID7_Pos                (7UL)                     /*!< GPIO IDR: PxID7 (Bit 7)                               */
#define GPIO_IDR_PxID7_Msk                (0x80UL)                  /*!< GPIO IDR: PxID7 (Bitfield-Mask: 0x01)                 */
#define GPIO_IDR_PxID6_Pos                (6UL)                     /*!< GPIO IDR: PxID6 (Bit 6)                               */
#define GPIO_IDR_PxID6_Msk                (0x40UL)                  /*!< GPIO IDR: PxID6 (Bitfield-Mask: 0x01)                 */
#define GPIO_IDR_PxID5_Pos                (5UL)                     /*!< GPIO IDR: PxID5 (Bit 5)                               */
#define GPIO_IDR_PxID5_Msk                (0x20UL)                  /*!< GPIO IDR: PxID5 (Bitfield-Mask: 0x01)                 */
#define GPIO_IDR_PxID4_Pos                (4UL)                     /*!< GPIO IDR: PxID4 (Bit 4)                               */
#define GPIO_IDR_PxID4_Msk                (0x10UL)                  /*!< GPIO IDR: PxID4 (Bitfield-Mask: 0x01)                 */
#define GPIO_IDR_PxID3_Pos                (3UL)                     /*!< GPIO IDR: PxID3 (Bit 3)                               */
#define GPIO_IDR_PxID3_Msk                (0x8UL)                   /*!< GPIO IDR: PxID3 (Bitfield-Mask: 0x01)                 */
#define GPIO_IDR_PxID2_Pos                (2UL)                     /*!< GPIO IDR: PxID2 (Bit 2)                               */
#define GPIO_IDR_PxID2_Msk                (0x4UL)                   /*!< GPIO IDR: PxID2 (Bitfield-Mask: 0x01)                 */
#define GPIO_IDR_PxID1_Pos                (1UL)                     /*!< GPIO IDR: PxID1 (Bit 1)                               */
#define GPIO_IDR_PxID1_Msk                (0x2UL)                   /*!< GPIO IDR: PxID1 (Bitfield-Mask: 0x01)                 */
#define GPIO_IDR_PxID0_Pos                (0UL)                     /*!< GPIO IDR: PxID0 (Bit 0)                               */
#define GPIO_IDR_PxID0_Msk                (0x1UL)                   /*!< GPIO IDR: PxID0 (Bitfield-Mask: 0x01)                 */
/* =========================================================  INTEN  ========================================================= */
#define GPIO_INTEN_PxIEN7_Pos             (7UL)                     /*!< GPIO INTEN: PxIEN7 (Bit 7)                            */
#define GPIO_INTEN_PxIEN7_Msk             (0x80UL)                  /*!< GPIO INTEN: PxIEN7 (Bitfield-Mask: 0x01)              */
#define GPIO_INTEN_PxIEN6_Pos             (6UL)                     /*!< GPIO INTEN: PxIEN6 (Bit 6)                            */
#define GPIO_INTEN_PxIEN6_Msk             (0x40UL)                  /*!< GPIO INTEN: PxIEN6 (Bitfield-Mask: 0x01)              */
#define GPIO_INTEN_PxIEN5_Pos             (5UL)                     /*!< GPIO INTEN: PxIEN5 (Bit 5)                            */
#define GPIO_INTEN_PxIEN5_Msk             (0x20UL)                  /*!< GPIO INTEN: PxIEN5 (Bitfield-Mask: 0x01)              */
#define GPIO_INTEN_PxIEN4_Pos             (4UL)                     /*!< GPIO INTEN: PxIEN4 (Bit 4)                            */
#define GPIO_INTEN_PxIEN4_Msk             (0x10UL)                  /*!< GPIO INTEN: PxIEN4 (Bitfield-Mask: 0x01)              */
#define GPIO_INTEN_PxIEN3_Pos             (3UL)                     /*!< GPIO INTEN: PxIEN3 (Bit 3)                            */
#define GPIO_INTEN_PxIEN3_Msk             (0x8UL)                   /*!< GPIO INTEN: PxIEN3 (Bitfield-Mask: 0x01)              */
#define GPIO_INTEN_PxIEN2_Pos             (2UL)                     /*!< GPIO INTEN: PxIEN2 (Bit 2)                            */
#define GPIO_INTEN_PxIEN2_Msk             (0x4UL)                   /*!< GPIO INTEN: PxIEN2 (Bitfield-Mask: 0x01)              */
#define GPIO_INTEN_PxIEN1_Pos             (1UL)                     /*!< GPIO INTEN: PxIEN1 (Bit 1)                            */
#define GPIO_INTEN_PxIEN1_Msk             (0x2UL)                   /*!< GPIO INTEN: PxIEN1 (Bitfield-Mask: 0x01)              */
#define GPIO_INTEN_PxIEN0_Pos             (0UL)                     /*!< GPIO INTEN: PxIEN0 (Bit 0)                            */
#define GPIO_INTEN_PxIEN0_Msk             (0x1UL)                   /*!< GPIO INTEN: PxIEN0 (Bitfield-Mask: 0x01)              */
#define GPIO_INTEN_PxIEN0									 GPIO_INTEN_PxIEN0_Msk	

/* =======================================================  RAWINTST  ======================================================== */
#define GPIO_RAWINTST_PxRIS7_Pos          (7UL)                     /*!< GPIO RAWINTST: PxRIS7 (Bit 7)                         */
#define GPIO_RAWINTST_PxRIS7_Msk          (0x80UL)                  /*!< GPIO RAWINTST: PxRIS7 (Bitfield-Mask: 0x01)           */
#define GPIO_RAWINTST_PxRIS6_Pos          (6UL)                     /*!< GPIO RAWINTST: PxRIS6 (Bit 6)                         */
#define GPIO_RAWINTST_PxRIS6_Msk          (0x40UL)                  /*!< GPIO RAWINTST: PxRIS6 (Bitfield-Mask: 0x01)           */
#define GPIO_RAWINTST_PxRIS5_Pos          (5UL)                     /*!< GPIO RAWINTST: PxRIS5 (Bit 5)                         */
#define GPIO_RAWINTST_PxRIS5_Msk          (0x20UL)                  /*!< GPIO RAWINTST: PxRIS5 (Bitfield-Mask: 0x01)           */
#define GPIO_RAWINTST_PxRIS4_Pos          (4UL)                     /*!< GPIO RAWINTST: PxRIS4 (Bit 4)                         */
#define GPIO_RAWINTST_PxRIS4_Msk          (0x10UL)                  /*!< GPIO RAWINTST: PxRIS4 (Bitfield-Mask: 0x01)           */
#define GPIO_RAWINTST_PxRIS3_Pos          (3UL)                     /*!< GPIO RAWINTST: PxRIS3 (Bit 3)                         */
#define GPIO_RAWINTST_PxRIS3_Msk          (0x8UL)                   /*!< GPIO RAWINTST: PxRIS3 (Bitfield-Mask: 0x01)           */
#define GPIO_RAWINTST_PxRIS2_Pos          (2UL)                     /*!< GPIO RAWINTST: PxRIS2 (Bit 2)                         */
#define GPIO_RAWINTST_PxRIS2_Msk          (0x4UL)                   /*!< GPIO RAWINTST: PxRIS2 (Bitfield-Mask: 0x01)           */
#define GPIO_RAWINTST_PxRIS1_Pos          (1UL)                     /*!< GPIO RAWINTST: PxRIS1 (Bit 1)                         */
#define GPIO_RAWINTST_PxRIS1_Msk          (0x2UL)                   /*!< GPIO RAWINTST: PxRIS1 (Bitfield-Mask: 0x01)           */
#define GPIO_RAWINTST_PxRIS0_Pos          (0UL)                     /*!< GPIO RAWINTST: PxRIS0 (Bit 0)                         */
#define GPIO_RAWINTST_PxRIS0_Msk          (0x1UL)                   /*!< GPIO RAWINTST: PxRIS0 (Bitfield-Mask: 0x01)           */
/* =======================================================  MSKINTCR  ======================================================== */
#define GPIO_MSKINTCR_PxMIS7_Pos          (7UL)                     /*!< GPIO MSKINTCR: PxMIS7 (Bit 7)                         */
#define GPIO_MSKINTCR_PxMIS7_Msk          (0x80UL)                  /*!< GPIO MSKINTCR: PxMIS7 (Bitfield-Mask: 0x01)           */
#define GPIO_MSKINTCR_PxMIS6_Pos          (6UL)                     /*!< GPIO MSKINTCR: PxMIS6 (Bit 6)                         */
#define GPIO_MSKINTCR_PxMIS6_Msk          (0x40UL)                  /*!< GPIO MSKINTCR: PxMIS6 (Bitfield-Mask: 0x01)           */
#define GPIO_MSKINTCR_PxMIS5_Pos          (5UL)                     /*!< GPIO MSKINTCR: PxMIS5 (Bit 5)                         */
#define GPIO_MSKINTCR_PxMIS5_Msk          (0x20UL)                  /*!< GPIO MSKINTCR: PxMIS5 (Bitfield-Mask: 0x01)           */
#define GPIO_MSKINTCR_PxMIS4_Pos          (4UL)                     /*!< GPIO MSKINTCR: PxMIS4 (Bit 4)                         */
#define GPIO_MSKINTCR_PxMIS4_Msk          (0x10UL)                  /*!< GPIO MSKINTCR: PxMIS4 (Bitfield-Mask: 0x01)           */
#define GPIO_MSKINTCR_PxMIS3_Pos          (3UL)                     /*!< GPIO MSKINTCR: PxMIS3 (Bit 3)                         */
#define GPIO_MSKINTCR_PxMIS3_Msk          (0x8UL)                   /*!< GPIO MSKINTCR: PxMIS3 (Bitfield-Mask: 0x01)           */
#define GPIO_MSKINTCR_PxMIS2_Pos          (2UL)                     /*!< GPIO MSKINTCR: PxMIS2 (Bit 2)                         */
#define GPIO_MSKINTCR_PxMIS2_Msk          (0x4UL)                   /*!< GPIO MSKINTCR: PxMIS2 (Bitfield-Mask: 0x01)           */
#define GPIO_MSKINTCR_PxMIS1_Pos          (1UL)                     /*!< GPIO MSKINTCR: PxMIS1 (Bit 1)                         */
#define GPIO_MSKINTCR_PxMIS1_Msk          (0x2UL)                   /*!< GPIO MSKINTCR: PxMIS1 (Bitfield-Mask: 0x01)           */
#define GPIO_MSKINTCR_PxMIS0_Pos          (0UL)                     /*!< GPIO MSKINTCR: PxMIS0 (Bit 0)                         */
#define GPIO_MSKINTCR_PxMIS0_Msk          (0x1UL)                   /*!< GPIO MSKINTCR: PxMIS0 (Bitfield-Mask: 0x01)           */
/* ========================================================  INTCLR  ========================================================= */
#define GPIO_INTCLR_PxICLR7_Pos           (7UL)                     /*!< GPIO INTCLR: PxICLR7 (Bit 7)                          */
#define GPIO_INTCLR_PxICLR7_Msk           (0x80UL)                  /*!< GPIO INTCLR: PxICLR7 (Bitfield-Mask: 0x01)            */
#define GPIO_INTCLR_PxICLR6_Pos           (6UL)                     /*!< GPIO INTCLR: PxICLR6 (Bit 6)                          */
#define GPIO_INTCLR_PxICLR6_Msk           (0x40UL)                  /*!< GPIO INTCLR: PxICLR6 (Bitfield-Mask: 0x01)            */
#define GPIO_INTCLR_PxICLR5_Pos           (5UL)                     /*!< GPIO INTCLR: PxICLR5 (Bit 5)                          */
#define GPIO_INTCLR_PxICLR5_Msk           (0x20UL)                  /*!< GPIO INTCLR: PxICLR5 (Bitfield-Mask: 0x01)            */
#define GPIO_INTCLR_PxICLR4_Pos           (4UL)                     /*!< GPIO INTCLR: PxICLR4 (Bit 4)                          */
#define GPIO_INTCLR_PxICLR4_Msk           (0x10UL)                  /*!< GPIO INTCLR: PxICLR4 (Bitfield-Mask: 0x01)            */
#define GPIO_INTCLR_PxICLR3_Pos           (3UL)                     /*!< GPIO INTCLR: PxICLR3 (Bit 3)                          */
#define GPIO_INTCLR_PxICLR3_Msk           (0x8UL)                   /*!< GPIO INTCLR: PxICLR3 (Bitfield-Mask: 0x01)            */
#define GPIO_INTCLR_PxICLR2_Pos           (2UL)                     /*!< GPIO INTCLR: PxICLR2 (Bit 2)                          */
#define GPIO_INTCLR_PxICLR2_Msk           (0x4UL)                   /*!< GPIO INTCLR: PxICLR2 (Bitfield-Mask: 0x01)            */
#define GPIO_INTCLR_PxICLR1_Pos           (1UL)                     /*!< GPIO INTCLR: PxICLR1 (Bit 1)                          */
#define GPIO_INTCLR_PxICLR1_Msk           (0x2UL)                   /*!< GPIO INTCLR: PxICLR1 (Bitfield-Mask: 0x01)            */
#define GPIO_INTCLR_PxICLR0_Pos           (0UL)                     /*!< GPIO INTCLR: PxICLR0 (Bit 0)                          */
#define GPIO_INTCLR_PxICLR0_Msk           (0x1UL)                   /*!< GPIO INTCLR: PxICLR0 (Bitfield-Mask: 0x01)            */
/* =======================================================  INTTYPCR  ======================================================== */
#define GPIO_INTTYPCR_PxITYPE7_Pos        (7UL)                     /*!< GPIO INTTYPCR: PxITYPE7 (Bit 7)                       */
#define GPIO_INTTYPCR_PxITYPE7_Msk        (0x80UL)                  /*!< GPIO INTTYPCR: PxITYPE7 (Bitfield-Mask: 0x01)         */
#define GPIO_INTTYPCR_PxITYPE6_Pos        (6UL)                     /*!< GPIO INTTYPCR: PxITYPE6 (Bit 6)                       */
#define GPIO_INTTYPCR_PxITYPE6_Msk        (0x40UL)                  /*!< GPIO INTTYPCR: PxITYPE6 (Bitfield-Mask: 0x01)         */
#define GPIO_INTTYPCR_PxITYPE5_Pos        (5UL)                     /*!< GPIO INTTYPCR: PxITYPE5 (Bit 5)                       */
#define GPIO_INTTYPCR_PxITYPE5_Msk        (0x20UL)                  /*!< GPIO INTTYPCR: PxITYPE5 (Bitfield-Mask: 0x01)         */
#define GPIO_INTTYPCR_PxITYPE4_Pos        (4UL)                     /*!< GPIO INTTYPCR: PxITYPE4 (Bit 4)                       */
#define GPIO_INTTYPCR_PxITYPE4_Msk        (0x10UL)                  /*!< GPIO INTTYPCR: PxITYPE4 (Bitfield-Mask: 0x01)         */
#define GPIO_INTTYPCR_PxITYPE3_Pos        (3UL)                     /*!< GPIO INTTYPCR: PxITYPE3 (Bit 3)                       */
#define GPIO_INTTYPCR_PxITYPE3_Msk        (0x8UL)                   /*!< GPIO INTTYPCR: PxITYPE3 (Bitfield-Mask: 0x01)         */
#define GPIO_INTTYPCR_PxITYPE2_Pos        (2UL)                     /*!< GPIO INTTYPCR: PxITYPE2 (Bit 2)                       */
#define GPIO_INTTYPCR_PxITYPE2_Msk        (0x4UL)                   /*!< GPIO INTTYPCR: PxITYPE2 (Bitfield-Mask: 0x01)         */
#define GPIO_INTTYPCR_PxITYPE1_Pos        (1UL)                     /*!< GPIO INTTYPCR: PxITYPE1 (Bit 1)                       */
#define GPIO_INTTYPCR_PxITYPE1_Msk        (0x2UL)                   /*!< GPIO INTTYPCR: PxITYPE1 (Bitfield-Mask: 0x01)         */
#define GPIO_INTTYPCR_PxITYPE0_Pos        (0UL)                     /*!< GPIO INTTYPCR: PxITYPE0 (Bit 0)                       */
#define GPIO_INTTYPCR_PxITYPE0_Msk        (0x1UL)                   /*!< GPIO INTTYPCR: PxITYPE0 (Bitfield-Mask: 0x01)         */
#define GPIO_INTTYPCR_PxITYPE0						 GPIO_INTTYPCR_PxITYPE0_Msk
/* =======================================================  INTPOLCR  ======================================================== */
#define GPIO_INTPOLCR_PxIVAL7_Pos         (7UL)                     /*!< GPIO INTPOLCR: PxIVAL7 (Bit 7)                        */
#define GPIO_INTPOLCR_PxIVAL7_Msk         (0x80UL)                  /*!< GPIO INTPOLCR: PxIVAL7 (Bitfield-Mask: 0x01)          */
#define GPIO_INTPOLCR_PxIVAL6_Pos         (6UL)                     /*!< GPIO INTPOLCR: PxIVAL6 (Bit 6)                        */
#define GPIO_INTPOLCR_PxIVAL6_Msk         (0x40UL)                  /*!< GPIO INTPOLCR: PxIVAL6 (Bitfield-Mask: 0x01)          */
#define GPIO_INTPOLCR_PxIVAL5_Pos         (5UL)                     /*!< GPIO INTPOLCR: PxIVAL5 (Bit 5)                        */
#define GPIO_INTPOLCR_PxIVAL5_Msk         (0x20UL)                  /*!< GPIO INTPOLCR: PxIVAL5 (Bitfield-Mask: 0x01)          */
#define GPIO_INTPOLCR_PxIVAL4_Pos         (4UL)                     /*!< GPIO INTPOLCR: PxIVAL4 (Bit 4)                        */
#define GPIO_INTPOLCR_PxIVAL4_Msk         (0x10UL)                  /*!< GPIO INTPOLCR: PxIVAL4 (Bitfield-Mask: 0x01)          */
#define GPIO_INTPOLCR_PxIVAL3_Pos         (3UL)                     /*!< GPIO INTPOLCR: PxIVAL3 (Bit 3)                        */
#define GPIO_INTPOLCR_PxIVAL3_Msk         (0x8UL)                   /*!< GPIO INTPOLCR: PxIVAL3 (Bitfield-Mask: 0x01)          */
#define GPIO_INTPOLCR_PxIVAL2_Pos         (2UL)                     /*!< GPIO INTPOLCR: PxIVAL2 (Bit 2)                        */
#define GPIO_INTPOLCR_PxIVAL2_Msk         (0x4UL)                   /*!< GPIO INTPOLCR: PxIVAL2 (Bitfield-Mask: 0x01)          */
#define GPIO_INTPOLCR_PxIVAL1_Pos         (1UL)                     /*!< GPIO INTPOLCR: PxIVAL1 (Bit 1)                        */
#define GPIO_INTPOLCR_PxIVAL1_Msk         (0x2UL)                   /*!< GPIO INTPOLCR: PxIVAL1 (Bitfield-Mask: 0x01)          */
#define GPIO_INTPOLCR_PxIVAL0_Pos         (0UL)                     /*!< GPIO INTPOLCR: PxIVAL0 (Bit 0)                        */
#define GPIO_INTPOLCR_PxIVAL0_Msk         (0x1UL)                   /*!< GPIO INTPOLCR: PxIVAL0 (Bitfield-Mask: 0x01)          */
#define GPIO_INTPOLCR_PxIVAL0							 GPIO_INTPOLCR_PxIVAL0_Msk
/* ========================================================  INTANY  ========================================================= */
#define GPIO_INTANY_PxIANY7_Pos           (7UL)                     /*!< GPIO INTANY: PxIANY7 (Bit 7)                          */
#define GPIO_INTANY_PxIANY7_Msk           (0x80UL)                  /*!< GPIO INTANY: PxIANY7 (Bitfield-Mask: 0x01)            */
#define GPIO_INTANY_PxIANY6_Pos           (6UL)                     /*!< GPIO INTANY: PxIANY6 (Bit 6)                          */
#define GPIO_INTANY_PxIANY6_Msk           (0x40UL)                  /*!< GPIO INTANY: PxIANY6 (Bitfield-Mask: 0x01)            */
#define GPIO_INTANY_PxIANY5_Pos           (5UL)                     /*!< GPIO INTANY: PxIANY5 (Bit 5)                          */
#define GPIO_INTANY_PxIANY5_Msk           (0x20UL)                  /*!< GPIO INTANY: PxIANY5 (Bitfield-Mask: 0x01)            */
#define GPIO_INTANY_PxIANY4_Pos           (4UL)                     /*!< GPIO INTANY: PxIANY4 (Bit 4)                          */
#define GPIO_INTANY_PxIANY4_Msk           (0x10UL)                  /*!< GPIO INTANY: PxIANY4 (Bitfield-Mask: 0x01)            */
#define GPIO_INTANY_PxIANY3_Pos           (3UL)                     /*!< GPIO INTANY: PxIANY3 (Bit 3)                          */
#define GPIO_INTANY_PxIANY3_Msk           (0x8UL)                   /*!< GPIO INTANY: PxIANY3 (Bitfield-Mask: 0x01)            */
#define GPIO_INTANY_PxIANY2_Pos           (2UL)                     /*!< GPIO INTANY: PxIANY2 (Bit 2)                          */
#define GPIO_INTANY_PxIANY2_Msk           (0x4UL)                   /*!< GPIO INTANY: PxIANY2 (Bitfield-Mask: 0x01)            */
#define GPIO_INTANY_PxIANY1_Pos           (1UL)                     /*!< GPIO INTANY: PxIANY1 (Bit 1)                          */
#define GPIO_INTANY_PxIANY1_Msk           (0x2UL)                   /*!< GPIO INTANY: PxIANY1 (Bitfield-Mask: 0x01)            */
#define GPIO_INTANY_PxIANY0_Pos           (0UL)                     /*!< GPIO INTANY: PxIANY0 (Bit 0)                          */
#define GPIO_INTANY_PxIANY0_Msk           (0x1UL)                   /*!< GPIO INTANY: PxIANY0 (Bitfield-Mask: 0x01)            */
#define GPIO_INTANY_PxIANY0								 GPIO_INTANY_PxIANY0_Msk
/* =========================================================  ODSET  ========================================================= */
#define GPIO_ODSET_PxODSET7_Pos           (7UL)                     /*!< GPIO ODSET: PxODSET7 (Bit 7)                          */
#define GPIO_ODSET_PxODSET7_Msk           (0x80UL)                  /*!< GPIO ODSET: PxODSET7 (Bitfield-Mask: 0x01)            */
#define GPIO_ODSET_PxODSET6_Pos           (6UL)                     /*!< GPIO ODSET: PxODSET6 (Bit 6)                          */
#define GPIO_ODSET_PxODSET6_Msk           (0x40UL)                  /*!< GPIO ODSET: PxODSET6 (Bitfield-Mask: 0x01)            */
#define GPIO_ODSET_PxODSET5_Pos           (5UL)                     /*!< GPIO ODSET: PxODSET5 (Bit 5)                          */
#define GPIO_ODSET_PxODSET5_Msk           (0x20UL)                  /*!< GPIO ODSET: PxODSET5 (Bitfield-Mask: 0x01)            */
#define GPIO_ODSET_PxODSET4_Pos           (4UL)                     /*!< GPIO ODSET: PxODSET4 (Bit 4)                          */
#define GPIO_ODSET_PxODSET4_Msk           (0x10UL)                  /*!< GPIO ODSET: PxODSET4 (Bitfield-Mask: 0x01)            */
#define GPIO_ODSET_PxODSET3_Pos           (3UL)                     /*!< GPIO ODSET: PxODSET3 (Bit 3)                          */
#define GPIO_ODSET_PxODSET3_Msk           (0x8UL)                   /*!< GPIO ODSET: PxODSET3 (Bitfield-Mask: 0x01)            */
#define GPIO_ODSET_PxODSET2_Pos           (2UL)                     /*!< GPIO ODSET: PxODSET2 (Bit 2)                          */
#define GPIO_ODSET_PxODSET2_Msk           (0x4UL)                   /*!< GPIO ODSET: PxODSET2 (Bitfield-Mask: 0x01)            */
#define GPIO_ODSET_PxODSET1_Pos           (1UL)                     /*!< GPIO ODSET: PxODSET1 (Bit 1)                          */
#define GPIO_ODSET_PxODSET1_Msk           (0x2UL)                   /*!< GPIO ODSET: PxODSET1 (Bitfield-Mask: 0x01)            */
#define GPIO_ODSET_PxODSET0_Pos           (0UL)                     /*!< GPIO ODSET: PxODSET0 (Bit 0)                          */
#define GPIO_ODSET_PxODSET0_Msk           (0x1UL)                   /*!< GPIO ODSET: PxODSET0 (Bitfield-Mask: 0x01)            */
/* =========================================================  ODCLR  ========================================================= */
#define GPIO_ODCLR_PxODCLR7_Pos           (7UL)                     /*!< GPIO ODCLR: PxODCLR7 (Bit 7)                          */
#define GPIO_ODCLR_PxODCLR7_Msk           (0x80UL)                  /*!< GPIO ODCLR: PxODCLR7 (Bitfield-Mask: 0x01)            */
#define GPIO_ODCLR_PxODCLR6_Pos           (6UL)                     /*!< GPIO ODCLR: PxODCLR6 (Bit 6)                          */
#define GPIO_ODCLR_PxODCLR6_Msk           (0x40UL)                  /*!< GPIO ODCLR: PxODCLR6 (Bitfield-Mask: 0x01)            */
#define GPIO_ODCLR_PxODCLR5_Pos           (5UL)                     /*!< GPIO ODCLR: PxODCLR5 (Bit 5)                          */
#define GPIO_ODCLR_PxODCLR5_Msk           (0x20UL)                  /*!< GPIO ODCLR: PxODCLR5 (Bitfield-Mask: 0x01)            */
#define GPIO_ODCLR_PxODCLR4_Pos           (4UL)                     /*!< GPIO ODCLR: PxODCLR4 (Bit 4)                          */
#define GPIO_ODCLR_PxODCLR4_Msk           (0x10UL)                  /*!< GPIO ODCLR: PxODCLR4 (Bitfield-Mask: 0x01)            */
#define GPIO_ODCLR_PxODCLR3_Pos           (3UL)                     /*!< GPIO ODCLR: PxODCLR3 (Bit 3)                          */
#define GPIO_ODCLR_PxODCLR3_Msk           (0x8UL)                   /*!< GPIO ODCLR: PxODCLR3 (Bitfield-Mask: 0x01)            */
#define GPIO_ODCLR_PxODCLR2_Pos           (2UL)                     /*!< GPIO ODCLR: PxODCLR2 (Bit 2)                          */
#define GPIO_ODCLR_PxODCLR2_Msk           (0x4UL)                   /*!< GPIO ODCLR: PxODCLR2 (Bitfield-Mask: 0x01)            */
#define GPIO_ODCLR_PxODCLR1_Pos           (1UL)                     /*!< GPIO ODCLR: PxODCLR1 (Bit 1)                          */
#define GPIO_ODCLR_PxODCLR1_Msk           (0x2UL)                   /*!< GPIO ODCLR: PxODCLR1 (Bitfield-Mask: 0x01)            */
#define GPIO_ODCLR_PxODCLR0_Pos           (0UL)                     /*!< GPIO ODCLR: PxODCLR0 (Bit 0)                          */
#define GPIO_ODCLR_PxODCLR0_Msk           (0x1UL)                   /*!< GPIO ODCLR: PxODCLR0 (Bitfield-Mask: 0x01)            */
/* ========================================================  INDBEN  ========================================================= */
#define GPIO_INDBEN_PxDIDB_Pos            (0UL)                     /*!< GPIO INDBEN: PxDIDB (Bit 0)                           */
#define GPIO_INDBEN_PxDIDB_Msk            (0xffUL)                  /*!< GPIO INDBEN: PxDIDB (Bitfield-Mask: 0xff)             */
#define GPIO_INDBEN_PxDIDB								 GPIO_INDBEN_PxDIDB_Msk
#define GPIO_INDBEN_SYNC_EN_Pos           (8UL)                     /*!< GPIO INDBEN: SYNC_EN (Bit 8)                          */
#define GPIO_INDBEN_SYNC_EN_Msk           (0x100UL)                 /*!< GPIO INDBEN: SYNC_EN (Bitfield-Mask: 0x01)            */
#define GPIO_INDBEN_SYNC_EN								 GPIO_INDBEN_SYNC_EN_Msk

/* ========================================================  DBCLKCR  ======================================================== */
#define GPIO_DBCLKCR_DBCLK_DIV_Pos        (0UL)                     /*!< GPIO DBCLKCR: DBCLK_DIV (Bit 0)                       */
#define GPIO_DBCLKCR_DBCLK_DIV_Msk        (0xfUL)                   /*!< GPIO DBCLKCR: DBCLK_DIV (Bitfield-Mask: 0x0f)         */
#define GPIO_DBCLKCR_DBCLK_DIV						 GPIO_DBCLKCR_DBCLK_DIV_Msk
#define GPIO_DBCLKCR_DBCLKEN_Pos          (4UL)                     /*!< GPIO DBCLKCR: DBCLKEN (Bit 4)                         */
#define GPIO_DBCLKCR_DBCLKEN_Msk          (0x10UL)                  /*!< GPIO DBCLKCR: DBCLKEN (Bitfield-Mask: 0x01)           */
#define GPIO_DBCLKCR_DBCLKEN							 GPIO_DBCLKCR_DBCLKEN_Msk
/* =========================================================  PUPDR  ========================================================= */
#define GPIO_PUPDR_PxPUPD7_Pos            (14UL)                    /*!< GPIO PUPDR: PxPUPD7 (Bit 14)                          */
#define GPIO_PUPDR_PxPUPD7_Msk            (0xc000UL)                /*!< GPIO PUPDR: PxPUPD7 (Bitfield-Mask: 0x03)             */
#define GPIO_PUPDR_PxPUPD6_Pos            (12UL)                    /*!< GPIO PUPDR: PxPUPD6 (Bit 12)                          */
#define GPIO_PUPDR_PxPUPD6_Msk            (0x3000UL)                /*!< GPIO PUPDR: PxPUPD6 (Bitfield-Mask: 0x03)             */
#define GPIO_PUPDR_PxPUPD5_Pos            (10UL)                    /*!< GPIO PUPDR: PxPUPD5 (Bit 10)                          */
#define GPIO_PUPDR_PxPUPD5_Msk            (0xc00UL)                 /*!< GPIO PUPDR: PxPUPD5 (Bitfield-Mask: 0x03)             */
#define GPIO_PUPDR_PxPUPD4_Pos            (8UL)                     /*!< GPIO PUPDR: PxPUPD4 (Bit 8)                           */
#define GPIO_PUPDR_PxPUPD4_Msk            (0x300UL)                 /*!< GPIO PUPDR: PxPUPD4 (Bitfield-Mask: 0x03)             */
#define GPIO_PUPDR_PxPUPD3_Pos            (6UL)                     /*!< GPIO PUPDR: PxPUPD3 (Bit 6)                           */
#define GPIO_PUPDR_PxPUPD3_Msk            (0xc0UL)                  /*!< GPIO PUPDR: PxPUPD3 (Bitfield-Mask: 0x03)             */
#define GPIO_PUPDR_PxPUPD2_Pos            (4UL)                     /*!< GPIO PUPDR: PxPUPD2 (Bit 4)                           */
#define GPIO_PUPDR_PxPUPD2_Msk            (0x30UL)                  /*!< GPIO PUPDR: PxPUPD2 (Bitfield-Mask: 0x03)             */
#define GPIO_PUPDR_PxPUPD1_Pos            (2UL)                     /*!< GPIO PUPDR: PxPUPD1 (Bit 2)                           */
#define GPIO_PUPDR_PxPUPD1_Msk            (0xcUL)                   /*!< GPIO PUPDR: PxPUPD1 (Bitfield-Mask: 0x03)             */
#define GPIO_PUPDR_PxPUPD0_Pos            (0UL)                     /*!< GPIO PUPDR: PxPUPD0 (Bit 0)                           */
#define GPIO_PUPDR_PxPUPD0_Msk            (0x3UL)                   /*!< GPIO PUPDR: PxPUPD0 (Bitfield-Mask: 0x03)             */
#define GPIO_PUPDR_PxPUPD0								 GPIO_PUPDR_PxPUPD0_Msk
/* ========================================================  SLEWCR  ========================================================= */
#define GPIO_SLEWCR_PxSR7_Pos             (7UL)                     /*!< GPIO SLEWCR: PxSR7 (Bit 7)                            */
#define GPIO_SLEWCR_PxSR7_Msk             (0x80UL)                  /*!< GPIO SLEWCR: PxSR7 (Bitfield-Mask: 0x01)              */
#define GPIO_SLEWCR_PxSR6_Pos             (6UL)                     /*!< GPIO SLEWCR: PxSR6 (Bit 6)                            */
#define GPIO_SLEWCR_PxSR6_Msk             (0x40UL)                  /*!< GPIO SLEWCR: PxSR6 (Bitfield-Mask: 0x01)              */
#define GPIO_SLEWCR_PxSR5_Pos             (5UL)                     /*!< GPIO SLEWCR: PxSR5 (Bit 5)                            */
#define GPIO_SLEWCR_PxSR5_Msk             (0x20UL)                  /*!< GPIO SLEWCR: PxSR5 (Bitfield-Mask: 0x01)              */
#define GPIO_SLEWCR_PxSR4_Pos             (4UL)                     /*!< GPIO SLEWCR: PxSR4 (Bit 4)                            */
#define GPIO_SLEWCR_PxSR4_Msk             (0x10UL)                  /*!< GPIO SLEWCR: PxSR4 (Bitfield-Mask: 0x01)              */
#define GPIO_SLEWCR_PxSR3_Pos             (3UL)                     /*!< GPIO SLEWCR: PxSR3 (Bit 3)                            */
#define GPIO_SLEWCR_PxSR3_Msk             (0x8UL)                   /*!< GPIO SLEWCR: PxSR3 (Bitfield-Mask: 0x01)              */
#define GPIO_SLEWCR_PxSR2_Pos             (2UL)                     /*!< GPIO SLEWCR: PxSR2 (Bit 2)                            */
#define GPIO_SLEWCR_PxSR2_Msk             (0x4UL)                   /*!< GPIO SLEWCR: PxSR2 (Bitfield-Mask: 0x01)              */
#define GPIO_SLEWCR_PxSR1_Pos             (1UL)                     /*!< GPIO SLEWCR: PxSR1 (Bit 1)                            */
#define GPIO_SLEWCR_PxSR1_Msk             (0x2UL)                   /*!< GPIO SLEWCR: PxSR1 (Bitfield-Mask: 0x01)              */
#define GPIO_SLEWCR_PASR0_Pos             (0UL)                     /*!< GPIO SLEWCR: PASR0 (Bit 0)                            */
#define GPIO_SLEWCR_PASR0_Msk             (0x1UL)                   /*!< GPIO SLEWCR: PASR0 (Bitfield-Mask: 0x01)              */
#define GPIO_SLEWCR_PASR0									 GPIO_SLEWCR_PASR0_Msk
/* =========================================================  DRVCR  ========================================================= */
#define GPIO_DRVCR_PxDRV7_Pos             (7UL)                     /*!< GPIO DRVCR: PxDRV7 (Bit 7)                            */
#define GPIO_DRVCR_PxDRV7_Msk             (0x80UL)                  /*!< GPIO DRVCR: PxDRV7 (Bitfield-Mask: 0x01)              */
#define GPIO_DRVCR_PxDRV6_Pos             (6UL)                     /*!< GPIO DRVCR: PxDRV6 (Bit 6)                            */
#define GPIO_DRVCR_PxDRV6_Msk             (0x40UL)                  /*!< GPIO DRVCR: PxDRV6 (Bitfield-Mask: 0x01)              */
#define GPIO_DRVCR_PxDRV5_Pos             (5UL)                     /*!< GPIO DRVCR: PxDRV5 (Bit 5)                            */
#define GPIO_DRVCR_PxDRV5_Msk             (0x20UL)                  /*!< GPIO DRVCR: PxDRV5 (Bitfield-Mask: 0x01)              */
#define GPIO_DRVCR_PxDRV4_Pos             (4UL)                     /*!< GPIO DRVCR: PxDRV4 (Bit 4)                            */
#define GPIO_DRVCR_PxDRV4_Msk             (0x10UL)                  /*!< GPIO DRVCR: PxDRV4 (Bitfield-Mask: 0x01)              */
#define GPIO_DRVCR_PxDRV3_Pos             (3UL)                     /*!< GPIO DRVCR: PxDRV3 (Bit 3)                            */
#define GPIO_DRVCR_PxDRV3_Msk             (0x8UL)                   /*!< GPIO DRVCR: PxDRV3 (Bitfield-Mask: 0x01)              */
#define GPIO_DRVCR_PxDRV2_Pos             (2UL)                     /*!< GPIO DRVCR: PxDRV2 (Bit 2)                            */
#define GPIO_DRVCR_PxDRV2_Msk             (0x4UL)                   /*!< GPIO DRVCR: PxDRV2 (Bitfield-Mask: 0x01)              */
#define GPIO_DRVCR_PxDRV1_Pos             (1UL)                     /*!< GPIO DRVCR: PxDRV1 (Bit 1)                            */
#define GPIO_DRVCR_PxDRV1_Msk             (0x2UL)                   /*!< GPIO DRVCR: PxDRV1 (Bitfield-Mask: 0x01)              */
#define GPIO_DRVCR_PxDRV0_Pos             (0UL)                     /*!< GPIO DRVCR: PxDRV0 (Bit 0)                            */
#define GPIO_DRVCR_PxDRV0_Msk             (0x1UL)                   /*!< GPIO DRVCR: PxDRV0 (Bitfield-Mask: 0x01)              */
#define GPIO_DRVCR_PxDRV0									 GPIO_DRVCR_PxDRV0_Msk
/* ==========================================================  AFR  ========================================================== */
#define GPIO_AFR_PxAFR7_Pos               (28UL)                    /*!< GPIO AFR: PxAFR7 (Bit 28)                             */
#define GPIO_AFR_PxAFR7_Msk               (0xf000000UL)             /*!< GPIO AFR: PxAFR7 (Bitfield-Mask: 0x0f)                */
#define GPIO_AFR_PxAFR6_Pos               (24UL)                    /*!< GPIO AFR: PxAFR6 (Bit 24)                             */
#define GPIO_AFR_PxAFR6_Msk               (0xf000000UL)             /*!< GPIO AFR: PxAFR6 (Bitfield-Mask: 0x0f)                */
#define GPIO_AFR_PxAFR5_Pos               (20UL)                    /*!< GPIO AFR: PxAFR5 (Bit 20)                             */
#define GPIO_AFR_PxAFR5_Msk               (0xf00000UL)              /*!< GPIO AFR: PxAFR5 (Bitfield-Mask: 0x0f)                */
#define GPIO_AFR_PxAFR4_Pos               (16UL)                    /*!< GPIO AFR: PxAFR4 (Bit 16)                             */
#define GPIO_AFR_PxAFR4_Msk               (0xf0000UL)               /*!< GPIO AFR: PxAFR4 (Bitfield-Mask: 0x0f)                */
#define GPIO_AFR_PxAFR3_Pos               (12UL)                    /*!< GPIO AFR: PxAFR3 (Bit 12)                             */
#define GPIO_AFR_PxAFR3_Msk               (0xf000UL)                /*!< GPIO AFR: PxAFR3 (Bitfield-Mask: 0x0f)                */
#define GPIO_AFR_PxAFR2_Pos               (8UL)                     /*!< GPIO AFR: PxAFR2 (Bit 8)                              */
#define GPIO_AFR_PxAFR2_Msk               (0xf00UL)                 /*!< GPIO AFR: PxAFR2 (Bitfield-Mask: 0x0f)                */
#define GPIO_AFR_PxAFR1_Pos               (4UL)                     /*!< GPIO AFR: PxAFR1 (Bit 4)                              */
#define GPIO_AFR_PxAFR1_Msk               (0xf0UL)                  /*!< GPIO AFR: PxAFR1 (Bitfield-Mask: 0x0f)                */
#define GPIO_AFR_PxAFR0_Pos               (0UL)                     /*!< GPIO AFR: PxAFR0 (Bit 0)                              */
#define GPIO_AFR_PxAFR0_Msk               (0x0fUL)                  /*!< GPIO AFR: PxAFR0 (Bitfield-Mask: 0x0f)                */
#define GPIO_AFR_PxAFR0										 GPIO_AFR_PxAFR0_Msk

/* =========================================================================================================================== */
/* ================                                          SYSCON                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  CFGR0  ========================================================= */
#define SYSCON_CFGR0_LOCKUPEN_Pos         (0UL)                     /*!< SYSCON CFGR0: LOCKUPEN (Bit 0)                        */
#define SYSCON_CFGR0_LOCKUPEN_Msk         (0x1UL)                   /*!< SYSCON CFGR0: LOCKUPEN (Bitfield-Mask: 0x01)          */
#define SYSCON_CFGR0_LOCKUPEN							SYSCON_CFGR0_LOCKUPEN_Msk
#define SYSCON_CFGR0_DBGDLSP_DIS_Pos      (1UL)                     /*!< SYSCON CFGR0: DBGDLSP_DIS (Bit 1)                     */
#define SYSCON_CFGR0_DBGDLSP_DIS_Msk      (0x2UL)                   /*!< SYSCON CFGR0: DBGDLSP_DIS (Bitfield-Mask: 0x01)       */
#define SYSCON_CFGR0_DBGDLSP_DIS					SYSCON_CFGR0_DBGDLSP_DIS_Msk
#define SYSCON_CFGR0_KEY_Pos              (16UL)                    /*!< SYSCON CFGR0: KEY (Bit 16)                            */
#define SYSCON_CFGR0_KEY_Msk              (0xffff0000UL)            /*!< SYSCON CFGR0: KEY (Bitfield-Mask: 0xffff)             */
#define SYSCON_CFGR0_KEY									 SYSCON_CFGR0_KEY_Msk
/* =======================================================  PORTINTCR  ======================================================= */
#define SYSCON_PORTINTCR_PADINTSEL_Pos    (0UL)                     /*!< SYSCON PORTINTCR: PADINTSEL (Bit 0)                   */
#define SYSCON_PORTINTCR_PADINTSEL_Msk    (0x1UL)                   /*!< SYSCON PORTINTCR: PADINTSEL (Bitfield-Mask: 0x01)     */
#define SYSCON_PORTINTCR_PADINTSEL				SYSCON_PORTINTCR_PADINTSEL_Msk
#define SYSCON_PORTINTCR_PADDLSPCON_Pos   (1UL)                     /*!< SYSCON PORTINTCR: PADDLSPCON (Bit 1)                  */
#define SYSCON_PORTINTCR_PADDLSPCON_Msk   (0x2UL)                   /*!< SYSCON PORTINTCR: PADDLSPCON (Bitfield-Mask: 0x01)    */
#define SYSCON_PORTINTCR_PADDLSPCON				SYSCON_PORTINTCR_PADDLSPCON_Msk
#define SYSCON_PORTINTCR_KEY_Pos          (16UL)                    /*!< SYSCON PORTINTCR: KEY (Bit 16)                        */
#define SYSCON_PORTINTCR_KEY_Msk          (0xffff0000UL)            /*!< SYSCON PORTINTCR: KEY (Bitfield-Mask: 0xffff)         */
#define SYSCON_PORTINTCR_KEY							SYSCON_PORTINTCR_KEY_Msk
/* ========================================================  PORTCR  ========================================================= */
#define SYSCON_PORTCR_SPINCS_SEL_Pos      (0UL)                     /*!< SYSCON PORTCR: SPINCS_SEL (Bit 0)                     */
#define SYSCON_PORTCR_SPINCS_SEL_Msk      (0xfUL)                   /*!< SYSCON PORTCR: SPINCS_SEL (Bitfield-Mask: 0x0f)       */
#define SYSCON_PORTCR_SPINCS_SEL					SYSCON_PORTCR_SPINCS_SEL_Msk
#define SYSCON_PORTCR_TIM10_GATE_SEL_Pos  (4UL)                     /*!< SYSCON PORTCR: TIM10_GATE_SEL (Bit 4)                 */
#define SYSCON_PORTCR_TIM10_GATE_SEL_Msk  (0x30UL)                  /*!< SYSCON PORTCR: TIM10_GATE_SEL (Bitfield-Mask: 0x03)   */
#define SYSCON_PORTCR_TIM10_GATE_SEL			SYSCON_PORTCR_TIM10_GATE_SEL_Msk
#define SYSCON_PORTCR_TIM11_GATE_SEL_Pos  (6UL)                     /*!< SYSCON PORTCR: TIM11_GATE_SEL (Bit 6)                 */
#define SYSCON_PORTCR_TIM11_GATE_SEL_Msk  (0xc0UL)                  /*!< SYSCON PORTCR: TIM11_GATE_SEL (Bitfield-Mask: 0x03)   */
#define SYSCON_PORTCR_TIM11_GATE_SEL			SYSCON_PORTCR_TIM11_GATE_SEL_Msk
#define SYSCON_PORTCR_LPTIM_GATE_SEL_Pos  (8UL)                     /*!< SYSCON PORTCR: LPTIM GATE_SEL (Bit 8)                       */
#define SYSCON_PORTCR_LPTIM_GATE_SEL_Msk  (0x300UL)                 /*!< SYSCON PORTCR: LPTIM_GATE_SEL (Bitfield-Mask: 0x03)         */
#define SYSCON_PORTCR_LPTIM_GATE_SEL			SYSCON_PORTCR_LPTIM_GATE_SEL_Msk
/* =========================================================  PCACR  ========================================================= */
#define SYSCON_PCACR_PCA_CAP0_SEL_Pos     (0UL)                     /*!< SYSCON PCACR: PCA_CAP0_SEL (Bit 0)                    */
#define SYSCON_PCACR_PCA_CAP0_SEL_Msk     (0x3UL)                   /*!< SYSCON PCACR: PCA_CAP0_SEL (Bitfield-Mask: 0x03)      */
#define SYSCON_PCACR_PCA_CAP0_SEL					SYSCON_PCACR_PCA_CAP0_SEL_Msk
#define SYSCON_PCACR_PCA_CAP1_SEL_Pos     (2UL)                     /*!< SYSCON PCACR: PCA_CAP1_SEL (Bit 2)                    */
#define SYSCON_PCACR_PCA_CAP1_SEL_Msk     (0xcUL)                   /*!< SYSCON PCACR: PCA_CAP1_SEL (Bitfield-Mask: 0x03)      */
#define SYSCON_PCACR_PCA_CAP1_SEL					SYSCON_PCACR_PCA_CAP1_SEL_Msk
#define SYSCON_PCACR_PCA_CAP2_SEL_Pos     (4UL)                     /*!< SYSCON PCACR: PCA_CAP2_SEL (Bit 4)                    */
#define SYSCON_PCACR_PCA_CAP2_SEL_Msk     (0x30UL)                  /*!< SYSCON PCACR: PCA_CAP2_SEL (Bitfield-Mask: 0x03)      */
#define SYSCON_PCACR_PCA_CAP2_SEL					SYSCON_PCACR_PCA_CAP2_SEL_Msk
#define SYSCON_PCACR_PCA_CAP3_SEL_Pos     (6UL)                     /*!< SYSCON PCACR: PCA_CAP3_SEL (Bit 6)                    */
#define SYSCON_PCACR_PCA_CAP3_SEL_Msk     (0xc0UL)                  /*!< SYSCON PCACR: PCA_CAP3_SEL (Bitfield-Mask: 0x03)      */
#define SYSCON_PCACR_PCA_CAP3_SEL					SYSCON_PCACR_PCA_CAP3_SEL_Msk
#define SYSCON_PCACR_PCA_CAP4_SEL_Pos     (8UL)                     /*!< SYSCON PCACR: PCA_CAP4_SEL (Bit 8)                    */
#define SYSCON_PCACR_PCA_CAP4_SEL_Msk     (0x300UL)                 /*!< SYSCON PCACR: PCA_CAP4_SEL (Bitfield-Mask: 0x03)      */
#define SYSCON_PCACR_PCA_CAP4_SEL					SYSCON_PCACR_PCA_CAP4_SEL_Msk
/* ========================================================  TIM1CR  ========================================================= */
#define SYSCON_TIM1CR_TIM1CH1IN_SEL_Pos   (0UL)                     /*!< SYSCON TIM1CR: TIM1CH1IN_SEL (Bit 0)                  */
#define SYSCON_TIM1CR_TIM1CH1IN_SEL_Msk   (0x7UL)                   /*!< SYSCON TIM1CR: TIM1CH1IN_SEL (Bitfield-Mask: 0x07)    */
#define SYSCON_TIM1CR_TIM1CH1IN_SEL				SYSCON_TIM1CR_TIM1CH1IN_SEL_Msk
#define SYSCON_TIM1CR_TIM1CH2IN_SEL_Pos   (4UL)                     /*!< SYSCON TIM1CR: TIM1CH2IN_SEL (Bit 4)                  */
#define SYSCON_TIM1CR_TIM1CH2IN_SEL_Msk   (0x70UL)                  /*!< SYSCON TIM1CR: TIM1CH2IN_SEL (Bitfield-Mask: 0x07)    */
#define SYSCON_TIM1CR_TIM1CH2IN_SEL				SYSCON_TIM1CR_TIM1CH2IN_SEL_Msk
#define SYSCON_TIM1CR_TIM1CH3IN_SEL_Pos   (8UL)                     /*!< SYSCON TIM1CR: TIM1CH3IN_SEL (Bit 8)                  */
#define SYSCON_TIM1CR_TIM1CH3IN_SEL_Msk   (0x700UL)                 /*!< SYSCON TIM1CR: TIM1CH3IN_SEL (Bitfield-Mask: 0x07)    */
#define SYSCON_TIM1CR_TIM1CH3IN_SEL				SYSCON_TIM1CR_TIM1CH3IN_SEL_Msk
#define SYSCON_TIM1CR_TIM1CH4IN_SEL_Pos   (12UL)                    /*!< SYSCON TIM1CR: TIM1CH4IN_SEL (Bit 12)                 */
#define SYSCON_TIM1CR_TIM1CH4IN_SEL_Msk   (0x7000UL)                /*!< SYSCON TIM1CR: TIM1CH4IN_SEL (Bitfield-Mask: 0x07)    */
#define SYSCON_TIM1CR_TIM1CH4IN_SEL				SYSCON_TIM1CR_TIM1CH4IN_SEL_Msk
#define SYSCON_TIM1CR_TIM1ETR_SEL_Pos     (16UL)                    /*!< SYSCON TIM1CR: TIM1ETR_SEL (Bit 16)                   */
#define SYSCON_TIM1CR_TIM1ETR_SEL_Msk     (0xf0000UL)               /*!< SYSCON TIM1CR: TIM1ETR_SEL (Bitfield-Mask: 0x0f)      */
#define SYSCON_TIM1CR_TIM1ETR_SEL					SYSCON_TIM1CR_TIM1ETR_SEL_Msk
#define SYSCON_TIM1CR_TIM1BRKOUTCFG_Pos   (20UL)                    /*!< SYSCON TIM1CR: TIM1BRKOUTCFG (Bit 20)                 */
#define SYSCON_TIM1CR_TIM1BRKOUTCFG_Msk   (0x100000UL)              /*!< SYSCON TIM1CR: TIM1BRKOUTCFG (Bitfield-Mask: 0x01)    */
#define SYSCON_TIM1CR_TIM1BRKOUTCFG				SYSCON_TIM1CR_TIM1BRKOUTCFG_Msk
#define SYSCON_TIM1CR_DSLPBRKEN_Pos       (21UL)                    /*!< SYSCON TIM1CR: DSLPBRKEN (Bit 21)                     */
#define SYSCON_TIM1CR_DSLPBRKEN_Msk       (0x200000UL)              /*!< SYSCON TIM1CR: DSLPBRKEN (Bitfield-Mask: 0x01)        */
#define SYSCON_TIM1CR_DSLPBRKEN						SYSCON_TIM1CR_DSLPBRKEN_Msk
#define SYSCON_TIM1CR_CLKFAILBRKEN_Pos    (22UL)                    /*!< SYSCON TIM1CR: CLKFAILBRKEN (Bit 22)                  */
#define SYSCON_TIM1CR_CLKFAILBRKEN_Msk    (0x400000UL)              /*!< SYSCON TIM1CR: CLKFAILBRKEN (Bitfield-Mask: 0x01)     */
#define SYSCON_TIM1CR_CLKFAILBRKEN				SYSCON_TIM1CR_CLKFAILBRKEN_Msk
/* ========================================================  TIM2CR  ========================================================= */
#define SYSCON_TIM2CR_TIM2CH1IN_SEL_Pos 	(0UL)                     /*!< SYSCON TIM2CR: TIM2CH1IN_SEL (Bit 0)               */
#define SYSCON_TIM2CR_TIM2CH1IN_SEL_Msk 	(0x7UL)                   /*!< SYSCON TIM2CR: TIM2CH1IN_SEL (Bitfield-Mask: 0x07) */
#define SYSCON_TIM2CR_TIM2CH1IN_SEL				SYSCON_TIM2CR_TIM2CH1IN_SEL_Msk
#define SYSCON_TIM2CR_TIM2CH2IN_SEL_Pos   (4UL)                     /*!< SYSCON TIM2CR: TIM2CH2IN_SEL (Bit 4)                  */
#define SYSCON_TIM2CR_TIM2CH2IN_SEL_Msk   (0x70UL)                  /*!< SYSCON TIM2CR: TIM2CH2IN_SEL (Bitfield-Mask: 0x07)    */
#define SYSCON_TIM2CR_TIM2CH2IN_SEL				SYSCON_TIM2CR_TIM2CH2IN_SEL_Msk
#define SYSCON_TIM2CR_TIM2CH3IN_SEL_Pos   (8UL)                     /*!< SYSCON TIM2CR: TIM2CH3IN_SEL (Bit 8)                  */
#define SYSCON_TIM2CR_TIM2CH3IN_SEL_Msk   (0x700UL)                 /*!< SYSCON TIM2CR: TIM2CH3IN_SEL (Bitfield-Mask: 0x07)    */
#define SYSCON_TIM2CR_TIM2CH3IN_SEL				SYSCON_TIM2CR_TIM2CH3IN_SEL_Msk
#define SYSCON_TIM2CR_TIM2CH4IN_SEL_Pos   (12UL)                    /*!< SYSCON TIM2CR: TIM2CH4IN_SEL (Bit 12)                 */
#define SYSCON_TIM2CR_TIM2CH4IN_SEL_Msk   (0x7000UL)                /*!< SYSCON TIM2CR: TIM2CH4IN_SEL (Bitfield-Mask: 0x07)    */
#define SYSCON_TIM2CR_TIM2CH4IN_SEL				SYSCON_TIM2CR_TIM2CH4IN_SEL_Msk
#define SYSCON_TIM2CR_TIM2ETR_SEL_Pos     (16UL)                    /*!< SYSCON TIM2CR: TIM2ETR_SEL (Bit 16)                   */
#define SYSCON_TIM2CR_TIM2ETR_SEL_Msk     (0xf0000UL)               /*!< SYSCON TIM2CR: TIM2ETR_SEL (Bitfield-Mask: 0x0f)      */
#define SYSCON_TIM2CR_TIM2ETR_SEL					SYSCON_TIM2CR_TIM2ETR_SEL_Msk
/* ========================================================  UNLOCK  ========================================================= */
#define SYSCON_UNLOCK_UNLOCK_Pos          (0UL)                     /*!< SYSCON UNLOCK: UNLOCK (Bit 0)                         */
#define SYSCON_UNLOCK_UNLOCK_Msk          (0x1UL)                   /*!< SYSCON UNLOCK: UNLOCK (Bitfield-Mask: 0x01)           */
#define SYSCON_UNLOCK_UNLOCK							 SYSCON_UNLOCK_UNLOCK_Msk
#define SYSCON_UNLOCK_KEY_Pos             (1UL)                     /*!< SYSCON UNLOCK: KEY (Bit 1)                            */
#define SYSCON_UNLOCK_KEY_Msk             (0xfffffffeUL)            /*!< SYSCON UNLOCK: KEY (Bitfield-Mask: 0x7fffffff)        */
#define SYSCON_UNLOCK_KEY									 SYSCON_UNLOCK_KEY_Msk

/* =========================================================================================================================== */
/* ================                                            RCC                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  HCLKDIV  ======================================================== */
#define RCC_HCLKDIV_AHBCKDIV_Pos          (0UL)                     /*!< RCC HCLKDIV: AHBCKDIV (Bit 0)                         */
#define RCC_HCLKDIV_AHBCKDIV_Msk          (0xffUL)                  /*!< RCC HCLKDIV: AHBCKDIV (Bitfield-Mask: 0xff)           */
#define RCC_HCLKDIV_AHBCKDIV							 RCC_HCLKDIV_AHBCKDIV_Msk
#define RCC_HCLKDIV_AHBCKDIV_1						(0x00000000)
/* ========================================================  PCLKDIV  ======================================================== */
#define RCC_PCLKDIV_APBCKDIV_Pos          (0UL)                     /*!< RCC PCLKDIV: APBCKDIV (Bit 0)                         */
#define RCC_PCLKDIV_APBCKDIV_Msk          (0xffUL)                  /*!< RCC PCLKDIV: APBCKDIV (Bitfield-Mask: 0xff)           */
#define RCC_PCLKDIV_APBCKDIV							 RCC_PCLKDIV_APBCKDIV_Msk
#define RCC_PCLKDIV_APBCKDIV_1						(0x00000000)
/* ========================================================  HCLKEN  ========================================================= */
#define RCC_HCLKEN_GPIOACKEN_Pos          (0UL)                     /*!< RCC HCLKEN: GPIOACKEN (Bit 0)                         */
#define RCC_HCLKEN_GPIOACKEN_Msk          (0x1UL)                   /*!< RCC HCLKEN: GPIOACKEN (Bitfield-Mask: 0x01)           */
#define RCC_HCLKEN_GPIOACKEN							 RCC_HCLKEN_GPIOACKEN_Msk
#define RCC_HCLKEN_GPIOBCKEN_Pos          (1UL)                     /*!< RCC HCLKEN: GPIOBCKEN (Bit 1)                         */
#define RCC_HCLKEN_GPIOBCKEN_Msk          (0x2UL)                   /*!< RCC HCLKEN: GPIOBCKEN (Bitfield-Mask: 0x01)           */
#define RCC_HCLKEN_GPIOBCKEN							 RCC_HCLKEN_GPIOBCKEN_Msk		
#define RCC_HCLKEN_GPIOCCKEN_Pos          (2UL)                     /*!< RCC HCLKEN: GPIOCCKEN (Bit 2)                         */
#define RCC_HCLKEN_GPIOCCKEN_Msk          (0x4UL)                   /*!< RCC HCLKEN: GPIOCCKEN (Bitfield-Mask: 0x01)           */
#define RCC_HCLKEN_GPIOCCKEN							 RCC_HCLKEN_GPIOCCKEN_Msk
#define RCC_HCLKEN_GPIODCKEN_Pos          (3UL)                     /*!< RCC HCLKEN: GPIODCKEN (Bit 3)                         */
#define RCC_HCLKEN_GPIODCKEN_Msk          (0x8UL)                   /*!< RCC HCLKEN: GPIODCKEN (Bitfield-Mask: 0x01)           */
#define RCC_HCLKEN_GPIODCKEN							 RCC_HCLKEN_GPIODCKEN_Msk
#define RCC_HCLKEN_CRCCKEN_Pos            (4UL)                     /*!< RCC HCLKEN: CRCCKEN (Bit 4)                           */
#define RCC_HCLKEN_CRCCKEN_Msk            (0x10UL)                  /*!< RCC HCLKEN: CRCCKEN (Bitfield-Mask: 0x01)             */
#define RCC_HCLKEN_CRCCKEN								 RCC_HCLKEN_CRCCKEN_Msk
#define RCC_HCLKEN_FLASHCKEN_Pos          (8UL)                     /*!< RCC HCLKEN: FLASHCKEN (Bit 8)                         */
#define RCC_HCLKEN_FLASHCKEN_Msk          (0x100UL)                 /*!< RCC HCLKEN: FLASHCKEN (Bitfield-Mask: 0x01)           */
#define RCC_HCLKEN_FLASHCKEN							 RCC_HCLKEN_FLASHCKEN_Msk
/* ========================================================  PCLKEN  ========================================================= */
#define RCC_PCLKEN_UART0CKEN_Pos          (0UL)                     /*!< RCC PCLKEN: UART0CKEN (Bit 0)                         */
#define RCC_PCLKEN_UART0CKEN_Msk          (0x1UL)                   /*!< RCC PCLKEN: UART0CKEN (Bitfield-Mask: 0x01)           */
#define RCC_PCLKEN_UART0CKEN							 RCC_PCLKEN_UART0CKEN_Msk
#define RCC_PCLKEN_UART1CKEN_Pos          (1UL)                     /*!< RCC PCLKEN: UART1CKEN (Bit 1)                         */
#define RCC_PCLKEN_UART1CKEN_Msk          (0x2UL)                   /*!< RCC PCLKEN: UART1CKEN (Bitfield-Mask: 0x01)           */
#define RCC_PCLKEN_UART1CKEN							 RCC_PCLKEN_UART1CKEN_Msk
#define RCC_PCLKEN_I2CCKEN_Pos            (2UL)                     /*!< RCC PCLKEN: I2CCKEN (Bit 2)                           */
#define RCC_PCLKEN_I2CCKEN_Msk            (0x4UL)                   /*!< RCC PCLKEN: I2CCKEN (Bitfield-Mask: 0x01)             */
#define RCC_PCLKEN_I2CCKEN								 RCC_PCLKEN_I2CCKEN_Msk
#define RCC_PCLKEN_LPUARTCKEN_Pos         (3UL)                     /*!< RCC PCLKEN: LPUARTCKEN (Bit 3)                        */
#define RCC_PCLKEN_LPUARTCKEN_Msk         (0x8UL)                   /*!< RCC PCLKEN: LPUARTCKEN (Bitfield-Mask: 0x01)          */
#define RCC_PCLKEN_LPUARTCKEN							 RCC_PCLKEN_LPUARTCKEN_Msk
#define RCC_PCLKEN_SPICKEN_Pos            (4UL)                     /*!< RCC PCLKEN: SPICKEN (Bit 4)                           */
#define RCC_PCLKEN_SPICKEN_Msk            (0x10UL)                  /*!< RCC PCLKEN: SPICKEN (Bitfield-Mask: 0x01)             */
#define RCC_PCLKEN_SPICKEN								 RCC_PCLKEN_SPICKEN_Msk
#define RCC_PCLKEN_LPTIMCKEN_Pos          (5UL)                     /*!< RCC PCLKEN: LPTIMCKEN (Bit 5)                         */
#define RCC_PCLKEN_LPTIMCKEN_Msk          (0x20UL)                  /*!< RCC PCLKEN: LPTIMCKEN (Bitfield-Mask: 0x01)           */
#define RCC_PCLKEN_LPTIMCKEN							 RCC_PCLKEN_LPTIMCKEN_Msk
#define RCC_PCLKEN_BASETIMCKEN_Pos        (6UL)                     /*!< RCC PCLKEN: BASETIMCKEN (Bit 6)                       */
#define RCC_PCLKEN_BASETIMCKEN_Msk        (0x40UL)                  /*!< RCC PCLKEN: BASETIMCKEN (Bitfield-Mask: 0x01)         */
#define RCC_PCLKEN_BASETIMCKEN						 RCC_PCLKEN_BASETIMCKEN_Msk
#define RCC_PCLKEN_SYSCONCKEN_Pos         (7UL)                     /*!< RCC PCLKEN: SYSCONCKEN (Bit 7)                        */
#define RCC_PCLKEN_SYSCONCKEN_Msk         (0x80UL)                  /*!< RCC PCLKEN: SYSCONCKEN (Bitfield-Mask: 0x01)          */
#define RCC_PCLKEN_SYSCONCKEN							 RCC_PCLKEN_SYSCONCKEN_Msk
#define RCC_PCLKEN_PCACKEN_Pos            (8UL)                     /*!< RCC PCLKEN: PCACKEN (Bit 8)                           */
#define RCC_PCLKEN_PCACKEN_Msk            (0x100UL)                 /*!< RCC PCLKEN: PCACKEN (Bitfield-Mask: 0x01)             */
#define RCC_PCLKEN_PCACKEN								 RCC_PCLKEN_PCACKEN_Msk
#define RCC_PCLKEN_OWIRECKEN_Pos          (9UL)                     /*!< RCC PCLKEN: OWIRECKEN (Bit 9)                         */
#define RCC_PCLKEN_OWIRECKEN_Msk          (0x200UL)                 /*!< RCC PCLKEN: OWIRECKEN (Bitfield-Mask: 0x01)           */
#define RCC_PCLKEN_OWIRECKEN							 RCC_PCLKEN_OWIRECKEN_Msk
#define RCC_PCLKEN_TIM1CKEN_Pos           (10UL)                    /*!< RCC PCLKEN: TIM1CKEN (Bit 10)                         */
#define RCC_PCLKEN_TIM1CKEN_Msk           (0x400UL)                 /*!< RCC PCLKEN: TIM1CKEN (Bitfield-Mask: 0x01)            */
#define RCC_PCLKEN_TIM1CKEN								 RCC_PCLKEN_TIM1CKEN_Msk
#define RCC_PCLKEN_TIM2CKEN_Pos           (11UL)                    /*!< RCC PCLKEN: TIM2CKEN (Bit 11)                         */
#define RCC_PCLKEN_TIM2CKEN_Msk           (0x800UL)                 /*!< RCC PCLKEN: TIM2CKEN (Bitfield-Mask: 0x01)            */
#define RCC_PCLKEN_TIM2CKEN								 RCC_PCLKEN_TIM2CKEN_Msk
#define RCC_PCLKEN_WWDGCKEN_Pos           (12UL)                    /*!< RCC PCLKEN: WWDGCKEN (Bit 12)                         */
#define RCC_PCLKEN_WWDGCKEN_Msk           (0x1000UL)                /*!< RCC PCLKEN: WWDGCKEN (Bitfield-Mask: 0x01)            */
#define RCC_PCLKEN_WWDGCKEN								 RCC_PCLKEN_WWDGCKEN_Msk
#define RCC_PCLKEN_ADCCKEN_Pos            (13UL)                    /*!< RCC PCLKEN: ADCCKEN (Bit 13)                          */
#define RCC_PCLKEN_ADCCKEN_Msk            (0x2000UL)                /*!< RCC PCLKEN: ADCCKEN (Bitfield-Mask: 0x01)             */
#define RCC_PCLKEN_ADCCKEN								 RCC_PCLKEN_ADCCKEN_Msk
#define RCC_PCLKEN_AWKCKEN_Pos            (14UL)                    /*!< RCC PCLKEN: AWKCKEN (Bit 14)                          */
#define RCC_PCLKEN_AWKCKEN_Msk            (0x4000UL)                /*!< RCC PCLKEN: AWKCKEN (Bitfield-Mask: 0x01)             */
#define RCC_PCLKEN_AWKCKEN								 RCC_PCLKEN_AWKCKEN_Msk
#define RCC_PCLKEN_RTCCKEN_Pos            (15UL)                    /*!< RCC PCLKEN: RTCCKEN (Bit 15)                          */
#define RCC_PCLKEN_RTCCKEN_Msk            (0x8000UL)                /*!< RCC PCLKEN: RTCCKEN (Bitfield-Mask: 0x01)             */
#define RCC_PCLKEN_RTCCKEN								 RCC_PCLKEN_RTCCKEN_Msk
#define RCC_PCLKEN_CLKCTRIMCKEN_Pos       (16UL)                    /*!< RCC PCLKEN: CLKCTRIMCKEN (Bit 16)                     */
#define RCC_PCLKEN_CLKCTRIMCKEN_Msk       (0x10000UL)               /*!< RCC PCLKEN: CLKCTRIMCKEN (Bitfield-Mask: 0x01)        */
#define RCC_PCLKEN_CLKCTRIMCKEN						 RCC_PCLKEN_CLKCTRIMCKEN_Msk
#define RCC_PCLKEN_IWDGCKEN_Pos           (17UL)                    /*!< RCC PCLKEN: IWDGCKEN (Bit 17)                         */
#define RCC_PCLKEN_IWDGCKEN_Msk           (0x20000UL)               /*!< RCC PCLKEN: IWDGCKEN (Bitfield-Mask: 0x01)            */
#define RCC_PCLKEN_IWDGCKEN								 RCC_PCLKEN_IWDGCKEN_Msk
#define RCC_PCLKEN_LVDVCCKEN_Pos          (18UL)                    /*!< RCC PCLKEN: LVDVCCKEN (Bit 18)                        */
#define RCC_PCLKEN_LVDVCCKEN_Msk          (0x40000UL)               /*!< RCC PCLKEN: LVDVCCKEN (Bitfield-Mask: 0x01)           */
#define RCC_PCLKEN_LVDVCCKEN				       RCC_PCLKEN_LVDVCCKEN_Msk
#define RCC_PCLKEN_BEEPCKEN_Pos           (19UL)                    /*!< RCC PCLKEN: BEEPCKEN (Bit 19)                         */
#define RCC_PCLKEN_BEEPCKEN_Msk           (0x80000UL)               /*!< RCC PCLKEN: BEEPCKEN (Bitfield-Mask: 0x01)            */
#define RCC_PCLKEN_BEEPCKEN								 RCC_PCLKEN_BEEPCKEN_Msk
#define RCC_PCLKEN_DBGCKEN_Pos            (20UL)                    /*!< RCC PCLKEN: DBGCKEN (Bit 20)                          */
#define RCC_PCLKEN_DBGCKEN_Msk            (0x100000UL)              /*!< RCC PCLKEN: DBGCKEN (Bitfield-Mask: 0x01)             */
#define RCC_PCLKEN_DBGCKEN								 RCC_PCLKEN_DBGCKEN_Msk
/* =========================================================  MCOCR  ========================================================= */
#define RCC_MCOCR_MCODIV_Pos              (0UL)                     /*!< RCC MCOCR: MCODIV (Bit 0)                             */
#define RCC_MCOCR_MCODIV_Msk              (0xffUL)                  /*!< RCC MCOCR: MCODIV (Bitfield-Mask: 0xff)               */
#define RCC_MCOCR_MCODIV									 RCC_MCOCR_MCODIV_Msk
#define RCC_MCOCR_MCOSEL_Pos              (8UL)                     /*!< RCC MCOCR: MCOSEL (Bit 8)                             */
#define RCC_MCOCR_MCOSEL_Msk              (0x700UL)                 /*!< RCC MCOCR: MCOSEL (Bitfield-Mask: 0x07)               */
#define RCC_MCOCR_MCOSEL									 RCC_MCOCR_MCOSEL_Msk
#define RCC_MCOCR_MCOSEL_0								(0x1 << RCC_MCOCR_MCOSEL_Pos)
#define RCC_MCOCR_MCOSEL_1								(0x2 << RCC_MCOCR_MCOSEL_Pos)
#define RCC_MCOCR_MCOSEL_2								(0x4 << RCC_MCOCR_MCOSEL_Pos)
#define RCC_MCOCR_MCOEN_Pos               (12UL)                    /*!< RCC MCOCR: MCOEN (Bit 12)                             */
#define RCC_MCOCR_MCOEN_Msk               (0x1000UL)                /*!< RCC MCOCR: MCOEN (Bitfield-Mask: 0x01)                */
#define RCC_MCOCR_MCOEN										 RCC_MCOCR_MCOEN_Msk
/* =========================================================  RSTCR  ========================================================= */
#define RCC_RSTCR_MCURST_Pos              (0UL)                     /*!< RCC RSTCR: MCURST (Bit 0)                             */
#define RCC_RSTCR_MCURST_Msk              (0x1UL)                   /*!< RCC RSTCR: MCURST (Bitfield-Mask: 0x01)               */
#define RCC_RSTCR_CPURST_Pos              (1UL)                     /*!< RCC RSTCR: CPURST (Bit 1)                             */
#define RCC_RSTCR_CPURST_Msk              (0x2UL)                   /*!< RCC RSTCR: CPURST (Bitfield-Mask: 0x01)               */
#define RCC_RSTCR_RSTKEY_Pos              (2UL)                     /*!< RCC RSTCR: RSTKEY (Bit 2)                             */
#define RCC_RSTCR_RSTKEY_Msk              (0xfffffffcUL)            /*!< RCC RSTCR: RSTKEY (Bitfield-Mask: 0x3fffffff)         */
/* =========================================================  RSTSR  ========================================================= */
#define RCC_RSTSR_MCURST_Pos              (0UL)                     /*!< RCC RSTSR: MCURST (Bit 0)                             */
#define RCC_RSTSR_MCURST_Msk              (0x1UL)                   /*!< RCC RSTSR: MCURST (Bitfield-Mask: 0x01)               */
#define RCC_RSTSR_MCURST									RCC_RSTSR_MCURST_Msk
#define RCC_RSTSR_CPURST_Pos              (1UL)                     /*!< RCC RSTSR: CPURST (Bit 1)                             */
#define RCC_RSTSR_CPURST_Msk              (0x2UL)                   /*!< RCC RSTSR: CPURST (Bitfield-Mask: 0x01)               */
#define RCC_RSTSR_CPURST									RCC_RSTSR_CPURST_Msk
#define RCC_RSTSR_WWDGRST_Pos             (2UL)                     /*!< RCC RSTSR: WWDGRST (Bit 2)                            */
#define RCC_RSTSR_WWDGRST_Msk             (0x4UL)                   /*!< RCC RSTSR: WWDGRST (Bitfield-Mask: 0x01)              */
#define RCC_RSTSR_WWDGRST									RCC_RSTSR_WWDGRST_Msk
#define RCC_RSTSR_IWDGRST_Pos             (3UL)                     /*!< RCC RSTSR: IWDGRST (Bit 3)                            */
#define RCC_RSTSR_IWDGRST_Msk             (0x8UL)                   /*!< RCC RSTSR: IWDGRST (Bitfield-Mask: 0x01)              */
#define RCC_RSTSR_IWDGRST									RCC_RSTSR_IWDGRST_Msk
#define RCC_RSTSR_LVDRST_Pos              (4UL)                     /*!< RCC RSTSR: LVDRST (Bit 4)                             */
#define RCC_RSTSR_LVDRST_Msk              (0x10UL)                  /*!< RCC RSTSR: LVDRST (Bitfield-Mask: 0x01)               */
#define RCC_RSTSR_LVDRST									RCC_RSTSR_LVDRST_Msk
#define RCC_RSTSR_PORRST_Pos              (5UL)                     /*!< RCC RSTSR: PORRST (Bit 5)                             */
#define RCC_RSTSR_PORRST_Msk              (0x20UL)                  /*!< RCC RSTSR: PORRST (Bitfield-Mask: 0x01)               */
#define RCC_RSTSR_PORRST									RCC_RSTSR_PORRST_Msk
#define RCC_RSTSR_LOCKUPRST_Pos           (6UL)                     /*!< RCC RSTSR: LOCKUPRST (Bit 6)                          */
#define RCC_RSTSR_LOCKUPRST_Msk           (0x40UL)                  /*!< RCC RSTSR: LOCKUPRST (Bitfield-Mask: 0x01)            */
#define RCC_RSTSR_LOCKUPRST								RCC_RSTSR_LOCKUPRST_Msk
#define RCC_RSTSR_PADRST_Pos              (7UL)                     /*!< RCC RSTSR: PADRST (Bit 7)                             */
#define RCC_RSTSR_PADRST_Msk              (0x80UL)                  /*!< RCC RSTSR: PADRST (Bitfield-Mask: 0x01)               */
#define RCC_RSTSR_PADRST									RCC_RSTSR_PADRST_Msk
#define RCC_RSTSR_SFTRST_Pos              (8UL)                     /*!< RCC RSTSR: SFTRST (Bit 8)                             */
#define RCC_RSTSR_SFTRST_Msk              (0x100UL)                 /*!< RCC RSTSR: SFTRST (Bitfield-Mask: 0x01)               */
#define RCC_RSTSR_SFTRST									RCC_RSTSR_SFTRST_Msk
/* =======================================================  SYSCLKCR  ======================================================== */
#define RCC_SYSCLKCR_HIRCEN_Pos           (0UL)                     /*!< RCC SYSCLKCR: HIRCEN (Bit 0)                          */
#define RCC_SYSCLKCR_HIRCEN_Msk           (0x1UL)                   /*!< RCC SYSCLKCR: HIRCEN (Bitfield-Mask: 0x01)            */
#define RCC_SYSCLKCR_HIRCEN								 RCC_SYSCLKCR_HIRCEN_Msk
#define RCC_SYSCLKCR_HXTEN_Pos            (1UL)                     /*!< RCC SYSCLKCR: HXTEN (Bit 1)                           */
#define RCC_SYSCLKCR_HXTEN_Msk            (0x2UL)                   /*!< RCC SYSCLKCR: HXTEN (Bitfield-Mask: 0x01)             */
#define RCC_SYSCLKCR_HXTEN								 RCC_SYSCLKCR_HXTEN_Msk
#define RCC_SYSCLKCR_LIRCEN_Pos           (2UL)                     /*!< RCC SYSCLKCR: LIRCEN (Bit 2)                          */
#define RCC_SYSCLKCR_LIRCEN_Msk           (0x4UL)                   /*!< RCC SYSCLKCR: LIRCEN (Bitfield-Mask: 0x01)            */
#define RCC_SYSCLKCR_LIRCEN								 RCC_SYSCLKCR_LIRCEN_Msk
#define RCC_SYSCLKCR_HXTBYP_Pos           (5UL)                     /*!< RCC SYSCLKCR: HXTBYP (Bit 5)                          */
#define RCC_SYSCLKCR_HXTBYP_Msk           (0x20UL)                  /*!< RCC SYSCLKCR: HXTBYP (Bitfield-Mask: 0x01)            */
#define RCC_SYSCLKCR_HXTBYP								 RCC_SYSCLKCR_HXTBYP_Msk
#define RCC_SYSCLKCR_HXTPORT_Pos          (6UL)                     /*!< RCC SYSCLKCR: HXTPORT (Bit 6)                         */
#define RCC_SYSCLKCR_HXTPORT_Msk          (0x40UL)                  /*!< RCC SYSCLKCR: HXTPORT (Bitfield-Mask: 0x01)           */
#define RCC_SYSCLKCR_HXTPORT							 RCC_SYSCLKCR_HXTPORT_Msk
#define RCC_SYSCLKCR_CLKFAILEN_Pos        (8UL)                     /*!< RCC SYSCLKCR: CLKFAILEN (Bit 8)                       */
#define RCC_SYSCLKCR_CLKFAILEN_Msk        (0x100UL)                 /*!< RCC SYSCLKCR: CLKFAILEN (Bitfield-Mask: 0x01)         */
#define RCC_SYSCLKCR_CLKFAILEN						 RCC_SYSCLKCR_CLKFAILEN_Msk
#define RCC_SYSCLKCR_WKBYHIRC_Pos         (15UL)                    /*!< RCC SYSCLKCR: WKBYHIRC (Bit 15)                       */
#define RCC_SYSCLKCR_WKBYHIRC_Msk         (0x8000UL)                /*!< RCC SYSCLKCR: WKBYHIRC (Bitfield-Mask: 0x01)          */
#define RCC_SYSCLKCR_WKBYHIRC							 RCC_SYSCLKCR_WKBYHIRC_Msk
#define RCC_SYSCLKCR_KEY_Pos              (16UL)                    /*!< RCC SYSCLKCR: KEY (Bit 16)                            */
#define RCC_SYSCLKCR_KEY_Msk              (0xffff0000UL)            /*!< RCC SYSCLKCR: KEY (Bitfield-Mask: 0xffff)             */
#define RCC_SYSCLKCR_KEY									 RCC_SYSCLKCR_KEY_Msk
/* =======================================================  SYSCLKSEL  ======================================================= */
#define RCC_SYSCLKSEL_CLKSW_Pos           (0UL)                     /*!< RCC SYSCLKSEL: CLKSW (Bit 0)                          */
#define RCC_SYSCLKSEL_CLKSW_Msk           (0xfUL)                   /*!< RCC SYSCLKSEL: CLKSW (Bitfield-Mask: 0x0f)            */
#define RCC_SYSCLKSEL_CLKSW								 RCC_SYSCLKSEL_CLKSW_Msk
#define RCC_SYSCLKSEL_CLKSW_0             (0x1U << RCC_SYSCLKSEL_CLKSW_Pos)     
#define RCC_SYSCLKSEL_CLKSW_1             (0x2U << RCC_SYSCLKSEL_CLKSW_Pos)     
#define RCC_SYSCLKSEL_CLKSW_2             (0x4U << RCC_SYSCLKSEL_CLKSW_Pos)    
#define RCC_SYSCLKSEL_CLKSW_3             (0x8U << RCC_SYSCLKSEL_CLKSW_Pos)    
#define RCC_SYSCLKSEL_KEY_Pos             (16UL)                    /*!< RCC SYSCLKSEL: KEY (Bit 16)                           */
#define RCC_SYSCLKSEL_KEY_Msk             (0xffff0000UL)            /*!< RCC SYSCLKSEL: KEY (Bitfield-Mask: 0xffff)            */
#define RCC_SYSCLKSEL_KEY									 RCC_SYSCLKSEL_KEY_Msk
/* ========================================================  HIRCCR  ========================================================= */
#define RCC_HIRCCR_HIRCTRIM_Pos           (0UL)                     /*!< RCC HIRCCR: HIRCTRIM (Bit 0)                          */
#define RCC_HIRCCR_HIRCTRIM_Msk           (0xfffUL)                 /*!< RCC HIRCCR: HIRCTRIM (Bitfield-Mask: 0xfff)           */
#define RCC_HIRCCR_HIRCTRIM								 RCC_HIRCCR_HIRCTRIM_Msk
#define RCC_HIRCCR_HIRCTRIM_0_8_Mask			(0x1ffUL)
#define RCC_HIRCCR_HIRCTRIM_9							(0x200 << RCC_HIRCCR_HIRCTRIM_Pos)
#define RCC_HIRCCR_HIRCTRIM_10						(0x400 << RCC_HIRCCR_HIRCTRIM_Pos)
#define RCC_HIRCCR_HIRCTRIM_11						(0x800 << RCC_HIRCCR_HIRCTRIM_Pos)
#define RCC_HIRCCR_HIRCRDY_Pos            (12UL)                    /*!< RCC HIRCCR: HIRCRDY (Bit 12)                          */
#define RCC_HIRCCR_HIRCRDY_Msk            (0x1000UL)                /*!< RCC HIRCCR: HIRCRDY (Bitfield-Mask: 0x01)             */
#define RCC_HIRCCR_HIRCRDY								 RCC_HIRCCR_HIRCRDY_Msk
#define RCC_HIRCCR_KEY_Pos                (16UL)                    /*!< RCC HIRCCR: KEY (Bit 16)                              */
#define RCC_HIRCCR_KEY_Msk                (0xffff0000UL)            /*!< RCC HIRCCR: KEY (Bitfield-Mask: 0xffff)               */
#define RCC_HIRCCR_KEY										 RCC_HIRCCR_KEY_Msk
/* =========================================================  HXTCR  ========================================================= */
#define RCC_HXTCR_HXTDRV_Pos              (0UL)                     /*!< RCC HXTCR: HXTDRV (Bit 0)                             */
#define RCC_HXTCR_HXTDRV_Msk              (0x7UL)                   /*!< RCC HXTCR: HXTDRV (Bitfield-Mask: 0x07)               */
#define RCC_HXTCR_HXTDRV									 RCC_HXTCR_HXTDRV_Msk
#define RCC_HXTCR_HXTSTARTUP_Pos          (4UL)                     /*!< RCC HXTCR: HXTSTARTUP (Bit 4)                         */
#define RCC_HXTCR_HXTSTARTUP_Msk          (0x30UL)                  /*!< RCC HXTCR: HXTSTARTUP (Bitfield-Mask: 0x03)           */
#define RCC_HXTCR_HXTSTARTUP							 RCC_HXTCR_HXTSTARTUP_Msk
#define RCC_HXTCR_HXTRDY_Pos              (6UL)                     /*!< RCC HXTCR: HXTRDY (Bit 6)                             */
#define RCC_HXTCR_HXTRDY_Msk              (0x40UL)            			/*!< RCC HXTCR: HXTRDY (Bitfield-Mask: 0x01)               */
#define RCC_HXTCR_HXTRDY									 RCC_HXTCR_HXTRDY_Msk
/* ========================================================  LIRCCR  ========================================================= */
#define RCC_LIRCCR_LIRCTRIM_Pos           (0UL)                     /*!< RCC LIRCCR: LIRCTRIM (Bit 0)                          */
#define RCC_LIRCCR_LIRCTRIM_Msk           (0x1ffUL)                 /*!< RCC LIRCCR: LIRCTRIM (Bitfield-Mask: 0x1ff)           */
#define RCC_LIRCCR_LIRCTRIM								RCC_LIRCCR_LIRCTRIM_Msk
#define RCC_LIRCCR_LIRCSTARTUP_Pos        (10UL)                    /*!< RCC LIRCCR: LIRCSTARTUP (Bit 10)                      */
#define RCC_LIRCCR_LIRCSTARTUP_Msk        (0xc00UL)                 /*!< RCC LIRCCR: LIRCSTARTUP (Bitfield-Mask: 0x03)         */
#define RCC_LIRCCR_LIRCSTARTUP						RCC_LIRCCR_LIRCSTARTUP_Msk
#define RCC_LIRCCR_LIRCSTARTUP_0					(0x01<<RCC_LIRCCR_LIRCSTARTUP_Pos)
#define RCC_LIRCCR_LIRCSTARTUP_1					(0x02<<RCC_LIRCCR_LIRCSTARTUP_Pos)
#define RCC_LIRCCR_LIRCRDY_Pos            (12UL)                    /*!< RCC LIRCCR: LIRCRDY (Bit 12)                          */
#define RCC_LIRCCR_LIRCRDY_Msk            (0x1000UL)                /*!< RCC LIRCCR: LIRCRDY (Bitfield-Mask: 0x01)             */
#define RCC_LIRCCR_LIRCRDY								RCC_LIRCCR_LIRCRDY_Msk
#define RCC_LIRCCR_KEY_Pos                (16UL)                    /*!< RCC LIRCCR: KEY (Bit 16)                              */
#define RCC_LIRCCR_KEY_Msk                (0xffff0000UL)            /*!< RCC LIRCCR: KEY (Bitfield-Mask: 0xffff)               */
#define RCC_LIRCCR_KEY										RCC_LIRCCR_KEY_Msk
/* =========================================================  LXTCR  ========================================================= */
#define RCC_LXTCR_LXTDRV_Pos              (0UL)                     /*!< RCC LXTCR: LXTDRV (Bit 0)                             */
#define RCC_LXTCR_LXTDRV_Msk              (0xfUL)                   /*!< RCC LXTCR: LXTDRV (Bitfield-Mask: 0x0f)               */
#define RCC_LXTCR_LXTDRV									 RCC_LXTCR_LXTDRV_Msk
#define RCC_LXTCR_LXTSTARTUP_Pos          (4UL)                     /*!< RCC LXTCR: LXTSTARTUP (Bit 4)                         */
#define RCC_LXTCR_LXTSTARTUP_Msk          (0x30UL)                  /*!< RCC LXTCR: LXTSTARTUP (Bitfield-Mask: 0x03)           */
#define RCC_LXTCR_LXTSTARTUP							 RCC_LXTCR_LXTSTARTUP_Msk
#define RCC_LXTCR_LXTRDY_Pos              (6UL)                     /*!< RCC LXTCR: LXTRDY (Bit 6)                             */
#define RCC_LXTCR_LXTRDY_Msk              (0x40UL)                  /*!< RCC LXTCR: LXTRDY (Bitfield-Mask: 0x01)               */
#define RCC_LXTCR_LXTRDY									 RCC_LXTCR_LXTRDY_Msk
#define RCC_LXTCR_LXTEN_Pos               (8UL)                     /*!< RCC LXTCR: LXTEN (Bit 8)                              */
#define RCC_LXTCR_LXTEN_Msk               (0x100UL)                 /*!< RCC LXTCR: LXTEN (Bitfield-Mask: 0x01)                */
#define RCC_LXTCR_LXTEN										 RCC_LXTCR_LXTEN_Msk
#define RCC_LXTCR_LXTBYP_Pos              (9UL)                     /*!< RCC LXTCR: LXTBYP (Bit 9)                             */
#define RCC_LXTCR_LXTBYP_Msk              (0x200UL)                 /*!< RCC LXTCR: LXTBYP (Bitfield-Mask: 0x01)               */
#define RCC_LXTCR_LXTBYP									 RCC_LXTCR_LXTBYP_Msk
#define RCC_LXTCR_LXTAON_Pos              (10UL)                    /*!< RCC LXTCR: LXTAON (Bit 10)                            */
#define RCC_LXTCR_LXTAON_Msk              (0x400UL)                 /*!< RCC LXTCR: LXTAON (Bitfield-Mask: 0x01)               */
#define RCC_LXTCR_LXTAON									 RCC_LXTCR_LXTAON_Msk
#define RCC_LXTCR_LXTPORT_Pos             (11UL)                    /*!< RCC LXTCR: LXTPORT (Bit 11)                           */
#define RCC_LXTCR_LXTPORT_Msk             (0x800UL)                 /*!< RCC LXTCR: LXTPORT (Bitfield-Mask: 0x01)              */
#define RCC_LXTCR_LXTPORT									 RCC_LXTCR_LXTPORT_Msk
#define RCC_LXTCR_KEY_Pos                 (16UL)                    /*!< RCC LXTCR: KEY (Bit 16)                               */
#define RCC_LXTCR_KEY_Msk                 (0xffff0000UL)            /*!< RCC LXTCR: KEY (Bitfield-Mask: 0xffff)                */
#define RCC_LXTCR_KEY											 RCC_LXTCR_KEY_Msk
/* ======================================================  IRQLATENCY  ======================================================= */
#define RCC_IRQLATENCY_IRQLATENCY_Pos     (0UL)                     /*!< RCC IRQLATENCY: IRQLATENCY (Bit 0)                    */
#define RCC_IRQLATENCY_IRQLATENCY_Msk     (0xffUL)                  /*!< RCC IRQLATENCY: IRQLATENCY (Bitfield-Mask: 0xff)      */
/* ========================================================  STICKCR  ======================================================== */
#define RCC_STICKCR_STCALIB_Pos           (0UL)                     /*!< RCC STICKCR: STCALIB (Bit 0)                          */
#define RCC_STICKCR_STCALIB_Msk           (0xffffffUL)              /*!< RCC STICKCR: STCALIB (Bitfield-Mask: 0xffffff)        */
#define RCC_STICKCR_SKEW_Pos              (24UL)                    /*!< RCC STICKCR: SKEW (Bit 24)                            */
#define RCC_STICKCR_SKEW_Msk              (0x1000000UL)             /*!< RCC STICKCR: SKEW (Bitfield-Mask: 0x01)               */
#define RCC_STICKCR_NOREF_Pos             (25UL)                    /*!< RCC STICKCR: NOREF (Bit 25)                           */
#define RCC_STICKCR_NOREF_Msk             (0x2000000UL)             /*!< RCC STICKCR: NOREF (Bitfield-Mask: 0x01)              */
/* ========================================================  SWDIOCR  ======================================================== */
#define RCC_SWDIOCR_SWDPORT_Pos           (0UL)                     /*!< RCC SWDIOCR: SWDPORT (Bit 0)                          */
#define RCC_SWDIOCR_SWDPORT_Msk           (0x1UL)                   /*!< RCC SWDIOCR: SWDPORT (Bitfield-Mask: 0x01)            */
#define RCC_SWDIOCR_KEY_Pos               (16UL)                    /*!< RCC SWDIOCR: KEY (Bit 16)                             */
#define RCC_SWDIOCR_KEY_Msk               (0xffff0000UL)            /*!< RCC SWDIOCR: KEY (Bitfield-Mask: 0xffff)              */
/* ========================================================  PERIRST  ======================================================== */
#define RCC_PERIRST_UART0RST_Pos          (0UL)                     /*!< RCC PERIRST: UART0RST (Bit 0)                         */
#define RCC_PERIRST_UART0RST_Msk          (0x1UL)                   /*!< RCC PERIRST: UART0RST (Bitfield-Mask: 0x01)           */
#define RCC_PERIRST_UART0RST						   RCC_PERIRST_UART0RST_Msk
#define RCC_PERIRST_UART1RST_Pos          (1UL)                     /*!< RCC PERIRST: UART1RST (Bit 1)                         */
#define RCC_PERIRST_UART1RST_Msk          (0x2UL)                   /*!< RCC PERIRST: UART1RST (Bitfield-Mask: 0x01)           */
#define RCC_PERIRST_UART1RST							 RCC_PERIRST_UART1RST_Msk
#define RCC_PERIRST_I2CRST_Pos            (2UL)                     /*!< RCC PERIRST: I2CRST (Bit 2)                           */
#define RCC_PERIRST_I2CRST_Msk            (0x4UL)                   /*!< RCC PERIRST: I2CRST (Bitfield-Mask: 0x01)             */
#define RCC_PERIRST_I2CRST								 RCC_PERIRST_I2CRST_Msk
#define RCC_PERIRST_LPUARTRST_Pos         (3UL)                     /*!< RCC PERIRST: LPUARTRST (Bit 3)                        */
#define RCC_PERIRST_LPUARTRST_Msk         (0x8UL)                   /*!< RCC PERIRST: LPUARTRST (Bitfield-Mask: 0x01)          */
#define RCC_PERIRST_LPUARTRST							 RCC_PERIRST_LPUARTRST_Msk
#define RCC_PERIRST_SPIRST_Pos            (4UL)                     /*!< RCC PERIRST: SPIRST (Bit 4)                           */
#define RCC_PERIRST_SPIRST_Msk            (0x10UL)                  /*!< RCC PERIRST: SPIRST (Bitfield-Mask: 0x01)             */
#define RCC_PERIRST_SPIRST						     RCC_PERIRST_SPIRST_Msk
#define RCC_PERIRST_LPTIMRST_Pos          (5UL)                     /*!< RCC PERIRST: LPTIMRST (Bit 5)                         */
#define RCC_PERIRST_LPTIMRST_Msk          (0x20UL)                  /*!< RCC PERIRST: LPTIMRST (Bitfield-Mask: 0x01)           */
#define RCC_PERIRST_LPTIMRST							 RCC_PERIRST_LPTIMRST_Msk
#define RCC_PERIRST_BASETIMRST_Pos        (6UL)                     /*!< RCC PERIRST: BASETIMRST (Bit 6)                       */
#define RCC_PERIRST_BASETIMRST_Msk        (0x40UL)                  /*!< RCC PERIRST: BASETIMRST (Bitfield-Mask: 0x01)         */
#define RCC_PERIRST_BASETIMRST						 RCC_PERIRST_BASETIMRST_Msk
#define RCC_PERIRST_SYSCONRST_Pos         (7UL)                     /*!< RCC PERIRST: SYSCONRST (Bit 7)                        */
#define RCC_PERIRST_SYSCONRST_Msk         (0x80UL)                  /*!< RCC PERIRST: SYSCONRST (Bitfield-Mask: 0x01)          */
#define RCC_PERIRST_SYSCONRST					     RCC_PERIRST_SYSCONRST_Msk
#define RCC_PERIRST_PCARST_Pos            (8UL)                     /*!< RCC PERIRST: PCARST (Bit 8)                           */
#define RCC_PERIRST_PCARST_Msk            (0x100UL)                 /*!< RCC PERIRST: PCARST (Bitfield-Mask: 0x01)             */
#define RCC_PERIRST_PCARST								 RCC_PERIRST_PCARST_Msk
#define RCC_PERIRST_OWIRERST_Pos          (9UL)                     /*!< RCC PERIRST: OWIRERST (Bit 9)                         */
#define RCC_PERIRST_OWIRERST_Msk          (0x200UL)                 /*!< RCC PERIRST: OWIRERST (Bitfield-Mask: 0x01)           */
#define RCC_PERIRST_OWIRERST							 RCC_PERIRST_OWIRERST_Msk
#define RCC_PERIRST_TIM1RST_Pos           (10UL)                    /*!< RCC PERIRST: TIM1RST (Bit 10)                         */
#define RCC_PERIRST_TIM1RST_Msk           (0x400UL)                 /*!< RCC PERIRST: TIM1RST (Bitfield-Mask: 0x01)            */
#define RCC_PERIRST_TIM1RST								 RCC_PERIRST_TIM1RST_Msk
#define RCC_PERIRST_TIM2RST_Pos           (11UL)                    /*!< RCC PERIRST: TIM2RST (Bit 11)                         */
#define RCC_PERIRST_TIM2RST_Msk           (0x800UL)                 /*!< RCC PERIRST: TIM2RST (Bitfield-Mask: 0x01)            */
#define RCC_PERIRST_TIM2RST								 RCC_PERIRST_TIM2RST_Msk
#define RCC_PERIRST_WWDGRST_Pos           (12UL)                    /*!< RCC PERIRST: WWDGRST (Bit 12)                         */
#define RCC_PERIRST_WWDGRST_Msk           (0x1000UL)                /*!< RCC PERIRST: WWDGRST (Bitfield-Mask: 0x01)            */
#define RCC_PERIRST_WWDGRST								 RCC_PERIRST_WWDGRST_Msk
#define RCC_PERIRST_ADCRST_Pos            (13UL)                    /*!< RCC PERIRST: ADCRST (Bit 13)                          */
#define RCC_PERIRST_ADCRST_Msk            (0x2000UL)                /*!< RCC PERIRST: ADCRST (Bitfield-Mask: 0x01)             */
#define RCC_PERIRST_ADCRST								 RCC_PERIRST_ADCRST_Msk
#define RCC_PERIRST_AWKRST_Pos            (14UL)                    /*!< RCC PERIRST: AWKRST (Bit 14)                          */
#define RCC_PERIRST_AWKRST_Msk            (0x4000UL)                /*!< RCC PERIRST: AWKRST (Bitfield-Mask: 0x01)             */
#define RCC_PERIRST_AWKRST								 RCC_PERIRST_AWKRST_Msk
#define RCC_PERIRST_CLKTRIMRST_Pos        (16UL)                    /*!< RCC PERIRST: CLKTRIMRST (Bit 16)                      */
#define RCC_PERIRST_CLKTRIMRST_Msk        (0x10000UL)               /*!< RCC PERIRST: CLKTRIMRST (Bitfield-Mask: 0x01)         */
#define RCC_PERIRST_CLKTRIMRST						 RCC_PERIRST_CLKTRIMRST_Msk
#define RCC_PERIRST_LVDVCRST_Pos          (18UL)                    /*!< RCC PERIRST: LVDVCRST (Bit 18)                        */
#define RCC_PERIRST_LVDVCRST_Msk          (0x40000UL)               /*!< RCC PERIRST: LVDVCRST (Bitfield-Mask: 0x01)           */
#define RCC_PERIRST_LVDVCRST							 RCC_PERIRST_LVDVCRST_Msk
#define RCC_PERIRST_BEEPRST_Pos           (19UL)                    /*!< RCC PERIRST: BEEPRST (Bit 19)                         */
#define RCC_PERIRST_BEEPRST_Msk           (0x80000UL)               /*!< RCC PERIRST: BEEPRST (Bitfield-Mask: 0x01)            */
#define RCC_PERIRST_BEEPRST								 RCC_PERIRST_BEEPRST_Msk
#define RCC_PERIRST_DBGRST_Pos            (20UL)                    /*!< RCC PERIRST: DBGRST (Bit 20)                          */
#define RCC_PERIRST_DBGRST_Msk            (0x100000UL)              /*!< RCC PERIRST: DBGRST (Bitfield-Mask: 0x01)             */
#define RCC_PERIRST_DBGRST								 RCC_PERIRST_DBGRST_Msk
#define RCC_PERIRST_GPIOARST_Pos          (24UL)                    /*!< RCC PERIRST: GPIOARST (Bit 24)                        */
#define RCC_PERIRST_GPIOARST_Msk          (0x1000000UL)             /*!< RCC PERIRST: GPIOARST (Bitfield-Mask: 0x01)           */
#define RCC_PERIRST_GPIOARST							 RCC_PERIRST_GPIOARST_Msk
#define RCC_PERIRST_GPIOBRST_Pos          (25UL)                    /*!< RCC PERIRST: GPIOBRST (Bit 25)                        */
#define RCC_PERIRST_GPIOBRST_Msk          (0x2000000UL)             /*!< RCC PERIRST: GPIOBRST (Bitfield-Mask: 0x01)           */
#define RCC_PERIRST_GPIOBRST							 RCC_PERIRST_GPIOBRST_Msk
#define RCC_PERIRST_GPIOCRST_Pos          (26UL)                    /*!< RCC PERIRST: GPIOCRST (Bit 26)                        */
#define RCC_PERIRST_GPIOCRST_Msk          (0x4000000UL)             /*!< RCC PERIRST: GPIOCRST (Bitfield-Mask: 0x01)           */
#define RCC_PERIRST_GPIOCRST							 RCC_PERIRST_GPIOCRST_Msk
#define RCC_PERIRST_GPIODRST_Pos          (27UL)                    /*!< RCC PERIRST: GPIODRST (Bit 27)                        */
#define RCC_PERIRST_GPIODRST_Msk          (0x8000000UL)             /*!< RCC PERIRST: GPIODRST (Bitfield-Mask: 0x01)           */
#define RCC_PERIRST_GPIODRST							 RCC_PERIRST_GPIODRST_Msk
#define RCC_PERIRST_CRCRST_Pos            (28UL)                    /*!< RCC PERIRST: CRCRST (Bit 28)                          */
#define RCC_PERIRST_CRCRST_Msk            (0x10000000UL)            /*!< RCC PERIRST: CRCRST (Bitfield-Mask: 0x01)             */
#define RCC_PERIRST_CRCRST								 RCC_PERIRST_CRCRST_Msk
/* ========================================================  RTCRST  ========================================================= */
#define RCC_RTCRST_RTCRST_Pos             (0UL)                     /*!< RCC RTCRST: RTCRST (Bit 0)                            */
#define RCC_RTCRST_RTCRST_Msk             (0x1UL)                   /*!< RCC RTCRST: RTCRST (Bitfield-Mask: 0x01)              */
#define RCC_RTCRST_RTCRST									 RCC_RTCRST_RTCRST_Msk
#define RCC_RTCRST_KEY_Pos                (16UL)                    /*!< RCC RTCRST: KEY (Bit 16)                              */
#define RCC_RTCRST_KEY_Msk                (0xffff0000UL)            /*!< RCC RTCRST: KEY (Bitfield-Mask: 0xffff)               */
#define RCC_RTCRST_KEY										 RCC_RTCRST_KEY_Msk
/* ========================================================  UNLOCK  ========================================================= */
#define RCC_UNLOCK_UNLOCK_Pos             (0UL)                     /*!< RCC UNLOCK: UNLOCK (Bit 0)                            */
#define RCC_UNLOCK_UNLOCK_Msk             (0x1UL)                   /*!< RCC UNLOCK: UNLOCK (Bitfield-Mask: 0x01)              */
#define RCC_UNLOCK_UNLOCK									 RCC_UNLOCK_UNLOCK_Msk
#define RCC_UNLOCK_KEY_Pos                (1UL)                     /*!< RCC UNLOCK: KEY (Bit 1)                               */
#define RCC_UNLOCK_KEY_Msk                (0xfffffffeUL)            /*!< RCC UNLOCK: KEY (Bitfield-Mask: 0x7fffffff)           */
#define RCC_UNLOCK_KEY										 RCC_UNLOCK_KEY_Msk

/** @} */ /* End of group PosMask_peripherals */

#ifdef __cplusplus
}
#endif

#endif /* CX32L003_H */

/** @} */ /* End of group CX32L003 */

