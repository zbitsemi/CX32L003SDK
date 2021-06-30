/**
  @page basetim_gate BASETIM gate example
  
  @verbatim
  ******************************************************************************
  * @file    basetim/basetim_gate/readme.txt 
  * @author  MCU Software Team
  * @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Description of the BASETIM gate example.
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
 - Pull down PC5 to enable base timer counter, then interrupt will be generated.   
 - PC's uart terminal will receive message from CX32L003.
 - LED will flash every 1 second. 
 */
