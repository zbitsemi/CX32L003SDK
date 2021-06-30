/**
  @page lpuart_polling_transmit_receive LPUART polling transmit and receive example
  
  @verbatim
  ******************************************************************************
  * @file    lpuart/lpuart_polling_transmit_receive/readme.txt 
  * @author  MCU Software Team
  * @version V1.0.0
  * @date    21-Oct-2019
  * @brief   Description of the LPUART polling transmit and receive example.
  ******************************************************************************
  @endverbatim

@par Hardware and Software environment

  - This example runs on CX32L003 devices.
    
  - This example has been tested with CX32L003-StarterKit board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Connect RXD(PA3-J5.10), TXD(PC5-J6.6), GND(J5.7) to PC's rs232 converter.
 - Open uart standard terminal and set baudrate 9600, 8bit, no parity check. 
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example 
 - PC's uart terminal will receive message "ABCDEFGHI" from CX32L003.
 - PC send message 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A to CX32L003 StarterKit.
 - When CX32L003 receive 10 charactors, it will finish receiving then send received datas back. 
 */
