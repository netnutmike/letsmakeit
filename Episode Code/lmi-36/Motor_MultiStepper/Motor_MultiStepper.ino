// MultiStepper
// -*- mode: C++ -*-
//
// Control both Stepper motors at the same time with different speeds
// and accelerations. 
// Requires the AFMotor library (https://github.com/adafruit/Adafruit-Motor-Shield-library)
// And AccelStepper with AFMotor support (https://github.com/adafruit/AccelStepper)
// Public domain!

#include <AccelStepper.h>
#include <AFMotor.h>

// two stepper motors one on each port

AF_Stepper motor2(200, 2);
AF_DCMotor motor(1);

// wrappers for the second motor!
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
    stepper2.moveTo(2048);
    
    motor.setSpeed(200);
 
    motor.run(RELEASE);
    motor.run(FORWARD);
}

void loop()
{
    // Change direction at the limits
    if (stepper2.distanceToGo() == 0) {
	stepper2.moveTo(-stepper2.currentPosition());
        motor.run(BACKWARD);
    }
    stepper2.run();
    
    
}
