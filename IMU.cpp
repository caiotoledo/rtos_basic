/*
 * IMU.cpp
 *
 *  Created on: 27 de dez de 2017
 *      Author: caio
 */

#include "Utils.h"
#include "IMU.h"
#include "MPU6050.h"

DigitalOut led1(LED1);

void imu_thread(void){
  MPU6050 imu;
  i2c.frequency(400000);  // use fast (400 kHz) I2C
  while(true){
    char whoami = imu.readByte(MPU6050_ADDRESS, WHO_AM_I_MPU6050);  // Read WHO_AM_I register for MPU-6050

    if (0x68 == whoami) {
      pc.printf("I AM 0x%x\n\r", whoami);
      led1 = !led1;
    } else {
      i2c.stop();
      i2c.start();
      pc.printf("I SHOULD BE 0x68\n\r");
    }

    Thread::wait(1000);
  }
}
