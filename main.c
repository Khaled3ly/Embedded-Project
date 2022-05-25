#include "Keypad.h"
#include "LCD.h"
#include "LED.h"
#include "Switch.h"
#include "systick timer.h"



#define state_init 0
#define state_measurmenet 1
#define state_defrost_beef 2
#define state_defrost_chicken 3
#define state_defrost 4
#define state_popcorn 5
#define state_stopped 6
#define state_cooking_time 7
#define state_oven_stop 8
#define state_oven_operation 9
#define state_oven_pause 10
#define state_oven 11
#define state_operation_beef 12
#define state_operation_pop 13
#define state_operation_cooking_time 14
#define state_operation_chicken 15
#define state_oven_resume 16

int current_state = state_oven_operation;
int prev_state = 0;
int pause_time;
int i, total_time;
int last_kilo = 0;
char last_letter = '0';
unsigned char letter;
unsigned char kilo, current_kilo;
unsigned char time1, time2, time3, time4;

int switch_state_machine(int start) {
	static int counter = 1;
  int current_switch_state = 0;
	if (start == 1){
		while ((Switch_Read('F', 0) != 0)){
	
		}
		current_switch_state = state_oven;
	}
	else if (start == 0){
		if (counter == 1){
			current_switch_state = state_oven_pause;
			counter ++;
		}
		else if (counter ==2){
			current_switch_state = state_stopped;
		}
	}
	else if (start == 3){
		current_switch_state = state_oven_resume; 
	}
	return current_switch_state;
}



void Initialize (void){
	LCD_Init();
	Keypad_Init();
	LED_Init('F',1);
	LED_Init('F',2);
	LED_Init('F',3);
	LED_Init('E',5); // Buzzer
	LED_OFF('E',5);
	
	Switch_Init('F',0);
	Switch_Init('F',4);
	Switch_Init('A',2);
}


int main(void) {
	Initialize();
	
  while (1)
	{
		
    while (Switch_Read('A', 2) != 0) {
				LCD_Send_CMD(0x01);
				LCD_Send_String(" Close Door");
			while (Switch_Read('A', 2) != 0){}
		}
  
    if (current_state == state_oven_operation) {
			LCD_Send_CMD(0x01);
			LCD_Send_String(" Press A, B, C, D");
			while (Keypad_Read()== 0xFF){}
      letter = Keypad_Read();

      switch (letter)

      {
        case 'A':
					LCD_Send_CMD(0x01);
          LCD_Send_String(" Popcorn");		
					LCD_Move_Cursor(2,1);
					LCD_Send_String("Press Start !");	
          current_state = switch_state_machine(1);
          break;

        case 'B':
					LCD_Send_CMD(0x01);
          LCD_Send_String(" Beef Weight?");
					delay_ms(200);
				  while (Keypad_Read()== 0xFF){}
					kilo = Keypad_Read();

          if (kilo > '0' && kilo <= '9') {		
            LCD_Send_CMD(0x01);
            LCD_Send_String(" Beef Weight: ");
						LCD_Send_Chr(kilo);
            delay_ms(2000);
            LCD_Send_CMD(0x01);
						LCD_Send_String(" Press Start !");	
            last_kilo = kilo - '0';
						current_state = switch_state_machine(1);

          } else {
            LCD_Send_CMD(0x01);
            LCD_Send_String(" err");
            delay_ms(2000);
            LCD_Send_CMD(0x01);
						current_state = state_oven_operation;
          }
          break;

        case 'C':
					LCD_Send_CMD(0x01);
          LCD_Send_String(" Chicken Weight?");
					delay_ms(200);
				  while (Keypad_Read()== 0xFF){}
					kilo = Keypad_Read();

          if (kilo > '0' && kilo <= '9') {		
            LCD_Send_CMD(0x01);
            LCD_Send_String(" Chicken Weight:");
						LCD_Send_Chr(kilo);
            delay_ms(2000);
            LCD_Send_CMD(0x01);
						LCD_Send_String(" Press Start !");	
            last_kilo = kilo - '0';
						current_state = switch_state_machine(1);

          } else {
            LCD_Send_CMD(0x01);
            LCD_Send_String(" err");
            delay_ms(2000);
            LCD_Send_CMD(0x01);
						current_state = state_oven_operation;
          }
          break;

        case 'D':
					LCD_Send_CMD(0x01);
          LCD_Send_String(" Cooking Time?");
					delay_ms(2000);
					LCD_Send_CMD(0x01);
					LCD_Send_String(" 00:0");
				  while (Keypad_Read()== 0xFF){}
					time1 = Keypad_Read();
					LCD_Send_Chr(time1);
					delay_ms(500);
					while (Keypad_Read()== 0xFF){}
					time2 = Keypad_Read();
					LCD_Send_CMD(0x01);
					LCD_Send_String(" 00:");
					LCD_Send_Chr(time1);
					LCD_Send_Chr(time2);
					delay_ms(500);
					while (Keypad_Read()== 0xFF){}
					time3 = Keypad_Read();
					LCD_Send_CMD(0x01);
					LCD_Send_String(" 0");
					LCD_Send_Chr(time1);
					LCD_Send_String(":");
					LCD_Send_Chr(time2);
					LCD_Send_Chr(time3);
					delay_ms(500);
					while (Keypad_Read()== 0xFF){}
					time4 = Keypad_Read();
					LCD_Send_CMD(0x01);
					LCD_Send_String(" ");
					LCD_Send_Chr(time1);
					LCD_Send_Chr(time2);
					LCD_Send_String(":");
					LCD_Send_Chr(time3);
					LCD_Send_Chr(time4);
					total_time = (time1 - '0') * 600 + (time2 - '0') * 60 + (time3 - '0') * 10 + (time4 - '0');
					LCD_Move_Cursor(2,1);
					LCD_Send_String(" Press Start !");	
          current_state = switch_state_machine(1);
          break;
      }
      last_letter = letter;
		}
		else if (current_state == state_oven) {
      LED_ON('F', 1);
      LED_ON('F', 2);
      LED_ON('F', 3);
      if (last_letter == 'A') {
				int value;
        for (value = 60; value > 0; value--){
          if (Switch_Read('F', 4) == 0){     // Pause
					current_state = switch_state_machine(0);
          if (current_state == state_oven_pause) {
           pause_time = value;
           break;
						}
          }
          LCD_Send_CMD(0x01);
          LCD_Send_String(" Time Left: ");
          LCD_Move_Cursor(1, 11);
					LCD_Send_Int(value);
          delay_ms(1000);
          LCD_Send_CMD(0x01);
					if (Switch_Read('A', 2) != 0){   // Door
					pause_time = value;
					current_state = switch_state_machine(0);
					break;
					}
					if (value == 1){
						current_state = state_stopped;
					}
        }
      }
			else if (last_letter == 'B') {
				int value;
        for (value = (30*last_kilo); value > 0; value--){
          if (Switch_Read('F', 4) == 0){
					current_state = switch_state_machine(0);
          if (current_state == state_oven_pause) {
           pause_time = value;
           break;
						}
          }
          LCD_Send_CMD(0x01);
          LCD_Send_String(" Time Left: ");
          LCD_Move_Cursor(1, 11);
					LCD_Send_Int(value);
          delay_ms(1000);
          LCD_Send_CMD(0x01);
					if (Switch_Read('A', 2) != 0){
					pause_time = value;
					current_state = switch_state_machine(0);
					break;
					}
					if (value == 1){
						current_state = state_stopped;
					}
        }
      }
			else if (last_letter == 'C') {
				int value;
        for (value = (12*last_kilo); value > 0; value--){
          if (Switch_Read('F', 4) == 0){
					current_state = switch_state_machine(0);
          if (current_state == state_oven_pause) {
           pause_time = value;
           break;
						}
          }
          LCD_Send_CMD(0x01);
          LCD_Send_String(" Time Left: ");
          LCD_Move_Cursor(1, 11);
					LCD_Send_Int(value);
          delay_ms(1000);
          LCD_Send_CMD(0x01);
					if (Switch_Read('A', 2) != 0){\
					pause_time = value;
					current_state = switch_state_machine(0);
					break;
					}
					if (value == 1){
						current_state = state_stopped;
					}
        }
      }
      else if (last_letter == 'D') {
				  for (total_time; total_time > 0; total_time--){
          if (Switch_Read('F', 4) == 0){     // Pause
					current_state = switch_state_machine(0);
          if (current_state == state_oven_pause) {
           pause_time = total_time;
           break;
						}
          }
          LCD_Send_CMD(0x01);
          LCD_Send_String(" Time Left: ");
          LCD_Move_Cursor(1, 11);
					LCD_Send_Int(total_time);
          delay_ms(1000);
          LCD_Send_CMD(0x01);
					if (Switch_Read('A', 2) != 0){   // Door
					pause_time = total_time;
					current_state = switch_state_machine(0);
					break;
					}
					if (total_time == 1){
						current_state = state_stopped;
					}
        }
     }
    }
    else if (current_state == state_oven_pause) {
			while (current_state == state_oven_pause){
        LED_TGL('F', 1);
        LED_TGL('F', 2);
        LED_TGL('F', 3);
				LCD_Send_CMD(0x01);
				LCD_Send_String(" Pause time :");
				LCD_Send_Int(pause_time);
				delay_ms(200);
			if (Switch_Read('F', 4) == 0){
				current_state = switch_state_machine(0);
			}	
			if (Switch_Read('F', 0) == 0){
			current_state = switch_state_machine(3);
			}	
			}			
		}
		else if (current_state == state_oven_resume){
			    for (pause_time; pause_time > 0; pause_time--){
					LED_ON('F', 1);
					LED_ON('F', 2);
					LED_ON('F', 3);
          LCD_Send_CMD(0x01);
          LCD_Send_String(" Time Left: ");
          LCD_Move_Cursor(1, 11);
					LCD_Send_Int(pause_time);
          delay_ms(1000);
          LCD_Send_CMD(0x01);
        }
					current_state = state_stopped;
		}
				else if (current_state == state_stopped)
        {	
					LCD_Send_CMD(0x01);
					LCD_Send_String(" Done !");
            for (i = 0; i<6; i++)
            {
                LED_TGL('F',1);
                LED_TGL('F',2);
                LED_TGL('F',3);
                delay_ms(500);
                LED_TGL('E',5); // Buzzer
            }
						LED_OFF('E',5);
						LED_OFF('F',1);
						LED_OFF('F',2);
						LED_OFF('F',3);
          current_state = state_oven_operation;   ///current_state == state_oven_operation I SHOULD IT BE THERE
        }
 
        prev_state = current_state;
	}
}
