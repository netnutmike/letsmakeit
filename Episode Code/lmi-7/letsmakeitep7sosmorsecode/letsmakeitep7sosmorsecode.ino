/*############### SEND SOS IN MORSE CODE SAMPLE #########################
       This code constantly sends SOS in morse code.
       
       The subroutines in this program are re-used in the second project
       where we can send out any text that is input.

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 6 (http://tech-zen.tv/index.php/shows/let-s-make-it/episodes/59-sensor-fun-with-arduino-1-massive-failure-but-4-successes-let-s-make-it-episode-6)
       
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

//set a constant for the pin we are going to use for the Morse Code Output
int ledPin = 13;

//duration of the dot in morse code, this is also the time between the dots and dashes
int dotDelay = 200;

void setup()                 
{
  // Setup the pin as output
  pinMode(ledPin, OUTPUT);
}

void loop()                    
{
  //send out the Morse Code for SOS
  morseCodeSequence("...");    // S
  morseCodeSequence("---");    // O
  morseCodeSequence("...");    // S
  
  delay(1000);    // Wait for 1 second
}

//=================================================================
//
// Function: morseCodeSequence
//
// Input: Character Array of Dots and Dashes to be sent
//
// Description:
//      This function takes as input an array or "." and "-" and
//      calls dotOrDash for each item in the array.
//
//      At the end of the sequence, there is a delay of 3 times 
//      the dot duration.
//=================================================================
void morseCodeSequence(char* sequence)
{
   int i = 0;
   
   // Loop for each element in the array
   while (sequence[i] != NULL)  
   {
       dotOrDash(sequence[i]);     // Send out the dot or dash
       i++;                        // Increment to the next element in the array
   }
   delay(dotDelay * 3);            // gap between letters
}


//=================================================================
//
// Function: dorOrDash
//
// Input: Character that should be either a dot or a dash
//
// Description:
//      This function first turns on the output then looks to see 
//      if the character is a "." and if so delays the dotDelay.
//      
//      If the character is not a "." then the routine assumes it
//      is a "-" and keep the output high for 3 times the length of
//      dotDelay.  This could be improved by making sure the 
//      character is a "-" but for most cases it would not matter.
//
//      After the delay time the pin is taken low turning off the 
//      LED.
//
//      Then it delays for one dotDelay time so the dots and dashes
//      do not run together.
//=================================================================
void dotOrDash(char dotOrDash)
{
  digitalWrite(ledPin, HIGH);
  if (dotOrDash == '.')
  {
    delay(dotDelay);           
  }
  else // must be a -
  {
    delay(dotDelay * 3);           
  }
  digitalWrite(ledPin, LOW);    
  delay(dotDelay); // gap between flashes
}


