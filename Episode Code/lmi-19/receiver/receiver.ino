int seconds = 0;

void setup()
{
  Serial.begin(2400);
}

void loop()
{
  char ch;
  if (Serial.available())      // is there anything to be read from serial port?
  {
    ch = Serial.read();        // read a single letter
    
    // print out to serial port the character we just read
    Serial.print(ch, DEC);
  }
  
}
