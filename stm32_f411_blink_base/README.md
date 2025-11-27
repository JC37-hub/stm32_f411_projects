# 🔴 STM32F411 — Proyecto Blink
Encendido y apagado de un LED usando retardos bloqueantes (HAL_Delay).

## 📌 Descripción
Este proyecto implementa el ejemplo clásico Blink usando una placa BlackPill STM32F411CEU6.
El LED conectado al pin configurado en CubeMX se enciende y apaga periódicamente mediante HAL_Delay.

Ideal para:
- Verificar toolchain y carga del firmware
- Validar reloj, GPIO y configuración inicial
- Introducirse al flujo CubeMX + HAL

## 🛠️ Hardware utilizado
- STM32F411CEU6 (BlackPill)
- 1 LED externo (o LED onboard si tu placa lo incluye)
- 1 resistencia si usas LED externo

## ⚙️ Configuración en STM32CubeMX

### Reloj
HSE → PLL → 100 MHz (frecuencia típica de la BlackPill)

### GPIO
| Periférico | Pin (ejemplo) | Modo        | Estado inicial |
|------------|---------------|-------------|----------------|
| LED        | PA5           | GPIO_Output | LOW            |

## 🧩 Funcionamiento
En el bucle principal se alterna el estado del LED usando un retardo bloqueante.  
Ejemplo de la lógica principal:

    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    HAL_Delay(500);   // Parpadeo de ~1 Hz

Efecto:
- Parpadeo constante
- Código simple pero bloqueante (no adecuado para multitarea real)

## 📂 Estructura del proyecto
```txt
stm32_f411_blink_base/
 ├── Core/
 ├── Drivers/
 ├── (archivos generados por CubeMX)
 └── README.md
```

## 🎯 Objetivos de aprendizaje
- Configurar un GPIO como salida
- Usar HAL_Delay correctamente
- Comprobar funcionamiento básico del microcontrolador
- Primer paso antes de timers, interrupciones o PWM

## 🚀 Siguientes pasos recomendados
- Blink no bloqueante usando un Timer
- Secuencia de 3 LEDs
- Interrupciones por botón
- PWM básico
