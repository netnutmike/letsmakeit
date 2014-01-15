
/*########################## COLOR SENSOR SAMPLE ################################
       This code is for reading a color sensor to determine the RGB values
       of the color the sensor is seeing.
       
       The sensor can only read one color at a time.  The sensor contains 4
       different light sensors.  One with a filter for red light, one with
       a filter for green light and one with a sensor for blue light.  The
       4th sensor is a clear filter.
       
       You set options by setting 4 different pins high or low.  Before you
       read a color you have to tell the sensor which color you want to read
       by setting the 4 option pins.

 
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


int s0=3, s1=4, s2=5, s3=6;      //define the 4 pins used for options
int out=2;
int flag=0;
byte counter=0;
byte countR=0,countG=0,countB=0;

void setup()
{
   Serial.begin(115200);
   pinMode(s0,OUTPUT);
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
 
}

void TCS()
 {
   flag=0; 
   digitalWrite(s1,HIGH);
   digitalWrite(s0,HIGH);
   digitalWrite(s2,LOW);
   digitalWrite(s3,LOW);
   attachInterrupt(0, ISR_INTO, LOW);
   timer0_init();
 
 }
 
void ISR_INTO()
 {
   counter++;
 }
 
 void timer0_init(void)
 {
    TCCR2A=0x00;
    TCCR2B=0x07;   //the clock frequency source 1024 points
    TCNT2= 100;    //10 ms overflow again
    TIMSK2 = 0x01; //allow interrupt
 }
 
 int i=0;
 ISR(TIMER2_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
{
     TCNT2=100;
     flag++;
    
     if(flag==1)
      {
        countR=counter;
        digitalWrite(s2,HIGH);
        digitalWrite(s3,HIGH);
      }
      else if(flag==2)
       {
        countG=counter;
        digitalWrite(s2,LOW);
        digitalWrite(s3,HIGH);
       }
       else if(flag==3)
        {
        countB=counter;
        digitalWrite(s2,LOW);
        digitalWrite(s3,LOW);
        
        }
        else if(flag==4)
         {
         flag=0;
         }
 counter=0;
}
void loop()
 {
  TCS();
do {
  Serial.print("red=");
  Serial.println(countR,DEC);
  Serial.print("green=");
  Serial.println(countG,DEC);
  Serial.print("blue=");
  Serial.println(countB,DEC);
  Serial.println("\n");
  delay(500);
} while(1);
 }
