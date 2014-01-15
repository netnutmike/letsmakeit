/*############################ ROLLING THE DICE ################################
       This code simulates rolling a Die.  It randomly determines how many times
       the Die will spin until it lands on the final number.  Each roll uses
       the randoom number generator to determine the value of each roll.
       
       We pause for each roll for (roll number * 10) + 50 milisenconds to
       simulate the rolling of the Die slowing down until we have completed
       the random number of rolls and stop on the final random number generated.
       
       We blink the final number 3 times.
       
       This code also outputs to the serial port so you can see what it is
       doing during the entire process.
       
       The following are the pinouts for this project.  Pins 4 - 9 are the
       six led's for the simulated die.
       
       Ping 11 is the button that is monitored to determine when the button
       is pressed.  There is a resistor from ground to each LED to limit the
       current flow.
       
       There is a resistor to ground on the arduino side of the switch so that
       the pin is not floating.

 
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

//Define the pins used for the LED's
int ledPins[6] = {4, 5, 6, 7, 8, 9};

//Define the different patterns for each number for the die
int dicePatterns[7][7] = {
  {0, 0, 0, 0, 0, 1},    // 1
  {0, 0, 1, 1, 0, 0},    // 2
  {0, 0, 1, 1, 0, 1},    // 3
  {1, 0, 1, 1, 0, 1},    // 4
  {1, 0, 1, 1, 1, 1},    // 5
  {1, 1, 1, 1, 1, 1},    // 6
  {0, 0, 0, 0, 0, 0}     // BLANK
};
  
// This is the pin that the button is attached to.  
int buttonPin = 11;

//blank is the last item in the defined number array.  It is used to turn off all LEDs (blank)
int blank = 6;

//=================================================================
//
// Function: setup
//
// Input: none
//
// Description:
//      In the setup routine, setup the pins for the output
//      We also set the seed for the Random function and setup
//      the serial output for the monitoring
//=================================================================

void setup()                    
{
  //set the pins for output and make sure they are off
  for (int i = 0; i < 6; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  
  //Set the seed for the random number generator by reading the current
  //value of the anonlog pin 0
  randomSeed(analogRead(0));
  
  //Start up the serial output
  Serial.begin(9600);
}

//=================================================================
//
// Function: loop
//
// Input: none
//
// Description:
//      This function will continuosly loop.  If the button is 
//      pressed it call the rollTheDice subroutine
//=================================================================

void loop()                    
{
  if (digitalRead(buttonPin))
  {
    Serial.println("Rolling The Dice");
    rollTheDice();
  }
  delay(100);
  
}

//========================================================================
//
// Function: rollTheDice
//
// Input: None
//
// Description:
//      This function will generate a random number between 15 and
//      25 and use it for the number of times the die will roll before
//      stopping.
//
//      It will loop once for each roll generating a random number
//      for each roll and displaying that random number on the simulated
//      die by setting calling the show function.
//
//      After is has gone through the loop the selected number of times
//      It stops on the last number and then blinks the number 3 times.
//========================================================================

void rollTheDice()
{
  int result = 0;
  int lengthOfRoll = random(15, 25);        //randomly determine how many rolls the die will do
  
  //print to the serial console the random number of rolls
  Serial.print(lengthOfRoll);
  Serial.println(" Rolls");
  
  //loop for each roll
  for (int i = 0; i < lengthOfRoll; i++)
  {
    result = random(0, 6);  // result will be 0 to 5 not 1 to 6
    show(result);
    
    //output this roll to serial monitor
    Serial.print("Roll: ");
    Serial.println(result+1);
    
    //remember that multiplication and division happen before addition and subtraction.
    //This means that the calculation below is the loop number multiplied by 10 then
    //50 added to it.  So each loop gets a longer delay simulating the die slowing down
    delay(50 + i * 10);
  }
  
  //we have fallen out of the roll loop, so print the last number to the serial monitor
  Serial.print("Dice Landed On: ");
  Serial.println(result+1);
  Serial.println("");
    
  //blink the final number 3 times
  for (int j = 0; j < 3; j++)
  {
    show(blank);
    delay(500);
    show(result);
    delay(500);
  }
}

//========================================================================
//
// Function: show
//
// Input: result (number to display on simulated die)
//
// Description:
//      This function loops through the dicePatterns and ledPins to set
//      the pins to the values in the array element for result.
//========================================================================
void show(int result)
{

 for (int i = 0; i < 6; i++)
 {
   digitalWrite(ledPins[i], dicePatterns[result][i]);
 }
}
