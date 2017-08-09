// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
// Requires the Adafruit_Motorshield v2 library 
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
// And AccelStepper with AFMotor support 
//   https://github.com/adafruit/AccelStepper

// This tutorial is for Adafruit Motorshield v2 only!
// Will not work with v1 shields

#include "AccelStepper.h"
#include "Adafruit_MotorShield.h"
#include "Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myStepper1 = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMS.getStepper(200, 2);


// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
void forwardstep1() {  
  myStepper1->onestep(FORWARD, DOUBLE);
}
void backwardstep1() {  
  myStepper1->onestep(BACKWARD, DOUBLE);
}
void forwardstep2() {  
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {  
  myStepper2->onestep(BACKWARD, DOUBLE);

}

AccelStepper Astepper1(forwardstep1, backwardstep1); // use functions to step
AccelStepper Astepper2(forwardstep2, backwardstep2); // use functions to step


void setup()
{  
   Serial.begin(9600);           // set up Serial library at 9600 bps
   Serial.println("Stepper test!");
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  // myStepper1->setSpeed(10);
  Astepper1.setSpeed(500);
  Astepper2.setSpeed(500);	
	
}

void loop()
{  
	// myStepper1->step(100,FORWARD,SINGLE);
	// myStepper1->step(100,BACKWARD,SINGLE);
   Astepper1.runSpeed();
   Astepper2.runSpeed();
}