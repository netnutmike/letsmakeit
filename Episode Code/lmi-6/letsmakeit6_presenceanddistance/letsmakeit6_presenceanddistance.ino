
/*############### PRESENCE AND DISTANCE SENSORS SAMPLE #########################
       This code monitors 2 different sensors.  One is monitored for presence and
       is basically a motion sensor that turn a pin high when it senses some
       motion.
       
       The other sensor is a distance sensor that we send a trigger signal to
       and then measure the amount of time it takes to get an echo.  Based on
       the amount of time we can calculate the distance to an object in front 
       of the sensor.

 
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

int MovementPin= 5;   // Define the pin we will use to read the presense state
int TriggerPin=13;    // Define the pin that we use to set off the trigger
int EchoPin= 12;      // Define the pin that we will use to read the echo response

void setup()
{
  // Start the serial port for the seial monitor at 115200.  Be sure your serial monitor is 115200
  Serial.begin(115200);

  // Setup the pins for INPUT and OUTPUT
  pinMode(TriggerPin,OUTPUT);   // output Mode
  pinMode(EchoPin, INPUT);      // input mode
  pinMode(MovementPin, INPUT);  // input mode
}

void loop()
{
  // define the 2 variables that we will use in this function
  long duration, distance;
  
  // set the pin low and wait 2 microseconds
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  
  // set the trigger pin high to transmit sound for 10 microseconds
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  
  // after 10 microseconds turn off the transmitter
  digitalWrite(TriggerPin, LOW);
  
  // read the duration by timing how long it takes for the echo to stop
  duration = pulseIn(EchoPin, HIGH);
  distance = duration / 148;      // device the duration by 148 for inches or 58 for centimeters
  
  // output the distance calculated
  Serial.print(distance);
  Serial.println(" inches");
  
  //check the pin for movement.  If it is high then movment was detected, so output to serial
  if (digitalRead(MovementPin)) {
    Serial.println("Movement Detected");
  }
  
  // just a blank line to make the serial monitor easier to read
  Serial.println(" ");
  
  delay(2000); //Delay for readability

}


