/*
 * Author : Abdullah Drwesh
 * Date   : 8/12/2021
 * Version: 1.0.0
 */

#ifndef KEYPAD_H
#define KEYPAD_H


void KEYPAD_Init(void);
void KEYPAD_Manage(void);
char KEYPAD_GetKey(void);
void KEYPAD_Callouts_KeyPressNotificaton(void);
void delay30ms();


#endif /* KEYPAD_H */

