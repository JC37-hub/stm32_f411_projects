# 🔢 STM32F411 – Contador Binario con Timer (3 LEDs)

Este proyecto implementa un **contador binario de 3 bits (0–7)** usando el **Timer 3 (TIM3)** del STM32F411.  
Cada bit del valor del contador se muestra en un LED:

- LED1 → bit 2  
- LED2 → bit 1  
- LED3 → bit 0  

La actualización del contador se realiza mediante **interrupciones del Timer**, no usando `HAL_Delay()`.  
Este proyecto es ideal para aprender:

- ⚙️ Configuración de timers en modo base  
- ⏱️ Interrupciones periódicas  
- 💡 Lectura de bits usando operadores shift (`>>`) y AND (`&`)  
- 🔌 Control de GPIO sin bloqueo

---

## 📁 Estructura del proyecto

```txt
stm32_f411_binary_counter_timer/
├── Core/
│   ├── Inc/
│   └── Src/        # Contiene main.c
├── Drivers/
└── README.md
```

---

## 🔌 Pines usados (GPIO)

| LED | Puerto | Pin | Bit del contador |
|-----|--------|-----|------------------|
| LED1 | GPIOA | PA0 | bit 2 |
| LED2 | GPIOA | PA1 | bit 1 |
| LED3 | GPIOA | PA2 | bit 0 |

---

## 🧠 Lógica del contador binario

El contador incrementa de 0 a 7 y luego vuelve a 0:

```c
binary_counter++;

if (binary_counter > 7)
{
    binary_counter = 0;
}
```

Luego cada LED se enciende según el bit correspondiente:

```c
if ((binary_counter >> 2) & 0x01) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
else HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

if ((binary_counter >> 1) & 0x01) HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
else HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);

if ((binary_counter >> 0) & 0x01) HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
else HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
```

---

## ⚙️ Configuración del Timer 3 (TIM3)

El timer genera una interrupción periódica según:

- **Prescaler = 9999**  
- **Periodo = 2499**  
- **Clock interno = 96 MHz**

Esto produce una interrupción aproximada de:

```
Frecuencia = 96MHz / (9999 + 1) / (2499 + 1)
≈ 4 Hz
```

Es decir, el contador cambia unas **4 veces por segundo**.

Inicialización del Timer:

```c
htim3.Instance = TIM3;
htim3.Init.Prescaler = 9999;
htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
htim3.Init.Period = 2499;
htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
HAL_TIM_Base_Init(&htim3);
```

Habilitación de interrupciones:

```c
HAL_TIM_Base_Start_IT(&htim3);
```

---

## 🔁 Callback de interrupción

Toda la magia ocurre aquí:

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        binary_counter++;
        if (binary_counter > 7) binary_counter = 0;

        // Actualizar bits hacia LEDs
        // bit 2
        if ((binary_counter >> 2) & 0x01)
            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

        // bit 1
        if ((binary_counter >> 1) & 0x01)
            HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);

        // bit 0
        if ((binary_counter >> 0) & 0x01)
            HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
    }
}
```

---

## 🚀 Objetivo del proyecto

Este ejemplo te entrena en:

- Uso del **Timer en interrupciones**
- Control de GPIO sin bloquear el flujo
- 🔍 Trabajo con **representación binaria**
- Desarrollo modular y eficiente en STM32

Es un paso importante para proyectos más avanzados como displays, multiplexado, PWM dinámico, etc.

---

## 💡 Ideas de mejora

- Cambiar la velocidad del contador
- Mostrar el número en un display de 7 segmentos
- Extenderlo a 4, 8 o 16 bits
- Sincronizarlo con un botón de incremento manual



