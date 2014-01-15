/**************************************************************
Name ShiftRegister_nleds_1
Author Bob Powell
texanfromiowa@gmail.com
Copyright (C) 2012-2013, Parallelus Automation, Inc.
Date May 25, 2013
Modified June 3, 2013
Version 1.0.0
Arduino 1.0.5
Notes: This code started as an example of using a shift register with
LEDs. It was modified for use with a single, standard 7-segment
display. Most of the original comments are left in place.
Notes Example for using "n" number of 74HC595 Shift Registers and LEDs.
Various test functions included for fun. Functions are written
for maximum flexibility, so everything is a variable.
This means that the code that calls the function, sets the
values of the variables which allows for the same function
to have an infinite number of variations.

This program is heavily commented to explain a number
of concepts. PLEASE READ!!!
In this version of the software, I switched to the Shifter (link below)
library for maximum flexibility in both the number of LEDs
and the number of shift registers. There is a little more
logic involved, but the added functionality is more than
worth it. It does seem to have been written with a 74HC595
in mind, so you may need to modify the code if other register
types are used.
Essentially, there are two steps to turn on and off leds.
First, use the LED[] array to set a given led on or off.
Second, use the writeBytes() function to send the array to
the shift registers. If you want the array reversed,
then use the writeBytesRev() function.
At a number of points in the code, you will see variations
of this: 1<<i This is bit shifting. If you want a full
explanation, go here: http://en.wikipedia.org/wiki/Logical_shift
The bit shifting is used because of the inherent problems
with floating point numbers. The preferred method for
calculating an exponent would be, for example, to use:
pow(2,3) which would equal 8 (the number 2, cubed (2^3))

Unfortunately, the function returns a float which may not
be exactly 8 (ie. 7.998761234). Using C casting to force an
integer would set this to a 7, which is unacceptable.
Rather than write code to fix this, bit shifting was used, which
ALWAYS gives you an integer, which is what we want anyway.
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
// Switched to the Shifter library. This allows for "n" number
// shift registers to be used without significant changes to the
// code. For help in adding libraries to the Arduino IDE, go here:
// http://www.arduino.cc/en/Hacking/Libraries
// This library was obtained from: http://bildr.org/2011/08/74hc595-breakout-arduino/
//
// The short version of installing a library it to, first, download the library
// (link above). They usually download as a zip file, so unzip the file which
// will usually create a directory of the libraries contents. Third, put this
// directory into the "libraries" directory of your Arduino IDE (Integrated
// Design Enviroment) software. In a typical Windows installation, the Arduino
// IDE executable file is located at: c:\Program Files\Arduino\Arduino.exe
// There is a directory called: c:\Program Files\Arduino\libraries
// The Shifter\ directory will go into this libraries directory.
// For a Mac, this directory is typically located at:
// /Applications/Arduino.app/Contents/Resources/Java/libraries
// If you have trouble, see the link above for complete instruction from Arduino
// You will need to restart the Arduino IDE for it to realize that this
// library is present. Once you have installed the library and restarted the
// IDE, this line tells the compilier to include it:
#include <Shifter.h>

// THESE VARIABLES CHANGE.
// Set the number of leds your using and the number of shift registers used.
// The Shifter library assumes one register = 8 bits. With this in mind,
// NUM_LED can never be greater that NUM_REG x 8 bits.
const int NUM_LED = 8; // number of leds
const int NUM_REG = 1; // number of shift registers


// Set variables - Global variables, except for the Arduino
// pins, are CAPITALIZED. This makes identification of local and
// global variables easy to understand. The compilier is case sensitive
// so it understands capitalized and lower case letters.

// These variables are too make things a little easier for humans to read.
// The "const" sets the variable so it cannot be changed
// later in the program (ie. make them constants). The standard
// constants "true" and "false" function just as well as these.
const bool OFF = 0;
const bool ON = 1;

// In this example, this chip is used: http://www.ti.com/lit/ds/symlink/sn74hc595.pdf
// (Since I worked for TI for almost a decade, I'm fond of their products. Plus, the
// quality can't be beat.)
// The names below match those in the datasheet, but can change from one datasheet to
// another depending on the manufacturer. The function of each pin remain the same.

// Pin connected to RCLK, pin 12, of ALL the 74HC595s
// ===
const int latchPin = 10;
// Pin connected to SRCLK, pin 11, of ALL the 74HC595s
// ===
const int clockPin = 11;
// Pin connected to SER, pin 14, of the FIRST 74HC595s
// =====
// All of the serial data will be going to this SER (data in)
// pin to all the register(s) you have connected.
const int dataPin = 12;

/* The rest of the 74HC595 pins and setup:

To daisy chain registers, pin 9, data out, of the first register connects
to pin 14, data in, of the second register, then pin 9, data out of the second
register connects to pin 14, data in, of the third register, etc. etc. This
code will support more registers than can be physically connected without
circuit modifications. Data in for all the registers is the dataPin
variable set above.
Also, you must tie ALL the latch and clock pin for ALL registers
together. When the Arduino sets the latchPin and clockPin variables
(created above) HIGH or LOW, it must set ALL latch and clock pins
HIGH and LOW TOGETHER!!! If this is not done, the chain of registers
will not work.
For each register used, don't forget to connect ALL registers as
show here:
Connect SRCLR (master reset), pin 10, to 5V. In this example,
the chip will not be reset and must always be set HIGH for the chip
to function. Setting this pin LOW resets the register.

Connect OE (output enable), pin 13, to GRD (LOW).
In this example, we are not using the 74HC595 for any
data input, so we never switch this pin from HIGH
to LOW, to switch if from inputing data to outputing
data, repestively.
One more, somewhat obvious detail, connect pin 15, Qa, to your first
led, pin 1, Qb, to the second led, pin 2, Qc, to your third led, and
so on. The 8th led will be connected to pin 7, Qh.
Again, see the datasheet for details.
*/


// Set up the shifter object used to send data to the registers.
Shifter shifter(dataPin, latchPin, clockPin, NUM_REG);


// Set up the array of leds that is used throughout the program
bool LED[NUM_LED];


/* Added constants for a 7 segment, common cathode single digit
alphanumeric display. In this example, a NTE3079 was used.
The datasheet can be found at: http://www.datasheetcatalog.org/datasheet/nte/NTE3078.pdf
The shift register is connected as:
Qa = Anode A
Qb = Anode B
Qc = Anode C
Qd = Anode D
Qe = Anode E
Qf = Anode F
Qg = Anode G
Qh = Anode D.P. (decimal point)

This quick example is for a single LED display with a single 74HC595.
The same basic idea applies for multiple LED's and displays.
Yes, a more effcient way of doing this would be with hex codes, but
I wanted to show how the pieces could be put together to create the
desired output. This code should also be included in a .h file as well.
A typical 7-Segment display is typically
A
-----
F | G | B
-----
E | | C
-----
D
So, the varible SEGA refers to segment A above, SEGB is segment B, etc.
*/

  const int SEGA = 1;
  const int SEGB = 2;
  const int SEGC = 4;
  const int SEGD = 8;
  const int SEGE = 16;
  const int SEGF = 32;
  const int SEGG = 64;
  const int SEGH = 128;

  int SEGMENTS[] = {SEGA, SEGB, SEGC, SEGD, SEGE, SEGF, SEGG, SEGH};
  
  const int NUM0 = SEGA + SEGB + SEGC + SEGD + SEGE + SEGF;
  const int NUM1 = SEGB + SEGC;
  const int NUM2 = SEGA + SEGB + SEGD + SEGE + SEGG;
  const int NUM3 = SEGA + SEGB + SEGC + SEGD + SEGG;
  const int NUM4 = SEGB + SEGC + SEGF + SEGG;
  const int NUM5 = SEGA + SEGC + SEGD + SEGF + SEGG;
  const int NUM6 = SEGA + SEGC + SEGD + SEGE + SEGF + SEGG;
  const int NUM7 = SEGA + SEGB + SEGC;
  const int NUM8 = SEGA + SEGB + SEGC + SEGD + SEGE + SEGF + SEGG;
  const int NUM9 = SEGA + SEGB + SEGC + SEGD + SEGF + SEGG;

  int NUMBERS[] = {NUM0, NUM1, NUM2, NUM3, NUM4 , NUM5, NUM6, NUM7, NUM8, NUM9};

  // Characters based on:
  // http://en.wikipedia.org/wiki/Seven-segment_display_character_representations
  const int A = SEGA + SEGB + SEGC + SEGE + SEGF + SEGG;
  const int B = SEGC + SEGD + SEGE + SEGF + SEGG;
  const int C = SEGD + SEGE + SEGG;
  const int D = SEGB + SEGC + SEGD + SEGE + SEGG;
  const int E = SEGA + SEGD + SEGE + SEGF + SEGG;
  const int F = SEGA + SEGE + SEGF + SEGG;
  const int G = SEGA + SEGC + SEGD + SEGE + SEGF;
  const int H = SEGC + SEGE + SEGF + SEGG;
  const int I = SEGC;
  const int J = SEGB + SEGC + SEGD + SEGE;
  const int K = SEGA + SEGC + SEGE + SEGF + SEGG;
  const int L = SEGD + SEGE + SEGF;
  const int M = SEGA + SEGB + SEGC + SEGE + SEGF;
  const int N = SEGC + SEGE + SEGG;
  const int O = SEGC + SEGD + SEGE + SEGG;
  const int P = SEGA + SEGB + SEGE + SEGF + SEGG;
  const int Q = SEGA + SEGB + SEGD + SEGE + SEGF + SEGG;
  const int R = SEGE + SEGG;
  const int S = SEGA + SEGC + SEGD + SEGF + SEGG;
  const int T = SEGD + SEGE + SEGF + SEGG;
  const int U = SEGC + SEGD + SEGE;
  const int V = SEGB + SEGC + SEGD + SEGE + SEGF;
  const int W = SEGB + SEGC + SEGD + SEGE + SEGF + SEGG;
  const int X = SEGB + SEGC + SEGE + SEGF + SEGG;
  const int Y = SEGB + SEGC + SEGD + SEGF + SEGG;
  const int Z = SEGA + SEGB + SEGD + SEGE;
  const int SPACE = 0;
  const int PERIOD = SEGH;

  int LETTERS[] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};

/**************************************************************
Function: setup
Purpose: set up Arduino
Args: none
Returns: nothing
Notes: This function is required by the Arduino
***************************************************************/
void setup() {

  // Set up the output pins.
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  
  // Set up the shifter output
  shifter.clear();
  shifter.write();
  
  // turn off all the LEDS, just in case
  allOff();
  writeBytes();

} // End of Arduino Setup



/**************************************************************
Function: loop
Purpose: loop funtion for Arduino
Args: none
Returns: nothing
Notes: This function is required by the Arduino, and the
Arduino will loop through this function indefinately.
***************************************************************/
void loop() {
  
  // Set a standard delay between each effect
  int loopDelay = 2000;
  
  // Flash all leds, to let us know its on
  // From original example
  flashAll(500, 3);
  delay(loopDelay);

  // 7-segment display tests
  sevenSegmentTests();

} // End of Arduino Loop



/**************************************************************
Function: sevenSegmentTests
Purpose: series of displays for a 7-segmet display
Args: none
Returns: nothing
Notes: Includes counting up and down, display the alphabet,
and others.
***************************************************************/
void sevenSegmentTests()
{
  int loopDelay = 2000;

  
  //==========================================================
  // Count from 0 to 10, and back to zero

  for(int i = 0; i <= 9; i++){
    setArray(NUMBERS[i]);
    writeBytes();
    delay(500);
  }
  
  for(int i =9; i >= 0; i--){
    setArray(NUMBERS[i]);
    writeBytes();
    delay(500);
  }

  allOff();
  writeBytes();
  
  delay(loopDelay);
 
  //==========================================================
  // Letters A to Z

  for(int i = 0; i <= 26; i++){
    setArray(LETTERS[i]);
    writeBytes();
    delay(500);
  }
 
  //==========================================================
  // Display a message
  
  int MESSAGE[] = {B, O, B, SPACE, W, A, S, SPACE, H, E, R, E + PERIOD};
  for(int i = 0; i <= 12; i++){
    setArray(MESSAGE[i]);
    writeBytes();
    delay(500);
  }
  allOff();
  writeBytes();
  
  delay(loopDelay);
  
  //==========================================================
  // Figure 8 pattern
  
  int fig8sequence[] = {SEGA, SEGB, SEGG, SEGE, SEGD, SEGC, SEGG, SEGF};
  int j = -1;
  int f8delay = 100;
  
  int k;
  for(int i = 0; i < 5; i++){
    for(k = 0; k < 8; k++, j++){
      if(k == 1)
        j = 0;
      setArray(fig8sequence[k] + fig8sequence[j]);
      writeBytes();
      delay(f8delay);
    }
  }
  setArray(fig8sequence[7]);
  writeBytes();
  delay(f8delay);
  allOff();
  writeBytes();

  delay(loopDelay);
 
 
  //==========================================================
  // Around the world - forwards and backwards
  
  j = -1;
  for(int k = 0; k < 5; k++){
    for(int i = 0; i < 6;i++){
      if(i == 1)
        j = 0;
      setArray(SEGMENTS[i] + SEGMENTS[j]);
      writeBytes();
      delay(50);
      j++;
    }
  }
  
  // hold the last segment for the transition from forward to reverse
  setArray(SEGMENTS[j]);
  writeBytes();
  delay(50);
  
  // now the other direction
  j = j - 1;
  for(int k = 0; k < 5; k++){
    for(int i = 5; i >= 0;i--){
      if(i == 4)
        j = 5;
      setArray(SEGMENTS[i] + SEGMENTS[j]);
      writeBytes();
      delay(50);
      j--;
    }
  }
  
  setArray(SEGMENTS[j]);
  writeBytes();
  delay(50);
  
  allOff();
  writeBytes();
  delay(loopDelay);
  
  
  //==========================================================
  // Don't know what to call this, but I like it!
  
  int t1 = SEGA + SEGC + SEGE + SEGG;
  int t2 = SEGB + SEGD + SEGF + SEGG;
  
  for(int i = 0; i < 6; i++){
    setArray(t1);
    writeBytes();
    delay(250);
    setArray(t2);
    writeBytes();
    delay(250);
  }
  
  allOff();
  writeBytes();
  delay(loopDelay);
  
}

/**************************************************************
Function: flashAll
Purpose: Flashes all leds
Args: int duration - how long an led is on
int count - how many times to flash
Returns: nothing
Notes:
***************************************************************/
void flashAll(int duration, int count)
{
  for(int i = 0; i < count; i++)
  {
    allOn();
    writeBytes();
    delay(duration);
    allOff();
    writeBytes();
    delay(duration);
  }
 
}



 
/**************************************************************
Function: sumArray
Purpose: Take a binary representation of the array of ON and OFF
positions, and generates an integer.
Args: int array[]
Returns: integer of the total
Notes: See comments on bit shifting at the beginning
of this file.
**************************************************************/
int sumArray(bool array[])
{
   int total = 0;
   
   for (int i = 0; i < NUM_LED; i++)
   {
     if (array[i] == ON)
total = total + (1<<i);
   }
   
   return(total);
}

/**************************************************************
Function: setArray
Purpose: Sets the primary array to the binary of the number
given.
Args: int num - number to put into array
Returns: nothing
Notes: See comments on bit shifting at the beginning
of this file. Since this is an integer, it must be
between -32,768 and 32,767, HOWEVER, it should
always be a positive number (0 to 32,767).
**************************************************************/
void setArray(int num)
{
  // Clear the array
  allOff();
  int i = 0;
  bool value;
  
  while (num > 0)
   {
     value = num & 1;
     if(value == true)
       LED[i] = ON;
     else
       LED[i] = OFF;
       
     num >>= 1;
     i++;
   }
/* for(int i = 0; i < NUM_LED; i++){
LED[i] = ON;
value = num & 1;
if(value == 1)
LED[i] = ON;
else
LED[i] = OFF;
num >>= 1;
} */
}


/**************************************************************
Function: allOn
Purpose: Turns ON all leds
Args: none
Returns: none
Notes:
**************************************************************/
void allOn()
{
   for (int i = 0; i < NUM_LED; i++)
   {
     LED[i] = ON;
   }
}

/**************************************************************
Function: allOff
Purpose: Turns OFF all leds
Args: none
Returns: none
Notes:
**************************************************************/
void allOff()
{
   for (int i = 0; i < NUM_LED; i++)
   {
     LED[i] = OFF;
   }
}



/**************************************************************
Function: writeBits
Purpose: Write the array with Most Significant Bit first (MSFBFIRST)
Args: none
Returns: nothing
Notes: This function is a wrapper function for outBytes()
***************************************************************/
void writeBytes()
{
  outBytes(MSBFIRST);
}


/**************************************************************
Function: writeBytesRev
Purpose: Write the array with Least Significant Bit first (MSFBFIRST)
Args: none
Returns: nothing
Notes: This function is a wrapper function for outBytes()
***************************************************************/
void writeBytesRev()
{
  outBytes(LSBFIRST);
}

/**************************************************************
Function: outBytes
Purpose: Send array data to shift register
Args: int dir - First or Least significant bit first
Returns: nothing
Notes: This is where data is actually sent out, but is not
intended to be used directly. writeBytes() and
writeBytesRev() should be used instead.
***************************************************************/
void outBytes(int dir)
{
   // set latch pin low so data can be sent
   digitalWrite(latchPin, LOW);
   // Clears previous data
   shifter.clear();
   
   // Set each pin according to what LED[] currently has.
   
   // most significant bit first
   if(dir == MSBFIRST)
   {
     for(int i = 0; i < sizeof(LED);i++)
     {
        if(LED[i] == ON)
         shifter.setPin(i, HIGH);
       else
         shifter.setPin(i, LOW);
     }
   }
   // least significant bit first - reverses what is in LED[]
   else if(dir == LSBFIRST)
   {
     int j = 0;
     for(int i = sizeof(LED) - 1; i > -1;i--)
     {
       if(LED[i] == ON){
         shifter.setPin(j, HIGH);
       }
       else{
         shifter.setPin(j, LOW);
       }
       j++;
     }
   }
   
   // Write the data to the registers
   shifter.write();
   // set the latch high to turn on the output
   digitalWrite(latchPin, HIGH);

}

// End of program
