/*############################## BASIC SHIFT REGISTER ##################################
       This sketch basically starts at 0 and counts up to 255 and outputs the number
       to the shift register.  In the code you can see how simple it is to communicate
       to a shift register.
     
       A shift register allows you to expand on the number of outputs that a device like
       an arduino can do.  
     
       To understand how the numbers correlate to the pins on the shift register you
       need to understand how a number can be translated into binary.  Here are some
       good links to better describe binary:
         http://en.wikipedia.org/wiki/Binary_number
         http://www.steveharrell.com/computer/binary.htm
         http://www.howstuffworks.com/binary-and-hexadecimal-number-systems.htm  

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 17 (http://tech-zen.tv/index.php/shows/let-s-make-it/episodes/112-shift-registers-and-an-arduino-episode-17)
       
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

//Pin connected to RCK of TPIC6B595
int latchPin = 8;
//Pin connected to SRCK of TPIC6B595
int clockPin = 12;
////Pin connected to SER IN of TPIC6B595
int dataPin = 11;



void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  for (int numberToDisplay = 0; numberToDisplay < 512; numberToDisplay++) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    byte registerOne = highByte(numberToDisplay);
    byte registerTwo = lowByte(numberToDisplay);
    
    shiftOut(dataPin, clockPin, MSBFIRST, registerTwo);
    shiftOut(dataPin, clockPin, MSBFIRST, registerOne);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    
    // pause before next value:
    delay(100);
  }
}
