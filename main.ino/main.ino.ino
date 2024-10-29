/********************************************************
Title: Pixel Tapelight Functional Test Code             *
Author: Franco Nepomuceno                               *
Date: 9/10/24                                           *
Rev: B                                                  *
Description:                                            *
Added W28214                                            *
a. WS2811                                               *
b. UCS2804B                                             *
c. TX1818 
d. WS2814                                              *
                                                        *    
Note#1: LED driver is the chip that controls the LEDs   *   
on tapelight. In this code, the name changed into       *
chipset as the company uses 'driver' as the name for    *
power supply.                                           *
                                                        *
Note#2: WS2811 and TX1818 have the same library while   *
UCS2904B has its own using NEOPIXEL.                    *
a. WS2811: FASTLED                                      *
b. TX1818: FASLED                                       *
c. UCS2904B: NEOPIXEL  
d. WS2814: NEOPIXEL with some alteration                *
                                                        *
Note#3: Processing user input are basically copies of   *  
cpAnswerKeypad.h with variable input LCD display        *
location and memory variable name                       *  
                                                        *
********************************************************/

#include <FastLED.h>
#include "blinkAllColorFast.h"                                                //FASTLED Lib
#include "colorRaceFast.h"                                                    //FASTLED Lib
#include "driverquestion.h"
#include "setupQuestion.h"
#include "blinkAllColorNeo.h"
#include "colorRaceNeo.h"
#include "cpAnswerKeypad.h"                                               //processKeypadCP() 
#include "chipsetAnswerKeypad.h"                                          //processKeypadChipset() 
#include "endTestAnswerKeypad.h" 
#include "setupAnswerKeypad.h"
#include "dimmingFast.h"                                         //processKeypadEndTest()
#include "dimmingNeo.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);   // Set the LCD address to 0x3F for 16 chars

#define DATA_PIN 11
#define MAX_CP 500                    //Subject to change

CRGB *leds;                          // Allocated array for FASTLEDs - Pointer 

// Global variables for user input
int CP = 0;                           // Initial cut-points (CP) value
int chipset = 0;                      // Initial LedDriver value
int endTest = 0;                      // Routine
//int user_confirmation_1 = 0;
//int user_confirmation_2 = 0;
// Allocate memory --> User char input from keypad
char* CP_userInput;                
char* chipset_userInput;   
char* ET_userInput;

void setup() 
{
  lcd.init();           // Initialize the LCD
  lcd.backlight();      // Turn on the backlight

  // Start Serial and set-up --> Welcome Screen
  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(3, 1);                                  //LCD --> (COLUMN, ROW)
  lcd.print("Welcome to the");
  lcd.setCursor(3, 2);
  lcd.print("Pixel Test Kit");
  lcd.setCursor(8, 3);
  lcd.print("Rev B");                                   //Change if revised
  delay(6000);
  lcd.clear();

  /*This is just a set of question to set up the equipment*/
  setup_question();                 //Keypad answers and conversion inside this file unlike the next questions. 

  /********************************************
   * Ask the user for the number of cut-points *
   *********************************************/
  lcd.clear();
  lcd.setCursor(0, 0);                                 //LCD --> (COLUMN, ROW)
  lcd.print("Enter the # of CPs");                    //Enter Cut Points
  lcd.setCursor(0, 1);
  lcd.print("'#' to ENTER");
  lcd.setCursor(0, 2);
  lcd.print("'*' to BACKSPACE");
  
  CP_userInput = processKeypadCP();
  CP = atoi(CP_userInput);                              //Changes from char type to int type
  //Check value and goes to LCD
  /*lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print(CP);
  delay(10000);*/

  /***************Serial Interface / Keyboard***********************************************
  while (Serial.available() == 0) {}  // Wait for user to input number of CPs

  CP = Serial.parseInt(); // Ensure it doesn't exceed max CPs. Value goes to cut_points
  ******************************************************************************************/
  /*Check for MAX cut points*/ 
  if (CP > MAX_CP) 
  {
    CP = MAX_CP;
  }
  else if (CP <= 0)
  {
    CP = 1; // Make sure it's at least 1
  }

  leds = new CRGB[CP];      //  Allocate memory for the LED array based on user input
  
  /*
  // Clear the serial buffer to remove any leftover input from the previous read
  while (Serial.available() > 0) 
  {
    Serial.read();  // Discard leftover characters
  }
  */
  /*******************************************************************
   * Ask the user for the kind of LED driver for the tapelight.       *
   * This section should be revised when new LED driver is introduced.*
   ********************************************************************/
  digitCount = 0;
  page_1_chipSelect();                                   //Just a introduction page for chip selection 1.5sec delay
  page_2_chipSelect();                                   // Ask for LED driver selection

  chipset_userInput = processKeypadChipset();
  chipset = atoi(chipset_userInput);                         //Change char type to int type

  bool valid_answer = false;
  while (!valid_answer)                                 // Loop while answer is incorrect
  {
    switch (chipset)
    {
      case 1: // WS2811 or TX1818
      case 2: // UCS2904B
      case 3: //WS2814
        valid_answer = true;                                    //Loop exit   
        break;

      default: // Invalid Choice
        lcd.clear();
        lcd.setCursor(0, 2);
        lcd.print("Invalid choice");
        page_2_chipSelect();    
        chipset_userInput = processKeypadChipset();
        chipset = atoi(chipset_userInput);                     //Changes from char type to int type
        break;
    }
  }
}

  

void loop() 
{
  if (chipset == 1)
  {
  
    Blink_all_color(leds, CP);
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.print("Wait...");
    delay(1500);
    Color_race(leds, CP);
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.print("Wait...");
    delay(1500);
    AutoDim_all_color(leds, CP, 255);

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("End test? 1-Yes 2-No");

    ET_userInput = processKeypadEndTest();
    endTest = atoi(ET_userInput); 

    bool endprogram = false;
    while(!endprogram){
      switch(endTest){
        case 1: 
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("Restarting prog..");
          delay(1000);
          //Soft reset
          asm volatile("jmp 0");
          break;
        
        case 2:
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("Continue test");
          delay(1000);
           // No need for `continue`, the loop will naturally repeat
           break;
        
        default:
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("LOL! Really?");
          lcd.setCursor(0, 2);
          lcd.print("Wrong input");
          lcd.setCursor(0, 3);
          lcd.print("BACK TO HOMEPAGE");
          delay(2500);
          asm volatile("jmp 0"); //Soft restart
          break;
      }
    }
  }
  else if (chipset == 2)
  {
     // Execute the LED driver 2 logic
    BlinkAllColorNeo(CP);
    lcd.setCursor(7,1);
    lcd.print("Wait...");
    delay(1500);
    ColorRaceNeo(CP); 
    delay(500);
    lcd.setCursor(7,1);
    lcd.print("Wait...");
    delay(1500);
    UCS2904B_2(CP);

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("End test? 1-Yes 2-No");

    bool endprogram = false;
    while(!endprogram){
      switch(endTest){
        case 1: 
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("Restarting prog..");
          delay(1000);
          //Soft reset
          asm volatile("jmp 0");
          break;
        
        case 2:
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("Continue test");
          delay(1000);
           // No need for `continue`, the loop will naturally repeat
           break;
        
        default:
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("LOL! Really?");
          lcd.setCursor(0, 2);
          lcd.print("Wrong input");
          lcd.setCursor(0, 3);
          lcd.print("BACK TO HOMEPAGE");
          delay(2500);
          asm volatile("jmp 0"); //Soft restart
          break;
      } 
    }
  }
    else if (chipset == 3){
      ws2814_blink(CP);
    }
    
}