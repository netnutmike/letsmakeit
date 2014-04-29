/*############### SEND SERVO POSITION BASED ON BUTTON VIA ZIGBEE ##################
       This code reads the button status and sends a pre-defined servo position
       based on what button is pressed.

 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 13 (http://tech-zen.tv/index.php/shows/let-s-make-it/episodes/59-sensor-fun-with-arduino-1-massive-failure-but-4-successes-let-s-make-it-episode-6)
       
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

int button1 = 9;
int button2 = 10;

int button1Value = 20;
int button2Value = 165;

int currentMode = 1;

void setup() 
{ 
  Serial.begin(9600);   // Startup the Serial Interface
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
} 
 
void loop() 
{ 
    char buf[4];
    
    if (!digitalRead(button1) && currentMode != 1) {
      sprintf(buf, "%d", button1Value);
      Serial.println(buf);
      currentMode = 1;
      delay(500);
    } 
    
    if (!digitalRead(button2) && currentMode != 2) {
      sprintf(buf, "%d", button2Value);
      Serial.println(buf);
      currentMode = 2;
      delay(500);
    }
}
