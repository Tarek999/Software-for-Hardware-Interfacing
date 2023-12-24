#include "GPIO.h"
#include "stm32f401cc_interface.h"

int main(void) {


	GPIO_Init('B', 3, INPUT , PUSH_PULL);
	GPIO_Init('B', 5, OUTPUT, PUSH_PULL);
	GPIO_Init('B', 6, OUTPUT, PUSH_PULL);
	GPIO_Init('B', 7, OUTPUT, PUSH_PULL);
	GPIOB_PUPDR |= 1<<(2*3);


	 int delay ;                                                       // variable for delay
	 int color = 0 ;
	    unsigned int Pushbutton_value ;                                   // variable detecting the value of push button input

	      while (1) {
	    	  for(delay = 0 ; delay<50000 ;delay++)                          //check if the button is pressed for 50ms
	    	                  {
	    		  Pushbutton_value = GPIO_ReadPin('B', 3);
	    	                      if(Pushbutton_value == 1)
	    	                    	  break;
	    	                  }

	    	  if(Pushbutton_value == 0)
	    	          {
	    	              	  color++;

									GPIO_WritePin('B', 5, color&1);
									GPIO_WritePin('B', 6, (color>>1)&1);
									GPIO_WritePin('B', 7, (color>>2)&1);

	    	          }

	    	          while(Pushbutton_value == 0)
	    	          {
	    	        	  Pushbutton_value = GPIO_ReadPin('B', 3);
	    	          }

	                  }


}











