// setupAnswerKeypad.h
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Declare the global variables for the keypad
extern Keypad customKeypad;
extern LiquidCrystal_I2C lcd;

// Buffer to hold 2 digits + null terminator
char setup_input[3];  // Char array to store 1-2 digits
extern byte digitCount;  // To track the number of digits entered

// Define the setupKeypadInput function here
char* setupKeypadInput() 
{
  digitCount = 0;
  lcd.setCursor(17, 0);  // Set cursor position on the LCD

  while (true) {
    char customKey = customKeypad.getKey();
    
    if (customKey) {
      if (customKey >= '0' && customKey <= '9') {
        // If a digit is pressed and we haven't reached 2 digits
        if (digitCount < 2) {
          setup_input[digitCount] = customKey;
          lcd.setCursor(18 + digitCount, 0);
          lcd.print(customKey);
          digitCount++;
        }
      } else if (customKey == '#') {
        // If the '#' (Enter) key is pressed
        setup_input[digitCount] = '\0';  // Null-terminate the input string
        return setup_input;  // Return the entered input
      } else if (customKey == '*') {
        // If the '*' key (Backspace) is pressed
        if (digitCount > 0) {
          digitCount--;  // Move back in the input array
          setup_input[digitCount] = '\0';  // Null out the last character
          lcd.setCursor(18 + digitCount, 0);  // Set cursor at the right position
          lcd.print(" ");  // Clear the last character on the LCD
          lcd.setCursor(18 + digitCount, 0);  // Move cursor back to the cleared position
        }
      }
    }
  }
}
