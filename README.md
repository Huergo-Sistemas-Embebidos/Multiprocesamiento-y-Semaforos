# ESP32 FreeRTOS Task and Semaphore Guide

## Creación y manejo de tasks

### Crear una task en un core específico
Mas info sobre cada parámetro: https://docs.espressif.com/projects/esp-idf/en/v4.3/esp32/api-reference/system/freertos.html

```cpp
xTaskCreatePinnedToCore(
taskFunction,   // Referencia a la funcion que vamos a ejecutar
"Task_Core1",   // Nombre para la funcion, sirve solamente para propositos de debugging
4096,           // Tamaño del stack la tarea
NULL,           // Parametro que recibe la funcion que le vamos a pasar
1,              // Prioridad de la tarea
NULL,           // no es importante
1               // El core donde queremos que corra la task (0/1)
);
```

### Firma de una task
```cpp
void taskFunction(void *parameter);
```

### Identificar en que core corre una task
```cpp
int core = xPortGetCoreID(); // core == 0 || core == 1
```

### Delay no bloqueante
```cpp
// la principal diferencia con delay(ms) es que es no bloqueante,
// osea pueden seguir ejecutando otras tareas asignadas al mismo core.
vTaskDelay(pdMS_TO_TICKS(cantidad_de_ms));
```

## Semáforos

### Declaración e inicialización
```cpp
SemaphoreHandle_t mySemaphore; // declaracion de la variable que vamos a usar como semaforo

// En el setup, antes de que cualquier funcion necesite usarlo,
// debemos inicializarlo:
mySemaphore = xSemaphoreCreateMutex(); // En este caso queremos que sea un mutex.
```

### Usando Semáforos
```cpp
// Acquire del semaforo en cuestion
// XSemaphoreTake recibe dos parametros,
// - Primero nuestro semaforo que declaramos arriba
// - Segundo un tiempo maximo de espera para tomarlo y evitar inanicion, se recomienda dejar 'portMAX_DELAY'
// El resultado de la llamada a esta función podemos compararla con pdTRUE para saber si efectivamente tomamos el semaforo.
if (xSemaphoreTake(mySemaphore, portMAX_DELAY) == pdTRUE){
// ...
}

// Liberar el semaforo
xSemaphoreGive(mySemaphore);
```
