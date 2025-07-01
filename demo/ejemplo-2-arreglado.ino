#include <Arduino.h>

volatile TaskHandle_t taskHandle0 = NULL;
volatile TaskHandle_t taskHandle1 = NULL;

void runTaskOnCore1(void (*taskFunction)(void *)) {
  xTaskCreatePinnedToCore(taskFunction, "Task_Core1", 4096, NULL, 1, (TaskHandle_t *)&taskHandle1, 1);
}

void runTaskOnCore0(void (*taskFunction)(void *)) {
  xTaskCreatePinnedToCore(taskFunction, "Task_Core0", 4096, NULL, 1, (TaskHandle_t *)&taskHandle0, 0);
}

int getCore() {
  return xPortGetCoreID();
}

SemaphoreHandle_t counterSemaphore;
volatile int contador = 0;
int duration[2] = { 0, 0 };

void exampleTask(void *parameter) {
  for (int i = 0; i < 1e6; i++) {
    if (xSemaphoreTake(counterSemaphore, portMAX_DELAY) == pdTRUE) {
      contador++;
    }
    xSemaphoreGive(counterSemaphore);
  }

  duration[getCore()] = millis();
  while (1) { delay(1000); }
}



void setup() {
  Serial.begin(115200);
  counterSemaphore = xSemaphoreCreateMutex();

  runTaskOnCore0(exampleTask);
  runTaskOnCore1(exampleTask);
}

void loop() {
  if (contador < 2e6) {
    Serial.printf("---------------------------------- CONTADOR: %d ----------------------------------\n", contador);
  }
  if (contador == 2e6) {
    Serial.printf("---------------------------------- DURACION: %d %d ----------------------------------\n", duration[0], duration[1]);
  }
}
