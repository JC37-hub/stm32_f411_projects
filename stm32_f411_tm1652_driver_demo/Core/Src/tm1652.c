#include "tm1652.h"
#include <string.h> // Para funciones como memset

// --- Variables Externas ---
// ¡Importante! Asegúrate de que tu handle de UART esté declarado en main.c y sea accesible.
// Por ejemplo, si CubeMX generó "huart1", deberías tener "extern UART_HandleTypeDef huart1;" en main.c
extern UART_HandleTypeDef TM1652_UART_HANDLE;

// --- Patrones de Segmentos para Dígitos Decimales (0-9) y Hexadecimales (A-F) ---
// (A-F son patrones estándar de 7 segmentos para letras mayúsculas)
const uint8_t tm1652_digit_patterns[] = {
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
    0x77, /* A */ // Hex A
    0x7C, /* B */ // Hex B
    0x39, /* C */ // Hex C
    0x5E, /* D */ // Hex D
    0x79, /* E */ // Hex E
    0x71  /* F */ // Hex F
};

// --- Buffer Interno para el Estado del Display ---
// Este buffer guarda el patrón de segmentos actual para cada uno de los 4 dígitos.
// Lo usamos para poder actualizar un solo dígito sin afectar a los demás,
// ya que el comando 0x08 espera los 4 bytes de datos de los dígitos.
static uint8_t tm1652_digit_buffer[4] = {0x00, 0x00, 0x00, 0x00}; // Inicialmente apagados

// --- Funciones Auxiliares Estáticas ---

/**
  * @brief Invierte los 4 bits menos significativos de un byte.
  *        Necesario para el cálculo del brillo según la hoja de datos.
  * @param n El byte de entrada.
  * @return El byte con los 4 bits menos significativos invertidos.
  */
static uint8_t TM1652_Reverse4Bits(uint8_t n) {
    uint8_t reversed_n = 0;
    // La implementación de la hoja de datos y los ejemplos sugieren un mapeo específico
    // no una simple inversión de bits. Basado en el ejemplo de Python:
    // bits = "{:0>4b}".format(n)
    // return int(bits[::-1], 2)
    // Para C, podemos hacerlo con shift y ORs manuales para los 4 bits
    if ((n >> 0) & 0x01) reversed_n |= (1 << 3); // Bit 0 -> Bit 3
    if ((n >> 1) & 0x01) reversed_n |= (1 << 2); // Bit 1 -> Bit 2
    if ((n >> 2) & 0x01) reversed_n |= (1 << 1); // Bit 2 -> Bit 1
    if ((n >> 3) & 0x01) reversed_n |= (1 << 0); // Bit 3 -> Bit 0
    return reversed_n;
}

/**
  * @brief Envía un comando o secuencia de datos al TM1652 a través de UART.
  * @param data Puntero al array de bytes a enviar.
  * @param len Longitud del array de bytes.
  */
static void TM1652_SendCommand(uint8_t* data, uint8_t len) {
    // Usamos el HAL_UART_Transmit en modo bloqueo.
    // El timeout de 100ms es un valor seguro, se puede ajustar.
    HAL_UART_Transmit(&TM1652_UART_HANDLE, data, len, 100);
    // Una pequeña demora después de cada comando puede ser útil para algunos módulos
    // Aunque el UART es asíncrono, el chip TM1652 puede necesitar tiempo para procesar.
    HAL_Delay(6); // Ajustado a 6ms por observación del ejemplo Python
}

// Función auxiliar para actualizar el display con el contenido del buffer interno
static void TM1652_UpdateDisplay(void) {
    uint8_t send_cmd[5];
    send_cmd[0] = 0x08; // Comando para escribir datos en el display
    memcpy(&send_cmd[1], tm1652_digit_buffer, 4); // Copiar los 4 patrones de dígitos
    TM1652_SendCommand(send_cmd, 5);
}

// --- Implementación de Funciones Públicas ---

void TM1652_Init(void) {
    TM1652_Clear();
    HAL_Delay(20);
    TM1652_SetBrightness(8); // Brillo por defecto (máximo)
    HAL_Delay(20);
}

void TM1652_SetBrightness(uint8_t brightness) {
    if (brightness > 8) { // Asegurar que el brillo esté en el rango válido (0-8)
        brightness = 8;
    }
    // Comando 0x18 para control de display.
    // El segundo byte define el brillo.
    // Basado en ejemplos: 0x10 | (reversed_brightness_value & 0x0F)
    // donde el valor de brillo se mapea de 1-8 a 0-7, y 0 se manejará.
    uint8_t send_cmd[2];
    send_cmd[0] = 0x18;
    // (brightness - 1) se convierte en 0-7, luego se invierten los bits y se enmascara.
    // Si brightness es 0, (0-1) es -1, lo cual es problematico con uint8_t.
    // Manejar brillo 0 (display apagado) de forma explícita si es necesario,
    // o asumir que 1 es el mínimo brillo. Los ejemplos usan brightness-1, así que lo seguimos.
    // El datasheet en pág 6, "Grid drive duty ratio setting", muestra que 0x10 es duty 8/16.
    // Así que 0x10 + (valor de 0 a 7 para el brillo).
    send_cmd[1] = 0x10 | (TM1652_Reverse4Bits(brightness - 1) & 0x0F);
    TM1652_SendCommand(send_cmd, 2);
}


void TM1652_WriteRawDigit(uint8_t segment_pattern, uint8_t digit_pos) {
    if (digit_pos > 3) { // Asegurar que la posición del dígito sea válida (0-3)
        return;
    }
    tm1652_digit_buffer[digit_pos] = segment_pattern; // Actualizar el buffer
    TM1652_UpdateDisplay(); // Enviar el contenido del buffer al display
}


void TM1652_WriteDecimalDigit(uint8_t decimal_value, uint8_t digit_pos) {
    if (decimal_value > 9) { // Asegurar que el valor sea un dígito decimal (0-9)
        decimal_value = 0x00; // Si no es válido, mostrar en blanco o error.
    }
    TM1652_WriteRawDigit(tm1652_digit_patterns[decimal_value], digit_pos);
}


void TM1652_WriteNumber(uint16_t number, uint8_t leading_zeros) {
    if (number > 9999) number = 9999; // Limitar a 4 dígitos

    uint16_t divisor = 1000;
    for (int i = 0; i < 4; i++) {
        uint8_t digit = (number / divisor) % 10;
        if (!leading_zeros && number < divisor && divisor != 1) { // Suprimir ceros iniciales
            tm1652_digit_buffer[i] = 0x00; // Espacio en blanco
        } else {
            tm1652_digit_buffer[i] = tm1652_digit_patterns[digit];
        }
        divisor /= 10;
    }
    TM1652_UpdateDisplay();
}


void TM1652_WriteHexDigit(uint8_t hex_value, uint8_t digit_pos) {
    if (hex_value > 0xF) { // Asegurar que el valor sea hexadecimal (0-15)
        hex_value = 0x00; // Si no es válido, mostrar en blanco
    }
    TM1652_WriteRawDigit(tm1652_digit_patterns[hex_value], digit_pos);
}


void TM1652_WriteHexNumber(uint16_t number, uint8_t leading_zeros) {
    if (number > 0xFFFF) number = 0xFFFF; // Limitar a 4 dígitos hex

    uint16_t divisor = 0x1000; // 4096 decimal
    for (int i = 0; i < 4; i++) {
        uint8_t digit = (number / divisor) & 0xF; // Extraer el dígito hex
        
        if (!leading_zeros && number < divisor && divisor != 1) { // Suprimir ceros iniciales
            tm1652_digit_buffer[i] = 0x00; // Espacio en blanco
        } else {
            tm1652_digit_buffer[i] = tm1652_digit_patterns[digit];
        }
        divisor /= 0x10; // Dividir por 16
    }
    TM1652_UpdateDisplay();
}


void TM1652_Clear(void) {
    // Limpiar el buffer interno
    memset(tm1652_digit_buffer, 0x00, 4);
    // Enviar el comando de limpieza (0x08 seguido de 4 ceros)
    TM1652_UpdateDisplay();
}
