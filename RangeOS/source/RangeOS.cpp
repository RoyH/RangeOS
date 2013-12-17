#include "RangeOS_main.h"



/* RangeTimingOS. System
 * Roy H ver 0.1
 */
// Library Declarations
#include <Keypad.h>
#include <Adafruit_CharacterOLED.h>//include the OLED library 


//-------KEYPAD SETUP--------------------------------------------------------------------------
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {
    '1','2','3'  }
  ,
  {
    '4','5','6'  }
  ,
  {
    '7','8','9'  }
  ,
  {
    '*','0','#'  }
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {
  14, 15, 16, 17}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  18, 19, 20}; //connect to the column pinouts of the keypad
// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//---------------------------------------------------------------------------------------------

//------OLEDSETUP------------------------------------------------------------------------------

Adafruit_CharacterOLED lcd(6, 7, 8, 9, 10, 11, 12);

//---------------------------------------------------------------------------------------------


void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
 

  lcd.begin(16, 2);// Initialize the LCD with 16 characters and 2 lines

}

int state = 1; //setting the initial state


void loop()
{

  while(state == 1) {
    homeScreen(); // loads boot screen
    switch (keyPress()) {
      case('#') :
      state = 2;
      lcd.clear();

    }
  }

  while(state == 2) {
   
   entryScreen();
  }

}





// METHODS

void homeScreen() { // Load Bootscreen Method
  lcd.setCursor(0,0);
  lcd.print("RANGE TIMING OS");
  lcd.setCursor(0,1);
  lcd.print("Press # to start");

}


char keyPress() {
  char key = kpd.getKey();
  return key;
}

void entryScreen() {
  lcd.setCursor(0,0);
  lcd.print("Enter Time");
}


