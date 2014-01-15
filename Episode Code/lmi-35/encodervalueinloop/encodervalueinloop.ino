/*######################### ENCODER VALUE IN LOOP ############################
       This is a small sketch that demonstrates a very basic encoder routine
       that can read the encoder in both directions.  However, this sketch
       has some limitations in that it only reads when pin 1 (A) goes high
       which means for every 4 "clicks" only one click in the current 
       direction.
       
       This is used to demonstrate something to watch for when reading an
       encoder.  A more complete sketch is also provided in the show notes.
       
       To connect the encoder, connect the common pin of the encoder to 
       GND and pin 1 (A) of the endcoder to digital pin 2 and pin 3 (B) to
       digital pin 3 on the arduino.
 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 35 at http://tech-zen.tv
       
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

#define encoderPinA  2
#define encoderPinB  3

int encoderPos = 0;
int encoderPinALast = LOW;
int n = LOW;

void setup() { 


  pinMode(encoderPinA, INPUT_PULLUP); 
  pinMode(encoderPinB, INPUT_PULLUP); 
  
  Serial.begin (9600);
  Serial.println("start");                // a personal quirk

} 

void loop(){
   n = digitalRead(encoderPinA);
   if ((encoderPinALast == LOW) && (n == HIGH)) {
     if (digitalRead(encoderPinB) == LOW) {
       encoderPos--;
     } else {
       encoderPos++;
     }
     Serial.print(encoderPos);
     Serial.println(" ");
   } 
   encoderPinALast = n;
  
}
