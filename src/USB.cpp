/*
 * USB.cpp
 *
 *  Created on: 11 de jan de 2018
 *      Author: caio
 */

#include "Utils.h"
#include "USB.h"

#define MAX_CMD     50

Queue<stCommand,MAX_CMD> qCommand;

struct cmd2Func {
  char str[50];
  funcCommand func;
};

struct cmd2Func mapFunc[MAX_CMD];
unsigned int lenMapFunc = 0;

char szMsg[100] = { 0 };
unsigned int uiLenMsg = 0;

static funcCommand Cmd2Func(char *szFunc){
  for (unsigned int i = 0; i < lenMapFunc; ++i) {
    if ( 0 == strcmp(szFunc, mapFunc[i].str) ) {
      /* Command found! */
      return mapFunc[i].func;
    }
  }

  /* If command isn't found return null */
  return NULL;
}

static int parseCmd(char *str, stCommand *cmd){

  unsigned int uiParseCount = 0;
  cmd->func = NULL;
  cmd->fValue = 0;
  cmd->eCmdType = eInvalidValue;

  char *pch;
  pch = strtok(str, ";");

  while (pch != NULL) {
    switch (uiParseCount++) {
    case 0:
      cmd->func = Cmd2Func(pch);
      if (!cmd->func) {
        return -1;
      }
      break;
    case 1:
      cmd->eCmdType = (eCommandType) atoi(pch);
      break;
    case 2:
      cmd->fValue = atoff(pch);
      break;
    default:
      break;
    }
    pch = strtok(NULL, ";");
  }

  return 0;
}

void commandFuncThread(void){
  while(true)
  {
    osEvent evt = qCommand.get();
    if (evt.status == osEventMessage) {
      stCommand *message = (stCommand*)evt.value.p;
      message->func(*message);
    }
  }
}

void data_recv(void){
  char *buf = (char *) malloc( sizeof(char) * (pc.available() + 1) );
  pc.gets(buf, pc.available()+1);
  LOG("%s", buf);

  /* Check if is a new string */
  if (strlen(buf) > 0) {
    /* Store this the message */
    memcpy( &szMsg[uiLenMsg], buf, strlen(buf));
    uiLenMsg += strlen(buf);
    szMsg[uiLenMsg] = 0;

    /* Check for a end message */
    if (strstr(szMsg, "\r")) {

      stCommand recvCmd;
      int ret = parseCmd(szMsg, &recvCmd);
      if ( 0 == ret ) {
        qCommand.put(&recvCmd);
      }

      memset(szMsg, 0, sizeof(szMsg));
      uiLenMsg = 0;
    }
  }

  free(buf);
}

int regFunc(const char *cmd, funcCommand func){

  if (!func) {
    return -1;
  }

  if (!cmd) {
    return -1;
  }

  if (lenMapFunc >= MAX_CMD) {
    return -1;
  }

  /* Adding new Function to map: */
  mapFunc[lenMapFunc].func = func;
  strcpy(mapFunc[lenMapFunc].str, cmd);
  lenMapFunc++;

  return 0;
}
