/*######################### READING BIO-FEEDBACK #########################
       This code outpus the feedback readings so you can see how the 
       Lie Detector works.

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 12 (http://tech-zen.tv/index.php/shows/let-s-make-it/episodes/59-sensor-fun-with-arduino-1-massive-failure-but-4-successes-let-s-make-it-episode-6)
       
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

int potPin = 1;
int sensorPin = 0;

int band=55;

void setup()
{
  pinMode(potPin, INPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int sensor = analogRead(sensorPin);
  int pot = analogRead(potPin);
  Serial.print("Pot: ");
  Serial.print(pot);
  Serial.print("   Sensor Input: ");
  Serial.print(sensor);
  Serial.print("   LED: ");
  if (sensor > (pot + band))
    Serial.println("RED");
  else if (sensor < (pot - band))
    Serial.println("BLUE");
  else
    Serial.println("GREEN");
    
 delay(500);
}

  
