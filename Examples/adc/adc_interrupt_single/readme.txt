/**
  @page adc_interrupt_single ADC single mode example
  
  @verbatim
  ******************************************************************************
  * @file    adc/adc_interrupt_single/readme.txt 
  * @author  MCU Software Team
  * @Version V1.2.0
  * @Date    2021-01-11
  * @brief   Description of the ADC interrupt single example.
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
 - ADC Channel4(PD3-J6.1) will be converted in ADC single mode 
 - PC's uart terminal will receive message from CX32L003. 
 */
