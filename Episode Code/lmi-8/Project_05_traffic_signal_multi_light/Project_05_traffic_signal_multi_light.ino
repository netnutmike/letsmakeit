/*########## SIMULATE REAL-LIFE TRAFFIC SIGNAL WITH TRAFFIC SENSOR ##################
       This code simulates a Traffic Signal with 2 different traffic lights.  It
       also simulates 2 different traffic sensors that detect when cars are waiting
       and changes the light timing based on waiting cars.

 
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
int redPin[] = {9, 6};
int yellowPin[] = {8, 5};
int greenPin[] = {7, 4};

//Define the Pin used for the button
int buttonPin[] = {11, 10};

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
  //setup pins for light 0
  pinMode(redPin[0], OUTPUT);    
  pinMode(yellowPin[0], OUTPUT);    
  pinMode(greenPin[0], OUTPUT);     
  pinMode(buttonPin[0], INPUT); 
  
  //setup pins for light 1
  pinMode(redPin[1], OUTPUT);    
  pinMode(yellowPin[1], OUTPUT);    
  pinMode(greenPin[1], OUTPUT);     
  pinMode(buttonPin[1], INPUT);
  
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
//      pressed it will cylcle through the 4 different states
//=================================================================

void loop()                    
{
  int wcnt;              //user for the wait counter
  
  switch (state) {
    case 0:                          //Light 1 green, wait for 10 seconds if a car is at light 2 or 20 seconds if no car
      setLights(0, LOW, LOW, HIGH);
      setLights(1, HIGH, LOW, LOW);
      
      Serial.println("Light 0 is Green");
      
      //Loop every 1 second, after 10 seconds look at the other light for a car waiting and continue right away if so
      //if not wait for 20 seconds
      
      wcnt=0;
      do {
        delay(1000);
        ++wcnt;
        
        Serial.println(wcnt);
        
        //just for my debugging
        if (digitalRead(buttonPin[1]))
          Serial.println("A Car is waiting at Light 1");
          
      } while (wcnt < 20 && !(wcnt > 10 && digitalRead(buttonPin[1])));
      
      break;
      
    case 1:                          //Light 1 Yellow for 10 Seconds
      setLights(0, LOW, HIGH, LOW);
      Serial.println("Light 0 is Yellow");
      delay(10000);
      break;
      
    case 2:                          //Light 1 Red, Wait 5 seconds for traffic to clear out of intersection
      setLights(0, HIGH, LOW, LOW);
      Serial.println("Light 0 is Red");
      delay(5000);
      break;
      
    case 3:                          // Light 2 Green, wait for 15 seconds if car is at light or 25 seconds if no car
      setLights(1, LOW, LOW, HIGH);
      Serial.println("Light 1 is Green");
      //Loop every 1 second, after 10 seconds look at the other light for a car waiting and continue right away if so
      //if not wait for 20 seconds
      
      wcnt=0;
      do {
        delay(1000);
        ++wcnt;
        
        Serial.println(wcnt);
        //just for my debugging
        if (digitalRead(buttonPin[0]))
          Serial.println("A Car is waiting at Light 0");
          
      } while (wcnt < 25 && !(wcnt > 15 && digitalRead(buttonPin[0])));
      
      break;
      
    case 4:                          // Light 2 Yellow for 10 seconds
      setLights(1, LOW, HIGH, LOW);
      Serial.println("Light 1 is Yellow");
      delay(10000);
      break;
      
    case 5:                          // Light 2 Red, wait for 5 seconds for traffic to clear out of intersection
      setLights(1, HIGH, LOW, LOW);
      Serial.println("Light 1 is Red");
      delay(5000);
      break;
      
    
  }
  
  ++state;
  if (state > 5)
    state = 0;
      
  
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

void setLights(int light, int red, int yellow, int green)
{
  digitalWrite(redPin[light], red);
  digitalWrite(yellowPin[light], yellow);
  digitalWrite(greenPin[light], green);
}  
  
