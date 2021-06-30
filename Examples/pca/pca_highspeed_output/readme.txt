/**
  @page pca_highspeed_output PCA highspeed output compare example
  
  @verbatim
  ******************************************************************************
  * @file    pca/pca_highspeed_output/readme.txt 
  * @author  MCU Software Team
  * @version V1.0.0
  * @date    17-Sep-2019
  * @brief   Description of the PCA highspeed output compare example.
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
 - PD2(J6.2) will output 92Hz sqaure wave.
 - LED will flash every 1 second. 
 */
