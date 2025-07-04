#include <Arduino.h>


void runTaskOnCore1(void (*taskFunction)(void *)) {
  xTaskCreatePinnedToCore(taskFunction, "Task_Core1", 1000, NULL, 1, NULL, 1);
}

void runTaskOnCore0(void (*taskFunction)(void *)) {
  xTaskCreatePinnedToCore(taskFunction, "Task_Core0", 1000, NULL, 1, NULL, 0);
}

int getCore() {
  return xPortGetCoreID();
}

void exampleTask(void *parameter) {
  for (;;) {
    int core = getCore();
    Serial.print("Tarea ejecutándose en Core ");
    Serial.println(core);
    delay(1000);
  }
}


void setup() {
  Serial.begin(115200);

  // Ejecutar tarea en Core 0
  runTaskOnCore0(exampleTask);

  // Ejecutar tarea en Core 1
  runTaskOnCore1(exampleTask);
}

void loop() {

  // Mas info sobre cada parametro:
  // https://docs.espressif.com/projects/esp-idf/en/v4.3/esp32/api-reference/system/freertos.html
  xTaskCreatePinnedToCore(
    taskFunction,   // Referencia a la funcion que vamos a ejecutar
    "Task_Core1",   // Nombre para la funcion, sirve solamente para propositos de debugging
    4096,           // Tamaño del stack la tarea
    NULL,           // Parametro que recibe la funcion que le vamos a pasar
    1,              // Prioridad de la tarea
    NULL,           // no es importante
    1               // El core donde queremos que corra la task (0/1)
  );

  // Firma de una task
  void taskFunction(void *parameter);

  // para saber en que core esta corriendo mi task:
  xPortGetCoreID();

  // Delay para utilizar en task. 
  // la principal diferencia con delay(ms) es que es no bloqueante, 
  // osea pueden seguir ejecutando otras tareas asignadas al mismo core.
  vTaskDelay(pdMS_TO_TICKS(cantidad_de_ms));


  // Semaforos:
  SemaphoreHandle_t mySemaphore; // declaracion de la varaible que vamos a usar como semaforo

  // En el setup, antes de que cualquier funcion necesite usarlo,
  // debemos inicializarlo:
  mySemaphore = xSemaphoreCreateMutex(); // En este caso queremos que sea un mutex.


  // Acquire del semaforo en cuestion
  // XSemaphoreTake recibe dos parametros, 
  //   - Primero nuestro semaforo que declaramos arriba
  //   - Segundo un tiempo maximo de espera para tomarlo y evitar inanicion, se recomienda dejar 'portMAX_DELAY'
  // El resultado de la llamada a esta función podemos compararla con pdTRUE para saber si efectivamente tomamos el semaforo.
  if (xSemaphoreTake(mySemaphore, portMAX_DELAY) == pdTRUE){
    // ...
  }

  // Liberar el semaforo
  xSemaphoreGive(mySemaphore);

}

