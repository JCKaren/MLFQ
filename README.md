# MLFQ Scheduler Simulator

Karen Michelle Jimenez Castro
CC: 1094244076

# Diseño y decisiones

## Decisiones de diseño

El proyecto fue organizado separando las responsabilidades del sistema en diferentes clases y capas. La intención principal fue evitar concentrar toda la lógica del simulador en una sola clase y facilitar el mantenimiento y la posibilidad de extender el proyecto.

Las principales decisiones fueron:

* `Process` representa el estado y comportamiento de cada proceso.
* `ReadyQueue` administra los procesos de cada cola y su quantum.
* `MlfqPolicy` contiene las reglas específicas del algoritmo MLFQ.
* `SimulationEngine` controla el reloj discreto y coordina la ejecución de los procesos.
* `MetricsCalculator` se encarga del cálculo de las métricas.
* Los exportadores CSV se encuentran en `infrastructure`, separando la generación de archivos de la lógica del simulador.
* `RunSimulation` coordina la ejecución de la aplicación y la generación de resultados.

Además, la configuración de los quantums y del intervalo de *priority boost* se centraliza en `SimulationConfig`, evitando tener estos valores distribuidos dentro de la lógica del programa.

---

## Principios de diseño aplicados

### Single Responsibility Principle (SRP)

Se aplicó el principio de responsabilidad única distribuyendo las responsabilidades entre diferentes clases.

Por ejemplo:

* `Process`: administra el estado de un proceso.
* `ReadyQueue`: administra una cola de procesos.
* `MlfqPolicy`: implementa las reglas de planificación MLFQ.
* `SimulationEngine`: ejecuta la simulación ciclo por ciclo.
* `MetricsCalculator`: calcula las métricas.
* `CsvResultsWriter`: exporta los resultados individuales.
* `CsvAggregateWriter`: exporta las métricas agregadas.

Esto permite que un cambio en una responsabilidad específica no obligue a modificar todo el sistema.

### Open/Closed Principle (OCP)

Se aplicó principalmente en la planificación mediante la interfaz `ISchedulingPolicy`.

`SimulationEngine` trabaja con la abstracción `ISchedulingPolicy` en lugar de depender directamente de `MlfqPolicy`.

Por lo tanto, sería posible agregar otra política de planificación, como `FcfsPolicy` o `RoundRobinPolicy`, implementando la misma interfaz sin modificar la lógica principal del motor de simulación.

### Dependency Inversion Principle (DIP)

El `SimulationEngine` recibe una referencia a `ISchedulingPolicy`, por lo que depende de una abstracción y no directamente de `MlfqPolicy`.

También se utilizaron las interfaces:

```cpp
IResultsExporter
IAggregateExporter
```

para desacoplar la lógica de aplicación de las implementaciones concretas encargadas de escribir archivos CSV.

### Encapsulamiento

Los atributos internos de `Process` son privados y su modificación se realiza mediante métodos controlados como:

```cpp
consumeTick()
changeQueue()
resetQuantum()
firstExecution()
finishProcess()
```

De esta manera, el estado del proceso no puede ser modificado directamente por cualquier componente.

---

## Patrón de diseño aplicado

### Strategy

El patrón **Strategy** se utiliza para representar la política de planificación.

La interfaz:

```cpp
ISchedulingPolicy
```

define las operaciones que necesita el motor de simulación, mientras que:

```cpp
MlfqPolicy
```

implementa específicamente el algoritmo MLFQ.

La relación es:

```text
SimulationEngine
       │
       ▼
ISchedulingPolicy
       ▲
       │
  MlfqPolicy
```

Esto permite cambiar la estrategia de planificación sin modificar el funcionamiento general de `SimulationEngine`.

No se agregaron otros patrones como Factory, Observer o State porque no eran necesarios para resolver el problema y agregarlos únicamente para cumplir una lista de patrones podría aumentar innecesariamente la complejidad del proyecto.

---

# Arquitectura

El proyecto utiliza una separación por capas inspirada en **Clean Architecture**, manteniendo la lógica principal del simulador independiente de los detalles de infraestructura.

La estructura es:

```text
┌──────────────────────────────────────────┐
│              Infrastructure              │
│                                          │
│  CsvResultsWriter                        │
│  CsvAggregateWriter                      │
│                                          │
│  Responsabilidad: archivos CSV           │
└─────────────────────┬────────────────────┘
                      │
                      ▼
┌──────────────────────────────────────────┐
│               Application                │
│                                          │
│  RunSimulation                            │
│                                          │
│  Responsabilidad: coordinación           │
└─────────────────────┬────────────────────┘
                      │
                      ▼
┌──────────────────────────────────────────┐
│                  Domain                 │
│                                          │
│  Process                                 │
│  ReadyQueue                              │
│  MlfqPolicy                              │
│  SimulationEngine                        │
│  MetricsCalculator                       │
│  ISchedulingPolicy                       │
│  ProcessMetrics                           │
│  SimulationConfig                         │
│                                          │
│  Responsabilidad: lógica del simulador   │
└──────────────────────────────────────────┘
```

La lógica del algoritmo MLFQ pertenece al **Domain**, mientras que la escritura de archivos CSV pertenece a **Infrastructure**. De esta manera, el funcionamiento del simulador no depende directamente de cómo se almacenan los resultados.

Esta separación facilita realizar cambios o reemplazar componentes sin afectar innecesariamente las demás partes del sistema.


# Estructura del proyecto

```text
MLFQ/
│
├── src/
│   ├── Main.cpp
│   │
│   ├── application/
│   │   ├── RunSimulation.cpp
│   │   └── RunSimulation.hpp
│   │
│   ├── domain/
│   │   ├── metrics/
│   │   │   ├── AggregateMetrics.hpp
│   │   │   ├── MetricsCalculator.cpp
│   │   │   └── MetricsCalculator.hpp
│   │   │
│   │   ├── process/
│   │   │   ├── Process.cpp
│   │   │   ├── Process.hpp
│   │   │   └── ProcessMetrics.hpp
│   │   │
│   │   ├── scheduling/
│   │   │   ├── ISchedulingPolicy.hpp
│   │   │   ├── MlfqPolicy.cpp
│   │   │   ├── MlfqPolicy.hpp
│   │   │   ├── ReadyQueue.cpp
│   │   │   ├── ReadyQueue.hpp
│   │   │   └── SimulationConfig.hpp
│   │   │
│   │   └── simulation/
│   │       ├── SimulationEngine.cpp
│   │       └── SimulationEngine.hpp
│   │
│   └── infrastructure/
│       ├── CsvAggregateWriter.cpp
│       ├── CsvAggregateWriter.hpp
│       ├── CsvResultsWriter.cpp
│       └── CsvResultsWriter.hpp
│
├── test/
│   └── unit/
│       ├── MetricsTest.cpp
│       ├── MlfqTest.cpp
│       ├── ProcessTest.cpp
│       ├── SimulationEngineTest.cpp
│       ├── TestHelper.hpp
│       └── TestMain.cpp
│
├── results.csv
├── aggregate.csv
├── build.ps1
└── README.md
```
# Ejecución

El proyecto incluye un script `build.ps1` para compilar la aplicación y las pruebas.

Se requiere:

* C++17
* `g++`
* PowerShell

Desde PowerShell:

```powershell
.\build.ps1              # compila y corre todo
.\build.ps1 -TestsOnly   # solo pruebas
.\build.ps1 -AppOnly     # solo la app
```

# Archivos generados

### `results.csv`

Contiene las métricas individuales de cada proceso:

```csv
PID,Arrival,Burst,Start,Finish,Response,Turnaround,Waiting
```

### `aggregate.csv`

Contiene las métricas promedio:

```csv
AverageResponseTime,AverageTurnaroundTime,AverageWaitingTime,TotalProcesses
```

---


