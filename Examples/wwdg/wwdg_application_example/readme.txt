/**
  @page wwdg_application_example
  
  @verbatim
  ******************************************************************************
  * @file    wwdg\wwdg_application_example\readme.txt 
  * @author  MCU Software Team
  * @version V1.0.0
  * @date    16-Oct-2019
  * @brief   Description of the wwdg example.
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
 
 case 0: Test to refresh the watchdog reload when counter small window 
 (1)set :#define WWDG_TEST_MODE		WWDG_REFRESH_DOG
 (2)can you see print from UART when start:
	Printf success using UART1, PD5-TXD, PD6-RXD
	Test WWDG RESET ,NO RESET!
	Enter Test IWDG refresh
 (3)You can't see "INT happen" from UART,if you see the print ,it is error..
 (4)You can see led Toggle Each ~2.9 seconds
 
case 1: Test interrupt ,when interrupt to refresh watchdog
 (1)set :#define WWDG_TEST_MODE		WWDG_REFRESH_INTERRUPT
 (2)You can see print from UART when start:
	Printf success using UART1, PD5-TXD, PD6-RXD
	PCLK freq :24000000HZ
	Test WWDG RESET ,NO RESET!
	Enter Test WWDG Interrupt
 (3)You can see print from UART(Interrupt count).
	INT 1
	INT 2
	INT 3
	.......
 (4)You can see led(D2) Toggle Each ~1.7 seconds
 
 case 2: Test reset ： no refresh watchdog
 (1)set :#define WWDG_TEST_MODE		WWDG_UNREFRESH_RESET
 (2)You can see print from UART when start:
	Printf success using UART1, PD5-TXD, PD6-RXD
	PCLK freq :24000000HZ
	Test WWDG RESET ,NO RESET!
	Enter Test WWDG UNREFRESH RESET ,wait 5S
 (3)You can see the print from UART after 1.5S+5S:
	INT 1
 (4)You can see print from UART after  ~1.3S .
	Printf success using UART1, PD5-TXD, PD6-RXD
	PCLK freq :24000000HZ
	Test WWDG RESET ,HAVE RESET!!!!
	Enter Test WWDG UNREFRESH RESET ,wait 5S
 (5)You can see the print from UART after 1.5S+5S:
	INT 1
 (6)You can see (4) and (5) each 3.3S+5S. 
 
 
case 3: Test reset ： refresh watchdog when large window
 (1)set :#define WWDG_TEST_MODE	WWDG_REFRESH_RESET
 (2)You can see print from UART when start:
	Printf success using UART1, PD5-TXD, PD6-RXD
	PCLK freq :24000000HZ
	Test WWDG RESET ,NO RESET!
	Enter Test WWDG REFRESH RESET ,wait 5S
	
 (3)You can see print from UART(Each ~1.2S+5S seconds reset).
	Printf success using UART1, PD5-TXD, PD6-RXD
	PCLK freq :24000000HZ
	Test WWDG RESET ,HAVE RESET!!!!
	Enter Test WWDG REFRESH RESET ,wait 5S
 


 
	
 