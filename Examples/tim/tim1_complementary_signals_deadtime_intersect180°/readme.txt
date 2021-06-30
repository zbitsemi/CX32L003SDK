/**
  @page tim_complementary_signals TIM timer complementary singals output function example
  
  @verbatim
  ******************************************************************************
  * @file    tim/tim_complementary_signals/readme.txt 
  * @author  MCU Software Team
  * @version V1.2.0
  * @date    13-Nov-2019
  * @brief   Description of the TIM complementary signals function example.
  ******************************************************************************
  @endverbatim

@par Hardware and Software environment

  - This example runs on CX32L003 devices.
    
  - This example has been tested with CX32L003-StarterKit board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example   
 - TIM1_CH1-PD4(J5.1), TIM1_CH1N-PD5(J5.2), TIM1_CH2-PD6(J5.3), TIM1_CH2N-PA1(J5.5),  will output PWM complementary wave.
 - void Output_Pulse_Numble(uint32_t Numble) can output Specifies the number of pulses.
 */
