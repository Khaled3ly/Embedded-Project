#include "LCD.h"



void pulse (void){
	Write_Pin(CTRL_Port,E,1);
	delay (2);
	Write_Pin(CTRL_Port,E,0);
}

void LCD_Send_CMD (char cmd){
	Write_Port(Data_Port,cmd);
	Write_Pin(CTRL_Port,RS,0);
	pulse();
	delay (1);
}

void LCD_Send_Chr (char chr){
	Write_Port(Data_Port,chr);
	Write_Pin(CTRL_Port,RS,1);
	pulse();
	delay (1);
}

//void LCD_Send_String (char *data){
//	while ((*data) != '0'){
//		LCD_Send_Chr((*data));
//		data++;
//	}
//}

//void LCD_Send_Int(int number)
//{
//  char toprint[4] = {0};
//  sprintf(toprint, "%d", number);
//  int i = 0;
//  while(toprint[i] != '\0')
//  {
//   LCD_Send_Chr(toprint[i]);
//    i++;
// }
//}

void LCD_CLR_Screen(void){
	LCD_Send_CMD(0x01);
	delay (10);
}

void LCD_Move_Cursor (char row, char col){
	char position = 0;
	if (row == 1){
		position = (0x80) + col - 1;
	}
	else if (row == 2){
		position = (0xC0) + col - 1;
	}
	LCD_Send_CMD(position);
	delay (1);
}

void LCD_Init (void){
	Port_Init(Data_Port);
	Port_Init(CTRL_Port);
	Set_Port_DIR (Data_Port,0xFF);
	Set_Pin_DIR (CTRL_Port,E,1);
	Set_Pin_DIR (CTRL_Port,RS,1);
	Set_Pin_DIR (CTRL_Port,RW,1);
	Write_Pin (CTRL_Port,RW,0);
	LCD_Send_CMD(0x38);	// Eight Bits Mode
	delay (1);
	LCD_Send_CMD(0x01); // Clear Screen
	delay (10);
	LCD_Send_CMD(0x06); // Entry Mode
	delay (1);
}