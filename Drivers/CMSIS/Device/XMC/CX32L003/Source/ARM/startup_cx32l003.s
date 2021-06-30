;*******************************************************************************
;* File Name          : startup_cx32l003.s
;* Author             : Software Team
;* Version            : V1.0.0
;* Date               : 21-Oct-2019
;* Description        : CX32L003 vector table for MDK-ARM 
;*                      toolchain.  
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure the clock system
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM0+ processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main. 
;*******************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>


; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
; <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
; <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler


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
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
			    LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

				EXPORT  GPIOA_IRQHandler          [WEAK]  ; GPIOA_IRQn          = 0,                                                     
				EXPORT  GPIOB_IRQHandler          [WEAK]  ; GPIOB_IRQn          = 1,                                                     
				EXPORT  GPIOC_IRQHandler          [WEAK]  ; GPIOC_IRQn          = 2,                                                     
				EXPORT  GPIOD_IRQHandler          [WEAK]  ; GPIOD_IRQn          = 3,                                                     
			    EXPORT  FLASH_IRQHandler          [WEAK]  ; FLASH_IRQHandler    = 4,                                                    
				;EXPORT  0                        [WEAK]  ; Reserved--------------5,                                                    
				EXPORT  UART0_IRQHandler          [WEAK]  ; UART0_IRQn          = 6,                                                     
				EXPORT  UART1_IRQHandler          [WEAK]  ; UART1_IRQn          = 7,                                                     
				EXPORT  LPUART_IRQHandler         [WEAK]  ; LPUART_IRQn 		= 8,                                                    
				;EXPORT  0                        [WEAK]  ; Reserved--------------9,                                                    
				EXPORT  SPI_IRQHandler            [WEAK]  ; SPI_IRQn       		= 10,                                                    
				;EXPORT  0                        [WEAK]  ;                                                  
				EXPORT  I2C_IRQHandler            [WEAK]  ; I2C_IRQn            = 12,                                                    
				;EXPORT 0                         [WEAK]  ;                                                   
				EXPORT  TIM10_IRQHandler          [WEAK]  ; TIM10_IRQn          = 14,                                                    
				EXPORT  TIM11_IRQHandler          [WEAK]  ; TIM11_IRQn          = 15,                                                    
				EXPORT  LPTIM_IRQHandler          [WEAK]  ; LPTIMER_IRQn  		= 16,                                                   
				;EXPORT  0                        [WEAK]  ; Reserved--------------17,                                                   
				EXPORT  TIM1_IRQHandler           [WEAK]  ; ADVTIM1             = 18,                                                    
				EXPORT  TIM2_IRQHandler           [WEAK]  ; ADVTIM2				= 19,                                               
				;EXPORT  0                        [WEAK]  ; Reserved--------------20,                                                   
				EXPORT  PCA_IRQHandler            [WEAK]  ; PCA_IRQn            = 21,                                                    
				EXPORT  WWDG_IRQHandler           [WEAK]  ; WWDT_IRQn           = 22,                                                    
				EXPORT  IWDG_IRQHandler           [WEAK]  ; IWDT_IRQn           = 23,                                                    
				EXPORT  ADC_IRQHandler            [WEAK]  ; ADC0_IRQn           = 24,                                                    
				EXPORT  LVD_IRQHandler            [WEAK]  ; LVD_IRQn            = 25,                                                
				EXPORT  VC_IRQHandler             [WEAK]  ; VC_IRQn             = 26,                                                   
				;EXPORT  0                        [WEAK]  ; Reserved--------------27,                                                   
				EXPORT  AWK_IRQHandler            [WEAK]  ; AWK_IRQn    		= 28,                      
				EXPORT  OWIRE_IRQHandler          [WEAK]  ; OWIRE_IRQn    		= 29,                       
				EXPORT  RTC_IRQHandler            [WEAK]  ; RTC_MATCH0_IRQn     = 30,
				EXPORT  CLKTRIM_IRQHandler        [WEAK]  ; CLKTRIM_IRQn        = 31 

                
GPIOA_IRQHandler          ; GPIOA_IRQn          = 0,                                                     
GPIOB_IRQHandler          ; GPIOB_IRQn          = 1,                                                     
GPIOC_IRQHandler          ; GPIOC_IRQn          = 2,                                                     
GPIOD_IRQHandler          ; GPIOD_IRQn          = 3,                                                     
FLASH_IRQHandler          ; FLASH_IRQHandler    = 4,                                                    
;0                         ; Reserved---------------5,                                                    
UART0_IRQHandler          ; UART0_IRQn          = 6,                                                     
UART1_IRQHandler          ; UART1_IRQn          = 7,                                                     
LPUART_IRQHandler         ; LPUART_IRQn 		= 8,                                                    
;0                        ; Reserved---------------9,                                                    
SPI_IRQHandler            ; SPI_IRQHandler      = 10,                                                    
;0                         ; Reserved---------------11,                                                    
I2C_IRQHandler            ; I2C_IRQHandler      = 12,                                                    
;0                         ; Reserved---------------13,                                                 
TIM10_IRQHandler          ; TIMER0_IRQn         = 14,                                                    
TIM11_IRQHandler          ; TIMER1_IRQn         = 15,                                                    
LPTIM_IRQHandler          ; LPTIMER_IRQn  		= 16,                                                   
;0                         ; Reserved---------------17,                                                   
TIM1_IRQHandler           ; ADVTim1_IRQn        = 18,                                                    
TIM2_IRQHandler           ; ADVTim2_IRQn        = 19,                                                     
;0                         ; Reserved---------------20,                                                   
PCA_IRQHandler            ; PCA_IRQn            = 21,                                                    
WWDG_IRQHandler           ; WWDT_IRQn           = 22,                                                    
IWDG_IRQHandler           ; IWDT_IRQn           = 23,                                                    
ADC_IRQHandler            ; ADC_IRQHandler      = 24,                                                    
LVD_IRQHandler            ; LVD_IRQn            = 25,                                                   
VC_IRQHandler             ; VC_IRQn             = 26,                                                     
;0                         ; Reserved---------------27,                                                   
AWK_IRQHandler            ; AWK_IRQn            = 28,                                                 
OWIRE_IRQHandler          ; OWIRE_IRQn          = 29,                        
RTC_IRQHandler            ; RTC_IRQHandler      = 30,    
CLKTRIM_IRQHandler        ; CLKTRIM_IRQn        = 31 
      
                B       .

                ENDP

                ALIGN

; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
