/**
  @page vc application example
  
  @verbatim
  ******************************************************************************
  * @file    vc/vc_application_example/readme.txt 
  * @author  MCU Software Team
  * @version V1.0.0
  * @date    25-Oct-2019
  * @brief   Description of the vc test example.
  ******************************************************************************
  @endverbatim

@par Hardware and Software environment

  - This example runs on CX32L003 devices.
    
  - This example has been tested with CX32L003-StarterKit board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - (option)Connect RXD(J10.1), TXD(J10.2), GND(J10.3) to PC's rs232 converter. 
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
 -
 -If the input voltage in PC5 is higher than 1.25V, the following information will be printed
		"Filter out is Slow"(Every four seconds)
-If the input voltage is less than 1.25V, the following information is printed
 
	"Filter Interrupt!
	Filter out is Hight"
	"Filter out is Hight""(Every four seconds)
NOTE:only low to hight ,Interruption will occur.
	We can adjust the interruption condition by setting
	

 */
