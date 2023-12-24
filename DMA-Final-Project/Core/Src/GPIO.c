/*
 * Author : Abdullah Drwesh
 * Date   : 7/12/2021
 * Version: 1.0.0
 */

#include "GPIO.h"

//#include "stm32f401cc_interface.h"

#define _OUTTYPE_MASK ((unsigned char)0x01)
#define _OUTTYPE_SHIFT 0

#define _PUPD_MASK ((unsigned char)0x06)
#define _PUPD_SHIFT 1

unsigned int * edge[2]= {EXTI_FTSR,EXTI_RTSR} ;
unsigned int * interr_pin[4] = {SYSCFG_EXTICR1, SYSCFG_EXTICR2, SYSCFG_EXTICR3,SYSCFG_EXTICR4};
unsigned int * NVIC_ISER[5]= {NVIC_ISER0, NVIC_ISER1,NVIC_ISER2,NVIC_ISER3,NVIC_ISER4};
unsigned int * enable[2]= {GPIOA_RCC,GPIOB_RCC} ;
unsigned int * lookup[2][10] = {{GPIOA_MODER,GPIOA_OTYPER,GPIOA_OSPEEDR,GPIOA_PUPDR,GPIOA_IDR,GPIOA_ODR,GPIOA_BSRR,GPIOA_LCKR,GPIOA_AFRL,GPIOA_AFRH},
								{GPIOB_MODER,GPIOB_OTYPER,GPIOB_OSPEEDR,GPIOB_PUPDR,GPIOB_IDR,GPIOB_ODR,GPIOB_BSRR,GPIOB_LCKR,GPIOB_AFRL,GPIOB_AFRH}} ;

void GPIO_EnableClock(unsigned int PortID)
{

	*enable[PortID] |= (0x01 << PortID);

}

void SYSCFG_EnableClock(void)
{

	*RCC_APB2ENR |= (0x01 << 14);

}


void UART_EnableClock(void)
{

	*RCC_APB1ENR |= (0x01 << 17);

}


void UART_Pin_Config(void)
{
	//enable transmit
	*USART_CR1 |= (0x01<<3);

	//USART enable
	*USART_CR1 |= (0x01<<13);

	//transmit 8 bit
	*USART_CR1 &= ~(0x01<<12);

	//oversampling 16 bit
	*USART_CR1 &= ~(0x01<<15);

	//stopbit
	*USART_CR2 &= ~(3<<12);
//	*USART_CR2 &= ~(0x03<<12);

	//Baud rate from the equation
	*USART_BRR = 0x683;

	*GPIOA_AFRL |= (0x07<<4*2);


}

void UART_Data_Transmit(const char* x)
{
	for (unsigned int i=0; x[i]!='\0'; i++)

	{
		*USART_DR=x[i];
		while(((*USART_SR&(0x01<<6))>>6)==0)
		{

		}
	}
}

void INTERRUPT_Pin_Config(unsigned int edge_case)
{

//	*interr_pin[PinNum] |= (0x01 << PortID);
	*SYSCFG_EXTICR1 |= (0x00); //EXTI0

	*EXTI_IMR |= (0x01 << 0);

	*edge[edge_case] |= (0x01 << 0);

//	*EXTI_PR |= (0x01 << PinNum);

}


void NVIC_ISER_Config(unsigned int REG, unsigned char PinNum)
{

	*NVIC_ISER[REG] = (0x01 << PinNum );

}



void GPIO_Init(unsigned int PortID, unsigned char PinNum, unsigned char PinMode,
               unsigned char DefaultState)
{
	//MODER
	*lookup[PortID][0] &= ~(0x03 << 2 * PinNum);
	*lookup[PortID][0] |= PinMode << 2 * PinNum;

	//OTYPER
	*lookup[PortID][1] &= ~(1 << PinNum);
	*lookup[PortID][1] |= ((DefaultState & _OUTTYPE_MASK) >> _OUTTYPE_SHIFT) << PinNum;

	//PUPDR
	*lookup[PortID][3] &= ~(0x03 << 2 * PinNum);
	*lookup[PortID][3] |= ((DefaultState & _PUPD_MASK) >> _PUPD_SHIFT) << (2 * PinNum);

}

unsigned char GPIO_WritePin(unsigned int PortID, unsigned char PinNum,
                            unsigned char Data)
{

	unsigned char result;
    if (((*lookup[PortID][0] & (0x03 << 2 * PinNum)) >> (2 * PinNum)) == 1) {
      if (Data) {
    	  *lookup[PortID][5] |= (1 << PinNum);
      } else {
    	  *lookup[PortID][5] &= ~(1 << PinNum);
      }
      result = OK;
    } else {
      result = NOK;
    }

    return result;
}

unsigned char GPIO_ReadPin(unsigned int PortID, unsigned char PinNum)

{
	unsigned char data;
	data = (*lookup[PortID][4] & (1 << PinNum)) >> PinNum;
	return data;
}
