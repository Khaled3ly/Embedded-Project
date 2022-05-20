#include "Keypad.h"


void Keypad_Init (void){
	// 0 -> 3 output
	// 4 -> 7 input
	Port_Init(Keypad_Port);
	Set_Port_DIR (Keypad_Port,0x0F);
	Enable_Port_PU (Keypad_Port,0xFF);
}

unsigned char Keypad_Read (void){
	const unsigned char keymap[4][4] = 
	{
		{ '1', '2', '3', 'A'},
		{ '4', '5', '6', 'B'},
		{ '7', '8', '9', 'C'},
		{ '*', '0', '#', 'D'},
	};
	
	char return_value = 0xFF;
	unsigned short int x;
	int col;
	int row;
	for ( row = 0; row < 4; row++){
		Write_Low_Nibble (Keypad_Port, 0xFF);
		Write_Pin (Keypad_Port, row, 0);
		for ( col = 0; col < 4; col++){
			x = Read_Pin(Keypad_Port, col+4);
			if (x == 0){
				return_value = keymap[row][col];
				break;
			}
		}
		if (x == 0) break;
	}
	return return_value;
}