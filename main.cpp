#include "mbed.h"
#include "rtos.h"
#include "USBSerial.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
USBSerial pc;
Thread thread;

void led2_thread(void) {
  while (true) {
    led2 = !led2;
    Thread::wait(1000);
  }
}

int main() {
  thread.start(led2_thread);

  while (true) {
    pc.printf("OPAAA\r\n");
    led1 = !led1;
    Thread::wait(500);
  }
}
