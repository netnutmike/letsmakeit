
int seconds = 0;

void setup()
{
Serial.begin(2400); // Bits per sec
}

void loop()
{
  Serial.print(seconds);
  ++seconds;
  if (seconds >= 255)
    seconds = 0;
  
  delay(1000);
}
