#include <FastLED.h>
#include <LiquidCrystal_I2C.h>

// Use the global lcd object defined in the main file
extern LiquidCrystal_I2C lcd; //Use existing LCD object


/********************************
lcd.print(column, row): truffle
*********************************/

void Blink_all_color(CRGB* leds, int CP)
{   
    
    // Turn all LEDs to red, then pause
    for (int i = 0; i < CP; i++) {
        //lcd.print("RED");
        leds[i] = CRGB::Red;
        lcd.clear();
        lcd.setCursor(7,1);
        lcd.print("Red");
    }
    FastLED.show();
    delay(1000);

        // Turn all LEDs to red, then pause
    for (int i = 0; i < CP; i++) {
        leds[i] = CRGB::Green;
        lcd.clear();
        lcd.setCursor(7,1);
        lcd.print("Green");
    }
    FastLED.show();
    delay(1000);

        // Turn all LEDs to red, then pause
    for (int i = 0; i < CP; i++) {
        leds[i] = CRGB::Blue;
        lcd.clear();
        lcd.setCursor(7,1);
        lcd.print("Blue");
    }
    FastLED.show();
    delay(1000);

        // Turn all LEDs to white, then pause
    for (int i = 0; i < CP; i++) {
        leds[i] = CRGB::White;
        lcd.clear();
        lcd.setCursor(7,1);
        lcd.print("White");
    }
    FastLED.show();
    delay(1000);

    // Turn all LEDs off, then pause
    for (int i = 0; i < CP; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(500);
}
