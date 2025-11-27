# 🔵 STM32F411 – Secuencia de 3 LEDs

Este proyecto en **STM32CubeIDE** controla tres LEDs conectados al **GPIOA**, encendiéndolos uno por uno con un retardo de 500 ms.  
Es un ejemplo básico para practicar:

- 🟩 Configuración de pines GPIO como salida  
- 🔁 Control secuencial de múltiples LEDs  
- ⏱️ Uso de `HAL_Delay()`  
- ⚙️ Configuración del reloj mediante PLL (HSE a 96 MHz)

---

## 📁 Estructura del proyecto

```txt
Three_LEDs_Sequence/
├── Core/
│   ├── Inc/        # Headers
│   └── Src/        # Código fuente principal (main.c)
├── Drivers/        # HAL de ST
└── README.md       # Documentación (este archivo)
```

---

## 🔌 Pines usados (GPIO)

Los 3 LEDs están configurados como:

| LED | Puerto | Pin |
|-----|--------|-----|
| LED1 | GPIOA | PA0 |
| LED2 | GPIOA | PA1 |
| LED3 | GPIOA | PA2 |

> (Si tus pines son distintos, ajusta el README después)

---

## ▶️ Funcionamiento principal

El `while(1)` enciende cada LED con un retardo de 500 ms:

```c
//Encender LED1
HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
HAL_Delay(500);
HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

//Encender LED2
HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
HAL_Delay(500);
HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);

//Encender LED3
HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
HAL_Delay(500);
HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
```

---

## ⚙️ Configuración del reloj (Clock)

El sistema usa:

- Oscilador externo **HSE**
- PLL activado
- Frecuencia final: **96 MHz**

Esto permite una ejecución estable del delay.

---

## 🛠️ Inicialización del GPIO

```c
GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
```

Los pines se inicializan como:

- **Output Push-Pull**
- **Sin resistencias internas**
- **Baja velocidad**

---

## 🚀 Objetivo del proyecto

Este ejemplo te entrena en:

- Configuración básica de GPIO  
- Uso de HAL en proyectos simples  
- Manejo secuencial de salidas digitales  
- Organización de proyectos STM32CubeIDE  

Es el siguiente paso después del clásico **Blink**.

---

## 💡 Ideas para extender el proyecto

- Cambiar los delays  
- Crear patrones dinámicos (Knight Rider, alternancia, etc.)  
- Controlar LEDs con timers en vez de `HAL_Delay()`  
- Añadir un botón para cambiar la secuencia



