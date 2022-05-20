#include "Switch.h"

void Switch_Init (unsigned char port_name, unsigned short int pin_number){
	Set_Pin_DIR (port_name, pin_number,0);
}

unsigned short int Switch_Read (unsigned char port_name, unsigned short int pin_number){
	return Read_Pin (port_name, pin_number);
}