#include <FastLED.h>
#include <LiquidCrystal_I2C.h>

// Use the global lcd object defined in the main file
extern LiquidCrystal_I2C lcd; // Use existing LCD object

/********************************
lcd.print(column, row): truffle
*********************************/

void AutoDim_all_color(CRGB* leds, int CP, int maxBrightness)
{   
    // Array of selected colors (Red, Green, Blue, White)
    CRGB colors[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::White};
    const char* colorNames[] = {"Red", "Green", "Blue", "White"};

    // Loop through the selected colors
    for (int colorIndex = 0; colorIndex < 4; colorIndex++) {
        
        // Gradually dim the brightness from maxBrightness to 0
        for (int b = maxBrightness; b >= 0; b -= 10) {  // Adjust step size for smooth dimming

            // Set each LED to the current color and dim it
            for (int i = 0; i < CP; i++) {
                leds[i] = colors[colorIndex];
                leds[i].fadeLightBy(255 - b);  // Adjust brightness by fading
            }
            
            // Update the LCD with the current color and brightness
            lcd.clear();
            lcd.setCursor(7, 1);
            lcd.print(colorNames[colorIndex]);
            //lcd.setCursor(7, 2);
            //lcd.print("Brightness: ");
            //lcd.print(b);

            FastLED.show();
            delay(100);  // Delay for smoother transitions
        }

        // Pause briefly before switching to the next color
        delay(500);
    }

    // Turn all LEDs off after the cycle
    for (int i = 0; i < CP; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(500);
}
