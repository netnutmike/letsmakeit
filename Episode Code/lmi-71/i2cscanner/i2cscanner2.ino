#include <Wire.h>

void setup() {
  Serial.begin (9600);
 
  Serial.println();
  Serial.println ("I2C scanner.....");
  Serial.println();
  Serial.println();
  
 
  Wire.begin();
  
}  

void loop() {
  byte count = 0;
  
  Serial.println ("I2C scanner. Scanning ...");
  count=0;
  
  for (byte i = 1; i < 120; i++)
    {
      Wire.beginTransmission (i);
      if (Wire.endTransmission () == 0)
        {
        Serial.print ("Found device at address: ");
        Serial.print (i, DEC);
        Serial.print (" (0x");
        Serial.print (i, HEX);
        Serial.println (")");
        count++;
        } 
    } 
    
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
  Serial.println();
  Serial.println();
  Serial.println();

  delay(5000);
}
