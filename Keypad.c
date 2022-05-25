#include "Keypad.h"


void Keypad_Init (void){
	// C4, C5, C6, C7 -> rows output
	// E1, E2, E3, E4 -> cols input
	Port_Init(Keypad_Port_Rows);
	Port_Init(Keypad_Port_Cols);
	Set_Port_DIR (Keypad_Port_Rows,0xF0);
	Set_Port_DIR (Keypad_Port_Cols,0x00);
	Enable_Port_PU (Keypad_Port_Rows,0xFF);
	Enable_Port_PU (Keypad_Port_Cols,0xFF);
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
		Write_Port (Keypad_Port_Rows, 0xFF);
		Write_Pin (Keypad_Port_Rows, row+4, 0);
		for ( col = 0; col < 4; col++){
			x = Read_Pin(Keypad_Port_Cols, col+1);
			if (x == 0){
				return_value = keymap[row][col];
				break;
			}
		}
		if (x == 0) break;
	}
	return return_value;
}
