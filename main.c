#include "Keypad.h"
#include "LCD.h"
#include "LED.h"
#include "Switch.h"
// INCLUDE GENERICDELAY


void Initializing (void){
    Port_Init(F);
    Keypad_Init(); // Initialized on Port D
    LCD_Init(); // Initialized on Port A and B

    LED_Init(F,1);
    LED_Init(F,2);
    LED_Init(F,3);

    Switch_Init(F,4); // Switch 1 (Pause/Stop)
    Switch_Init(F,0); // Switch 2 (Start)
    Switch_Init(B,3); // External Switch 3 (Door)

    LED_Init(B,4); // Buzzer
}


void Stop_Oven (void){
    LED_OFF(F,1);
    LED_OFF(F,2);
    LED_OFF(F,3);
    main ();
}

void Done_Oven (void){
    for (int i = 0; i <= 3; i++)
    {
        LED_TGL(F,1);
        LED_TGL(F,2);
        LED_TGL(F,3);
        LED_TGL(B,4);
        genericDelay(500);
    }
    Stop_Oven();
}


void main (void){

    Initializing();
    int time;
    LCD_CLR_Screen(); 
    LCD_Move_Cursor(1,1);
    LCD_Send_String ("WELCOME !");

    while (1)
    {
        unsigned char Keypad_Input = Keypad_Read();
        int Keypad_Input_Int = Keypad_Input - '0';          //Conversion from char to int

        while (Switch_Read(B,3) == '0')               // CHECK IF DOOR IS CLOSED
        {
            switch (Keypad_Input)                         // LOOK FOR KEYPAD INPUT
            {
                case 'A':                           // IF A IS PRESSED POPCORN
                    LCD_Move_Cursor(1,1);
                    LCD_Send_String ("Popcorn");
                    genericDelay(1000);             // LEAVE POPCORN ON SCREEN FOR 1 SEC
                    LCD_Send_String ("Press Start");
                    while (Switch_Read(F,0) != '0')
                    {
                                                    // IF SWITCH 2 (START) NOT PRESSED DO NOTHING
                    }

                    for (time = 60; time > 0; time--)
                    {   
                        if (Switch_Read(F,4) != '0')  // IF SWITCH 1 (PAUSE) NOT PRESSED
                        {
                            LED_ON(F,1);
                            LED_ON(F,2);
                            LED_ON(F,3);
                            LCD_CLR_Screen(); 
                            LCD_Move_Cursor(1,1);
                            LCD_Send_String ("Time Left: ");
                            LCD_Move_Cursor(1,10);
                            LCD_Send_Int(time);
                            genericDelay(1000);   
                        }
                        else if (Switch_Read(F,4) == '0')    // IF SWITCH 1 (PAUSE) IS PRESSED FIRST TIME
                        {   
                            while (Switch_Read(F,4) != '0' || Switch_Read(F,0) != '0')  // STAY IN THE LOOP AS LONG AS (STOP/START NOT PRESSED)
                            {                        
                                LED_TGL(F,1);
                                LED_TGL(F,2);
                                LED_TGL(F,3);      //LEDS KEEP TOGLING WHILE PAUSED  (APPLY TO OTHER CASES)
                                genericDelay(500);
                            }
                            if (Switch_Read(F,4) == '0')
                            {
                                Stop_Oven ();               // IF SWITCH 1 (STOP) IS PRESSED SECOND TIME
                            }
                            else if (Switch_Read(F,0) == '0') // IF SWITCH 2 (START) IS PRESSED AFTER PAUSED
                            {
                                continue;
                            }
                        }    
                    }
                    Done_Oven();
                    break;

                case 'B':                                       // IF B IS PRESSED BEEF
                    LCD_Move_Cursor(1,1);
                    LCD_Send_String ("Beef Weight ?");          // ASKING USER FOR WEIGHT
                    while (Keypad_Input == 0xFF)                // WAIT FOR USER INPUT
                    {

                    }                  
                    LCD_Move_Cursor(1,10);
                    //if (Keypad_Input == '1' || Keypad_Input == '2' || Keypad_Input == '3' || Keypad_Input == '4' || Keypad_Input == '5' || Keypad_Input == '6' || Keypad_Input == '7' || Keypad_Input == '8' || Keypad_Input == '9')
                    if (Keypad_Input_Int >= 1 && Keypad_Input_Int <= 9)
                    {
                        LCD_Send_String(Keypad_Input);              // SHOWING ENTERED NUMBER FROM 1 - 9 ON LCD
                    }
                    else
                    {                                          // IF ENTETRED ANYTHING ELSE (1-9)
                        LCD_Send_String ("Err"); 
                    }
                    genericDelay(2000);
                    LCD_CLR_Screen();
                    LCD_Send_String ("Press Start");
                    while (Switch_Read(F,0) != '0')
                    {
                                                                     // IF SWITCH 2 (START) NOT PRESSED DO NOTHING
                    }
                    time = (30 * Keypad_Input_Int);                 // CONVERT FROM CHAR TO INT AND THEN GET TIME 30 SEC FOR EACH KILO
                    for (time; time > 0; time--)
                    {
                        if (Switch_Read(F,4) != '0')  // IF SWITCH 1 (PAUSE) NOT PRESSED
                        {
                            LED_ON(F,1);
                            LED_ON(F,2);
                            LED_ON(F,3);
                            LCD_CLR_Screen(); 
                            LCD_Move_Cursor(2,1);
                            LCD_Send_String ("Time Left: ");
                            LCD_Move_Cursor(2,10);
                            LCD_Send_Int(time);
                            genericDelay(1000);
                        }
                        else if (Switch_Read(F,4) == '0')    // IF SWITCH 1 (PAUSE) IS PRESSED FIRST TIME
                        {
                            while (Switch_Read(F,4) != '0' || Switch_Read(F,0) != '0')  // STAY IN THE LOOP AS LONG AS (STOP/START NOT PRESSED)
                            {                        
                                LED_TGL(F,1);
                                LED_TGL(F,2);
                                LED_TGL(F,3);      //LEDS KEEP TOGLING WHILE PAUSED  (APPLY TO OTHER CASES)
                                genericDelay(500);
                            }
                            if (Switch_Read(F,4) == '0')
                            {
                                Stop_Oven ();               // IF SWITCH 1 (STOP) IS PRESSED SECOND TIME
                            }
                            else if (Switch_Read(F,0) == '0') // IF SWITCH 2 (START) IS PRESSED AFTER PAUSED
                            {
                                continue;
                            }
                        }    
                    }
                    Done_Oven();
                    break;

                case 'C':                                          // IF C IS PRESSED CHICKEN
                    LCD_Move_Cursor(1,1);
                    LCD_Send_String ("Chicken Weight ?");          // ASKING USER FOR WEIGHT
                    while (Keypad_Input == 0xFF)                   // WAIT FOR USER INPUT
                    {

                    }                  
                    LCD_Move_Cursor(1,10);
                    //if (Keypad_Input == '1' || Keypad_Input == '2' || Keypad_Input == '3' || Keypad_Input == '4' || Keypad_Input == '5' || Keypad_Input == '6' || Keypad_Input == '7' || Keypad_Input == '8' || Keypad_Input == '9')
                    if (Keypad_Input_Int >= 1 && Keypad_Input_Int <= 9)
                    {
                        LCD_Send_String(Keypad_Input);             // SHOWING ENTERED NUMBER FROM 1 - 9 ON LCD
                    }
                    else{                                          // IF ENTETRED ANYTHING ELSE (1-9)
                        LCD_Send_String ("Err"); 
                    }
                    genericDelay(2000);
                    LCD_CLR_Screen();
                    LCD_Send_String ("Press Start");
                    while (Switch_Read(F,0) != '0')
                    {
                                                                    // IF SWITCH 2 (START) NOT PRESSED DO NOTHING
                    }
                    time = (12 * Keypad_Input_Int);                 // CONVERT FROM CHAR TO INT AND THEN GET TIME 12 SEC FOR EACH KILO
                    for (time; time > 0; time--)
                    {
                        if (Switch_Read(F,4) != '0')  // IF SWITCH 1 (PAUSE) NOT PRESSED
                        {
                            LED_ON(F,1);
                            LED_ON(F,2);
                            LED_ON(F,3);
                            LCD_CLR_Screen(); 
                            LCD_Move_Cursor(2,1);
                            LCD_Send_String ("Time Left: ");
                            LCD_Move_Cursor(2,10);
                            LCD_Send_Int(time);
                            genericDelay(1000);
                        }
                        else if (Switch_Read(F,4) == '0')    // IF SWITCH 1 (PAUSE) IS PRESSED FIRST TIME
                        {
                            while (Switch_Read(F,4) != '0' || Switch_Read(F,0) != '0')  // STAY IN THE LOOP AS LONG AS (STOP/START NOT PRESSED)
                            {                        
                                LED_TGL(F,1);
                                LED_TGL(F,2);
                                LED_TGL(F,3);      //LEDS KEEP TOGLING WHILE PAUSED  (APPLY TO OTHER CASES)
                                genericDelay(500);
                            }
                            if (Switch_Read(F,4) == '0')
                            {
                                Stop_Oven ();               // IF SWITCH 1 (STOP) IS PRESSED SECOND TIME
                            }
                            else if (Switch_Read(F,0) == '0') // IF SWITCH 2 (START) IS PRESSED AFTER PAUSED
                            {
                                continue;
                            }
                        }    
                    }
                    Done_Oven();
                    break;

                case 'D':
                    LCD_Move_Cursor(1,1);                        // IF C IS PRESSED CHICKEN
                    LCD_Send_String ("Cooking Time ?");          // ASKING USER FOR TIME
                    while (Keypad_Input == 0xFF)                   // WAIT FOR USER INPUT
                    {

                    }
                    LCD_Move_Cursor(2,10);
                    /*char arr[] = "00000";
                    int counter = 5;
                    int last_char = 0;
                    int value = 1;
                    int numberofdigits = 0;
                    while (counter-- != 0)
                    {
    1                    value = Keypad_Input_Int + last_char * 10;
                        arr[counter]=value;
                        // convert value from int to string and put it in arr (itoa function)
                        LCD_Send_String (arr);
                        last_char = value;
                        numberofdigits++;
                    }
                    if (numberofdigits > 2)
                    {
                        arr[2] = ':';
                    }
                    LCD_Send_String (arr);*/
                    LCD_CLR_Screen();
                    LCD_Send_String ("Press Start");
                    while (Switch_Read(F,0) != '0')
                    {
                                                                    // IF SWITCH 2 (START) NOT PRESSED DO NOTHING
                    }
    2                //time = ();                 // CONVERT TIME FROM XX:XX FORMAT TO SECS
                    for (time; time > 0; time--)
                    {
                        if (Switch_Read(F,4) != '0')  // IF SWITCH 1 (PAUSE) NOT PRESSED
                        {
                            LED_ON(F,1);
                            LED_ON(F,2);
                            LED_ON(F,3);
                            LCD_CLR_Screen(); 
                            LCD_Move_Cursor(2,1);
                            LCD_Send_String ("Time Left: ");
                            LCD_Move_Cursor(2,10);
                            LCD_Send_Int(time);
                            genericDelay(1000);
                        }
                        else if (Switch_Read(F,4) == '0')    // IF SWITCH 1 (PAUSE) IS PRESSED FIRST TIME
                        {
                            while (Switch_Read(F,4) != '0' || Switch_Read(F,0) != '0')  // STAY IN THE LOOP AS LONG AS (STOP/START NOT PRESSED)
                            {                        
                                LED_TGL(F,1);
                                LED_TGL(F,2);
                                LED_TGL(F,3);      //LEDS KEEP TOGLING WHILE PAUSED  (APPLY TO OTHER CASES)
                                genericDelay(500);
                            }
                            if (Switch_Read(F,4) == '0')
                            {
                                Stop_Oven ();               // IF SWITCH 1 (STOP) IS PRESSED SECOND TIME
                            }
                            else if (Switch_Read(F,0) == '0') // IF SWITCH 2 (START) IS PRESSED AFTER PAUSED
                            {
                                continue;
                            }
                        }   
                    }
                    Done_Oven();
                    break;

                default:
                    LCD_Send_String ("Wrong Input");    // IF USER ENTERED ELSE (A,B,C,D)
                    Stop_Oven();
            }
        }
    }
}
