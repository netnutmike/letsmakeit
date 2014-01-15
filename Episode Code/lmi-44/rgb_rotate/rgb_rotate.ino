/*############################## RGB Rotate ##################################
       This sketch is a very simple sketch that rotates 3 pins.  Each pin has
       attached to it a transistor that is controlling one of the primary
       colors (red, green or blue) on a RGB led strip.

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 44 (http://letmakeit.tv)
       
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

const int redPin =  2;
const int greenPin =  3;
const int bluePin =  4;


void setup() {
  // set the digital pin as output:
  pinMode(redPin, OUTPUT);   
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
}

void loop()
{
  
    digitalWrite(redPin, HIGH);
    delay(250);
    digitalWrite(redPin, LOW);
    
    digitalWrite(greenPin, HIGH);
    delay(250);
    digitalWrite(greenPin, LOW);
    
    digitalWrite(bluePin, HIGH);
    delay(250);
    digitalWrite(bluePin, LOW);
    

}

