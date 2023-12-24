#include "stm32f4xx.h"
int main (){
	__HAL_RCC_GPIOB_CLK_ENABLE();  //enable clock of port B GPIOB
	GPIO_InitTypeDef LED ;
	LED.Mode= GPIO_MODE_OUTPUT_PP ;
	LED.Pin= GPIO_PIN_2 ;
	HAL_GPIO_Init(GPIOB, &LED);
	
	GPIO_InitTypeDef PushButton ;
	PushButton.Mode= GPIO_MODE_INPUT ;
	PushButton.Pin= GPIO_PIN_0 ;
	HAL_GPIO_Init(GPIOB, &PushButton);
	
	GPIO_PinState state ;
	while (1) { 
		state = HAL_GPIO_ReadPin ( GPIOB, GPIO_PIN_0 ) ;
		if(state)
		{ HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);}
		else 
		{ HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);}
            }
	     }
