#include "BalanceMotor.h"

BalanceMotors::BalanceMotors():
	AFMS(Adafruit_MotorShield()).
	stepper_1_AFMS(AFMS.getStepper(STEPS_PER_REVOLUTION, 1)),
	stepper_2_AFMS(AFMS.getStepper(STEPS_PER_REVOLUTION, 2)),
	accel_stepper_1(stepper_1_AFMS_forward, stepper_1_AFMS_backward),
	accel_stepper_2(stepper_2_AFMS_forward, stepper_2_AFMS_backward)
{
	AFMS.begin();
}

BalanceMotors::~BalanceMotors()
{
}
void BalanceMotors::stepper_1_AFMS_forward()
{
	this->stepper_1_AFMS->onestep(FORWARD, SINGLE);
}

void BalanceMotors::stepper_1_AFMS_backward()
{
	this->stepper_1_AFMS->onestep(BACKWARD, SINGLE);
}

void BalanceMotors::stepper_2_AFMS_forward()
{
	this->stepper_2_AFMS->onestep(FORWARD, SINGLE);
}

void BalanceMotors::stepper_2_AFMS_backward()
{
	this->stepper_2_AFMS->onestep(BACKWARD, SINGLE);
}

bool BalanceMotors::run_motor(float motor_rpm, uint8_t motor_number)
{
	float motor_angular_velocity = motor_rpm * RPM_TO_RAD_PER_SECONDS;
	bool success;

	if (motor_number == 1)
	{
		this->accel_stepper_1.setSpeed(motor_angular_velocity);
		this.accel_stepper_1.runSpeed();
		success = true;
	}
	else if (motor_number == 2)
	{
		this->accel_stepper_2.setSpeed(motor_angular_velocity);
		this.accel_stepper_2.runSpeed();
		success = true;
	}
	else
	{
		success = false;
	}

	return success;
}