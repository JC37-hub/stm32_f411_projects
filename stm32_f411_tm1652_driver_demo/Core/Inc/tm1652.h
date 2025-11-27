#ifndef TM1652_H
#define TM1652_H

#include "stm32f4xx_hal.h" // Incluye el archivo HAL principal de tu proyecto
#include <stdint.h>

// --- Definiciones ---
// Handle del UART utilizado para la comunicación con el TM1652.
// ¡DEBES DECLARAR ESTA VARIABLE EXTERNAMENTE EN TU ARCHIVO main.c!
// Ejemplo: extern UART_HandleTypeDef huart1; si usas USART1.
#define TM1652_UART_HANDLE huart1 // <<-- MODIFICA ESTO al handle de tu UART (ej. huart1)

// --- Prototipos de Funciones Públicas ---

/**
  * @brief Inicializa el módulo TM1652.
  *        Envía comandos de limpieza y brillo inicial.
  */
void TM1652_Init(void);

/**
  * @brief Establece el nivel de brillo del display TM1652.
  * @param brightness Nivel de brillo de 0 (más tenue) a 8 (más brillante).
  */
void TM1652_SetBrightness(uint8_t brightness);

/**
  * @brief Muestra un patrón de segmentos directo en una posición específica del display.
  *        Utiliza un buffer interno para gestionar los 4 dígitos.
  * @param segment_pattern El patrón de 8 bits para encender los segmentos (0x00 para apagado total).
  * @param digit_pos La posición del dígito (0 para el más a la izquierda, 3 para el más a la derecha).
  */
void TM1652_WriteRawDigit(uint8_t segment_pattern, uint8_t digit_pos);

/**
  * @brief Muestra un dígito decimal en una posición específica del display.
  *        Utiliza un buffer interno para gestionar los 4 dígitos.
  * @param decimal_value El valor decimal a mostrar (0-9).
  * @param digit_pos La posición del dígito (0 para el más a la izquierda, 3 para el más a la derecha).
  */
void TM1652_WriteDecimalDigit(uint8_t decimal_value, uint8_t digit_pos);

/**
  * @brief Muestra un número decimal (hasta 4 dígitos) en el display.
  *        Gestiona automáticamente la conversión y las posiciones.
  * @param number El número decimal a mostrar (0-9999).
  * @param leading_zeros Si es 1, muestra ceros iniciales (ej. 0007), si es 0, los suprime (ej.   7).
  */
void TM1652_WriteNumber(uint16_t number, uint8_t leading_zeros);

/**
  * @brief Muestra un dígito hexadecimal (0-F) en una posición específica del display.
  *        Utiliza el buffer interno para gestionar los 4 dígitos.
  * @param hex_value El valor hexadecimal a mostrar (0-15).
  * @param digit_pos La posición del dígito (0 para el más a la izquierda, 3 para el más a la derecha).
  */
void TM1652_WriteHexDigit(uint8_t hex_value, uint8_t digit_pos);

/**
  * @brief Muestra un número hexadecimal (hasta 4 dígitos) en el display.
  *        Gestiona automáticamente la conversión y las posiciones.
  * @param number El número hexadecimal a mostrar (0x0000-0xFFFF).
  * @param leading_zeros Si es 1, muestra ceros iniciales (ej. 0007), si es 0, los suprime (ej.   7).
  */
void TM1652_WriteHexNumber(uint16_t number, uint8_t leading_zeros);

/**
  * @brief Limpia todos los dígitos del display TM1652.
  */
void TM1652_Clear(void);

#endif // TM1652_H