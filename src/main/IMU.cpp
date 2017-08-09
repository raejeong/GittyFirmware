#include "IMU.h"

IMU::IMU():
   bno(Adafruit_BNO055(55))
{
}

IMU::~IMU()
{
}

bool IMU::initialize_imu()
{
  bool success = this->bno.begin();
  if(success)
  {
    delay(1000);
    bno.setExtCrystalUse(true);
  }
  return success;
}

bool IMU::calibrate_imu(int (&calibration_info)[4])
{
    bool success;
    /* Get the four calibration values (0..3) */
    /* Any sensor data reporting 0 should be ignored, */
    /* 3 means 'fully calibrated" */
    uint8_t system, gyro, accel, mag;
    system = gyro = accel = mag = 0;
    this->bno.getCalibration(&system, &gyro, &accel, &mag);
    calibration_info[0] = system;
    calibration_info[1] = gyro;
    calibration_info[2] = accel;
    calibration_info[3] = mag;

    success = system==3 and gyro==3 and accel==3 and mag==3;
    return success;
}

void IMU::get_imu_data(float (&imu_data)[7])
{
  imu::Vector<3> acceleration = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Quaternion quaternion = bno.getQuat();
  imu_data[0] = acceleration.x();
  imu_data[1] = acceleration.y();
  imu_data[2] = acceleration.z();
  imu_data[3] = quaternion.x();
  imu_data[4] = quaternion.y();
  imu_data[5] = quaternion.z();
  imu_data[6] = quaternion.w();
}