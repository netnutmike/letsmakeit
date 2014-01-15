/**************************************************************
Name LedControl_7segment_demo
Author Bob Powell
texanfromiowa@gmail.com
Copyright (C) 2012-2013, Parallelus Automation, Inc.
Date May 23, 2013
Modified June 3, 2013
Version 1.0.0
Arduino 1.0.5
Notes Example for using one Maxim MAX7219 chip and an array of eight
7-segment LED displays. This demo uses the LedControl library
which can be found here: http://playground.arduino.cc/Main/LedControl
This library also supports 8x8 arrays of leds (including matrix
displays), but those functions are not used in this demo.
IMPORTANT: The library/chip is organized such that the right-hand
digit display is numbered 0, and work to the left. In this example,
using 8 digits, the left most digit is numbered 7 in the software.
This library, by design, does not support letters that do not
look right on a 7-segment display. In this example, I wanted to
use all letters even if they do not look "perfect." The characters
used can be found here: http://en.wikipedia.org/wiki/Seven-segment_display_character_representations
Note: An S is the same as a 5.
To make this addition, changes to the file 'LedControl.h' were made.
First, ascii NULL (charTable[0]) changed to B00000000 from B01111110.
Second, all other letters were added that were not included in the
standard definition. Here is the new section of code for the .h file:
This table defines standard ASCII characters from 0 to 128. For many
of the characters, a binary 0 (B00000000) is used. It doesn't make
sense to try and display a carriage return, escape char, or tab.
Reference for how digits are organized can be found in table 6 in the
datasheet.

Here is the replacement section of code for the LedControl.h file:
const static byte charTable[128] = {
B00000000,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
B01111111,B01111011,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B10000000,B00000001,B10000000,B00000000,
B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
B01111111,B01111011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B01011110,
B00110111,B00010000,B00111100,B01010111,B00001110,B01110110,B00010101,B00011101,
B01100111,B01101111,B00000101,B00011011,B01001111,B00011100,B00111110,B00111111,
B00110111,B00111011,B01101100,B00000000,B00000000,B00000000,B00000000,B00001000,
B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B01011110,
B00110111,B00010000,B00111100,B01010111,B00001110,B01110110,B00010101,B00011101,
B01100111,B01101111,B00000101,B00011011,B01001111,B00011100,B00111110,B00111111,
B00110111,B00111011,B01101100,B00000000,B00000000,B00000000,B00000000,B00000000
};


This program is heavily commented to explain a number
of concepts. PLEASE READ!!!
Legal Stuff:
============

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
at your option, any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
Personal note:
==============

If you do something interesting with this code, expand it, or just
have a question, please email me at the address above.

I hope you find this example helpful. Enjoy.

Bob

****************************************************************/
#include "LedControl.h"

/* The chip used, which is supported by this library, is a Maxim
MAX7129. Here is the datasheet:
http://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf

Please read the datasheet for details concerning connections.
In this case, here are the important connections:
Arduino Pin MAX7219 Pin
=========== ===========
12 1 DataIn
11 13 Clock
10 12 Load
The iset pin, number 18, on the MAX7219 has 40k ohm resistance
(four 10k ohm resistors in series) connected to it.
If multiple chips are used, they must be daisy chained together.
Pin 24, DataOut, of the first chip should be connected to DataIn
of the second chip. DataOut of the second chip is connected to
DataIn of the third chip, etc. etc.
The LedControl library makes connecting to the chip easy. To
setup the lc class, the argument are:
LedControl(DataIn pin, Clock pin, Load pin, number of MAX7219 chips)
In our case, we have only one MAX7219 connected, so our setup
is the next line of code.
*/
  LedControl lc = LedControl(12,11,10,1);
 
  // Number of 7-segment display digits connected
  const int NUM_DIGIT = 8;
 
  // Setup contants for displaying text (no scrolling)
  const int LEFT = 0;
  const int RIGHT = 1;
  const int CENTER = 2;

  
  // This constant is used a couple times, and probably should be removed.
  const byte SPACE = B00000000;
  //const byte PERIOND = B10000000;



/**************************************************************
Function: setup
Purpose: set up Arduino
Args: none
Returns: nothing
Notes: This function is required by the Arduino
***************************************************************/
void setup() {
  // Wakeup the MAX7219
  // The first variable, like most functions in the library, is for which display
  // the function is referencing. In this example, only one chip is used, so the
  // variable points to chip '0'. If multiple chips are used, multiple function
  // calls would be used pointing to chips 1, 2, etc.
  // Using 'true' would turn the chip off (shutting down is true)
  lc.shutdown(0,false);
  // Set duty cycle for each MAX7219
  // Values of 0 to 16 are valid.
  // To have the display look right on the video camera, the intensity is turned down
  lc.setIntensity(0,3);
  // Clear any leftover values
  lc.clearDisplay(0);
  
  //Serial.begin(9600);
  //Serial.println("Started");
  
}// End of Arduino Setup



/**************************************************************
Function: loop
Purpose: loop funtion for Arduino
Args: none
Returns: nothing
Notes: This function is required by the Arduino, and the
Arduino will loop through this function indefinately.
***************************************************************/
void loop() {

  int delayTime = 2000;

  scrollText("Demo for - Lets Make It.tv", 500);
  delay(delayTime);

  // do some counting
  counter(0, 250, 10);
  delay(delayTime/2);
  counter(250, 0, 10);
  delay(delayTime);
  lc.clearDisplay(0);
  delay(delayTime);
  
  counter(250, -250, 5);
  delay(delayTime);
  
  // Display text
  displayText("Arduino");
  delay(delayTime*2);
  displayTextJust("Right", RIGHT);
  delay(delayTime*2);
  displayTextJust("Left", LEFT);
  delay(delayTime*2);
  displayTextJust("Center", CENTER);
  delay(delayTime*2);
  
  // scroll text
  scrollText("a", 500);
  delay(delayTime);
  scrollText("scroll", 500);
  delay(delayTime);
  scrollText("abcdefgh", 500);
  delay(delayTime);
    
} // End of Arduino Loop


/**************************************************************
Function: counter
Purpose: counts from one number to another
Args: int duration - how long an led is on
int startNum - starting number
int endNum - ending number
Returns: nothing
Notes:
**************************************************************/
void counter(int startNum, int endNum, int duration){

  char tc[NUM_DIGIT];

  // Counting up
  if (endNum > startNum){
    for(int i = startNum; i <= endNum; i++){
      itoa(i,tc,10);
      displayText(tc);
      delay(duration);
    }
  }
  // Counting down
  else if(startNum > endNum){
    for(int i = startNum; i >= endNum; i--){
      itoa(i,tc,10);
      displayText(tc);
      delay(duration);
    }
  }
  // Start = end, so we do nothing and return
  else
    return;
    
}



/**************************************************************
Function: displayText
Purpose: displays given text
Args: char text[] - text to be displayed
Returns: nothing
Notes: Text is right justified
THERE IS NO ERROR CHECKING FOR TEXT GREATER THAN THE
NUMBER OF DIGITS
**************************************************************/
void displayText(char text[]){
 
  int textLength = arrayLength(text);
  int displayStart = textLength - 1;
  char newText[8];
    
  copyArray(newText, displayStart, text, 0, textLength);
    
  for(int j = 0; j < NUM_DIGIT ; j++){
    lc.setChar(0,j,newText[j],false);
  }
    
}


/**************************************************************
Function: displayTextJust
Purpose: displays given text with specified justification
Args: char text[] - text to be displayed
int justification - Left, Right, or Centered
Returns: nothing
Notes: THERE IS NO ERROR CHECKING FOR TEXT GREATER THAN THE
NUMBER OF DIGITS
**************************************************************/
void displayTextJust(char text[], int justification){
 
  int textLength = arrayLength(text);
  int displayStart;
  char newText[8];
  int startText;
  
  if(justification == LEFT)
    displayStart = NUM_DIGIT - 1;
  else if(justification == CENTER)
    displayStart = (NUM_DIGIT - 1) - ((NUM_DIGIT-textLength)/2);
  else
    displayStart = textLength - 1;
  
  // Set the array that will be use to set the display
  copyArray(newText, displayStart, text, 0, textLength);

  // Set the display
  for(int j = 0; j < NUM_DIGIT ; j++){
    lc.setChar(0,j,newText[j],false);
  }
    
}

/**************************************************************
Function: scrollText
Purpose: scrolls text across the display
Args: char text[] - text to be displayed
int duration - delay time between loops
Returns: nothing
Notes: Remember, the 0 position in the text to be displayed
is on the left while the 0 position of the MAX7219
is on the right.
**************************************************************/
void scrollText(char text[], int duration){
 
  int displayStart = 0;
  int startText = 0;
  int textLength = arrayLength(text);
  int cycles = textLength + NUM_DIGIT;
  int half = cycles/2;
  int numCopy = 1;
  
  char newText[8];
  
  for(int i = 0; i < cycles; i++){
    
    // Set the startText position - It cannot be less than 0;
    if( (i - NUM_DIGIT + 1) < 0)
      startText = 0;
    else
      startText = i - NUM_DIGIT + 1;
   
    // Calculate the starting position of the display - It cannot be greater that NUM_DIGIT
    if(i < NUM_DIGIT)
      displayStart = i;
    else
      displayStart = NUM_DIGIT - 1;
      
    // Get the number of letters to copy
    if(half >= i)
      numCopy = displayStart + 1;
    else
      numCopy = cycles - startText - NUM_DIGIT;
    
    // numCopy cannot be greater than the number of digits or the length of the text
    if(numCopy > NUM_DIGIT)
      numCopy = NUM_DIGIT;
    else if(numCopy >= textLength)
      numCopy = textLength;
        
    // Set the array that will be use to set the display
    copyArray(newText, displayStart, text, startText, numCopy);
    
    // Set the display
    for(int j = 0; j < NUM_DIGIT ; j++){
      lc.setChar(0,j,newText[j],false);
    }
     
    delay(duration);
  }
  
}

/**************************************************************
Function: copyArray
Purpose: Copies contents of one array to another for display
Args: char* dest - pointer to the char array to display
int destStart - starting point of the display -
0 is on the far right and x is to the far left
char* source - pointer to the source char array
int sourceStart - starting point of the display -
Read left (0) to right
int num - number of characters to copy
Returns: nothing
Notes:
**************************************************************/
void copyArray(char* dest, int destStart, char* source, int sourceStart, int num){
   
  clearArray(dest);
   
  for(int i = 0; i < num ; i++,destStart--,sourceStart++){
    dest[destStart] = source[sourceStart];
  }
    
}
/**************************************************************
Function: arrayLength
Purpose: count the number of characters in an array
Args: char array[] - array to be counted
Returns: int length - number of characters
Notes: The Arduino "sizeof" function does not work as expected,
so this function is used.
**************************************************************/
int arrayLength(char array[]){
  
  int length = 0;
  
  while(array[length] > 0)
    length++;
    
  return length;
}
  
  
/**************************************************************
Function: clearArray
Purpose: clears char array that will be sent to the display
Args: char* dest - pointer to the char array being cleared
Returns: nothing
Notes:
**************************************************************/
void clearArray(char* dest){
  for(int i = 0; i < NUM_DIGIT; i++)
    dest[i] = SPACE;
}


// End of program
