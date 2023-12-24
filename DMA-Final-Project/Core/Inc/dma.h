//Tarek Mohamed Rashad 	Sec1 	B.N43
//Fatma Hussain Wageeh 	Sec2	B.N8


#ifndef DMA_H
#define DMA_H

#define DMA_REG(Base_Address,Offset) ((unsigned int*)(Base_Address+Offset))

// DMA Base Address
#define DMA2 (0x40026400)
#define DMA1 (0x40026000)

// RCC address to enable DMA pin 22 for dma2 pin 21 form dma1
#define RCC_AHB1ENR (DMA_REG(0x40023800,0x30))

//Interrupts for both DMAs
#define DMA1_LISR (DMA_REG(DMA1, 0x0000))
#define DMA2_LISR (DMA_REG(DMA2, 0x0000))

#define DMA1_HISR (DMA_REG(DMA1, 0x0004))
#define DMA2_HISR (DMA_REG(DMA2, 0x0004))

#define DMA1_LIFCR (DMA_REG(DMA1, 0x0008))
#define DMA2_LIFCR (DMA_REG(DMA2, 0x0008))

#define DMA1_HIFCR (DMA_REG(DMA1, 0x000C))
#define DMA2_HIFCR (DMA_REG(DMA2, 0x000C))


// Stream0 registers for both DMAs

#define DMA1_S0CR (DMA_REG(DMA1, 0x0010))
#define DMA2_S0CR (DMA_REG(DMA2, 0x0010))

#define DMA1_S0NDTR (DMA_REG(DMA1, 0x0014))
#define DMA2_S0NDTR (DMA_REG(DMA2, 0x0014))

#define DMA1_S0PAR (DMA_REG(DMA1, 0x0018))
#define DMA2_S0PAR (DMA_REG(DMA2, 0x0018))

#define DMA1_S0M0AR (DMA_REG(DMA1, 0x001C))
#define DMA2_S0M0AR (DMA_REG(DMA2, 0x001C))

#define DMA1_S0M1AR (DMA_REG(DMA1, 0x0020))
#define DMA2_S0M1AR (DMA_REG(DMA2, 0x0020))

#define DMA1_S0FCR (DMA_REG(DMA1, 0x0024))
#define DMA2_S0FCR (DMA_REG(DMA2, 0x0024))

//define the macros

#define Arr_Size ((int)100)

//direction of transaction (0 = p-->m ,1 = m-->p, 2 = m-->m )
#define P_M ((unsigned char)0x00)
#define M_P ((unsigned char)0x01)
#define M_M ((unsigned char)0x02)

//Data size for both memory and peripheral (0=byte, 1= 16-bit, 2 = 32 bit)
#define BYTE ((unsigned char)0x00)
#define HALF_WORD ((unsigned char)0x01)
#define FULL_WORD ((unsigned char)0x02)

// type 0 for single and 1 for burst
#define SINGLE ((unsigned char)0x00)
#define BURST ((unsigned char)0x01)

// mode 0 for direct and 1 for FIFO
#define DIR ((unsigned char)0x00)
#define FIFO ((unsigned char)0x01)


//priority (0 = low ,1 = medium, 2 = high, 3= very high )
#define LOW ((unsigned char)0x00)
#define MED ((unsigned char)0x01)
#define HIGH ((unsigned char)0x02)
#define VERY_HIGH ((unsigned char)0x03)



//Declarations of dma.c functions
void DMA_EnableClock (unsigned int DMA_ID);

void Stream0_Init(unsigned int* src, unsigned int* dest , int channel_id, int direction, int priority ,int items_num, int item_size,int type,int mode );

void Stream0_enable(void);

void callout_notif(void);

unsigned int check_state(void);

int compare(unsigned int* src, unsigned int* dest);


#endif /* DMA_H */
