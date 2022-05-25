#include "LCD.h"



void LCD_Send_CMD(unsigned long cmd){
	GPIO_PORTB_DATA_R = cmd;
	GPIO_PORTA_DATA_R &= ~0x20;
	GPIO_PORTA_DATA_R |= 0x80;
	delay_us(40);
	GPIO_PORTA_DATA_R &= ~0x80;
}

void LCD_Send_Chr(unsigned long data){
	GPIO_PORTB_DATA_R = data;
	GPIO_PORTA_DATA_R |= 0x20;
	GPIO_PORTA_DATA_R |= 0x80;
	delay_us(40);
	GPIO_PORTA_DATA_R &= ~0x80;
	delay_ms(10);
}

void LCD_Send_String (char *data){
	while ((*data) != '\0'){
		LCD_Send_Chr((*data));
		data++;
	}
}

void LCD_Send_Int(int number)
{
	int i = 0;
  char toprint[4] = {0};
  sprintf(toprint, "%d", number);
  while(toprint[i] != '\0')
  {
    LCD_Send_Chr(toprint[i]);
    i++;
  }
}

//void LCD_CLR_Screen(void){
//	LCD_Send_CMD(0x01);
//	delay_ms (10);
//}

void LCD_Move_Cursor (unsigned long row, unsigned long col){
	char position = 0;
	if (row == 1){
		position = (0x80) + col - 1;
	}
	else if (row == 2){
		position = (0xC0) + col - 1;
	}
	LCD_Send_CMD(position);
	delay_ms (1);
}
void delay_us(int time)
{
int i, j;
for(i = 0 ; i < time; i++)
  for(j = 0; j < 3; j++){}
}
void delay_ms(int time)
{
int i, j;
for(i = 0 ; i < time; i++)
  for(j = 0; j < 3180; j++){}
}

void LCD_Init (void){
	Port_Init('A');
	Port_Init('B');
	LCD_Send_CMD(0x38); //8 bit
	delay_ms(2);			
	LCD_Send_CMD(0x01); // clr
	delay_ms(2);	
  LCD_Send_CMD(0x06);
	delay_ms(2);	
	LCD_Send_CMD(0x80);
	delay_ms(2);	
	LCD_Send_CMD(0x0E);
	delay_ms(2);	
}
