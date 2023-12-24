//Tarek Mohamed Rashad 	Sec1 	B.N43
//Fatma Hussain Wageeh 	Sec2	B.N8


#include "dma.h"
#include "GPIO.h"

void DMA_EnableClock (unsigned int DMA_ID)
{
	// pin 21 for dma1, pin 22 for dma2
	*RCC_AHB1ENR |= (1<< (20+DMA_ID));
}

void Stream0_Init(unsigned int* srcc, unsigned int* destt , int channel_id, int priority ,int direction, int items_num, int item_size, int type, int mode )
{
	int disable_pin = (*DMA2_S0CR & (1 << 0)) >> 0 ;
	// if the pin is high write low to it
	if(disable_pin == 1)
	{
		*DMA2_S0CR &= ~(1<<0);
		/* Wait until EN bit is cleared */
		while(disable_pin == 1);
	}

	//Enable DMA transfer complete interrupt TCIE
	*DMA2_S0CR |= (1<<4);

	//Enable DMA transfer error interrupt TEIE
	*DMA2_S0CR |= (1<<2);

	//Set DMA as flow control
	*DMA2_S0CR &= ~(1<<5);

	//configure priority to very high put (1 0) in pin 16 and 17
	*DMA2_S0CR |= (priority<<16);

	//address increment for p and m PINC, MINC
	*DMA2_S0CR |= (1<<9);
	*DMA2_S0CR |= (1<<10);

	//load the data to peripheral and memory
	*DMA2_S0PAR= (unsigned int) srcc;
	*DMA2_S0M0AR= (unsigned int) destt;

	//total number of items
	*DMA2_S0NDTR = items_num;

	//Select channel from 0 to 7 in pins 25,26,27
	*DMA2_S0CR |= (channel_id<<25);

	//direction of transaction (0 = p-->m ,1 = m-->p, 2 = m-->m )
	*DMA2_S0CR |= (direction<<6);

	//Data size for both memory and peripheral (0=byte, 1= 16-bit, 2 = 32 bit)
	*DMA2_S0CR |= (item_size<<11);
	*DMA2_S0CR |= (item_size<<13);

	// type 0 for single and 1 for burst
	if (type == 1)
	{
		//burst transfer configuration inc4
		*DMA2_S0CR |= (1<<23);
		*DMA2_S0CR |= (1<<21);
	}
	else
	{
		//single mood
		*DMA2_S0CR &= ~(1<<23);
		*DMA2_S0CR &= ~(1<<21);
	}
	//if direction=2 or type=1 3shan fel m-->m lazem a3mel fifo mode
	if ((direction == 2) || (mode == 1))
	{
		// disable direct mode
		*DMA2_S0FCR |= (1<<2);

		//FIFO threshold to full fifo
		*DMA2_S0FCR |= (3<<0);
	}

	else
	{
		// enable direct mode
		*DMA2_S0FCR &= ~(1<<2);
	}
}

void Stream0_enable(void)
{
	*DMA2_S0CR |= (1<<0);
}


unsigned int check_state(void)
{
	unsigned int state =0 ;
	unsigned int tc = (*DMA2_LISR & (1 << 5)) >> 5;
	unsigned int te = (*DMA2_LISR & (1 << 3)) >> 3;

	state |= (tc<<0);
	state |= (te<<1);

	return state;
}

void DMA2_Stream0_IRQHandler(void)
{

	callout_notif();
	*DMA2_LIFCR |= (1<<5);
	*DMA2_LIFCR |= (1<<3);
}
