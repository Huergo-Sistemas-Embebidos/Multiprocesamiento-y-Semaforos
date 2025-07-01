# Enunciado: Simulación de aterrizajes en un aeropuerto con ESP32 y FreeRTOS
## Contexto:
Se te encarga de simular el sistema de control de aterrizajes de un aeropuerto en un microcontrolador ESP32. El aeropuerto cuenta con varias pistas de aterrizaje (por ejemplo, 3 pistas), y una torre de control que autoriza los aterrizajes. Cada pista solo puede ser utilizada por un avión a la vez, y la torre de control es la encargada de dar el visto bueno para que los aviones aterricen.
## Requisitos:
### Tareas de aviones (Core 0):
- Crea varias tareas (por ejemplo, 5 aviones), todas ejecutándose en el Core 0 del ESP32.
- Cada avión representa una tarea que intenta aterrizar en una de las pistas disponibles.
- Cada pista de aterrizaje está protegida por un mutex propio (uno por pista).
- Cada avión:
  1. Espera un tiempo aleatorio (simulando el tiempo de aproximación).
  2. Solicita permiso a la torre de control para aterrizar.
  3. Cuando recibe el permiso, intenta adquirir el mutex de una pista libre.
  4. Una vez adquirida la pista, simula el aterrizaje (espera un tiempo aleatorio).
  5. Libera la pista (libera el mutex).
  6. Vuelve a empezar el proceso.
### Torre de control (Core 1):
- Implementa una tarea que corre en el Core 1 del ESP32.
- La torre de control es la encargada de autorizar los aterrizajes.
- Lleva un registro de qué aviones están esperando y otorga permisos de aterrizaje de forma ordenada (por ejemplo, por orden de llegada).
- Puede usar colas (FreeRTOS queues) para gestionar las solicitudes de aterrizaje.
- La torre de control notifica a los aviones cuando pueden proceder a aterrizar.
- Sincronización y comunicación:
  1. Usa mutex para proteger cada pista de aterrizaje.
  2. Usa colas o semaforos para la comunicación entre los aviones y la torre de control.
Asegurarse de que nunca haya dos aviones aterrizando en la misma pista al mismo tiempo.
### Mensajes por puerto serie (UART):
- Muestra mensajes indicando:
  1. Cuando un avión solicita aterrizar.
  2. Cuando la torre de control autoriza el aterrizaje.
  3. Cuando un avión toma una pista y comienza a aterrizar.
  4. Cuando un avión libera la pista.
### Tiempos aleatorios:
- Los tiempos de aproximación y aterrizaje deben ser aleatorios para simular la variabilidad real.
