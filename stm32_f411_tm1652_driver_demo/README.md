# 👓 STM32F411 TM1652 Driver Demo

![TM1652 Display](https://img.shields.io/badge/TM1652-Driver-blueviolet)
![STM32F411](https://img.shields.io/badge/STM32F411-Microcontroller-green)
![UART Communication](https://img.shields.io/badge/UART-19200bps-yellowgreen)

## ✨ Visión General del Proyecto

¡Bienvenido al proyecto **STM32F411 TM1652 Driver Demo**! Este repositorio alberga un driver completo y modular, desarrollado desde cero, para controlar el display LED de 4 dígitos y 7 segmentos TM1652 mediante comunicación UART con un microcontrolador STM32F411.

Este proyecto es una demostración práctica de cómo interactuar con periféricos seriales de bajo nivel, configurando el UART del STM32 para un protocolo no estándar (8 bits de datos, Paridad IMPAR, 1 bit de parada) y gestionando la visualización de información de forma eficiente. Es un testimonio de que la paciencia, la depuración metódica y el trabajo llevan al éxito.

## 🚀 Características del Driver

*   **Comunicación UART Robusta:** Configuración precisa a 19200 bps, 8 bits de datos, Paridad IMPAR, 1 bit de parada.
*   **Control de Brillo:** Ajuste programable de la intensidad del display.
*   **Buffer de Dígitos Interno:** Gestión inteligente del display para actualizar dígitos individualmente sin afectar a los demás.
*   **Escritura Flexible:** Funciones para escribir patrones de segmentos crudos, dígitos decimales y dígitos hexadecimales.
*   **Display Multi-dígito:** Funciones para mostrar números decimales y hexadecimales de hasta 4 dígitos, con opción de supresión o visualización de ceros iniciales.
*   **Modular y Reutilizable:** Implementado en archivos `tm1652.h` y `tm1652.c` para fácil integración en otros proyectos.

## 🛠️ Configuración del Hardware y Conexión

*   **Microcontrolador:** STM32F411RETx (u otro STM32F411 compatible).
*   **Módulo Display:** TM1652 (con pines SDA, G, VCC).

### Conexión:

*   **TM1652 VCC** ➡️ **5V** (desde STM32 o fuente externa)
*   **TM1652 G (GND)** ➡️ **GND**
*   **TM1652 SDA** ➡️ **Pin PA9 (USART1_TX)** del STM32F411 (o el pin TX del periférico UART configurado).

### Configuración en STM32CubeMX:

1.  **UART (Ej. USART1):**
    *   **Mode:** Asynchronous
    *   **Baud Rate:** `19200`
    *   **Word Length:** `9 Bits (including parity)`
    *   **Parity:** `Odd` (¡Crucial!)
    *   **Stop Bits:** `1 Stop Bit`
    *   **NVIC:** Habilitar interrupción global del USART.
    *   **Advanced Parameters:** Data Direction: `RECEIVE AND TRANSMIT`, Over Sampling: `16 SAMPLES`
2.  **GPIO (para demos futuras):** 4 pines configurados como `GPIO_Input` con `Pull-down` (o `No pull-up and no pull-down` según se necesite), con User Labels (ej. `INPUT_BIT0_Pin` a `INPUT_BIT3_Pin`). Para la demo actual, no se usan.

## ⚙️ Estructura del Proyecto

El proyecto se organiza de la siguiente manera:

*   `Core/Inc/`: Archivos de cabecera de STM32CubeIDE.
    *   `tm1652.h`: Interfaz del driver TM1652.
*   `Core/Src/`: Archivos fuente de STM32CubeIDE.
    *   `main.c`: Lógica principal del programa y demos.
    *   `tm1652.c`: Implementación del driver TM1652.

## 📝 Uso del Driver y Demos

El archivo `main.c` contiene un bucle principal (`while(1)`) que ejecuta una secuencia de demostraciones para ilustrar las capacidades del driver:

1.  **`DEMO_SEGMENT_TEST`**: Muestra "0123" y luego enciende individualmente cada segmento de cada dígito, verificando la funcionalidad a nivel de hardware.
2.  **`DEMO_BINARY_COUNT`**: Conteo binario de 0000 a 1111 (0 a F en hexadecimal) a través de los cuatro dígitos.
3.  **`DEMO_DECIMAL_COUNT`**: Conteo decimal de 0000 a 0100, mostrando ceros iniciales.
4.  **`DEMO_HEXADECIMAL_COUNT`**: Conteo hexadecimal de 0000 a 00FF (0 a FF en hexadecimal), mostrando ceros iniciales.

Cada demo está diseñada para ser rápida y visualmente atractiva.

## 🌟 Reconocimientos

## 👓 


