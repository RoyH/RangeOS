

/* RangeTimingOS. System
 * Roy H ver 0.1
 */
// Library Declarations
#include <Keypad.h>
#include <Adafruit_CharacterOLED.h>//include the OLED library
#include <Shifter.h>



//-------KEYPAD SETUP--------------------------------------------------------------------------
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {
    '1','2','3'            }
  ,
  {
    '4','5','6'            }
  ,
  {
    '7','8','9'            }
  ,
  {
    '*','0','#'            }
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

// Shifter Setup

Shifter shifter(2, 2, 3, 4);  //Setup Shifter instance with number of digits and pin numbers





void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  shifter.clear();

  lcd.begin(16, 2);// Initialize the LCD with 16 characters and 2 lines

}


//list of screens
int HOME_SCREEN = 1;
int INPUT_ARROWTIME = 2;
int CONFIRM_SCREEN = 3;
int MAINTIMER =4;
int COMPLETE_SCREEN = 5;
int ABORT_SCREEN = 6;
int BEEP_SCREEN = 7;
int LEAD_IN = 8;

int state = HOME_SCREEN; //setting the initial state
String input = "";
String currentKey = "";
boolean beep;


void loop()
{

  while(state == HOME_SCREEN) {
    homeScreen(); // loads boot screen
    switch (keyPress()) {
      case('#') :
      state = INPUT_ARROWTIME;
      lcd.clear();

    }
  }

  while(state == INPUT_ARROWTIME) {   //Serial.println("test");
    displayLines("Input Time : ", input);
    if (KeyCheck() == 'n') {
      //get current key
      //Serial.println(currentKey);
      if (input.length() < 4) {
        input = input += currentKey;
        displayLines("Input Time : ", input);
      }
    }


    if (currentKey == "*") {
      input = input.substring(0, input.length() - 1);
      displayLines("Input Time : ", input);
    }

    // Case if currentKey is #!
    if (currentKey == "#") {

      if (input == "") {
        displayLines("WARNING", "Input a Number!!");
        delay(1000);   

      } 
      else {

        state = BEEP_SCREEN;
        lcd.clear();

      }

    }

  }

  while(state == BEEP_SCREEN) {
    displayLines("BEEP at 5 secs?" ,"1 - NO, 2 - YES");


    switch(KeyCheck()) {
      case('*') :
      state = INPUT_ARROWTIME;
      break;

      case('n') :
      if (currentKey == "1") {
        beep = false;
        state = CONFIRM_SCREEN;
      }
      else if (currentKey == "2") {
        beep = true;
        state = CONFIRM_SCREEN;
      }
      break;

    }




  }



  while(state == CONFIRM_SCREEN) {
    displayLines("Time Set : " + input,"Press # to START");


    switch(KeyCheck()) {
      case('*') :
      state = BEEP_SCREEN;
      break;
      case('#') :
      state = LEAD_IN;
      break;
    }

  }

  while(state == LEAD_IN) {
     leadinSeq(10,6,MAINTIMER);

  }  

  while(state == MAINTIMER) {
    //displayLines("test","");  


    timerSeq(input.toInt(),beep,6,5);


  }   

  while(state==COMPLETE_SCREEN) {
    displayLines("End Complete","Home-* | Rest-#");
    switch(KeyCheck()) {
      case('*'):
      state = HOME_SCREEN;
      break;
      case('#'):
      state = LEAD_IN;
      break;
    }

  } 

  while(state==ABORT_SCREEN) {
    displayLines("Aborted","Home-* | Rest-#");
    switch(KeyCheck()) {
      case('*'):
      state = HOME_SCREEN;
      break;
      case('#'):
      state = LEAD_IN;
      break;
    }

  } 
  // resets current key at every loop.
  currentKey == ""; 
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



char KeyCheck() {
  char key = kpd.getKey();
  currentKey = (String) key;
  switch (key){ 
  case '0' : 
  case '1' : 
  case '2' : 
  case '3' : 
  case '4' : 
  case '5' : 
  case '6' : 
  case '7' : 
  case '8' : 
  case '9': 
    return 'n';
    break;
  case '*':
    return '*';
    break;
  case '#':
    return '#';
    break;
  }

}

void displayLines(String line1, String line2) {


  //appends whitespace
  while (line1.length() <= 16) {
    line1 = line1 += " ";
  }

  while (line2.length() <= 16) {
    line2 = line2 += " ";
  }

  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);

}



void timerSeq(int time, boolean beep, int abortState, int completeState) {
  for(int i = time; i >= 0;i--){

    //display code
    displayLines("SHOOTING TIME", (String) i);
    shifter.display(i);


    // check if less than 5
    if(i <= 5 && i != 0 && beep == true) {
      tone(5,2028,70); 

    } 
    else {
      if(i == 0){
        for(int j = 1; j <= 3; j++) {
          tone(5,2028,70);
          delay(200);

        }
        state = completeState;
      }




    }


    // poling loop delay.
    for(int z = 0; z <= 455; z++) {      
      if(KeyCheck() == '*') {
        i = 0;
        state = abortState;
        tone(5,1800,70);
        delay(200);
        tone(5,1800,70);
        delay(200);
        tone(5,1800,70);

      }

      delay(2);

    }
  } 

}

void leadinSeq(int time, int abortState, int completeState) {
  tone(5,2000,500);
  for(int i = time; i >= 0;i--){

    //display code
    displayLines("Lead in", (String) i);
    shifter.display(i);



    if(i == 0){
      
        tone(5,1900,70);
        delay(200);
        tone(5,1900,70);
      
      state = completeState;
    } else {
    // Polling Loop delay
    for(int z = 0; z <= 455; z++) {      
      if(KeyCheck() == '*') {
        i = 0;
        state = abortState;
        tone(5,1800,70);
        delay(200);
        tone(5,1800,70);
        delay(200);
        tone(5,1800,70);

      }

      delay(2);

    }
    }


  }




} 






