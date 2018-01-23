#include "Utils.h"

#include "IMU.h"
#include "USB.h"

#define BLINK_TIME    500

DigitalOut led1(LED1);
unsigned int ledTime = 500;

Thread tFunc;
Thread tLED;
Thread tImu(osPriorityRealtime,DEFAULT_STACK_SIZE,0);

void led_thread(void){
  while(true){
    led1 = !led1;
    Thread::wait(ledTime);
  }
}

void startLedThread(stCommand val){
  if (val.eCmdType == eSetValue) {
    if (val.fValue > 0) {
      ledTime = val.fValue;
      tLED.start(led_thread);
      pc.printf("LED Thread Started! BlinkTime %d ms\r\n", ledTime);
    } else {
      tLED.terminate();
      led1 = 0;
      pc.printf("LED Thread Finish!\r\n");
    }
  } else if (val.eCmdType == eGetValue) {
    bool isRunning = true;
    if (tLED.get_state() == Thread::Deleted) {
      isRunning = false;
    }
    pc.printf("Thread LED %s\r\n", isRunning ? "Running" : "Stopped", tLED.get_state());
  }

}

void showVer(stCommand val) {
  char ver[50];
  formatVersion(ver);
  pc.printf("Version %s %s\r\n", PROJECT_NAME, ver);
}

int main() {
  /* Enable USB interrupt */
  pc.attach(data_recv);

  tImu.start(imu_thread);
  tLED.start(led_thread);
  tFunc.start(commandFuncThread);

  /* Register Commands: */
  regFunc("version", showVer);
  regFunc("led", startLedThread);
  regFunc("go", startIMUsample);
  regFunc("sample", setIMUSampleRate);

  while (true) {
    Thread::wait(osWaitForever);
  }
}
