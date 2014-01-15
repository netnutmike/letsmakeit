/*######################  TRAFFIC SIGNAL EXAMPLE #################################
       This code is the first step in demonstrating creating a traffic signal
       with an arduino.  In this example we first create a sketch that cycles
       the traffic light from red-yellow-green-yellow and then back to red.
       
       This is done by creating a State table.  So we introduce how a state
       table works.

 
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

//Define the pins used for the LED's for Light 1
int redPin = 6;
int yellowPin = 5;
int greenPin = 4;

//Define the Pin used for the button
int buttonPin = 10;

//Define the variable that is used to remember the state of the light
int state = 0;

//=================================================================
//
// Function: setup
//
// Input: none
//
// Description:
//      In the setup routine, setup the pins for the input or 
//      output depending on how they are going to be used
//=================================================================

void setup()                    
{
  pinMode(redPin, OUTPUT);    
  pinMode(yellowPin, OUTPUT);    
  pinMode(greenPin, OUTPUT);     
  pinMode(buttonPin, INPUT); 
}

//=================================================================
//
// Function: loop
//
// Input: none
//
// Description:
//      This function will continuosly loop.  If the button is 
//      pressed it will cylcle through the 4 different states
//=================================================================

void loop()                    
{
  if (digitalRead(buttonPin))
  {
    if (state == 0)
    {
      setLights(HIGH, LOW, LOW);
      state = 1;                      //move to next state
    }
    else if (state == 1)
    {
      setLights(LOW, HIGH, LOW);
      state = 2;                      //move to next state
    }
    else if (state == 2)
    {
      setLights(LOW, LOW, HIGH);
      state = 3;                      //move to next state
    }
    else if (state == 3)
    {
      setLights(LOW, HIGH, LOW);
      state = 0;                      //start over
    }
    delay(1000);
  }
}

//=================================================================
//
// Function: setLights
//
// Input: Status of the Red, Yellow and Green Lights
//
// Description:
//      This function takes as input the state of each of the 
//      colored LED's and turns them either on or off depending 
//      on the status passed in.
//=================================================================

void setLights(int red, int yellow, int green)
{
  digitalWrite(redPin, red);
  digitalWrite(yellowPin, yellow);
  digitalWrite(greenPin, green);
}  
  
