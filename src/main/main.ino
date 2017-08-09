#include "IMU.h"
#include "Adafruit_MS_PWMServoDriver.h"
#include "Adafruit_MotorShield.h"
#include "AccelStepper.h"

#define STEPS_PER_REVOLUTION 200
#define RPM_TO_RAD_PER_SECONDS 0.10471975512
#define JUMP_PIN 7
#define DATA_FLAG 999

IMU robot_imu;
int commands[] = {0, 0, 0};

// BalanceMotors robot_motors;

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// two stepper motors one on each port
// Adafruit_StepperMotor *motor1 = AFMS.getStepper(STEPS_PER_REVOLUTION, 1);
Adafruit_StepperMotor *motor2 = AFMS.getStepper(STEPS_PER_REVOLUTION, 2);

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
// void forwardstep1()
// {  
//   motor1->onestep(FORWARD, INTERLEAVE);
// }

// void backwardstep1()
// {  
//   motor1->onestep(BACKWARD, INTERLEAVE);
// }
// wrappers for the second motor!
void forwardstep2()
{  
  motor2->onestep(FORWARD, INTERLEAVE);
}
void backwardstep2()
{  
  motor2->onestep(BACKWARD, INTERLEAVE);
}

// Motor shield has two motor ports, now we'll wrap them in an AccelStepper object
// AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);

bool set_motor_speed(int motor_rpm, int motor_number)
{
	float motor_angular_velocity = motor_rpm * RPM_TO_RAD_PER_SECONDS;
	bool success;

	if (motor_number == 1)
	{
		// stepper1.setSpeed(motor_angular_velocity);
		// stepper1.runSpeed();
		success = true;
	}
	else if (motor_number == 2)
	{
		stepper2.setSpeed(motor_angular_velocity);
		stepper2.runSpeed();
		success = true;
	}
	else
	{
		success = false;
	}

	return success;
}

void run_motors()
{
	// stepper1.runSpeed();
	stepper2.runSpeed();
}


void send_info(String info)
{
	Serial.print(0);
	Serial.print(", ");
	Serial.println(info);
}

void send_data(float data[])
{
	Serial.print(1);
	Serial.print(", ");
	int data_len = 7;
	for(int i=0; i<data_len-1; i++)
	{
		Serial.print(data[i]);
		Serial.print(", ");
	}
	Serial.println(data[data_len-1]);
}

void read_data()
{
	if(Serial.available() >= 7)
	{
		int data_flag = Serial.parseInt();
		Serial.println(data_flag,DEC);
		if(data_flag==DATA_FLAG)
		{
			for(int i=0; i<3; i++)
			{
				commands[i] = Serial.parseInt();
			}
			set_motor_speed(commands[1], 1);
			set_motor_speed(commands[2], 2);
			send_info("INFO: Command data received.");
		}
		else
		{
			Serial.flush();
		}
	}
}

void jump(int jump_effort)
{
	analogWrite(JUMP_PIN, jump_effort);
}

void setup()
{
	bool success;
	Serial.begin(9600);
	send_info("INFO: Serial started");
	success = robot_imu.initialize_imu();
	while(!success)
	{
		success = robot_imu.initialize_imu();
	}
	send_info("INFO: IMU initialized!");
	AFMS.begin();
	int calibration_info[] = {0, 0, 0, 0};
	String calibration_string;
	success = false;
	do
	{
		success = robot_imu.calibrate_imu(calibration_info);
		calibration_string = "ERROR: IMU needs to be calibrated. system: ";
		calibration_string += calibration_info[0];
		calibration_string += ", gyro: ";
		calibration_string += calibration_info[1];
		calibration_string += ", accel: ";
		calibration_string += calibration_info[2];
		calibration_string += ", mag: ";
		calibration_string += calibration_info[3];
		send_info(calibration_string);
		delay(1000);
		success = true;
	}while(!success);
	calibration_string = "ERROR: IMU calibrated. system: ";
	calibration_string += calibration_info[0];
	calibration_string += ", gyro: ";
	calibration_string += calibration_info[1];
	calibration_string += ", accel: ";
	calibration_string += calibration_info[2];
	calibration_string += ", mag: ";
	calibration_string += calibration_info[3];
	send_info(calibration_string);
	// stepper1.setSpeed(200);
	stepper2.setSpeed(200);
	pinMode(JUMP_PIN, OUTPUT);
}

void loop()
{
	// int success;
	// read_data();
	// jump(commands[0]);
	run_motors();
	// float imu_data[7];
	// robot_imu.get_imu_data(imu_data);
	// send_data(imu_data);
}
