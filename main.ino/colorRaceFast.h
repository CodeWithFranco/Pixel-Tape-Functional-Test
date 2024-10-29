#include <FastLED.h>
#include <LiquidCrystal_I2C.h>

// Use the global lcd object defined in the main file
extern LiquidCrystal_I2C lcd; //Use existing LCD object

void Color_race(CRGB* leds, int cut_points)
{
  for(int i = 0; i <= cut_points; i++)   
  {   
    leds[i] = CRGB::Red;
    FastLED.show();
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.print("Red");
    leds[i] = CRGB::Black;   
    delay(100);  
  } 
  for(int i = 0; i <= cut_points; i++)   
  {   
     leds[i] = CRGB::Green;
     FastLED.show();
      lcd.clear();
      lcd.setCursor(7,1);
      lcd.print("Green");
     leds[i] = CRGB::Black;   
     delay(100);  
  } 
  for(int i = 0; i <= cut_points; i++)   
  {   
     leds[i] = CRGB::Blue;
     FastLED.show();
     lcd.clear();
     lcd.setCursor(7,1);
     lcd.print("Blue");
     leds[i] = CRGB::Black;   
     delay(100); 
  } 
  for(int i = 0; i <= cut_points; i++)   
  {  
    leds[i] = CRGB::White;
    FastLED.show();
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.print("White");
    leds[i] = CRGB::Black;   
    delay(100); 
  } 
}


