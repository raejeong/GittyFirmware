#ifndef BALANCE_MOTORS_H
#define BALANCE_MOTORS_H

#include "Adafruit_MotorShield.h"
#include "AccelStepper.h"

#define STEPS_PER_REVOLUTION 200
#define RPM_TO_RAD_PER_SECONDS 0.10471975512

class BalanceMotors
{
private:
	Adafruit_MotorShield AFMS;
	Adafruit_StepperMotor *stepper_1_AFMS;
	Adafruit_StepperMotor *stepper_2_AFMS;
	AccelStepper accel_stepper_1;
	AccelStepper accel_stepper_2;
	void stepper_1_AFMS_forward();
	void stepper_1_AFMS_backward();
	void stepper_2_AFMS_forward();
	void stepper_2_AFMS_backward();

public:
	BalanceMotors();
	~BalanceMotors();
	bool run_motor(float speed, uint8_t motor_number);
}

#endif