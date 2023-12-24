//Tarek Mohamed Rashad 	Sec1 	B.N43
//Fatma Hussain Wageeh 	Sec2	B.N8

#include "GPIO.h"
#include "dma.h"
#include "Keypad.h"

unsigned int src[Arr_Size];
unsigned int dest[Arr_Size];
char *txt;
int state = 1;

int main(void) {

  //initialize the source array
  for(unsigned char i=0; i<100; i++)
  {
	  src[i] = 100 *(i+1);
  }

  //GPIO Configurations
  GPIO_EnableClock(0);
  GPIO_Init(0, 0, OUTPUT , PUSH_PULL);
  GPIO_Init(0, 5, OUTPUT , PUSH_PULL);

  //DMA2_S0 position is 56 and that's on NVIC_ISER1 pin (56-32) 24
  NVIC_ISER_Config(1,24);

  //DMA Configurations
  //DMA clock enable
  DMA_EnableClock (2);

  //initializes Stream0
  Stream0_Init(src, dest , 0 , VERY_HIGH , M_M , Arr_Size , FULL_WORD , BURST ,FIFO);

  Stream0_enable();

  //UART Configurations
  UART_EnableClock(); //enables UART clock

  GPIO_Init(0, 2, ALTERNATE_FUN, PUSH_PULL);

  GPIO_Init(0, 3, ALTERNATE_FUN, PUSH_PULL);

  UART_Pin_Config();

  UART_Data_Transmit(txt);

  while (1);
  return 0;
}

int compare(unsigned int* srcc, unsigned int* destt)
{
	for(int i; i<100; i++)
	{
		if(srcc[i] == destt[i]);
		else
		{
			state = 0;
		}
	}
	return state;
}


void callout_notif(void)
{
	//compare both arrays to check if the transfere is successful
	unsigned int comp = compare(src,dest);
	if (comp == 1)
	{
//		GPIO_WritePin(0,0,1);
		txt = "Copied Successfully";
	}

	else
	{
//		GPIO_WritePin(0,5,1);
		txt = "Copying failed";
	}

	unsigned int status = check_state();
	unsigned int tc_bit = (status & (1 << 0)) >> 0;
	unsigned int te_bit = (status & (1 << 1)) >> 1;
	if (tc_bit)
	{
		//transfere complete blue led
		GPIO_WritePin(0,0,1);
	}

	if (te_bit)
	{
		// transfere error red led
		GPIO_WritePin(0,5,1);
	}

}











void delay30ms() {
  unsigned int i;
  for (i = 0; i < 30000; i++) {
  }
}
