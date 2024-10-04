#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Use the global lcd object defined in the main file
extern LiquidCrystal_I2C lcd; //Use existing LCD object

// Declare the setupKeypadInput function here
extern char* setupKeypadInput();  // Declare as extern to let the linker find its definition


void question_1();
void question_2();

void setup_question(int &user_confirmation_1, int &user_confirmation_2)
{
  // Ask question 1
  question_1();
  user_confirmation_1 = atoi(setupKeypadInput());  // Process keypad input
  
  // Validate the answer
  if (user_confirmation_1 == 1) {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Ok, next step!");
    delay(1500);
    lcd.clear();
  } else {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("LOL. Try again!");
    delay(1500);
    setup_question(user_confirmation_1, user_confirmation_2);  // Retry question
  }

  // Ask question 2
  question_2();
  user_confirmation_2 = atoi(setupKeypadInput());  // Process keypad input
  
  // Validate the answer
  if (user_confirmation_2 == 1) {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Ok, next step!");
    delay(1500);
    lcd.clear();
  } else {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("LOL. Try again!");
    delay(1500);
    setup_question(user_confirmation_1, user_confirmation_2);  // Retry question
  }
}

void question_1()
{
  lcd.setCursor(0, 0);
  lcd.print("Connect tapelight.");
  lcd.setCursor(0, 1); 
  lcd.print("Verify: 24v or 12v");
  lcd.setCursor(0, 2);
  lcd.print("Press '1' to confirm");
}

void question_2()
{
  lcd.setCursor(0, 0);
  lcd.print("Plug in VAC for UUT");
  lcd.setCursor(0, 1);
  lcd.print("Verify UUT Vin(-_-)");
  lcd.setCursor(0, 2);
  lcd.print("Press '1' to confirm");
}


