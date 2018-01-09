#include "Utils.h"

#include "IMU.h"

Thread tImu;

int main() {
  char ver[50];
  formatVersion(ver);

  tImu.start(imu_thread);

  while (true) {
    pc.printf("Version %s %s\r\n", PROJECT_NAME, ver);
    Thread::wait(5000);
  }
}
