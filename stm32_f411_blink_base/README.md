🔴 STM32F411 — Proyecto Blink

Encendido y apagado de un LED usando retardos bloqueantes (HAL_Delay).

📌 Descripción

Este proyecto implementa el clásico ejemplo Blink utilizando una placa BlackPill STM32F411CEU6.
El LED conectado al pin configurado en CubeMX se enciende y apaga periódicamente usando retardos simples (HAL_Delay).

Es un ejercicio ideal para:

verificar toolchain

probar programación de la placa

validar configuración de reloj y pines

iniciarse en el flujo HAL + CubeMX

🛠️ Hardware utilizado

STM32F411CEU6 (BlackPill)

1 LED externo (o el LED onboard si la placa lo tiene)

1 resistencia (si se usa LED externo)

⚙️ Configuración en STM32CubeMX
Reloj

HSE → PLL → 100 MHz (típico para BlackPill)

GPIO
Periférico	Pin	Modo	Estado inicial
LED	Ej: PA5	GPIO_Output	LOW
🧩 Funcionamiento

El programa principal ejecuta un ciclo infinito:

HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
HAL_Delay(500); // 500 ms


Esto provoca:

1 Hz de parpadeo (aprox.)

Código completamente bloqueante
→ Ideal para comenzar
→ No recomendado para aplicaciones complejas

📂 Estructura del proyecto
stm32_f411_blink_base/
 ├── Core/
 ├── Drivers/
 ├── .project files...
 └── README.md   ← este archivo

🎯 Objetivos de aprendizaje

✔ Configurar un GPIO de salida
✔ Entender el uso de HAL_Delay
✔ Probar la carga del firmware vía ST-Link
✔ Confirmar que la toolchain está correcta
✔ Primer paso antes de secuencias, timers o interrupciones

🚀 Siguientes pasos recomendados

Después de Blink, puedes avanzar a:

🟡 Blink no bloqueante usando Timers

🟢 Contador binario con 3 LEDs

🔵 Interrupciones por botón

⚙️ PWM básico
