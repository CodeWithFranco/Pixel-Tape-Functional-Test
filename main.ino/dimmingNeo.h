#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIN            11           // Pin where your NeoPixel strip is connected
#define LED_TYPE       NEO_GRBW     // Set this to NEO_GRBW if your strip is RGBW (with a white channel)

extern LiquidCrystal_I2C lcd; // Use existing LCD object

// Define the NeoPixel strip object with 0 LEDs initially (you will update length in the function)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, LED_TYPE + NEO_KHZ800);

// Extern declaration for setPixelColor (defined in another file)
extern void setPixelColor(int ledIndex, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
extern Adafruit_NeoPixel strip; //main declaration is in blinkAllColorNeo

// Forward declaration of dimAllLEDs function
void dimAllLEDs(int CP, const char* colorName, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

// Function to dim the LEDs gradually for all LEDs
void UCS2904B_dimming(int CP) {
  strip.updateLength(CP);  // Update the length of the strip to CP LEDs
  strip.begin();           // Initialize the strip
  strip.show();            // Turn all LEDs off to start

  // Dimming effect for Red, Green, Blue, and White colors on all LEDs
  dimAllLEDs(CP, "Red", 0, 255, 0, 0);
  dimAllLEDs(CP, "Green", 255, 0, 0, 0);
  dimAllLEDs(CP, "Blue", 0, 0, 255, 0);
  dimAllLEDs(CP, "White", 0, 0, 0, 255);

  // Turn all LEDs off
  for (int i = 0; i < CP; i++) {
    setPixelColor(i, 0, 0, 0, 0);   // Turn off the LED
  }
  strip.show();                   // Update the strip
}

// Helper function to gradually dim all LEDs with a specific color
void dimAllLEDs(int CP, const char* colorName, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
  // Increase brightness gradually for all LEDs
  for (int brightness = 0; brightness <= 255; brightness += 5) {  
    for (int i = 0; i < CP; i++) {
      setPixelColor(i, (red * brightness) / 255, (green * brightness) / 255, (blue * brightness) / 255, (white * brightness) / 255);
    }
    strip.show();  // Update the strip

    // Update the LCD display
    lcd.clear();
    lcd.setCursor(7, 1);
    lcd.print(colorName);

    delay(20);  // Small delay for smooth dimming effect
  }

  delay(500);  // Wait for 500 milliseconds before switching to the next color

  // Decrease brightness gradually for all LEDs
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    for (int i = 0; i < CP; i++) {
      setPixelColor(i, (red * brightness) / 255, (green * brightness) / 255, (blue * brightness) / 255, (white * brightness) / 255);
    }
    strip.show();  // Update the strip
    delay(20);     // Small delay for smooth dimming effect
  }
}

