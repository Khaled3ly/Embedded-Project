#ifndef Keypad_H_  
#define Keypad_H_
#include "Drivers.h"
#define Keypad_Port_Rows 'C'
#define Keypad_Port_Cols 'E'

void Keypad_Init (void);
unsigned char Keypad_Read (void);

#endif
