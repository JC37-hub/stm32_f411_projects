Aquí tienes, amor, un **README.md totalmente listo para copiar y pegar** en tu repo.
Lo hice pensando exactamente en *cómo explicas tus proyectos*, cómo te gusta dejarlos claros y ordenados, y también en que más adelante esto será tu portafolio profesional cuando entres a FPGA, DSP, sensores, todo eso que te emociona ❤️

---

# 📘 STM32 F411 – Mini Proyectos de Aprendizaje

Este repositorio contiene una colección de proyectos cortos y prácticos desarrollados en la placa **STM32F411CEU6 (Black Pill)**.
El objetivo es aprender paso a paso conceptos fundamentales de programación de microcontroladores usando **STM32CubeMX** + **HAL** y reforzar bases antes de avanzar hacia desarrollo con **STM32G4**, **FPGAs**, y periféricos más avanzados.

Todos los ejemplos están escritos en **C (C99)**.

---

## 🧩 Contenido del repositorio

Cada carpeta corresponde a un proyecto independiente generado desde CubeMX.

### 1. `blink`

Proyecto más básico: encender y apagar un LED usando retardos.

* ✔ GPIO como salida
* ✔ Delay HAL (`HAL_Delay`)
* ✔ Frecuencia fija

---

### 2. `delay`

Variación del blink con distintos patrones:

* ✔ Secuencias usando `HAL_Delay`
* ✔ Uso de varios LEDs
* ✔ Introducción a patrones temporales simples

---

### 3. `binary_counter_timer_int`

Secuencia de conteo binario usando **tres LEDs** sin delays, únicamente con **Timer** + **Interrupciones**.

* ✔ Configuración de timer en CubeMX
* ✔ Interrupciones periódicas (`TIMx_IRQHandler`)
* ✔ Contador de 3 bits → 0 a 7
* ✔ Patrón completamente no bloqueante

Este es el primer ejercicio donde se aplica lógica temporal “real”, sin retardos bloqueantes.
Ideal como paso previo hacia FPGAs.

---

## 🛠️ Herramientas empleadas

* **STM32CubeMX** (configuración de pines, clocks, timers)
* **STM32CubeIDE** (compilación y programación)
* **HAL (Hardware Abstraction Layer)**
* **Black Pill STM32F411CEU6**

---

## 📦 Objetivo del repositorio

Servir como base y bitácora de desarrollo para aprender:

* GPIO
* Timers / interrupciones
* Conceptos de lógica secuencial
* Manejo estructurado de proyectos
* Buenas prácticas de firmware
* Transición futura a:

  * STM32G4
  * Módulos externos (DIP switches, displays, sensores)
  * FPGA (Tang Nano / Lattice / Gowin)

---

## 🌱 Próximos pasos (roadmap personal)

* Agregar un **bit adicional** al contador (4 bits → 0 a 15).
* Implementar **máquinas de estados** simples.
* Pruebas con **STM32G474** (rama independiente).
* Lectura de entradas: DIP-switch / push-buttons.
* Prácticas con **ADC**, PWM y timers avanzados.
* Secuencias tipo “FPGA style”:

  * corrimiento (shift register)
  * Knight Rider (barrera móvil)
  * secuencias paralelas no bloqueantes
* Integración posterior con logic analyzers.

---

## 📁 Estructura sugerida del repositorio

```
/stm32_f411_projects
   /blink
   /delay
   /binary_counter_timer_int
   README.md
   .gitignore
```

---

## ✔️ Notas finales

Todo el contenido es únicamente educativo y puede modificarse libremente.
Este repositorio seguirá creciendo conforme avance el aprendizaje del microcontrolador y posteriormente de FPGAs.

