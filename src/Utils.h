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

#define PROJECT_NAME  "rtos_basic"

extern Serial serialDebug;

#define LOG(...)    serialDebug.printf(__VA_ARGS__);

extern USBSerial pc;

void formatVersion(char *buildVersion);

#endif /* UTILS_H_ */
