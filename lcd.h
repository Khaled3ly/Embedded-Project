#ifndef lcd_H_  
#define lcd_H_
#include "Drivers.h"
#include "tm4c123gh6pm.h"
#include <stdio.h> 
#define Data_Port 'B'   // Add data ports here
#define CTRL_Port 'A'	// Add control ports here
#define RS 5 			// CTRL ReadWrite pin
#define RW 6 			// CTRL RegisterSelect (Command or Data) pin
#define E 7 			// CTRL E pin

void LCD_Init (void);
void LCD_Send_CMD (unsigned long);
void LCD_Send_Chr (unsigned long);
void LCD_Send_String (char *);
void LCD_Send_Int(int);
//void LCD_CLR_Screen(void);
void LCD_Move_Cursor (unsigned long, unsigned long);
void delay_ms(int);
void delay_us(int);

#endif
