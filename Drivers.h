#ifndef Drivers_H_  
#define Drivers_H_
#include "tm4c123gh6pm.h"

void Port_Init (unsigned char);
void Set_Pin_DIR (unsigned char, unsigned short int, unsigned short int);
void Write_Pin (unsigned char, unsigned short int, unsigned short int);
void Toggle_Pin (unsigned char, unsigned short int);
void Set_Port_DIR (unsigned char, unsigned short int);
void Write_Port (unsigned char, unsigned short int);
unsigned short int Read_Pin (unsigned char, unsigned short int);
unsigned short int Read_Port (unsigned char);
void Enable_PU (unsigned char, unsigned short int);
void Enable_Port_PU (unsigned char, unsigned short int);
void Write_High_Nibble (unsigned char, unsigned short int);
void Write_Low_Nibble (unsigned char, unsigned short int);

#endif