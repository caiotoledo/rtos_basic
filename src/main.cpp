#include "Utils.h"

#include "IMU.h"

#define BLINK_TIME    500

DigitalOut led1(LED1);

Thread tLED;
Thread tImu(osPriorityRealtime,DEFAULT_STACK_SIZE,0);

void led_thread(void){
  while(true){
    led1 = !led1;
    Thread::wait(BLINK_TIME);
  }
}

int main() {
  char ver[50];
  formatVersion(ver);

  tImu.start(imu_thread);
  tLED.start(led_thread);

  while (true) {
    pc.printf("Version %s %s\r\n", PROJECT_NAME, ver);
    Thread::wait(5000);
  }
}
