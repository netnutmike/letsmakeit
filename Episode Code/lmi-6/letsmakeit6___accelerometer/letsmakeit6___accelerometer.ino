/*############### VIRTUABOTIX BASIC ACCELEROMETER CODE #########################
This code enables the accelarometer and reads in the values via analog pin
and outputs the values to the serial monitor.

Below is a pinout layout that I took from the sample code header.

            ######################################################
 TO PIN A0  #                                                    # To 5 Volts
       ######                                                    ######
       #    #     X Axis                              5 Volt     #    #
       ######                                                    ######
 TO PIN A1  #                                                    #
       ######                                                    ######
       #    #     Y Axis                              3.3 Volt   #    #
       ######                                                    ######
 TO PIN A2  #                                                    # To Ground
       ######                                                    ######
       #    #     Z Axis                              Ground     #    #
       ######                                                    ######
 TO PIN 4   #                                                    #
       ######                                                    ######
       #    #     Sleep                 GS (Sensitivity Select)  #    #
       ######                                                    ######
            #                                                    #
       ######                                                    ######
       #    #     0G                             ST (Self Test)  #    #
       ######                                                    ######
            #                                                    #
            ######################################################
    
 
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

int sleepPin= 4;      // Turning sleep high turns on the Accelerometer
int HiPrecision=5;    // This pin sets the precision.  Play with the values by setting it HIGH and LOW
int xpin= A0;         // Anolog pin for reading the X value
int ypin = A1;        // Analog pin for reading the Y value
int zpin = A2;        // Analog pin for reading the Z value

void setup()
{
  // Setup serial port for outputting to the serial monitor.  Be sure your seial monitor is set to 115200
  Serial.begin(115200);
  
  //##########################################
  //  Setup our pins
  //##########################################
  
  //Set the sleep pin as output and set it high to turn on the acceleromiter
  pinMode(sleepPin,OUTPUT);
  digitalWrite(sleepPin, HIGH);//turns off sleep mode and activates device
  
  //Set the Precision pin to output and set it low.  This seems to get the most variation in value.
  pinMode(HiPrecision,OUTPUT);
  digitalWrite(HiPrecision, LOW);
  
  //Setup each analog pin as input and set the internal pull-up resitor to on.
  pinMode(xpin, INPUT);//input mode
  digitalWrite(xpin, HIGH);//turn on pull up resistor
  
  pinMode(ypin, INPUT);//input mode
  digitalWrite(ypin, HIGH);//turn on pull up resistor
  
  pinMode(zpin, INPUT);//input mode
  digitalWrite(zpin, HIGH);//turn on pull up resistor
}

// Time to do the actual work
void loop()
{
delay(2000); //Delay for readability on the serial monitor

/output a title and pin value for X, Y and Z
Serial.print("X Reading: "); 
Serial.println(analogRead(xpin), DEC);
Serial.print("Y Reading: "); 
Serial.println(analogRead(ypin), DEC);
Serial.print("Z Reading: "); 
Serial.println(analogRead(zpin), DEC);
Serial.println(" ");
}


