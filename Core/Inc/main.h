/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern uint8_t data_buf[256];
extern volatile uint16_t page_ptr;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FLASH_nRST_Pin GPIO_PIN_3
#define FLASH_nRST_GPIO_Port GPIOA
#define FLASH_CS_GPIO_Port_Pin GPIO_PIN_4
#define FLASH_CS_GPIO_Port_GPIO_Port GPIOA
#define ECG_CS_Pin GPIO_PIN_0
#define ECG_CS_GPIO_Port GPIOB
#define SPI_CS_Pin GPIO_PIN_12
#define SPI_CS_GPIO_Port GPIOB
#define SPI_CS_EXTI_IRQn EXTI15_10_IRQn
#define LED_Out_Pin GPIO_PIN_15
#define LED_Out_GPIO_Port GPIOA
#define ECG_DR_Pin GPIO_PIN_6
#define ECG_DR_GPIO_Port GPIOB
#define ECG_DR_EXTI_IRQn EXTI9_5_IRQn
#define ECG_ALARM_Pin GPIO_PIN_7
#define ECG_ALARM_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
