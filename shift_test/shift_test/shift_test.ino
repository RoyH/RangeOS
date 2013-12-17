
#include <Shifter.h>

// num of digits, SRCK, SERIN, RCK
Shifter shifter(2, 2, 3, 4);  //Setup Shifter instance with number of digits and pin numbers

void setup()
{
  shifter.clear();
  Serial.begin(9600);
}

void loop()
{
  int x;
  
  
  for (x = 50; x >= 0; x--)
   { 
  shifter.display(x);
  Serial.println(x);
  delay(250);
   }
   
}
