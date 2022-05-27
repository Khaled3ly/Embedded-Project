#include "Drivers.h"

#define SET_BIT(reg,bit) reg |= (1<<bit)
#define CLR_BIT(reg,bit) reg &= (~(1<<bit))
#define TOG_BIT(reg,bit) reg ^= (1<<bit)
#define READ_BIT(reg,bit) (reg & (1<<bit)) >> bit 


void Port_Init (unsigned char port_name){
	
	switch (port_name){
		case 'A':
		case 'a':
			SET_BIT(SYSCTL_RCGCGPIO_R,0);
			while (READ_BIT(SYSCTL_PRGPIO_R,0)==0);
			GPIO_PORTA_LOCK_R = 0x4C4F434B;
			GPIO_PORTA_CR_R |= 0xFF;
			GPIO_PORTA_DEN_R |= 0xE4;
			GPIO_PORTA_AFSEL_R &= ~0xE4;
			GPIO_PORTA_AMSEL_R &= ~0xE4;
			GPIO_PORTA_PCTL_R &= ~0xE4;
			GPIO_PORTA_DIR_R &= ~0x04;
			GPIO_PORTA_DIR_R |= 0xE0;
			GPIO_PORTA_DATA_R &= ~0x40;
			break;

		case 'B':
		case 'b':
			SET_BIT(SYSCTL_RCGCGPIO_R,1);
			while (READ_BIT(SYSCTL_PRGPIO_R,1)==0);
			GPIO_PORTB_LOCK_R = 0x4C4F434B;
			GPIO_PORTB_CR_R |= 0xFF;
			GPIO_PORTB_DEN_R |= 0xFF;
			GPIO_PORTB_AFSEL_R &= ~0xFF;
			GPIO_PORTB_AMSEL_R &= ~0xFF;
			GPIO_PORTB_PCTL_R &= ~0xFF;
			GPIO_PORTB_DIR_R |= 0xFF;
			break;

		case 'C':
		case 'c':
			SET_BIT(SYSCTL_RCGCGPIO_R,2);
			while (READ_BIT(SYSCTL_PRGPIO_R,2)==0);
			GPIO_PORTC_LOCK_R = 0x4C4F434B;
			GPIO_PORTC_CR_R |= 0xFF;
			GPIO_PORTC_DEN_R |= 0xFF;
			break;

		case 'D':
		case 'd':
			SET_BIT(SYSCTL_RCGCGPIO_R,3);
			while (READ_BIT(SYSCTL_PRGPIO_R,3)==0);
			GPIO_PORTD_LOCK_R = 0x4C4F434B;
			GPIO_PORTD_CR_R |= 0xFF;
			GPIO_PORTD_DEN_R |= 0xFF;
			break;

		case 'E':
		case 'e':
			SET_BIT(SYSCTL_RCGCGPIO_R,4);
			while (READ_BIT(SYSCTL_PRGPIO_R,4)==0);
			GPIO_PORTE_LOCK_R = 0x4C4F434B;
			GPIO_PORTE_CR_R |= 0x3F;
			GPIO_PORTE_DEN_R |= 0x3F;
			break;

		case 'F':
		case 'f':
			SET_BIT(SYSCTL_RCGCGPIO_R,5);
			while (READ_BIT(SYSCTL_PRGPIO_R,5)==0);
			GPIO_PORTF_LOCK_R = 0x4C4F434B;
			GPIO_PORTF_CR_R |= 0x1F;
			GPIO_PORTF_DEN_R |= 0x1F;
			break;
	}
	
}

void Set_Pin_DIR (unsigned char port_name, unsigned short int pin_number, unsigned short int direction){
	
	switch (port_name){
		case 'A':
		case 'a':
			if (direction == 1) {
				SET_BIT(GPIO_PORTA_DIR_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTA_DIR_R,pin_number);
			}
			break;
		
		case 'B':
		case 'b':
			if (direction == 1) {
				SET_BIT(GPIO_PORTB_DIR_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTB_DIR_R,pin_number);
			}
			break;
		
		case 'C':
		case 'c':
			if (direction == 1) {
				SET_BIT(GPIO_PORTC_DIR_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTC_DIR_R,pin_number);
			}
			break;
		
		case 'D':
		case 'd':
			if (direction == 1) {
				SET_BIT(GPIO_PORTD_DIR_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTD_DIR_R,pin_number);
			}
			break;
		
		case 'E':
		case 'e':
			if (direction == 1) {
				SET_BIT(GPIO_PORTE_DIR_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTE_DIR_R,pin_number);
			}
			break;
		
		case 'F':
		case 'f':
			if (direction == 1) {
				SET_BIT(GPIO_PORTF_DIR_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTF_DIR_R,pin_number);
			}
			break;
	}
}

void Write_Pin (unsigned char port_name, unsigned short int pin_number, unsigned short int data){
		
	switch (port_name){
		case 'A':
		case 'a':
			if (data == 1) {
				SET_BIT(GPIO_PORTA_DATA_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTA_DATA_R,pin_number);
			}
			break;
		
		case 'B':
		case 'b':
			if (data == 1) {
				SET_BIT(GPIO_PORTB_DATA_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTB_DATA_R,pin_number);
			}
			break;
		
		case 'C':
		case 'c':
			if (data == 1) {
				SET_BIT(GPIO_PORTC_DATA_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTC_DATA_R,pin_number);
			}
			break;
		
		case 'D':
		case 'd':
			if (data == 1) {
				SET_BIT(GPIO_PORTD_DATA_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTD_DATA_R,pin_number);
			}
			break;
		
		case 'E':
		case 'e':
			if (data == 1) {
				SET_BIT(GPIO_PORTE_DATA_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTE_DATA_R,pin_number);
			}
			break;
		
		case 'F':
		case 'f':
			if (data == 1) {
				SET_BIT(GPIO_PORTF_DATA_R,pin_number);
			}
			else
			{
				CLR_BIT(GPIO_PORTF_DATA_R,pin_number);
			}
			break;
	}
}

void Toggle_Pin (unsigned char port_name, unsigned short int pin_number){
		
	switch (port_name){
		case 'A':
		case 'a':
			TOG_BIT(GPIO_PORTA_DATA_R,pin_number);
			break;
		
		case 'B':
		case 'b':
			TOG_BIT(GPIO_PORTB_DATA_R,pin_number);
		break;
		
		case 'C':
		case 'c':
			TOG_BIT(GPIO_PORTC_DATA_R,pin_number);
			break;
		
		case 'D':
		case 'd':
			TOG_BIT(GPIO_PORTD_DATA_R,pin_number);
			break;
		
		case 'E':
		case 'e':
			TOG_BIT(GPIO_PORTE_DATA_R,pin_number);
			break;
		
		case 'F':
		case 'f':
			TOG_BIT(GPIO_PORTF_DATA_R,pin_number);
			break;
	}
}
void Set_Port_DIR (unsigned char port_name, unsigned short int direction){
	
	switch (port_name){
		case 'A':
		case 'a':
			GPIO_PORTA_DIR_R |= direction;
			break;
		
		case 'B':
		case 'b':
			GPIO_PORTB_DIR_R |= direction;
			break;
		
		case 'C':
		case 'c':
			GPIO_PORTC_DIR_R |= direction;
			break;
		
		case 'D':
		case 'd':
			GPIO_PORTD_DIR_R |= direction;
			break;
		
		case 'E':
		case 'e':
			GPIO_PORTE_DIR_R |= direction;
		break;
		
		case 'F':
		case 'f':
			GPIO_PORTF_DIR_R |= direction;
			break;
	}
}
void Write_Port (unsigned char port_name, unsigned short int data){

	switch (port_name){
		case 'A':
		case 'a':
			GPIO_PORTA_DATA_R |= data;
			break;
		
		case 'B':
		case 'b':
			GPIO_PORTB_DATA_R |= data;
			break;
		
		case 'C':
		case 'c':
			GPIO_PORTC_DATA_R |= data;
			break;
		
		case 'D':
		case 'd':
			GPIO_PORTD_DATA_R |= data;
		break;
		
		case 'E':
		case 'e':
			GPIO_PORTE_DATA_R |= data;
			break;
		
		case 'F':
		case 'f':
			GPIO_PORTF_DATA_R |= data;
			break;
	}	
}
unsigned short int Read_Pin (unsigned char port_name, unsigned short int pin_number){
	switch (port_name){
		case 'A':
		case 'a':
			return READ_BIT(GPIO_PORTA_DATA_R,pin_number);
			break;

		case 'B':
		case 'b':
			return READ_BIT(GPIO_PORTB_DATA_R,pin_number);		
			break;

		case 'C':
		case 'c':
			return READ_BIT(GPIO_PORTC_DATA_R,pin_number);		
			break;

		case 'D':
		case 'd':
			return READ_BIT(GPIO_PORTD_DATA_R,pin_number);
			break;

		case 'E':
		case 'e':
			return READ_BIT(GPIO_PORTE_DATA_R,pin_number);
			break;

		case 'F':
		case 'f':
			return READ_BIT(GPIO_PORTF_DATA_R,pin_number);
			break;
	}
}
unsigned short int Read_Port (unsigned char port_name){
	switch (port_name){
		case 'A':
		case 'a':
			return GPIO_PORTA_DATA_R;
			break;

		case 'B':
		case 'b':
			return GPIO_PORTB_DATA_R;		
			break;

		case 'C':
		case 'c':
			return GPIO_PORTC_DATA_R;		
			break;

		case 'D':
		case 'd':
			return GPIO_PORTD_DATA_R;
			break;

		case 'E':
		case 'e':
			return GPIO_PORTE_DATA_R;
			break;

		case 'F':
		case 'f':
			return GPIO_PORTF_DATA_R;
			break;
	}
}
void Enable_PU (unsigned char port_name, unsigned short int pin_number){
	switch (port_name){
		case 'A':
		case 'a':
			SET_BIT(GPIO_PORTA_PUR_R,pin_number);
			break;
		
		case 'B':
		case 'b':
			SET_BIT(GPIO_PORTB_PUR_R,pin_number);
			break;
		
		case 'C':
		case 'c':
			SET_BIT(GPIO_PORTC_PUR_R,pin_number);
			break;
		
		case 'D':
		case 'd':
			SET_BIT(GPIO_PORTD_PUR_R,pin_number);
			break;
		
		case 'E':
		case 'e':
			SET_BIT(GPIO_PORTE_PUR_R,pin_number);
			break;
		
		case 'F':
		case 'f':
			SET_BIT(GPIO_PORTF_PUR_R,pin_number);
			break;
	}
}
void Enable_Port_PU (unsigned char port_name, unsigned short int pins){
	switch (port_name){
		case 'A':
		case 'a':
			GPIO_PORTA_PUR_R |= pins;
			break;
		
		case 'B':
		case 'b':
			GPIO_PORTB_PUR_R |= pins;
			break;
		
		case 'C':
		case 'c':
			GPIO_PORTC_PUR_R |= pins;
			break;
		
		case 'D':
		case 'd':
			GPIO_PORTD_PUR_R |= pins;
			break;
		
		case 'E':
		case 'e':
			GPIO_PORTE_PUR_R |= pins;
			break;
		
		case 'F':
		case 'f':
			GPIO_PORTF_PUR_R |= pins;
			break;
	}
}
void Write_High_Nibble (unsigned char port_name, unsigned short int data){

	data <<= 4;

	switch (port_name){
		case 'A':
		case 'a':
			GPIO_PORTA_DATA_R &= 0x0F;
			GPIO_PORTA_DATA_R |= data;
			break;
		
		case 'B':
		case 'b':
			GPIO_PORTB_DATA_R &= 0x0F;
			GPIO_PORTB_DATA_R |= data;
			break;
		
		case 'C':
		case 'c':
			GPIO_PORTC_DATA_R &= 0x0F;
			GPIO_PORTC_DATA_R |= data;
			break;
		
		case 'D':
		case 'd':
			GPIO_PORTD_DATA_R &= 0x0F;
			GPIO_PORTD_DATA_R |= data;
			break;
		
		case 'E':
		case 'e':
			GPIO_PORTE_DATA_R &= 0x0F;
			GPIO_PORTE_DATA_R |= data;
			break;
		
		case 'F':
		case 'f':
			GPIO_PORTF_DATA_R &= 0x0F;
			GPIO_PORTF_DATA_R |= data;
			break;
	}		
}
void Write_Low_Nibble (unsigned char port_name, unsigned short int data){

	switch (port_name){
		case 'A':
		case 'a':
			GPIO_PORTA_DATA_R &= 0xF0;
			GPIO_PORTA_DATA_R |= data;
			break;
		
		case 'B':
		case 'b':
			GPIO_PORTB_DATA_R &= 0xF0;
			GPIO_PORTB_DATA_R |= data;
			break;
		
		case 'C':
		case 'c':
			GPIO_PORTC_DATA_R &= 0xF0;
			GPIO_PORTC_DATA_R |= data;
			break;
		
		case 'D':
		case 'd':
			GPIO_PORTD_DATA_R &= 0xF0;
			GPIO_PORTD_DATA_R |= data;
			break;
		
		case 'E':
		case 'e':
			GPIO_PORTE_DATA_R &= 0xF0;
			GPIO_PORTE_DATA_R |= data;
			break;
		
		case 'F':
		case 'f':
			GPIO_PORTF_DATA_R &= 0xF0;
			GPIO_PORTF_DATA_R |= data;
			break;
	}		
}
