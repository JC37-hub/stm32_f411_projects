/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tm1652.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
// Declaraciones de variables privadas
extern UART_HandleTypeDef TM1652_UART_HANDLE; //Declaracion para la libreria acceda
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  TM1652_Init(); // Llama a la inicialización de nuestro driver TM1652
  TM1652_Clear();  // <-- Y la limpieza del display AQUÍ, solo una vez.
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  // Definimos un estado para las demos
  typedef enum {
      DEMO_SEGMENT_TEST = 0,
      DEMO_BINARY_COUNT,
      DEMO_DECIMAL_COUNT,
      DEMO_HEXADECIMAL_COUNT,
      NUM_DEMOS              // Número total de demos automáticas
  } DemoMode_t;

  DemoMode_t currentDemoMode = DEMO_SEGMENT_TEST; // Empezamos con la prueba de segmentos
  uint16_t demo_counter = 0; // Contador universal para varias demos

  while (1)
  {
	  /* USER CODE END WHILE */

	  /* USER CODE BEGIN 3 */

	  TM1652_Clear();
	  HAL_Delay(1000); // Pequeño retraso entre cada modo de demostración

	  switch (currentDemoMode) {
	      case DEMO_SEGMENT_TEST:
	          // Demo 1: Encendido/apagado de segmentos individuales (por dígito)
	          // Muestra un 0-3 para indicar la posición, luego recorre los segmentos.
	          TM1652_SetBrightness(5); // Brillo intermedio para este demo

	          // Primero, mostramos 0,1,2,3 en sus posiciones
	          TM1652_WriteDecimalDigit(0, 0);
	          TM1652_WriteDecimalDigit(1, 1);
	          TM1652_WriteDecimalDigit(2, 2);
	          TM1652_WriteDecimalDigit(3, 3);
	          HAL_Delay(2000); // Dejarlo visible un tiempo

	          // Luego, recorre cada segmento de cada dígito
	          for (uint8_t pos = 0; pos < 4; pos++) { // Para cada dígito (0-3)
	              for (uint8_t segment_bit = 0; segment_bit < 7; segment_bit++) { // Para cada segmento (a-g, el 8vo bit es DP)
	                  TM1652_Clear(); // Limpiar todo el display
	                  // Encender solo un segmento en la posición actual
	                  TM1652_WriteRawDigit(1 << segment_bit, pos);
	                  HAL_Delay(100);
	              }
	          }
	          break;

	      case DEMO_BINARY_COUNT:
	          // Demo 2: Conteo binario de 0000 a 1111 (en 4 dígitos)
	          TM1652_Clear();
	          TM1652_SetBrightness(8); // Brillo máximo
	          for (demo_counter = 0; demo_counter <= 0xF; demo_counter++) { // 0 a 15 decimal, 0 a F hex
	              // Convertir cada bit a un dígito binario (0 o 1) y mostrarlo
	              TM1652_WriteDecimalDigit((demo_counter >> 3) & 0x01, 0); // Bit 3 (MSB)
	              TM1652_WriteDecimalDigit((demo_counter >> 2) & 0x01, 1); // Bit 2
	              TM1652_WriteDecimalDigit((demo_counter >> 1) & 0x01, 2); // Bit 1
	              TM1652_WriteDecimalDigit(demo_counter & 0x01, 3);       // Bit 0 (LSB)
	              HAL_Delay(300); // Velocidad media
	          }
	          break;

	      case DEMO_DECIMAL_COUNT:
	          // Demo 3: Conteo decimal de 0000 a 0100 (rápido)
	          TM1652_Clear();
	          TM1652_SetBrightness(8); // Brillo máximo
	          for (demo_counter = 0; demo_counter <= 100; demo_counter++) { // Contar hasta 100
	              TM1652_WriteNumber(demo_counter, 1); // Con ceros iniciales
	              HAL_Delay(50); // Rápido
	          }
	          break;

	      case DEMO_HEXADECIMAL_COUNT:
	          // Demo 4: Conteo hexadecimal de 00 a FF (rápido)
	          TM1652_Clear();
	          TM1652_SetBrightness(8); // Brillo máximo
	          for (demo_counter = 0; demo_counter <= 0xFF; demo_counter++) { // Contar hasta FF (255 decimal)
	              TM1652_WriteHexNumber(demo_counter, 1); // Con ceros iniciales
	              HAL_Delay(50); // ¡Muy rápido!
	          }
	          break;

	      default:
	          // Manejo de valores inesperados para currentDemoMode.
	          break;
	  }

	  // Avanzar al siguiente modo de demostración
	  currentDemoMode = (DemoMode_t)((currentDemoMode + 1) % NUM_DEMOS);

	  /* USER CODE END 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 19200;
  huart1.Init.WordLength = UART_WORDLENGTH_9B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_ODD;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
