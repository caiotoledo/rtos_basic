/*
 * IMU.cpp
 *
 *  Created on: 27 de dez de 2017
 *      Author: caio
 */

#include "Utils.h"
#include "IMU.h"
#include "MPU6050.h"

#define SAMPLE_RATE_IMU   500

void imu_sample(const void *args);

MPU6050 imu;

RtosTimer imuSample(imu_sample, osTimerPeriodic, (void *)0);
bool boIMUSampleRunning = false;

void imu_sample(const void *args){
  int16_t accel[3] = { 0 };
  double fAccel[3] = { 0 };
  int16_t gyro[3] = { 0 };
  double fGyro[3] = { 0 };

  /* Get Accel Data: */
  imu.readAccelData(accel);
  for (int i = 0; i < 3; ++i) {
    fAccel[i] = accel[i] * imu.getAres();
  }
  pc.printf("Acceleration:\t%.3f\t%.3f\t%.3f\n\r", fAccel[0], fAccel[1], fAccel[2]);

  /* Get Gyro Data: */
  imu.readGyroData(gyro);
  for (int i = 0; i < 3; ++i) {
    fGyro[i] = gyro[i] * imu.getGres();
  }
  pc.printf("Gyroscope:\t%.3f\t%.3f\t%.3f\n\r", fGyro[0], fGyro[1], fGyro[2]);
}

void startIMUsample(stCommand val){

  if (val.eCmdType == eSetValue) {
    if (val.fValue > 0) {
      pc.printf("Start IMU Sample - For %.2f s\r\n", (float)(val.fValue/1000));
      imuSample.start(SAMPLE_RATE_IMU);
      boIMUSampleRunning = true;
      Thread::wait(val.fValue);
      boIMUSampleRunning = false;
      imuSample.stop();
      pc.printf("Finish IMU Sample\r\n");
    } else {
      boIMUSampleRunning = false;
      imuSample.stop();
    }
  } else if (val.eCmdType == eGetValue) {
    pc.printf("Thread IMU Sample %s\r\n", boIMUSampleRunning ? "Running" : "Stopped");
  }

}

void imu_thread(void){
  /* use fast (400 kHz) I2C */
  i2c.frequency(400000);

  /* Verify if MPU6050 is present: */
  char whoami = imu.readByte(MPU6050_ADDRESS, WHO_AM_I_MPU6050);
  if (whoami != 0x68){
    while(true){
      LOG("I SHOULD BE 0x68\n\r");
      Thread::wait(3000);
    }
  }

  /* Initialize MPU6050 */
  imu.initMPU6050();

  Thread::wait(osWaitForever);
}
