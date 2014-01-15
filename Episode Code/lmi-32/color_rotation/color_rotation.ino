/*####################### RGB COLOR ROTATOR #########################
       This code is a short example of how to change color in an RGB
       LED.  This code is also used in the lie detector sketch.  This
       was created to show an example of what you can do with an RGB
       LED.

 
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

long red=0xFF0000;
long green=0x00FF00;
long blue=0x0000FF;
long currentColor=0;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
    currentColor = currentColor+100;
    setColor(blue);
}

void setColor(long rgb)
{
  int red = rgb >> 16;
  int green = (rgb >> 8) & 0xFF;
  int blue = rgb & 0xFF;
  analogWrite(redPin,  red);
  analogWrite(greenPin,  green);
  analogWrite(bluePin,  blue);
}

  
