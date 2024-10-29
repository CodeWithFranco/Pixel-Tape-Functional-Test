#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIN            11           // Pin where your NeoPixel strip is connected
#define LED_TYPE       NEO_GRBW     // Set this to NEO_GRBW if your strip is RGBW (with a white channel)
//#define LEDS_PER_DRIVER 1          // Define how many LEDs each driver controls

extern Adafruit_NeoPixel strip;  //Use existing Adafruit object
extern LiquidCrystal_I2C lcd; //Use existing LCD object

// Forward declaration of the setPixelColor function
void setPixelColor(int ledIndex, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

void USC2904B_race(int CP) 
{
  //int totalLEDs = CP; // Calculate the total number of LEDs
  strip.updateLength(CP);                // Update the length of the strip with total number of LEDs
  strip.begin();                        // Initialize the strip
  strip.show();                         // Turn all LEDs off to start

  // Set individual LEDs to different colors, one per driver
  for (int i = 0; i < CP; i++) {
    setPixelColor(i, 0, 255, 0, 0); // Set LED to red
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.print("Red");
    strip.show();                   // Update the strip
    delay(100);                    
    setPixelColor(i, 0, 0, 0, 0);
  }

  delay(250);  

  for (int i = 0; i < CP; i++) {
    setPixelColor(i, 255, 0, 0, 0); // Set LED to green
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.print("Green");
    strip.show();                   // Update the strip
    delay(100);                    
    setPixelColor(i, 0, 0, 0, 0);
  }

  delay(250);  

  for (int i = 0; i < CP; i++) {
    setPixelColor(i, 0, 0, 255, 0); // Set LED to blue
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.print("Blue");
    strip.show();                   // Update the strip
    delay(100);                     
    setPixelColor(i, 0, 0, 0, 0);
  }

  delay(250);  

  for (int i = 0; i < CP; i++) {
    setPixelColor(i, 0, 0, 0, 255); // Set LED to white
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.print("White");
    strip.show();                   // Update the strip
    delay(100);                    
    setPixelColor(i, 0, 0, 0, 0);
  }

  delay(50); 

  // Turn all LEDs off one by one
  for (int i = 0; i < CP; i++) {
    setPixelColor(i, 0, 0, 0, 0);   // Turn off the LED
    strip.show();                   // Update the strip
    delay(250);                   
  }
}

// Helper function to set a single pixel to a given color
void setPixelColor(int ledIndex, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
  strip.setPixelColor(ledIndex, strip.Color(red, green, blue, white));
}

void WS2814_race(int CP){
  Adafruit_NeoPixel strip = Adafruit_NeoPixel(CP, PIN, NEO_RGBW + NEO_KHZ800);
  strip.begin();
  strip.show();
  
  for(int i = 0; i < CP; i++){
    strip.setPixelColor(i, strip.Color(255, 0, 0, 0)); //White
    lcd.clear();
    lcd.setCursor(7, 1);
    lcd.print("White");
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 0, 0, 0)); //Turn off proceeding CPs
  }
  delay(250);

  for (int i = 0; i < CP; i++){
    strip.setPixelColor(i, strip.Color(0, 255, 0, 0)); //Red
    lcd.clear();
    lcd.setCursor(7, 1);
    lcd.print("Red");
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 0, 0, 0)); //Turn off proceeding CPs
  }
  delay(250);

    for (int i = 0; i < CP; i++){
      strip.setPixelColor(i, strip.Color(0, 0, 255, 0)); //Green
      lcd.clear();
      lcd.setCursor(7, 1);
      lcd.print("Green");
      strip.show();
      delay(100);
      strip.setPixelColor(i, strip.Color(0, 0, 0, 0)); //Turn off proceeding CPs
    }
    delay(250);

    for (int i = 0; i < CP; i++){
      strip.setPixelColor(i, strip.Color(0, 0, 0, 255)); // Blue
      lcd.clear();
      lcd.setCursor(7, 1);
      lcd.print("Blue");
      strip.show();
      delay(100);
      strip.setPixelColor(i, strip.Color(0, 0, 0, 0)); //Turn off proceeding CPs
    }
    delay(50);

    // for (int i = 0; i < CP; i++){
    //   strip.setPixelColor(i, strip.Color(0, 0, 0, 0)); //Turn off each CP
    //   strip.show();
    //   delay(250);
    // }
}