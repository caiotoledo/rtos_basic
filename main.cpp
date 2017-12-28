#include "Utils.h"

#include "IMU.h"

DigitalOut led1(LED1);
Thread tLed, tImu;

void led1_thread(void) {
  while (true) {
    led1 = !led1;
    Thread::wait(500);
  }
}

int main() {
  Thread::wait(3000);
  char ver[50];
  formatVersion(ver);
  pc.printf("Version %s %s\r\n", PROJECT_NAME, ver);
  Thread::wait(1500);

//  tLed.start(led1_thread);
  tImu.start(imu_thread);

  while (true) {
    pc.printf("Teste\r\n");
    Thread::wait(1500);
  }
}
