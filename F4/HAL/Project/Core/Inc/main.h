/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Luggage_Pin GPIO_PIN_2
#define Luggage_GPIO_Port GPIOE
#define Seat2_Display_Pin GPIO_PIN_3
#define Seat2_Display_GPIO_Port GPIOE
#define Seat1_Display_Pin GPIO_PIN_4
#define Seat1_Display_GPIO_Port GPIOE
#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOE
#define Key_Rest_Pin GPIO_PIN_0
#define Key_Rest_GPIO_Port GPIOF
#define Chair_Dir_Pin GPIO_PIN_1
#define Chair_Dir_GPIO_Port GPIOF
#define Other_Singal_Pin GPIO_PIN_2
#define Other_Singal_GPIO_Port GPIOF
#define Desk_Signal_Pin GPIO_PIN_3
#define Desk_Signal_GPIO_Port GPIOF
#define VOICE_Pin GPIO_PIN_4
#define VOICE_GPIO_Port GPIOF
#define usb_log_Pin GPIO_PIN_0
#define usb_log_GPIO_Port GPIOA
#define usb_logA1_Pin GPIO_PIN_1
#define usb_logA1_GPIO_Port GPIOA
#define W25Qxx_CS_Pin GPIO_PIN_4
#define W25Qxx_CS_GPIO_Port GPIOA
#define LED_RUN_Pin GPIO_PIN_15
#define LED_RUN_GPIO_Port GPIOB
#define Backrest_ADJ_Pin GPIO_PIN_9
#define Backrest_ADJ_GPIO_Port GPIOC
#define Legsupt_ADJ_Pin GPIO_PIN_11
#define Legsupt_ADJ_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
