#include "LED.h"

void LED_Init (unsigned char port_name, unsigned short int pin_number){
	Port_Init(port_name);
	Set_Pin_DIR (port_name, pin_number,1);	
}

void LED_ON (unsigned char port_name, unsigned short int pin_number){
	Write_Pin (port_name, pin_number,1);
}

void LED_OFF (unsigned char port_name, unsigned short int pin_number){
	Write_Pin (port_name, pin_number,0);
}

void LED_TGL (unsigned char port_name, unsigned short int pin_number){
	Toggle_Pin (port_name, pin_number);
}
