/*############### LIE DETECTOR / BIO-FEEDBACK #########################
       This code works like a bio-feedback sensor.  It can be used
       to detect if a subject is lying.  The theory is that when
       someone is lying their resistance goes down.
       
       This code basically compares the resistance to a value that
       is set by a potentiometer on the board.  After the pot is adjusted,
       if the resistance goes up or down it will change an RGB LED 
       indicator.

 
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


int redPin = 9;
int greenPin = 11;
int bluePin = 10;
int buzzerPin = 7;

int potPin = 1;
int sensorPin = 0;

long red=0xFF0000;
long green=0x00FF00;
long blue=0x000080;

int band=60;

void setup()
{
  pinMode(potPin, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  int gsr = analogRead(sensorPin);
  int pot = analogRead(potPin);
  if (gsr > (pot + band))
  {
    setColor(red);
    beep();
  } else if (gsr < (pot - band))
    setColor(blue);
  else
    setColor(green);
}

void setColor(long rgb)
{
  int red = rgb >> 16;
  int green = (rgb >> 8) & 0xFF;
  int blue = rgb & 0xFF;
  analogWrite(redPin, 255 - red);
  analogWrite(greenPin, 255 - green);
  analogWrite(bluePin, 255 - blue);
}

void beep()
{
  for (int i=0; i<1000; ++i)
  {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(100);
  }
}
  
