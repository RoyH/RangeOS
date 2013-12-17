#include <Shifter.h>



void setup()
{
  //shifter.clear();
}

// num of digits, SRCK, SERIN, RCK
Shifter shifter(2, 2, 3, 4);  //Setup Shifter instance with number of digits and pin numbers
void loop()
{
  int x;
  
  //shifter.display(23);
   
  for (x = 0; x < 15; x++)
   { 
  shifter.display(x);
  delay(1000);
   }
}
