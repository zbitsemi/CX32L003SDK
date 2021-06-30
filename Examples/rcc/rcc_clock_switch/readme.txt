/**
  @page rcc_clock_switch RCC CLOCK switch example
  
  @verbatim
  ******************************************************************************
  * @file    rcc/rcc_clock_switch/readme.txt 
  * @author  MCU Software Team
  * @version V1.0.0
  * @date    21-Oct-2019
  * @brief   Description of the RCC CLOCK switch example.
  ******************************************************************************
  @endverbatim

@par Hardware and Software environment

  - This example runs on CX32L003 devices.
    
  - This example has been tested with CX32L003-StarterKit board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Connect RXD(J10.1), TXD(J10.2), GND(J10.3) to PC's rs232 converter.
 - Open serial port standard terminal and set baudrate 9600, 8bit, no parity check. 
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
 - PC's uart terminal will receive message from CX32L003. 
 - Press user button(USR SW1) to trigger clock switch(HIRC->HXT->LIRC->LXT->HIRC.....), led will flash 4 time between switching interval.  
 */
