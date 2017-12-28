/*
 * Utils.h
 *
 *  Created on: 27 de dez de 2017
 *      Author: caio
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "mbed.h"
#include "rtos.h"
#include "USBSerial.h"
#include "I2C.h"

extern USBSerial pc;

#define PROJECT_NAME  "rtos_basic"

void formatVersion(char *buildVersion);


#endif /* UTILS_H_ */
