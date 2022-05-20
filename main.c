#include "Keypad.h"
#include "LCD.h"
#include "LED.h"
#include "Switch.h"


#define state_init 0
#define state_measurmenet 1 
#define state_defrost_beef   2
#define state_defrost_chicken 3
#define state_defrost   4
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
 
int sw_2_is_pressed = 1;
int sw1_is_pressed = 1;
int sw3_is_pressed = 1;
int current_state = state_oven_operation;
int prev_state = 0;
int pause_time;
int i;
#define state_init_1 0 
#define state_1 1 
int current_switch_state = state_init_1;
 
 int switch_state_machine(int start) 
   {
    int current_switch_state = 0;
   if (sw_2_is_pressed && start != 0)
     {
        current_switch_state = state_oven;
 
     }
   else if (sw_2_is_pressed && prev_state == state_oven_pause) //int prev_state = 0;
     {
        // get current time, display it
        cout << "state previous is pause" << endl;
     }
   else
     {
        static int counter = 0;
 
        if (sw1_is_pressed)
        {
            counter++;
 
            if (counter == 1)
            {
                current_switch_state = state_oven_pause;
 
                // store current time
            }
            else if (counter == 2)
            {
                current_switch_state = state_oven_stop;
 
            }
        }
    }
 
    return current_switch_state;

 // sw1 f4 , sw2 f0, sw3 B3
 
int switch_state_machine(int start);

void Initializing (void){
	Port_Init('F');
    Keypad_Init(); // Initialized on Port D
    LCD_Init(); 

    LED_Init('F',1);   //set direction
    LED_Init('F',2);
    LED_Init('F',3);

    Switch_Init('F',4); // Switch 1       //set direction
    Switch_Init('F',0); // Switch 2
    Switch_Init('B',3); // External Switch 3

    LED_Init('D',4); // check pin  Buzzer
}



int main(void)
{
    Initializing();

    char last_kilo = '0';
    char last_letter = '0';
    while (Switch_Read('D',5) != 0){}
    {
 
      if (current_state == state_oven_operation)
        {
            // oven operation
            unsigned char letter = Keypad_Read();
 
              switch (letter) { 								// LOOK FOR KEYPAD INPUT
              
							case 'A':    
							current_state = state_popcorn;
               break;
								
               case 'B':  
                current_state = state_defrost_beef;
               break;
            
               case 'C':  
               current_state = state_defrost_chicken;
               break;
            
               case 'D':  
               current_state = state_cooking_time;
              break;
           last_letter = letter;
        }
							
				
 
    else if (current_state == state_popcorn)
        {
            
        LCD_Send_String ("pop corn");
			current_state = switch_state_machine(1);
        }
				
				
				
     else if (current_state == state_defrost_beef)
        {
            LCD_Send_String ( "beef weight?" )
            unsigned char kilo = Keypad_Read();
            if (kilo > '0' && kilo < '10')
            {
				LCD_CLR_Screen();
				LCD_Send_String ("beef weight: ");
        LCD_Send_String(kilo);
				genericDelay(2000);
        LCD_CLR_Screen();
				last_kilo = kilo;
			
            }
            else
            {  
                LCD_CLR_Screen();
                LCD_Send_String ("err");
                genericDelay(2000);
				        LCD_CLR_Screen()
            }
            current_state = switch_state_machine(1);
        }
				
				
				
     else if (current_state == state_defrost_chicken)
        {
			     LCD_Send_String ("chicken weight?");
            unsigned char kilo = keypad_read();
                    if (kilo > '0' && kilo < '10')
            {
                LCD_CLR_Screen();
				LCD_Send_String ("chicken weight: kilo");
				genericDelay(2000);
                LCD_CLR_Screen();
				last_kilo = kilo;
            }
                     else
              {
				LCD_CLR_Screen();
                LCD_Send_String ("err");
                genericDelay(2000);
				LCD_CLR_Screen();
              }
				current_state = switch_state_machine(1);
            }
			else if (current_state == state_cooking_time)
        {
                char arr[] = "00000";
                int counter = 5;
                int last_char = 0;
                int value = 1;
                int multiplier = 1;
                int numberofdigits = 0;
            while (counter-- != 0)
            {
                unsigned char letter = Keypad_Read();
                int digit = letter - '0';
                value = digit + last_char * 10;
                _itoa(value, &arr[counter], 10);
                cout << arr << endl;
                last_char = value;
                numberofdigits++;
            }
            if (numberofdigits > 2)
            {
                arr[2] = ':';
            }
            cout << arr << endl;
            current_state = switch_state_machine(1);
           
         }
     
      else if (current_state == state_oven)
        {
            LED_ON('F',1);
            LED_ON('F',2);
            LED_ON('F',3);

            if (last_letter == 'A')
            {
				        int delay = 60;
                while (--delay)
                {
                    current_state = switch_state_machine(0);
                    if (current_state == state_oven_pause)
                    {
                        pause_time = delay;
                    break;
                    }
                    else if (current_state == state_stopped)
                    {
                        break;
                    }
                    LCD_Move_Cursor(2,1);
                    LCD_Send_String ("Time Left:");
                    LCD_Move_Cursor(2,12);
                    // Convert Delay from integer to char to print on LCD
                    LCD_Send_String(delay);
				             genericDelay(1000);
					           LCD_CLR_Screen(); 
                }
                
            }
						
						
         else if (last_letter == 'B')
            {
							    
           int value = (5 * 60 * last_kilo) / 10;
				            while (--value)
                {	   
				    current_state = switch_state_machine(0);
                    if (current_state == state_oven_pause)
                    {
                        pause_time = value;
                        break;
                    }
                    else if (current_state == state_stopped)
                    {
                        break;
                    }
                LCD_Move_Cursor(2,1);
                LCD_Send_String ("Time Left: ");
                LCD_Move_Cursor(2,12); 
                // Convert Value from integer to char to print on LCD 
				         genericDelay(1000);
				          LCD_CLR_Screen();
                }
                 
            }
						
						
         else if (last_letter == 'C')
            {
                int value = (2 * 60 * last_kilo) / 10;
				           while (--value)
                {
                    current_state = switch_state_machine(0);
                    if (current_state == state_oven_pause)
                    {
                        pause_time = value;
                        break;
                    }
                    else if (current_state == state_stopped)
                    {
                        break;
                    }
                LCD_Move_Cursor(2,1);
                LCD_Send_String ("Time Left: ");
                LCD_Move_Cursor(2,12); 
                // Convert Value from integer to char to print on LCD 
                genericDelay(1000);
                LCD_CLR_Screen();
                }
            }
						
						
						
          else if (last_letter == 'D')
            {
                // d
            }
						   
            current_state = state_stopped;

        }
 
				
				
			
				
        else if (current_state == state_oven_pause)
        {
					GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
            
					// oven pause
            // stop timer
 
            if (last_letter == 'a')
            {
 
                current_state = switch_state_machine(0);
            }
            else if (last_letter == 'b')
            {
 
            }
            else if (last_letter == 'c')
            {
 
            }
            else
            {
                // d
            }
            current_state = switch_state_machine(0);
        }
 

				
        else if (current_state == state_stopped)
        {
            for (i = 0; i<3; i++)
            {
                LED_TGL('F',1);
                LED_TGL('F',2);
                LED_TGL('F',3);
                genericDelay(1000);
                LED_ON('B',4); // Buzzer
            }

          current_state = state_oven_operation;   ///current_state == state_oven_operation I SHOULD IT BE THERE
        }
 
        prev_state = current_state;
    }
 
    
    return 0;
}
		


      int switch_state_machine(int start) ;
{
    int current_switch_state = 0;
   if (sw_2_is_pressed && start != 0)
     {
        current_switch_state = state_oven;
 
     }
   else if (sw_2_is_pressed && prev_state == state_oven_pause) //int prev_state = 0;
     {
        // get current time, display it
        cout << "state previous is pause" << endl;
     }
   else
     {
        static int counter = 0;
 
        if (sw1_is_pressed)
        {
            counter++;
 
            if (counter == 1)
            {
                current_switch_state = state_oven_pause;
 
                // store current time
            }
            else if (counter == 2)
            {
                current_switch_state = state_oven_stop;
 
            }
        }
    }
 
    return current_switch_state;
    // state machine switches
}
 