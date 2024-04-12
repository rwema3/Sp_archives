/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include <stdlib.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "liquidcrystal_i2c.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define INPUT_BUFFER_SIZE 4
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

char input_buffer[INPUT_BUFFER_SIZE];
int buffer_index = 0;

GPIO_InitTypeDef GPIO_InitStructPrivate = {0};
uint32_t previousMillis = 0;
uint32_t currentMillis = 0;
uint8_t keyPressed = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */
int calculate_angle(char *input);
void move_servo(int angle);
void clear_input_buffer(void);
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
  MX_TIM2_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);


     HD44780_Init(2);
     HD44780_Clear();
     HD44780_SetCursor(0,0);
     HD44780_PrintStr("HELLO");
     HD44780_SetCursor(10,1);
     HD44780_PrintStr("WORLD");
     HAL_Delay(2000);

     HD44780_Clear();
     HD44780_SetCursor(0,0);
     HD44780_PrintStr("HI Ds");
     HAL_Delay(2000);
     HD44780_NoBacklight();
     HAL_Delay(2000);
     HD44780_Backlight();

     HAL_Delay(2000);
     HD44780_Cursor();
     HAL_Delay(2000);
     HD44780_Blink();
     HAL_Delay(5000);
     HD44780_NoBlink();
     HAL_Delay(2000);
     HD44780_NoCursor();
     HAL_Delay(2000);

     HD44780_NoDisplay();
     HAL_Delay(2000);
     HD44780_Display();

     HD44780_Clear();
     HD44780_SetCursor(0,0);
     HD44780_PrintStr("Embedded s)");


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	 HAL_TIM_PeriodElapsedCallback(&htim2);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 15;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB9 PB8 PB7 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_7|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB3 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA15 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
int value;
void displayEachNumber(char *asciiValue){

	value = atoi(asciiValue); // Convert string to integer
	HD44780_Clear();
	HD44780_SetCursor(0,0);
	HD44780_PrintStr(value);
}


int angle;
int calculate_angle(char *input)
{

  HD44780_Clear();
  HD44780_SetCursor(0,0);
  HD44780_PrintStr(input);

  // Convert the three-digit input to an integer angle value (0-180)
  angle = atoi(input); // Convert string to integer
  // Constrain the angle between 0 and 180
  angle = angle < 0 ? 0 : (angle > 180 ? 180 : angle); // Ensure angle is within valid range
  return angle; // Return the calculated angle
}

int pulse_width;
void move_servo(int angle)
{
  // Convert the angle to the corresponding PWM pulse width
  // Adjust the calculation according to your servo specifications
    pulse_width = 250 + (angle * 999) / 180; // Modified calculation for pulse width
	//pulse_width =1249;
  // Update the PWM pulse width
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pulse_width); // Set PWM pulse width for servo
}



void clear_input_buffer(void)
{
  // Reset the input buffer and index
  for (int i = 0; i < INPUT_BUFFER_SIZE; i++)
  {
    input_buffer[i] = '\0'; // Set each element of the buffer to null character
  }
  buffer_index = 0; // Reset the buffer index to start receiving new input
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim2) {
    if (htim2->Instance == TIM2) {
        // Toggle the onboard LED on GPIO pin PA5
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
       HAL_Delay(3000);
    }
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  currentMillis = HAL_GetTick();
  if (currentMillis - previousMillis > 10) {
    /*Configure GPIO pins : PB6 PB7 PB8 PB9 to GPIO_INPUT*/
    GPIO_InitStructPrivate.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStructPrivate.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructPrivate.Pull = GPIO_NOPULL;
    GPIO_InitStructPrivate.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructPrivate);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
    if(GPIO_Pin == GPIO_PIN_6 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6))
    {
      keyPressed = 68; //ASCII value of D
    }
    else if(GPIO_Pin == GPIO_PIN_7 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
    {
      keyPressed = 67; //ASCII value of C
    }
    else if(GPIO_Pin == GPIO_PIN_8 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8))
    {
      keyPressed = 66; //ASCII value of B
    }
    else if(GPIO_Pin == GPIO_PIN_9 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9))
    {
      keyPressed = 65; //ASCII value of A
    }

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
    if(GPIO_Pin == GPIO_PIN_6 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6))
    {
      keyPressed = 35; //ASCII value of #
    }
    else if(GPIO_Pin == GPIO_PIN_7 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
    {
      keyPressed = 57; //ASCII value of 9
      HD44780_Clear();
      HD44780_SetCursor(0,0);
      HD44780_PrintStr(keyPressed);
      //__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 1249);
    }
    else if(GPIO_Pin == GPIO_PIN_8 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8))
    {
      keyPressed = 54; //ASCII value of 6
      //__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 916);

//      HD44780_Clear();
//      HD44780_SetCursor(0,0);
//      HD44780_PrintStr("60");
     // HAL_Delay(1000);
    }
    else if(GPIO_Pin == GPIO_PIN_9 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9))
    {
      keyPressed = 51; //ASCII value of 3
//      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 583);
//      HD44780_Clear();
//      HD44780_SetCursor(0,0);
//      HD44780_PrintStr("30");
    }

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
    if(GPIO_Pin == GPIO_PIN_6 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6))
    {
      keyPressed = 48; //ASCII value of 0
//      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 250);
//      HD44780_Clear();
//      HD44780_SetCursor(0,0);
//      HD44780_PrintStr("0");
    }
    else if(GPIO_Pin == GPIO_PIN_7 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
    {
      keyPressed = 56; //ASCII value of 8
//      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 1138);
     //jdam
    }
    else if(GPIO_Pin == GPIO_PIN_8 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8))
    {
      keyPressed = 53; //ASCII value of 5
//      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 805);
//      HD44780_Clear();
//      HD44780_SetCursor(0,0);
//      HD44780_PrintStr("50");
    }
    else if(GPIO_Pin == GPIO_PIN_9 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9))
    {
      keyPressed = 50; //ASCII value of 2
      displayEachNumber(keyPressed);
//      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 472);
//      HD44780_Clear();
//      HD44780_SetCursor(0,0);
//      HD44780_PrintStr("20");
    }

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
    if(GPIO_Pin == GPIO_PIN_6 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6))
    {
      keyPressed = 42; //ASCII value of *
//      HD44780_Clear();
//      HD44780_SetCursor(0,0);
//      HD44780_PrintStr("Not valid");
    }
    else if(GPIO_Pin == GPIO_PIN_7 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
    {
      keyPressed = 55; //ASCII value of 7
//      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 1027);
//      HD44780_Clear();
//      HD44780_SetCursor(0,0);
//      HD44780_PrintStr("70");
    }
    else if(GPIO_Pin == GPIO_PIN_8 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8))
    {
      keyPressed = 52; //ASCII value of 4
//      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 694);
//      HD44780_Clear();
//      HD44780_SetCursor(0,0);
//      HD44780_PrintStr("40");
    }
    else if(GPIO_Pin == GPIO_PIN_9 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9))
    {
      keyPressed = 49; //ASCII value of 1
//      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 361);
//      HD44780_Clear();
//      HD44780_SetCursor(0,0);
//      HD44780_PrintStr("10");
    }

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
    /*Configure GPIO pins : PB6 PB7 PB8 PB9 back to EXTI*/
    GPIO_InitStructPrivate.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStructPrivate.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructPrivate);
    previousMillis = currentMillis;


    if (buffer_index < INPUT_BUFFER_SIZE - 1) {


        input_buffer[buffer_index++] = keyPressed; // Store pressed key in the buffer

    }

  if (buffer_index == INPUT_BUFFER_SIZE - 1 && keyPressed == 35) { // '#' key pressed

	  input_buffer[buffer_index] = '\0'; // Null-terminate the string
//      HD44780_Clear();
//      HD44780_SetCursor(0,0);
     // HD44780_PrintStr(input_buffer);
      int angle = calculate_angle(input_buffer);
      move_servo(angle);
      clear_input_buffer();

    }
  }
}
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

#ifdef  USE_FULL_ASSERT
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
