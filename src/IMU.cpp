/*
 * IMU.cpp
 *
 *  Created on: 27 de dez de 2017
 *      Author: caio
 */

#include "Utils.h"
#include "IMU.h"
#include "MPU6050.h"

MPU6050 imu;
DigitalOut led1(LED1);

void imu_sample(const void *args){
  int16_t accel[3] = { 0 };
  int16_t gyro[3] = { 0 };

  /* Get Accel Data: */
  imu.readAccelData(accel);
  pc.printf("Accel: %d - %d - %d\n\r", accel[0], accel[1], accel[2]);

  /* Get Gyro Data: */
  imu.readGyroData(gyro);
  pc.printf("Gyro: %d - %d - %d\n\r", gyro[0], gyro[1], gyro[2]);

  led1 = !led1;
}

void imu_thread(void){
  /* use fast (400 kHz) I2C */
  i2c.frequency(400000);

  /* Verify if MPU6050 is present: */
  char whoami = imu.readByte(MPU6050_ADDRESS, WHO_AM_I_MPU6050);
  if (whoami != 0x68){
    pc.printf("I SHOULD BE 0x68\n\r");
    return;
  }

  /* Initialize MPU6050 */
  imu.initMPU6050();

  RtosTimer imuSample(imu_sample, osTimerPeriodic, (void *)0);
  imuSample.start(1000);

  Thread::wait(osWaitForever);
}
