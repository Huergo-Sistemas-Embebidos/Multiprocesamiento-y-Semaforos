#include <Arduino.h>


volatile TaskHandle_t taskHandle0 = NULL;  // Añadido volatile
volatile TaskHandle_t taskHandle1 = NULL;  // Añadido volatile

void runTaskOnCore1(void (*taskFunction)(void*)) {
  xTaskCreatePinnedToCore(taskFunction, "Task_Core1", 1000, NULL, 1, (TaskHandle_t*)&taskHandle1, 1);
}

void runTaskOnCore0(void (*taskFunction)(void*)) {
  xTaskCreatePinnedToCore(taskFunction, "Task_Core0", 1000, NULL, 1, (TaskHandle_t*)&taskHandle0, 0);
}

int getCore() {
  return xPortGetCoreID();
}

void exampleTaskFoo(void* parameter) {
  for (;;) {
    Serial.print("Task 1: Foo");
    delay(10);
    Serial.println(" - Task 1: Bar");
    delay(10);
  }
}

void exampleTaskBar(void* parameter) {
  for (;;) {
    Serial.print("Task 2: Foo");
    delay(10);
    Serial.println(" - Task 2: Bar");
    delay(10);
  }
}

void setup() {
  Serial.begin(115200);
  runTaskOnCore0(exampleTaskFoo);
  runTaskOnCore1(exampleTaskBar);
}

void loop() {
}
