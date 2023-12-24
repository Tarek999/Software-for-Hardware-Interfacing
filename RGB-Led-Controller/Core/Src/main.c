#include "stm32f401cc_interface.h"


int main(void) {

  	RCC_AHB1ENR |= (1 << 1) ;                                                   // Enable peripheral register port B
    GPIOB_MODER &= ~(0x03<<(2*3));	                                            // pin 3 input
    GPIOB_MODER &= ~((0x03<<(2*5))|(0x03<<(2*6))|(0x03<<(2*7)));                // reset pins (5,6,7)
	GPIOB_MODER |= (0x01<<(2*5))|(0x01<<(2*6))|(0x01<<(2*7)); 					// LED Pins (5,6,7) output
	GPIOB_OTYPER &= ~((0x03<<5)|(0x01<<6)|(0x01<<7)); 							// Pins output type (5,6,7) Push-Pull
    GPIOB_PUPDR &= ~(0x03<<(2*3));                                              // reset pin 3
	GPIOB_PUPDR |= (0x01<<(2*3));                                               // pin 3 pull up (active low)


    int delay ;                                                       // variable for delay
    unsigned int Pushbutton_value ;                                   // variable detecting the value of push button input

      while (1) {
    	  for(delay = 0 ; delay<50000 ;delay++)                          //check if the button is pressed for 50ms
    	                  {
    		  Pushbutton_value = ((GPIOB_IDR>>3)&1);
    	                      if(Pushbutton_value == 1)
    	                    	  break;
    	                  }

    	  if(Pushbutton_value == 0)
    	          {


    	                  if(((GPIOB_ODR>>5)&7) <7)
    	                  {
    	                      GPIOB_ODR+=1<<5;
    	                  }
    	                  else
    	                  {
    	                      GPIOB_ODR&=~(7<<5);
    	                  }

    	          }

    	          while(Pushbutton_value == 0)
    	          {
    	        	  Pushbutton_value = ((GPIOB_IDR>>3)&1);
    	          }

                  }

}


