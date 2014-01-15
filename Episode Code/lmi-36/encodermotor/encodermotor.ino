/*######################### ENCODER DC MOTOR CONTROL ############################
       This sketch takes the encoder code from Episode 35 and uses it to control
       a the speed and direction of a DC motor.  Turning the encoder clockwise 
       starts the motor in the clockwise direction and turning the encoder more
       makes the motor run faster.
      
       Turn the encoder counter clockwise to slow it down to a stop.  Keep going 
       to have the motor go in reverse, keep turning to increase the speed. 
 
   From: Mike Myers (http://mikemyers.me)  @netnutmike
       Let's Make It Episode 36 at http://tech-zen.tv
       
       http://tech-zen.tv
       
       For the sample code, show notes, contact information and many more 
       videos, visit the show page at http://tech-zen.tv/letsmakeit

       Please subscribe to our YouTube channel or our netcasts at any of 
       your favorite netcast / podcast outlets.

       We normally record Let's Make It live on Monday evenings around 
       9pm eastern. You can watch it live by going to tech-zen.tv and clicking 
       the live link at the top of the page.

       We also have a community setup for our viewers and listeners. You can 
       join the community by going to community.tech-zen.tv.

       We love input on what you would like to know or if you have an idea for 
       a new Let's Make it episode, you can contact us via email or phone at 
       the show information page.
################################################################################*/

#include <AccelStepper.h>
#include <AFMotor.h>

#define encoderPinA  53
#define encoderPinB  51

int motorspeed = 0;
int encoderPinALast = LOW;
int encoderPinBLast = LOW;
int n = LOW;

AF_DCMotor motor(1);

void setup()
{  
    motor.setSpeed(0);
 
    motor.run(RELEASE);
    //motor.run(FORWARD);
    
    pinMode(encoderPinA, INPUT_PULLUP); 
    pinMode(encoderPinB, INPUT_PULLUP);
}

void loop()
{  
    n = digitalRead(encoderPinA);
   if ((encoderPinALast != n )) {
     if (((n == HIGH) && (digitalRead(encoderPinB) == LOW)) || 
         ((n == LOW) && (digitalRead(encoderPinB) == HIGH))) {
       motorspeed = motorspeed - 10;
     } else {
       motorspeed = motorspeed + 10;
     }
     //Serial.print(encoderPos);
     //Serial.println(" ");
   } else {
     n = digitalRead(encoderPinB);
     if ((encoderPinBLast != n )) {
       if (((n == HIGH) && (digitalRead(encoderPinA) == LOW)) || 
           ((n == LOW) && (digitalRead(encoderPinA) == HIGH))) {
         motorspeed = motorspeed + 10;
       } else {
         motorspeed = motorspeed - 10;
       }
       //Serial.print(encoderPos);
       //Serial.println(" ");
     }
   }
   encoderPinALast = digitalRead(encoderPinA);
   encoderPinBLast = digitalRead(encoderPinB);
   
   if (motorspeed > 10) {
     if (motorspeed > 200)
       motorspeed = 200;
     motor.setSpeed(motorspeed);
     motor.run(FORWARD);
   } else if (motorspeed < -10) {
     if (motorspeed < -200)
       motorspeed = -200;
     motor.setSpeed(abs(motorspeed));
     motor.run(BACKWARD);
   } else {
     motor.run(RELEASE);
   }
    
}
