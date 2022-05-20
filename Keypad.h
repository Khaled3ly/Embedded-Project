#ifndef Keypad_H_  
#define Keypad_H_
#include "Drivers.h"
#define Keypad_Port 'B'

void Keypad_Init (void);
unsigned char Keypad_Read (void);

#endif