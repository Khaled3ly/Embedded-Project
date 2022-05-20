#ifndef LED_H_  
#define LED_H_
#include "Drivers.h"

void LED_Init (unsigned char, unsigned short int);
void LED_ON (unsigned char, unsigned short int);
void LED_OFF (unsigned char, unsigned short int);
void LED_TGL (unsigned char, unsigned short int);

#endif