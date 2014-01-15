/*######################### ENCODER TO STEPPER MOTOR ############################
       This sketch takes the encoder code from Episode 35 and uses it to control
       a stepper motor.  We turn the encoder clockwise and the stepper motor turns
       clockwise as well.  Same thing for turning the encoder counter clockwise. 
 
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

int encoderPos = 0;
int encoderPinALast = LOW;
int encoderPinBLast = LOW;
int n = LOW;

AF_Stepper motor2(200, 2);

// wrappers for the motor!
void forwardstep2() {  
  motor2.onestep(FORWARD, SINGLE);
}
void backwardstep2() {  
  motor2.onestep(BACKWARD, SINGLE);
}

// Motor shield has two motor ports, now we'll wrap them in an AccelStepper object
AccelStepper stepper2(forwardstep2, backwardstep2);

void setup()
{  
    stepper2.setMaxSpeed(500.0);
    stepper2.setAcceleration(100.0);
    stepper2.moveTo(0);
    
    pinMode(encoderPinA, INPUT_PULLUP); 
    pinMode(encoderPinB, INPUT_PULLUP);
}

void loop()
{  
    n = digitalRead(encoderPinA);
   if ((encoderPinALast != n )) {
     if (((n == HIGH) && (digitalRead(encoderPinB) == LOW)) || 
         ((n == LOW) && (digitalRead(encoderPinB) == HIGH))) {
       motor2.step(100, BACKWARD, MICROSTEP);
     } else {
       motor2.step(100, FORWARD, MICROSTEP);
     }
   } else {
     n = digitalRead(encoderPinB);
     if ((encoderPinBLast != n )) {
       if (((n == HIGH) && (digitalRead(encoderPinA) == LOW)) || 
           ((n == LOW) && (digitalRead(encoderPinA) == HIGH))) {
         motor2.step(100, FORWARD, MICROSTEP);
       } else {
         motor2.step(100, BACKWARD, MICROSTEP);
       }
     }
   }
   encoderPinALast = digitalRead(encoderPinA);
   encoderPinBLast = digitalRead(encoderPinB);
    
}
