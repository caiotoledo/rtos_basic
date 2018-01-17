/*
 * USB.h
 *
 *  Created on: 11 de jan de 2018
 *      Author: caio
 */

#ifndef SRC_USB_H_
#define SRC_USB_H_

typedef enum {
  eGetValue,
  eSetValue,
  eInvalidValue
} eCommandType;

typedef struct stCommand_t stCommand;

typedef void (*funcCommand)(stCommand);

typedef struct stCommand_t {
  funcCommand func;
  eCommandType eCmdType;
  float fValue;
} stCommand;

void data_recv(void);
int regFunc(const char *cmd, funcCommand func);
void commandFuncThread(void);

#endif /* SRC_USB_H_ */
