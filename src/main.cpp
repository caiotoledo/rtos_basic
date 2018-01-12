#include "Utils.h"

#include "IMU.h"

#define BLINK_TIME    500

DigitalOut led1(LED1);
Serial serial(SERIAL_TX, SERIAL_RX, 9600);

Thread tLED;
Thread tImu(osPriorityRealtime,DEFAULT_STACK_SIZE,0);

void data_recv(void){
  char *buf = (char *) malloc( sizeof(char) * (pc.available() + 1) );
  pc.gets(buf, pc.available()+1);
  serial.printf("%s", buf);
  free(buf);
}

void led_thread(void){
  while(true){
    led1 = !led1;
    Thread::wait(BLINK_TIME);
  }
}

int main() {
  char ver[50];
  formatVersion(ver);

  pc.attach(data_recv);

  tImu.start(imu_thread);
  tLED.start(led_thread);

  while (true) {
    pc.printf("Version %s %s\r\n", PROJECT_NAME, ver);
    Thread::wait(20000);
  }
}
