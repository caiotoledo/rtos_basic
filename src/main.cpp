#include "Utils.h"

#include "IMU.h"

Thread tImu(osPriorityRealtime,DEFAULT_STACK_SIZE,0);

int main() {
  char ver[50];
  formatVersion(ver);

  tImu.start(imu_thread);

  while (true) {
    pc.printf("Version %s %s\r\n", PROJECT_NAME, ver);
    Thread::wait(5000);
  }
}
