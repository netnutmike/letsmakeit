/*############### SEND MESSAGE VIA MORSE CODE SAMPLE #########################
       This code takes input from the serial port for the text that is to 
       be sent via Morse Code then sends one character at a time by blinking
       an LED in Morse Code.
       
       This will also send back to the serial monitor the text that it is
       sending via Morse Code so you can track along with the text that is
       being sent.

 
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

//define the morse code for the alphabet and numbers
char* letters[] = {
  ".-",     // A
  "-...",   // B
  "-.-.",   // C
  "-..",    // D
  ".",      // E
  "..-.",   // F
  "--.",    // G
  "....",   // H
  "..",     // I
  ".---",   // J
  "-.-",    // K
  ".-..",   // L
  "--",     // M
  "-.",     // N
  "---",    // O
  ".--.",   // P
  "--.-",   // Q
  ".-.",    // R
  "...",    // S
  "-",      // T
  "..-",    // U
  "...-",   // V
  ".--",    // W
  "-..-",   // X
  "-.--",   // Y
  "--.."    // Z
};

char* numbers[] = {
  "-----",   // 1
  ".----",   // 2
  "..---",   // 3
  "...--",   // 4
  "....-",   // 5
  ".....",   // 6
  "-....",   // 7
  "--...",   // 8
  "---..",   // 9
  "----."
};

void setup()                 
{
  // Setup the pin as output
  pinMode(ledPin, OUTPUT);
  
  //Setup the serial port for 9600
  Serial.begin(9600);

}

void loop()                    
{
  char ch;
  if (Serial.available())      // is there anything to be read from serial port?
  {
    ch = Serial.read();        // read a single letter
    
    // print out to serial port the character we are about to send
    Serial.print(ch);
    
    // Is it lowercase letter?
    if (ch >= 'a' && ch <= 'z')
    {
      morseCodeSequence(letters[ch - 'a']);
    }
    else if (ch >= 'A' && ch <= 'Z')    // Uppercase Letter
    {
      morseCodeSequence(letters[ch - 'A']);
    }
    else if (ch >= '0' && ch <= '9')    // Number
    {
      morseCodeSequence(numbers[ch - '0']);
    }
    else if (ch == ' ')                // Space (wait for 4 times dotDelay
    {
     delay(dotDelay * 4);      // gap between words  
    }
  } else {
    //make space between sends on teh serial monitor
    Serial.println(" ");
    
  }
  
  Serial.println(" ");
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


