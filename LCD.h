#ifndef LCD_H_  
#define LCD_H_
#include "Drivers.h"
#include <stdio.h> 
#define Data_Port 'A'   // Add data ports here
#define CTRL_Port 'C'	// Add control ports here
#define E 4 			// CTRL E pin
#define RS 5 			// CTRL RegisterSelect (Command or Data) pin
#define RW 6 			// CTRL ReadWrite pin

void LCD_Init (void);
void pulse (void);
void LCD_Send_CMD (char);
void LCD_Send_Chr (char);
void LCD_Send_String (char);
void LCD_Send_Int(int);
void LCD_CLR_Screen(void);
void LCD_Move_Cursor (char, char);

#endif