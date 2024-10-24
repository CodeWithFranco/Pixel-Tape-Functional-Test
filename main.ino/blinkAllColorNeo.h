#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIN        11           // Pin where your NeoPixel strip is connected

extern LiquidCrystal_I2C lcd; //Use existing LCD object
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, LED_TYPE + NEO_KHZ800); // Initialize with 0 LEDs initially

// Forward declaration of the setAllPixels function
void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

void BlinkAllColorNeo(int CP) 
{
  Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
  // Dynamically set the number of LEDs based on the user input (CP)
  strip.updateLength(CP);  // Update the length of the strip with the user input
  strip.begin();           // Initialize the strip
  strip.show();            // Turn all LEDs off to start

  // Turn all LEDs red
  setAllPixels(CP, 0, 255, 0, 0);  // Red color
  strip.show();                    // Update the strip to show the red color
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("Red");
  delay(1000);                     // Wait for 1000 milliseconds (on time)

  setAllPixels(CP, 255, 0, 0, 0);  // Green color
  strip.show();                    // Update the strip to show the green color
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("Green");
  delay(1000);                     // Wait for 1000 milliseconds (on time)

  setAllPixels(CP, 0, 0, 255, 0);  // Blue color
  strip.show();                    // Update the strip to show the blue color
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("Blue");
  delay(1000);                     // Wait for 1000 milliseconds (on time)

  setAllPixels(CP, 0, 0, 0, 255);  // White/Yellow color
  strip.show();                    // Update the strip to show the white/yellow color
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("White");
  delay(1000);                     // Wait for 1000 milliseconds (on time)

  // Turn all LEDs off
  setAllPixels(CP, 0, 0, 0, 0);    // Black/off color
  strip.show();                    // Update the strip to turn off the LEDs
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("Wait...");
  delay(500);                     // Wait for 2000 milliseconds (off time)
}

// Helper function to set all pixels to a given color
void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
  Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
  for (int i = 0; i < CP; i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue, white));
  }
}

void ws2814(int CP)
{
  // Start with NEO_GRBW, but try NEO_RGBW and NEO_BRGW if it doesn't work.
  Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_RGBW + NEO_KHZ800);  // Start with RGBW, switch if necessary

  strip.begin();
  strip.show();  // Initialize all pixels to 'off'

  //White
  strip.setPixelColor(0, strip.Color(255, 0, 0, 0));  // Red
  strip.show();
  delay(5000);

  //Red
  strip.setPixelColor(0, strip.Color(0, 255, 0, 0));  // Green
  strip.show();
  delay(1000);

  //Green
  strip.setPixelColor(0, strip.Color(0, 0, 255, 0));  // Blue
  strip.show();
  delay(1000);

  /Bluee
  strip.setPixelColor(0, strip.Color(0, 0, 0, 255));  // White (using the W channel)
  strip.show();
  delay(1000);
}
