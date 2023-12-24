/*
 * Author : Abdullah Drwesh
 * Date   : 7/12/2021
 * Version: 1.0.0
 */
#include "GPIO.h"


unsigned char sevenSegHex[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                                   0x6D, 0x7D, 0x07, 0x7F, 0x6F};
unsigned char counter=0;

void delay30ms() {
  unsigned int i;
  for (i = 0; i < 30000; i++) {
  }
}

int main(void)
{


  GPIO_EnableClock(0); //enable Port A
  GPIO_EnableClock(1); //enable Port B
  EXTI_EnableClock(); //enables SYSCFG register & APB2 BUS

  GPIO_Init(0, 0, INPUT, PULL_UP);   //for pushbutton 1
  GPIO_Init(0, 1, INPUT, PULL_UP);   //for pushbutton 2

  //7-segment output pins
  for (int i = 0; i < 7; i++)
  {
    GPIO_Init(1, i, OUTPUT, PUSH_PULL);
  }

  EXTI_INIT(0,0); // 0 for EXIT0 ,0 for falling edge
  EXTI_INIT(1,0); // 1 for EXIT1 ,0 for falling edge

//7segment Display
	for (int i = 0; i < 7; i++)
	{
		GPIO_WritePin(1, i, (sevenSegHex[counter] & (1 << i)) >> i);
	}

  while (1)
		for (int i = 0; i < 7; i++)
		{
			GPIO_WritePin(1, i, (sevenSegHex[counter] & (1 << i)) >> i);
		}



  return 0;
}


void INCREMENT(void)
{
	//close interrupt 1 (race condition)
	*EXTI_IMR &= ~(0x01 << 1);

	*EXTI_PR |= (0x01 << 0);

	if (counter==9)
	{
			counter=9;
	}
	else
	{
		counter++;
	}

	//re-open interrupt 1 (race condition)
	*EXTI_IMR |= (0x01 << 1);


}

void DECREMENT(void)
{

	//close interrupt 0 (race condition)
	*EXTI_IMR &= ~(0x01 << 0);

	*EXTI_PR |= (0x01 << 1);
	if (counter==0)
	{
			counter=0;
	}
	else
	{
		counter--;
	}

	//reopen interrupt 1 (race condition)
	*EXTI_IMR |= (0x01 << 0);

}

