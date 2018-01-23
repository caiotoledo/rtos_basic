/*
 * IMU.h
 *
 *  Created on: 28 de dez de 2017
 *      Author: caio
 */

#ifndef IMU_H_
#define IMU_H_

void imu_thread(void);

/* Command Callback Functions: */
void startIMUsample(stCommand val);
void setIMUSampleRate(stCommand val);

#endif /* IMU_H_ */
