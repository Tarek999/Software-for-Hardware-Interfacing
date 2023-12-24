/*
 * Author : Abdullah Drwesh
 * Date   : 8/12/2021
 * Version: 1.0.0
 */
#include "Keypad.h"
#include "GPIO.h"
//#include "stm32f401cc_interface.h"
unsigned char key_state=0;
unsigned char buttons[4][3] = {{1,2,3},{4,5,6},{7,8,9},{0,0,0}};
unsigned char pressed_key;
unsigned char row, col;

void KEYPAD_Init(void)
{

	for(row=0; row<=3;row++)
	{
		GPIO_Init(1 ,row,INPUT,PULL_UP);
	}
	for(col=5; col<=7;col++)
	{
		GPIO_Init(1,col,OUTPUT,PUSH_PULL);
	}
}


void KEYPAD_Manage(void)
{
	if(key_state==0)
	{
		for(col=5; col<=7;col++)
		{
			GPIO_WritePin(1,col,0);
			for(row=0; row<=3;row++)
			{
				if(GPIO_ReadPin(1,row)==0)
				{
					for(int i; i<2500; i++){}
					if(GPIO_ReadPin(1,row)==0)
					{
						key_state=1;
						pressed_key= buttons[row][col-5];
						KEYPAD_Callouts_KeyPressNotificaton();

					}
				}
			}
			GPIO_WritePin(1,col,1);
		}
	}

}


char KEYPAD_GetKey()
{
	unsigned char key;
	if(key_state==1)
	{
		key_state=0;
		key=pressed_key;
		return key;
	}
	else
	{
		return -1;
	}
}

