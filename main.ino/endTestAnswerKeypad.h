#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Keypad setup
extern const byte ROWS; // 4 rows
extern const byte COLS; // 4 columns

// Define the keymap
extern char hexaKeys[ROWS][COLS];

// Connect keypad rows and columns to Arduino pins
extern byte rowPins[ROWS];  // Connect to the row pinouts of the keypad
extern byte colPins[COLS];  // Connect to the column pinouts of the keypad

// Create the keypad object
extern Keypad customKeypad;

// Buffer to hold 2 digits + null terminator
char endTest_input[3];             // Char array to store 1-2 digits - user_input[0]-[2]
extern byte digitCount;            // To track the number of digits entered

char* processKeypadEndTest() 
{
  digitCount = 0;                                        //Number of digits pressed by user
  lcd.setCursor(9, 3);                                   //LCD --> (COLUMN, ROW)
  

  while (true) {
    char customKey = customKeypad.getKey();
    
    if (customKey) {
      if (customKey >= '0' && customKey <= '9') {
        // If a digit is pressed and we haven't reached 2 digits
        if ( digitCount < 3) {
          endTest_input[digitCount] = customKey;            // Store the digit in user_input
          lcd.setCursor(9 + digitCount, 3);              // Move the cursor based on the digits
          digitCount++;                                  // Move to the next position
          lcd.print(customKey);                         // Show the digit as it's typed

          /*Programmer Check digit count --> hide if not needed*/
          //lcd.setCursor(9, 3);                          
          //lcd.print(digitCount);
        }
      } else if (customKey == '#') {
        // If the '#' (Enter) key is pressed
        endTest_input[digitCount] = '\0';         // Null-terminate the input string

        // Return the entered input to the main function
        return endTest_input;
      } else if (customKey == '*') {
        // If the '*' key (Backspace) is pressed
        if (digitCount > 0) {
          digitCount--;                           // Move back in the input array
          endTest_input[digitCount] = '\0';               // Null out the last character
          
          // Update the LCD to reflect the change
          lcd.setCursor(9 + digitCount, 3);        // Set the cursor at the right position
          lcd.print(" ");                          // Clear the last character on the LCD
          lcd.setCursor(9 + digitCount, 3);       // Move cursor back to the cleared position
        }
      }
    }
  }
}