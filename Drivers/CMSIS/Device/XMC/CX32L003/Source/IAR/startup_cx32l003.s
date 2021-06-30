/**
  ******************************************************************************
    PLACEHOLDER for CMSIS-CORE Startup Device Assembler File 
    for the LPC1800 Series for the IAR Compiler Toolchain
  ******************************************************************************  
  */ 
  
        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler                  ; Reset Handler

        DCD     NMI_Handler                    ; NMI Handler
        DCD     HardFault_Handler              ; Hard Fault Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     SVC_Handler                    ; SVCall Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     PendSV_Handler                 ; PendSV Handler
        DCD     SysTick_Handler                ; SysTick Handler

        ; External Interrupts
        DCD     GPIOA_IRQHandler          ; GPIOA_IRQn          = 0,
        DCD     GPIOB_IRQHandler          ; GPIOB_IRQn          = 1,
        DCD     GPIOC_IRQHandler          ; GPIOC_IRQn          = 2,
        DCD     GPIOD_IRQHandler          ; GPIOD_IRQn          = 3,
		DCD     FLASH_IRQHandler          ; FLASH_IRQHandler    = 4,
		DCD     0                         ; Reserved--------------5,
        DCD     UART0_IRQHandler          ; UART0_IRQn          = 6,
        DCD     UART1_IRQHandler          ; UART1_IRQn          = 7,
		DCD     LPUART_IRQHandler         ; LPUART_IRQn			= 8,
		DCD     0                         ; Reserved--------------9,
        DCD     SPI_IRQHandler       	  ; SPI_IRQn       	    = 10,
        DCD     0                         ; Reserved--------------11,
        DCD     I2C_IRQHandler            ; I2C0_IRQn           = 12,
        DCD     0                         ; Reserved--------------13,
        DCD     TIM10_IRQHandler          ; TIM10_IRQn          = 14,
        DCD     TIM11_IRQHandler          ; TIM11_IRQn          = 15,
		DCD     LPTIM_IRQHandler          ; LPTIMER_IRQn        = 16,
		DCD     0                         ; Reserved--------------17,
        DCD     TIM1_IRQHandler           ; ADVTIM1             = 18,
		DCD     TIM2_IRQHandler        	  ; ADVTIM2---------------19,
		DCD     0                         ; Reserved--------------20,
        DCD     PCA_IRQHandler            ; PCA_IRQn            = 21,
        DCD     WWDG_IRQHandler           ; WWDT_IRQn           = 22,
        DCD     IWDG_IRQHandler           ; IWDT_IRQn           = 23,
        DCD     ADC_IRQHandler            ; ADC_IRQn            = 24,
		DCD     LVD_IRQHandler            ; LVD_IRQn            = 25,
		DCD     VC_IRQHandler             ; VC_IRQn             = 26,
		DCD     0                         ; Reserved--------------27,
		DCD     AWK_IRQHandler            ; AWK_IRQn            = 28,
		DCD     OWIRE_IRQHandler          ; OWIRE_IRQn          = 29,
        DCD     RTC_IRQHandler     		  ; RTC_MATCH0_IRQn     = 30,
        DCD     CLKTRIM_IRQHandler        ; CLKTRIM_IRQn        = 31 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0
        
        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler

		PUBWEAK GPIOA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPIOA_IRQHandler
        B GPIOA_IRQHandler
		
		PUBWEAK GPIOB_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPIOB_IRQHandler
        B GPIOB_IRQHandler
		
		PUBWEAK GPIOC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPIOC_IRQHandler
        B GPIOC_IRQHandler
		
		PUBWEAK GPIOD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPIOD_IRQHandler
        B GPIOD_IRQHandler
		
		PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler	
		
		PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART0_IRQHandler
        B UART0_IRQHandler
		
		PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART1_IRQHandler
        B UART1_IRQHandler
		
		PUBWEAK LPUART_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPUART_IRQHandler
        B LPUART_IRQHandler
		
		PUBWEAK SPI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI_IRQHandler
        B SPI_IRQHandler
		
		PUBWEAK I2C_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C_IRQHandler
        B I2C_IRQHandler
		
	    PUBWEAK TIM10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM10_IRQHandler
        B TIM10_IRQHandler
		
	    PUBWEAK TIM11_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM11_IRQHandler
        B TIM11_IRQHandler
		
	    PUBWEAK LPTIM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM_IRQHandler
        B LPTIM_IRQHandler
		
		PUBWEAK TIM1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_IRQHandler
        B TIM1_IRQHandler
		
		PUBWEAK TIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM2_IRQHandler
        B TIM2_IRQHandler
		
		PUBWEAK PCA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PCA_IRQHandler
        B PCA_IRQHandler
		
		PUBWEAK WWDG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDG_IRQHandler
        B WWDG_IRQHandler
		
		PUBWEAK IWDG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IWDG_IRQHandler
        B IWDG_IRQHandler
		
	    PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_IRQHandler
        B ADC_IRQHandler

		PUBWEAK LVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LVD_IRQHandler
        B LVD_IRQHandler
		
		PUBWEAK VC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
VC_IRQHandler
        B VC_IRQHandler

        PUBWEAK AWK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
AWK_IRQHandler
        B AWK_IRQHandler
		
		PUBWEAK OWIRE_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
OWIRE_IRQHandler
        B OWIRE_IRQHandler
		
		PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler
		
		PUBWEAK CLKTRIM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CLKTRIM_IRQHandler
        B CLKTRIM_IRQHandler
		
       

        END
;************************ (C) COPYRIGHT XMC *****END OF FILE*****
