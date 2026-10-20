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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUT1_Pin GPIO_PIN_0
#define BUT1_GPIO_Port GPIOA
#define BUT2_Pin GPIO_PIN_1
#define BUT2_GPIO_Port GPIOA
#define BUT3_Pin GPIO_PIN_2
#define BUT3_GPIO_Port GPIOA
#define DISP_EXTMODE_Pin GPIO_PIN_4
#define DISP_EXTMODE_GPIO_Port GPIOA
#define DISP_SCLK_Pin GPIO_PIN_5
#define DISP_SCLK_GPIO_Port GPIOA
#define DISP_SI_Pin GPIO_PIN_7
#define DISP_SI_GPIO_Port GPIOA
#define DISP_SCS_Pin GPIO_PIN_0
#define DISP_SCS_GPIO_Port GPIOB
#define DISP_EXTCOMIN_Pin GPIO_PIN_1
#define DISP_EXTCOMIN_GPIO_Port GPIOB
#define DISP_DISP_Pin GPIO_PIN_2
#define DISP_DISP_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
