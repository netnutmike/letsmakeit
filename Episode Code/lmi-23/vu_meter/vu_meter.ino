/*############### SET SERVO POSITION BASED ON SERIAL INPUT #########################
       This code will take input from the Serial port in the form of a number.
       
       It takes this number and positions a servo between 0 and 180 degrees.
       
       To know when the number actually ends, a non numeric character must follow
       the number.  Typically the serial input would not be used, it is just for this 
       example.

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 12 (http://tech-zen.tv/index.php/shows/let-s-make-it/episodes/59-sensor-fun-with-arduino-1-massive-failure-but-4-successes-let-s-make-it-episode-6)
       
       http://tech-zen.tv
       
       For the sample code, show notes, contact information and many more 
       videos, visit the show page at http://tech-zen.tv/letsmakeit

       Please subscribe to our YouTube channel or our netcasts at any of 
       your favorite netcast / podcast outlets.

       We normally record Let's Make It live on Tuesday evenings around 
       7pm eastern. You can watch it live by going to tech-zen.tv and clicking 
       the live link at the top of the page.

       We also have a community setup for our viewers and listeners. You can 
       join the community by going to community.tech-zen.tv.

       We love input on what you would like to know or if you have an idea for 
       a new Let's Make it episode, you can contact us via email or phone at 
       the show information page.
################################################################################*/


int ledPins[] = {3,4,5,6,7,8,9,10,11,12};
int switchPin = 2;
int soundPin = 0;

boolean showPeak = false;
int peakValue = 0;
long lastPeak = 0;

void setup()
{
  for (int i=0; i< 10; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(switchPin, INPUT);
}

void loop()
{
  if (digitalRead(switchPin))
  {
    showPeak = !showPeak;
    peakValue = 0;
    delay(200);
  }
  
  int value = analogRead(soundPin);
  int topLED = map(value, 0, 1023, 0, 11) -1;
  
  if (millis() > (lastPeak + 2000))
  {
    peakValue = 0;
  }
    
  if (topLED > peakValue)
  {
    peakValue = topLED;
    lastPeak = millis();
  }
  
  for (int i=0; i<10; i++)
  {
    digitalWrite(ledPins[i], (i <= topLED || (showPeak && i == peakValue)));
  }
  
  delay(50);
}
