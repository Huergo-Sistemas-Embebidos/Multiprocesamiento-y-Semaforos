#include <Arduino.h>

volatile TaskHandle_t taskHandle0 = NULL;
volatile TaskHandle_t taskHandle1 = NULL;

void runTaskOnCore1(void (*taskFunction)(void *)) {
  xTaskCreatePinnedToCore(taskFunction, "Task_Core1", 1000, NULL, 1, (TaskHandle_t *)&taskHandle1, 1);
}

void runTaskOnCore0(void (*taskFunction)(void *)) {
  xTaskCreatePinnedToCore(taskFunction, "Task_Core0", 1000, NULL, 1, (TaskHandle_t *)&taskHandle0, 0);
}

int getCore() {
  return xPortGetCoreID();
}

volatile int contador = 0;

void exampleTask(void *parameter) {
  for (int i = 0; i < 1e6; i++) {
    contador++;
  }

  while (true) {
    delay(1000);
  }
}

void setup() {
  Serial.begin(115200);
  runTaskOnCore0(exampleTask);
  runTaskOnCore1(exampleTask);
}

void loop() {
  delay(2000);
  Serial.printf("---------------------------------- CONTADOR: %d ----------------------------------\n", contador);
}
