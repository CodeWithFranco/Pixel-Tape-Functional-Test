/* Add chipset /LED driver in the future*
****************************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Use the global lcd object defined in the main file
extern LiquidCrystal_I2C lcd; //Use existing LCD object

void Driver_question()
{
  lcd.clear();
  
  //Ask for driver selection
  lcd.setCursor(0, 0);
  lcd.print("What chipset are");
  lcd.setCursor(0, 1);
  lcd.print("you using? ");
  lcd.setCursor(0, 2);
  lcd.print("1: WS2811 or TX1818");
  lcd.setCursor(0, 3);
  lcd.print("2: UCS2904B");
}