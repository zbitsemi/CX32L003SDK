/**
  @page uart_interrupt_transmit_receive_parity UART interrupt transmit and receive with parity example
  
  @verbatim
  ******************************************************************************
  * @file    uart/uart_interrupt_transmit_receive_parity/readme.txt 
  * @author  MCU Software Team
  * @version V1.0.0
  * @date    17-Sep-2019
  * @brief   Description of the UART interrupt transmit and receive with parity example.
  ******************************************************************************
  @endverbatim

@par Hardware and Software environment

  - This example runs on CX32L003 devices.
    
  - This example has been tested with CX32L003-StarterKit board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Connect RXD(PA1-J5.5), TXD(PA2-J5.6), GND(J5.7) to PC's rs232 converter.
 - Open uart standard terminal and set baudrate 9600, 9bit, odd parity check. 
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example 
 - PC's uart terminal will receive message "ABCDEFGHI" from CX32L003.
 - PC send message 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A to CX32L003 StarterKit.
 - When CX32L003 receive 10 charactors, it will finish receiving then send received datas back. 
 */
