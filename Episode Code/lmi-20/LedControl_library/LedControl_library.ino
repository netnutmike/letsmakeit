#include "LedControl.h"

void setup() {
  //wake up the MAX72XX from power-saving mode 
   lc.shutdown(0,false);
   //set a medium brightness for the Leds
   lc.setIntensity(0,8);
 }
void loop() {}
