#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Use the global lcd object defined in the main file
extern LiquidCrystal_I2C lcd; //Use existing LCD object

// Declare the setupKeypadInput function here
extern char* setupKeypadInput();  // Declare as extern to let the linker find its definition
int user_confirmation_1 = 0;
int user_confirmation_2 = 0;

void question_1();
void question_2();

void setup_question()
{
  // Ask question 1
  question_1();
  user_confirmation_1 = atoi(setupKeypadInput());  // Process keypad input
  
  bool valid_answer = false;
  while (!valid_answer)                                 // Loop while answer is incorrect
  {
    switch(user_confirmation_1)
    {
      case 1: //The only valid answer
      lcd.clear();
      lcd.setCursor(3, 1);
      lcd.print("Ok, next step!");
      delay(1500);
      valid_answer = true;
      break;
    
    default: //Any other choice
      lcd.clear();
      lcd.setCursor(3, 1);
      lcd.print("LOL. Try again!");
      delay(1500);
      question_1();
      user_confirmation_1 = atoi(setupKeypadInput());  // Process keypad input
    }
  }

  // Ask question 2
  question_2();
  user_confirmation_2 = atoi(setupKeypadInput());  // Process keypad input

  valid_answer = false;
  while (!valid_answer)                                 // Loop while answer is incorrect
  {
    switch(user_confirmation_2)
    {
      case 1: //The only valid answer
      lcd.clear();
      lcd.setCursor(3, 1);
      lcd.print("Ok, next step!");
      delay(1500);
      valid_answer = true;
      break;
    
    default: //Any other choice
      lcd.clear();
      lcd.setCursor(3, 1);
      lcd.print("LOL. Try again!");
      delay(1500);
      question_2();
      user_confirmation_2 = atoi(setupKeypadInput());  // Process keypad input
    }
  }
}

void question_1()
{
  lcd.setCursor(0, 0);
  lcd.print("Read BOM for Vin");
  lcd.setCursor(0, 1); 
  lcd.print("Verify: 24v or 12v");
  lcd.setCursor(0, 2);
  lcd.print("Press '1' to confirm");
  lcd.setCursor(0, 3);
  lcd.print("Press '#' to ENTER");
}

void question_2()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connect TapeLight");
  lcd.setCursor(0, 1);
  lcd.print("Turn Vin switch ON");
  lcd.setCursor(0, 2);
  lcd.print("Press '1' to confirm");
  lcd.setCursor(0, 3);
  lcd.print("Press '#' to ENTER");
}


