/**
  ******************************************************************************
  * @file    cx32l003_hal_syscon.h
  * @author  MCU Software Team
  * @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Header file of SYSCON HAL module.
  ******************************************************************************
 **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CX32L003_HAL_SYSCON_H
#define __CX32L003_HAL_SYSCON_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cx32l003_hal_def.h"

/** @addtogroup SYSCON
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** @defgroup SYSCON_Exported_Types SYSCON Exported Types
  * @{
  */

/**
  * @}
  */ 

/* Exported constants --------------------------------------------------------*/
#define SYSCON_KEY_UNLOCK		 	(0x5A69)

#define SYSCON_DEFAULT			 	(0x00U)				
#define SYSCON_UART0_RXD 		 	(0x01U)
#define SYSCON_UART1_RXD 		 	(0x02U)
#define SYSCON_LPUART_RXD		 	(0x03U)
#define SYSCON_LIRC		 				(0x04U)

#define SYSCON_HIGHLEVEL			(0x00U)
#define SYSCON_LOWLEVEL				(0x00U)
#define SYSCON_PA1						(0x01U)
#define SYSCON_PA2						(0x02U)
#define SYSCON_PA3						(0x03U)
#define SYSCON_PB4						(0x04U)
#define SYSCON_PB5						(0x05U)
#define SYSCON_PC3						(0x06U)
#define SYSCON_PC4						(0x07U)
#define SYSCON_PC5						(0x08U)
#define SYSCON_PC6						(0x09U)
#define SYSCON_PC7						(0x0AU)
#define SYSCON_PD1						(0x0BU)
#define SYSCON_PD2						(0x0CU)
#define SYSCON_PD3						(0x0DU)
#define SYSCON_PD4						(0x0EU)
#define SYSCON_PD6						(0x0FU)

#define SYSCON_CLKFAILBRKEN		SYSCON_TIM1CR_CLKFAILBRKEN
#define SYSCON_DSLPBRKEN			SYSCON_TIM1CR_DSLPBRKEN

#define SYSCON_OCOUT_LOWLEVEL	SYSCON_TIM1CR_TIM1BRKOUTCFG
#define SYSCON_OCOUT_BYTIM1		(0x00U)



/* Exported macro ------------------------------------------------------------*/

/** @defgroup SYSCON_Exported_Macros SYSCON Exported Macros
  * @{
  */

#define __HAL_SYSCON_REGWR_LOCK()							(SYSCON->UNLOCK = (0x2AD5334C << SYSCON_UNLOCK_KEY_Pos) & SYSCON_UNLOCK_KEY)
#define __HAL_SYSCON_REGWR_UNLOCK()						(SYSCON->UNLOCK = SYSCON_UNLOCK_UNLOCK | (0x2AD5334C << SYSCON_UNLOCK_KEY_Pos))

/** @brief Macro to disable deep sleep mode in debug mode, allow to debug deep sleep mode.
  * @note  In debug mode, CPU will not enter deep sleep mode
  */
#define __HAL_SYSCON_DBGDEEPSLEEP_ENABLE() 			  \
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							SET_BIT(SYSCON->CFGR0, SYSCON_CFGR0_DBGDLSP_DIS | (SYSCON_UNLOCK_KEY << SYSCON_CFGR0_KEY_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)	

/** @brief Macro to enable deep sleep mode in debug mode, debug mode will quit in deep sleep mode.
  * @note  In debug mode, deep sleep mode will make debug mode quit
  */
#define __HAL_SYSCON_DBGDEEPSLEEP_DISABLE() 			\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							CLEAR_WPBIT(SYSCON->CFGR0, SYSCON_CFGR0_DBGDLSP_DIS, (SYSCON_UNLOCK_KEY << SYSCON_CFGR0_KEY_Pos)); \
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)	

/** @brief Macro to enable cpu lock up function.
  */
#define __HAL_SYSCON_LOCKUP_ENABLE() 			\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							SET_BIT(SYSCON->CFGR0, SYSCON_CFGR0_LOCKUPEN | (SYSCON_UNLOCK_KEY << SYSCON_CFGR0_KEY_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)	
						
/** @brief Macro to disable cpu lock up function.
  */
#define __HAL_SYSCON_LOCKUP_DISABLE() 			\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							CLEAR_WPBIT(SYSCON->CFGR0, SYSCON_CFGR0_LOCKUPEN, (SYSCON_UNLOCK_KEY << SYSCON_CFGR0_KEY_Pos)); \
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)		

/** @brief Macro to config PAD interrupt mode as AUTO for deep sleep:.
  */
#define __HAL_SYSCON_DEEPSLEEP_PADINT_AUTO() 			\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							CLEAR_WPBIT(SYSCON->PORTINTCR, SYSCON_PORTINTCR_PADDLSPCON, (SYSCON_UNLOCK_KEY << SYSCON_PORTINTCR_KEY_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)							
						
/** @brief Macro to config PAD interrupt mode as ACTIVE for deep sleep.
  */
#define __HAL_SYSCON_DEEPSLEEP_PADINT_ACTIVE() 			\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							SET_BIT(SYSCON->PORTINTCR, SYSCON_PORTINTCR_PADDLSPCON | (SYSCON_UNLOCK_KEY << SYSCON_PORTINTCR_KEY_Pos));	\
							CLEAR_WPBIT(SYSCON->PORTINTCR, SYSCON_PORTINTCR_PADINTSEL, (SYSCON_UNLOCK_KEY << SYSCON_PORTINTCR_KEY_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)


/** @brief Macro to select low power timer gate signal input source from gpio.
  * @param __SOURCE__: source for LPTIM gate input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: LPTIM_GATE alternate function is low power timer gate signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is low power timer gate signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is low power timer gate signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is low power timer gate signal input source							
  */
#define __HAL_SYSCON_LPTIM_GATE(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_LPTIM_GATE_SEL, ((__SOURCE__) << SYSCON_PORTCR_LPTIM_GATE_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)						
						
						
/** @brief Macro to select timer11 gate signal input source from gpio.
  * @param __SOURCE__: source for TIM11 gate input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: TIM11_GATE alternate function is timer11 gate signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is timer11 gate signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is timer11 gate signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is timer11 gate signal input source							
  */
#define __HAL_SYSCON_TIM11_GATE(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_TIM11_GATE_SEL, ((__SOURCE__) << SYSCON_PORTCR_TIM11_GATE_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)								
		
						
/** @brief Macro to select timer10 gate signal input source from gpio.
  * @param __SOURCE__: source for TIM10 gate input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: TIM10_GATE alternate function is timer10 gate signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is timer10 gate signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is timer10 gate signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is timer10 gate signal input source							
  */
#define __HAL_SYSCON_TIM10_GATE(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_TIM10_GATE_SEL, ((__SOURCE__) << SYSCON_PORTCR_TIM10_GATE_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)	
						

/** @brief Macro to select spi slave mode NCS signal input source from gpio.
  * @param __SOURCE__: source for spi NCS signal input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_HIGHLEVEL: high level is spi NCS input source			
	*						@arg	SYSCON_PA1			: PA1 is spi NCS input source			
	*						@arg	SYSCON_PA2			: PA2 is spi NCS input source			
	*						@arg	SYSCON_PA3			: PA3 is spi NCS input source			
	*						@arg	SYSCON_PB4			: PB4 is spi NCS input source			
	*						@arg	SYSCON_PB5			:	PB5 is spi NCS input source					
	*						@arg	SYSCON_PC3			:	PC3 is spi NCS input source					
	*						@arg	SYSCON_PC4			:	PC4 is spi NCS input source					
	*						@arg	SYSCON_PC5			:	PC5 is spi NCS input source					
	*						@arg	SYSCON_PC6			:	PC6 is spi NCS input source					
	*						@arg	SYSCON_PC7			:	PC7 is spi NCS input source					
	*						@arg	SYSCON_PD1			:	PD1 is spi NCS input source					
	*						@arg	SYSCON_PD2			:	PD2 is spi NCS input source					
	*						@arg	SYSCON_PD3			:	PD3 is spi NCS input source					
	*						@arg	SYSCON_PD4			:	PD4 is spi NCS input source					
	*						@arg	SYSCON_PD6			:	PD6 is spi NCS input source					
  */
#define __HAL_SYSCON_SPINCS(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_SPINCS_SEL, ((__SOURCE__) << SYSCON_PORTCR_SPINCS_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)	



/** @brief Macro to select pca cap4 signal input source from gpio.
  * @param __SOURCE__: source for pca cap4 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: PCA_CH4 alternate function is pca cap4 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is pca cap4 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is pca cap4 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap4 signal input source							
  */
#define __HAL_SYSCON_PCA_CAP4(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP4_SEL, ((__SOURCE__) << SYSCON_PCACR_PCA_CAP4_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)								
		
						
/** @brief Macro to select pca cap3 signal input source from gpio.
  * @param __SOURCE__: source for pca cap3 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: PCA_CH3 alternate function is pca cap3 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is pca cap3 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is pca cap3 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap3 signal input source							
  */
#define __HAL_SYSCON_PCA_CAP3(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP3_SEL, ((__SOURCE__) << SYSCON_PCACR_PCA_CAP3_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)							

			
/** @brief Macro to select pca cap2 signal input source from gpio.
  * @param __SOURCE__: source for pca cap2 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: PCA_CH2 alternate function is pca cap2 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is pca cap2 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is pca cap2 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap2 signal input source							
  */
#define __HAL_SYSCON_PCA_CAP2(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP2_SEL, ((__SOURCE__) << SYSCON_PCACR_PCA_CAP2_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)							
						
						
/** @brief Macro to select pca cap1 signal input source from gpio.
  * @param __SOURCE__: source for pca cap1 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: PCA_CH1 alternate function is pca cap1 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is pca cap1 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is pca cap1 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap1 signal input source							
  */
#define __HAL_SYSCON_PCA_CAP1(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP1_SEL, ((__SOURCE__) << SYSCON_PCACR_PCA_CAP1_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)									
						
						
/** @brief Macro to select pca cap0 signal input source from gpio.
  * @param __SOURCE__: source for pca cap0 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: PCA_CH0 alternate function is pca cap0 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is pca cap0 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is pca cap0 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap0 signal input source							
  */
#define __HAL_SYSCON_PCA_CAP0(__SOURCE__)					\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP0_SEL, ((__SOURCE__) << SYSCON_PCACR_PCA_CAP0_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)								
						
						
/** @brief Macro to select timer1 break signal input source from other peripheral.
  * @param __SOURCE__: source for timer1 break signal input
  *          This parameter can be any combination the following values:
	*						@arg	SYSCON_CLKFAILBRKEN: clock fail is timer1 break signal input source			
	*						@arg	SYSCON_DSLPBRKEN: deep sleep is timer1 break signal input source								
  */
#define __HAL_SYSCON_TIM1_BREAKIN_SEL(__SOURCE__)		\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_CLKFAILBRKEN | SYSCON_TIM1CR_DSLPBRKEN, (__SOURCE__));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)												
						

/** @brief Macro to configure timer1 ocxp/ocxnp output signal when break.
  * @param __CONFIG__: config ocxp/ocxnp output signal when break received
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_OCOUT_LOWLEVEL: ocxp/ocxnp output low level when break received 	
	*						@arg	SYSCON_OCOUT_BYTIM1: ocxp/ocxnp output controlled by timer1 configuration when break received 					
  */
#define __HAL_SYSCON_TIM1_BREAKOUT_CFG(__CONFIG__)		\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1BRKOUTCFG, (__CONFIG__));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)								
						
						
/** @brief Macro to select timer1 etr signal input source from gpio.
  * @param __SOURCE__: source for timer1 etr input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_LOWLEVEL : low level is timer1 etr input source			
	*						@arg	SYSCON_PA1			: PA1 is timer1 etr input source			
	*						@arg	SYSCON_PA2			: PA2 is timer1 etr input source			
	*						@arg	SYSCON_PA3			: PA3 is timer1 etr input source			
	*						@arg	SYSCON_PB4			: PB4 is timer1 etr input source			
	*						@arg	SYSCON_PB5			:	PB5 is timer1 etr input source					
	*						@arg	SYSCON_PC3			:	PC3 is timer1 etr input source					
	*						@arg	SYSCON_PC4			:	PC4 is timer1 etr input source					
	*						@arg	SYSCON_PC5			:	PC5 is timer1 etr input source					
	*						@arg	SYSCON_PC6			:	PC6 is timer1 etr input source					
	*						@arg	SYSCON_PC7			:	PC7 is timer1 etr input source					
	*						@arg	SYSCON_PD1			:	PD1 is timer1 etr input source					
	*						@arg	SYSCON_PD2			:	PD2 is timer1 etr input source					
	*						@arg	SYSCON_PD3			:	PD3 is timer1 etr input source					
	*						@arg	SYSCON_PD4			:	PD4 is timer1 etr input source					
	*						@arg	SYSCON_PD6			:	PD6 is timer1 etr input source							
  */
#define __HAL_SYSCON_TIM1ETR_SEL(__SOURCE__)					\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1ETR_SEL, ((__SOURCE__) << SYSCON_TIM1CR_TIM1ETR_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)							
						

/** @brief Macro to select tim1 ch4 signal input source from gpio.
  * @param __SOURCE__: source for tim1 ch4 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: TIM1_CH4 alternate function is tim1 ch4 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is tim1 ch4 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is tim1 ch4 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch4 signal input source		
	*						@arg	SYSCON_LIRC: LIRC is tim1 ch4 signal input source								
  */
#define __HAL_SYSCON_TIM1CH4IN_SEL(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1CH4IN_SEL, ((__SOURCE__) << SYSCON_TIM1CR_TIM1CH4IN_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)									


/** @brief Macro to select tim1 ch3 signal input source from gpio.
  * @param __SOURCE__: source for tim1 ch3 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: TIM1_CH3 alternate function is tim1 ch3 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is tim1 ch3 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is tim1 ch3 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch3 signal input source		
	*						@arg	SYSCON_LIRC: LIRC is tim1 ch3 signal input source								
  */
#define __HAL_SYSCON_TIM1CH3IN_SEL(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1CH3IN_SEL, ((__SOURCE__) << SYSCON_TIM1CR_TIM1CH3IN_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)							
						

/** @brief Macro to select tim1 ch2 signal input source from gpio.
  * @param __SOURCE__: source for tim1 ch2 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: TIM1_CH2 alternate function is tim1 ch2 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is tim1 ch2 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is tim1 ch2 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch2 signal input source		
	*						@arg	SYSCON_LIRC: LIRC is tim1 ch2 signal input source								
  */
#define __HAL_SYSCON_TIM1CH2IN_SEL(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1CH2IN_SEL, ((__SOURCE__) << SYSCON_TIM1CR_TIM1CH2IN_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)				

						
/** @brief Macro to select tim1 ch1 signal input source from gpio.
  * @param __SOURCE__: source for tim1 ch1 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: TIM1_CH1 alternate function is tim1 ch1 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is tim1 ch1 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is tim1 ch1 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch1 signal input source		
	*						@arg	SYSCON_LIRC: LIRC is tim1 ch1 signal input source								
  */
#define __HAL_SYSCON_TIM1CH1IN_SEL(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1CH1IN_SEL, ((__SOURCE__) << SYSCON_TIM1CR_TIM1CH1IN_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)							
						
	
/** @brief Macro to select timer2 etr signal input source from gpio.
  * @param __SOURCE__: source for timer2 etr input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_LOWLEVEL : low level is timer1 etr input source			
	*						@arg	SYSCON_PA1			: PA1 is timer1 etr input source			
	*						@arg	SYSCON_PA2			: PA2 is timer1 etr input source			
	*						@arg	SYSCON_PA3			: PA3 is timer1 etr input source			
	*						@arg	SYSCON_PB4			: PB4 is timer1 etr input source			
	*						@arg	SYSCON_PB5			:	PB5 is timer1 etr input source					
	*						@arg	SYSCON_PC3			:	PC3 is timer1 etr input source					
	*						@arg	SYSCON_PC4			:	PC4 is timer1 etr input source					
	*						@arg	SYSCON_PC5			:	PC5 is timer1 etr input source					
	*						@arg	SYSCON_PC6			:	PC6 is timer1 etr input source					
	*						@arg	SYSCON_PC7			:	PC7 is timer1 etr input source					
	*						@arg	SYSCON_PD1			:	PD1 is timer1 etr input source					
	*						@arg	SYSCON_PD2			:	PD2 is timer1 etr input source					
	*						@arg	SYSCON_PD3			:	PD3 is timer1 etr input source					
	*						@arg	SYSCON_PD4			:	PD4 is timer1 etr input source					
	*						@arg	SYSCON_PD6			:	PD6 is timer1 etr input source							
  */
#define __HAL_SYSCON_TIM2ETR_SEL(__SOURCE__)					\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2ETR_SEL, ((__SOURCE__) << SYSCON_TIM2CR_TIM2ETR_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)	

						
/** @brief Macro to select tim2 ch4 signal input source from gpio.
  * @param __SOURCE__: source for tim2 ch4 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: TIM2_CH4 alternate function is tim2 ch4 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is tim2 ch4 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is tim2 ch4 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch4 signal input source		
	*						@arg	SYSCON_LIRC: LIRC is tim2 ch4 signal input source								
  */
#define __HAL_SYSCON_TIM2CH4IN_SEL(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2CH4IN_SEL, ((__SOURCE__) << SYSCON_TIM2CR_TIM2CH4IN_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)	
	

/** @brief Macro to select tim2 ch3 signal input source from gpio.
  * @param __SOURCE__: source for tim2 ch3 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: TIM2_CH3 alternate function is tim2 ch3 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is tim2 ch3 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is tim2 ch3 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch3 signal input source		
	*						@arg	SYSCON_LIRC: LIRC is tim2 ch3 signal input source								
  */
#define __HAL_SYSCON_TIM2CH3IN_SEL(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2CH3IN_SEL, ((__SOURCE__) << SYSCON_TIM2CR_TIM2CH3IN_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)							
						
						
/** @brief Macro to select tim2 ch2 signal input source from gpio.
  * @param __SOURCE__: source for tim2 ch2 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: TIM2_CH2 alternate function is tim2 ch2 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is tim2 ch2 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is tim2 ch2 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch2 signal input source		
	*						@arg	SYSCON_LIRC: LIRC is tim2 ch2 signal input source								
  */
#define __HAL_SYSCON_TIM2CH2IN_SEL(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2CH2IN_SEL, ((__SOURCE__) << SYSCON_TIM2CR_TIM2CH2IN_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)							
						
						
/** @brief Macro to select tim2 ch1 signal input source from gpio.
  * @param __SOURCE__: source for tim2 ch1 input
  *          This parameter can be one of the following values:
	*						@arg	SYSCON_DEFAULT: TIM2_CH1 alternate function is tim2 ch1 signal input source			
	*						@arg	SYSCON_UART0_RXD: UART0_RXD alternate function is tim2 ch1 signal input source		
	*						@arg	SYSCON_UART1_RXD: UART1_RXD alternate function is tim2 ch1 signal input source	
	*						@arg	SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch1 signal input source		
	*						@arg	SYSCON_LIRC: LIRC is tim2 ch1 signal input source								
  */
#define __HAL_SYSCON_TIM2CH1IN_SEL(__SOURCE__)				\
						do{												  					\
							__HAL_SYSCON_REGWR_UNLOCK(); 				\
							MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2CH1IN_SEL, ((__SOURCE__) << SYSCON_TIM2CR_TIM2CH1IN_SEL_Pos));	\
							__HAL_SYSCON_REGWR_LOCK();	  			\
						}while(0U)								
						
/**
  * @}
  */ 


/**
  * @}
  */ /* End of group SYSCON */

#ifdef __cplusplus
}
#endif

#endif /* __CX32L003_HAL_SYSCON_H */

