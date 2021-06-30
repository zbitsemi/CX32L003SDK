/**
  @page iwdg_example
  
  @verbatim
  ******************************************************************************
  * @file    iwdg\iwdg_application_example\readme.txt 
  * @author  MCU Software Team
  * @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Description of the iwdg example.
  ******************************************************************************
  @endverbatim

@par Hardware and Software environment

  - This example runs on CX32L003 devices.
    
  - This example has been tested with CX32L003-StarterKit board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Connect RXD(J10.1), TXD(J10.2), GND(J10.3) to PC's rs232 converter.
 - Open uart standard terminal and set baudrate 9600, 8bit, no parity check. 
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
 - PC's uart terminal will receive message from CX32L003. 
 */
 
 case 0: Test to refresh the independent watchdog counter
 (1)set :#define IWDG_TEST_MODE		IWDG_REFRESH_DOG
 (2)can you see print from UART when start:
	Printf success using UART1, PD5-TXD, PD6-RXD
	Test IWDG RESET ,NO RESET!
	Enter Test IWDG refresh
 (3)You can't see "INT happen" from UART.If you see it ,it is error.
 (4)You can see led Toggle Each ~2.6 seconds
 
case 1: Test interrupt 
 (1)set :#define IWDG_TEST_MODE		IWDG_REFRESH_INTERRUPT
 (2)can you see print from UART when start:
	Printf success using UART1, PD5-TXD, PD6-RXD
	Test IWDG RESET ,NO RESET!
	Enter Test IWDG Interrupt
 (3)You can see print from UART(Interrupt count).
	INT 1
	INT 2
	INT 3
	.......
 (4)You can see led Toggle Each ~2.7 seconds
 
 case 2: Test  reset
 (1)set :#define IWDG_TEST_MODE		IWDG_REFRESH_RESET
 (2)You can see print from UART when start:
	Printf success using UART1, PD5-TXD, PD6-RXD
	Test IWDG RESET ,NO RESET!
	Enter Test IWDG RESET ,wait 5S
 (3)You can see print from UART(Each ~2.7S+5S seconds reset).
	Printf success using UART1, PD5-TXD, PD6-RXD
	Test IWDG RESET ,HAVE RESET!!!!
	Enter Test IWDG RESET ,wait 5S
 