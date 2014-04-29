/*############### SET SERVO POSITION BASED ON SERIAL INPUT #########################
       This code will take input from the Serial port in the form of a number.
       
       It takes this number and positions a servo between 0 and 180 degrees.
       
       To know when the number actually ends, a non numeric character must follow
       the number.  Typically the serial input would not be used, it is just for this 
       example.

 
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

#include <Servo.h> 
 
Servo myservoa;          // Create servo object to control a servo 
Servo myservob;
Servo myservoc;
Servo myservod;
 
char readstr[4];        // Character Array to store the serial input
int cstrpos = 0;        // Variable to store the current input array position
long val = 0;           // variable to store the value from the input 
 
int maxValue = 175;
int mode = 0;
int servo = 1;
int numbers = 0;
char servoid;
 
void setup() 
{ 
  Serial.begin(9600);   // Startup the Serial Interface
  myservoa.attach(9);    // Attaches the servo on pin 9 to the servo object 
  myservob.attach(10);
  myservoc.attach(11);
  myservod.attach(6);
} 
 
void loop() 
{ 
  char ch;              //A Place to Store the character we just read
  
  if (Serial.available())      // is there anything to be read from serial port?
  {
    ch = Serial.read();        // read a single character
    
    // print out to serial port the character we received (similar to an echo)
    Serial.print(ch);
    if (ch >= 'a' && ch <= 'd') {
      mode = numbers;
      servoid = ch;
    }
    
    if (mode == numbers) {
      if (ch >= '0' && ch <= '9')    // Number so store it in the input array
      {
        readstr[cstrpos] = ch;      // Add the read character to the array of read numbers
        ++cstrpos;                  // Increase the position in the array
      }
      else                          // not a number so lets set the position of the servo
      {
       readstr[cstrpos] = '\0';     // Add a null to the end of the string array to terminate the string
       val = atol(readstr);         // Convert the string to a long int
   
       if (val > maxValue) {
         val = 175;
       }
       
       cstrpos = 0;                 // Reset the array position back to the beginning so the next input starts a new input
       
       //Print to the serial port what we are going to do
       Serial.print("Servo ");
       Serial.print(servoid);
       Serial.print(" set to: ");
       Serial.println(val);
       Serial.println("");
       mode = servo;
      }
    }
  } 
  
  // The servo needs constant feed of values so we constantly output the PWM value
  myservo.write(val);            // Set the PWM value to send to the servo
  delay(15);                     // Just a little delay
    
} 
