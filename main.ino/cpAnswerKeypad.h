#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Keypad setup
const byte ROWS = 4; // 4 rows
const byte COLS = 4; // 4 columns

// Define the keymap
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connect keypad rows and columns to Arduino pins
byte rowPins[ROWS] = {9, 8, 7, 6};  // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2};  // Connect to the column pinouts of the keypad

// Create the keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Buffer to hold 2 digits + null terminator
char user_input[3];             // Char array to store 1-2 digits - user_input[0]-[2]
byte digitCount = 0;            // To track the number of digits entered

void initKeypadLCD() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Print initial message
  lcd.setCursor(0, 0);
  lcd.print("Enter digits:");
  lcd.setCursor(0, 1);
}

char* processKeypadCP() 
{
  digitCount = 0;                                        //Number of digits pressed by user
  lcd.setCursor(16, 3);                                   //LCD --> (COLUMN, ROW)
  

  while (true) {
    char customKey = customKeypad.getKey();
    
    if (customKey) {
      if (customKey >= '0' && customKey <= '9') {
        // If a digit is pressed and we haven't reached 2 digits
        if ( digitCount < 3) {
          user_input[digitCount] = customKey;            // Store the digit in user_input
          lcd.setCursor(9 + digitCount, 3);              // Move the cursor based on the digits
          digitCount++;                                  // Move to the next position
          lcd.print(customKey);                         // Show the digit as it's typed

          /*Programmer Check digit count --> hide if not needed*/
          //lcd.setCursor(9, 3);                          
          //lcd.print(digitCount);
        }
      } else if (customKey == '#') {
        // If the '#' (Enter) key is pressed
        user_input[digitCount] = '\0';         // Null-terminate the input string

        // Return the entered input to the main function
        return user_input;
      } else if (customKey == '*') {
        // If the '*' key (Backspace) is pressed
        if (digitCount > 0) {
          digitCount--;                           // Move back in the input array
          user_input[digitCount] = '\0';               // Null out the last character
          
          // Update the LCD to reflect the change
          lcd.setCursor(9 + digitCount, 3);        // Set the cursor at the right position
          lcd.print(" ");                          // Clear the last character on the LCD
          lcd.setCursor(9 + digitCount, 3);       // Move cursor back to the cleared position
        }
      }
    }
  }
}